/*
 * See http://stackoverflow.com/a/8782978/467582
 */


#include "meminfo.h"


/*
 * Macros
 */


#define DIE(...) die(__FILE__, __LINE__, __VA_ARGS__);
#define ARRAY_SIZE(x)  (sizeof(x) / sizeof(x[0]))


/*
 * Utility functions
 */


/**
 * From http://www.lemoda.net/c/die/index.html
 * @param filename name of the .c file that called die()
 * @param line_number
 * @param format format passed to printf()
 * @param ... arguments passed to printf()
 */
void
die (const char* filename, int line_number, const char * format, ...)
{
    va_list vargs;
    va_start (vargs, format);
    fprintf (stderr, "%s:%d: ", filename, line_number);
    vfprintf (stderr, format, vargs);
    fprintf (stderr, "\n");
    exit (EXIT_FAILURE);
}

void printsize(const char* format, double bytes)
{
    char prefixes[] = { 'B', 'K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y' };
    int i;
    double cur_size = 1024;
    for (i = 0; i < ARRAY_SIZE(prefixes); i++)
    {
        if (bytes < cur_size)
        {
            double rounded = bytes / (cur_size / 1024);
            printf("%s %6.2f %ciB (%zu bytes)\n", format, rounded, prefixes[i], (size_t) bytes);
            return;
        }
        cur_size *= 1024;
    }
}


/*
 * Main
 */


/*
(int [2]) mib = {
  [0] = 6
  [1] = 24
}
(int64_t) mem_phys = 17179869184
(size_t) length = 8
(mach_msg_type_number_t) count = 15
(vm_statistics_data_t) vmstat = {
  free_count = 2009359
  active_count = 828938
  inactive_count = 250995
  wire_count = 747704
  zero_fill_count = 467736689
  reactivations = 3151718
  pageins = 36328070
  pageouts = 133478
  faults = 1109587216
  cow_faults = 22870451
  lookups = 2084840
  hits = 29
  purgeable_count = 8800
  purges = 272352
  speculative_count = 84424
}
 */


// From http://stackoverflow.com/a/8782978/467582
int
main()
{
    meminfo_t meminfo = get_meminfo();

    printf("CTL_HW = %i\n", CTL_HW);
    printf("HW_MEMSIZE = %i\n", HW_MEMSIZE);
    printf("\n");

    printf("Memory\n");
    printf("------\n");
    printsize("phys:     ", meminfo.total_bytes);
    printsize("wired:    ", meminfo.wired_bytes);
    printsize("active:   ", meminfo.active_bytes);
    printsize("inactive: ", meminfo.inactive_bytes);
    printsize("free:     ", meminfo.free_bytes);
}

// From http://stackoverflow.com/a/8782978/467582
meminfo_t
get_meminfo()
{
    // 1. Getting the machine's physical memory is simple with sysctl:

    int mib [] = { CTL_HW, HW_MEMSIZE };
    int64_t mem_phys = 0;
    size_t length = sizeof(mem_phys);

/*
sysctl  --  (libc, -lc)  --  /usr/lib/libc.dylib, /usr/lib/system/libsystem_c.dylib, /usr/lib/system/libsystem_kernel.dylib
    args:
       int    *name;    // integer vector describing variable
       int     nlen;    // length of this vector
       void   *oldval;  // 0 or address where to store old value
       size_t *oldlenp; // available room for old value
                           overwritten by actual size of old value
       void   *newval;  // 0 or address of new value
       size_t  newlen;  // size of new value
*/

    if (-1 == sysctl(mib, 2, &mem_phys, &length, NULL, 0))
        DIE("ERROR: sysctl() failed");

    // Physical memory is now in mem_phys

    // 2. VM stats are only slightly trickier:

    mach_msg_type_number_t count = HOST_VM_INFO_COUNT; // uint
    vm_statistics_data_t vmstat; // struct

    mach_port_t host_priv = mach_host_self(); // uint
    host_info_t host_info = (host_info_t)&vmstat; // intptr

    // defined in /usr/include/mach/host_info.h
    int flavor = HOST_VM_INFO;

    kern_return_t kern_return = host_statistics(host_priv, flavor, host_info, &count); // int
    kern_return_t kern_success = KERN_SUCCESS;

/*
// See: http://www.gnu.org/software/hurd/gnumach-doc/Message-Format.html
//      http://web.mit.edu/darwin/src/modules/xnu/osfmk/man/host_statistics.html

kern_return_t   host_statistics
                (host_priv_t                          host_priv,   // unsigned int
                 host_flavor_t                           flavor,   // unsigned int
                 host_info_t                          host_info,   // ref vm_statistics_data_t (IntPtr)
                 mach_msg_type_number_t         host_info_count);  // unsigned int  (natural_t == __darwin_natural_t)  // defined in /usr/include/mach/i386/vm_types.h
*/

    // if (KERN_SUCCESS != host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmstat, &count))
    if (KERN_SUCCESS != kern_return)
        DIE("ERROR: host_statistics() failed");

    // 3. You can then use the data in vmstat to get the information you'd like:

    double mem_pages_total        = vmstat.wire_count + vmstat.active_count + vmstat.inactive_count + vmstat.free_count;
    double mem_pages_wired_pct    = vmstat.wire_count     / mem_pages_total;
    double mem_pages_active_pct   = vmstat.active_count   / mem_pages_total;
    double mem_pages_inactive_pct = vmstat.inactive_count / mem_pages_total;
    double mem_pages_free_pct     = vmstat.free_count     / mem_pages_total;

    double mem_bytes_wired    = mem_pages_wired_pct    * mem_phys;
    double mem_bytes_active   = mem_pages_active_pct   * mem_phys;
    double mem_bytes_inactive = mem_pages_inactive_pct * mem_phys;
    double mem_bytes_free     = mem_pages_free_pct     * mem_phys;

    meminfo_t meminfo = {
        mem_phys,
        mem_bytes_wired,
        mem_bytes_active,
        mem_bytes_inactive,
        mem_bytes_free
    };

    return meminfo;

    // 4. There is also a 64-bit version of the interface.
}

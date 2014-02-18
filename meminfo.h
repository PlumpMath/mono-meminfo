
#ifndef MEMTEST_H
#define MEMTEST_H


#include <libgen.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _SYSLIMITS_H_
#include <syslimits.h>
#endif
#ifdef _SYS_SYSLIMITS_H_
#include <sys/syslimits.h>
#endif

// sysctl():
#include <sys/types.h>
#include <sys/sysctl.h>

// host_statistics() and mach_host_self():
#include <mach/mach.h>

// typedef natural_t mach_msg_type_number_t:
// #include <mach/message.h>

// typedef __darwin_natural_t natural_t:
// #include <mach/machine/vm_types.h>

// HOST_VM_INFO_COUNT:
// #include <mach/host_info.h>


#ifdef  __cplusplus
extern "C" {
#endif


typedef struct meminfo_struct {
    unsigned long total_bytes;
    unsigned long wired_bytes;
    unsigned long active_bytes;
    unsigned long inactive_bytes;
    unsigned long free_bytes;
} meminfo_t;


meminfo_t
get_meminfo();


#ifdef  __cplusplus
}
#endif


#endif  /* MEMTEST_H */


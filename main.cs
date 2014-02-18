using System;
using System.Runtime.InteropServices;

public static class MainModule
{
    public static void Main(string[] args)
    {
        meminfo_t meminfo = libmeminfo.get_meminfo();

        Console.WriteLine("total:    {0} bytes", meminfo.total_bytes);
        Console.WriteLine("free:     {0} bytes", meminfo.free_bytes);
        Console.WriteLine("-------------------");
        Console.WriteLine("wired:    {0} bytes", meminfo.wired_bytes);
        Console.WriteLine("active:   {0} bytes", meminfo.active_bytes);
        Console.WriteLine("inactive: {0} bytes", meminfo.inactive_bytes);

        //Console.WriteLine("HOST_INFO_MAX = {0}", libmeminfo.HOST_INFO_MAX);
    }
}
using System;
using System.Runtime.InteropServices;

public static class MainModule
{
    public static void Main(string[] args)
    {
        meminfo_t meminfo = libmeminfo.get_meminfo();

        // Console.WriteLine("total:    {0} bytes", meminfo.total_bytes);
        // Console.WriteLine("free:     {0} bytes", meminfo.free_bytes);
        // Console.WriteLine("-------------------");
        // Console.WriteLine("wired:    {0} bytes", meminfo.wired_bytes);
        // Console.WriteLine("active:   {0} bytes", meminfo.active_bytes);
        // Console.WriteLine("inactive: {0} bytes", meminfo.inactive_bytes);

        Console.WriteLine("Memory Usage");
        Console.WriteLine("------------");
        PrintBytes("Total   ", meminfo.total_bytes);
        PrintBytes("Free    ", meminfo.free_bytes);
        PrintBytes("Wired   ", meminfo.wired_bytes);
        PrintBytes("Active  ", meminfo.active_bytes);
        PrintBytes("Inactive", meminfo.inactive_bytes);

        //Console.WriteLine("HOST_INFO_MAX = {0}", libmeminfo.HOST_INFO_MAX);
    }

    private static void PrintBytes(string desc, ulong numBytes)
    {
        var friendly = HumanFriendlyFileSize(numBytes);
        Console.WriteLine("{0} : {1} ({2:N0} bytes)", desc, friendly, numBytes);
    }

    /// <summary>
    ///     Generates a human-friendly file size string (e.g., <c>"2.1 GiB"</c>).
    /// </summary>
    /// <param name="byteCount">File size in bytes.</param>
    /// <returns>
    ///     Human-friendly string representation of the file size specified by <paramref name="byteCount"/>.
    /// </returns>
    /// <seealso cref="http://stackoverflow.com/a/4975942/467582"/>
    public static string HumanFriendlyFileSize(ulong byteCount)
    {
        string[] suf = { "B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB" }; // Longs run out around EB
        if (byteCount == 0)
            return "0 " + suf[0];
        int place = Convert.ToInt32(Math.Floor(Math.Log(byteCount, 1024)));
        double num = Math.Round(byteCount / Math.Pow(1024, place), 1);
        string fmt = place == 0 ? "0" : "0.0";
        return string.Format("{0} {1}", num.ToString(fmt), suf[place]);
    }

    public static string FormatFileSize(long filesize, ushort maxFractionalDigits = 1)
    {
        string[] sizes = { "B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB" };
        double len = filesize;
        var order = 0;
        while (len >= 1024 && order + 1 < sizes.Length)
        {
            order++;
            len = len / 1024;
        }

        var fractionalFormat = maxFractionalDigits > 0 ? "." + new string('#', maxFractionalDigits) : "";

        // Adjust the format string to your preferences. For example "{0:0.#}{1}" would
        // show a single decimal place, and no space.
        return string.Format("{0:0" + fractionalFormat + "} {1}", len, sizes[order]);
    }
}
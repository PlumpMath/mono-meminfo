# SWIG Test: C interop with Mono/C# on Mac OS X 10.9 (Mavericks)

Sample output:

    Memory Usage
    ------------
    Total    : 2.0 GiB (2,147,483,648 bytes)
    Free     : 263.0 MiB (275,749,123 bytes)
    Wired    : 230.8 MiB (242,062,891 bytes)
    Active   : 814.6 MiB (854,146,283 bytes)
    Inactive : 739.6 MiB (775,525,348 bytes)

## Requirements

*   Mac OS X 10.9 Mavericks or newer
*   Xcode 5 + command line tools
    *   clang
    *   make
*   brew
    *   binutils
    *   swig

## Compiling / Running

### All In One

```bash
make
```

### Separate

```bash
make clean swig
```

followed by:

```bash
make mono run
```

Alternatives
============

For memory information, you can also run ```/usr/bin/vm_stat```:

    Mach Virtual Memory Statistics: (page size of 4096 bytes)
    Pages free:                                1850.
    Pages active:                            593980.
    Pages inactive:                          587724.
    Pages speculative:                          330.
    Pages throttled:                              0.
    Pages wired down:                       2433464.
    Pages purgeable:                            403.
    "Translation faults":                1156469357.
    Pages copy-on-write:                   26490573.
    Pages zero filled:                    490893797.
    Pages reactivated:                      5166920.
    Pages purged:                            318757.
    File-backed pages:                       180279.
    Anonymous pages:                        1001755.
    Pages stored in compressor:             1475040.
    Pages occupied by compressor:            574639.
    Decompressions:                         5124671.
    Compressions:                           9140533.
    Pageins:                               38687398.
    Pageouts:                                281931.
    Swapins:                                  76698.
    Swapouts:                                353785.

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

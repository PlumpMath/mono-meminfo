# SWIG Test: C interop with Mono/C# on Mac OS X 10.9 (Mavericks)

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

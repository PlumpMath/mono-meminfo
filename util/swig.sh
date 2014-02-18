#!/bin/bash

UNAME=`uname`

if [ "$UNAME" = 'Darwin' ]; then
    LIB_EXT=.dylib
else
    LIB_EXT=.so
fi

swig -csharp libmeminfo.i
clang -arch i386 -c -fpic *.c
clang -arch i386 -shared *.o -o libmeminfo"$LIB_EXT"
lipo -info *.dylib

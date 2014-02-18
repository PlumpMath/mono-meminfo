#!/bin/bash

mv meminfo.c{,.bak}
mv meminfo.h{,.bak}
mv main.cs{,.bak}

rm -rf *.c *.cs *.o *.so *.dylib *.exe

mv meminfo.c{.bak,}
mv meminfo.h{.bak,}
mv main.cs{.bak,}

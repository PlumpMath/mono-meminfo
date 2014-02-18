#!/bin/bash

# -main:CLASS
# -target:[exe|winexe|library|module]
# -out:FILE

dmcs -main:MainModule -out:meminfo.exe *.cs

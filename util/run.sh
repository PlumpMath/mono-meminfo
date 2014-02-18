#!/bin/bash

if [ "$DEBUG" == '1' ]; then
    MONO_LOG_LEVEL=debug mono ./meminfo.exe
else
    mono ./meminfo.exe
fi

%module libmeminfo
%{
/* Includes the header in the wrapper code */
#include "meminfo.h"
%}

/* Parse the header file to generate wrappers */
%include "meminfo.h"

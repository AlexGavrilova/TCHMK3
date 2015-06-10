%module LongNum
%{
/* Includes the header in the wrapper code */
#include "class.h"
%}

/* Parse the header file to generate wrappers */
%include "class.h"

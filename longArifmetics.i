%module longArifmetics
%{
/* Includes the header in the wrapped code */
#include "longArifmetics.h"
%}

%rename(_in) operator >>;
%rename(_out) operator <<;

/* Parse the header file to generate wrappers */
%include "longArifmetics.h"

#ifndef __LUCID_DEBUG_OUT_C__
#define __LUCID_DEBUG_OUT_C__

#include <stdio.h>

#ifdef DEBUG_OUT_ENABLED
    #define DEBUG_OUT(str) puts(str)
#else
    #define DEBUG_OUT(str)
#endif

#endif
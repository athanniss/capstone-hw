#ifndef __LUCID_DEBUG_OUT_H__
#define __LUCID_DEBUG_OUT_H__

#include <stdio.h>

#define DEBUG_OUT_ENABLED

#ifdef DEBUG_OUT_ENABLED
    #define DEBUG_OUT(str) puts(str)
    #define DEBUG_PRINTF(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
    #define DEBUG_OUT(str)
#endif

#endif
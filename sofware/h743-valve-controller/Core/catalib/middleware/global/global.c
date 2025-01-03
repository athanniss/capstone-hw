#ifndef __LUCID_GLOBAL_C__
#define __LUCID_GLOBAL_C__

#include "global.h"

static volatile uint32_t gLucidGlobalTime_ms = 0;

void LC_Global_IncrementMsTick(void)
{
    gLucidGlobalTime_ms++;
}

uint32_t LC_Global_GetRuntime_ms(void)
{
    return gLucidGlobalTime_ms;
}

uint32_t LC_Global_GetElapsedTime_ms(uint32_t previousTime_ms)
{
    uint32_t elapsedTime_ms = 0;

    if(gLucidGlobalTime_ms >= previousTime_ms)
        elapsedTime_ms = gLucidGlobalTime_ms - previousTime_ms;
    else
        // Overflow of gLucidGlobalTime_ms has occured
        elapsedTime_ms = (UINT32_MAX - previousTime_ms) + gLucidGlobalTime_ms;

    return elapsedTime_ms;
}

#endif
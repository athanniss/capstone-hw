#ifndef __LUCID_GLOBAL_H__
#define __LUCID_GLOBAL_H__

#include <stdint.h>

void        LC_Global_IncrementMsTick(void);
uint32_t    LC_Global_GetElapsedTime_ms(uint32_t previousTime_ms);
uint32_t    LC_Global_GetRuntime_ms(void);


#endif
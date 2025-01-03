#ifndef __LUCID_ROTARY_ENCODER_H__
#define __LUCID_ROTARY_ENCODER_H__

#include <stdint.h>
#include "rotary-encoder-conf.h"

typedef enum
{
    eENCODER_PIN_STATE_INVALID,
    eENCODER_PIN_STATE_HIGH,
    eENCODER_PIN_STATE_LOW,
}lucidEncoder_State_e;

void        LC_RotaryEncoder_Init(void);
void        LC_RotaryEncoder_Handler();
int32_t     LC_RotaryEncoder_GetCount(lucidEncoder_e encoder);
uint32_t    LC_RotaryEncoder_GetAcceleration(lucidEncoder_e encoder);

#endif
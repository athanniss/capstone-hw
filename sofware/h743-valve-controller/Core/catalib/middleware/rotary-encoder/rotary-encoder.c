#ifndef __ROTARY_ENCODER_C__
#define __ROTARY_ENCODER_C__

#include "global.h"
#include "rotary-encoder.h"
#include "rotary-encoder-if.h"
#include <stddef.h>
#include "debug-out.h"

static volatile uint32_t gLucidEncoderPreviousTime_ms = 0;
static volatile uint32_t gLucidRotaryEncodersElapsedTime_ms = 0;

typedef struct
{
    uint32_t                debounceTimer_ms;
    uint32_t                encoderAcceleration;

    lucidEncoder_State_e    pinA_PreviousState;
    lucidEncoder_State_e    pinB_PreviousState;
}lucidRotaryEncoder_State_t;

typedef struct
{
    uint32_t debounceTime_ms;
}lucidRotaryEncoder_Settings_t;


typedef struct 
{
    lucidEncoder_e          encoder;
    lucidEncoder_Pin_e      pinA;
    lucidEncoder_Pin_e      pinB;

    int32_t                count;
    void                   (*countCallback)(void);

    lucidRotaryEncoder_State_t state;
    lucidRotaryEncoder_Settings_t settings;
}lucidRotaryEncoder_t;

lucidRotaryEncoder_t gLucidRotaryEncoders[] = 
{
    // WARNING!!! LEAVE debounceTime_ms = 0 FOR NOW !!!!!!!
    { eENCODER1, eENCODER_PIN_1_A, eENCODER_PIN_1_B, 0, NULL, .state = { 0 }, .settings = { .debounceTime_ms = 0 } },
};

#define LUCID_ENCODER_COUNT  (sizeof(gLucidRotaryEncoders)/sizeof(gLucidRotaryEncoders[0]))

void LC_RotaryEncoder_Init(void)
{
    uint8_t cnt = 0;

    for(cnt = 0; cnt < LUCID_ENCODER_COUNT; cnt++)
    {
        gLucidRotaryEncoders[cnt].state.encoderAcceleration = 0;
        gLucidRotaryEncoders[cnt].state.debounceTimer_ms = 0;
        gLucidRotaryEncoders[cnt].state.pinA_PreviousState = LC_RotaryEncoder_GetPinState(gLucidRotaryEncoders[cnt].pinA);
        gLucidRotaryEncoders[cnt].state.pinB_PreviousState = LC_RotaryEncoder_GetPinState(gLucidRotaryEncoders[cnt].pinB);
    }
}

void LC_RotaryEncoder_Handler()
{
    uint8_t cnt = 0;
    uint32_t dT_ms = 0;

    dT_ms = LC_Global_GetElapsedTime_ms(gLucidEncoderPreviousTime_ms);

    if(dT_ms != 0)
    {
        gLucidEncoderPreviousTime_ms = LC_Global_GetRuntime_ms();
        gLucidRotaryEncodersElapsedTime_ms += dT_ms;

        // Check if PinA or PinB changed states
        for(cnt = 0; cnt < LUCID_ENCODER_COUNT; cnt++)
        {
            if(gLucidRotaryEncoders[cnt].state.debounceTimer_ms > 0)
            {
                // Debounce timer is running so block change detection
                gLucidRotaryEncoders[cnt].state.debounceTimer_ms -= dT_ms;
            }

            if(gLucidRotaryEncodersElapsedTime_ms >= 10)
            {
                gLucidRotaryEncodersElapsedTime_ms = 0;

                if(gLucidRotaryEncoders[cnt].state.encoderAcceleration > 0)
                    gLucidRotaryEncoders[cnt].state.encoderAcceleration--;
            }

            if(gLucidRotaryEncoders[cnt].state.debounceTimer_ms <= 0)
            {
                // Debounce timer has expired so update the button state

                lucidEncoder_State_e pinA_State = LC_RotaryEncoder_GetPinState(gLucidRotaryEncoders[cnt].pinA);
                lucidEncoder_State_e pinB_State = LC_RotaryEncoder_GetPinState(gLucidRotaryEncoders[cnt].pinB);            

                // Check Transition of Phase A
                if(gLucidRotaryEncoders[cnt].state.pinA_PreviousState != pinA_State)
                {
                    // Pin A State Change Detected
                    if(pinA_State == eENCODER_PIN_STATE_LOW)
                    {
                        gLucidRotaryEncoders[cnt].state.encoderAcceleration++;

                        if(pinB_State == eENCODER_PIN_STATE_HIGH)
                            gLucidRotaryEncoders[cnt].count++;
                        else
                            gLucidRotaryEncoders[cnt].count--;

                        if(gLucidRotaryEncoders[cnt].countCallback != NULL)
                            gLucidRotaryEncoders[cnt].countCallback();

                        DEBUG_PRINTF("\tDBG Encoder: %li \t %li\n", gLucidRotaryEncoders[cnt].count, gLucidRotaryEncoders[cnt].state.encoderAcceleration);
                    }

                    // Reset the debounce timer Whenever a change has been detected
                    gLucidRotaryEncoders[cnt].state.debounceTimer_ms = gLucidRotaryEncoders[cnt].settings.debounceTime_ms;
                    gLucidRotaryEncoders[cnt].state.pinA_PreviousState = pinA_State;
                }

                // Check Transition of Phase B
                if(gLucidRotaryEncoders[cnt].state.pinB_PreviousState != pinB_State)
                {
                    gLucidRotaryEncoders[cnt].state.encoderAcceleration++;

                    // Pin B State Change Detected
                    if(pinB_State == eENCODER_PIN_STATE_LOW)
                    {
                        if(pinA_State == eENCODER_PIN_STATE_LOW)
                            gLucidRotaryEncoders[cnt].count++;
                        else
                            gLucidRotaryEncoders[cnt].count--;

                        if(gLucidRotaryEncoders[cnt].countCallback != NULL)
                            gLucidRotaryEncoders[cnt].countCallback();

                        DEBUG_PRINTF("\tDBG Encoder: %li \t %li\n", gLucidRotaryEncoders[cnt].count, gLucidRotaryEncoders[cnt].state.encoderAcceleration);
                    }

                    // Reset the debounce timer Whenever a change has been detected
                    gLucidRotaryEncoders[cnt].state.debounceTimer_ms = gLucidRotaryEncoders[cnt].settings.debounceTime_ms;
                    gLucidRotaryEncoders[cnt].state.pinB_PreviousState = pinB_State;
                }                                  
            }
        }

    }
}

int32_t LC_RotaryEncoder_GetCount(lucidEncoder_e encoder)
{
    return gLucidRotaryEncoders[encoder].count;
}


uint32_t LC_RotaryEncoder_GetAcceleration(lucidEncoder_e encoder)
{
    return gLucidRotaryEncoders[encoder].state.encoderAcceleration;
}

#endif


#ifndef __LUCID_ROTARY_ENCODER_IF_C__
#define __LUCID_ROTARY_ENCODER_IF_C__

#include "rotary-encoder.h"
#include "main.h"

typedef struct
{
    lucidEncoder_Pin_e  EncoderPin;
    GPIO_TypeDef        *EncoderPort;
    uint32_t            EncoderMcuPin;
}lucidRotaryEncoder_PinDefinition_t;

static lucidRotaryEncoder_PinDefinition_t gLucidEncoder_PinDefinition_If[] = 
{
    { eENCODER_PIN_1_A,        USR_ENC1_A_GPIO_Port,     USR_ENC1_A_Pin},
    { eENCODER_PIN_1_B,        USR_ENC1_B_GPIO_Port,     USR_ENC1_B_Pin},
};

#define LUCID_ENCODER_PIN_CNT  (sizeof(gLucidEncoder_PinDefinition_If)/sizeof(gLucidEncoder_PinDefinition_If[0]))

/**
 * @brief  Get the state of a specified rotary encoder pin.
 * 
 * This function checks the state of the specified rotary encoder pin and returns
 * whether the pin is in a high or low state.
 * 
 * @param  encoderPin The pin of the rotary encoder to check. This should be a value
 *                    of type `lucidEncoder_Pin_e` and must be less than `LUCID_ENCODER_PIN_CNT`.
 * 
 * @return The state of the specified rotary encoder pin. This will be one of the following:
 *         - eENCODER_PIN_STATE_HIGH if the pin is high.
 *         - eENCODER_PIN_STATE_LOW if the pin is low.
 *         - eENCODER_PIN_STATE_INVALID if the specified pin is out of range.
 */
lucidEncoder_State_e LC_RotaryEncoder_GetPinState(lucidEncoder_Pin_e encoderPin)
{
    lucidEncoder_State_e retVal = eENCODER_PIN_STATE_INVALID;

    if(encoderPin < LUCID_ENCODER_PIN_CNT)
    {
        if(LL_GPIO_IsInputPinSet(gLucidEncoder_PinDefinition_If[encoderPin].EncoderPort, gLucidEncoder_PinDefinition_If[encoderPin].EncoderMcuPin))
            retVal = eENCODER_PIN_STATE_HIGH;
        else
            retVal = eENCODER_PIN_STATE_LOW;
    }

    return retVal;
}

#endif
#ifndef __LUCID_BUTTON_C__
#define __LUCID_BUTTON_C__

#include "button.h"
#include "main.h"

typedef struct
{
    lucidButton_e       Button;
    GPIO_TypeDef        *ButtonPort;
    uint32_t            ButtonPin;
}lucidButton_if_t;

static lucidButton_if_t gLucidButton_PinDefinition_If[] = 
{
    {eBUTTON_USER_A,        USR_SW_2_GPIO_Port,     USR_SW_2_Pin},
    {eBUTTON_USER_B,        USR_SW_1_GPIO_Port,     USR_SW_1_Pin},
    {eBUTTON_ENCODER_A,     USR_SW_ENC_GPIO_Port,   USR_SW_ENC_Pin},
};

#define LUCID_BUTTON_COUNT  (sizeof(gLucidButton_PinDefinition_If)/sizeof(gLucidButton_PinDefinition_If[0]))

lucidButton_State_e LC_Button_GetState(lucidButton_t *button)
{
    lucidButton_State_e retVal = eBUTTON_STATE_INVALID;

    if(button != NULL && button->button < LUCID_BUTTON_COUNT)
    {
        if(LL_GPIO_IsInputPinSet(gLucidButton_PinDefinition_If[button->button].ButtonPort, gLucidButton_PinDefinition_If[button->button].ButtonPin))
            retVal = eBUTTON_STATE_RELEASED;
        else
            retVal = eBUTTON_STATE_PRESSED;
    }

    return retVal;
}

#endif
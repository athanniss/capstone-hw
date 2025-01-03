#ifndef __LUCID_LED_IF_C__
#define __LUCID_LED_IF_C__

#include "main.h"
#include "led.h"

typedef struct
{
    lucidLed_e       Led;
    GPIO_TypeDef     *LedPort;
    uint32_t         LedPin;
}lucidLed_if_t;

static lucidLed_if_t gLucidLedPinDefinition_If[] = 
{
    { eLED_USER_AMBER,       LED_USR_1_GPIO_Port,    LED_USR_1_Pin },
    { eLED_USER_BLUE,        LED_USR_2_GPIO_Port,    LED_USR_2_Pin },
    { eLED_USER_RED,         LED_USR_3_GPIO_Port,    LED_USR_3_Pin },
};

#define LUCID_LED_COUNT  (sizeof(gLucidLedPinDefinition_If)/sizeof(gLucidLedPinDefinition_If[0]))

void LC_Button_SetState(lucidLed_e led, lucidLed_State_e state)
{
    if(led < LUCID_LED_COUNT)
    {
        if(state == eBUTTON_STATE_OFF)
            LL_GPIO_ResetOutputPin(gLucidLedPinDefinition_If[led].LedPort, gLucidLedPinDefinition_If[led].LedPin);
        else
            LL_GPIO_SetOutputPin(gLucidLedPinDefinition_If[led].LedPort, gLucidLedPinDefinition_If[led].LedPin);
    }
}

#endif
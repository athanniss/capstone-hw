#ifndef __LUCID_LED_H__
#define __LUCID_LED_H__

typedef enum
{
    eLED_USER_AMBER = 0,
    eLED_USER_BLUE,
    eLED_USER_RED,
}lucidLed_e;

typedef enum
{
    eBUTTON_STATE_TOGGLE,
    eBUTTON_STATE_ON,
    eBUTTON_STATE_OFF,
}lucidLed_State_e;

#endif
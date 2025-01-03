#ifndef __LUCID_BUTTON_H__
#define __LUCID_BUTTON_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum
{
    eBUTTON_USER_A = 0,
    eBUTTON_USER_B,
    eBUTTON_ENCODER_A,
}lucidButton_e;

typedef enum
{
    eBUTTON_STATE_INVALID,
    eBUTTON_STATE_PRESSED,
    eBUTTON_STATE_RELEASED,
}lucidButton_State_e;

typedef struct 
{
    uint16_t debounceTime_ms;
    uint16_t longPressTime_ms;
    uint16_t longPressTickTime_ms;
}lucidButton_Settings_t;

typedef struct 
{
    void (*pressCallback)(void);
    void (*releaseCallback)(void);
    void (*longPressCallback)(void);
    void (*longPressTickCallback)(void);
}lucidButton_Callbacks_t;

typedef struct 
{
    lucidButton_e           button;
    lucidButton_State_e     previousState;

    int16_t                 debounceTimer_ms;
    int16_t                 longPressTimer_ms;
    int16_t                 longPressTickTimer_ms;
    bool                    isLongPressDetected;

    lucidButton_Settings_t      settings;
    lucidButton_Callbacks_t     callbacks;
}lucidButton_t;

void LC_Button_Init(void);
void LC_Button_Handler(void);

lucidButton_State_e LC_Button_GetState(lucidButton_t *button);

#endif
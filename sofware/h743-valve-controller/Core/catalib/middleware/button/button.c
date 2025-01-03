#ifndef __LUCID_BUTTON_C__
#define __LUCID_BUTTON_C__

#include "button.h"
#include <stdbool.h>
#include "debug-out.h"
#include "global.h"

static volatile uint32_t gLucidButtonPreviousTime_ms = 0;

static void LC_Button_HandleStateChange(lucidButton_t *button, lucidButton_State_e currentState);
static void LC_Button_HandleLongPress(lucidButton_t *button, uint32_t dT_ms);
static void LC_Button_HandleButtonRelease(lucidButton_t *button);

static lucidButton_t gLucidButtons[] = 
{
    { eBUTTON_USER_A,        .settings = {50, 3000, 500}, .callbacks = {NULL, NULL, NULL, NULL} },
    { eBUTTON_USER_B,        .settings = {50, 3000, 500}, .callbacks = {NULL, NULL, NULL, NULL} },
    { eBUTTON_ENCODER_A,     .settings = {50, 3000, 500}, .callbacks = {NULL, NULL, NULL, NULL} },
};

#define LUCID_BUTTON_COUNT  (sizeof(gLucidButtons)/sizeof(gLucidButtons[0]))

void LC_Button_Init()
{
    uint8_t cnt = 0;

    for(cnt = 0; cnt < LUCID_BUTTON_COUNT; cnt++)
    {
        gLucidButtons[cnt].previousState    = eBUTTON_STATE_RELEASED;

        gLucidButtons[cnt].debounceTimer_ms = 0;
        gLucidButtons[cnt].longPressTimer_ms = 0;
        gLucidButtons[cnt].longPressTickTimer_ms = gLucidButtons[cnt].settings.longPressTickTime_ms;
        gLucidButtons[cnt].isLongPressDetected = false;
    }
}

void LC_Button_Handler()
{
    uint8_t cnt = 0;
    uint32_t dT_ms = 0;

    dT_ms = LC_Global_GetElapsedTime_ms(gLucidButtonPreviousTime_ms);

    if(dT_ms != 0)
    {
        gLucidButtonPreviousTime_ms = LC_Global_GetRuntime_ms();

        for(cnt = 0; cnt < LUCID_BUTTON_COUNT; cnt++)
        {           
           if(gLucidButtons[cnt].debounceTimer_ms > 0)
           {
                // Debounce timer is running so block change detection
                gLucidButtons[cnt].debounceTimer_ms -= dT_ms;
           }
           
           if(gLucidButtons[cnt].debounceTimer_ms <= 0)
           {
                // Debounce timer has expired so update the button state
                lucidButton_State_e currentState = LC_Button_GetState(&gLucidButtons[cnt]);

                // Check for Button Press Change
                if(currentState != gLucidButtons[cnt].previousState)
                {
                    LC_Button_HandleStateChange(&gLucidButtons[cnt], currentState);

                    // Reset the debounce timer
                    gLucidButtons[cnt].debounceTimer_ms = gLucidButtons[cnt].settings.debounceTime_ms;
                }
                // Check for Long Press
                else if(    currentState                        == eBUTTON_STATE_PRESSED    &&
                            gLucidButtons[cnt].previousState    == eBUTTON_STATE_PRESSED)
                {
                    LC_Button_HandleLongPress(&gLucidButtons[cnt], dT_ms);
                }

                gLucidButtons[cnt].previousState = currentState;
           }
        }        
    }
}

static void LC_Button_HandleStateChange(lucidButton_t *button, lucidButton_State_e currentState)
{
    if(button != NULL)
    {
        // Button Press Change Detected
        if(currentState == eBUTTON_STATE_PRESSED)
        {
            DEBUG_OUT("\tDBG Button: Button Press Detected");
            // Button Pressed Callback
            if(button->callbacks.pressCallback != NULL)
                button->callbacks.pressCallback();
        }
        else if(currentState == eBUTTON_STATE_RELEASED)
        {
            DEBUG_OUT("\tDBG Button: Button Release Detected");
        
            // Button Released Callback
            if(button->callbacks.releaseCallback != NULL)
                button->callbacks.releaseCallback();

            LC_Button_HandleButtonRelease(button);
        }
    }
}

static void LC_Button_HandleLongPress(lucidButton_t *button, uint32_t dT_ms)
{
    if(button != NULL)
    {
        // Increment the long press timer
        button->longPressTimer_ms += dT_ms;

        if( button->isLongPressDetected == false &&
            (button->longPressTimer_ms >= button->settings.longPressTime_ms))
        {
            button->isLongPressDetected = true;

            DEBUG_OUT("\tDBG Button: Long Press Detected");
            // Long Press Callback
            if(button->callbacks.longPressCallback != NULL)
                button->callbacks.longPressCallback();                        
        }

        // Long Press Tick
        if(button->longPressTimer_ms >= button->longPressTickTimer_ms)
        {
            DEBUG_OUT("\tDBG Button: Long Press Tick");
            // Increment the long press tick timer:
            button->longPressTickTimer_ms += button->settings.longPressTickTime_ms;

            // Long Press Tick Callback
            if(button->callbacks.longPressTickCallback != NULL)
                button->callbacks.longPressTickCallback();
        }
    }
}

static void LC_Button_HandleButtonRelease(lucidButton_t *button)
{
    if(button != NULL)
    {
        // Reset the Long Press Timers
        button->longPressTimer_ms = 0;
        button->longPressTickTimer_ms = button->settings.longPressTickTime_ms;
        button->isLongPressDetected = false;
    }
}

#endif
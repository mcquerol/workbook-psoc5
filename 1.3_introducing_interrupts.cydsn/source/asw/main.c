/**
* \file main
* \author Peter Fromm
* \date 5.12.2019
*
* \brief Demonstrator for critical regions
*
*/

#include "project.h"
#include "global.h"

#include "button.h"
#include "tft.h"
#include "seven.h"
#include "led.h"
#include "joystick.h"

volatile uint8 toggle = 0;

CY_ISR_PROTO(isr_BUTTON_3);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_BUTTON_3_StartEx(isr_BUTTON_3);
    
    for(;;)
    {
        // Check if the button is pressed
        if (toggle)
        {
            // Toggle the LEDs
            LED_green_Write(1);
            LED_yellow_Write(0);
            LED_red_Write(1);
        }
        else
        {
            // Toggle the LEDs
            LED_green_Write(0);
            LED_yellow_Write(1);
            LED_red_Write(0);
        }
    }
}

/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

CY_ISR(isr_BUTTON_3)
{
    //BUTTON_3_ClearInterrupt();
    
    if(toggle == 0)
    {
        toggle = 1;    
    }
    else
    {
        toggle = 0;    
    }
    
}

/* [] END OF FILE */
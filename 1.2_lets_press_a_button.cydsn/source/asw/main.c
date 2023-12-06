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



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

for(;;)
    {
        //let's read the button
        uint8 buttonStatus = BUTTON_3_Read();
        
        if (buttonStatus != 0)
        {
            LED_green_Write(1);
            LED_yellow_Write(0);
            LED_red_Write(1);
        }
        else
        {
            
        }
    }
}

/********************************************************************************
 * ISR Definitions
 ********************************************************************************/


/* [] END OF FILE */
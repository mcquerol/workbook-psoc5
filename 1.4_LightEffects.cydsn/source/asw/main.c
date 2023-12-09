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

enum eeledColor
{

    yellow,
    red,
    green

};

typedef enum eeledColor ledColor_t;


void setTrafficLight(uint16 delay, ledColor_t color)
{
    switch(color)
    {
        case yellow:
            LED_green_Write(0);
            LED_yellow_Write(1);
            LED_red_Write(0);
        break;
            
        case green:
            LED_green_Write(1);
            LED_yellow_Write(0);
            LED_red_Write(0);
        break;


        case red:
            LED_green_Write(0);
            LED_yellow_Write(0);
            LED_red_Write(1);
        break;
        
    }
    CyDelay(delay*1000);
}



int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    LED_Init();
   
    // Start Operating System
    for(;;)
    {
        //setTrafficLight(2,yellow);
        //setTrafficLight(5,green);
        //setTrafficLight(2,yellow);
        //setTrafficLight(3,red);
        
//        for (int i = 0; i <= 255; i++) {
//            LED_RGB_Set(i,i,i);        
//            // Add a delay to control the fading speed
//            // This delay may need adjustment based on your specific requirements
//            for (volatile int delay = 0; delay < 10000; delay++);
//        }
//        for (int i = 255; i >= 0; i--) {
//            LED_RGB_Set(i,i,i);        
//            // Add a delay to control the fading speed
//            // This delay may need adjustment based on your specific requirements
//            for (volatile int delay = 0; delay < 10000; delay++);
//        }
        
        //TODO fix
        
                for (int i = 0; i <= 255; i++) {
            if (i <= 127) {
                // Red is fading in
                LED_RGB_Set(i, 0, 0);
            } else {
                // Green is fading in while Red is fading out
                LED_RGB_Set(255 - i, i - 127, 0);
            }

            // Add a delay to control the fading speed
            // This delay may need adjustment based on your specific requirements
            for (volatile int delay = 0; delay < 10000; delay++);
        }

        // Fade out
        for (int i = 255; i >= 0; i--) {
            if (i <= 127) {
                // Green is fading out
                LED_RGB_Set(255 - i, i, 0);
            } else {
                // Blue is fading in while Green is fading out
                LED_RGB_Set(0, 255 - i, i - 127);
            }

            // Add a delay to control the fading speed
            // This delay may need adjustment based on your specific requirements
            for (volatile int delay = 0; delay < 10000; delay++);
        }

        // Fade out blue (final stage)
        for (int i = 255; i >= 0; i--) {
            // Blue is fading out
            LED_RGB_Set(0, 255 - i, i);

            // Add a delay to control the fading speed
            // This delay may need adjustment based on your specific requirements
            for (volatile int delay = 0; delay < 10000; delay++);
        }
       
    }
}

/********************************************************************************
 * ISR Definitions
 ********************************************************************************/


/* [] END OF FILE */
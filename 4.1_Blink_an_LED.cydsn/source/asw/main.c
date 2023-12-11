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


//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
   
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
}

void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
    ShutdownOS(0);
    while(1)
    {
    }
}

/********************************************************************************
 * Task Definitions
 ********************************************************************************/

/** TASK tsk_init
 * initializes the UART, LEDs, JOYSTICK, Seven Segment Display and TFT
 * it also activates the extended tasks and displays a
 * welcome message to the user through UART
 * this task is automatically started when the OS is started in the main function
 */
TASK(tsk_init)
{
    //Init MCAL Drivers (uncomment accordinly)
    
     UART_LOG_Start();
//    LED_Init();
//    SEVEN_Init();
//    JOYSTICK_Init();
//    TFT_init();

    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
    
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    //Activate alarms
    SetRelAlarm(alrm_SampleAlarm,1,1000); //sample alarm being triggered every second (change as needed)
    
    //Activate extended tasks
    ActivateTask(tsk_background);
    
    TerminateTask();
}

/** TASK tsk_background
 * low priority task with a nop command
 */
TASK(tsk_background)
{
    while(1)
    {
        __asm("nop");
    }
    
    TerminateTask();
}

/** TASK tsk_SampleTask (change as needed)
 * medium priority task which prints "Hello World\n" to the UART port every second
 */
TASK(tsk_SampleTask)
{
    UART_LOG_PutString("Hello World\n");
    LED_Toggle(LED_ALL);

    TerminateTask();
}

/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

//ISR2()
//{
//}

/* [] END OF FILE */
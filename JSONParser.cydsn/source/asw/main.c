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

#include "Ringbuffer.h"



ringbuffer_t rb; // global ringbuffer object
volatile int endOfStringRecieved = 0;

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
    LED_Init();
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
    //SetRelAlarm(alrm_SampleAlarm,1,1000); //sample alarm being triggered every second (change as needed)
    
    //Activate extended tasks
    ActivateTask(tsk_background);
    ActivateTask(tsk_json);
    
    UART_LOG_PutString("JSON PARSER\n");
    
    ringbuffer_init(&rb,uint8_t_MAX);
    
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


TASK(tsk_json)
{

    while (1)
    {
        EventMaskType ev = 0;
        WaitEvent(ev_endOfString);
        GetEvent(tsk_json, &ev);
        ClearEvent(ev);
        LED_Toggle(LED_ALL);
        if (endOfStringRecieved)
        {
            for (int i = 0; i < rb.m_fillLevel; i++)
            {
                uint8_t tempData;
                ringbuffer_read(&rb,&tempData);;
                UART_LOG_PutChar(tempData);
            }
            // Reset the endOfStringReceived flag
            endOfStringRecieved = 0;
        }

    }

    TerminateTask();
}

TASK(tsk_sampleTask)
{
 
    TerminateTask();
}
/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

ISR2(isr_uart_rx)
{

    LED_Toggle(LED_RED);

    do
    {
        
        char recievedData = UART_LOG_GetChar();
        ringbuffer_write(&rb, recievedData);

        UART_LOG_PutChar(recievedData);
        
        if (recievedData == '0')
        {
            UART_LOG_PutChar(recievedData);
            LED_Toggle(LED_YELLOW);
            endOfStringRecieved = 1;
            SetEvent(tsk_json,ev_endOfString);
        }
        
    }while(UART_LOG_GetRxBufferSize() !=0);
    
        /*Check that the ringbuffer isn't empty, if it is, ignore it*/
    if((rb.m_fillLevel > 0))
    {
        SetEvent(tsk_json, ev_endOfString);
    }
    else
    {
        /*Not a valid message, discard*/
        UART_Log_ClearRxBuffer();
    }

    UART_LOG_PutString(
}

/* [] END OF FILE */
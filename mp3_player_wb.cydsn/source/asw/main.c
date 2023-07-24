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

#include "mp3.h"

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
    
    //Activate extended tasks
    ActivateTask(tsk_logic);
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
TASK(tsk_logic)
{
    EventMaskType ev;
    currState = __state_STANDBY;
    WaitEvent(ev_button);
    GetEvent(tsk_logic, &ev);
    ClearEvent(ev);
    
    while(1)
    {
        switch(currState)
        {
            case __state_STANDBY:
                if((ev & ev_button) && (btnFlag == __flag_nextSong))
                {
                    UART_LOG_PutString("next song\n");
                }
                else if((ev & ev_button) && (btnFlag == __flag_prevSong))
                {
                    UART_LOG_PutString("previous song\n");
                }
                else if((ev & ev_button) && (btnFlag == __flag_playSong))
                {
                    UART_LOG_PutString("play song\n");
                    currState = __state_PLAYING;
                }
                else
                {    
                    LED_Toggle(LED_RED);
                }
                
            break;
            
            case __state_PLAYING:
                if((ev & ev_button) && (btnFlag == __flag_increaseVolume))
                {
                    UART_LOG_PutString("increasing volume\n");
                }
                else if((ev & ev_button) && (btnFlag == __flag_decreaseVolume))
                {
                    UART_LOG_PutString("decreasing volume\n");
                }
                else if((ev & ev_button) && (btnFlag == __flag_pauseSong))
                {
                    UART_LOG_PutString("pause song\n");
                    currState = __state_STANDBY;
                }
                else if((ev & ev_button) && (btnFlag == __flag_skipSong))
                {
                    UART_LOG_PutString("skipping song\n");
                }
                else
                {
                    LED_Toggle(LED_GREEN);
                }
            break;
            
            default:
            break;
        }
    }
    TerminateTask();
}

/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

ISR2(isr_Button)
{
    if(BUTTON_IsPressed(BUTTON_1))
    {
        btnFlag = (currState == __state_STANDBY) ? __flag_nextSong : __flag_increaseVolume;  
        SetEvent(tsk_logic, ev_button);    
    }
    
    if(BUTTON_IsPressed(BUTTON_2))
    {
        btnFlag = (currState == __state_STANDBY) ? __flag_prevSong : __flag_decreaseVolume;  
        SetEvent(tsk_logic, ev_button);    
    }
    
    if(BUTTON_IsPressed(BUTTON_3))
    {
        btnFlag = (currState == __state_STANDBY) ? __flag_playSong : __flag_pauseSong;  
        SetEvent(tsk_logic, ev_button);    
    }
    
    if(BUTTON_IsPressed(BUTTON_4))
    {
        btnFlag = __flag_skipSong;
        SetEvent(tsk_logic, ev_button);    
    }
}


/* [] END OF FILE */
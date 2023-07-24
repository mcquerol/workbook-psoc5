/**
* \file main
* \author Peter Fromm
* \date 5.12.2019
*
* \brief Demonstrator for critical regions
*
*/


#include "global.h"
#include "project.h"

#include "seven.h"
#include "led.h"

#include "time.h"
#include "stdlib.h"
#include "stdio.h"  

    
enum eSTATES
{
    STATE_START,
    STATE_DISPLAYSSD,
    STATE_BUTTONPRESS,
    STATE_TOOSLOW
};

typedef enum eSTATES STATES_t;    
    
STATES_t state;    
boolean_t button; // TRUE = left button, FALSE = right button
static uint8_t timeScore = 0; //keep track of the time;
static uint8_t roundNo = 0;
EventMaskType ev = 0;
int SSDnum;
int randTime;

/* State Functions */
RC_t start();
RC_t displayssd();
RC_t buttonpress();
RC_t tooslow();

/* Message Functions */
void startMessage();
void correctMessage();
void incorrectMessage();
void tooslowMessage();
void finalMessage();

////////////////////////////////////
/* TODO
* get ev timeout working
* do the code for time measuremtn
* do the code for the logging
*/

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
    SEVEN_Init();

    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
    
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    //Activate extended tasks
    ActivateTask(tsk_logic);
    ActivateTask(tsk_background);
    
    UART_LOG_PutString("WELCOME TO THE REACTION GAME!\n");
    
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

TASK(tsk_logic)
{
    while(1)
    {
        WaitEvent(ev_button | ev_randTime | ev_timeout);
        GetEvent(tsk_logic, &ev);
        ClearEvent(ev);
        
        if(roundNo > 10)
        {
            SEVEN_Clear(SEVEN_0);
            SEVEN_Clear(SEVEN_1);
            finalMessage();
            return;
        }
        
        switch(state)
        {
            case STATE_START:
            UART_LOG_PutString("state 1\n");
                start();
            break;
            
            case STATE_DISPLAYSSD:
            UART_LOG_PutString("state 2\n");
                displayssd();
            break;
                
            case STATE_BUTTONPRESS:
            UART_LOG_PutString("state 3\n");
                buttonpress();
                roundNo++;
            break;
            
            case STATE_TOOSLOW:
            UART_LOG_PutString("state 4\n");
                tooslow();
                roundNo++;
                UART_LOG_PutString("state 4aaaaaaa\n");
            break;
                 
            default:
            break;
        }
    }
    TerminateTask();
}

/** TASK tsk_timer
 * Cyclic task being activated every 1ms until the user presses a button
 * the task increases the value of the global reaction time variable
 * once the user presses a button the total time (time of button press - time of SSD activation) it is displayed in UART.
 */
TASK(tsk_timer)
{
   timeScore++;
}

/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

ISR2(isr_Button)
{
    if(BUTTON_1_Read() == 1) // button 1 (left) on PSoC
    {
        SetEvent(tsk_logic,ev_button);
        button = TRUE; //set flag to left
    }
    
    if(BUTTON_2_Read() == 1) // button 2 (right) on PSoC
    {
        SetEvent(tsk_logic,ev_button);
        button = FALSE; //set flag to right
    }
}

RC_t start()
{
    UART_LOG_PutString("Press the left button if a 1 is shown or press the right button if a 2 is shown\n");
    if(((ev & ev_button) && (BUTTON_2_Read() == 1)) || ((ev & ev_button) && (BUTTON_1_Read() == 1)))
	{
       SSDnum = (rand() % 2) + 1; //ssd value
	   randTime = (rand() % 3 + 1) * 1000; //random wait time value
	   CancelAlarm(alrm_randTime);
	   SetRelAlarm(alrm_randTime,randTime,0); // 2 seconds for test purposes
	}
	state = STATE_DISPLAYSSD;
                
    return RC_SUCCESS;
}

RC_t displayssd()
{
    if(ev & ev_randTime)
	{
		if((uint8_t)SSDnum == 1)
		{
			SEVEN_Set(SEVEN_0,1);
			SEVEN_Set(SEVEN_1,1);
		}
		else
		{
			SEVEN_Set(SEVEN_0,2);
			SEVEN_Set(SEVEN_1,2);
		}
        CancelAlarm(alrm_measureTime);
        SetRelAlarm(alrm_measureTime,1,1);
        state = STATE_BUTTONPRESS;
	}
    return RC_SUCCESS;
}

RC_t buttonpress()
{
    CancelAlarm(alrm_measureTime);
	if(ev & ev_button)
	{
        CancelAlarm(alrm_1000ms);
        SetRelAlarm(alrm_1000ms,1000,1);
		if((uint8_t)SSDnum == 1) //if ssd is number 1, user must press the right button
		{
			if((ev & ev_button) && (BUTTON_1_Read() == 1))
			{
                correctMessage();
            }
            else
            {
                incorrectMessage();
            }
		}
        else //if ssd is number 2, user must press the left button
        {
            if((ev & ev_button) && (BUTTON_1_Read() == 1))
            {
                incorrectMessage();
            }
            else
            {
                correctMessage();
            }
        }
	}
    if(GetAlarm(alrm_1000ms,(unsigned int*)1000))
    {
        SetEvent(tsk_logic,ev_timeout);
        state = STATE_TOOSLOW;
    }
    else
    {
        state = STATE_START;
    }
    //clear the displays
    SEVEN_Clear(SEVEN_0);
    SEVEN_Clear(SEVEN_1); 
    return RC_SUCCESS;
}

RC_t tooslow()
{
    if(ev & ev_timeout)
    {
        CancelAlarm(alrm_1000ms);
        tooslowMessage();
		//clear the displays
		SEVEN_Clear(SEVEN_0);
		SEVEN_Clear(SEVEN_1);
        
    }
    state = STATE_START;
    
    return RC_SUCCESS;
}

/* Message Functions to display to UART */


void correctMessage()
{
    UART_LOG_PutString("correct button pressed\n");
    UART_LOG_PutString("Press any button to go to the next round\n");
    UART_LOG_PutString("=======================================================\n");
}

void incorrectMessage()
{
    UART_LOG_PutString("Incorrect button pressed\n");
    UART_LOG_PutString("Press any button to go to the next round\n");
    UART_LOG_PutString("=======================================================\n");
}

void tooslowMessage()
{
    UART_LOG_PutString("TIMEOUT!\n");
    UART_LOG_PutString("Press any button to go to the next round\n");
    UART_LOG_PutString("=======================================================\n");
}

void finalMessage()
{
    UART_LOG_PutString("END of the game");
    LED_Toggle(LED_ALL);
}
/* [] END OF FILE */
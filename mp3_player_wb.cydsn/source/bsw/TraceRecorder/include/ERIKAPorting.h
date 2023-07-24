/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef ERIKA_PORTING_H
#define ERIKA_PORTING_H
#endif
    
/*ERIKA OS Changes
ERIKAOS_1_ee - Inclusion of ERIKA component
trcRecorder.h - Inclusion of trace recorder files.
configUSE_TRACE_FACILITY - Needed for enabling tracing internally in Tracerecorder
TRACE_TICK_RATE_HZ, TRACE_CPU_CLOCK_HZ - Originally defined in "FreeRTOS.h". Now we are directly hardcoding
TaskHandle_t,UBaseType_t - introducing new types to support tracealyzer updated version.
*/
#include "ErikaOS_1_ee.h" 
#include "trcRecorder.h" 
#define configUSE_TRACE_FACILITY 1 

/*
Below define the offsets from which ID are derived for tasks / Alarms / Resources 
*/
#define TASK_ID_OFFSET 1
#define ALARM_ID_OFFSET 10
#define RESOURCE_ID_OFFSET 20

/* [] END OF FILE */


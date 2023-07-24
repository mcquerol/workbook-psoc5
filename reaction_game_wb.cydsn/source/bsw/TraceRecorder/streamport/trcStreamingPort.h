/*******************************************************************************
 * Trace Recorder Library for Tracealyzer v3.1.2
 * Percepio AB, www.percepio.com
 *
 * trcStreamingPort.h
 *
 * The interface definitions for trace streaming ("stream ports").
 * This "stream port" sets up the recorder to use USB CDC as streaming channel.
 * The example is for STM32 using STM32Cube.
 *
 * Terms of Use
 * This file is part of the trace recorder library (RECORDER), which is the 
 * intellectual property of Percepio AB (PERCEPIO) and provided under a
 * license as follows.
 * The RECORDER may be used free of charge for the purpose of recording data
 * intended for analysis in PERCEPIO products. It may not be used or modified
 * for other purposes without explicit permission from PERCEPIO.
 * You may distribute the RECORDER in its original source code form, assuming
 * this text (terms of use, disclaimer, copyright notice) is unchanged. You are
 * allowed to distribute the RECORDER with minor modifications intended for
 * configuration or porting of the RECORDER, e.g., to allow using it on a 
 * specific processor, processor family or with a specific communication
 * interface. Any such modifications should be documented directly below
 * this comment block.  
 *
 * Disclaimer
 * The RECORDER is being delivered to you AS IS and PERCEPIO makes no warranty
 * as to its use or performance. PERCEPIO does not and cannot warrant the 
 * performance or results you may obtain by using the RECORDER or documentation.
 * PERCEPIO make no warranties, express or implied, as to noninfringement of
 * third party rights, merchantability, or fitness for any particular purpose.
 * In no event will PERCEPIO, its technology partners, or distributors be liable
 * to you for any consequential, incidental or special damages, including any
 * lost profits or lost savings, even if a representative of PERCEPIO has been
 * advised of the possibility of such damages, or for any claim by any third
 * party. Some jurisdictions do not allow the exclusion or limitation of
 * incidental, consequential or special damages, or the exclusion of implied
 * warranties or limitations on how long an implied warranty may last, so the
 * above limitations may not apply to you.
 *
 * Tabs are used for indent in this file (1 tab = 4 spaces)
 *
 * Copyright Percepio AB, 2017.
 * www.percepio.com
 ******************************************************************************/

#ifndef TRC_STREAMING_PORT_H
#define TRC_STREAMING_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Implement the below macros to define your own stream port. If your transfer 
 * method uses RTOS functions, you should not send the data directly but use 
 * the recorder's internal buffer to store the trace data, for later transfer by
 * the TzCtrl task. Check the predefined stream ports for examples on how to use 
 * the internal buffer (e.g., TCP/IP, UART or USB CDC).
 *
 * Read more at http://percepio.com/2016/10/05/rtos-tracing/  
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include <project.h>
#include "trcStreamingConfig.h"

/*=======================[ Symbols ]===============================================================*/
    
#define PORT_UART       1                   /**<\brief use an UART Module*/
#define PORT_UART_DMA   2                   /**<\brief use an UART Module with DMA (not implemented yet)*/
#define PORT_USB        3                   /**<\brief use the USBUART module*/

/*=======================[ config ]================================================================*/
    
/** \brief Selects the streaming configuration to be used.
 * can be:
 * PORT_UART        -> use an UART Module
 * PORT_UART_DMA    -> use an UART Module with DMA
 * PORT_USB         -> use the USBUART module
 */
#define TRACEPORT       PORT_USB

//----------- config check
#if(!(TRACEPORT==PORT_UART||TRACEPORT==PORT_USB))
    #error Unsupported streaming port configuration
#endif

/*=======================[ references to stream port implementation ]===================================*/

/**\brief initializes the selected streaming hardware (UART or USB)*/
void trcUART_init(void);

/**
 * \brief receive data from the streaming port
 * @param p_data        Pointer to the data container in which the received bytes will be stored
 * @param size          The maximum size (number of bytes) tracelayzer expects
 * @param p_NumBytes    Pointer to a value, which indicates how many bytes actually have been read
 * @return  always 0 (success)
 */
int32_t trcUARTReceive(uint8_t* p_data, uint32_t size, int32_t* p_NumBytes);

/**
 * \brief transmit data trough the streaming port
 * @param p_data        Pointer to the data container in which the data to be transmitted is stored
 * @param size          Number of bytes to be transmitted
 * @param p_NumBytes    Number of bytes that have been transmitted
 * @return always 0 (success)
 */
int32_t trcUARTTransmit(uint8_t* p_data, uint32_t size, int32_t* p_NumBytes);

/*=======================[ tracealyzer binding ]=======================================================*/

//----------- Trace Buffer

//if static allocation of trace buffer is configured
#if TRC_RECORDER_BUFFER_ALLOCATION == TRC_RECORDER_BUFFER_ALLOCATION_STATIC
    
    //macro to create the buffer
    #define TRC_STREAM_PORT_ALLOCATE_FIELDS() char _TzTraceData[(TRC_CFG_PAGED_EVENT_BUFFER_PAGE_COUNT) * (TRC_CFG_PAGED_EVENT_BUFFER_PAGE_SIZE)];       	
	
    //reference to the buffer
    extern char _TzTraceData[(TRC_CFG_PAGED_EVENT_BUFFER_PAGE_COUNT) * (TRC_CFG_PAGED_EVENT_BUFFER_PAGE_SIZE)];
        
    //macro for trace buffer allocation. Undefined for static allocation
    #define TRC_STREAM_PORT_MALLOC()
#else
    //macro to define the trace buffer pointer
    #define TRC_STREAM_PORT_ALLOCATE_FIELDS() static char* _TzTraceData = NULL;
    
    //macro to dynamically allocate new memory
    #define TRC_STREAM_PORT_MALLOC() _TzTraceData = TRC_PORT_MALLOC(TRC_PAGED_EVENT_BUFFER_PAGE_COUNT * TRC_PAGED_EVENT_BUFFER_PAGE_SIZE);
#endif


//----------- IO functions

/**\brief tracealyzer binding for streaming port start*/
#define TRC_STREAM_PORT_INIT() trcUART_init(); 

/**\brief tracealyzer binding for streaming port read data */
#define TRC_STREAM_PORT_READ_DATA(_ptrData, _size, _ptrBytesRead)  trcUARTReceive(_ptrData, _size, _ptrBytesRead)

/**\brief tracealyzer binding for streaming port write data */
#define TRC_STREAM_PORT_WRITE_DATA(_ptrData, _size, _ptrBytesSent)  trcUARTTransmit(_ptrData, _size, _ptrBytesSent)

//----------- Hooks
#define TRC_STREAM_PORT_ON_TRACE_BEGIN()  prvPagedEventBufferInit(_TzTraceData);
#define TRC_STREAM_PORT_ON_TRACE_END() /* Do nothing */


#ifdef __cplusplus
}
#endif

#endif /* TRC_STREAMING_PORT_H */

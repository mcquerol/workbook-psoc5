/**
 * \file 	trcStreamingPort.c
 * \author	Sandeep Raju 				Hochschule Darmstadt - sandeep.raju@stud.h-da.de
 * \author	Sameera Chilmattur 			Hochschule Darmstadt - sameera.b.r.chilmattur@stud.h-da.de
 * \author	Thomas Barth 				Hochschule Darmstadt - thomas.barth@h-da.de
 * \date 	03.05.2019
 *
 * \brief 	Streaming Port implementation for percepio tracealyzer
 *
 *
 * ----- Changelog -----
 * 
 *
 * \copyright Copyright 2019
 * Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
 * Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
 * (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
 * this paragraph and the following paragraph appear in all copies, modifications, and distributions.
 * Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
 *
 * \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
 * The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
 * This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
 */

/*=======================[ includes ]==============================================================*/
#include "trcRecorder.h"
#include "trcStreamingPort.h"

/*=======================[ enable ]================================================================*/
#if (TRC_USE_TRACEALYZER_RECORDER == 1)
#if(TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)

/*=======================[ implementation ]==============================================================*/
    
void trcUART_init(void){

#if (TRACEPORT==PORT_UART)
    UART_LOG_Start();
#endif

#if (TRACEPORT==PORT_USB)
    //start USB
    USBUART_Start(0, USBUART_5V_OPERATION);
    
    //check if USB is connected
    if(0!=USBUART_GetConfiguration()){
        
        //Init CDC (communications device class)
        USBUART_CDC_Init();
    };
    
#endif
}

int32_t trcUARTReceive(uint8_t* p_data, uint32_t size, int32_t* p_NumBytes){
    
#if (TRACEPORT==PORT_UART)
    //byte iterator
	uint32_t i;
    
    //read number of bytes waiting in the RX FIFO
    uint32_t bytesInBuffer=UART_LOG_GetRxBufferSize();
   
    //check if there is any data
	if(bytesInBuffer>0)	{
        
        //check if the number of bytes received exceeds the storage provided by the trace lib
		if (bytesInBuffer <= size){
            
            //copy bytes from RX FIFO to tracealyzer container
            for(i=0;i<bytesInBuffer;i++)
                p_data[i]=UART_LOG_GetByte();

            //update number of bytes received
			*p_NumBytes=bytesInBuffer;
		}
        //number of bytes exceeds memory provided by the trace lib
		else{
		            
            //copy bytes from RX FIFO to tracealyzer container
            for(i=0;i<size;i++)
                p_data[i]=UART_LOG_GetByte();
                
            //update number of bytes received
            *p_NumBytes=size;
		}
	}
	else{
		//update number of bytes received
        *p_NumBytes=0;
	}
#endif   
    
#if (TRACEPORT==PORT_USB)
    //check if the USB state changed
    if (0u != USBUART_IsConfigurationChanged()){
        
        // Initialize IN endpoints when device is configured.
        if (0u != USBUART_GetConfiguration()){
            //Enumeration is done, enable OUT endpoint to receive data from host.
            USBUART_CDC_Init();
        }
    }
    
    //check if USB is connected
    if(0!=USBUART_GetConfiguration()){
                
        //check if there is data waiting for us
        if (0u != USBUART_DataIsReady()){
            
            //read bytes from the RX buffer. Partial read is not supported (size argument is ignored)
            (void)size;
            *p_NumBytes=USBUART_GetAll(p_data);
            
        }else{  //no data
            *p_NumBytes=0;
        }
    }else{  //USB disconnected
        *p_NumBytes=0;
    }

#endif
    
	return 0;
}

int32_t trcUARTTransmit(uint8_t* p_data, uint32_t size, int32_t* p_NumBytes){
    
#if (TRACEPORT==PORT_UART)
    //send bytes
	UART_LOG_PutArray(p_data, size);
    
    //update number of sent bytes
	*p_NumBytes=size;
#endif
    
#if (TRACEPORT==PORT_USB)
    //check if the USB state changed
    if (0u != USBUART_IsConfigurationChanged()){
        
        // Initialize IN endpoints when device is configured.
        if (0u != USBUART_GetConfiguration()){
            //Enumeration is done, enable OUT endpoint to receive data from host.
            USBUART_CDC_Init();
        }
    }
    
    //check if USB is connected
    if(0!=USBUART_GetConfiguration()){
        
        //Init CDC (communications device class)
        USBUART_CDC_Init();
        
        //check if previous transfers have finished
        if(USBUART_CDCIsReady()!=0){
            //truncate numer of bytes to be send to 64(limit by USB)
            if(size>64)
                size=64;
            
            //send data
        	USBUART_PutData(p_data, size);
            
            //update number of sent bytes
        	*p_NumBytes=size;
        }else{ //previous transfer has not been finished yet
        
            //update number of sent bytes
        	*p_NumBytes=0;
        }
    }
    else{  //USB disconnected
        *p_NumBytes=0;
    }
#endif
    
    //return value is not evaluated
	return 0;
}

#endif	/*(TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)*/
#endif  /*(TRC_USE_TRACEALYZER_RECORDER == 1)*/
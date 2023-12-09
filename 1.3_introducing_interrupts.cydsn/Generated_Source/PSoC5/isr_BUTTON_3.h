/*******************************************************************************
* File Name: isr_BUTTON_3.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isr_BUTTON_3_H)
#define CY_ISR_isr_BUTTON_3_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_BUTTON_3_Start(void);
void isr_BUTTON_3_StartEx(cyisraddress address);
void isr_BUTTON_3_Stop(void);

CY_ISR_PROTO(isr_BUTTON_3_Interrupt);

void isr_BUTTON_3_SetVector(cyisraddress address);
cyisraddress isr_BUTTON_3_GetVector(void);

void isr_BUTTON_3_SetPriority(uint8 priority);
uint8 isr_BUTTON_3_GetPriority(void);

void isr_BUTTON_3_Enable(void);
uint8 isr_BUTTON_3_GetState(void);
void isr_BUTTON_3_Disable(void);

void isr_BUTTON_3_SetPending(void);
void isr_BUTTON_3_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_BUTTON_3 ISR. */
#define isr_BUTTON_3_INTC_VECTOR            ((reg32 *) isr_BUTTON_3__INTC_VECT)

/* Address of the isr_BUTTON_3 ISR priority. */
#define isr_BUTTON_3_INTC_PRIOR             ((reg8 *) isr_BUTTON_3__INTC_PRIOR_REG)

/* Priority of the isr_BUTTON_3 interrupt. */
#define isr_BUTTON_3_INTC_PRIOR_NUMBER      isr_BUTTON_3__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_BUTTON_3 interrupt. */
#define isr_BUTTON_3_INTC_SET_EN            ((reg32 *) isr_BUTTON_3__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_BUTTON_3 interrupt. */
#define isr_BUTTON_3_INTC_CLR_EN            ((reg32 *) isr_BUTTON_3__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_BUTTON_3 interrupt state to pending. */
#define isr_BUTTON_3_INTC_SET_PD            ((reg32 *) isr_BUTTON_3__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_BUTTON_3 interrupt. */
#define isr_BUTTON_3_INTC_CLR_PD            ((reg32 *) isr_BUTTON_3__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_BUTTON_3_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: SEVEN_DP.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SEVEN_DP_H) /* Pins SEVEN_DP_H */
#define CY_PINS_SEVEN_DP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SEVEN_DP_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SEVEN_DP__PORT == 15 && ((SEVEN_DP__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SEVEN_DP_Write(uint8 value);
void    SEVEN_DP_SetDriveMode(uint8 mode);
uint8   SEVEN_DP_ReadDataReg(void);
uint8   SEVEN_DP_Read(void);
void    SEVEN_DP_SetInterruptMode(uint16 position, uint16 mode);
uint8   SEVEN_DP_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SEVEN_DP_SetDriveMode() function.
     *  @{
     */
        #define SEVEN_DP_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SEVEN_DP_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SEVEN_DP_DM_RES_UP          PIN_DM_RES_UP
        #define SEVEN_DP_DM_RES_DWN         PIN_DM_RES_DWN
        #define SEVEN_DP_DM_OD_LO           PIN_DM_OD_LO
        #define SEVEN_DP_DM_OD_HI           PIN_DM_OD_HI
        #define SEVEN_DP_DM_STRONG          PIN_DM_STRONG
        #define SEVEN_DP_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SEVEN_DP_MASK               SEVEN_DP__MASK
#define SEVEN_DP_SHIFT              SEVEN_DP__SHIFT
#define SEVEN_DP_WIDTH              1u

/* Interrupt constants */
#if defined(SEVEN_DP__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SEVEN_DP_SetInterruptMode() function.
     *  @{
     */
        #define SEVEN_DP_INTR_NONE      (uint16)(0x0000u)
        #define SEVEN_DP_INTR_RISING    (uint16)(0x0001u)
        #define SEVEN_DP_INTR_FALLING   (uint16)(0x0002u)
        #define SEVEN_DP_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SEVEN_DP_INTR_MASK      (0x01u) 
#endif /* (SEVEN_DP__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SEVEN_DP_PS                     (* (reg8 *) SEVEN_DP__PS)
/* Data Register */
#define SEVEN_DP_DR                     (* (reg8 *) SEVEN_DP__DR)
/* Port Number */
#define SEVEN_DP_PRT_NUM                (* (reg8 *) SEVEN_DP__PRT) 
/* Connect to Analog Globals */                                                  
#define SEVEN_DP_AG                     (* (reg8 *) SEVEN_DP__AG)                       
/* Analog MUX bux enable */
#define SEVEN_DP_AMUX                   (* (reg8 *) SEVEN_DP__AMUX) 
/* Bidirectional Enable */                                                        
#define SEVEN_DP_BIE                    (* (reg8 *) SEVEN_DP__BIE)
/* Bit-mask for Aliased Register Access */
#define SEVEN_DP_BIT_MASK               (* (reg8 *) SEVEN_DP__BIT_MASK)
/* Bypass Enable */
#define SEVEN_DP_BYP                    (* (reg8 *) SEVEN_DP__BYP)
/* Port wide control signals */                                                   
#define SEVEN_DP_CTL                    (* (reg8 *) SEVEN_DP__CTL)
/* Drive Modes */
#define SEVEN_DP_DM0                    (* (reg8 *) SEVEN_DP__DM0) 
#define SEVEN_DP_DM1                    (* (reg8 *) SEVEN_DP__DM1)
#define SEVEN_DP_DM2                    (* (reg8 *) SEVEN_DP__DM2) 
/* Input Buffer Disable Override */
#define SEVEN_DP_INP_DIS                (* (reg8 *) SEVEN_DP__INP_DIS)
/* LCD Common or Segment Drive */
#define SEVEN_DP_LCD_COM_SEG            (* (reg8 *) SEVEN_DP__LCD_COM_SEG)
/* Enable Segment LCD */
#define SEVEN_DP_LCD_EN                 (* (reg8 *) SEVEN_DP__LCD_EN)
/* Slew Rate Control */
#define SEVEN_DP_SLW                    (* (reg8 *) SEVEN_DP__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SEVEN_DP_PRTDSI__CAPS_SEL       (* (reg8 *) SEVEN_DP__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SEVEN_DP_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SEVEN_DP__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SEVEN_DP_PRTDSI__OE_SEL0        (* (reg8 *) SEVEN_DP__PRTDSI__OE_SEL0) 
#define SEVEN_DP_PRTDSI__OE_SEL1        (* (reg8 *) SEVEN_DP__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SEVEN_DP_PRTDSI__OUT_SEL0       (* (reg8 *) SEVEN_DP__PRTDSI__OUT_SEL0) 
#define SEVEN_DP_PRTDSI__OUT_SEL1       (* (reg8 *) SEVEN_DP__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SEVEN_DP_PRTDSI__SYNC_OUT       (* (reg8 *) SEVEN_DP__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SEVEN_DP__SIO_CFG)
    #define SEVEN_DP_SIO_HYST_EN        (* (reg8 *) SEVEN_DP__SIO_HYST_EN)
    #define SEVEN_DP_SIO_REG_HIFREQ     (* (reg8 *) SEVEN_DP__SIO_REG_HIFREQ)
    #define SEVEN_DP_SIO_CFG            (* (reg8 *) SEVEN_DP__SIO_CFG)
    #define SEVEN_DP_SIO_DIFF           (* (reg8 *) SEVEN_DP__SIO_DIFF)
#endif /* (SEVEN_DP__SIO_CFG) */

/* Interrupt Registers */
#if defined(SEVEN_DP__INTSTAT)
    #define SEVEN_DP_INTSTAT            (* (reg8 *) SEVEN_DP__INTSTAT)
    #define SEVEN_DP_SNAP               (* (reg8 *) SEVEN_DP__SNAP)
    
	#define SEVEN_DP_0_INTTYPE_REG 		(* (reg8 *) SEVEN_DP__0__INTTYPE)
#endif /* (SEVEN_DP__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SEVEN_DP_H */


/* [] END OF FILE */

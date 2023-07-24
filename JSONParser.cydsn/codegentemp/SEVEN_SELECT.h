/*******************************************************************************
* File Name: SEVEN_SELECT.h  
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

#if !defined(CY_PINS_SEVEN_SELECT_H) /* Pins SEVEN_SELECT_H */
#define CY_PINS_SEVEN_SELECT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SEVEN_SELECT_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SEVEN_SELECT__PORT == 15 && ((SEVEN_SELECT__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SEVEN_SELECT_Write(uint8 value);
void    SEVEN_SELECT_SetDriveMode(uint8 mode);
uint8   SEVEN_SELECT_ReadDataReg(void);
uint8   SEVEN_SELECT_Read(void);
void    SEVEN_SELECT_SetInterruptMode(uint16 position, uint16 mode);
uint8   SEVEN_SELECT_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SEVEN_SELECT_SetDriveMode() function.
     *  @{
     */
        #define SEVEN_SELECT_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SEVEN_SELECT_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SEVEN_SELECT_DM_RES_UP          PIN_DM_RES_UP
        #define SEVEN_SELECT_DM_RES_DWN         PIN_DM_RES_DWN
        #define SEVEN_SELECT_DM_OD_LO           PIN_DM_OD_LO
        #define SEVEN_SELECT_DM_OD_HI           PIN_DM_OD_HI
        #define SEVEN_SELECT_DM_STRONG          PIN_DM_STRONG
        #define SEVEN_SELECT_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SEVEN_SELECT_MASK               SEVEN_SELECT__MASK
#define SEVEN_SELECT_SHIFT              SEVEN_SELECT__SHIFT
#define SEVEN_SELECT_WIDTH              1u

/* Interrupt constants */
#if defined(SEVEN_SELECT__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SEVEN_SELECT_SetInterruptMode() function.
     *  @{
     */
        #define SEVEN_SELECT_INTR_NONE      (uint16)(0x0000u)
        #define SEVEN_SELECT_INTR_RISING    (uint16)(0x0001u)
        #define SEVEN_SELECT_INTR_FALLING   (uint16)(0x0002u)
        #define SEVEN_SELECT_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SEVEN_SELECT_INTR_MASK      (0x01u) 
#endif /* (SEVEN_SELECT__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SEVEN_SELECT_PS                     (* (reg8 *) SEVEN_SELECT__PS)
/* Data Register */
#define SEVEN_SELECT_DR                     (* (reg8 *) SEVEN_SELECT__DR)
/* Port Number */
#define SEVEN_SELECT_PRT_NUM                (* (reg8 *) SEVEN_SELECT__PRT) 
/* Connect to Analog Globals */                                                  
#define SEVEN_SELECT_AG                     (* (reg8 *) SEVEN_SELECT__AG)                       
/* Analog MUX bux enable */
#define SEVEN_SELECT_AMUX                   (* (reg8 *) SEVEN_SELECT__AMUX) 
/* Bidirectional Enable */                                                        
#define SEVEN_SELECT_BIE                    (* (reg8 *) SEVEN_SELECT__BIE)
/* Bit-mask for Aliased Register Access */
#define SEVEN_SELECT_BIT_MASK               (* (reg8 *) SEVEN_SELECT__BIT_MASK)
/* Bypass Enable */
#define SEVEN_SELECT_BYP                    (* (reg8 *) SEVEN_SELECT__BYP)
/* Port wide control signals */                                                   
#define SEVEN_SELECT_CTL                    (* (reg8 *) SEVEN_SELECT__CTL)
/* Drive Modes */
#define SEVEN_SELECT_DM0                    (* (reg8 *) SEVEN_SELECT__DM0) 
#define SEVEN_SELECT_DM1                    (* (reg8 *) SEVEN_SELECT__DM1)
#define SEVEN_SELECT_DM2                    (* (reg8 *) SEVEN_SELECT__DM2) 
/* Input Buffer Disable Override */
#define SEVEN_SELECT_INP_DIS                (* (reg8 *) SEVEN_SELECT__INP_DIS)
/* LCD Common or Segment Drive */
#define SEVEN_SELECT_LCD_COM_SEG            (* (reg8 *) SEVEN_SELECT__LCD_COM_SEG)
/* Enable Segment LCD */
#define SEVEN_SELECT_LCD_EN                 (* (reg8 *) SEVEN_SELECT__LCD_EN)
/* Slew Rate Control */
#define SEVEN_SELECT_SLW                    (* (reg8 *) SEVEN_SELECT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SEVEN_SELECT_PRTDSI__CAPS_SEL       (* (reg8 *) SEVEN_SELECT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SEVEN_SELECT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SEVEN_SELECT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SEVEN_SELECT_PRTDSI__OE_SEL0        (* (reg8 *) SEVEN_SELECT__PRTDSI__OE_SEL0) 
#define SEVEN_SELECT_PRTDSI__OE_SEL1        (* (reg8 *) SEVEN_SELECT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SEVEN_SELECT_PRTDSI__OUT_SEL0       (* (reg8 *) SEVEN_SELECT__PRTDSI__OUT_SEL0) 
#define SEVEN_SELECT_PRTDSI__OUT_SEL1       (* (reg8 *) SEVEN_SELECT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SEVEN_SELECT_PRTDSI__SYNC_OUT       (* (reg8 *) SEVEN_SELECT__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SEVEN_SELECT__SIO_CFG)
    #define SEVEN_SELECT_SIO_HYST_EN        (* (reg8 *) SEVEN_SELECT__SIO_HYST_EN)
    #define SEVEN_SELECT_SIO_REG_HIFREQ     (* (reg8 *) SEVEN_SELECT__SIO_REG_HIFREQ)
    #define SEVEN_SELECT_SIO_CFG            (* (reg8 *) SEVEN_SELECT__SIO_CFG)
    #define SEVEN_SELECT_SIO_DIFF           (* (reg8 *) SEVEN_SELECT__SIO_DIFF)
#endif /* (SEVEN_SELECT__SIO_CFG) */

/* Interrupt Registers */
#if defined(SEVEN_SELECT__INTSTAT)
    #define SEVEN_SELECT_INTSTAT            (* (reg8 *) SEVEN_SELECT__INTSTAT)
    #define SEVEN_SELECT_SNAP               (* (reg8 *) SEVEN_SELECT__SNAP)
    
	#define SEVEN_SELECT_0_INTTYPE_REG 		(* (reg8 *) SEVEN_SELECT__0__INTTYPE)
#endif /* (SEVEN_SELECT__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SEVEN_SELECT_H */


/* [] END OF FILE */

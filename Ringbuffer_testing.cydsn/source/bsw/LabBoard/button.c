/**
* \file button.c
* \author P. Fromm
* \date 29.7.17
*
* \brief Simple button driver
*
* \copyright Copyright ©2016
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

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "project.h"
#include "button.h"

#include "button_1.h"
#include "button_2.h"
#include "button_3.h"
#include "button_4.h"


/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Initialize Button
 * @return RC_SUCCESS if ok
 */
RC_t BUTTON_Init(cyisraddress address)
{
 
    if (address != 0)
    {
        isr_Button_StartEx(address);
    }
    
    return RC_SUCCESS;
}

/**
 * Initialize Button
 * @param BUTTON_id_t button - check if the corresponding button is pressed
 * @return TRUE if button is pressed
 */
boolean_t BUTTON_IsPressed(BUTTON_id_t button)
{
    boolean_t result = FALSE;
    
    switch (button)
    {
        case BUTTON_1 : if (BUTTON_1_Read() == 1) result = TRUE; break;
        case BUTTON_2 : if (BUTTON_2_Read() == 1) result = TRUE; break;
        case BUTTON_3 : if (BUTTON_3_Read() == 1) result = TRUE; break;
        case BUTTON_4 : if (BUTTON_4_Read() == 1) result = TRUE; break;
    }
    
    return result;
}

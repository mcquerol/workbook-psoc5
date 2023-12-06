/**
* \file seven.c
* \author P. Fromm
* \date 28.8.17
*
* \brief Driver for 7 segment displays
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
#include "seven.h"




/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

#define SEVEN__A  0b10000000
#define SEVEN__B  0b01000000
#define SEVEN__C  0b00100000
#define SEVEN__D  0b00010000
#define SEVEN__E  0b00001000
#define SEVEN__F  0b00000100
#define SEVEN__G  0b00000010
#define SEVEN__DP 0b00000001


/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

//    ABCDEFG
const static uint8_t SEVEN__BitPattern[] = 
{
    0b11111100,     //0
    0b01100000,     //1
    0b11011010,     //2
    0b11110010,     //3
    0b01100110,     //4
    0b10110110,     //5
    0b10111110,     //6
    0b11100000,     //7
    0b11111110,     //8
    0b11110110,     //9
    0b11101110,     //a
    0b00111110,     //b
    0b10011100,     //c
    0b01111010,     //d
    0b10011110,     //e
    0b10001110,     //f
    0b00000001      //decimal point
};
    
//We need to store the last latch value per display
//-1 means empty
static sint8_t SEVEN__latch_value[2] = {-1,-1};
static uint8_t SEVEN__latch_pattern[2] = {0,0};

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/



/**
 * Initilasation of the seven segment display
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_Init()
{
    
    SEVEN_Clear(SEVEN_0);
    SEVEN_Clear(SEVEN_1);
    
    return RC_SUCCESS;
}


/**
 * Sets value for one display
 * @param SEVEN_id_t sevenId - identifier for the segment to be set
 * @param uint8_t value - value to be set, valid range 0...15
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_Set(SEVEN_id_t sevenId, uint8_t value)
{
    if (value > 0x0F)
    {
        return RC_ERROR_BAD_PARAM;
    }
    
    //Set the selection bit for the display
    SEVEN_SELECT_Write((uint8_t)sevenId);
    
    //Set the bitpattern
    //As we do not have a single port, we have to do it bit by bit
    
    uint8_t pattern = SEVEN__BitPattern[value];
    
    //Store the current pattern in the software latch (needed for the DP function)
    SEVEN__latch_value[(uint8_t)sevenId] = value;
    SEVEN__latch_pattern[(uint8_t)sevenId] = pattern;
    
    SEVEN_reg_Write(pattern);
    return RC_SUCCESS;
    
}

/**
 * Get value for one display
 * @param SEVEN_id_t sevenId - identifier for the segment to be set
 * @param uint8_t value - current value, valid range 0...15
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_Get(SEVEN_id_t sevenId, sint8_t* value)
{
    *value = SEVEN__latch_value[(uint8_t)sevenId];
    return RC_SUCCESS;
}


/**
 * Sets both displays
 * @param uint8_t value - value to be set, valid range 0...255
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_SetHex(uint8_t value)
{
    SEVEN_Set(SEVEN_1, value / 16);
    SEVEN_Set(SEVEN_0, value % 16);
    
    return RC_SUCCESS;
}

/**
 * Sets decimal point for one display
 * @param SEVEN_id_t sevenId - identifier for the segment to be set
 * @param uint8_t value - value to be set, valid range 0 (OFF)...1(ON)
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_SetDP(SEVEN_id_t sevenId, uint8_t value)
{
    
    if (value > 1)
    {
        return RC_ERROR_BAD_PARAM;
    }
    
    //Restore the last display pattern
    uint8_t pattern = 0;
    if (SEVEN__latch_value[(uint8_t)sevenId] != -1)
    {
        pattern = SEVEN__latch_pattern[(uint8_t)sevenId];
    }
    
    //Set the selection bit for the display
    SEVEN_SELECT_Write((uint8_t)sevenId);
    
    //Set the port to the pattern currently active
    SEVEN_reg_Write(pattern);
    
    //Set the decimal point
    SEVEN_DP_Write(value);

    return RC_SUCCESS;
}

/**
 * Clears one display
 * @param SEVEN_id_t sevenId - identifier for the segment to be set
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_Clear(SEVEN_id_t sevenId)
{
    //Set software latch to cleared
    SEVEN__latch_value[(uint8_t)sevenId] = -1;
    
    //Set the selection bit for the display
    SEVEN_SELECT_Write((uint8_t)sevenId);
    
    //Clear every bit
    SEVEN_reg_Write(0);
    
    return RC_SUCCESS;
}
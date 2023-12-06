/**
* \file seven.h
* \author P. Fromm
* \date 28.8.17
*
* \brief Driver for 7 segment displays
*
* The seven segment driver controls the inverter for latch selection as well as the 2 latch registers for setting the seven segment display.
* The control of the decimal point is decoupled from the display value. 
*
* \note <notes>
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - <version; data of change; author>
*            - <description of the change>
*
* \copyright Copyright �2016
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

/**
 * Programming rules (may be deleted in the final release of the file)
 * ===================================================================
 *
 * 1. Naming conventions:
 *    - Prefix of your module in front of every function and static data. 
 *    - Scope _ for public and __ for private functions / data / types, e.g. 
 *       Public:  void CONTROL_straightPark_Init();
 *       Private: static void CONTROL__calcDistance();
 *       Public:  typedef enum {RED, GREEN, YELLOW} CONTROL_color_t
 *    - Own type definitions e.g. for structs or enums get a postfix _t
 *    - #define's and enums are written in CAPITAL letters
 * 2. Code structure
 *    - Be aware of the scope of your modules and functions. Provide only functions which belong to your module to your files
 *    - Prepare your design before starting to code
 *    - Implement the simple most solution (Too many if then else nestings are an indicator that you have not properly analysed your task)
 *    - Avoid magic numbers, use enums and #define's instead
 *    - Make sure, that all error conditions are properly handled
 *    - If your module provides data structures, which are required in many other files, it is recommended to place them in a file_type.h file
 *	  - If your module contains configurable parts, is is recommended to place these in a file_config.h|.c file
 * 3. Data conventions
 *    - Minimize the scope of data (and functions)
 *    - Global data is not allowed outside of the signal layer (in case a signal layer is part of your design)
 *    - All static objects have to be placed in a valid linker sections
 *    - Data which is accessed in more than one task has to be volatile and needs to be protected (e.g. by using messages or semaphores)
 *    - Do not mix signed and unsigned data in the same operation
 * 4. Documentation
 *    - Use self explaining function and variable names
 *    - Use proper indentation
 *    - Provide Javadoc / Doxygen compatible comments in your header file and C-File
 *    		- Every  File has to be documented in the header
 *			- Every function parameter and return value must be documented, the valid range needs to be specified
 *     		- Logical code blocks in the C-File must be commented
 *    - For a detailed list of doxygen commands check http://www.stack.nl/~dimitri/doxygen/index.html 
 * 5. Qualification
 *    - Perform and document design and code reviews for every module
 *    - Provide test specifications for every module (focus on error conditions)
 *
 * Further information:
 *    - Check the programming rules defined in the MIMIR project guide
 *         - Code structure: https://fromm.eit.h-da.de/intern/mimir/methods/eng_codestructure/method.htm
 *         - MISRA for C: https://fromm.eit.h-da.de/intern/mimir/methods/eng_c_rules/method.htm
 *         - MISRA for C++: https://fromm.eit.h-da.de/intern/mimir/methods/eng_cpp_rules/method.htm 
 **/
 
#ifndef SEVEN_H
#define SEVEN_H
    
    
#include "global.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

    
//####################### MACROS


//####################### Enumerations
/**
* \brief Enumeration identifying the display to be set
*
*/
typedef enum {
  SEVEN_0 = 0,          /**< Right seven segment display */
  SEVEN_1 = 1,          /**< Left seven segment display */
} SEVEN_id_t;  

// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class SEVEN
{
public:
#endif /* Together */

/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/



/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * Initilasation of the seven segment display
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_Init();

/**
 * Sets value for one display
 * @param SEVEN_id_t sevenId - identifier for the segment to be set
 * @param uint8_t value - value to be set, valid range 0...15
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_Set(SEVEN_id_t sevenId, uint8_t value);

/**
 * Get value for one display
 * @param SEVEN_id_t sevenId - identifier for the segment to be set
 * @param uint8_t value - current value, valid range -1...15, -1 means empty display
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_Get(SEVEN_id_t sevenId, sint8_t* value);

/**
 * Sets both displays
 * @param uint8_t value - value to be set, valid range 0...255
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_SetHex(uint8_t value);

/**
 * Sets decimal point for one display
 * @param SEVEN_id_t sevenId - identifier for the segment to be set
 * @param uint8_t value - value to be set, valid range 0 (OFF)...1(ON)
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_SetDP(SEVEN_id_t sevenId, uint8_t value);

/**
 * Clears one display
 * @param SEVEN_id_t sevenId - identifier for the segment to be set
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_Clear(SEVEN_id_t sevenId);


/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER
//Not visible for compiler, only used for document generation
private:

//Attributes

/**
 * <description>
 */
static type FILE__variable;

//Operations

/**
 * <description>
 * @param <para 1>
 * @return <return description>
 */
static type FILE__function(uint16_t cmd);


};
#endif /* Together */

#endif /* FILE_H */

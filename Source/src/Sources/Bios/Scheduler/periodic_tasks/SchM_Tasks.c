/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         SchM_Tasks.c
* Instance:         RPL_1
* %version:         1
* %created_by:      Diego Flores
* %date_created:    Mon Jul  13 10:20:00 2015 		
*=============================================================================*/
/* DESCRIPTION : SchM_Tasks                        */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source template according to  */
/* the new software platform                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 07/01/2015  |       descripcion de modulo   | Diego Flores     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "SchM_Tasks.h"
#include "GPIO.h"
#include "WindowLifter.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */


/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	SchM_Task_1p563ms
 *  Description          :  Container for functionality that is 
                            executed periodically.
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/

void SchM_Task_1p563ms(void)
{
	
}

/**************************************************************
 *  Name                 :	SchM_Task_3p125ms
 *  Description          :  Container for functionality that is 
                            executed periodically.
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/

void SchM_Task_3p125ms(void)
{
	State_Machine();
}

/**************************************************************
 *  Name                 :	SchM_Task_6p25ms
 *  Description          :  Container for functionality that is 
                            executed periodically.
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/

void SchM_Task_6p25ms(void)
{
	LED_TOGGLE(LED1);
}

/**************************************************************
 *  Name                 :	SchM_Task_12p5ms
 *  Description          :  Container for functionality that is 
                            executed periodically.
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/

void SchM_Task_12p5ms(void)
{
	LED_TOGGLE(LED4);
}

/**************************************************************
 *  Name                 :	SchM_Task_25ms
 *  Description          :  Container for functionality that is 
                            executed periodically.
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/

void SchM_Task_25ms(void)
{
	LED_TOGGLE(LED3);
}

/**************************************************************
 *  Name                 :	SchM_Task_50ms
 *  Description          :  Container for functionality that is 
                            executed periodically.
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/

void SchM_Task_50ms(void)
{
	LED_TOGGLE(LED2);
}

/**************************************************************
 *  Name                 :	SchM_Task_100ms
 *  Description          :  Container for functionality that is 
                            executed periodically.
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/

void SchM_Task_100ms(void)
{
	Ms_Counter();
}
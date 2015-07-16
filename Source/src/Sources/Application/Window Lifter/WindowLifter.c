/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         WindowLifter.c
* Instance:         RPL_1
* version:         1
* created_by:      Diego Flores
* date_created:    Wend Jul  01 11:00:00 2015 
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
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


/** Own headers */
#include "WindowLifter.h"
#include "Idle&Anti_Pinch.h"
#include "DownFunction.h"
#include "UpFunction.h"


/* GPIO routines prototypes */ 

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
T_UBYTE rub_state;
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
 *  Name                 :	STATE_MACHINE
 *  Description          :  Finite State machine that controls all functions of the window lifter
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :  nothing
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void STATE_MACHINE(void)
{
	switch (rub_state)
	{
		case IDLE:  
					rub_state=IDLE;
					break;

		case WINDOWMANUAL_OPENING:
					rub_state=IDLE;
					break;
		
		case WINDOWMANUAL_CLOSING:
					
					rub_state=IDLE;
					break;
					
		case WINDOWAUTO_OPENING:
					 rub_state=IDLE;
					break;
					
		case WINDOWAUTO_CLOSING:
					rub_state=IDLE;
					break;
					
		case ANTI_PINCH:
					rub_state=IDLE;
					break;
					
		default: 	rub_state=	IDLE;
					
					break;
	}
}

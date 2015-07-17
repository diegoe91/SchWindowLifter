/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         WindowLifter.c
* Instance:         RPL_1
* version:          2
* created_by:       Diego Flores
* date_created:    	Wend Jul  01 11:00:00 2015 
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : here is the finite state machine of the window lifter   */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  2.7      | 07/01/2015  |       descripcion de modulo   | Diego Flores     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */


/** Own headers */
#include "WindowLifter.h"
#include "Idle&Anti_Pinch.h"
#include "DownFunction.h"
#include "UpFunction.h"
#include "typedefs.h"


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
T_UBYTE rub_state=IDLE;  /* Initialize the first state of the Window lifter finite states machine */
T_SBYTE rsb_PositionLedbar=9; /* Variable that indicates the led bar position  */

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
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/
void State_Machine(void)
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
					
					rub_state = Window_Manual_Closing();
					break;
					
		case WINDOWAUTO_OPENING:
					 rub_state=IDLE;
					break;
					
		case WINDOWAUTO_CLOSING:
					rub_state = Window_Auto_Closing();
					break;
					
		case ANTI_PINCH:
					rub_state = Anti_Pinch();
					break;
					
		default: 	rub_state=	IDLE;
					
					break;
	}
}

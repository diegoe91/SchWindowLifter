/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         WindowLifter.c
* Instance:         RPL_2
* version:          1 
* created_by:      David Rosales
* date_created:    Wed  07/15/15 
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
/*  1.0      | 07/15/15    |   Matched Code and scheduler  | David Rosales    */
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
T_UBYTE rub_State=IDLE;
T_SBYTE rsb_PositionLedbar = WINDOW_TOTALLY_CLOSED;
/* WORD RAM variables */
T_UWORD ruw_Time_Counter=TIME_COUNT_RESTART;
T_UWORD ruw_Pace_Counter=PACE_TIME_REQUIRED;

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
	switch (rub_State)
	{
		case IDLE:  
					Idle_Func ();
					break;

		case WINDOWMANUAL_OPENING:
			    	rub_State=Manual_Open_Func();
					break;
		
		case WINDOWMANUAL_CLOSING:
					
					rub_State=IDLE;
					break;
					
		case WINDOWAUTO_OPENING:
					rub_State= Auto_Open_Func();
					break;
					
		case WINDOWAUTO_CLOSING:
					rub_State=IDLE;
					break;
					
		case ANTI_PINCH:
					rub_State=IDLE;
					break;
					
		default: 	rub_State=	IDLE;
					
					break;
	}
}

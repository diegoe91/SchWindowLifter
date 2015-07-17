/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         Idle&Anti_Pinch.c
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
#include "Idle&Anti_Pinch.h"
#include "GPIO.h"
#include "WindowLifter.h"
#include "typedefs.h"

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

T_UBYTE ruw_Idle_Time_Counter=TIME_COUNT_RESTART;

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
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/

void Idle_Func ()
{
	
	LED_OFF (LED_GREEN);
	LED_OFF (LED_BLUE);
	ruw_Pace_Counter=PACE_TIME_REQUIRED;/*Overpasses the pace time counter to ensure the first led is turn on/off on time (0ms)*/
		if ((BUTTON_DOWN_PRESSED==PRESSED ) &&(rsb_PositionLedbar>=WINDOW_TOTALLY_OVERCLOSED)) /*Checks if the down button is pressed and the window is  already open*/
		{
			if ((ruw_Idle_Time_Counter>DEBOUNCED_TIME) && (BUTTON_DOWN_PRESSED==PRESSED)) /*Checks the debounce time has been met*/
			{
				rub_State = WINDOWAUTO_OPENING; /*Sets the state machine to window open*/
					LED_ON (LED_GREEN);
			}
			else ruw_Idle_Time_Counter++; /*increments conter +1ms*/
		}
		if ((BUTTON_UP_PRESSED==PRESSED ) &&(rsb_PositionLedbar<WINDOW_TOTALLY_CLOSED)) /*checks window is not totally closed and if the close button is pressed*/
		{
			if ((ruw_Idle_Time_Counter>DEBOUNCED_TIME) && (BUTTON_UP_PRESSED==PRESSED)) /*checks the button has been pressed more than the debounced time*/
			{
				rub_State = WINDOWAUTO_CLOSING;
				LED_ON (LED_BLUE);
			}
			else ruw_Idle_Time_Counter++;  /*Tim counter increments 1ms*/
		}
			
			if ((BUTTON_DOWN_PRESSED==NO_PRESSED)&&(BUTTON_UP_PRESSED==NO_PRESSED))  /*Assures if no button is pressed, the state machines stays in IDLE*/
			{
			ruw_Idle_Time_Counter=TIME_COUNT_RESTART;
			rub_State=IDLE;
			}
			else
			{
				/*do nothing*/
			}
}
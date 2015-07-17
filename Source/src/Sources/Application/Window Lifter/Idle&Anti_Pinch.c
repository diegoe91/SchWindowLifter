/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         Idle&Anti_Pinch.c
* Instance:         RPL_1
* version:          1 
* created_by:      
* date_created:    Fri Jan  9 14:38:03 2004 
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
/*  1.0      | DD/MM/YYYY  |                               | Mr. Template     */
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

void IDLE_Func ()
{
	
	LED_OFF (LED_GREEN);
	LED_OFF (LED_BLUE);
	ruw_Pace_Counter=Pace_Count401;
		if ((BUTTON_DOWN_PRESSED==PRESSED ) &&(rsb_PositionLedbar>=Leds_Count0)) 
		{
			if ((ruw_Time_Counter>Button_Validation) && (BUTTON_DOWN_PRESSED==PRESSED)) 
			{
				rub_State = WINDOWAUTO_OPENING;
					LED_ON (LED_GREEN);
			}
			else ruw_Time_Counter++;
		}
		if ((BUTTON_UP_PRESSED==PRESSED ) &&(rsb_PositionLedbar<Leds_Count9)) 
		{
			if ((ruw_Time_Counter>Button_Validation) && (BUTTON_UP_PRESSED==PRESSED)) 
			{
				rub_State = WINDOWAUTO_CLOSING;
				LED_ON (LED_BLUE);
			}
			else ruw_Time_Counter++;
		}
			
			if ((BUTTON_DOWN_PRESSED==NO_PRESSED)&&(BUTTON_UP_PRESSED==NO_PRESSED))
			{
			ruw_Time_Counter=Time_Count0;
			rub_State=IDLE;
			}
}
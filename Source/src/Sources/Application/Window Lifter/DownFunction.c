/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         DownFunction.c
* Instance:         RPL_1
* version:          1
* created_by:       uid02495 
* date_created:     Fri Jan  9 14:38:03 2004 
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
#include "DownFunction.h"
#include "WindowLifter.h"
#include "GPIO.h"
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


/**************************************************************
 *  Name                 : opening_func
 *  Description          : Fuction emulates opening window by turning off leds
 *  Parameters           :  None
 *  Return               :   None
 *  Critical/explanation :     No
 **************************************************************/



void opening_func ()  /*Fuction emulates opening window by turning off leds*/
{
	
	LED_OFF (rsb_PositionLedbar);
	rsb_PositionLedbar--;
	ruw_Pace_Counter=Pace_Restart;
	
}




T_SBYTE MANUAL_OPEN_Func()
{
	if (BUTTON_DOWN_PRESSED==PRESSED )
        {
	        if ((ruw_Pace_Counter>Pace_Count400)&&(rsb_PositionLedbar>=Leds_Count0))
			{
				opening_func();
			}
	        else ruw_Pace_Counter++;
        }
        if (BUTTON_DOWN_PRESSED==NO_PRESSED)
        {
        	rub_State = IDLE;
        	rsb_PositionLedbar++;
        }
        return(rsb_PositionLedbar);
}


T_SBYTE AUTO_OPEN_Func()
{
		if ((BUTTON_DOWN_PRESSED==NO_PRESSED)&&(ruw_Time_Counter<Time_Count500))
				{
					
					if (ruw_Pace_Counter>Pace_Count400)
					{
					opening_func();
					}
					else ruw_Pace_Counter++;
					rub_State=WINDOWAUTO_OPENING;
				}
	if(BUTTON_DOWN_PRESSED==PRESSED)
	{
		
		ruw_Time_Counter++;
		if ((BUTTON_DOWN_PRESSED==PRESSED ) &&(ruw_Time_Counter>Time_Count500))
		{
			rub_State = WINDOWMANUAL_OPENING;
			
		}
	}
		if(rsb_PositionLedbar<Leds_Count0) 
		{
		rub_State=IDLE;
		rsb_PositionLedbar=Leds_Count0;
		}
		  return(rsb_PositionLedbar);
}
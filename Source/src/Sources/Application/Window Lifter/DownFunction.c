/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         DownFunction.c
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

extern T_SBYTE rsb_PositionLedbar;
/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */

T_UBYTE rub_CounterOnOff_Flag=0;
/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */

#define OFF 				                  0
#define ON  	     		                  1
#define T_0ms				                  0
#define T_10ms	     		                  3
#define T_400ms				                  4
#define T_500ms				                  5

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
 *  Name                 : Opening_Func
 *  Description          : Fuction emulates opening window by turning off leds
 *  Parameters           :  None
 *  Return               :   None
 *  Critical/explanation :     No
 **************************************************************/



void Opening_Func (void)  /*Fuction emulates opening window by turning off leds*/
				      /*Program will access function once the 400 ms counter has been met */
{
	
	LED_OFF (rsb_PositionLedbar); /* turns off the first led positioned*/
	rsb_PositionLedbar--;        /*decreases the led counter */
	rub_CounterOnOff_Flag=OFF; /* Flag off to get 400 ms counter restarted */

}	
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
 *  Name                 : MANUAL_OPEN_Func
 *  Description          : Fuction checks if the button "down" is still pressed, if so, the window goes down while pressed
 *  Parameters           :  None
 *  Return               :   rub_State
 *  Critical/explanation :     No
 **************************************************************/


T_UBYTE Manual_Open_Func(void)   
{
	rub_CounterOnOff_Flag=ON; /*Time counter increments*/
	if (BUTTON_DOWN_PRESSED==PRESSED )  /*Checks if button is still pressed*/
        {
	        if ((ruw_Time_Counter>=PACE_TIME_REQUIRED)&&(rsb_PositionLedbar>=WINDOW_TOTALLY_OPEN)) /*checks if the pace counter is 400ms, to turn off leds every 400ms*/
			{
				Opening_Func();  /*turns off leds every 400 ms*/
			}
	        else 
	        {
	        	/* Do nothing*/
	        } 
        }
        if (BUTTON_DOWN_PRESSED==NO_PRESSED)   /*checks if the button is no longer pressed*/
        {
        	rub_State = IDLE;  /*returns the state machine to idle*/
        	rsb_PositionLedbar++;  /*Assures PositionLedBar ends up in 0, not in -1 */
        }
        else
        {
        	/*do nothing*/
        }
      return(rub_State);
}


/**************************************************************
 *  Name                 : Auto_Open_Func
 *  Description          : Fuction checks the button pressed time is <500ms to open the window automatically
 *  Parameters           :  None
 *  Return               :   rub_State
 *  Critical/explanation :     No
 **************************************************************/

T_UBYTE Auto_Open_Func(void)
{
 	rub_CounterOnOff_Flag=ON;
		if ((BUTTON_DOWN_PRESSED==NO_PRESSED)&&(ruw_Time_Counter<BUTTON_TIME_500MS))/*checks the time has been pressed less than 500ms*/
				{
					
					if (ruw_Time_Counter>=PACE_TIME_REQUIRED) /*Checks the Pace counter is 400ms to turn a led*/
					{
					Opening_Func();  /*turns off leds every 400ms*/
					}
					else      
					{
						/*do nothing*/
					}
					rub_State=WINDOWAUTO_OPENING; /*Assures the state machine in Auto Opening State*/
				}
	else if(BUTTON_DOWN_PRESSED==PRESSED)  /*checks if the button keeps being pressed*/
	{
		
		if ((BUTTON_DOWN_PRESSED==PRESSED ) &&(ruw_Time_Counter>BUTTON_TIME_500MS)) /*checks if the the button pressed time has overpassed the 500ms*/
		{
			rub_State = WINDOWMANUAL_OPENING;  /*chenges the state machine to Manual opening*/
			
		}
		else 
		{
			/*do notghing*/
		}
	}
	else if(rsb_PositionLedbar<WINDOW_TOTALLY_OPEN) /*checks if the window is totally open*/
		{
		rub_State=IDLE;  /*changes the state machine to IDLE*/ 
		rsb_PositionLedbar=WINDOW_TOTALLY_OPEN;  /*assures Positionedbar ends up in 0*/
		}
	else 
	   {
	   	/*do nothing*/
	   }
		  return(rub_State);
}

/**************************************************************
 *  Name                 :	Ms_Counter
 *  Description          :  function that manage the millisecond counter 
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/

void Ms_Counter(void)
{
	if(rub_CounterOnOff_Flag==ON) /* checks if the flag is on to start the counter */ 
	{
		ruw_Time_Counter++;
	}
	else if(rub_CounterOnOff_Flag==OFF)	/* checks if the flag is off to stop the counter */
	{
		ruw_Time_Counter=0;
	}
	else
	{
		/* Do nothing */
	}
}

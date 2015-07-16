/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         UpFunction.c
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
/*  1.      | 16/07/2015  |                               | Diego Flores     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */

/** Own headers */
#include "UpFunction.h"
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

/* WORD RAM variables */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */
T_UBYTE rub_ControlManual_Flag=0;			/* flag to control auto and manual mode */
T_UBYTE rub_CounterOnOff_Flag=0;			/* flag to control counter operation */
extern T_SBYTE rsb_PositionLedbar;          /* variable that turn on/off the led bar */
T_UBYTE rub_AutoFlag=0;                     /* flag that checks the auto mode is on */

/* WORD RAM variables */
T_UWORD ruw_time_counter = 0;  		/* Initialize the main time counter */
T_UWORD ruw_counter_anti_pinch =0; 	/* Initialize the anti pinch counter */


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
#define T_800ms				                  8
#define CLOSE				                  9
#define BarLed_OverFlow		                 10
#define ACTIVATED			  				  1
#define DEACTIVATED			  				  0
#define LED_BLUE			  				  PORTA10
#define ANTI_PINCH_PRESS	  				  BOTTON_PRESS(BUTTON4)					
#define BUTTON_WINDOW_OPEN_PRESS			  BOTTON_PRESS(BUTTON2)	
#define BUTTON_WINDOW_CLOSE_PRESS			  BOTTON_PRESS(BUTTON3)	


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
 *  Name                 :	WINDOW_BARLED_CLOSE
 *  Description          :  Turn on Barled's Leds 
 *  Parameters           :  T_SBYTE lsb_PositionLedbar - This is the variable that select 
 							wich led will turns on in the led bar 
 *  Return               :	none
 *  Critical/explanation :  no]
 **************************************************************/

void Window_LedBar_Close (T_SBYTE lsb_PositionLedbar) 
{
	LED_ON(lsb_PositionLedbar); /* Turns on a led in the led bar when the window is closing */
}

/* Exported functions */
/* ------------------ */

/**************************************************************
 *  Name                 :	Window_Manual_Closing
 *  Description          :  function that closes the window in the manual mode
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/

T_UBYTE Window_Manual_Closing(void)
{	
	T_UBYTE lub_state=WINDOWMANUAL_CLOSING; /* Initializes the state that the function will return to the finite state machine
											   to 	WINDOWMANUAL_CLOSING */
	rub_CounterOnOff_Flag=ON;				/* change the counter flag to on to start the counter */
	if((ANTI_PINCH_PRESS == ACTIVATED) && (rsb_PositionLedbar < CLOSE)) /* checks that the anti pinch button is pressed  */
																		/* and the Window is not totally close */
	{
		ruw_counter_anti_pinch++;
		if(ruw_counter_anti_pinch >= T_10ms)	/* checks that the anti pinch button is pressed for more than 10ms*/
		{
			lub_state=	ANTI_PINCH;				/*change the state to anti pinch */
			rub_CounterOnOff_Flag=OFF;
			ruw_counter_anti_pinch=T_0ms;	
		}
		else
		{
			/* Do nothing */
		}
	}
	else	/* restart anti pinch time counter if the anti pinch button is pressed for less than 10ms */
	{
		ruw_counter_anti_pinch=T_0ms;
	}
	if(((BUTTON_WINDOW_OPEN_PRESS == DEACTIVATED) && (BUTTON_WINDOW_CLOSE_PRESS == ACTIVATED)) && (rsb_PositionLedbar < BarLed_OverFlow)) /* checks that only the window close bottun is pressed and the window is open */
	{	
		if(ruw_time_counter>=T_400ms) /* checks that the counter is upper than 400ms */
		{
			Window_LedBar_Close(rsb_PositionLedbar); /* turn on one led of the led bar */
			rsb_PositionLedbar++;
			ruw_time_counter=T_0ms;
		}
		else
		{
			/* Do nothing */
		}					
	}
	else /* if the window open button is not longer pressed or the window is close change the state to idle and restart values */
	{
		if(rsb_PositionLedbar >= BarLed_OverFlow) /* if the position of the led bar is more than 9 (his higher value) change*/
												  /* change his value to 9 */
		{
			rsb_PositionLedbar =CLOSE;
		}
		else 
		{
			/* Do nothing */
		}
		lub_state=	IDLE;
		ruw_time_counter=T_0ms;
		LED_OFF(LED_BLUE);
		rub_CounterOnOff_Flag=OFF;
	}
	return lub_state;
}



/**************************************************************
 *  Name                 :	Window_Auto_Closing
 *  Description          :  function that closes the window in the auto mode
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/
 
T_UBYTE Window_Auto_Closing(void)
{
	T_UBYTE lub_state=WINDOWAUTO_CLOSING;
	rub_CounterOnOff_Flag=ON;
	if(rsb_PositionLedbar<CLOSE) /* Turn on a window close indicator */
	{
		LED_ON(LED_BLUE);	
	}
	else
	{
		/* Do nothing */
	}
	if((ANTI_PINCH_PRESS == ACTIVATED) && (rsb_PositionLedbar < CLOSE)) /* checks that the anti pinch button is pressed  */
																		/* and the Window is not totally close */
	{
		ruw_counter_anti_pinch++;
		if(ruw_counter_anti_pinch >= T_10ms) /* checks that the anti pinch button is pressed for more than 10ms*/
		{
			lub_state=	ANTI_PINCH;			 /*change the state to anti pinch */
			ruw_counter_anti_pinch=T_0ms;
			rub_CounterOnOff_Flag=OFF;	
		}
		else
		{
			/* Do nothing */
		}
	}
	else
	{
		ruw_counter_anti_pinch=T_0ms;
	}				
	if((((BUTTON_WINDOW_OPEN_PRESS == DEACTIVATED) && (BUTTON_WINDOW_CLOSE_PRESS == ACTIVATED)) && (rsb_PositionLedbar < BarLed_OverFlow)) && rub_ControlManual_Flag == DEACTIVATED) /* checks that only the window close bottun is pressed and the window is open */
	{
		if((ruw_time_counter==T_0ms || ruw_time_counter==T_400ms)) /* checks that the counter is 0ms or 400 ms to turn on a led in the led bae */
		{
			Window_LedBar_Close(rsb_PositionLedbar);
			rsb_PositionLedbar++;	
		}
		else if(ruw_time_counter >= T_500ms) /* checks that the counter is 500ms to change the state to manual  */
		{
			lub_state=	WINDOWMANUAL_CLOSING;
		}
		else
		{
			/* Do nothing */
		}
	}
	else if(rsb_PositionLedbar < BarLed_OverFlow) /* auto mode checks that the window is open */
	{
		rub_ControlManual_Flag = ACTIVATED;
		if((ruw_time_counter>=T_400ms) && (rub_AutoFlag==0)) /* turn on a led in the led bar when the counter is 400ms */
		{
			rub_AutoFlag=1;
			Window_LedBar_Close(rsb_PositionLedbar);
			rsb_PositionLedbar++;
		}
		else if( ruw_time_counter>=T_800ms) /* turn on a led in the led bar when the counter is 800ms */
		{
			rub_AutoFlag=1;
			Window_LedBar_Close(rsb_PositionLedbar);
			rsb_PositionLedbar++;
			if(ruw_time_counter>=T_800ms) /* restart the counter to 400ms to count to 800ms to turn on a new led */
			{
				ruw_time_counter=T_400ms;
			}
			else
			{
				/* Do nothing */
			}
		}
		else
		{
			/* Do nothing */
		}
	}
	else
	{
		/* Do nothing */
	}
	if(rsb_PositionLedbar >= BarLed_OverFlow) /* when the window is close restart all values */
	{
		rub_ControlManual_Flag = DEACTIVATED;
		lub_state=	IDLE;
		rsb_PositionLedbar=CLOSE;
		rub_CounterOnOff_Flag=ON;
		LED_OFF(LED_BLUE);
		rub_AutoFlag=0;
	}
	else
	{
		/* Do nothing */
	}
	return lub_state;
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
		ruw_time_counter++;
	}
	else if(rub_CounterOnOff_Flag==OFF)	/* checks if the flag is off to stop the counter */
	{
		ruw_time_counter=0;
	}
	else
	{
		/* Do nothing */
	}
}


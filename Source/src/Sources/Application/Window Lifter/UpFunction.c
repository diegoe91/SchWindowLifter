/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         UpFunction.c
* Instance:         RPL_1
* version:          2
* created_by:       Diego Flores 
* date_created:     Fri Jan  9 14:38:03 2004 
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : here is the functions that close the window, manual and */
/* automatically                                                              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  2.15      | 21/07/2015  |                               | Diego Flores     */
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
extern T_UBYTE rub_CounterOnOff_Flag;			/* flag to control counter operation */
extern T_SBYTE rsb_PositionLedbar;          /* variable that turn on/off the led bar */
T_UBYTE rub_AutoFlag=0;                     /* flag that checks the auto mode is on */
T_UBYTE rub_flagT_0ms=0;
T_UBYTE rub_flagT_400ms=0;

/* WORD RAM variables */
extern T_UWORD ruw_time_counter;  		/* main time counter */
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
 *  Critical/explanation :  no
 **************************************************************/

void Window_LedBar_Close (T_SBYTE lsb_PositionLedbar) 
{
	LED_ON(lsb_PositionLedbar); /* Turns on a led in the led bar when the window is closing */
	rsb_PositionLedbar++;
}

/* Exported functions */
/* ------------------ */

/**************************************************************
 *  Name                 :	Window_Manual_Closing
 *  Description          :  function that closes the window in the manual mode
 *  Parameters           :  none
 *  Return               :  lub_State_MC
 *  Critical/explanation :  no
 **************************************************************/

T_UBYTE Window_Manual_Closing(void)
{	
	T_UBYTE lub_State_MC=WINDOWMANUAL_CLOSING; /* Initializes the state that the function will return to the finite state machine
											   to 	WINDOWMANUAL_CLOSING */
	T_UWORD luw_Time_Counter_MC=Reed_Ms_Counter(); /* Reeds Time_counter value*/
 	T_SBYTE lsb_PositionLedbar_MC=Reed_PositionLedbar(); /* Reeds PositionLedbar */
	rub_CounterOnOff_Flag=ON;				/* change the counter flag to on to start the counter */
	if((ANTI_PINCH_PRESS == ACTIVATED) && (rsb_PositionLedbar < CLOSE)) /* checks that the anti pinch button is pressed  */
																		/* and the Window is not totally close */
	{
		ruw_counter_anti_pinch++;
		if(ruw_counter_anti_pinch >= T_10ms)	/* checks that the anti pinch button is pressed for more than 10ms*/
		{
			lub_State_MC=	ANTI_PINCH;				/*change the state to anti pinch */
			rub_CounterOnOff_Flag=OFF;				/* Restart values */
			ruw_counter_anti_pinch=T_0ms;
			ruw_time_counter=T_0ms;	
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
	if((BUTTON_WINDOW_OPEN_PRESS == DEACTIVATED) && (BUTTON_WINDOW_CLOSE_PRESS == ACTIVATED) && (lsb_PositionLedbar_MC < BarLed_OverFlow)) /* checks that only the window close bottun is pressed and the window is open */
	{	
		if(luw_Time_Counter_MC == T_800ms) /* checks that the counter is upper than 400ms */
		{
			Window_LedBar_Close(lsb_PositionLedbar_MC); /* turn on one led of the led bar */
			ruw_time_counter=T_400ms;
		}
		else
		{
			/* Do nothing */
		}					
	}
	else /* if the window open button is not longer pressed or the window is close change the state to idle and restart values */
	{
		if(lsb_PositionLedbar_MC >= BarLed_OverFlow) /* if the position of the led bar is more than 9 (his higher value) change*/
												  /* change his value to 9 */
		{
			rsb_PositionLedbar =CLOSE;
		}
		else 
		{
			/* Do nothing */
		}
		lub_State_MC=	IDLE;				/* Restart values and flags */
		rub_CounterOnOff_Flag=OFF;
		ruw_time_counter=T_0ms;
		LED_OFF(LED_BLUE);
		rub_flagT_0ms=DEACTIVATED;  
		rub_flagT_400ms=DEACTIVATED;
	}
	return lub_State_MC;
}



/**************************************************************
 *  Name                 :	Window_Auto_Closing
 *  Description          :  function that closes the window in the auto mode
 *  Parameters           :  none
 *  Return               :  lub_State_AC
 *  Critical/explanation :  no
 **************************************************************/
 
T_UBYTE Window_Auto_Closing(void)
{
	T_UBYTE lub_State_AC=WINDOWAUTO_CLOSING;
	T_UWORD luw_Time_Counter_AC=Reed_Ms_Counter(); /* Reeds Time_Counter value */
 	T_SBYTE lsb_PositionLedBar_AC=Reed_PositionLedbar(); /* Reeds PositionLedbar */
	rub_CounterOnOff_Flag=ON;
	if((ANTI_PINCH_PRESS == ACTIVATED) && (lsb_PositionLedBar_AC < CLOSE)) /* checks that the anti pinch button is pressed  */
																		/* and the Window is not totally close */
	{
		ruw_counter_anti_pinch++;
		if(ruw_counter_anti_pinch >= T_10ms) /* checks that the anti pinch button is pressed for more than 10ms*/
		{
			lub_State_AC=	ANTI_PINCH;			 /*change the state to anti pinch */
			ruw_counter_anti_pinch=T_0ms;
			rub_CounterOnOff_Flag=OFF;
			ruw_time_counter=T_0ms;	
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
	if((BUTTON_WINDOW_OPEN_PRESS == DEACTIVATED) && (BUTTON_WINDOW_CLOSE_PRESS == ACTIVATED) && (lsb_PositionLedBar_AC < BarLed_OverFlow) && rub_ControlManual_Flag == DEACTIVATED) /* checks that only the window close bottun is pressed and the window is open */
	{
		if(((luw_Time_Counter_AC == T_0ms) && (rub_flagT_0ms==DEACTIVATED)) || ((luw_Time_Counter_AC == T_400ms) && (rub_flagT_400ms==ACTIVATED))) /* checks that the counter is 0ms or 400 ms to turn on a led in the led bae */
		{
			Window_LedBar_Close(lsb_PositionLedBar_AC);
	        rub_flagT_0ms=ACTIVATED;
	        if(luw_Time_Counter_AC == T_400ms)  
	        {
	        	rub_flagT_400ms=ACTIVATED;
	        }
		}
		else if(luw_Time_Counter_AC == T_500ms) /* checks that the counter is 500ms to change the state to manual  */
		{
			lub_State_AC=	WINDOWMANUAL_CLOSING;
		}
		else
		{
			/* Do nothing */
		}
	}
	else if(lsb_PositionLedBar_AC < BarLed_OverFlow) /* auto mode checks that the window is open */
	{
		rub_ControlManual_Flag = ACTIVATED;
		if((ruw_time_counter==T_400ms) && (rub_AutoFlag==DEACTIVATED)) /* turn on a led in the led bar when the counter is 400ms */
		{
			rub_AutoFlag=ACTIVATED;
			Window_LedBar_Close(lsb_PositionLedBar_AC);
		}
		else if(ruw_time_counter==T_800ms) /* turn on a led in the led bar when the counter is 800ms */
		{
			Window_LedBar_Close(lsb_PositionLedBar_AC);
			ruw_time_counter=T_400ms; /* restart the counter to 400ms to count to 800ms to turn on a new led */
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
	if(lsb_PositionLedBar_AC >= BarLed_OverFlow) /* when the window is close restart all values */
	{
		rub_ControlManual_Flag = DEACTIVATED;
		rub_AutoFlag=DEACTIVATED;
		lub_State_AC=	IDLE;
		rsb_PositionLedbar=CLOSE;
		rub_CounterOnOff_Flag=OFF;
		ruw_time_counter=T_0ms;
		LED_OFF(LED_BLUE);
		rub_AutoFlag=0;
		rub_flagT_0ms=DEACTIVATED;
		rub_flagT_400ms=DEACTIVATED;  
	}
	else
	{
		/* Do nothing */
	}
	return lub_State_AC;
}
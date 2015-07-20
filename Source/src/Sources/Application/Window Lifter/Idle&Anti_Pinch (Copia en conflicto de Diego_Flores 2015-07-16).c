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
#define LED_BLUE			  				  PORTA10
#define LED_GREEN			  				  PORTA11
#define BarLed_UnderFlow		             -1
#define ACTIVATED			  				  1
#define DEACTIVATED			  				  0
#define T_0ms				                  0
#define T_400ms				                  4
#define OFF 				                  0
#define ON  	     		                  1
#define T_5s								 50
#define OPEN				                  0

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
extern T_UBYTE rub_CounterOnOff_Flag;	/* flag that controls the counter */
extern T_SBYTE rsb_PositionLedbar;		/* variable that has the position of the led bar */

/* WORD RAM variables */
T_UWORD ruw_Open_Flag =0; 			 	/* flag that checks if the window is totally open*/
extern T_UWORD ruw_time_counter;		/* counter */

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
 *  Name                 :	WINDOW_LEDBAR_OPEN
 *  Description          :  Turn off Barled's Leds 
 *  Parameters           :  T_SBYTE lsb_BarLed - It is the position of the window (Barled) 
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
 
void Window_LedBar_Open (T_SBYTE lsb_BarLed) /* Turn off one led of the bar led */
{	
	LED_OFF(lsb_BarLed);
}

/* Exported functions */
/* ------------------ */

/**************************************************************
 *  Name                 :	anti_pinch
 *  Description          :  function that controls the anti pinch button
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :  nothing
 *  Critical/explanation :    [yes / No]
 **************************************************************/
 
T_UBYTE Anti_Pinch(void)
{
	T_UBYTE lub_state=ANTI_PINCH;
	rub_CounterOnOff_Flag=ON;
	if(ruw_Open_Flag == DEACTIVATED) /* Checks if the window is not totally open */
	{
		LED_OFF(LED_BLUE);
		LED_ON(LED_GREEN);
		if(ruw_time_counter>=T_400ms) /* checks if the counter is 400ms to turn off a led in the led bar */
		{
			Window_LedBar_Open(rsb_PositionLedbar);
			rsb_PositionLedbar--;
			if(ruw_time_counter>=T_400ms) /*restart the counter when the counter is 400ms */
			{
				ruw_time_counter=T_0ms;
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
	ruw_time_counter++;
	if(rsb_PositionLedbar <= BarLed_UnderFlow) /* checks that the window is totally open to restart values*/
	{
		ruw_Open_Flag = ACTIVATED;
		rsb_PositionLedbar=OPEN;
		LED_OFF(LED_GREEN);
	}
	else
	{
		/* Do nothing */
	}
	if(ruw_time_counter >= T_5s) /*when the counter is 5 seconds change the state to idle to wait for a pressed button*/
	{
		lub_state=	IDLE;
		ruw_time_counter=T_0ms;
		ruw_Open_Flag = DEACTIVATED;
	}
	else
	{
		/* Do nothing */
	}
	return lub_state;
}
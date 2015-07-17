/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         Idle&Anti_Pinch.c
* Instance:         RPL_1
* version:          2 
* created_by:       Diego Flores
* date_created:     Fri Jan  9 14:38:03 2004 
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : here are the functions of the anti pinch and idle       */
/* 							                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  2.7      | 17/07/2015  |                               | Diego Flores     */
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
#define OPEN				                  0
#define T_5s								 50

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
T_UWORD ruw_Open_Flag =0; 			 	/* flag that checks if the window is totally open*/
extern T_UBYTE rub_CounterOnOff_Flag;	/* Flag to activate the counter*/
extern T_UWORD ruw_time_counter;		/* counter that is incresing every 100 ms*/
extern T_SBYTE rsb_PositionLedbar;      /* Variable that indicates the led bar position */

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
 *  Name                 :	Window_LedBar_Open
 *  Description          :  Turn off Barled's Leds 
 *  Parameters           :  T_SBYTE lsb_BarLed - It is the position of the window (Barled) 
 *  Return               :	none
 *  Critical/explanation :  no
 **************************************************************/
 
void Window_LedBar_Open (T_SBYTE lsb_BarLed) /* Turn off one led in the bar led */
{	
	LED_OFF(lsb_BarLed);
}

/* Exported functions */
/* ------------------ */

/**************************************************************
 *  Name                 :	anti_pinch
 *  Description          :  function that controls the anti pinch button 
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/
 
T_UBYTE Anti_Pinch(void)
{
	T_UBYTE lub_state=ANTI_PINCH;
	rub_CounterOnOff_Flag=ON; /* Activate the counter */
	if(ruw_Open_Flag == DEACTIVATED) /* checks the flag that is activated when the window is completly open */
	{
		LED_OFF(LED_BLUE);
		LED_ON(LED_GREEN);
		if(ruw_time_counter>=T_400ms) /* checks that the time of the counter is 400ms or over */
		{
			Window_LedBar_Open(rsb_PositionLedbar); /* sends the position of the ledbar to turn off a led*/
			rsb_PositionLedbar--;
			if(ruw_time_counter>=T_400ms) /* checks that the time of the counter is 400ms or over to restart the counter */
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
		if(rsb_PositionLedbar <= BarLed_UnderFlow) /* checks when the window is completely open */
		{
			ruw_Open_Flag = ACTIVATED; /* activate the flag that indicates that the window is now open */
			rsb_PositionLedbar=OPEN;
			LED_OFF(LED_GREEN);
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
	if(ruw_time_counter >= T_5s) /* waits 5 seconds of the counter to send the program to idle  */
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

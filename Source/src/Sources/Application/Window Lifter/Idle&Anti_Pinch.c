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
extern T_UBYTE rub_CounterOnOff_Flag;
extern T_UWORD ruw_time_counter;

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
 *  Name                 :	WINDOW_LEDBAR_OPEN
 *  Description          :  Turn off Barled's Leds 
 *  Parameters           :  T_SBYTE lsb_BarLed - It is the position of the window (Barled) 
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
 
void WINDOW_LEDBAR_OPEN (T_SBYTE lsb_BarLed) /* Turn off one led of the bar led */
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
	if((rsb_PositionLedbar > BarLed_UnderFlow) && (ruw_Open_Flag == DEACTIVATED))
	{
		LED_OFF(LED_BLUE);
		LED_ON(LED_GREEN);
		if(ruw_time_counter>=T_400ms)
		{
			WINDOW_BARLED_OPEN(rsb_PositionLedbar);
			rsb_PositionLedbar--;
			if(ruw_time_counter>=T_400ms)
			{
				ruw_time_counter=T_0ms;
			}
		}
	}
	ruw_time_counter++;
	if(rsb_PositionLedbar == BarLed_UnderFlow)
	{
		ruw_Open_Flag = ACTIVATED;
		rsb_PositionLedbar=OPEN;
		LED_OFF(LED_GREEN);
	}
	if(ruw_time_counter >= T_5s)
	{
		lub_state=	IDLE;
		ruw_time_counter=T_0ms;
		ruw_Open_Flag = DEACTIVATED;
	}
	return lub_state;
}

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
/*  2.15      | 21/07/2015  |                               | Diego Flores     */
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
T_UBYTE rub_Idle_Time_Counter=TIME_COUNT_RESTART;
extern T_UBYTE rub_CounterOnOff_Flag;	/* Flag to activate the counter*/
extern T_SBYTE rsb_PositionLedbar;      /* Variable that indicates the led bar position */

/* WORD RAM variables */
T_UWORD ruw_Open_Flag =0; 			 	/* flag that checks if the window is totally open*/
extern T_UWORD ruw_time_counter;		/* counter that is incresing every 100 ms*/

/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */
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
#define BUTTON_DOWN_PRESSED			          BOTTON_PRESS(BUTTON2)
#define BUTTON_UP_PRESSED	        		  BOTTON_PRESS(BUTTON3)
#define PRESSED								  1
#define NO_PRESSED				              0

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
	rsb_PositionLedbar--;
}

/* Exported functions */
/* ------------------ */

/**************************************************************
 *  Name                 :	Idle_func()
 *  Description          :  its the main state where awaits for a valid press button
 *  Parameters           :  none
 *  Return               :	lub_State_Id
 *  Critical/explanation :  No
 **************************************************************/

T_UBYTE Idle_Func ()
{
	T_UBYTE lub_State_Id=IDLE;
	LED_OFF (LED_GREEN);
	LED_OFF (LED_BLUE);
	ruw_Pace_Counter=PACE_TIME_REQUIRED;/*Overpasses the pace time counter to ensure the first led is turn on/off on time (0ms)*/
	if ((BUTTON_DOWN_PRESSED==PRESSED ) &&(rsb_PositionLedbar>=WINDOW_TOTALLY_OPEN)) /*Checks if the down button is pressed and the window is  already open*/
	{
		if ((rub_Idle_Time_Counter>=DEBOUNCED_TIME) && (BUTTON_DOWN_PRESSED==PRESSED)) /*Checks the debounce time has been met*/
		{
			lub_State_Id = WINDOWAUTO_OPENING; /*Sets the state machine to window open*/
			LED_ON (LED_GREEN);
		}
		else rub_Idle_Time_Counter++; /*increments conter +1ms*/
	}
	if ((BUTTON_UP_PRESSED==PRESSED ) &&(rsb_PositionLedbar<=WINDOW_TOTALLY_CLOSED)) /*checks window is not totally closed and if the close button is pressed*/
	{
		if ((rub_Idle_Time_Counter>=DEBOUNCED_TIME) && (BUTTON_UP_PRESSED==PRESSED)) /*checks the button has been pressed more than the debounced time*/
		{
			lub_State_Id = WINDOWAUTO_CLOSING;
			LED_ON (LED_BLUE);
		}
	else rub_Idle_Time_Counter++;  /*Tim counter increments 1ms*/
	}		
	if ((BUTTON_DOWN_PRESSED==NO_PRESSED)&&(BUTTON_UP_PRESSED==NO_PRESSED))  /*Assures if no button is pressed, the state machines stays in IDLE*/
	{
		rub_Idle_Time_Counter=TIME_COUNT_RESTART;
		lub_State_Id=IDLE;
	}
	else
	{
		/*do nothing*/
	}
	return lub_State_Id;
}

/**************************************************************
 *  Name                 :	anti_pinch
 *  Description          :  function that controls the anti pinch button 
 *  Parameters           :  none
 *  Return               :  lub_State_AP
 *  Critical/explanation :  no
 **************************************************************/
 
T_UBYTE Anti_Pinch(void)
{
	T_UBYTE lub_State_AP=ANTI_PINCH;
	T_UWORD luw_Time_Counter_AP=Reed_Ms_Counter(); /* Reeds the value of the counter */
 	T_SBYTE lsb_PositionLedbar_AP=Reed_PositionLedbar(); /* Reeds the value of the position led bar */
	rub_CounterOnOff_Flag=ON; /* Activate the counter */
	if(ruw_Open_Flag == DEACTIVATED) /* checks the flag that is activated when the window is completly open */
	{
		LED_OFF(LED_BLUE);
		LED_ON(LED_GREEN);
		if(luw_Time_Counter_AP == T_400ms) /* checks that the time of the counter is 400ms or over */
		{
			Window_LedBar_Open(lsb_PositionLedbar_AP); /* sends the position of the ledbar to turn off a led*/
			ruw_time_counter=T_0ms;    /*restart the counter */
		}
		else
		{
			/* Do nothing */
		}
		if(lsb_PositionLedbar_AP <= BarLed_UnderFlow) /* checks when the window is completely open */
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
	if(luw_Time_Counter_AP >= T_5s) /* waits 5 seconds of the counter to send the program to idle  */
	{
		lub_State_AP=	IDLE;
		rub_CounterOnOff_Flag=OFF;
		ruw_time_counter=T_0ms;
		ruw_Open_Flag = DEACTIVATED;		
	}
	else
	{
		/* Do nothing */
	}
	return lub_State_AP;
}
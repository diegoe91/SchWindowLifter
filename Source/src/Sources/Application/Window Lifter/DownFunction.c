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
/*  2.15      | 21/07/15    |   Matched Code and scheduler  | Diego Flores    */
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

extern T_UBYTE rub_CounterOnOff_Flag;
extern T_SBYTE rsb_PositionLedbar;

/* WORD RAM variables */
extern T_UWORD ruw_time_counter;

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
#define BUTTON_DOWN_PRESSED			          BOTTON_PRESS(BUTTON2)
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
	ruw_time_counter=0; /* Flag off to get 400 ms counter restarted */
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
 *  Parameters           : None
 *  Return               : lub_State_MO
 *  Critical/explanation : No
 **************************************************************/


T_UBYTE Manual_Open_Func(void)   
{	
	T_UBYTE lub_State_MO=WINDOWMANUAL_OPENING;
	T_UWORD luw_time_counter_MO=Reed_Ms_Counter();
	T_SBYTE lsb_PositionLedbar_MO=Reed_PositionLedbar();
	rub_CounterOnOff_Flag=ON; /*Time counter increments*/
	
 	
	if (BUTTON_DOWN_PRESSED==PRESSED )  /*Checks if button is still pressed*/
    {
		if ((luw_time_counter_MO>=PACE_TIME_REQUIRED)&&(lsb_PositionLedbar_MO>=WINDOW_TOTALLY_OPEN)) /*checks if the pace counter is 400ms, to turn off leds every 400ms*/
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
     	lub_State_MO = IDLE;  /*returns the state machine to idle*/
        rub_CounterOnOff_Flag=OFF;
        ruw_time_counter=0; /* Flag off to get 400 ms counter restarted */
     }
     else
     {
        /*do nothing*/
     }
     if(lsb_PositionLedbar_MO<WINDOW_TOTALLY_OPEN)
     {
     	rsb_PositionLedbar=WINDOW_TOTALLY_OPEN;  /*assures Positionedbar ends up in 0*/
     	lub_State_MO = IDLE;  /*returns the state machine to idle*/
        rub_CounterOnOff_Flag=OFF;
        ruw_time_counter=0; /* Flag off to get 400 ms counter restarted */
     }
     return lub_State_MO ;
}


/**************************************************************
 *  Name                 : Auto_Open_Func
 *  Description          : Fuction checks the button pressed time is <500ms to open the window automatically
 *  Parameters           : None
 *  Return               : lub_State_AO
 *  Critical/explanation : No
 **************************************************************/

T_UBYTE Auto_Open_Func(void)
{
	T_UBYTE lub_State_AO=WINDOWAUTO_OPENING;
 	T_UWORD luw_Time_Counter_AO=Reed_Ms_Counter(); /* Reeds Ms_Counter value */
 	T_SBYTE lsb_PositionLed_AO=Reed_PositionLedbar(); /* Reeds PositionLedbar */
 	rub_CounterOnOff_Flag=ON;
 	
	if ((BUTTON_DOWN_PRESSED==NO_PRESSED)&&(ruw_Time_Counter<BUTTON_TIME_500MS)&&(lsb_PositionLed_AO>=WINDOW_TOTALLY_OPEN))/*checks the time has been pressed less than 500ms*/
	{
					
		if (luw_Time_Counter_AO>=PACE_TIME_REQUIRED) /*Checks the Pace counter is 400ms to turn a led*/
		{
			Opening_Func();  /*turns off leds every 400ms*/
		}
		else      
		{
			/*do nothing*/
		}
		lub_State_AO=WINDOWAUTO_OPENING; /*Assures the state machine in Auto Opening State*/
	}
	else if(BUTTON_DOWN_PRESSED==PRESSED)  /*checks if the button keeps being pressed*/
	{
		if ((BUTTON_DOWN_PRESSED==PRESSED ) && (luw_Time_Counter_AO>BUTTON_TIME_500MS)) /*checks if the the button pressed time has overpassed the 500ms*/
		{
			lub_State_AO = WINDOWMANUAL_OPENING;  /*chenges the state machine to Manual opening*/
			
		}
		else 
		{
			/*do notghing*/
		}
	}
	else if(lsb_PositionLed_AO<WINDOW_TOTALLY_OPEN) /*checks if the window is totally open*/
	{
		lub_State_AO=IDLE;  /*changes the state machine to IDLE*/ 
		rsb_PositionLedbar=WINDOW_TOTALLY_OPEN;  /*assures Positionedbar ends up in 0*/
		rub_CounterOnOff_Flag=OFF;
		ruw_time_counter=0; /* Flag off to get 400 ms counter restarted */
	}
	else 
	{
	   	/*do nothing*/
	}
		  return lub_State_AO;
}


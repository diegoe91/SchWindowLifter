/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         WindowLifter.c
* Instance:         RPL_1
* version:          2
* created_by:       Diego Flores
* date_created:    	Wend Jul  01 11:00:00 2015 
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : here is the finite state machine of the window lifter   */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  2.7      | 07/01/2015  |       descripcion de modulo   | Diego Flores     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */


/** Own headers */
#include "WindowLifter.h"
#include "Idle&Anti_Pinch.h"
#include "DownFunction.h"
#include "UpFunction.h"
#include "typedefs.h"


/* GPIO routines prototypes */ 

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
T_UBYTE rub_State=IDLE;  /* Initialize the first state of the Window lifter finite states machine */
T_SBYTE rsb_PositionLedbar = WINDOW_TOTALLY_CLOSED;  /* Variable that indicates the led bar position  */
T_UBYTE rub_CounterOnOff_Flag=0;			/* flag to control counter operation */

/* WORD RAM variables */
T_UWORD ruw_Time_Counter=TIME_COUNT_RESTART;
T_UWORD ruw_Pace_Counter=PACE_TIME_REQUIRED;
T_UWORD ruw_time_counter = 0;  		/* Initialize the main time counter */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */
#define OFF 				                  0
#define ON  	     		                  1

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
 *  Name                 :	STATE_MACHINE
 *  Description          :  Finite State machine that controls all functions of the window lifter
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/
void State_Machine(void)
{
	switch (rub_State)
	{
		case IDLE:  
					rub_State=Idle_Func();
					break;

		case WINDOWMANUAL_OPENING:
					rub_State=Manual_Open_Func();
					break;
		
		case WINDOWMANUAL_CLOSING:
					
					rub_State = Window_Manual_Closing();
					break;
					
		case WINDOWAUTO_OPENING:
					 rub_State= Auto_Open_Func();
					break;
					
		case WINDOWAUTO_CLOSING:
					rub_State = Window_Auto_Closing();
					break;
					
		case ANTI_PINCH:
					rub_State = Anti_Pinch();
					break;
					
		default: 	rub_State=	IDLE;
					
					break;
	}
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

/**************************************************************
 *  Name                 :	Reed_Ms_Counter
 *  Description          :  function that manage the millisecond counter 
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/

T_UWORD Reed_Ms_Counter(void)
{
	T_UWORD luw_time_counter;
	luw_time_counter=ruw_time_counter;
	return luw_time_counter;
}

/**************************************************************
 *  Name                 :	Reed_Ms_Counter
 *  Description          :  function that manage the millisecond counter 
 *  Parameters           :  none
 *  Return               :  none
 *  Critical/explanation :  no
 **************************************************************/

T_SBYTE Reed_PositionLedbar(void)
{
	T_SBYTE lsb_PositionLedbar;
	lsb_PositionLedbar=rsb_PositionLedbar;
	return lsb_PositionLedbar;
}
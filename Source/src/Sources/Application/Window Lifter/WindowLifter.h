/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        WindowLifter.h
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

#ifndef _WINDOWLIFTER_H                               /* To avoid double inclusion */
#define _WINDOWLIFTER_H

/* Includes */
/* -------- */
#include "typedefs.h"
#include "GPIO.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */
#define WINDOW_TOTALLY_OPEN 0
#define WINDOW_TOTALLY_CLOSED 9
#define WINDOW_TOTALLY_OVERCLOSED 10
#define DEBOUNCED_TIME 3
#define TIME_COUNT_RESTART 0
#define PACE_RESTART 0

/* WORDS*/
#define PACE_TIME_REQUIRED 4

#define BUTTON_TIME_500MS 5



/* WORDS */


/* LONGS and STRUCTURES */

typedef enum
{
	IDLE,
	WINDOWMANUAL_OPENING,
	WINDOWMANUAL_CLOSING,
	WINDOWAUTO_OPENING,
	WINDOWAUTO_CLOSING,
	ANTI_PINCH
	
}STATES;

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 
extern T_UBYTE rub_State;
extern T_SBYTE rsb_PositionLedbar;
/* WORD RAM variables */
extern T_UWORD ruw_Time_Counter;
extern T_UWORD ruw_Pace_Counter;
/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
extern void STATE_MACHINE(void);


/* Functions macros */


/* Exported defines */


#endif /* _DUMMY_H */
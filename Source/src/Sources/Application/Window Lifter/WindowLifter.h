/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        WindowLifter.h
* Instance:         RPL_1
* version:         1 
* created_by:      Diego Flores
* date_created:    Wendsday July 01 10:55:01 2015 
*=============================================================================*/
/* DESCRIPTION : Header file template                                         */
/*============================================================================*/
/* FUNCTION COMMENT : contains only symbols which are exported to internal    */
/* platform modules. This will not be delivered with the library              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 16/07/2015  | SAR/SIF/SCN_xxx               | Diego Flores     */
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
#define Leds_Count0 0
#define Leds_Count10 10
#define Leds_Count9 9
#define Button_Validation 10
#define Time_Count0 0
#define Pace_Restart 0

/* WORDS*/
#define Pace_Count400 400
#define Pace_Count401 401
#define Time_Count500 500
#define AntiPinch_TimeLimit 5000


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
extern T_UWORD x;
/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
extern void STATE_MACHINE(void);
extern void opening_func (void)  ;

extern T_SBYTE MANUAL_OPEN_Func();
extern T_SBYTE AUTO_OPEN_Func();

/* Functions macros */


/* Exported defines */


#endif /* _DUMMY_H */
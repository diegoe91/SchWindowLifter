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

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
extern void STATE_MACHINE(void);

/* Functions macros */


/* Exported defines */


#endif /* _DUMMY_H */
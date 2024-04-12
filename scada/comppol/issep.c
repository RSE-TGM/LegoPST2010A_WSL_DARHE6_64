/*
   modulo issep.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)issep.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*                                                                    *
*			Procedura issep                                             *
*                                                                    *
*	La procedura rende 1 se il carattere passato e' un separatore     *
* compreso tra quelli elencati sotto, -1 altrimenti.                 *
*                                                                    *
*********************************************************************/
#include <osf1.h>
#include "tipi.h"
#include "chascii.inc"

issep(c)
char c;
{
switch(c) {
	case   BLANK :
	case APTONDA :
	case CHTONDA :
	case VIRGOLA :
	case    0x5b :     /* aperta quadra */
	case    0x5d :     /* chiusa quadra */
	case    0x3a :     /* due punti */
	case    0x00 :     /* fine stringa */
	case    0x2e :	    /* punto */
		return(1);
	default :
		return(-1);
}
}


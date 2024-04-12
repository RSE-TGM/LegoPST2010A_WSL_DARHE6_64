/**********************************************************************
*
*       C Source:               float_to_bin.c
*       Subsystem:              3
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Oct 21 13:43:42 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: float_to_bin.c-2 %  (%full_filespec: float_to_bin.c-2:csrc:3 %)";
#endif
/*
   modulo float_to_bin.c
   tipo 
   release 1.8
   data 7/12/95
   reserved @(#)float_to_bin.c	1.8
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)float_to_bin.c	1.8\t7/12/95";
/*
        Fine sezione per SCCS
*/
/*
	La seguente routine prende in ingresso il float valore e
	restituisce 0 o 1 a seconda che valore sia pari o dispari
*/

#include <stdio.h>
#include <string.h>
#include "libmanovra.h"

struct app_int_st{
#if defined AIX
	char spare_c[3];
        unsigned spare : 7;
        unsigned pari_dispari : 1;
#endif
#if defined ULTRIX || defined OSF1 || defined VMS || defined SCO_UNIX || defined LINUX
        unsigned pari_dispari : 1;
        unsigned spare : 7;
#endif
        };
typedef struct app_int_st APP_INT;


unsigned float_to_bin(float valore)
{
APP_INT app_int;
int valore_intero;
	
	valore_intero=valore;
#if defined ULTRIX || defined OSF1 || defined SCO_UNIX
	memcpy(&app_int,&valore_intero,1);
#endif
#if defined AIX || defined LINUX
	memcpy(&app_int,&valore_intero,4);
#endif
	return(app_int.pari_dispari);
}

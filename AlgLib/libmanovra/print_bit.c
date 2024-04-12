/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
   modulo print_bit.c
   tipo 
   release 1.3
   data 7/12/95
   reserved @(#)print_bit.c	1.3
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)print_bit.c	1.3\t7/12/95";
/*
        Fine sezione per SCCS
*/
/*

	La seguente routine stampa il contenuto in bit del char in ingresso
*/

#include <stdio.h>
#include <string.h>
#include "libmanovra.h"

struct app_char_st{
        unsigned bit_0 : 1;
        unsigned bit_1 : 1;
        unsigned bit_2 : 1;
        unsigned bit_3 : 1;
        unsigned bit_4 : 1;
        unsigned bit_5 : 1;
        unsigned bit_6 : 1;
        unsigned bit_7 : 1;
        };
typedef struct app_char_st APP_CHAR;

int print_bit(char *c)
{
APP_CHAR app_char;

	memcpy(&app_char,c,sizeof(char));
	printf("|%d%d%d%d%d%d%d%d|\n",
		app_char.bit_0,app_char.bit_1,app_char.bit_2,app_char.bit_3,
		app_char.bit_4,app_char.bit_5,app_char.bit_6,app_char.bit_7);

}

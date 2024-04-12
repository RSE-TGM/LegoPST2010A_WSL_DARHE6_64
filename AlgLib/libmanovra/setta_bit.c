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
   modulo setta_bit.c
   tipo 
   release 1.3
   data 7/12/95
   reserved @(#)setta_bit.c	1.3
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)setta_bit.c	1.3\t7/12/95";
/*
        Fine sezione per SCCS
*/
/*

	La seguente routine setta a valore il bit indicato in posizione
	nel char c
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


int setta_bit(char *c, unsigned valore, int posizione)
{
APP_CHAR app_char;
	
/*	printf("Setto %d il bit %d\n",valore,posizione);*/
	memcpy(&app_char,c,sizeof(char));
	if(posizione==0) app_char.bit_0=valore;
	else
	  if(posizione==1) app_char.bit_1=valore;
	  else
	    if(posizione==2) app_char.bit_2=valore;
	    else
	      if(posizione==3) app_char.bit_3=valore;
	      else
	        if(posizione==4) app_char.bit_4=valore;
	        else
	          if(posizione==5) app_char.bit_5=valore;
	          else
	          if(posizione==6) app_char.bit_6=valore;
	          else
	            if(posizione==7) app_char.bit_7=valore;
	memcpy(c,&app_char,sizeof(char));
}

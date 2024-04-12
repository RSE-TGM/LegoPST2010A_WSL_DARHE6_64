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
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)suoni.c	5.1\t11/10/95";
/*
   modulo suoni.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)suoni.c	5.1
*/
#include <stdio.h>


beep()
{
int c=7;
	printf("%c",c);
}

suono_errore()
{
	beep();
	beep();
	beep();
	sleep(1);
	beep();
}

suono_warning()
{
	beep();
}
	

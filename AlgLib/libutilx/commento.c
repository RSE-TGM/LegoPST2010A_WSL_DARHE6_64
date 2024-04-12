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
static char SccsID[] = "@(#)commento.c	5.1\t11/10/95";
/*
   modulo commento.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)commento.c	5.1
*/
#include <stdio.h>
#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>

#include "libutilx.h"

void commento(testo)
	char *testo;
{
if(DEBUG)
	printf("%s %d\n",testo,DEBUG);
}

/**********************************************************************
*
*       C Source:               readdescr.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 12:07:34 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: readdescr.c,2 %  (%full_filespec: 1,csrc,readdescr.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)readdescr.c	1.11\t3/27/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include "linfo.h"

void AllocaDescrmodello(DESCRMODELLO *ptr,int nchar)
{
   ptr->descrizione = (char *)XtMalloc( (nchar*sizeof(char)) );
}


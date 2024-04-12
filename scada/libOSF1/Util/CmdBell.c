/**********************************************************************
*
*       C Source:               CmdBell.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 24 14:37:04 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: CmdBell.c-3 %  (%full_filespec: CmdBell.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <osf1.h>
#include <stdio.h>
#include <dos.h>

#include "UxXt.h"
#include "g2comdb.inc"
#include "g2ptrdb.inc"
#include "g1tipdb.inc"
#include "diagnodi.inc"
#include "netmsg.h"
#include "mesqueue.h"
#include "messcada.inc"

extern short c_digor;

void CmdBell(int mode)
{
QUEUE_PACKET pack;
S_TRATG mtra;

// Variazione dello stato del digitale
if((mode && !bitvalue(dbdd+stCicalino,g2di_sl)) ||
   (!mode && bitvalue(dbdd+stCicalino,g2di_sl)))
{
	pack.que=c_digor;
	pack.wto=0;
	pack.flg=MSG_WAIT;
	pack.amsg=&mtra;
	pack.lmsg=sizeof(S_TRATG);
	mtra.mess=macdd;  
	mtra.ext=g1tipdd;
	mtra.indice=stCicalino;
	mtra.stato=(mode>0)? 1:0;
	enqueue(&pack);
}

#if defined OSF1 || defined LINUX
if(mode)
	bitset(dbdd+stCicalino,g2di_sl,1);
else
	bitset(dbdd+stCicalino,g2di_sl,0);
return;

/*
#ifdef XSCADA_INTERFACE
if(UxDisplay)
	XBell(UxDisplay,100);
else
#endif
	printf("%c",7);
*/
#endif
}


/**********************************************************************
*
*       C Source:               AttivaXscada.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Wed Jun 16 17:03:06 2004 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: AttivaXscada.c-4 %  (%full_filespec: AttivaXscada.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <Xm/Xm.h>




#ifdef XSCADA_INTERFACE
AttivaXscada(int argc,char **argv)
{


	printf("AttivaXscada\n\n\n");
	mainXscada(argc,argv);
}
#endif

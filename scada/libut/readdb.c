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
/*
        Fine sezione per SCCS
*/
/*
	la funzione readdb legge dal file fdbdp le caratteristiche
	del database
*/

#include <osf1.h>
#include <stdio.h>

#include "ansiscr.h"
#include "ctasti.inc"
#include "dconf.inc"

readdb(header)
DB_HEADER *header;
{
FILE *fp;
char fnome[FILENAME_MAX+1];

strcpy(fnome,conf[RTF]);
strcat(fnome,"/fdbdp.rtf") ;
fp=fopen(fnome,"rb+") ;
if(fp) fread(header,sizeof(DB_HEADER),1,fp);
else
{
	printf(" errore open fdpdb readdb ");
	exit(0);
}
fclose(fp);
}


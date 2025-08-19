/**********************************************************************
*
*       C Source:               rwgerarc.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 15:35:58 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: rwgerarc.c-3 %  (%full_filespec: rwgerarc.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	Legge dal file FGERARCH.RTF i livelli, di tutti i punti
	e per tutti i tipi di punti, di gerarchia allarmi.
*/

#include <osf1.h>
#include <stdio.h>

#include "g0strdb.inc"
#include "g2ptrdb.inc"
#include "dconf.inc"
#include <string.h>
#include <stdlib.h>

extern void iodb(FILE *, short, char *, int, int);

void rwgerarc(flag,db,ut)
DB_HEADER *db, *ut;
short flag ;
{
char fnome[FILENAME_MAX+1];
FILE *fp ;
short lung ;
unsigned long int offset;
		
#ifdef GERARC
/* Le gerarchie possono essere solamente lette */
if(flag) return;

strcpy(fnome,&conf[RTF][0]) ;          
strcat(fnome,FGERARCH) ;
fp=fopen(fnome,"rb") ;
if(!fp)
{
   perror("FGERARCH\n");
   exit(0);
}

/* Analogici acquisiti */
offset=0;
if(ut->dimaa)
	iodb(fp,flag,(char *)dbaag,sizeof(S_DBGERA),db->dimaa);        
else
	dbaag=NULL;

/* Analogici calcolati standard */
offset=offset+sizeof(S_DBGERA)*(long)db->dimaa;
if(ut->dimas)
	iodb(fp,flag,(char *)dbasg,sizeof(S_DBGERA),db->dimas);        
else
	dbasg=NULL;

/* Analogici calcolati non standard */
offset=offset+sizeof(S_DBGERA)*(long)db->dimas;
if(ut->dimac)
	iodb(fp,flag,(char *)dbacg,sizeof(S_DBGERA),db->dimac);        
else
	dbacg=NULL;

/* Analogici calcolati di diagnostica */
offset=offset+sizeof(S_DBGERA)*(long)db->dimac;
if(ut->dimad)
	iodb(fp,flag,(char *)dbadg,sizeof(S_DBGERA),db->dimad);        
else
	dbadg=NULL;

/* Analogici di uscita */
offset=offset+sizeof(S_DBGERA)*(long)db->dimad;
if(ut->dimao)
	iodb(fp,flag,(char *)dbaog,sizeof(S_DBGERA),db->dimao);        
else
	dbaog=NULL;

/* Digitali acquisiti */
offset=offset+sizeof(S_DBGERA)*(long)db->dimao;
if(ut->dimda)
	iodb(fp,flag,(char *)dbdag,sizeof(S_DBGERA),db->dimda);
else
	dbaog=NULL;

/* Digitali calcolati standard */
offset=offset+sizeof(S_DBGERA)*(long)db->dimda;
if(ut->dimds)
	iodb(fp,flag,(char *)dbdsg,sizeof(S_DBGERA),db->dimds);
else
	dbdsg=NULL;

/* Digitali calcolati non standard */
offset=offset+sizeof(S_DBGERA)*(long)db->dimds;
if(ut->dimdc)
	iodb(fp,flag,(char *)dbdcg,sizeof(S_DBGERA),db->dimdc);
else
	dbdcg=NULL;

/* Digitali di diagnostica */
offset=offset+sizeof(S_DBGERA)*(long)db->dimdc;
if(ut->dimdd)
	iodb(fp,flag,(char *)dbddg,sizeof(S_DBGERA),db->dimdd);
else
	dbddg=NULL;

/* Digitali di uscita */
offset=offset+sizeof(S_DBGERA)*(long)db->dimdd;
if(ut->dimdo)
	iodb(fp,flag,(char *)dbdog,sizeof(S_DBGERA),db->dimdo);
else
	dbdog=NULL;

/* Organi */
offset=offset+sizeof(S_DBGERA)*(long)db->dimdo;
if(ut->dimor)
	iodb(fp,flag,(char *)dbog,sizeof(S_DBGERA),db->dimor);
else
	dbog=NULL;

/* Stringhe */
offset=offset+sizeof(S_DBGERA)*(long)db->dimor;
if(ut->dimst)
	iodb(fp,flag,(char *)dbstg,sizeof(S_DBGERA),db->dimst);
else
	dbstg=NULL;

fclose(fp);
#endif
return;
}

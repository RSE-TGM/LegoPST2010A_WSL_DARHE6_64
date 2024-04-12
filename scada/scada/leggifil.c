/**********************************************************************
*
*       C Source:               leggifil.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 15:58:27 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: leggifil.c-3 %  (%full_filespec: leggifil.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*-> leggifil

        la function leggifile legge dal file strat.rtf la configurazione
		  delle linee seriali e parallele e le assegnazioni delle stampan-
		  ti a tabulati e libro giornale
	
		  29 Gennaio 1993
		  Inserita modifica per gestione linea Hardcopy
*/
#include <osf1.h>	 
#include <stdio.h>	 

#include "diagnodi.inc"
#include "dconf.inc"
#include "g2comdb.inc"
#include "print.inc"
#include "pscserr.inc"

//MAXextern char port_hc;
char port_hc;

/*
	vettore indirizzi schede bitbus (valori di default)
*/

int addrbb[2]={0x208,0x220};

leggifile()
{
int   appoint;
FILE  *fp;
short i;
char  stringa[200];
char  device[30];
S_FIS *p_fis;
short prn=0, val, data, stbit;
static char dig_prn[]={stprn1,stprn2,stprn3,stprn4,stprn5,stprn6};

strcpy(stringa,conf[RTF]);
strcat(stringa,STRAT);
fp=fopen(stringa,"r+");
if(!fp) pscserr(ERR_IO,ROU_LEGGIFIL,FILE_STRAT,0,SYS_HALT_DOS);

/*
	salto righe di commento
*/
for(;;)
{
	fgets(stringa,100,fp);
	if(stringa[0]!=';') break;
}
/*
	leggo la definizione delle linee 	e inizializzo le
	tabelle dei device
*/
p_fis=&stfis[0];
for(i=0;i<n_fis-1;i++,p_fis++)
   {
	data=0;
	stbit=0;
	sscanf(stringa,"%d %s %hd %hd %hd %c ",&appoint,device,&p_fis->baud,
		&data,&stbit,&p_fis->parity);
	p_fis->data=data;
	p_fis->stbit=stbit;
   	p_fis->linea=(char)appoint; // scanf legge come intero, ci vuole cast
	p_fis->flag=tpr_null;
	if(!strcmp(device,"PRN"))
	   {
		p_fis->dig=&dbdd[dig_prn[prn]];
		bitset(p_fis->dig,g2di_sl,1);					// off line
		prn++;
	   }
	if(!strcmp(device,"HCP"))							// carico n. porta in port_hc
	   {
		p_fis->dig=&dbdd[dig_prn[prn]];
		bitset(p_fis->dig,g2di_sl,1);					// off line
		prn++;
		port_hc=p_fis->linea;
	   }
	if(!strcmp(device,"NUL")) p_fis->linea=-1;
	fgets(stringa,100,fp);
   }
stfis[fis_disk].flag=tpr_null;					// tabella per disco 
stfis[fis_disk].dig=&dbdd[sthdisk];			// assegnata di default
stfis[fis_disk].linea=fis_disk;					// tabella per disco 
bitset(&dbdd[sthdisk],g2di_sl,0);		   // on line
/*
	salto righe di commento
*/
for(;;)
   {
	fgets(stringa,100,fp);
	if(stringa[0]!=';') break;
   }
/*
	leggo distribuzione stampanti fra libro giornale e
	tabulati
*/
sscanf(stringa,"%s %hd %hd",device,&stloga[0].indice[0],
											&stloga[1].indice[0]);
fgets(stringa,100,fp);
sscanf(stringa,"%s %hd %hd",device,&stloga[0].indice[1],
							&stloga[1].indice[1]);
fgets(stringa,100,fp);
sscanf(stringa,"%s %hd %hd",device,&stlogt[0].indice[0],
							&stlogt[1].indice[0]);
fgets(stringa,100,fp);
sscanf(stringa,"%s %hd %hd",device,&stlogt[0].indice[1],
							&stlogt[1].indice[1]);
/*
	controllo assegnazioni
*/
if(stloga[0].indice[0] >= n_fis || stloga[0].indice[1] >= n_fis
|| stloga[1].indice[0] >= n_fis || stloga[1].indice[1] >= n_fis
|| stlogt[0].indice[0] >= n_fis || stlogt[0].indice[1] >= n_fis
|| stlogt[1].indice[0] >= n_fis || stlogt[1].indice[1] >= n_fis)
{
		pscserr(ERR_CONF,ROU_LEGGIFIL,FILE_STRAT,0,SYS_HALT_DOS);
}
#if n_remote != 0
/*
   inizializzazione per devices remote 
*/
for(i=0;i<n_remote;i++)
{
   stremote[i].indice[0]=n_fis+i;
   stremote[i].indice[1]=-1;
   stfis[n_fis+i].flag=tpr_null;
   stfis[n_fis+i].dig=&dbdd[i];
   stfis[n_fis+i].linea=i;
   bitset(&dbdd[i],g2di_sl,1);
}
#endif
/*
	lettura eventuali indirizzi schede bitbus o altro
*/

for(;;)
{
	fgets(stringa,100,fp);
	if(feof(fp)) break;
	if(stringa[0]==';') continue;					// commento
	if(!strncmp(stringa,"ADDR_BB1",8))
	{
		if(sscanf(stringa,"%s %x",device,&addrbb[0]) !=2) pscserr(ERR_CONF,ROU_INIT,ADDR_BB,0,SYS_HALT);
	}
	if(!strncmp(stringa,"ADDR_BB2",8))
	{
		if(sscanf(stringa,"%s %x",device,&addrbb[1]) !=2) pscserr(ERR_CONF,ROU_INIT,ADDR_BB,0,SYS_HALT);
	}
}
fclose(fp);
}

/**********************************************************************
*
*       C Source:               sepiniz.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 16:03:09 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sepiniz.c-3 %  (%full_filespec: sepiniz.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*

	Sepiniz.c

	La routine Sepiniz esegue le operazioni iniziali per la gestione
	di una rete inet formata da armadi Sepa.
	Esegue le seguenti operazioni:
	-	legge header file fsvar
	-  per ogni armadio definito nell'header alloca la memoria
	   per gli svincoli
	-	inizializza la diagnostica dei nodi ponendoli off line e
		in modo operativo slave
	-	calcola il numero effettivo di armadi definiti e pone tutte
		le misure FA
	-  legge i coefficienti k relativi agli analogici del data base
		memorizzati alla fine dei record relativi agli armadi

	La routine opera supponendo che Marte non sia ancora attivo e
	che il data base di sistema sia gia' stato allocato.
	In caso di errore di allocazione memoria o di I/O su disco
	termina il programma

	Parametri

	nessuno

	Ritorno

	nessuno

	20 Aprile 1993

*/
#include <malloc.h>

#include "comunic.inc"
#include "g2comdb.inc"
#include "sepdati.inc"
#include "pscserr.inc"
#include "dconf.inc"
#include "sepdiag.inc"

extern DB_HEADER h_db;

sepiniz()
{
FILE *fp;
char filename[FILENAME_MAX+1];
HEA_FSVAR *pheafsvar;
short i;
short *pflag;

strcpy(filename,conf[RTF]);
strcat(filename,FSVAR);

fp=fopen(filename,"rb");
if(fp==NULL) pscserr(ERR_IO,ROU_INIT,FILE_FSVAR,0,SYS_HALT_DOS);
/*
	leggo header file per conoscere gli armadi definiti, n. punti
	associati
*/
fread((char*) heafsvar,sizeof(heafsvar),1,fp);
/*
	per ogni armadio verifico se ci sono associati dei punti
*/
n_confar=0;
for(i=0,pheafsvar=&heafsvar[0];i<sp_armadi;i++,pheafsvar++)
{
	if(pheafsvar->n_punti)
	{
		n_confar++;
		svinarp[i]=(short *)malloc(pheafsvar->l_punto*2);
		if(!svinarp[i]) pscserr(ERR_MEM,ROU_INIT,i,pheafsvar->l_punto*2,SYS_HALT_DOS);
		fseek(fp,(long)i*(long)sp_nump*(long)2+sp_heasvar,SEEK_SET);
		if(fread(svinarp[i],pheafsvar->l_punto*2,1,fp)!=1)
			pscserr(ERR_IO,ROU_INIT,FILE_FSVAR,1,SYS_HALT_DOS);
	}
	else svinarp[i]=0;
}
/*
	lettura indici coefficienti K
*/
fseek(fp,(long)sp_armadi*(long)sp_nump*(long)2+sp_heasvar,SEEK_SET);
if((Kaa=malloc(h_db.dimaa))==NULL) pscserr(ERR_MEM,ROU_INIT,h_db.dimaa,0,SYS_HALT_DOS);
if(fread(Kaa,1,h_db.dimaa,fp)!=h_db.dimaa)
				pscserr(ERR_IO,ROU_INIT,FILE_FSVAR,2,SYS_HALT_DOS);

fclose(fp);
/*
   pongo off line la comunicazione con i nodi della rete
	nel data base di sistema e nella struttura sepnodi
*/
pflag=&dbdd[stastopa];
for(i=0;i<(modper9b-stastopa);i++,pflag++) 
   if(((i+1)%3)) bitset(pflag,g2di_sl,1);

for(i=0;i<n_tot_nodi;i++)
{
     snodi[i].stato[n_digretA]=1;
     snodi[i].stato[n_digretB]=1;
     snodi[i].stato[n_digmodF]=0;
}
for(i=0;i<sp_armadi;i++) if(svinarp[i]) armfa(i,0);
return(0);
}

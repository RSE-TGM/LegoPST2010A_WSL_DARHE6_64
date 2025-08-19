/**********************************************************************
*
*       C Source:               init.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 31 10:41:35 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: init.c-4 %  (%full_filespec: init.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*->init 
	la function init inizializza :
	-	tabelle allarmi

	apre i file operativi :
	-  fnomi
	-	fddde
	-  fstato
	-  fdizst

	19	Aprile 1993
	Inserita gestione errore con routine pscserr
	Inserita open file Fdeao per caso acquisizione da periferiche non Sdi

   10 Febbraio 1995
   Inserita Gestione per AEM (file REGIS.RTF e comandi)
*/

#include <osf1.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#if defined OSF1 || defined LINUX
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <sys\types.h>
#include <sys\stat.h>
#endif

#include "switch.inc"         // per abilitare gli svincoli
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "video.inc"
#include "allar.inc"
#include "dconf.inc"
#include "diagnodi.inc"
#include "diagnoan.inc"
#include "pscserr.inc"

/* Function prototypes */
extern void pscserr(int, int, int, int, int);
extern void readiz(void *, FILE *);
extern void readtab(FILE *);

int init()
{
char fnome[FILENAME_MAX+1];
short lung;
short i,j ;
FILE *fp ;
/*
	lettura stati ammissibili per i vari tipi di organi
*/
lung=strlen(conf[RTF]);
strcpy(fnome,conf[RTF]);
strcpy(&fnome[lung],FSTATO) ;
fp=fopen(fnome,"rb") ;
if(!fp)   pscserr(ERR_IO,ROU_INIT,FILE_FSTATO,0,SYS_HALT_DOS);
for(i=0;i<g0dimtip;i++)if(!fread(&storg[i],sizeof(S_FSTATO),1,fp))
			 break ;
fclose(fp) ;
/*
	lettura stati in chiaro degli organi
*/
strcpy(&fnome[lung],FDIZST) ;
fp=fopen(fnome,"r+") ;
if(!fp)  pscserr(ERR_IO,ROU_INIT,FILE_FDIZST,0,SYS_HALT_DOS);
readiz(stat_diz,fp) ;
fclose(fp) ;

strcpy(&fnome[lung],FNOMI) ;
fpp[fnomi]=fopen(fnome,"rb") ;
if(!fpp[fnomi]) pscserr(ERR_IO,ROU_INIT,FILE_FNOMI,0,SYS_HALT_DOS);

strcpy(&fnome[lung],FDDE) ;
fpp[fdde]=fopen(fnome,"rb+") ;
if(!fpp[fdde])   pscserr(ERR_IO,ROU_INIT,FILE_FDDE,0,SYS_HALT_DOS);

#if defined (STAR_SDI)					// per periferiche tipo di tipo Sdi
#else
	strcpy(&fnome[lung],FDCOM) ;
	fpp[fdcom]=fopen(fnome,"rb") ;
	if(!fpp[fdcom])  pscserr(ERR_IO,ROU_INIT,FILE_FDCOM,0,SYS_HALT_DOS);

	strcpy(&fnome[lung],FDEAO) ;
	fpp[fdeao]=fopen(fnome,"rb") ;
	if(!fpp[fdeao])   pscserr(ERR_IO,ROU_INIT,FILE_FDEAO,0,SYS_HALT_DOS);
#endif

if (TABUL)									  /* tabulati	*/
   {
	strcpy(&fnome[lung],FTAB) ;
	fpp[ftab]=fopen(fnome,"rb") ;
	if(!fpp[ftab])   pscserr(ERR_IO,ROU_INIT,FILE_FTAB,0,SYS_HALT_DOS);

	strcpy(&fnome[lung],FDIZTAB) ;
	fp=fopen(fnome,"rb+") ;
	if(!fp)  pscserr(ERR_IO,ROU_INIT,FILE_FDIZTAB,0,SYS_HALT_DOS);
	readtab(fp) ;
	fclose(fp) ;
   }
//
//	inizializza tabelle video	associando fino a num_pall
//	pagine allarmi a ciascun video
//
for(i=0;i<num_video;i++)
{
	if(i>=num_pall) tstv[i].ind_un=0;
	else tstv[i].ind_un=i;
	for(j=0;j<n_zone;j++)
	{
		tstv[i].tsv[j].v_tipo=0;
		tstv[i].tsv[j].v_input=0;
		memset(tstv[i].tsv[j].v_pagina,0,10);
	}
}
#if defined (AEM)
   AemFileInit();
#endif

return(0);

}

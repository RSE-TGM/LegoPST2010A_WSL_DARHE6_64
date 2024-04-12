/**********************************************************************
*
*       C Source:               virtdisk.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 16:57:22 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: virtdisk.c-3 %  (%full_filespec: virtdisk.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	la routine stdisk scrive su disco le stringhe allarmi.
   I file vengono chiamati FILBGxy
      dove:
         x e' il numero della stampante virtuale
         y e' il numero del file in uso
           
   Ogni file viene chiuso al superamento di circa 360K bytes

   Parametri

      short    indice stampante virtuale
      char*    stringa da memorizzare su disco
      short    n. caratteri da scrivere
      short    se =1 viene forzata la chiudura del file

   Ritorno

      nessuno

*/
#include <osf1.h>
#include <dos.h>
#include <stdio.h>

#include "print.inc"
#include "virtinv.h"
#include "dconf.inc"
#include "g2comdb.inc"
#include "diagnoan.inc"

stdisk(char* stringa, short lung, short flag)
{
short ier;
S_PVIRT *pVirt;
char fnomeLbg[FILENAME_MAX+1];

pVirt=&virtprn[NLbgVirt];

if(NLbgVirt!=PLbgVirt)        // la precedente stampante virtuale e l'attuale coincidono ?
{
   if(LbgFp!=NULL) fclose(LbgFp);      // no! chiudo il file attualmente in uso
}
if(!pVirt->ByteOcc || (NLbgVirt!=PLbgVirt))
{
   PLbgVirt=NLbgVirt;
   if(!pVirt->ByteOcc)        // se deve essere cambiato il nome del file
   {
/*
	aggiorno nel data base di diagnostica il n. del file in uso
	e l'ora e il giorno in cui e' stato aperto
	poiche' il file e' in uso resetto il bit FZ di copiato
*/
   	pVirt->IFileU=dbadv[pVirt->DFileU];
	   pVirt->IFileU++;
   	if(pVirt->IFileU>max_n_allfile) pVirt->IFileU=1;
   	dbadv[pVirt->DFileU]=pVirt->IFileU;
	   dbadv[pVirt->DFileP+pVirt->IFileU-1]=dbadv[db_giorno]+dbadv[db_ora]*100;
   	bitset(&dbadf[pVirt->DFileP+pVirt->IFileU-1],g2an_fz,0);
   }	
   strcpy(fnomeLbg,conf[RTF]);
	strcat(fnomeLbg,FPRN00);
	fnomeLbg[strlen(fnomeLbg)-2]=fnomeLbg[strlen(fnomeLbg)-2]+NLbgVirt+1;      // virtuale
	fnomeLbg[strlen(fnomeLbg)-1]=fnomeLbg[strlen(fnomeLbg)-1]+pVirt->IFileU;   // file in uso
	strcat(fnomeLbg,RTFEXT);
   if(!pVirt->ByteOcc)
   	LbgFp=fopen(fnomeLbg,"wb");      // dimensione 0
   else
   	LbgFp=fopen(fnomeLbg,"ab");     // mantiene le dimensioni attuali
	if(LbgFp==NULL) return; 
/*
	verifico che il file successivo sia gia' stato copiato su dischetto
*/
  	virttlbg(NLbgVirt);
}
if(wbyte(fileno(LbgFp),(short*)stringa,pVirt->ByteOcc,lung)==-1) 
                           printf(" err wbyte %d",ier);

pVirt->ByteOcc=pVirt->ByteOcc+lung;
if(pVirt->ByteOcc > max_byte_LbgOcc && (flag==si_fine))   
{
   pVirt->ByteOcc=0;
   fclose(LbgFp); 
}
}




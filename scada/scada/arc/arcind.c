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
   arcind.c

   La funzione inizializza la struttura arcsort assegnando l'indirizzo
   e il dimensionamento del buffer da utilizzare per le operazioni di
   I/O in caso di ricerca dati d'archivio e l'indirizzo e il dimensiona-
   mento dei buffer per la preparazione dei messaggi di visualizzazione
   trend storici.
   Viene chiamata dal task tabul nella fase di inizializzazione

   Parametri

   indir char*    indirizzo del buffer I/O
   dim   short    dimensioni del buffer
   vdir  char*    indirizzo buffer per messaggi
   vdim  short    dimensioni del buffer

   Ritorno

   nessuno

   26 Marzo 1992  rel. 1.0 Fc
*/
#include <osf1.h>
#include "arc.inc"
arcind(indir,dim,vdir,vdim)
ARC_DBS *indir;
char *vdir;
short dim, vdim;
{
arcsort.indir=indir;
arcsort.dim=dim;
arcsort.vis=vdir;
arcsort.vdim=vdim;
return(0);
}

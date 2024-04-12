/**********************************************************************
*
*       C Source:               arctrc.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 31 14:20:38 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: arctrc.c-4 %  (%full_filespec: arctrc.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   arctrc

   Il modulo interpreta il messaggio msen con stringa $TRC
   ed invia al task tabulati il messaggio S_FLOPPY

   Parametri

   mric  short*      puntatore al messaggio della send (da $TRC)
   msen  S_FLOPPY*   puntatore al messaggio da inviare al task tabul

   Ritorno

   short lunghezza del messaggio da inviare al task tabulati

   3 Aprile 1992  Rel. 1.0 Fc
*/
#include <osf1.h>
#include <string.h>

#include "arc.inc"
#include "arcvis.inc"
#include "fileop_names.h"
arctrc(mric,msen)
short *mric;
S_FLOPPY *msen;
{
char *str;
char app[3];
short i;
ARCNOME *posname;

msen->lung=sizeof(S_FLOPPY);
msen->mess=mtrasfarc;
/*
   copio il nome del file in (*mric+3) lunghezza nome file
*/
mric=mric+3;
strncpy(msen->nome,(char*)(mric+1),*(mric));
msen->nome[*mric]=0;
mric=mric+1+(((*mric)-1)/2+1);   // punto al tipo del prossimo argomento
                                 // considerando la possibilita' di stringhe
                                 // dispari
/*
   dal nome del file ricavo il numero dell'archivio e ricerco
   il nome del file nella tabella arcnome
   in base alla durata dell'archivio aggiungo l'estensione ARC o ARS
*/
memcpy(app,msen->nome,2);
app[2]=0;
msen->archivio=atoi(app);
/*
   se il risultato della conversione e' 0 significa che non si
   tratta di file di archivio (gli archivi sono numerati da 1)
   e si e' avuto un errore nella chiamata ad atoi
*/
if(!msen->archivio)     // file qualunque aggiungo estensione .RTF
{
   msen->archivio=-1;
   msen->n_file=-1;
   strcat(msen->nome,RTFEXT);
}
else                    // file d'archivio: aggiungo estensione e n. file
{
#if defined OSF1 || defined LINUX
   if(!arcdes[msen->archivio-1].hea.c_dur) strcat(msen->nome,".ars");
   else strcat(msen->nome,".arc");
#else
   if(!arcdes[msen->archivio-1].hea.c_dur) strcat(msen->nome,".ARS");
   else strcat(msen->nome,".ARC");
#endif
   posname=arcnome[msen->archivio-1].arc;
   for(i=0;i<arcdes[msen->archivio-1].hea.n_file;i++,posname++)
   {
      if(!strcmp(posname,msen->nome)) break;
   }
   msen->n_file=i;
}
msen->blocco=*(mric+3);      // blocco
msen->dim=*(mric+1);         // dimensione
msen->flag=*(mric+5);        // flag

return(sizeof(S_FLOPPY));
}

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
   verifalt

   La funzione viene chiamata dalla routine verifall quando
   nell'allarme  generato deve essere inserito anche il valore
   del tempo del posto periferico
   Il messaggio MALLA viene trasformato in MALLAT prelevando il
   tempo dal buffer in common dell'acquisizione dove e' stato 
   memorizzato prima di chiamare la routine verifall

   Parametri

   QUEUE_PACKET *pack    pacchetto per send
   S_MALLA     *mess    messaggio malla da trasformare

   Ritorno

   nessuno

   4 Dicembre 1992 Fc
*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "tipal.inc"
#include "mesqueue.h"

MISTIME timeac;       /* valore tempo posto periferico    */

verifalt(pack,mess)
QUEUE_PACKET *pack;
S_MALLA *mess;
{
S_MALLAT messt;

/*
   ricopio messaggio ed inserisco tempo
*/
messt.m=*mess;
messt.t=timeac;
/*
   inserisco il valore
*/
messt.v=dbaav[mess->punt];
/*
   modifico lunghezza
*/
pack->lmsg=sizeof(S_MALLAT);
pack->amsg=(char*) & messt;
enqueue(pack);
}



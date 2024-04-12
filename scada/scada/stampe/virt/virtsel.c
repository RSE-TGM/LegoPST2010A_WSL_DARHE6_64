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
   virtsel.c

   La routine esegue le funzioni associate alla SEND $VIRT
   In base al valore della funzione:

      1     rende operativa la nuova configurazione
            (associazione zone - stampanti, stampante virtuale tabulati)
      2     reset flag FZ associato ad un file di libro giornale
            viene indicata la stampante virtuale ed il numero del
            file coinvolto

	Il messaggio e' cosi' formato:
		  
	word 0		= -2	argomento intero
	word 1		funzione
   word 2      = -2  argomento intero
   word 3      numero stampante
	word 4      = -2  argomento intero
	word 5		numero file libro giornale
   word 6      tappo

   Parametri
      mess  short *     messaggio di selezione zone

   Ritorno
      nessuno

*/
#include <osf1.h>
#include <stdio.h>

#include "print.inc"
#include "virtinv.h"
#include "g2comdb.inc"
#include "messcada.inc"
#include "allar.inc"
#include "video.inc"

struct  sel_zon {
								short arg1;
							   short funz;
                        short arg2;
                        short nvirt;
								short arg3;
								short nfile;
							} ;
			
virtsel(mess)
struct sel_zon *mess;
{
   short i;
   switch (mess->funz)
   {
   case 1:        // salvataggio nuova configurazione (word bassa + word alta)
      for(i=0;i<n_virt_lbg;i++)
      {
         virtprn[i].abzon=((short)dbadv[pVirtZone+i*2+1])<<16;
         virtprn[i].abzon+=(short)dbadv[pVirtZone+i*2];
      }
      if(gDefTabPrn>0 && gDefTabPrn<=n_virt_tab) gDefTabPrn=dbadv[pDefTab];
   break;
   case 2:        // set Flag FZ file libro giornale
   	bitset(&dbadf[virtprn[mess->nvirt-1].DFileP+mess->nfile-1],g2an_fz,1);
      virttlbg(mess->nvirt-1);
   break;
   }
return;
}



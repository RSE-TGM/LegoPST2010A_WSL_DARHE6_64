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
   ricono.c

   La funzione tratta i rientri degli allarmi con tipo di trattamento 3 e 8.
   Ricerca l'emissione corrispondente fra gli allarmi da riconoscere e 
   quelli gia' riconosciuti.

   Se l'emissione e' fra quelli gia' riconosciuti l'allarme viene eliminato
   dall'archivio, se invece deve essere ancora riconosciuta viene variato il
   tipo di trattamento a 4 in modo che , al momento del riconoscimento, non
   venga inserita in archivio.


   Parametri

   struct buff_all   *elem       puntatore alla struttura allarmi del punto
                                 da ricercare
   short             unita       zona di appartenenza del punto

   
   Ritorno

   nessuno

   27 Maggio 1992    Rel. 1.0 Fc.

	21 Gennaio 1993
	Gestione contatori allarmi per zona. Inserimento
	livelli di severita
*/   
#include <stdio.h>

#include "switch.inc"         // contiene parametri di attivazione
#include "g2comdb.inc"
#include "messcada.inc"
#include "allar.inc"

ricono (elem,unita)
struct buff_all * elem;
short unita;
{
short i, j, lsev, nallsev;
int data;
char *upal;         //  puntatore ai data base allarmi assegnati alla zona
                    //  di impianto
short point;        //  punt. dbs diagno contatori
S_DBS_ALL *all;     //  puntatore al data base allarmi in esame
struct buff_all *pall;  // elemento data allarme in scansione

/*
   ricerco l'emissione corrispondente al rientro specificato in *elem
   in tutte i data base allarmi possibili
*/
upal=&bDbsAlu[unita].pal[0];
for(i=0;i<max_dbsall;i++,upal++)
{
   if((*upal)==-1)  break;
   all= &bDbsAll[*upal];
/*
   setto lock della pagina che sto controllando
   e verifico la presenza dell'allarme
*/
  rew(all->mbox,0,&data );
  pall=all->pall;
  for(j=0;j<all->pout;j++,pall++)
  {
      if(pall->m.punt == elem->m.punt && ((pall->m.satt & 0x7F) == elem->m.sprec)  &&
      (pall->m.ext == elem->m.ext) && (pall->m.ertr & M_NOSEALL ) != 0x84 )
/*
        trovata emissione corrispondente verifico se e' ancora da
        riconoscere e gia' stato riconosciuto
*/
       {
           if(pall->mask >= 0 )      /*    da riconoscere        */
                 pall->m.ertr = (pall->m.ertr & M_SEALL) | 0x84 ;
           else                      /* riconosciuto             */
           {
                 pall->m.punt=-1 ;
                 bDbsAlu[unita].n_ar[*upal]--;      // decremento n. all. in archivio
                 if (CONT_ALL_ZONE)
                     {
                     point=first_cont_all+(max_zone*(*upal)+unita)*2+1;
                     dbadv[point]--;
  	                  lsev=( (pall->m.ertr & M_SEALL) >> 4);
                     nallsev= --bDbsAlu[unita].n_arsev[lsev][*upal];// dec. all. del livello
                     allsev (&dbadf[point],nallsev,lsev);
                     }
                 (*all->db_ar)=(*all->db_ar)-1; // in data base
         		  all->fchanga=1  ;
            }
        }
   }
   tra(all->mbox,1 );
}
return(0) ;
}



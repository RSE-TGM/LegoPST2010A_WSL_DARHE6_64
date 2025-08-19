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
   ricsi.c

   La funzione esegue il riconoscimento singolo di un punto data
   la sua posizione nella pagina allarmi.

   Se e' una emissione viene spostato il puntatore di archiviazione
   se e' invece un rientro viene eliminato insieme alla corrispondente
   emissione 

   La compattazione degli allarmi viene effettuata solo all'arrivo
   del messaggio di congelamento off

   Parametri

   apos   short       posizione del punto in pagina allarmi da 1 a 16
   alv   S_DBS_ALV    puntatore tabella video allarmi
   
   Ritorno

   nessuno

   11 Novembre 1992

*/   
#include <osf1.h>
#include <stdio.h>
#include <stdlib.h>

#include "switch.inc"         // contiene parametri di attivazione
#include "g2comdb.inc"
#include "messcada.inc"
#include "allar.inc"
#include "diagnoan.inc"

// External function declarations
extern int rew(int, int, int*);
extern int tra(int, int);
extern int gestri(short, short, short);
extern int allsev(short*, short, short);

int ricsi (apos,alv)
short apos;
S_DBS_ALV *alv;
{
S_DBS_ALL *ald;                     // puntatore dbs allarmi 
short punt;                         // punt. dbs diagno contatori
struct buff_all *all, *jall;        // puntatore elementi del dbs allarmi 
short j, i, lsev, nallsev;
short trat;                   // tipo di trattamento
short pvis0;                  // posizione ultimo allarme visualizzato
int data;
short iniciclo;               // inizio ciclo ricerca pagina allarmi
short zona;                   // zona impianto

ald=&bDbsAll[alv->pal];          // puntatore al data base allarmi
if(alv->pvis0==ald->pin) return(0); // intervenuto riconoscimento automatico
                                    // abortisco operazione
/*
   setto lock della pagina che sto controllando
   e verifico la presenza dell'allarme
*/
rew(ald->mbox,0,&data );
/*
   la variabile alv->pvis0 contiene la posizione dell'ultimo allarme
   inviato + 1
   La ricerca e' quindi da farsi all'indietro
*/
pvis0=alv->pvis0-1;              // posizione effettiva
all=ald->pall;                   // puntatore al buffer allarmi
all=all+pvis0;                   // sull' ultimo allarme visualizzato
/*
   j indice scorrimento allarmi effettivamente della zona voluta
   non ancora riconosciuti
*/
iniciclo=min(16,alv->nallco);
for(j=iniciclo;;all--,pvis0--)
{
    if(all->mask >=0 && abilzo.abil_zone[all->mask]) 
    {
      j--;
      if(j<alv->svi[apos-1]) break;
    }
}
/*
   gestione bit RI
*/
zona=all->mask;
//printf(" p %d ",all->m.punt);
gestri(all->m.ext,all->m.punt,0);
/*
   verifico se rientro o emissione
   Se emissione sposto il puntatore di archiviazione nella nuova
   posizione se superiore alla precedente
*/
if(all->m.ertr & 0x80 )                       // emissione
{
   dbadv[allemdb1+alv->pal*2]--;
   trat= (all->m.ertr & M_TRALL) ;        // inserimento in archivio ?
//printf("E ");
   if(trat  == 2  || trat == 3 || trat == 5 || trat == 8)
      {
      bDbsAlu[zona].n_ar[alv->pal]++;      // incremento cont. zona   
      *(ald->db_ar)=*(ald->db_ar)+1;            // incremento cont. globale
      if (CONT_ALL_ZONE)
         {
         punt=first_cont_all+(max_zone*alv->pal+zona)*2+1;
         dbadv[punt]++;
  	      lsev=( (all->m.ertr & M_SEALL) >> 4);
         nallsev = ++bDbsAlu[zona].n_arsev[lsev][alv->pal];// incr. all. del livello
         allsev (&dbadf[punt],nallsev,lsev);
         }
      all->mask=all->mask | 0x8000;             // riconosciuto
      if(pvis0 >= ald->pinv) 
         ald->pinv=pvis0+1; // nuovo puntatore archivio
/*
   modifico la tabella svi per allineamento con pagina allarmi
*/
      for(i=0;i<apos;i++) 
         alv->svi[i]++;
      }
   else 
      all->m.punt=-1;                      // non va in archivio elimino
}
else                                         // rientro
{
   dbadv[allridb1+alv->pal*2]--;
//printf("R ");
/*
   ricerco emissione corrispondente: se e' in archivio la elimino
   se e' in pagina allarmi vario il tipo di trattamento in modo
   che non venga archiviata
*/
  jall=all-1;
  if((all->m.ertr & M_TRALL)== 5 || (all->m.ertr & M_TRALL)== 2)
  {
     for(j=pvis0-1;j>=0;j--,jall--)
     {
      if(jall->m.punt == all->m.punt && ((jall->m.satt & 0x7F) == all->m.sprec)  &&
      (jall->m.ext == all->m.ext) && (jall->m.ertr & 0x80) )
/*
        trovata emissione corrispondente verifico se e' ancora da
        riconoscere e gia' stato riconosciuto
*/
       {
       // printf(" CE %d ",jall->m.punt);
           if(!(jall->mask & 0x8000))              // da riconoscere
           {       jall->m.ertr = (jall->m.ertr & M_SEALL) | 0x84 ;
                  // printf("ric ");
           } 
           else                       /* riconosciuto            */
               {
                  jall->m.punt=-1;                    // cancellazione emissione
                  bDbsAlu[zona].n_ar[alv->pal]--;      // decremento n. all. in archivio
                  if (CONT_ALL_ZONE)
                     {
                     punt=first_cont_all+(max_zone*alv->pal+zona)*2+1;
                     dbadv[punt]--;
  	                  lsev=( (jall->m.ertr & M_SEALL) >> 4);
                     nallsev = --bDbsAlu[zona].n_arsev[lsev][alv->pal];// dec. all. del livello
                     allsev (&dbadf[punt],nallsev,lsev);
                     }
                  (*ald->db_ar)=(*ald->db_ar)-1; // in data base
               }
            break;
        }
      }
   }
   all->m.punt=-1;                     // cancellazione rientro
}
if(alv->ind_all) alv->ind_all--;            // decremento puntatore ultimo allarme (se non in pagina allarmi)
                                            // allarme visualizzato
*(ald->db_al)=*(ald->db_al)-1;            // decremento cont. globale
bDbsAlu[zona].n_al[alv->pal]--;           // decremento cont. zona
if (CONT_ALL_ZONE)
   {
   punt=first_cont_all+(max_zone*alv->pal+zona)*2;
   dbadv[punt]--;
   lsev=( (all->m.ertr & M_SEALL) >> 4);
   nallsev = --bDbsAlu[zona].n_alsev[lsev][alv->pal];  // dec. all. del livello
   allsev (&dbadf[punt],nallsev,lsev);
   }
tra(ald->mbox,1);
return(0) ;
}


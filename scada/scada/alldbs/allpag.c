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
   allpag.c

   La subroutine allpag.c gestisce il riconoscimento  degli allarmi
   inserite nel vettore di puntatori S_PUNT costruito in seguito
   ad una richiesta di riconoscimento da pagina video qualsiasi
   Ogni punto viene ricercato nel data base allarmi e riconosciuto
   secondo la procedura gia' utilizzata nel modulo allric.c

   Parametri:

   Ndba  short          indice data base allarmi in cui effettuare la ricerca
   point S_PUNT*        vettore puntatori da riconoscre

   Ritorno

   nessuno

      6 Aprile 1995
         Corretta gestione tappo fine puntatori da esaminare

*/
#include <stdio.h>
#include <stdlib.h>

#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "tipal.inc"
#include "mesqueue.h"
#include "diagnoan.inc"


allpag(Ndba,point)
short Ndba;
S_PUNT * point;               // vettore misure da riconoscere
{
int data;
short npout;                  // n. massimo allarmi inseriti
short zona;                   // zona di impianto
short trat;                   // tipo di trattamento
short punt;
struct buff_all *all, *all_conf;     // elemento buffer allarmi
short iall,j, lsev, nallsev;
short flagpin;
#include "diagnodi.inc"
QUEUE_PACKET queue, qcval;
S_TRATG     mtra;             // messaggio diagnostica allarme riconosciuto
S_DBS_ALL *dba;               // data base allarmi da esaminare
S_MCVAL mcval;

dba=&bDbsAll[Ndba];
if(!(*(dba->db_al))) return; // nessun allarme da riconoscere

if (SEGNALA_RIC_ALLARMI)
{
	queue.que=c_digor;
	queue.wto=4;								// time out non infinito per evitare
	queue.flg=MSG_WAIT;					// blocchi in caso di riconoscimento automatico
	queue.amsg=(char*)&mtra;
	queue.lmsg=sizeof(mtra);
	mtra.ext=g1tipdd;
	mtra.stato=1;
	mtra.mess=macdd;
	mtra.indice=ricall+Ndba;
   if ((!SYS_DUALE) || sys_master)
	   enqueue(&queue);
}
rew(dba->mbox,0, &data );
npout=dba->pout;
/*
   esamino tutti i puntatori fino al tappo
*/
for (;point->point!=-1;point++)         
{
   all=dba->pall+dba->pin;                // data base allarmi da esaminare a partire dal meno recente
   iall=dba->pin;
   for(;iall<npout;iall++,all++)
   {
/*
   ricerco il punto nella lista degli allarmi
*/
      if((all->mask >=0) && (all->m.ext==point->tipo) && (all->m.punt==point->point))
      {
         gestri(all->m.ext,all->m.punt,0);      // reset RI
         zona=all->mask;                     // zona associata
/*
   verifico il tipo di trattamento e se si tratta di emissione o rientro
   emissioni 2 3 5 8 inserimento in archivio
*/
         if(all->m.ertr & 0x80 )
         {
            dbadv[allemdb1+Ndba*2]--;      // elimino emissione
            trat= (all->m.ertr & M_TRALL) ;
            if(trat  == 2  || trat == 3 || trat == 5 || trat == 8)
            {
                all->mask=all->mask+0x8000;  // allarme riconosciuto
                *(dba->db_ar)=*(dba->db_ar)+1;     // incremento cont. globale
                bDbsAlu[zona].n_ar[Ndba]++;    // incremento cont. zona
                if (CONT_ALL_ZONE)
                {
                  punt=first_cont_all+(max_zone*Ndba+zona)*2+1;
                  dbadv[punt]++;
     	            lsev=( (all->m.ertr & M_SEALL) >> 4);
                  nallsev = ++bDbsAlu[zona].n_arsev[lsev][Ndba];// incr. all. del livello
                  allsev (&dbadf[punt],nallsev,lsev);
               }
            }
            else all->m.punt=-1;          // non inserita in archivio
         }
/*
        rientro  2 5 ricerca emissione
*/
         else
         {
            dbadv[allridb1+Ndba*2]--;      // elimino rientro
            if((all->m.ertr & M_TRALL)== 5 || (all->m.ertr & M_TRALL)== 2)
            {
               for(all_conf=dba->pall,j=0;j<iall;j++, all_conf++)
               {
                  if(all_conf->m.punt  == all->m.punt &&
                  ((all_conf->m.satt & 0x7F)  ==  all->m.sprec ) &&
                  (all_conf->m.ext  == all->m.ext ))
                  {
/*                         
        trovata emissione cancello l'elemento dagli
        archivi
*/
                     all_conf->m.punt = -1 ;
                     *(dba->db_ar)=*(dba->db_ar)-1;               // decremento cont. globale
                     bDbsAlu[zona].n_ar[Ndba]--;    // decremento cont. zona   
                     if (CONT_ALL_ZONE)
                     {
                        punt=first_cont_all+(max_zone*Ndba+zona)*2+1;
                        dbadv[punt]--;
  	                     lsev=( (all->m.ertr & M_SEALL) >> 4);
                        nallsev = --bDbsAlu[zona].n_arsev[lsev][Ndba];// dec. all. del livello
                        allsev (&dbadf[punt],nallsev,lsev);
                      }
                      break;
                  }
               }
           }
           all->m.punt=-1;       // cancello rientro
         }
         *(dba->db_al)=*(dba->db_al)-1;                              // decremento cont. globale
         bDbsAlu[zona].n_al[Ndba]--;                             // decremento cont. zona
         if (CONT_ALL_ZONE)
         {     
            punt=first_cont_all+(max_zone*Ndba+zona)*2;
            dbadv[punt]--;
            lsev=( (all->m.ertr & M_SEALL) >> 4);
            nallsev = --bDbsAlu[zona].n_alsev[lsev][Ndba];  // dec. all. del livello
            allsev (&dbadf[punt],nallsev,lsev);
         }
      }
   }
}
/*
   eseguito riconoscimento di tutti i punti indicati: procedo
   al compattamento del buffer
*/
dba->pout=0;      // reset puntatori
dba->pin=0;
dba->pinv=0;
flagpin=1;
for(j=0,all_conf=dba->pall,all=dba->pall;j<npout;j++,all_conf++)
{
   if(all_conf->m.punt != -1 )
   {
      dba->pout++;
	   if(all != all_conf) (*all)=(*all_conf);
      if(all->mask<0)      // in archivio gia' riconosciuti
      {
         dba->pinv=dba->pout;    // puntatore inserimento in archivio per criterio
         if(flagpin) dba->pin++; // puntatore assoluto punti in archivio
      }
      else flagpin=0;      
      all++;
    }
}
if((*dba->db_al)==0)             // se sono stati riconosciuti tutti
{                                // gli allarmi devo aggiornare i video
   qcval.que = c_cval;
   qcval.flg = MSG_WAIT;
   qcval.wto = 4;
   qcval.amsg=(char*)&mcval;
   qcval.lmsg=sizeof(S_MCVAL);
   mcval.video=0;                // non significativo
   mcval.direz=0;
   mcval.zona=0;
   mcval.indice=mall;               // richiedo aggiornamento video
   dba->fchanga=1;
   enqueue( &qcval);
}
tra(dba->mbox,1);
if (SEGNALA_RIC_ALLARMI)
{
   if((*dba->db_al)==0)
   {
      mtra.indice=noall+Ndba;
      if ((!SYS_DUALE) || sys_master)
		   enqueue(&queue);
   }
}
return;
}

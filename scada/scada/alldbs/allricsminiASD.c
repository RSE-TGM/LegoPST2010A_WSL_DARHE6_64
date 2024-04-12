/**********************************************************************
*
*       C Source:               allric.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Fri Dec 13 15:53:36 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: allricsminiASD.c-6 %  (%full_filespec: allricsminiASD.c-6:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
   ricsminiASD.c

   La subroutine ricsminiASD gestisce il riconoscimento  di un allarme 
   da miniASD. Le informazioni riguardanti l' allarme da riconoscere
   punt ext ertr + data, sono inserite nella struttura S_DBS_ALV.
   Quando l' allarme viene trovato ne viene fatto il riconoscimento.
   L' allarme puo' anche non trovarsi + nel db allarmi perche' puo'
   essere gia' stato riconosciuto.

   Emissioni      2, 3, 5
                  vengono inserite in archivio
   Rientri        2, 5
                  vengono eliminate le corrispondenti emissioni gia'
                  archiviate

   Per ogni allarme trattato vengono aggiornati i contatori degli
   allarmi in archivio e degli allarmi da riconoscere.

   Parametri

   alv   S_DBS_ALV*     puntatore alla tabella allarmi relativa al
                        video che ha richiesto il riconoscimento

   Ritorno

   nessuno

   26 Maggio 1992    Rel. 1.0    Fc.

	21 Gennaio 1993
   Inserita gestione contatori allarmi in emissione e rientro
   per zona

*/
#include <osf1.h>
#include <stdio.h>
#include <stdlib.h>

#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "tipal.inc"
#include "mesqueue.h"
#include "diagnoan.inc"

ricsminiASD(alv)
S_DBS_ALV *alv;               // tabella video allarmi 
{
short limite;                 // n. massimo allarmi da riconoscere
S_DBS_ALL *all;               // puntatore dbs allarmi da considerare
short punt;                   // punt. dbs diagno contatori 
short ind;                    // indice allarme in esame a partire
                              // dal meno recente
int data;
short datav;            // per appoggio
short trat;                   // tipo di trattamento
short npout;                  // n. massimo allarmi in data base
struct buff_all *all_ex, *all_conf, *all_pin;
short u, j, lsev, nallsev;
short flagpin;
short save_pinv;              // salvo indice allarme archiviato piu' recente
                              // memorizzato in all->pinv
short zona;
#include "diagnodi.inc"
QUEUE_PACKET queue;
S_TRATG     mtra;
short all_found=0;           /* Mi segnala se ho trovato allarme */
short ack_set=0;             /* Indica se il riconoscimento e' avvenuto */

all=&bDbsAll[alv->par_miniASD.db];       // data base allarmi associato al video
/*
Operazioni da effettuare se ho una pagina allarmi aperta
*/
#if defined GERARC
abzon(&alv->mask1,&alv->mask2,alv->pal,alv->abgera);  // ricerco zone e gerarchie abilitate
#else
abzon(&alv->mask1,&alv->mask2,alv->pal);  // ricerco zone abilitate
#endif
/*******
if(!abilzo.n_al) return(0);
********/

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
	mtra.indice=ricall+alv->pal;
   if ((!SYS_DUALE) || sys_master)
	   enqueue(&queue);
   }

flagpin=0;                                 // nessun allarme non riconosciuto

/*
N.B. all->pin e' un puntatore ad un elemento della tabella allarmi.
Prima di questo elemento ho solo allarmi riconosciuti
*/

ind=all->pin;                              // indice scorrimento buffer
save_pinv=all->pinv;                       // salvo indice all. archiviato piu' recente
all->pinv=all->pin;                        // indice inserimento in archivio
#ifdef DEBUGYES
printf("allric:all->pinv=%d\n",all->pinv);
#endif

/* 
all_pin e all_ex sono puntatori per lo
scorrimento della tabella
*/

all_pin=all->pall+ind;                     /* indir.inserimento archivio */
all_ex=all_pin;                     	   /* indirizzo allarme da esaminare */

u=rew(all->mbox,0, &data );
npout=all->pout;
#ifdef DEBUGYES
printf("allric:all->pout=%d\n",all->pout);
#endif

/*
        Routine per allineamento indicatori pvis0 e pvis1 per scroll archivio
        o pagina allrmi. Viene chiamata in caso di riconoscimento a pagine e
        lo stesso data base e' visualizzato su altri video.
*/
allpvis(alv->pal,0,0);				// inizializzazione puntatori

/*
Eseguo un ciclo per scorrere la tabella allarmi e trovare
l' allarme cercato.
La ricerca termina se:
        1) sono arrivato fino alla fine della tabella indice == pout
        2) ho trovato l' allarme cercato
*/
/*
ind punta ad all->pin
*/

for ( ; ind < npout && !all_found ; all_ex++,ind++)
{
#ifdef DEBUGYES
printf("------npout=%d ind=%d------\n",npout,ind);
printf("all_ex->m.punt=%d all_ex->m.ext=%d all_ex->m.ertr=%x all_ex->ore=%d all_ex->minuti=%d all_ex->secondi=%dall_ex->m.satt and=%x,all_ex->m.sprec=%x\n",
         all_ex->m.punt,all_ex->m.ext,all_ex->m.ertr,
         all_ex->ore,all_ex->minuti,all_ex->secondi,
         (all_ex->m.satt & 0x7F),all_ex->m.sprec);
#endif

/*
   verifico che l'allarme abbia la zona di impianto corrispondente
   a quella selezionata e che sia ancora da riconoscere  (mask>0)
   in tal caso li ricopio senza trattarli
*/

   if(u=allmatch(all_ex,alv))
      {
#ifdef DEBUGYES
      printf("Risultato=%d\n",u);
#endif
      (*all_pin)=(*all_ex);
      if(all_ex->mask >=0) flagpin=1;     // allarme ancora da riconoscere
                                          // non incrementare il contatore
                                          // punti archiviati
      else if(!flagpin) all->pin++;       // incremento punt. allarmi in arc.
      all_pin++;
      all->pinv++;
      continue;
      }/* end if(allmatch */

   all_found=1;
/*
   allarme da riconoscere: 	reset bit RI
*/
#ifdef DEBUGYES
   printf("allricASD: TROVATO !!! to ri ext=%d punt=%d\n",
                           all_ex->m.ext,all_ex->m.punt);
#endif
   gestri(all_ex->m.ext,all_ex->m.punt,0);
   zona=all_ex->mask;                     // zona associata
/*
   verifico il tipo di trattamento e se si tratta di emissione o rientro
   emissioni 2 3 5 8 inserimento in archivio
*/
   if(all_ex->m.ertr & 0x80  && !(all_ex->mask & 0x8000))
   {
#ifdef DEBUGYES
printf("allric: allarme e' in emissione\n");
#endif
      dbadv[allemdb1+alv->pal*2]--;      // elimino emissione
      trat= (all_ex->m.ertr & M_TRALL) ;
      if(trat  == 2  || trat == 3 || trat == 5 || trat == 8)
          {
          (*all_pin)=(*all_ex); /* tecnica per cancellare eventuale rientro */
          all_pin->mask=all_pin->mask+0x8000;  // allarme riconosciuto
          ack_set=1;
#ifdef DEBUGYES
          printf("RICONOSC.!!! all_pin->mask=%x\n",all_pin->mask);
#endif
          if(!flagpin) all->pin++;
          all->pinv++;
          all_pin++;
#ifdef DEBUGYES
printf("allric: allarme e' in emissione all_pin=%d all->pinv=%d\n",
                 all->pin,all->pinv);
#endif
          *(all->db_ar)=*(all->db_ar)+1;     // incremento cont. globale
          bDbsAlu[zona].n_ar[alv->pal]++;    // incremento cont. zona
/*
Debug
*/
#ifdef DEBUGYES
printf("*******************DEBUG dopo if  ***********************\n");
         for(all_conf=all->pall,j=0;j< all->pout;j++, all_conf++)
		{
printf("j=%d\n",j);
printf("all_conf->m.punt=%d all_conf->m.ext=%d all_conf->m.ertr=%x all_conf->secondi=%d\n",all_conf->m.punt,all_conf->m.ext,all_conf->m.ertr,all_conf->secondi);
		}
printf("*******************DEBUG***********************\n");
printf("allric: allarme e' in emissione incrementati contatori\n");
#endif
          if (CONT_ALL_ZONE)
            {
            punt=first_cont_all+(max_zone*alv->pal+zona)*2+1;
            dbadv[punt]++;
  	         lsev=( (all_ex->m.ertr & M_SEALL) >> 4);
            nallsev = ++bDbsAlu[zona].n_arsev[lsev][alv->pal];// incr. all. del livello
            allsev (&dbadf[punt],nallsev,lsev);
            }
         }
   }
/*
        rientro  2 5 ricerca emissione
Quando ho un rientro devo andare a ritrovare il corrispondente
all in emissione. Pertanto devo rianalizzare la tabella allarmi 
all' indietro partendo dall' allarme in rientro da riconoscere
*/
   else
   {
#ifdef DEBUGYES
printf("allric:allarme in rientro\n");
#endif
      allpvis(alv->pal,ind,1);
      if((all_ex->m.ertr & M_TRALL)== 5 || (all_ex->m.ertr & M_TRALL)== 2)
      {
         /*for(all_conf=all->pall,j=0;j< all->pinv;j++, all_conf++)*/
         /*
         Parto dall' allarme in riconoscimento e vado all' indietro
         */
         j=ind;
         for(all_conf=all->pall+ind-1;j>0;j--, all_conf--)
         {

#ifdef DEBUGYES
printf("[%d] all_conf->m.punt=%d all_conf->m.ext=%d all_conf->m.ertr=%x all_conf->ore=%d all_conf->minuti=%d all_conf->secondi=%d all_conf->m.satt and=%x,all_ex->m.sprec=%x all_conf->mask =%x\n",j,
         all_conf->m.punt,all_conf->m.ext,all_conf->m.ertr,
         all_conf->ore,all_conf->minuti,all_conf->secondi,
         (all_conf->m.satt & 0x7F),all_ex->m.sprec,all_conf->mask );
#endif
            if(all_conf->m.punt  == all_ex->m.punt &&
              ((all_conf->m.satt & 0x7F)  ==  all_ex->m.sprec ) &&
              (all_conf->m.ext  == all_ex->m.ext ) &&
               (all_conf->mask & 0x8000 ) )
               {
               ack_set=1;
#ifdef DEBUGYES
printf("creco emiss:trovato!!!\n");
#endif
/*                      
        trovata emissione cancello l'elemento dagli
        archivi
*/
                all_conf->m.punt = -1 ;
                *(all->db_ar)=*(all->db_ar)-1;               // decremento cont. globale
                bDbsAlu[zona].n_ar[alv->pal]--;    // decremento cont. zona   
                if (CONT_ALL_ZONE)
                  {
                  punt=first_cont_all+(max_zone*alv->pal+zona)*2+1;
                  dbadv[punt]--;
  	               lsev=( (all_ex->m.ertr & M_SEALL) >> 4);
                  nallsev = --bDbsAlu[zona].n_arsev[lsev][alv->pal];// dec. all. del livello
                  allsev (&dbadf[punt],nallsev,lsev);
                  }
                break;
               }
         }   /* end for */
     }
     if(ack_set)
        dbadv[allridb1+alv->pal*2]--;      // elimino rientro
     else
        {
        all->pinv++;
        fprintf(stderr,"WARNING:alarm emission not found for back-to-normal \
                alarm punt=%d ext=%d \n",all_ex->m.punt,all_ex->m.ext);
        }
   }    /* end else all in rientro */

/*
Inserisco controllo per evitare che se ho un rientro [!(all_ex->m.ertr & 0x80)]
senza la corrispondente emissione, si decrementi il cont globale all

Se ho un allarme in emissione o ho un rientro con associata una emissione ...
*/
   if( ack_set  )
      {
      *(all->db_al)=*(all->db_al)-1;   // decremento cont. globale
      bDbsAlu[zona].n_al[alv->pal]--;  // decremento cont. zona
      if (CONT_ALL_ZONE)
         {
         punt=first_cont_all+(max_zone*alv->pal+zona)*2;
         dbadv[punt]--;
         lsev=( (all_ex->m.ertr & M_SEALL) >> 4);
         /*
         dec. all. del livello
         */
         nallsev = --bDbsAlu[zona].n_alsev[lsev][alv->pal];
         allsev (&dbadf[punt],nallsev,lsev);
         }
      }
}  /* end for */
/*
        compatto buffer archivio se il buffer allarmi e'
        quasi completo
*/
if(all->pout >= (all->dim)*80/100)
{
printf("COMPATTO BUFFER ARCHIVIO\n");
   allpvis(alv->pal,0,0);
   all_ex= all->pall;
   data=all->pin;
   datav=all->pinv;
   for(j=0,all_conf=all->pall;j<all->pinv;j++,all_conf++)
   {
      if(all_conf->m.punt != -1 )
         {
	 if(all_ex != all_conf) (*all_ex)=(*all_conf);
         all_ex++;
         }
      else 
         {
         if(j<all->pin) data -- ;        /* posto vuoto */
         datav--;
         allpvis(alv->pal,j,1);
         }
   }
   all->pin=data ;   /* nuovo puntatore */
   all->pinv=datav;
}
/*
        compatto buffer allarmi riconosciuti
*/
#ifdef DEBUGYES
printf("allric: ind=%d prima compatto buffer allarmi ri all->pinv=%d\n",ind,all->pinv);
#endif
all_ex= all->pall + all->pinv;
for (j=ind,all_conf= all->pall+j; j < all->pout;j++, all_conf++)
{
    (*all_ex)=(*all_conf);
    all_ex++ ;
}
#ifdef DEBUGYES
printf("allric:all->pout prima =%d ind=%d\n",all->pout,ind);
#endif
all->pout=all->pinv+(all->pout-ind);
#ifdef DEBUGYES
printf("allric:all->pout dopo =%d",all->pout);
#endif
alv->pvis0=all->pin;
#ifdef DEBUGYES
printf("allric: all->pout=%d alv->pvis0=%d =all->pin\n",all->pout,all->pin);
#endif
if(save_pinv > all->pinv) save_pinv=all->pinv+(save_pinv-ind);
all->pinv=max(all->pinv,save_pinv);
#ifdef DEBUGYES
printf("allric: all->pinv=%d\n",all->pinv);
#endif
tra(all->mbox,1);
/*
Debug
*/
#ifdef DEBUGYES
printf("*******************DEBUG***********************\n");
         for(all_conf=all->pall,j=0;j< all->pout;j++, all_conf++)
		{
printf("j=%d\n",j);
printf("all_conf->m.punt=%d all_conf->m.ext=%d all_conf->m.ertr=%x all_conf->secondi=%d\n",all_conf->m.punt,all_conf->m.ext,all_conf->m.ertr,all_conf->secondi);
		}
printf("*******************DEBUG***********************\n");
#endif
if (SEGNALA_RIC_ALLARMI)
   {
printf("allric:SEGNALA_RIC_ALLARMI !!!\n");
	if((*all->db_al)==0)
	   {
		mtra.indice=noall+alv->pal;
      if ((!SYS_DUALE) || sys_master)
		   enqueue(&queue);
	   }
   }
/*
Sblocco il lock e rendo il video pronto ad altre richieste 
*/
alv->par_miniASD.lock=0;
return(0);
}

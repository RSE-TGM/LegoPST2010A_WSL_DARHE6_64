/**********************************************************************
*
*       C Source:               alldec.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr  1 15:09:41 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: alldecminiASD.c-4 %  (%full_filespec: alldecminiASD.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*

   Dec.c

   Gestisce l'invio dei messaggi Vdeal e Vpaal per l'aggiornamento
   degli allarmi scandendo il data base indicato.

   Parametri

   flag  short    =1 visualizzare allarmi da riconoscere (Vdeal)

   off   short    n. di stringhe allarmi da visualizzare
                  16 pagina allarmi
                  8  archivio verso i piu' recenti
                  -16 pagina archivio prima pagina
                 -8 archivio verso i pou' vecchi

   all  S_DBS_ALL*  puntatore al data base allarmi da esaminare

   alv  S_DBS_ALV*  puntatore alla tabella video coinvolta

   Ritorno

      1     se non e' stato vidualizzato nessun allarme
            in caso di richiesta allarmi in archivio

      0     in tutti gli altri casi


   22 Maggio 1992  Rel. 1.0      Fc.

   20 Gennaio 1993
	Inserita gestione scroll pagina, riconoscimento singolo e
	livelli di severita'

    20 Ottobre 1994
   Ampliamento per MMI-Window (eliminata fzi)

    14 Marzo 1995
   Definita routine Allcod per codifica stringa allarmi (viene utilizzata
   anche per inviare la stringa associata all'ultimo allarme)

*/
#include <osf1.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "pscserr.inc"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include "messcada.inc"
#include	"mesqueue.h"
#include "allar.inc"
#include "diagnodi.inc"
#include "tipal.inc"

// External function declarations
extern int rew(int, int, int*);
extern int tra(int, int);
extern int allinger(void *, void *, void *);
extern int GetAlarmValue(short);
extern int allcod(short, void *, void *);

S_VDEAL   dec_mess;
extern S_ALL_PER_ZONE allxzone;

int decminiASD (flag,off,ald,alv)
short flag,off;
S_DBS_ALV *alv;
S_DBS_ALL *ald;
{
short stato;
short ier;
long tot ;
S_STRALL   *str ;
struct buff_all all ;
char desc[rec_fdda] ;  			/* buffer per leggere dai file descrittori */
short trat,ind_colore;
S_DBS_ALL *ali;
int kk;               
int appo;

#define l_header (sizeof(S_VDEAL)-16*sizeof(S_STRALL))

char appo_ger[n_gerarchie];
short i,h,l,j;
short  nall ;  					/* n. allarmi inseriti 							*/
short num,inizio,fine,inc;
short *pvis;
short pvisminiASD=0;            /* puntatore allarmi visualizz. per miniASD */
short f_mov;                  // flag movimento o ricopiatura
short f_pal;                  // flag pagina allarmi o archivio

short fzi;							// offset inizio puntatori per pagina allarmi

QUEUE_PACKET pack;

fzi=max_mis_zone*zonai;

pack.que = c_mmio;
pack.flg = MSG_WAIT;
pack.wto = 0;


/*
        se flag ==2 si tratta di inviare solamente il messaggio
        di aggiornamento parziale
        non occorre decodificare gli allarmi
*/
#ifdef DEBUGYES
printf("alldec_miniASD: filtro=%d tipo_all=%d \n",alv->par_miniASD.filtro,alv->par_miniASD.tipo);
#endif
memset(dec_mess.pag,0,l_pagina);
/*
Se miniASD inserisci nome di riconoscimento per messaggio
*/
   memcpy(dec_mess.pag,"$MINIASD",8);

dec_mess.zona=zonai+1;


switch(flag )                     // testo se si tratta di movimento 
{                                 // in pagina allarmi o archivio 
case 1:
   inizio=-1;
   fine=off-1 ;
   f_mov=0;
   inc=1;
   break;


default:                            // 0 mov. in archivio 4 movimento in pagina allarmi
   f_mov=1;                         // movimento
   if(off<0) {inizio=-off;fine=0;inc=-1;}
   else      {inizio=-1;  fine=off-1; inc=1; }
   if(!alv->ind_all) 
   {
      if(flag==4)       // in caso di scroll pagina allarmi si parte
      {                 // con gia' 16 allarmi presenti 
         alv->ind_all=16+abs(off);
         alv->ind_sav=abs(off);
         alv->movi=+1;
      }
      else { f_mov=0; alv->ind_all=abilzo.n_ar;}  // prima paginata archivio
   }
   else
   {                                               // cambio direzione ?
      if(off>0 && alv->movi==-1) alv->ind_all=alv->ind_all+ min(alv->ind_sav+8,16) ;
      else if(off<0 && alv->movi==1) alv->ind_all=alv->ind_all - min(8+alv->ind_sav,16);
                                                   // medesima direzione
      else alv->ind_all=alv->ind_all + alv->ind_sav*alv->movi ;
    }
   break;
}
if(off < 0)                                        // indice allarme da trattare
{  alv->movi=-1; num=1 ;  pvis=&alv->pvis1;  }
else
{  alv->movi=1 ; num=0 ;  pvis=&alv->pvis0;   }

/*
		  se visualizzo per la prima volta devo anche inizializzare a -2 
		  i 16 elementi di gdav a zero l'estensione ed inserire il tappo
*/
#ifdef DEBUGYES
printf("decASD: inizio ciclo !!! \n");
#endif
for(i=inizio; i != fine ;)
{
        if(pvisminiASD>=ald->pout)  break;
/*
   lock buffer allarmi: serve in caso di riconoscimento automatico
	quando rical e dec possono interrompersi a vicenda
*/
	rew(ald->mbox,0,&appo);
        all= *(ald->pall+(pvisminiASD));
		  tra(ald->mbox,1);
/*
        verifico accettabilita' allarme in base alle zone selezionate
        se sono in pagina allarmi non visualizzo allarmi gia' ricono-
        sciuti e viceversa se sono in archivio
        if(flag && all.mask <0) continue; 
        if(!flag && all.mask >=0) continue; 
        if((abilzo.abil_zone[all.mask & 0x7FFF]) && (all.m.punt != -1 ))
*/
/*
Controllo che l' allarme sia attivo
*/
#ifdef DEBUGYES
              printf("decASD: pvisminiASD=%d pout=%d\n",pvisminiASD,ald->pout);
              printf("decASD: trovato all[%d] punt=%d ext=%d ertr=%x\
                              ore=%d min.=%d sec=%d\n", 
                              i,all.m.punt,all.m.ext,all.m.ertr,all.ore,
                              all.minuti,all.secondi);
#endif
        if( (all.m.punt != -1 ))
	   {
	   allinger(&all.m,alv,appo_ger); 
           /*
           Casi in cui considero l' allarme:
           1) filtro ==0 && tipo_all!=tipo_richiesta
           2) filtro ==1 && tipo_all==tipo_richiesta
	   */
           if( 
                (  (!alv->par_miniASD.filtro) && 
                   (GetAlarmValue(all.m.punt)!=alv->par_miniASD.tipo)  ) ||
 
                (  (alv->par_miniASD.filtro) &&
                   (GetAlarmValue(all.m.punt)==alv->par_miniASD.tipo)  )
             )
              {

	      if(!memcmp(alv->par_miniASD.gerarchia,appo_ger,n_gerarchie)) 
	         {
#ifdef DEBUGYES
                 printf("\ndecASD:TROVATO !!!  all[%d] punt=%d ext=%d \
                              ertr=%x \n\n",i,all.m.punt,all.m.ext,all.m.ertr);
#endif
                 i=i+inc;   /* allarme valido da visualizzare */

                 str= & dec_mess.stringall[i] ;
                 allcod(flag, str, &all);
#ifdef DEBUGYES
                 printf("alldec: emissione[%d]=%d\n",i,
                         dec_mess.stringall[i].emission);
#endif
/*
Inserisco la gerarchia del punto riempiendo il campo hierarchy
del singolo allarme
*/
	         memcpy(dec_mess.stringall[i].hierarchy,appo_ger,n_gerarchie);

                 }/*end if memcmp */
              }/* end if filtro  */







	}/* end if (all->m.punt!=-1) */
        pvisminiASD++ ;
}
/*
        aggiorno puntatore agli allarmi visualizzati dell'
        archivio e mando  messaggio di aggiornamento parziale o
        totale
*/

MESS :
dec_mess.indice=vdeal ; 				/* messaggio completo */

dec_mess.video=ald->video+1 ;
dec_mess.nodo=ald->video;
dec_mess.cicalino=0;
dec_mess.n_pagina=ald->def; 	                  // data base allarmi
dec_mess.n_archivio=alv->cod;                   // codice visualizzazione
dec_mess.n_parch=abilzo.n_ar;                   // all. archiviati della zona
/*printf("MESS valore TOT pen=%d  TOT arc = %d\n",abilzo.n_al,abilzo.n_ar);*/
dec_mess.n_pall=abilzo.n_al;    				      // allarmi riconosciuti della zona		
/*
Inserisci nel messaggio la situazione delle verie zone allarmi
*/
memcpy(&dec_mess.zone_all,&allxzone,sizeof(S_ALL_X_ZONE));
/*
   Se non ci sono allarmi nelle zone selezionate verifico la situazione
   complessiva. Se ci sono allarmi pongo il contatore a un valore negativo
*/
if(!dec_mess.n_pall && (*ald->db_al)!=0)  dec_mess.n_pall=-1;
dec_mess.n_arch=0;          						

nall=0 ;
if(flag==2) goto INVIO ;  							   /* mess. parziale completo */
/*
   se si tratta di movimento in pagina allarmi la gestione
   equivale al movimento in archivio flag viene posto a 0
*/
if(flag==4) flag=0;
if(!f_mov)      					/* inserisco funzione */
{       
      dec_mess.funzione=0 ; 				/* ricopiare */
      nall=i+1;                              /* n. allarmi in messaggio */
}
else
{       
      if(off>0)dec_mess.funzione=2;          /* inserire dal basso */
      else     dec_mess.funzione=1;          /* inserire dall'alto */
}
/*
   se il numero degli allarmi inviati e' == 16 e sto gestendo
   la pagina allarmi setto il flag di pagina completa nella tabella
   video (la variabile full non deve essere modificata se sto muovendomi
   in pagina allarmi)
*/

if(flag) goto INVIO ;                        /* non occorrono altre informazioni */
INVIO :
/*
Inserisco comunque No total di allarmi trovati, nel messaggio
*/
#ifdef DEBUGYES
printf("decASD:Sto per inviare msg nall=%d\n",nall);
#endif
dec_mess.n_all=nall ;  								/* n. allarmi nel messaggio */


pack.amsg = (char*) &dec_mess;
pack.lmsg=l_header+sizeof(S_STRALL)*nall; /* n. byte mess. string. + header */
			
enqueue(&pack) ;
alv->par_miniASD.lock=0;
return(0) ;
}

/**********************************************************************
*
*       C Source:               alldec.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug 29 16:24:57 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: alldec.c-12 %  (%full_filespec: alldec.c-12:csrc:1 %)";
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
                  =0 visualizzare allarmi in archivio (Vdeal)
                  =2 aggiornamento parziale (Vpaal)
      		      =3 visualizzare allarmi da riconoscere 
                     (ricopiatura senza clear) (Vdeal)
                  =4 movimento in pagina allarmi di 8 allarmi alla volta
                  =5 richiesta visualizzazione all per gerar. miniASD

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

S_VDEAL   dec_mess;
extern S_ALL_PER_ZONE allxzone;

dec (flag,off,ald,alv)
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
char *appo;

#define l_header (sizeof(S_VDEAL)-16*sizeof(S_STRALL))

char appo_ger[n_gerarchie];
short i,h,l,j;
short  nall=0 ;  					/* n. allarmi inseriti 							*/
short num,inizio,fine,inc;
short *pvis;
short pvisminiASD;            /* puntatore allarmi visualizz. per miniASD */
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
memset(dec_mess.pag,0,l_pagina);
/*
Se miniASD inserisci nome di riconoscimento per messaggio
*/
if(flag==5)
   memcpy(dec_mess.pag,"$MINIASD",8);
else
   memcpy(dec_mess.pag,"$ALLARMI",8);

dec_mess.zona=zonai+1;
if(flag==2) goto MESS ;

if(tstv[ald->video].tsv[zonai].v_tipo==p_ar) f_pal=1;  // archivio
else f_pal=0;                                         // allarmi

switch(flag )                     // testo se si tratta di movimento 
{                                 // in pagina allarmi o archivio 
case 1:
case 2:
case 3:
   inizio=-1;
   fine=off-1 ;
   inc=1;
   alv->pvis1=alv->pvis0-1 ;
   alv->ind_all=0 ;
   f_mov=0;                         // ricopiatura
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
if(!f_mov) 
{
   for(i=0;i<16;i++)
	{
		gdav[ald->video][fzi+i].tipo=-2;	gdav[ald->video][fzi+i].point=-2;
		gdav[ald->video][fzi+i].ext=0;
	}
	gdav[ald->video][fzi+16].point=-1;
}

for(i=inizio; i != fine ;)
{
/*
        la ricerca viene interrotta quando :
        sono stati presentati tutti gli allarmi da riconoscere
        alv->movi=1  flag=1 pvis[1] = pout
        si e' arrivati in fondo all'archivio
        alv->movi=-1 flag=0 pvis[0]=-1
        si e' arrivati all'inizio dell'archivio con alv->movi =1
        alv->movi=1 flag=0 pvis[0] = pin
        si e' arrivati all'inizio dell'archivio con alv->movi =-1
        nella visualizzazione degli allarmi da riconoscere
        alv->movi=-1 flag=4 pvis1 = pin
        i=fine e nel caso di archivio devo essere posizionata
        sul primo allarme accettabile (vedi maschera)
*/
        if((alv->pvis0 >= ald->pout) && (alv->movi==+1)) break ;
        if((alv->pvis1 < 0) && (alv->movi==-1))break ;
        if((alv->pvis0 == ald->pinv) && (alv->movi==1) && (!flag)) break ;
        if((alv->pvis1 < ald->pin) && (alv->movi==-1) && (flag)) break ;


/*
   lock buffer allarmi: serve in caso di riconoscimento automatico
	quando rical e dec possono interrompersi a vicenda
*/
	rew(ald->mbox,0,&appo);
        all= *(ald->pall+(*pvis));
		  tra(ald->mbox,1);
        *pvis=(*pvis) + alv->movi ;
/*
        verifico accettabilita' allarme in base alle zone selezionate
        se sono in pagina allarmi non visualizzo allarmi gia' ricono-
        sciuti e viceversa se sono in archivio
*/
        if(flag && all.mask <0) continue; 
        if(!flag && all.mask >=0) 
          {
          printf("DEBUG: IGNORO all.m.punt=%d all.mask=%x\n",all.m.punt,all.mask);
          continue; 
          }
        else if (!flag)
          {
          printf("DEBUG: CONSIDERO all.m.punt=%d all.mask=%x\n",all.m.punt,all.mask);
          }
        if((abilzo.abil_zone[all.mask & 0x7FFF]) && (all.m.punt != -1 ))
	{
#ifdef FABIO
	memcpy(&dec_mess.zone_all,&allxzone,sizeof(S_ALL_X_ZONE));
printf("alldec.c: allarmi per zona:\n");
for(kk=0;kk<5;kk++)
	{
	printf("gerarchie default:zona=%d\n",kk);
	printf("n_all_pen[kk]=%d\n",dec_mess.zone_all.n_all_pen[kk]);
        printf("n_all_arc[kk]=%d\n",dec_mess.zone_all.n_all_arc[kk]);
	}
#endif
#ifdef GERARC
	if(allinger(&all.m,alv,appo_ger))
#endif
	    {
            i=i+inc;   /* allarme valido da visualizzare */

            str= & dec_mess.stringall[i] ;
            allcod(flag, str, &all);
/*printf("alldec: emissione[%d]=%d\n",i,dec_mess.stringall[i].emission);*/
/*
Inserisco la gerarchia del punto riempiendo il campo hierarchy
del singolo allarme
*/
		memcpy(dec_mess.stringall[i].hierarchy,appo_ger,n_gerarchie);
/*
printf("alldec.c: gerarchia alv:\n");
for(kk=0;kk<n_gerarchie;kk++)
        {
        printf("|%d",dec_mess.stringall[i].hierarchy[kk]);
        }
printf("\n");
*/
        }/*end if allinger */
	}/* end if abilzo */

}
/*
        aggiorno puntatore agli allarmi visualizzati dell'
        archivio e mando  messaggio di aggiornamento parziale o
        totale
*/

MESS :
if(flag==2)
{		
   dec_mess.indice=vpaal;				/* messaggio parziale */
	dec_mess.funzione=off;				/* se off =1 aggiornamento parziale	*/
												/* con ricopiatura data base   		*/
}
else    dec_mess.indice=vdeal ; 				/* messaggio completo */

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
#ifdef FABIO
printf("alldec.c: allarmi per zona:\n");
for(kk=0;kk<5;kk++)
	{
	printf("gerarchie default:zona=%d\n",kk);
	
	printf("n_all_PEN[kk]=%d\n",allxzone.n_all_pen[kk]);
	printf("n_all_ARC[kk]=%d\n",allxzone.n_all_arc[kk]);
	printf("n_all_pen[kk]=%d\n",dec_mess.zone_all.n_all_pen[kk]);
        printf("n_all_arc[kk]=%d\n",dec_mess.zone_all.n_all_arc[kk]);
	}
#endif
/*
   Se non ci sono allarmi nelle zone selezionate verifico la situazione
   complessiva. Se ci sono allarmi pongo il contatore a un valore negativo
*/
if(!dec_mess.n_pall && (*ald->db_al)!=0)  dec_mess.n_pall=-1;
dec_mess.n_arch=0;          							// puntat.in archivio 

nall=0 ;
if(flag==2) goto INVIO ;  							   /* mess. parziale completo */
/*
   se si tratta di movimento in pagina allarmi la gestione
   equivale al movimento in archivio flag viene posto a 0
*/
if(flag==4) flag=0;
if(!f_mov)      					/* inserisco funzione */
{       
      dec_mess.funzione=0 ; 						/* ricopiare */
		if(flag==3) dec_mess.funzione=3 ;		/*	ricopiare senza cancellare */	
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
if(flag)
{
   if(nall == 16) alv->full=0;
   else alv->full=1;
}

if(flag) goto INVIO ;                        /* non occorrono altre informazioni */

if(i==inizio) return(1) ;                    /* nessun allarme da archivio */

if(off> 0)  nall=i+1;                        /* n.allarmi freccia in giu' */
else                                         /* n. allarmi freccia in su' */
{        
   if(i != fine )         /* caso piu' vecchi  */
   {      
       for(l=0;l<(abs(off)-i);l++) memcpy(&dec_mess.stringall[l],&dec_mess.stringall[i+l],sizeof(S_STRALL)) ;
       nall=l ;    /* shift delle stringhe */
    }      
    else           /* se buffer non completo */
       nall=abs(off) ;
}
if(!f_mov) alv->ind_sav=nall ;            /* prima paginata archivio    */
else alv->ind_sav=abs(off);               /* movimento pagina allarmi o archivio */   
/*
        casi limite nel calcolo del puntatore all'ultimo
        allarme inserito nel messaggio
*/
if(f_pal && alv->ind_all > abilzo.n_ar)
      	alv->ind_all=abilzo.n_ar;	 		                  /*fine ar.*/
else if(!f_pal && alv->ind_all > abilzo.n_al)
      	alv->ind_all=abilzo.n_al;	 		                  /*fine ric.*/
/*
   esame casi limiti in fondo e all'inizio per scroll archivi e
   scroll pagina allarmi
*/
else if(f_pal)
{
   if(alv->pvis1 <0 && off<0 ) alv->ind_all=nall;   			/*in.su	 */
   else if(alv->pvis1 <0 && off >0) alv->ind_all=16+nall; /*in giu	 */
}
else
{
   if(off<0 && alv->pvis0>=ald->pout) alv->ind_all=abilzo.n_al-16;  /* in su */
   if(off>0 && alv->pvis1<=ald->pin) alv->ind_all=nall+16;           /* in giu*/   
}
dec_mess.n_arch=alv->ind_all;

INVIO :
// printf("DEBUG: Invio msg pag allarmi nall= %d flag=%d \n",dec_mess.n_all,flag);
dec_mess.n_all=nall ;  								/* n. allarmi nel messaggio */


pack.amsg = (char*) &dec_mess;
pack.lmsg=l_header+sizeof(S_STRALL)*nall; 			/* n. byte mess. string. + header */
			
enqueue(&pack) ;

if(flag==2) return(0) ;      /* fine operazioni per aggiorn. parz. */

tstv[ald->video].tsv[zonai].v_input=0 ;   		/* aggiornamento bloccato */
/*
        inserimento nuovi puntatori nella tabella video
        e ripristino del contatore aggiornamento
*/

if( nall < 16 && f_mov)     /* spos. a gruppi di 8 o 16 */
{
   if(off<0)
   { for(i=15;i>=nall;i--) { gdav[ald->video][fzi+i].tipo=gdav[ald->video][fzi+i-nall].tipo ;
	   	                    gdav[ald->video][fzi+i].point=gdav[ald->video][fzi+i-nall].point ;
		     						}
     for(i=0;i<nall;i++)   { gdav[ald->video][fzi+i].tipo= dec_mess.stringall[i].p.ext;
        			 			     gdav[ald->video][fzi+i].point= dec_mess.stringall[i].p.point;
			 						}	
   } 
   else																						 
   { for(i=nall;i<=15;i++) { gdav[ald->video][fzi+i-nall].tipo=gdav[ald->video][fzi+i].tipo;
	 								  gdav[ald->video][fzi+i-nall].point=gdav[ald->video][fzi+i].point;
									}
     for(i=16-nall;i<16;i++) { gdav[ald->video][fzi+i].tipo=dec_mess.stringall[i-16+nall].p.ext;
  									    gdav[ald->video][fzi+i].point=dec_mess.stringall[i-16+nall].p.point;
                             }   										   														  
   }
} 
else                /* inviata pagina completa */
  for(i=0;i<nall;i++) {	gdav[ald->video][fzi+i].point=dec_mess.stringall[i].p.point;
								gdav[ald->video][fzi+i].tipo =dec_mess.stringall[i].p.ext;
							 }														

tstv[ald->video].tsv[zonai].v_periodo=1;	 /* periodo aggiornamento 		*/
tstv[ald->video].tsv[zonai].v_cont=1; 		 /* invio immediato dei dati 	*/
tstv[ald->video].tsv[zonai].v_input=inp_db; /* input da data base 			*/
/*
        sistemo il limite non utilizzato della finestra in caso di
        spostamento nell'archivio o in pagina allarmi
*/
if(f_mov)
{
   num=abs(num-1) ;  /* sposto il limite della finestra */
   if(num) pvis=&alv->pvis1; 
   else pvis=&alv->pvis0;
   for(l=0;l<nall;)  /* numero effettivo di allarmi nuovi */
   {       
      (*pvis)=(*pvis)+alv->movi ;
      all= *(ald->pall+(*pvis));
      if(!f_pal && all.mask <0 ) continue;   // pag. allarmi riconosciuto
      if(f_pal && all.mask >=0 ) continue;   // pag. allarmi da riconoscere
      if((abilzo.abil_zone[all.mask & 0x7FFF]) && (all.m.punt != -1 )) 
#ifdef GERARC
      if(allinger(&all.m,alv,NULL))
#endif
		l++;
    }
}
return(0) ;
}

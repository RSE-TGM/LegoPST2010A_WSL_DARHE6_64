/**********************************************************************
*
*       C Source:               allcval.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 24 15:34:44 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: allcval.c-9 %  (%full_filespec: allcval.c-9:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
      Cval.c

      il task cval gestisce la visualizzazione dei data base allarmi.
      Visualizzazione, riconoscimento e archivi.

      Parametri

      nessuno

      22 Maggio 1992    Rel. 1.0 Fc
      20 Gennaio 1993
      Inserita gestione movimento in pagina allarmi, riconoscimento
      singolo e congelamento pagina allarmi
*/
#include <stdio.h>
#include <string.h>

#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include "messcada.inc"
#include	"mesqueue.h"
#include "allar.inc"
#include "diagnodi.inc"

#if defined OSF1 || defined LINUX
extern short mbox_scgev; // mbox per isncronizzazzione del messaggio
                         // mria fra scgev a cval
#endif

#ifdef GERARC
char g_cAbilCalcGer[max_dbsall];
extern short mbox_abilger;
#endif

// External function declarations
extern int abzon(short *, short *, short, char *);
extern int dec(int, int, void *, void *);
extern void decminiASD(int, int, void *, void *);
extern int rew(int, int, void *);
extern void tra(int, int);
extern void allmute(void);
extern void rical(void *);
extern void ricsminiASD(void *);
extern void allcomp(void *);
extern void allriv(void *, int);

int tcval ( )
{
/*
        definizione messaggio da scodare
*/

short nvideo ;        /* n. del video associato al messagio */
S_MCVAL  mcval ;
S_VPAGV mvpagv ;
S_ZONE *ptv ;
int i;
short j;
short ier;
S_DBS_ALV *alv;               // puntatore tabella video
S_DBS_ALV *ali;               // puntatore ad una generica tabella video
S_DBS_ALL *all;               // puntatore dbs allarmi
S_DBS_ALV alvid;              // puntatore tabella video allarmi
                              // di appoggio per riconoscimento sistema
                              // slave

#ifdef GERARC
int iRew;	// Parametro fittizio per istruzione rew()
#endif

QUEUE_PACKET pack;
QUEUE_PACKET spack;

alvid.mask1=0xFFFF;             // riconoscimento per tutte le zone
alvid.mask2=0xFFFF;             // riconoscimento per tutte le zone


INIZIO :

pack.que = c_cval;
pack.flg = MSG_WAIT;
pack.wto = 0;
pack.amsg = (char *)  &mcval;

spack.que = c_mmio;
spack.flg = MSG_WAIT;
spack.wto = 0;

/*
        verifico se ci sono dei messaggi
        se non ce ne sono mi sospendo
*/
dequeue(&pack);
/*
        scodo il messaggio
*/
nvideo=mcval.video ;
alv=&bDbsAlv[nvideo];                     // tabella dbs all. per video
all=&bDbsAll[alv->pal];                   // data base allarmi associato al video
ptv=& tstv[nvideo].tsv[zonai] ;           // zona video interessata
/*
        analisi del tipo di messaggio
*/
switch (mcval.indice)
{
/*
	in caso di richiesta pagina allarmi (non archivio) da tasto riservato forzo
	visualizzazione di tutte le zone
*/
case  mpal :    /* messaggio mpal */
		if (!mcval.direz)					
		{
		      alv->mask1=0xFFFF;               // tutte le zone
      		alv->mask2=0xFFFF;
		      alv->cod=0;
		}
case  mpal1:                           // solo quelle selezionate
/*
      controllo che la pagina allarmi non sia gia'
      visualizzata	con zone in comune su un altro 
      video
*/
   ali=&bDbsAlv[0];
   for(i=0;i<num_video;i++,ali++)
   {
      if(i==nvideo) continue;
      if(tstv[i].tsv[zonai].v_tipo != p_al && tstv[i].tsv[zonai].v_tipo != p_ar) continue;
      if(ali->pal == alv->pal && ((ali->mask1 & alv->mask1)
          || (ali->mask2 & alv->mask2))) goto INIZIO;
   }
/*
   preparo buffer zone abilitate e relativi contatori
*/
#ifndef GERARC 
   abzon(&alv->mask1,&alv->mask2,alv->pal);
#else
   abzon(&alv->mask1,&alv->mask2,alv->pal,alv->abgera);
#endif
/*
        mando il messaggio vpagv e procedo alla decodifica
        delle stringhe in allarme
*/
    ptv->v_input=0;			 
	 mvpagv.zona=zonai;				mvpagv.video=nvideo+1;
    mvpagv.nodo=nvideo;
	 memset(mvpagv.page,0,l_pagina); strcpy(mvpagv.page,"$ALLARMI");
	 memset(mvpagv.elen,-1,l_pagina); 
	 mvpagv.input= inp_db  ;
	 mvpagv.spare1=-1;

	 spack.amsg=(char *) &mvpagv;
	 spack.lmsg=sizeof(S_VPAGV);	   mvpagv.indice=vpagv;

/*
   se sono slave non devo inviare la richiesta di visualizza
   parte fissa a MMI per compatibilita' con la gestione delle
   altre pagine
*/
    if ((!SYS_DUALE) || sys_master) 
	   {
	   enqueue(&spack);
	   
	   }
   
    alv->pvis0=all->pin ;
    all->video=nvideo;                        // video associato alla pagina


/* 
 Case archive request and archive without any alarm: modified.
 A msg for archived alarms is sent anyway with alarms number set to 0
 The previous version sent a msg with the alarms in emission state.
 
Previous version was:
    if(!mcval.direz || !abilzo.n_ar) 
*/

    if(!mcval.direz )
       { 
       ptv->v_tipo=p_al;
       dec (1,16,all,alv) ;
       }
    else				  
       {  
       ptv->v_tipo=p_ar;								  
       alv->ind_all=0;
       alv->pvis1=all->pinv-1;       /* allarmi in */
       alv->pvis0=all->pinv;         /* archivio   */
       dec (0,-16,all,alv) ;
       }
     memcpy(ptv->v_pagina,mvpagv.page,l_pagina) ;
     goto INIZIO ;


case  mpalminiASD:                           // solo quelle selezionate
/*
      controllo che la pagina allarmi non sia gia'
      visualizzata	con zone in comune su un altro 
      video
*/
all=&bDbsAll[alv->par_miniASD.db];        /* data base allarmi associato alla 
                                             richiesta del miniASD */
/*
Evito di rifare controllo su altre pag allarmi che e' 
stato gia' fatto 
*/
   /* alv->pvis0=all->pin ; */
    all->video=nvideo;                        // video associato alla pagina
/*
Chiamo due volte il messaggio dec con il nuovo flag per
trovare gli allarmi del db 1 e del db2 in successione
*/
       decminiASD(1,16,all,alv) ;

     goto INIZIO ;



case mhal :
/*
   verifico se c'e' la pagina archivio in questo
   caso rivisualizzo gli allarmi ancora da riconoscere
   preparo buffer zone abilitate e relativi contatori
*/
     all->video=nvideo;                        // video associato alla pagina
     if(ptv->v_tipo == p_ar)
     {
          ptv->v_tipo=p_al;
          alv->pvis0=all->pin;
#ifndef GERARC
          abzon(&alv->mask1,&alv->mask2,alv->pal);
#else
   abzon(&alv->mask1,&alv->mask2,alv->pal,alv->abgera);
#endif
          dec (1,16,all,alv) ;
      }
     goto INIZIO ;

case mria :
/*
        solo se c'e' la pagina allarmi visualizzata
        permetto il riconoscimento solo se gli allarmi visualizzati
        sono i primi 16
*/

#ifdef GERARC
        rew(mbox_abilger,0,&iRew);
	g_cAbilCalcGer[alv->pal]=1;
        tra(mbox_abilger,1);
#endif
   if (ptv->v_tipo==p_al && (SKR_ALL && (all->pin>=alv->pvis1 || alv->ricsi) 
                                                || (!SKR_ALL)))      
     {
     if (RIC_SI)                   // riconoscimento singolo
         {
         if(alv->ricsi)                // aggiorno tutti i video
            {                            
            for (i=0,alv=&bDbsAlv[0];i<num_video;i++,alv++)
               {
#ifndef GERARC
               abzon(&alv->mask1,&alv->mask2,alv->pal);
#else
               abzon(&alv->mask1,&alv->mask2,alv->pal,alv->abgera);
#endif
               all->video=i;             
               dec(2,1,all,alv) ;
               }
			   allmute();						// verifica per cicalino
#if defined OSF1 || defined LINUX
	    tra(mbox_scgev,1); // sblocco il task scgev
#endif
            goto INIZIO;
            }
         }
         ptv->v_input=0 ; /* stop agg.*/
	      rical(alv);
			allmute();						// verifica per cicalino
/*
        chiamo dec aggiorno i video associati alla stessa unita
*/
         all->video=nvideo;                        // video associato alla pagina
#ifndef GERARC
         abzon(&alv->mask1,&alv->mask2,alv->pal);  // ricalcolo contatori
#else
         abzon(&alv->mask1,&alv->mask2,alv->pal,alv->abgera);
#endif
			dec (1,16,all,alv);
         for (i=0,alv=&bDbsAlv[0];i<num_video;i++,alv++)
         {
             all->video=i;             
             if(i!=nvideo) dec(2,0,all,alv) ;
         }
      }               
#if defined OSF1 || defined LINUX
      tra(mbox_scgev,1); // sblocco il task scgev
#endif
      goto INIZIO ;



case mricsminiASD :
/*
        solo se c'e' la pagina allarmi visualizzata
        permetto il riconoscimento solo se gli allarmi visualizzati
        sono i primi 16
*/
/*
Verificare se serve
*/
#ifdef GERARC
        rew(mbox_abilger,0,&iRew);
	g_cAbilCalcGer[alv->pal]=1;
        tra(mbox_abilger,1);
#endif
/*
Verifica  se operazione con miniASD e' abilitata
*/
/*   if (ptv->v_tipo==p_al && (SKR_ALL && (all->pin>=alv->pvis1 || alv->ricsi) 
                                                || (!SKR_ALL)))      
*/
     if( alv->par_miniASD.lock)
     {
         ptv->v_input=0 ; /* stop agg.*/
	      ricsminiASD(alv);
	      allmute();		// verifica per cicalino
/*
        chiamo dec aggiorno i video associati alla stessa unita
*/
         all->video=nvideo;                        // video associato alla pagina
#ifndef GERARC
         abzon(&alv->mask1,&alv->mask2,alv->pal);  // ricalcolo contatori
#else
         abzon(&alv->mask1,&alv->mask2,alv->pal,alv->abgera);
#endif
			dec (1,16,all,alv);
         for (i=0,alv=&bDbsAlv[0];i<num_video;i++,alv++)
         {
             all->video=i;             
             if(i!=nvideo) dec(2,0,all,alv) ;
         }
      }               
#if defined OSF1 || defined LINUX
      tra(mbox_scgev,1); // sblocco il task scgev
#endif
      goto INIZIO ;


case mnaa :
/*
        verifico se e' presente una pagina allarmi
        o archivio
        in base a cio' e alla direzione in cui devo muovermi
        chiamo dec con opportuni parametri
*/
/*
        parto dalla pagina allarmi e visualizzo i piu vecchi in
        archivio
*/
#ifndef GERARC
        abzon(&alv->mask1,&alv->mask2,alv->pal);
#else
        abzon(&alv->mask1,&alv->mask2,alv->pal,alv->abgera);
#endif
        all->video=nvideo;                        // video associato alla pagina
        if (!SKR_ALL)
            {
            if(ptv->v_tipo== p_al && mcval.direz!=0)
               {       
               if(alv->ricsi) 
                  goto INIZIO;
               if(abilzo.n_ar)                 /* se ci sono */
                  {       
                  alv->pvis1=all->pinv-1;        /* allarmi in */
                  alv->pvis0=all->pinv;           /* archivio   */
                  ptv->v_tipo=p_ar ;
                  dec(0,-16,all,alv) ;
                  }
               goto INIZIO ;                  
               }
            }
        else
            {
/*
        pagina allarmi visualizzo gli 8 piu' recenti
*/
            if(ptv->v_tipo== p_al && mcval.direz==0)
               {
               if(!alv->ricsi && alv->nallco == nall_vi) 
                  dec(4,8,all,alv)   ;
               goto INIZIO ; 
               }
/*
        pagina allarmi visualizzo gli 8 piu' vecchi
*/
            if(ptv->v_tipo== p_al && mcval.direz)
               {
               if(alv->ricsi || alv->nallco < nall_vi) 
                  goto INIZIO;
               ier=dec(4,-8,all,alv)   ;
               if(ier && abilzo.n_ar)              /* se ci sono */
                  {       
                  alv->pvis1=all->pinv-1;        /* allarmi in */
                  alv->pvis0=all->pinv;          /* archivio   */
                  ptv->v_tipo=p_ar ;
      		      alv->ind_all=0;
                  dec(0,-16,all,alv) ;
                  }
               goto INIZIO ; 
               }
            }
/*
        pagina archivio visualizzo gli 8 piu' vecchi
*/
        if(ptv->v_tipo== p_ar && mcval.direz!=0 && alv->pvis1 >=0)
            {
             dec(0,-8,all,alv)   ;
             goto INIZIO ; 
            }
/*
        pagina archivio visualizzo gli 8 piu' recenti
*/
         if(ptv->v_tipo== p_ar && mcval.direz==0)
            {     
            if( dec(0,8,all,alv))
/*
        se non ci sono piu` allarmi recenti visualizzo la  pagina
        allarmi
*/
            {        
                  alv->pvis0=all->pin;
		            dec(1,16,all,alv);
                  ptv->v_tipo= p_al ;
             }
         }
        goto INIZIO;
case mall :
/*
        aggiorno le pagine variate chiamando dec
        se sono presenti sul video o mandando un messaggio
        vpaal di aggiornamento parziale a tutti i video
        interessati
        se sono slave riconoscimento automatico con rical
*/
   for (j=0,all=&bDbsAll[0];j<max_dbsall;j++,all++)
      {
      if(!all->fchanga) 
         continue;           // nessun allarme
#ifdef GERARC
	rew(mbox_abilger,0,&iRew);
	g_cAbilCalcGer[alv->pal]=1;
	tra(mbox_abilger,1);
#endif
      rew(all->mbox,0,&i) ;
      all->fchanga=0 ;
      tra(all->mbox,1);
      if (SYS_DUALE && (!sys_master)) 
         {
         alvid.pal=j;
         rical(&alvid);
         }
      else
         {
         for (i=0,alv=&bDbsAlv[0];i<num_video;i++,alv++)
            {
            all->video=i;    
#ifndef GERARC
            abzon(&alv->mask1,&alv->mask2,j);
#else
            abzon(&alv->mask1,&alv->mask2,j,alv->abgera);
#endif
            if((tstv[i].tsv[zonai].v_tipo == p_al || tstv[i].tsv[zonai].v_tipo == p_ar)
							  && (j== alv->pal))
               {     									/* messagg vdeal */
		if(alv->full && tstv[i].tsv[zonai].v_tipo == p_al)
		  {
	          alv->pvis0=all->pin ;
/*
   se sono in riconoscimento automatico (full == -1) richiedo anche il clear 
   della  pagina allarmi e non solo la riscrittura
*/
                  if(alv->full==1) 
		     {
                     dec(3,16,all,alv)   ;
		     }
                  else 
                     {
                     dec(1,16,all,alv);
		     }
		     
		}
	   else // if(alv->full ... ecc. 
		{
                dec(2,1,all,alv);	  /* aggiornamento parziale con ricopiatura dati */
		}
              }
       	   else 
              {
              dec(2,0,all,alv);		     /* aggiornamento parziale senza ricopiatura    */
	      }
         }
      }
    }  /* end for principale */
   break ;
   
/*
   aggiornamento pagina dopo riconoscimento singolo
*/
case mriv:
      if (RIC_SI)
         {
#ifndef GERARC
         abzon(&alv->mask1,&alv->mask2,alv->pal);
#else
        abzon(&alv->mask1,&alv->mask2,alv->pal,alv->abgera);
#endif
         allcomp(alv);
         allriv(alv,nvideo);
         }
      break;
}

goto INIZIO ;

}

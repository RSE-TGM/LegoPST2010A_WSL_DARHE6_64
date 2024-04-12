/**********************************************************************
*
*       C Source:               allcall.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Mon May 31 09:49:22 1999 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: allcall.c-6.1.3 %  (%full_filespec: allcall.c-6.1.3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   call.c

   Task che gestisce l'inserimento degli allarmi nei vari data base
   in base all'unita' di appartenenza dei punti.
   E' in attesa del messaggio S_MALLA sulla coda c_visall.
   Alla fine del trattamento dei messaggi in coda invia la segnalazione
   al task Cval per l'aggiornamento delle pagine allarmi.

   Parametri 

   nessuno

   22 Maggio 1992    Rel. 1.0  Fc.
   16 Novembre 1992  Rel. 1.1  GM.Furlan 
      Caso simulatore: data sostituita da ora DOS
   20 Gennaio 1993
      Modifiche per gestione contatori allarmi severita'
      rientro ed emissione
*/
#include <stdio.h>

#include "switch.inc"         // contiene parametri di attivazione
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "diagnoan.inc"
#include "allar.inc"
#include "tipal.inc"
#include "mesqueue.h"
#ifdef AC_SIMULATORE
   #include "simana.inc"
#endif

S_MCVAL  messop = { 0,mall,0,0} ;   // {direz,indice,video,zona}

#ifdef GERARC
extern char g_cAbilCalcGer[];
extern short mbox_abilger;
#endif

extern int ricPreviousAll(S_DBS_ALV *,S_MALLA);


_call ( )
{
struct buff_all app , *all_ex;   /* buffer di appoggio per trasf. messaggio */
                                 /* e modifiche X ric. autom. dopo INITDB   */
short ins;
int ier;
short i, k, lsev , nallsev;
char  unita;           /* zona di impianto                             */
S_DBS_ALU *alu;        /* puntatore alla tabella delle zone di impianto*/
char *upal;            /* puntatore ai dbs allarmi associati alla zona */
short point;           /* punt. dbs diagno contatori                   */
S_DBS_ALL *all;        /* puntatore al data allarmi                    */
S_DBS_ALV alv;         /* tabella video allarmi fittizia per riconosc. */
                       /* automatico                                   */
S_DBS_ALV *ali;        /* puntatore di appoggio                        */
short *n_al;           /* contatore allarmi da inserire                */
short ab_cic; 	       /* abilitazione cicalino                        */
short ins_ric;         /* Riconosc. automatico dopo INITDB             */
short enable_compact=0;  /* enable automatic alarm compact               */
short trat;            /* tipo di trattamento                          */

#ifdef GERARC
int iRew;	/* Parametro fittizio per istruzione rew() */
#endif

   S_MALLAT mess;      /* messaggio scodato                            */
QUEUE_PACKET pack;
QUEUE_PACKET spack;

// Modalita' normale: riconoscimento automatico non innescato
/*****
Inserire switch su var di ambiente
*****/
ins_ric=0;

pack.que = c_visall;	
pack.flg= MSG_WAIT;					/* messaggio da ricevere */
pack.wto=0;
//
// LINEE TELEFONICHE DEFAULT
pack.amsg= (char *) &mess;

memset(&spack,0,sizeof(spack));
spack.que = c_cval;
spack.flg = MSG_NOWAIT;				/* messaggio per visualizzazione allarmi */
spack.wto = 1;						  
spack.lmsg = sizeof(S_MCVAL);
spack.amsg = (char *) &messop;

wai(20);								 // attesa per aspettare definizione ora al dos
										 // da parte del task tr che attende la risposta
										 // dalla scheda 546	nel caso di stop MB

us.stal.mess=mstal ;
alv.mask1=0xFFFF;             // riconoscimento per tutte le zone
alv.mask2=0xFFFF;             // riconoscimento per tutte le zone
alv.nallco=16;                // riconoscimento 16 allarmi alla volta
alv.ricsi=0;                  // riconoscimento singolo

/*
Test if the environment variable is set
*/
if(getenv("SCDCOMPACTALL"))
   {
   if(!strcmp(getenv("SCDCOMPACTALL"),"YES"))
       enable_compact=1;
   else enable_compact=0;
   }


INIZIO :

memset(&app,0,sizeof(struct buff_all));
if(dequeue(&pack))
{
	   pack.flg= MSG_WAIT;				// coda vuota attesa infinita
		pack.wto=0;
/*
	accodo a cval il messaggio aggiornamento pagine allarmi
*/
		enqueue(&spack);
      goto INIZIO ;             
}

pack.flg= MSG_NOWAIT;	// coda non vuota attesa non infinita
app.m=mess.m;                     // ricopio messaggio 
/*    
   arrivato messaggio sulla coda
   calcolo il tempo per l'emissione dell'allarme
*/
us.stal.ora=dbadv[db_ora] ;
us.stal.sec=dbadv[db_secondi];
us.stal.min=dbadv[db_minuti];

#ifdef AC_SIMULATORE
   us.stal.gior=dbadv[db_ora_sim];
   us.stal.mese=dbadv[db_minuti_sim];
   us.stal.anno=dbadv[db_secondi_sim];
printf("_call:minuti=%f\n",(float)dbadv[db_minuti]);
printf("_call:ora=%f\n",(float)dbadv[db_ora]);
#else
   us.stal.gior=dbadv[db_giorno];
   us.stal.mese=dbadv[db_mese];
   if(dbadv[db_anno]>=2000) us.stal.anno=dbadv[db_anno]-2000;
   else 						    us.stal.anno=dbadv[db_anno]-1900;
#endif

/*
	inserisco ora giorno minuti anche nel pacchetto che andra'
	nel buffer allarmi
*/
if(pack.lmsg == sizeof(S_MALLAT))      // inserisco tempo fornito
{                                      // dal messaggio MALLAT
   app.giorno =mess.t.dd;
   app.ore    =mess.t.hh;
printf("_call:ore=%d\n",app.ore);
   app.minuti =mess.t.mm;
   app.secondi=mess.t.ss;
}
{
app.giorno = dbadv[db_giorno];
app.ore    = us.stal.ora ;
app.minuti = us.stal.min ;
app.secondi= us.stal.sec;
}


ins=0  ;  /* non inserire l'allarme */

if (PAS_STOP)
#if defined (DEBUG)
   ;
#else
		trigger(app.m.ext,app.m.punt);
#endif


if (GESREP)
{
    if(app.m.ertr & 0x80)              // emissione
        GestRep(app.m.ext, app.m.punt, 1, app.m.satt);
     else                              // rientro
        GestRep(app.m.ext, app.m.punt, 0, app.m.sprec);
}

/*
	in stampa tutti gli allarmi con trattamento diverso da zero
	eccetto il tipo 7 di cui vengono stampate solo le emissioni
*/
ab_cic=tab_cic[(app.m.ertr & M_SEALL) >> 4];		// recupero severita' e timer cicalino
if((app.m.ertr & M_TRALL)) 
{
/*
	allarme accettabile  per stampe lo accodo,  caso 7 e 8 stampa solo
	emissioni
*/
	if((app.m.ertr & M_NOSEALL)!= 7 && (app.m.ertr & M_NOSEALL)!=8)
      if(pack.lmsg==sizeof(S_MALLAT)) stamalt(&mess);
      else  	stamal(&app.m);

	unita= cunita(app.m.punt,app.m.ext) ; 
	if(unita==-1) goto INIZIO;					// punto non definito
   app.mask=unita;                        // inserisco in record allarmi
   alu=&bDbsAlu[unita];                   // seleziono la zona impianto

	switch (app.m.ertr & M_TRALL)
	{
	case 2  :         /* visual. e/r */
	case 4  :         /* visual. e/r */
		ins=1 ;
		break ;
	case 6  :   /* visual. emiss. Per organi, stampa delle varazioni di stato comandate e spontanee */
		if ( (app.m.ext != g1tipor && app.m.ertr & 0x80) ||
           (app.m.ext == g1tipor && app.m.satt==var_org) ) 
		ins=1 ;
		break ;
	case 3  :         /* visual. e */
	case 8  :	      /* visual. e */
		if(app.m.ertr  & 0x80) ins=1 ;
		else
		{
			ins=0 ;     /* elim. emissione */
			ricono(&app,unita);	
		}
		break ;
	case 5  :   /*  non vis. solo al. cond. */
      if(app.m.ertr & 0x80)            /* emissione   */
      {   if(app.m.satt!=con_al && app.m.satt!=con_ba )ins=1 ;}
      else
      {   if(app.m.sprec!=con_al && app.m.sprec!=con_ba )ins=1 ;}
  	}

}

if(ins)
  {
  if(ab_cic) 
  CmdBell(tip_cic); 

  // segnalo colori in reverse
  if(pack.lmsg==sizeof(S_MALLAT)) app.m.satt=app.m.satt + 0x80;  
     flag_all=1;	// arrivati allarmi nuovi sulla pagina allarmi

/*
	se l'allarme deve essere presentato su pagina allarmi
	viene settato il bit RI del punto
*/


         /*
         Verifico se l' allarme e' da inserire gia' riconosciuto
         perche' sono in fase di startup o ho caricato uno 
         snapshot. (Verifica su bit 13 di dbdatr[indice-pto]).
         */


   if(bitvalue(&dbdatr[app.m.punt],ric13start) && ( app.m.ext==g1tipda ))
     {
     if(app.m.ertr & 0x80)
        ins_ric=1;
     bitset(&(dbdatr[app.m.punt]),ric13start,0);   
     }

   if(!ins_ric)       
      gestri(app.m.ext,app.m.punt,1); // De ric. solo se non in ric. autom.

   upal=&alu->pal[0];               // puntatore dbs associati alla zona

/*
	l'allarme deve essere visualizzato ricerco il dbs allarmi in cui
   inserirlo
*/
   for(i=0;i<max_dbsall;i++,upal++,n_al++)
      {

      if(*(upal) == -1) 
         break;             // fine ciclo
      all=&bDbsAll[*upal];                 // individuo il dbs allarmi
#ifdef GERARC
      rew(mbox_abilger,0,&iRew) ;
      g_cAbilCalcGer[*upal]=1;
      tra(mbox_abilger,1);
#endif

/*
 Block for the automatic acknowledgment  of previous alarms of the same point.
 The 6th bit of dbatr is tested and if the new alarm is an emission, an
 automatic acknowledgment is to be triggered.
*/

        if(enable_compact)
           if( (app.m.ertr & 0x80) && (!ins_ric) && 
             (bitvalue(&dbdatr[app.m.punt],ric6compact)) )
             {
#ifdef DEBUGYES
             printf("DEBUG: Dovrei chiamare ricPreviousAll db=%d punt=%d\n",*upal,app.m.punt);
#endif
             alv.pal=*upal;
             ricPreviousAll(&alv,app.m);
             }



/*
	inserisco l'allarme nel data base indicato settando il lock del dbs
   allarmi che sto considerando
	- incremento il contatore degli allarmi cont_all
	- incremento il puntatore al primo posto libero pout
*/
       if(all->pout >= all->dim)              // pieno ?
          {
          alv.pal=*upal;
          rical(&alv);                     // riconosco

          // forzo l'aggiornamento $ALLARMI
          for(k=0,ali=&bDbsAlv[0];k<num_video;k++,ali++) 
              if(ali->pal==(*upal)) ali->full=-1; 

          all->fchanga=1;                // variato dbs

       	  if(all->pout >= all->dim) 
              goto INIZIO;

	  }   /* end compattamento db allarmi */


        /*
        Parte per inserimento allarme nel db
        */
	rew(all->mbox,40,(int *)& ier) ;  // invio e-mail
        trat = (app.m.ertr & M_TRALL) ; // verify treatment (only for ins_ric)

        if(ins_ric)  
           {
           /*
           Solo per questi trattamenti 2,3,5,8; 1 allarme con 
           il trattamento 6 ad esempio, non viene inserito
           */
           if (trat  == 2  || trat == 3 || trat == 5 || trat == 8 ) 
              {
              all_ex=all->pall + all->pout;  // mi metto dove ins allarme
              memcpy((char *) (all->pall + all->pout),(char *) & app,sizeof(app)) ;
              all_ex->mask=all_ex->mask+0x8000;  // allarme riconosciuto
              alu->n_ar[*upal]++;
              all->pin++;     // inc. puntatore allarmi ric. consecutivi
              all->pinv++;    // inc. puntatore allarmi ric. consecutivi X video
              *(all->db_ar)=*(all->db_ar)+1 ;
              all->fchanga=1 ;
              all->pout++ ;
              }
           }
        else
           {
           alu->n_al[*upal]++;    // incremento n. all. della zona
#ifdef DEBUGYES
           printf("\n\nDEBUG:Inserisco allarme punt=%d in posiz. pout=%d \n",app.m.punt,all->pout);
#endif
           memcpy((char *) (all->pall + all->pout),(char *) & app,sizeof(app)) ;
	   all->fchanga=1 ;
	   all->pout++ ;
	   *(all->db_al)=*(all->db_al)+1 ;
           }


      if (CONT_ALL_ZONE)
         {
         point=first_cont_all+(max_zone*(*upal)+unita)*2;
         dbadv[point]++;
  	      lsev=( (app.m.ertr & M_SEALL) >> 4);
         nallsev=  ++alu->n_alsev[lsev][*upal];    // incremento n. all. della zona
         allsev (&dbadf[point],nallsev,lsev);
         }

      if( (app.m.ertr & 0x80) && (!ins_ric) )
         {
         if(enable_compact)  // only if alarm compact env is YES
            bitset(&(dbdatr[app.m.punt]),ric6compact,0);   
         dbadv[allemdb1+(*upal)*2]++;      // inserita emissione
         }
      else
         {
         if(enable_compact)  // only if alarm compact env is YES
            bitset(&(dbdatr[app.m.punt]),ric6compact,1);   
         dbadv[allridb1+(*upal)*2]++;      // inserito rientro
         }

      tra(all->mbox,1) ;

      } /* end for su max_dball (No db allarmi) */
}
ins_ric=0;
goto INIZIO ;
}


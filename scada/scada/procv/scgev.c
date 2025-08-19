/**********************************************************************
*
*       C Source:               scgev.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 16:46:14 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: scgev.c-6 %  (%full_filespec: scgev.c-6:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
     	il task gevid gestisce i messaggi provenienti da STOP
	I messaggi trattati per stop sono:
		- MCSP
		- MDIA
		- MPAV
		- MCLR

   19 Giugno 1992    Fc.

   Inserito lock con tabul per messaggi copia floppy, visualizzazione 
   trend storici e stampa tabulati (lockarc)

   18 Gennaio 1993   Fc.
   Modifiche per nuova gestione allarmi

   18 Luglio 1994    Fc.
   Modifica gestione messaggio $ALLARMI (SEND Pol)

	7 Settembre 1994 Fc.
	Modifica per gestione fine a 10 zone per compatibilita' com MMI-WIN

   28 Novembre 1994
      Inserita gestione messaggio per MMI Win vedi hostfiow e descrizw

   12 Dicembre 1994
      Inserita gestione messaggio mrdp esteso per lettura e scrittura
      contemporanea in data base

   27 Dicembre 1994
      Inserita gestione messaggio vdsgrack per ack consenso proseguire
      invio dati trend (verdi arctrend.c)
      Messaggio hardcopy MMI Window mhcp.

   06 Marzo 1995
      Inserita gestione riconoscimento allarmi da qualsiasi pagina video
      SEND $RICSIN

   18 Aprile 1995
      Inserita gestione messaggio mrdbl e mwdbl

   20 Giugno 1995
      Inserimento gestione stampante virtuale per richiesta tabulati

   22 Settembre 1995
      Gestione messaggio SEND per ISA "$ISA"

*/
#include <osf1.h>
#include <stdio.h>
#include <dos.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include "messcada.inc"
#include	"mesqueue.h"
#include "allar.inc"
#include "diagnodi.inc"
#include "diagnoan.inc"
#include "tipal.inc"
#include "print.inc"
#include "svindia.inc"
#include "netmsg.h"
#include "pscserr.inc"
#include "dconf.inc"
#include "pscs.cfg"
#include <all_1.h>
#include <string.h>

extern short c_hcwin;
extern int rxpio_tcb, txpio_tcb;
extern char leggi_data;
int jj;

union mess_inp { 	S_PALI all ;   /* richiesta pagina allarmi 	*/
						S_PAV pag ;    /* richiesta pagina video 		*/
		 			   S_MDIA dia ;   /* diagnostica micro				*/
                  S_TERM ter;    /* richiesta tabulato (per.)  */
		 				S_MCSP mcp ;	/* modifica stato punto 		*/
		 				S_MRDP  mrd;   /* richiesta descr. punto		*/
		 				S_MTAB  tab;   /* richiesta stampa tabulato	*/
						S_MSEN  mut ;	/* messaggio per utente			*/
						S_MAGGR gra;   /* richiesta aggiornamento grafico  */
                  S_IHCPY hcp;   /* richiesta hardcopy  MMI Win */  
                  S_RICHFILE rich; /* richiesta file su SCADA    */
						} ;


		struct t_mess     { 
								  short mess;
							     union mess_inp m; } sl;

union mess_out  { S_MCVAL mcval ; /* gestione allarmi  	              */
			      	S_VPAGV pag ;   /* richiesta pagina al micro         */
		  				S_PALO  cle ;   /* clear video	                    */
		  				S_STAB  tab ;   /* richiesta stampa tabulato         */
						S_SFILE sfil;	/* richiesta stampa file		*/
						S_VISARC vis;   /* richiesta visualizzazione archivi */
						CH_DATE dat ;   /* richiesta cambio data  			  */
						S_MMASTER mst;	/* messaggio diventa master		  */
			struct dosdate_t datet;
		   struct dostime_t timet;
					} r ;
extern int duatask_tcb;

//#if defined (STAR_SEPA)
//   #include "sepdiag.inc"
//#endif

short varstvid[max_video];          /* tabella variazione stato dei video */
												/* vedi task taggcfg						*/

#if defined (AC_INETDUALE)
	extern char _BitbusAddress;
#endif
#if defined (AC_SAMP)
   extern int  periodo_ora_samp;
#endif

extern char winFlagArc;           // flag per abilitare nella routine arctrend l'attesa dell'ack
extern char winStopArc;           // =1 procedere all'invio del messaggio dati =0 attendere messaggio vdsgrack

// Function declarations for missing functions
int bitvalue(short *buffer, short indice);
void hostfio(void *message);
void hostfiow(void *message);
void bitset(short *buffer, short indice, short bit);
void CmdBell(int flag);
void res(int tcb);
int arcvis(void *message, void *result);
void modpun(S_MCSP mcp, int flag);
void Rwritewi(S_MCSP *mcp);
void descriz(S_MRDP mrd);
void descrizwin(S_MRDP *mrd);
void wai(int delay);
void pscserr(int error_type, int task_id, int routine_id, int error_code, int sys_action);
int allselASD(short *buffer, int video);
int allsel(short *buffer, int video);
int allgerzo(short *buffer, int video);
void rall(short param1, short param2, short video);
void allsric(short *buffer, short video, int flags);
int tabFound(char *name, void *mut);
int arctrc(short *buffer, void *result);
void stamar(short *buffer, int flags);
void gesele(short param1, short param2, short param3);
int _dos_settime(struct dostime_t *time);
int _dos_setdate(struct dosdate_t *date);
void virtsel(short *buffer);
void isainv(short *buffer, int length);
int diagnet(short stvide, void *message, short *video);
void hcwin(int op, int video, int param);
void CloseTrFile(int video);
void mmidbl(void *message);
void trfile(void *message);

void scgev ( )
{
short video;
S_ZONE  *ptv ;
struct tm *ptr ;
short point,ext;
short *dbs;
char *p1,*p2;
short ier ;
short allarme, archivio;
short stato;
short k,i,j;
short indx ;
short lTab, *pTab;
S_TRATG mtra;
short pag_all, arch_all ;
QUEUE_PACKET pack ;
QUEUE_PACKET hpack;
QUEUE_PACKET spack;
QUEUE_PACKET dqueue;
QUEUE_PACKET  tqueue;
QUEUE_PACKET  slpack;

S_VIDEO *ptstv;

#if defined (AC_INETDUALE)
	#include "mesest.inc"
	QUEUE_PACKET ipack;
	S_INET_ABIL  mess_abil;
	S_INET_MASTER mess_master;
	S_INET_SYS	  mess_sys;
#endif

QUEUE_PACKET  wqueue, hcqueue;

hcqueue.que = c_hcwin;     // hardcopy
hcqueue.flg = MSG_WAIT;
hcqueue.wto = 0;
hcqueue.amsg=(char *)&sl.m;

wqueue.que = c_tabul;
wqueue.flg = MSG_WAIT;
wqueue.wto = 0;
wqueue.amsg=(char *)&sl.m.mcp;

#if defined (AC_INETDUALE)
	ipack.wto=0;
	ipack.flg=MSG_WAIT;
	ipack.que=c_ut_tx;
#endif

pack.que = c_mmii;
pack.flg = MSG_WAIT;
pack.wto = 0;
pack.amsg = (char *)  &sl.m;

spack.que = c_cval;
spack.flg = MSG_WAIT;
spack.wto = 20;
spack.amsg=(char*)&r;
spack.lmsg=sizeof(S_MCVAL);

dqueue.que = c_digor;
dqueue.flg = MSG_WAIT;
dqueue.wto = 20;
dqueue.lmsg=sizeof(S_TRATG);
dqueue.amsg = (char*) &mtra;


if (TABUL)									  /* tabulati	*/
   {
   tqueue.que = c_tabul;
   tqueue.flg = MSG_WAIT;
   tqueue.wto = 20;
   tqueue.amsg=(char *) & r;
   }

if (SYS_DUALE)
   {
   slpack.que = c_dua_tx;
   slpack.flg = MSG_WAIT;
   slpack.wto = 20;
   slpack.amsg=(char *) & sl;
   }

hpack.que = c_mmio;
hpack.flg = MSG_WAIT;
hpack.wto = 0;
hpack.amsg=(char*)&r;

/*
	   ciclo interpretazione messaggi micro operatore
*/
LOOP :
dequeue(&pack);							/* scoda messaggio */

/*
	se il sistema e' duale e sono master devo accodare
	allo slave tutti i messaggi che ricevo	
*/
if (SYS_DUALE)
   {
   if((sl.m.pag.indice != mdia) && (sl.m.pag.indice != STATOPORTA) && sys_master
	   && bitvalue(&dbdd[slaveagg],g2di_sl))
      {
	   sl.mess=MSG_MMI;
	   slpack.lmsg=pack.lmsg+2;
	   enqueue(&slpack);
      }
   }

dprintf(1,"[scgev.c] arrivato messaggio\n");
switch ((unsigned char)sl.m.pag.indice)
   {
	
   case READDATA:                 // gestione richieste file io remoto
   case WRITEDATA:
   case DELETEFILE:
	   hostfio(&sl.m);
	   goto LOOP;

   case FReadW:                 // gestione richieste file io remoto
   case FWriteW:
   case FDeleteW:
	   hostfiow(&sl.m);
	   goto LOOP;

   case mpal :
   case mhal :
   case mnaa :
   case mria :
	   if(!sl.m.all.video) 
         goto LOOP ;	               /* non accetto video 0 */
	   r.mcval.video=sl.m.all.video-1 ;
	   r.mcval.direz=sl.m.all.direz ;
	   r.mcval.zona=zonai ;
	   r.mcval.indice=sl.m.all.indice ;
	   enqueue(&spack);
	   goto LOOP;

   case   mdia:					/*		diagnostica periferiche stop */
	   for(i=0;i<(pack.lmsg-h_dia)/2;i++)
	      {
      		point=sl.m.dia.a[i].allarme;
      		if(point==-1) continue ;				/* punto non definito	  */
      		stato=sl.m.dia.a[i].condiz;
      		bitset(&dbdd[point],g2di_asl,stato) ;
         	if(stato==bitvalue(&dbdd[point],g2di_sl)) continue;
      	   if((!bitvalue(&dbdd[point],g2di_fs)) && 
      		(!bitvalue(&dbdd[point],g2di_fz)))
      		{
		      	bitset(&dbdd[point],g2di_sl,stato) ;
      			if(dbddu[point]==-1) continue;
      			mtra.mess=macdd;  mtra.ext=g1tipdd;
      			mtra.indice=point; mtra.stato=stato;
      			enqueue(&dqueue);
            }
   		   if(point == (stdint1+5) && sl.m.dia.a[i].condiz) 
            CmdBell(0);          //	digitale tacitazione cicalino
/*
	verifico se si tratta della segnalazione di un video off-line
	in tal caso cancello le pagine sul video
*/
		   if(point >= stvide1 && point <= stvide9 && sl.m.dia.a[i].condiz)	 
		      {
		      hpack.lmsg=sizeof(S_PALO);
			   r.cle.indice=vclrv;
			   r.cle.video=point-stvide1+1;
			   r.cle.nodo=point-stvide1;
			   r.cle.zona=zonaw+1;					 // zona window
			   enqueue(&hpack);
			   r.cle.zona=zonas+1;					 // zona servizio
			   enqueue(&hpack);
			   r.cle.zona=zonai+1;					 // zona intera
			   enqueue(&hpack);
		      }

/*
	commutazione slave->master richiedo la visualizzazione
	delle pagine nelle tabelle stato video
*/
         if (SYS_DUALE)
            {
	         if((point==master) && sl.m.dia.a[i].condiz)
		         {
#if defined (AC_INETDUALE)
/*
	se divento master devo dichiararmi master sia di rete che come
   funzionamento
*/
			      ipack.lmsg=sizeof(S_INET_MASTER);		// Master di rete
			      ipack.amsg=(char *)&mess_master;
		   	   mess_master.hea.addr_nodo=nodo_test_rete;
			      mess_master.hea.prov=cl_scada;
			      mess_master.hea.dest=cl_scada;
			      mess_master.hea.mess=inet_modo;
			      mess_master.modo=MASTER;
			      while(_BitbusAddress==-1) 
                  wai(2);
			      mess_master.nodo=_BitbusAddress;
			      enqueue(&ipack);

			      ipack.lmsg=sizeof(S_INET_SYS);			// modo operativo Master
			      ipack.amsg=(char*)&mess_sys;
			      mess_sys.hea.addr_nodo=nodo_test_rete;
			      mess_sys.hea.prov=cl_scada;
			      mess_sys.hea.dest=cl_scada;
			      mess_sys.hea.mess=inet_sys;
			      mess_sys.modo=MASTER;
			      enqueue(&ipack);
			      tra(mbox_inet,1);
               sys_master=1;
               wai(5);
               inetmast();
#endif
               sys_master=1;
		         res(rxpio_tcb);
		         res(txpio_tcb);
		         hpack.lmsg=sizeof(S_MMASTER);			// segnalo a MMI Master
		         r.mst.indice=MMASTER;
		         r.mst.classe=0;
		         for(j=0;j<num_video;j++)
			         {
			         r.mst.nodo=j;
			         enqueue(&hpack);
	   	         }
            }
/*
	se varia lo stato di comunicazione con lo slave abilito o disabilito
	anche i nodi inet delle stop
*/
#if defined (AC_INETDUALE)
            if(point==stlink)
			      {
			      ipack.wto=0;
			      ipack.flg=MSG_WAIT;
			      ipack.amsg=(char*)&mess_abil;
			      ipack.que=c_ut_tx;
			      ipack.lmsg=sizeof(HEASCA)+sizeof(mess_abil.n_nodi)+sizeof(S_NAB);

			      mess_abil.hea.addr_nodo=nodo_test_rete;
			      mess_abil.hea.prov=cl_scada;
		         mess_abil.hea.dest=cl_scada;
			      mess_abil.hea.mess=inet_abil;
			      mess_abil.n_nodi=1;
/*
	abilito nodi stop A e stop B
*/
			      if(! sl.m.dia.a[i].condiz)
				      mess_abil.n[0].abil=nodo_abilitato ;
			      else
				      mess_abil.n[0].abil=nodo_non_abilitato ;
			      mess_abil.n[0].addr=nodo_stop_1;
			      enqueue(&ipack);
			      mess_abil.n[0].addr=nodo_stop_2;
			      enqueue(&ipack);
			      tra(mbox_inet,1);
		         }  
#endif
/*
	caduta comunicazione con slave emetto rientro slaveiniz e slaveon
*/
		      if((point==stlink) && sl.m.dia.a[i].condiz)
		         {
/*
	devo riinizializzare il task tlink per l'aggiornamento
	dello slave
*/
			      res(duatask_tcb);

			      mtra.mess=macdd;  mtra.ext=g1tipdd;
			      if(bitvalue(&dbdd[slaveagg],g2di_sl))
			         {
				      bitset(&dbdd[slaveagg],g2di_sl,0);
				      mtra.indice=slaveagg; mtra.stato=0;
				      enqueue(&dqueue);
			         }
			      if(bitvalue(&dbdd[slaveon],g2di_sl))
			         {
				      bitset(&dbdd[slaveon],g2di_sl,0);
				      mtra.indice=slaveon; mtra.stato=0;
				      enqueue(&dqueue);
			         }
		         }
            }
         }
	   goto LOOP ;

   case   mpav :			/* visualiz. nuova pagina video	*/
	   ptv=& tstv[sl.m.pag.video-1].tsv[sl.m.pag.zona-1] ;
	   ptv->v_input=-1 ;
	   ptv->v_tipo=sl.m.pag.tipo;
	   indx=(sl.m.pag.zona-1)*max_mis_zone ;
							/* ricopio puntatori nella tabella video */
	   if(sl.m.pag.num_punti)
	      {																								  
		   p1= (char *) & gdav[sl.m.pag.video-1][indx] ;		  /* sistema */
		   p2= (char *) & sl.m.pag.d.p[0] ;
	 	   memcpy(p1,p2,sl.m.pag.num_punti*4) ;
/*
	fino ad ora non sono stati utilizzati vedi video.inc
*/
//		   p1= (char *) & punt_dbl[sl.m.pag.video-1][indx] ;	  /* locali  */
//		   p2= (char *) & sl.m.pag.d.s[sl.m.pag.num_punti] ;
//		   memcpy(p1,p2,sl.m.pag.num_punti*2) ;
	      }																								  
	   gdav[sl.m.pag.video-1][indx+sl.m.pag.num_punti].point=-1;	/*tappo*/
/* 	se viene spedita una pagina senza variabili di link
	non viene riempita  la sua tabella di stato video in modo
	che GDAC  la non aggiorni  */

	   if(!sl.m.pag.num_punti)
	      {
		   memcpy(&ptv->v_pagina[0],&sl.m.pag.nome[0],10) ;
   	   gdav[sl.m.pag.video-1][indx].point=-1;	                  /*tappo*/
		   goto LOOP;
	      }
      if (PER_GDAC!=1)
         {
	      if(sl.m.pag.per_sca < 0)  					/* periodo */
		      ptv->v_periodo= (- sl.m.pag.per_sca )*PER_GDAC/10 ;  /* periodo */
	      else
		      ptv->v_periodo= sl.m.pag.per_sca*PER_GDAC  ;  		  /* periodo */
         }
      else
         {
	      ptv->v_periodo= sl.m.pag.per_sca   ;  					/* periodo */
         }
      
	   memcpy(&ptv->v_pagina[0],&sl.m.pag.nome[0],10) ;
	   ptv->v_video=sl.m.pag.video-1;
	   ptv->v_address[0]=0 ;
	   ptv->v_cont=1 ;
	   ptv->v_input=sl.m.pag.tin  ;                   /* tipo inp */
	   goto LOOP ;

   case    mclr :								          /* clear zona video */

	   ptv= &tstv[sl.m.pag.video-1].tsv[sl.m.pag.zona-1]  ;
      ptv->v_input=0;
	   memset(&ptv->v_pagina[0],0,10);
	   memset(&ptv->v_address[0],0,10) ;
	   ptv->v_tipo=0 ;
      goto LOOP ;

   case    maggrwin:             // solo per MMI Win
   case    maggr:                                /* maggr clear zona e visualizzazione archivi */
									   						 /* se la zona e' intera setto ind_un n. pagina allarmi a -1 */
      if(!sys_master) goto LOOP;
      if(sl.m.pag.indice==maggr) winFlagArc=0;
      else  winFlagArc=1;           // attendere ack dopo ogni invio di dati

#if defined (SEPA) || defined (ACK_TREND)        // caso Sepa: abilitazione ack su messaggio
#if defined (MMI_PC)       // dati trend (non nel caso di STOPPC)
#else
            winFlagArc=1;           // attendere ack dopo ogni invio di dati
#endif
#endif

      if (ARCHIVI_NV)
         {
     	   tqueue.lmsg=arcvis(&sl.m,&r);
         if(tqueue.lmsg)          // messaggio di risposta ?
            {
            if(bitvalue(&dbdd[lockarc],g2di_asl)) 
               bitset(&dbdd[lockarc],g2di_sl,1);
            enqueue(&tqueue);
            }
         }
	   goto LOOP;

   case vdsgrack:   // consenso all'invio del prossimo messaggio di dati
      winStopArc=1;         // procedere all' invio del prossimo dato
      goto LOOP;

   case mcsp :													/* modifica stato punto */

/*
	esamina se nella sigla vi sono wildcharacters: in tal caso
	invia alla coda di tabul il messaggio di modifica stato punto
*/
	   if(sl.m.mcp.point[0]!=0 && sl.m.mcp.point[0]!=1 && sl.m.mcp.point[0]!=2 
	                           && memchr(sl.m.mcp.point,WILDCHAR,SCD_SIGLA))
		   {
		   sl.m.mcp.classe=0;
         if (TABUL)
            {
	         wqueue.lmsg=sizeof(S_MCSP);
		      enqueue(&wqueue);
            }
		   }
	   else
		   {
		   if(sl.m.mcp.point[0]==1)
			   {
			   sl.m.mcp.point[0]=0;
		 	   modpun(sl.m.mcp,1);	
			   }
		   else 
            if(sl.m.mcp.point[0]==2)
			      {
			      sl.m.mcp.point[0]=0;
		 	      modpun(sl.m.mcp,2); 
			      }
		      else
			      {
		 	      modpun(sl.m.mcp,0);	
			      }
		   }
	   goto LOOP ;

   case mcspext :	         // rwrite lettura e scrittura contemporanea
      Rwritewi(&sl.m.mcp);
	   goto LOOP ;

   case mrdp :										/* richiesta descrizione punto	*/

	   descriz(sl.m.mrd) ;	 
	   goto LOOP ;

   case mrdpwin :								/* richiesta descrizione punto MMI win	*/

	   descrizwin(&sl.m.mrd) ;	 
	   goto LOOP ;

   case msen :										/* messaggio per utente			*/
/* 
	Stop sistema senza ripresa
*/
	if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$HLT",sl.m.mut.buff.s[0]))
	{
		hpack.lmsg=sizeof(S_MMASTER);			// segnalo a MMI Stop Sistema
		r.mst.indice=STOPMMI;
		r.mst.classe=0;
		for(i=0;i<num_video;i++)
		{
			r.mst.nodo=i;
			enqueue(&hpack);
		}
		wai(40);									// attesa 10 sec.
		pscserr(ERR_TASK,TASK_RETE,TASK_RETE,END_ERR,SYS_HALT_FLUSH);
	}
/*
Verifico se si tratta per msg per miniASD
*/
if(sl.m.mut.buff.s[0]>0 && (!strncmp(&sl.m.mut.buff.c[2],"$MINIASD",sl.m.mut.buff.s[0])))
   {
#ifdef DEBUGYES
   printf("scgev.c:Ricevuto msg per miniASD !!!\n");
   printf("scgev.c:sl.m.mut.buff.s[0]/2+1=%d\n",(sl.m.mut.buff.s[0])/2+1);
#endif
   r.mcval.direz=allselASD(&sl.m.mut.buff.s[sl.m.mut.buff.s[0]/2+1],
                                     	     sl.m.mut.video);
         if(r.mcval.direz==-1) 
            goto LOOP;       // messaggio non accettabile
		   r.mcval.video=sl.m.mut.video-1;                 
		   r.mcval.zona=zonai;
		   switch (r.mcval.direz)
         {
            case mpalminiASD:                  // pagina allarmi o archivio
               r.mcval.indice=mpalminiASD;
#ifdef DEBUGYES
               printf("scgev: indice=mpalminiASD\n");
#endif
            break;
            case mricsminiASD:                 // riconoscimento allarmi
               r.mcval.indice=mricsminiASD;
            break;
         }
		   enqueue(&spack);
		   goto LOOP; 	
   }
/*
	la modifica dell'archvio viene permessa se non si e' in archivio
*/
#ifndef GERARC
	   if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$ALLARMI",sl.m.mut.buff.s[0]))
         {
		   r.mcval.direz=allsel(&sl.m.mut.buff.s[sl.m.mut.buff.s[0]/2+1],
                  sl.m.mut.video);
#else
	if(sl.m.mut.buff.s[0]>0 && (!strncmp(&sl.m.mut.buff.c[2],"$ALLARMI",sl.m.mut.buff.s[0]) ||
	                            !strncmp(&sl.m.mut.buff.c[2],"$ALLGERZO",strlen("$ALLGERZO"))))
	{
		if(!strncmp(&sl.m.mut.buff.c[2],"$ALLARMI",sl.m.mut.buff.s[0]))
			r.mcval.direz=allsel(&sl.m.mut.buff.s[sl.m.mut.buff.s[0]/2+1],
                                     	     sl.m.mut.video);
		else
			r.mcval.direz=allgerzo(&sl.m.mut.buff.s[sl.m.mut.buff.s[0]/2+1],
                                     	     sl.m.mut.video);
#endif
         if(r.mcval.direz==-1) 
            goto LOOP;       // messaggio non accettabile
		   r.mcval.video=sl.m.mut.video-1;                 
		   r.mcval.zona=zonai;
		   switch (r.mcval.direz)
         {
            case 1: case 0:         // pagina allarmi o archivio
               r.mcval.indice=mpal1;
            break;
            case 2:                 // riconoscimento allarmi
               r.mcval.indice=mria;
            break;
            case 3: case 4:         // scorrimento allarmi alto e basso
               r.mcval.indice=mnaa;
               r.mcval.direz=r.mcval.direz-3;
            break;
         }
		   enqueue(&spack);
		   goto LOOP; 	
	      }
/*
	richiesta stampa file ascii
*/
	   if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$SFILE",sl.m.mut.buff.s[0]))
         {
	   	r.sfil.lung=sizeof(S_SFILE);
		   r.sfil.mess=msfile;
         r.sfil.richiesta=-1;          // stampante di default
		   memset(r.sfil.nome,0,l_sfile);
		   strcpy(r.sfil.nome,conf[RTF]);
		   strcat(r.sfil.nome,"\\");
		   strncpy(&r.sfil.nome[strlen(r.sfil.nome)], &sl.m.mut.buff.c[sl.m.mut.buff.s[0]+4],
					 sl.m.mut.buff.s[sl.m.mut.buff.s[0]/2+1]);
		   strcat(r.sfil.nome,RTFEXT);
		   tqueue.lmsg=sizeof(S_SFILE);
		   enqueue(&tqueue);
		   goto LOOP;
	      }						
/*
	funzione di riconoscimento singolo e congelamneto pagina allarmi
*/
	   if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$RAL",sl.m.mut.buff.s[0]))
         {
         rall(sl.m.mut.buff.s[4],sl.m.mut.buff.s[6],sl.m.mut.video-1);
		   goto LOOP; 	
	      }
/*
   riconoscimento allarmi da qualsiasi pagina video
*/
	   if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$RICSIN",sl.m.mut.buff.s[0]))
      {
	      allsric(&sl.m.mut.buff.s[(sl.m.mut.buff.s[0]-1)/2+2], sl.m.mut.video-1,
            sl.m.mut.zona-1);
         goto LOOP;
      }

      if (TABUL)     //richiesta lancio tabulato
         {
	      if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$TAB",sl.m.mut.buff.s[0]))
	         {
			   r.tab.mess=mstab;
			   r.tab.video=sl.m.mut.video ;
			   r.tab.zona=zonaw;
			   memset(r.tab.nome,0,l_tnome);
            pTab=(short*) &sl.m.mut.buff.c[sl.m.mut.buff.s[0]+4];
            lTab=sl.m.mut.buff.s[sl.m.mut.buff.s[0]/2+1];
			   memcpy(r.tab.nome,&sl.m.mut.buff.c[sl.m.mut.buff.s[0]+4],
				            	 sl.m.mut.buff.s[sl.m.mut.buff.s[0]/2+1]);
			   tqueue.lmsg=sizeof(S_STAB);
#if defined (VIRTLBG)
            pTab=pTab+(lTab-1)/2+1;
            if(*pTab==-1) r.tab.richiesta=-1;   // stampante di default
            else
            {
               pTab++;
               r.tab.richiesta=(*pTab)-1;        // stampante specificata
            }
            if(tabFound(r.tab.nome,&sl.m.mut)) goto LOOP;
#endif
            if(bitvalue(&dbdd[lockarc],g2di_asl)) 
               bitset(&dbdd[lockarc],g2di_sl,1);
			   enqueue(&tqueue);
			   goto LOOP;
	         }
         }
      if (ARCHIVI_NV)    //richiesta lancio tabulato da archivi
         {
	      if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$ARC",sl.m.mut.buff.s[0]))
	         {	
			   r.tab.mess=mstabarc;
			   r.tab.video=sl.m.mut.video ;
			   r.tab.zona=zonaw;
			   r.tab.richiesta=r_procv ;
			   r.tab.archivio=(char)(sl.m.mut.buff.s[4]);
			   r.tab.giorno=(unsigned char)(sl.m.mut.buff.s[6]);
			   r.tab.mese=(unsigned char)(sl.m.mut.buff.s[8]);
			   r.tab.anno=sl.m.mut.buff.s[10];
			   r.tab.ore=(unsigned char)sl.m.mut.buff.s[12];
			   r.tab.minuti=(unsigned char)sl.m.mut.buff.s[14];
			   r.tab.secondi=0;
			   r.tab.ncamp=sl.m.mut.buff.s[16];
			   tqueue.lmsg=sizeof(S_STAB);
            if(bitvalue(&dbdd[lockarc],g2di_asl)) 
               bitset(&dbdd[lockarc],g2di_sl,1);
			   enqueue(&tqueue);
			   goto LOOP;
	         }
	      if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$ARCSEC",sl.m.mut.buff.s[0]))
	         {	
			   r.tab.mess=mstabarc;
			   r.tab.video=sl.m.mut.video ;
			   r.tab.zona=zonaw;
			   r.tab.richiesta=r_procv ;
			   r.tab.archivio=(char)(sl.m.mut.buff.s[6]);
			   r.tab.giorno=(unsigned char)(sl.m.mut.buff.s[8]);
			   r.tab.mese=(unsigned char)(sl.m.mut.buff.s[10]);
			   r.tab.anno=sl.m.mut.buff.s[12];
			   r.tab.ore=(unsigned char)sl.m.mut.buff.s[14];
			   r.tab.minuti=(unsigned char)sl.m.mut.buff.s[16];
			   r.tab.secondi=(unsigned char)sl.m.mut.buff.s[18];
			   r.tab.ncamp=sl.m.mut.buff.s[20];
			   tqueue.lmsg=sizeof(S_STAB);
            if(bitvalue(&dbdd[lockarc],g2di_asl)) 
               bitset(&dbdd[lockarc],g2di_sl,1);
			   enqueue(&tqueue);
			   goto LOOP;
	         }
/*
	richiesta trasferimento su dischetto archivio ( e suo descrittore )
*/
         if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$TRC",sl.m.mut.buff.s[0]))
	         {	
		      tqueue.lmsg=arctrc(&sl.m.mut.buff.s[0],&r);
            if(bitvalue(&dbdd[lockarc],g2di_asl)) 
               bitset(&dbdd[lockarc],g2di_sl,1);
		      enqueue(&tqueue);
		      goto LOOP;
	         }
         }
      if (TABUL)   //trasferimento file ricetta FPOLn.VAR su dischetto
         {
	      if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$TFILE",sl.m.mut.buff.s[0]))
	         {	
			   r.tab.mess=mtrasfpol;
			   r.tab.video=sl.m.mut.video ;
			   r.tab.zona=zonaw;
			   r.tab.richiesta=r_procv ;

			   r.tab.archivio=(char)(sl.m.mut.buff.s[5]);// n. del file
			   tqueue.lmsg=sizeof(S_STAB);
			   enqueue(&tqueue);
			   goto LOOP;
	         }
/*
	trasferimento file allarmi ALLARn.RTF su dischetto
	setto il bit FZ di copiato
*/
	      if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$TALL",5))
	         {
			   if(sl.m.mut.buff.s[5]==n_allfile) 
               goto LOOP;  	// file in uso
			   r.tab.archivio=(char)(sl.m.mut.buff.s[5]);		// n. del file
			   if(dbadv[r.tab.archivio+db_falco1-1] == 0.0) 
               goto LOOP;
			   r.tab.mess=mtrasfall;
			   r.tab.video=sl.m.mut.video ;
		   	r.tab.zona=zonaw;
			   r.tab.richiesta=r_procv ;
			   tqueue.lmsg=sizeof(S_STAB);
            if(bitvalue(&dbdd[lockarc],g2di_asl)) 
               bitset(&dbdd[lockarc],g2di_sl,1);
			   enqueue(&tqueue);
			   goto LOOP;
	         }
         }
/*
	stampa allarmi in archivio e da riconoscere
*/
	   if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$STAL",5))
	      {
         stamar(&sl.m.mut.buff.s[4],0);
		   goto LOOP;
	      }
/*
	stampa elenchi punti	 vengono passati il tipo di punto e l'elenco
   con o senza zona specificata
*/
	   if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$ELEN",5))
	      {
		   if(sl.m.mut.buff.s[8]==-1) 
            sl.m.mut.buff.s[9]=-1;
		   gesele(sl.m.mut.buff.s[5],sl.m.mut.buff.s[7],sl.m.mut.buff.s[9]);
		   goto LOOP;
	      }
	   if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$MUTE",5))
	      {
		   CmdBell(0);					// stop cicalino
		   goto LOOP;
	      }
	   if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$CLK",sl.m.mut.buff.s[0]))
	      {
#if defined (SELTA)
         // manda messaggio di cambio data e ora
			mtra.ext=g1tipdd;
			mtra.stato=1;
			mtra.mess=macdd;
			mtra.indice=oldsysdate;
         enqueue(&dqueue);
#endif
		   r.timet.hour=sl.m.mut.buff.s[8];
		   r.timet.minute=sl.m.mut.buff.s[6];
		   r.timet.second=sl.m.mut.buff.s[4];
		   r.timet.hsecond=0;
		   _dos_settime(&r.timet);
		   r.datet.day=sl.m.mut.buff.s[10];
		   r.datet.month=sl.m.mut.buff.s[12];
		   r.datet.year=sl.m.mut.buff.s[14];
		   r.datet.dayofweek=0;
		   _dos_setdate(&r.datet);
		   leggi_data=1;									// forzo flag di data variata
															// pscswd deve rileggere la data
#if defined (SELTA)
         // aspetta che sistema legga nuova data
         wai(40);
         // manda messaggio di nuova data e ora
			mtra.indice=newsysdate;
         enqueue(&dqueue);
#if defined (AC_SAMP)
            periodo_ora_samp=100;      // forzo invio ora a front end
#endif
#endif
         goto LOOP;               
         }
//
// interpretazione messaggio per registratori: utente AEM
//
#if defined (AEM)
      	if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$REG",sl.m.mut.buff.s[0]))
	      {	
            aemsend(&sl.m.mut.buff.s[3]);
		      goto LOOP;
         }
#endif
#if defined (VIRTLBG)
	   if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$VIRT",sl.m.mut.buff.s[0]))
         {
		      virtsel(&sl.m.mut.buff.s[sl.m.mut.buff.s[0]/2+1]);
            goto LOOP;
         }
#endif
      if(sl.m.mut.buff.s[0] >0 && ! strncmp(&sl.m.mut.buff.c[2],"$ISA",sl.m.mut.buff.s[0]))
         {	
             isainv(&sl.m.mut.buff.s[0],pack.lmsg-l_hea_msen);     // messaggio da interpretare
			   goto LOOP;
         }
      break;
   case STATUS_R:
      break;
   case STATOPORTA:
      ier=diagnet(stvide1,&sl.m,&video);
		if(ier<0) 
         break;
      varstvid[video]=1;  // segnala una variazione dello stato del video
      ptv= &tstv[video].tsv[0]  ;
      switch(ier)
         {  
     	   case 1:                     // caduta comunicazione
            for(i=0;i<n_zone;i++,ptv++)  // cancello pagine visualizzate da tabella SCADA
               {
//				   memset(&ptv->v_pagina[0],0,10);
      	      ptv->v_tipo=0 ;
               ptv->v_input=0;
               }
            hcwin (op_hc_off, video+1, 0);   // reset hardcopy
#if defined (VIRTLBG)
            CloseTrFile(video);              // reset trasmissione file
#endif
            break;
         case 0:
			   if(sys_master)			// se master segnalo al driver MMI
			      {
			      hpack.lmsg=sizeof(S_MMASTER);
				   r.mst.indice=MMASTER;
				   r.mst.classe=0;
				   r.mst.nodo=video;
				   enqueue(&hpack);
#if defined (WINMMI)
               tstv[video].tsv[zonai].v_pagina[0]=0;  // forzo
				   for(k=0;k<n_zone_matrox-1;k++,ptv++)  // cancellazione della sola pagina Allarmi
#else
				   for(k=0;k<n_zone_matrox;k++,ptv++)
#endif
				      {
					   if(ptv->v_pagina[0])
				         {
						   if(!strcmp(ptv->v_pagina,"$ALLARMI"))		 // caso pagina allarmi
						      {
							   r.mcval.video=video;
							   r.mcval.direz=0 ;
							   r.mcval.zona=zonai ;
							   r.mcval.indice=mpal;
							   enqueue(&spack);
						      }
					      else															// caso pagina generica
						      {
						      r.pag.zona=k+1;
						      r.pag.video=video+1;
						      r.pag.nodo=video;
						      memset(r.pag.elen,-1,10);
						      memcpy(r.pag.page,ptv->v_pagina,10);
						   	r.pag.input=inp_db;
						      r.pag.indice=vpagv;
						      hpack.lmsg=sizeof(S_VPAGV);
						      enqueue(&hpack);
						      }
					      }
					   else
					      {
							hpack.lmsg=sizeof(S_PALO); // ed aggiorno stringhe allarmi
							r.cle.indice=vclrv;
							r.cle.video=video+1;
							r.cle.nodo=video;
							r.cle.zona=k+1;
							enqueue(&hpack);
					      }
				      }
			      }
            for (i=0;i<max_dbsall;i++)			// aggiornamento scritta allarmi
               {
               if (bDbsAll[i].def)
                  {
                  bDbsAll[i].fchanga=1;
                  r.mcval.indice=mall;
                  enqueue(&spack);
                  }
               }
            break;
         }
      goto LOOP ;
   case mhcp:           // messaggio hardcopy MMI Win vedi thcwin.c
       hcqueue.lmsg=pack.lmsg;
       enqueue(&hcqueue);
   break;
   case mrdbl:
   case mwdbl:
       mmidbl(&sl.m);
   break;
   case mackfile:
   case mricfile:
   case minvfile:
#if defined (VIRTLBG)
      trfile(&sl.m);
#endif
   break;
   default:
      pscserr(ERR_TASK,TASK_SCGEV,ROU_SCGEV,sl.m.pag.indice,SYS_CONT);
	   goto LOOP;
   }
   goto LOOP ;
}


/**********************************************************************
*
*       C Header:               mesprocv.inc
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Thu Jul  1 17:19:32 2004 %
*
**********************************************************************/
/*
	il file di include messprocv.inc contiene le
	strutture dei messaggi utilizzati dai task
	che gestiscono gli allarmi e che comunicano con
	il micro operatore
	call gevid cval gdac

        9 Giugno 1995
        Ampliato il messaggio S_PAV da 256 a 384 punti nel descrittore
        della pagina
*/
#include <all_1.h>
#include "tag.h"
#define  l_pagina 10
#define  l_elenco 10
#define  KKSCODE     "@#K@"
#define  SEPARATORCODE     '|'
/*
	struttura per definire l' header dei messaggi
	fra HOST <--> STOP
*/
typedef struct head_m { 
                        short nodo;
                        char indice ;
		 	char classe;
		 	char zona ;
		 	char video ;
		 	short info[6];
			} HEAD_M ;
#define l_headm  sizeof(HEAD_M)
/*
	struttura messaggio di reset dei dizionari
	Host-->Stop in seguito all' arrivo a Host di un
	messaggio Reset Dizionari da Config
*/
#define  vreset 42
typedef struct v_resd {	
			HEAD_M h ;
		      } V_RESD;

/*
	messaggio di aggiornamento dei descrittori delle pagine
	video da Host-->Stop
	VPAGE
*/
#define vpages 40
typedef struct v_page {	
			HEAD_M h ;
			short ind_file;
			short ind_bloc;
			char  bl_disc[512];
		      } V_PAGE ;

#define mall 1          /* arrivati nuovi allarmi */

#define mpal 2           /* visualizzare pagina allarmi */
#define mhal 3  	/* home pagina allarmi 		*/
#define mnaa 4		/* movimento in archivio	*/
#define mria 5		/* riconoscimento allarmi	*/
#define magp 6          /* aggiornare stringhe allarmi sui video     */
                        /* (per mmi remota all'aggancio)             */
#define mriv 7          // rivisualizzazione pagina allarmi dopo ric. singolo
#define mpal1 8         /* visualizzazione pagina allarmi senza variare zona */
#define mpalminiASD  9  /* richiesta all miniASD                 */
#define mricsminiASD  10  /* riconoscimento singolo miniASD       */
/*
	la struttura S_PALI viene utilizzata per i messaggi
	mpal mhal e mnaa provenienti da micro operatore
*/
typedef struct s_pali { 
                        short nodo ;
			char  indice;	
                        char  classe;
		   	char zona ;
		   	char video  ;
		   	char pagina[l_pagina]  ;
			short direz;	
				 } S_PALI ;
/*
	la struttura S_PALO viene utilizzata per i messaggi
	verso il micro vclear e vfxal
*/
#define vclrv 16	/* clear video			*/
#define vfxal 60	/* visualizzazione parte fissa  */
typedef struct s_palo { 
                        short nodo ;
		   	char indice ;
		   	char classe  ;
		   	char zona   ;
		   	char video  ;
	           	short funzione[5] ;
			 } S_PALO ;
/*
	tipi di input su video operatore
*/
#define inp_dir 4      /* input diretto */
#define inp_ar    2    /* input da archivio */
#define inp_db  1      /* input da db   */
#define inp_ut  3      /* input da utente */
/*
	tipi messaggi da micro operatore
*/
#define mclr   16      /* richiesta clear zona video */
#define mpav   17     /* descrittori nuova pagina */
#define msen   18     /* messaggio per utente  */


#define lmax_descr 640        /* n. max words per descrittore */
typedef union dbs_l {  short s[lmax_descr*3];
			S_PUNT p[lmax_descr*3/2]; } DBS_L;
typedef struct s_mpav { 
                        short nodo;
			char indice ;
			char classe ;
			char zona ;
			char video ;
			char nome[l_pagina];   /* nome pagina */
			short spare1 ;
			short tin    ;   /* tipo inp o direz $pal */
			short num_punti; /* numero punti in D.B.S.  */
			char  tipo;     /* tipo di pagina */
			char  spare2;
			short spare3;
			char  per_sca;   /* formato spare	  */
			char  formato ; /* periodo scansione     */
			DBS_L d ;
		      } S_PAV;
/*
	struttura stringa di allarme
*/
struct ppnt { char tipo ;
	      char ext  ;
	     short point ;} ;
typedef struct string_all {    
                                short lun;
#if defined OSF1 || defined LINUX
				int  spare; 
#else
				long  spare; 
#endif
			 	short pont    ;
			   	S_PUNT  p  ;
				char  colorast ;
				char  aster ;
				short zero ;
				char  colorstr ;
				char  data[9] ;
				char  desc[28+SCD_SIGLA+SCD_DESCRIZIONE_ALL];
				char hierarchy[n_gerarchie];
				char emission;
				} S_STRALL ;
/*
	struttura messaggio vdeal aggiornamento parte
	variabile $pal
*/
/*
Struttura che tiene conto del numero di allarmi per ciascuna zona
di impianto. Fatta su misura per messaggistica SCADA pagina allarmi mmi.
Introdotta da Fabio 6/97.
*/
typedef struct s_all_x_zone{
                        short n_all_pen[32];   /* allarmi pendenti per ogn
i zona*/
                        short n_all_arc[32];   /* allarmi riconosciuti " "
   " */
                        } S_ALL_X_ZONE;
/*
	definizione messaggi aggiornamenti parziali o totali
	pagina allarmi
*/
#define vpaal 52
#define vdeal 50
typedef struct svdeal {  
                         short nodo;
                         char  indice;
                         char  classe;
	       		 char zona  ;
	       		 char video ;
	      		 char  pag[l_pagina] ;
			 short spare ;	
	    	  	 short n_pagina ;	 /*	n. pagina allarmi     */
		     	 short n_archivio ;	 /*     n. archivio corrente  */
			 short n_pall;		 /* n. allarmi da riconoscere */
			 short n_parch;		 /* n. allarmi in archivio    */
			 short n_all;		 /* n. allarmi nel mess.      */	
			 short n_arch;		 /* puntat. allarme archvio   */
			 short funzione;	 /* tipo funzione  0 1 2      */		
			 short cicalino;         /* =1 emettere suono	      */
                         S_ALL_X_ZONE zone_all;
                         S_STRALL stringall[16] ;
			} S_VDEAL ;
/*
Definizioni stati degli allarmi
*/
#define EMISSIONE 	1
#define RIENTRO		0
#define RICONOSCIUTO	2

/*
	messaggi valori per aggiornamento pagine video ed invio
	ora utilizzati in gdac
*/
#define vdasi 34
typedef struct s_vdasi{  
                         short nodo;
		      	 char  indice ;
	      	 	 char  classe  ;
	     		 char  zona   ;
	       		 char  video  ;
	      		 char  pag[l_pagina] ;
             		 short spare1  ;
			 short num_dati;
              		 char  dati[5120];} S_VDASI ;
#define vtime 70
typedef struct s_time {  
                         short nodo;
		      	 char  indice ;
	      	 	 char  classe  ;
	     		 char  zona   ;
	       		 char  video  ;
#if defined OSF1 || defined LINUX
			 short cicalino;
	      		 short spare1[5] ;
#else
	      		 short spare1[6] ;
#endif
             		 short anno    ;
              		 short mese   ;
			 short giorno ;
			 short ore ;
			 short minuti ;
			 short secondi ;} S_VTIME ;
/*
	messaggio di diagnostica micro operatore
*/
#define mdia 9
#define max_dia 16		// al massimo 16 segnalazioni

typedef struct s_aldia  { 
			unsigned short allarme:15;
			unsigned short condiz:1;	 // =0 rientro 1 emissione 
			} S_ALDIA;

typedef struct  s_mdia {
                        short nodo;
			char indice	;
			char classe	;
			S_ALDIA a[max_dia] ;} S_MDIA ;

typedef struct  s_mdia_r {				// struttura per un solo allarme
                        short nodo;
			char indice	;
			char classe	;
			S_ALDIA a	;} S_MDIA_R ;

#define  h_dia (sizeof(S_MDIA)-(sizeof(S_ALDIA)*max_dia))		
/*
        definizione messaggio richiesta stampa da terminali 
*/
#define mterm  10
typedef struct  s_term {
                        short nodo;
			char indice	;
			char classe	;
			char zona	;
			char video	;
			short spare3[6] ;
                        short carattere ;
			short linea;
			} S_TERM;

/*
	definizione messaggio per utente o EXEC KILL o variazione
	archivio allarmi (@ALL ) o stampa allarmi in archivio
	(@STP)
*/
#define lu_us 4		/* lunghezza nome user */
#define lu_me 12	/* lunghezza messaggio */
#define of_fu  1        /* offset nell'user name in cui c'e' la */
			/* funzione da eseguire			*/
#define msen 18

typedef union u_vsfi {  char c[512];
			short s[256];
			float f[128];
		     }  U_VSFI ;

typedef struct s_msen {
                        short nodo;
			char indice	;
		        char classe	;
			char zona	;
			char video	;
			char pag[l_pagina]    ;
			short spare1    ;
#if defined OSF1_40  || defined LINUX
			short spare2    ;
#endif
		        U_VSFI buff     ;
		       } S_MSEN ;


#define l_hea_msen (sizeof(S_MSEN)-sizeof(U_VSFI))
/*	
	messaggio di richiesta visualizzazione pagina
	al micro
*/
#define vpagv  4
typedef struct s_vpagv  {
                         short nodo;
			 char  indice;
			 char classe ;
			 char  zona;
			 char  video;
			 char  page[l_pagina];
			 short spare1;
			 char  elen[l_elenco];
			 short input; }  S_VPAGV ;
/*
	definizione messaggio richiesta descrizione punto
	e messaggio di risposta
*/
#define mrdp 19		/* richiesta descrizione	*/
#define mrdpwin 20	/* richiesta descrizione per MMI Win */
#define vdesp 64	/* messaggio di risposta	*/
typedef struct s_mrdp   {
                         short nodo;
			 char  indice ;
			 char  classe;
			 char  zona  ;
			 char  video ;
			 char  pag[l_pagina] ;
			 short spare1;
			 short punto[SCD_SIGLA/2];
			 short tipo; } S_MRDP ;
#define lu_de 80	/* lunghezza descrizione */
#define lu_mi 8         /* lunghezza unita' mis. */
typedef struct s_vdespa {
                         short nodo;
			 char  indice ;
			 char  classe ;
			 char  zona ;
			 char video ;
			 char  pag[l_pagina];
			 short spare1;
			 short tipo ;   /* indice pagina */
			 short ext;  /*puntatore */
			 short punt ;   
			 char desc[lu_de];
	               } S_VDESPA ;

typedef struct s_mrdpwin   {
                         short nodo;
			 char  indice ;
			 char  classe ;
                   	 char  zona  ;
			 char  video ;
			 char  pag[l_pagina] ;
			 short spare1;
			 short punto[SCD_SIGLA/2];         					// nome del punto 
			 short tipo;								   // tipo del punto oppure -1 se non noto
			 short dblpunt;							   // puntatore locale variabile puntatore
			 short dbltipo;								// puntatore locale tipo punto
			 short dbltag;							    // puntatore locale tag
			 short dbldesc;							  // puntatore locale desc
			 short dblunita;							  //  puntatore locale unmis
			 short dblstat;								//  puntatore locale stato
			   } S_MRDPWIN ;
			   
#define winlu_mi 10         		// lunghezza unita' di misura o tipo di organo o stata 0 per digitale
#define winlu_st   8				  // lunghezza stato 1 per digitale
typedef struct s_vdespawin {
                         short nodo;
			 char  indice ;
			 char  classe ;
                         char  zona ;
			 char video ;
			 char  pag[l_pagina];
			 short spare1;
			 short tipo ;   								// tipo di punto
			 short ext; 									// estensione punto in dbs
			 short punt ;   							  // indice in data base sistema
			 char  nome[SCD_SIGLA];  
			 char desc[SCD_DESCRIZIONE];
			 char unmis[winlu_mi];
			 char stato[winlu_st];
			 short dblpunt;							   // puntatore locale variabile puntatore
			 short dbltipo;								// puntatore locale tipo punto
			 short dbltag;							    // puntatore locale tag
			 short dbldesc;							  // puntatore locale desc
			 short dblunita;							    //  puntatore locale unmis
			 short dblstat;								//  puntatore locale stato
	               } S_VDESPAWIN ;
/*
	mcsp: messaggio modifica punto, vstat: messaggio di risposta
        mcspext: messaggio per rwrite (funzione di lock), vstatext messaggio di risposta
*/
#define mcsp 8
#define mcspext 11 
typedef union u_dati   { char  c[g0lunst] ;
			 float f     ;
			 short s[5] ; } U_DATI ;
typedef struct s_mcsp   {
                         short nodo;
		         char  indice ;
			 char  classe ;
			 char  zona  ;
			 char  video;
			 char  pag[l_pagina];
			 short dbl;                 // solo per mcspext indica indice in dbl
			 short point[SCD_SIGLA/2] ;
			 short funz ;
			 short tipo ;
			U_DATI dat ; } S_MCSP ;
/*
	Definizione wildchar utilizzato per le funzioni di
        modifica punto
*/
#define WILDCHAR '?'

#define vstat 62
#define vstatext 63                     // risposta a messaggio mcspext
typedef union u_valf    { char c[g0lunst] ;
			  short s[3] ;
			  float f ; } U_VALF ;

typedef struct s_vstat { 
                         short nodo;
			 char indice ;
			 char classe ;
			 char zona ;
			 char video ;
			 char pag[l_pagina];
			 short dbl;
			 short tip_pun ;
			 short ext ;
			 short punt ;
			U_VALF val ; } S_VSTAT ;
/*
	definizione labels utilizzate in modpun.c
*/
#define m_tipud    -2
#define m_nondef   -1
#define m_analogico 1
#define m_digitale  2
#define m_organo    3
#define m_reale	    4
#define m_integ	    5
#define m_bool 	    6
#define m_dout 	    7
#define m_stringa   8
#define m_orsch     9

#define m_anls	   19		// bassa sicurezza
#define m_anlc	   20		// bassa conduzione
#define m_anhc	   21		// alta  conduzione
#define m_anhs	   22		// alta  sicurezza

/*
	definizione codici di errore utilizzati in modpun.c
*/
#define  erres   1	/*punto non esistente 		*/
#define  errtip  2	/*tipo diverso 			*/
#define  errst   3	/*stato in chiaro non esistente	*/
#define  errfs   4	/*punto gia' fuori scansione	*/
#define  errin   5	/*punto gia' in  scansione	*/
#define  errso   6	/*soglia non corretta 		*/
#define  oktab   7	/*tabulato in stampa 		*/
#define  errtab  8	/*tabulato errato 		*/

#define  old_lun  8	/*vecchia lunghezza sigle */
#define  new_lun 10	/*nuova   lunghezza sigle */

/*
	definizione labels per le funzioni possibili
	da operatore
*/
#define  f_none  0
#define  f_mvaf  1
#define  f_mval  2
#define  f_mfla  3
#define  f_forz  4
#define  f_fsca  5
#define  f_isca  6

/*
	definizione messaggio lancio tabulato
*/
#define mtab 15
typedef struct s_mtab	{ 
			  short  mess ;
			  char   video ;
			  char   zona ;
			  short  spare[3] ;
			  char   nome[8] ;/*!!! sara' 10 */
			  short  tip_dat ;
			  short  tip_arch ; } S_MTAB ;

/*
	definizione messaggio VDIA
	diagnostica sistema host
*/
#define vdia 48
typedef struct s_vdia {	
                        short nodo;
			char  indice;
			char  classe;
			char  video ;
			char  zona  ;
			char  spare1[12];
			short condiz;
			short ind_all;
		      } S_VDIA;
/*
	definizione messaggio S_VOUUT_CONFIG (del tipo VOUUT)
        utilizzato per invio a MMI di una stringa di 20 caratteri
*/
#define vouut 66
typedef struct s_vouut { 
                         short nodo;
			 char  indice;
			 char  classe;
			 char  zona ;
			 char  video ;
			 char  spare1[12];
                         char x;
                         char y;
                         char colore;
                         char zoom ;
                         short lungh;
                         char  buff[20];
			} S_VOUUT_CONFIG;

typedef struct s_vouut_vga { 
                         short nodo;
			 char  indice;
			 char  classe;
			 char  zona ;
			 char  video ;
			 char  spare1[12];
                         char x;
                         char y;
                         char colore;
                         char zoom ;
                         short lungh;
                         char  buff[50];
			} S_VOUUT_VGA;

/*
	Richiesta aggiornamento grafico.
	STOP  -----> HOST
*/

#define  maggr 21
#define  maggrwin  22
#define  max_curve 4
#define  l_crit  22     // lunghezza in bytes del criterio di estrazione

typedef struct mis_crit {
			 char mis[SCD_SIGLA];
			 char crit[l_crit];
			} MIS_CRIT;

typedef struct s_maggr {
                        short nodo;
			HEAD_M h;    // header
                        char quadr;  // quadrante 
			char n_mis;  // num. misure 
			char estr;   // criterio di estrazione
			char rappr;  // tipo di rappresentazione
			MIS_CRIT mc[max_curve];   // descrizione misure da
						// rappresentare e loro criterio
						// di estrazione.
		       } S_MAGGR;

/*
	Invio parametri per grafico.
	HOST -------> STOP
*/
#define vprgr 54
#define lu_descr 24
typedef struct mis_des { char umis[lu_mi];
			 char descr[lu_descr];} MIS_DES;

typedef struct s_vprgr {
			HEAD_M h;
                        char quadr;      // quadrante 
                        char n_mis;      // numero misure inviate
			float t_iniz;    // tempo iniziale
			float t_fin;     // tempo finale
			short giorno;  	 // giorno inizio estrazione
			short mese;      // mese inizio estrazione
			short anno;      // anno inizio estrazione
			MIS_DES md[max_curve]; // unit… di misura e descrizione
					       // dei punti richiesti
		       } S_VPRGR;

/*
	Invio dati storici vettoriali per grafico
        HOST -------> STOP
*/
#define  vdsgrack  23   // consenso all'invio del prossimo messaggio di dati
#define vdsgr  46
#define l_bcamp 1024  // lunghezza buffer campioni
		      // dimensionato per 64 analogici
#define num_bcamp (l_bcamp/4)   // numero massimo di campioni
				// inviabili.
typedef struct inf_mis {
		       unsigned short cont_camp:13;   // numero di campioni
				         	     // presenti nel messaggio
		       unsigned short t:2;
		       unsigned short v:1;
		       } INF_MIS;
typedef union bcamp {
		    float f[num_bcamp];
		    short s[num_bcamp*2];
		    } BCAMP;
typedef struct s_vdsgr {
			HEAD_M h;
                        char quadr;   // quadrante 
			char i_cur;   // indice della curva di cui si inviano i campioni
			INF_MIS infmis; // informazioni relative a tipo,numero,e
				        // visualizzazione della misura.
			float t_primo;   // tempo primo campione
			float t_ultimo;  // tempo ultimo campione 
			BCAMP b;
			}S_VDSGR;

#define lun_vdsgr sizeof(S_VDSGR)
#define lpa_vdsgr (lun_vdsgr-sizeof(BCAMP))

/*
	Richiesta read blocco su file
        MMI ------> HOST 
*/
#define MAXFILESCADA 100
#define WRITEDATA  30
#define READDATA   31
#define DELETEFILE 32

#define FWriteW  97				// caso MMI Window
#define FReadW   98
#define FDeleteW 99

#ifndef LRECFIO
#include <all_16.h>
#include "fio.h"
#include <all_1.h>
#endif
	
typedef struct {
               short nodo;
	       char  indice ;
	       char  classe ;
	       char  zona  ;
	       char  video;
	       char  pag[l_pagina];
	       short   idfile;
	       short   recno;
	       char  b[LRECFIO];	 } BRICFIO;

#define LBRIC (sizeof(BRICFIO) - LRECFIO)

#define STOPMMI	    101			// stop sistema MMI (utilizza pacchetto S_MMASTER)

#define RWRITEDATA  90
#define RREADDATA   91
#define RDELETEFILE 92

typedef struct s_mmaster {
		short nodo;
		char  indice;
		char  classe;
			} S_MMASTER;

//
//		Messggi utilizzati per gestione hardcopy MMI Win
//
#define mhcp	80		        // richiesta stampa  e relativa risposta
#define MAX_DATIHCPY	512		// n. massimo byte inviati per hardcopy
#define max_hcpy_video  7               // n. massimo hardcopy per video

typedef struct s_ihcpy {				// struttura invio hardcopy
        		short nodo;
	        	char  indice;
		        char  classe;
                        short video;
			short  nhcpy;	 //  n. hardcopy da effettuare
			short nbyte;	 //  n. byte inviati
                        short bLast;      // =1 ultimo messaggio
			char  dati[MAX_DATIHCPY] ;
				} S_IHCPY;  

typedef struct	s_rhcpy	{			 // struttura riposta a messaggio di invio hardcopy
        		short nodo;
	        	char  indice;
		        char  classe;
			short	nhcpy;		// n. hardcpy richiesta
                        short   bFirst;         // primo messaggio ?
				} S_RHCPY;	
//
//      definizioni operazioni possibili per la gestione dell'hardcopy
//
#define op_hc_new       1       // nuova hardcopy
#define op_hc_cont      2       // messaggio intermedio
#define op_hc_off       3       // caduta comunicazione
#define op_hc_end       4       // fine hardcopy in corso
//
//      indici messaggi richiesta lettura o scrittura 
//      nel data base del posto operatore indicato
//      La risposta ha lo stessa indice e struttura
//
#define mrdbl    81     // lettura
#define mwdbl    82     // scrittura
#define max_dbl_dati    80
typedef struct s_mdbl {
                         short nodo;
			 char  indice ;
			 char  classe ;
                   	 char  zona  ;
			 char  video ;
			 char  pag[l_pagina] ;
			 short dblpunt;	   // puntatore locale variabile puntatore
                         char  npostop;    // n. del posto operatore a partire da 1
                         char  idbl;       // indice del data base da utilizzare
                         short iele;      // indice elemento
                         short dim;        // n. byte da trasferire
                         char  dati[max_dbl_dati]; // buffer per trasferimento dati
			   } S_MMIDBL ;

// messaggio per la visualizzazione dei tabulati installati

#define mtabinst 83
typedef struct s_tabinst{
                         short nodo;
			 char  indice ;
			 char  classe ;
                         char  zona  ;
			 char  video ;
			 char  pag[l_pagina] ;
			 S_DIZTAB tabulato[n_tabu];
 		   	}S_TABINST;

// messaggio per l'invio di un file a MMI

#define mricfile  37              // richiesta file (il nome e' terminato con NULL)
#define dim_invfile   1024      // dimensione blocco dati da inviare
#define dim_chfile     100      // n. massimo caratteri nome file
typedef struct s_richfile{
                         short nodo;
			 char  indice ;
			 char  classe ;
                         char  zona  ;
			 char  video ;
			 char  pag[l_pagina] ;
                         short nObj;     // n. oggetto
			 char  nfile[dim_chfile];
 		   	}S_RICHFILE;

#define minvfile 38              // invio file
typedef struct s_invfile{
                         short nodo;
			 char  indice ;
			 char  classe ;
                         char  zona  ;
			 char  video ;
			 char  pag[l_pagina] ;
                         short nObj;     // n. oggetto
			 char  bInizio;         // flag primo blocco
			 char  bLast;           // flag ultimo blocco
                         short nByte;           // n. byte inviati
                         char  buff[dim_invfile];
 		   	}S_INVFILE;

#define mackfile  39      // ack da mmi richiesta nuovo blocco
typedef struct s_ack_file {
                        short nodo;
			char  indice ;
			char  classe ;
                        char  zona  ;
        		char  video ;
			char  pag[l_pagina] ;
                        short nObj;     // n. oggetto
                        short bStop;     // =1 stop trasmissione
                        short bInit;     // =1 primo messaggio (utilizzato da SCADA verso MMI)
                          } S_ACKFILE;
#include <all_16.h>

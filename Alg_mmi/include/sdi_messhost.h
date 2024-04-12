/**********************************************************************
*
*       C Header:               sdi_messhost.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Oct  9 12:04:11 1998 %
*
**********************************************************************/
/**/
/*	File di include messhost.h*/
/*	*/
/*	Contiene le strutture dei messaggi da e per hosts*/
/**/
#define  l_pagina 10
#define  l_elenco 10
/**/
/*	struttura per definire l'header dei messaggi*/
/**/
typedef struct s_heahost { 
                        short nodo;
                        char indice ;		/* codice messaggio*/
					 	char classe;
					  } S_HEAHOST;	
/**/
/*	invio tempo e data  */
/**/
#define vtime 70
typedef struct s_vtime {  
                 S_HEAHOST hea;
	     		 char  zona   ;
	       		 char  video  ;
	      		 short spare1[6] ;
             	 short anno    ;
              	 short mese   ;
			 	 short giorno ;
			 	 short ore ;
			 	 short minuti ;
			 	 short secondi ;
			 	 } S_VTIME ;					  
		 	 
/**/
/*	sistema host master*/
/**/
#define hostmaster	100
/**/
/*	diagnostica comunicazione*/
/**/
#define hostcom		  90		
typedef struct s_hostcom {  
                 S_HEAHOST hea;
	     		 short     com;	 	 
	     		 } S_HOSTCOM;
/**/
/*		descrittore pagina con variabili link associate*/
/*	     		 */
#define mpav   17 	     		 
#define max_link 640
/**/
/*	tipi di input associabili ad una pagina*/
/**/

#define inp_db  1      /* input da data base di sistema   */
#define inp_ar  2      /* input da archivio */
#define inp_ut  3      /* input da utente   */
#define inp_dir 4      /* input diretto */

typedef struct s_pdbd_{
		char tipo;
		char ext;
		short indice;
		} S_PDBS;

typedef struct s_mpav { 
            S_HEAHOST hea;
			char zona ;
			char video ;
			char nome[l_pagina];   		/* nome pagina*/
			short spare1 ;
			short tin    ;   			/* tipo input*/
			short num_punti; 			/* numero punti in D.B.S. */
			char  tipo;   				/* tipo di pagina sinottico, trend o pagina allarmi*/
			char  spare2;
			short spare3;
			char  per_sca;   			/* periodo scansione*/
			char  formato ;				/* formato (non significativo)*/
			S_PDBS point[max_link];
		      } S_PAV;
/*                                                        */
/*	dati per aggiornamento pagine video*/
/**/
#define vdasi 34
typedef struct s_vdasi{  
					S_HEAHOST hea;
					 char  zona   ;
	       			 char  video  ;
	      		 	 char  pag[l_pagina] ;
             		 short spare1  ;
			 		 short num_byte;
              		 char  dati[5120];
              		 }  S_VDASI ;
/**/
/*	definizione messaggi aggiornamenti parziali o totali*/
/*	pagina allarmi*/
/**/
#define vpaal 52			/* aggiornamento parziale*/
#define vdeal 50			/* aggiornamento totale*/

#define	all_data	9		/* n. byte data*/
/*
Modificato per Teleperm 
by Fabio
*/
/*
#define all_desc	108	
*/
#define all_desc	120		/* n. byte descrizione*/
#define n_all_str	16		/* n. stringhe allarme*/
#define n_gerarchie	6		/* n. di livelli gerarchia*/
#define max_zone        32              /* n. massimo zone di impianto */
#define dim_emission 	1		/* dim emissione (1 char) */

typedef struct string_all {    	/* struttura stringa allarmi*/
                short lun;
/* il campo seguente era un long */
				int  spare;
			 	short pont;
			   	S_PDBS p;
				char  colorast ;
				char  aster;
				short zero;
				char  colorstr ;
				char  data[all_data];
				char  desc[all_desc];
				char hierarchy[n_gerarchie];
				char emission;
				} S_STRALL;
typedef struct s_all_per_zone{
                        short n_all_pen[max_zone];   /* allarmi pendenti per ogn
i zona*/
                        short n_all_arc[max_zone];   /* allarmi riconosciuti " "
   " */
                        } S_ALL_PER_ZONE;

				
typedef struct svdeal {  
					S_HEAHOST hea;
                    char zona  ;
	       		 	char video ;
	      		 	char  pag[l_pagina] ;
			 		short spare ;	
	    	  	 	short n_dataBase ;	 /*	n. data base associato alla pagina allarmi*/
		     	 	short n_codice ;	 /* n. codice identificativo della pagina allarmi*/
			 		short n_pall;		 /* n. allarmi da riconoscere*/
			 		short n_parch;		 /* n. allarmi in archivio*/
			 		short n_all;		 /* n. allarmi nel mess.*/
			 		short n_arch;		 /* puntat. allarme archvio*/
			 		short funzione;	 	 /* tipo funzione  0 1 2 3*/
			 		short cicalino;      /* =1 emettere suono*/
					S_ALL_PER_ZONE zone_all;
                    			S_STRALL stringall[n_all_str] ;
                      } S_VDEAL ;
/**/
/*	messaggio di richiesta visualizzazione pagina*/
/**/
#define vpagv  4
typedef struct s_vpagv  {
						 S_HEAHOST hea;
						 char  zona;
						 char  video;
						 char  page[l_pagina];
						 short spare1;
						 char  elen[l_elenco];
						 short input; }  S_VPAGV ;
						 
/**/
/*	la struttura S_VCLRV viene utilizzata per i messaggi*/
/*	vclear*/
/**/
#define vclrv 16	/* clear video*/
typedef struct s_vclrv { 
						S_HEAHOST hea;
					   	char zona   ;
					   	char video  ;
			           	short funzione[5] ;
			          } S_VCLRV ;
/**/
/*	la struttura S_PALI viene utilizzata per i messaggi*/
/*	mpal mhal e mnaa provenienti da micro operatore*/
/**/
			          
#define mall 1      /* arrivati nuovi allarmi*/
#define mpal 2      /* visualizzare pagina allarmi*/
#define mhal 3  	/* home pagina allarmi*/
#define mnaa 4		/* movimento in archivio*/
#define mria 5		/* riconoscimento allarmi*/
#define magp 6      /* aggiornare stringhe allarmi sui video (per mmi remota all'aggancio)*/
#define mriv 7      /* aggiornamento file dopo riconoscimento singolo*/
#define mpal1 8     /* visualizzazione pagina allarmi senza variare zona*/
typedef struct s_pali { 
						S_HEAHOST hea;
						char zona;
		   				char video;
		   				char pagina[l_pagina];
						short direz;				/* direzione di scroll	*/
				 	   } S_PALI ;

/**/
/*		Messaggio msen:	invia comunicazione a scada da mmi attraverso*/
/*		l'istruzione SEND*/
/**/
#define msen 18 
#define msen_stringa	1	/* stringa	 tipi lato mmi*/
#define msen_intero		2	/* intero	*/
#define msen_reale		3	/* analogico e reale*/
#define msen_punt		4	/* qualsiasi tipo di puntatore */
#define msen_digitale	5   /* digitale e logico*/

#define ssen_intero		-2	/* intero	tipi lato scada*/
#define ssen_float		-3	/* float	*/
#define ssen_punt		-4	/* puntatore  */
#define ssen_digitale	-5  /* digitale*/

typedef union u_vsfi {  
			char c[512];
			short s[256];
			     }  U_VSFI ;
			     
typedef struct s_msen {
            S_HEAHOST  hea;
			char zona;
			char video;
			char pag[l_pagina];
			short spare;
		    U_VSFI buff;
		       } S_MSEN ;
/**/
/*		messagio modifica stato punto e risposta*/
/*	*/
/**/
#define  erres   1	/*punto non esistente 		*/
#define  errtip  2	/*tipo diverso 			*/
#define  errst   3	/*stato in chiaro non esistente	*/
#define  errfs   4	/*punto gia' fuori scansione	*/
#define  errin   5	/*punto gia' in  scansione	*/
#define  errso   6	/*soglia non corretta 		*/

#define w_analogico 0			/* tipi di punti in modifica codice POL istruzione WRITE*/
#define w_digitale  2
#define w_organo    1
#define w_dout 	    7
#define w_stringa   8
#define w_anls	   19		/* bassa sicurezza*/
#define w_anlc	   20		/* bassa conduzione*/
#define w_anhc	   21		/* alta  conduzione*/
#define w_anhs	   22		/* alta  sicurezza*/

#define m_analogico 1			/* tipi di punti in modifica  codici messagio per SCADA */
#define m_digitale  2
#define m_organo    3
#define m_reale	    4
#define m_integ	    5
#define m_bool 	    6
#define m_dout 	    7
#define m_stringa   8
#define m_orsch     9
#define m_anls	   19		/* bassa sicurezza*/
#define m_anlc	   20		/* bassa conduzione*/
#define m_anhc	   21		/* alta  conduzione*/
#define m_anhs	   22		/* alta  sicurezza*/

#define  f_none  0			/* tipi di funzioni possibili*/
#define  f_mvaf  1
#define  f_mval  2
#define  f_mfla  3
#define  f_forz  4
#define  f_fsca  5
#define  f_isca  6

#define mcsp 8
typedef union u_dati {
			 char  c[16] ;
			 float f     ;
			 short s[5] ; 
			 } U_DATI ;
			 
typedef struct s_mcsp   {
               S_HEAHOST hea;
             char  zona  ;
			 char  video;
			 char  pag[l_pagina];
			 short spare3 ;
			 short point[l_pagina/2] ;
			 short funz ;
			 short tipo ;
			U_DATI dat ;
				 } S_MCSP ;			          
#define vstat 62					/* messaggio di risposta*/
typedef union u_valf    { 
				char c[6] ;
			  	short s[3] ;
			  	float f ; } U_VALF ;

typedef struct s_vstat { 
             S_HEAHOST hea;
			 char zona ;
			 char video ;
			 char pag[l_pagina];
			 short spare3;
			 short tip_pun ;
			 short ext ;
			 short punt ;
			U_VALF val ; } S_VSTAT ;


/* TREND STORICI: INIZIO*/
/* Strutture dei messaggi utilizzati per la visualizzazione*/
/* dei dati di archivio*/

/**/
/* Messaggio richiesta dati di un quadrante inviato da mmi a scada*/
/**/
#define  maggr          21              /* indice messaggio*/
#define  maggr_new      22              /* indice messaggio con gestione
					   ack   */
#define  max_sigqua      4              /* n. massimo sigle in un quadrante*/
/*
#define  l_sigqua       10
*/
/*
modifica di Fabio 25/9/96
*/
#define  l_sigqua       20              /* lunghezza sigle in un quadrante*/
#define  l_pagina       10

typedef struct h_mtrend {
                        short   nodo;
                        char    indice;
                        char    spare;
                        char    zona;
                        char    video;
                        char    pagina[l_pagina];
                        short   codtrend;       /* codice trend assegnato da scada*/
                        char    indqua;         /* indice quadrante*/
                        char    n_mis;          /* numero curve*/
                        } H_MTREND;

typedef struct s_maggr {
                        H_MTREND hea;
                        char    archivio;       /* numero archivio*/
                        char    spare2;
                        char    sigla[max_sigqua*l_sigqua]; 
		       } S_MAGGR;

/**/
/* Messaggio inviato a tabul per l'invio dati storici a mmi*/
/**/
#define mvisarc    42
typedef struct s_visarc {
                        H_MTREND hea;
                        char    archivio;       /* numero archivio*/
                        char    spare2;
                        char    point[max_sigqua];
                        } S_VISARC;

/**/
/* Messaggio di invio parametri di configurazione di un quadrante*/
/* trend storico da scada a mmi*/
/**/
#define vprgr           54              /* indice messaggio      */
/*
*
*#define l_desqua        24              
*/
#define l_desqua        60	/* lunghezza descrizione sigla*/
#define l_staqua         8              /* lunghezza stato o unita' di misura sigla*/

typedef struct qmisdes { 
                        char descr[l_desqua];
						char stat0[l_staqua];
						char stat1[l_staqua];
                        } QMISDES;

typedef struct s_vprgr {
                        H_MTREND hea;
						float t_iniz;    		/* tempo iniziale in sec.*/
						float durata;    		/* durata temporale in sec.*/
                        float interv;    		/* minimo intervallo campionamento*/
						short giorno;  	 		/* giorno inizio estrazione*/
						short mese;      		/* mese inizio estrazione*/
						short anno;      		/* anno inizio estrazione*/
						QMISDES md[max_sigqua];	/* unita' di misura e descrizione dei punti richiesti*/
		       } S_VPRGR;

#define l_vprgr (sizeof(S_VPRGR)-sizeof(QMISDES)*max_sigqua)

/* */
/* Messaggio di invio dati un quadrante  trend storico da scada a mmi*/
/* */
#define vdsgr           46      /* indice messaggio*/
#define vdsgr_ack       23      /* indice messaggio ack vdsgr */
#define num_qcamp      200      /* n. massimo campioni*/

#define HT_BEGTRASM	2			/* flag di inizio trasmissione*/
#define HT_ENDTRASM	1			/* flag di fine trasmissione*/

typedef struct anval {	/* caso archiviazione normale per analogici*/
		   float val;	/* valore campione*/
		   char flag;	/* flag campione*/
		   char imis;	/* indice misura all'interno del record di FDARC.RTF*/
		  } ANVAL;
		  
typedef struct anave {	/* caso archiviazione lenta per analogici*/
		   float med;	/* media campioni attuale*/
		   char ctot;	/* numero totale campioni attuale*/
		   char cfsfa;	/* numero campioni non validi (fuori scans, fuori att) attuale*/
		  } ANAVE;
		  
typedef union an {	    /* caso analogico*/
		   ANVAL camp;
		   ANAVE ave;
		  } AN;

typedef struct di {		/* caso digitali*/
		  short dtipo;
		  short f_s;    /* flag e stato digitale*/
          char  dspare1;
          char  imis;
		  } DI;

typedef struct or {	    /* caso organi*/
		  short otipo;
		  short f_s;    /* flag e stato organo*/
          char  ospare1;
          char  imis;
		  } OR;

typedef union datdbs { 
		       AN a;
		       DI d;
		       OR o;
		      } DATDBS;

typedef struct qcamp {
				        float temp;	/* tempo campione*/
                        DATDBS val;	/* valore campione*/
		             } QCAMP;

#define l_ftemp  4                  /* dimensionamento campo float temp*/

typedef struct s_vdsgr {
                        H_MTREND hea;
               			unsigned char n_camp;     /* n. campioni*/
                        char    flag; 		      /* flag fine ultimi dati*/
						QCAMP   b;          	  /* buffer campioni     */
					   }S_VDSGR;

#define l_vdsgr (sizeof(S_VDSGR)-sizeof(QCAMP))

#define l_cra_vdsgr 22
#define l_cra_qcamp 6

#define l_maxgr 1400                 /* dimensione massima messaggio*/

/* */
/* Messaggio per trasferimento file su floppy*/
/* */
#define l_filext   13               /* lunghezza massima nome file + estensione*/
#define mtrasfarc  41

typedef struct s_floppy {
                        short lung;
                        short mess;
                        char  nome[l_filext];
                        short blocco;   /* n. blocco richiesto*/
                        short dim;      /* dimensione blocco a multipli di 1k*/
                        char  archivio; 
                        char  n_file;
                        short flag;     /* =1 ultimo blocco*/
                        } S_FLOPPY;
/* TREND STORICI: FINE*/
  
							                      
                  /*----------------------------------------------*/
                  


/*
	struttura stringa di allarme
*/
struct ppnt { char tipo ;
	      char ext  ;
	     short point ;} ;

/*
	struttura messaggio vdeal aggiornamento parte
	variabile $pal
*/

/*
	messaggio di diagnostica micro operatore
*/
#define mdia 9
#define max_dia 16		/* al massimo 16 segnalazioni*/

typedef struct s_aldia  { 
			unsigned short allarme:15;
			unsigned short condiz:1;	 /* =0 rientro 1 emissione */
			} S_ALDIA;

typedef struct  s_mdia {
                        short nodo;
			char indice	;
			char classe	;
			S_ALDIA a[max_dia] ;} S_MDIA ;

typedef struct  s_mdia_r {				/*struttura per un solo allarme*/
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

/*
	definizione messaggio richiesta descrizione punto
	e messaggio di risposta
*/
#define mrdp 19		/* richiesta descrizione	*/
#define vdesp 64	/* messaggio di risposta	*/
typedef struct s_mrdp   {
                         short nodo;
			 char  indice ;
			 char  classe;
			 char  zona  ;
			 char  video ;
			 char  pag[l_pagina] ;
			 short spare1;
			 short punto[5];
			 short tipo; } S_MRDP ;
#define lu_no 10	/* lunghezza nome 	 */
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





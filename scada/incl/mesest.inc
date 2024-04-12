/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#define MESEST_INCL
#ifdef _PUBLIC
#define _PUBLIC1
#undef _PUBLIC
#endif

#ifdef _PUBLIC1
#define _PUBLIC
#undef _PUBLIC1
#endif
#include "eqschpas.inc"
#include <all_1.h>
#undef long 
#define long int

#define   cpu 0                /* tipo cpu per tra mbox_inet */

#define  reteA	1
#define  reteB	2
#define  MASTER 1
#define  SLAVE 	0

                                // per routine aggtime()
#define RUNMODE		0       // modo normale
#define SETMODE		1       // forza aggiornamento al prossimo ciclo
#define T_AGGTIME       120     // periodo aggiornamento in 500 msec


/*
        il file di include mesest contiene le strutture
        dei messaggi che da stop vngono inviati a DAC o
	SCADA minimo  e viceversa
	Tutti i messaggi sono preceduti da un header comune                                                                
*/
#define cl_dac    1		/* classe dac	        */
#define cl_scada  0		/* classe scada	        */
#define cl_config 2		/* classe config	*/
#define cl_iommi  3		/* classe iommi		*/
#define cl_mmi	  4		/* classe mmi		*/

#define max_nodi_inet	32	/* numero max. nodi inet	*/
/*
        descrittore di nodo
        status          utilizzato per memorizzare lo stato del nodo 
                        per le due reti
        iniz            =nd_ver   verificare configurazione  (testnodi)
                        =nd_cfg   da configurare (acqui)
                        =nd_con   configurato (carac) 
                        =nd_con1  configurato e richiesti i digitali (carac)
                                  (testnodi se va off line)              
        line            stato sulla rete propria
*/
#define nd_con  0
#define nd_ver  1
#define nd_cfg  2
#define nd_con1 3
#define nd_reg  4

#define n_DigNodi	3	//	n. punti diagnostica per nodo
#define n_DigRetA	0	//	diagn . rete A
#define n_DigRetB	1	//	diagn. rete B
#define n_DigModF	2	//	diagn. mod. funzionamento

typedef struct s_desinet { unsigned  char  stato[n_DigNodi];
                           unsigned  char  iniz;
                           unsigned  char  linea;   // on/off
                           unsigned  char  Rce;     // flag Rce in corso
                          } S_DESINET;

typedef struct s_desinetaem { unsigned  char  status;
                           unsigned  char  iniz;
                           unsigned  char  line;   // on/off
                          } S_DESINETAEM;
/*
        flag per la gestione diagnostica contatori comunicazione
        armadi vedi gesarm.c
*/
#define cn_reset        0       /* reset contatori              */
#define cn_incr         1       /* incrementa contatori         */
#define cn_test         2       /* testa se variato             */
#define cn_incra        3       /* incrementa contatori rete A  */
#define cn_incrb        4       /* incrementa contatori rete B  */

#define max_nodi_diag	21	/* numero max. nodi diagnostica */
#define nodo_test_rete 	255	/* nodo per test comunicazioni	*/
#define nodo_config  	1	/* nodo riservato a config	*/
#define nodo_stop_1  	2	/* nodi riservati a stop	*/
#define nodo_stop_2  	3	/* nodi riservati a stop	*/
#define nodo_armadi     8	/* primo nodo riservato all'acq.*/

typedef struct hea_scada{ short addr_nodo  ;
			  unsigned char	mess ;		/* indice messaggio		*/
			  unsigned char msl  :2;	/* destinazione master/slave    */			
			  unsigned char prov :3;	/* classe di provenienza	*/
			  unsigned char dest :3;	/* classe di destinazione	*/
			 } HEASCA;			/* i define da utilizzare sono  */
							/* definiti in messcada.inc     */
							/* AGG_SLAVE,AGG_MASTER,AGG_ALL */
/*
	messaggio per conoscere lo stato della rete
*/
#define inet_stato	0x90
#define inet_modo	0x91
#define inet_sys	0x92
#define comm_sys	0x93
#define inet_abil	0x94

#define rete_A		0			
#define rete_B		0x80			


typedef struct s_inet_sys {
			HEASCA	hea;
			short	modo;
			   }  S_INET_SYS;

typedef struct s_inet_master {
			HEASCA	hea;
			short	modo;
			short	nodo;
			   }  S_INET_MASTER;

typedef struct s_nab	{  char addr;
			   char abil;
			} S_NAB;

#define	nodo_abilitato		1
#define nodo_non_abilitato	0

typedef struct s_inet_abil {
			HEASCA	hea;
			short   n_nodi;
			S_NAB	n[max_nodi_inet];
			   }  S_INET_ABIL;

/*	
	messaggio di risposta
*/
#define mstrete		30
#define mask_sta	0x01		// bit collegamento rete a
#define mask_stb	0x02		// bit collegamento rete b
#define mask_mod	0x80		// modo operativo
#define mask_msa	0x10		// master rete A
#define mask_msb	0x20		// master rete B

#define varete		32		// variazione stato di un nodo

typedef struct s_strete{ 
			 HEASCA hea;
			 char  st_nodo[max_nodi_inet]; } S_STRETE;

typedef struct s_vanodo {
	       unsigned	char  	ind;	// indirizzo nodo
	       unsigned	char	stat;	// stato del nodo;
			} S_VANODO;
typedef struct s_varete{ 
			 HEASCA hea;
			 S_VANODO  nodo[max_nodi_inet]; } S_VARETE;
/*
   mstcfg messaggio set data e release di configurazione
   mgtcfg messaggio get release e data di configurazione
   rgtcfg messaggio risposta a una richiesta di configurazione
*/
#define mgtcfg 24                       
#define rgtcfg 69                       
#define mstcfg 23
typedef struct s_mstcfg {
			HEASCA hea;
			short  giorno;
			short  mese;
			short  anno;
			short  ora;
			char   release[6]; } S_MSTCFG;
/*
	richiesta di tutti i digitali
*/
#define mrsdi 14
typedef struct s_mrsdi {
			HEASCA hea;
			short  point; } S_MRSDI;
/*
	definizione dei messaggi da scada a dac
*/
/*
        definizione dei messaggi per l'inserimento e la
        eliminazione di un punto analogico acquisito
        
        s_minan inserimento analogico acquisito
	s_melan cancellazione punto analogico acquisito
*/
#define minan 1         /* inserimento          */
#define melan 2         /* eliminazione         */

typedef struct s_minan {
                         HEASCA  hea ;
                         S_FDEACQ b ; } S_MINAN ;

typedef struct s_melan {
                         HEASCA  hea ;
                         short punt ; } S_MELAN ;
/*
        definizione dei messaggi per l'inserimento e la
        eliminazione di un punto digitale acquisito
        
        s_mindi inserimento digitale acquisito
	s_meldi cancellazione punto digitale acquisito
*/
#define mindi 16         /* inserimento          */
#define meldi 17         /* eliminazione         */

typedef struct s_pmindi {
			 short puntdb;
			 short indfis; } S_PMINDI;
#define max_mindi 8
typedef struct s_pmindiext {
			 short puntdb;
			 short indfis;
			 short flag;
                                         } S_PMINDIEXT;

typedef struct s_mindi {
                         HEASCA  hea ;
			 short    numd;
                         S_PMINDI b[max_mindi]; } S_MINDI ;
typedef struct s_mindiext {
                         HEASCA  hea ;
			 short    numd;
                         S_PMINDIEXT b[max_mindi]; } S_MINDIEXT ;

typedef struct s_meldi {
                         HEASCA  hea ;
                         short punt ; } S_MELDI ;
/*
        definizione dei messaggi per l'inserimento e la
        eliminazione di un punto digitale di uscita
        
        s_mindo inserimento digitale di uscita
	s_meldo cancellazione punto digitale di uscita
*/
#define mindo 20         /* inserimento          */
#define meldo 21         /* eliminazione         */

typedef struct s_mindo {
                         HEASCA  hea ;
                         S_FDCOM  b; } S_MINDO ;

typedef struct s_meldo {
                         HEASCA  hea ;
                         short indice;}  S_MELDO ;

/*
        definizione dei messaggi per l'inserimento e la
        eliminazione di un punto analogico di uscita
        
        s_minao inserimento analogico di uscita
	s_melao cancellazione punto analogico di uscita
*/
#define minao 11         /* inserimento          */
#define melao 12         /* eliminazione         */

typedef struct s_minao {
                         HEASCA  hea ;
                         S_FDEAO b; } S_MINAO ;

typedef struct s_melao {
                         HEASCA  hea ;
                         short indice;}  S_MELAO ;


#define mstr  4         /* start acquisizione     */
#define mstp  5         /* stop acquisizione      */
#define mrst 6         /* reset configurazione   */

/*
	definizione dei messaggi da dac a scada
*/

#define mdana 64        /* invio dati analogici		    */
#define max_analogici 180

union f_i {	float f;
		long  l;
                char  c[4]; };
typedef struct s_dtaa {
		short point ;
		union f_i val ; } S_DTAA ;
typedef struct s_mdana {
		HEASCA hea ;	
		S_DTAA  dati[max_analogici]; } S_DANA ;

#define mddig 65	/* invio dati digitali		    */
#define max_digitali 256
/*
	struttura record digitali
*/
struct D_VAL	{
		unsigned short val :14;
		unsigned short FA  : 1;
		unsigned short ST  : 1;
		};
#define MASK_ST 0x8000
#define MASK_Q	0x4000
union DIG_VAL {
		short digital;
		struct D_VAL d_val;
	      };

typedef struct s_mddig {
		HEASCA hea;
		long	secondo;
		union DIG_VAL dig_val[max_digitali]; } S_DDIG ;

typedef struct s_mddig_s {
		HEASCA hea;
		union DIG_VAL dig_val[max_digitali]; } S_DDIG_SEPA ;




#define mscdo 9	       /* invio comando digitale da SCADA a DAC   */

typedef struct s_mscdo {
		HEASCA hea;
		short  indice; } S_MSCDO ;

typedef struct s_mscdo_sep {
		HEASCA hea;
		short  indice;
		char   valore; 
		char   temp; } S_MSCDO_SEP;

#define mdcom 66      /* attivare comando da DAC a SCADA	  */

typedef struct s_mdcom {
		HEASCA  hea ;
		short   comando;
		short   tipo;
		short   organo;
		short	time;
                S_STATI  stat[st_com] ;
		short	abili; }	S_MDCOM ;

#define mscao 10	       /* invio comando analogico da SCADA a DAC   */

typedef struct s_mscao {
		HEASCA hea;
		short  indice; 
		float  valore;	} S_MSCAO ;
/*
	struttura messaggio generico da Scada
*/
typedef struct s_msgo {
			unsigned char mess;
			char classe_scada;
			S_DTAA dta;
		      } M_MSGO;

/*
	messaggi per il caricamento dei pas
*/
#define minps  	25	// codice messaggio di inizializzazione pas
#define mcaps   26	// codice messaggio di caricamento pas
#define mfips   27	// codice messaggio di fine caricamento pas

/* Struttura messaggio di inizializzazione */

typedef struct s_minps { HEASCA  hea;
			 short	 n_pas ;
			 long	 l_dbl;
			 long	 l_rtf;
			 short   sto_sta;
			 short   run_fre;
           		 char    buf_pcb[DIMPCB]; } S_MINPS;

/* Struttura messaggio di fine caricamento pas */

typedef struct s_mfips { HEASCA  hea;
			 short	 n_pas ; } S_MFIPS;

#define n_dim 512	// dimensione in byte blocco di trasferimento dati

#define f_dbl 0			/* codice file data base locale */
#define f_rtf 1			/* codice file programma        */

/* Struttura messaggio di caricamento aree dati pas */

typedef struct s_mcaps { HEASCA	 hea;
			 short	 n_pas;
			 short   n_file;
			 short   n_blocco;
			 short   n_bytes;
		         short   flag;
			 char	 blocco[n_dim]; } S_MCAPS;

#define mabi 1		// abilitazione nodo
#define mdis 2		// disabilitazione nodo

typedef struct s_mabi { HEASCA hea;
			short nodo; } S_MABI;

#define mdmast  15      // diventa Master
#define amastA  0x100   // per forzare invio ad A
#define amastB  0x200   // per forzare invio ad B
/*
	maschere per acquisizione con reti duali
*/
#define MaskReteA	0x4000
#define MaskReteB	0x8000
#define MaskNodo	0x00FF

/*
        messaggio con orario
*/
#define mclock  67

typedef struct s_mclock { HEASCA  hea;
                          char    gio;
                          char    mese;
                          char    anno;
                          char    ore;
                          char    min;
                          char    sec;
                                } S_MCLOCK;
#include <all_16.h>
#undef long 
#define long long

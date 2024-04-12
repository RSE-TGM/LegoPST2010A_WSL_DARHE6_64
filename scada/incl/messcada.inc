/**********************************************************************
*
*       C Header:               messcada.inc
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Dec 16 13:23:59 2002 %
*
**********************************************************************/
/*
	messcada.inc
	nell'include vengono definiti i messaggi fra i
	task real-time scada

        30 Dicembre 1992
        Inserimento maschere per trattamento e livelli di severita'
        nel messaggio S_MALLA

*/
#include "switch.inc"
#define mall 1
#include <all_1.h>

typedef struct s_mcval { char direz ;
			 char indice ;
			 char video ;
			 char zona  ; } S_MCVAL ;

/*
	messaggio invio allarme a call
*/
typedef struct s_malla { unsigned char ertr ;
			 char ext ;
		         short punt;
			 char  sprec;
			 char  satt ;
			 unsigned char  sogl1;
			 unsigned char  sogl2;} S_MALLA ;

#define M_TRALL         0x0F    /* maschera per trattamento      */
#define M_SEALL         0x30    /* maschera severita'            */
#define M_NOSEALL       0xCF    /* eliminazione severita'        */

#include <all_16.h>
#include "mesestel.inc"
#include <all_1.h>
typedef struct s_mallat { S_MALLA  m;
                          MISTIME  t;
                          float    v;
                        } S_MALLAT;
/*
	messaggi verso il task tratg trattamenti generici
*/
#define mtrdi   3       	/* richiesta trattamento digitale */
				/* in seguito a variazione del    */
				/* valore o del flag di fuori att.*/
#define mtror   4               /* richiesta trattamento organo in*/
				/* caso di variazione dello stato */
#define mcaor   5		/* ricalcolare lo stato organo    */
				/* in seguito a forzamento o fuori*/
				/* scansione			  */
#define mcadi   6		/* ricalcolare digitale calcolato */
				/* in seguito a forzamento o fuori*/
				/* scansione			  */
#define macdi   1       	/* acquisizione digitale */
				/* deve essere utilizzato ogni 	  */
				/* volta che viene variato stato  */
				/* od il flag di FA di un digitale*/
				/* qualsiasi (non di diagnostica) */
#define macdd   2               /* acquisizione diagnostica       */
#define mfadi   7               /* variazione flag fa		  */
#define macst   8		/* modifica stringa		  */
#define maudi   9               /* gestione flag AU               */

#define macdit  10              /* variazione stato               */
#define mtrdit  11              /* trattamento                    */
#define mfadit  12              /* variazione fuori attendibilita'*/


typedef struct s_tratg { short mess ;
			 char  stato ;
			 char  ext ;
			 short indice ;} S_TRATG ;

typedef struct s_tratgt { S_TRATG  m;
                          MISTIME  t;
                        } S_TRATGT;
/*
	messaggi per gestione duale e aggiornamento
	configurazione
*/
#define FILE_MMI	3		// trasmissione file mmi
#define TESTA_FILE	5 		// nome file RTF
#define file_iniz       -1              // nome file fittizio per inizio
                                        // trasferimento files operativi
#define file_rev        "RV"            // nome particolare di file
                                        // per variazione release data base
#define DATI_FILE  	6		// contenuto file RTF
#define FINE_FILE  	7		// fine file RTF
#define FINE_TX    	8		// fine trasmissione file
#define	SL_READY	9
#define SL_AGG		10	        // slave aggiornato
#define SL_AGG_ACQ	90	        // segnalazione per acquisizione
#define SL_ONLINE	11
#define MSG_ACQUI	12
#define MSG_MMI		13
#define STATOSIS        14 	 	// messaggio richiesta stato
#define FORZAMASTER     15 		// messaggio forzamento master
#define	AGG_REV 	16              // variata release slave
#define EOM	        17		// fine comunicazione con 186
#define MSG_VDB         18              // invio dati digitali e analogici
                                        // acquisiti
#define NO_STATOSIS	19		// messaggio stato sistema non master
#define MSG_CFGOK	21 		// configurazione ok
#define MSG_CFGKO	22		// configurazione ko
#define MSG_DB          23		// invio data base
#define MSG_CLOCK       24		// messaggio scrittura clock

#define STATOSISES      25 	 	// messaggio richiesta stato (estesa)

#define AGG_MASTER	0		// trasmissione solo a master
#define AGG_SLAVE	1		// trasmissione solo a slave
#define AGG_ALL		2		// trasmissione a master e slave
#define BIT_COMPRESS    0x80		// trasmissione in compresso

#define RTF_TRASF	30

#define lun_fnome 12

typedef struct txf1 {	
			short nodo;
			char tipomess;
			char aggtype;
#if defined OSF1 || defined LINUX
                        int numbyte;
#else
                        long numbyte;
#endif
			char nome[lun_fnome];
		      } TXTESTA_FILE_ETH;			                            

#define l_dati_file     512			
typedef struct txf3  {	
			short nodo;
			char tipomess;
			char aggtype;
                        short numbyte;
			char dati [l_dati_file];
		    } TXDATI_FILE_ETH;

typedef struct txf2 {	
			short nodo;
			char tipomess;
			char aggtype;
			short tipofile;	
		      } TXFINE_FILE_ETH;			                            
			
#define MAXFILE 100			/* n. max files trasferibili */	       

struct trasm_fmmi_eth {		//struttura trasmissione file MMI
		short nodo;
		char indice;
		char f_agg;		// tipo di aggiornamento
		char ack;		// indice micro
		char video;
                short num_mes;         /* contatore del numero di messaggi
                                           verso lo scada */
		short spare[2];
		short ind_file;		// indice file da aggiornare
		short ind_blocco;	// indice del blocco disco del file
		short bl_dsk[256];	// blocco disco
		};
/*
	struttura messaggi di stato sistema (master, slave, A, B e
	rispettive release data base)
*/
#define SIS_A 0
#define SIS_B 1
#define MASTER 1
#define OFF 0
#define ON 1
#define SLAVE  0
			// maschere per test byte di status

#define MASK_IDEN 	 0x40
#define MASK_MASTER 	 0x80
#define MASK_WDDUALE 	 0x10

#define max_video1      9               
typedef struct rx_statosys	{short nodo;
				 short mess;
			 unsigned char status; 
			 unsigned char rete;
			 	  char rel_propria[4];
			   	  char rel_duale[4];
				  char n_video;			// n. video della configurazione
				  short stvideo[max_video1];
				} RX_STATOSIS;

typedef struct tx_ack		{short nodo;
				 short mess;
				} TX_ACK;
#define MESSACK	       30	
/*
	tipo di device da utilizzare per la trasmissione
*/
#define dev_disco	0
#define dev_seriale	1
#define dev_bitbus	2
#define dev_ethernet	3

#include <all_16.h>

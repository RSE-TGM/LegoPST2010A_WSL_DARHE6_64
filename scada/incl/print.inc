/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

/*-> print

        il file di include print.inc
        contiene :

        .       file pointer file descrittori e
                dimensione dei record
        .       tabelle device per l'output
        
        10 Novembre 1994 Fc
        Inserita definizione struttura per stampa stringa ASCII
*/

#include "defpub.h"
#include <all_1.h>
#include <tag.h>
# undef long
#define long int

/*
        definizione delle strutture associate alle linee seriali
        per le stampanti
*/
#define n_fis (8+1)              // n. linee fisiche + disco
#define fis_disk (n_fis-1)	 // linea per disco

typedef struct s_fis    {
                         short  baud;   // baud rate
                         char   data;   // data bit
                         char   stbit;  // stop bit
                         char   parity; // parita
                         char   linea;  // n. linea associata
			 char   flag ;  // allarmi o tabulato ?
                         char   stato;  // stato del device
			short   *dig;	// puntatore in data base logico
                        } S_FIS;

#define si_fine	        0
#define no_fine		1       
/*
        definizione della struttura dei device logici
*/
#define n_device 2
typedef struct s_log    {
		unsigned char page_a;	// n. pagine libro giornale
		unsigned char page_g;	// n. pagine attivita' generiche
                unsigned char righe_a;  // n. righe libro giornale
                unsigned char righe_g;  // n. righe attivita' generiche
                short indice[n_device]; // indice device fisici associati
		short prev;		// corrente device fisico utilizzato
                        } S_LOG;
/*
        sia il libro giornale che i tabulati possono al
        massimo avere n stampanti logiche in parallelo
        associate
        ad ogni stampante logica possono poi venire assegnati
        fino a n_device device fisici
*/
#define n_loga 2
#define n_logt 2
/*
	se sono state definite delle linee remote
	(seconda scheda 546) definisco la tabella
	di svincolo
*/
pub S_FIS stfis[n_fis];
pub S_LOG stloga[n_loga];
pub S_LOG stlogt[n_logt];
/*
	buffer di comunicazione dati tra stampe e intesta.c
	l'intestazione per tpr_archivio non e' statica
	quindi occorre un mezzo per trasmettere i valori variabili
*/
pub short	infotesta[4];
/*
        struttura per il formato di stampa degli allarmi
        normali
*/
#define c_tipo  8
#define c_stp   8
#define c_sta  10
#define c_val  10
#define c_data 2
#define c_umis 8
typedef struct shea	{ short lung;
			  char	szvir;          
			  char  linea; } HEA_STA;
typedef struct s_foral  {
			 HEA_STA hea;
			 long blank_1 ;
                         char gior[c_data] ;
                         char sep_1;
                         char mese[c_data];
                         char sep_2;
                         char anno[c_data] ;
                         long blank_2 ;
                         char ora[c_data];
                         char sep_3 ;
                         char min[c_data];
                         char sep_4;
                         char sec[c_data];
                         long blank_3;
                         char nome[SCD_SIGLA];
                         long blank_4;
                         char desc[SCD_DESCRIZIONE_LBG];
                         long blank_5 ;
                         char tipo[c_tipo];
                         long blank_6;
                         char st_prec[c_stp] ;
                         long blank_7;
                         char st_att[c_sta];
                         long blank_8;
                         char val[c_val] ;
                         short  new ;
                         char eos ;
		         char even;
                         } S_FORAL ;
#define max_righe 26

/*
	definizione tipi di stampa
	tpr_reset richiede il reset dello stato delle stampanti
	lo stato viene posto a 1 quando in stampa c'e' un tabulato
	per bloccare la stampa contemporanea degli allarmi
	tpr_tabulato		da usare in caso di stampa tabulato
	tpr_allarme		da usare in caso di stampa libro
				giornale
	tpr_archivio		da usare in caso di stampa allarmi
				da riconoscere e archiviati
	tpr_stringa		da usare per segnalazione su stampante
				generiche (una sola scritta)
	tpr_elenco		da usare in caso di stampa elenchi
	tpr_allarme_2		da usare qualora si vuole ridirigere
				l'allarme sulla stampante tabulati
	
	Le righe e le pagine vengono incrementate sia per tpr_allarme che
	per tpr_archivio a cui e' associata un diverso tipo di intestazione
*/
#define		tpr_reset      -1
#define		tpr_tabulato	0
#define		tpr_allarme	1
#define		tpr_stringa	2
#define		tpr_null	3		
#define		tpr_archivio	4
#define		tpr_elenco	5
#define		tpr_allarme_2	6
/*
	variabile che indica la variazione del giorno
	per reset libro giornale
*/
pub short i_day;
/*
	indici per la scrittura del libro giornale
	su disco
*/
pub short   n_allfile;			// indice file in uso da 1 a 8
#define max_n_allfile  8	 	// max. n. files 8
pub long    byte_allfile;  		// n. byte scritti sul file in uso
#define max_byte_allfile  132000	// dimensione max. del file in bytes
pub FILE *fpstall;			// canale per scrittura su disco

/*
	struttura per variazione data su 546
*/
#define linea_clock	-1	
typedef struct ch_date  {
			 HEA_STA hea;
			 short   zero ;
			 char	 sec;
			 char	 min;
			 char	 ore;
			 char	 zero1;
			 char	 giorno;
			 char	 mese;
			 char	 zero2;
			 char	 anno;
			 char    mese1;
			 char    zero3;
			}   CH_DATE;
/*
	stringa utilizzata per la stampa degli allarmi in archivio
	o in pagina allarmi
*/
typedef struct s_forar  {
			 HEA_STA hea;
			 long blank_1 ;
                         char gior[c_data] ;
                         char sep_1;
                         char ora[c_data];
                         char sep_2 ;
                         char min[c_data];
                         char sep_3;
                         char sec[c_data];
                         long blank_2;
                         char nome[SCD_SIGLA];
                         long blank_3;
                         char desc[SCD_DESCRIZIONE_LBG];
                         long blank_4 ;
                         char tipo[c_tipo];
                         long blank_5;
                         char st_prec[c_stp] ;
                         long blank_6;
                         char st_att[c_sta];
                         short  new ;
                         short  eos ;
                         } S_FORAR ;
/*
	strutture per intestazione libro giornale allarmi
*/
typedef struct intall_1 {
  		       HEA_STA hea;
		       char blank_1[10];
                       char data[8];
                       char blank_2[10] ;
                       char bmaster[12];
                       char sys;
                       char blank_4[67];
                       char page[4] ;
                       char blank_3[2];
                       char num[4];
                       short new;
                       short eos; } S_INTALL_1 ;
#define l_intall 122 
typedef struct intall_2 {
	     	       HEA_STA hea;
		       char stringa[l_intall];
                       short new; 
		       short eos; } S_INTALL_2 ;

typedef struct s_ffeed 	{ HEA_STA hea;
		  char   ff[2]; } S_FFEED;

/*
	stringhe per intestazione tabulato con allarmi
	da riconoscere e in archivio
*/
#define l_intear	120
typedef struct s_intear  {
			 HEA_STA hea;
			 char stringa[l_intear];
			 short new_1;
			 short new_2;
                         } S_INTEAR ;

/*
	stringa utilizzata per la stampa degli elenchi
*/
#define c_value		8
typedef struct s_forel_al {
			 HEA_STA hea;
			 long blank_1;
                         char nome[SCD_SIGLA];
                         char blank_3;
                         char desc[SCD_DESCRIZIONE];
                         char blank_4;
			 char umis[c_umis];
			 char blank_u;
                         char valhs[c_value] ;
                         char blank_5;
                         char valhc[c_value] ;
                         char blank_6;
                         char vallc[c_value] ;
                         char blank_7;
                         char valls[c_value] ;
                         char blank_8;
                         char value[c_value] ;
                         short  new ;
                         short  eos ;
                         } S_FOREL_AL ;

typedef struct s_forel_di {
			 HEA_STA hea;
			 long blank_1;
                         char nome[SCD_SIGLA];
                         char blank_3;
                         char desc[SCD_DESCRIZIONE];
                         char blank_8;
                         char value[c_value] ;	
                         short  new ;
                         short  eos ;
                         } S_FOREL_DI ;

typedef struct s_forel_an {
			 HEA_STA hea;
			 long blank_1;
                         char nome[SCD_SIGLA];
                         char blank_3;
                         char desc[SCD_DESCRIZIONE];
                         char blank_8;
                         char umis[c_umis] ;   
                         char blank_9;
                         char value[c_value] ;	
                         short  new ;
                         short  eos ;
                         } S_FOREL_AN ;

#define lfostr 60
typedef struct s_fostr {
	   HEA_STA hea;
	   long blank_1 ;
           char gior[c_data] ;
           char sep_1;
           char mese[c_data];
           char sep_2;
           char anno[c_data] ;
           long blank_2 ;
           char ora[c_data];
           char sep_3 ;
           char min[c_data];
           char sep_4;
           char sec[c_data];
           long blank_3;
           char message[lfostr];
                  } S_FOSTR;
/*
	flag per indicare coda stampe piena
	viene settato da stamal (task call) e resettato da
	stampe dopo aver svuotato la coda 
*/
pub char  full_stampe;

#include <all_16.h>
#undef  long
#define long long

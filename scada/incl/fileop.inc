/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#include "schede.inc"
#include "tag.h"
#define FILEOP_INCL
/*
        file fileop.inc

        contiene la definizione dei record dei file
        operativi
*/

                        short puntgf;
/* SCD_SIGLA punto SCD_DESCRIZIONE desc SCD_UNIMIS unita' mis. */
#define rec_fdaa        (SCD_SIGLA+SCD_DESCRIZIONE+SCD_UNIMIS)

#define conv_te          1   /* termocoppia                             */
#define conv_tj          2   /* termocoppia                             */
#define conv_tt          3   /* termocoppia                             */
#define conv_tk          4   /* termocoppia                             */
#define conv_tr          5   /* termocoppia                             */
#define conv_ts          6   /* termocoppia                             */

#define conv_gd          7   /* giunto freddo                           */
#define conv_gb          8   /* giunto freddo                           */

#define conv_pol         9   /* conversione polinomiale        		*/

#define conv_rd         12   /* termoresistenze                         */
#define conv_rb         13   /* termoresistenze                         */

#define conv_cont	16   /* conversione per diagnostica e contatori */
#define conv_ch		17   /* conversione per contatori hw		*/
#define conv_log	18   /* conversione per logici			*/

#define COD_NORCE       0x00
#define COD_RCE         0x01
#define COD_TRIG        0x02
#define COD_SCAT        0x03
#define MASK_STAT       0x8000

/*
	Struttura del descrittore analogici acquisiti.
        Definizione della struttura dell'indirizzo fisico del punto
*/
typedef struct ind_fis {
                unsigned short indir:12;	  /* indirizzo punto	  */
                unsigned short tipo:4;     /* tipo scheda	  */
                }   IND_FIS;
typedef union u_ind_fis {
		IND_FIS  b;
		short    s; } U_IND_FIS;
/*
	struttura campo  indice range - delta elab - coeff. grande variazione
*/
typedef struct ran_el_gv {
                unsigned short gv:4;	 /* grande variazione	  */
                unsigned short el:7;      /* delta elaborazioni	  */
                unsigned short ra:5;      /* indici range 	  */
                }   RAN_EL_GV;
/*
        Definizione della struttura del descrittore analogici acquisiti:
*/
typedef struct rec_fdeacq  {
                        unsigned char tipo;
                        unsigned char classe;
                        short puntdb;
                        U_IND_FIS indfis;
                        RAN_EL_GV range;
                        short puntgf;
                        float cfilt;
                        float limfz;
                        float a;
                        float b;
                        float c;
                        float d;
                        float e;
                        short micro;
                      }  S_FDEACQ ;

#define rec_fdeacq sizeof(S_FDEACQ)
/*
        tabella coppie limiti di attendibilita'
*/
#define num_coppie 32
/*
        tabella occupazione indici fisici
*/
#define rec_fselaq (max_fisici/8)	    /* 1 bit per punto 1 record */
					    /*	per ogni tipo di scheda */
#define rec_fdpunas 512     /* scheda punto */
/* SCD_SIGLA punto SCD_DESCRIZIONE desc SCD_UNIMIS unita' di misura */
#define rec_fdas    (SCD_SIGLA+SCD_DESCRIZIONE+SCD_UNIMIS)

#define rec_fdpunac 512     /* scheda punto */
/* SCD_SIGLA punto SCD_DESCRIZIONE desc SCD_UNIMIS unita' di misura */
#define rec_fdac    (SCD_SIGLA+SCD_DESCRIZIONE+SCD_UNIMIS)

#define rec_fdpunad 512     /* scheda punto */
/* SCD_SIGLA punto SCD_DESCRIZIONE desc SCD_UNIMIS unita' mis. */
#define rec_fdad   (SCD_SIGLA+SCD_DESCRIZIONE+SCD_UNIMIS) 

#define rec_fdpunao 512     /*  scheda punto    */
/* SCD_SIGLA punto SCD_DESCRIZIONE descrizione  SCD_UNIMIS unita' mis. */
#define rec_fdao    (SCD_SIGLA+SCD_DESCRIZIONE+SCD_UNIMIS)
/*
	definizione del record del file fdeao
*/
typedef struct rec_fdeao  { 
			short puntdb;
			U_IND_FIS indfis;
			float	lapf;
			float	coeff;
			float	molt;
			float	add;
			short	peri;
			  } S_FDEAO ;

#define rec_fdeao (sizeof(S_FDEAO))
/*
        Definizione della struttura del descrittore digitali acquisiti:
*/
typedef struct rec_fdeda  {
                        short puntdb;		/* il bit piu' significativo */
                        U_IND_FIS indfis;	/* contiene l'inversione di  */
			short micro;		/* polarita'		     */
                      }  S_FDEDA ;  

typedef struct rec_fdedaext  {
                        short puntdb;		/* il bit piu' significativo */
                        U_IND_FIS indfis;	/* contiene l'inversione di  */
			short flag;
			short micro;		/* polarita'		     */
                      }  S_FDEDAEXT ;  


#define rec_fdeda sizeof(S_FDEDA)

#define rec_fselda (max_fisici/8)	    /* 1 bit per punto 1 record */

#define rec_fdpunda 512     /* scheda punto */
/* SCD_SIGLA punto SCD_DESCRIZIONE desc SCD_STATO*2 stati 0 e 1*/
#define rec_fdda        (SCD_SIGLA+SCD_DESCRIZIONE+SCD_STATO*2)

#define rec_fdpunds 512     /* scheda punto */
/* SCD_SIGLA punto SCD_DESCRIZIONE desc SCD_STATO*2 stati 0 e 1*/
#define rec_fdds        (SCD_SIGLA+SCD_DESCRIZIONE+SCD_STATO*2)

#define rec_fdpundc 512     /* scheda punto */
/* SCD_SIGLA punto SCD_DESCRIZIONE desc SCD_STATO*2 stato 0 e 1*/
#define rec_fddc        (SCD_SIGLA+SCD_DESCRIZIONE+SCD_STATO*2)

#define rec_fdpundd 512     /* scheda punto */
/* SCD_SIGLA punto SCD_DESCRIZIONE desc SCD_STATO*2 stati 0 e 1*/
#define rec_fddd   (SCD_SIGLA+SCD_DESCRIZIONE+SCD_STATO*2)

#define rec_fdpundo 512    /*  scheda punto */
/* SCD_SIGLA punto SCD_DESCRIZIONE descrizione     */
#define rec_fddo    (SCD_SIGLA+SCD_DESCRIZIONE)
typedef struct s_stati  {       char st_att;
                                char st_fut; } S_STATI ;
#define st_com 4
typedef struct s_fdcom  {       short comando ;
                                short tipo ;
                                short organo ;
                                short time ;
                                S_STATI  stat[st_com] ;
                                short   abili ;
                          	short  numdo;
				U_IND_FIS usc1;
				short	temp1;		
				U_IND_FIS usc2;
				short	temp2;		
				U_IND_FIS usc3;
				short	temp3;		
				U_IND_FIS usc4;
				short	temp4;
				short	micro;		
 			 } S_FDCOM ;

#define rec_fdcom  sizeof(S_FDCOM)

#define rec_fdpunor 512     /* scheda punto */
/* SCD_SIGLA punto SCD_DESCRIZIONE desc SCD_TIPOR tipo organo */
#define rec_fdor        (SCD_SIGLA+SCD_DESCRIZIONE+SCD_TIPOR)
#define num_stati 64
#define lun_stato 8          /* lunghezza nome stato in chiaro */
typedef struct s_fstato { short ncontr ;
                          char  vet_stati[num_stati];} S_FSTATO ;
#define rec_fstato     sizeof(S_FSTATO)

#define rec_fdpunto 512
#define rec_fdizst  512

#define rec_fdpunst 512     /* scheda punto */
/* SCD_SIGLA punto SCD_DESCRIZIONE desc  */
#define rec_fdst    (SCD_SIGLA+SCD_DESCRIZIONE)

/*
	definizione offset per file descrittore unico
	fdde
*/
#define of_fdaa 	0
#define of_fdas		((long)of_fdaa+(long)rec_fdaa*(long)h_db.dimaa)
#define of_fdac		((long)of_fdas+(long)rec_fdas*(long)h_db.dimas)
#define of_fdad		((long)of_fdac+(long)rec_fdac*(long)h_db.dimac)
#define of_fdao		((long)of_fdad+(long)rec_fdad*(long)h_db.dimad)
#define of_fdda		((long)of_fdao+(long)rec_fdao*(long)h_db.dimao)
#define of_fdds		((long)of_fdda+(long)rec_fdda*(long)h_db.dimda)
#define of_fddc		((long)of_fdds+(long)rec_fdds*(long)h_db.dimds)
#define of_fddd		((long)of_fddc+(long)rec_fddc*(long)h_db.dimdc)
#define of_fddo		((long)of_fddd+(long)rec_fddd*(long)h_db.dimdd)
#define of_fdor		((long)of_fddo+(long)rec_fddo*(long)h_db.dimdo)
#define of_fdst		((long)of_fdor+(long)rec_fdor*(long)h_db.dimor)
/*
    Parte relativa ai TABULATI (LOGEDITOR).
	estensioni associate ai tabulati
*/
#define g1tiptc   21      /* tipo tabulati gestione              */
#define g1tiptg   22      /* tipo tabulati caratteristiche       */
#define g1tipin   0x4E49  /* corrispondente a IN  tipo include   */
/*
        definizione strutture e record per files
        associati ai tabulati
*/
#define  n_tabu   32   /* n. tabulati max. definibili  */
#define l_nomtab 10    // lunghezza nome tabulato       	
/*
        definizione file dizionario tabulati 
*/
typedef struct s_diztab {       char nome[l_nomtab] ;
                                short periodo ;
                                } S_DIZTAB ;
#define rec_fdiztab sizeof(S_DIZTAB)
	 	

#define l_datab 2048   // dimensioni massime in byte parte dati del programma 
		       // di gestione tabulati.
#define l_codtab 6144  // dinensioni massime in byte parte codice del programma
		       // di gestione tabulati (== 3 kbyte). 
/*
	Struttura header file FTAB.
*/
typedef struct s_htab   {       short tip_dat ;
                                short arc_frq ;
                                short cicli ;
                                short spare ;	 } S_HTAB;
#define l_htab sizeof(S_HTAB)
#define DATBAS   1    /* dati prelevati da data base */
#define ARCHIVIO 2    /* dati prelevati da archivio  */

#define off_dat l_htab   // offset all'interno di un record a cui inizia 
 			  // la sezione dati.
#define off_cod (l_htab+l_datab)  // offset a cui inizia la sezione codice.
/*
	Struttura header parte codice di FTAB
*/
typedef struct s_hcod {
		       short lung;	// lung. file oggetto
		       short percamp;	// periodo di campionamento
                       short spare[14];	 
                       short entryI;	// entry init
                       short entry0;	// entry 0
                       short entry1;	// entry 1
		       short entryT;	// entry term
		       short entint[48];  // entry int 0 ... entry int 47
                       short menu[12];	
             	      } S_HCOD;
#define l_hcod sizeof(S_HCOD)
#define rec_ftab (l_htab+l_datab+l_codtab)
/*
	HEADER del blocco DATI di FTAB.RTF
*/
typedef struct head_datab {
			short n_link;    // numero delle variabili di link
			short l_data;     // occupazione totale in byte delle 
					  // var. tipo DATA.
			unsigned char n_point;    // numero costanti puntatori.
			unsigned char spare;     // spare ?.
			short camp;              // periodo di campionamento.
			} HEAD_DATAB;
#define l_hdat sizeof(HEAD_DATAB)


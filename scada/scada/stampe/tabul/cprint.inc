/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
        il file decpr.inc contiene tutti i codici
        relativi agli argomenti dell'istruzione print

        p_xxxxxx        definiscono i codici operativi
        l_xxxxxx        definiscono la lunghezza delle
                        istruzioni
*/
#define p_pag 	  0x00b
#define l_pag 	  1
#define p_ret 	  0x00c
#define l_ret 	  1
#define p_tim1 	  0x00d
#define l_tim1    1
#define p_tim2    0x00e
#define l_tim2    1
#define p_spaces  0x00f
#define l_spaces  2
#define p_cod 	  0x010
#define l_cod     2
#define p_desc    0x011
#define l_desc    2

#define p_umis    0x012
#define l_umis    2
#define p_org     0x013
#define l_org     2
#define p_stringa 0x014
#define p_format  0x015
#define l_format  3
#define p_dl      0x016
#define l_dl      2
#define p_sgraf   0x017
#define l_sgraf   3
#define p_graf    0x018
#define n_graf    6       /* n. max. misure per graf      */

/*
	DEFINE dei tipi di variabili di data base locale
*/
#define tanalogico 0
#define tdigitale  1
#define torgano    2
#define treale     3
#define tintero    4
#define tlogico    5
#define tdig_out   6
#define tstringa   7
#define tpuntan    9
#define tpuntdi   10
#define tpuntor   11

/*
        definizione dei format in parallelo al codice
        di decodifica
*/
typedef struct { unsigned char fraz:4;
	         unsigned char tot:4;
	 } REALE;
typedef union {	 unsigned char in;
		 REALE 	 re;
	      } SPEC_FORM;
pub struct formato {
		SPEC_FORM f;
		unsigned char tipo;
		 }*pform;

/*   Esempi di specifica formato

     Per tipo reale o analogico ( pform->tipo==reale ) 
            pform->f.re.mm
	    pform->f.re.nn

     Per tipo intero, organo o stringa (pform->tipo== ...)
	    pform->f.in
*/


#define  pl_umis 8      /* lunghezza unita' di misura */
#define  po_nome 0      /*  offset                      */
#define  po_desc SCD_SIGLA     /*      su files                */
#define  po_umis (SCD_SIGLA+SCD_DESCRIZIONE)   /*        descrittori        */
/*
	Tabelle di svincolo tipo di punto in data base di sistema 
	- offset nel file dei descrittori e dimensione dei record
*/ 
extern short nbyte[];		
extern long off_f[];		

pub short numgrafv;    // numero di variabili da visualizzare nel grafico     

pub struct dosdate_t oggi;
pub struct dostime_t adesso;

#define lstr_tempo 12	     // lunghezza stringa di stampa per 
			     // data o per ora.
#define lstr_ret 2              // lunghezza stringa di stampa per CR + LF
#define lstr_pag 2              // lunghezza stringa di stampa per CR + LF
#define l_riga 100
pub short lunprint;    // numero di caratteri da stampare
pub short diff;

pub struct s_tabul { HEA_STA	hea;
		 char 		strprint[l_riga]; } ta;


typedef struct s_dire  {        
                          unsigned byad  :11;
                          unsigned biad  :3;
                          unsigned indi  :1;
			  unsigned spare :1;  } S_DIRE ;

typedef struct s_indi  {  
                          unsigned byad  :8; 
                          unsigned disp  :6;
                          unsigned indi  :1;
		          unsigned spare :1;  } S_INDI ;

typedef struct s_indd  {        
                          unsigned byad  :8;
                          unsigned biad  :3;
                          unsigned disp  :3;
                          unsigned indi  :1;
		          unsigned spare :1;  } S_INDD ;

#define b_organo 2
#define b_reale  3
#define b_stringa 4
#define b_analogico 0
#define b_intero 1

pub float coeff_add;   // coefficiente additivo utilizzato dalla GRAF
pub float coeff_mol;   // coefficiente moltiplicativo utilizzato dalla GRAF


pub union u_indirizzi      {        S_INDD dd ;     /* indiret. bit */
                                S_INDI di ;     /* indiretto    */
                                S_DIRE re ;     /* diretto      */
                                short  s;
                        } i ;             /* indirizzi    */
pub union u_val {   float   f;
                long    l ;
                short   s[2];
                char   c[6] ;} u  ;


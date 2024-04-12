/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#include "defpub.h"
/*
        arctab.inc

        File di include per le strutture utilizzate nella stampa
        di un tabulato di archivio

        20 Marzo 1992   Rel. 1.0 Fc
*/ 
#include <all_1.h>
#include <tag.h>
#undef long 
#define long int

/*
        intestazione data e n. pagina
*/
typedef struct inarc_1  {  
                         HEA_STA hea;
			 char blank_1[10];  
                         char data[8];
                         char blank_2[90] ;
                         char page[4] ;
                         char blank_3[2];
                         char num[4];
                         short new;
                         short eos;
                       } INARC_1;
/*
        intestazione n. archivio in stampa
*/
				   
typedef struct inarc_2        {
                       HEA_STA hea;
		       char blank_1[30];
                       char titolo[11];
		       char indice[2];
		       char blank_2[7];
		       char titolo_2[14];
		       char ora[8];
                       char blank_3[48];
                       short new;
                       short eos; } INARC_2;
/*
        desrizione misura inserita nell'archivio
*/
typedef struct rigaint {
                HEA_STA hea;
		char blank_0[3];
		char progr[2];
		char blank_1[3];
		char nome[SCD_SIGLA];
		char blank_2[3];
		char descr[SCD_DESCRIZIONE];
		char blank_3[3];
		char umis[SCD_UNIMIS];
		char blank_4[3];
		char stat1[SCD_STATO];
		short new;
	       } RIGAINT;

#define n_misst 9                        // numero di misure alla volta nel tabulato
/*
        riga di intestazione dati
*/
typedef struct rigTag {
                       HEA_STA hea;
		       char blank1[21];
		       char nome[n_misst][SCD_SIGLA+1];
		       short new;
		       } RIGTAG;
/*
        riga valori con data
*/
typedef struct rigval {
                      HEA_STA hea;
		      char date[7];
		      char ore[8];
		      char blank1[2];
		      char valori[n_misst][SCD_SIGLA+1];
		      short new;
		      } RIGVAL;


pub struct   {  HEA_STA hea;                           // from feed 
            short   val; } arcontrol;              // newline e fine

pub struct   {  HEA_STA hea;                       
            char    errore[80];} arcerr;       

pub RIGAINT righeint[n_misst];
pub INARC_1  intarc_1 ;
pub INARC_2  intarc_2 ;
pub RIGTAG rtag;
pub RIGVAL rval;
/*
        definizione codici messaggiutilizzati da arctabini.c
*/
#define minit   1               // inizializzare buffer
#define msigle  2               // scrittura descrizioni misure o

#include <all_16.h>
#undef long 
#define long long

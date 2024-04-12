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
   modulo VarEdit.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)VarEdit.h	5.1
*/
#ifndef VAREDIT
#define VAREDIT

#define SU	1  /*  Direzione di ricerca verso l'alto  */
#define GIU	2  /*  Direzione di ricerca verso il basso  */

#define MODELLI		5  /*  Selezione lista dei modelli  */
#define VARIABILI	6  /*  Selezione lista delle variabili  */
#define GENERALE	7  /*  Selezione lista moduli o blocchi */

#define ALL		10 /*  Selezione dall'option menu di una ricerca
				totale delle informazioni   */
#define COMPONENT	11 /*  Selezione dall'option menu di una ricerca
				filtrata attraverso il componente  */
#define SUBSYSTEM	12 /*  Selezione dall'option menu di una ricerca
				filtrata attraverso il sotto sistema */

#define XlDVarXO  "Input Variable"    /* Etichetta per variabile di input */
#define XlDVarXA  "Output Variable"   /* Etichetta per variabile di output */

/******************************************
  Definizione del tipo di struttura usata per la descrizione del
        tipo di variabile, le unita' di misura ammesse e i coefficienti
        per le trasformazioni da una unita' di misura ad un'altra
******************************************/

#define NUMERO_TIPI_UMIS 5
#define LUNGHEZZA_NOMI_UMIS 7
#define LUNGHEZZA_COEFFICIENTI 30

typedef struct selezione_uni_mis {
           char *codice; /* tipo della misura per esteso */
           char type;      /* iniziale variabile lego per individuazione
                              unita' di misura  */
           int sel;        /* indice unita' di misura selezionata */
           char *codm[NUMERO_TIPI_UMIS];
                        /* nomi delle unita' di misura selezionabili */
           char *A[NUMERO_TIPI_UMIS];
           char *B[NUMERO_TIPI_UMIS];
           } SELEZIONE_UNI_MIS;

#endif

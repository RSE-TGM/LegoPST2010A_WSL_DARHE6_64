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
   modulo uni_mis.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)uni_mis.h	5.1
*/
/*
 uni_mis.h
  contiene le informazioni relative alle unita' di misura utilizzate
*/

#define N_TIPI_UMIS 5
#define L_NOMI_UMIS 7

typedef struct s_uni_mis {
           char codice[9]; /* tipo della misura per esteso */
           char type;      /* iniziale variabile lego per individuazione
                              unita' di misura  */
           int sel;        /* indice unita' di misura selezionata */
           char codm[N_TIPI_UMIS][L_NOMI_UMIS]; /* nomi delle unita' di misura 
                                         selezionabili */
           float A[N_TIPI_UMIS];
           float B[N_TIPI_UMIS];
           } S_UNI_MIS;

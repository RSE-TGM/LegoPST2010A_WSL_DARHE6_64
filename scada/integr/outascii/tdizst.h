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
  -> tdizst.h

  Contiene la definizione della tabella
  operativa del dizionario degli stati 
  degli organi.

  Creazione: 28/3/1996
  Autori: M. De Chirico & E. Locatelli
*/

typedef struct s_tdizst {
char Stato[DB_StatoOrg];
int codice;
} TDIZST;

#ifndef h_tdizst_h
#define h_tdizst_h

STRUCT_TABLE tdizst[]={
        {"Stato",TIPO_CHAR,0,""},
        {"codice",TIPO_INT,0,""},
	};

#define NUM_RECORD_TDIZST sizeof(tdizst)/sizeof(STRUCT_TABLE)
#endif


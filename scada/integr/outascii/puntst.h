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
        -> puntst.h

        Contiene la definizione della tabella
        operativa dei punti ST.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_puntst {
char Sigla[DB_Sigla];
char Descrizione[DB_Descrizione];
char Valore[DB_ValoreSTR];
int Zonaimpianto;
int Trattamento;
int Severita;
char Note[DB_Note];
int Dainstallare;
char Gerarchia[DB_Gerarchia];
} PUNTST;

#ifndef h_puntst_h
#define h_puntst_h

STRUCT_TABLE editst[]={
        {"Sigla",          TIPO_CHAR,0,     "" },
        {"Descrizione",    TIPO_CHAR,0,     ""},
        {"Valore",  TIPO_CHAR,0,     "" },
        {"Zonaimpianto",   TIPO_INT,      0  ,""},
        {"Trattamento",    TIPO_INT,      0 ,""},
        {"Severita",       TIPO_INT,      0   ,""},
        {"Note",           TIPO_CHAR,0,     "" },
        {"Dainstallare", TIPO_BOOLEAN,0,"No"},
        {"Gerarchia",      TIPO_CHAR,0,     ""  }
	};

#define NUM_CAMPI_EDITST sizeof(editst)/sizeof(STRUCT_TABLE)

#endif

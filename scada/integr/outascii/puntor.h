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
        -> puntor.h

        Contiene la definizione della tabella
        operativa dei punti OR.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_puntor {
char Sigla [DB_Sigla];
char Descrizione[DB_Descrizione];
int Zonaimpianto;
int Timeout;
char Tipo[DB_TipoOrg];
char SCont1[DB_Sigla];
char SCont2[DB_Sigla];
char SCont3[DB_Sigla];
char SCont4[DB_Sigla];
char SCont5[DB_Sigla];
char STProt[DB_STProt];
int Inibente;
char StatoI[DB_StatoOrg];
char TagPP1[DB_Sigla]; 
char TagPP2[DB_Sigla];
int TInibiz;
int Trattamento;
int Severita;
char Note[DB_Note];
int Dainstallare;
char Gerarchia[DB_Gerarchia];
} PUNTOR;

#ifndef h_puntor_h
#define h_puntor_h

STRUCT_TABLE editor[]={
        {"Sigla",          TIPO_CHAR,0,     "" },
        {"Descrizione",    TIPO_CHAR,0,     ""},
        {"Zonaimpianto",   TIPO_INT,      0  ,""},
        {"Timeout",   TIPO_INT,      0  ,""},
        {"Tipo",          TIPO_CHAR,0,     ""},
        {"SCont1",          TIPO_CHAR,0,     ""  },
        {"SCont2",          TIPO_CHAR,0,     ""  },
        {"SCont3",          TIPO_CHAR,0,     ""  },
        {"SCont4",          TIPO_CHAR,0,     ""  },
        {"SCont5",          TIPO_CHAR,0,     ""  },
        {"STProt",          TIPO_CHAR,0,     "" },
        {"Inibente",     TIPO_INT,      0  ,""},
        {"StatoI",          TIPO_CHAR,0,     "" },
        {"TagPP1",          TIPO_CHAR,0,     "" },
        {"TagPP2",          TIPO_CHAR,0,     "" },
        {"TInibiz",    TIPO_INT,      0 ,""},
        {"Trattamento",    TIPO_INT,      0 ,""},
        {"Severita",       TIPO_INT,      0   ,""},
        {"Note",           TIPO_CHAR,0,     "" },
        {"Dainstallare", TIPO_BOOLEAN,0,"No"},
        {"Gerarchia",      TIPO_CHAR,0,     ""  }
	};

#define NUM_CAMPI_EDITOR sizeof(editor)/sizeof(STRUCT_TABLE)

#endif

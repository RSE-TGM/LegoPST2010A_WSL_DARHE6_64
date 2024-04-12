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
        -> puntto.h

        Contiene la definizione della tabella
        operativa dei tipi di organo.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_puntto {
char Text[DB_Text];
int codice;
char Descrizione[DB_Descrizione];
int NumSegC;
char DescrSeg1[DB_Descrizione];
char DescrSeg2[DB_Descrizione];
char DescrSeg3[DB_Descrizione];
char DescrSeg4[DB_Descrizione];
char DescrSeg5[DB_Descrizione];
char Stato1[DB_StatoOrg];
char Stato2[DB_StatoOrg];
char Stato3[DB_StatoOrg];
char Stato4[DB_StatoOrg];
char Stato5[DB_StatoOrg];
char Stato6[DB_StatoOrg];
char Stato7[DB_StatoOrg];
char Stato8[DB_StatoOrg];
char Stato9[DB_StatoOrg];
char Stato10[DB_StatoOrg];
char Stato11[DB_StatoOrg];
char Stato12[DB_StatoOrg];
char Stato13[DB_StatoOrg];
char Stato14[DB_StatoOrg];
char Stato15[DB_StatoOrg];
char Stato16[DB_StatoOrg];
char Stato17[DB_StatoOrg];
char Stato18[DB_StatoOrg];
char Stato19[DB_StatoOrg];
char Stato20[DB_StatoOrg];
char Stato21[DB_StatoOrg];
char Stato22[DB_StatoOrg];
char Stato23[DB_StatoOrg];
char Stato24[DB_StatoOrg];
char Stato25[DB_StatoOrg];
char Stato26[DB_StatoOrg];
char Stato27[DB_StatoOrg];
char Stato28[DB_StatoOrg];
char Stato29[DB_StatoOrg];
char Stato30[DB_StatoOrg];
char Stato31[DB_StatoOrg];
char Stato32[DB_StatoOrg];
} PUNTTO;

#ifndef h_puntto_h
#define h_puntto_h

STRUCT_TABLE editto[]={
        {"TipoO",          TIPO_CHAR,0,     "" },
        {"codice",         TIPO_INT,      0 ,""},
        {"Descrizione",     TIPO_CHAR,0,    "OSF1"},
        {"NumSegC",       TIPO_INT,      0  ,""},
        {"DescrSeg1",    TIPO_CHAR,0,     "" },
        {"DescrSeg2",    TIPO_CHAR,0,     "" },
        {"DescrSeg3",    TIPO_CHAR,0,     "" },
        {"DescrSeg4",    TIPO_CHAR,0,     "" },
        {"DescrSeg5",    TIPO_CHAR,0,     "" },
        {"Stato1",    TIPO_CHAR,0,    "Cont"},
        {"Stato2",    TIPO_CHAR,0,    "Cont"},
        {"Stato3",    TIPO_CHAR,0,    "Cont"},
        {"Stato4",    TIPO_CHAR,0,    "Cont"},
        {"Stato5",    TIPO_CHAR,0,    "Cont"},
        {"Stato6",    TIPO_CHAR,0,    "Cont"},
        {"Stato7",    TIPO_CHAR,0,    "Cont"},
        {"Stato8",    TIPO_CHAR,0,    "Cont"},
        {"Stato9",    TIPO_CHAR,0,    "Cont"},
        {"Stato10",    TIPO_CHAR,0,    "Cont"},
        {"Stato11",    TIPO_CHAR,0,    "Cont"},
        {"Stato12",    TIPO_CHAR,0,    "Cont"},
        {"Stato13",    TIPO_CHAR,0,    "Cont"},
        {"Stato14",    TIPO_CHAR,0,    "Cont"},
        {"Stato15",    TIPO_CHAR,0,    "Cont"},
        {"Stato16",    TIPO_CHAR,0,    "Cont"},
        {"Stato17",    TIPO_CHAR,0,    "Cont"},
        {"Stato18",    TIPO_CHAR,0,    "Cont"},
        {"Stato19",    TIPO_CHAR,0,    "Cont"},
        {"Stato20",    TIPO_CHAR,0,    "Cont"},
        {"Stato21",    TIPO_CHAR,0,    "Cont"},
        {"Stato22",    TIPO_CHAR,0,    "Cont"},
        {"Stato23",    TIPO_CHAR,0,    "Cont"},
        {"Stato24",    TIPO_CHAR,0,    "Cont"},
        {"Stato25",    TIPO_CHAR,0,    "Cont"},
        {"Stato26",    TIPO_CHAR,0,    "Cont"},
        {"Stato27",    TIPO_CHAR,0,    "Cont"},
        {"Stato28",    TIPO_CHAR,0,    "Cont"},
        {"Stato29",    TIPO_CHAR,0,    "Cont"},
        {"Stato30",    TIPO_CHAR,0,    "Cont"},
        {"Stato31",    TIPO_CHAR,0,    "Cont"},
        {"Stato32",    TIPO_CHAR,0,    "Cont"},
	};

#define NUM_CAMPI_EDITTO sizeof(editto)/sizeof(STRUCT_TABLE)

#endif

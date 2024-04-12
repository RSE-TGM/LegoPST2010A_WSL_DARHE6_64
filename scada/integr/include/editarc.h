/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef h_editarc_h
#define h_editarc_h


STRUCT_TABLE editarc[]={
        {"Indice",          TIPO_INT,0,     "" },
        {"Descrizione",    TIPO_CHAR,0,     ""},
        {"Tipo",   TIPO_INT,      0  ,""},
        {"PeriodoL",   TIPO_INT,      0  ,""},
        {"Durata",   TIPO_INT,      0  ,""},
        {"NumeroFile",   TIPO_INT,      0  ,""},
        {"TriggerA",   TIPO_INT,      0  ,""},
        {"TriggerD",   TIPO_INT,      0  ,""},
        {"TotPar",   TIPO_INT,      0  ,""},
        {"DatiVet",   TIPO_INT,      0  ,""},
        {"Campione01",    TIPO_CHAR,0,     ""},
        {"Campione02",    TIPO_CHAR,0,     ""},
        {"Campione03",    TIPO_CHAR,0,     ""},
        {"Campione04",    TIPO_CHAR,0,     ""},
        {"Campione05",    TIPO_CHAR,0,     ""},
        {"Campione06",    TIPO_CHAR,0,     ""},
        {"Campione07",    TIPO_CHAR,0,     ""},
        {"Campione08",    TIPO_CHAR,0,     ""},
        {"Campione09",    TIPO_CHAR,0,     ""},
        {"Campione10",    TIPO_CHAR,0,     ""},
        {"Campione11",    TIPO_CHAR,0,     ""},
        {"Campione12",    TIPO_CHAR,0,     ""},
        {"Campione13",    TIPO_CHAR,0,     ""},
        {"Campione14",    TIPO_CHAR,0,     ""},
        {"Campione15",    TIPO_CHAR,0,     ""},
        {"Campione16",    TIPO_CHAR,0,     ""},
        {"Campione17",    TIPO_CHAR,0,     ""},
        {"Campione18",    TIPO_CHAR,0,     ""},
        {"Campione19",    TIPO_CHAR,0,     ""},
        {"Campione20",    TIPO_CHAR,0,     ""},
        {"Campione21",    TIPO_CHAR,0,     ""},
        {"Campione22",    TIPO_CHAR,0,     ""},
        {"Campione23",    TIPO_CHAR,0,     ""},
        {"Campione24",    TIPO_CHAR,0,     ""},
        {"Campione25",    TIPO_CHAR,0,     ""},
        {"Campione26",    TIPO_CHAR,0,     ""},
        {"Campione27",    TIPO_CHAR,0,     ""},
        {"Campione28",    TIPO_CHAR,0,     ""},
        {"Campione29",    TIPO_CHAR,0,     ""},
        {"Campione30",    TIPO_CHAR,0,     ""},
        {"Campione31",    TIPO_CHAR,0,     ""},
        {"Campione32",    TIPO_CHAR,0,     ""},
        {"Campione33",    TIPO_CHAR,0,     ""},
        {"Campione34",    TIPO_CHAR,0,     ""},
        {"Campione35",    TIPO_CHAR,0,     ""},
        {"Campione36",    TIPO_CHAR,0,     ""},
        {"Campione37",    TIPO_CHAR,0,     ""},
        {"Campione38",    TIPO_CHAR,0,     ""},
        {"Campione39",    TIPO_CHAR,0,     ""},
        {"Campione40",    TIPO_CHAR,0,     ""},
        {"Campione41",    TIPO_CHAR,0,     ""},
        {"Campione42",    TIPO_CHAR,0,     ""},
        {"Campione43",    TIPO_CHAR,0,     ""},
        {"Campione44",    TIPO_CHAR,0,     ""},
        {"Campione45",    TIPO_CHAR,0,     ""},
        {"Campione46",    TIPO_CHAR,0,     ""},
        {"Campione47",    TIPO_CHAR,0,     ""},
        {"Campione48",    TIPO_CHAR,0,     ""},
        {"Campione49",    TIPO_CHAR,0,     ""},
        {"Campione50",    TIPO_CHAR,0,     ""},
        {"Campione51",    TIPO_CHAR,0,     ""},
        {"Campione52",    TIPO_CHAR,0,     ""},
        {"Campione53",    TIPO_CHAR,0,     ""},
        {"Campione54",    TIPO_CHAR,0,     ""},
        {"Campione55",    TIPO_CHAR,0,     ""},
        {"Campione56",    TIPO_CHAR,0,     ""},
        {"Campione57",    TIPO_CHAR,0,     ""},
        {"Campione58",    TIPO_CHAR,0,     ""},
        {"Campione59",    TIPO_CHAR,0,     ""},
        {"Campione60",    TIPO_CHAR,0,     ""},
        {"Campione61",    TIPO_CHAR,0,     ""},
        {"Campione62",    TIPO_CHAR,0,     ""},
        {"Campione63",    TIPO_CHAR,0,     ""},
        {"Campione64",    TIPO_CHAR,0,     ""},
        {"Campione65",    TIPO_CHAR,0,     ""},
        {"Campione66",    TIPO_CHAR,0,     ""},
        {"Campione67",    TIPO_CHAR,0,     ""},
        {"Campione68",    TIPO_CHAR,0,     ""},
        {"Campione69",    TIPO_CHAR,0,     ""},
        {"Campione70",    TIPO_CHAR,0,     ""},
        {"Campione71",    TIPO_CHAR,0,     ""},
        {"Campione72",    TIPO_CHAR,0,     ""},
        {"Campione73",    TIPO_CHAR,0,     ""},
        {"Campione74",    TIPO_CHAR,0,     ""},
        {"Campione75",    TIPO_CHAR,0,     ""},
        {"Campione76",    TIPO_CHAR,0,     ""},
        {"Campione77",    TIPO_CHAR,0,     ""},
        {"Campione78",    TIPO_CHAR,0,     ""},
        {"Campione79",    TIPO_CHAR,0,     ""},
        {"Campione80",    TIPO_CHAR,0,     ""},
        {"Campione81",    TIPO_CHAR,0,     ""},
        {"Campione82",    TIPO_CHAR,0,     ""},
        {"Campione83",    TIPO_CHAR,0,     ""}
	};

#define NUM_CAMPI_EDITARC sizeof(editarc)/sizeof(STRUCT_TABLE)

typedef struct s_editarc{
        int Indice;
        char Descrizione[SCD_DESCRIZIONE+1];
        int Tipo;
        int PeriodoL;
        int Durata;
        int NumeroFile;
        int TriggerA;
        int Trigger;
        int TotPar;
        int DatiVet;
        char Campione[n_misarc][SCD_SIGLA+1];
	} S_EDITARC;

#endif

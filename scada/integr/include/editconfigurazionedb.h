/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef h_editconfigurazionedb_h
#define h_editconfigurazionedb_h

#define DB_NOMEIMPIANTO "Puerto"
#define DB_TIPO         "SIMU"
#define DB_DESCRIZIONE  "Puerto"
#define DB_SUBUTEN      "Puerto"
#define DB_DIMAA        9600
#define DB_DIMAS        9600
#define DB_DIMAC        9600
#define DB_DIMAD        2048
#define DB_DIMAO        9600
#define DB_DIMDA        9600
#define DB_DIMDS        9600
#define DB_DIMDC        9600
#define DB_DIMDD        2048
#define DB_DIMDO        9600
#define DB_ORGANI	0
#define DB_STRINGHE	0

STRUCT_TABLE editconfigurazionedb[]={
        {"NomeImpianto",          TIPO_CHAR,0,     DB_NOMEIMPIANTO },
        {"Tipo",          TIPO_CHAR,0,     DB_TIPO },
        {"Descrizione",          TIPO_CHAR,0,     DB_DESCRIZIONE },
        {"subuten",          TIPO_CHAR,0,     DB_SUBUTEN },
        {"DimAA",          TIPO_INT,DB_DIMAA,     "" },
        {"DimAS",          TIPO_INT,DB_DIMAS,     "" },
        {"DimAC",          TIPO_INT,DB_DIMAC,     "" },
        {"DimAD",          TIPO_INT,DB_DIMAD,     "" },
        {"DimAO",          TIPO_INT,DB_DIMAO,     "" },
        {"DimDA",          TIPO_INT,DB_DIMDA,     "" },
        {"DimDS",          TIPO_INT,DB_DIMDS,     "" },
        {"DimDC",          TIPO_INT,DB_DIMDC,     "" },
        {"DimDD",          TIPO_INT,DB_DIMDD,     "" },
        {"DimDO",          TIPO_INT,DB_DIMDO,     "" },
        {"Organi",          TIPO_INT,DB_ORGANI,     "" },
        {"Stringhe",          TIPO_INT,DB_STRINGHE,     "" },
	};

#define NUM_CAMPI_EDITCONFIGURAZIONEDB sizeof(editconfigurazionedb)/sizeof(STRUCT_TABLE)

#endif

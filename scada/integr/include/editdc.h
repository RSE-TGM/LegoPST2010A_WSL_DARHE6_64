/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef h_editdc_h
#define h_editdc_h


STRUCT_TABLE editdc[]={
        {"Sigla",          TIPO_CHAR,0,     "" },
        {"Descrizione",    TIPO_CHAR,0,     ""},
        {"Stato0",    TIPO_CHAR,0,     "" },
        {"Stato1",    TIPO_CHAR,0,     "" },
        {"TagPP1",    TIPO_CHAR,0,     "" },
        {"TagPP2",    TIPO_CHAR,0,     "" },
        {"TInib",    TIPO_CHAR,0,     "" },
        {"Zonaimpianto",   TIPO_INT,      0  ,""},
        {"Trattamento",    TIPO_INT,      0 ,""},
        {"Severita",       TIPO_INT,      0   ,""},
        {"Note",           TIPO_CHAR,0,     "" },
        {"Dainstallare", TIPO_BOOLEAN,0,"No"},
        {"Gerarchia",      TIPO_CHAR,0,     ""  }
	};

#define NUM_CAMPI_EDITDC sizeof(editdc)/sizeof(STRUCT_TABLE)

#endif

/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef h_editor_h
#define h_editor_h


STRUCT_TABLE editor[]={
        {"Sigla",          TIPO_CHAR,0,     "" },
        {"Descrizione",    TIPO_CHAR,0,     ""},
        {"Zonaimpianto",   TIPO_INT,      0  ,""},
        {"Timeout",   TIPO_INT,      0  ,""},
        {"Tipo",  TIPO_CHAR,0,     "" },
        {"SCont1",  TIPO_CHAR,0,     "" },
        {"SCont2",  TIPO_CHAR,0,     "" },
        {"SCont3",  TIPO_CHAR,0,     "" },
        {"SCont4",  TIPO_CHAR,0,     "" },
        {"SCont5",  TIPO_CHAR,0,     "" },
        {"STProt",  TIPO_CHAR,0,     "" },
        {"Inibente",   TIPO_INT,      0  ,""},
        {"TagPP1",    TIPO_CHAR,0,     "" },
        {"TagPP2",    TIPO_CHAR,0,     "" },
        {"TInibiz",    TIPO_CHAR,0,     "" },
        {"Trattamento",    TIPO_INT,      0 ,""},
        {"Severita",       TIPO_INT,      0   ,""},
        {"Note",           TIPO_CHAR,0,     "" },
        {"Dainstallare", TIPO_BOOLEAN,0,"No"},
        {"Gerarchia",      TIPO_CHAR,0,     ""  }
	};

#define NUM_CAMPI_EDITOR sizeof(editor)/sizeof(STRUCT_TABLE)

#endif

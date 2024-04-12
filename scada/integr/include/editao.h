/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef h_editao_h
#define h_editao_h


STRUCT_TABLE editao[]={
        {"Sigla",          TIPO_CHAR,0,     "" },
        {"Descrizione",    TIPO_CHAR,0,     ""},
        {"Morsetticampo",  TIPO_CHAR,0,     "" },
        {"cavo",           TIPO_CHAR,0,     ""},
        {"Morsettisistema",  TIPO_CHAR,0,     ""},
        {"TipoPeriferica",  TIPO_CHAR,0,     "SIMU"},
        {"IDperi",         TIPO_INT,      0 ,""},
        {"Nomescheda",     TIPO_CHAR,0,    "OSF1"},
        {"IDscheda",       TIPO_INT,      0  ,""},
        {"IDpunto",        TIPO_INT,      0 ,""},
        {"Unitamisura",    TIPO_CHAR,0,     "" },
        {"TipoSegnale",    TIPO_CHAR,0,    "Cont"},
        {"CSbasso",        TIPO_INT,      0,""},
        {"CSalto",         TIPO_INT,      0 ,""},
        {"FSbasso",        TIPO_INT,      0,""},
        {"FSalto",         TIPO_INT,      0,""},
        {"Coeffiltro",     TIPO_INT,      0,""},
        {"LimiteFiltro",   TIPO_INT,      0,""},
        {"Zonaimpianto",   TIPO_INT,      0  ,""},
        {"Note",           TIPO_CHAR,0,     "" },
        {"Dainstallare", TIPO_BOOLEAN,0,"No"},
        {"SiglaSim",       TIPO_CHAR,0,     "" },
        {"InStampa",         TIPO_INT,      0,""},
        {"Gerarchia",      TIPO_CHAR,0,     ""  }
	};

#define NUM_CAMPI_EDITAO sizeof(editao)/sizeof(STRUCT_TABLE)

#endif

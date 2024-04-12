/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef h_editaa_h
#define h_editaa_h


STRUCT_TABLE editaa[]={
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
        {"Periodo",        TIPO_INT,      0  ,""  },
        {"TipoSegnale",    TIPO_CHAR,0,    "Cont"},
        {"CSbasso",        TIPO_INT,      0,""},
        {"CSalto",         TIPO_INT,      0 ,""},
        {"IdAttendibile",  TIPO_INT,      0,""},
        {"CoeffGV",        TIPO_INT,      0,""},
        {"TipoConversione",  TIPO_CHAR,0,     "NL"},
        {"FSbasso",        TIPO_INT,      0,""},
        {"FSalto",         TIPO_INT,      0,""},
        {"Coeff0",         TIPO_INT,      0 ,""},
        {"Coeff1",         TIPO_INT,      0,""},
        {"Coeff2",         TIPO_INT,      0,""},
        {"Coeff3",         TIPO_INT,      0,""},
        {"Coeff4",         TIPO_INT,      0,""},
        {"GiuntoFreddo",   TIPO_CHAR,0,     ""},
        {"Coeffiltro",     TIPO_INT,      0,""},
        {"Limite0",        TIPO_INT,      0,""},
        {"Zonaimpianto",   TIPO_INT,      0  ,""},
        {"LalBC",          TIPO_CHAR,0,     ""},
        {"LalBS",          TIPO_CHAR,0,     ""  },
        {"LalAC",          TIPO_CHAR,0,     "" },
        {"LalAS",          TIPO_CHAR,0,     ""},
        {"BandaMorta",     TIPO_INT,      0  ,""},
        {"Trattamento",    TIPO_INT,      0 ,""},
        {"Severita",       TIPO_INT,      0   ,""},
        {"Note",           TIPO_CHAR,0,     "" },
        {"Dainstallare", TIPO_BOOLEAN,0,"No"},
        {"SiglaSim",       TIPO_CHAR,0,     "" },
        {"Gerarchia",      TIPO_CHAR,0,     ""  }
	};

#define NUM_CAMPI_EDITAA sizeof(editaa)/sizeof(STRUCT_TABLE)

#endif

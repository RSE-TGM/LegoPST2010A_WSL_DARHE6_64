/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef h_editac_h
#define h_editac_h


STRUCT_TABLE editac[]={
        {"Sigla",          TIPO_CHAR,0,     "" },
        {"Descrizione",    TIPO_CHAR,0,     ""},
        {"valoreDB",       TIPO_INT,0,     ""},
        {"Unitamisura",    TIPO_CHAR,0,     "" },
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
        {"Gerarchia",      TIPO_CHAR,0,     ""  }
	};

#define NUM_CAMPI_EDITAC sizeof(editac)/sizeof(STRUCT_TABLE)

#endif

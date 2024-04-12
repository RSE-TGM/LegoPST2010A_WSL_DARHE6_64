/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef h_editas_h
#define h_editas_h


STRUCT_TABLE editas[]={
        {"Sigla",          TIPO_CHAR,0,     "" },
        {"Descrizione",    TIPO_CHAR,0,     ""},
        {"Unitamisura",    TIPO_CHAR,0,     "" },
        {"Periodo",        TIPO_INT,      0  ,""  },
        {"TipoCalc",       TIPO_INT,      0  ,""  },
        {"Contrib1",    TIPO_CHAR,0,     "" },
        {"Contrib2",    TIPO_CHAR,0,     "" },
        {"Contrib3",    TIPO_CHAR,0,     "" },
        {"Contrib4",    TIPO_CHAR,0,     "" },
        {"Contrib5",    TIPO_CHAR,0,     "" },
        {"Contrib6",    TIPO_CHAR,0,     "" },
        {"Contrib7",    TIPO_CHAR,0,     "" },
        {"Contrib8",    TIPO_CHAR,0,     "" },
        {"Freq",        TIPO_INT,      0,""},
        {"Codice",      TIPO_INT,      0,""},
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

#define NUM_CAMPI_EDITAS sizeof(editas)/sizeof(STRUCT_TABLE)
#endif

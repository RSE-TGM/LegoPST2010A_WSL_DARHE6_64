/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef h_editda_h
#define h_editda_h


STRUCT_TABLE editda[]={
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
        {"Contatto",        TIPO_INT,      0 ,""},
        {"Stato0",    TIPO_CHAR,0,     "" },
        {"Stato1",    TIPO_CHAR,0,     "" },
        {"TagPP1",    TIPO_CHAR,0,     "" },
        {"TagPP2",    TIPO_CHAR,0,     "" },
        {"TInib",    TIPO_CHAR,0,     "" },
        {"Zonaimpianto",   TIPO_INT,      0  ,""},
        {"TipoSegnale",    TIPO_INT,      0  ,""},
        {"Trattamento",    TIPO_INT,      0 ,""},
        {"Severita",       TIPO_INT,      0   ,""},
        {"Note",           TIPO_CHAR,0,     "" },
        {"Dainstallare", TIPO_BOOLEAN,0,"No"},
        {"SiglaSim",       TIPO_CHAR,0,     "" },
        {"Gerarchia",      TIPO_CHAR,0,     ""  }
	};

#define NUM_CAMPI_EDITDA sizeof(editda)/sizeof(STRUCT_TABLE)

#endif

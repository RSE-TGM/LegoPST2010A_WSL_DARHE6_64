/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef h_editdo_h
#define h_editdo_h


STRUCT_TABLE editdo[]={
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
        {"IDscheda2",       TIPO_INT,      INT_NODEF  ,""},
        {"IDpunto2",        TIPO_INT,      INT_NODEF ,""},
        {"IDscheda3",       TIPO_INT,      INT_NODEF  ,""},
        {"IDpunto3",        TIPO_INT,      INT_NODEF ,""},
        {"IDscheda4",       TIPO_INT,      INT_NODEF  ,""},
        {"IDpunto4",        TIPO_INT,      INT_NODEF ,""},
        {"Temporizzazione", TIPO_INT,      0 ,""},
        {"Tempo",           TIPO_INT,      0 ,""},
        {"Azione",          TIPO_INT,      0 ,""},
        {"Zonaimpianto",    TIPO_INT,      0  ,""},
        {"TipoCom",         TIPO_INT,      1  ,""},
        {"SiglaOrg",        TIPO_CHAR,0,     "" },
        {"TimeOut",         TIPO_INT,      0  ,""},
        {"StAttuale1",      TIPO_CHAR,0,     "" },
        {"StAtteso1",       TIPO_CHAR,0,     "" },
        {"StAttuale2",      TIPO_CHAR,0,     "" },
        {"StAtteso2",       TIPO_CHAR,0,     "" },
        {"StAttuale3",      TIPO_CHAR,0,     "" },
        {"StAtteso3",       TIPO_CHAR,0,     "" },
        {"StAttuale4",      TIPO_CHAR,0,     "" },
        {"StAtteso4",       TIPO_CHAR,0,     "" },
        {"ComProt", TIPO_BOOLEAN,0,"No"},
        {"Note",           TIPO_CHAR,0,     "" },
        {"InStampa",         TIPO_INT,      0,""},
        {"Dainstallare", TIPO_BOOLEAN,0,"No"},
        {"SiglaSim",       TIPO_CHAR,0,     "" },
        {"Gerarchia",      TIPO_CHAR,0,     ""  }
	};

#define NUM_CAMPI_EDITDO sizeof(editdo)/sizeof(STRUCT_TABLE)

#endif

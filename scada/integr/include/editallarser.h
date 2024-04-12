/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef h_editallarser_h
#define h_editallarser_h


STRUCT_TABLE editallarser[]={
        {"TipoCicalino",          TIPO_INT,99,     "" },
        {"Sev1Cica",          TIPO_INT,0,     "" },
        {"Sev2Cica",          TIPO_INT,0,     "" },
        {"Sev3Cica",          TIPO_INT,0,     "" },
        {"FaMediaT",          TIPO_INT,40,     "" },
        {"FaFiltro",          TIPO_INT,40,     "" },
        {"FaScarto",          TIPO_INT,60,     "" },
        {"FaMediaI",          TIPO_INT,40,     "" },
        {"FaSomma",          TIPO_INT,40,     "" },
        {"FaIntegrale",          TIPO_INT,40,     "" },
        {"freq_ut",          TIPO_INT,1,     "" },
        {"REP_MESS",          TIPO_INT,0,     "" },
        {"REP_RETRY",          TIPO_INT,0,     "" },
	};

#define NUM_CAMPI_EDITALLARSER sizeof(editallarser)/sizeof(STRUCT_TABLE)

#endif

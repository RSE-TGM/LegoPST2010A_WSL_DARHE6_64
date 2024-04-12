/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef h_editallarline_h
#define h_editallarline_h


STRUCT_TABLE editallarline[]={
        {"Indice",          TIPO_INT,0,     "" },
        {"Device",          TIPO_CHAR,0,     "NUL" },
        {"baud",          TIPO_CHAR,0,     "9600" },
        {"data",          TIPO_CHAR,0,     "8" },
        {"stop",          TIPO_CHAR,0,     "1" },
        {"parita",          TIPO_CHAR,0,     "N" },
	};

#define NUM_CAMPI_EDITALLARLINE sizeof(editallarline)/sizeof(STRUCT_TABLE)

#endif

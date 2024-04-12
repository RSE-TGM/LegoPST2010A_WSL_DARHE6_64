/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef h_editDescriSc_h
#define h_editDescriSc_h

STRUCT_TABLE editDescriScnocab[]={
        {"NomeScheda",          TIPO_CHAR,0,     "" },
        {"Codice",   TIPO_INT,      0  ,""},
        {"Descrizione",    TIPO_CHAR,0,     ""},
        {"NumeroAA",   TIPO_INT,      0  ,""},
        {"NumeroAO",   TIPO_INT,      0  ,""},
        {"NumeroDA",   TIPO_INT,      0  ,""},
        {"NumeroDO",   TIPO_INT,      0  ,""},
        };

#define NUM_CAMPI_EDITDESCRISC_NOCAB sizeof(editDescriScnocab)/sizeof(STRUCT_TABLE)

struct struct_table_cab_st
        {
        char *riga;
        };

typedef struct struct_table_cab_st STRUCT_TABLE_CAB;

STRUCT_TABLE_CAB editDescriSc[]={
{"\"NomeScheda\";\"Codice\";\"Descrizione\";\"NumeroAA\";\"NumeroAO\";\"NumeroDA\";\"NumeroDO\""},
{"\"OSF1\";6;\"PROVE SIMUALTORE\";32767;32767;32767;32767"},
	};

#define NUM_RECORD_EDITDESCRISC sizeof(editDescriSc)/sizeof(STRUCT_TABLE_CAB)
#endif

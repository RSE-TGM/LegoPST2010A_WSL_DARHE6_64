/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef h_editTabPeri_h
#define h_editTabPeri_h

STRUCT_TABLE editTabPerinocab[]={
        {"IndStar",          TIPO_INT,0,     "" },
        {"TipoP",    TIPO_INT,0,     ""},
        {"Duale",   TIPO_INT,      0  ,""},
        {"Abilitato",    TIPO_INT,0,     "" },
        };

#define NUM_CAMPI_EDITTABPERI_NOCAB sizeof(editTabPerinocab)/sizeof(STRUCT_TABLE)

struct struct_table_cab_st
        {
        char *riga;
        };

typedef struct struct_table_cab_st STRUCT_TABLE_CAB;

STRUCT_TABLE_CAB editTabPeri[]={
{"\"IndStar\";\"TipoP\";\"Duale\";\"Abilitato\""},
{"0;;1;0"},
	};

#define NUM_RECORD_EDITTABPERI sizeof(editTabPeri)/sizeof(STRUCT_TABLE_CAB)
#endif

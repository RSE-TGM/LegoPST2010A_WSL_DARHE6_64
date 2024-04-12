/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef h_editCPerif_h
#define h_editCPerif_h

STRUCT_TABLE editCPerifnocab[]={
        {"IndStar",          TIPO_INT,0,     "" },
        {"NomeScheda",    TIPO_CHAR,0,     ""},
        {"Quantita",   TIPO_INT,      0  ,""},
        };

#define NUM_CAMPI_EDITCPERIF_NOCAB sizeof(editCPerifnocab)/sizeof(STRUCT_TABLE)

struct struct_table_cab_st
        {
        char *riga;
        };

typedef struct struct_table_cab_st STRUCT_TABLE_CAB;

STRUCT_TABLE_CAB editCPerif[]={
{"\"IndStar\";\"NomeScheda\";\"Quantita\""},
{"0;\"OSF1\";1024"},
	};

#define NUM_RECORD_EDITCPERIF sizeof(editCPerif)/sizeof(STRUCT_TABLE_CAB)
#endif

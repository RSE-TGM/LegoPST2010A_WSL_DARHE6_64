/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef h_editnomi_h
#define h_editnomi_h


STRUCT_TABLE editnomi[]={
        {"Sigla",          TIPO_CHAR,0,     "" },
        {"Tipo",          TIPO_CHAR,0,     "" },
        {"PointDB",          TIPO_INT,0,     "" },
        {"ExtDB",          TIPO_INT,0,     "" },
	};

#define NUM_CAMPI_EDITNOMI sizeof(editnomi)/sizeof(STRUCT_TABLE)

#endif

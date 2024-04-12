/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef h_installa_err_h
#define h_installa_err_h


STRUCT_TABLE installa_err_table[]={
        {"ERR_ID",    TIPO_INT,0,     ""},
        {"ERR_CODE",    TIPO_INT,0,     ""},
        {"ERR_TAG",          TIPO_CHAR,0,     "" },
        {"ERR_DESCRIPTION",    TIPO_CHAR,0,     ""},
	};

#define NUM_CAMPI_INSTALLA_ERR sizeof(installa_err_table)/sizeof(STRUCT_TABLE)

#endif

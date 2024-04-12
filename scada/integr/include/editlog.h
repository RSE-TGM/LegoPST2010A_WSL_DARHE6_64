/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

typedef struct s_tabulati {
char Nome[DB_Nome];
int Periodo;
int Periodico;
int Ciclo;
int attesa;
int Tipo;
} TABULATI;

#ifndef h_tabulati_h
#define h_tabulati_h

STRUCT_TABLE tabulati[]={
        {"Nome",TIPO_CHAR,0,""},
        {"Periodo",TIPO_INT,0,""},
        {"Periodico",TIPO_INT,0,""},
        {"Cicli",TIPO_INT,0,""},
        {"Attesa",TIPO_INT,0,""},
        {"Tipo",TIPO_INT,0,""},
	};

#define NUM_RECORD_TABULATI sizeof(tabulati)/sizeof(STRUCT_TABLE)
#endif


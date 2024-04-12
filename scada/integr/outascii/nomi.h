/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
        -> nomi.h

        Contiene la definizione della tabella
        operativa dei punti DC.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_nomi {
	char Sigla[DB_Sigla_Nomi];
	char Tipo[DB_TipoDb];
	int PointDB;
	int ExtDB;
} NOMI;

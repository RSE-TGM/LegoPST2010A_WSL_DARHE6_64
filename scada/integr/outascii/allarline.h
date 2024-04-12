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
        -> allarline.h

        Contiene la definizione della tabella
        operativa dei punti DC.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_allarline {
	int Indice;
	char Device[DB_Tipo_AllarLine];
	char baud;
	char data;
	char stop;
	char parita;
} ALLARLINE;

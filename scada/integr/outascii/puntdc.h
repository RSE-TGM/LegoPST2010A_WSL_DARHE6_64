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
        -> puntdc.h

        Contiene la definizione della tabella
        operativa dei punti DC.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_puntdc {
char Sigla[DB_Sigla];
char Descrizione[DB_Descrizione];
char Stato0[DB_Stato0];
char Stato1[DB_Stato1];
char TagPP1[DB_Sigla]; 
char TagPP2[DB_Sigla];
int TInib;
int Zonaimpianto;
int Trattamento;
int Severita;
char Note[DB_Note];
int Dainstallare;
char Gerarchia[DB_Gerarchia];
} PUNTDC;

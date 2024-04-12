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
        -> puntac.h

        Contiene la definizione della tabella
        operativa dei punti AC.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_puntac {
char Sigla[DB_Sigla];
char Descrizione[DB_Descrizione];
double valoreDB;
char Unitamisura[DB_Unitamisura];
int Zonaimpianto;
char LalBC[DB_LalBC];
char LalBS[DB_LalBS];
char LalAC[DB_LalAC];
char LalAS[DB_LalAS];
int BandaMorta;
int Trattamento;
int Severita;
char Note[DB_Note];
int Dainstallare;
char Gerarchia[DB_Gerarchia];
} PUNTAC;

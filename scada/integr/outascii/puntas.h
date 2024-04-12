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
        -> puntas.h

        Contiene la definizione della tabella
        operativa dei punti AS.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_puntas {
char Sigla[DB_Sigla];
char Descrizione[DB_Descrizione];
char Unitamisura[DB_Unitamisura];
int Periodo;
int TipoCalc;
char Contrib1[DB_Sigla];
char Contrib2[DB_Sigla];
char Contrib3[DB_Sigla];
char Contrib4[DB_Sigla];
char Contrib5[DB_Sigla];
char Contrib6[DB_Sigla];
char Contrib7[DB_Sigla];
char Contrib8[DB_Sigla];
int Freq;
int Codice;
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
} PUNTAS;

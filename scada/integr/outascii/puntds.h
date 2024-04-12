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
        -> puntds.h

        Contiene la definizione della tabella
        operativa dei punti DS.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/

#define  DB_Stato0DS DB_Stato0-2
typedef struct s_puntds {
char Sigla[DB_Sigla];
char Descrizione[DB_Descrizione];
int TipoCalc;
char SiglaDig1[DB_Sigla];
char SiglaDig2[DB_Sigla];
char SiglaDig3[DB_Sigla];
char SiglaDig4[DB_Sigla];
char Stato0[DB_Stato0DS];
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
} PUNTDS;

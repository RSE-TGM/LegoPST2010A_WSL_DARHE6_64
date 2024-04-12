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
        -> puntao.h

        Contiene la definizione della tabella
        operativa dei punti AO.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_puntao {
char Sigla[DB_Sigla];
char Descrizione[DB_Descrizione];
char Morsetticampo[DB_Morsetticampo];
char cavo[DB_cavo];
char Morsettisistema[DB_Morsettisistema];
char TipoPeriferica[DB_TipoPeriferica];
int IDperi;
char Nomescheda[DB_Nomescheda];
int IDscheda;
int IDpunto;
char Unitamisura[DB_Unitamisura];
char TipoSegnale[DB_TipoSegnale];
int CSbasso;
int CSalto;
double FSbasso;
double FSalto;
double Coeffiltro;
double LimiteFiltro;
int Zonaimpianto;
char Note[DB_Note];
int Dainstallare;
char SiglaSim[DB_SiglaSim];
int InStampa;
char Gerarchia[DB_Gerarchia];
} PUNTAO;

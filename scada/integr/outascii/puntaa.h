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
        -> puntaa.h

        Contiene la definizione della tabella 
	operativa dei punti AA.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_puntaa {
char Sigla [DB_Sigla];
char Descrizione [DB_Descrizione];
char Morsetticampo [DB_Morsetticampo];
char cavo [DB_cavo];
char Morsettisistema [DB_Morsettisistema];
char TipoPeriferica [DB_TipoPeriferica];
int IDperi;
char Nomescheda [DB_Nomescheda];
int IDscheda;
int IDpunto;
char Unitamisura [DB_Unitamisura];
int Periodo;
char TipoSegnale [DB_TipoSegnale];
int CSbasso;
int CSalto;
int IdAttendibile;
int CoeffGV;
char TipoConversione [DB_TipoConversione];
double FSbasso;
double FSalto;
double Coeff0;
double Coeff1;
double Coeff2;
double Coeff3;
double Coeff4;
char GiuntoFreddo [DB_GiuntoFreddo];
double Coeffiltro;
double Limite0;
int Zonaimpianto;
char LalBC [DB_LalBC];
char LalBS [DB_LalBS];
char LalAC [DB_LalAC];
char LalAS [DB_LalAS];
int BandaMorta;
int Trattamento;
int Severita;
char Note[DB_Note];
int Dainstallare;
char SiglaSim [DB_SiglaSim];
char Gerarchia [DB_Gerarchia];
} PUNTAA;

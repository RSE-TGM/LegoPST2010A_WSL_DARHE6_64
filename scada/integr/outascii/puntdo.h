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
        -> puntdo.h

        Contiene la definizione della tabella
        operativa dei punti DO.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_puntdo {
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
int IDscheda2;
int IDpunto2;
int IDscheda3;
int IDpunto3;
int IDscheda4;
int IDpunto4;
int Temporizzazione;
int Tempo;
int Azione;
int Zonaimpianto;
int TipoCom;
char SiglaOrg[DB_Sigla];
int TimeOut;
char StAttuale1[DB_StatoOrg];
char StAtteso1[DB_StatoOrg];
char StAttuale2[DB_StatoOrg];
char StAtteso2[DB_StatoOrg];
char StAttuale3[DB_StatoOrg];
char StAtteso3[DB_StatoOrg];
char StAttuale4[DB_StatoOrg];
char StAtteso4[DB_StatoOrg];
int ComProt;
char Note[DB_Note];
int InStampa;
int Dainstallare;
char SiglaSim[DB_SiglaSim];
char Gerarchia[DB_Gerarchia];
} PUNTDO;

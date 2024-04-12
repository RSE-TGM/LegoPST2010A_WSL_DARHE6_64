/*
   modulo puntda.h
   tipo 
   release 1.2
   data 4/5/96
   reserved @(#)puntda.h	1.2
*/
/*
   modulo puntda.h
   tipo 
   release 1.1
   data 3/28/96
   reserved @(#)puntda.h	1.1
*/
/*
        -> puntda.h

        Contiene la definizione della tabella
        operativa dei punti DA.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_puntda {
char Sigla[DB_Sigla];
char Descrizione[DB_Descrizione];
char Morsetticampo [DB_Morsetticampo];
char cavo [DB_cavo];
char Morsettisistema [DB_Morsettisistema];
char TipoPeriferica [DB_TipoPeriferica];
int IDperi;
char Nomescheda [DB_Nomescheda];
int IDscheda;
int IDpunto;
int Contatto;
char Stato0[DB_Stato0];
char Stato1[DB_Stato1];
char TagPP1[DB_Sigla]; 
char TagPP2[DB_Sigla];
int TInib;
int Zonaimpianto;
char TipoSegnale;
int Trattamento;
int Severita;
char Note[DB_Note];
int Dainstallare;
char SiglaSim [DB_SiglaSim];
char Gerarchia[DB_Gerarchia];
} PUNTDA;

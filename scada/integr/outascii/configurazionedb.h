/*
   modulo configurazionedb.h
   tipo 
   release 1.2
   data 4/5/96
   reserved @(#)configurazionedb.h	1.2
*/
/*
        -> configurazionedb.h

        Contiene la definizione della tabella
        operativa dei punti DC.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_configurazionedb {
	char NomeImpianto[DB_NomeImpianto];
	char Tipo[DB_TipoImpianto];
	char Descrizione[DB_DescrizioneImpianto];
	char subuten[DB_subutenImpianto];
	int DimAA;
	int DimAS;
	int DimAC;
	int DimAD;
	int DimAO;
	int DimDA;
	int DimDS;
	int DimDC;
	int DimDD;
	int DimDO;
	int Organi;
	int Stringhe;
} CONFIGURAZIONEDB;

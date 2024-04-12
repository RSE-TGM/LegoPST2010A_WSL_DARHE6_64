/*
   modulo allarser.h
   tipo 
   release 1.2
   data 4/5/96
   reserved @(#)allarser.h	1.2
*/
/*
        -> allarser.h

        Contiene la definizione della tabella
        operativa dei punti DC.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_allarser {
	int TipoCicalino;
	int Sev1Cica;
	int Sev2Cica;
	int Sev3Cica;
	int FaMediaT;
	int FaFiltro;
	int FaScarto;
	int FaMediaI;
	int FaSomma;
	int FaIntegrale;
	int freq_ut;
	int REP_MESS;
	int REP_RETRY;
} ALLARSER;

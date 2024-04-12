/*
   modulo allarliv.h
   tipo 
   release 1.2
   data 4/5/96
   reserved @(#)allarliv.h	1.2
*/
/*
        -> allarliv.h

        Contiene la definizione della tabella
        operativa dei punti DC.

        Creazione: 28/3/1996
        Autori: M. De Chirico & E. Locatelli
*/
typedef struct s_allarliv {
	int Indice;
	char ColSev1[DB_ColSev];
	char ColSev2[DB_ColSev];
	char ColSev3[DB_ColSev];
	char Emissione[DB_EmRientro];
	char Rientro[DB_EmRientro];
} ALLARLIV;

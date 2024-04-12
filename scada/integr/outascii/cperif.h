/*
   modulo cperif.h
   tipo 
   release 1.2
   data 4/5/96
   reserved @(#)cperif.h	1.2
*/
/*
  -> cperif.h

  Contiene la definizione della tabella
  operativa delle schede di I/O.

  Creazione: 1/4/1996
  Autori: M. De Chirico & E. Locatelli
*/

typedef struct s_cperif {
int IndStar;
char NomeScheda[DB_NomeScheda];
int Quantita;
} CPERIF;

#ifndef h_cperif_h
#define h_cperif_h

STRUCT_TABLE cperif[]={
        {"IndStar",TIPO_INT,0,""},
        {"NomeScheda",TIPO_CHAR,0,""},
        {"Quantita",TIPO_INT,0,""},
	};

#define NUM_RECORD_CPERIF sizeof(cperif)/sizeof(STRUCT_TABLE)
#endif


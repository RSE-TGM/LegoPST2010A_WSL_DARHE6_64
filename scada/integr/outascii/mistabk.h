/*
   modulo mistabk.h
   tipo 
   release 1.3
   data 4/5/96
   reserved @(#)mistabk.h	1.3
*/
/*
  -> mistabk.h

  Contiene la definizione della tabella
  operativa per le definizioni dei 
  coefficienti K.

  Creazione: 29/3/1996
  Autori: M. De Chirico & E. Locatelli
*/

typedef struct s_mistabk {
int Indice;
double Coeff;
} MISTABK;

#ifndef h_mistabk_h
#define h_mistabk_h

STRUCT_TABLE mistabk[]={
        {"Indice",TIPO_INT,0,""},
        {"Coeff",TIPO_FLOAT,0,""},
	};

#define NUM_CAMPI_MISTABK sizeof(mistabk)/sizeof(STRUCT_TABLE)
#endif


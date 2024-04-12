/*
   modulo prfloop.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)prfloop.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <osf1.h>
#include <stdio.h>
#include <malloc.h>

#include "chascii.inc"

#include "tipi.h"

#define LUNGSTR      70

extern int trbrloop[];
extern int contif;
extern int contloop;
extern int nword_o;
extern int cont_label;
extern int fdint;
extern int righeint;

extern int stackif[MAXIF][5];

struct etichette *listlabel();


/*********************************************************************
*          							                                       *
*			Procedura prfloop  			                                 *
*          							                                       *
*********************************************************************/

prfloop()

{

char intlinea[LUNGSTR];
int j=0;

sbianca(intlinea,LUNGSTR-1);

if ( (contloop == 0 ) || ( stackif[contif -1][0] == -1) ) {

/* Trovo ENDLOOP non preceduta dall'istruzione LOOP */

	stampa_err(67,1,"ENDLOOP");

}

else {

/* Trovata istruzione di chiusura ENDLOOP */

  stackif[contif-1][4]=-1; /* fine LOOP */

  j=sprintf(intlinea,"%d",nword_o);

  intlinea[j++]=BLANK;

/* Incremento il PC di 2 word */

  nword_o+=wordpar_ch[0];

  j+=sprintf(&intlinea[j],"%s","JUMP LABEL_");
  j+=sprintf(&intlinea[j],"%03d",stackif[contif-1][0]);

/* Scrittura di intlinea sul file intermedio */

  scrivisufile(fdint,intlinea,j+1,&righeint);

  if ( ( stackif[contif-1][2] != -1 ) ) {

  /* Istruzione LOOP con BREAKLOOP */

  stackif[contif-1][3] = nword_o;

  /* Inserisco la label di break nella listlabel */

  cima=listlabel(cima,2);

  sbianca(intlinea,LUNGSTR-1);

  j = sprintf(intlinea,"%s","LABEL_"); 
  j+= sprintf(&intlinea[j],"%03d",stackif[contif-1][2]);

  scrivisufile(fdint,intlinea,j+1,&righeint);

  trbrloop[contloop-1]=0;  // resetto flag di trovato braeakloop

  }

}

}


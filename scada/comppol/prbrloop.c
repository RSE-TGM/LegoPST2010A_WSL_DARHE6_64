/*
   modulo prbrloop.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)prbrloop.c	1.1
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

int trbrloop[MAXLOOP];

extern int trloop[];

extern int contif;
extern int contloop;
extern int nword_o;
extern int cont_label;
extern int fdint;
extern int righeint;

extern int stackif[MAXIF][5];

/********************************************************************
*								                                            *
*			Procedura prbrloop			                                *
*								                                            *
********************************************************************/

prbrloop()

{

char intlinea[LUNGSTR];
int i,j=0;

sbianca(intlinea,LUNGSTR-1);

/* Verifico giusto concatenarsi istruzioni LOOP e BREAKLOOP */

if ( (contloop == 0) ) {

		stampa_err(67,1,"BREAKLOOP");

}

else  {

/* Assegno nello stackif un nuovo numero di label */

if ( trbrloop[contloop-1] == 0 ) {

/* Prima istruzione breakloop nel livello contif salvato nel vettore */
/* trloop con indice contloop -1                                     */

  stackif[ trloop[contloop-1] -1][2]=++cont_label;

  trbrloop[contloop -1] = 1;  // setto il flag di trovato breakloop

  }

/* Preparo la line del file intermedio */

  j=sprintf(intlinea,"%d",nword_o);

  intlinea[j++]=BLANK;

/* Incremento il PC di 2 word */

  nword_o+=wordpar_ch[0];

  j+=sprintf(&intlinea[j],"%s","JUMP LABEL_");
  j+=sprintf(&intlinea[j],"%03d",stackif[( trloop[contloop-1] -1 )][2]);

/* Scrittura di intlinea sul file intermedio */

  scrivisufile(fdint,intlinea,j+1,&righeint);

}

}


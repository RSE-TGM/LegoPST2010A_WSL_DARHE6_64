/*
   modulo procloop.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)procloop.c	1.1
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

int trloop[MAXLOOP];

extern int contif;
extern int contloop;
extern int nword_o;
extern int cont_label;
extern int fdint;
extern int righeint;

extern char linea_cor[];


extern int stackif[MAXIF][5];

struct etichette *listlabel();

/*********************************************************************
*          							                                       *
*			Procedure procloop			                                 *
*          							                                       *
*********************************************************************/

procloop(indistr)

int indistr;

{

int i,ok,M,dim,ind;
int j;
short flginsbreak;

char st[6];
char intlinea[LUNGSTR];

contif++;    /* incremento livello nidificazione degli if-case */
contloop++;  /* incremento livello nidificazione dei loop */

/* Verifico numero massimo livelli annidamento */

if(contif>MAXIF || contloop >MAXLOOP ) {
	stampa_err(66,0,"0"); /* superate le dimensioni massime */
	return(-2);
}

for(i=0;i<4;i++)      /* inizializzo lo stack  a -1 tranne l' ultima */
	stackif[contif-1][i]=-1;

stackif[contif-1][i]=1;  /* finche' = 1 ==> LOOP attiva */

/* Inserisco la label di ciclo istruzione LOOP */

sbianca(intlinea,LUNGSTR-1);
cont_label++;

j = sprintf(intlinea,"%s","LABEL_"); 
j+= sprintf(&intlinea[j],"%03d",cont_label);

scrivisufile(fdint,intlinea,j+1,&righeint);

/* Inserisco nello stackif il numero e il PC della prima label */

stackif[contif-1][0]=cont_label; /* numero della label */
stackif[contif-1][1]=nword_o;    /* PC associato alla label */

/* Salvo il valore di contif nel vettore trloop */

trloop[contloop-1] = contif;

/* Inserisco la Label nella lista delle label */

cima=listlabel(cima,0);

/* Chiamata routine di compilazione istruzioni LOOP e REPLOOP */

switch ( indistr ) {

	case 12 :

	ctrloop(indistr);

	break;

	case 15 :

	/* istruzione REPLOOP */

	creploop(indistr);

	flginsbreak = 1;

	break;

}

/* Ciclo di analisi chiusura LOOP con istruzione ENDLOOP */

while(stackif[contif-1][4]==1) {

	if( flginsbreak == 1 ) {

		flginsbreak = 0;

		memcpy(&linea_cor[0],"BREAKLOOP",9);

		linea_cor[9] = 0x00;

		i=scegli(0);

	}

	i=scegli(1);

	if( (i == -3) || (i==-4) ) {

		stampa_err(68,1,"ENDLOOP");

	   if( i==-4 )
		  return(-1); // E O F senza istruzione END
		else 
		  return(-2); // Incontrata istruzione END

	}

}

contif--;   /* decremento livello nidificazione degli if-case */
contloop--; /* decremento livello nidificazione delle loop */

}

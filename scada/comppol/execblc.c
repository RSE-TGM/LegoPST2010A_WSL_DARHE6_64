/*
   modulo execblc.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)execblc.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <osf1.h>
#include <stdio.h>
#include <ctype.h>

#include "chascii.inc"

#include "tipi.h"

extern char linea_cor[];
extern int nword_o;
extern int entry[];
extern int fdint;
extern int righeint;
extern int subrcorr;

/*********************************************************************
*          							                                       *
*			Procedura execblc                                           *
*          							                                       *
*********************************************************************/

execblc(codice)

int codice;  //  indice relativo al nome della istruzione

{

int i,M,tipo,ind,dim;
int ier;
char nomevar[LUNG_VAR+1];

/* Ciclo di caricamento nome blocco da eseguire */

for(M=7,i=0;linea_cor[M]!=BLANK && linea_cor[M]!=0x00 &&
            ( (ier=isalnum((int)(linea_cor[M]))) != 0 || linea_cor[M]==UNDSCORE ) &&
            i<LUNG_VAR ; M++)

	nomevar[i++]=linea_cor[M];

nomevar[i]=0x00;

if( i == 0 ) {
	stampa_err(58,0,"0"); /* nome blocco non specificato */
	return; 
}

if( ier == 0 ) {
	stampa_err(58,0,"0"); /* nome blocco non corretto    */
	return; 
}

/* Verifico eventuali errori di sintassi nell'istruzione exec */

while ( linea_cor[M] !=0x00 )
  {
  
  if( linea_cor[M] != BLANK ) {
	 stampa_err(6,0,"0"); /* errore di sintassi istruzione exec */
    return; 
    }

  else {

    M++;

    }
  }

/* Verifico se la variabile risulta definita */

if( (tipo=cerca(testa,nomevar,&dim,&ind)) < 0 ) {

	stampa_err(59,1,nomevar); /* variabile non definita */
	return;

}

if( ( tipo & 15 ) != 13 ) {

	stampa_err(60,1,nomevar); /* variabile non di tipo PB */
	return;

}

if(tipo>=16)
	cnome(nomevar,&tipo,&M);

if((i=controlla(nomevar,&M,tipo))!=-1)
	intfile(codice);

}

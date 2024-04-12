/*
   modulo stampa_s.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)stampa_s.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <malloc.h>


#include "defpath.inc"
#include "tipi.h"


extern short fddeb;
extern short numvar_deb;


stampa_sufile(albero)

struct  variabili *albero;

{

short i;

if(albero!=NULL)  {
	if(albero->nome[0]!=0x23) {
		i=write(fddeb,albero->nome,EF_LUNGVAR);
		i=albero->tipo;

/***     VERSIONE PER C 4.0  */        
		i=write(fddeb,&i,2);
		i=albero->indirizzo;
		i=write(fddeb,&i,2);

/***      VERSIONE PER C 5.0    
		i=write(fddeb,(char *)i,2);
		i=albero->indirizzo;
		i=write(fddeb,(char *)i,2);
****/
		numvar_deb++;
	}
	stampa_sufile(albero->left);
	stampa_sufile(albero->right);
}
}


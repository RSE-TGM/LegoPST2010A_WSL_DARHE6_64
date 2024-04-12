/*
   modulo iscostan.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)iscostan.c	1.1
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


/*********************************************************************
*          							                                       *
*			Procedura iscostante                                        *
*          							                                       *
*	La procedura testa se il nome passato in nomevar e' una           *
*  costante o no. Nel primo caso rende il tipo della costante, nel   *
*  secondo -1.                                                       *
*          							                                       *
*********************************************************************/

iscostante(albero,nomevar,gr,cod)
struct variabili *albero;
char nomevar[];
short *gr;
short *cod;
{
short n;
if(albero==NULL)
	return(-1);
if((strcmp(albero->nome,nomevar))==0 &&
    (short)(albero->codicevar) == 3 ) {
	*gr=albero->flag;
	*cod=atoi(albero->valcost);
	return(albero->tipo & 15);
}
if((strcmp(nomevar,albero->nome))<0)
	n=iscostante(albero->left,nomevar,gr,cod);
else
	n=iscostante(albero->right,nomevar,gr,cod);
}


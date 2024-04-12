/*
   modulo cnome.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)cnome.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*          							                                       *
*			Procedura cnome                                             *
*                                                                    *
* 	Cambia il nome passato in nomevar mettendo come primo carat=      *
* tere #, come secondo in numero della subtroutine corrente e poi vi *
* copia il vecchio nome. Inoltre incrementa M di due, cioe' dei 2    *
* caratteri aggiunti alla riga e fa considerare al tipo della var.   *
* solo i primi 4 bit.                                                *
*                                                                    *
*********************************************************************/
#include "osf1.h"
#include <stdio.h>
#include <string.h>
#include "tipi.h"

extern int subrcorr;
extern int contsubr;
extern char nomeogges[];

cnome(nomevar,tipo,M)
char nomevar[];
int *tipo;
int *M;
{
char ausvar[LUNG_VAR+1];
if(*tipo>=256)
{
	*M=*M+strlen(nomeogges)+1;
	*tipo &= 15;
}
else
{
	if(*tipo!=-1)
		*tipo &=15;
	(*M)+=2;
	ausvar[0]=0x23;
/*  ausvar[1]=subrcorr+0x30; */
	sprintf(&ausvar[1],"%02d",subrcorr);
	(*M)++;
	strcpy(&ausvar[3],nomevar);
	strcpy(nomevar,ausvar);
}
}


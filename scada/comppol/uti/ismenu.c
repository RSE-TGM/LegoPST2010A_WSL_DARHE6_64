/*
   modulo ismenu.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)ismenu.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include "defpath.inc"

#include "chascii.inc"
#include "tipi.h"

extern short indmenu[];

extern char linea_cor[];




/*********************************************************************
*                                                                    *
*			Procedura ismenu                                            *
*          							                                       *
*	La procedura legge a partire dall M-esima posizione della         *
* riga corrente una variabile e controlla che sia un menu gia'       *
* definito. Se lo e' rende 1, altrimenti -1. Per controllarlo        *
* basta guardare se il vettore indmenu all' offset corrispondente    *
* al numero di menu' letto e' diverso od uguale a -1. Nel primo      *
* caso il numero di menu' e' corretto, nel secondo no.               *
*          							                                       *
*********************************************************************/

ismenu(valvar,M)
char valvar[];
short *M;
{
short i,ok;
for(i=0;i<EF_LUNGVAR && linea_cor[*M]!=BLANK && linea_cor[*M]!=0x00;(*M)++)
	valvar[i++]=linea_cor[*M];
valvar[i]=0x00;  /* leggo il numero del menu' da attivare */
if((ok=isintero(valvar))!=1 || (i=atoi(valvar))<1 || i>12 ||
	indmenu[i-1]==-1)
	ok=-1;
return(ok);
}


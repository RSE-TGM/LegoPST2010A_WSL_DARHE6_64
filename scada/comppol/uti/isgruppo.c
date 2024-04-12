/*
   modulo isgruppo.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)isgruppo.c	1.1
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

extern char linea_cor[];

/*********************************************************************
*          							                                       *
*			Procedura isgruppo                                          *
*          							                                       *
*	La procedura legge a partire dall M-esima posizione della         *
* riga corrente una variabile e controlla che sia un gruppo, cioe'   *
* una costante definita di tipo gruppo (campo flag=1). Se non si     *
*vuole leggere la costante basta passare a M una variabile con valore*
* -1. Ritorna -1 se non e' un gruppo, il numero del gruppo viceversa.*
*          							                                       *
*********************************************************************/

isgruppo(nomevar,M)
char nomevar[];
short *M;
{
short i,ok,cod;
if((*M)!=-1) {
	for(i=0;i<EF_LUNGVAR && linea_cor[*M]!=BLANK && linea_cor[*M]!=0x00;(*M)++)
		nomevar[i++]=linea_cor[*M];
	nomevar[i]=0x00;
}
if((ok=iscostante(testa,nomevar,&i,&cod))!=-1 && ok!=4 && i!=1)
		ok=-1; 	     /* accetto solo costanti intere */
if(ok!=-1)
	ok=cod;
return(ok);
}


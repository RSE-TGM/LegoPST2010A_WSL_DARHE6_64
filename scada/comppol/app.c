/*
   modulo app.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)app.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*								                                             *
*			Procedura legginvar                                         *
*                                                                    *
*  La procedura viene chiamata per leggere dalla stringa linea_cor,  *
* i nomi (2 o 3) delle variabili che costituiscono l' espressione    *
* aritmetica, ne trova una alla volta e se riscontra un errore       *
* (tipo fine stringa non attesa ) ritorna -1, viceversa 0.           *
*                                                                    *
*********************************************************************/

#include "osf1.h"

legginvar(nomevar,codice,M,ciclo)
char nomevar[];	  // nome variabile (di ritorno)
int codice;			  // codice dell'istruzione
int *M;				  // puntatore da cui iniziare a leggere i nomi
						  // (punta all'interno di linea_corr sul primo
						  // carattere appartenente al nome della variabile).
int ciclo;
{
int i,temp=0;

for(i=0;linea_cor[*M]!=BLANK && linea_cor[*M]!=0x00 &&
linea_cor[*M]!=VIRGOLA && linea_cor[*M]!=APTONDA &&
((subrcorr==-1 && i<EF_LUNGVAR) || (subrcorr!=-1 && i<LUNG_VAR)); (*M)++)
		nomevar[i++]=linea_cor[*M];	  // copia il nome in nomevar
nomevar[i]='\0';
	if(linea_cor[*M]==APTONDA)  {
		temp=*M;
}

while(linea_cor[*M]!=VIRGOLA && linea_cor[*M]!=0x00)
	(*M)++;

if(linea_cor[*M]==0x00 && ciclo!=2) {		// ha trovato una sola variabile
	if(codice!=-1)
		stampa_err(11,1,par_chiav[codice]);
	else
		stampa_err(11,1,"MOVP");
	return(-1);
}
if(temp!=0)			 // se Š specificato un elemento di variabile
						 // vettoriale (..) esce con M puntato su (
	*M=temp;
return(0);
}


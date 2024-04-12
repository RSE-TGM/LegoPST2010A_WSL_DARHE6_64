/*
   modulo cerca.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)cerca.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*
*	cerca (albero,ndato,dimvett,indvar)
*		struct variabili *albero;
*		char ndato[];
*		int *dimvett;
*		int *indvar;
*
*	cerca1 (albero,ndato,dimvett,indvar) 
*		struct variabili *albero;
*		char ndato[];
*		int *dimvett;
*		int *indvar; 
*
*	cerca2 (albero,ndato,dimvett,indvar)             
*		struct variabili *albero;                     
*		char ndato[];                                 
*		int *dimvett;                                 
*		int *indvar;                                  
*
*********************************************************************/
#include "osf1.h"
#include <stdio.h>
#include <string.h>

#include "chascii.inc"
#include "define.inc"
#include "tipi.h"


#define NUM_ARG	20
extern int subrcorr;			 
extern int tvarsubr[10][NUM_ARG+1];
extern int hh;
extern char *nvarsubr[10][NUM_ARG];
extern char *nomi_subr[];
extern struct variabili *inserisci();
extern char nomeogges[];
extern char linea_cor[];
/*********************************************************************
*                                                                    *
*            Procedura cerca                                         *
*                                                                    *
* La procedura cerca nell' albero delle variabili la stringa ndato,  *
* se non esiste nessuna variabile con quel nome la ricerca negli     *
* argomenti della subr. corrente ( se siamo in una subr.), se anche  *
* li' non la trova significa che la variabile non e' definita e      *
* ritorna -1, altrimenti ritorna il tipo della variabile             *
* cercata e pone nella prima variabile intera passata la dimensione  *
* dell'eventuale vettore, oppure 0 se la variabile non e' un vettore *
* e nella seconda l' idirizzo della variabile nel D.B.               *
* Per determinare il tipo di una variabile bisogna fare l' and bit a *
* bit con il numero 15.                                              *
*                                                                    *
*********************************************************************/
char *cercastr(char*, char*);

cerca (albero,ndato,dimvett,indvar)
struct variabili *albero;
char ndato[];
int *dimvett;
int *indvar;
{
int n;
char appvar[LUNG_VAR+1];
char applinea[DMX_RIGA+1];
short find;
char *focc;
char *locc;

focc=strchr(ndato,'Š');				// elimino eventuale concatenazione
if(focc!=NULL) *focc=0;				// precedente con nome oggetto

strcpy(appvar,ndato);
strcat(appvar,"Š");
strcat(appvar,nomeogges);


if((n=cerca1(albero,appvar,dimvett,indvar))==-1)
{
	if((n=cerca1(albero,ndato,dimvett,indvar))==-1 && subrcorr!=-1)
		n=cerca2(albero,ndato,dimvett,indvar);
}
else
{
	locc=linea_cor;
	do
	{	
		locc=cercastr(locc,ndato);
		if(locc!=NULL && ((*(locc+strlen(ndato))!='Š')))  // gia sostituito ?
		{
			focc=locc;
			*focc=0;						// sostituisco nome con nome+oggetto a cui si riferisce
			strcpy(applinea,linea_cor);
			*focc=' ';						// sostituisco nome con nome+oggetto a cui si riferisce
			focc=focc+strlen(ndato);
			strcat(applinea,appvar);
			strcat(applinea,focc);
			strncpy(linea_cor,applinea,DMX_RIGA);
			strcpy(ndato,appvar);
			return(n+256);		// cambiata la riga linea_cor e tipo locale
		}
		if(locc) locc=locc+strlen(ndato);
	}
	while(locc);
	if(focc!=NULL) *focc='Š';		// ripristino nome completo
	return(n+256);		// cambiata la riga linea_cor	e tipo locale
}
return(n);
}

/*********************************************************************
*																							*
*          Procedura cerca1														*
*																							*
* 	Serve per verificare se la variabile passata in ndato e'				*
* presente o meno tra le variabili dichiarate. Se presente rende il  *
* tipo e pone in dimvett e indvar rispettivamente la dimensione      *
* vettoriale e l' indirizzo, viceversa -1.									*
*																							*
*********************************************************************/

cerca1 (albero,ndato,dimvett,indvar)
struct variabili *albero;
char ndato[];
int *dimvett;
int *indvar;
{
int n,i;
if(albero==NULL)
		return(-1);   /* variabile non esistente */

if(!strcmp(ndato,albero->nome))   {
	n=albero->tipo & 15;
	if(albero->tipo>15)
		*dimvett=(albero->tipo-n) / 16;
	else
		*dimvett=0;
	*indvar=albero->indirizzo;
 	return(n); /* variabile trovata e rendo il tipo */
}
if((strcmp(ndato,albero->nome))<0)
	n=cerca1(albero->left,ndato,dimvett,indvar);
else
	n=cerca1(albero->right,ndato,dimvett,indvar);
}

/*********************************************************************
*                                                                    *
*          Procedura cerca2                                          *
*                                                                    *
*	Viene chiamata per verificare se la variabile passatagli in       *
* ndato e' uno degli argomenti della subroutine corrente (la indica  *
* subrcorr). Se non la trova rende -1, viceversa ne cambia il nome e *
* la inserisce nell' albero passando cd=5 (segno cosi' che e' una    *
* variabile locale ) e cambio tutte le occorrenze nella riga della   *
* variabile con il nuovo suo nuovo nome.                             *
*																							*
*********************************************************************/

cerca2 (albero,ndato,dimvett,indvar)
struct variabili *albero;
char ndato[];
int *dimvett;
int *indvar;
{
int ok,n,i,temp=-1;
char newvar[LUNG_VAR+1];
for(i=0;i<tvarsubr[subrcorr][NUM_ARG];i++)
	if((strcmp(ndato,nvarsubr[subrcorr][i]))==0) {
		temp=i;
		break;
	}
if(temp==-1)
	return(-1); /* la variabile non appartine ad alcuna subr. */

/* ho trovato la variabile e gli cambio il nome rendendolo unico */

newvar[0]=0x23;          /* inserisco il # come primo carattere */
/**  newvar[1]=subrcorr+0x30; /* ed il numero di subr. (0-9) a cui appartiene */
sprintf(&newvar[1],"%02d",subrcorr); /* ed il numero di subr. (0-9) a cui appartiene */
strcpy(&newvar[3],ndato);
n=2+16*((temp+2)*2); /* l' ultimo campo indica anche l' offset dell' argomento */
testa=inserisci(testa,newvar,tvarsubr[subrcorr][temp],&hh,nomi_subr[subrcorr],5,n);
cambianvar(ndato,newvar,&ok); /* cambio le occorrenze nella riga della var */
*indvar=temp;
*dimvett=(tvarsubr[subrcorr][temp]-(tvarsubr[subrcorr][temp] & 15))/16;
/* se ho cambiato linea_cor ok=1, altrimenti ok=0 */
return((tvarsubr[subrcorr][temp] & 15)+16*ok);
}


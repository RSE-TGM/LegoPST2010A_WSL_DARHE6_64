/*
   modulo declink.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)declink.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	declink.c
	Inserisce indicato nella lista dei nomi LINK utilizzati come
	parametri nell'istruzione PAG

	Parametri
		char *nomevar	nome misura in data base di sistema
		short tipo 	tipo di variabile 
	Ritorno
		-1		se la variabile esiste ma e' tipo diverso
		>1		tutto corretto posizione nella tabella

*/
#include "osf1.h"
#include <stdio.h>

#define n_parLink		2048
#define l_parLink		10

#include "all_1.h"
typedef struct s_parLink {
		char nome[l_parLink];
		short tDBL;
			} S_PARLINK;
#include "all_16.h"
			
S_PARLINK	parLink[n_parLink];

declink(nomevar,tipo)
char* nomevar;
short tipo;
{
short i;
S_PARLINK* pparLink;

for(i=0,pparLink=&parLink[0];i<n_parLink;i++,pparLink++)
{
	if(!pparLink->nome[0])		  // posizione vuota
	{
		strncpy(pparLink->nome,nomevar,l_parLink);
		pparLink->tDBL=tipo;
		return (i);
	}
	else				// stesso nome
	{
		if(!strncmp(nomevar,pparLink->nome,l_parLink))
		{
			if(pparLink->tDBL==tipo) return(i);			// stesso tipo
			else return(-1);									// incongruenza
		}
	}
}
return(-1);
}
/*
	savlink
	Routine per il salvataggio su disco della tabella dei link
	utilizzati per il passaggio dei parametri (solo quelli effettiva
	mente inseriti)

	Parametri
	short		canale file

	Ritorno
	nessuno

*/
savlink(fpln)
short fpln;
{
	short i;
	S_PARLINK* pparLink;

	for(i=0,pparLink=&parLink[0];i<n_parLink;i++,pparLink++)
	{
		if(!pparLink->nome[0]) break;		  // posizione vuota
	}																									  
	write(fpln,&i,sizeof(i));				  // memorizzo n. parametri Link
	write(fpln,parLink,sizeof(S_PARLINK)*i);
	return;
}

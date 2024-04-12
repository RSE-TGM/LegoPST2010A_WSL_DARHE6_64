/*
   modulo decgrp.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)decgrp.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include "osf1.h"
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

#include "tipi.h"
#include "define.inc"
/*
	decgrp.c
	Inserisce il nome del gruppo indicato nelle istruzioni LDEFINE e LDATA
	nella lista generale. 

	Parametri
		char *nomegrp	nome del gruppo indicato

	Ritorno
		< 0 		esaurito spazio		
		>=0		la posizione nella tabella

*/

#define n_Grp		2048
#define l_Grp		20

#include "all_1.h"
typedef struct s_Grp {
		char nome[l_Grp];		// nome del gruppo
		short indVar;			// n. di variabili utilizzate
		short indDB;			// indice progressivo di occupazione data base locale
		short indGru;			// indice progressivo define gruppi
			} S_GRP;
#include "all_16.h"
			
S_GRP	grp[n_Grp];

decgrp(nomevar)
char* nomevar;
{
short i;
S_GRP* pGrp;

for(i=0,pGrp=&grp[0];i<n_Grp;i++,pGrp++)
{
	if(!pGrp->nome[0])		  // posizione vuota
	{
		strncpy(pGrp->nome,nomevar,l_Grp);
		return (i+1);
	}
	else				// stesso nome
	{
		if(!strncmp(nomevar,pGrp->nome,l_Grp))
		{
			return(i+1);			// gia' inserito
		}
	}
}
stampa_err(80,0,"");
return(-1);
}
/*
	GetIndGrp
		restituisce il puntatore alla locazione contenente
		in byte il grado di occupazione del data base locale
		ed incrementa il n. di variabili associate al gruppo

	Parametri

		short	indice del gruppo in esame (da 1 a 1024)
		short	DATA=2, DEFINE=1 (solo per data si incrementa il n.
				di variabile e per i DEFINE di tipo gruppo)
		short gruppo =1 si tratta di define gruppo
						 =0 si tratta di data quasiasi

	Ritorno

		int*	puntatore alla locazione di occupazione
*/
int* GetIndGrp(indice, tipo, gruppo)
short indice;
short tipo;
short gruppo;
{
	if(tipo==2)
	{
		grp[indice-1].indVar++;
		if(gruppo) grp[indice-1].indGru++;
	}
	return(&grp[indice-1].indDB);
}
/*
	AllDBGrp
		Verifica il valore di occuopazione dei data base locali
		e li allinea alla word

	Parametri

		nessuno

	Ritorno

		nessuno
*/
AllDBGrp()
{
short i;
S_GRP* pGrp;
for(i=0,pGrp=&grp[0];i<n_Grp;i++,pGrp++)
{
	if(pGrp->nome[0])		  // posizione occupata
	{							  // allineamento alla word
		pGrp->indDB=(pGrp->indDB+1) & 0xFFFE; 
	}
}
return (0);
}
/*
	MaxGrpDB
		Verifica che il valore di occupazione dei data base locali
		non superi il valore indicato come parametro

	Parametri

		int n. byte massimo

	Ritorno

		0 non superato
		1 superato
*/
MaxGrpDB(valore)
int valore;
{
short i;
S_GRP* pGrp;
for(i=0,pGrp=&grp[0];i<n_Grp;i++,pGrp++)
{
	if(pGrp->indDB>=valore) return(1);
}
return(0);
}
/*
	SavGrp
	Routine per il salvataggio su disco dei data base locali di ogni
	oggetto. Vengono memorizzate: n. word che lo compongono e la lista
	dei nomi delle variabili e dei data associati secondo la struttura
	utilizzata nella mappa complessiva

	Parametri
	nessuno

	Ritorno
	nessuno
*/
SavGrp(canale)
short canale;
{
short i;
S_GRP* pGrp;

for(i=0,pGrp=&grp[0];i<n_Grp;i++,pGrp++)
{
	if(pGrp->nome[0])
	{
		write(canale,&pGrp->nome[1],l_Grp-1);		// escluso '_'
		write(canale,&pGrp->indVar,2);		// n. variabili associate al gruppo
		write(canale,&pGrp->indGru,2);		// n. variabili define GR
		write(canale,&pGrp->indDB,2);		// n. word occupazione DBL
		InsGrp(testa,i,canale,0);				// ricerca nell'albero tutti i DATA associabili al gruppo
		InsGrp(testa,i,canale,1);				// ricerca nell'albero tutte le DEFINE GR associabili al gruppo
	}
	else
	{
		return(0);
	}
}
return(0);
}
/*
	InsGrp
	Routine che scorre l'alberper il salvataggio su disco dei data base locali di ogni
	oggetto. Vengono memorizzate: n. word che lo compongono e la lista
	dei nomi delle variabili e dei data associati secondo la struttura
	utilizzata nella mappa complessiva

	Parametri
		struct variabili   albero delle variabili
		short		indice del gruppo da esaminare
		short		canale del file
		short    flag  (DATA o DEFINE GR ?)

	Ritorno
	nessuno
*/
InsGrp(albero,indice,canale, flag)
struct variabili *albero;
short indice;
short canale;
short flag;
{
short tipo;
char stapp[LUNG_VAR];
float fvar;
int ivar;

if(albero!=NULL)			// struttura delle variabili non vuota
{
	if(albero->indirizzo & 0x8000)		// variabile locale all'oggetto
	{
		if((((albero->codicevar & 0xFFF0) >> 4)==indice+1) &&
			((albero->codicevar & 3 ) ==  3) && (albero->flag==flag)) 
		{
			tipo=albero->tipo & 15;
			memset(stapp,0,LUNG_VAR);
			sprintf(stapp,"%s",albero->nome);
			write(canale,stapp,LUNG_VAR);
			write(canale,&albero->tipo,2);
			write(canale,&albero->indirizzo,2);
			switch(tipo)
			{
			case treale :				// costante reale
				fvar=atof(albero->valcost);
				write(canale,&fvar,4);
			break;
			case tintero :				// costante intera
				ivar=atoi(albero->valcost);
				write(canale,&ivar,2);
			break;
			case tlogico :				// costante logica
				write(canale,albero->valcost,1);
			break;
			case tpuntan :			
			case tpuntdi :
			case tpuntor :
			case tpuntcom:
			case 14:		 // ?
			case tpuntst :
				memset(stapp,0,LUNG_VAR);
				sprintf(stapp,"%s",albero->valcost);
				write(canale,stapp,LUNG_VAR_LINK_DBS);
			break;
			default :							// costante stringa
				ivar=(albero->tipo-tipo)/16;			// dimensione reale della costante
				write(canale,albero->valcost,ivar);
				break;
			}
		}
	}
	/* Chiamata ricorsiva di inserimento nel file .map */

	InsGrp(albero->left,indice,canale,flag);
	InsGrp(albero->right,indice,canale,flag);
}
return(0);
}

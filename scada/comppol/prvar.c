/*
   modulo prvar.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)prvar.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/* ->PRVAR.C
 *   provvede alla ricerca e ai controlli relativi alle istruzioni di
 *   stampa relative alle variabili (COD,DESC,UNMIS,ORG)
 *   La parola chiave che deve essere seguita da [NOMEVAR]
 *			.Si verifica che il nome della variabile sia corretto
 *			.Si verifica che la variabile esista e che se possiede
 *			 un indice esso sia compatibile con le dim. della var.
 *			 stessa
 *			.Si verifica la compatibilit… del tipo della variabile
 *			 con i tipi ammissibili per l'istruzione in esame.
 *			.Viene scritto sul file intermedio il nome della variabile
 */

#include <osf1.h>
#include <stdio.h>
#include "chascii.inc"
#include "tipi.h"
#include "ctrprint.inc"

extern char linea_cor[];
extern char codstring[];
extern RECPRINT tabprint[];
extern char vet_term[];
#define lun_codif  5

prvar(stringa,j,M,spiazzPC,ind_tab)
char *stringa;
short *j,*M,*spiazzPC;
short ind_tab;       // indice corrispondente alla posizione in tabprint
						 // della istruzione da considerare.
{
static char vet_term[]=       // vettore dei terminatori ammessi per delimitare
                        // il nome di variabile
		 {CHQUADRA};
short ier;
short tipo,dim,ind;
char nomevar[LUNG_VAR+1];
if(linea_cor[(*M)]!=APQUADRA)
	stampa_err(6,0,"0");    /* errore di sintassi */
else (*M)++;				 // si posiziona all'inizio del nome
ier=estrnome(&linea_cor[(*M)],nomevar,LUNG_VAR,vet_term,1,1);	// estrae il nome della variabile
										   // N.B. il nome viene estratto senza eventuale 
										   // indice di specificazione elemento

if(ier || !strlen(nomevar)) stampa_err(58,0,"0"); // nome variabile scorretto o mancante 
(*M)+=strlen(nomevar);         // si posiziona sul il terminatore
if(!ier)   // se il nome Š corretto cerca se corrisponde ad una variabile 
			  // definita.
	{
	tipo=cerca(testa,nomevar,&dim,&ind);	 // cerca il nome nella
														 // simbol table.
	if(tipo==-1)   // variabile non definita
		stampa_err(59,0,"0");
	else           // variabile definita
		{
		if(tipo>=16)
		cnome(nomevar,&tipo,M);  // modifica il nome nel caso di
										  // nome locale a subroutine.
		(*M)++;  // salto la chiusura

		if(ctrtipo(tipo,tabprint[ind_tab].tipamm))	// se il tipo della variabile
																	// Š tra quelli ammessi.
			{
			(*spiazzPC)++;
			stringa[(*j)++]=BLANK;
			(*j)+=sprintf(&stringa[(*j)],"%s",nomevar);	  // scrive sulla riga del
																  // file intermedio il nome
			}													  // della variabile.
		else stampa_err(60,0,"0");

		}
	}
}

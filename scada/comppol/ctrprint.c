/*
   modulo ctrprint.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)ctrprint.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>
#include "ctrprint.inc"
#include "chascii.inc"

#include "tipi.h"

#define LUNGSTR	   100
#define POS1	     3
#define POS2	    10

extern char linea_cor[];
extern int nword_o;
extern int fdint;
extern int righeint;
extern int subrcorr;

/*********************************************************************
*
*			Procedura ctrprint
*	Esegue controlli e decodifica per l' istruzione  PRINT
*
*********************************************************************/
		       // par.chiave  lung.chiave    codif.  flag     tipi ammessi
		       //				     n.var.
RECPRINT tabprint[num_chiav]=
                   {"PAG",     3,          "$000b",  0,  -1,-1,-1,-1,
                              "\\",      1,          "$000c",  0,  -1,-1,-1,-1,
                              "TIM1",    4,          "$000d",  0,  -1,-1,-1,-1,
                              "TIM2",    4,          "$000e",  0,  -1,-1,-1,-1,
                              "COD",     3,          "$0010",  1,  tpuntan,tpuntdi,tpuntor,-1,
                         "DESC",    4,          "$0011",  1,  tpuntan,tpuntdi,tpuntor,-1,
                              "UNMIS",   5,          "$0012",  1,  tpuntan,-1,-1,-1,
                         "ORG",     3,          "$0013",  1,  torgano,-1,-1,-1,
                                   "DL",      2,          "$0016",  1,  tdigitale,tlogico,-1,-1,
                                   "SGRAF",      5,            "$0017",  0,  -1,-1,-1,-1,
                                   "GRAF",    4,          "$0018",  6,  tanalogico,treale,-1,-1,
                              };

char codspaces[]="$000f";  // codifica per la stampa di n blank
char codstring[]="$0014";  // codifica per la stampa di stringa
char codformat[]="$0015";  // codifica per la stampa di valore di variabile
			                  // con il formato mm.nn[NOME_VAR]



ctrprint(codice)
int codice;
{
short ier;
short flagvar;
short i,j,M;
short tipo,dim,ind;
short spiazzPC=1;  // variabile utilizzata per calcolare l'incremento del 
						 // program counter.

char stringa[LUNGSTR+1];		// stringa che andr… scritta sul file

togliblank(linea_cor,0);	// pulisce la linea di codice dai blank

M=6;             			  // si posiziona dopo la parola chiave PRINT

/*
	Inizializza la riga per file intermedio e vi scrive la parola
	chiave PRINT.
*/

sbianca(stringa,LUNGSTR);    // riempie di blank la stringa.
j=POS1;
j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
stringa[j]=BLANK;
j=POS2;
j+=sprintf(&stringa[j],"%s",par_chiav[codice]);  /* inserisco PRINT */
scrivisufile(fdint,stringa,j+1,&righeint);

/* Verifica che la parola chiave PRINT sia seguita da (" altrimenti
   segnala errore di sintassi													 */

if(linea_cor[M-1]!=APTONDA)
	stampa_err(6,0,"0");    /* errore di sintassi */

/*
	Esamina se nella riga in esame Š presente una parola chiave o un formato
	di stampa: per fare ci• utilizza la tabella tabprint[] definita in 
	ctrprint.inc.  Tale tabella Š formata da records contenenti:
	.parola chiave da individuare .lunghezza della parola chiave .codice
	in ascii con cui sostituire la parola nel file intermedio .flag indicante
	se la parola chiave deve essere seguita da [NOME_VARIABILE]
	L'analisi termina quando viene trovata la chiusura di parentesi.
*/
for(;;)
	{
	sbianca(stringa,LUNGSTR);    // riempie di blank la stringa.
	j=POS1;
	j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
	stringa[j]=BLANK;
	j=POS2;
	i=0;
	spiazzPC++;
	while(i<num_chiav &&(ier=memcmp(&linea_cor[M],tabprint[i].chiave,tabprint[i].lung)))
		i++;

	if(ier)		// caso in cui non si Š trovata la parola chiave: esamino gli
					// altri casi (stringa ASCII o format di stampa)
		{
		flagvar=0;  // non sar… necessaria una ulteriore ricerca di nomi
						// di variabili.
/*
	Caso di stringa.
*/
                  					// se trova " -> deve essere una stringa
		if(linea_cor[M]==VIRGOLETTE)
														// scrive su file intermedio
														// la decodifica di stampa stringa
														// e la stringa da stampare.
			prstringa(stringa,&j,&M,&spiazzPC,LUNGSTR);
		else 
/*
	Caso di format di stampa.
*/
			format(stringa,&j,&M,&spiazzPC);	// vede se Š un format di stampa
														// (compreso stampa di blank) e
														// provvede alla scrittura su file 
														// intermedio della decodifica.
		}
	else		   // caso in cui si Š trovata la decodifica nella tabella:
					// copio sulla riga del file intermedio la decodifica.
		{
		memcpy(&stringa[j],tabprint[i].codifica,lun_codif);
		j+=lun_codif;    	    // si posiziona dopo la codifica sulla riga del
									 // file intermedio
		M+=tabprint[i].lung;  // si posiziona dopo la parola chiave sulla
									 // riga corrente del sorgente
		flagvar=tabprint[i].flag;   // flagvar indica se si deve trovare 
											 // il nome di variabile racchiuso
											 // tra [ ].
		}
/*
	Caso di parola chiave che deve essere seguita da [NOMEVAR]
	(cioŠ per le istruzioni COD, DESC, UNMIS, ORG):
			.Si verifica che il nome della variabile sia corretto
			.Si verifica che la variabile esista e che se possiede
			 un indice esso sia compatibile con le dim. della var.
			 stessa
			.Si verifica la compatibilit… del tipo della variabile
			 con i tipi ammissibili per l'istruzione in esame.
			.Viene scritto sul file intermedio il nome della variabile
*/
	if(flagvar==1)  // deve cercare il nome di variabile tra [ ] e
						 // verificare che tale nome esista.
		prvar(stringa,&j,&M,&spiazzPC,i);
	if(i==i_graf || i==i_sgraf)		 // trattamento istruzioni GRAF e SGRAF
		prgraf(stringa,&j,&M,&spiazzPC,i);
/*
	Scrittura sul file intermedio della riga ottenuta.
*/
	scrivisufile(fdint,stringa,j+1,&righeint);
/*
	Individua se Š arrivato a fine istruzione PRINT
*/
	if(linea_cor[M]==CHTONDA)
		{				 
		if(linea_cor[M+1]==0) 	  // l'istruzione Š chiusa correttamente:
										  // inserisce il tappo di fine istruzione
										  // (-1) ed esce dal ciclo di analisi della
										  // istruzione.
			{
			sbianca(stringa,LUNGSTR);    // riempie di blank la stringa.
			j=POS1;
			j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
			stringa[j]=BLANK;
			j=POS2;
			spiazzPC++;
			j+=sprintf(&stringa[j],"%2d",-1); /* inserisco il tappo di
                                              fine istruzione  */

			scrivisufile(fdint,stringa,j+1,&righeint);
			nword_o+=spiazzPC;  /* aggiorno il PC */
			if(j>LUNGSTR) stampa_err(45,0,"0");    /* errore di sintassi */
			break;  // esce dal ciclo di analisi della
						// istruzione
			}
		else 
			stampa_err(6,0,"0");    /* errore di sintassi */
		}
	else if (linea_cor[M]==',')
		M++;
	else
		{
		stampa_err(6,0,"0");    /* errore di sintassi */
		return(1);
		}
	}
return(1);
}





/*
   modulo ctrfrewr.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)ctrfrewr.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include "osf1.h"
#include <stdio.h>
#include <string.h>

#include "chascii.inc"

#include "tipi.h"

#include "ctrfrewr.inc"


#define LUNGSTR	100
#define POS1	     3
#define POS2	    10

extern short lnbyvar[];
extern char linea_cor[];
extern int nword_o;
extern int fdint;
extern int righeint;
extern int subrcorr;

/*********************************************************************
*
*			Procedura ctrfrewr
*	Esegue controlli e decodifica per le istruzioni FREAD/FWRITE
*
*********************************************************************/

ctrfrewr(codice,flgrewr)

int codice;   // indice nome istruzione da analizzare 
int flgrewr;  // flag indicante il tipo di istruzione 0 = FREAD 1 = FWRITE 

{

short cnvarint=0; // contatore variabili intere scandite nella lista param.
short *pvtamm;    // puntatore vettore tipi ammessi 
short ier;
short lstr;
short lstring;
short i,j,M;
short tipo,dim,ind;
short spiazzPC=1;  // variabile utilizzata per calcolare l'incremento del 
						 // program counter.

char stringa[LUNGSTR],		// stringa che andr… scritta sul file
	  nomevar[LUNG_VAR+1];

/* Inizio controllo e decodifica istruzione FREAD/FWRITE */

togliblank(linea_cor,0);	// pulisce la linea di codice dai blank

M= strlen(par_chiav[codice])+1; 
sbianca(stringa,LUNGSTR);    // riempie di blank la stringa

j=POS1;
j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
stringa[j]=BLANK;

j=POS2;
j+=sprintf(&stringa[j],"%s",par_chiav[codice]);  /* inserisco FREAD/FWRITE */

scrivisufile(fdint,stringa,j+1,&righeint);

/* Verifica che la parola chiave FREAD/FWRITE sia seguita da (" altrimenti
   segnala errore di sintassi													 */

if(linea_cor[M-1]!=APTONDA) {
	stampa_err(6,0,"0");    /* errore di sintassi */
	return(1);

	}

/* Ciclo di analisi lista di argomenti istruzione FREAD/FWRITE */

for(;;)
	{

	sbianca(stringa,LUNGSTR);    // riempie di blank la stringa.
	j=POS1;
	j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
	stringa[j]=BLANK;
	j=POS2;

		/* estrae il nome della variabile dalla lista argomenti */

		ier=estrnome(&linea_cor[M],nomevar,LUNG_VAR,vterfrewr,2,1);	

	      // N.B. il nome viene estratto senza eventuale 
		   // indice di specificazione elemento

		if( (ier == 1) || ( lstr = strlen(nomevar) ) == 0 ) {

		  stampa_err(58,0,"0"); // nome variabile non corretto o mancante 
		  break;

		  }

		M+=strlen(nomevar);         // si posiziona sul il terminatore

		if(ier == 0)   // se il nome Š corretto cerca se corrisponde ad una variabile 
					      // definita.

			{

			/* Verifico esistenza e congruenza dell'argomento */

			tipo=cerca(testa,nomevar,&dim,&ind);	 // cerca il nome nella
																 // simbol table.

			if(tipo==-1) {   // variabile non definita
				stampa_err( 59,1,nomevar );
				break;

				}

			else

				{

				/* Variabile con nome corretto e definita */

				if(tipo>=16)
					cnome(nomevar,&tipo,&M);  // modifica il nome nel caso di
													  // nome locale a subroutine.

				controlla(nomevar,&M,tipo);  // controlla la correttezza dell'indice
													  // della variabile (se specificato) nei
													  // confronti della dimensione della 
													  // stessa e lo appende a nomevar.
													  // Dopo la chiamata della funzione
													  // M punta al carattere seguente la ')'

				/* Carico il puntatore pvtamm */

				if ( cnvarint < 2 ) {

				  /* Analisi primi argomenti interi lista parametri */

				  pvtamm = vtfrwid;


				  }

				  else {

				  /* Analisi successiva lista argomenti */

				  pvtamm = vtfrwls;

				  }

				if(ctrtipo(tipo,pvtamm))  // se il tipo della variabile
											     // Š tra quelli ammessi.
					{

					cnvarint = cnvarint + 1;

					j+=sprintf(&stringa[j],"%s",nomevar);	  // scrive sulla riga del
																		  // file intermedio il nome
																		  // della variabile.
					stringa[j] = BLANK;
					j++;
					spiazzPC++;

					j+=sprintf(&stringa[j],"$%04x",tipo);
					stringa[j] = BLANK;
					j++;
					spiazzPC++;

					j+=sprintf(&stringa[j],"$%04x",lnbyvar[tipo]);
					spiazzPC++;

					}

				else {

				  /* Tipo variabile argomento non ammesso */

				  stampa_err(60,1,nomevar);
				  break;

				  }

				}
			}

/* Variabile con nome corretto definita e di tipo ammesso */

/* Scrittura sul file intermedio della riga ottenuta */

	scrivisufile(fdint,stringa,j+1,&righeint);

   if( (linea_cor[M]==VIRGOLA) ) {

    /* salto il carattere terminatore del nome variabile */

	 M++; 

	 }

/* Individua se Š arrivato alla fine istruzione FREAD/FWRITE */

	else {

	if(linea_cor[M]==CHTONDA)

		{

		/* Incontrato nella lista argomenti il carattere CHTONDA */

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
			break;

			}

		else {

		   /* Istruzione terminata non correttamente */

			stampa_err(6,0,"0");    /* errore di sintassi */
			return(1);

			}

		}

		else {

		/* Manca il carattere CHTONDA di terminazione lista argomenti */

			stampa_err(6,0,"0");    /* errore di sintassi */
			return(1);

			}

		}

	}  // chiusura ciclo di scansione lista parametri

	return(1);

}

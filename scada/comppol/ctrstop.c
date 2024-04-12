/*
   modulo ctrstop.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)ctrstop.c	1.1
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
#include <ctype.h>

#include "chascii.inc"

#include "tipi.h"


#define LUNGSTR	100
#define POS1	     3
#define POS2	    10

extern char linea_cor[];
extern int nword_o;
extern int fdint;
extern int righeint;
extern int subrcorr;

extern char vterwait[];

/*********************************************************************
*
*			Procedura ctrstop
*	Esegue controlli e decodifica per l' istruzione STOP/START
*
*********************************************************************/

ctrstop(codice,flstop)

int codice;  // indice nome istruzione da analizzare 
int flstop;  // flstop = 1 compilazione istruzione STOP sequenza

{

short ier;
short lstr;
short j,M;
short k,indnum,cntind;
short tipo,range;
short spiazzPC=1;  // variabile utilizzata per calcolare l'incremento del 
						 // program counter.

char stringa[LUNGSTR],		// stringa che andr… scritta sul file
	  nomevar[LUNG_VAR+1];

/* Inizio controllo e decodifica istruzione WAIT */

togliblank(linea_cor,0);	// pulisce la linea di codice dai blank

if ( flstop == 1 ) {

/* Compilazione istruzione STOP sequenza */

M = 5;

}

else {

/* Compilazione istruzione START sequenza */

M = 6;

}

sbianca(stringa,LUNGSTR);    // riempie di blank la stringa

j=POS1;
j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
stringa[j]=BLANK;

j=POS2;
j+=sprintf(&stringa[j],"%s",par_chiav[codice]);  /* inserisco STOP/START */

/* Verifico se alla parola chiave STOP/START segue la lista argomenti */

if( linea_cor[M-1] == 0x00 ) {

/* Istruzione STOP/START non seguita da indice pas e sequenza */

	stampa_err(6,0,"0");    /* errore di sintassi */
	return(1);

	}

/* Verifica che la parola chiave STOP/START sia seguita da (" altrimenti
   segnala errore di sintassi													      */

if(linea_cor[M-1]!=APTONDA) {
	stampa_err(6,0,"0");    /* errore di sintassi */
	return(1);

	}

/* Analisi lista di argomenti istruzione STOP/START */

cntind = 0;  // reset contatore indici numerici

for(;;)
	{

		/* Estrae indice numerico relativo al P.A.S. */

		ier=estrnome(&linea_cor[M],nomevar,LUNG_VAR,vterwait,2,0);	

		if( (ier == 1) || ( lstr = strlen(nomevar) ) == 0 ) {

		  stampa_err(69,0,"0"); // indice non corretto o mancante 
		  break;

		  }

		M+=strlen(nomevar);   // si posiziona sul il terminatore

		if(ier == 0)   // decodifico valore numerico indice

			{

			/* Verifico se nomevar rappresenta un intero */

			tipo = 1;  // nomevar rappresenta un indice intero

			for ( k=0; k < lstr; k++) {

			  if ( !isdigit(nomevar[k]) ) {

			  /* Carattere che non rappresenta un digit */

			  tipo = -1;

			  break;

			  }

			}

			if(tipo==-1) {   // indice non corretto

				if ( cntind < 2 ) {

				stampa_err( 70,1,nomevar );
				break;

				}

				else {

				stampa_err( 71,1,nomevar );
				break;

				}

				}

			else

				{

				   /* Indice numerico corretto */

					indnum = atoi(nomevar);

					if ( cntind == 0 ) 
						range = 10;
					else 
						if ( cntind == 1 )
							range = 48;

					if ( indnum <= range ) {

					stringa[j] = BLANK;
					j++;
					j+=sprintf(&stringa[j],"$%04x",indnum);
					spiazzPC++;
					cntind++;

					if ( cntind > 2 ) {

					/* Lista argomenti STOP/START con piu' di due indici */

					stampa_err( 71,1,nomevar );
					break;

					}

				  }

				else {

				/* Valore indice non ammissibile */

					stampa_err( 72,1,nomevar );
					break;


					}

				}

         if( (linea_cor[M]==VIRGOLA) ) {

         	/* salto il carattere terminatore indice numerico */

         	M++; 

	      }

/* Individua se Š arrivato alla fine istruzione STOP/START */

	      else {

	        if(linea_cor[M]==CHTONDA)

		   	{

		/* Incontrato nella lista argomenti il carattere CHTONDA */

		   	if(linea_cor[M+1]==0) 	  // l'istruzione Š chiusa correttamente:

					{

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

    }

	}  // chiusura ciclo di scansione lista parametri

	return(1);

}

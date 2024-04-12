/*
   modulo prstring.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)prstring.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/* ->PRSTRINGA.C
 *      decodifica la stampa di una stringa racchiusa tra " ".
 *		  _ Prepara sulla riga da scrivere sul file intermedio:
 *             .	decodifica dell'istruzione di stampa stringa
 *             .  lunghezza della stringa da stampare
 *             .  stringa da stampare (allineata a word)
 */
#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include "chascii.inc"
#include "tipi.h"


extern char linea_cor[];
extern char codstring[];

#define lun_codif  5

prstringa(stringa,j,M,spiazzPC, LUNGSTR)
char *stringa;
short *j,*M,*spiazzPC;
short LUNGSTR;
{
short lstring;
memcpy(&stringa[(*j)],codstring,lun_codif);	// copia sulla riga file 
														// intermedio il codice
														// di stampa stringa
(*spiazzPC)++;
			
(*j)+=lun_codif;    	    // si posiziona dopo la codifica sulla riga del
							 // file intermedio
							 // calcola la lunghezza della stringa
if((lstring=strchr(&linea_cor[(*M)+1],VIRGOLETTE)-&linea_cor[(*M)+1])>=1)
		                                      // se trova le virgolette di
														  // chiusura copia la stringa
														  // sulla riga.
	{
	stringa[(*j)++]=BLANK;
	sprintf(&stringa[(*j)],"$%04x",lstring);	 // scrive la lung.stringa
	(*j)+=lun_codif;     // si posiziona dopo la codifica di lung.string
	stringa[(*j)++]=BLANK;
	if((*j)+lstring >= LUNGSTR-2)
	{
		stampa_err(45,0,"0");    /* stringa troppo lunga */
		return;
	}
	do
		stringa[(*j)++]=linea_cor[(*M)++];	// copia la stringa
	while(linea_cor[(*M)]!=VIRGOLETTE);	// copia la stringa

	if(lstring%2)	  // se la stringa Š di lunghezza dispari
						  // aggiunge un blank per allinearla alla
						  // word.
		{
		stringa[(*j)++]=BLANK;
		lstring++;			 // lunghezza occupata realmente dalla stringa
		}
	stringa[(*j)++]=linea_cor[(*M)++];	// copia le " finali e si posiziona
													// al carattere successivo.
		(*spiazzPC)+=lstring/2;	      // incremento lo spiazzamento del 
												// program counter dell n. di word
												// occupate dalla stringa
	}
}


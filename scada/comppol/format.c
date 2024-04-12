/*
   modulo format.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)format.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/* -> FORMAT.C
 *       vede se ä un format di stampa	 (compreso stampa di blank)
 *       e prepara la eventuale riga per il file intermedio nella
 *       forma:
 *           . Per stampa di blank
 *                   $codifica_stampa_blank   $numero_di_blank
 *           . Per stampa valore di variabile (con format mm.nn)
 *                   $codifica_stampa_var   $tipo_mm_nn  nome_variabile 
 *       riceve come parametri:
 *           puntatore alla stringa in cui si sta inserendo il codice intermedio
 *           il puntatore all'indice che scandisce la stringa.
 *       ritorna :
 *           . -1 se errore
 *				 . 0 se OK
 */
#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "chascii.inc"
#include "tipi.h"

#ifdef INGLESE
#define  stinor      "For st, in, or types format is: mm.0"
#define  blankNum    "0 < blanks <80"
#else
#define  blankNum    "il numero di spazi deve essere > 0 e < 80"
#define  stinor      "Per tipi st, in, or formato ammesso: mm.0"
#endif

extern char linea_cor[];
extern char codspaces[];
extern char codformat[];
#define lun_codif  5

format(stringa,j,M,spiazzPC)
char *stringa;
short *j,*M,*spiazzPC;
{
static char vet_term[]=       // vettore dei terminatori ammessi per delimitare
                        // il nome di variabile
		 {CHQUADRA,APTONDA};
short num1,num2;         // valori ricavati dalla decodifica del format
short ier,tipo,dim,ind,i;
char nomevar[LUNG_VAR+1];
static char term[4]={'[',PUNTO,'X',-1};    // vettore contenente i terminatori
static short tipiamm[6]={tintero,tanalogico,torgano,treale,tstringa,-1};
char nomeform1[3];       // conterrÖ il format prima parte
char nomeform2[3];       // conterrÖ il format seconda parte

ier=estrnome(&linea_cor[*M],nomeform1,2,term,sizeof(term),0);
if(ier)   // se non si ä trovato il nome 
	stampa_err(6,0,"0");    /* errore di sintassi */


(*M)+=strlen(nomeform1);         // si posiziona sul il terminatore
											// che puï essere '.' o  'x' o  '['
switch(linea_cor[*M])
	{
	case 'X':		// sono nel caso di 'nnx' ciä spazi blank 

		i=0;			 // controlla che la stringa sia formata da cifre
		while(nomeform1[i]!=0)
		{ 
		if(!isdigit(nomeform1[i++]))  
			{stampa_err(61,0,"0");return;} 
		}

		num1=atoi(nomeform1);	  // torna 0 se la conversione non riesce
		if(num1<=0 || num1>80 )   // verifica che il numero degli spazi sia nel
										  // range corretto
			stampa_err(61,1,blankNum);  

/*  verifica che la x sia seguita da ','o da ')'   */
		(*M)++;
		if(linea_cor[*M]!=',' && linea_cor[*M]!=')')
			stampa_err(6,0,"0");    /* errore di sintassi */
		memcpy(&stringa[*j],codspaces,lun_codif);	// copia sulla riga file 
																// intermedio il codice
																// di stampa spazi
		(*spiazzPC)++;				 // incrementa spiazzamento program counter
		(*j)+=lun_codif;    	    // si posiziona dopo la codifica sulla riga del
									 // file intermedio
		stringa[(*j)++]=BLANK;
		(*j)+=sprintf(&stringa[*j],"$%04x",num1);	 // scrive il numero di blank
		return(0);
		break;
	case '.':	  // caso di format del tipo mm.nn
					  // ä necessario  controllare che mm <= 15 e che 
					  // nn <= mm-2 .

		i=0;			 // controlla che la stringa sia formata da cifre
		while(nomeform1[i]!=0)
		{ 
		if(!isdigit(nomeform1[i++]))  
			{stampa_err(61,0,"0");return;} 
		}


		(*M)++;			  // si posiziona dopo il '.'

/* estrae il secondo valore di specifica formato (nn)	considerando come
   terminatore ammesso soltanto '[': -> alla funzione estrnome viene 
	passato come numero di terminatori da considerare il valore 1
	(ultimo parametro della funzione )     */

		ier=estrnome(&linea_cor[*M],nomeform2,2,term,1,0);
		(*M)+=strlen(nomeform2);   // di posiziona sul terminatore
		if(ier)   // se non si ä trovato il nome o se si ä
			stampa_err(6,0,"0");    /* errore di sintassi */
	
		i=0;			 // controlla che la stringa sia formata da cifre
		while(nomeform2[i]!=0)
		{ 
		if(!isdigit(nomeform2[i++]))  
			{stampa_err(61,0,"0");return;} 
		}

/*
	Estrazione del nome della variabile specificata tra [  ].
*/
		(*M)++;    // si posiziona sul primo carattere della variabile
		ier=estrnome(&linea_cor[*M],nomevar,LUNG_VAR,vet_term,2,1);	// estrae il nome della variabile
												   // N.B. il nome viene estratto senza eventuale 
												   // indice di specificazione elemento

		if(ier || !strlen(nomevar)) {stampa_err(58,0,"0");return(-1);} // nome variabile scorretto o mancante 
		(*M)+=strlen(nomevar);         // si posiziona sul il terminatore
/*
   se il nome ä corretto cerca se corrisponde ad una variabile 
   definita.
*/
		tipo=cerca(testa,nomevar,&dim,&ind);	 // cerca il nome nella
  															 // simbol table.
		if(tipo==-1)   // variabile non definita
			{stampa_err(59,0,"0");return(-1);}
		if(tipo>=16)
			cnome(nomevar,&tipo,M);  // modifica il nome nel caso di
											  // nome locale a subroutine.
		controlla(nomevar,M,tipo);  // controlla la correttezza dell'indice
											  // della variabile (se specificato) nei
											  // confronti della dimensione della 
											  // stessa e lo appende a nomevar.
											  // Dopo la chiamata della funzione
											  // M punta al carattere seguente la ')'
		if(linea_cor[*M]==']')  (*M)++;  // salto la chiusura
		else {stampa_err(6,0,"0"); return(-1);}   /* errore di sintassi */
  		if(!ctrtipo(tipo,tipiamm))    // se il tipo della variabile
											  // non ä tra quelli ammessi.
		     {stampa_err(60,0,"0"); return(-1);}

		num1=atoi(nomeform1);	  // torna 0 se la conversione non riesce
/*
	In tutti i casi tranne quello di tipo stringa il primo campo del 
	format (num1) deve essere <=15.
*/
		if(num1 > 15 && tipo!=tstringa)  
			{		// formato di stampa scorretto
			stampa_err(61,1,"format mm.nn ; 0 < mm <=15"); 
			return(-1);    // non si ä trovato il format 
			}

/*
	Nel caso di tipo stringa il primo campo del format (num1) deve essere <=80.
*/
		if(num1 > 80 && tipo==tstringa)  
			{		// formato di stampa scorretto
			stampa_err(61,1," mm.0 ; string - mm <=80"); 
			return(-1);    // non si ä trovato il format 
			}

		num2=atoi(nomeform2);	  // torna 0 se la conversione non riesce
/* 
	Controlla che nel caso il tipo della variabile sia intero organo o stringa
	il formato sia specificato come mm.0
*/
		if (tipo==tintero || tipo==tstringa || tipo==torgano)
			{
			if( num2 )
				{stampa_err(61,1,stinor); return(-1);}
			}
/*
	Controlla nel caso di tipo float
*/
		else 	if(num2<0 || num2 > num1-2)   // verifica che il numero degli spazi sia nel
						                        // range corretto cioä  0 <=num2<= num1-2.
			{		// formato di stampa scorretto
			stampa_err(61,1,"format mm.nn ;  0 < nn <=(mm-2) "); 
			return(-1);   
			}
/*
	Procede alla scrittura sulla riga di: 
         .  codice della istruzione di format		
	      .  tipo della variabile
			.  formato di stampa  (mm nn)
			.  nome della variabile
*/

	   memcpy(&stringa[*j],codformat,lun_codif);	// copia sulla riga file 
																// intermedio il codice
																// di format
		(*spiazzPC)++;				 // incrementa spiazzamento program counter
		(*j)+=lun_codif;    	    // si posiziona dopo la codifica sulla riga del
										 // file intermedio
		stringa[(*j)++]=BLANK;
/* scrive il tipo (occupazione 1 short)	*/
		(*j)+=sprintf(&stringa[*j],"$%02x",tipo);

/* scrive la codifica del format:

			 - nel caso di intero, stringa o organo (== format sicuramente del
				tipo num1.0) scrive num1 su uno short.
			 - negli altri casi (format del tipo num1.num2) scrive su byte
				i due valori di num1 e num2
*/
		if( (tipo==tintero || tipo==tstringa || tipo==torgano))
			(*j)+=sprintf(&stringa[*j],"%02x",num1);
		else
			{
			(*j)+=sprintf(&stringa[*j],"%1x",num1);
			(*j)+=sprintf(&stringa[*j],"%1x",num2);
			}
		stringa[(*j)++]=BLANK;

		(*spiazzPC)++;
		(*j)+=sprintf(&stringa[*j],"%s",nomevar);	  // scrive sulla riga del
																  // file intermedio il nome
																  // della variabile.
		return(0);
		break;
	}
}		

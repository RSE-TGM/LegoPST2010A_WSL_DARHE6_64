/*
   modulo prgraf.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)prgraf.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/* -> PRGRAF.C
 *      Provvede alla scrittura sul file intermedio :
 *        - per la routine GRAF
 *      		  . scrive il numero di argomenti relativi
 *            . inizializza una nuova riga
 *        - per la routine SGRAF 
 *            . decodifica i due valori di limite alto e basso
 *              per il grafico
 *				  . li scrive sulla riga ed inserisce la riga nel
 *					 file intermedio
 */

#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "chascii.inc"
#include "tipi.h"
#include "ctrprint.inc"

#define MAX_NVAR 6	// numero massimo di variabili ammesse nella istruzione
							// GRAF
extern char linea_cor[];
extern RECPRINT tabprint[];
extern int errori;

prgraf(stringa,j,M,spiazzPC,ind_tab)
char *stringa;
short *j,*M,*spiazzPC;
short ind_tab;       // indice corrispondente alla posizione in tabprint
						   // della istruzione da considerare.
{
char nomevar[MAX_NVAR][LUNG_VAR+1];
static char vet_term[]=       // vettore dei terminatori ammessi per delimitare
                             // il nome di variabile
		 {CHQUADRA,VIRGOLA};
short ivar,i,ier;
short tipo,dim,ind;
static short flag_sgraf;    // flag utilizzato per stabilire se prima di
									 // una istruzione GRAF c'Š stata una istruz.
									 // SGRAF che definisce la scala. Se ci• non
									 // avviene verra segnalato un errore.
char term;
#define LUNG_LIM 7  // massima lunghezza in caratteri ammessa per i
						  // limiti della SGRAF ; poiche si prevedono limiti
						  // compresi nel range -32768   +32768  ( verranno
						  // rappresentati ciascuno con uno short) la lunghezza
						  // massima della stringa che li contiene (compreso il
						  // terminatore ) sara di 7 bytes.
char lim_basso[LUNG_LIM];	 // limiti basso e alto di fondo scala
char lim_alto[LUNG_LIM];
short basso,alto;
/*
		Istruzione SGRAF.
*/
if(ind_tab == i_sgraf)     
	{
	if(linea_cor[(*M)]!=APQUADRA)
		stampa_err(6,0,"0");    /* errore di sintassi */
	else (*M)++;				 // si posiziona all'inizio dell limite basso
	term=',';                // accette come terminatore del limite basso
									 // la virgola.
									 // Estrae il limite basso.
	if(estrnome(&linea_cor[(*M)],lim_basso,LUNG_LIM,&term,1,0))
		{stampa_err(6,0,"0");return;}    /* errore di sintassi */
	term=']';
	(*M)+=strlen(lim_basso)+1;         // si posiziona dopo il terminatore
	if(estrnome(&linea_cor[(*M)],lim_alto,LUNG_LIM,&term,1,0))
		{stampa_err(6,0,"0");return;}    /* errore di sintassi */
	(*M)+=strlen(lim_alto)+1;         // si posiziona dopo il terminatore

/*   controlla i valori dei limiti estratti   */
	i=0;
	if(lim_basso[i]=='-' || lim_basso[i]=='+') i++;
	while(lim_basso[i]!=0)
		{ 
		if(!isdigit(lim_basso[i++]))  
			{stampa_err(62,0,"0");return;}    /* limiti di trend scorretti */
		}
	i=0;
	if(lim_alto[i]=='-' || lim_alto[i]=='+') i++;
	while(lim_alto[i]!=0)
		{ 
		if(!isdigit(lim_alto[i++]))  
			{stampa_err(62,0,"0");return;}    /* limiti di trend scorretti */
		}


	if( sscanf(lim_basso,"%d",&basso)!=1  || sscanf(lim_alto,"%d",&alto)!=1)
		{stampa_err(62,0,"0");return;}    /* limiti di trend scorretti */

	if(basso >= alto)
		{stampa_err(62,0,"0");return;}    /* limiti di trend scorretti */

	stringa[(*j)++]=BLANK;
	(*j)+=sprintf(&stringa[(*j)],"$%04x",basso); // scrive sulla riga del file intermedio
	stringa[(*j)++]=BLANK;
	(*j)+=sprintf(&stringa[(*j)],"$%04x",alto); // scrive sulla riga del file intermedio

/*  setta a 1 il flag che indica che si Š trovata l'istruzione sgraf  */
	flag_sgraf=1;  
	(*spiazzPC)+=2;     // incrementa lo spiazzamento program counter
	}
/*
		Istruzione GRAF.
*/
else		  
	{
	if(linea_cor[(*M)]!=APQUADRA)
		{stampa_err(6,0,"0");return;}    /* errore di sintassi */
	else (*M)++;				 // si posiziona all'inizio del nome
	ivar=0;       // indice che scorre la matrice dei nomi delle variabili
	if(flag_sgraf==0)			// caso di istruzione GRAF senza precedente
									// istruzione SGRAF
		stampa_err(64,0,"0");  
/*
  		Ciclo per l'estrazione delle variabili
*/
	while(ivar < MAX_NVAR)
		{
                                 // estrae il nome della variabile
										   // N.B. il nome viene estratto senza eventuale 
										   // indice di specificazione elemento

		ier=estrnome(&linea_cor[(*M)],&nomevar[ivar][0],LUNG_VAR,vet_term,2,1);
		
		(*M)+=strlen(&nomevar[ivar][0]);         // si posiziona sul il terminatore
								    // nome variabile scorretto o mancante 
		if(ier || !strlen(&nomevar[ivar][0])) {stampa_err(58,0,"0");return;}
		if(!ier)   // se il nome Š corretto cerca se corrisponde ad una variabile 
					  // definita.
			{
			tipo=cerca(testa,&nomevar[ivar][0],&dim,&ind);	 // cerca il nome nella
														         		 // simbol table.
			if(tipo==-1)   // variabile non definita
				stampa_err(59,0,"0");
			else           // variabile definita
				{
				if(tipo>=16)
					cnome(&nomevar[ivar][0],&tipo,M);  // modifica il nome nel caso di
													  // nome locale a subroutine.

				if(!ctrtipo(tipo,tabprint[ind_tab].tipamm))	// se il tipo della variabile
																			// non Š tra quelli ammessi.
					stampa_err(60,0,"0");

				if(linea_cor[(*M)]==']') {(*M)++;break;}  // salto la chiusura
																		 // ed esco dal ciclo
				else if(linea_cor[(*M)]==',') {(*M)++;ivar++;}  // salto la chiusura
				else {stampa_err(6,0,"0");return;}      // errore di sintassi 
																	 // esco dalla routine

				}
			}
		}
	if(linea_cor[(*M)-1]!=']')  // se si Š usciti per raggiungimento di
										 // massimo numero di variabili e non si
										 // Š alla fine della lista (non c'Š ']')
	    {stampa_err(63,0,"0");return;}      // troppi argomenti 
/*
	Scrittura sul file intermedio
*/
                          // scrive il numero di variabili da rappresentare
	stringa[(*j)++]=BLANK;
	(*j)+=sprintf(&stringa[(*j)],"$%04x",ivar+1); 
	(*spiazzPC)++;
								  // scrive i nomi delle variabili
	for(i=0;i<=ivar;i++)
		{
		(*spiazzPC)++;
		stringa[(*j)++]=BLANK;
		(*j)+=sprintf(&stringa[(*j)],"%s",&nomevar[i][0]);	 
		}
	}
}

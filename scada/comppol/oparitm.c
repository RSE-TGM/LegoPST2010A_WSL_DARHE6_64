/*
   modulo oparitm.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)oparitm.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*								                                             *
*			   File OPARITM.C			                                    *
*								                                             *
* 			PROCEDURE CONTENUTE 			                                 *
*								                                             *
*	aritmetic(codice)                 		                           *
*			int codice;                     	                           *
*								                                             *
*	legginvar(nomevar,codice,M,ciclo)                                 *
*			char nomevar[];                                             *
*			int codice;                                                 *
*			int *M;                                                     *
*			int ciclo;                                                  *
*								                                             *
*	assegna(codice)                                                   *
*			int codice;                                                 *
*								                                             *
*	procstack(codice)  	                                             *
*			int codice;                                                 *
*								                                             *
*	controlla(nomevar,M,tipovar_cost)                                 *
*			char nomevar[];                                             *
*			int *M;                                                     *
*			int tipovar_cost;                                           *
*								                                             *
*********************************************************************/

#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include "chascii.inc"

#include "tipi.h"

extern char linea_cor[];
extern int nword_o;
extern int subrcorr;


/*********************************************************************
*								                                             *
*			Procedura aritmetic 			                                 *
*								                                             *
*  La procedura viene chiamata per analizzare e produrre il codice,  *
* se l' istruzione e' corretta, di una operazione tra interi o reali.*
*  L' intero passato alla procedura rappresenta il codice della      *
* istruzione ed e' compreso tra 64 e 84 o tra 107 e 111 compresi.    *
*  La procedura e' suddivisa in tre parti, a seconda del numero      *
* degli argomenti che l' istruzione deve avere ( 1, 2, 3 );          *
* verifica che gli stessi siano in numero giusto e compatibili, e,   *
* se tutto e' ok, inserisce nella lista l' istruzione con gli        *
* indirizzi degli operandi, altrimenti chiama la routine di errore.	*			                     *
*								                                             *
*********************************************************************/

aritmetic(codice)
int codice;
{
char nomevar[LUNG_VAR+1],temp[6];
int M,i,ciclo=0,tipo[3],dim[3],ind[3];
int sem,cicloleggi,flgciclo;

tipo[0]=-2;

/*
	Test per determinare il numero di operandi della funzione
*/

if( codice < 72 || codice==107 || codice==128 ) 	  
	{

	/* Operazione con tre operandi */

	M=5;

	ciclo = 0;
	flgciclo = 0;
	cicloleggi = ciclo;

	while ( flgciclo == 0 )  	// ciclo di lettura argomenti

		{

		sem=legginvar(nomevar,codice,&M,cicloleggi);

		if(sem==-1) 	 // se errore in lettura forza l'uscita dal ciclo
			{
			flgciclo=1;
			tipo[0]=-2;
			}

		else  			 // lettura corretta
			{

			if ( ciclo <= 2 ) {

				tipo[ciclo]=cerca(testa,nomevar,&dim[ciclo],&ind[ciclo]);

				if(tipo[ciclo]>=16)
					cnome(nomevar,&tipo[ciclo],&M);

				controlla(nomevar,&M,tipo[ciclo]);
				ciclo++;
				M++;

				if (ciclo == 3 ) {

					cicloleggi = 2;

					}

				else {

					cicloleggi = ciclo;

					}

				}

			else {

				/* Superato numero di argomenti previsti */

					if ( strlen(nomevar) != 0 ) {

						flgciclo = 1;

						stampa_err(11,1,par_chiav[codice]);

					}

					else {

						flgciclo = 1;

					}

				}

	 		}
		}

	M=0;

	if (codice != 128) {

		/* Operazioni tra (analogici o reali) oppure (organi o interi) */

		if((codice%2)==0 || codice==107) {

			/* operazione tra reali o analogici */

			if((tipo[0]==3 || tipo[0]==0) &&
		   	(tipo[1]==3 || tipo[1]==0) &&
		   	(tipo[2]==3 || tipo[2]==0))
					M=1;
		}
		else

			/* operazione tra interi o organi */

			if((tipo[0]==4 || tipo[0]==2) &&
		   	(tipo[1]==4 || tipo[1]==2) &&
		   	(tipo[2]==4 || tipo[2]==2))
					M=1;

		}

	else {

			/* operazione SUMS di somma di stringhe (codice = 128) */

			if( (tipo[0]==7) &&
		   	 (tipo[1]==7) &&
		   	 (tipo[2]==7) )
					M=1;

	}

	if(M)
		intfile(codice);
	else
		if(tipo[0]!=-2)
			stampa_err(12,1,par_chiav[codice]);
	}  /* fine caso codice < 72 */
else
	if(codice==72 || codice==73) {
		M=5;
		for(i=0;linea_cor[M]!=BLANK && linea_cor[M]!=0x00 &&
			linea_cor[M]!=APTONDA && i<EF_LUNGVAR; M++)
				nomevar[i++]=linea_cor[M];
		nomevar[i]='\0';
		if(linea_cor[M]==APTONDA)  {
 	}
		while(linea_cor[M]!=BLANK &&
		linea_cor[M]!=0x00 && linea_cor[M]!=VIRGOLA)
			M++;
		if(linea_cor[M]==BLANK)
			M++;
		if(linea_cor[M]!=0x00)
			stampa_err(11,1,par_chiav[codice]);
		else  {
			tipo[0]=cerca(testa,nomevar,&dim[0],&ind[ciclo]);
			if(tipo[0]>=16)
				cnome(nomevar,&tipo[0],&M);
			controlla(nomevar,&M,tipo[0]);
			if((codice==72 && (tipo[0]==3 || tipo[0]==0)) ||
			   (codice==73 && (tipo[0]==4 || tipo[0]==2)))
				intfile(codice);
			else
				stampa_err(12,1,par_chiav[codice]);
		}
	}  /* fine caso 72 <= codice <= 73  */
	else {
		for(M=0;linea_cor[M]!=BLANK && linea_cor[M]!=0x00;M++)
			;
		M++;

		ciclo = 0;
		flgciclo = 0;
		cicloleggi = ciclo;

		while ( flgciclo == 0 )  {

			sem=legginvar(nomevar,codice,&M,cicloleggi+1);

			if(sem==-1)  {
				flgciclo=1;
				tipo[0]=-2;
			}

			else  {

				if ( ciclo <= 1 ) {

					tipo[ciclo]=cerca(testa,nomevar,&dim[ciclo],&ind[ciclo]);

					if(tipo[ciclo]>=16)
						cnome(nomevar,&tipo[ciclo],&M);

					controlla(nomevar,&M,tipo[ciclo]);
					ciclo++;
					M++;

					if (ciclo == 2 ) {

						cicloleggi = 1;

						}

					else {

						cicloleggi = ciclo;

						}

					}

				else {

					/* Superato numero di argomenti previsti */

						if ( strlen(nomevar) != 0 ) {

							flgciclo = 1;

							stampa_err(11,1,par_chiav[codice]);

						}

						else {

							flgciclo = 1;

						}

					}

		 		}
			}

		M=0;
		if(codice>=78) { /* operazione tra reali o analogici */
			if((tipo[0]==3 || tipo[0]==0) &&
			   (tipo[1]==3 || tipo[1]==0))
				M=1;
		}
		else
			if((codice%2)==0) {   /* operazione tra reali o analogici */
				if((tipo[0]==3 || tipo[0]==0) &&
				   (tipo[1]==3 || tipo[1]==0))
					M=1;
			}
			else                 /* operazione tra interi o organi */
				if((tipo[0]==4 || tipo[0]==2) &&
				   (tipo[1]==4 || tipo[1]==2))
					M=1;

		if(M)
			intfile(codice);
		else
			if(tipo[0]!=-2)
				stampa_err(12,1,par_chiav[codice]);
	}  /* fine caso codice > 73 */
}

/*********************************************************************
*								                                             *
*			Procedura legginvar                                         *
*                                                                    *
*  La procedura viene chiamata per leggere dalla stringa linea_cor,  *
* i nomi (2 o 3) delle variabili che costituiscono l' espressione    *
* aritmetica, ne trova una alla volta e se riscontra un errore       *
* (tipo fine stringa non attesa ) ritorna -1, viceversa 0.           *
*                                                                    *
*********************************************************************/

legginvar(nomevar,codice,M,ciclo)
char nomevar[];	  // nome variabile (di ritorno)
int codice;			  // codice dell'istruzione
int *M;				  // puntatore da cui iniziare a leggere i nomi
						  // (punta all'interno di linea_corr sul primo
						  // carattere appartenente al nome della variabile).
int ciclo;
{
int i,temp=0;

for(i=0;linea_cor[*M]!=BLANK && linea_cor[*M]!=0x00 &&
linea_cor[*M]!=VIRGOLA && linea_cor[*M]!=APTONDA &&
((subrcorr==-1 && i<EF_LUNGVAR) || (subrcorr!=-1 && i<LUNG_VAR)); (*M)++)
		nomevar[i++]=linea_cor[*M];	  // copia il nome in nomevar
nomevar[i]='\0';
	if(linea_cor[*M]==APTONDA)  {
		temp=*M;
}

while(linea_cor[*M]!=VIRGOLA && linea_cor[*M]!=0x00)
	(*M)++;

if(linea_cor[*M]==0x00 && ciclo!=2) {		// ha trovato una sola variabile
	if(codice!=-1)
		stampa_err(11,1,par_chiav[codice]);
	else
		stampa_err(11,1,"MOVP");
	return(-1);
}
if(temp!=0)			 // se Š specificato un elemento di variabile
						 // vettoriale (..) esce con M puntato su (
	*M=temp;
return(0);
}

/*********************************************************************
*                                                                    *
*			Procedura assegna			      										*
*                                                                    *
*	La procedura viene chiamata per compilare le istruzioni di   		*
* assegnamento ,immediato o tra variabili. La procedura legge una    *
* variabile alla volta, e controlla che sia di tipo ammissibile con  *
* l' operazione indicata.                                            *
*                                                                    *
*********************************************************************/

assegna(codice)
int codice;
{
char nomevar[LUNG_VAR+1],valore[81];
int tipo,dimvett,ciclo=0,indvett,temp=-1,i=0,M,ok,d,salva;

if(codice==57)			 // si posiziona dopo la parola chiave ( M scorre la
							 // riga di codice).
	M=6;
else
	M=5;
//      Cicla una volta per ogni argomento    
while (ciclo<2) {		 
	while(linea_cor[M]==BLANK)		 // se ci sono spazi avanza
		M++;
	ok=legginvar(nomevar,codice,&M,ciclo+1);
	if(ok==-1) {						// errore nel numero di argomenti:
		ciclo=3;                   // fine riga inaspettata 
		tipo=-2;
	}
	else {							   // nome trovato correttamente

//     Cerca la variabile nell'albero della simbol table e ne 
//     ricava il tipo.

		tipo=cerca(testa,nomevar,&dimvett,&indvett);
		if(tipo>=16)		 // vede se la variabile Š locale a una subroutine
			cnome(nomevar,&tipo,&M);	 // aggiunge al nome l'indice relativo
												 // alla subroutine corrente 
		controlla(nomevar,&M,tipo);
		M++;
	}
	if(!(codice==56 || codice==57)) {
if(!(((tipo==3 || tipo==0) && (codice==53 || codice==55)) ||
     ((tipo==4 || tipo==2) && (codice==52 || codice==54)) ||
      (tipo==7 && (codice==105 || codice==106)) || codice==-1))
			stampa_err(12,1,par_chiav[codice]); /* tipo operatore non corretto */
		if(codice==54 || codice==55 || codice==106) {
			i=1;
			break; /* se assegnamento immediato esco
				  dal ciclo per leggere e controllare
				  il valore da inserire */
		}
		if(codice==-1) {  /* caso MOVP */
			if(ciclo==0)
				if(tipo==9 || tipo==10 || tipo==11 || tipo==12 || tipo == 15)
/* salvo il tipo del primo op. */	temp=tipo;
				else
					stampa_err(12,1,"MOVP");
			else
				if(temp!=-1) {/* controllo che i due operatori siano uguali */	
					if(!(temp==tipo ))
						stampa_err(12,1,"MOVP");
				}
				else
/* controllo il secondo anche */	if(!(tipo==9 || tipo==10 || tipo==11|| tipo==12)) {
/* se il primo e' sbagliato   */
						stampa_err(12,1,"MOVP");
					}
		}
	}
	else {
		if(ciclo==0) {
			if(!((codice==57 && (tipo==2 || tipo==4)) ||
			      codice==56 && (tipo==0 || tipo==3)))
				stampa_err(12,1,par_chiav[codice]);
			/* tipo operatore non corretto */
		}
		else {
			if(!((codice==56 && (tipo==2 || tipo==4)) ||
			      codice==57 && (tipo==0 || tipo==3)))
				stampa_err(12,1,par_chiav[codice]);
			/* tipo operatore non corretto */
		}
	}
	ciclo++;
}
if(i==1 && ciclo!=3) {
	M--;
	togliblank(linea_cor,M);
	while(linea_cor[M]!=VIRGOLA)
		M++;
	salva=++M;
	for(i=0;linea_cor[M]!=0x00;M++)
		valore[i++]=linea_cor[M];
	valore[i]=0x00;
	if(codice==54) {  /* verifico che il valore sia corretto */
		if((ok=isintero(valore))!=1)
			stampa_err(17,1,nomevar);
	}
	else
		if(codice==55) {
			if((ok=isreale(valore))!=1)
				stampa_err(18,1,nomevar);
/* controllo che il numero passato sia un reale, e se e' scritto come
   un intero, gli aggiungo il punto decimale per disinguerlo */
			if((ok=isintero(valore))==1) {
				if(linea_cor[M]==0x00)
					linea_cor[M+1]=0x00;
				linea_cor[M]=0x2e;
				}
			}
		else {   /* caso stringa */
			if(valore[0]!=VIRGOLETTE) {
/* mancano " iniziali */	stampa_err(19,0,"0");
				return;
			}
			for(i=1;valore[i]!=VIRGOLETTE && valore[i]!=0x00;i++)
				;
			if(valore[i]==0x00) {
/* mancano " finali */		stampa_err(6,0,"0");
				return;
			}
			if((i-1)>dimvett) {
				stampa_err(45,0,"0");
				return;
			}
			if((i%2)==1)    /* se nø di caratteri dispari */
				valore[i++]=' ';  /* inserisco 1 terminatore */
			valore[i]='#'; /* inserisco fine stringa */
			valore[i+1]=0;
			nword_o+=3 + (i/2);  /* 3 = PC, VAR. ADDRESS, LUNG. STRINGA */
 				     /* i/2 = word occupate dalla stringa */
			sprintf(&linea_cor[salva],"%d",i);
			strcat(linea_cor,",");
			strcat(linea_cor,valore);
		}
}
if(codice==-1)
	codice=53;
intfile(codice);
}


/*********************************************************************
*                                                                    *
*       Procedura procstack                                          *
*                                                                    *
*********************************************************************/

procstack(codice)
int codice;
{
int sem=0,M,i,tipo,dimvett,indvett;
char nomevar[LUNG_VAR+1];
if(codice==43 || codice==42)
	M=6;
else
	M=5;
while(linea_cor[M]==BLANK)
	M++;
legginvar(nomevar,codice,&M,2);
if(!(codice==42 || codice==43)) {
	tipo=cerca(testa,nomevar,&dimvett,&indvett);
	if(tipo>=16)
		cnome(nomevar,&tipo,&M);
	controlla(nomevar,&M,tipo);
	if(((codice%2)==0 && (tipo==2 || tipo==4)) ||
	   ((codice%2)==1 && (tipo==0 || tipo==3)))
		sem=1;
}
else {
	if(codice==42)  {
		if((isintero(nomevar))==1)
			sem=1;
	}
	else
		if((isreale(nomevar))==1)
			sem=1;
}
if(sem==1)
	intfile(codice);
else
	stampa_err(12,1,nomevar); /* operatore non corretto */
}

/*********************************************************************
*          							                                       *
*			Procedura controlla                                         *
*                                                                    *
*	La procedura controlla che la variabile passata in nomevar        *
* sia stata definita, e se si tratta di un vettore, ne controlla la  *
* dimensione per vedere se si fa riferimento ad un campo ammissibile.*
*                                                                    *
*********************************************************************/

controlla(nomevar,M,tipovar_cost)
char nomevar[];
int *M;
int tipovar_cost;
{
int tipoaus=-1,d=0,tipo,i,dimvett,indvett,ok;
char valore[81];

if(tipovar_cost==4)
	tipoaus=2;
if(tipovar_cost==3)
	tipoaus=0;
//  cerca la variabile nella simbol table e ne determina il tipo

tipo=(cerca(testa,nomevar,&dimvett,&indvett) & 15);

if(!(tipo==tipovar_cost || (tipo==tipoaus && tipo!=-1))) {
	if(tipo==-1)
		stampa_err(4,1,nomevar);  /* variabile non trovata */
	else
		stampa_err(12,1,nomevar);  /* tipo errato */
	return(-1);
}
if(linea_cor[*M]==APTONDA) {			// vede se Š un vettore
	for(i=0,(*M)++;linea_cor[*M]!=CHTONDA && i<4; (*M)++)
		valore[i++]=linea_cor[*M];		 // copia in valore i caratteri compresi
												 // tra '(' e ')'.
// aggiunge a nomevar le parentesi e il valore

	valore[i]=0x00;
	for(i=0;nomevar[i]!=0x00;i++)
			;
	nomevar[i++]=APTONDA;
	sprintf(&nomevar[i],"%s",valore);
	for(i=0;nomevar[i]!=0x00;i++)
			;
	nomevar[i++]=CHTONDA;
	nomevar[i]=0x00;

	(*M)++;			 // si posiziona dopo la chiusura della parentesi
	if((ok=isintero(valore))==1)	  // vede se il valore compreso tra le 
											  // parentesi corrisponde ad un intero
		d=atoi(valore);
	else {								// errore: non corrisponde a un intero
			stampa_err(17,1,nomevar);
			return(-1);
	}
	if(d>dimvett || d==0) {
/* si fa riferimento ad una componente del vettore inesistente */
		stampa_err(8,1,nomevar);
		return(-1);
	}
}
return(d);
}

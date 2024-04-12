/*
   modulo opgruppi.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)opgruppi.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <osf1.h>
#include <stdio.h>

#include "chascii.inc"

#include "tipi.h"
#include "data_tip.h"

#define  LUNGSTR	60
#define  POS1		 3
#define  POS2		10
#define VAL_MAX_AN_RW 60

extern char linea_cor[];
extern char *par_chiav[];
extern int nword_o;
extern int righeint;
extern int fdint;
extern int wordpar_ch[];

char *zona[]={ "S","I","W",};
char *color[]={"B","R","G","Y","L","M","C","W"};


/*********************************************************************
*          							     *
*			Procedura opgruppi                           *
*          							     *
*	La procedura viene chiamata per risolvere le istruzioni      *
* "ROTG", "MOVG", "SCALG"; controlla che gli argomenti passati siano *
* corretti e, se lo sono, inserisce la riga nel file intermedio.     *
*          							     *
*********************************************************************/

opgruppi(codice)
int codice;
{
int tipo,dim,ind,sem=1,ok,i,M,j,LIM1=640,LIM2=480;
char nomevar[LUNG_VAR+1];
if(codice==114)
	M=6;
else
	M=5;
for(i=0;i<4;i++) {
	legginvar(nomevar,codice,&M,2);    /* leggo l' ultimo argomento */
	ok=cerca(testa,nomevar,&dim,&ind);
	if(ok==-1)  {
		stampa_err(4,1,nomevar);
		sem=-1;
		if(i==2 && codice==112)
			break;
	}
	else {
		if(ok>=16)                        /* se sono in una subroutine  */
			cnome(nomevar,&ok,&M);    /* gli cambio il nome         */
		controlla(nomevar,&M,ok);
		if(i<2) {  /* i primi due argomenti sono sempre interi */
			if(!(ok==4 || ok==2))  {
				stampa_err(12,1,nomevar);
				sem=-1;
			}
		}
		else {
			if(codice==112) {  /* MOVG mi aspetto un gruppo */
				if(ok!=4) {    			  /* controllo che sia un intero */
					stampa_err(29,1,nomevar); /* non e' un intero */
					sem=-1;
				}
				break;
			}
			if(i==2) { /* III argomento ---> reale */
				if(!(ok==0 || ok==3))
					stampa_err(12,1,nomevar);
			}
			else  { /* aspetto il nome del gruppo */
				if(ok!=4) {    			  /* controllo che sia un intero */
					stampa_err(29,1,nomevar); /* non e' un intero */
					sem=-1;
				}
			}
		}
	}
	M++;
}
if(sem)
	intfile(codice);
}


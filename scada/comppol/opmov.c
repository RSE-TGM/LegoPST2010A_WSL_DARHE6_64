/*
   modulo opmov.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)opmov.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	opmov
	Il file contiene i programmi per la compilazione delle istruzioni
	MOVA, MOVR
*/
#include <osf1.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "chascii.inc"
#include "tipi.h"

extern char linea_cor[];
extern int nword_o;
extern int fdint, fdlst;
extern int righeint;
/*********************************************************************
* 																							*
*                       Procedura movgr                              *
*                                                                    *      
*	La procedura si occupa delle decodifica delle istruzioni          *
*  di movimento e di dimensinamento degli oggetti

	MOVA ... (DX,DY)
	MOVR ...	(DX,DY)
	SCALG ... (SCALA, TIPO)
	ROTG  ... (ANGOLO, DX, DY)

	Il nome dell'oggetto e' opzionale, tra parentesi invece sono
	obbligatori gli argomenti di tipo reale (tutti eccetto TIPO)

	Parametri
		codice 	short codice istruzione
		narg		short n. argomenti
		targ		short* vettore tipo argomenti

*********************************************************************/

#define POS1	     3
#define POS2	    10

movgr(codice, narg, targ)
int codice;
short narg;
short targ[];
{
char nomevar[LUNG_VAR+1];
#define LUNGSTR 200
char stringa[LUNGSTR];
short spiazzPC=1;					// n. word occupate dall'istruzione
short tipo;
short j,i;
short M, Msave;
short ok, dim, ind;

memset(stringa,' ',sizeof(stringa));
j=POS1;
j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
stringa[j]=BLANK;
j=POS2;
M=strlen(par_chiav[codice])+1;
j+=sprintf(&stringa[j],"%s",par_chiav[codice]);  /* codice istruzione */
scrivisufile(fdint,stringa,j+1,&righeint);

spiazzPC=1; 				// calcolo program count
memset(stringa,' ',sizeof(stringa));
j=POS1;
j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC, */
stringa[j++]=BLANK;
j=POS2+6;
Msave=M;
legginvar(nomevar,codice,&M,2);
if(strlen(nomevar))								// gruppo specificato
{
	ok=cerca(testa,nomevar,&dim,&ind);
	if(ok>=16)
		cnome(nomevar,&ok,&M);
	controlla(nomevar,&M,ok);
	if(ok!=4)
		stampa_err(29,1,nomevar); /* non e' un gruppo */
	else
		strcpy(&stringa[j],nomevar);
   M=Msave+strlen(nomevar)+1;    // nome gruppo + spazio
}
else				// nome oggetto non presente
{
	strcpy(&stringa[j],"-1");
}
scrivisufile(fdint, stringa, 0,&righeint);
spiazzPC+=1;
/*
		ciclo ricerca nomi variabili 
*/
linea_cor[M]=' ';			// elimino (
togliblank(linea_cor,M);

for(i=0;i<narg;i++)
{
	memset(stringa,' ',sizeof(stringa));
	j=POS1;
	j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC, */
	stringa[j++]=BLANK;
	j=POS2+6;
	legginvar(nomevar,codice,&M,2);
	if(i==narg-1)
	{
		if(nomevar[strlen(nomevar)-1]!=CHTONDA) 
							stampa_err(6,0,nomevar);	 // errore di sintassi
		else nomevar[strlen(nomevar)-1]=0; 
	}
	tipo=cerca(testa,nomevar,&dim,&ind);
	if(tipo>=16)	cnome(nomevar,&tipo,&M);
	controlla(nomevar,&M,tipo);
	M++;
	if(strlen(nomevar))				// variabile definita : deve essere di tipo reale
	{
		memset(stringa,' ',sizeof(stringa));
		j=POS1;
		j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC, */
		stringa[j++]=BLANK;
		j=POS2+6;
		strcpy(&stringa[j], nomevar);
		scrivisufile(fdint,stringa,0,&righeint);
		spiazzPC+=1;
		if(tipo!=targ[i])
   		stampa_err(12,1,nomevar);  	// tipo non accettabile
	}
	else
	{
		stampa_err(6,0,nomevar);	 // errore di sintassi
		break;
	}
}
nword_o+=spiazzPC;  /* aggiorno il PC */
}


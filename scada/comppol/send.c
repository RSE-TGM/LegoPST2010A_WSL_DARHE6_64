/*
   modulo send.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)send.c	1.1
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

#define LUNGSTR	   100
#define POS1	     3
#define POS2	    10

extern char linea_cor[];
extern int nword_o;
extern int fdint;
extern int righeint;
extern int subrcorr;

/*********************************************************************
*          							     *
*			Procedura send
*          							     *
*********************************************************************/

send(codice)
int codice;
{
int temp,nuovariga,j,i,M,s=0,dim,ind,tipo;
int spiazzPC=0,n,aus=0;
char istruz[5];
char stringa[LUNGSTR],nomevar[LUNG_VAR+1];
togliblank(linea_cor,5);
sbianca(stringa,LUNGSTR);
M=6;	/* salto la "(" */
j=POS1;
j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
stringa[j]=BLANK;
j=POS2;
j+=sprintf(&stringa[j],"%s",par_chiav[codice]);  /* inserisco SEND */
scrivisufile(fdint,stringa,j+1,&righeint);
spiazzPC=1; /* comincio a calcolare il codice prodotto da send */
	    /* per ora considero solo il  Codice.istr */
while(1) {
	nuovariga=0;
	if(linea_cor[M]==VIRGOLETTE) { /* caso stringa fra apici */
		sbianca(stringa,15);
		j=POS1;
		j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC, */
		stringa[j++]=BLANK;
		j=POS2+6;
		stringa[j++]=linea_cor[M++]; /* le virgolette iniziali, */
		for(i=0;i<81 && linea_cor[M]!=VIRGOLETTE && linea_cor[M]!=0x00;i++)
			stringa[j++]=linea_cor[M++];  /* la stringa da scrivere */
		if((i%2)==1)  {   /* se il numero di caratteri e' dispari */
			stringa[j++]=BLANK; /* aggiungo un BLANK alla fine */
			i++;      /* ed incremento il numero di caratteri */
			aus=-1;
		}
		stringa[j++]=VIRGOLETTE;   /* virgolette finali */
		stringa[j]=0x00;
		if(linea_cor[M]!=VIRGOLETTE)  
			stampa_err(1,0,"0");  /* errore di sintassi, non ho chiuso le " */
		M++;
/* codice prodotto :
	prima word :
		byte alto :
			0 ( per identificare il tipo di argomento )
		byte basso :
			lunghezza stringa	( in bytes, anche dispari )
	dalla seconda word :
			caratteri ASCII della stringa (sempre in numero PARI) */
		spiazzPC+=(i/2)+1; /* numero caratteri stringa / 2 = word occupate dalla stringa */
		sprintf(&stringa[POS2],"%s","$");
		temp=sprintf(&stringa[POS2+1],"%04x",i+aus); /* lunghezza stringa */
		aus=0;
		stringa[temp+POS2+1]=BLANK;
		scrivisufile(fdint,stringa,j+1,&righeint);
	}
	else
		if(linea_cor[M]==0x00)
			nuovariga=1; 		/*  fine riga */
		else {
			legginvar(nomevar,codice,&M,2);  /* leggo nome var */
/* elimino la ")", se c'e, dall' ultima posizione del nome, parentesi che
	mi ritrovo se l' argomento Š l' ultimo della SEND */
			if(nomevar[strlen(nomevar)-1]==CHTONDA)  {
				M--;
				nomevar[strlen(nomevar)-1]=0x00;
			}
			tipo=cerca(testa,nomevar,&dim,&ind);
			if(tipo>=16)
				cnome(nomevar,&tipo,&M);
			controlla(nomevar,&M,tipo);
/* controllo tipi ed argomenti ed inserisco nel file intermedio */
/* i tipi accettati sono : analogico(0) reale(3) intero(4) stringa(7) e
	i puntatori a analogico(9) digitale(10) e organo(11) */
			if(tipo==-1 || (!(tipo==0 || tipo==3 || tipo==4 || tipo==7 || tipo==9 || tipo==10 || tipo==11 
               || tipo==tdigitale || tipo==tlogico))) {
				if(tipo!=-1)
					stampa_err(12,1,nomevar);  /* errore di sintassi, non ho chiuso le " */
			}
			else {
	 			sbianca(stringa,LUNGSTR-1);
            j=POS1;
   			j+=sprintf(&stringa[j],"%4d",nword_o);
	   		stringa[j]=BLANK;
		   	j=POS2;
				spiazzPC+=2; /* 1 word di formato, 1 word per indirizzo var */
				sprintf(&stringa[j++],"%s","$");

/* determino il formato dell' argomento */
				switch(tipo) {
				case 0 : 	/* analogico */
				case 3 : 	/* reale */
					i=2+256*3;
				break;
            case tlogico:  
            case tdigitale:
               i=2+256*5;
            break;
				case 4 : 	/* intero */
					i=2+256*2;
				break;
				case 7 : 	/* stringa */
					i=2+256;
				break;
				case 9 : 	/* puntatore ad analogico */
				case 10: 	/* puntatore a digitale  */
				case 11: 	/* puntatore ad organo */
					i=2+256*4;
				break;
				}

				j+=sprintf(&stringa[j],"%04x",i); /* formato argomento */
				stringa[j++]=BLANK;
				j+=sprintf(&stringa[j],"%s",nomevar);
				scrivisufile(fdint,stringa,j+1,&righeint);
			}		
		}
	if(linea_cor[M]==0x00)   
		nuovariga=1;
	if(nuovariga==1) {
		while((i=new_lico())==0)
			;
		if(i==-1)
			return(-1);
		/**
		for(n=0;n<4 && linea_cor[n]>=0x41 && linea_cor[n]<=0x5a;n++)
			istruz[n]=linea_cor[n];
		istruz[n]='\0';
		if((strcmp(istruz,"SEND"))!=0) 
			break;
		**/
		M=0;
		togliblank(linea_cor,M);
	}
	else   {
		if(linea_cor[M]==CHTONDA)	/* SEND terminata */
			break;
		if(!(linea_cor[M]==VIRGOLA))
			stampa_err(6,0,"0");
		M++;
	}
}    /* fine while */

/* inserisco il tappo finale (-1) */
spiazzPC++;
sbianca(stringa,15);
j=POS1;
j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
stringa[j]=BLANK;
j=POS2;
j+=sprintf(&stringa[j],"%2d",-1); /* inserisco la word vuota */
scrivisufile(fdint,stringa,j+1,&righeint);

nword_o+=spiazzPC;  /* aggiorno il PC */
return(1);
}



/*
   modulo step2.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)step2.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*                                                                     *
*         File step2.c                                               *
*                                                                    *
*			PROCEDURE CONTENUTE                                         *
*                                                                    *
*	riordina()                                                        *
*                                                                    *
*	insvariabili(aus)                                                 *
*			struct variabili *aus;                                      *
*                                                                    *
*	prcodice()                                                        *  
*                                                                    *
*	trova(aus,nomecodice)                                             *
*			struct symb_list *aus;                                      *
*			char nomecodice[];                                          *
*								                                             *
*********************************************************************/

#include <osf1.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>

#include "chascii.inc"

#include "tipi.h"


extern struct symb_list *ins_symb();
extern int fdout;
extern int fdint;
extern int n_byte[];
extern int contrari[];
extern int aggind[];

int inv_if[]=
{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

/*********************************************************************
*                                                                    *
*			   Procedura riordina()                                     *
*                                                                    *
* Questa procedura e' il main della seconda parte dalla compilazione,*
* per prima cosa inserisce nella symble table le etichette con la    *
* relativo indirizzo, poi inserisce le variabili usate, deallocca le *
* strutture non piu' utilizzate ed infine produce il codice della    *
* compilazione.		                                                *
*                                                                    *
*********************************************************************/

riordina()
{
struct etichette *aus, *ausapp;
char nomel[10];

/* Inserisco le etichette una ad una nella S.T. prendendole dalla
   lista precedentemente costruita  */

insvariabili(testa); /* Inserisco nella S.T. le variabili */
for(aus=cima;aus!=NULL;) {
	sprintf(nomel,"%s","LABEL_");
	sprintf(&nomel[6],"%03d",aus->nomelabel);
	inizio=ins_symb(inizio,nomel,aus->vallabel,-1,-1,-1,0);
   ausapp=aus;
   aus=aus->prox;
	free(ausapp);
}
prcodice();          /* Produco il codice */
}

/*********************************************************************
*                                                                    *
*			   Procedura insvariabili()                                 *
*								                                             *
* Questa procedura viene chiamata per inserire le variabili usate nel*
* programma e definite tramite le  istruzioni DEFINE o DATA nella    *
* Symble Table,prendendole una ad una in "pre-order mode" dall'albero*
* che le contiene.			                                          *
*								                                             *
*********************************************************************/

insvariabili(aus)
struct variabili *aus;
{
int n,d;
if(aus!=NULL) {
	insvariabili(aus->left);
	insvariabili(aus->right);
	n=aus->tipo & 15;
	if(aus->tipo>15)
		d=(aus->tipo-n) / 16;
	else
		d=0;
	if(aus->flag==1)
		n=8;
	if(aus->flag!=2)
		inizio=ins_symb(inizio,aus->nome,aus->indirizzo,n,d,aus->nriga_input,1);
	else
		inizio=ins_symb(inizio,aus->nome,aus->indirizzo,n,d,aus->nriga_input,3);
	free(aus->valcost);
	free(aus);
}
}


/*********************************************************************
*								                                             *
*			   Procedura prcodice()                                     *
*								                                             *
* Questa procedura viene chiamata per produrre il codice vero e      *
* proprio risultato della compilazione. 			                     *
* Essa legge dal file "codice.int" un carattere alla volta, non      *
* considerando, quando ci sono, il numero di word di ogni istruzione *
* e cioe' le prime cifre di ogni riga, posizionandosi sulla prima    *
* parola da cercare. Trovatala ne scrive il codice relativo sul file *
* di output "codice.ab".                                             *
*								                                             *
*********************************************************************/

prcodice()

{

float fris;
char c[1],nomevar[LUNG_VAR+1],stcodice[7],etic[7];
char n_var_num[LUNG_VAR+1];
int ok,stop,tipo,sem=0,i,p,n,j,ris,vet,temp;
int cercala,ntipo,flag;
int aus,aus1,provv,ic;
int save_i,tresten,indesten,letic,flcont;

for(i=0;i<sizeof(nomevar);i++)
	nomevar[i]=0x00;

etic[6]=0x00;

n=read(fdint,c,1);
while(n!=0)
{
	sem=0;
	if(c[0]==0x0d)
	{
		stop=0;
		while(c[0]!=0x0a)
			n=read(fdint,c,1);
	}
	else
	{
		while(c[0]==BLANK) n=read(fdint,c,1);
		ic = 0;  // indice buffer di save nome variabile che inizia con numero
		memset(n_var_num,0,LUNG_VAR+1);
		while(c[0]!=BLANK && c[0]>=0x30 && c[0]<=0x39 )
		{
			n_var_num[ic] = c[0];
			ic++;
			n=read(fdint,c,1);
		}
		while(c[0]==BLANK)
		{
			n=read(fdint,c,1);
			ic = 0;
		}
		stop=1;
	}

	/* Ciclo di caricamento stringa dal file intermedio */

	while( stop==1 )
	{
		cercala=1;
		if ( ic > 0 )
		{
		/* Carico la parte iniziale numerica del nome della variabile */
			memcpy(nomevar,n_var_num,ic);
			i = ic;
		}
		else	i = 0;
		aus1=0;
		flcont=1;
		vet=0;

		while(c[0]!=BLANK && c[0]!=APTONDA && c[0]!=CHTONDA &&
		      c[0]!=VIRGOLA && c[0]!=0x00 && c[0]!=0x0D && c[0]!=0x0a &&
				c[0]!=VIRGOLETTE && flcont==1 )
		{
			if(c[0]==PUNTO)
			{
				/* incontrato il carattere di separazione "." */
				save_i = i;
				/* Ciclo di lettura estensione successiva al "." */
				for(i=0;i<2;i++)
				{
					n=read(fdint,c,1);
					if ( ( c[0] == 0x00 ) ||  ( c[0] == 0x0d ) ||
					     ( c[0] == ' ') ||	( c[0] == 0x0a ) ||
					     ( c[0] == VIRGOLA ) )
					{
				   /* Trovato carattere di terminazione riga */
						etic[i]=0x00;
						flcont = 0;
						break;
					}
					etic[i]=c[0];
				}
				etic[i]=0x00;
				tresten = 0; // reset flag di trovata estensione
				if ( ( letic = strlen(etic) ) == 2 )
				{
					/* Ciclo di verifica dei caratteri di estensione */
					for(i=0;i<MAX_EST;i++)
					{
						if((strcmp(etic,estensioni[i]))==0)
						{
							tresten = 1;  // set flag di trovata estensione
							indesten = i; // salvo indice estensione 
							break;
						}
					}
				}
				if ( tresten == 1 )
				{
					/* Caratteri di estensione tra quelli ammessi */
					i = save_i;
					/* controllo se si tratta di un reale o del separatore tra una
					   variabile e la sua estensione */
					nomevar[i]=0x00;
					i = indesten;
					if((ris=trova(inizio,nomevar,&tipo,&flag))!=-1)
					{
						/* Variabile definita */
						cercala=0;
						/* Salvo l'indice che individua l'estensione */
						ntipo=tipo;
						if(flag!=3)
						{ /* non sono in una subroutine, devo aggiornare il puntatore */
							if(tipo==0)		/* analogico */
								ris+=4;
							else
								if(tipo==2)	/* organo */
									ris+=1;
						}
						i=val_est[i][ntipo];
/* controllo se devo riferimi a quel byte ( se i<=7) o a quello
   successivo (i>=8). In questo caso incremento ris (l'indirizzo) */
						if(i>=8 && flag!=3) {  /* lo incremento solo se non sono in una subroutine */

							/* incremento ris al byte successivo */
							/* ricalcolo l'offset del bit nel byte successivo */

							ris++;
							i-=8;
						}

		            if(flag!=3)			/* se variabile non di una subroutine */
			 				ris+= 2048*i;	/* carico bit address nei bit 11 12 13*/
						else { /* caso variabile in una subroutine */
							if(tipo==0) /* analogico */
								i+=32;
							if(tipo==2) /* organo */
								i+=8;
			 				ris+= 256*i;	/* carico bit address in ris */
						}
						aus1=1;
					}
				else
					/* Variabile non definita ris = -1 */
					nomevar[i++]=c[0];
	 		   }
				else
				{
					/* Caratteri di estensione non tra quelli ammessi */
					i = save_i;
					nomevar[i++] = PUNTO;
					letic = strlen(etic);
					memcpy(&nomevar[i],&etic[0],letic);
					i = i + letic;
				}
			}  // chiusura carattere letto uguale a "."
			else
				/* Carattere letto dal file intermedio diverso da "." */
				nomevar[i++]=c[0];
			if ( c[0] != 0x00 ) 
				n=read(fdint,c,1);
		}  /* Chiusura ciclo interno di lettura */

		if(c[0]==VIRGOLETTE)
		{
			n=read(fdint,c,1);
			while(c[0]!=VIRGOLETTE && c[0]!=0x00) {
				if(c[0]=='#' || c[0]==0x0d || c[0]==0x0a)	/* caso IMOVS : il carattere di # rappresenta il NULL */
            {
					c[0]=0;
            }
            else
            {
				   write(fdout,c,1);
   				n=read(fdint,c,1);
            }
			}
			if(c[0]==0x00)
				write(fdout,c,1);
			while(c[0]!=0x0a)
				n=read(fdint,c,1);
			break;
		}

		if(aus1==0)
			nomevar[i]=0x00;
		sem++;

		for(p=0;p<6;p++)
			etic[p]=nomevar[p];
		if((strcmp(etic,"LABEL_"))==0 && sem==1)
		{
			i=0;
			c[0]=0x00;
		}
		etic[5]=0x00;
		if((strcmp(etic,"SUBR_"))==0 && sem==1)
		{
			i=0;
			c[0]=0x00;
		}
		if(n==0)	break;
		if(c[0]==APTONDA)
		{
			/* ciclo di caricamento indice variabile vettoriale in etic */
			vet=1;
			sbianca(etic,5);
			j=0;
			do {
				n=read(fdint,c,1);
				etic[j++]=c[0];
			}
			while(c[0]!=CHTONDA);

			n=read(fdint,c,1);
			etic[j-1]=0x00;
		}
		if ( c[0]==0x00 || c[0]==0x0D)
		{
			while(c[0]!=0x0a)
				n=read(fdint,c,1);
			stop=0;
			sem=0;
		}

		if(i>0 || aus1==1)
		{
			if(cercala)
				ris=trova(inizio,nomevar,&tipo,&flag);
			ok=1;
			if(ris==-1)
			{
			/* costante immediata intera oppure reale */
				if((ok=isintero(nomevar))==1)
				{
					ris=atoi(nomevar);
					write(fdout,&ris,2);
				}
				else
					if((ok=isreale(nomevar))==1)
					{
                  if(!strcmp(nomevar,"'FFFFH'"))
                     memset ((char *)&fris,0xFF,4);
                  else
   						fris=atof(nomevar);
						provv=write(fdout,&fris,4);
					}
					else
					{
						if(nomevar[0]==0x24) {
							sscanf(&nomevar[1],"%x",&ris);
							write(fdout,&ris,2);
						}
						else
						{
							ok=-1;
							printf("\n non ho trovato %s\n",nomevar);
						}
						break;
					}
				ok=-1;
				stop=0; 
			}

			if( vet==1 ) {

				temp=atoi(etic);

            if(flag!=3)  {         /* se e' una variabile o cost */
                                   /* incremento del n.di byte corretti */
					if(tipo!=5)
						ris+=n_byte[tipo]*(temp-1);
					else {              /* caso logici */ 	
                	aus=temp/16;     /* determino il numero di word indirizzata */	
                  ris+=aus*2;      /* determino la word su cui posizionarmi */	
                  aus=(temp%16);   /* individuo il numero del bit */	
                  if(aus>0)        /* decremento per iniziare da 0 */	
                  	aus--;
                  if(aus>=8)  {    /* se indirizzo un bit superiore a 8 */		
                  	ris++;        /* incremento di un byte il posizionamento */		 
                     aus-=8;       /* indirizzo i bit a partire da 0 */			
						}
                  ris+=2048*aus;   /* inserisco i valori ai bit 11,12,13 */	
					}
	 			}
   	      else	                   /* se var di una subr. */	
      	   	ris+=256*(temp-1);    /* aggiungo l' offset a partire */	
      	                            /* dal secondo byte dell' indirizzo indiretto */
			}

			if(flag!=3)
				if(tipo>0 && cercala==1)
					ris+=2048*aggind[tipo];

			if(ok!=-1)
				write(fdout,&ris,2);
/*
			if((strcmp(nomevar,"PAG"))==0) {
				pagstep2();
				while(c[0]!=0x0a)
					n=read(fdint,c,1);
				sem=0;				
				break;
			}
*/
			while(n>0 && stop==1 && (c[0]==BLANK || c[0]==VIRGOLA))
				n=read(fdint,c,1);

			if(n==0)
				stop=0;
			vet=0;
		}
	}
	if(n>0)
		n=read(fdint,c,1);
}
}

/*********************************************************************
*								     *
*			   File step2.c                              *
*								     *
* Questa procedura serve per cercare nella S.T. il nome desiderato   *
* indicato da nomecodice e rende il codice relativo a quel nome.     *
*								     *
*********************************************************************/

trova(aus,nomecodice,tipo,flag)
struct symb_list *aus;
char nomecodice[];
int *tipo;
int *flag;
{
int n;
if(aus==NULL)
	return(-1);
if((strcmp(nomecodice,aus->stringa))==0)  {
	*tipo=aus->tipovar;
	*flag=aus->tipocodice;
	n=aus->codice_ogg;
	if((*flag)==2 && ((n>=2 && n<=15) || (n==118 || n==119))) {
		if(n==118)
			n=119;
		else
			if(n==119)
				n=118;
			else
				n=contrari[n-2];
	}		
	return(n);
}
if((strcmp(nomecodice,aus->stringa))<=0)
	n=trova(aus->sinistra,nomecodice,tipo,flag);
else
	n=trova(aus->destra,nomecodice,tipo,flag);
}

/*********************************************************************
*          							     *
*          							     *
*********************************************************************/

pagstep2()
{
char nome[15],*p;
char car[1],d[3];
int ris=0,num,i,n,j;

/* leggo il nome dell' elenco o della pagina , se trovo -1 --> non c'Š */
p=nome;
for (num=0;num<2;num++) {
	for(i=0;nome[i-1]!=',';i++) 
			n=read(fdint,&nome[i],1);
	nome[i-1]=0x00;
	if(strcmp(nome,"-1")==0) {
		i=-1;
		for(j=0;j<5;j++)
			write(fdout,&i,2);			/* elenco o pagina non presente, inserisco 5 volte -1 */
	}
	else	{
		if(nome[0]=='"') {
			for(i=1;i<11;i++)
				if(nome[i]==BLANK || nome[i]=='"')
					nome[i]=0x00; 
			write(fdout,&nome[1],10);		/* elenco o pagina presente, cambio i BLANK in NULL */
		}
		else {
			write(fdout,&ris,2);	     /* prima word : 0 */
			if((p=strchr(nome,0x20))!=NULL)
				*p=0;
			ris=trova(inizio,nome,&n,&j);
 			if (j!=3)
	 			ris+=2048*aggind[n];
			write(fdout,&ris,2);	     /* seconda word : indirizzo variabile */
			ris=0;
			for(j=2;j<5;j++)
				write(fdout,&ris,2);			/* inserisco i 3 NULL */
		}
	}
}

/* leggo il nome della pagina 
for(i=0;nome[i-1]!=',';i++) 
		n=read(fdint,&nome[i],1);
nome[i-1]=0x00;
for(i=0;i<10;i++)
		if(nome[i]==BLANK)
			nome[i]=0x00; 
write(fdout,nome,10);		/* cambio i BLANK in NULL */

/* leggo il codice video */
read(fdint,&nome[0],1);		/* salto il "$" */
if(nome[0]=='$') {	/* caso video come stringa */
	read(fdint,nome,4);
	nome[4]=0x00;
	sscanf(nome,"%x",&i);
	write(fdout,&i,2);
	write(fdout,&ris,2);	     /* seconda word : 0 */
}
else {
	i=1;
	do 
		n=read(fdint,&nome[i++],1);
	while(nome[i-1]!=0) ;
	write(fdout,&ris,2);	     /* prima word : 0 */
	if((p=strchr(nome,0x20))!=NULL)
		*p=0;
	ris=trova(inizio,nome,&n,&j);
 	if (j!=3)
		ris+=2048*aggind[n];

	write(fdout,&ris,2);	     /* seconda word : indirizzo variabile */
}
}

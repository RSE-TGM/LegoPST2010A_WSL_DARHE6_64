/*
   modulo subr.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)subr.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*********************************************************************
*          							                                       *
*			File subr.c 		                                          *
*          							                                       *
*	procgosub()						                                       *
*	procsub()                                                         *
*	fastringa(t,incr,valore)                                          *
*		char *t;                                                       *
*		int incr;                                                      *
*		char valore[];                                                 *
*          							                                       *
*********************************************************************/

#include <osf1.h>
#include <stdio.h>

#include "chascii.inc"
#include "define.inc"
#include "tipi.h"
#include "iniz.h"

#define maxlung_istr 12
#define LUNGSTR      60
#define POS1	      3
#define POS2	     10
#define MAXGOSUB    256
#define SUBR_FIND    64

extern int nword_o;
extern char c[];
extern char linea_cor[];
extern int cont_label;
extern int fdint;
extern int righeint;
extern int contgosub;
extern int contsubr;
extern struct symb_list *ins_symb();
int subrcorr=-1;
int finesubr=-1;

/*********************************************************************
*          							                                       *
*			Procedura procgosub			                                 *
*          							                                       *
* La procedura serve per compilare l' istruzione gosub. Per          *
* prima cosa verifica che il numero delle gosub sia inferiore al     *
* masssimo previsto e che le subr. definite siano meno di 10. Poi    *
* espande le istruzioni complementari a gosub e verifica che gli     *
* argomenti passati siano coerenti con le precedenti gosub alla      *
* medesima subr. o, se e' chiamata per la prima volta, inserisce nel *
* vettore dei tipi degli argomenti il tipo di ciascuno in ordine     *
* sequenziale. Per ogni argomento inoltre verifica che sia stato     *
* dichiarato precedentemente. Oltre al tipo nel vettore viene memo=  *
* rizzato l' indirizzo nel DBL della variabile (moltiplicato per 16),*
* per i vettori viene cosi' rintracciato l' indirizzo di DBL cui     *
* riferirsi.						  	                                    *
*          							                                       *
*********************************************************************/

procgosub()
{
int contarg=0,i=85,j,t,M,trovato,loctsubr[NUM_ARG+1];
int tipo,d,dim,ind,temp,indarg;
int flgerr,flendls,lsig;
char stringa[LUNGSTR],nomevar[LUNG_VAR+1],nomesub[LUNG_VAR+1];

if(++contgosub>MAXGOSUB) {
	stampa_err(32,0,"0"); /* troppe gosub o procedure */
	return;
}

if(contgosub==1)
	for(t=0;t<7;t++) {
		inizio=ins_symb(inizio,private[t],i,-1,-1,-1,2);
		i++;
	}

for(i=0;i<NUM_ARG+1;i++)
	loctsubr[i]=-1;

for(t=2;t<7;t+=3)                     	/* inserisco PUSH_FP  e  */
	fastringa(private[t],1,"0");  		/* MOV_SP-->FP           */

for(i=0,M=6;i<(EF_LUNGVAR - 1) && linea_cor[M]!=BLANK && linea_cor[M]!=0x00
	&& linea_cor[M]!=APTONDA;M++)
	nomesub[i++]=linea_cor[M];    /* leggo nome subr. */
nomesub[i]=0x00;

flgerr = 0;

while(linea_cor[M]!=0x00 && linea_cor[M]!=APTONDA) {

	if ( !(linea_cor[M]==BLANK || linea_cor[M]==TAB) ) {

		if (flgerr == 0 ) {

			flgerr = 1;
			stampa_err(76,0,"0");

		}
	}
	M++;
}

trovato=0;
for(i=0;i<contsubr;i++)
	if((strcmp(nomesub,nomi_subr[i]))==0)  {
		trovato=1;  /* verifico se ho incontrato altre */
 		break;      /* gosub alla stessa subroutine */
	}
temp=i; /* memorizzo a quale subr. mi riferisco se gia' esiste */

/* determino i dati di ogni parametro e li pongo nel vettore locale,
inserendo anche, moltiplicato per 16, l' indirizzo in DBL della
variabile che mi servira' poi per inserirlo nello stack ed inserisco
nel vettore locale dei nomi i nomi delle variabili passate */

if(linea_cor[M]==0x00) {

	/* Caso istruzione GOSUB senza lista degli argomenti */

	for(i=0;i<NUM_ARG;i++)        /* non ci sono argomenti */
		loctsubr[i]=-1;
	loctsubr[i]=0;

}

else {

	/* Caso istruzione GOSUB con lista degli argomenti */

	M++;

	indarg=0;
	flendls=0;

	while(linea_cor[M]!=0x00 && indarg<NUM_ARG+1) {

		while ( linea_cor[M] == BLANK || linea_cor[M] == TAB )
			M++;

		getsigsub(nomevar,&M); /* leggo il nome dell' argomento */

		if ( (strlen(nomevar)) == 0 ) {

		stampa_err(76,0,"0");

		}

		while ( linea_cor[M] == BLANK || linea_cor[M] == TAB )
			M++;

		if(linea_cor[M]==CHTONDA) {

			flendls = 1;

		}

		if(((tipo=cerca(testa,nomevar,&dim,&ind)) & 15)!=-1) {
			if(tipo>=16)
				cnome(nomevar,&tipo,&M);
			d=controlla(nomevar,&M,tipo); /* verifico l' esistenza */
		if(indarg<NUM_ARG)  {
			strcpy(locnsubr[indarg],nomevar);
			if(tipo==3 || tipo==4 || tipo==5 || tipo==7)
				loctsubr[indarg++]=tipo+16*64;
			else
				loctsubr[indarg++]=tipo;
		}
		}

		while ( linea_cor[M] == BLANK || linea_cor[M] == TAB )
			M++;

		if (linea_cor[M] == CHTONDA ) {

			flendls = 1;

		}

		M++;

	} /* end while */

	if ( (flendls == 0) ) {

		stampa_err(76,0,"0");

	}

	if(indarg>NUM_ARG)
		stampa_err(33,0,"0"); /* troppi argomenti passati */

	loctsubr[NUM_ARG]=indarg;

} /* end else */

if(trovato==0) {   /* inserisco nelle strutture i dati dei parametri */

	if(contsubr==NUM_SUBR) {
		stampa_err(32,0,"0"); /* troppe gosub o procedure */
		return;
	}

	strcpy(nomi_subr[contsubr],nomesub); /* nome subr. */
	for(i=0;i<NUM_ARG+1;i++)
   		tvarsubr[contsubr][i]=loctsubr[i]; /* tipi argomenti */
	contsubr++;
}
else {  /* controllo che i parametri delle precedenti chiamate
	   siano corretti e che la subr. non sia gia' stata incontrata */
	if(tvarsubr[temp][NUM_ARG]>=SUBR_FIND)
		stampa_err(37,1,nomesub); /* la subr. e' gia stata definita */
	trovato=1;
	for(i=0;i<NUM_ARG;i++)
		if((loctsubr[i] & 15)!=(tvarsubr[temp][i] & 15)) {
			trovato=0;
			break;
		}
	if(trovato==0 || 
	(loctsubr[NUM_ARG] & (SUBR_FIND-1))!=(tvarsubr[temp][i] & (SUBR_FIND-1))) {
		stampa_err(34,0,"0"); /* argomenti in contrasto con
                               definizioni precedenti */
		return;
	}
}
/* inserisco nello stack le variabili passate in ordine inverso */
for(i=(loctsubr[NUM_ARG] & (SUBR_FIND-1))-1;i>=0;i--) {
/*	fastringa(private[0],2,(loctsubr[i]-(loctsubr[i] & 15))/16); */
	fastringa(private[0],2,locnsubr[i]);
}
fastringa(private[2],1,"0");  	  /* inserisco PUSH_FP    */
/* inserisco codice istruzione gosub */
j=0;
j+=sprintf(nomevar,"%s","SUBR_");
sprintf(&nomevar[j],"%s",nomesub);
j=0;
j+=sprintf(stringa,"%s",par_chiav[16]);
stringa[j++]=BLANK;
sprintf(&stringa[j],"%s",nomevar);
fastringa(stringa,2,"0");
for(t=3;t<5;t++) 	              /* inserisco POP_SP e   */
	fastringa(private[t],1,"0");  /*           POP_FP     */
}


/*********************************************************************
*          							                                       *
*			Procedura procsub                                           *
*          							                                       *
* La procedura viene chiamata per risolvere le definizioni di        *
* subr.; essa verifica che sia possibile trovare una tale istruzione *
* e poi verifica che la subr. sia stata specificata da qualche gosub,*
* ne ricerca il numero che la rappresenta ponendolo in subrcorr, e   *
* verifica se il numero degli argomenti e' corretto. Ogni argomento  *
* viene inserito nella matrice nvarsubr alla riga specificata da     *
* subrcorr e alla colonna corrispondente al numero di argomento nella*
* definizione. Poi la procedura cicla fino a trovare l' ends della   *
* subroutine compilando le istruzione trovate.                       *
*          							                                       *
*********************************************************************/

procsub()

{

int tipo,ind,dim,i,M,j;
int flgerr;
char nomesub[LUNG_VAR+1],nomevar[LUNGSTR+1];

if(!(finesubr==1 || finesubr==-1)) {
	stampa_err(14,1,"SUBROUTINE"); /* definiz. subr. nidificate */
	return(1);
}

finesubr=0; /* lo metto a zero perche' indica che sono in una subr. */

for(i=0,M=11;i<(EF_LUNGVAR - 1) && linea_cor[M]!=BLANK && linea_cor[M]!=0x00
	&& linea_cor[M]!=APTONDA;M++)
	nomesub[i++]=linea_cor[M];
nomesub[i]=0x00; /* leggo il nome della subr. */

flgerr = 0;

while(linea_cor[M]!=0x00 && linea_cor[M]!=APTONDA) {

	if ( !(linea_cor[M]==BLANK || linea_cor[M]==TAB) ) {

		if (flgerr == 0 ) {

			flgerr = 1;
			stampa_err(6,0,"0");

		}
	}
	M++;
}

j=0;

j+=sprintf(nomevar,"%s","SUBR_");     /* creo una label del tipo : */
j+=sprintf(&nomevar[j],"%s",nomesub); /* SUBR_nome-subr */
inizio=ins_symb(inizio,nomevar,nword_o,-1,-1,-1,0); /* la inserisco nella ST */
scrivisufile(fdint,nomevar,j+1,&righeint);
for(i=0;i<contsubr;i++)  /* cerco la subroutine tra quelle definite */
	if((strcmp(nomesub,nomi_subr[i]))==0) {
		subrcorr=i;
		break;
	}
if(i==contsubr) {

	/* subroutine non chiamata da nessuna gosub */

	stampa_err(35,1,nomesub); 
	return(1);

}
else
	if(tvarsubr[i][NUM_ARG]>=SUBR_FIND) {
		stampa_err(37,1,nomesub); /* subroutine gia'definita */
		return(1);
	}
if(linea_cor[M]==BLANK)
	M++;
if(linea_cor[M]==0x00) {
	if(tvarsubr[subrcorr][NUM_ARG]!=0)
		stampa_err(34,0,"0"); /* numero di argomenti errato */
	tvarsubr[subrcorr][NUM_ARG]+=SUBR_FIND ; /* segno che la subr. e' definita */
}
else {
	if(linea_cor[M]!=APTONDA) {
		stampa_err(6,0,"0"); /* manca la parentesi tonda */
		return(1);
	}

/* cambio il valore dell' ultimo campo della matrice aggiungendogli
   SUBR_FIND, indicando cosi' che la subr. e' stata definita */

	tvarsubr[subrcorr][NUM_ARG]+=SUBR_FIND;

/* leggo ogni argomento e lo inserisco in nvarsubr, controllando che
   il numero di parametri sia corretto ( il numero di parametri lo si
   determina con l' AND bit a bit tra l' ultimo campo e SUBR_FIND -1) 
	e che non vi siano argomenti con lo stesso nome di altre variabili globali */

	for(i=0;1;i++) {
		if(linea_cor[++M]==BLANK)
			M++;
		for(j=0;linea_cor[M]!=BLANK && linea_cor[M]!=VIRGOLA &&
 	        linea_cor[M]!=CHTONDA && linea_cor[M]!=0x00;M++)
			nomesub[j++]=linea_cor[M];
		nomesub[j]=0x00;
		if(linea_cor[M]==BLANK)
			M++;
		if(linea_cor[M]==0x00)  {
			stampa_err(6,0,"0"); /* err. di sintassi */
			break;
		}
		if(i<tvarsubr[subrcorr][NUM_ARG]) {
			if((tipo=cerca1(testa,nomesub,&ind,&dim))==-1)
				strcpy(nvarsubr[subrcorr][i],nomesub);
			else
				stampa_err(38,1,nomesub); /* argomento gia' definito ne DBL */
		}
		if(linea_cor[M]==CHTONDA) {
			if(i!=(tvarsubr[subrcorr][NUM_ARG] & (SUBR_FIND -1))-1)
/* num. argomenti errato */	stampa_err(34,0,"0");
			break;
		}
	}    /* end for */
}  /* end else */

fastringa(private[5],1,"0");  /* inserisco MOV_SP-->FP */

while(finesubr==0) {  /* compilo tutte le istruzioni presenti */

	i=scegli(1);  /* nella subr. finche' non trovo ENDS   */

	/* i = -3 trovata istruzione END */
	/* i = -4 trovato EOF del file sorgente */

	if( (i==-3) || (i==-4) ) {   /* che pone finesubr a 1 */

		                         /* se trovo EOF significa che */
		stampa_err(36,1,"ENDS"); /* manca ENDS della SUBROUTINE */
		return(i);

	}

}

}

/*********************************************************************
*          							     *
*          							     *
*********************************************************************/

fastringa(t,incr,valore)
char *t;
int incr;
char valore[];
{
int i,j;
char stringa[LUNGSTR];
sbianca(stringa,LUNGSTR-1);
j=POS1;
j+=sprintf(&stringa[j],"%4d",nword_o);
stringa[j]=BLANK;
j=POS2;
j+=sprintf(&stringa[j],"%s",t);
if((strcmp(valore,"0"))!=0) {
	stringa[j++]=BLANK;
	j+=sprintf(&stringa[j],"%s",valore);
}
nword_o+=incr;
scrivisufile(fdint,stringa,j+1,&righeint);
}

/*********************************************************************
*								                                             *
*			Procedura getsigsub                                         *
*                                                                    *
*********************************************************************/

getsigsub(nomevar,M)
char nomevar[];	  // nome variabile (di ritorno)
int *M;				  // puntatore da cui iniziare a leggere le sigle
						  // (punta all'interno di linea_cor sul primo
						  // carattere appartenente alla sigla della variabile).
{

int i,temp=0;

for(i=0;linea_cor[*M]!=BLANK && linea_cor[*M]!=0x00 &&
linea_cor[*M]!=VIRGOLA && linea_cor[*M]!=APTONDA &&
linea_cor[*M]!=CHTONDA &&
((subrcorr==-1 && i<EF_LUNGVAR) || (subrcorr!=-1 && i<LUNG_VAR)); (*M)++)
		nomevar[i++]=linea_cor[*M];	  // copia il nome in nomevar

nomevar[i]=0x00;

return;

}



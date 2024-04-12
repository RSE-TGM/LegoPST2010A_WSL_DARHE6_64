/*
   modulo se.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)se.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/********************************************************************
*                                                                   *
*                        File se.c                                  *
*                                                                   *
*  PROCEDURE CONTENUTE                                              *
*                                                                   *
*	procif(codice)                                                   *
*       int codice;                                                 *
*	procelse()                                                       *    
*	procendif()                                                      *   
*	struct etichette *listlabel(aus,i)                               *
*			struct etichette *aus;                                     *
*			int i;                                                     *
*	proccase()                                                       *
*	procfcase()                                                      *
*	procbegin()                                                      *
*                                                                   *
********************************************************************/

#ifdef INGLESE
#define OutOfMemory     " OUT OF MEMORY < listlabel >"
#define press           " PRESS ANY KEY TO CONTINUE "
#else
#define press           " PREMI UN TASTO PER CONTINUARE "
#define OutOfMemory     " MEMORIA INSUFFICIENTE PER ALLOCAZIONE IN < listlabel >"
#endif


#include <osf1.h>
#include <stdio.h>
#include <malloc.h>

#include "chascii.inc"

#include "tipi.h"

#define maxlung_istr 12
#define LUNGSTR      70
#define POS1	      3
#define POS2	     10

extern int contif;
extern int contcase;
extern int nword_o;
extern char linea_cor[];
extern int cont_label;
extern int fdint;
extern char c[];
extern int hh;
extern int righeint;

char nomev[LUNG_VAR+1];
char nome_var_case[MAXIF][LUNG_VAR+1];
int stackif[MAXIF][5];
int trovbegin[MAXIF];
int fltrbegin[MAXIF];  // flag = 1 trovato begin ; flag = 0 trovato break
int contrari[]=
{	3, 2, 7, 6, 5, 4, 9, 8, 13, 12, 11, 10, 15, 14  };
struct etichette *listlabel();

/********************************************************************
*                                                                   *
*          Procedura procif                                         *
*                                                                   *
*  La procedura viene chiamata quando si incontra una istruzione IF *
* e mantiene il controllo dell' esecuzione finche' il relativo      *
* ENDIF non e' stato trovato, preoccupandosi cioe' lei di chiamare  *
* la smisto per la scelta dell' istruzione successiva. Per mantenere*
* la giusta nidificazione degli if, si fa uso di uno pseudo stack   *
* di cinque  campi interi :                                         *
* -     il primo contiene il nome dell' etichetta corrispondente    *
*	all' istruzione if                                               *
* -	il secondo il numero di word del codice oggetto a cui         *
*	saltare per eseguire l' ELSE relativo, in pratica il valore      *
*       dell' etichetta del primo campo.                            *
* -     il terzo contiene il nome dell' etichetta corrispondente    *
*	all' istruzione then per evitare l' else.                        *
* -	il quarto il numero di word del codice oggetto a cui          *
*	saltare per non eseguire l' ELSE relativo, in pratica  il        *
*       valore dell' etichetta del terzo campo.                     *
* -	il quinto viene posto a 1 quando trovato IF ed a 0 quando     *
*	trovato l'ENDIF. Indica cioe' fino a quando l'IF e' attivo       *
*  La procedura verifica che tipo di IF ha incontrato, e se richiede*
* test su variabili, le cerca e verifica che siano di tipo compati= *
* bile, altrimenti segnala errore; fatto questo inserisce nella     *
* lista il codice dell'istruzione IF con eventualmente gli indirizzi*
* delle variabili nel DBL determinati tramite la cerca, lasciando   *
* 5 bytes blank per poter in seguito inserire il jump all' ELSE.    *
*                                                                   *
********************************************************************/

procif(codice)
int codice;
{
int j=0,sem,tipo[2],dim[2],ind[2],ciclo=0,i,M=0;
char st[maxlung_istr],nomevar[LUNG_VAR+1],stringacod[LUNGLISTA];
char intlinea[LUNGSTR];
tipo[0]=-2;
sbianca(intlinea,LUNGSTR-1);
if(codice==118)
	codice=119;	             /* caso IFEQS */
else
	if(codice==119)
		codice=118;	        /* caso IFNES */
	else
	codice=contrari[codice-2];  /* trovo l' if negato */
j=POS1;                     /* preparo la stringa per il file intermedio */
j+=sprintf(&intlinea[j],"%4d",nword_o);      /* inserisco il P.C. */
intlinea[j++]=BLANK;
nword_o+=wordpar_ch[codice];                 /* incremento il PC */
strcpy(nomevar,par_chiav[codice]);
nomevar[0]=0x42; /* B */
nomevar[1]=0x52; /* R */
j=POS2;
j+=sprintf(&intlinea[j],"%s",nomevar);       /* inserisco l' istruzione cambiando IF con GR */
intlinea[j++]=BLANK;
cont_label++;
j+=sprintf(&intlinea[j],"%s","LABEL_");      /* e LABEL_XXX corripondente all' ELSE */
j+=sprintf(&intlinea[j],"%03d",cont_label);  /* pongo XXX=contlabel */
if((++contif) > MAXIF ) {
	stampa_err(20,0,"0");  /* superato max nidificazione */
	return(-2);
}
if(codice > 3) {   /* casi in cui vi sono altri due argomenti */
	intlinea[j]=BLANK;
	for(M=0;linea_cor[M]!=BLANK && linea_cor[M]!=0x00;M++)
			;
	M++;
	while(ciclo < 2) {
		sem=legginvar(nomevar,codice,&M,ciclo+1);  /* leggo un argomento */
		if(sem==-1) {
			ciclo=2;      /* manca almeno un argomento, non */
			tipo[0]=-2;   /* segnalo errore, lo fa gia' legginvar */
		}
		else {  /* controllo che la var esista */
	tipo[ciclo]=cerca(testa,nomevar,&dim[ciclo],&ind[ciclo]);
/* se sono in una subroutine (tipo[ciclo]>=16) chiamo cnome */
				if(tipo[ciclo]>=16)
/* cambia le occorrenze di nomevar */	cnome(nomevar,&tipo[ciclo],&M);
/* verifico se vettore */	controlla(nomevar,&M,tipo[ciclo]);
				ciclo++;
				if(ciclo==1) {
/* inserisco il primo argomento */	intlinea[j++]=BLANK;
					j+=sprintf(&intlinea[j],"%s",nomevar);
					intlinea[j++]=BLANK;
				}
				else {
/* inserisco il secondo arghomento */
					j+=sprintf(&intlinea[j],"%s",nomevar);
				}
				M++;
		}
	}
	M=0; 	/* controllo corretezza tipi argomenti */
	if(((tipo[0]==3 || tipo[0]==0) && (tipo[1]==3 || tipo[1]==0)) ||
 	   ((tipo[0]==4 || tipo[0]==2) && (tipo[1]==4 || tipo[1]==2)) ||
 	   ((codice==118 || codice==119 ) && (tipo[0]==7 && tipo[1]==7)))
		M=1;  /* controllo positivo */
	if(M==0)
		if(tipo[0]!=-2)
			stampa_err(12,1,par_chiav[codice]);
}
scrivisufile(fdint,intlinea,j+1,&righeint);   /* inserisco la stringa sul file */
stackif[contif-1][0]=cont_label;     /* inizializzo lo stack */
stackif[contif-1][1]=-1;
stackif[contif-1][2]=-1;
stackif[contif-1][3]=-1;
stackif[contif-1][4]=1;
i=new_lico();      /* leggo la riga successiva per vedere se c'e' THEN o ELSE */
for(i=0;i<maxlung_istr-1 && linea_cor[i]>=0x41 && linea_cor[i]<=0x5a;i++)
	st[i]=linea_cor[i];
st[i]='\0';
if(!((i=strcmp(st,"THEN"))==0 || (i=strcmp(st,"ELSE"))==0))
	stampa_err(21,0,"0");  /* non segue ne THEN ne ELSE */
M=strcmp(st,"ELSE");
while(stackif[contif-1][4]==1) {
	if(M==0) {          /* se istruzione senza THEN */
		scegli(0);  /* devo analizzare la riga con else */
		M=1;        /* riprendo ad analizzare le righe successive */
	}
	i=scegli(1);        /* analizzo riga succevviva */

	if( (i == -3) || (i==-4) ) {

		stampa_err(22,1,"ENDIF");

	   if( i==-4 )
		  return(-1); // E O F senza istruzione END
		else 
		  return(-2); // Incontrata istruzione END

	}

}
contif--;    /* decremento livello di nidificazione */
}

/********************************************************************
*								                                            *
*			Procedura procelse			                                *
*								                                            *
* La procedura, se non ci sono incongruenze con le istruzioni IF    *
* (del tipo trovato un ELSE senza IF ), inserisce nella lista       *
* l' istruzione JUMP, per saltare il codice dell' ELSE, lasciando   *
* in bianco l' indirizzo, ed inserisce nel secondo campo dello      *
* stack il valore della riga di output incrementato di 1, ottenendo *
* cosi' il giusto indirizzo a cui saltare.                          *
* Se viene chiamata da un case, compie solo il primo passo.         *
* Se trova un  errore non compie questi due passi ma visualizza     *
* l'errore.						 	                                      *
*								                                            *
********************************************************************/

procelse(sem)

int sem;    /* sem=0 ==> siamo in un case, sem=1 ==> if */

{

char intlinea[LUNGSTR];
int i,j=0;

sbianca(intlinea,LUNGSTR-1);

/* verifico giusto susseguirsi istruzioni IF [THEN] ELSE o CASE BEGIN BREAK */

if(((contif==0 && sem==1) || ((contcase==0 || trovbegin[contif-1]!=1) && sem==0 )) ||
     stackif[contif-1][0]==-1 || stackif[contif-1][1]!=-1) {
	trovbegin[contif-1]=0;
	if(sem==1)
		stampa_err(22,1,"ELSE");  /* sono in un IF */
	else
		stampa_err(22,1,"BREAK"); /* sono in un CASE */
}
else  {
	trovbegin[contif-1]=0;  /* segnalo che ho trovato il BREAK */

	if ( sem == 0 ) {

	/* Caso di istruzione BREAK setto flag di trovato */

	fltrbegin[contif-1] = 0;

	}

	if(stackif[contif-1][2]==-1)               /* assegno una nuova label */
		stackif[contif-1][2]=++cont_label;
	j=sprintf(intlinea,"%d",nword_o);    /* preparo la stringa inserendo il PC, */
	intlinea[j++]=BLANK;
	nword_o+=wordpar_ch[0];              /* incremento il PC */
	j+=sprintf(&intlinea[j],"%s","JUMP LABEL_");
	j+=sprintf(&intlinea[j],"%03d",stackif[contif-1][2]);
	scrivisufile(fdint,intlinea,j+1,&righeint);
	if(sem==1)  {  /* caso if */
		stackif[contif-1][1]=nword_o; /* inserisco l' indirizzo per l' ELSE */
		sbianca(intlinea,LUNGSTR-1);
		j=sprintf(intlinea,"%s","LABEL_     :");
		intlinea[j]=BLANK;
		j=POS2-4;
		j+=sprintf(&intlinea[j],"%03d",stackif[contif-1][0]);
		scrivisufile(fdint,intlinea,j+1,&righeint);
		cima=listlabel(cima,0);    /* assegno i valori alle label */
	}
}
}

/********************************************************************
*								    *
*			Procedura procendif			    *
*								    *
*   La procedura, se non ci sono incongruenze con le istruzioni IF  *
* (del tipo trovato un ENDIF senza IF ), inserisce nel quarto campo *
* o nel secondo se siamo nel caso di un IF senza ELSE,              *
* dello stack il valore della riga corrente del file di output      *
* incrementata di 1, fornendo cosi' l'indirizzo corretto a cui      *
* saltare se eseguito il THEN per evitare l' ELSE, e chiama la      *
* risolvi per inserire tutti gli indirizzi lasciati blank           *
*  Se viene trovato ENDIF senza IF non vengono compiuti gli ultimi  *
* passi ma visualizzato l' errore.                                  *
*								    *
********************************************************************/

procendif()
{
char intlinea[LUNGSTR];
int i,j=0;
sbianca(intlinea,LUNGSTR-1);
if(contif==0)
	stampa_err(22,1,"ENDIF");
else {  /* preparo scritta della label a cui saltare per fine  if */
	j=sprintf(intlinea,"%s","LABEL_");
	if(stackif[contif-1][2]==-1)  {
		j+=sprintf(&intlinea[j],"%03d",stackif[contif-1][0]);
		stackif[contif-1][1]=nword_o; /* senza ELSE */
	}
	else   {
		j+=sprintf(&intlinea[j],"%03d",stackif[contif-1][2]);
		stackif[contif-1][3]=nword_o;
	}
	scrivisufile(fdint,intlinea,j+1,&righeint);
	if(stackif[contif-1][2]==-1)
		cima=listlabel(cima,0); /* if senza ELSE */
	else
		cima=listlabel(cima,2); /* if completo o senza THEN */
	for(i=0;i<5;i++)
		stackif[contif-1][i]=-1;
}
}

/********************************************************************
*								                                            *
*			Procedura listlabel			                                *
*								                                            *
*   La procedure serve per inserire nella lista nel primo campo il  *
* valore dei campi 1 o 3 dello stack, cioe' il nome della label, e  *
* nel secondo il valore della label stessa che si trova nela campo  *
* dello stack successivo a quello passato (e quindi 2 o 4).         *
*								                                            *
********************************************************************/

struct etichette *listlabel(aus,i)
struct etichette *aus;
int i;
{
if(aus==NULL)  {
	aus=(struct etichette *)malloc(sizeof(struct etichette));

	if ( aus == NULL ) {

	/* Memoria insufficiente per l'allocazione */

	printf(OutOfMemory);
	bell();
	printf(press);
	getc(stdin);

	exit(0);

	}

	if ( i >= 0 ) {

	aus->nomelabel=stackif[contif-1][i];
	aus->vallabel=stackif[contif-1][i+1];

	}
	else {

	aus->nomelabel = cont_label;
	aus->vallabel = nword_o + 4;

	}

	aus->prox=NULL;

	}

else

	aus->prox=listlabel(aus->prox,i);
return(aus);

}


/*********************************************************************
*          							                                       *
*			Procedure proccase			                                 *
*          							                                       *
*	La procedura e' chiamata per l' istruzione CASE. Legge la         *
* variabile del CASE e controlla che sia un intero o un organo, legge*
* la riga successiva aspettandosi il BEGIN, incrementa il numero di  *
* if nidificati ed il contatore dei CASE, poi finche' non trova l'   *
* ENDCASE relativo cicla compilando le istruzioni che lo compongono. *
*          							                                       *
*********************************************************************/

proccase()
{
int i,ok,M,dim,ind;
char st[maxlung_istr];

contif++;    /* incremento livello nidificazione degli if-case */
contcase++;  /* incremento livello nidificazione dei case */
if(contif>MAXIF || contcase >MAXCASE ) {
	stampa_err(20,0,"0"); /* superate le dimensioni massime */
	return(-2);
}
for(i=0;i<4;i++)      /* inizializzo lo stack  a -1 tranne l' ultima */
	stackif[contif-1][i]=-1;
stackif[contif-1][i]=1;  /* finche; =1 ==> CASE attivo */
M=5;
while(linea_cor[M]==BLANK)
	M++;
for(i=0;linea_cor[M]!=BLANK && linea_cor[M]!=0x00 &&
	linea_cor[M]!=APTONDA && i<EF_LUNGVAR; M++)
	nomev[i++]=linea_cor[M];
nomev[i]=0x00;    /* ho letto il nome della variabile del CASE */
i=cerca(testa,nomev,&dim,&ind); /* la cerco per vedere se esiste */
if(i>=16)
	cnome(nomev,&i,&M);
if(!(i==4 || i==2))             /* e ne controllo il tipo */
	stampa_err(16,1,nomev); /* variabile case non intero o organo */
ok=controlla(nomev,&M,4);       /* controllo se vettore */
if((i=new_lico())==-1) {
	stampa_err(21,0,"0");
	return(-1);
}

/* inserisco il nome della variabile nello stack degli argomenti */

memcpy(nome_var_case[contcase-1],nomev,LUNG_VAR+1);

for(i=0;i<maxlung_istr-1 && linea_cor[i]>=0x41 && linea_cor[i]<=0x5a;i++)
	st[i]=linea_cor[i];
st[i]='\0';                    /* leggo istruzione presente nella riga */
if((i=strcmp(st,"BEGIN"))!=0)
	stampa_err(21,0,"0");  /* CASE senza BEGIN successivo */
ok=0;
while(stackif[contif-1][4]==1) {
	i=scegli(ok);
	ok=1;

	if( (i == -3) || (i==-4) ) {

		stampa_err(22,1,"ENDCASE");

	   if( i==-4 )
		  return(-1); // E O F senza istruzione END
		else 
		  return(-2); // Incontrata istruzione END

	}

}
contif--;   /* decremento livello nidificazione degli if-case */
contcase--; /* decremento livello nidificazione dei case */

/* riprendo il nome della variabile dallo stack degli argomenti */
if(contcase>0)
	memcpy(nomev,nome_var_case[contcase-1],LUNG_VAR+1);


}

/*********************************************************************
*          							                                       *
*			Procedura procfcase			                                 *
*          							                                       *
*	La procedura viene chiamata quando incontro ENDCASE. Essa         *
* controlla che ci sia un case attivo da chiudere, se lo trova       *
* inserisce nel file intermedio LABEL_XXX corrispondente a fine case *
* ed inserisce nel secondo campo dello stack il PC, corrispondente   *
* all' indirizzo della label.                                        *
*          							                                       *
*********************************************************************/

procfcase()

{

char intlinea[LUNGSTR];
int i,j=0,s=0;

sbianca(intlinea,LUNGSTR-1);

if(contcase==0 || trovbegin[contif-1]!=1) {
	trovbegin[contif-1]=0;
	stampa_err(22,1,"ENDCASE");  /* trovo ENDCASE senza CASE o BEGIN */
	if(contcase!=0)              /* se ENDCASE senza BEGIN, segnalo */
		stackif[contif-1][4]=-1; /* fine CASE */
}
else {
	trovbegin[contif-1]=0;
	fltrbegin[contif-1]=0;
	i=sprintf(intlinea,"%s","LABEL_");  /* preparo label di fine case */
	do {
		j=i;
		j+=sprintf(&intlinea[j],"%03d",stackif[contif-1][s]);
		stackif[contif-1][1]=nword_o; /* indirizzo a cui saltare */
		scrivisufile(fdint,intlinea,j+1,&righeint);
		s+=2;
	}
	while(s<3 && stackif[contif-1][2]!=-1);
	cima=listlabel(cima,0);
	if(stackif[contif-1][2]!=-1)  {
		stackif[contif-1][3]=nword_o;
		cima=listlabel(cima,2);
	}
	for(i=0;i<5;i++)                   /* annullo lo stack corrente */
		stackif[contif-1][i]=-1;   /* segnalando fine case */
}
}

/*********************************************************************
*          							                                       *
*			Procedura procbegin			                                 *
*          							                                       *
*********************************************************************/

procbegin()
{
struct variabili *inserisci();
int tipo,dim,ind;
int codice,M=6,i,ok,j;
char aiuto[12],valore[15],nomevar[LUNG_VAR+1];
char intlinea[LUNGSTR];


trovbegin[contif-1]=1;

if(contcase==0) {
	stampa_err(21,1,"BEGIN"); /* trovato BEGIN senza CASE */
	return(1);
}


sscanf(&linea_cor[M],"%8s",valore);
M+=strlen(valore);
j=0;
if((ok=isintero(valore))!=1)  {

/* Caso di istruzione BEGIN < nome variabile > */
 
	tipo=cerca(testa,valore,&dim,&ind);
	if((tipo & 15)!=4) 
		stampa_err(17,1,valore); /* il valore non e' un intero */
	else {
		if(tipo>=16)
			cnome(valore,&tipo,&M);
		controlla(valore,&M,tipo);
		j+=sprintf(&aiuto[j],"%s",valore);
	}
}

else  {

/* Caso di istruzione BEGIN < valore numerico intero > */

	j+=sprintf(aiuto,"%s","CASE_");
	j+=sprintf(&aiuto[j],"%s",valore);
	testa=inserisci(testa,aiuto,4,&hh,valore,4,0);

}


if ( fltrbegin[contif-1] == 1 ) {

/* Caso istruzioni BEGIN successive senza incontrare BREAK */

	sbianca(intlinea,LUNGSTR-1);

	/* Preparo linea file intermedio */

	j=sprintf(intlinea,"%d",nword_o);    /* inserisco PC */
	intlinea[j++]=BLANK;

	nword_o+=wordpar_ch[0];              /* incremento il PC */

	j+=sprintf(&intlinea[j],"%s","JUMP LABEL_");

	cont_label++;  // incremento il contatore di label 

	j+=sprintf(&intlinea[j],"%03d",cont_label);

	scrivisufile(fdint,intlinea,j+1,&righeint);

	/* Inserisco la label nella lista delle label */

	cima=listlabel(cima,-1);

}

if(stackif[contif-1][0]!=-1) {

/* Caso di istruzione BEGIN diversa dalla prima del CASE */

	stackif[contif-1][1]=nword_o;
	sbianca(intlinea,LUNGSTR-1);
	j=sprintf(intlinea,"%s","LABEL_");
	j+=sprintf(&intlinea[j],"%03d",stackif[contif-1][0]);
	scrivisufile(fdint,intlinea,j+1,&righeint);
	cima=listlabel(cima,0);

}

sbianca(intlinea,LUNGSTR-1);

codice=8;   /* inserisco la scritta del tipo : */

j=POS1;     /* BRNEI  nomelabel  VARIABILE     VALORE */
j+=sprintf(&intlinea[j],"%4d",nword_o);
nword_o+=wordpar_ch[codice];
intlinea[j]=BLANK;
j=POS2;
strcpy(nomevar,par_chiav[codice]);
nomevar[0]=0x42; /* B */
nomevar[1]=0x52; /* R */
j+=sprintf(&intlinea[POS2],"%s",nomevar);
cont_label++;
intlinea[j++]=BLANK;
j+=sprintf(&intlinea[j],"%s","LABEL_");
j+=sprintf(&intlinea[j],"%03d",cont_label);
intlinea[j++]=BLANK;
j+=sprintf(&intlinea[j],"%s",nomev);
intlinea[j++]=BLANK;
j+=sprintf(&intlinea[j],"%s",aiuto);
scrivisufile(fdint,intlinea,j+1,&righeint);
stackif[contif-1][0]=cont_label;
stackif[contif-1][1]=-1;

if ( fltrbegin[contif-1] == 1 ) { 

	sbianca(intlinea,LUNGSTR-1);

	j=sprintf(intlinea,"%s","LABEL_");
	j+=sprintf(&intlinea[j],"%03d",( cont_label - 1 ));
	scrivisufile(fdint,intlinea,j+1,&righeint);

	}

fltrbegin[contif-1] = 1;

}

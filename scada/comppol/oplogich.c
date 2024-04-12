/*
   modulo oplogich.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)oplogich.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/**********************************************************************
*          							                                       *
*			File oplogiche.c			                                    *
*          							                                       *
*		       PROCEDURE CONTENUTE 			                           *
*	logica(codice)                                                    *
*			int codice;                                                 *
*	procentry()                                                       *
*	cod_entry(nomevar,val_M,limite,offset)                            *
*			char nomevar[];                                             *
*			int val_M;                                                  *
*			int limite;                                                 *
*			int offset;                                                 *
*	periodo()                                                         *
*	gestmenu()                                                        *
*	davalore(nomevar,M)                                               *
*			char nomevar[];                                             *
*			int *M;                                                     *
*	gruppi(codice)                                                    *
*			int codice;                                                 *
*	attivo(codice)                                                    *
*			int codice;                                                 *
*	loadm_g(codice)                                                   *
*			int codice;                                                 *
*          							                                       *
*********************************************************************/

#include <osf1.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#ifdef LINUX
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <types.h>
#include <stat.h>
#endif
#include <string.h>

#include "chascii.inc"

#include "tipi.h"

#define 	LUNGSTR	132
#define 	LIM_GR  100
#define	DIM_MENU			20

extern char linea_cor[];
extern int nword_o;
extern int entry[];
extern int inentry;
extern int menu[DIM_MENU][DIM_MENU];
extern int indmenu[];
extern int fdint, fdlst;
extern int righeint;
extern int subrcorr;
extern int val_est[MAX_EST][5];
extern int indcpl;
//
// variabili per gestione listing oggetti 
//
extern char nomeogg[];
extern char nomeogges[];
extern FILE* fpsor;
extern int errori, erroriogg;

/*********************************************************************
*          							     *
*			Procedura logica 			     *
*          							     *
*********************************************************************/

logica(codice)
int codice;
{
int trovato,i,M,tipo,dimvett,indvett;
char nomevar[LUNG_VAR+1];
if(codice==18)
	M=5;
else
	if(codice==23)
		M=3;
	else
		M=4;
while(linea_cor[M]==BLANK)
	M++;
for(i=0;((i<EF_LUNGVAR &&  subrcorr==-1) || (subrcorr!=-1 && i<LUNG_VAR)) &&
	linea_cor[M]!=BLANK && linea_cor[M]!=PUNTO &&
	linea_cor[M]!=0x00 && linea_cor[M]!=APTONDA; M++)
	nomevar[i++]=linea_cor[M];    /* leggo nome variabile */
nomevar[i]=0x00;
tipo=cerca(testa,nomevar,&dimvett,&indvett);
if (tipo==-1) {  // variabile non definita
   stampa_err(59,1,nomevar);
	return(0);
 }
if(tipo>=16)
	cnome(nomevar,&tipo,&M);
if(tipo==5)
	controlla(nomevar,&M,tipo);
if(linea_cor[M]==BLANK || linea_cor[M]==0x00) {
	if(tipo==5 || tipo==1)
		intfile(codice);
	else
		stampa_err(12,1,par_chiav[codice]);
/* variabile non corretta, non e' un logico e non ha estensione */
}
else {
	if(tipo<=2 || tipo==tintero) { /* analogici,digitali,organi e interi*/
		M++;
		for(i=0;i<2 && linea_cor[M]!=BLANK &&
			linea_cor[M]!=0x00;M++)
			nomevar[i++]=linea_cor[M];  /* leggo estensione */
		nomevar[i]=0x00;
	 	trovato=-1;
		for(i=0;i<MAX_EST;i++)    /* cerco se ammissibile */
			if((strcmp(nomevar,estensioni[i]))==0) {
				trovato=i;  /* estensione ammissibile */
				break;
			}
		if(trovato>-1 && (val_est[trovato][tipo]>=0))
			intfile(codice);
		else
			stampa_err(23,1,nomevar);
	}
	else
		stampa_err(12,1,par_chiav[codice]); /* tipo variabile non corretta */
}
}

/*********************************************************************
*          							     *
*			Procedura /procentry			     *
*          							     *
*	La procedura si incarica di decodificare l' istruzione ENTRY *
* analizzando di che tipo di entry si tratta, segnalando eventuali   *
* errori, e inserisce nel vettore entry il valore del program counter*
* aiutandosi se opportuno con la procedura cod_entry. L' ordine con  *
* cui le entry possono essere inserite nel programma e' casuale,     *
* mentre nel vettore sono memorizzate, e verranno quindi scritte sul *
* file di output, con il seguente ordine :                           *
* entry init, entry 0, entry 1, entry term, entry int 0, entry int 1 *
* ........, entry int 47.                                            *
*	Se qualche entry non e' usata il suo valore e' -1.           *
*          							     *
*********************************************************************/
short bFirst=0;
extern int fdout;
procentry()
{
int i,M,j,per;
char nomevar[LUNG_VAR+1];
short limite;
char rigaogg[100];

if(indcpl==2) limite=N_ENTRY;		//Pas
else limite=2;							// Pagine Video
if((i=cod_entry(nomevar,6,limite,1))==1)
{  
   inentry=1;
	return;   /* ENTRY nn gia' risolta da cod_entry */
}

if(!(strcmp(nomevar,"NEW"))) {
   if(bFirst )
   {
   	write(fdout,&nword_o,2);     /* lunghezza file oggetto in word */
      per=0;
   	write(fdout,&per,2);         /* periodo di campionamento       */

   	for(i=0,j=0;i<14;i++)        /* 14 word spare */
	   	write(fdout,&j,2);

   	for(i=0;i<N_ENTRY;i++)
	   	write(fdout,&entry[i],2);   /* inserisco le entry */

   	for(i=0;i<12;i++)
	   	write(fdout,&indmenu[i],2); /* inserisco i menu */
      for(i=0;i<N_ENTRY;i++)       /* inizializzo vettore entry */
	      entry[i]=-1;

      for(i=0;i<12;i++)       /* inizializzo vettore menu  */
      	indmenu[i]=-1;
//
// verifico se sono stati rilevati errori per l'oggetto
// In caso di nessuno errore cancello il file lst
//
     	if(fdlst) close(fdlst);           // chiudo file listing
      if(errori==erroriogg) unlink(nomeogg);
      if(fgets(rigaogg,sizeof(rigaogg),fpsor)!=NULL)
      {
			sscanf(rigaogg,"%s %s",nomeogg,nomeogges);
         strcat(nomeogg,".LST");          // nome file in cui inserire listing
         erroriogg=errori;               // errori attuali
			if(access(nomeogg,0))			  //  se non esiste
			{
	      	fdlst=creat(nomeogg,S_IREAD|S_IWRITE);
   		   close(fdlst);
   		   fdlst=open(nomeogg,O_RDWR|O_BINARY);
			}
			else									// esiste gia' (nome comune a piu' oggetti)
			{
   		   fdlst=open(nomeogg,O_RDWR|O_BINARY|O_APPEND);
				erroriogg--;
			}
      }
   }
   bFirst=1;
	return;           /* al primo posto il PC */
}
inentry=1;
if((strcmp(nomevar,"INIT"))==0) {
	entry[0]=nword_o; /* ENTRY INIT, pongo nel vettore delle entry, */
	return;           /* al primo posto il PC */
}
if((strcmp(nomevar,"TERM"))==0) {
	if(entry[3]==-1) {
		entry[3]=nword_o; /* ENTRY TERM, pongo nel vettore */
		return;           /* delle entry al quarto post il PC */
	}
	stampa_err(25,0,"0"); /* ENTRY TERM gia' definita */
	return;
}
if((strcmp(nomevar,"LBCLK"))==0) {
	if(entry[4]==-1) {
		entry[4]=nword_o; /* ENTRY LBCLK, pongo nel vettore */
		return;           /* delle entry al quarto post il PC */
	}
	stampa_err(25,0,"0"); /* ENTRY LBCLK gia' definita */
	return;
}
if((strcmp(nomevar,"RBCLK"))==0) {
	if(entry[5]==-1) {
		entry[5]=nword_o; /* ENTRY RBCLK, pongo nel vettore */
		return;           /* delle entry al quarto post il PC */
	}
	stampa_err(25,0,"0"); /* ENTRY RBCLK gia' definita */
	return;
}
if((strcmp(nomevar,"LBDCLK"))==0) {
	if(entry[6]==-1) {
		entry[6]=nword_o; /* ENTRY LBDCLK, pongo nel vettore */
		return;           /* delle entry al quarto post il PC */
	}
	stampa_err(25,0,"0"); /* ENTRY LBDCLK gia' definita */
	return;
}
if((strcmp(nomevar,"RBDCLK"))==0) {
	if(entry[7]==-1) {
		entry[7]=nword_o; /* ENTRY RBDCLK, pongo nel vettore */
		return;           /* delle entry al quarto post il PC */
	}
	stampa_err(25,0,"0"); /* ENTRY RBDCLK gia' definita */
	return;
}
if((strcmp(nomevar,"KEY"))==0)
	if((i=cod_entry(nomevar,10,N_ENTRY,8))==1)
		return;  /* ENTRY KEY nn con nn accettabile, gia' svolto da cod_entry */
	else {
		stampa_err(17,1,nomevar); /* ENTRY KEY con numero errato */
		return;
	}
stampa_err(24,0,"0"); /* ENTRY con sequenza successiva errata */
return;
}


/*********************************************************************
*          							     *
*			Procedura cod_entry                          *
*          							     *
*	La procedura testa se l' argomento della entry e' un numero, *
* ed in questo caso alla fine rende 1, o una stringa, in questo caso *
* rende -1. Se si tratta di un numero, ne controlla la validita' e   *
* se corretto lo inserisce nel vettore delle enmtry.                 *
*	Per valutare la correttezza viene passato il parametro limite*
* che vale 2 quando si tratta di una entry semplice e 48 per una     *
* entry int. Per stabilire la posizione nella tabella delle entry si *
* utilizza la variabile offset, che vale 1 per le entry semplici e 4 *
* per le entry int.                                                  *
*          							     *
*********************************************************************/

cod_entry(nomevar,val_M,limite,offset)
char nomevar[];
int val_M;
int limite;
int offset;
{
int M,i,in;
sscanf(&linea_cor[val_M],"%8s",nomevar);
if((isintero(nomevar))==1) {
	in=atoi(nomevar);
	if(limite==N_ENTRY)		/* caso ENTRY INT, devo portare il range da 1..48 a 0..47 */
		in--;
	if(in>=0 && in<limite)
		if(entry[in+offset]==-1)
			entry[in+offset]=nword_o;
		else
			stampa_err(25,0,"0"); /* ENTRY  gia' definita */
	else
		stampa_err(24,0,"0"); /* ENTRY con numero errato */
	return(1);
}
return(-1);
}

/*********************************************************************
*          							                                       *
*			Procedura periodo                                           *
*          							                                       *
* La procedura serve per individuare, se presente il periodo         *
* di campionamento. Per default il suo valore e' 5, che viene reso   *
* se l' istruzione periodo non e' stata trovata. Se l' istruzione    *
* viene trovata, si controlla che l' argomento sia corretto, in ogni *
* caso viene letta la linea successiva.                              *
*          							                                       *
*********************************************************************/

periodo()

{

int n=2;		/* valore di default per il periodo di aggiornamento */
int i,M;
char nomevar[9];
double x;
sscanf(linea_cor,"%8s",nomevar);             /* caricamento parola chiave */

if((strcmp(nomevar,"PERIODO"))==0) {

	/* Riconosciuta parola chiave PERIODO */

	sscanf(&linea_cor[8],"%8s",nomevar);		/* caricamento periodo */

	if((isreale(nomevar))==1) {

		/* nomevar contiene un numero intero */
		x=atof(nomevar);
		if( x>0. && x<1. ) n=-( x*10. );          /* memorizzo il periodo */
      else{
   		i=atoi(nomevar);
	   	if( i>=0 && i<=999 ){
            if(i>127) i=127;
			   n=i;                 /* memorizzo il periodo */
            }
		   else
			   stampa_err(31,1,nomevar);		/* valore intero non accettabile */
   	}
	}
	else
		stampa_err(17,1,nomevar);			/* nomevar non contiene un intero */

	while((i=new_lico())==0)				/* leggo la riga successiva */
		;											/* per ricondurmi nella condizione */
	if(i==-1)									/* di prima riga dopo PERIODO */
		return(-n);

}

return(n); /* se ho trovato il periodo n=periodo, per defalut n=2 */

}

/*********************************************************************
*          							                                       *
*			Procedura gestmenu                                          *
*          							                                       *
* La procedura serve per la gestione dei menu. Essa per ogni         *
* istruzione menu incontrata ne legge il nome (numero) controlla che *
* sia ben definito ed inserisce i gruppi costituenti nella matrice   *
* menu nelle posizioni rispettive. Determina in "i" il numero di     *
* righe della definizione, ed in "max_j" il numero massimo di colonne*
* Quando i gruppi sono terminati (==> incontro "[") inserisco        *
* la matrice relativa a quel menu nel file intermedio, incrementando *
* il P.C. di quanti bytes ho scritto sul file.                       *
* L' ordine di definizione dei menu' e' indifferente.                *
*          							                                       *
*********************************************************************/

gestmenu()
{
int ok,s,t,M,i,j,n,finemenu=1,sem,max_j,lg=-1,vis;
int ris,tot,fine,cont,ins;
char valvar[EF_LUNGVAR+1],stringa[LUNGSTR],nonsel[100][9];

sbianca(stringa,LUNGSTR-1);

while(1) {

	sem=1; /* indica se l' istruzione e' corretta */
	vis=0;

	/* Ciclo di caricamento della parola chiave MENU */

	for(i=0;i<8 && linea_cor[i]>=0x41 && linea_cor[i]<=0x5a;i++)
		valvar[i]=linea_cor[i];
	valvar[i]=0x00;

	if((strcmp(valvar,"MENU"))!=0) {
		if(finemenu==0)
			stampa_err(26,0,"0"); /* non trovata riga con "[" e "]" */
		return(1);
	}

	finemenu=0;

	/* Ciclo di caricamento del numero associato al MENU */

	for(M=5,i=0;i<4 && linea_cor[M]!=BLANK &&
	    linea_cor[M]!=APTONDA && linea_cor[M]!=0x00;M++)
		valvar[i++]=linea_cor[M];
	valvar[i]=0x00;

	/* Ciclo di ricerca carattere "(" */

	while(linea_cor[M]!=APTONDA)
		if(linea_cor[M]==0x00)
			break;
		else
			M++;

	/* Verifico l'accettabilita' del numero associato al MENU */

	if(((isintero(valvar))==1) && ((i=atoi(valvar))>=1) &&
	i<=12 && indmenu[i-1]==-1 ) { 

		/* caso indice MENU accettabile */

		indmenu[i-1]=nword_o;

	}
	else {

		/* Caso indice MENU non accettabile */

		sem=0;
		stampa_err(27,0,valvar); /* numero menu' non valido */

	}

	for(i=0;i<DIM_MENU;i++)
		for(j=0;j<DIM_MENU;j++)
			menu[i][j]=255;

	i=j=max_j=0;

	/* Ciclo di analisi sintattica matrice di gruppi */

	while(1) {

		while(linea_cor[M]!=APTONDA)
			if(linea_cor[M++]==0x00) {
 				stampa_err(6,0,"0");   /* errore di sintassi manca la ( iniziale*/
				linea_cor[M]=CHTONDA;  /* forzo la ) per non segnalare un altro errore */
				break;
			}

		while(linea_cor[M]!=CHTONDA && linea_cor[M]!=0x00) {

			if(linea_cor[++M]==BLANK)
				M++;
			davalore(valvar,&M);
			if((ok=isgruppo(valvar,&lg))!=-1 || (ok=atoi(valvar))==-1) {
				if(j<DIM_MENU)
					if(ok!=-1)
						menu[i][j++]=ok;	// inserisco gruppo 
					else
						menu[i][j++]=255;	// inserisco 255 (gruppo -1)
				else
					stampa_err(28,0,"0"); /* troppi gruppi */
			}
			else
				stampa_err(29,1,valvar); /* gruppo non valido */

		}	// terminata l'analisi di una riga 

		if(linea_cor[M]!=CHTONDA) 
 				stampa_err(6,0,"0"); /* errore di sintassi, manca la ) finale */

		while((n=new_lico())==0)
			;
		if(n==-1)
			return(-1);

		if(linea_cor[0]==APQUADRA) {

		/* Riga corrente che inizia con il carattere "[" */

			finemenu=1; /* istr. menu finita correttamente */
			fine=1;
			tot=0;

		/* Ciclo di ricerca del primo carattere significativo nella riga */

			M = 1;

			while ( (linea_cor[M]==BLANK) || (linea_cor[M]==TAB) ) {

			M++;

			}

			if(linea_cor[M]==CHQUADRA)
				fine=0;

			lg=-1;

			/* Ciclo di analisi lista gruppi tra parentesi quadre */

			while(fine) {

				for(s=0;linea_cor[M]!=BLANK &&
				linea_cor[M]!=VIRGOLA && linea_cor[M]!=0x00 &&
				linea_cor[M]!=CHQUADRA && s<EF_LUNGVAR; M++)
						valvar[s++]=linea_cor[M];
				valvar[s]=0x00;

				/* Ciclo di posizionamento sul primo carattere significativo */

				while ( (linea_cor[M]==BLANK) || (linea_cor[M]==TAB) ) {
					M++;
				}

				switch(linea_cor[M]) {

				case VIRGOLA :
					if(linea_cor[++M]==BLANK)
						M++;
					break;

				case CHQUADRA :
					fine=0;
					break;

				default :

					/* Attenzione gestione non CHIARA !!! */

					while((n=new_lico())==0)
						;
					if(n==-1)
						return(-1);
					M=0;
					break;

				} /* fine switch su linea_cor[M] */

 				if((ok=isgruppo(valvar,&lg))!=-1 && presente(ok,i+1,max_j+1)==0) {

					strcpy(nonsel[tot++],valvar);

				}
				else
					stampa_err(75,1,valvar);

			if(tot>LIM_GR) {
				stampa_err(30,0,"0"); /* troppi gruppi */
				break;
			}

	      }  /* fine while(fine) di analisi lista gruppi tra par. quadre */

			while((n=new_lico())==0)
				;
			if(n==-1)
				return(-1);

			if(j-1>max_j)
				max_j=j-1; /* determino il max numero di componenti per ogni riga 
								  tenendo conto che ha senso solo quando ho un menu
								  con una sola riga, e che , quindi, non passo da sotto */
			break;

		}	/* la nuova riga non inizia con il carattere "[" */

		/* Incremento l'indice di riga i */

		i++;

		if(j-1>max_j)
			max_j=j-1; /* determino il max numero di
                       componenti per ogni riga */

		/* Reset puntatore carattere in linea_cor M e indice di colonna j */

		M=j=0;

	} /* fine while(1) di analisi sintattica MENU */

	max_j++;
	if((max_j%2)!=0)
		max_j++;
	if(sem==1) {   /* devo inserire nel file intermedio il menu
	                  ed incrementare il P.C. */
		j=3;
		j+=sprintf(&stringa[3],"%4d",nword_o);
		t=(i+1)*256+(max_j);
/**
		t=(i+1)+(max_j)*256;
**/
		j+=3;
		j+=sprintf(&stringa[j],"%s","$");
		j+=sprintf(&stringa[j],"%04x",t);
		j+=3;
		j+=sprintf(&stringa[j],"%s","$");
		j+=sprintf(&stringa[j],"%04x",0);
		j+=3;
		t=255+(tot+1)/2*256;
		j+=sprintf(&stringa[j],"%s","$");
		j+=sprintf(&stringa[j],"%04x",t);
		for(t=3;t<j;t++)
			if(stringa[t]==0x00)
				stringa[t]=BLANK;
		scrivisufile(fdint,stringa,j+1,&righeint);
		sbianca(stringa,j);
		for(s=0;s<=i;s++) {
			sprintf(&stringa[3],"%4d",nword_o);
			j=7;
			for(t=0;t<max_j;t+=2) {
				j+=3;
				M=menu[s][t]+(256*menu[s][t+1]);
				j+=sprintf(&stringa[j],"%s","$");
				j+=sprintf(&stringa[j],"%04x",M);
			}
			for(t=3;t<j;t++)
				if(stringa[t]==0x00)
					stringa[t]=BLANK;
			scrivisufile(fdint,stringa,j+1,&righeint);
			sbianca(stringa,j);
		}
	/* inserisco i gruppi visualizzabili ma non selezionabili */
		for(ris=0;ris<tot;) {
			sprintf(&stringa[3],"%4d",nword_o);
			j=7;
			for(cont=0;cont<8 && ris<tot;cont++,ris++) {
				ok=isgruppo(nonsel[cont],&lg);
				if((ris%2)!=0) {
					ins=ins+256*ok;
					j+=3;
					j+=sprintf(&stringa[j],"%s","$");
					j+=sprintf(&stringa[j],"%04x",ins);
				}
				else
 					ins=ok;
				if(ris==tot-1 && (tot%2)!=0) {
					ins=ins+256*255;
					j+=3;
					j+=sprintf(&stringa[j],"%s","$");
					j+=sprintf(&stringa[j],"%04x",ins);
				}
			} /* fine for interno */
			for(t=3;t<j;t++)
				if(stringa[t]==0x00)
					stringa[t]=BLANK;
			scrivisufile(fdint,stringa,j+1,&righeint);
			sbianca(stringa,j);
		}   /* fine for esterno */
		if((tot%2)==1)
			tot++; /* anche se il numero di gruppi e' dispari
				  bisogna considerarli sempre due a due */

/* inserisco il tappo -1 */

		j=3;
		j+=sprintf(&stringa[3],"%4d",nword_o);
		stringa[j]=BLANK;
		t=-1;
		j+=3;
		j+=sprintf(&stringa[j],"%s","$");
		j+=sprintf(&stringa[j],"%04x",t);
		scrivisufile(fdint,stringa,j+1,&righeint);
		sbianca(stringa,j);

		nword_o+=((i+1)*(max_j)/2)+3+tot/2+1; /* incremento P.C.
				   i+1     = numero righe
			  	   max_j = numero max colonne
				   3       = num. word per ogni menu
				   tot /2  = num. di gruppi non sel.
					1		  = tappo finale        		*/
	}
} /* fine while esterno */
}

/*********************************************************************
*          							     *
*          							     *
*********************************************************************/

presente(ok,imax,jmax)
int ok,imax,jmax;
{
int i,j;
for(i=0;i<imax;i++)
	for(j=0;j<jmax;j++)
		if(menu[i][j]==ok)
			return(1);
return(0);
}

/*********************************************************************
*          							     *
*			Procedura davalore                           *
*          							     *
*	Rende in nomevar il nome del gruppo, fermandosi al BLANK,    *
* alla virgola o alla parentesi tonda chiusa.                        *
*          							     *
*********************************************************************/

davalore(nomevar,M)
char nomevar[];
int *M;
{
int i;
for(i=0;linea_cor[*M]!=BLANK && linea_cor[*M]!=0x00 &&
    linea_cor[*M]!=VIRGOLA && linea_cor[*M]!=CHTONDA && i<EF_LUNGVAR; (*M)++)
	nomevar[i++]=linea_cor[*M];
nomevar[i]=0x00;
while(linea_cor[*M]!=VIRGOLA && linea_cor[*M]!=CHTONDA &&
      linea_cor[*M]!=0x00)
	(*M)++;
}

/*********************************************************************
* 																							*
*                       Procedura gruppi                             *
*                                                                    *      
*	La procedura si occupa di alcune istruzioni riguardanti i         *
* gruppi, e precisamente OUTG, INV, VISON, VISOFF, TSEL, 				*
*     																					*
* Per ciascuna l'argomento successivo e' opzionale (intero o costante*
* gruppo) ed indica l'oggetto grafico a cui e' riferito.
* Solo per le istruzioni OUTG e OUTGV e' possibili elencare le variabili
* associate al gruppo (possono essere di qualsiasi tipo).
* controlla che l' argomento successivo sia un intero o una costante *
* intera. In caso affermativo inserisce l' istruzione nel file       *
* intermedio, viceversa segnala errore.                              *
* E' chiamata anche, e si comporta allo stesso mod o per la NCURDS   *
*          							                                       *
*********************************************************************/

#define POS1	     3
#define POS2	    10

gruppi(codice)
int codice;
{
int dim,ind,i,M,ok, Msave;
char nomevar[LUNG_VAR+1];
char stringa[LUNGSTR];
int j;
short spiazzPC=1;					// n. word occupate dall'istruzione
short tipo;

switch (codice) {
case 33 :		 /* INV */
	M=4;
	break;
case 34 :		 /* VISON */
	M=7;
	break;
case 35 :		 /* VISOFF */
	M=8;
	break;
case 116 :		 /* NCURS */
	M=6;
	break;
case 99:       /* accept */
   M=7;
   break;
case 127 :		 /* OUTGV */
	M=6;
	break;
default :		 /* OUTG, TSEL, ZOOM, CONF, COLL */
	M=5;
	break;
}

memset(stringa,' ',sizeof(stringa));
j=POS1;
j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC */
stringa[j]=BLANK;
j=POS2;
j+=sprintf(&stringa[j],"%s",par_chiav[codice]);  /* inserisco SEND */
scrivisufile(fdint,stringa,j+1,&righeint);
spiazzPC=1; /* comincio a calcolare il codice prodotto da send */

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
		ciclo ricerca nomi variabili solo per istruzioni OUTG e OUTGV
*/
linea_cor[M]=' ';			// elimino (
while(linea_cor[M]==' ') M++;

for(;;)
{
	memset(stringa,' ',sizeof(stringa));
	j=POS1;
	j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC, */
	stringa[j++]=BLANK;
	j=POS2+6;
	legginvar(nomevar,codice,&M,2);
	if(!strlen(nomevar))			// inserisco tappo solo se si tratta di OUTG o OUTGV
	{
		if(!strcmp(par_chiav[codice],"OUTG") || !strcmp(par_chiav[codice],"OUTGV")
   		|| !strcmp(par_chiav[codice],"ACCEPT"))
		{
			memset(stringa,' ',sizeof(stringa));
			j=POS1;
			j+=sprintf(&stringa[j],"%4d",nword_o);  /* inserisco il PC, */
			stringa[j++]=BLANK;
			j=POS2+6;
			sprintf(&stringa[j],"-1");
			scrivisufile(fdint,stringa,0,&righeint);
			spiazzPC+=1;
		}
		break;
	}
	if(strcmp(par_chiav[codice],"OUTG") && strcmp(par_chiav[codice],"OUTGV")
   		&& strcmp(par_chiav[codice],"ACCEPT"))
	{
		stampa_err(6,0,nomevar);	 // errore di sintassi
		break;
	}
	if(nomevar[strlen(nomevar)-1]==CHTONDA)	// fine istruzione
	{
		nomevar[strlen(nomevar)-1]=0;
		linea_cor[M-1]=' ';
		M--;
	}
	tipo=cerca(testa,nomevar,&dim,&ind);
	if(tipo>=16)	cnome(nomevar,&tipo,&M);
	controlla(nomevar,&M,tipo);
	switch(tipo)
	{
	case tanalogico : 
	case treale : 		
	case tdigitale:
	case tintero:
	case tlogico:
	case tstringa:
   case torgano:
	break;
	default:
   	stampa_err(12,1,nomevar);  	// tipo non accettabile
	break;
	}
	sprintf(&stringa[j],"$%02d02 %s",tipo,nomevar);
	scrivisufile(fdint,stringa,0,&righeint);
	spiazzPC+=2;
	M++;						// elimino ;
}
nword_o+=spiazzPC;  /* aggiorno il PC */
}

/*********************************************************************
*          							     *
*			Procedura attivo                             *
*          							     *
*	La procedura controlla che il menu indicato nell' istruzione *
* sia stato definito precedentemente con l' istruzione menu, se si   *
* inserisce l' istruzione sul file intermedio, altrimenti segnala    *
* un errore.                                                         *
*       							     *
*********************************************************************/

attivo(codice)
int codice;
{
int ok,M;
char valvar[9];
M=6;
if((ok=ismenu(valvar,&M))==-1)
	stampa_err(27,1,valvar); /* numero menu non corretto */
else
	intfile(codice);     /* inserisco nel file intermedio */
}

/*********************************************************************
*          							     *
*			Procedura loadm_g                            *
*          							     *
*********************************************************************/

loadm_g(codice)
int codice;
{
int i,M,tipo,ind,dim;
char nomevar[LUNG_VAR+1];
for(M=5,i=0;linea_cor[M]!=BLANK && linea_cor[M]!=0x00 &&
    linea_cor[M]!=VIRGOLA && linea_cor[M]!=CHTONDA &&
    ((subrcorr==-1 && i<EF_LUNGVAR) || (subrcorr!=-1 && i<LUNG_VAR)); M++)
	nomevar[i++]=linea_cor[M];
nomevar[i]=0x00;
if(i==0) {
	stampa_err(6,0,"0"); /* non e' presente nessuna variabile */
	return;              /* come fine riga inaspettata */
}
if(((tipo=cerca(testa,nomevar,&dim,&ind)) & 15 )!=4) {
	stampa_err(12,1,nomevar); /* variabile non presente o non intera */
	return;
}
if(tipo>=16)
	cnome(nomevar,&tipo,&M);
if((i=controlla(nomevar,&M,tipo))!=-1)
	intfile(codice);
}

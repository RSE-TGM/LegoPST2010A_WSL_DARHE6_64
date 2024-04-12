/*
   modulo inser_in.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)inser_in.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <osf1.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <string.h>

#include "chascii.inc"
#include "define.inc"

#include "fledf.inc"

#define		DIMFILE		40

extern short opzenvincl;      /* opzione di set ambiente per INCLUDE */
extern char  envincl[];       /* stringa contenente il path di ambiente */

extern int fdi;      /* descrittore del file sorgente      */
extern int fdint;    /* descrittore del file intermedio    */
extern int fddeb;    /* descrittore del file di debugger   */
extern int nrigaco;  /* numero relativo di riga nel modulo corrente */
extern int numriga;  /* numero riga corrente file di input */
extern int cfiltmp;  /* contatore file temporanei prodotti */

extern int stkinc[]; /* Pseudo stack di gestione annidamento INCLUDE */

extern int *stk;     /* Puntatore allo pseudo stack */

extern char dzmod[]; /* Dizionario nomi moduli di INCLUDE */
extern int odzmod;   /* indice occupazione diz. nomi moduli INCLUDE */


#include "all_1.h"
extern struct TBIND {

	int ptdzmod;  /* indice relativo al primo byte del nome modulo */
	int indass;   /* indice assoluto di riga nel file sorgente */
	int indrel;   /* indice relativo di riga nel file corrente */
	};
#include "all_16.h"

extern struct TBIND tabind[];  /* Tabella indici assoluti e relativi */

extern int itabind;  /* indice progressivo Tabella indici */


inser_include(nomefile)

char nomefile[];   /* Nome del file sorgente */

{

int i;
FILE *fpi; /* descrittore file sorgente */
FILE *fpo; /* descrittore file di output */

char appdizio[NBYMOD];  /* Variabile di appoggio nome modulo INCLUDE */

int ier,lstrin,indstr;

/* Chiudo il file sorgente */

close(fdi);

/* Apro su fpi il file sorgente da compilare */
/* Apro su fpo il file di espansione istruzioni INCLUDE <0.TMP> */

fpi=fopen(nomefile,"r+");
fpo=fopen("0.tmp","w+");

/* Inizializzo il pseudo stack di gestione annidamento INCLUDE */

for ( i = 0; i < NWSTKINC; i++ ) {
	stkinc[i] = -1;
	}

/* Inizializzo il dizionario nomi moduli di INCLUDE */

for ( i = 0; i < DDZMOD; i++ ) {
	dzmod[i] = 0x20;
	}

/* Inizializzo tabella indici assoluti e relativi di riga */

for ( i = 0; i < NRTABIND; i++ ) {
	tabind[i].ptdzmod = -1;
	tabind[i].indass = -1;
	tabind[i].indrel = -1;
	}

/* Inizializzo il primo livello dello stack e della tabella tabind */

memset(appdizio,0x20,NBYMOD);

lstrin = strlen(nomefile);

strncpy(appdizio,nomefile,lstrin);

ier = gesdizio(dzmod,DDZMOD,NBYMOD,appdizio,&odzmod,&indstr);

/* Inserimento primo livello pseudo stack */

*(stk) = indstr;
*(stk+1) = numriga;
*(stk+2) = nrigaco;

/* Aggiorno il puntatore allo stack */

stk+=3;

/* Inserisco la prima riga della tabella indici */

tabind[itabind].ptdzmod = indstr;
tabind[itabind].indass = numriga;
tabind[itabind].indrel = nrigaco;

/* Aggiorno l'indice corrente della tabella indici */

itabind++;

ins_incl(fpi,fpo,&cfiltmp,nomefile);

/* Chiudo il file 0.TMP */

fclose(fpo);

/* Apro su fdi il file 0.TMP */

fdi=open("0.tmp",O_RDONLY);

numriga=0;
}



ins_incl(fpi,fpo,numfile,nommod)

FILE *fpi; /* descrittore file di input  */
FILE *fpo; /* descrittore file di output */
int *numfile;
char *nommod;

{

FILE *fploc;
char linea[DMX_RIGA+1],*p,*t,nomefile[DIMFILE+1],nomerec[13];
int ret,nomereci[6];

char appdizio[NBYMOD];  /* Variabile di appoggio nome modulo INCLUDE */
char appconc[NBYMOD];  /* Variabile di appoggio nome modulo INCLUDE */
char appmod[13];        /* Variabile di appoggio da espandere  */

int ier,lstrin,indstr;

short lstrconc;

/* Inizializzo la variabile di appoggio tutta con il carattere blank */

memset(appdizio,0x20,NBYMOD);
memset(appmod,0x00,13);

p=linea;

/* Azzero il contatore di riga relativo al modulo corrente */

nrigaco = 0;

/* Ciclo principale di lettura dal file sorgente */

while( (fgets(linea,DMX_RIGA,fpi)) != NULL ) {

	numriga++;
	nrigaco++;
	ret=0;

/* Verifico se la linea corrente contiene la stringa INCLUDE */

/* Converto tutti i caratteri alfabetici in maiuscolo */

   strupr(linea);

	if( (p=strstr(linea,"INCLUDE") ) != NULL)
		ret=1;

/* Scandisco l'intera linea (caratteri di terminazione 0x0d 0x0a) */
/* alla ricerca del carattere <;> di definizione dei commenti     */

	for(t=linea; *t!=0x0a && *t!=CAR_COMM; t++)
	 ;
	if( ret==1 && p<t ) {

	/* Ho trovato una istruzione INCLUDE */

   /* Sposto il puntatore sul primo carattere del nome file di editing */

		p+=8;

 /* Determino il nome del file di editing e lo inserisco in nomefile  */
 /* Trascuro nella ricerca il carattere blank e il carattere tab 0x09 */

		while(*p==BLANK || *p==TAB)
			p++;

		for(ret=0; ret<DIMFILE && *p>0x20 && *p< 0x7a && *p!=0x0d && *p!=0x0a; ret++,p++)
			nomefile[ret]=*p;

/* Inserisco il carattere nullo di terminazione del nome file di editing */

		nomefile[ret]=0x00;
		fploc=fopen(nomefile,"r");
		if(!fploc)					// file di include non esistente
		{
			   stp0_err(51,1,nomefile,nommod);
			   if ( fddeb > 0 ) {
			     close(fddeb);
				  unlink("CODICE.DEB");
				}
			   if ( fdint > 0 ) {
			     close(fdint);
				  unlink("CODICE.INT");
				}
			   fclose(fpo);
			   fclose(fpi);
			   delfcomp(*numfile);	 			// chiusura file temporanei
			   exit(0);
		}
		else
		{
	   /* Operazioni di concatenazione INCLUDE */

	      ier = gesdizio(dzmod,DDZMOD,NBYMOD,appdizio,&odzmod,&indstr);
		   ier = pushinc(indstr);
			strcpy(appmod,nomefile);
		   ins_incl(fploc,fpo,numfile,appmod);
		}
	}

	else {

/* Ricopio dalla posizione corrente la linea sul file di output */

		fputs(linea,fpo);

	}

	sbianca(linea,DMX_RIGA);

}

/* Trovata la file del file di espansione corrente */

ier = popinc();

fclose(fpi);

}

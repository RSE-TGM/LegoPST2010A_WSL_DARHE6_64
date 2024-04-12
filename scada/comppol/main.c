/*
   modulo main.c
   tipo 
   release 1.2
   data 6/13/96
   reserved @(#)main.c	1.2
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
#ifdef LINUX
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <types.h>
#include <stat.h>
#endif
#include <io.h>
#include <memory.h>

#include "chascii.inc"
#include "define.inc"
#include "tipi.h"
#include "gesincl.inc"
/*
        31/10/95        mp
        Aggiunto switch /u per la scelta dell'utente    
*/ 

#define Versione "\r\n "

#ifdef INGLESE
   char intestaz[]=" name                         code       type        dim     def_row   ";
   char *desicpl[] = {									  
   "  SYNOPTIC      ",
   "  REPORT    ",
   "  APPLICATION PROGRAM    " };
#define errParNum    "\n Error : bad parameters number\n"
#define noSource     "\n Error : source file not found\n"
#define noCompInd    "\n Error : compiling address undefined\n"
#define InOp         "\nError : Options mismatch\n"
#define errDupOp     "\nError : Duplicated option < %s >  \n"
#define badOp        "\nError : < %s > bad option\n"
#define opstrTooL    "\nError : Option string < %s > too long\n"
#define sintOp       "\nError : Bad option syntax < %s > \n"
#define UnOpIn       "\nUnknown option ignored\n"
#define POLComp      "\n\r P.O.L. Win Compiler %s - Ver. 1.10"
#define FirstStep    "\n\n\r First step   "
#define DBLOvFlw     "\n ***** ERROR DBL overflow (max. 2048 byte) \n"
#define attention    "\n Attention :\n"
#define errsF        " %d  errors found - "
#define errF         " %d  error found - "   
#define noSecStep    " Can't go on with second step\n"
#define firstStepEnd "First step end   "
#define secondStep   "Second step  "
#define End          "End\n"
#else
#define End          "Fine compilazione\n"
#define secondStep   "Secondo passo  "
#define firstStepEnd "Fine primo passo   "
#define noSecStep    " Impossibile procedere al secondo passo\n"
#define errF         " %d  errore trovato - "   
#define errsF         " %d  errori trovati - "
#define attention    "\n Attenzione :\n"
#define DBLOvFlw     "\n ***** ERROR Superata la dimensione massima DBL (2048 byte) \n"
#define FirstStep    "\n\r Primo passo   "
#define POLComp      "\n\r Compilatore linguaggio P.O.L.II Win %s - Ver. 1.10"
#define UnOpIn       "\nOpzioni non considerate perche' errate\n"
#define sintOp       "\nErrore : Sintassi opzione < %s > non corretta\n"
#define opstrTooL    "\nErrore : Stringa opzione < %s > troppo lunga\n"
#define badOp        "\nErrore : Opzione < %s > non ammessa\n"
#define errDupOp     "\nErrore : Opzione < %s >  duplicata \n"
#define InOp         "\nErrore : Opzioni incompatibili\n"
#define noCompInd    "\n Errore : indirizzo di compilazione omesso\n"
#define noSource     "\n Errore : il file sorgente non esiste\n"
#define errParNum    "\n Errore : errato numero di argomenti\n"
   char intestaz[]=" nome                        codice     tipo        dim     riga_def  ";
   char *desicpl[] = {									 
   "  PAGINE VIDEO  ",
   "  TABULATI  ",
   "  PROGRAMMI APPLICATIVI  " };
#endif

short opzenvincl=0;
short opzuser=0;

char 	envincl[NBYMOD];


int fdi;        /* descrittore del file sorgente */
int fdint;      /* descrittore del file intermedio */
int fdmap;      /* descrittore del file di mappa */
int fdout; 	    /* descrittore del file finale */
int fdlst=0;    /* descrittore del file di listing */
int fdsym=0;    /* descrittore simboli */
int fddeb=0;	 /* descrittore del file per debugger */
FILE *fpsor;    /* file pointer lista nomi oggetti in compilazione */


int indcpl=-1;	 /* indirizzo di compilazione  */

char c[3];   /* Contiene i seguenti codici ASCII 0D 0A 00 */

/* Il vettore entry contiene l'indirizzo di posizionamento del PC 
   relativo alle entry :
		 entry init  --> offset 0
 	    entry    0  --> offset 1
 	    entry    1  --> offset 2
		 entry term  --> offset 3
 	    entry int 1 --> offset 4 ( ammessi da 1 a 48 ) */


int entry[N_ENTRY];

int indmenu[12];

int INDDB=0;      /* quantita' di DB occupata, primo indirizzo libero */

int contsubr=0;   /* numero di subroutine definite */

int numvar_deb=0; /* numero di variabili da scrivere nel file di debugger */

int rigaerr=2;     /* indica la riga di video ove scrivere l' errore */

int istruzioni=0;  /* numero di istruzioni analizzate */

int cont_label=0;  /* numeri di etichette costruite */

int cont=0;

int FINEPAGINA=58; /* lunghezza pagine dei file di listing e interm. */

int inentry=0;     /* se =1 ==> ho incontrato una entry 
                      se =0 ==> trovato term della entry */

int menu [DIM_MENU][DIM_MENU];

int cont_gruppi=0;

int errori=0;     /* numero di errori trovati durante la compilazione */
int erroriogg;    /* numero di errori associati al singolo oggetto */

int nword_o=0;    /* numero di word nel file di output */

int contcase=0;   /* numero di case nidificati */

int contloop=0;   /* numero di loop nidificate */

int contif=0;     /* indica il numero di if nidificati in quel momento */

short flgjump=0;  /* flag che indica l'utilizzo della istruzione JUMP */
short flgloop=0;  /* flag che indica l'utilizzo della istruzione LOOP */
short flgreploop=0; /* flag che indica l'utilizzo della istruzione REPLOOP */

int contgosub=0;  /* numero di chiamate di subroutine */

int stop_link;

int righelst=58;

/* contatore linea scritte nella pagina corrente file di listing */

int righeint=58;

/* contatore linea scritte nella pagina corrente file intermedio */

char linea_cor[DMX_RIGA];

char nome_var_map[LUNG_VAR_LINK_DBS+1];

extern int subrcorr;

extern int tvarsubr[NUM_SUBR][NUM_ARG+1];

extern char *nomi_subr[];

char nomeogg[FILENAME_MAX+1];                // nome dell'oggetto di cui si sta compilando il codice        */
char nomeogges[FILENAME_MAX+1];              // nome dell'oggetto di cui si sta compilando il codice        */

void setuserp();                // set ambiente per utente PIOMBINO

/**********************************************************************
*								                                              *
*		                main                        	                   *
*								                                              *
* E' il main del programma, controllato che il numero di argomenti    *
* passati al programma siano corretti e che il file passato esista,   *
* chiama la procedura "var" per inizializzare le variabili e          *
* successivamente la procedura scegli per la gestione della compila=  *
* zione. Terminata quest' ultima se non ci sono errori crea il file   *
* di uscita, altrimenti segnala il numero di errori trovati.          *
*								                                              *
**********************************************************************/

main(argc,argv)

int argc;         /* Numero degli argomenti passati */
char *argv[];     /* Vettore di puntatori alle stringhe argomemto */

{

int opzioni=1;      /* flag presenza opzioni di compilazione */
int cancella=1;     /* flag cancellazione file intermedio  */
int list_only=0;    /* flag richiesta file di listing senza simbol table */
int list_sym=0;     /* flag richiesta file di listing con simbol table   */
int deb=0;          /* flag opzione di debugger */
int listtable=0;    /* flag richiesta file di estensione .map */
char nomesor[FILENAME_MAX+1];   /* nome file sorgente da compilare        */
short lnomesor;     /* lunghezza nome sorgente                 */
FILE *fpL;          /* file pointer lista sorgenti            */

char rigaogg[100];

int per,rel=0,s,rit,j,i;
int iniziocost;
long DIST;
char f[2],loc[7];

short flgop,indop;
short lenvincl,ier;
char strapp[5];

/* Controllo la correttezza formale della linea di comando */

/* Controllo il numero degli argomenti passati */

if(argc<=1) {
	printf(errParNum);
	exit(0);
	}

/* Controllo le opzioni di help ammesse */

if((strcmpi(argv[1],"/h"))==0 || (strcmp(argv[1],"?"))==0)

	help_menu();

strcpy(nomesor,argv[1]);
lnomesor=strlen(nomesor);

if(argc>3) {
	opzioni=0;
	}

/* Analisi indirizzo di compilazione passato come parametro */

if( (strcmpi(argv[2],"/0")!=0) &&
    (strcmpi(argv[2],"/1")!=0) &&
    (strcmpi(argv[2],"/2")!=0) ) {

  /* Indirizzo di compilazione omesso */

	printf(noCompInd);
	exit(0);

	}

/* Converto in formato intero l'indirizzo di compilazione */

indcpl = atoi( (argv[2] + 1) );

/* Ciclo di analisi delle opzioni passate come argomenti */

for(i = 3; i < argc; i++) {

	flgop = 0;

	/* Ciclo di ricerca nel vettore delle opzioni ammesse */

	for ( indop = 0; indop < NMXOPCMP; indop++ ) {

		if ( ( strcmpi(argv[i],stropcmp[indop]) ) == 0 ) {

			/* Argomento compreso tra le opzioni ammesse */
			/* verifico una eventuale duplicazione di argomenti */

			if ( utiopcmp[indop] < 0 ) {

				utiopcmp[indop]=1;

				switch (indop) {

					case 0:

						opzioni=1;  /* opzione corretta */
						cancella=0; /* non cancellare il file intermedio */

					break;

					case 1:

						if(list_only==1) {
							printf(InOp);
							exit(0);    /* voglio e non voglio la ST */
						}

				 		else  {
							list_sym=1; /* file di listing con ST */
							opzioni=1;  /* opzione corretta */
						}

					break;

					case 2:

						if(list_sym==1) {
							printf(InOp);
							exit(0);
						}

 					   else {

							list_only=1;   /* file listing senza simbol table */
							opzioni=1;     /* opzione corretta */

						}


					break;

					case 3:

						listtable=1;  /* file di estensione .map */
						opzioni=1;    /* opzione corretta */

					break;

					case 4:

						opzioni=1; /* opzione corretta */
						deb=1;     /* opzione debugger */

					break;

				}

				flgop = 1;

				break;

			}

			else {

			/* rilevata duplicazione argomento */

			printf(errDupOp,argv[i]);
			exit(0);

			}
		}
	}

	if ( flgop == 0 ) {

		/* Argomento non trovato tra le opzioni ammesse */

		memcpy(strapp,argv[i],4);

		strapp[4] = 0x00;

		if ( ( strnicmp(strapp,"/U",2) ) == 0 ) {	/* opzione tipo utente */
			if (opzuser) {
				printf(errDupOp,argv[i]);		/* opzione duplicata */
				exit(0);
			}
			else {
				opzuser++;
				if(strapp[3]!='\0') {
				 	printf(badOp,argv[i]);
				 	exit(0);
				}
				switch(strapp[2]) {
					case 'p':			
					case 'P':
						setuserp();
						opzioni=1;
						break;
					default:
						printf(badOp,argv[i]);
						exit(0);
				}
			}
		}
		else if ( ( strcmpi(strapp,"/IE=") ) == 0 ) {

			if ( opzenvincl == 0 ) {

				/* Analisi sintattica opzione di ambiente include IE */

				lenvincl = strlen( (argv[i] + 4) );

				if ( lenvincl > (NBYMOD - 2) ) {

					printf(opstrTooL,argv[i]);
					exit(0);

				}

				memcpy (envincl,(argv[i] + 4),lenvincl);

				ier = ctreninc(envincl);

				if ( ier != 0 ) {

					printf(sintOp,argv[i]);
					exit(0);

				}

				/* setto il flag di utilizzo opzione di ambiente include */

				opzenvincl = 1;
				opzioni=1;

				/* termino la stringa di path con il carattere BAKSLASH */

				if ( envincl[lenvincl - 1] != BAKSLASH ) {

					envincl[lenvincl] = BAKSLASH;

					lenvincl++;

					envincl[lenvincl] = 0x00;

				}


			}

			else {

				/* rilevata duplicazione argomento */

				printf(errDupOp,argv[i]);
				exit(0);

			}

		}
		else {
			printf(badOp,argv[i]);
			exit(0);
		}

	}

/* Chiusura ciclo di analisi opzioni */

}
INIZIO:                 // ciclo di compilazione di un sorgente

errori=0;     /* reset numero di errori trovati durante la compilazione */
nword_o=0;    /* numero di word nel file di output */
contcase=0;   /* numero di case nidificati */
contloop=0;   /* numero di loop nidificate */
contif=0;     /* indica il numero di if nidificati in quel momento */
flgjump=0;  /* flag che indica l'utilizzo della istruzione JUMP */
flgloop=0;  /* flag che indica l'utilizzo della istruzione LOOP */
flgreploop=0; /* flag che indica l'utilizzo della istruzione REPLOOP */
contgosub=0;  /* numero di chiamate di subroutine */
righelst=58;
righeint=58;
INDDB=0;      /* quantita' di DB occupata, primo indirizzo libero */
contsubr=0;   /* numero di subroutine definite */
numvar_deb=0; /* numero di variabili da scrivere nel file di debugger */
istruzioni=0;  /* numero di istruzioni analizzate */
cont_label=0;  /* numeri di etichette costruite */
cont=0;
inentry=0;     /* se =1 ==> ho incontrato una entry 
                      se =0 ==> trovato term della entry */

if((fdi=open(nomesor,O_RDONLY))==-1) {    // open sorgente
	printf(noSource);
	exit(0);
	}

strcpy(&nomesor[lnomesor],".SOR");        // open lista oggetti inseriti nel sorgente
fpsor=fopen(nomesor,"r+");
if(fpsor==NULL)
{
	perror(nomesor);
	exit(0);
}
if(fgets(rigaogg,sizeof(rigaogg),fpsor)!=NULL)
{
		sscanf(rigaogg,"%s %s",nomeogg,nomeogges);
      strcat(nomeogg,".LST");          // nome file in cui inserire listing
      erroriogg=errori;               // errori attuali
      unlink(nomeogg);
}

if(opzioni==0)
	printf(UnOpIn);

/* Analisi opzioni relative al file di listing */

strcpy(&nomesor[lnomesor],".AB");
unlink(nomesor);
strcpy(&nomesor[lnomesor],".MAP");
unlink(nomesor);

if(list_only==1 || list_sym==1) {

/* Opzione di compilazione /ls o /lo */

/* Cancello Creo e Apro il file nomeogg.LST */

   strcpy(&nomesor[lnomesor],".LST");
	fdlst=creat(nomeogg,S_IREAD|S_IWRITE);
	close(fdlst);
	fdlst=open(nomeogg,O_RDWR|O_BINARY);
}

strcpy(&nomesor[lnomesor],".DEB");
unlink(nomesor);

if(deb==1) { 

/* Opzione di compilazione /deb */

/* Cancello Creo e Apro il file CODICE.DEB */

	fddeb=creat(nomesor,S_IREAD|S_IWRITE);
	close(fddeb);
	fddeb=open(nomesor,O_RDWR|O_BINARY);

}

strcpy(&nomesor[lnomesor],".SYM");
unlink(nomesor);

if(list_sym==1) { 			// richiesta symbol table

/* Cancello Creo e Apro il file *.sym */

	fdsym=creat(nomesor,S_IREAD|S_IWRITE);
	close(fdsym);
	fdsym=open(nomesor,O_RDWR|O_BINARY);

}
/* Inizio PRIMO PASSO COMPILAZIONE */

printf(Versione);
printf(POLComp,desicpl[indcpl]);
nomesor[lnomesor]=0;
printf(" %s",nomesor);
printf(FirstStep);
c[0]=0x0d;
c[1]=0x0a;
c[2]=0x00;

/* Cancello Creo e Apro il file intermedio CODICE.INT */

strcpy(&nomesor[lnomesor],".INT");
unlink(nomesor);
fdint=creat(nomesor,S_IREAD|S_IWRITE);
close(fdint);
fdint=open(nomesor,O_RDWR|O_BINARY);

for(i=0;i<N_ENTRY;i++)       /* inizializzo vettore entry */
	entry[i]=-1;

for(i=0;i<12;i++)       /* inizializzo vettore menu  */
	indmenu[i]=-1;

for(i=0;i<NUM_SUBR;i++)       /* inizializzo tabella tipi variabile delle subr */
	for(s=0;s<NUM_ARG+1;s++)
		tvarsubr[i][s]=-1;

nomesor[lnomesor]=0;
rit=inser_include(nomesor);  /* espansione  istruzioni INCLUDE  abbandonate */

rit=var();            	     /* inserisco le variabili DEFINE */

rit=cost();           	     /* inserisco le costanti  DATA   */

rit=letturadb();             /* cerco le variabili di LINK */

rit=gestmenu();              /* definizioni dei menu' di selezione */

per=periodo();      /* periodo */
//if((per=periodo())<0) {      /* periodo */
//	rit=-per;
//	per=-1;
//}

/* Ciclo di analisi sintattica istruzioni con generazione file */
/* intermedio CODICE.INT ( primo passo compilazione )          */

cima=NULL;
inizio=NULL;

/* Cancello creo e apro il file oggetto CODICE.AB */

strcpy(&nomesor[lnomesor],".AB");
unlink(nomesor);
fdout=creat(nomesor,S_IREAD|S_IWRITE);
close(fdout);
fdout=open(nomesor,O_RDWR|O_BINARY);

if(rit!=-1)  {

         /* Riprendo l'analisi del file sorgente a partire  */
         /* dall'ultima istruzione caricata dalla procedura */
         /* di analisi periodo                              */

         rit=scegli(0);

	      while (!(rit==-4 || rit==-3))
		   rit=scegli(1);

}

/* rit = -3 incontrata istruzione END */
/* rit = -4 fine file sorgente senza istruzione END */

if(rit==-4)   /* non c'e END alla fine del file */
	stampa_err(47,0,"0");

/* Ricavo gli indirizzi nel DBL delle variabili e costanti allocate  */

/* L'allocazione degli indirizzi nel DBL procede secondo l'ordine :  */

/* 1 - variabili di tipo LINK   */
/* 2 - variabili di tipo DEFINE */
/* 3 - costanti  di tipo DATA */

/* Variabili di tipo LINK e DEFINE */

for(s=0;s<2;s++)

	for(i=0;i<NUM_TIPVAR;i++) { 

		insDB(testa,i,s,&INDDB);

		/* Procedo per ogni tipo di variabile a verificare l'allineamento */
		/* alla word dell'indirizzo */

		if(INDDB%2==1) 
			INDDB++;		 /* allineamento alla word data base generale*/
		AllDBGrp();		 /* allineamento alla word data base locali	*/
	}

/* Controllo se superata dimensione assegnata al DBL */

if(INDDB>DIMDB || MaxGrpDB(DIMDB)) { 

	printf(DBLOvFlw);
	if(fdlst>0) scrivisufile(fdlst,DBLOvFlw,1,&righelst);
   strcpy(&nomesor[lnomesor],".AB");
   unlink(nomesor);
	exit(0);

}

/* Allocazione costanti di tipo DATA nel DBL */


for(i=0;i<NUM_TIPVAR;i++) { 

	insDB(testa,i,2,&rel);

	if(rel%2==1)       /* allineamento alla word */
		rel++;

}

/* Ricavo l'indirizzo di inizio delle costanti nel DBL */

iniziocost=DIMDB+1-rel; 

/* Ricavo il vero indirizzo delle costanti nel DBL     */

inscostanti(testa,iniziocost,3); 

rel=0;

/* Ricavo quanto DBL riservare alle costanti definite dal compilatore
   per risolvere le istruzioni CASE e poi ne calcolo l' indirizzo reale */

/* Variabile intera di tipo 4 */

insDB(testa,4,3,&rel);

inscostanti(testa,( iniziocost-rel ),4);

for(i=0;i<contsubr;i++)  /* controllo che siano definite tutte */

	if(tvarsubr[i][NUM_ARG]<16)    /* le subroutine chiamate da gosub */
		stampa_err(48,1,nomi_subr[i]);

close(fdi);

/* Ciclo di cancellazione file temporanei 0.TMP 1.TMP ... */

i=0;

while(1) {  

	sprintf(loc,"%d",i);
	strcat(loc,".TMP");
	if((rit=remove(loc))==-1)
		break;
	i++;

}

/* Controllo il numero totale di errori riscontrati nel primo passo */

 if(errori>0)  {

	close(fdout);
 /* Riscontrato almeno un errore durante il primo passo di compilazione */

	printf(attention);							

	if (errori>1)

		printf(errsF,errori);

	else

		printf(errF,errori);

	printf(noSecStep);

  }

  else {

  /* Riscontrato nessun errore durante il primo passo di compilazione */

	printf(firstStepEnd);
	printf(secondStep);

	if(fdlst>0) {

	/* Scrittura sul file di listing */

		scrivivar();  /* e le variabili e costanti in ordine di indirizzo */

	}
	if(listtable==1) {

	/* Selezionata opzione di compilazione con mappa */
	/* Cancello creo e apro il file CODICE.MAP */

      strcpy(&nomesor[lnomesor],".MAP");
		unlink(nomesor);
		fdmap=creat(nomesor,S_IREAD|S_IWRITE);
		close(fdmap);
		fdmap=open(nomesor,O_RDWR|O_BINARY);

		mapfile();             /* genero il file CODICE.MAP */

      strcpy(&nomesor[lnomesor],".PLN");		// parametri link
		unlink(nomesor);
		fdmap=creat(nomesor,S_IREAD|S_IWRITE);
		close(fdmap);
		fdmap=open(nomesor,O_RDWR|O_BINARY);
		savlink(fdmap);
		close(fdmap);
      strcpy(&nomesor[lnomesor],".OBJ");		// parametri variabili privati oggetti
		unlink(nomesor);
		fdmap=creat(nomesor,S_IREAD|S_IWRITE);
		close(fdmap);
		fdmap=open(nomesor,O_RDWR|O_BINARY);
		SavGrp(fdmap);
		close(fdmap);
	}

	if(deb==1) {

	/* Selezionata opzione di compilazione debugger */

		for(i=0;i<72;i++)
			write(fddeb,"$",1); /* inserisco il separatore tra codice e variabili */
		write(fddeb,&c[2],1);   /* il carattere 0x00 */
		write(fddeb,c,2);   /* il separatore e' $ */
		write(fddeb,&i,2);  /* inserisco un blank per il numero di variabili */
		stampa_sufile(testa); /* inserisco le variabili */
		DIST=-(numvar_deb*(EF_LUNGVAR+2+2)+2);
		i=lseek(fddeb,DIST,SEEK_CUR);
		write(fddeb,&numvar_deb,2);  /* inserisco il numero di variabili */
		close(fddeb);

	}


	close(fdint);
   strcpy(&nomesor[lnomesor],".INT");
	fdint=open(nomesor,O_RDWR|O_BINARY);

/* Scrittura file oggetto CODICE.AB  */

/* Header file CODICE.AB ( 80 word ) */

	write(fdout,&nword_o,2);     /* lunghezza file oggetto in word */
	write(fdout,&per,2);         /* periodo di campionamento       */

	for(i=0,j=0;i<14;i++)        /* 14 word spare */
		write(fdout,&j,2);

	for(i=0;i<N_ENTRY;i++)
		write(fdout,&entry[i],2);   /* inserisco le entry */

	for(i=0;i<12;i++)
		write(fdout,&indmenu[i],2); /* inserisco i menu */

   /* Inizio secondo passo di compilazione */

	riordina();                    /* secondo passo    */

	close(fdout);
	lseek(fdint,0L,SEEK_END);
	insvar_subr(fdint,&righeint);  /* inserisco le variabili locali delle subr */
	scrivisufile(fdint,c,2,&righeint);
	scrivisufile(fdint,intestaz,51,&righeint);
	scrivisufile(fdint,c,2,&righeint);
	instable(inizio,0);            /* inserisco la ST */
	close(fdint);

	if (cancella==1)
   {
      strcpy(&nomesor[lnomesor],".INT");
		unlink(nomesor);
   }
	if(list_sym==1) {   /* inserisco nel file di listing : */
	
	righelst=1;
		if(subrcorr!=-1)
			insvar_subr(fdsym,&righelst);  /* le variabili locali delle subr */
		scrivisufile(fdsym,c,2,&righelst);
		scrivisufile(fdsym,intestaz,51,&righelst);
		scrivisufile(fdsym,c,2,&righelst);
		instable(inizio,1);                    /* la ST */
		close(fdsym);
	}
   if(list_only==1 || list_sym) close(fdlst);
 }
printf(End);

if(fdlst)                        // verifico errori ultimo oggetto
{
   if(errori==erroriogg) unlink(nomeogg);
}
if(errori)        // in caso di errori cancello .AB
{
   strcpy(&nomesor[lnomesor],".AB");
   unlink(nomesor);
}
exit(0);
}


/*
        set ambiente per utente PIOMBINO
*/

void setuserp() {

extern char *tipistlk[];
extern char *tipistlkp[];
extern short tipvarlk[];
extern short tipvarlkp[];
extern short codistlk[];
extern short codistlkp[];

extern char *tipistrd[];
extern char *tipistrdp[];
extern short codistrd[];
extern short codistrdp[];
extern short tvdblrd[];
extern short tvdblrdp[];
extern short tvdbsrd[];
extern short tvdbsrdp[];

extern char *tipistwr[];
extern char *tipistwrp[];
extern short codistwr[];
extern short codistwrp[];
extern short tvdblwr[];
extern short tvdblwrp[];
extern short tvdbswr[];
extern short tvdbswrp[];
        
memcpy(tipistlk,tipistlkp,NUM_TIPLK*sizeof(char*));              // LINK
memcpy(tipvarlk,tipvarlkp,NUM_TIPLK*sizeof(short));     
memcpy(codistlk,codistlkp,NUM_TIPLK*sizeof(short));     

memcpy(tipistrd,tipistrdp,NUM_TIPRD*sizeof(char*));              // READ
memcpy(codistrd,codistrdp,NUM_TIPRD*sizeof(short));     
memcpy(tvdblrd, tvdblrdp, NUM_TIPRD*sizeof(short));     
memcpy(tvdbsrd, tvdbsrdp, NUM_TIPRD*sizeof(short));     

memcpy(tipistwr,tipistwrp,NUM_TIPWR*sizeof(char*));              // WRITE
memcpy(codistwr,codistwrp,NUM_TIPWR*sizeof(short));     
memcpy(tvdblwr, tvdblwrp, NUM_TIPWR*sizeof(short));     
memcpy(tvdbswr, tvdbswrp, NUM_TIPWR*sizeof(short));     

}

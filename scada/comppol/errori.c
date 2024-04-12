/*
   modulo errori.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)errori.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include "chascii.inc"
#include "define.inc"

#define ERR_STOP 10

#ifdef INGLESE
   char *descrerr[]={
   /* 0 */	"INSTRUCTION UNKNOWN    ",
   /* 1 */	"TOO MANY VARIABLES       ",
   /* 2 */	"UNKNOWN MEASURE TYPE    ",
   /* 3 */	"BAD MEASURE TYPE - DEFINE MISMATCH     ",
   /* 4 */	"UNDEFINED MEASURE  ",
   /* 5 */	"MEASURE REDEFINITION           ",
   /* 6 */	"SYNTAX ERROR      ",
   /* 7 */	"BAD INITIALIZATION     ",
   /* 8 */	"BAD VECTOR SIZE OR TYPE MISMATCH             ",
   /* 9 */	"CONSTANT VARIABLE OR VARIABLE ALREADY LINKED  ",
   /*10 */ "BAD ENTRY/TERM NUMBER   ",
   /*11 */ "BAD PARAMETERS NUMBER     ",
   /*12 */ "PARAMETERS TYPE MISMATCH    ",
   /*13 */ "INSTRUCTION NOT IN SUBROUTINE   ",
   /*14 */ "NOT AFTER TERM OR ENDS",
   /*15 */ "NOT AFTER RET",
   /*16 */ "CASE VARIABLE IS NEITHER INTEGER OR DEVICE",
   /*17 */ "VALUE NOT INTEGER",
   /*18 */ "VALUE NOT REAL",
   /*19 */ "VALUE NOT STRING",
   /*20 */	"TOO MANY NESTED IF AND/OR CASE              ",
   /*21 */	"THEN/BEGIN NOT FOUND AFTER IF/CASE            ",
   /*22 */	"DOESN'T AGREE WITH IF/CASE INSTRUCTION NUMBER",
   /*23 */	"BAD EXTENSION    ",
   /*24 */	"BAD ENTRY TYPE         ",
   /*25 */	"ENTRY ALREADY DEFINED",
   /*26 */	"[....] NOT FOUND",
   /*27 */	"BAD OR DUPLICATED MENU NUMBER ",
   /*28 */	"BAD SELECTION GROUPS NUMBER       ",
   /*29 */	"NOT GROUP DEFINED       ",
   /*30 */	"TOO MANY VIEWABLE GROUPS    ",
   /*31 */	"BAD PERIOD VALUE           ",
   /*32 */	"TOO MANY GOSUB OR SUBROUTINE DEFINITIONS ",
   /*33 */	"TOO MANY PARAMETERS (MAX. 20)",
   /*34 */	"PARAMETERS MISMATCH                      ",
   /*35 */	"SUBROUTINE NEVER USED (GOSUB)       ",
   /*36 */	"SUBROUTINE END NOT FOUND   ",
   /*37 */	"SUBROUTINE ALREADY DEFINED",
   /*38 */	"DBL VARIABLE REDEFINITION",
   /*39 */	"INTEGER VALUE OUT OF RANGE",
   /*40 */	"FORBIDDEN AREA",
   /*41 */ "PARAMETER ALREADY DEFINED",
   /*42 */ "PARAMETER VALUE NOT CORRECT  ",
   /*43 */ "PAGE NAME NOT FOUND       ",
   /*44 */ "UNACCEPTABLE DECIMAL DIGITS   ",
   /*45 */ "STRING LENGTH GREATER THAN DEFINED        ",
   /*46 */ "INSTRUCTION NOT BETWEEN ENTRY AND TERM  ",
   /*47 */ "END NOT FOUND             ",
   /*48 */ "SUBROUTINE NOT FOUND  ",
   /*49 */ "RECORD NAME NOT FOUND   ",
   /*50 */ "BAD EDITING FILE NAME           ",
   /*51 */ "RECORD NAME UNKNOWN    ",
   /*52 */ "BAD ZOOM COEFFICIENT  ",
   /*53 */ "TOO MANY POINTERS                 ",
   /*54 */ "UNDEFINED SYMBOL  ",
   /*55 */ "DISPLAY INDEX UNDEFINED",
   /*56 */ "PAGE AND LIST NOT FOUND      ",
   /*57 */ "TOO MANY INSTRUCTIONS (MAX. 1000)          ",
   /*58 */ "BAD VARIABLE NAME OR NAME NOT FOUND   ",
   /*59 */ "UNDEFINED VARIABLE    ",
   /*60 */ "BAD VARIABLE TYPE             ",
   /*61 */ "BAD PRINT FORMAT             ",
   /*62 */ "BAD TREND LIMITS           ",
   /*63 */ "GRAF : TOO MANY PARAMETERS (MAX. 6 )",
   /*64 */ "GRAF MUST BE PRECEEDED BY SGRAF     ",
   /*65 */ "LINE CHARACTERS OVERFLOW (MAX. 2000)              ",
   /*66 */ "TOO MANY NESTED IF AND/OR LOOP              ",
   /*67 */ "MUST BE PRECEEDED BY LOOP ",
   /*68 */ "DOESN'T AGREE WITH LOOP INSTRUCTION NUMBER ",
   /*69 */ "BAD OR NOT FOUND APS/SEQUENCE NUMERIC INDEX         ",
   /*70 */ "BAD APS/SEQUENCE NUMERIC INDEX           ",
   /*71 */ "BAD STOP/START INSTRUCTION NUMERIC INDEX        ",
   /*72 */ "BAD APS/SEQUENCE NUMERIC INDEX            ",
   /*73 */ "BAD VARIABLE NAME    ",
   /*74 */ "KEYWORD USED AS VARIABLE NAME                          ",
   /*75 */ "NOT GROUP DEFINED OR SELECTABLE GROUP",
   /*76 */ "GOSUB SYNTAX ERROR                 ",
   /*77 */ "NO PARAMETERS NEEDED FOR INSTRUCTION     ",
   /*78 */ "PATHNAME OVERFLOW (MAX. 40)                            ",
	/*80 */ "TOO MANY GROUP DEFINED "
		};
#define tooManyErr      "Too many errors, can't go on."
#define line            "line ( %04d ) "
#define module          ": Module "
#define errFoundRow     " ***** ERROR FOUND LINE"
#else
#define errFoundRow     " ***** ERRORE ALLA RIGA "
#define module          ": Modulo "
#define line            "linea ( %04d ) "
#define tooManyErr      "Troppi errori, impossibile proseguire."
   char *descrerr[]={
   /* 0 */	"ISTRUZIONE NON DEFINITA",
   /* 1 */	"DEFINITE TROPPE VARIABILI",
   /* 2 */	"TIPO MISURA NON PREVISTO",
   /* 3 */	"TIPO SIGLA INCONGRUENTE CON FASE DEFINE",
   /* 4 */	"MISURA NON DEFINITA",
   /* 5 */	"MISURA DUPLICATA IN FASE DEFINE",
   /* 6 */	"ERRORE DI SINTASSI",
   /* 7 */	"ERRATA INIZIALIZZAZIONE",
   /* 8 */	"DIMENSIONE VETTORE ERRATA O TIPO INCONGRUENTE",
   /* 9 */	"MISURA DEFINITA COME COSTANTE O GIA' LINKATA",
   /*10 */ "ERRATO NUMERO ENTRY/TERM",
   /*11 */ "NUMERO DI OPERANDI ERRATO",
   /*12 */ "TIPO OPERANDI INCOMPATIBILI",
   /*13 */ "ISTRUZIONE NON IN UNA SUBROUTINE",
   /*14 */ "NON PRECEDUTA DA TERM O ENDS",
   /*15 */ "NON PRECEDUTA DA RET",
   /*16 */ "VARIABILE CASE NON INTERA O ORGANO",
   /*17 */ "VALORE NON INTERO",
   /*18 */ "VALORE NON REALE",
   /*19 */ "VALORE NON STRINGA",
   /*20 */	"SUPERATO LIVELLO MAX ANNIDAMENTI IF E/O CASE",
   /*21 */	"ISTRUZIONE THEN/BEGIN NON TROVATA DOPO IF/CASE",
   /*22 */	"IN NUMERO NON CORRISPONDENTE ALLE ISTRUZIONI IF/CASE",
   /*23 */	"ESTENSIONE ERRATA",
   /*24 */	"TIPO ENTRY NON PREVISTO",
   /*25 */	"ENTRY GIA' DEFINITA",
   /*26 */	"MANCANO [....]",
   /*27 */	"NUMERO MENU' NON CORRETTO O DUPLICATO",
   /*28 */	"ERRATO NUMERO GRUPPI SELEZIONABILI",
   /*29 */	"NON DEFINITO COME GRUPPO",
   /*30 */	"TROPPI GRUPPI VISUALIZZABILI",
   /*31 */	"VALORE PERIODO NON CORRETTO",
   /*32 */	"TROPPE GOSUB O DEFINIZIONI DI SUBROUTINE",
   /*33 */	"TROPPI ARGOMENTI (MAX 20)",
   /*34 */	"ARGOMENTI IN CONTRASTO CON ALTRE CHIAMATE",
   /*35 */	"SUBROUTINE SENZA GOSUB PRECEDENTE",
   /*36 */	"FINE SUBROUTINE NON TROVATA",
   /*37 */	"SUBROUTINE GIA' DEFINITA",
   /*38 */	"VARIABILE GIA' DEFINITA NEL DBL",
   /*39 */	"VALORE INTERO MA FUORI RANGE",
   /*40 */	"ZONA NON AMMISSIBILE",
   /*41 */ "PARAMETRO GIA' DEFINITO",
   /*42 */ "VALORE ARGOMENTO NON CORRETTO",
   /*43 */ "MANCA IL NOME DELLA PAGINA",
   /*44 */ "CIFRE DECIMALI NON ACCETTABILI",
   /*45 */ "LUNGHEZZA STRINGA MAGGIORE DIMENSIONE VAR.",
   /*46 */ "ISTRUZIONE NON COMPRESA TRA ENTRY E TERM",
   /*47 */ "ISTRUZIONE END NON TROVATA",
   /*48 */ "SUBROUTINE NON TROVATA",
   /*49 */ "MANCA IL NOME DEL RECORD",
   /*50 */ "NOME FILE DI EDITING INESISTENTE",
   /*51 */ "NOME RECORD SCONOSCIUTO",
   /*52 */ "FATTORE DI ZOOM ERRATO",
   /*53 */ "PUNTATORI IN NUMERO TROPPO ELEVATO",
   /*54 */ "SIMBOLO INDEFINITO",
   /*55 */ "INDICE VIDEO NON DEFINITO",
   /*56 */ "MANCANO SIA PAGINA CHE ELENCO",
   /*57 */ "SUPERATO NUMERO MASSIMO ISTRUZIONI ( 1000 )",
   /*58 */ "NOME VARIABILE NON CORRETTO O MANCANTE",
   /*59 */ "VARIABILE NON DEFINITA",
   /*60 */ "TIPO VARIABILE NON AMMISSIBILE",
   /*61 */ "FORMATO DI STAMPA SCORRETTO  ",
   /*62 */ "LIMITI DI TREND SCORRETTI  ",
   /*63 */ "GRAF : TROPPI ARGOMENTI (MAX 6)  ",
   /*64 */ "GRAF DEVE ESSERE PRECEDUTA DA SGRAF ",
   /*65 */ "SUPERATO NUMERO MASSIMO CARATTERI PER RIGA ( 200 )",
   /*66 */ "SUPERATO LIVELLO MAX ANNIDAMENTI IF E/O LOOP",
   /*67 */ "NON PRECEDUTO DA ISTRUZIONE LOOP",
   /*68 */ "IN NUMERO NON CORRISPONDENTE ALLE ISTRUZIONI LOOP ",
   /*69 */ "INDICE NUMERICO APS/SEQUENZA NON CORRETTO O MANCANTE",
   /*70 */ "INDICE NUMERICO APS/SEQUENZA NON CORRETTO",
   /*71 */ "INDICE NUMERICO IN ECCESSO ISTRUZIONE STOP/START",
   /*72 */ "VALORE NUMERICO INDICE APS/SEQUENZA NON ACCETTABILE",
   /*73 */ "NOME VARIABILE NON ACCETTABILE",
   /*74 */ "UTILIZZATA UNA PAROLA CHIAVE COME NOME DI UNA VARIABILE",
   /*75 */ "NON DEFINITO COME GRUPPO OPPURE GRUPPO SELEZIONABILE",
   /*76 */ "ERRORE DI SINTASSI ISTRUZIONE GOSUB",
   /*77 */ "ISTRUZIONE CHE NON AMMETTE ARGOMENTI",
   /*78 */ "PATHNAME COMPLETO FILE DI EDITING TROPPO LUNGO (MAX 40)"
	/*80 */ "DEFINITI TROPPI GRUPPI CON DATA BASE LOCALE "
		};
#endif

extern int fdi;
extern int fdint;
extern int fdlst;
extern int fddeb;
extern int fdmap;
extern int numriga;
extern int nrigaco;
extern int righelst;
extern int rigaerr;
extern int errori;
extern int cfiltmp;   /* Contatore file estensione TMP */

extern char dzmod[];  /* Dizionario nomi moduli */


stampa_err(n,m,c)
int n;     /* Indice relativo alla stringa di diagnostica */
int m;	  /* Se m = 1 viene visualizzata la stringa c */
char c[];

{
int d,j=0,k;
char sterrori[200];
int nrrel,ctch;

if (++errori==1)
	erase_screen();

   /*
if(errori==ERR_STOP+1) {
	curxy(23,2);
	printf(tooManyErr);
	curxy(24,2);

	close(fdi);

	delfcomp(cfiltmp);

	exit(0);

}
   */

curxy(rigaerr,2);

ctch = detnriga(numriga,&nrrel);

printf(line,nrrel);

printf(module);

if ( ctch ==  0 ) {

  for ( k=0; k<40; k++) {

  printf("%c",dzmod[k]);

  }

}

else {

  for ( k=0; k<10; k++ ) {

  printf("%c",dzmod[(NBYMOD * ctch + 40 + k)]);

  }

}

if(m==1) {

	printf("\n\r   %s  --->  ",c);
   printf("%s",descrerr[n]);

   }

else {

   printf("\n\r %s",descrerr[n]);

}

/* Gestione file di listing */

if(fdlst>0) {
	j+=sprintf(sterrori,"%s ",errFoundRow);
	sterrori[j]=BLANK;
	j+=sprintf(&sterrori[++j],"%04d",numriga);
	sterrori[j]=BLANK;
	j+=sprintf(&sterrori[++j],"%s"," : ");

	if(m==1) {
      strcat(sterrori,c);
      strcat(sterrori," ");
	}

   strcat(sterrori,descrerr[n]);
	scrivisufile(fdlst,sterrori,j+1,&righelst);
}

rigaerr+=2;

}





stp0_err(n,m,c,nmodulo)
int n;     /* Indice relativo alla stringa di diagnostica */
int m;	  /* Se m = 1 viene visualizzata la stringa c */
char c[];
char *nmodulo; /* puntatore al nome del modulo corrente */

{
int d,j=0,k;
char sterrori[120];
char appnmod[11];

memset (appnmod,0x00,11);

memcpy (appnmod,nmodulo,10);

/* Verifico se devo eseguire una pulizia dello schermo */

if (++errori==1)
	erase_screen();

curxy(rigaerr,2);

printf(line,nrigaco);

printf(module);

  printf("%s",appnmod);

if(m==1)
	printf("\n\r   %s  --->  ",c);

printf("%s",descrerr[n]);

/* Gestione file di listing */

if(fdlst>0) {
	j+=sprintf(sterrori,"%s ",errFoundRow);
	sterrori[j]=BLANK;
	j+=sprintf(&sterrori[++j],"%04d",numriga);
	sterrori[j]=BLANK;
	j+=sprintf(&sterrori[++j],"%s"," : ");

	if(m==1) {
		strcat(sterrori,c);
		strcat(sterrori," ");
	}

	strcat(sterrori,descrerr[n]);
	scrivisufile(fdlst,sterrori,j+1,&righelst);
}

rigaerr+=2;

}


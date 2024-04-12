/*
   modulo scriviva.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)scriviva.c	1.1
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
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

#include "chascii.inc"

#include "tipi.h"

#include "define.inc"


/***********************************************************************
*								                                               *
*			Procedura scrivivar			                                   *
*					                                                        *
* La procedura viene chiamata solo quando vi e' l' opzione "/ls"       *
* e serve per inserire nel file di listing rispettivamente le varia=   *
* bili di link, quelle di define e le costanti in ordine di indirizzo  *
* con cui sono state inserite nel DBL.				                       *
* Precisamente questa procedura serve solo per inserire i titoli sul   *
* file, e chiamare nell' ordine giusto la scrvar_cost per ottenere     *
* che siano ordinate.						                                *
*								                                               *
***********************************************************************/

#ifdef INGLESE
#define varLink      "LINK VARIABLES   "
#define dbsVAR       "DBS VAR   "
#define dblVAR       "DBL VAR   "
#define varTip       "VARIABLE TYPE "
#define dblAddr      "DBL ADDRESS     "
#define defVar       "DEFINE VARIABLES   "
#define COSTANTI     "     CONSTANTS     "
#define dblCOST      "DBL CONST  "
#define costTip      "CONSTANT TYPE"
#define costVal      "CONSTANT VALUE       "
#else
#define costVal      "VALORE DELLA COSTANTE"
#define costTip      "TIPO COSTANTE"
#define dblCOST      "COST IN DBL"
#define COSTANTI     "     COSTANTI      "
#define defVar       "VARIABILI DI DEFINE"
#define dblAddr      "INDIRIZZO IN DBL"
#define varTip       "TIPO VARIABILE"
#define dblVAR       "VAR IN DBL"
#define dbsVAR       "VAR IN DBS"
#define varLink      "VARIABILI DI LINK"
#endif

extern char c[];

/* contatore linea scritte nella pagina corrente file di listing */
extern int righelst;

extern int fdlst;        /* descrittore file di listing */

scrivivar()

{

char titoli[DIM_RIGA];
int i,j;
sbianca(titoli,79);
sprintf(&titoli[20],"%s",varLink);
scrivisufile(fdlst,c,2,&righelst);
scrivisufile(fdlst,c,2,&righelst);
scrivisufile(fdlst,titoli,80,&righelst);
scrivisufile(fdlst,c,2,&righelst);
sbianca(titoli,79);
j=1;
j+=sprintf(&titoli[j],"%s",dbsVAR);
titoli[j]=BLANK;
j=15;
j+=sprintf(&titoli[j],"%s",dblVAR);
titoli[j]=BLANK;
j=30;
j+=sprintf(&titoli[j],"%s",varTip);
titoli[j]=BLANK;
j=47;
j+=sprintf(&titoli[j],"%s",dblAddr);
	scrivisufile(fdlst,titoli,j+1,&righelst);
for(i=0;i<NUM_TIPVAR;i++)
	scrvar_cost(testa,i,0);
scrivisufile(fdlst,c,2,&righelst);
sbianca(titoli,79);
sprintf(&titoli[20],"%s",defVar);
scrivisufile(fdlst,titoli,60,&righelst);
scrivisufile(fdlst,c,2,&righelst);
sbianca(titoli,79);
j=1;
j+=sprintf(&titoli[j],"%s","          ");
titoli[j]=BLANK;
j=15;
j+=sprintf(&titoli[j],"%s",dblVAR);
titoli[j]=BLANK;
j=30;
j+=sprintf(&titoli[j],"%s",varTip);
titoli[j]=BLANK;
j=47;
j+=sprintf(&titoli[j],"%s",dblAddr);
	scrivisufile(fdlst,titoli,j+1,&righelst);
for(i=0;i<NUM_TIPVAR;i++)
	scrvar_cost(testa,i,1);
scrivisufile(fdlst,c,2,&righelst);
sbianca(titoli,79);
sprintf(&titoli[25],"%s",COSTANTI);
scrivisufile(fdlst,titoli,80,&righelst);
sbianca(titoli,79);
j=1;
j+=sprintf(&titoli[j],"%s",dblCOST);
titoli[j]=BLANK;
j=15;
j+=sprintf(&titoli[j],"%s",costTip);
titoli[j]=BLANK;
j=33;
j+=sprintf(&titoli[j],"%s",dblAddr);
titoli[j]=BLANK;
j=53;
j+=sprintf(&titoli[j],"%s",costVal);
scrivisufile(fdlst,titoli,j+1,&righelst);
scrvar_cost(testa,4,3);
for(i=0;i<NUM_TIPVAR;i++)
	scrvar_cost(testa,i,2);
scrivisufile(fdlst,c,2,&righelst);

}



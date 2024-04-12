/*
   modulo mapfile.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)mapfile.c	1.1
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

/*********************************************************************
*          							                                       *
*			Procedura mapfile                                           *
*          							                                       *
* La procedura serve per inserire nel file .map le variabili e       *
* le costanti utilizzate dal programma secondo l' ordine :           *
*	1) variabili di link                                              *
*	2) variabili di define (tranne i gruppi)                          *
*	3) costanti (per primi i gruppi)                                  *
* Le prime tre word del file inoltre contengono rispettivamente      *
* il numero di variabili di link, di variabili di define e di        *
* costanti piu' gruppi.                                              *
*          	                                                         *
*********************************************************************/

#ifdef INGLESE
#define STRcpointers "\n\r constant pointers overflow (max. 255) \n"
#else
#define STRcpointers "\n\r superate 255 costanti di tipo puntatore \n"
#endif

extern int stop_link;

extern int fdmap;        /* descrittore file di mappa */

mapfile()

{

int i=0,contalink=0,contadata=0,contavar=0,contagr=0;
int save,contapointer=0;

write(fdmap,&i,2);  /* riservo le prime quattro word del file */
write(fdmap,&i,2);  /* scrivendoci 0 */
write(fdmap,&i,2);
write(fdmap,&i,2);
write(fdmap,&i,2);

stop_link=0;

/* Ciclo di inserimento variabili di LINK */

for(i=0;i<NUM_TIPVAR;i++)             /* inserisco le variabili di DBS */
	insmap(testa,i,&contalink,0);

stop_link=1;

for(i=0;i<NUM_TIPVAR;i++)             /* inserisco le corrispondenti var. */
	insmap(testa,i,&contavar,0);		  /* di DBL                           */

for(i=0;i<NUM_TIPVAR;i++)             /* inserisco le DEFINE   */
	insmap(testa,i,&contavar,1);

/* Indice di tipo variabile i = 4 --> tipo intero */

i=4;
insmap(testa,i,&contagr,6);           /* inserisco i gruppi    */

contadata=contagr;                    /* considero anche i gruppi tra i data */

for(i=0;i<NUM_TIPVAR;i++)   {        /* inserisco le costanti */
	save=contadata;
	insmap(testa,i,&contadata,2);

	if(i>=9)
		contapointer+=(contadata-save);
	if(i==4)
		insmap(testa,4,&contadata,3); /* inserisco le costanti CASE_n */
}
lseek(fdmap, 0L, SEEK_SET);
write(fdmap,&contalink,2);            /* inserisco il numero di LINK, */
write(fdmap,&contavar,2);             /* di DEFINE (senza gruppi),    */
write(fdmap,&contagr,2); 	           /* gruppi                       */
write(fdmap,&contapointer,2);         /* puntatori                    */
write(fdmap,&contadata,2);            /* di costanti (+ gruppi)       */
close(fdmap);

/* contpointer su un byte deve essere <= di 255 */

if(contapointer>255) {

/* contpointer non puo' essere espresso su un byte */

printf(STRcpointers);


	}

}



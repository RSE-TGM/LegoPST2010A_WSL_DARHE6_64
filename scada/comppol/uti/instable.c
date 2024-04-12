/*
   modulo instable.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)instable.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <malloc.h>

#include "defpath.inc"

#include "chascii.inc"
#include "tipi.h"


#define LUNGSTR	    100
#define POS2          25
#define POS3          (POS2+10)
#define SPOS1	       POS3
#define SPOS2 	       (POS3+11)
#define SPOS3	       (SPOS2+10)
#define SPOS4	       (SPOS3+10)
#define DIMDB	     2047


extern short righeint;
extern short righelst;
extern short fdint;
extern short fdsym;

extern short contrari[];

extern char *private[];

#ifdef INGLESE
char *t_var[NUM_TIPVAR]={ "ANALOG","DIGITAL","DEVICE","REAL",
		"INTEGER","LOGIC","DIG.OUT.","STRING","GROUP",
		"ANA.PTR","DIG.PTR","DEV.PTR","COM.PTR","BLK.PTR",
		"INT.PTR","STR.PTR" };
#else
char *t_var[NUM_TIPVAR]={ "ANALOGICA","DIGITALE","ORGANO","REALE",
		"INTERA","LOGICA","DIG.OUT.","STRINGA","GRUPPO",
		"PUNT_AN","PUNT_DI","PUNT_OR","PUNT_CO","PUNT_BL",
		"PUNT_IN","PUNT_ST" };
#endif

/*********************************************************************
*          							                                       *
*			Procedura instable			                                 *
*          							                                       *
*	La procedura viene chiamata per inserire nel file di listing      *
* ( sem=1 ) o in quello intermedio (sem=0) la S.T. Per le istruzione *
* viene scritto solo il nome ed il codice prodotto, come per le      *
* label che pero' vengono scritte solo sul file intermedio, mentre   *
* per le variabili e le costanti vengono scritti il codice prodotto  *
* (= l' indirizzo in DBL) il tipo e l' eventuale dimensione.         *
* Da notare che oltre alle label ci sono delle differenze tra i due  *
* file: caso tipico sono gli IF che nel file di listing vengono      *
* capovolti ( viene scritto cioe' l' IF negato, dato che la S.T.     *
* contiene gli gia' negati si ottiene l' IF scritto nel sorgente),   *
* mentre nel file intermedio viene scritto cosi' come e', scrivendo  *
* cosi' il contrario rispetto al sorgente.			                  *
*          							                                       *
*********************************************************************/

instable(albero2,sem)
struct symb_list *albero2;
short sem;
{
static char strsymb_table[LUNGSTR];
short i,provv,fdlocale,trovato;
if(albero2!=NULL) {
	instable(albero2->sinistra,sem);
	if(sem==0) {
 		provv=righeint;
		fdlocale=fdint;
	 }
	else  {
 		provv=righelst;
		fdlocale=fdsym;
	 }
	trovato=0;
	for(i=0;i<7;i++)
		if((strcmp(private[i],albero2->stringa))==0) {
			trovato=1;
			break;
		}
	if(sem==0 || (albero2->tipocodice!=0 &&
	   albero2->tipocodice!=3 && trovato==0 &&
	  !(albero2->tipocodice==2 && albero2->codice_ogg==0))) {
		for(i=0;i<LUNGSTR-1;i++)
			strsymb_table[i]=BLANK;
		strsymb_table[i]=0x00;
			if(sem==1 && albero2->tipocodice==2 &&
			  (strcmp("CASE",albero2->stringa)!=0) &&
 	 ((albero2->codice_ogg <16 && albero2->codice_ogg>1 ) ||
		 (albero2->codice_ogg ==118 || albero2->codice_ogg==119)))	{
		 	if(albero2->codice_ogg ==118 )
				sprintf(strsymb_table,"%s",par_chiav[119]);
			else
				if(albero2->codice_ogg ==119 )
					sprintf(strsymb_table,"%s",par_chiav[118]);
				else
					sprintf(strsymb_table,"%s",par_chiav[contrari[albero2->codice_ogg-2]]);
			}
			else
				sprintf(strsymb_table,"%s",albero2->stringa);
			sprintf(&strsymb_table[POS2+4],"%5x",albero2->codice_ogg);
			if(albero2->tipocodice!=1) {
			for(i=0;i<POS2+4;i++)
				if(strsymb_table[i]==0x00)
					strsymb_table[i]=BLANK;
			scrivisufile(fdlocale,strsymb_table,POS3+4,&provv);
			if(fdlocale==fdint)
				righeint=provv;
			else
				righelst=provv;
			}
		else {
			sprintf(&strsymb_table[SPOS1+4],"%s",t_var[albero2->tipovar]);
			sprintf(&strsymb_table[SPOS2+4],"%4d",albero2->dimvar);
			sprintf(&strsymb_table[SPOS3+4],"%4d",albero2->riga_def );
 			for(i=0;i<SPOS3+4;i++)
				if(strsymb_table[i]==0x00)
					strsymb_table[i]=BLANK;
			scrivisufile(fdlocale,strsymb_table,SPOS4,&provv);
			if(fdlocale==fdint)
				righeint=provv;
			else
				righelst=provv;
		}
	}
	instable(albero2->destra,sem);
   free(albero2);
}
}


/*
   modulo ins_symb.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)ins_symb.c	1.1
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

#include "tipi.h"

#ifdef INGLESE
#define STRmemins " OUT OF MEMORY IN < ins_symb >"
#define STRpreuntst " PRESS ANY KEY TO CONTINUE     "
#else
#define STRmemins " MEMORIA INSUFFICIENTE PER ALLOCAZIONE IN < ins_symb >"
#define STRpreuntst " PREMI UN TASTO PER CONTINUARE "
#endif

/*********************************************************************
*          							                                       *
*			Procedura ins_symb			                                 *
*          							                                       *
* 	La procedura inserisce nell' albero della S.T. la variabile,      *
*  la costante, l' istruzione o la label passata e riempie i campi   *
*  con i parametri passati relativi. L' ordine con cui vengono 		*
*  inserite le parole e' :                                           *
*  parole_chiavi                                                     *
*	label                                                             *
*	variabili e costanti                                              *
* I parametri passati non interessanti per il tipo in questione      *
* vengono messi a -1 dal chiamante.                                  *
*          							                                       *
*********************************************************************/


struct symb_list *ins_symb(albero2,ncodice,valcodice,tipo,dim,origine,dato)
struct symb_list *albero2;
char ncodice[];				// nome parola chiave per istruz.,nome var. o
								   // nome costante .
short valcodice;					// contiene a seconda del tipo di simbolo memorizzato:
									// . codice relativo (per parola chiave istruzione)
									//	. indirizzo in DBL (per le variabili)
									// . valore del program counter cui si riferisce
									//   (per le label).
short tipo;						// per var. o costante (-1 se non Š una variabile).
short dim;							// dimensione della variabile (solo per variabili) 
short origine;					//	riga di definizione nel file sorgente (solo var.)
short dato;						// specifica il tipo di simbolo:
									//       0   .label
									//       1   .variabile
									//       2   .istruzione
									//       3   .variabile locale di subroutine 
{
if(albero2==NULL) {
	albero2=(struct symb_list *) malloc(sizeof(struct symb_list));

	if ( albero2 == NULL ) {

	/* Memoria insufficiente per l'allocazione */
	printf(STRmemins);
	bell();
	/* premi un tasto per continuare */
	printf(STRpreuntst);
	getc(stdin);

	exit(0);

	}

	strcpy(albero2->stringa,ncodice);
	albero2->codice_ogg=valcodice;
	albero2->tipovar=tipo;
	albero2->dimvar=dim;
	albero2->riga_def=origine;
	albero2->tipocodice=dato;
	albero2->destra=NULL;
	albero2->sinistra=NULL;
}
else
	if((strcmp(ncodice,albero2->stringa))>0)
albero2->destra=ins_symb(albero2->destra,ncodice,valcodice,tipo,dim,origine,dato);
	else
		if((strcmp(ncodice,albero2->stringa))<0)
albero2->sinistra=ins_symb(albero2->sinistra,ncodice,valcodice,tipo,dim,origine,dato);
return(albero2);
}


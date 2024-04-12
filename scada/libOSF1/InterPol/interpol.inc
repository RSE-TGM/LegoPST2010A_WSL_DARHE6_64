/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/* 
        Contiene la dichiarazione delle strutture utilizzate 
	all'interno del'interprete.
*/

#include "all_1.h"

typedef struct s_interp { char *dbc ;  	/* data base locale a by 	*/
                          short *dbs ;  /* data base locale a hw 	*/
                          short *pc ;   /* indirz. codice da eseguire	*/
                          long  *stk ; 	/* indiriz. stack        	*/
                          long  *siniz;	/* ind. inizio stack     	*/
                          long  *sfine;	/* ind. fine stack       	*/
                          short *inc ;  /* inizio codice         	*/
                          char *d ;     /* struttura dati               */
                        } S_INTERP ;

#define n_tstack 300    /* word per stack               */
#define n_tdbl   2048   /* bytes data base locale       */

#define b_organo 	2
#define b_reale  	3
#define b_stringa 	4
#define b_analogico 	0
#define b_intero 	1

float coeff_add;   // coefficiente additivo utilizzato dalla GRAF
float coeff_mol;   // coefficiente moltiplicativo utilizzato dalla GRAF

#include "all_16.h"


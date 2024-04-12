/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#include "all_1.h"
int numriga=0;     /* numero assoluto di riga nel file sorgente   */
int nrigaco=0;     /* numero relativo di riga nel modulo corrente */
int cfiltmp=1;     /* contatore file temporanei creati dal compilatore */

int stkinc[NWSTKINC];  /* Pseudo stack di gestione annidamento INCLUDE */

int *stk=stkinc;  /* Puntatore allo pseudo stack */

char dzmod[(DDZMOD * NBYMOD)];  /* Dizionario nomi moduli di INCLUDE */

int odzmod=0;  /* Indice di occupazione dizionario moduli */

/* Definizione della struttura dei dati memorizzati nello stack */

struct TBIND {

	int ptdzmod;  /* indice relativo al primo byte del nome modulo */
	int indass;   /* indice assoluto di riga nel file sorgente */
	int indrel;   /* indice relativo di riga nel file corrente */
	};

struct TBIND tabind[NRTABIND];  /* Tabella indici assoluti e relativi */

int itabind=0;  /* indice progressivo che punta all'elemento di tabind */



#include "all_16.h"

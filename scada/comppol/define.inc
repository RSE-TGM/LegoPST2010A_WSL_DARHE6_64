/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/* File di include contenente le istruzioni di define */


#define	DIM_MENU            20
#define DIMDB             2047
#define DIM_RIGA           120
#define DMX_RIGA           2000
#define DMX_RILST          350
#define NUM_ARG	            20
#define NUM_SUBR	    20
#define LUNG_VAR_LINK_DBS   10


/* Numero massimo livelli gerarchici di annidamento istruzioni INCLUDE */

#define MXANNINC            20

/* Numero di word che compongono il pseudo stack di gestione INCLUDE */

#define NWSTKINC        3 * MXANNINC

/* Dimensionamento tabella indici assoluti e relativi di riga */

#define NRTABIND           200

/* Numero totale di byte che costituiscono un nome modulo completo */
/* - 40 byte : nome completo di path del file di editing */
/* - 10 byte : nome del record su file di editing esclusa l'estensione */

#define NBYMOD              50

/* Dimensionamento dizionario nomi moduli che coincide con il numero */
/* massimo di file di include distinti */

#define DDZMOD              50



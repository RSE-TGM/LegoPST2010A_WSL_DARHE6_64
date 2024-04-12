/**********************************************************************
*
*       C Header:               lg1.h
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Jul 20 11:59:56 2001 %
*
**********************************************************************/

#ifndef LG1_H
#define LG1_H



#define MAX_BLOCCHI 1000
#define MAX_MODULI  300


/* Tipi di variabile. Le variabili di tipo USCITA e STATO vengono
 * considerate variabili di uscita.
 */
typedef enum _tag_tipo_var { INGRESSO, USCITA, STATO } TIPO_VAR;



/* tipi di blocco. */
typedef enum _tag_tipo_bl { REGOLAZIONE, PROCESSO } TIPO_MOD;



/* Descrittore di una variabile. */
typedef struct _tag_var {
             char      nome[9];
             char      descr[64];
             int       connessioni; /* numero di connessioni della variabile */
             TIPO_VAR  tipo;
} VAR;



/* Descrittore di una connessione.
 * Il campo 'var_interna' contiene l'indice, nel vettore 'variabili', della
 * variabile connessa.
 * Il campo 'blocco_esterno' e' l'indice, nel vettore dei blocchi, del blocco
 * a cui appartiene l'altra variabile della connessione.
 * Il campo 'var_esterna' e' l'indice, nel vettore 'variabili' del blocco 
 * esterno, dell'altra variabile della connessione.
 * Il campo succ punta alla connessione successiva nella lista delle
 * connessioni.
 */
typedef struct _tag_conn {
             int var_interna;
             int var_esterna;
             int blocco_esterno;
#ifndef DESIGN_TIME
             struct _tag_conn *succ;
#else
             int              *succ;
#endif
} CONN; 



/* Descrittore di un blocco.
 * Il campo 'variabili' e' un array di descrittori di tipo VAR che viene 
 * allocato dinamicamente e dimensionato a 'num_variabili'.
 * Il campo 'variabili_connesse' e' una lista di descrittori
 * di tipo CONN allocata dinamicamente.
 */
typedef struct _tag_bl {
             TIPO_MOD tipo;
             char     str_tipo[7];
             char     label[9];
             char     sigla_modulo[5];
             char     sigla_blocco[5];
             char     descr_blocco[55];
             int      modulo;
             int      num_variabili;
             VAR      *variabili;
             CONN     *variabili_connesse;
} BLOCCO;


/* Descrittore di un modulo. */
/* 2-7-93 introdotta descrizione C.M. */
typedef struct _tag_modulo {
        TIPO_MOD tipo;
        char     sigla[5];
        char     descr[80];
} MODULO;


/* Descrittore di un modello. */
typedef struct _tag_modello {
         char nome[80];
         char path_legocad[1024];
} MODELLO;


/* Dichiarazione delle variabili */

extern MODELLO modello;

extern MODULO  moduli[MAX_MODULI];
extern int     num_tot_moduli;

extern BLOCCO  blocchi[MAX_BLOCCHI];
extern int     num_blocchi;

extern char modulename[];
extern char blockname[];
extern char blockdescr[];


#endif


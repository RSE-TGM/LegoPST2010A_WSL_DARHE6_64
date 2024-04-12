/**********************************************************************
*
*       C Header:               lg1_topsim.h
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Jul 20 12:02:05 2001 %
*
**********************************************************************/
/*
   modulo lg1_topsim.h
   tipo 
   release 1.25
   data 2/15/96
   reserved @(#)lg1_topsim.h	1.25
*/
#ifndef LG1_TOPSIM_H
#define LG1_TOPSIM_H


#define MAX_MODELLI 300
#define MAX_BLOCCHI 1000


/* Tipi di variabile. Le variabili di tipo USCITA e STATO vengono
 * considerate variabili di uscita.
 */
typedef enum _tag_tipo_var { INGRESSO, USCITA, STATO } TIPO_VAR;



/* tipi di blocco. */
typedef enum _tag_tipo_bl { REGOLAZIONE, PROCESSO, NOLEGO } TIPO_MOD;


/* lista degli ingressi */
typedef struct _tag_lista_ing {
                    char                  nome[9];
                    char                  descr[64];
                    int                   visitato;
                    struct _tag_lista_ing *succ;
} LISTA_ING;
                                      



/* Descrittore di una variabile. */
typedef struct _tag_var {
             char      nome[9];
             char      descr[64];
             int       connessioni; /* numero di connessioni della variabile interne alla task */
             int       model_conn;  /* numero di connessioni della variabile tra task diverse  */
             TIPO_VAR  tipo;
} VAR;



/* Descrittore di una connessione tra variabili reletive alla stessa task.
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

/* Descrittore delle connessioni tra variabili di task diverse  
 * int modello_interno; indice nel vettore dei modelli della variabile interna
 * int modello_esterni; indice nel vettore dei modelli della variabile da connettere
 * int blocco_interno;  indice nel vettore dei blocchi del modello interno
 * int blocco_esterno;  indice nel vettore dei blocchi del modello esterno
 * int var_interna;     indice nel vettore delle variabili del blocco interno
 * int var esterna;     indice nel vettore delle variabili del blocco esterno
*/

typedef struct _tag_conn_model {
             int modello_interno;
             int modello_esterno;
             int blocco_interno;
             int blocco_esterno;
             int var_interna;
             int var_esterna;
#ifndef DESIGN_TIME
             struct _tag_conn_model *succ;
#else
             int              *succ;
#endif
} CONNMODEL; 


/* Descrittore di un blocco.
 * Il campo 'variabili' e' un array di descrittori di tipo VAR che viene 
 * allocato dinamicamente e dimensionato a 'num_variabili'.
 * Il campo 'variabili_connesse' e' una lista di descrittori
 * di tipo CONN allocata dinamicamente.
 * Il campo 'var_conn_task' e' una lista di descrittori
 * di tipo CONNTASK allocata dinamicamente
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
             CONNMODEL *var_conn_task;
} BLOCCO;


/* Descrittore di una task (modello) per topsim  */
typedef struct _tag_modello {
         char nome[80];
         char descr[80];
         char local_path[100];
         TIPO_MOD tipo_task;
         char OS[20];
         char host[20];
         char guest[20];
         char remote_path[100];
         float activation_interval;
         int num_blocchi;
         BLOCCO blocchi[MAX_BLOCCHI];   /* lista dei blocchi della singola task (modello) */
} MODELLO;


typedef struct _tag_simulatore {
        char path[256];
	char nome[80];
        char descr[80];
        int nmodelli;
        MODELLO *modelli[MAX_MODELLI];   /* lista delle task del simulatore */
        char bm[5];
        char scada[10];
        char bi[10];
} SIMULATORE;

#endif   /* LG1_TOPSIM_H */


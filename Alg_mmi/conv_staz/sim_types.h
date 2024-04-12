/**********************************************************************
*
*	C Header:		sim_types.h
*	Instance:		5
*	Description:	
*	%created_by:	lomgr %
*	%date_created:	Mon Nov 23 17:13:56 1998 %
*
**********************************************************************/
#if defined MFFR
#include "buffer_mffr.h"
#include "snap_sked.h"
#endif
/* **************************************************************** */

# define  STATO          0    /* per variabili di stato                 */
# define  INGRESSO_NC    1    /* per variabili di ingresso non connesse */
# define  INGRESSO_C     2    /* per variabili di ingresso connesse     */
# define  NO_GRAF_SEL    3    /* per variabili da registare             */
# define  GRAF_SEL       4    /* per variabili da registare             */
# define  NO_GRAF_SEL_MOM 5   /* per variabili da registare             */
# define  GRAF_SEL_MOM   6    /* per variabili da registare             */
# define  VERO           1
# define  FALSO          0
# define  ANALOGICO      0    /* da utilizzare nel campo tipo_var */
# define  DIGITALE       1    /* dell struttura VARIABILI         */
#if defined REPLAY
# define  PERT_RUN_TIME  1    /* perturbazione run-time inviata ... */
# define  PERT_REPLAY    2    /* perturbazione inviata durante il replay */
#endif

/*
        Questo file contiene tutte le definizioni e
        i tipi riguardanti le perturbazioni
*/
#define PERT_SCALINO         1
#define PERT_RAMPA           2
#define PERT_RAMPA_STOP      3
#define PERT_IMPULSO         4
#define PERT_IMPULSO_STOP    5
#define PERT_UP              6
#define PERT_DOWN            7
#define PERT_NOT             8
#define PERT_TO              9
#define PERT_TO_STOP        10
#define PERT_PERIODIC         11
#define PERT_PERIODIC_STOP    12
#define PERT_WHITENOISE       13
#define PERT_WHITENOISE_STOP  14

/* ***************************************************************** */


/* La struttura MODEL contiene le informazioni utilizzate run-time dallo
   schedulatore per ciascun modello

        char name[MAX_LUN_NOME_MODELLO];
                nome del modello

        int  lun_name;
                lunghezza del nome del modello

        char descr[65];
                breve descrizione del modello

        char sistema_operativo[MAX_LUN_SISTEMA];
                sistema operativo della macchina dove viene implementato
                il modello

        char host[MAX_LUN_HOST];
                nome della macchina dove viene implementato il modello

        char utente[MAX_LUN_UTENTE];
                utente della dove viene implementato il modello

        char path[80];
                path dell'eseguibile del modello (privato di /proc)

        int  lun_path;
                lunghezza del path

        float dt;
                passo di integrazione del modello

        int punt_ivus;
                puntatore relativo in shared memory all'inizio delle
                variabili di uscita del modello

        int punt_ivin;
                puntatore relativo in shared memory all'inizio delle
                variabili di ingresso del modello

        int punt_ider;
                puntatore relativo in shared memory all'inizio delle
                derivate del modello

        int punt_idati;
                puntatore relativo in shared memory all'inizio dei
                dati del modello

        int num_ic;
                numero degli ingressi connessi del modello

        int punt_ing[MAX_COLL];
                puntatore assoluto ad una variabile del modello che
                risulta connessa alla variabile di uscita di un altro modello
                ex:
                        (*var)punt_ing[i]=(*var)punt_usc[i]
        int punt_usc[MAX_COLL];
                puntatore assoluto ad una variabile di un altro modello
                componete il simulatore che deve essere connesso al
                modello in oggetto
*/

struct model_st
       {
        char name[MAX_LUN_NOME_MODELLO+3];
        int  lun_name;
        char descr[68];
        char sistema_operativo[MAX_LUN_SISTEMA];
        char host[MAX_LUN_HOST];
        char utente[MAX_LUN_UTENTE];
        char path[80];
        int  lun_path;
        int  tipo_task;
        float dt;
        int punt_ivus;
        int punt_ivin;
        int punt_ider;
        int punt_idati;
        int num_ic;
        int punt_ing[MAX_COLL];
        int punt_usc[MAX_COLL];
       } ;

typedef struct model_st MODEL ;

/*
   la struttura COLLEGAMENTO contiene il numero delle variabili collegate
   ed i puntatori all'elenco dei puntatori a queste ultime
   utilizzo: COLLEGAMENTO collegamento[MAX_MODEL][MAX_MODEL]
*/

struct collegamento_st
        {
        int numero_collegamenti;
        int *ingresso;
        int *uscita;
        };

typedef struct collegamento_st COLLEGAMENTO;

/*
 La struttra SCAMBIO scambio[MAX_MODEL][MAX_DT_DEC] contiene la tabella
 di svincolo per i lo scambio di dati fra i singoli modelli ad ogni micro
 passo di tempo
 ex: scambio[0][4].read[3]=1 -> il modello 0 deve leggere dei dati
                                dal modello 3 a DT=4
*/

struct scambio_st
        {
        int read[MAX_MODEL];
        int write[MAX_MODEL];
        };

typedef struct scambio_st SCAMBIO;

/*
  La struttura TABEL tabel[MAX_MODEL] contiene la tabella per
  l'attivazione dei singoli modelli all'interno del passo di simulazione
  ex: tabel[0].inst[5] -> il modello 0 deve essere risvegliato a DT=5
*/
struct tabel_st
       {
        int inst[MAX_DT_DEC];
        int forzatura;
       } ;

typedef struct tabel_st TABEL ;

/* La struttura NOMI viene utilizzata come struttura di appoggio per la
   creazione del file binario variabili.rtf:

         char name[MAX_MODEL][MAX_LUN_NOME_MODELLO];
                nomi dei modelli componenti la simulazione

         int nmod;
                numero dei modelli

         int num_blocchi[MAX_MODEL];
                numero dei blocchi di ciascun modello

         char nom_bloc[MAX_MODEL][N002][MAX_LUN_NOME_BLOCCO];
                nomi dei blocchi divisi per modello

        int num_dati_bloc[MAX_MODEL][N002+1];
                numero dei dati del blocco
*/

struct nomi_st
        {
         char name[MAX_MODEL][MAX_LUN_NOME_MODELLO];
         int nmod;
         int num_blocchi[MAX_MODEL];
         char nom_bloc[MAX_MODEL][N002][MAX_LUN_NOME_BLOCCO];
         int num_dati_bloc[MAX_MODEL][N002+1];
        };
/* la struttura S02 contiene la prima parte del file binario
   topologia.rtf:

        int nmod;
                numero dei modelli componenti la simulazione

        int nrip;
                numero di sottopassi nei quali viene suddiviso un
                singolo passo di simulazione

        MODEL model[MAX_MODEL];
                vedi struttura MODEL

        TABEL tabel[MAX_MODEL];
                vedi struttura TABEL

        char macro_modello[12];
                nome del modello

        int  lun_macro_modello;
                lunghezza del nome del modello

        char descr_macro_modello[68];
                breve descrizione del modello (la compilazione di questo
                campo e' facoltativa)

*/


struct s02_st     {
                   int nmod;
                   int nrip;
                   MODEL model[MAX_MODEL];
                   TABEL tabel[MAX_MODEL];
                   char macro_modello[12];
                   int  lun_macro_modello;
                   char descr_macro_modello[68];
                   char host_bm[MAX_LUN_HOST];
                   char host_scada[MAX_LUN_HOST];
                   char host_bi[MAX_LUN_HOST];
                  }  ;

/*
   Le struttura F04 S04 e VARLEGO sono  strutture di appoggio interne
   al processo NET_COMPI
*/

struct f04_st     {
                   int nbl;
                   int neqal;
                   int nvart;
                   int neqsis;
                   int nu;
                   int nbl1;
                   char nom_bloc[N002][MAX_LUN_NOME_BLOCCO];
                   int ip[M003];
                   int ipvrs[N005];
                   char nom_sivar[N003][100];
                   int iout_sivar[N003];
                   char nom_vari[N004][100];
                   int iout_vari[N004];
                   int ndati;
                   int lun_path;
                   char path[90];
                   int ipdati[N002+1];
                  } ;

struct s04_st     {
                   char nom_sivar[N003][100];
                   char nom_vari[N004][100];
                  } ;

struct varlego_st {
                   int neqsis;
                   int nu;
                   int nderi;
                   char nom_sivar[N003][100];
                   char nom_vari[N004][100];
                  } ;

/* La struttra VARIABILI viene utilizzata per accedere al file
   variabili.rft, del quale, durante la simulazione, esiste un immagine
   in memoria.

        char nome[MAX_LUN_NOME_VAR];
                nome della variabile

        char descr[MAX_LUN_DESCR_VAR];
                descrizione della variabile;

        unsigned short  mod;
                indice del modello 1..

        unsigned short  blocco;
                indice del blocco 1..

        char  tipo;
                tipo di variabile: ingresso non conn/conn uscita o
                stato

        int  addr;
                indirizzo in database della variabile

        char  typ;
                variabile selezionata o meno per la grafica

        char  typlg;
                variabile selezionata o meno per la grafica

        char tipo_var;
                variabile digitale o analogica
*/

struct variabili_st {
                char nome[MAX_LUN_NOME_VAR];
                char descr[MAX_LUN_DESCR_VAR];
                unsigned short  mod;
                unsigned short  blocco;
                char  tipo;
                int  addr;
                char  typ;
                char  typlg;
                int tipo_var;
               } ;

/* La struttra NOMI_MODELLI viene utilizzata per accedere al file
   variabili.rft, del quale, durante la simulazione, esiste un immagine
   in memoria.

        char nome[MAX_LUN_NOME_MODELLO];
                nome del modello

        unsigned short num_blocchi;
                numero dei blocchi del modello

        int offset;
                indice di appoggio
*/

struct nomi_modelli_st{
                char nome[MAX_LUN_NOME_MODELLO];
                unsigned short num_blocchi;
                int offset;
                };
/*
   La struttra NOMI_MODELLI viene utilizzata per accedere al file
   variabili.rft, del quale, durante la simulazione, esiste un immagine
   in memoria.

        char nome[MAX_LUN_NOME_BLOCCO];
                nome del blocco
*/

struct nomi_blocchi_st{
                char nome[MAX_LUN_NOME_BLOCCO];
                int  num_dati;
                };

/*
   La struttura SELZIONE viene utilizzata dal processoNET_MONIT per
scrivere e leggere l'header del file recorder.var

        char nome_mod[80];
                nome del simulatore

        char nome_selezione[80];
                nome della selezione grafica

        char autore_selezione[80];
                autore della selezione grafica

        char versione_selezione[80];
                versione della selezione grafica
*/

struct selezione_st {
                 char nome_mod[80];
                 char nome_selezione[80];
                 char autore_selezione[80];
                 char versione_selezione[80];
                };
/*
  La struttura SNTAB viene utilizzato come header di ciascun snapshot
registrato nel file snapshot.dat

        int stat;
                stato dello snapshot (libero[0] o occupato[1])

        int pos;
                posizione all'interno del file

        int prog;
                indice dello snapshot

        char descr[SNAP_DESC];
                descrizione dello snapshot
*/

struct sntab_st {
                 int stat;
                 int pos;
                 int prog;
                 int mod;
                 int forzato;
                 float val[MAX_VAL_SNAP];
                 char descr[SNAP_DESC];
                 char datasn[DATA_SNAP];
                 char temposn[TEMPO_SNAP];
                } ;

typedef struct sntab_st    SNTAB   ;

/*
  La struttura SNAP viene utilizzata per contenere uno snapshot

        SNTAB tab;
                header dello snapshot

        float var[NUM_VAR_TOT_MOD];
                dati dello snapshot
        char  aus[DIM_SNAP_AUS];
                sezione di dati ausiliari

*/
struct snap_st {
                SNTAB tab;
                float var[NUM_VAR_TOT_MOD];
                char  aus[DIM_SNAP_AUS];
#if defined MFFR
                char smfr[sizeof(SNAP_SKED)];
#endif
               } ;

/*
  La struttura DATI_SNAP viene utilizzata per contenere i dati di uno
snapshot
        float var[NUM_VAR_TOT_MOD];
                dati dello snapshot
        char  aus[DIM_SNAP_AUS];
                sezione di dati ausiliari
*/

struct dati_snap_st {
                float var[NUM_VAR_TOT_MOD];
                char  aus[DIM_SNAP_AUS];
#if defined MFFR
                char smfr[sizeof(SNAP_SKED)];
#endif
               } ;

/*

        runtime_replay: indica se e' una perturbazione proveniente
                        dall'esterno (PERT_RUN_TIME) oppure gestita
                        durante il replay (PERT_REPLAY) [solo per REPLAY]
        posizione: posizione nell'area pert
        tipo: tipo di perturbazione (vedi sopra)
        indirizzo: indirizzo in shared memory della variabile da perturbare
        esaminata: variabile di appoggio;
        valore_delta: valore finale o delta, utilizzato da SCALINO, RAMPA,
                      IMPULSO
        rateo_durata: rateo della rampa (delta su secondi) o durata
                      dell'impulso
        t: se >=0 : tempo a cui attivare la perturbazione
           se <0  : delta t a cui attivare la perturbazione

*/

struct tipo_pert_st {
#if defined REPLAY
        int runtime_replay;
#endif
        int posizione;
        int tipo;
        int indirizzo;
        int esaminata;
        float valore_delta; /* parametro T1 per pert. periodiche */
        float rateo_durata; /* parametro T2 per pert. periodiche */
        float t;
        float period;
        float phase;
        float meanvalue;
        float wide;
        float t_null_var;   /* tempo nullo per spike o varianza
                                per white noise                 */
        };


typedef enum _flag_sel { SEL_REG, SEL_LGPH } FLAG_SEL;

typedef struct snap_st         SNAP      ;
typedef struct dati_snap_st    DATI_SNAP ;
typedef struct s02_st          S02       ;
typedef struct f04_st          F04       ;
typedef struct s04_st          S04       ;
typedef struct varlego_st      VARLEGO   ;
typedef struct nomi_st         NOMI      ;
typedef struct selezione_st    SELEZIONE ;
typedef struct variabili_st    VARIABILI ;
typedef struct nomi_modelli_st NOMI_MODELLI ;
typedef struct nomi_blocchi_st NOMI_BLOCCHI ;
typedef struct tipo_pert_st    TIPO_PERT ;

#if defined BACKTRACK
typedef struct sntab_st    BKTAB   ;
typedef struct snap_st         BKTK      ;
typedef struct dati_snap_st    DATI_BKTK ;
#endif
/* ***************************************************************** */


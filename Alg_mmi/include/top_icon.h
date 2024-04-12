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
   modulo top_icon.h
   tipo 
   release 1.14
   data 7/4/95
   reserved @(#)top_icon.h	1.14
*/
#define NVAR_IN_ICON 100  /* Max numero di variabili in un icona */
#define LUNSIGL   5      /* Lunghezza delle sigle */
#define LUNNOME   9      /* Lunghezza dei nomi */
#define LUNDESC  80      /* Lunghezza stringhe descrittive dell'icona */
#define NSCHEMI 1000      /* Max numero di schemi */
#define NICON   300      /* Max numero di icone in uno schema */
#define NINTE   100      /* Max numero di icone di interfaccia */
#define M_CONN  100      /* Significato analogo  a NINTE */
#define NMDLTI  100      /* Max numero di moduletti leggibili da uno schema */
#define NMODULI 100      /* Max numero di moduletti di una task */
#define MAX_SHE_INLIST 1000  /* Max. num di schemi in lsiat_schemi.dat */
#define AGG_SCHE       25  /* Quantita' per riallocare ill numero precedente */
#define LUNVALF14      11  /* Lunghezza campo valore dati letti da f14.dat */

/*
   Struttura per la scrittura su file delle informazioni di una 
   icona. Il file, <nomepagina>.reg viene utilizzato per la 
   creazione del file ASCII <nomepagina>.top da parte del programma
   topsch.
*/
typedef struct top_icon_st
        {
        char  icn_sigl[LUNSIGL];       /* sigla icona  */
        char  pr_nome[LUNNOME];        /* tipo icona+sigla progressiva icona(4+4)*/
        char  pr_desc[LUNDESC];       /* descrizione icona *//*Da 54 a 80 !! */
        char  pr_var[NVAR_IN_ICON][LUNNOME];     /* nome variabile i-esima */
        /*char pr_val[NVAR_IN_ICON][LUNDESC];*/
        float pr_val[NVAR_IN_ICON];      /* valore variabile i-esima */
        char  pr_viorg[NVAR_IN_ICON][LUNNOME];   /* nome originale variabili */
        char  pr_type[NVAR_IN_ICON][3];    /* tipo variabile (IN,UA,US) */
        char  pr_vds[NVAR_IN_ICON][LUNDESC];    /* descrizione variabile */
        /*****
        ******/
        char  flag_est_var[NVAR_IN_ICON][2];
        int   pr_v_fl[NVAR_IN_ICON];       /* flag variabile connessa */
        char  pr_idvin[NVAR_IN_ICON][7];   /* sigla icona collegata   */
        int   pr_nuvto;   /* numero variabili totali nella icona */ 
        int   pr_nuvin;   /* numero variabili di ingresso nella icona */ 
        int   pr_nuvot;   /* numero variabili di uscita */
        int   pr_nuvdt;   /* numero variabili - dati */
        short pr_ndat;    /* numero dei dati fisici e geometrici del blocco */
        int   fl_macro;   /* flag indicante se il blocco e' macromodulo */
        char  var_assoc[NVAR_IN_ICON][LUNNOME];   /* tag dato i_esimo */
        /*****
        ******/
        char  flag_est_dat[NVAR_IN_ICON][2];
        char  des_assoc[NVAR_IN_ICON][LUNDESC];
        /*char  val_assoc[NVAR_IN_ICON][LUNDESC];*/   /* valore del dato i-esimo */
        float  val_assoc[NVAR_IN_ICON];
        } TOP_ICON;


/*
   Strutture dati relative alle pagine di regolazione e alle icone
   di interfaccia con i loro eventuali collegamenti.
*/

/* Descrizione del collegamento di una icona 
   interfaccia collegata  */
typedef struct icon_colleg_st
        {
        char  int_sche[LUNNOME];
        char  int_varl[10];
        char  int_varr[10];
        }ICON_COLLEG;

/* Descrizione di un icona di interfaccia */
typedef struct icon_interf_st
        {
        char  int_icnsigl[LUNSIGL];
        char  int_conn[3];
        ICON_COLLEG clg;
        }ICON_INTERF;

/* Descrizione dello schema */
typedef struct schm_st
        {
        int   num_icn_interf;
        char  uso_schema[3];
        char  id_schema[LUNSIGL];
        char  des_schema[LUNDESC];
        }SCHM;

/* Nomi e descrizione dei moduletti */
typedef struct modul_lst_st
   {
   int num;
   char nome[NMDLTI][LUNSIGL];
   char desc[NMDLTI][LUNDESC];
   }MODUL_LST;

/* Descrizione dello schema */
typedef struct desc_schema_st
        {
        SCHM schm;
        MODUL_LST mdlt;
        ICON_INTERF *icn_interf;
        }DESC_SCHEMA;

/*
   Struttura utilizzata per la lettura del file schema_14.dat 
   caricata in rd_f14 ed utilizzata in setta_valori_14.
*/
typedef struct
   {
   char nome[LUNNOME];       /* Nome della variabile letta da f14.dat */
   char fval[LUNVALF14];     /* Valore della medesima (stringa) */
   } VARS;


/*
   Strutture dati relative alla geDastione della lista schemi, lista_schemi.dat
*/
/* Informazioni degli schemi salvati o da salvare in lista_schemi.dat */
typedef struct lst_schm_st
        {
        int  again;        /* 0 presente, 1 libero, -1 da non inserire */
        char name[5];      /* Nome dello schema nella lista */
        char descr[203];   /* Descrizione dello schema nella lista */
        }LST_SCHM;




/*
   Strutture dati relative alla generazione dei macromoduli.
*/

typedef struct
   {
   char nome_var_conn[LUNSIGL];
   } VAR_CONN;

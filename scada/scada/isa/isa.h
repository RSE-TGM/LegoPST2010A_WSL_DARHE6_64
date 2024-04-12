/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/* definizione messaggi e strutture dati per funzionalita' ISA
*/


extern DB_HEADER h_db;

#define MSCNVSD   0x101
#define MSGETSD   0x102
#define MSLSFILE  0x103
#define MSLSFILX  0x183
#define MSGETFILE 0x104
#define MSGETFILX 0x184
#define MSGETCNF  0x105
#define MSWRSD    0x106
#define MSGSSAMP  0x107
#define MSGRSTRI  0x108
#define MSGETINF  0x109
#define MSPUTFILE 0x10A
#define MSGETMSG  0x10B
#define MSGETSTR  0x10C
#define MSWRSTR   0x10D

#define MRCNVSD   0x201
#define MRGETSD   0x202
#define MRLSFILE  0x203
#define MRGETFILE 0x204
#define MRGETCNF  0x205
#define MRWRSD    0x106
#define MRGETINF  0x209
#define MRPUTFILE 0x20A
#define MRGETMSG  0x20B
#define MRGETSTR  0x20C
#define MRWRSTR   0x20D



typedef struct {
            unsigned    short ch;
                    short cod;
                    short id; } HEADISA;
                    
#define LSIGLE 10
#define MAXSIGLE 100 
#define MAXSIGLESTR 30           // n. massimo stringhe
#define MAXINF 20 
#define MAXMSGLENGHT 2500        /* massima lunghezza messaggio */

typedef struct {
                    HEADISA h;
                    short      npunti;
                   char    sigle[LSIGLE * MAXSIGLE]; } SCNVSD;

typedef struct { short p;
                      short e;} PUNDB;  
                
typedef struct {
                    HEADISA h;
                    short npunti;
                    PUNDB token[MAXSIGLE];
                    } SGETSD;

typedef struct {
            short flag;
            float v;} misan;

typedef union  {
            misan m;
            short d;
            short w[3]; } VDB;

typedef struct {
                    HEADISA h;
                    short npunti;
                    VDB val[MAXSIGLE];
                    } RGETSD;

typedef struct  {                 // data base stringhe
            short flag;
            char  w[g0lunst]; } VDBSTR;

typedef struct {                 // messaggio aggiornamento stringhe
                    HEADISA h;
                    short npunti;
                    VDBSTR val[MAXSIGLESTR];
                    } RGETSTR;



typedef struct {
                    HEADISA h;
                    char lista[14];
                    short spare;
                    } SLSFILE;

#define LENGBUF 512

typedef struct {
                    HEADISA h;
                    char lista[14];
                    char flgcontinue;
                    char wildchar;
                    char b[LENGBUF];
                    } RLSFILE;


typedef struct {
                    HEADISA h;
                    char file[14];
                    long spare1;
                    long spare2;
                    short spare3;
                    } SGETFILE;


typedef struct {
                    HEADISA h;
                    char file[14];
                    long total;
                    long offset;
                    short len;
                    char b[LENGBUF];
                    } RGETFILE;

typedef struct {
    HEADISA h;
    char file[14];      /* nome file */
    long total;
    long offset;
    short len;
    short modo; /* 1 normale 2 sovrascrivi */
    char b[LENGBUF];} SPUTFILE;

typedef struct {
    HEADISA h;
    char file[14];
    long total;
    long spare2;
    short ret;          /* 0 ok altrimenti errore su host */ 
    short spare1;
    } RPUTFILE;


typedef struct {
                    HEADISA h;
                    } SGETCNF;


typedef struct {
                    HEADISA h;
                    DB_HEADER hdb;
                    } RGETCNF;

typedef struct {
                    HEADISA h;
                    short npunti;
                    PUNDB token[MAXINF];
                    } SGETINF;
typedef struct {
               char sigla[16];
               char descri[32];
               char info1[10];
               char info2[10];
               } STINF;
               
typedef struct {
                    HEADISA h;
                    short npunti;
                    STINF stinf[MAXINF];
                    } RGETINF;



typedef struct 
   {
   unsigned char  cod;
   unsigned short index;
   } HEADSAMP;

/* Questa e` la struttura presumibilmente utilizzata nel trasferimento stringhe */
/* ISA <-> SAMP. Per SCADA e` una struttura qualsivoglia, salvo la posizione dei*/
/* campi "appl_Eth" e "nodo_samp" e l'effettiva posizione e congruenza dei      */
/* campi "l_hdr" ed "l_info". */
 
typedef struct
   {
   unsigned char  l_hdr;     // Lunghezza header
   unsigned char  appl_Eth;  // Indice applicativo Ethernet (poi indice coda di risposta!)
   unsigned char  nodo_samp; // Indice nodo SAMP di destinazione
   unsigned short ind_pp;    // Indirizzo posto periferico destinatario
   unsigned short durata;    // Durata collegamento per il trasferimento con STC (in sec)
   unsigned char  str_cont;  // Contatore delle stringhe (gestito da STC)
   unsigned char  canale;    // Canale seriale (gestito da STC)
   unsigned char  f_tx;      // Flag di trasmissione
   unsigned char  f_rx;      // Flag di ricezione
   unsigned char  l_info;    // Lunghezza campo "inf[]"
   unsigned char  inf[232];  // Corpo del messaggio
   } MESS_SAMP;

typedef struct 
   {
   HEADISA   h;
   HEADSAMP  hs;
   MESS_SAMP info;
   } SSAMP, RGETM;

typedef struct 
   {
   HEADISA   h;
   HEADSAMP  hs;
   } RSAMP;

/* messaggi generici per SCC Enel */
typedef struct {
    HEADISA h;
    } SGETMSG;
               
typedef struct {
    HEADISA h;
    short len;
    char buffer [2048];
    } RGETMSG;

/* ad uso scrittura in d.b. */

/* il dato puo' essere costituito da un valore float + flag e maschera di abilitazione
   dei flag da modificare. Nel caso di digitali e/o organi il valore float non e'
    significativo */

typedef struct {
            short flag;
            float v; } misao;


#define  ISA_MNONE  0
#define  ISA_MVAF   1
#define  ISA_MVAL   2
#define  ISA_MFLA   3
#define  ISA_MFORZ  4
#define  ISA_MFSCA  5
#define  ISA_MISCA  6

#define     ISA_MLL   19        // bassa sicurezza
#define     ISA_ML    20        // bassa conduzione
#define ISA_MH    21        // alta  conduzione
#define ISA_MHH   22        // alta  sicurezza

typedef struct {
                    PUNDB p;
                    short op;
                    short flag;
                    float f; } WRDB;
                    
typedef struct {
                    HEADISA h;
                    short npunti;
                    WRDB w[MAXSIGLE];
                    } SWRDB;

typedef struct {
                    PUNDB p;
                    short op;
                    short flag;
                    char  str[g0lunst]; } WRDBSTR;
                    
typedef struct {
                    HEADISA h;
                    short npunti;
                    WRDBSTR w[MAXSIGLESTR];
                    } SWRDBSTR;

// union dei messaggi possibili gestiti dal task isa()
typedef union  {
    HEADISA h;
    RX_STATOSIS ssys;                       /* risposta stato sistema                */
    SCNVSD bscnvsd; 
    SGETSD brcnvsd; 
    SGETSD bsgetsd; 
    RGETSD brgetsd; 
    RGETSTR brgetstr; 
    SLSFILE bslsfile;   
    RLSFILE brlsfile;   
    SGETFILE bsgetfile;
    RGETFILE brgetfile;
    SPUTFILE bsputfile;
    RPUTFILE brputfile;
    SGETCNF bsgetcnf;
    RGETCNF brgetcnf;
    SWRDB   bswrdb;
    SWRDB   brwrdb;
    SWRDBSTR   bswrdbstr;
    SWRDBSTR   brwrdbstr;
    SGETINF bsgetinf;   
    RGETINF brgetinf;   
    SSAMP       ssamp;  // messaggio trasferimento stringa a nodo SAMP
    RGETM       rgetm;  // messaggio stringhe pendenti da nodo SAMP 
    SGETMSG bsgetmsg;
    RGETMSG brgetmsg;
    
    char       buff[2500];
    M_APR apr;   // msg richiesta archivi presenti
    M_EFR efr;        // msg richiesta elenco file archivio-descrittore ASCII
    M_TFR tfr;        // msg richiesta trasmissione file d'archivio
    M_FLGPR flbgpr;   // msg richiesta file libro giornale presenti
    M_APS aps;  // msg trasmissione archivi presenti
    M_EFLGS efs;       // msg trasmissione elenco file archivio-descrittore ASCII
    M_TFS tfs;     // msg trasmissione file archivio
    M_FLGPS flbgps; // msg trasmessione nø file libro giornale presenti
} U_ISA_MESS;


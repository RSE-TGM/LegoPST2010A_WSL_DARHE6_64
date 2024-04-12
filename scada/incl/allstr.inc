/**********************************************************************
*
*       C Header:               allstr.inc
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Feb  5 11:53:41 1998 %
*
**********************************************************************/
/*
        allstr.inc

        Include che contiene le strutture necessarie alla gestione
        dei data base allarmi.
        Viene incluso dal file allar.inc. 


        19 Maggio 1992 Rel.1.0  Fc.

        30 Dicembre 1992 Rel. 1.1 
        Inserimento gestione contatori livelli di severita'
        Variabili per congelamento e riconoscimento singolo o
        a pagine

*/
#include "defpub.h"
#include "maxpar.inc"
#include "tipal.inc"
#include <all_1.h>

/*
        definizione struttura parallela a ciascun data base
        allarmi 
*/
typedef struct s_dbs_alp {       
                          char  def;       /* flag dbs definito            */
                          char  fchanga;   /* flag nuovo allarme           */
                struct buff_all *pall;     /* puntatore memoria allocata   */
                          short dim;       /* n. max allarmi consentiti    */
                          short pout;      /* pos. inserimento nuovo all.  */
                          short pin;       /* pos. inserimento in archivio */
                                           /* assoluto                     */
                          short pinv;      /* come pin ma rispetto criterio*/
                          short mbox;      /* mail box associata           */
                          float *db_al;    /* punt. anal. allarmi da ric.  */
                          float *db_ar;    /* punt. anal. allarmi ricon.   */
                          short video;     /* video associato              */
                   } S_DBS_ALL;

pub S_DBS_ALL  bDbsAll[max_dbsall];
/*
        definizione struttura parallela a ciascun video relativa alla
        gestione delle varie pagine allarmi
*/
#define RICSI_NO     0          // non riconoscimento singolo
#define RICSI_AB     1          // abilitato riconoscimento singolo
#define RICSI_EF     2          // effettuato il riconoscimento si almeno un all.
/*
Definisco struttura contenete informazioni per miniASD
gerarchia:
	gerarchia per la query su db allarmi
filtro
	operazione di filtraggio (0 tutti gli all. tranne quelli nel campo tipo)
				 (1 solo gli allarmi del campo tipo )
tipo
	tipo di allarme da filtrare
tipo_operazione 
	riconoscimento, interrogazione ...
lock 
	verifica che non vi sia un' altra richiesta mentre si sta eseguendo una
        operazione
db 
	database allarmi su cui operare
...
Seguono elementi che caratterizzano un allarme

*/
typedef struct s_dbs_miniASD {
                             unsigned char gerarchia[n_gerarchie];
                             int filtro;         /*  filtro  */
                             int tipo;            /* tipo allarme filtrato */
                             int tipo_operazione;  
                             int lock;          /*
						Se operaz. in corso rifiuta 
						altre operaz.
						*/
                             int db;           /* database */
/*
   inserisco dati per identificare univocamente l' allarme
   questi dati saranno utilizzati nel riconosc. singolo da miniASD
*/
                             short punt;
                             char ext;
                             unsigned char  ertr ;
                             unsigned char  giorno ;
                             unsigned char  ore    ;
                             unsigned char  minuti ;
                             unsigned char  secondi;
                             
                             } S_DBS_MINIASD;

typedef struct s_dbs_alv {char  pal;       /* n. pagina allarmi in uso     */
                          char  movi;      /* ultimo movimento in archivio */
                          short mask1;     /* zone selezionate  0-15       */
                          short mask2;     /* zone selezionate 16-32       */
                          short pvis0;     /* pos.0 finestra visualizz.    */
                          short pvis1;     /* pos.1 finestra visualizz.    */
                          short ind_all;   /* indice ultimo allarme visual.*/
                          short ind_sav;   /* ultimo allarme inviato       */
                          short full;      /* =0 16 allarmi visualizzati   */                                
                                           /* 1 <16 allarmi visualizzati   */
                                           /* -1 in riconoscimento autom.  */
                          short cod;       /* codice visualizzazione       */
                                           /* relativo alle zone selezion. */
                                           /* definito dal messaggio $ALL. */
                          short ricsi;     /* = 0 riconoscimento a 16      */                                
                                           /* = 1 riconoscimento singolo   */
                                           /* = 2 riconosciuto almeno 1 all*/
                          short nallco;    /* num allarmi al congelamento  */
                          char  svi[nall_vi];
                                           /* svincolo pagina - buffer all.*/
                                           /* per riconoscimento singolo   */     
#ifdef GERARC
			  char abgera[n_gerarchie];	/* gerarchia selezionata */
#endif
         /* parte per mini ASD */

                          S_DBS_MINIASD par_miniASD;
                   } S_DBS_ALV;

pub S_DBS_ALV bDbsAlv[max_video];
/*
        definizione struttura svincolo fra unita' di appartenenza e data
        base allarmi (al massimo max_dbsall data base)
*/
typedef struct s_dbs_alu {
                       char  pal[max_dbsall];
                       short n_al[max_dbsall];  // n. allarmi da riconoscere
                       short n_ar[max_dbsall];  // n. allarmi in archivio
                       short n_alsev[max_liv][max_dbsall];  // all. per sever. da riconoscere
                       short n_arsev[max_liv][max_dbsall];  // all. per sever. in archivio
                        } S_DBS_ALU;                                

pub S_DBS_ALU bDbsAlu[max_zone];
/*
        definizione struttura flag zone abilitate
        viene utilizzata dalla funzione dec.c e costruita
        dalla funzione abzon (task cval)
*/
typedef struct s_zone_abil {
                char abil_zone[max_zone];     // flag zone selezionate per la visualizzazione
                short n_al;                   // allarmi da riconoscere delle zone selezionate
                short n_ar;                   // allarmi in archivio delle zone selezionate
                        } S_ZONE_ABIL;
/*
Struttura che tiene conto del numero di allarmi per ciascuna zona
di impianto. Fatta su misura per messaggistica SCADA pagina allarmi mmi.
Introdotta da Fabio 6/97.
*/
typedef struct s_all_per_zone{
			short n_all_pen[max_zone];   /* allarmi pendenti per ogni zona*/
                	short n_all_arc[max_zone];   /* allarmi riconosciuti " "   " */
			} S_ALL_PER_ZONE;

pub S_ZONE_ABIL abilzo;

extern short mbox_all_0;        // definita in d386.asm 

#define CIC_STOP	0
#define CIC_INFINITO   -1
pub short tab_cic[max_liv];			// cicalino per livelli severita'
pub short tip_cic;				// tipo cicalino
#include <all_16.h>

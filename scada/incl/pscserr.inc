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
        pscserr.inc

        Il file di include contiene le definizioni dei codici di errore,
        dei task utilizzati per la segnalazione di malfunzionamenti del
        pacchetto scada.

        06 Aprile  1992  -  Rel. 1.0 Fc
        15 Ottobre 1992  -  Rel. 1.1 GM.Furlan: 
                            errori task supervisione simulatore.
        30 Dicembre 1992 -  Rel. 1.2 Fc
                            Codici configurazione allarmi
        19 Aprile        -  Rel. 1.3 Fc
                            Codici Errori open file
        11 Maggio       -   Rel. 1.4 Fc
                            Errori task reperibili
        09 Giugno 1995   -  Rel. 1.4 GM.Furlan: 
                            errori task comunicazione PLC-S5
*/

/*
        flag tipo di gestione dell'errore
*/
#define SYS_HALT        0
#define SYS_CONT        1
#define SYS_HALT_DOS    2
#define SYS_HALT_FLUSH  3
/*
        tipi di errore
*/
#define ERR_IO          0               // errore open, read o write
#define ERR_MEM         1               // errore allocazione memoria
#define ERR_TASK        2               // errore run time task
#define ERR_CONF        3               // errore configurazione
#define STOP_TASK       4               // richiesta stop sistema
/*
        codici di errore
*/
#define	END_ERR         99              // stop completo al sistema
/*
        definizione task e codici
*/
#define TASK_ARC        0                  // archivi
#define ROU_FNOM        0
#define ROU_OPEN        2        
#define ROU_OPEN1       3        
#define ROU_OPEN2       4        
#define ROU_OPEN3       5        
#define ROU_WR          6
#define ROU_FNOM0       7
#define ROU_FNOM1       8
#define ROU_DIG         9
#define ROU_ANA        11
#define ROU_AVE        12
#define ROU_READ       13

#define TASK_ACQUI      3                // acquisizione
#define ROU_SETAA       0                           // puntatore scorretto
#define ROU_SETDI       1
#define ROU_ACQUI       2                           // messaggio sconosciuto
#define ROU_SETAA1      3                           // svincolo scorretto
#define ROU_TIME        4                           // ora scorretta
#define ROU_DATE        5                           // data scorretta

#define ROU_RCE		6
#define ROU_RCEORD	7


#define TASK_ALLARMI      4                  // allarmi
#define ROU_ALLDEF      0
#define ROU_ALLDEC      1
#define ROU_ALLDEF1     2
#define ROU_ALLTRAT     3
#define ROU_ALLSEV      4
#define COEF_MEDIAT     5                            // coeff. media
#define COEF_FILTRO     6                            // coeff. media
#define COEF_SCARTO     7                            // coeff. media
#define COEF_MEDIAI     8                            // coeff. media
#define COEF_SOMMA      9                            // coeff. media
#define COEF_INTEGRALE  10                           // coeff. media
#define TAB_K           11                           // tabella coefficienti K troppi valori
#define TAB_K_COD       12                           // tabella coefficienti K errore decodifica
#define TAB_CIC_        13                           // definizione timer cicalino
#define DEF_SCONOSCIUTA 14                           // chiave sconosciuta	
#define TIP_CIC_        15                           // definizione timer cicalino
#define RESET_UT        16                           // definizione frequenza reset calcolate definito da utente
#define REP_RETRY       17                           // n. retry reperibili
#define REP_MESS        18                           // n. messaggi accodabili

#define TASK_PAS          5                  // PAS
#define ROU_ALLOCPAS    0

#define TASK_WD           6                  // superato valore limite del  
#define ROU_PSCSWD      0                            // contatore di WATCH-DOG

#define TASK_SIMACQUI     7                  // acquisizione da simulatore
#define ROU_FSVIN       0                            // file di svincolo
#define ROU_SDCFG       1                            // send configurazione
#define ROU_STOPT       2                            // stop task 
#define ROU_MESS        3                            // messaggio sconosciuto
#define ROU_LOAD        4                            // errore successione blocchi aggiornamento DB
#define ROU_SVALL       5                            // errore salvataggio database allarmi
#define ROU_SVDBS       5                            // errore salvataggio database punti

#define TASK_AGGCFG       8                  // aggiornamento da config
#define ROU_AGGFMA      0			     // forza master
#define ROU_AGGMES      1			     // incongruenza messaggi	
#define ROU_AGGSCO      2			     // messaggio sconosciuto	
#define ROU_AGGFIL      3			     // errore file

#define TASK_SCGEV        9
#define ROU_SCGEV       0
#define ROU_REGIS       1

#define ROU_INIT  	10                  // fase inizializzazione
#define FILE_FSTATO     0                           // open file
#define FILE_FDIZST     1
#define FILE_FNOMI      2
#define FILE_FDDE       3
#define FILE_FDCOM      4
#define FILE_FTAB       5
#define FILE_FDIZTAB    6
#define FILE_FSVAR      7
#define FILE_FDEAO      8
#define ADDR_BB         9
#define FILE_FVIRTPRN   10
#define FILE_INI   	11


#define ROU_PNTA        14
#define ROU_PNTD        15
#define ROU_COEFF       16
#define ROU_SV_AO       17
#define ROU_HASP_INI    18


#define	TASK_RETE       11                  // stop sistema gestione rete inet

#define TASK_DUALE      12
#define ROU_DUALE       0
	
#define ROU_LEGGIFIL    13                  // fase inizializzazione
#define FILE_STRAT      0                   // open file errata apertura strat.rtf o fvirtprn.rtf

#define TASK_IOBOARD	14
#define	ROU_GETBUS  	0		

#define TASK_STAMPE     15
#define ROU_STFILE      0
#define ROU_STAMPE      1

#define TASK_RCE        16
#define	ROU_PRN         0

#define TASK_ASINCT     17
#define ROU_CALCDIT     0

#define TASK_TABUL      18
#define ROU_CPRINT      0

#define TASK_TXREM      19                   // Task trasmissione a terminali remoti
#define ROU_TXREMINIT   0

#define TASK_REP        20
#define ROU_INI_DIA             0       // manca la diagnostica necessaria
#define ROU_REP_OPEN            1       // impossibile aprire un file
#define ROU_REP_PTUNKNOWN       2       // punto di tipo sconosciuto
#define ROU_REP_PTNOTFOUND      3       // punto non trovato
#define ROU_REP_OUTOFMEM        4       // memoria insufficiente per allocare gli svincoli
#define ROU_INI_TABELLA         5       // file di configurazione errato

#define TASK_S5         21                   // acquisizione da PLC S5-Siemens
#define UDD_OP          0                            // errore da UDD_OPEN
#define UDD_WR          1                            // errore da UDD_WRITE
#define UDD_RD          2                            // errore da UDD_READ
#define NO_BUF          3                            // errore allocazione buffer in area Real
#define FILE_SCAN       4                            // errore apertura SCAN.LIS  
#define FILE_FDEACQ     5                            // errore apertura FDEACQ.RTF
#define FILE_FDEDA      6                            // errore apertura FDEDA.RTF
#define ROU_CTRLMSG     7                            // congruenza messaggio   
#define ERR_IDB  0                                // indice DB
#define ERR_TPTI 1                                // tipo punti
#define ERR_NPTI 2                                // numero punti

#define TASK_ISA         22                   // ISA
#define ROU_ALLOC       0                            // errore allocazione

#define TASK_RS232       23
#define ROU_CHIP        0
        
#define TASK_ATTIPER    24    
#define	ROU_HASP_QRY         0

#define TASK_RCELAC     25
#define	ROU_STORERCE         0
#define	ROU_WRITERCE         1

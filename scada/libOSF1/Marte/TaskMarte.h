/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#include <maxpar.inc>
extern test_p1();
extern test_p2();

/* 
	definizione delle task del dello SCADA
*/
extern pscsini();    /* task con autostart = 1 */
extern attiper();
extern pscswd();
extern scgev();
extern gdac();
extern PrintThreadState();
extern DriverRete();
extern asinct();
extern tcval();
extern _call();
extern arcwai();
extern _tabulati();
extern acqui();
extern print();
extern stampe();
extern taggcfg();
extern tabper();

/*
	define per mailbox
*/
#define MBOX_ARCHIV	0   // 0
#define MBOX_ALL_0	MBOX_ARCHIV +1  // 1
#define MBOX_LBG	MBOX_ALL_0 + max_dbsall   // 7
#define MBOX_DISK	MBOX_LBG +1   // 8
#define MBOX_PAG1	MBOX_DISK +1  
#define MBOX_PAG2	MBOX_PAG1 +1 
#define MBOX_PAG3	MBOX_PAG2 +1
#define MBOX_PAG4	MBOX_PAG3 +1
#define MBOX_PAG5	MBOX_PAG4 +1
#define MBOX_PAGRES1	MBOX_PAG5 +1
#define MBOX_PAGRES2	MBOX_PAGRES1 +1   
#define MBOX_PAGRES3	MBOX_PAGRES2 +1  
#define MBOX_PAGRES4	MBOX_PAGRES3 +1 
#define MBOX_PAGRES5	MBOX_PAGRES4 +1
#define MBOX_SCGEV	MBOX_PAGRES5 +1
#define MBOX_ABILGER	MBOX_SCGEV +1

/*
	define per tcb
*/
#define PSCSINI_TCB 	0
#define PSCSWD_TCB 	1
#define PCCOM_TCB 	2
#define ASINCT_TCB 	3
#define _CALL_TCB 	4
#define STAMPE_TCB 	5
#define SCGEV_TCB 	6
#define TCVAL_TCB 	7
#define ATTIPER_TCB 	8
#define MONITOR_TCB 	9
#define GDAC_TCB 	10
#define TAGGCFG_TCB 	12
#define SCHC_TCB 	13
#define THCWIN_TCB 	14
#define TCTE3_TCB 	15
#define TCTE4_TCB 	16
#define REPTASK_TCB 	17
#define IDLE_TCB 	18
#define GPS_TCB 	19
#define ACQUI_TCB 	20
#define _TABULATI_TCB 	21
#define TABPER_TCB 	22
#define ARCWAI_TCB 	23
#define _ISA_TCB 	24
#define RXPIO_TCB 	25
#define TXPIO_TCB 	26
#define DUATASK_TCB 	27
#define PAG1_TCB 	28
#define PAG2_TCB 	29
#define PAG3_TCB 	30
#define PAG4_TCB 	31
#define PAG5_TCB 	32
#define STATISTICS_TCB 	33
#define ACCODA_C_MMII_TCB 	34
#define SCODA_C_MMIO_TCB 	35
#define DRIVER_RETE_TCB 	36
#define PRINT_00_TCB 		37
#define PRINT_01_TCB 		38
#define PRINT_02_TCB 		39
#define PRINT_03_TCB 		40
#define PRINT_04_TCB 		41
#define PRINT_05_TCB 		42
#define PRINT_06_TCB 		43
#define PRINT_07_TCB 		44

#define P1_TCB 			45
#define P2_TCB 			46
/*
	define per le priorit' delle task 
	PRIO_FIFO_MIN 14
	PRIO_FIFO_MAX 21
*/
#define PSCSINI_PRIO 	15
#define PSCSWD_PRIO 	18
#define PCCOM_PRIO 	15
#define ASINCT_PRIO 	16
#define _CALL_PRIO 	19
#define STAMPE_PRIO 	15
#define SCGEV_PRIO 	15
#define TCVAL_PRIO 	19
#define ATTIPER_PRIO 	15
#define MONITOR_PRIO 	15
#define GDAC_PRIO 	15
#define TAGGCFG_PRIO 	15
#define SCHC_PRIO 	15
#define THCWIN_PRIO 	15
#define TCTE3_PRIO 	15
#define TCTE4_PRIO 	15
#define REPTASK_PRIO 	15
#define IDLE_PRIO 	15
#define GPS_PRIO 	15
#define ACQUI_PRIO 	20
#define _TABULATI_PRIO 	15
#define TABPER_PRIO 	15
#define ARCWAI_PRIO 	17
#define _ISA_PRIO 	15
#define RXPIO_PRIO 	15
#define TXPIO_PRIO 	15
#define DUATASK_PRIO 	15
#define PAG1_PRIO 	15
#define PAG2_PRIO 	15
#define PAG3_PRIO 	15
#define PAG4_PRIO 	15
#define PAG5_PRIO 	15
#define STATISTICS_PRIO 15
#define ACCODA_C_MMII_PRIO 	15
#define SCODA_C_MMIO_PRIO 	15
#define DRIVER_RETE_PRIO 	20
#define PRINT_00_PRIO 		15
#define PRINT_01_PRIO 		15
#define PRINT_02_PRIO 		15
#define PRINT_03_PRIO 		15
#define PRINT_04_PRIO 		15
#define PRINT_05_PRIO 		15
#define PRINT_06_PRIO 		15
#define PRINT_07_PRIO 		15

#define P1_PRIO			18
#define P2_PRIO 		17

typedef struct _ELE_TASK_MARTE{
	int auto_start;
        int codice;
        char *nome;
	int (*procedura)();
        int prio;
        } ELE_TASK_MARTE;

#if defined ENEL_SIM
#define NUM_ELE_TASK_MARTE	26
#else
#define NUM_ELE_TASK_MARTE	25
#endif
static ELE_TASK_MARTE ele_task_marte[] = {
#if defined ENEL_SIM
        {
	0,
	ACQUI_TCB,
	"Acqui",
	&acqui,
	ACQUI_PRIO,
        },
#endif
        {
	0,
	TABPER_TCB,
	"tabper",
	&tabper,
	TABPER_PRIO,
        },
        {
	0,
	TAGGCFG_TCB,
	"taggcfg",
	&taggcfg,
	TAGGCFG_PRIO,
        },
        {
	0,
	GDAC_TCB,
	"gdac",
	&gdac,
	GDAC_PRIO,
        },
        {
	0,
	SCGEV_TCB,
	"scgev",
	&scgev,
	SCGEV_PRIO,
        },
        {
	0,
	ATTIPER_TCB,
	"attiper",
	&attiper,
	ATTIPER_PRIO,
        },
        {
	0,
	STATISTICS_TCB,
	"Statistica processi",
	&PrintThreadState,
	STATISTICS_PRIO,
        },
        {
	0,
	PSCSWD_TCB,
	"pscswd",
	&pscswd,
	PSCSWD_PRIO,
        },
        {
	1,
	PSCSINI_TCB,
	"pscsini",
	&pscsini,
	PSCSINI_PRIO,
        },
        {
	1,
	DRIVER_RETE_TCB,
	"DriverRete",
	&DriverRete,
	DRIVER_RETE_PRIO,
        },
        {
	0,
	ASINCT_TCB,
	"Asinct",
	&asinct,
	ASINCT_PRIO,
        },
        {
	0,
	_CALL_TCB,
	"Call",
	&_call,
	_CALL_PRIO,
        },
        {
	0,
	TCVAL_TCB,
	"Cval",
	&tcval,
	TCVAL_PRIO,
        },
        {
	0,
	ARCWAI_TCB,
	"Archvi",
	&arcwai,
	ARCWAI_PRIO,
        },
        {
	0,
	_TABULATI_TCB,
	"Tabulati",
	&_tabulati,
	_TABULATI_PRIO,
        },
        {
	0,
	STAMPE_TCB,
	"Stampe",
	&stampe,
	STAMPE_PRIO,
        },
        {
	1,
	PRINT_00_TCB,
	"Printer 00",
	&print,
	PRINT_00_PRIO,
        },
        {
	1,
	PRINT_01_TCB,
	"Printer 01",
	&print,
	PRINT_01_PRIO,
        },
        {
	1,
	PRINT_02_TCB,
	"Printer 02",
	&print,
	PRINT_02_PRIO,
        },
        {
	1,
	PRINT_03_TCB,
	"Printer 03",
	&print,
	PRINT_03_PRIO,
        },
        {
	1,
	PRINT_04_TCB,
	"Printer 04",
	&print,
	PRINT_04_PRIO,
        },
        {
	1,
	PRINT_05_TCB,
	"Printer 05",
	&print,
	PRINT_05_PRIO,
        },
        {
	1,
	PRINT_06_TCB,
	"Printer 06",
	&print,
	PRINT_06_PRIO,
        },
        {
	1,
	PRINT_07_TCB,
	"Printer 07",
	&print,
	PRINT_07_PRIO,
        },
        {
	1,
	P1_TCB,
	"Programma prova 01",
	&test_p1,
	P1_PRIO,
        },
        {
	1,
	P2_TCB,
	"Programma prova 02",
	&test_p2,
	P2_PRIO,
        },
};


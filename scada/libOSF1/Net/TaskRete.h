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
   modulo %M%
   tipo %Y%
   release %I%
   data %G%
   reserved %W%
*/
/*
	elenco delle task di rete da attivare
*/
#define MAX_DRIVER_CONN		16
typedef struct _ELE_TASK_RETE{
	char descr[100];  // descrizione della connessione
        short coda_input; // coda verso scada
        short coda_output; // coda da scada
        int port;   // porta di rete prima connessione
	int numero_conn; // numero delle connessioni da aprire
        } ELE_TASK_RETE;

typedef struct _ELE_TASK_RETE_TH{
	pthread_t main;  // identificato thread main
	pthread_t input[MAX_DRIVER_CONN];//identificatore thread ricezione rete
	pthread_t output; // identificatore thread trasmissione rete
	int fp[MAX_DRIVER_CONN];
	int fp_in[MAX_DRIVER_CONN];
	FILE *fp_log;
	} ELE_TASK_RETE_TH;

#define NUM_ELE_TASK_RETE      4
#define TASK_RETE_MMI      0
static ELE_TASK_RETE ele_task_rete[] = {
        {
	"Connessione mmi",
	9,
	10,
	1900,
	3,
        },
        {
	"Connessione simulatore dati",
	5,
	6,
	3000,
	1,
        },
        {
	"Connessione simulatore comandi",
	29,
	30,
	2050,
	1,
        },
        {
	"Connessione config",
	11,
	12,
	9000,
	1,
        },
};

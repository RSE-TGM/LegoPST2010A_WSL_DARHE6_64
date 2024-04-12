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
   modulo comp_vme.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)comp_vme.h	5.1
*/
/*
	
	Include per processo comp_vme e tasknl_vme.
	Contiene i valori minimi e massimi per l'acquisizione dalle
	schede di I/O.
	Il massimo numero delle schede.
	Il numero di canali per scheda
*/


/*

		Parametri di configurazione schede

*/
#define MAX_VAL         4095          /* valore max I/O schede analogiche */
#define MIN_VAL         0             /* valore min I/O schede analogiche */
#define MAX_SCHEDE_INPUT        10
#define MAX_SCHEDE_DIG          10
#define DIG_PER_SCHEDA		48    /* numero dei digitali per scheda */
#define CANALI_SCHEDE_INPUT     32    /* numero di canali di input analogici */





/*
		Parametri interni
*/
#define MAX_RIGHE_IO    	1000  /* max numero di punti configurati */
#define RIGHE_NULLE 		10    /*numero di righe da saltare sul 
					file *.pn                        */





/*
	Struttura per la lettura del file *.pn
*/
struct righello_st
        {
        char nome_campo[10];
        int inizio;
        int size;
        int tipo; /* 0 char    1 int       2 float */
        };
typedef struct righello_st RIGHELLO;
RIGHELLO righello[]={
        "addr",83,8,1,
        "tipo_d",53,2,0,
        "variab",16,8,0,
        "min",25,9,2,
        "max",35,10,2,
        "sigla",1,8,0,
        "task",92,8,0,
        "task_d",25,8,0,
        "mask",92,8,1
                };
int num_campi= (sizeof(righello) / sizeof(righello[0]));



/*


		NON TOCCARE LE DEFINIZIONI CHE SEGUONO


*/
#define USCITE_AGGIUNTIVE	MAX_SCHEDE_INPUT+2
#define TIPO_ANALOG_INPUT       1
#define TIPO_ANALOG_OUTPUT      2
#define TIPO_DIGITAL_INPUT      3
#define TIPO_DIGITAL_OUTPUT     4


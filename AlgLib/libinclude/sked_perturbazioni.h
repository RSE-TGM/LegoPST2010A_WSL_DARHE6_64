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
   modulo sked_perturbazioni.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)sked_perturbazioni.h	5.1
*/
/*
	Questo file contiene tutte le definizioni e
 	i tipi riguardanti le perturbazioni
*/
#define SCALINO		1
#define RAMPA		2
#define RAMPA_STOP	3
#define IMPULSO		4
#define IMPULSO_STOP	5
#define UP		6
#define DOWN		7
#define NOT		8


/*

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


struct perturbazione_st {
	int tipo;     		
	int indirizzo;
	int esaminata;
	float valore_delta;
	float rateo_durata;
	float t;
	};

typedef  struct perturbazione_st PERTURBAZIONE;



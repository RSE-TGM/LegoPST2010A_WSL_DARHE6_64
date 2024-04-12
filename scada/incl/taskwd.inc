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
        TASKWD.INC 
           Contiene definizioni e strutture per la gestione del watch-dog

        14 Luglio 1992  -  GM.Furlan
*/

#include "defpub.h"

// task da controllare 
#define wd_attiper	0       // task atiper: organi e calcolate
#define wd_arc  	1       // task archivi
#define wd_acqui	2       // task acquisizione
#define wd_asinct       3       // task attivita' asincrone
#define wd_stampe       4       // task di stampa
#define wd_tabul        5       // task tabulati
#define wd_gdac         6       // task gestione dati acquisiti
#define wd_scgev        7       // task gestione messaggi video
#define wd_pas          8       // task gestione pas

#define n_task          9       // numero dei task da controllare

// stati del task
#define TRUN             1       // stato di run del task
#define TSTOP            2       // stato di stop del task
#define TS_STOP          3       // conferma dello stato di stop del task

// tipo di task
#define TPERIODICO      0       // task periodico
#define TNONPERIODICO   1       // task non periodico

// struttura watch-dog
typedef struct s_wd  {
        char  task_st;   // stato task: 1=TRUN; 2=TSTOP; 3=TS_STOP 
        char  task_per;  // flag task periodico: 0=periodico; 1=non periodico
        short cont;      // contatore di watch-dog
                     }  S_WD;

pub S_WD wd[n_task];                // tabella di watch-dog

// valori limite del contatore di watch-dog per ogni task
#define wd_max_attiper  120      
#define wd_max_arc      120      
#define wd_max_tabul    3600      

/**********************************************************************
*
*       C Header:               simula.inc
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu May 13 10:23:22 1999 %
*
**********************************************************************/
/*
        SIMULA.INC 
           Contiene definizioni e variabili generali per la gestione 
           del simulatore

        09.09.1992  -  GM.Furlan  -  Rel. 1.00
*/
#include <stdio.h>

#define SAVE    0
#define RESTORE 1

#define VERO    1
#define FALSO   0

#define APRO    1
#define CHIUDO  0

#define SVALL   0
#define CLALL   1
#define SVTRD   0
#define CLTRD   1

/*
Valori che puo' assumere riconosci_all in simacqui e simlddbs.
riconosci_all gestisce l' inserimento automatico di allarmi in
archivio, invece che in emissione, dopo LOADCI
*/
#define LOADCIRICALLDIS	        -1   // ric. automatico in startup disabled
#define LOADCIRICALLOFF	        0    // ric. autom. enabled ma off
#define LOADCIRICALLON	        1    // ric. automatico richiesto dopo LOADCI
#define LOADCIRICALLDONE        2    // ric. automatico avvenuto


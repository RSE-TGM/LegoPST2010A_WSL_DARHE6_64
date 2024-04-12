/**********************************************************************
*
*       C Header:               banco_globals.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:34:39 1997 %
*
**********************************************************************/
/*
 * banco_globals.h
 *
 * contains all the global definition
 */
#include <stdio.h>
#ifndef NO_PARENT
#define NO_PARENT    ((swidget)0)
#endif

/*
 * widgets
 */
extern swidget masterMenu;
swidget create_masterMenu();

extern swidget initialCondition;
swidget create_initialCondition();

extern swidget archiveEdit;
swidget create_archiveEdit();

extern swidget archiveSavereq;
swidget create_archiveSavereq();

extern swidget initSimulator;
swidget create_initSimulator();
/*
 * dati globali
 */
char titolo_sessione[MAX_LUN_COMMENTO];
char init_from[MAX_LUN_COMMENTO];
/*
 * dati da statistiche
 */
int stato_sim;         /* stato simulatore                */
int last_backtrack;    /* ultimo backtrack registrato(record da 1 a ...)*/
                               
int tempo_finale_impostato;	/* = 1 e' stato imposto un limite di tempo */
/********************************************************/

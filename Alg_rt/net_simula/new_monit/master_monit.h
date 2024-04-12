/**********************************************************************
*
*       C Header:               master_monit.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:40:29 1997 %
*
**********************************************************************/
/*
 * master_monit.h
 */
#ifndef MASTER_MONIT_H
#define MASTER_MONIT_H
/******************************************************************/
#include "sim_param.h"
#include "sim_types.h"
#include "dispatcher.h"

#include "bistrutt.h"

#include "option.h"
extern OPTIONS_FLAGS options;

#ifndef NO_PARENT
#define NO_PARENT ((swidget)0)
#endif
extern int inizializzazione;

extern swidget topLevelShell1;
extern swidget sessionName;
extern swidget initialCondition;
extern swidget initSimCi;
extern swidget initSimBt;
extern swidget backtrackManagement;
extern swidget optionSet;
extern swidget archiveSavereq;
extern swidget archiveEdit;
extern swidget selVarCr;
extern swidget editPert;


extern swidget create_sessionName();
extern swidget create_backtrackManagement();
extern swidget create_optionSet();
extern swidget create_selVarCr();
extern swidget create_edit_pert();

extern char titolo_sessione[MAX_LUN_COMMENTO];
extern void Popup_Menu();
extern int clear_message_list();
/******************************************************************/
#endif

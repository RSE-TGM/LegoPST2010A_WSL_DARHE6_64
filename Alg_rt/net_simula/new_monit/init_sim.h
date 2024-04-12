/**********************************************************************
*
*       C Header:               init_sim.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:38:44 1997 %
*
**********************************************************************/
/*
 * init_sim.h
 */
#ifndef INIT_SIM_H
#define INIT_SIM_H
/********************************************************************/
#include "sim_param.h"
#include "sim_types.h"
#include "dispatcher.h"

extern int read_lista_snap();
extern int display_lista_snap();
extern int read_lista_bt();
extern int display_lista_bt();
extern swidget create_previewSnap();
#define INIT_FROM_CI   0
#define INIT_FROM_BT   1
swidget initSimCi;
swidget initSimBt;
Widget tasto_load_ci;
Widget tasto_load_bt;

extern void Popup_Menu();
/********************************************************************/
#endif

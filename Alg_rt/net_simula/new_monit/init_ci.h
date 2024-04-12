/**********************************************************************
*
*       C Header:               init_ci.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:38:36 1997 %
*
**********************************************************************/
/*
 * init_ci.h
 */
#ifndef INIT_CI_H
#define INIT_CI_H
/*********************************************************/
#include "sim_param.h" 

/****** si rende parametrico dopo le modifiche allo sked 8apr97 fm
static Widget IcScrollForm[MAX_SNAP_SHOT];
static Widget IcNumber[MAX_SNAP_SHOT];
static Widget IcProtect[MAX_SNAP_SHOT];
static Widget IcDate[MAX_SNAP_SHOT];
static Widget IcDescription[MAX_SNAP_SHOT];
static Widget IcModified[MAX_SNAP_SHOT];

char nriga[MAX_SNAP_SHOT][3];
******************/

Widget *IcScrollForm;
Widget *IcNumber;
Widget *IcProtect;
Widget *IcDate;
Widget *IcDescription;
Widget *IcModified;

char *nriga;

void IcSelActivate();
int ic_sel;
/*********************************************************/
#endif

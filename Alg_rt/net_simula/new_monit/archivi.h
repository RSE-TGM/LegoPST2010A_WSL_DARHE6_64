/**********************************************************************
*
*       C Header:               archivi.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:33:27 1997 %
*
**********************************************************************/
/*
 * archivi.h
 *
 */
#ifndef ARCHIVI_INCLUDED
#define ARCHIVI_INCLUDED   
/*************************************************************/
#include "bistrutt.h"
/*************************************************************/

int disco_libero;     /* disco disponibile per l' operazione */
int disco_richiesto;     /* disco necessario al salvataggio  */
float archsavetinit;     /* tempo inizio richiesto           */
float archsavetfin;      /* tempo finale richiesto           */
/*************************************************************/
char comm_arch_save[MAX_LUN_COMMENTO]; /* commento archivio salvato */
/*************************************************************/
ARCHIVE_REQ archive_req;                /* struttura per la richiesta */
/*************************************************************/
extern Widget areaMessaggi;
/*************************************************************/
#endif

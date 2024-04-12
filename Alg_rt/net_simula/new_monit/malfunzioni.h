/**********************************************************************
*
*       C Header:               malfunzioni.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Fri Jun  6 16:38:14 1997 %
*
**********************************************************************/
/*
 * malfunzioni.h
 */
#ifndef MALFUNZIONI_H
#define MALFUNZIONI_H
/************************************************************/
#define MALF_SCEN_FILE		".scenariMalf"
#define FREM_SCEN_FILE		".scenariFrem"

#define	MALFUNZIONI		   0    /* flag per attivazione malfunzioni  */
#define  FUNZIONI_REMOTE 	1    /* flag per attivazione frem         */
#define  SOMMARIO_MALF 		2    /* flag per attivazione sommario malf*/
#define  SOMMARIO_FREM 		3    /* flag per attivazione sommario frem*/

#define  MAX_CODICE_MALF SOMMARIO_FREM /* per offset filtri          */

/************************************************************/
#endif

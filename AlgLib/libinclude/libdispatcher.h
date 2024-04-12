/**********************************************************************
*
*       C Header:               libdispatcher.h
*       Subsystem:              3
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Oct 18 17:23:25 2005 %
*
**********************************************************************/
/*
   modulo libdispatcher.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)libdispatcher.h	5.1
*/
/* 
	Include della libreria libdispatcher:
		la libreria contiene le chiamate per poter comunicare 
		con il processo sked attraverso il processo dispatcher.
*/


int     SD_aggancio ();
int     SD_backtrack ();
int     SD_chiusura ();
int     SD_editic ();
int     SD_freeze ();
int     SD_goup ();
int     SD_inizializza ();
int     SD_loadic ();
int     SD_removeic ();
int     SD_run ();
int     SD_saveic ();
int     SD_sgancio ();
int     SD_stepcr ();
int     SD_stop ();
int     SD_timescaling ();
int     SD_maxsimtime ();
int     from_dispatcher ();
int     to_dispatcher ();

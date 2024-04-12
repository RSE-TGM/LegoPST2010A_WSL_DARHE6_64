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
   modulo statistics.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)statistics.h	5.1
*/
#ifndef _statistics_h
#define _statistics_h

#if defined VMS
typedef struct {short    buflen,           /* Length of output buffer */
                         itmcode;          /* Item code */
                void     *buffer;          /* Buffer address */
                void     *retlen;          /* Return length address */
                               } ITMLST;   /* Layout of item-list elements */
#endif

#define  START_TIME    700000000     /* shift convenzionale della data   */

typedef struct {
        double start_process;   /* t (in millisec) partenza processo */
	double last_call;       /* t (in millisec) ultima richiesta
			  	   statistiche */
	double user_time;       /* percentuale di tempo di CPU in chiamate 
			 	   utente dall'ultima richiesta di statistiche*/
	double tot_user_time;   /* totale tempo di CPU in millisec. utilizzato
				   in chiamate utente */
	double max_user_time;   /* massima percentuale di tempo di CPU
				   in chiamate utente */
	double ave_user_time;   /* media delle percentuali di tempo di CPU
                                   in chiamate utente */
	double first_user_time;
        double system_time;     /* percentuale di tempo di CPU in chiamate
                                   di sistema  dall'ultima richiesta 
				   di statistiche*/
        double tot_system_time; /* totale tempo di CPU in millisec. utilizzato
                                   in chiamate di sistema */
        double max_system_time; /* massima percentuale di tempo di CPU
                                   in chiamate di sistema */
        double ave_system_time; /* media delle percentuali di tempo di CPU
                                   in chiamate di sistema */
	double first_system_time;
	double io_oper;         /* numero di blocchi di I/O dall'ultima 
			           richiesta di statistiche*/
	double tot_io_oper;     /* totale di blocchi di I/O dall'ultima
                                   richiesta di statistiche*/
	double max_io_oper;     /* massimo numero di blocchi di I/O fra
				   due successive chiamate di richiesta
				   di statistiche         */
	double ave_io_oper;     /* media dei numero di blocchi di I/O fra
                                   due successive chiamate di richiesta
                                   di statistiche         */
        double first_io_oper;
        }  STATISTICS;

int init_statistics(STATISTICS *);
int get_statistics(STATISTICS *);
int print_statistics(STATISTICS *);

#endif

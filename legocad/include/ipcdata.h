/**********************************************************************
*
*       C Header:               ipcdata.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:02:18 1996 %
*
**********************************************************************/
/*** ipcdata.h ***/

/* Buffo Massimo, Calleri Nicola 11/06/1992 */

#define BUFFER_SIZE	256

#define NOT_OK	1
#define OK_MESG	0

typedef char byte;

typedef struct {
                  char applicativo[8];
                  int  codice;
                  int  lunghezza;
               } header_mesg;

/*** fine ipcdata.h ***/

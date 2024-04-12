/**********************************************************************
*
*       C Header:               MarteP.h
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Oct 21 15:23:06 2002 %
*
**********************************************************************/
#ifndef _MarteP_h
#define _MarteP_h

#include <Marte/Marte.h>

typedef struct _MarteMailbox {
	pthread_cond_t  condition;
	pthread_mutex_t mutex;
	int valore;
	} MarteMailbox;

MarteMailbox *PuntMarteMailbox;

#define MAX_MAILBOX     50
#define REAL_TIME_CLOCK     55  /* millisecondi */

#endif

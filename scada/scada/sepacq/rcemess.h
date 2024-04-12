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
	RceMess.h

	Contiene gli indici dei messaggi per la stampa continua e
	perturbografica degli Rce e la struttura del messaggio

*/
#include "rce.h"

#define  rceprnc		1				// stampa continua
#define  rceprnp		2				// stampa perturbografica
/*
	definizione struttura  Rce
*/
typedef struct s_strce {
					short mess;
               short gruppo;
					S_RCE rce;
					} S_STRCE;

/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif

/*
		AGGIORNAMENTO VERSO SUPERVISIONE

	Ver. 1.0		7/1/'93

*/

#include <pthread.h>
#include <stdio.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
#endif
#if defined VMS
# include "vmsipc.h"
#endif
#include "sim_param.h" 
#include "libnet.h"
#include "dispatcher.h" 
#include "agg_scada.h"	/* include lato supervisione */

int     ack_ssc ();
int     ack_send ();


int     ack_ssc (fp)
int     fp;
{
    SM_DIAGNO msg_diag;
short   codice_msg;
int     tipo_msg;

    /* attende ack */
    readn (fp, &msg_diag, sizeof (SM_DIAGNO));

    /* converte i campi del messaggio */
    memcpy (&codice_msg,
	    converti_short_f (&msg_diag.hea.mess, RICEZIONE, FORM_DATI),
	    sizeof (short));
    if (codice_msg != DIAGNO)
	printf ("AGG_SCADA:attesa ack, ricevuto mess. indesiderato [%d]\n",
		codice_msg);
    memcpy (&tipo_msg,
	    converti_int_f (&msg_diag.tipo, RICEZIONE, FORM_DATI),
	    sizeof (int));
    switch (tipo_msg)
    {
	case NOMESS: 
	    {
		printf ("AGG_SCADA:attesa ack, NOMESS\n");
		break;
	    }
	case OK: 
	    {
		//printf ("AGG_SCADA:attesa ack, OK\n");
		break;
	    }
	case NOSTART: 
	    {
		printf ("AGG_SCADA:attesa ack, NOSTART\n");
		break;
	    }
	case NOSTOP: 
	    {
		printf ("AGG_SCADA:attesa ack, NOSTOP\n");
		break;
	    }
	case NOLOADCI: 
	    {
		printf ("AGG_SCADA:attesa ack, NOLOADCI\n");
		break;
	    }
	case NOINITDB: 
	    {
		printf ("AGG_SCADA:attesa ack, NOINITDB\n");
		break;
	    }
	case NOALT: 
	    {
		printf ("AGG_SCADA:attesa ack, NOALT\n");
		break;
	    }
	case NORUN: 
	    {
		printf ("AGG_SCADA:attesa ack, NORUN\n");
		break;
	    }
	case NODBUPD: 
	    {
		printf ("AGG_SCADA:attesa ack, NODBUPD\n");
		break;
	    }
	case NOSIMTIME: 
	    {
		printf ("AGG_SCADA:attesa ack, NOSIMTIME\n");
		break;
	    }
	case NOFREEZE: 
	    {
		printf ("AGG_SCADA:attesa ack, NOFREEZE\n");
		break;
	    }
	case NOBKTKON: 
	    {
		printf ("AGG_SCADA:attesa ack, NOBKTKON\n");
		break;
	    }
	case NOBKTKOFF: 
	    {
		printf ("AGG_SCADA:attesa ack, NOBKTKOFF\n");
		break;
	    }
	case NOLOADBT: 
	    {
		printf ("AGG_SCADA:attesa ack, NOLOADBT\n");
		break;
	    }
	case NOREPON: 
	    {
		printf ("AGG_SCADA:attesa ack, NOREPON\n");
		break;
	    }
	case NOREPOFF: 
	    {
		printf ("AGG_SCADA:attesa ack, NOREPOFF\n");
		break;
	    }
	case NOSTEP: 
	    {
		printf ("AGG_SCADA:attesa ack, NOSTEP\n");
		break;
	    }
	default: 
	    {
		printf ("AGG_SCADA : tipo ack sconosciuto\n");
	    }
    }
}



int     ack_send (fp)
int     fp;
{
    SM_DIAGNO msg_diag;
short   codice_msg;
int     tipo_msg;
short   size;

    codice_msg = CFG;
    tipo_msg = OK;
    size = sizeof (SM_DIAGNO);

    memcpy (&msg_diag.hea.mess,
	    converti_short_f (&codice_msg, TRASMISSIONE, FORM_DATI),
	    sizeof (short));
    memcpy (&msg_diag.hea.nodo,
	    converti_short_f (&size, TRASMISSIONE, FORM_DATI),
	    sizeof (short));
    memcpy (&msg_diag.tipo,
	    converti_int_f (&tipo_msg, TRASMISSIONE, FORM_DATI),
	    sizeof (int));

    /* invia ack */
    writen (fp, &msg_diag, sizeof (SM_DIAGNO));

}

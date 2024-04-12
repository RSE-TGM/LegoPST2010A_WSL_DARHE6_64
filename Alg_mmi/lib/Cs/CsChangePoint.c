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
   modulo CsChangePoint.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)CsChangePoint.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)CsChangePoint.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#ifndef VMS
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#else
#include <vmsipc.h>
#endif

#include <sim_param.h>
#include <Cs/Cs.h>

/*
    Prepara e spedisce il messaggio per la modifica di un punto in una pagina
*/
int CsChangePoint(int coda,int id_shm, int posizione, int tipo, int indirizzo)
{
MSG_CHANGE_POINT_MMI msg;


    msg.mtype  = CHANGE_POINT_MMI;
    msg.id_shm = id_shm;
    msg.posizione = posizione;
    msg.indirizzo = indirizzo;
    msg.tipo = tipo;
    msg_snd(coda,&msg,sizeof(MSG_CHANGE_POINT_MMI)-sizeof(long),!IPC_NOWAIT);

    return(1);
}

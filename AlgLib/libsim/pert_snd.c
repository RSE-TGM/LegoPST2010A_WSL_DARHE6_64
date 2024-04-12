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
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)pert_snd.c	5.1\t11/7/95";
/*
   modulo pert_snd.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)pert_snd.c	5.1
*/
# include <stdio.h>
# include <errno.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
#endif
#if defined VMS || defined HELIOS
# include "vmsipc.h"
#endif
# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "comandi.h"
#include <Rt/RtMemory.h>

int pert_snd(int id_msg_pert,int tipo,int indirizzo,
		float valore_delta,float rateo_durata,
		float period,float phase,float meanvalue,
		float wide,float t_null_var,float t)
{
int tipo_ritorno;
MSG_PERT messaggio;

printf("pert_snd id = %d tipo = %d\n",id_msg_pert,tipo);
/* riempimento struttura messaggio  */
#if defined REPLAY
messaggio.perturbazione.runtime_replay=PERT_RUN_TIME;
#endif
messaggio.perturbazione.tipo=tipo;
messaggio.perturbazione.indirizzo=indirizzo;
messaggio.perturbazione.valore_delta=valore_delta;
messaggio.perturbazione.rateo_durata=rateo_durata;
messaggio.perturbazione.period=period;
messaggio.perturbazione.phase=phase;
messaggio.perturbazione.meanvalue=meanvalue;
messaggio.perturbazione.wide=wide;
messaggio.perturbazione.t_null_var=t_null_var;
messaggio.perturbazione.t=t;

messaggio.mtype=tipo;

msg_snd(id_msg_pert,&messaggio,sizeof(TIPO_PERT),!IPC_NOWAIT);

return(1);
}


int pert_snd_replay(int id_msg_pert,int tipo,int indirizzo,
		float valore_delta,float rateo_durata,
		float period,float phase,float meanvalue,
		float wide,float t_null_var,float t)
{
int tipo_ritorno;
MSG_PERT messaggio;

/* riempimento struttura messaggio  */
#if defined REPLAY
messaggio.perturbazione.runtime_replay=PERT_REPLAY;
#endif
messaggio.perturbazione.tipo=tipo;
messaggio.perturbazione.indirizzo=indirizzo;
messaggio.perturbazione.valore_delta=valore_delta;
messaggio.perturbazione.rateo_durata=rateo_durata;
messaggio.perturbazione.period=period;
messaggio.perturbazione.phase=phase;
messaggio.perturbazione.meanvalue=meanvalue;
messaggio.perturbazione.wide=wide;
messaggio.perturbazione.t_null_var=t_null_var;
messaggio.perturbazione.t=t;

messaggio.mtype=tipo;

msg_snd(id_msg_pert,&messaggio,sizeof(TIPO_PERT),!IPC_NOWAIT);

return(1);
}

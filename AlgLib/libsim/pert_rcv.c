/**********************************************************************
*
*       C Source:               pert_rcv.c
*       Subsystem:              3
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 11:36:30 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: pert_rcv.c-3 %  (%full_filespec: pert_rcv.c-3:csrc:3 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)pert_rcv.c	5.1\t11/7/95";
/*
   modulo pert_rcv.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)pert_rcv.c	5.1
*/
# include <stdio.h>
# include <errno.h>
#include <string.h>

# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
#include <sys/msg.h>

# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "comandi.h"
# include "sked.h"
#include <Rt/RtMemory.h>
#include <Rt/RtDbPunti.h>
#include <Rt/RtErrore.h>


extern int fp_com[MAX_MODEL];

extern int nmod;                /* numero di modelli */

extern char *fp_app[MAX_MODEL];
extern int *fp_size[MAX_MODEL];

extern int stato_sked;
extern int tipo_sked;

extern RtDbPuntiOggetto dbpunti;

extern int ins_area_pert_att(int, int, float, float,
        float, float, float, float, float, float);


int pert_rcv(id_msg_pert)
int id_msg_pert;
{
int tipo_ritorno;
MSG_PERT messaggio_pert;
PACCHETTO_NET pacchetto_net;
int i;
int modello;




while((msg_rcv(id_msg_pert,&messaggio_pert,sizeof(TIPO_PERT),(long)(-(OFFSET_PERT)),
        IPC_NOWAIT,TIMEOUT_INF))>0)
        {
#if defined REPLAY
	 /* se lo stato e' == da STATO_REPLAY scoda le perturbazioni
	    del tipo PERT_REPLAY ed elimina le altre, se lo stato e'
	    diverso da STATO_REPLAY esamina le pert. del tipo PERT_RUN_TIME
	    eliminando le altre
	  */
	if(tipo_sked==MASTER)
		{
        	if((stato_sked==STATO_REPLAY)&&
               	   (messaggio_pert.perturbazione.runtime_replay==PERT_RUN_TIME))
			continue;
        	if((stato_sked!=STATO_REPLAY)&&
                   (messaggio_pert.perturbazione.runtime_replay==PERT_REPLAY))
			continue;
		}
#endif
	modello = RtDbPGetModelFromInd(dbpunti,
		messaggio_pert.perturbazione.indirizzo);
	if(modello < 0)
		return(-1);
printf("ricevuta pert modello=%d   tipo=%d ind=%d\n",
        modello,
        messaggio_pert.perturbazione.tipo,
        messaggio_pert.perturbazione.indirizzo);
        if(fp_com[modello]==0)
            {
            /* inserisce la perturbazione */
            ins_area_pert_att( messaggio_pert.perturbazione.tipo,
                        messaggio_pert.perturbazione.indirizzo,
                        messaggio_pert.perturbazione.valore_delta,
                        messaggio_pert.perturbazione.rateo_durata,
                        messaggio_pert.perturbazione.period,
                        messaggio_pert.perturbazione.phase,
                        messaggio_pert.perturbazione.meanvalue,
                        messaggio_pert.perturbazione.wide,
			messaggio_pert.perturbazione.t_null_var,
                        messaggio_pert.perturbazione.t);
             tipo_ritorno=messaggio_pert.perturbazione.indirizzo+
                        messaggio_pert.mtype;
             messaggio_pert.mtype=tipo_ritorno;
             }
           else
             {
printf("spedisco la perturbazione in rete\n");
             /* spedisce la perturbazione in rete  */
             /* ricerca un identificatore per la risposta */
             for(i=0;i<nmod;i++)
                if(fp_com[i]==0)
                        break;
             /*messaggio_pert.perturbazione.nodo_sorgente=i;*/
             pacchetto_net.header_net.sorg=(-1);
             pacchetto_net.header_net.dest=(-1);
             pacchetto_net.header_net.tasksorg=(-1);
             pacchetto_net.header_net.taskdest=(-1);
             pacchetto_net.header_net.tipo=DATIPERT;
             pacchetto_net.header_net.flag=(-1);
             pacchetto_net.header_net.lun=sizeof(MSG_PERT);
             pacchetto_net.header_net.codice=(-1);
             memcpy(&pacchetto_net.dato[0],&messaggio_pert,
                        sizeof(MSG_PERT));
	     i = RtDbPGetModelFromInd(dbpunti,
		messaggio_pert.perturbazione.indirizzo);
	     if(i < 0)
			return(-1);
             /* scrive il pacchetto nel buffer di rete  */

        memcpy(&fp_app[i][(*(fp_size[i]))],&pacchetto_net,
                sizeof(HEADER_NET)+pacchetto_net.header_net.lun);

        *fp_size[i]= *fp_size[i]+sizeof(HEADER_NET)+
                        pacchetto_net.header_net.lun;
             }
        }
return(1);
}

int pert_rcv_null(id_msg_pert)
int id_msg_pert;
{
MSG_PERT messaggio_pert;

while((msg_rcv(id_msg_pert,&messaggio_pert,sizeof(TIPO_PERT),(long)(-(OFFSET_PERT)),
        IPC_NOWAIT,TIMEOUT_INF))>0);

return(1);
}

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
# include <stdio.h>
# include <errno.h>
# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "comandi.h"
#include <Rt/RtMemory.h>



/*
    Da chiarire se devo passare anche il type.
    Al momento no, infatti mi basta vedere che esista 
    gia' la malfunzione sulla variabile.
*/
int pert_malfunction_stop(int id_msg_pert,int indirizzo,float tempo)
{
if(pert_snd(id_msg_pert,PERT_MALFUNCTION_STOP,indirizzo,
		0.,0.,0.,0.,0.,0.,0.,tempo)==1)
	return(1);
else
	return(0);
}

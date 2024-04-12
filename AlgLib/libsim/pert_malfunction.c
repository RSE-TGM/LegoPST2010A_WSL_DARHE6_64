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



int pert_malfunction(int id_msg_pert,int indirizzo,float target,
		     float type,float tempo)
{
int typeint;

typeint=type;
type=typeint;
if(pert_snd(
         id_msg_pert,PERT_MALFUNCTION,indirizzo,target,0.,
		0.,0.,0.,0.,type,tempo)==1)
        return(1);
else
        return(0);
}

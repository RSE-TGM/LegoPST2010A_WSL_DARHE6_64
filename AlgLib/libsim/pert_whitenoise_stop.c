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
static char SccsID[] = "@(#)pert_whitenoise_stop.c	5.1\t11/7/95";
/*
   modulo pert_whitenoise_stop.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)pert_whitenoise_stop.c	5.1
*/
# include <stdio.h>
# include <errno.h>
# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "comandi.h"
#include <Rt/RtMemory.h>



int pert_whitenoise_stop(int id_msg_pert,int indirizzo,float tempo)
{
if(pert_snd(id_msg_pert,PERT_WHITENOISE_STOP,indirizzo,
		0.,0.,0.,0.,0.,0.,0.,tempo)==1)
	return(1);
else
	return(0);
}

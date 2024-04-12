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
/*
        Fine sezione per SCCS
*/
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include <Marte/MarteP.h>
#include <Marte/TaskMarte.h>


void tas(int indice)
{
extern TCB *PuntTcb;
int pos_ele;

for(pos_ele=0;pos_ele<NUM_ELE_TASK_MARTE;pos_ele++)
        if(ele_task_marte[pos_ele].codice == indice)
                break;
if(pos_ele == NUM_ELE_TASK_MARTE)
        return;
ActivateThread((pthread_startroutine_t)ele_task_marte[pos_ele].procedura,
                        ele_task_marte[pos_ele].nome, 
			ele_task_marte[pos_ele].prio,indice);

return;



SetBookState(indice,1);
pthread_mutex_lock(&(PuntTcb[indice].mutex));
pthread_cond_signal(&(PuntTcb[indice].condition));
pthread_mutex_unlock(&(PuntTcb[indice].mutex));
return;
}

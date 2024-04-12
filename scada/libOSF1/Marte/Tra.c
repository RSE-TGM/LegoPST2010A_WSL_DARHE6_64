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


int tra(int indice, int valore)
{
if(valore ==0)
	return(1);
pthread_mutex_lock(&(PuntMarteMailbox[indice].mutex));
if(PuntMarteMailbox[indice].valore !=0)
	{
	pthread_mutex_unlock(&(PuntMarteMailbox[indice].mutex));
	return(2);
	}
PuntMarteMailbox[indice].valore = valore;
pthread_cond_signal(&(PuntMarteMailbox[indice].condition));
pthread_mutex_unlock(&(PuntMarteMailbox[indice].mutex));
pthread_yield();
return(0);
}

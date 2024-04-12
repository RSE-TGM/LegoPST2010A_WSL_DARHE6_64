/**********************************************************************
*
*       C Source:               sem_op.c
*       Subsystem:              3
*       Description:
*       %created_by:    mauric %
*       %date_created:  Thu Feb 12 13:30:47 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sem_op.c-1.1.1 %  (%full_filespec: sem_op.c-1.1.1:csrc:3 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sem_op.c	5.1\t11/7/95";
/*
   modulo sem_op.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sem_op.c	5.1
*/
# include "libipc.h"

void sem_op(id,value)
int id;
int value;
{
int valsem;

#if defined UNIX
if((op_op[0].sem_op=value)==2)
	perror("Impossibile avere valore == 0");
valsem=semctl(id,0,GETVAL,0);

if(semop(id,&op_op[0],1)<0)
{
        printf(" id %d  value %d valore %d \n",id,value,valsem);
	perror("Errore di sem_op");
}
#endif
}


/************************************************************/
/*                                                          */
/*   Funzione che consente di eseguire operazioni sul       */
/*   semaforo dedicato al controllo delle code al           */
/*   dispatcher.                                            */
/*                                                          */
/************************************************************/
void sem_op_dispatcher(id,value)
int id;
int value;
{
int valsem;

#if defined UNIX
if((op_op_disp[0].sem_op=value)==2)
	perror("Impossibile avere valore == 0");
valsem=semctl(id,0,GETVAL,0);

if(semop(id,&op_op_disp[0],1)<0)
{
        printf(" id %d  value %d valore %d \n",id,value,valsem);
	perror("Errore di semop");
}
#endif
}


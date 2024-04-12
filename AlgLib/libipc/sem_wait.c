/**********************************************************************
*
*       C Source:               sem_wait.c
*       Subsystem:              3
*       Description:
*       %created_by:    mauric %
*       %date_created:  Thu Feb 12 13:42:30 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: sem_wait.c-2 %  (%full_filespec: sem_wait.c-2:csrc:3 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)sem_wait.c	5.1\t11/7/95";
/*
   modulo sem_wait.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sem_wait.c	5.1
*/

# include "libipc.h"

void sem_wait(id)
int id;
{
#if defined UNIX
sem_op(id,(-1));
#endif
}



/************************************************************/
/*                                                          */
/*   Funzione che consente di decrementare il semaforo      */
/*   dedicato al controllo delle code al dispatcher ogni    */
/*   volta che viene prelevato un messaggio su di esse.     */
/*                                                          */
/************************************************************/
void sem_wait_disp(id)
int id;
{
#if defined UNIX
sem_op_dispatcher(id,(-1));
#endif
}





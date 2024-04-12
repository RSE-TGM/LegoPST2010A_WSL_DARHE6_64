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
/*******************************************************
*
*	interfc()
*	
*	Simula la chiamata all'interprete del POL
*	assembler chiamando l'interprete C.
*
*******************************************************/
#include <osf1.h>
#include <malloc.h>

#include "eqschpas.inc"
#include "stschpas.inc"
#include "interpol.inc"
#include "fileop.inc"

void interfc(struct SCB *scb,struct SCHEDULER *s_interp)
{
	S_INTERP s;
	/* Inizializzazione campi della struttura e allocazione dello stack */
	s.dbc=(char *)s_interp->buf_dbl;
	s.dbs=(short *)s_interp->buf_dbl;
	s.pc=(short *)((char *)s_interp->buf_pr+scb->ind_cod);
	s.inc=s_interp->buf_pr;
	s.siniz=(int *)malloc(n_tstack);
	s.stk=s.siniz;
	s.sfine=(int *)((char *)s.siniz+n_tstack);

	/* Chiamata all'interprete C */
	interp(&s);

	/* Libera la memoria */
	free(s.siniz);
}


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
static char SccsID[] = "@(#)pf_address.c	5.3\t11/30/95";
/*
   modulo pf_address.c
   tipo 
   release 5.3
   data 11/30/95
   reserved @(#)pf_address.c	5.3
*/
# include <stdio.h>
# include <string.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
#endif
#if defined VMS
#include "vmsipc.h"
#endif
# include "sim_param.h"		/* parametri generali LEGO          */
# include "sim_types.h"		/* tipi e costanti LEGO             */
# include "pf_macro.h"          /* macro per switch VMS-UNIX    */


int             tot_variabili;	/* numero totale variabili dei modelli      */
VARIABILI      *variabili;	/* database variabili di tutti i modelli    */
char           *ind_sh_top;	/* puntatore inizio shared memory sh_var */
int             id_sh;		/* identificatore sh_var */
FLAG_SEL        flag_sel = SEL_REG;
int             nu_var_sel;

pf_address()
{
  char           *nome_file;
  int             shr_usr_key;	/* chiave utenti shared  */
  int             k;
  int             j;
  FILE           *fp;

  /* costruzione o aggancio sh_var */
  costruisci_var(&ind_sh_top, &variabili, &id_sh);

  /* ricerca tot_variabili */
  tot_variabili = numero_variabili(ind_sh_top);

  /* lettura della selezione dal file recorder.var */
  nome_file = (char *) malloc(sizeof(char) * 50);
  strcpy(nome_file, "recorder.edf");
  legge_sel(nome_file);
  free(nome_file);
}

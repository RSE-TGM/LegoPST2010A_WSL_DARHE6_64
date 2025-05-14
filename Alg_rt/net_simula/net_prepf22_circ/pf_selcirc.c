/**********************************************************************
*
*       C Source:               pf_selcirc.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug 29 14:37:31 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: pf_selcirc.c-9 %  (%full_filespec: pf_selcirc.c-9:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)pf_selcirc.c	5.2\t11/30/95";
/*
   modulo pf_selcirc.c
   tipo 
   release 5.2
   data 11/30/95
   reserved @(#)pf_selcirc.c	5.2
*/
# include <stdio.h>
# include <string.h>
#include <errno.h>
#if defined VMS
#include <types.h>
#include <stat.h>
# include <unixio.h>
# include <file.h>
#endif   /* VMS */
# include <Rt/RtDbPunti.h>
# include <Rt/RtErrore.h>

# include "sim_param.h"		/* parametri generali LEGO       */
# include "sim_types.h"		/* tipi di uso LEGO              */
# include "sim_ipc.h"		/* parametri per semafori        */
# include "f22_circ.h"
# include "pf_macro.h"          /* macro per switch VMS-UNIX    */


RtDbPuntiOggetto dbpunti;

/* ************** Definizione variabili globali ******************** */

int             num_var_graf;	/* numero variabili selezionate per f22      */
int             tot_variabili;	/* numero variabili di tutti i modelli       */
int             variabili_registrate; /* numero delle variabili effettivamente
				     registrate                              */
int            *iout_graf;	/* indirizzi variabili per file f22          */
extern VARIABILI *variabili;

/*
 * Dichiarazioni file 
 */
extern FILE    *fpda;		/* f22 circolare registrazione dati    */
F22CIRC_HD      header;		/* Struttura degli header              */

int             append_mode;
extern int      num_campioni; 
extern int      num_var; 

int     ora(int*, int*, int*);
int     data(int*, int*, int*);


/*
 * Crea il file f22circ.hd e f22circ.dat e f22circ.var (per VMS). 
 */
int pf_selcirc()
{
F22CIRC_T       istante;	/* Istante del campione salvato */
F22CIRC_VAR     descr;
float          *campioni;
int             i, j;
int             conta = 0;
int             var_selezionate;
int ore,minuti,secondi,giorno,mese,anno;
HEADER_REGISTRAZIONI hreg;
int  offheader;

#if defined F22_APPEND
  if ( fpda = fopen("f22circ.dat", "r") ) 
  {
    append_mode = 1;
    fclose(fpda);
  } else
    append_mode = 0;
#else
  append_mode = 0;
#endif   /* F22_APPEND */



  /* Calcolo del numero di variabili grafiche */
  num_var_graf = 0;
  for (j = 1; j <= tot_variabili; j++)
    if (variabili[j - 1].typ == GRAF_SEL)
      num_var_graf = num_var_graf + 1;


  /* Inserisce in SHM di num_var_graf */
  if( num_var > num_var_graf )
     RtDbPPutNumCr(dbpunti,num_var_graf);
  else
     RtDbPPutNumCr(dbpunti,num_var);

  /* calcolo del numero di variabili effettivamente registrate sul file */
#if defined F22_ALLOC || defined PIACENZA
  variabili_registrate = num_var;
#else
  variabili_registrate = num_var_graf ;
#endif

 offheader = sizeof(HEADER_REGISTRAZIONI)+sizeof(F22CIRC_HD)+
             variabili_registrate*sizeof(F22CIRC_VAR);

#if defined DEBUG_PF22 
 printf("net_prepf22_circ Fase di calcolo dei parametri dimensionali :\n");
 printf("\t\t append_mode=%d num_var=%d max_campioni=%d\n",
         append_mode,num_var,num_campioni);
 printf("\t\t num_var_graf=%d variabili_registrate=%d tot_variabili=%d \n",
         num_var_graf,variabili_registrate,tot_variabili);
 printf("\t\t offheader=%d size totale file ===> %d \n",
         offheader,(num_var+1)*sizeof(float)*num_campioni+offheader);
#endif

/* Allocazione vettore indirizzi variabili */
  iout_graf = (int *) malloc(variabili_registrate * sizeof(int));
  for (i = 0; i < variabili_registrate; i++)
    iout_graf[i] = -1;

  if (append_mode == 0)
  {
    fpda = (FILE *) fopen("f22circ.dat", "w");
  } else
  {
    fpda = (FILE *) fopen("f22circ.dat", "r+");
  }

/*
    Se tot_variabili supera variabili_registrate (num_var)=header.num_var_graf
    il ciclo di caricamento per iout_graf viene  limitato al valore di
    variabili_registrate anziche' tot_variabili perche' se _NUM_VAR e'
    minore di tot_variabili si limita la registrazione alle prime _NUM_VAR
    variabili.
*/
  RtDbPGetHeaderReg(dbpunti,&hreg);
#if defined DEBUG_PF22
  printf("net_prepf22_circ legge da SHM i parametri %d %d %d %d %d %d %d\n",
          hreg.simulator.max_snap_shot,
          hreg.simulator.max_back_track,
          hreg.simulator.max_campioni,
          hreg.simulator.num_var,
          hreg.simulator.max_pertur,
          hreg.simulator.spare_snap,
          hreg.simulator.pert_clear);
#endif

  if (append_mode == 1)
  {
    i = 0;
    for (j = 0; j < tot_variabili; j++)
    {
      if (variabili[j].typ == GRAF_SEL)
      {
	iout_graf[i] = variabili[j].addr;
	i++;
        if ( i==variabili_registrate )
           {
           fprintf(stderr,
"\t ATTENZIONE effettivamente selezionabili %d variabili grafiche, non'%d \n",
                   variabili_registrate,tot_variabili);
           break;
           }
      }
    }
    return (1);
  }


  /* Scrittura header su f22circ.hd */
  RtDbPGetHeaderReg(dbpunti,&hreg);

#if defined DEBUG_PF22
  printf("\t\t Scrivo pf22 hreg %d %d %d %d %d %d %d\n",
          hreg.simulator.max_snap_shot,
          hreg.simulator.max_back_track,
          hreg.simulator.max_campioni,
          hreg.simulator.num_var,
          hreg.simulator.max_pertur,
          hreg.simulator.spare_snap,
          hreg.simulator.pert_clear);
#endif

  scrivi(&hreg, sizeof(HEADER_REGISTRAZIONI), 1, fpda);
  fluscia(fpda); /* mauric */

  header.num_campioni = num_campioni;
  header.num_var_graf = variabili_registrate ;
  header.p_iniz = 0;
  header.p_fine = 0;
  ora(&ore,&minuti,&secondi);
  header.ore = ore;
  header.minuti = minuti;
  header.secondi = secondi;
  data(&giorno,&mese,&anno);
  header.giorno = giorno;
  header.mese = mese;
  header.anno = anno;


  scrivi(&header, sizeof(F22CIRC_HD), 1, fpda);
  fluscia(fpda); /* mauric */

  /* Scrittura nomi variabili e descrizione */
  i = 0;
  conta = 0;
  for (j = 0; j < tot_variabili; j++)
  {
    if (variabili[j].typ == GRAF_SEL)
    {
      conta++;
      if (conta > variabili_registrate )
      {
	fprintf(stderr,"ATTENZIONE scrivo %d anziche' %d variabili grafiche\n",
	       conta-1, num_var_graf);
        break;
      }
      iout_graf[i] = variabili[j].addr;
      strcpy(descr.nomevar,variabili[j].nome);
      strncpy(descr.descvar, variabili[j].descr, 70);
      descr.descvar[70] = '\0';
      scrivi(&descr, sizeof(F22CIRC_VAR), 1, fpda);
      fluscia(fpda); /* mauric */
      i++;
    }
  }
  var_selezionate = i;

/*
#if defined DEBUG_PF22
printf("net_prepf22_circ Fase di scrittura header:\n");
printf("\t\t header.num_var_graf=%d variabili_reg.=%d var_selez.=%d\n",
         header.num_var_graf,variabili_registrate,var_selezionate);
#endif
*/

#if defined F22_ALLOC || defined PIACENZA
  strcpy(descr.nomevar, "libera  ");
  strcpy(descr.descvar, "   ---   ");
  /* Scrittura della parte rimanente delle descrizioni */
  j = 0;
  for (i = var_selezionate; i < variabili_registrate; i++)
  {
    scrivi(&descr, sizeof(F22CIRC_VAR), 1, fpda);
    fluscia(fpda);
    j++;
  }
  /* printf("Ho messo la struttura vuota a %d variabili\n", j); */
#endif  /* F22_ALLOC */

  fluscia(fpda);


#if defined F22_ALLOC || defined PIACENZA
  /* Allocazione statica del file f22circ.dat */
  campioni = (float *) calloc(variabili_registrate+1, sizeof(float));
  scrivi(campioni, sizeof(float), (variabili_registrate+1) *  header.num_campioni, fpda);
  fluscia(fpda);
  free(campioni);

#endif /* F22_ALLOC */

}/* Fine File */

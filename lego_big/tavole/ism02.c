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

/* **************************************************************** *
 * *** ROUTINES PER L'INIZIALIZZAZIONE DELLE TAVOLE DEL VAPORE  *** *
 * **************************************************************** */

# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <math.h>


/* ************  DEFINIZIONE VARIABILI GLOBALI ***************** */

extern float (*valda)[];                  /* dati numerici TAVOLE       */

/* ************************************************************** */

ism02_(lreg,jvalpt,vet)

   int *lreg,*jvalpt;
   float (*vet)[];

   {
    int jval;

    for (jval=1; jval<=(*lreg); jval++)
         (*valda)[(*jvalpt)+jval-1] = (*vet)[jval-1];

   }   /* FINE DELLA ism02 */

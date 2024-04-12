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
static char SccsID[] = "@(#)sked_pacchetti.c	5.1\t11/7/95";
/*
   modulo sked_pacchetti.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)sked_pacchetti.c	5.1
*/
#include <stdio.h>
#include <string.h>
#include "sim_param.h"
#include "sim_types.h"
#include "comandi.h"
#include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>

extern COLLEGAMENTO collegamento[MAX_MODEL][MAX_MODEL];
extern RtDbPuntiOggetto dbpunti;
PACCHETTO_NET   pacchetto_net;




costruisci_pacchetto(modello_a, modello_b, tab)
   int             modello_a;
   int             modello_b;
   int             tab;
{
   int             i;
   int             dimensione;

   dimensione = collegamento[modello_b][modello_a].numero_collegamenti;
   pacchetto_net.header_net.sorg = (-1);	/* momentaneamente a -1 */
   pacchetto_net.header_net.dest = (-1);	/* momentaneamente a -1 */
   pacchetto_net.header_net.tasksorg = modello_a;
   pacchetto_net.header_net.taskdest = modello_b;
   pacchetto_net.header_net.tipo = DATISIM;
   pacchetto_net.header_net.flag = tab;
   pacchetto_net.header_net.lun = dimensione * sizeof(float);
   pacchetto_net.header_net.codice = (-1);
   for (i = 0; i < dimensione; i++)
   {
      pacchetto_net.dato[i] = RtDbPGetValueD(dbpunti,
	 collegamento[modello_b][modello_a].uscita[i]);
   }
}

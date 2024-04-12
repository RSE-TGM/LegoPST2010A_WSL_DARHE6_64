/**********************************************************************
*
*       C Source:               btsnapfiles.c
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Tue Jul  1 16:01:37 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: btsnapfiles.c-5 %  (%full_filespec: btsnapfiles.c-5:csrc:1 %)";
#endif

/*
 * btsnapfiles.c
 *				funzioni di gestione diretta dei files bt e snapshot
 */
#include <stdio.h>
#include <string.h>

#include <X11/Xlib.h>
#include <Xm/List.h>
#include <Xm/Text.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/ToggleBG.h>
#include <Xm/RowColumn.h>
#include <Xm/SeparatoG.h>
#include <Xm/Separator.h>
#include <Xm/Xm.h>

#include "UxXt.h"

#include "sim_param.h"
#include "sim_types.h"
#include "dispatcher.h"

extern int _MAX_SNAP_SHOT;

#include "sked.h"

#include "parametri.h"
#include "messaggi.h"
#include "bistrutt.h"
#include "banco_globals.h"
#include "btsnapfiles.h"

#include "backtrack.h"

extern int _MAX_BACK_TRACK;

extern VARIABILI *variabili;
extern char *ind_sh_top;
extern int size_area_dati;
extern int size_header_snap;
extern int size_blocco_snap;
extern int size_parte1_bktk;
extern int size_blocco_bktk;

extern Widget areaMessaggi;
extern Widget masterMenu;
extern int stato_sim;
/********************************************************************/
/*
 * Legge il valore della variabile puntata da p e n e la restituisce in 
 * val. Ritorna <0 per errore.
 */
int leggi_da_bt (fp, p, val, n)
FILE *fp;
int p;                      /* puntatore                            */
float *val;                 /* valore                               */
int n;                      /* n. di record (da 1 a ...)            */
{
int nmodel;   /* da 0 a ... */
int offset;
float app;

	if ((nmodel = ind_modello (ind_sh_top, p, variabili)) < 0)
		{
		return (-1);
		}

printf ("leggi_da_bt : n = %d\n",n);

/******
	offset = ((_MAX_BACK_TRACK * sizeof(BKTAB)) +   
      (n - 1) * (size_area_dati+   sizeof(float)+   
#if defined MFFR
		sizeof(SNAP_SKED)+
#endif
		DIM_SNAP_AUS+
		MAX_UPDOWN * sizeof(float) + MAX_UPDOWN * sizeof(int))+
		p*sizeof(float));
***************/

	offset = size_parte1_bktk + n * size_blocco_bktk +
				p*sizeof(float);

   fseek(fp, offset, SEEK_SET);
	fread (&app,sizeof(float),1,fp);
	*val = app;
	
	return (0);
}
/********************************************************************/
/*
 * Legge il valore della variabile puntata da p e n e la restituisce in 
 * val. Ritorna <0 per errore.
 */
int leggi_da_ci (fp, p, val, n)
FILE *fp;
int p;                      /* puntatore                            */
float *val;                 /* valore                               */
int n;                      /* n. di record (da 1 a ...)            */
{
int nmodel;   /* da 0 a ... */
int offset;
float app;

/* fprintf (stderr,"leggi_da_ci per punt. = %d\n",p); **/

   if ((nmodel = ind_modello (ind_sh_top, p, variabili)) < 0)
      {
      return (-1);
      }
	offset = size_header_snap + (n-1)*size_blocco_snap + p*sizeof(float);
   fseek(fp, offset, SEEK_SET);
   fread (&app,sizeof(float),1,fp);
   *val = app;
  
   return (0);
}

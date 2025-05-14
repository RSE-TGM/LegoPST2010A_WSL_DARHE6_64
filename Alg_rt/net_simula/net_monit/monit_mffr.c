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
   modulo monit_mffr.c
   tipo 
   release 5.2
   data 1/24/96
   reserved @(#)monit_mffr.c	5.2
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)monit_mffr.c	5.2\t1/24/96";
/*
        Fine sezione per SCCS
*/
#ifdef MFFR
# include <stdio.h>
# include <math.h>
# include <string.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/timeb.h>
#endif
#if defined VMS
# include <stdlib.h>
# include "vmsipc.h"
#endif
# include "sim_param.h"
# include "sim_types.h"       /* tipi di varibili LEGO               */
# include "sim_ipc.h"
# include <X11/Xlib.h>
# include <Mrm/MrmAppl.h>
# include <Xm/ScrolledW.h>
# include <Xm/List.h>
# include <Xm/Label.h>
# include <Xm/Text.h>
# include <Xm/Frame.h>
# include <Xm/ToggleB.h>
# include <Xm/PushB.h>
# include <Xm/RowColumn.h>
# include <Xm/Form.h>
# include <Xm/Xm.h>
# include <Xm/MessageB.h>
# include "monit.h"
# include "monituil.h"
# include "libutilx.h"
# include "sked.h"
# include "dispatcher.h"
# include "agg_manovra.h"

#include  "monit_mffr.h"
#include <Rt/RtMemory.h>

extern SNAP_SKED sommari;
extern SOMMARIO_FR sommario_fr;
extern SOMMARIO_MF sommario_mf;
extern char *ind_sh_top;   /* puntatore inizio shared memory sh_var */
extern VARIABILI *variabili;  /* database delle variabili  */
extern int tot_variabili;  /* numero totale delle variabili      */
extern Widget tasto_ok;
extern Widget tasto_fr_ok;
extern Widget val_att_fr_w[MAX_FR_SOMM];
extern Widget val_att_w[MAX_MF_SOMM];
extern VALORI_AGG val_agg;

float leggi_valore(int p);  /* legge il valore di una variabile dal database */
Widget PostDialod();

int clear_readmf();
int clear_readfr();
int sommario_mf_to_snap();
int sommario_fr_to_snap();
int snap_to_sommario_mf();
int snap_to_sommario_fr();
int aggiorna_grafica();
int aggiorna_sommario_mf();
int aggiorna_sommario_fr();



/*****************************************************************/
int clear_snap_sked()
{
   sommari.somm_snappati = 0;
   clear_readmf();
   clear_readfr();
   return(0);
}
/*****************************************************************/
int clear_readmf()
{
int i;
   sommari.readmf.ul_mf = 0;
   sommari.readmf.flg_modm = 0;

   for (i=0; i<MAX_MF_SOMM; i++)
      {
      strcpy (sommari.readmf.nome_mf[i],"");
      sommari.readmf.address[i] = -1;
		sommari.readmf.vdef_mf[i] = 0.0;
      sommari.readmf.dstr_mf[i] = -1;
      sommari.readmf.dur_mf[i]  = -1;
      sommari.readmf.ramp_mf[i] = 0.0;
      sommari.readmf.sevf_mf[i] = 0.0;
      sommari.readmf.vatt_mf[i] = 0.0;
      strcpy (sommari.readmf.satt_mf[i],"");
      }
   return(0);
}
/*****************************************************************/
int clear_readfr()
{
int i;
   sommari.readfr.ul_fr = 0;
   sommari.readfr.flg_modf = 0;

   for (i=0; i<MAX_FR_SOMM; i++)
      {
      strcpy (sommari.readfr.nome_fr[i],"");
      sommari.readfr.address[i] = -1;
      sommari.readfr.vdef_fr[i] = 0.0;
      sommari.readfr.ramp_fr[i] = 0.0;
      sommari.readfr.sevf_fr[i] = 0.0;
      sommari.readfr.vatt_fr[i] = 0.0;
      strcpy (sommari.readfr.satt_fr[i],"");
      }
   return(0);
}
/*****************************************************************/
int sommari_to_snap()
{
	sommario_mf_to_snap();
	sommario_fr_to_snap();
	sommari.somm_snappati = SOMMARI_SNAPPATI;
	return(0);
}
/*****************************************************************/
int sommario_mf_to_snap()
{
int i;

	sommari.readmf.ul_mf = sommario_mf.numero;
	sommari.readmf.flg_modm = 0;

	for (i=0; i<MAX_MF_SOMM; i++)
		{
		strcpy (sommari.readmf.nome_mf[i], sommario_mf.label[i]);
		sommari.readmf.address[i] = sommario_mf.address[i];
		sommari.readmf.vdef_mf[i] = sommario_mf.val_def[i];
		sommari.readmf.dstr_mf[i] = sommario_mf.delay[i];
		sommari.readmf.dur_mf[i]  = sommario_mf.durata[i];
		sommari.readmf.ramp_mf[i] = sommario_mf.rampa[i];
		sommari.readmf.sevf_mf[i] = sommario_mf.target[i];
		sommari.readmf.vatt_mf[i] = sommario_mf.attuale[i];
		strcpy (sommari.readmf.satt_mf[i], sommario_mf.stato[i]);
		sommari.readmf.occupato[i]= sommario_mf.occupato[i];
		}
	return(0);
}
/*****************************************************************/
int sommario_fr_to_snap()
{
int i;

   sommari.readfr.ul_fr = sommario_fr.numero;
	sommari.readfr.flg_modf = 0;

   for (i=0; i<MAX_FR_SOMM; i++)
      {
      strcpy (sommari.readfr.nome_fr[i], sommario_fr.label[i]);
      sommari.readfr.address[i] = sommario_fr.address[i];
      sommari.readfr.vdef_fr[i] = sommario_fr.val_def[i];
      sommari.readfr.ramp_fr[i] = sommario_fr.rampa[i];
      sommari.readfr.sevf_fr[i] = sommario_fr.target[i];
      sommari.readfr.vatt_fr[i] = sommario_fr.attuale[i];
      strcpy (sommari.readfr.satt_fr[i], sommario_fr.stato[i]);
      sommari.readfr.occupato[i]= sommario_fr.occupato[i];
      }
   return(0);
}
/*****************************************************************/
int snap_to_sommari()
{
	if (sommari.somm_snappati == SOMMARI_SNAPPATI)
		{
		snap_to_sommario_mf();
		snap_to_sommario_fr();
		aggiorna_grafica();
		return(0);
		}
	return(-1);
}
/*****************************************************************/
int snap_to_sommario_mf()
{
int n;
int nmod,i,nblocchi;
unsigned short indice_modello;
unsigned short indice_blocco;

	sommario_mf.numero = sommari.readmf.ul_mf;

	for (i=0; i<MAX_MF_SOMM; i++)
      {
		strcpy (sommario_mf.label[i], sommari.readmf.nome_mf[i]);
		strcpy (sommario_mf.descrizione[i],"");
		sommario_mf.address[i] = sommari.readmf.address[i];
		sommario_mf.val_def[i] = sommari.readmf.vdef_mf[i];
		sommario_mf.delay[i]   = sommari.readmf.dstr_mf[i];
		sommario_mf.durata[i]  = sommari.readmf.dur_mf[i];
		if (sommario_mf.durata[i] == 0.0)
			sommario_mf.durata_non_inf[i] = 0;
		else
			sommario_mf.durata_non_inf[i] = 1;
		sommario_mf.rampa[i]   = sommari.readmf.ramp_mf[i];
		sommario_mf.target[i]  = sommari.readmf.sevf_mf[i];
		sommario_mf.attuale[i] = sommari.readmf.vatt_mf[i];
		strcpy (sommario_mf.stato[i], sommari.readmf.satt_mf[i]);
		sommario_mf.occupato[i] = sommari.readmf.occupato[i];
		}

	dati_blocco_malf(&nmod, &indice_modello, &nblocchi, &indice_blocco);
	for (n=0; n<sommario_mf.numero; n++)
		{
		if (sommario_mf.occupato[n] == OCCUPATO)
			{
			for (i=0; i<tot_variabili; i++)
				{
				if ((variabili[i].mod == (indice_modello+1)) &&
					 (variabili[i].blocco == (indice_blocco+1)) &&
					 (!strcmp(variabili[i].nome, sommario_mf.label[n])))
					{
					strcpy (sommario_mf.descrizione[n], variabili[i].descr);
					taglia_descr (sommario_mf.descrizione[n]);
					if (variabili[i].addr != sommario_mf.address[n])
						{
						printf ("*** VARIABILE %s: puntatore cambiato ***\n",
								sommario_mf.label[n]);
						}
					break;
					}
				if (i == tot_variabili)
					{
					printf ("*** VARIABILE %s NON IN DATABASE ***\n",
								sommario_mf.label[n]);
					}
			   }
			}
		}
	return(0);
}
/*****************************************************************/
int snap_to_sommario_fr()
{
int n;
int nmod,i,nblocchi;
unsigned short indice_modello;
unsigned short indice_blocco;

	sommario_fr.numero = sommari.readfr.ul_fr;

	for (i=0; i<MAX_FR_SOMM; i++)
      {
		strcpy (sommario_fr.label[i], sommari.readfr.nome_fr[i]);
		strcpy (sommario_fr.descrizione[i],"");
		sommario_fr.address[i] = sommari.readfr.address[i];
		sommario_fr.val_def[i] = sommari.readfr.vdef_fr[i];
		sommario_fr.rampa[i]   = sommari.readfr.ramp_fr[i];
		sommario_fr.target[i]  = sommari.readfr.sevf_fr[i];
		sommario_fr.attuale[i] = sommari.readfr.vatt_fr[i];
		strcpy (sommario_fr.stato[i], sommari.readfr.satt_fr[i]);
		sommario_fr.occupato[i] = sommari.readfr.occupato[i];
		}
	dati_blocco_frem(&nmod, &indice_modello, &nblocchi, &indice_blocco);
   for (n=0; n<sommario_fr.numero; n++)
      {
      if (sommario_fr.occupato[n] == OCCUPATO)
         {
         for (i=0; i<tot_variabili; i++)
            {
            if ((variabili[i].mod == (indice_modello+1)) &&
                (variabili[i].blocco == (indice_blocco+1)) &&
                (!strcmp(variabili[i].nome, sommario_fr.label[n])))
               {
               strcpy (sommario_fr.descrizione[n], variabili[i].descr);
               taglia_descr (sommario_fr.descrizione[n]);
               if (variabili[i].addr != sommario_fr.address[n])
                  {
                  printf ("*** VARIABILE %s: puntatore cambiato ***\n",
                        sommario_fr.label[n]);
                  }
               break;
               }
            if (i == tot_variabili)
               {
               printf ("*** VARIABILE %s NON IN DATABASE ***\n",
                        sommario_fr.label[n]);
               }
            }
         }
      }
	return(0);
}
/*****************************************************************/
int aggiorna_grafica()
{
	aggiorna_sommario_mf();
	aggiorna_sommario_fr();
	return(0);
}
/*****************************************************************/
int aggiorna_sommario_mf()
{
int i;

	for (i=0; i<MAX_MF_SOMM; i++)
		aggiorna_riga_sommario(i);

	if (sommario_mf.numero >= MAX_MF_SOMM)
      tasto_bloccato(tasto_ok,"MF");
	return(0);
}
/*****************************************************************/
int aggiorna_sommario_fr()
{
int i;

   for (i=0; i<MAX_FR_SOMM; i++)
      aggiorna_riga_sommario_fr(i);

   if (sommario_fr.numero >= MAX_MF_SOMM)
      tasto_bloccato(tasto_fr_ok,"FR");
   return(0);
}
/*****************************************************************/
float leggi_valore(int addr)
{
AGGIORNA_VALORI agg;
int size;

	agg.n = 1;
	agg.updvar[0].indirizzo = addr;
	size = sizeof(int)+agg.n*(sizeof(int)+sizeof(float));
	if (SD_varupd(MONIT,(char*)&agg,size) < 0)
         printf ("MONIT: errore lettura valore singolo\n");

	return (agg.updvar[0].valore);
}
/*****************************************************************/
int aggiorna_valori_sommari()
{
	aggiorna_valori_mf();
	aggiorna_valori_fr();
	return(0);
}
/*****************************************************************/
int aggiorna_valori_mf()
{
AGGIORNA_VALORI agg;
int size;
int i;
char temp[100];

if ((val_agg.stato_sked != STATO_STOP) &&
   (val_agg.stato_sked != STATO_FREEZE) &&
   (val_agg.stato_sked != STATO_ERRORE))
   {
	if (sommario_mf.numero > 0)
		{
		agg.n = sommario_mf.numero;
   	for (i=0; i<agg.n; i++)
         agg.updvar[i].indirizzo = sommario_mf.address[i];

   	size = sizeof(int)+agg.n*(sizeof(int)+sizeof(float));
   	if (SD_varupd(MONIT,(char*)&agg,size) < 0)
         printf ("MONIT: errore SD_varupd agg malf\n");

		for (i=0; i<agg.n; i++)
			{
			if (sommario_mf.attuale[i] != agg.updvar[i].valore)
				{
				sommario_mf.attuale[i] = agg.updvar[i].valore;
				if (isdigital(sommario_mf.label[i]))
					sprintf (temp,"%1.0f",sommario_mf.attuale[i]);
				else
					sprintf (temp,"%f",sommario_mf.attuale[i]);
				XtVaSetValues (val_att_w[i],XmNvalue,temp,NULL);
				}
			}
		}
	}
	return(0);
}
/*****************************************************************/
int aggiorna_valori_fr()
{
AGGIORNA_VALORI agg;
int size;
int i;
char temp[100];

if ((val_agg.stato_sked != STATO_STOP) &&
   (val_agg.stato_sked != STATO_FREEZE) &&
   (val_agg.stato_sked != STATO_ERRORE))
   {
	if (sommario_fr.numero > 0)
		{
   	agg.n = sommario_fr.numero;
   	for (i=0; i<agg.n; i++)
         agg.updvar[i].indirizzo = sommario_fr.address[i];

   	size = sizeof(int)+agg.n*(sizeof(int)+sizeof(float));
   	if (SD_varupd(MONIT,(char*)&agg,size) < 0)
         printf ("MONIT: errore SD_varupd agg frem\n");

   	for (i=0; i<agg.n; i++)
      	{
			if (sommario_fr.attuale[i] != agg.updvar[i].valore)
				{
      		sommario_fr.attuale[i] = agg.updvar[i].valore;
				if (isdigital(sommario_fr.label[i]))
					sprintf (temp,"%1.0f",sommario_fr.attuale[i]);
				else
      			sprintf (temp,"%f",sommario_fr.attuale[i]);
      		XtVaSetValues (val_att_fr_w[i],XmNvalue,temp,NULL);
				}
      	}
		}
	}
   return(0);
}
/**************************************************************/
Widget PostDialog (p,t,s)
Widget p;
int t;
char *s;
{
Widget dialog_w;
XmString testo;
Pixel colore;

	XtVaGetValues (p, XmNbackground, &colore, NULL);
	dialog_w = XmCreateMessageDialog (p, "dialog", NULL, 0);

	testo = XmStringCreateLtoR (s , XmSTRING_DEFAULT_CHARSET);
	XtVaSetValues (dialog_w,
			XmNdialogType   , t,
			XmNmessageString, testo,
			XmNbackground, colore,
			XmNdialogTitle, XmStringCreateSimple("ATTENZIONE"),
			NULL);
	XmStringFree(testo);
	XtUnmanageChild (XmMessageBoxGetChild(dialog_w,XmDIALOG_HELP_BUTTON));
	XtUnmanageChild (XmMessageBoxGetChild(dialog_w,XmDIALOG_CANCEL_BUTTON));
	XtManageChild (dialog_w);
	XtPopup (XtParent(dialog_w), XtGrabNone);
	return (dialog_w);
}
#endif

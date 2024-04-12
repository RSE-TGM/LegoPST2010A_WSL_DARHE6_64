/**********************************************************************
*
*       C Source:               perturbazioni.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Tue Oct 22 13:48:19 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: perturbazioni.c-4.1.1 %  (%full_filespec: perturbazioni.c-4.1.1:csrc:1 %)";
#endif
#include <stdio.h>
#include <malloc.h>

#include <X11/Xlib.h>
#include <Xm/List.h>
#include <Xm/Text.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/Xm.h>

#include "UxXt.h"

#include "sim_param.h"
#include "sim_types.h"
#include "dispatcher.h"
#include "parametri.h"
#include "refresh.h"
#include "editPert.h"
#include "messaggi.h"
extern int _MAX_PERTUR;
extern int tot_variabili;
extern VAL val;
extern Widget      areaMessaggi;
extern int editPertRate;

int displayPert (Widget padre)
{
int k;
_UxCeditPert *Ctx;
Widget ListAtt;
Widget ListUnatt;
extern TIPO_PERT *perturbazioni;
extern TIPO_PERT *perturbazioni_old;
extern VARIABILI *variabili;
char testo[500];
XmString c_app_str;
char *str;
XmString c_str;
int posizione =0;
int variab;
/*
 * acquisizione del Context
 */
	Ctx = (_UxCeditPert *) UxGetContext (padre);
/*
 * aggancia gli oggetti
 */
	ListAtt = Ctx->UxeditPertAttScrollList;
	ListUnatt = Ctx->UxeditPertUnattScrollList;
/*
 * clear delle liste
 */
	XtUnmanageChild (ListAtt);
	clear_lista (ListAtt);
	XtUnmanageChild (ListUnatt);
	clear_lista (ListUnatt);
/*
 * esame perturbazioni e display
 */
	for( k =0 ; k < _MAX_PERTUR*2 ; k++ )
		{
		if(perturbazioni[k].tipo != -1)
			{
			++posizione;
			perturbazioni[k].rateo_durata=
   				(float)fabs((double)perturbazioni[k].rateo_durata);
			for( variab = 0; variab < tot_variabili ; variab ++ )
			if(variabili[variab].addr == perturbazioni[k].indirizzo)
   			break;

			switch(perturbazioni[k].tipo){
			case (PERT_SCALINO):
   			{
   			sprintf(testo,"STEP on %s - target value %f",
       			variabili[variab].nome, perturbazioni[k].valore_delta);
   			break;
   			};
			case (PERT_RAMPA):
   			{
   			sprintf(testo,"RAMP on %s - target value %f - grad. %f",
       			variabili[variab].nome, perturbazioni[k].valore_delta,
      			perturbazioni[k].rateo_durata);
   			break;
   			};
			case (PERT_RAMPA_STOP):
   			{
   			sprintf(testo,"STOP RAMP on %s", variabili[variab].nome);
   			break;
   			};
			case (PERT_TO):
   			{
   			sprintf(testo,"TO on %s - target value %f",
       			variabili[variab].nome, perturbazioni[k].valore_delta);
   			break;
   			};
			case (PERT_TO_STOP):
   			{
   			sprintf(testo,"STOP TO on %s", variabili[variab].nome);
   			break;
   			};
			case (PERT_IMPULSO):
   			{
   			sprintf(testo,"PULSE on %s - target value %f - wide %f",
       			variabili[variab].nome, perturbazioni[k].valore_delta,
      			perturbazioni[k].rateo_durata);
   			break;
   			};
			case (PERT_IMPULSO_STOP):
   			{
   			sprintf(testo,"STOP PULSE on %s", variabili[variab].nome);
   			break;
   			};
			case (PERT_UP):
   			{
   			sprintf(testo,"UP on %s", variabili[variab].nome);
   			break;
   			};
			case (PERT_DOWN):
   			{
   			sprintf(testo,"DOWN on %s", variabili[variab].nome);
   			break;
   			};
			case (PERT_NOT):
   			{
   			sprintf(testo,"NOT on %s", variabili[variab].nome);
   			break;
   			};
			case (PERT_PERIODIC):
   			{
   			if(perturbazioni[k].valore_delta== -1)
      			sprintf(testo,
   			"SINUSOIDAL on %s - period= %f - wide = %f - mean value = %f - phase = %f",
      			variabili[variab].nome, perturbazioni[k].period,
      			perturbazioni[k].wide,perturbazioni[k].meanvalue,
      			perturbazioni[k].phase);
   			else
      			sprintf(testo,
   			"TRAPEZOIDAL on %s - period= %f - wide = %f - mean value = %f - phase = %f T1 =%f - T2 = %f - T3 = %f",
      			variabili[variab].nome, perturbazioni[k].period,
      			perturbazioni[k].wide,perturbazioni[k].meanvalue,
      			perturbazioni[k].phase, perturbazioni[k].valore_delta,
      			perturbazioni[k].rateo_durata,perturbazioni[k].t_null_var);
   			break;
   			};
			case (PERT_PERIODIC_STOP):
   			{
   			sprintf(testo,"STOP PERIODIC on %s", variabili[variab].nome);
   			break;
   			};
			case (PERT_WHITENOISE):
   			{
   			sprintf(testo,"WHITE NOISE on %s - variance %f - mean value %f",
         			variabili[variab].nome,perturbazioni[k].t_null_var,
         			perturbazioni[k].meanvalue);
   			break;
   			};
			case (PERT_WHITENOISE_STOP):
   			{
   			sprintf(testo,"STOP WHITE NOISE on %s",variabili[variab].nome);
   			break;
   			};
			case (PERT_MALFUNCTION):
        			{
        			sprintf(testo,"MALFUNCTION on %s - type %f - target value %f",
                        			variabili[variab].nome,perturbazioni[k].t_null_var,
                        			perturbazioni[k].valore_delta);
        			break;
        			};
			case (PERT_MALFUNCTION_STOP):
        			{
        			sprintf(testo,"STOP MALFUNCTION on %s",variabili[variab].nome);
        			break;
        			};
			};
			if(perturbazioni[k].t >0)
						sprintf(testo,"%s  [on at %f]",
   						testo, perturbazioni[k].t+val.actual.tempo_sim);


			str=(char*)XtMalloc(sizeof(char)*(strlen(testo)+20));
			strcpy(str,testo);
			c_str=XmStringCreateLtoR(str,XmSTRING_DEFAULT_CHARSET);
			if(perturbazioni[k].t <= 0)
						{
						XmListAddItemUnselected(ListAtt,c_str,0);
						}
			else
						{
						XmListAddItemUnselected(ListUnatt,c_str,0);
						}
			XSync(UxDisplay,False);
			XtFree(str);
			XmStringFree(c_str);
			}
		}
		XtManageChild(ListAtt);
		XtManageChild(ListUnatt);

}
/**************************************************************/
int richiesta_editPertRate (w)
Widget w;
{
char risp [10];
char old_val[10];
int new_val;
char *messaggio;
int esito;

   sprintf (old_val,"%d",editPertRate);
   create_richiestaDati (w, PERTRATE, old_val, risp);
   new_val = atoi(risp);
   printf ("risp = %s: %d\n",risp,new_val);

	if (new_val < 1)
		new_val = 1;

	editPertRate = new_val;
   esito = 0;
   messaggio = (char *)malloc (strlen(PERTRATE)+strlen(OPER_FALLITA)+20);
   sprintf (messaggio,"%s :%d",PERTRATE,new_val);
   add_message (areaMessaggi,messaggio,LIVELLO_1);
   free (messaggio);
   return(esito);
}
/**************************************************************/
int updateEditPertLabel (lab)
Widget lab;
{
char *app;
	app = (char *)malloc (strlen (PERT_FREQ_UPD)+20);
	sprintf (app,"%s %d %s",PERT_FREQ_UPD,editPertRate," Sec.");
	XtVaSetValues (lab,RES_CONVERT(XmNlabelString,app), NULL);
	free (app);
	return (0);
}

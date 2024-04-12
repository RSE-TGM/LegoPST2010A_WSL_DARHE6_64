/**********************************************************************
*
*       C Source:               monit_data.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Fri Nov 21 11:51:21 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: monit_data.c-2 %  (%full_filespec: monit_data.c-2:csrc:1 %)";
#endif
/*
   modulo monit_data.c
   tipo 
   release 5.2
   data 1/24/96
   reserved @(#)monit_data.c	5.2
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)monit_data.c	5.2\t1/24/96";
/*
        Fine sezione per SCCS
*/
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
#endif
#if defined VMS
# include "vmsipc.h"
#endif
# include <X11/Xlib.h>
# include <Mrm/MrmAppl.h>
# include <Xm/Xm.h>
# include <Xm/List.h>
# include <Xm/TextF.h>
# include <Xm/Label.h>
# include <Xm/RowColumn.h>
# include <Xm/ScrolledW.h>
# include "sim_param.h"         /* parametri generali LEGO          */
# include "sim_types.h"         /* tipi e costanti LEGO             */
# include "dispatcher.h"
# include "monit.h"
# include "monituil.h"
#include "mod_data.h"
#include "monit_mffr.h"
# include <Rt/RtMemory.h>


extern modello_selezionato;
extern blocco_selezionato;

extern Display *display;

extern Widget widget_array[MAX_WIDGETS];/* Place to keep all other */

typedef struct vedi_dati
{
int tipologia_riga;           /* 1=commento 2=1 dato ... 4=3 dati */
Widget rowcol;
Widget w_label_comm;
Widget w_label_1;
Widget w_text_1;
Widget w_label_2;
Widget w_text_2;
Widget w_label_3;
Widget w_text_3;
char c_label_1[12];
char c_text_1[12];
char c_label_2[12];
char c_text_2[12];
char c_label_3[12];
char c_text_3[12];
char c_label_comm[150];
char spare [2];
} VEDI_DATI;
int numero_righe= -1; 
VEDI_DATI *riga=NULL;

char *piniz=NULL;



void seleziona_data(w, tag, reason)
Widget w;
int *tag;
XmListCallbackStruct *reason;
{
int i,k;
int nrighe;
char riga_f14[150];
Arg args[50];           /* per settaggio argomenti widgets */
Widget p_w_child;
int qq;
Pixel color_back;
Pixel color_forg;
XmString app_string;
int kk=0;

if (*tag==k_elenco_modelli_modat)
{
	modello_selezionato=reason->item_position;
	blocco_selezionato=1;
	mo_blocchi(widget_array[k_elenco_blocchi_modat]);
}

if (*tag==k_elenco_blocchi_modat)
	{
/*
	abilita il tasto OK
*/
        i=0;
        XtSetArg (args[i], XmNsensitive, True);i++;
	XtSetValues(widget_array[k_data_dialog_ok],args,i);

/* Lettura colore foreground e background dalla Scrolled List elenco modelli */
   /*
  */
        i=0;
        XtSetArg (args[i], XmNbackground, &color_back);i++;
        XtSetArg (args[i], XmNforeground, &color_forg);i++;
        XtGetValues(widget_array[k_elenco_modelli_modat],args,i);
        if ( piniz != NULL )
          free(piniz);
	blocco_selezionato=reason->item_position;
	printf("lettura dati modello %d blocco %d\n",
			modello_selezionato,blocco_selezionato);
	if(SD_editdata (MONIT, modello_selezionato,blocco_selezionato,
			&piniz,&nrighe)>0)
		vis_messaggio("Acknowledge EDIT DATA received",0);
	else
		{
		vis_messaggio("Warning:Acknowledge EDIT DATA not received\n",1);
		return;
		}
/*
        new_leggi(modello_selezionato,blocco_selezionato,&piniz,&nrighe);
*/
        printf("numero_righe (new)=%d\n",numero_righe);
        distruggi_figli(&numero_righe,riga);
        if (riga != NULL)
           free(riga);
        riga = (VEDI_DATI*)calloc(nrighe,sizeof(VEDI_DATI));
	for(k=0;k<nrighe;k++)
		{
/*
		printf("monit: %s\n",&piniz[k*LUN_RIGA_F14]);
*/
                riga_dati(&piniz[k*LUN_RIGA_F14],&riga[k]);
		strcpy(riga_f14,&piniz[k*LUN_RIGA_F14]);
		riga_f14[LUN_RIGA_F14-1]=0;
/* Gestione sul tipo di riga riguardo all'assegnamento */
		i=0;
    		XtSetArg (args[i], XmNx, 5); i++;
                XtSetArg (args[i], XmNy, 40*k+5); i++;	
                XtSetArg (args[i], XmNpacking, XmPACK_TIGHT); i++;	
                XtSetArg (args[i], XmNorientation, XmHORIZONTAL); i++;	
                XtSetArg (args[i], XmNnumColumns, 1); i++;	
        	XtSetArg (args[i], XmNbackground, color_back);i++;
        	XtSetArg (args[i], XmNforeground, color_forg);i++;
/*
		riga[k].rowcol=XmCreateRowColumn(widget_array[k_data_rowcol],
		"row",args,i);	
*/
		riga[k].rowcol=widget_array[k_data_rowcol];
                if (riga[k].tipologia_riga == 1 )
                      {
                      i=0;
    		      XtSetArg (args[i], XmNx, 5); i++;
/*
                      XtSetArg (args[i], XmNy, 0); i++;	
*/
                      XtSetArg (args[i], XmNy, 40*k+5); i++;	
                      XtSetArg (args[i], XmNbackground, color_back); i++;
                      XtSetArg (args[i], XmNforeground, color_forg); i++;
		      app_string=XmStringCreateSimple (riga[k].c_label_comm); 
                      XtSetArg (args[i], XmNlabelString, app_string);i++;
		      riga[k].w_label_comm = 
                           XmCreateLabel (riga[k].rowcol, 
                                          "label", args, i);
/*
printf("widget_array[k_data_rowcol]=%d  w_lab=%d i=%d  k=%d\n",
	widget_array[k_data_rowcol],
	riga[k].w_label_comm,
	i,k);	
*/
		      XmStringFree(app_string);
    		      XtManageChild (riga[k].w_label_comm);
                      }
                if (   riga[k].tipologia_riga == 2 ||
                       riga[k].tipologia_riga == 3 ||
                       riga[k].tipologia_riga == 4    )
                      {
                      i=0;
    		      XtSetArg (args[i], XmNx, 5); i++;
                      XtSetArg (args[i], XmNy, 40*k+5); i++;	
    		      XtSetArg (args[i], XmNwidth, 85); i++;	
                      XtSetArg (args[i], XmNbackground, color_back); i++;
                      XtSetArg (args[i], XmNforeground, color_forg); i++;
		      app_string=XmStringCreateSimple (riga[k].c_label_1);
                      XtSetArg (args[i], XmNlabelString, app_string);i++;
		      riga[k].w_label_1 = 
                           XmCreateLabel (riga[k].rowcol,"label", args, i);
		      XmStringFree(app_string);
    		      XtManageChild (riga[k].w_label_1);
                      i=0;
                      XtSetArg (args[i], XmNx, 95); i++;
                      XtSetArg (args[i], XmNy, 40*k+5); i++;	
                      XtSetArg (args[i], XmNwidth, 105); i++;
                      /*XtSetArg (args[i], XmNvalue,riga[k].c_text_1 ); i++;*/
                      XtSetArg (args[i], XmNmarginHeight, 1); i++;
                      XtSetArg (args[i], XmNbackground, color_back); i++;
                      XtSetArg (args[i], XmNforeground, color_forg); i++;
                      XtSetArg (args[i], XmNmaxLength,10); i++;
                      XtSetArg (args[i], XmNcolumns,12); i++;
printf("Prima XmCreateText\n");
                      riga[k].w_text_1 =
                           XmCreateTextField (riga[k].rowcol, "text", args, i);
printf("Dopo XmCreateText\n");
                      XmTextFieldSetString(riga[k].w_text_1,riga[k].c_text_1 );
                      XtManageChild (riga[k].w_text_1);
                      if (   riga[k].tipologia_riga == 3 ||
                             riga[k].tipologia_riga == 4   )
                         {
                         i=0;
                         XtSetArg (args[i], XmNx, 205); i++;
                         XtSetArg (args[i], XmNy, 40*k+5); i++;	
    		         XtSetArg (args[i], XmNwidth, 85); i++;	
                         XtSetArg (args[i], XmNbackground, color_back); i++;
                         XtSetArg (args[i], XmNforeground, color_forg); i++;
		         app_string=XmStringCreateSimple (riga[k].c_label_2);
                         XtSetArg (args[i], XmNlabelString, app_string);i++;
		         riga[k].w_label_2 = 
                              XmCreateLabel (riga[k].rowcol, 
                                          "label", args, i);
                         XmStringFree(app_string);
    		         XtManageChild (riga[k].w_label_2);
                         i=0;
                         XtSetArg (args[i], XmNx, 295); i++;
                         XtSetArg (args[i], XmNy, 40*k+5); i++;	
                         XtSetArg (args[i], XmNwidth, 105); i++;
                         /*XtSetArg (args[i], XmNvalue,riga[k].c_text_2);i++;*/
                         XtSetArg (args[i], XmNmarginHeight, 1); i++;
                         XtSetArg (args[i], XmNbackground, color_back); i++;
                         XtSetArg (args[i], XmNforeground, color_forg); i++;
                         XtSetArg (args[i], XmNmaxLength,10); i++;
                         XtSetArg (args[i], XmNcolumns,12); i++;
                         riga[k].w_text_2 =
                            XmCreateTextField (riga[k].rowcol,"text", args, i);
                         XmTextFieldSetString(riga[k].w_text_2,
                                              riga[k].c_text_2 );
                         XtManageChild (riga[k].w_text_2);
                         if (   riga[k].tipologia_riga == 4 ) 
                            {
                            i=0;
    		            XtSetArg (args[i], XmNx, 405); i++;
                            XtSetArg (args[i], XmNy, 40*k+5); i++;	
    		            XtSetArg (args[i], XmNwidth, 85); i++;	
                            XtSetArg (args[i], XmNbackground, color_back); i++;
                            XtSetArg (args[i], XmNforeground, color_forg); i++;
		            app_string=XmStringCreateSimple (riga[k].c_label_3);
                            XtSetArg (args[i], XmNlabelString, app_string);i++;
		            riga[k].w_label_3 = 
                                 XmCreateLabel (riga[k].rowcol, 
                                          "label", args, i);
                            XmStringFree(app_string);
    		            XtManageChild (riga[k].w_label_3);
                            i=0;
                            XtSetArg (args[i], XmNx, 495); i++;
                            XtSetArg (args[i], XmNy, 40*k+5); i++;	
                            XtSetArg (args[i], XmNwidth, 105); i++;
                            /*
                            XtSetArg (args[i], XmNvalue,riga[k].c_text_3);i++;
                            */
                            XtSetArg (args[i], XmNmarginHeight, 1); i++;
                            XtSetArg (args[i], XmNbackground, color_back); i++;
                            XtSetArg (args[i], XmNforeground, color_forg); i++;
                            XtSetArg (args[i], XmNmaxLength,10); i++;
                            XtSetArg (args[i], XmNcolumns,12); i++;
                            riga[k].w_text_3 =
                                 XmCreateTextField (riga[k].rowcol,
                                          "text", args, i);
                            XmTextFieldSetString(riga[k].w_text_3,
                                                 riga[k].c_text_3 );
                            XtManageChild (riga[k].w_text_3);
                            }
                         } 
                      }
/*
		XtManageChild(riga[k].rowcol);
*/
		}
        printf("ASSEGNO numero_righe (old=%d)= nrighe(%d)\n",
                numero_righe,nrighe);
        numero_righe = nrighe;
	}
}


void seleziona_editdata_activate(w, tag, reason)
Widget w;
int *tag;
unsigned long *reason;
{
int k=0;
int i;
int j;
int qq;
int modifica=1;
VEDI_DATI *app_riga;
char app[15];
char new_text_1[12];
char new_text_2[12];
char new_text_3[12];
Arg args[50];           /* per settaggio argomenti widgets */
char *punt;
char *punt_out_dati;


/*
	disabilita il tasto OK
*/
        i=0;
        XtSetArg (args[i], XmNsensitive, False);i++;
	XtSetValues(widget_array[k_data_dialog_ok],args,i);


if (*tag==k_data_dialog_ok)
   {
/* Controllo eventuali cambiamenti nella struttura dei dati (riga) */
   while( (k<numero_righe)&&modifica )
      {
printf("\n                   ---  K = %d --- \n",k);
      if ( riga[k].tipologia_riga != 1 )
         {
         strcpy(new_text_1,XmTextFieldGetString(riga[k].w_text_1));
         if ( 0!=strncmp(riga[k].c_text_1,new_text_1,10) )
            modifica = 0;
printf("dato-1-:Text=%s|  l=%d    text(old)=%s|  l=%d  modi=%d\n",
                 new_text_1,strlen(new_text_1),riga[k].c_text_1,
                 strlen(riga[k].c_text_1),modifica);
         if ( riga[k].tipologia_riga == 3 || 
              riga[k].tipologia_riga == 4   )
            {
            strcpy(new_text_2,XmTextFieldGetString(riga[k].w_text_2));
            if ( 0!=strncmp(riga[k].c_text_2,new_text_2,10) )
               modifica = 0;
printf("dato-2-:Text=%s|  l=%d    text(old)=%s|  l=%d  modi=%d\n",
                 new_text_2,strlen(new_text_2),riga[k].c_text_2,
                 strlen(riga[k].c_text_2),modifica);
            if ( riga[k].tipologia_riga == 4 )
               {
               strcpy(new_text_3,XmTextFieldGetString(riga[k].w_text_3));
               if ( 0!=strncmp(riga[k].c_text_3,new_text_3,10) )
                  modifica = 0;
printf("dato-3-:Text=%s|  l=%d    text(old)=%s|  l=%d  modi=%d\n",
                 new_text_3,strlen(new_text_3),riga[k].c_text_3,
                 strlen(riga[k].c_text_3),modifica);
               }
            }
         }
       k++;
       }
   if ( modifica == 0 )
      {
      punt_out_dati = (char*)calloc(numero_righe,LUN_RIGA_F14);
      printf("seleziona=OK:ora modifico i dati numero_righe=%d\n",
              numero_righe);
      memorizza_dati(numero_righe,riga,punt_out_dati,piniz);
/* modifica */
      if ( SD_modidata(MONIT,punt_out_dati,numero_righe)> 0 )
         {
         vis_messaggio ("Modifica dati effettuata",0);
         }
      else
         {
         vis_messaggio ("Modifica dati non eseguita",1);
         }
      free(punt_out_dati);
      printf("seleziona=OK:fine modifica dati\n");
      }
/*
   distruggi_figli(&numero_righe,riga);
   printf("seleziona=OK:fine distruggi figli\n");
*/
   /*XtUnmanageChild(widget_array[k_data_dialog]);*/ 
   XtUnmanageChild(widget_array[k_data_dialog]);
   free(piniz);
   piniz = NULL;
   printf("seleziona=OK:fine \n");
   }  /* Fine del data_dialog_ok */
if (*tag==k_data_dialog_canc)
   {
   printf("\n Scelta effettuata : Canc\n");
   distruggi_figli(&numero_righe,riga);
   printf("Canc : ho distrutto i figli\n");
   XtUnmanageChild(widget_array[k_data_dialog]);
   free(piniz);
   piniz = NULL;
   }
}



/*
     Salvataggio della zona dati modificata 
*/
memorizza_dati(int numero, VEDI_DATI *linea, char *pout, char *pin)
{
#define STRNBLANK "          "
int k;
int kk=0;
int j=0;
char *punt;
int lun1,lun2,lun3;
char dato1[11],dato2[11],dato3[11];
char new_text_1[20];
char new_text_2[20];
char new_text_3[20];
char app[100];
char riga_f14[150];
int delta;
int new_off; 

printf("INGRESSO IN MEMORIZZA DATI\n");

/*    vengono cancellati i valori dei dati  */
      punt = pout;
      for(k=0;k<numero;k++)
         {
         if ( linea[k].tipologia_riga == 1 )
            memcpy(punt,&pin[k*LUN_RIGA_F14],LUN_RIGA_F14);
         if ( linea[k].tipologia_riga == 2 || 
              linea[k].tipologia_riga == 3 ||
              linea[k].tipologia_riga == 4   )
            {
            strcpy(new_text_1,
                   XmTextFieldGetString(riga[k].w_text_1));
            j=1; 
            if ( linea[k].tipologia_riga == 3 ||
                 linea[k].tipologia_riga == 4   )
                 {
                 j++; 
                 strcpy(new_text_2,
                        XmTextFieldGetString(riga[k].w_text_2));
                 if ( linea[k].tipologia_riga == 4 )
                    {
                    strcpy(new_text_3,
                           XmTextFieldGetString(riga[k].w_text_3));
                    j++;
                    }
                 }
/*          Inserimento dei dati nella riga   */
            memcpy(riga_f14,&pin[k*LUN_RIGA_F14],LUN_RIGA_F14);
            switch(j)
               {
               case 1 : 
                  delta = 10 - strlen(new_text_1);
                  new_off = OFF_INI_DATO1 + strlen(new_text_1);
                  strncpy(&riga_f14[OFF_INI_DATO1],new_text_1,
                          strlen(new_text_1));
                  strncpy(&riga_f14[new_off],STRNBLANK,delta);
                  break;
               case 2 : 
                  delta = 10 - strlen(new_text_1);
                  new_off = OFF_INI_DATO1 + strlen(new_text_1);
                  strncpy(&riga_f14[OFF_INI_DATO1],new_text_1,
                          strlen(new_text_1));
                  strncpy(&riga_f14[new_off],STRNBLANK,delta);
                  delta = 10 - strlen(new_text_2);
                  new_off = OFF_INI_DATO2 + strlen(new_text_2);
                  strncpy(&riga_f14[OFF_INI_DATO2],new_text_2,
                          strlen(new_text_2));
                  strncpy(&riga_f14[new_off],STRNBLANK,delta);
                  break;
               case 3 : 
                  delta = 10 - strlen(new_text_1);
                  new_off = OFF_INI_DATO1 + strlen(new_text_1);
                  strncpy(&riga_f14[OFF_INI_DATO1],new_text_1,
                          strlen(new_text_1));
                  strncpy(&riga_f14[new_off],STRNBLANK,delta);
                  delta = 10 - strlen(new_text_2);
                  new_off = OFF_INI_DATO2 + strlen(new_text_2);
                  strncpy(&riga_f14[OFF_INI_DATO2],new_text_2,
                          strlen(new_text_2));
                  strncpy(&riga_f14[new_off],STRNBLANK,delta);
                  delta = 10 - strlen(new_text_3);
                  new_off = OFF_INI_DATO3 + strlen(new_text_3);
                  strncpy(&riga_f14[OFF_INI_DATO3],new_text_3,
                          strlen(new_text_3));
                  strncpy(&riga_f14[new_off],STRNBLANK,delta);
                  break;
               default:
                  printf("memorizza_dati:errore in riga numero %d\n",
                          k+1);
                  printf("sul numero dei dati (%d)\n",j);
                  break;
               }
             j=0;
             memcpy(punt,riga_f14,LUN_RIGA_F14);
             }
         punt+=LUN_RIGA_F14; 
         }  /* fine ciclo for */
/*
         printf ("*************************\n"); 
         punt = pout;
         for(k=0;k<numero;k++)
           { 
              printf ("%s",punt); 
              punt+ = LUN_RIGA_F14;
           }
*/
printf("USCITA DA MEMORIZZA DATI\n");
}     
/* fine funzione */










riga_dati(char *piniz, VEDI_DATI *linea)
{
char riga_f14[150];
int lun;

         strcpy(riga_f14,piniz);
         printf("riga_dati:riga_f14=%s|  lun=%d\n",riga_f14,strlen(riga_f14));
         linea->tipologia_riga = 1;
         if ( riga_f14[OFF_END_DATO1]=='*' &&
                      strlen(riga_f14)>=(OFF_END_DATO1+1) )
            linea->tipologia_riga = 2;
         if ( riga_f14[OFF_END_DATO2]=='*' &&
                      strlen(riga_f14)>=(OFF_END_DATO2+1) )
            linea->tipologia_riga = 3;
         if ( riga_f14[OFF_END_DATO3]=='*' &&
                      strlen(riga_f14)>=(OFF_END_DATO3+1) )
            linea->tipologia_riga = 4;
         switch (linea->tipologia_riga)
            {
            case 1:
               strcpy(linea->c_label_comm,riga_f14);
               lun = strlen(linea->c_label_comm);
               linea->c_label_comm[lun-1] = '\0';
/*
               lun = strlen(linea->c_label_comm);
               linea->c_label_comm[lun] = '\0';
*/
               break;
            case 2:
               strncpy(linea->c_text_1,&riga_f14[OFF_INI_DATO1],10);
               strncpy(linea->c_label_1,&riga_f14[OFF_INI_DESC1],8);
               linea->c_label_1[8] = '\0';
               linea->c_text_1[10] = '\0';
/*
               lun = strlen(linea->c_label_1);
               linea->c_label_1[lun] = '\0';
               lun = strlen(linea->c_text_1);
               linea->c_text_1[lun] = '\0';
*/
               if ( !blank_string(linea->c_text_1) )
                  linea->c_text_1[1] = '\0';
               break;
            case 3:
               strncpy(linea->c_text_1,&riga_f14[OFF_INI_DATO1],10);
               strncpy(linea->c_label_1,&riga_f14[OFF_INI_DESC1],8);
               strncpy(linea->c_text_2,&riga_f14[OFF_INI_DATO2],10);
               strncpy(linea->c_label_2,&riga_f14[OFF_INI_DESC2],8);
		
		linea->c_text_1[10] = '\0';
		linea->c_label_1[8] = '\0';
		linea->c_text_2[10] = '\0';
		linea->c_label_2[8] = '\0';
/*
               lun = strlen(linea->c_label_1);
               linea->c_label_1[lun] = '\0';
               lun = strlen(linea->c_label_2);
               linea->c_label_2[lun] = '\0';
               lun = strlen(linea->c_text_1);
               linea->c_text_1[lun] = '\0';
               lun = strlen(linea->c_text_2);
               linea->c_text_2[lun] = '\0';
*/
               if ( !blank_string(linea->c_text_1) )
                  linea->c_text_1[1] = '\0';
               if ( !blank_string(linea->c_text_2) )
                  linea->c_text_2[1] = '\0';
               break;
            case 4:
               strncpy(linea->c_text_1, &riga_f14[OFF_INI_DATO1],10);
               strncpy(linea->c_label_1,&riga_f14[OFF_INI_DESC1],8);
               strncpy(linea->c_text_2, &riga_f14[OFF_INI_DATO2],10);
               strncpy(linea->c_label_2,&riga_f14[OFF_INI_DESC2],8);
               strncpy(linea->c_text_3, &riga_f14[OFF_INI_DATO3],10);
               strncpy(linea->c_label_3,&riga_f14[OFF_INI_DESC3],8);
		linea->c_text_1[10] = '\0';
		linea->c_label_1[8] = '\0';
		linea->c_text_2[10] = '\0';
		linea->c_text_3[10] = '\0';
		linea->c_label_2[8] = '\0';
		linea->c_label_3[8] = '\0';
/*
               lun = strlen(linea->c_label_1);
               linea->c_label_1[lun] = '\0';
               lun = strlen(linea->c_label_2);
               linea->c_label_2[lun] = '\0';
               lun = strlen(linea->c_label_3);
               linea->c_label_3[lun] = '\0';
               lun = strlen(linea->c_text_1);
               linea->c_text_1[lun] = '\0';
               lun = strlen(linea->c_text_2);
               linea->c_text_2[lun] = '\0';
               lun = strlen(linea->c_text_3);
               linea->c_text_3[lun] = '\0';
*/
               if ( !blank_string(linea->c_text_1) )
                  linea->c_text_1[1] = '\0';
               if ( !blank_string(linea->c_text_2) )
                  linea->c_text_2[1] = '\0';
               if ( !blank_string(linea->c_text_3) )
                  linea->c_text_3[1] = '\0';
               break;
            default :
               printf("riga_dati:riga letta di formato non corretto.\n");
               break;
            }
/* Stampe del contenuto della struttura */
/*
            if (linea->tipologia_riga==1)
                  {
                  printf(" \n%s|\n",
                       linea->c_label_comm);
                  }
            else
               if (linea->tipologia_riga==2)
                  {
                  printf(" %s=%s|\n",
                           linea->c_label_1,linea->c_text_1);
                  }
               else
                  if (linea->tipologia_riga==3)
                     {
                     printf(" %s=%s|       %s=%s|\n",
                              linea->c_label_1,linea->c_text_1,
                              linea->c_label_2,linea->c_text_2);
                     }
                  else
                     if (linea->tipologia_riga==4)
                        {
                        printf(" %s=%s|       %s=%s|        %s=%s|\n",
                                 linea->c_label_1,linea->c_text_1,
                                 linea->c_label_2,linea->c_text_2,
                                 linea->c_label_3,linea->c_text_3);
                        }
                     else
                        {
                        printf("Errore riga_dati:tipologia riga=%d\n",
                                linea->tipologia_riga);
                        }
                  
printf("----------fine riga_dati-------------\n");
*/
}


/*****************************************/
riga_dati2(char *piniz, VEDI_DATI *linea)
{
char riga_f14[LUN_RIGA_F14];
int lun;

         strcpy(riga_f14,piniz);
         linea->tipologia_riga = 1;
         if ( riga_f14[OFF_END_DATO1]=='*' &&
                      strlen(riga_f14)>=(OFF_END_DATO1+1) )
            linea->tipologia_riga = 2;
         if ( riga_f14[OFF_END_DATO2]=='*' &&
                      strlen(riga_f14)>=(OFF_END_DATO2+1) )
            linea->tipologia_riga = 3;
         if ( riga_f14[OFF_END_DATO3]=='*' &&
                      strlen(riga_f14)>=(OFF_END_DATO3+1) )
            linea->tipologia_riga = 4;
         switch (linea->tipologia_riga)
            {
            case 1:
               strcpy(linea->c_label_comm,riga_f14);
               lun = strlen(linea->c_label_comm);
               linea->c_label_comm[lun-1] = '\0';
               break;
            case 2:
               strncpy(linea->c_text_1,&riga_f14[OFF_INI_DATO1],10);
               strncpy(linea->c_label_1,&riga_f14[OFF_INI_DESC1],8);
               linea->c_label_1[8] = '\0';
               linea->c_text_1[10] = '\0';
/*
               if ( !blank_string(linea->c_text_1) )
                  linea->c_text_1[1] = '\0';
*/
               break;
            case 3:
               strncpy(linea->c_text_1,&riga_f14[OFF_INI_DATO1],10);
               strncpy(linea->c_label_1,&riga_f14[OFF_INI_DESC1],8);
               strncpy(linea->c_text_2,&riga_f14[OFF_INI_DATO2],10);
               strncpy(linea->c_label_2,&riga_f14[OFF_INI_DESC2],8);
               linea->c_text_1[10] = '\0';
               linea->c_label_1[8] = '\0';
               linea->c_text_2[10] = '\0';
               linea->c_label_2[8] = '\0';
/*
               if ( !blank_string(linea->c_text_1) )
                  linea->c_text_1[1] = '\0';
               if ( !blank_string(linea->c_text_2) )
                  linea->c_text_2[1] = '\0';
*/
               break;
            case 4:
               strncpy(linea->c_text_1, &riga_f14[OFF_INI_DATO1],10);
               strncpy(linea->c_label_1,&riga_f14[OFF_INI_DESC1],8);
               strncpy(linea->c_text_2, &riga_f14[OFF_INI_DATO2],10);
               strncpy(linea->c_label_2,&riga_f14[OFF_INI_DESC2],8);
               strncpy(linea->c_text_3, &riga_f14[OFF_INI_DATO3],10);
               strncpy(linea->c_label_3,&riga_f14[OFF_INI_DESC3],8);
               linea->c_text_1[10] = '\0';
               linea->c_label_1[8] = '\0';
               linea->c_text_2[10] = '\0';
               linea->c_text_3[10] = '\0';
               linea->c_label_2[8] = '\0';
               linea->c_label_3[8] = '\0';
/*
               if ( !blank_string(linea->c_text_1) )
                  linea->c_text_1[1] = '\0';
               if ( !blank_string(linea->c_text_2) )
                  linea->c_text_2[1] = '\0';
               if ( !blank_string(linea->c_text_3) )
                  linea->c_text_3[1] = '\0';
*/
               break;
            default :
               printf("riga_dati:riga letta di formato non corretto.\n");
               break;
            }
}
/*****************************************/


/*
    Ritorna 0 se la stringa contiene solo dei blank.
*/
int blank_string(char *parola)
{
int i;

i = strlen(parola);
while( (parola[i-1] == ' ')&&(i>0) )
   i--;
return(i);
}



distruggi_figli(int *numero, VEDI_DATI *riga_distr)
{
int k;
int i;
Arg args[50];           /* per settaggio argomenti widgets */

        for(k=0 ; k < *numero ; k++)
           {
/*            printf("tipo=%d\n",riga_distr[k].tipologia_riga);          */
           /* XtDestroyWidget(riga_distr[k].rowcol); */
           if ( riga_distr[k].tipologia_riga == 1 )
              {
                /* printf("sto per distruggere un tipo 1,  k=%d\n",k);
		printf("Stato widget prima %d\n",
			UtStatoWidget(riga_distr[k].w_label_comm)); */
              XtDestroyWidget(riga_distr[k].w_label_comm);
/*              printf("distruggi:common\n");                            */
/*
		printf("Stato widget dopo %d\n",
			UtStatoWidget(riga_distr[k].w_label_comm));
*/
              }
           if ( (riga_distr[k].tipologia_riga == 2) ||
                (riga_distr[k].tipologia_riga == 3) ||
                (riga_distr[k].tipologia_riga == 4)   )
              {
/*              printf("distruggi:prima di label e text _1\n");        */
              XtDestroyWidget(riga_distr[k].w_label_1);
              XtDestroyWidget(riga_distr[k].w_text_1);
/*              printf("distruggi:dopo di label e text _1\n");         */
              if ( (riga_distr[k].tipologia_riga == 3) ||
                   (riga_distr[k].tipologia_riga == 4)   )
                 {
/*                 printf("distruggi:prima di label e text _2\n");     */
                 XtDestroyWidget(riga_distr[k].w_label_2);
                 XtDestroyWidget(riga_distr[k].w_text_2);
/*                 printf("distruggi:dopo di label e text _2\n");      */
                 if ( (riga_distr[k].tipologia_riga == 4) )
                    {
/*                    printf("distruggi:prima di label e text _3\n");  */
                    XtDestroyWidget(riga_distr[k].w_label_3);
                    XtDestroyWidget(riga_distr[k].w_text_3);
/*                    printf("distruggi:dopo di label e text _3\n");   */
                    }
                 }
              }
           }
        *numero = 0;
}



/*
#include <errno.h>
#include "libnet.h"


    In funzione del numero del  modello, dal  numero del blocco, dal
    path del file  f14.dat viene letta per righe la regione dati del
    blocco cercato e memorizzata a partire dal puntatore p_iniz  che
    viene restituito assieme al numero di righe memorizzate.
*/
int new_leggi(int numero_mod,
                   int numero_bl, char **p_iniz,int *nrighe)
{
char path_f14[FILENAME_MAX];
FILE *fp_f14;
char *nome_bl;
char nome[9];
char *p_iniz_tmp;
char riga_f14[LUN_RIGA_F14];
char *ret;
int i=0,dim=0,pos_riga_prec;
int size;
short blocco_trovato=FALSE;
int n_bl_md;
int n_md;


     printf("new_leggi:\n");
     if (numero_mod==1)
        {
        strcpy(path_f14,"../../legocad/tanica/f14.dat");
        if (numero_bl==1)
           strcpy(nome,"TANK");
        else
           strcpy(nome,"VALV");
        }
     else
        {
        strcpy(path_f14,"../../legocad/regola/f14.dat");
        if (numero_bl==1)
           strcpy(nome,"REGO");
        }
     printf("new_leggi:f14=%s  nome=%s\n",path_f14,nome);
/*   Posizionamento sul blocco cercato */
     if ( -1==cerca_blocco_file(path_f14,nome,&fp_f14) )
        {
        fprintf(stderr,"new_leggi: blocco non trovato!\n");
        fclose(fp_f14);
        return(-1);
        }
     pos_riga_prec=ftell(fp_f14);
/*   Calcolo il numero di righe della zona dati da memorizzare */
     fgets(riga_f14,LUN_RIGA_F14,fp_f14);
     dim=1;
     while ( (fgets(riga_f14,LUN_RIGA_F14,fp_f14) !=NULL) &&
              strncmp(riga_f14,HEADER_BLOCCO_F14,strlen(HEADER_BLOCCO_F14)) &&
             (strncmp(riga_f14,FINE_FILE,strlen(FINE_FILE)))   )
        dim++;
     size = sizeof(riga_f14)*dim;
     *p_iniz=(char*)calloc(1,size);
     *nrighe = dim;
     p_iniz_tmp=(*p_iniz);
     fseek(fp_f14,pos_riga_prec,0);
     fgets(riga_f14,LUN_RIGA_F14,fp_f14);
     memcpy(p_iniz_tmp,riga_f14,sizeof(riga_f14));
     p_iniz_tmp+=sizeof(riga_f14);
     while (    (fgets(riga_f14,LUN_RIGA_F14,fp_f14) !=NULL)
             && strncmp(riga_f14,HEADER_BLOCCO_F14,strlen(HEADER_BLOCCO_F14))
             && strncmp(riga_f14,FINE_FILE,strlen(FINE_FILE))                  )
        {
        memcpy(p_iniz_tmp,riga_f14,sizeof(riga_f14));
        p_iniz_tmp+=sizeof(riga_f14);
        }
      p_iniz_tmp=(*p_iniz);
      fclose(fp_f14);
      printf("***********************************************\n");
      for (i=0;i<dim;i++)
        {
        strncpy(riga_f14,p_iniz_tmp,sizeof(riga_f14));
        printf("new:%s",riga_f14);
        p_iniz_tmp+=sizeof(riga_f14);
        }
      printf("***********************************************\n");
      return(1);
}




/*
   Cerca nel file specificato la zona con i dati del blocco nome_bl
   posizionandosi alla riga precedente l'inizio della zona dati.
*/
cerca_blocco_file(char *path_f14,char *nome_bl,FILE **ffp_f14)
{
FILE *fp_f14;
char riga_f14[LUN_RIGA_F14];
char *ret;
int i=0,dim=0,pos_riga_prec;
int size;
short blocco_trovato=FALSE;

     *ffp_f14=fopen(path_f14,"r+");
        if ( *ffp_f14==NULL )
           {
           fprintf(stderr,"cerca_blocco_file:errore apertura f14 ");
           return(-1);
           }
     while (    (fgets(riga_f14,LUN_RIGA_F14,*ffp_f14) !=NULL)
             && (strncmp(riga_f14,HEADER_SEZ_DATI,strlen(HEADER_SEZ_DATI)))
             && (strncmp(riga_f14,FINE_FILE,strlen(FINE_FILE)))          );
     do
        {
        do
           pos_riga_prec=ftell(*ffp_f14);
        while (    ( (ret=fgets(riga_f14,LUN_RIGA_F14,*ffp_f14)) !=NULL)
                && strncmp(riga_f14,HEADER_BLOCCO_F14,strlen(HEADER_BLOCCO_F14))
                && strncmp(riga_f14,FINE_FILE,strlen(FINE_FILE))  );
        if ( !strncmp(&(riga_f14[OFF_NOME_BLOC_DATI]),nome_bl,strlen(nome_bl)) )
              blocco_trovato = TRUE;
        }
     while(     strncmp(riga_f14,FINE_FILE,strlen(FINE_FILE))
             && !blocco_trovato
             && ( (ret=fgets(riga_f14,LUN_RIGA_F14,*ffp_f14)) !=NULL )      );
     if ( !strncmp(riga_f14,FINE_FILE,strlen(FINE_FILE)) || ret==NULL )
        {
        printf("cerca_blocco_file : ATTENZIONE FINE FILE\n");
        return(-1);
        }
     fseek(*ffp_f14,pos_riga_prec,0);
     return(1);
}


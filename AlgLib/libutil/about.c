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
static char SccsID[] = "@(#)about.c	5.1\t11/10/95";
/*
   modulo about.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)about.c	5.1
*/
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <Xm/Text.h>
#include <Xm/MainW.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/BulletinB.h>
#include <Xm/Label.h>
#include <Xm/Separator.h>
#include <Xm/Form.h>
#include <Xm/Xm.h>
#include "versione_processi.h"

char   *getenv ();

static Widget about_widget;
extern NOMI_PROCESSI Nome_del_processo;

static void about_destroy();


void about(topLevel)
Widget topLevel;
{
int i;
Widget wRow, wTopLev, wbutton,wText;
Arg args[50];           /* per settaggio argomenti widgets */
char testo[2000];
char riga[100];


if(about_widget==NULL)
    {
    memset(testo,0,2000);
    memset(riga,0,100);

    i=0;
    XtSetArg (args[i], XmNwidth, 700); i++;
    XtSetArg (args[i], XmNheight, 300); i++;
    XtSetArg (args[i], XmNdefaultPosition, False); i++;
    XtSetArg (args[i], XmNdialogStyle, XmDIALOG_SYSTEM_MODAL); i++;
    wTopLev = XtCreateManagedWidget 
	("About", topLevelShellWidgetClass,topLevel, args, i);

    i = 0;
    about_widget = XmCreateForm (wTopLev, "form_aing", args, i);


    i = 0;
    XtSetArg (args[i], XmNx, 0); i++;
    XtSetArg (args[i], XmNy, 0); i++;
    XtSetArg (args[i], XmNspacing, 0); i++;
    XtSetArg (args[i], XmNorientation, XmVERTICAL); i++;
    XtSetArg (args[i], XmNpacking, XmPACK_NONE); i++;
    XtSetArg (args[i], XmNresizeHeight, False); i++;
    XtSetArg (args[i], XmNresizeWidth, False); i++;
    XtSetArg (args[i], XmNwidth, 700); i++;
    XtSetArg (args[i], XmNheight, 300); i++;
    wRow = XmCreateRowColumn (about_widget, "About", args, i);

    i=0;
    XtSetArg (args[i], XmNx, 0); i++;
    XtSetArg (args[i], XmNy, 0); i++;
    XtSetArg (args[i], XmNwidth, 700); i++;
    XtSetArg (args[i], XmNheight, 240); i++;
    XtSetArg (args[i], XmNeditable, False); i++;
    XtSetArg (args[i], XmNeditMode, XmMULTI_LINE_EDIT); i++;
    XtSetArg (args[i], XmNcursorPositionVisible, False ); i++;

/* testo */
	sprintf (riga,"Processo: %s\n", Nome_del_processo.nome);
	strcat(testo,riga);
	sprintf (riga,"Versione: %s\n", Nome_del_processo.versione);
	strcat(testo,riga);
#if defined PIACENZA
	sprintf(riga,"Applicazione sviluppata per: DPTSAP Piacenza\n");
#endif
#if defined ENEL_CRA
	sprintf(riga,"Applicazione sviluppata per: ENEL C.R.A. Milano\n");
#endif
	strcat(testo,riga);
	sprintf (riga,"Data: %s\n", Nome_del_processo.data);
	strcat(testo,riga);
	sprintf (riga,"Output: terminale\n");
	strcat(testo,riga);
#if defined F22_APPEND
	sprintf (riga,"Gestione f22: apertura in append mode\n");
	strcat(testo,riga);
#endif
#if defined LASTSNAP
	sprintf (riga,"Gestione snapshot: registrazione automatica al termine della simulazione \n");
	strcat(testo,riga);
#endif
#if defined BANCO_ISTRUTTORE
	sprintf (riga,"Interfacciamento Banco Istruttore: abilitato\n");
	strcat(testo,riga);
#endif
#if defined BANCO_MANOVRA
	sprintf (riga,"Interfacciamento Banco Manovra: abilitato\n");
	strcat(testo,riga);
#endif
#if defined SCADA
	sprintf (riga,"Interfacciamento Scada: abilitato\n");
	strcat(testo,riga);
#endif
#if defined BACKTRACK
	sprintf (riga,"Gestione Backtrack: abilitata\n");
	strcat(testo,riga);
#endif
#if defined SAVEPERT
	sprintf (riga,"Registrazione Perturbazioni: abilitata\n");
	strcat(testo,riga);
#endif
#if defined REPLAY
	sprintf (riga,"Gestione REPLAY: abilitata\n");
	strcat(testo,riga);
#endif
#if defined MFFR
	sprintf (riga,"Gestione Malfunzioni e Funzioni Remote: abilitata\n");
	strcat(testo,riga);
#endif

    XtSetArg (args[i], XmNvalue, testo); i++;


    wText=XmCreateText(wRow, "text", args, i);
    XtManageChild (wText);


    i=0;
    XtSetArg (args[i], XmNx, 300); i++;
    XtSetArg (args[i], XmNy, 250); i++;
    XtSetArg (args[i], XmNwidth, 150); i++;
    XtSetArg (args[i], XmNheight, 40); i++;
    XtSetArg (args[i], XmNlabelString, 
	XmStringCreateLtoR ("    Quit    ", XmSTRING_DEFAULT_CHARSET)); i++;
    wbutton = XmCreatePushButton (wRow, "bottone", args, i);
    XtAddCallback (wbutton, XmNactivateCallback, (XtCallbackProc)about_destroy, NULL);
    XtManageChild (wbutton);


    XtManageChild (wRow);
    XtManageChild (about_widget);
    }

}

static void about_destroy(w, info, str)
        Widget w;
caddr_t info;
XmSelectionBoxCallbackStruct * str;
{
	XtDestroyWidget (XtParent(about_widget));
        about_widget=NULL;
}

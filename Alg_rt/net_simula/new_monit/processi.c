/**********************************************************************
*
*       C Source:               processi.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Nov  8 17:36:05 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: processi.c-9 %  (%full_filespec: processi.c-9:csrc:1 %)";
#endif

/*
 * processi.c
 *
 * funzioni relative alla attivazione e monitoraggio processi
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>

#include <X11/Xlib.h>
#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/ToggleB.h>
#include <Xm/RowColumn.h>

#include "sim_param.h"
#include "sim_types.h"
#include "dispatcher.h"
#include "ric_aing.h"
#include "option.h"
#include "messaggi.h"
#include "processStart.h"

#include "parametri.h"

extern VARIABILI *variabili;
extern char *ind_sh_top;
extern int id_sh;
extern int nmod;
extern int tot_variabili;
extern OPTIONS_FLAGS options;
void act_selection_display ();

RICHIESTA_AING richiesta_aing;  /* struttura per richiesta aing */
int stato_aing=0; /* 1 processo aing gia' attivato */
int pid_aing= -1;
extern int id_msg_aing;    /* coda di messaggi con aing */

char listaDisplay[MAX_DISPLAY][MAX_DISPLAY_NAME];

int attiva_aing (w, label)
Widget w;    /* interfaccia chiamante   */
char *label;
{
char *proc_argv[4];
char *proc_envp[8];
char proc_name[FILENAME_MAX];
char *path;
// char *getenv();
int indx;
int jjj;

/* verifica la necessita' di lanciare il processo aing */
stato_aing=stato_processo(pid_aing);
if(stato_aing<=0)
 {
 /* lancia il processo aing */
 path=getenv("LEGORT_BIN");

 proc_argv[0]=(char*)malloc(100);
 proc_argv[1]=(char*)malloc(100);
 proc_argv[2]=(char*)malloc(100);
 proc_envp[0]=(char*)malloc(100);
 proc_envp[1]=(char*)malloc(100);
 proc_envp[2]=(char*)malloc(100);
 proc_envp[3]=(char*)malloc(FILENAME_MAX);
 proc_envp[4]=(char*)malloc(100);
 proc_envp[5]=(char*)malloc(100);
 proc_envp[6]=(char*)malloc(FILENAME_MAX);
 proc_envp[7]=NULL;


#if defined UNIX
 sprintf(proc_name,"%s/xaing\00",path); 
#endif
#if defined VMS
 sprintf(proc_name,"%sxaing\00",path);
#endif
 sprintf(proc_argv[0],"xaing\00");
 sprintf(proc_argv[1],"%d\00",1);
 proc_argv[2]=NULL;
#if defined UNIX
 sprintf(proc_envp[0],"DISPLAY=%s\00",getenv("DISPLAY"));
 sprintf(proc_envp[1],"SHR_USR_KEY=%s\00",getenv("SHR_USR_KEY"));
 sprintf(proc_envp[2],"SHR_TAV_KEY=%s\00",getenv("SHR_TAV_KEY"));
 sprintf(proc_envp[3],"LEGORT_BIN=%s\00",getenv("LEGORT_BIN"));
 sprintf(proc_envp[4],"HOME=%s\00",getenv("HOME"));
 sprintf(proc_envp[5],"DEBUG=%s\00",getenv("DEBUG"));
 sprintf(proc_envp[6], "LD_LIBRARY_PATH=%s\00", getenv("LD_LIBRARY_PATH"));
 proc_envp[7]=NULL;

for(jjj=0; jjj < 7; jjj++) {
printf("banco:prima di lanciare xaing: proc_envp[%d]=%s\n", jjj, proc_envp[jjj]);
} 


#endif
#if defined VMS
 proc_envp[0]=NULL;
#endif
#ifndef SCO_UNIX
 pid_aing = fork();
#else
 pid_aing = fork();
#endif
 stato_aing=pid_aing;
 if(stato_aing==(-1))
    perror("vfork aing");
 if ( stato_aing == 0 )
      {
#ifndef SCO_UNIX
      sigsetmask(0);      /* sblocca tutti i segnali */
#endif

printf ("Attivazione [%s]\n",proc_name);

      execve(proc_name,proc_argv,proc_envp);
      perror("execve aing");
      exit(0);
      }
 }

if ((indx = get_label_indx (label)) >= 0)
	{
	strcpy(richiesta_aing.nome_variabile,variabili[indx].nome);
	richiesta_aing.mtype=RIC_AING;
	msg_snd(id_msg_aing,&richiesta_aing,
   	sizeof(RICHIESTA_AING) - sizeof(long),IPC_NOWAIT);
	}
	
return (0);
}
/*****************************************************************/
int crea_display_selection (w, p)
Widget w;                    /* chiamante                        */
OPTIONS_FLAGS p;             /* struttura opzioni                */
{
_UxCprocessStart *Ctx;
int i;

	Ctx = (_UxCprocessStart *)UxGetContext (w);

   /* Creation of menu8_p1 */
   Ctx->UxMenuShellDisplay = XtVaCreatePopupShell ("menu8_p1_shell",
         xmMenuShellWidgetClass, Ctx->UxdisplaySelectForm,
         XmNwidth, 1,
         XmNheight, 1,
         XmNallowShellResize, TRUE,
         XmNoverrideRedirect, TRUE,
         NULL );

   Ctx->Uxmenu8_p1 = XtVaCreateWidget( "menu8_p1",
         xmRowColumnWidgetClass,
         Ctx->UxMenuShellDisplay,
         XmNrowColumnType, XmMENU_PULLDOWN,
         NULL );
   UxPutContext( Ctx->Uxmenu8_p1, (char *) Ctx );


	for (i=0; i<MAX_DISPLAY; i++)
		{
		strcpy (listaDisplay[i],p.options_display.display_name[i]);
		if (!strcmp(listaDisplay[i],""))
			continue;
   	Ctx->UxdisplaySelectionButton[i] = XtVaCreateManagedWidget( "",
         xmPushButtonWidgetClass, Ctx->Uxmenu8_p1,
         RES_CONVERT( XmNlabelString, listaDisplay[i]),
         NULL );
   	UxPutContext( Ctx->UxdisplaySelectionButton[i], (char *) Ctx );
		XtAddCallback ( Ctx->UxdisplaySelectionButton[i],
					XmNactivateCallback, act_selection_display,
							listaDisplay[i]);
		}


   /* Creation of menu8 */
   Ctx->UxdisplayMenu = XtVaCreateManagedWidget( "menu8",
         xmRowColumnWidgetClass,
         Ctx->UxdisplaySelectForm,
         XmNrowColumnType, XmMENU_OPTION,
         XmNsubMenuId, Ctx->Uxmenu8_p1,
         RES_CONVERT( XmNlabelString, PROC_START_DISPLAY ),
         XmNx, 60,
         XmNy, 100,
         NULL );
   UxPutContext( Ctx->UxdisplayMenu, (char *) Ctx );

	return (0);
}
/********************************************************************/
/*
 * gestione selezione display
 */
void act_selection_display (w, data, reason)
Widget w;
char *data;
XmPushButtonCallbackStruct *reason;
{
_UxCprocessStart *Ctx;

	Ctx = (_UxCprocessStart *)UxGetContext (w);
	strcpy (Ctx->UxselectedDisplay,data);
printf ("callback: display = [%s]\n",Ctx->UxselectedDisplay);
	return;
}

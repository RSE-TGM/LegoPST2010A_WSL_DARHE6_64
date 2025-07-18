/**********************************************************************
*
*       C Source:               other.c
*       Subsystem:              2
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Jul 19 11:06:32 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: other.c-11 %  (%full_filespec: other.c-11:csrc:2 %)";
#endif
/*
        Inizio sezione per SCCS
*/
/*
   modulo other.c
   tipo 
   release 5.3
   data 2/16/96
   reserved @(#)other.c	5.3
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)other.c	5.3\t2/16/96";
/*
        Fine sezione per SCCS
*/

/****************************************************************
		file: other.c

	File contenente tutte le routine di appoggio elaborate
	esternamente a Uimx 
****************************************************************/
#include <sys/types.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>
#ifndef VMS
#include <sys/wait.h>
#endif
#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include <Xm/PushB.h>
#include <Xm/Label.h>
#include <Xm/RowColumn.h>
#include <Xm/TextF.h>
#include <Xl/Xl.h>
#include <Ol/OlDatabaseTopologia.h>
#include <Ol/OlForm.h>
#include <Xl/XlCoreP.h>
#include <Xl/XlPort.h>
#include <Xl/XlManager.h>
#include <Xl/XlCompositeP.h>
#include "res_edit.h"
#include "config.h"
#include "libutilx.h"
#include "Lucchetto.bmp"
//#include "other.h"

extern int PushColorCB(),PushFontCB(),OptMenuCB(),OptResCB();
extern int PushResCB(),TextResCB(),PushIconCB();
extern int PushVarInpCB(),PushVarOutCB(),PushVarRegCB();
extern int PushCompCB(),PushSubSCB();
extern int PushFormCB(),PushInputCB();
extern Widget CreaPushButton(),CreaTextField();
extern char *CvtPixToStr();
OlFormObject ResGetForm (Widget );

int NumGruppi = 7;
char *Gruppi_resource [] = {	"Geometric",
                       		"Specific",
		       		"Color Attribute",
				"Change Color Var 1",
				"Change Color Var 2",
				"Change Color Var 3",
				"Change Color Var 4"};
#ifdef VMS
XtIntervalId timer; /* ID del timer utilizzato per la temporizzazione
                       del refresh grafici */

/*----------------------------------------------
 * procedura periodica legata all'Xtimeout 
 * per il refresh della lista della interfaccia  
 *----------------------------------------------*/
static void timer_proc(client_data,id)
caddr_t client_data;
XtIntervalId *id;
{
   extern void RefreshLista(); /* funzione definita a livello di applicativo */
   extern void rimuovi_callback();
   PROG_DATA *pdata;

   pdata = (PROG_DATA *)client_data;

/*
   printf("timer_proc: stato_processo -> %d\n", pdata->fpid);
*/

   if( stato_processo( pdata->fpid) == 0) /* figlio terminato */
   {
      rimuovi_callback();
      if( XtIsRealized(pdata->ogg) && XtIsManaged(pdata->ogg) )
      {
         RefreshLista(); 
      }
   }
   else
   {
        timer= XtAppAddTimeOut( XtWidgetToApplicationContext( pdata->ogg ),
                          (unsigned long)1000,timer_proc,pdata);
        pdata->Itimer = timer;
   }
}

/*-------------------------------------------------------------------
 *    Routine che permette dilanciare un eseguibile che richieda di
 *       specificare un numero di parametri arbitrario;la lista deve
 *       iniziare con il nome dell'eseguibile e quindi deve proseguire
 *       con l'elenco dei parametri;la lista deve essere terminata con
 *       un NULL;
 *-------------------------------------------------------------------*/   
PROG_DATA *ActiveProgWithParameter (char * StringaEseguibile, ...)
{    
   int pid;
   int i;
   char *argomento; /* puntatore di appoggio per contenere di volta in volta
                       un nuovo argomento */

#define MAX_ARGOMENTI 10  /* numero massimo di argomenti di chiamata per
                             la function attiva_prog_par */
   char *argv[MAX_ARGOMENTI];
   char *newarg[MAX_ARGOMENTI];
   va_list args;
   PROG_DATA *prog_data;
   char prgname[200];

   argv[0]=StringaEseguibile;
/* leggo gli argomenti */
   va_start(args, StringaEseguibile);
   i=1;
   while ((argomento=va_arg(args,char *))!=0)
   {
      argv[i]=argomento;
      i++;
      if(i==MAX_ARGOMENTI)
      {
         printf("ActiveProgWhitParameter: Max number of argument!\n");
         exit(1);
      }
   }

   argv[i]=argomento;
   va_end(args);

   prog_data = XtMalloc(sizeof(PROG_DATA));


/* il primo argomento che mi aspetto e' l'ID di uno widget da cui ricavare
   il context, gli altri sono gli argomenti argc,argv per la exec
   del programma bitmap o draw e utilizzo newarg per questi ultimi
*/

   newarg[0] = argv[1];
   newarg[1] = argv[2];
   newarg[2] = argv[3];
   newarg[3] = argv[4];
   newarg[4] = NULL;


   strcpy(prgname,XlGetenv("LEGOMMI_BIN"));
   strcat(prgname,newarg[0]);
   strcat(prgname,".exe");
   
#if defined SCO_UNIX
   if((pid=fork())==0)
#else
   if((pid=vfork())==0)
#endif
   {
      execv(prgname,newarg);
   }
   else   /* caso padre */
   {
      prog_data->ogg = argv[0];

      prog_data->fpid = pid;
/*
      printf("attivazione prog_data->ogg %d --- prog_data->fpid %d\n",
                prog_data->ogg,prog_data->fpid);
*/
/*
      timer=XtAppAddTimeOut(XtWidgetToApplicationContext(argv[0]),
                      (unsigned long)1000,timer_proc,prog_data);
*/
      timer = XtAppAddTimeOut(XtWidgetToApplicationContext(argv[0]),
                              (unsigned long)1000,timer_proc,prog_data);
      prog_data->Itimer = timer;
      return(prog_data);
   }
   return(0);
}

#endif
#ifndef VMS
/************************************************
     Routine che riceve il segnale di chiusura dell'eseguibile al quale
        e' stato associato ed esegue quindi una routine definita a
        livelLo di applicativo;
void CloseProgram
        (
        segnale                 -->
        code                    -->
        scp                     -->
        )

        Valore di Ritorno       -->  Nessun valore di ritorno;

*************************************************/
void CloseProgram(segnale,code,scp)
int segnale,code;
struct sigcontext *scp;
{
extern void RefreshLista(); /* funzione definita a livello di
                                     applicativo */
#ifdef ULTRIX
union wait status;
#elif AIX || defined SCO_UNIX || LINUX
int status;
#elif OSF1
pid_t status;
#else
#endif

if (segnale == SIGCHLD)
        {
        wait(&status);
        signal(SIGCHLD,(SIG_DFL) );
        RefreshLista();
        }
}

/***************************************************
    Routine che permette dilanciare un eseguibile che richieda di
        specificare un numero di parametri arbitrario;la lista deve
        iniziare con il nome dell'eseguibile e quindi deve proseguire
        con l'elenco dei parametri;la lista deve essere terminata con
        un NULL;
    Esempio:
        ActiveProgWithParameter (nome_eseguibile,par1,par2, ...,(char *)0);

        Il Numero massimo di parametri e' fissato da MAX_ARGOMENTI;

int ActiveProgWithParameter
        (
        va_list                 -->  Lista degli argomenti;
        )

        Valore di ritorno       -->  Viene ritornato il pid del processo
                                        associato al programma lanciato;
****************************************************/
int ActiveProgWithParameter (char * StringaEseguibile, ...)
{
int pid;
int i;
char *argomento; /* puntatore di appoggio per contenere di volta in volta
                    un nuovo argomento */
#define MAX_ARGOMENTI 10  /* numero massimo di argomenti di chiamata per
                             la function attiva_prog_par */
char *argv[MAX_ARGOMENTI];
va_list args;
argv[0]=StringaEseguibile;
va_start(args, StringaEseguibile);
i=1;
while ((argomento=va_arg(args,char *))!=0)
        {
        argv[i]=argomento;
        i++;
        if(i==MAX_ARGOMENTI)
                {
                printf("ActiveProgWhitParameter: Max number of argument!\n");
                exit(1);
                }
        }
argv[i]=argomento;
va_end(args);
#ifndef DESIGN_TIME
signal(SIGCHLD,CloseProgram);
#if defined SCO_UNIX
if((pid=fork())==0)
#else
if((pid=vfork())==0)
#endif
        {
        execvp(argv[0],argv);
        }
else
{
        return(pid);
}
#else
printf("Simula attivazione \n");
#endif
return(1);
}

/********************************************
    Routine che uccide un processo dal pid:

void KillPrecess
        (
        pid                     -->  Pid del processo da uccidere;
        )

        Valore di ritorno       -->  Nessun valore di ritorno;

**********************************************/
void KillProcess (pid)
int pid;
{
char Numero[10];
char Comando[50];

sprintf (Numero,"%d",pid);
strcpy (Comando,"kill ");
strcat (Comando,Numero);
/*
printf ("Eseguo comando: [%s]\n",Comando);
*/
system (Comando);
}
#endif  /*---------------- endif VMS -----------------*/

/*
 PagGetType
 restituisce il tipo di pagina: attenzione!! serve solo
 per il main di prova in resource; la versione reale e'
 in config
*/
#ifndef ON_PAGEDIT
int PagGetType(PAGINA *pag)
{
    if( !strcmp(pag->geom.tipo,TIPO_SINOTTICO) )
       return(TYPE_SINOTTICO);
    if( !strcmp(pag->geom.tipo,TIPO_STAZIONI) )
       return(TYPE_STAZIONE);
    if( !strcmp(pag->geom.tipo,TIPO_LIBRERIA) )
       return(TYPE_LIBRERIA);
    if( !strcmp(pag->geom.tipo,TIPO_REGOLAZIONE) )
       return(TYPE_REGOLAZIONE);
}
#endif

/**********************************************************
	Restituisce True o False se wid e' o meno
	un oggetto XlComposite
        (per evitare problemi con AIC)
**********************************************************/
int EComposite (Widget wid)
{
	return ( XlIsXlComposite (wid) );
}

/*********************************************************
	Restituisce l'ID dell'oggetto padre dell'oggetto
	'wid' passato come parametro
        (per evitare problemi con AIC)
*********************************************************/
Widget GetPadre (Widget wid)
{
	return ( XtParent (wid) );
}

/*********************************************************
	Restituisce un puntatore ad una stringa contenente
	il nome dell'oggetto 'wid' passato come parametro
        (per evitare problemi con AIC)
*********************************************************/
char *WidGetName (Widget wid)
{
	return (XtName (wid) );
}

/*********************************************************
	Restituisce un puntatore alla classe dell'oggetto
	'wid' passato come parametro
        (per evitare problemi con AIC)
*********************************************************/
WidgetClass GetClass (Widget wid)
{
	return (XtClass (wid) );
}

/*********************************************************
	Restituisce True o False se l'oggetto passato
	come parametro e o meno visualizzato
        (per evitare problemi con AIC)
*********************************************************/
int Usato (Widget wid)
{
	return ( XtIsManaged (wid) );
}

/*********************************************************
	Restituisce il puntatore al display associato 
	allo Widget passato come parametro
        (per evitare problemi con AIC)
*********************************************************/
Display *GetDisplay (Widget wid)
{
	return ( XtDisplay (wid) );
}

/************************************************************
	   Funzione SettaModifica: setta la label per la segnalazione
	delle modifiche effettuate con il valore di 
	modificato  
************************************************************/
int SettaModifica (Widget wid)
{
	char Appo[3];
	XmString StrLab;
	
	strcpy (Appo,"|");
	StrLab = XmStringCreateSimple (Appo);
	set_something_val (wid, XmNlabelString, (XtArgVal) StrLab);
	XmStringFree (StrLab);
	return (OK);
}

/************************************************************
	Funzione che crea una label
************************************************************/
Widget CreaLabel (parent, nome, label, width)
Widget parent;
char *nome;
XmString label;
Dimension width;
{
	Widget appo;
	Arg args[10];
	int narg;

	narg = 0;
	XtSetArg (args[narg], XmNmarginHeight, 0); narg++;
	XtSetArg (args[narg], XmNmarginTop, 0); narg++;
	XtSetArg (args[narg], XmNmarginBottom, 0); narg++;
	if (width != 0)
	{
		XtSetArg (args[narg], XmNrecomputeSize, FALSE ); narg++;
		XtSetArg (args[narg], XmNwidth, width ); narg++;
	}
	XtSetArg (args[narg], XmNlabelString, label); narg++;
	XtSetArg (args[narg], XmNalignment, XmALIGNMENT_BEGINNING); narg++;
	appo = XmCreateLabel (parent, nome, args, narg);
	XtManageChild (appo);
	return (appo);
}

/************************************************************
	Inserisce una label; se la risorsa e' libera la viene 
	utilizzata per la visualizzazione delle modifiche o
	degli errori in input, se la risorsa e' LOCKED la 
	label viene utilizzata per indicare con un lucchetto
	che la risorsa e' LOCKED
************************************************************/
void InserisciLabelErr (XlConfInfo conf,Widget RowC,Widget WidSelected,int TipoP)
{
char s[128];
Arg args[20];
Widget Ritorno;
XmString StrLab;
int narg;
Pixmap Disegno;

strcpy (s,"ModErrLab");
StrLab = XmStringCreateSimple(" ");
if ( (conf.confinfo_type > LOCKED_PAG) && ( (TipoP==TYPE_SINOTTICO) ||
	(TipoP==TYPE_STAZIONE) || (TipoP==TYPE_REGOLAZIONE) ) )
  {
  /*  Carico il file del lucchetto  */
  LoadBitmap (WidSelected,&Disegno,Lucchetto_bits,Lucchetto_width,Lucchetto_height);

  /*  Creo la label con il Pixmap  */
  narg = 0;
  XtSetArg (args[narg], XmNmarginHeight, 0); narg++;
  XtSetArg (args[narg], XmNmarginTop, 0); narg++;
  XtSetArg (args[narg], XmNmarginBottom, 0); narg++;
  XtSetArg (args[narg], XmNlabelType, XmPIXMAP); narg++;
  XtSetArg (args[narg], XmNlabelPixmap, Disegno); narg++;
  XtSetArg (args[narg], XmNlabelInsensitivePixmap, Disegno); narg++;
  Ritorno = XmCreateLabel (RowC,s,args,narg);
  XtManageChild (Ritorno);
  }
else
  /*  Creo la label per gli errori o le modifiche  */
  Ritorno = CreaLabel (RowC,s,StrLab,20);
XmStringFree (StrLab);
}

/************************************************************
	Inserisce nel rowcolumn passato come parametro gli
	oggetti relativi alla risorsa di tipo XlRAnimatedColor 
************************************************************/
void InserisciXlRAnimatedColor (Widget Padre,  /* Oggetto selezionato sulla
                                          drawing area */
                        Widget RC,     /* Row col. su cui creare gli
                                          oggetti */
                        XlConfInfo conf,  /* confinfo relativa alla
                                             singola risorsa */
                        int NumRiga,      /* indice della confinfo
                                             nel vettore delle confinfo
                                             dell'oggetto */
                        int TipoP)        /* indica se la risorsa
                                             e' locked */
{
char s[128],*Value;
Widget Wid;
XmString StrLab;
XlAnimatedColor AnCol;
Pixel AnColPix;
Arg args[3];
char appo[300], immo[300];

/*  Crea il pushButton   */
strcpy (s,"pushButt");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaPushButton (RC,s,StrLab,250);
XtAddCallback (Wid,XmNactivateCallback,(XtCallbackProc)PushColorCB,(XtPointer)NumRiga);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");


// printf("resource name %s\n",conf.resource_name);


        XtSetArg (args[0], conf.resource_name, &AnCol);
        XtGetValues (Padre, args, 1);

/*
        printf("valori risorse lette\n");
        printf("AnCol.colore = %d\n",AnCol.colore); 
        printf("AnCol.blink_rate = %f\n",AnCol.blink_rate); 
        printf("AnCol.trasparent = %d\n",AnCol.trasparent); 
*/

Value = (char *)CvtPixToStr (Padre,conf.resource_name);

sprintf(appo, "%s %f %d", Value, AnCol.blink_rate, AnCol.trasparent);

printf("InserisciXlRAnimatedColor: contenuto = %s %f %d ", Value, AnCol.blink_rate, AnCol.trasparent);

Wid = CreaTextField (RC,s,appo,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Value);

/*
printf("Uscito InserisciXlRAnimatedColor.n");
*/
}

/************************************************************
	Inserisce nel rowcolumn passato come parametro gli
	oggetti relativi alla risorsa di tipo XlRColor 
************************************************************/
void InserisciXlRColor (Widget Padre,  /* Oggetto selezionato sulla
                                          drawing area */
			Widget RC,     /* Row col. su cui creare gli
                                          oggetti */
			XlConfInfo conf,  /* confinfo relativa alla
                                             singola risorsa */
			int NumRiga,      /* indice della confinfo
                                             nel vettore delle confinfo
					     dell'oggetto */                
			int TipoP)        /* indica se la risorsa
                                             e' locked */
{
char s[128],*Value;
Widget Wid;
XmString StrLab;

/*  Crea il pushButton   */
strcpy (s,"pushButt");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaPushButton (RC,s,StrLab,250);
XtAddCallback (Wid,XmNactivateCallback,(XtCallbackProc)PushColorCB,(XtPointer)NumRiga);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
Value = (char *)CvtPixToStr (Padre,conf.resource_name);
Wid = CreaTextField (RC,s,Value,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Value);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa  di tipo XlRFont
************************************************************/
void InserisciXlRFont (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
char s[128],*Value,*Appo;
Widget Wid;
Arg args[1];

/*  Crea il pushButton   */
strcpy (s,"pushButt");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaPushButton (RC,s,StrLab,250);
XtAddCallback (Wid,XmNactivateCallback,(XtCallbackProc)PushFontCB,(XtPointer)NumRiga);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&Value);
XtGetValues (Padre,args,1);
Appo = XtNewString (Value);
Wid = CreaTextField (RC,s,Appo,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Appo);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa di tipo XlROption
************************************************************/
void InserisciXlROption (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
Widget Wid,menu_shell,menu1_p1,menu1,*Wid_push;
char s[128],s1[128],s2[128],s_menu[128],*Value,*token;
int k,valore;
Arg args[1];

/*  Crea la label   */
strcpy (s,"label");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaLabel (RC,s,StrLab,250);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il MenuOption  */
strcpy (s, "rca");
strcpy (s1, "rcb");
strcpy (s_menu, "menu");

/*  Crea la shell che gestira' l'OptMenu  */
menu_shell = XtVaCreatePopupShell (s_menu,
	xmMenuShellWidgetClass, RC,
	XmNwidth, 1,
	XmNheight, 1,
	XmNallowShellResize, TRUE,
	XmNoverrideRedirect, TRUE,
	NULL );

/*  Crea il pane principale  */
menu1_p1 = XtVaCreateWidget (s1,
	xmRowColumnWidgetClass, menu_shell,
	XmNmarginHeight,0,
	XmNrowColumnType, XmMENU_PULLDOWN,
	NULL);

Wid_push=(Widget *)XtCalloc(15,sizeof(Widget));
k=0;
Value=XtNewString(conf.enum_options);
token = strtok (Value,",");
while (token != NULL)
{
        strcpy (s2,"opt");
        StrLab = XmStringCreateSimple (token);
        Wid_push[k]=CreaPushButton(menu1_p1,s2,StrLab,NULL);
        XtAddCallback (Wid_push[k],XmNactivateCallback,(XtCallbackProc)OptResCB,(XtPointer)NumRiga);
        token = strtok (NULL,",");
        k++;
	XmStringFree (StrLab);
}
/* MAURIC 
        printf("InserisciXlROption:   k = %d\n",k);
*/
/*  Legge la selezione attualmente attiva */
XtSetArg (args[0], conf.resource_name, &valore);
XtGetValues (Padre, args, 1);

/* Crea il rowcolumn che contiene tutto
        l'optionmenu   */
menu1 = XtVaCreateManagedWidget (s,
	xmRowColumnWidgetClass, RC,
	XmNwidth, 100,
	XmNsubMenuId, menu1_p1,
	XmNmenuHistory, Wid_push[valore],
	XmNrowColumnType, XmMENU_OPTION,
	NULL);

XtFree (Value);
XtFree (Wid_push);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa di tipo XlRDimension
************************************************************/
void InserisciXlRDimension (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
Arg args[1];
Dimension dimen;
char s[128],*Value;
Widget Wid;

/*  Crea la label   */
strcpy (s,"label");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaLabel (RC,s,StrLab,250);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&dimen);
XtGetValues (Padre,args,1);
Value = (char *)XtCalloc (10,sizeof(char));
sprintf (Value,"%d",dimen);
Wid = CreaTextField (RC,s,Value,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Value);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa passata nella confinfo
************************************************************/
void InserisciXlRPosition (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
Arg args[1];
Position posiz;
char s[128],*Value;
Widget Wid;

/*  Crea la label   */
strcpy (s,"label");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaLabel (RC,s,StrLab,250);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&posiz);
XtGetValues (Padre,args,1);
Value = (char *)XtCalloc (10,sizeof(char));
sprintf (Value,"%d",posiz);
Wid = CreaTextField (RC,s,Value,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Value);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa passata nella confinfo
************************************************************/
void InserisciXlRTipoVarInp (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
	OlDatabaseTopologiaObject Db, /* Database topologia corrente:
					 serve per vedere se il database
                                         non e' allocato ed in tal caso
				         rendere insensitive il bottone di 
					 richiamo del VariableEditor */
				int TipoP)
{
XmString StrLab;
char s[128],*Value,*Appo;
Widget Wid;
Arg args[1];

/*  Crea il pushButton   */
strcpy (s,"pushButt");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaPushButton (RC,s,StrLab,250);
XtAddCallback (Wid,XmNactivateCallback,(XtCallbackProc)PushVarInpCB,(XtPointer)NumRiga);
XmStringFree (StrLab);
if (Db == NULL)
	set_something_val (Wid, XmNsensitive, (XtArgVal) False);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&Value);
XtGetValues (Padre,args,1);
Appo = XtNewString (Value);
Wid = CreaTextField (RC,s,Appo,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Appo);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa passata nella confinfo
************************************************************/
void InserisciXlRTipoVarReg (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
char s[128],*Value,*Appo;
Widget Wid;
Arg args[1];

/*  Crea il pushButton   */
strcpy (s,"pushButt");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaPushButton (RC,s,StrLab,250);
XtAddCallback (Wid,XmNactivateCallback,(XtCallbackProc)PushVarRegCB,(XtPointer)NumRiga);
XmStringFree (StrLab);
if (ResGetForm(Padre) == NULL)
	set_something_val (Wid, XmNsensitive, (XtArgVal) False);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&Value);
XtGetValues (Padre,args,1);
Appo = XtNewString (Value);
Wid = CreaTextField (RC,s,Appo,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Appo);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa passata nella confinfo
************************************************************/
void InserisciXlRFile (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
char s[128],*Value,*Appo;
Widget Wid;
Arg args[1];

/*  Crea il pushButton   */
strcpy (s,"pushButt");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaPushButton (RC,s,StrLab,250);
XtAddCallback (Wid,XmNactivateCallback,(XtCallbackProc)PushIconCB,(XtPointer)NumRiga);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&Value);
XtGetValues (Padre,args,1);
Appo = XtNewString (Value);
Wid = CreaTextField (RC,s,Appo,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Appo);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa passata nella confinfo
************************************************************/
void InserisciXlRInputValue (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
char s[128],*Value,*Appo;
Widget Wid;
Arg args[1];

/*  Crea il pushButton   */
strcpy (s,"pushButt");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaPushButton (RC,s,StrLab,250);
XtAddCallback (Wid,XmNactivateCallback,(XtCallbackProc)PushInputCB,(XtPointer)NumRiga);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&Value);
XtGetValues (Padre,args,1);
Appo = XtNewString (Value);
Wid = CreaTextField (RC,s,Appo,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Appo);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa passata nella confinfo
************************************************************/
void InserisciXlRForm (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
char s[128],*Value,*Appo;
Widget Wid;
Arg args[1];

/*  Crea il pushButton   */
strcpy (s,"pushButt");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaPushButton (RC,s,StrLab,250);
XtAddCallback (Wid,XmNactivateCallback,(XtCallbackProc)PushFormCB,(XtPointer)NumRiga);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&Value);
XtGetValues (Padre,args,1);
Appo = XtNewString (Value);
Wid = CreaTextField (RC,s,Appo,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Appo);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa passata nella confinfo
************************************************************/
void InserisciXlRSubSystem (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
char s[128],*Value,*Appo;
Widget Wid;
Arg args[1];

/*  Crea il pushButton   */
strcpy (s,"pushButt");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaPushButton (RC,s,StrLab,250);
XtAddCallback (Wid,XmNactivateCallback,(XtCallbackProc)PushSubSCB,(XtPointer)NumRiga);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&Value);
XtGetValues (Padre,args,1);
Appo = XtNewString (Value);
Wid = CreaTextField (RC,s,Appo,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Appo);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa passata nella confinfo
************************************************************/
void InserisciXlRComponent (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
char s[128],*Value,*Appo;
Widget Wid;
Arg args[1];

/*  Crea il pushButton   */
strcpy (s,"pushButt");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaPushButton (RC,s,StrLab,250);
XtAddCallback (Wid,XmNactivateCallback,(XtCallbackProc)PushCompCB,(XtPointer)NumRiga);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&Value);
XtGetValues (Padre,args,1);
Appo = XtNewString (Value);
Wid = CreaTextField (RC,s,Appo,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Appo);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa passata nella confinfo
************************************************************/
void InserisciXlRTipoVarOut (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
			OlDatabaseTopologiaObject Db,int TipoP)
{
XmString StrLab;
char s[128],*Value,*Appo;
Widget Wid;
Arg args[1];

/*  Crea il pushButton   */
strcpy (s,"pushButt");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaPushButton (RC,s,StrLab,250);
XtAddCallback (Wid,XmNactivateCallback,(XtCallbackProc)PushVarOutCB,(XtPointer)NumRiga);
XmStringFree (StrLab);
if (Db == NULL)
	set_something_val (Wid, XmNsensitive, (XtArgVal) False);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&Value);
XtGetValues (Padre,args,1);
Appo = XtNewString (Value);
Wid = CreaTextField (RC,s,Appo,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Appo);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa passata nella confinfo
************************************************************/
void InserisciXlRText (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
char s[128],*Value,*Appo;
Widget Wid;
Arg args[1];

/*  Crea la label  */
strcpy (s,"label");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaLabel (RC,s,StrLab,250);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&Value);
XtGetValues (Padre,args,1);
Appo = XtNewString (Value);
Wid = CreaTextField (RC,s,Appo,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Appo);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa passata nella confinfo
************************************************************/
void InserisciXlRFloat (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
char s[128],*Value;
Widget Wid;
Arg args[1];
float Valore;

/*  Crea la label   */
strcpy (s,"label");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaLabel (RC,s,StrLab,250);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
Value = (char *)XtCalloc (40,sizeof(char));
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&Valore);
XtGetValues (Padre,args,1);
sprintf (Value,"%g",Valore);
Wid = CreaTextField (RC,s,Value,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Value);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa passata nella confinfo
************************************************************/
void InserisciXlRInt (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
char s[128],*Value;
Widget Wid;
Arg args[1];
int Valore;

/*  Crea la label   */
strcpy (s,"label");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaLabel (RC,s,StrLab,250);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
Value = (char *)XtCalloc (20,sizeof(char));
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&Valore);
XtGetValues (Padre,args,1);
sprintf (Value,"%d",Valore);
Wid = CreaTextField (RC,s,Value,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Value);
}

/************************************************************
        Inserisce nel rowcolumn passato come parametro gli
        oggetti relativi alla risorsa passata nella confinfo
************************************************************/
void InserisciGenerica (Widget Padre,Widget RC,XlConfInfo conf,int NumRiga,
				int TipoP)
{
XmString StrLab;
char s[128],*Value,*Appo;
Widget Wid;
Arg args[1];

/*  Crea la label   */
strcpy (s,"label");
StrLab=XmStringCreateSimple(conf.confinfo_name);
Wid = CreaLabel (RC,s,StrLab,250);
XmStringFree (StrLab);

/*  Crea la label   */
InserisciLabelErr (conf,RC,Padre,TipoP);

/*  Crea il textField  */
strcpy (s,"textfield");
XtSetArg (args[0], conf.resource_name,&Value);
XtGetValues (Padre,args,1);
Appo = XtNewString (Value);
Wid = CreaTextField (RC,s,Appo,100);
XtAddCallback (Wid,XmNvalueChangedCallback,(XtCallbackProc)TextResCB,(XtPointer)NumRiga);

XtFree (Appo);
}

/***********************************************************
	Controlla se la risorsa puntata dalla confinfo deve essere
	locked, quindi impossibile da settare dal Resource Editor
	o se deve essere libera, quindi modificabile da Resource
	Editor
***********************************************************/
int ControllaLock (int TipoPag,XlConfInfo confi,Widget RCmom,Widget Figlio)
{
int ValRet=confi.confinfo_type;


/*  Controllo se l'oggetto e' una porta di una icona di regolazione
	e ci si trova su una drawing area che non sia di una libreria
	blocco tutte le risorse  */
if ( (XlIsPort (Figlio)) && (TipoPag != TYPE_LIBRERIA) )
  set_something_val (RCmom, XmNsensitive, (XtArgVal) False);

/*
 Caso di risorse locked sia livello di pagina
 che a livello di libreria
*/
if( confi.confinfo_type > LOCKED_PAG_LIB)
	{
	ValRet = confi.confinfo_type - LOCKED_PAG_LIB;
/*  Setto a insensitive il rowcol che contiene gli oggetti
    relativi alla risorsa  */
        set_something_val (RCmom, XmNsensitive, (XtArgVal) False);
	}
/*
 Caso di risorse locked a livello di libreria
*/
else if ( confi.confinfo_type > LOCKED_LIB)
        {
	ValRet = confi.confinfo_type - LOCKED_LIB;
	if(TipoPag == TYPE_LIBRERIA)
		{
		set_something_val (RCmom, XmNsensitive, (XtArgVal) False);
		}
	}
/*
 Caso di risorse locked a livello di pagina
*/
else if ( confi.confinfo_type > LOCKED_PAG )
  {
  ValRet = confi.confinfo_type - LOCKED_PAG;
  switch (TipoPag)
    {
    case TYPE_SINOTTICO:
    case TYPE_STAZIONE:
    case TYPE_REGOLAZIONE:
      /*  Setto a insensitive il rowcol che contiene gli oggetti
	relativi alla risorsa  */
      set_something_val (RCmom, XmNsensitive, (XtArgVal) False);
    break;
    }
  }
return (ValRet);
}

/*************************************************************
	Preparazione delle liste (oggetti grafici relativi)
        delle risorse appartenenti
	al gruppo passato come parametro (Es: Geometric, Specific ...)
*************************************************************/
void PrepListaRes (Widget Widres_rc, /* row column contenitore degli oggetti
                                   descriventi il gruppo; es: 
				   Geometric_RC     */
              Widget Figlio,    /* oggetto selezionato nella drawing area */
              int Gruppo,       /* intero che indica il tipo di gruppo
                                   (Geometrica, Color, Specifica ....) */
	      OlDatabaseTopologiaObject Dbt, /* Database Topologia */
	      int TipoPagina)   /* tipo pagina: se Libreria,Regolazione o
                                   Sinottico .   Serve per gestire a seconda
                                   del tipo di pagina un Lock differente. */
{
	XlConfInfo *confinfo;
	XlCoreClassRec *WidClassSel;
	XlManagerClassRec *WidClassSelM;

	Arg args[10];
	int NumRiga,narg,TipoRes;
	int j,numConf;
	Widget Wid_riga,Wid;
	char s[128],s1[128];
	Pixel Colore;
	XmString XmStringa;

	/*  Lettura della classe dell'oggetto per risalire
		alla struttura "confinfo"   */
	WidClassSel = (XlCoreClassRec *)XtClass(Figlio);
	WidClassSelM = (XlManagerClassRec *)XtClass(Figlio);
	if (Gruppo == XlRGrGeom)
	{
	if(XtIsComposite(Figlio))
		{
		/*  Prende le confinfo di xlmanager */
		confinfo = xlManagerClassRec.xlmanager_class.confinfo;
		numConf = xlManagerClassRec.xlmanager_class.num_confinfo;
		}
	else
		{
		/*  Prende le confinfo di xlcore   */
		confinfo = xlCoreClassRec.xlcore_class.confinfo;
		numConf  = xlCoreClassRec.xlcore_class.num_confinfo;
		}
	}else
	{
		/*  Prende le confinfo relative all'oggetto  */
		if (XlIsXlCore(Figlio))
			{
			confinfo = WidClassSel->xlcore_class.confinfo;
			numConf = WidClassSel->xlcore_class.num_confinfo;
			}
		else
			{
                        confinfo = WidClassSelM->xlmanager_class.confinfo;
                        numConf = WidClassSelM->xlmanager_class.num_confinfo;
			}
	}

	/*  Creazione delle righe contenenti l'intera lista  */

	NumRiga = 0;

	for (j=0; j < numConf; j++)
	{
		/*   Controlla il gruppo della risorsa da
			visualizzare   */
		if (confinfo[j].confinfo_group == Gruppo)
		{
                	/*   Creazione di un rowcol per ogni riga  */
	                strcpy (s,"r_rowcol");
       		        Wid_riga = XtVaCreateWidget (s,
                	xmRowColumnWidgetClass, Widres_rc,
              	  	XmNisAligned, FALSE,
                	XmNpacking, XmPACK_TIGHT,
                	XmNorientation, XmHORIZONTAL,
                	XmNnumColumns, 1,
                	NULL);

			/*  Controllo per il lock delle risorse  */
			TipoRes = ControllaLock (TipoPagina,confinfo[j],Wid_riga,Figlio);

	   	    	switch (TipoRes)
			{
                        case XlRAnimatedColor:
                                /* E' una risorsa relativa ad un colore e
                                quindi viene creata una riga composta da un
                                pushButton, una label per segnalare le
                                modifiche o gli errori in inserimento e
                                infine un textField per l'input diretto del
                                colore    */

                                InserisciXlRAnimatedColor (Figlio,Wid_riga,
                                        confinfo[j],NumRiga,TipoPagina);
                        break;
			case XlRColor:
				/* E' una risorsa relativa ad un colore e
				quindi viene creata una riga composta da un
				pushButton, una label per segnalare le 
				modifiche o gli errori in inserimento e
				infine un textField per l'input diretto del
				colore    */

				InserisciXlRColor (Figlio,Wid_riga,
					confinfo[j],NumRiga,TipoPagina);
			break;
                        case XlROption:
                                /* E' una risorsa che deve essere gestita da
				un MenuOption e quindi viene creata una riga
				composta da una label per il nome della risorsa
				una label per segnalare le modifiche o gli
				errori in inserimento e infine il MenuOption
				per il settaggio della risorsa  */

				InserisciXlROption (Figlio,Wid_riga,
					confinfo[j],NumRiga,TipoPagina);

                        break;
			case XlRTipoVarInp:
				/* E' una risorsa relativa ad una variabile 
				di input dall'MMI e
				quindi viene creata una riga composta da un
				pushButton, una label per segnalare le 
				modifiche o gli errori in inserimento e
				infine un textField per l'input diretto del
				colore    */

				InserisciXlRTipoVarInp (Figlio,Wid_riga,
					confinfo[j],NumRiga,Dbt,TipoPagina);
			break;
			case XlRTipoVarOut:
				/* E' una risorsa relativa ad una variabile
				di output dall'MMI e
				quindi viene creata una riga composta da un
				pushButton, una label per segnalare le 
				modifiche o gli errori in inserimento e
				infine un textField per l'input diretto del
				colore    */

				InserisciXlRTipoVarOut (Figlio,Wid_riga,
					confinfo[j],NumRiga,Dbt,TipoPagina);
			break;
                        case XlRForm:
                                /* E' una risorsa relativa ad un file 
                                quindi viene creata una riga composta da un
                                pushButton, una label per segnalare le
                                modifiche o gli errori in inserimento e
                                infine un textField per l'input diretto del
                                nome file    */

                                InserisciXlRForm (Figlio,Wid_riga,
                                        confinfo[j],NumRiga,TipoPagina);
                        break;
                        case XlRInputValue:
                                /* E' una risorsa relativa a valori di
				input di una form di un modulo di regolazione 
                                quindi viene creata una riga composta da un
                                pushButton, una label per segnalare le
                                modifiche o gli errori in inserimento e
                                infine un textField per l'input diretto del
                                colore    */

                                InserisciXlRInputValue (Figlio,Wid_riga,
                                        confinfo[j],NumRiga,TipoPagina);
                        break;
                        case XlRFile:
                                /* E' una risorsa relativa ad un file 
                                quindi viene creata una riga composta da un
                                pushButton, una label per segnalare le
                                modifiche o gli errori in inserimento e
                                infine un textField per l'input diretto del
                                colore    */

                                InserisciXlRFile (Figlio,Wid_riga,
                                        confinfo[j],NumRiga,TipoPagina);
                        break;
			case XlRSubSystem:
				/* E' una risorsa relativa alla selezione
				di un SubSystem e viene
				qiundi creata un ariga composta da un
				pushButton, una label per segnalare le
				modifiche o gli errori in inserimento e 
				infine un textField per l'input diretto del
				nome del SubSystem   */ 

				InserisciXlRSubSystem (Figlio,Wid_riga,
					confinfo[j],NumRiga,TipoPagina);
			break;
			case XlRComponent:
				/* E' una risorsa relativa alla selezione
				di un Component e viene
				qiundi creata un ariga composta da un
				pushButton, una label per segnalare le
				modifiche o gli errori in inserimento e 
				infine un textField per l'input diretto del
				nome del Component   */ 

				InserisciXlRComponent (Figlio,Wid_riga,
					confinfo[j],NumRiga,TipoPagina);
			break;
                    	case XlRDimension:
                                /* E' una risorsa relativa ad una dimensione
				e quindi viene creata una label per il
				nome della risorsa, una label per la
				segnalazione delle modifiche o degli errori
				e un textfield per l'inserimento del
				valore della risorsa  */

				InserisciXlRDimension (Figlio,Wid_riga,
					confinfo[j],NumRiga,TipoPagina);

			break;
                        case XlRPosition:
                                /* E' una risorsa relativa ad una posizione
                                e quindi viene creata una label per il
                                nome della risorsa, una label per la
                                segnalazione delle modifiche o degli errori
                                e un textfield per l'inserimento del
                                valore della risorsa  */

                                InserisciXlRPosition (Figlio,Wid_riga,
                                        confinfo[j],NumRiga,TipoPagina);

                        break;
			case XlRFont:
				/* E' una risorsa relativa ad un font e
				quindi viene creata una riga composta da un
				pushButton, una label per segnalare le 
				modifiche o gli errori in inserimento e
				infine un textField per l'input diretto del
				font    */

				InserisciXlRFont (Figlio,Wid_riga,
					confinfo[j],NumRiga,TipoPagina);

			break;
			case XlRTipoVarPort:
				/* E' un nome di una variabile associata
   				   ad una porta nel caso di schemi di
				   regolazione   */
				InserisciXlRTipoVarReg (Figlio,Wid_riga,
                                        confinfo[j],NumRiga,TipoPagina);
			break;
			case XlRTipoVarReg:

				/* E' un nome di una variabile di animazione
				   per regolazione   */
				InserisciXlRTipoVarReg (Figlio,Wid_riga,
					confinfo[j],NumRiga,TipoPagina);

			break;
			case XlRText:
				/* E' una risorsa relativa ad un bitmap e
				quindi viene creata una riga composta da un
				pushButton, una label per segnalare le 
				modifiche o gli errori in inserimento e
				infine un textField per l'input diretto del
				caratteristiche del bitmap    */

				InserisciXlRText (Figlio,Wid_riga,
					confinfo[j],NumRiga,TipoPagina);

			break;
                    	case XlRFloat:
                                /* E' una risorsa relativa ad un 
				float e quindi viene 
				creata una riga composta da una label, una
				label per segnalare le modifiche o gli errori
				in inserimento e infine un textField per 
				l'input del valore della risorsa  */

				InserisciXlRFloat (Figlio,Wid_riga,
					confinfo[j],NumRiga,TipoPagina);

			break;
                    	case XlRInt:
                                /* E' una risorsa relativa ad un 
				int e quindi viene 
				creata una riga composta da una label, una
				label per segnalare le modifiche o gli errori
				in inserimento e infine un textField per 
				l'input del valore della risorsa  */

				InserisciXlRInt (Figlio,Wid_riga,
					confinfo[j],NumRiga,TipoPagina);

			break;
                    	default:
                                /* E' una risorsa generica e quindi viene 
				creata una riga composta da una label, una
				label per segnalare le modifiche o gli errori
				in inserimento e infine un textField per 
				l'input del valore della risorsa  */

				InserisciGenerica (Figlio,Wid_riga,
					confinfo[j],NumRiga,TipoPagina);

			break;
                        }

			/*   Inserisce una tag  non visibile per la
				memorizzazione dell'indice della confinfo
				che viene memorizzato come nome del
                                widget stesso  */
			sprintf (s1,"%d",j);
			narg = 0;
			Wid = XmCreateTextField (Wid_riga, s1, args, narg);

			if( (TipoRes == XlRColor) || (TipoRes == XlRAnimatedColor) )
				{
				XtSetArg (args[0], confinfo[j].resource_name,
								&Colore);
				XtGetValues (Figlio, args, 1);

				XmStringa = XmStringCreateSimple (" ");
				strcpy (s,"VisCol");
				narg = 0;
				Wid = XtVaCreateManagedWidget (s,
				xmLabelWidgetClass, Wid_riga,
				XmNlabelString, XmStringa,
				XmNbackground, Colore,
				XmNmarginHeight, 0,
				XmNmarginTop, 0,
				XmNmarginBottom, 0,
				XmNrecomputeSize, FALSE,
				XmNwidth, 15,
				NULL);
				XmStringFree (XmStringa);
				}

			/*  Incrementa il contatore delle righe da inserire */
			NumRiga ++;
			XtManageChild (Wid_riga);
		}
	}
}

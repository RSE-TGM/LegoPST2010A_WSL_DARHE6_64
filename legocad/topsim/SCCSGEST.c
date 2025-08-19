
/*******************************************************************************
	SCCSGEST.c
	(Generated from interface file SCCSGEST.i)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo SCCSGEST.i
   tipo 
   release 1.24
   data 8/29/95
   reserved @(#)SCCSGEST.i	1.24
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include "topsim.h"
#include "lg1_topsim.h"
#include "questionMsgDb.h"

/*******************************************************************************
	The definition of the context structure:
	If you create multiple instances of your interface, the context
	structure ensures that your callbacks use the variables for the
	correct instance.

	For each swidget in the interface, each argument to the Interface
	function, and each variable in the Instance Specific section of the
	Declarations Editor, there is an entry in the context structure.
	and a #define.  The #define makes the variable name refer to the
	corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	Widget	UxSCCSGEST;
	Widget	Uxform5;
	Widget	UxscrolledWindow5;
	Widget	UxListVersion;
	Widget	UxgetButton;
	Widget	UxeditButton;
	Widget	UxdeltaButton;
	Widget	UxcancelButton;
	Widget	Uxlabel4;
	Arg	Uxargs[5];
	Cardinal	Uxnargs;
	unsigned char	Uxversione[20];
	TIPO_OP	Uxtipop;
	unsigned char	*Uxsimpath;
} _UxCSCCSGEST;

#define SCCSGEST                UxSCCSGESTContext->UxSCCSGEST
#define form5                   UxSCCSGESTContext->Uxform5
#define scrolledWindow5         UxSCCSGESTContext->UxscrolledWindow5
#define ListVersion             UxSCCSGESTContext->UxListVersion
#define getButton               UxSCCSGESTContext->UxgetButton
#define editButton              UxSCCSGESTContext->UxeditButton
#define deltaButton             UxSCCSGESTContext->UxdeltaButton
#define cancelButton            UxSCCSGESTContext->UxcancelButton
#define label4                  UxSCCSGESTContext->Uxlabel4
#define args                    UxSCCSGESTContext->Uxargs
#define nargs                   UxSCCSGESTContext->Uxnargs
#define versione                UxSCCSGESTContext->Uxversione
#define tipop                   UxSCCSGESTContext->Uxtipop
#define simpath                 UxSCCSGESTContext->Uxsimpath

static _UxCSCCSGEST	*UxSCCSGESTContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_SCCSGEST();

/* Function declarations */
char *extract_string(XmString item);

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

int get_version_from_string(char *strin,char *strout)
{
  int i;
  char *ini=NULL,*fin=NULL;
  Boolean stop = False;

/*
   si suppone che la stringa di input abbia il formato
   "  5.4 data time user"
*/


  for(i=0;i<strlen(strin);i++)
     if( strin[i] == '*' )
        strin[i] = ' ';   

  for(i=0;i<strlen(strin);i++)
  {
     /* setto l'inizio dopo i blank iniziali */
     if( strin[i] != ' ' && !stop )
     {
        ini = &(strin[i]);
        printf("ini =%s\n",ini);
        stop = True;
     }
       
     /* setto la fine al primo blank successivo a inizio */  
     if( ini != NULL && strin[i] == ' ')
     {
        fin = &(strin[i]);
        *fin = 0;
        printf("fin =%s\n",fin);
        break;
     }
  }

/* copio i caratteri individuati */
  strncpy(strout,ini,(fin-ini)+1);

}

int exist_sccsdir(char *path)
{
   char sccsdir[100];

   strcpy(sccsdir,path);
   strcat(sccsdir,"/SCCS");
   if( chdir(sccsdir) != 0 ) /* la directory non e' accessibile */
      return(False);

   return(True);
}

void get_vers_selected()
{
}


void leggi_lS01(FILE *fp)
{
   char str[100],result[200],*appo;
   int n;
   XmString xstring;
   char vers[100];
   char comm[100];
   int reiniz;          /* =1 se riga vuota  =0 se c'e qualcosa*/
   int commento;        /* =0 riga di versione =1 riga di commento */  

/* leggo il file l.S01 generato con il comando sccs get -l S01 
   il quale e' strutturato cosi'
      riga della versione del file
      riga di commento (opzionale) questa riga puo' non esserci
      riga (possono essere anche di piu') con 1 solo char 
*/ 

   reiniz = 0;
   commento = 0;
   n=0;
   while( fgets(str,80,fp) != NULL)
   {
/* ho letto una riga con 1 solo char */
      if( strlen(str) == 1)
         reiniz = 1;
      else 
         reiniz = 0;

/* creo l'item */ 
      if( reiniz && commento)
      {
            appo = strchr(vers,'\n');
            if( appo )
               *appo = ' ';
            appo = strchr(vers,'\t');
            if( appo )
              *appo = ' ';
            appo = strchr(comm,'\n');
            if( appo )
               *appo = ' ';
            appo = strchr(comm,'\t');
            if( appo )
               *appo = ' ';

         sprintf(result,"%s  - %s",vers,comm);

         xstring = XmStringCreateSimple(result);
         XmListAddItem(ListVersion,xstring,1); 
         strcpy(result,"");

         commento = 0;

      }
       
/* se ho letto qualcosa */  
      if( !reiniz )
      {

/* ho un commento se ho gia' letto la versione */
         if( commento )
            strcpy(comm,str);


/* ho una versione o all'inizio della lettura del file o
   se ho gia' costruito l'item cioe' ho letto una riga vuota
   quindi la prossima riga sara' sicuramente una versione  
*/
         if( !commento ) 
         {  
            strcpy(vers,str);
            commento = 1;
         }

      }
      else
      {
         strcpy(vers,"");
         strcpy(comm,""); 
      }

    }      
}



void riempi_lista()
{
   FILE *fp;
  
   if( (fp = fopen("l.S01","r")) != NULL)
      leggi_lS01(fp);
  
   fclose(fp);
}

void abilita_getbutton()
{
   nargs=0;
   XtSetArg(args[nargs],XmNsensitive,True);nargs++;
   XtSetValues(getButton,args,nargs);   
   XtSetValues(editButton,args,nargs); 
}

void disabilita_getbutton()
{
   nargs=0;
   XtSetArg(args[nargs],XmNsensitive,False);nargs++;
   XtSetValues(getButton,args,nargs);   
   XtSetValues(editButton,args,nargs); 
}

void abilita_deltabutton()
{
   nargs=0;
   XtSetArg(args[nargs],XmNsensitive,False);nargs++;
   XtSetValues(deltaButton,args,nargs);   
}

void disabilita_deltabutton()
{
   nargs=0;
   XtSetArg(args[nargs],XmNsensitive,False);nargs++;
   XtSetValues(deltaButton,args,nargs);   
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	singleSelectionCB_ListVersion( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCSCCSGEST            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSCCSGESTContext;
	UxSCCSGESTContext = UxContext =
			(_UxCSCCSGEST *) UxGetContext( UxWidget );
	{
	char cstring[STRLONG];
	XmString item;
	
	
	/* recupero l'item selezionato tramite gli arg della callback */
	
	item = XmStringCopy( ((XmListCallbackStruct *)UxCallbackArg)->item );
	strcpy(cstring,extract_string(item));
	
	printf("Selezione =%s\n",cstring);
	
	/* recupero dalla stringa dell'item la versione */
	get_version_from_string(cstring,versione);
	
	printf("versione=%s\n",versione);
	
	
	}
	UxSCCSGESTContext = UxSaveCtx;
}

static void	activateCB_getButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCSCCSGEST            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSCCSGESTContext;
	UxSCCSGESTContext = UxContext =
			(_UxCSCCSGEST *) UxGetContext( UxWidget );
	{
	extern void set_working_directory();
	extern Boolean open_simulator();
	extern swidget SimSelection;
	extern Boolean get_sccsS01();
	
	/*
	   e' necessario adesso recuperare in  read only (get) la versione
	   che l'utente ha selezionato sulla lista
	*/
	
	set_working_directory(simpath);
	
	printf("\n\n Attenzione! in questa versione viene estratto in \n ReadOnly la  versione di S01 %s\n",versione);
	
	get_sccsS01(versione);
	
	/* open di un simulatore */
	if( open_simulator(simpath) == True)
	   printf("Open del simulatore andata a buon fine\n");
	else
	   printf("Open del simulatore NON andata a buon fine\n");
	
	UxDestroyInterface(SimSelection);
	UxDestroyInterface(XtParent(UxWidget));                         
	
	}
	UxSCCSGESTContext = UxSaveCtx;
}

static void	activateCB_editButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCSCCSGEST            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSCCSGESTContext;
	UxSCCSGESTContext = UxContext =
			(_UxCSCCSGEST *) UxGetContext( UxWidget );
	{
	extern void set_working_directory();
	extern Boolean open_simulator();
	extern swidget SimSelection;
	extern Boolean edit_sccsS01();
	
	
	set_working_directory(simpath);
	
	printf("\n\n Attenzione! in questa versione viene estratto in \n WriteMode la ultima versione di S01\n");
	
	edit_sccsS01(versione);
	
	/* open di un simulatore */
	if( open_simulator(simpath) == True)
	   printf("Open del simulatore andata a buon fine\n");
	else
	   printf("Open del simulatore NON andata a buon fine\n");
	
	UxDestroyInterface(SimSelection);
	UxDestroyInterface(XtParent(UxWidget));                         
	
	}
	UxSCCSGESTContext = UxSaveCtx;
}

static void	activateCB_deltaButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCSCCSGEST            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSCCSGESTContext;
	UxSCCSGESTContext = UxContext =
			(_UxCSCCSGEST *) UxGetContext( UxWidget );
	{
	extern swidget SimSelection;
	extern Boolean delta_sccsS01();
	
	delta_sccsS01();
	
	UxDestroyInterface(XtParent(UxWidget));                         
	
	}
	UxSCCSGESTContext = UxSaveCtx;
}

static void	activateCB_cancelButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCSCCSGEST            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSCCSGESTContext;
	UxSCCSGESTContext = UxContext =
			(_UxCSCCSGEST *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(XtParent(UxWidget));
	}
	UxSCCSGESTContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_SCCSGEST()
{

	SCCSGEST = XtVaCreatePopupShell( "SCCSGEST",
			topLevelShellWidgetClass, UxTopLevel,
			XmNheight, 400,
			XmNwidth, 360,
			XmNy, 350,
			XmNx, 410,
			NULL );

	UxPutContext( SCCSGEST, (char *) UxSCCSGESTContext );

	form5 = XtVaCreateManagedWidget( "form5",
			xmFormWidgetClass, SCCSGEST,
			XmNheight, 190,
			XmNwidth, 160,
			XmNy, 70,
			XmNx, 100,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form5, (char *) UxSCCSGESTContext );

	scrolledWindow5 = XtVaCreateManagedWidget( "scrolledWindow5",
			xmScrolledWindowWidgetClass, form5,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopOffset, 40,
			XmNtopAttachment, XmATTACH_FORM,
			XmNbottomOffset, 60,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 50,
			XmNx, 20,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( scrolledWindow5, (char *) UxSCCSGESTContext );

	ListVersion = XtVaCreateManagedWidget( "ListVersion",
			xmListWidgetClass, scrolledWindow5,
			XmNselectionPolicy, XmSINGLE_SELECT,
			XmNheight, 260,
			XmNwidth, 320,
			NULL );

	UxPutContext( ListVersion, (char *) UxSCCSGESTContext );

	getButton = XtVaCreateManagedWidget( "getButton",
			xmPushButtonWidgetClass, form5,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNtopWidget, scrolledWindow5,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Get" ),
			XmNheight, 30,
			XmNwidth, 50,
			XmNy, 340,
			XmNx, 20,
			NULL );

	UxPutContext( getButton, (char *) UxSCCSGESTContext );

	editButton = XtVaCreateManagedWidget( "editButton",
			xmPushButtonWidgetClass, form5,
			XmNleftOffset, 80,
			XmNleftAttachment, XmATTACH_FORM,
			XmNtopWidget, scrolledWindow5,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Edit" ),
			XmNheight, 30,
			XmNwidth, 50,
			XmNy, 340,
			XmNx, 90,
			NULL );

	UxPutContext( editButton, (char *) UxSCCSGESTContext );

	deltaButton = XtVaCreateManagedWidget( "deltaButton",
			xmPushButtonWidgetClass, form5,
			XmNleftOffset, 150,
			XmNleftAttachment, XmATTACH_FORM,
			XmNtopWidget, scrolledWindow5,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Delta" ),
			XmNheight, 30,
			XmNwidth, 50,
			XmNy, 340,
			XmNx, 170,
			NULL );

	UxPutContext( deltaButton, (char *) UxSCCSGESTContext );

	cancelButton = XtVaCreateManagedWidget( "cancelButton",
			xmPushButtonWidgetClass, form5,
			XmNleftAttachment, XmATTACH_SELF,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopWidget, scrolledWindow5,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Cancel" ),
			XmNheight, 30,
			XmNwidth, 80,
			XmNy, 340,
			XmNx, 290,
			NULL );

	UxPutContext( cancelButton, (char *) UxSCCSGESTContext );

	label4 = XtVaCreateManagedWidget( "label4",
			xmLabelWidgetClass, form5,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNtopOffset, 5,
			XmNtopAttachment, XmATTACH_FORM,
			XmNbottomWidget, scrolledWindow5,
			XmNbottomOffset, 5,
			XmNbottomAttachment, XmATTACH_WIDGET,
			RES_CONVERT( XmNlabelString, "SCCS Version of Sim1" ),
			XmNheight, 30,
			XmNwidth, 320,
			XmNy, 10,
			XmNx, 20,
			NULL );

	UxPutContext( label4, (char *) UxSCCSGESTContext );

	XtAddCallback( SCCSGEST, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxSCCSGESTContext );

	XtAddCallback( ListVersion, XmNsingleSelectionCallback,
			singleSelectionCB_ListVersion,
			(XtPointer) UxSCCSGESTContext );

	XtAddCallback( getButton, XmNactivateCallback,
			activateCB_getButton,
			(XtPointer) UxSCCSGESTContext );

	XtAddCallback( editButton, XmNactivateCallback,
			activateCB_editButton,
			(XtPointer) UxSCCSGESTContext );

	XtAddCallback( deltaButton, XmNactivateCallback,
			activateCB_deltaButton,
			(XtPointer) UxSCCSGESTContext );

	XtAddCallback( cancelButton, XmNactivateCallback,
			activateCB_cancelButton,
			(XtPointer) UxSCCSGESTContext );



	return ( SCCSGEST );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_SCCSGEST( _Uxtipop, _Uxsimpath )
	TIPO_OP	_Uxtipop;
	unsigned char	*_Uxsimpath;
{
	Widget                  rtrn;
	_UxCSCCSGEST            *UxContext;

	UxSCCSGESTContext = UxContext =
		(_UxCSCCSGEST *) XtMalloc( sizeof(_UxCSCCSGEST) );

	tipop = _Uxtipop;
	simpath = _Uxsimpath;
	{
		extern SIMULATORE *alloca_simulatore();
		extern SIMULATORE *simulatore; 
		
		extern void set_working_directory();
		extern Boolean get_working_directory();
		char wdir[100];
		
		
		printf("simpath = [%s]\n",simpath);
		
		set_working_directory(simpath);
		
		
		if( get_working_directory(wdir) == FALSE)
		   return(NULL);
		
		printf("wdir = [%s]\n",wdir);
		
		
		printf("set dir %s\nactual directory for Simulator %s\n",simpath,wdir);
		
		 
		/* ricavo il file l.S01 che contiene 
		   la storia delle revisioni del file S01 */
		
		system("sccs get -l S01");
		rtrn = _Uxbuild_SCCSGEST();

		if( tipop == SAVESIM )
		{
		  disabilita_getbutton();
		  riempi_lista();
		}
		else if( tipop == OPENSIM )
		{
		  disabilita_deltabutton();
		  riempi_lista();
		}
		
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_SCCSGEST( _Uxtipop, _Uxsimpath )
	TIPO_OP	_Uxtipop;
	unsigned char	*_Uxsimpath;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_SCCSGEST( _Uxtipop, _Uxsimpath );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/


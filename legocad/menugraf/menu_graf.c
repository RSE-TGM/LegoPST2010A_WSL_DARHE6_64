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
#ifndef DESIGN_TIME
/*
   modulo menu_graf.c
   tipo 
   release 1.3
   data 3/28/95
   reserved @(#)menu_graf.c	1.3
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)menu_graf.c	1.3\t3/28/95";
/*
        Fine sezione per SCCS
*/
#endif

/*-----------------------------------------------------------
 * This is the project main program file for Xt generated 
 * code. You may add application dependent source code 
 * at the appropriate places. 
 * 			     
 * Do not modify the statements preceded by the dollar
 * sign ($), these statements will be replaced with
 * the appropriate source code when the main program is  
 * generated.  
 *
 * $Date: 92/04/23 14:57:13 $  		$Revision: 1.11.37.1.45.1 $ 
 *-----------------------------------------------------------*/ 

#ifdef XOPEN_CATALOG
#include <locale.h>
#endif


#include <stdio.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <Xm/Xm.h>
#include <Xm/CutPaste.h>

/*---------------------------------------------------- 
 * UxXt.h needs to be included only when compiling a 
 * stand-alone application. 
 *---------------------------------------------------*/
#ifndef DESIGN_TIME
#include "UxXt.h"
#endif /* DESIGN_TIME */

XtAppContext	UxAppContext;
Widget		UxTopLevel;
Display		*UxDisplay;
int		UxScreen;

/*----------------------------------------------
 * Insert application global declarations here
 *---------------------------------------------*/

/*	Oggetti relativi alle interfacce  */
extern swidget create_Edit_Time_Win(),Edit_Time_Win;
extern swidget create_Resampling(),Resampling;
extern swidget create_Sampling(),Sampling;
extern swidget create_Message(),Message;
extern swidget create_Description(),Description;
extern swidget create_Menu_graf_exit(),Menu_graf_exit;

extern swidget Edt_start_time;
extern swidget Edt_stop_time;
extern swidget Titolo_edit;
extern swidget path_name;
extern swidget start_time;
extern swidget stop_time;
extern swidget num_var;
extern swidget PasteItem_V;
extern swidget Push_Deselect;

char Path_appo[101];
float delta_nuovo,delta_vecchio,New_delta;
float old_campione,new_iniziale,new_finale;
int numero_temp,non_f22,Find_sel,numero_campioni,campioni,Scelta;
int New_Sampl,Modifica,Salvato,nome_valido,pid;

char *elenco_filetmp;
FILE *fpELENCO;

main(argc,argv)
	int 	argc;
	char 	*argv[];
{
	/*-----------------------------------------------------------
	 * Declarations.
         * The default identifier - mainIface will only be declared 
	 * if the interface function is global and of type swidget.
	 * To change the identifier to a different name, modify the
	 * string mainIface in the file "xtmain.dat". If "mainIface"
         * is declared, it will be used below where the return value
	 * of  PJ_INTERFACE_FUNCTION_CALL will be assigned to it.
         *----------------------------------------------------------*/ 

  	Widget mainIface;

	/*---------------------------------
	 * Interface function declaration
	 *--------------------------------*/	

 	Widget  create_Menu_graf();

	

	 unsigned long lun;
	 int status;

	/*---------------------
	 * Initialize program
	 *--------------------*/

#ifdef XOPEN_CATALOG
	setlocale(LC_ALL, "");
#endif

  	UxTopLevel = XtAppInitialize(&UxAppContext, "menugraf",
				     NULL, 0, &argc, argv, NULL, NULL, 0);

	UxDisplay = XtDisplay(UxTopLevel);
	UxScreen = XDefaultScreen(UxDisplay);

	/* We set the geometry of UxTopLevel so that dialogShells
	   that are parented on it will get centered on the screen
	   (if defaultPosition is true). */

	XtVaSetValues(UxTopLevel,
			XtNx, 0,
			XtNy, 0,
			XtNwidth, DisplayWidth(UxDisplay, UxScreen),
			XtNheight, DisplayHeight(UxDisplay, UxScreen),
			NULL);

	/*-------------------------------------------------------
	 * Insert initialization code for your application here 
	 *------------------------------------------------------*/

	/*******************************************************
		Creazione di tutte le interfacce
	 *******************************************************/
	 Message 	   = create_Message();
	 Edit_Time_Win 	   = create_Edit_Time_Win();
	 Menu_graf_exit    = create_Menu_graf_exit();
	 Sampling 	   = create_Sampling();
	 Resampling 	   = create_Resampling();
	 Description 	   = create_Description();
	/********************************************************
		Inizializzazione delle variabili di uso comune
	 ********************************************************/
	 Find_sel 	= 0;
	 numero_temp 	= 1;
	 Modifica 	= 0;
	 Salvato 	= 1;
	 nome_valido 	= 0;
       
         elenco_filetmp = tmpnam(NULL);

         if( (fpELENCO = fopen(elenco_filetmp,"w")) ==  NULL)
         {
             printf("Cannot open temporary file, EXIT\n");
             exit(0);
         }


	/*----------------------------------------------------------------
	 * Create and popup the first window of the interface.  The 	 
	 * return value can be used in the popdown or destroy functions.
         * The Widget return value of  PJ_INTERFACE_FUNCTION_CALL will 
         * be assigned to "mainIface" from  PJ_INTERFACE_RETVAL_TYPE. 
	 *---------------------------------------------------------------*/

	mainIface = create_Menu_graf();

	UxPopupInterface(mainIface, no_grab);

	/*-----------------------
	 * Enter the event loop 
	 *----------------------*/
	 
  	XtAppMainLoop (UxAppContext);
}

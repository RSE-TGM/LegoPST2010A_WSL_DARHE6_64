
/*******************************************************************************
	editShell1.c
	(Generated from interface file editShell1.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/Label.h>
#include <Xm/TextF.h>
#include <Xm/Form.h>
#include <Xm/DialogS.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo editShell1.i
   tipo 
   release 2.6
   data 3/20/95
   reserved @(#)editShell1.i	2.6
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <Xm/MwmUtil.h>
#include <Xm/Text.h>
#ifndef FILTRI_H
#include "filtri.h"
#endif


extern void delete_all_items();
extern void add_items_list();

extern char filedf[];                 /* filename file di editing */
extern FILE *fpedf;                   /* file di edting */
extern FILTRI *filtri[];              /* vettore filtri */
extern short num_filtri;              /* numero di filtri definiti */

extern swidget scrolledList1;
extern swidget scrolledList2;

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
	Widget	Uxform2;
	Widget	UxtextField2;
	Widget	Uxlabel1;
	Widget	Uxlabel2;
	Widget	UxpushButton1;
	Widget	UxpushButton2;
	Widget	UxtextField3;
	Widget	UxtextField4;
	Widget	UxtextField5;
	Widget	UxtextField6;
	Widget	UxtextField7;
	Widget	UxtextField8;
	Widget	UxtextField9;
	Widget	UxtextField10;
	Widget	UxtextField11;
	Widget	Uxlabel3;
	Widget	Uxlabel4;
	Widget	Uxlabel5;
	Widget	Uxlabel6;
	Widget	Uxlabel7;
	Widget	Uxlabel8;
	Widget	Uxlabel9;
	Widget	Uxlabel10;
	Widget	Uxlabel11;
	Widget	Uxlabel12;
	int	Uxapro;
} _UxCeditShell1;

#define form2                   UxEditShell1Context->Uxform2
#define textField2              UxEditShell1Context->UxtextField2
#define label1                  UxEditShell1Context->Uxlabel1
#define label2                  UxEditShell1Context->Uxlabel2
#define pushButton1             UxEditShell1Context->UxpushButton1
#define pushButton2             UxEditShell1Context->UxpushButton2
#define textField3              UxEditShell1Context->UxtextField3
#define textField4              UxEditShell1Context->UxtextField4
#define textField5              UxEditShell1Context->UxtextField5
#define textField6              UxEditShell1Context->UxtextField6
#define textField7              UxEditShell1Context->UxtextField7
#define textField8              UxEditShell1Context->UxtextField8
#define textField9              UxEditShell1Context->UxtextField9
#define textField10             UxEditShell1Context->UxtextField10
#define textField11             UxEditShell1Context->UxtextField11
#define label3                  UxEditShell1Context->Uxlabel3
#define label4                  UxEditShell1Context->Uxlabel4
#define label5                  UxEditShell1Context->Uxlabel5
#define label6                  UxEditShell1Context->Uxlabel6
#define label7                  UxEditShell1Context->Uxlabel7
#define label8                  UxEditShell1Context->Uxlabel8
#define label9                  UxEditShell1Context->Uxlabel9
#define label10                 UxEditShell1Context->Uxlabel10
#define label11                 UxEditShell1Context->Uxlabel11
#define label12                 UxEditShell1Context->Uxlabel12
#define apro                    UxEditShell1Context->Uxapro

static _UxCeditShell1	*UxEditShell1Context;

Widget	editShell1;
Widget	textField1;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_editShell1();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/*===================================================================
|
|  clear_field:  ripulisce la finestra di input dati
|
====================================================================*/

int clear_field()
{
   char appo[MAXCHNAME+1];

   strcpy(appo,"");
   UxPutText(textField1,appo);
   UxPutText(textField2,appo);
   UxPutText(textField3,appo);
   UxPutText(textField4,appo);
   UxPutText(textField5,appo); 
   UxPutText(textField6,appo);
   UxPutText(textField7,appo); 
   UxPutText(textField8,appo);
   UxPutText(textField9,appo);
   UxPutText(textField10,appo);
   UxPutText(textField11,appo);

}

/*===============================================================
|
|   aggiorna_edit_shell: visualizza nella shell i dati di un filtro
|
|===============================================================*/

int aggiorna_edit_shell(FILTRI *filtro)
{
   printf("\naggiorna edti shell con filtro ->%s\n",filtro->nome_filtro);

   clear_field();
   UxPutText(textField1,filtro->nome_filtro);
   UxPutText(textField2,filtro->var[0]);
   UxPutText(textField3,filtro->var[1]);
   UxPutText(textField4,filtro->var[2]);
   UxPutText(textField5,filtro->var[3]);
   UxPutText(textField6,filtro->var[4]);
   UxPutText(textField7,filtro->var[5]);
   UxPutText(textField8,filtro->var[6]);
   UxPutText(textField9,filtro->var[7]);
   UxPutText(textField10,filtro->var[8]);
   UxPutText(textField11,filtro->var[9]);
}

/*===============================================================
|
|   aggiorna_filtro: modifica i dati di un filtro
|
|===============================================================*/

int aggiorna_filtro(FILTRI *filtro)
{
   char appo[100];
   int i;

 
   printf("\naggiorna filtro %s \n",filtro->nome_filtro);
   strcpy(appo,UxGetText(textField1));
   if(strlen(appo))
   {
      strcpy(filtro->nome_filtro,appo);
      filtro->num_var=0;
    
      strcpy(appo,UxGetText(textField2));
      if(strlen(appo))
      {
         strcpy(filtro->var[0],appo);
         filtro->num_var++;         
      
         strcpy(appo,UxGetText(textField3));
         if(strlen(appo))
         { 
            strcpy(filtro->var[1],appo);
            filtro->num_var++;         
      
            strcpy(appo,UxGetText(textField4));
            if(strlen(appo))
            {      
               strcpy(filtro->var[2],appo);
               filtro->num_var++;         
      
               strcpy(appo,UxGetText(textField5));
               if(strlen(appo))
               {
                  strcpy(filtro->var[3],appo);
                  filtro->num_var++;         
         
                  strcpy(appo,UxGetText(textField6));
                  if(strlen(appo))
                  {
                     strcpy(filtro->var[4],appo);
                     filtro->num_var++;         
      
                     strcpy(appo,UxGetText(textField7));
                     if(strlen(appo))
                     {
                        strcpy(filtro->var[5],appo);
                        filtro->num_var++;         
      
                        strcpy(appo,UxGetText(textField8));
                        if(strlen(appo))
                        {
                           strcpy(filtro->var[6],appo);
                           filtro->num_var++;         

                           strcpy(appo,UxGetText(textField9));
                           if(strlen(appo))
                           {
                              strcpy(filtro->var[7],appo);
                              filtro->num_var++;         
      

                              strcpy(appo,UxGetText(textField10));
                              if(strlen(appo))
                              {
                                 strcpy(filtro->var[8],appo);
                                 filtro->num_var++;         
      

                                 strcpy(appo,UxGetText(textField11));
                                 if(strlen(appo))
                                 {
                                    strcpy(filtro->var[9],appo);
                                    filtro->num_var++;         
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }

      printf("ho %d filtri\n",filtro->num_var);
   }

   delete_all_items(scrolledList1);
   delete_all_items(scrolledList2);
   refresh_lista_nomi();
}

/*===============================================================
|
|   aggiungi_filtri: inserisce un nuovo  filtro nella tabella dei filtri
|
|===============================================================*/

int aggiungi_filtro()
{

   char appo[100];
   char *nomi[MAXFILTRI];
   short i;
   extern FILTRI *filtro_init();

   printf("\naggiungi  filtro \n");

   
   filtri[num_filtri] = filtro_init();
   num_filtri++;
   aggiorna_filtro(filtri[num_filtri - 1]);


   printf("\naggiungi  filtro \n");
   printf("\n          filtro n.1  %s\n",filtri[num_filtri - 1]->var[0]);
   printf("\n          filtro n.2  %s\n",filtri[num_filtri - 1]->var[1]);
   printf("\n          filtro n.3  %s\n",filtri[num_filtri - 1]->var[2]);
   printf("\n          filtro n.4  %s\n",filtri[num_filtri - 1]->var[3]);
   printf("\n          filtro n.5  %s\n",filtri[num_filtri - 1]->var[4]);
   printf("\n          filtro n.6  %s\n",filtri[num_filtri - 1]->var[5]);
   printf("\n          filtro n.7  %s\n",filtri[num_filtri - 1]->var[6]);
   printf("\n          filtro n.8  %s\n",filtri[num_filtri - 1]->var[7]);
   printf("\n          filtro n.9  %s\n",filtri[num_filtri - 1]->var[8]);
   printf("\n          filtro n.10 %s\n",filtri[num_filtri - 1]->var[9]);

   for(i=0;i<num_filtri;i++)
   {
      nomi[i] = (char *)(malloc(sizeof(char) * MAXCHNAME));
      strcpy(nomi[i],filtri[i]->nome_filtro);
   }

   delete_all_items(scrolledList1);
   delete_all_items(scrolledList2);
   add_items_list(scrolledList1,nomi,num_filtri);

   
   for(i=0;i<num_filtri;i++)
      free(nomi[i]);

   clear_field();

}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_pushButton1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCeditShell1          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxEditShell1Context;
	UxEditShell1Context = UxContext =
			(_UxCeditShell1 *) UxGetContext( UxWidget );
	{
	extern int operaz;
	extern short num_filtro_selez;
	
	switch(operaz)
	{
	   case NEW_FILTRO:
	     printf("\nswitch entry NEW_FILTRO\n");
	     aggiungi_filtro();
	   break;
	   case OPEN_FILTRO:
	     printf("\nswitch entry OPEN_FILTRO\n");
	     aggiorna_filtro(filtri[num_filtro_selez]);
	   break;
	}
	
	
	}
	UxEditShell1Context = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_editShell1()
{

	editShell1 = XtVaCreatePopupShell( "editShell1",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNallowShellResize, TRUE,
			XmNheight, 410,
			XmNwidth, 360,
			XmNy, 266,
			XmNx, 454,
			NULL );

	UxPutContext( editShell1, (char *) UxEditShell1Context );

	form2 = XtVaCreateWidget( "form2",
			xmFormWidgetClass, editShell1,
			XmNtraversalOn, TRUE,
			XmNdialogStyle, XmDIALOG_PRIMARY_APPLICATION_MODAL,
			RES_CONVERT( XmNdialogTitle, "Filter Edit" ),
			XmNheight, 410,
			XmNwidth, 360,
			XmNy, 10,
			XmNx, 0,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form2, (char *) UxEditShell1Context );

	textField1 = XtVaCreateManagedWidget( "textField1",
			xmTextFieldWidgetClass, form2,
			XmNmaxLength, 10,
			XmNheight, 40,
			XmNwidth, 140,
			XmNy, 60,
			XmNx, 130,
			NULL );

	UxPutContext( textField1, (char *) UxEditShell1Context );

	textField2 = XtVaCreateManagedWidget( "textField2",
			xmTextFieldWidgetClass, form2,
			XmNmaxLength, 4,
			XmNcolumns, 4,
			XmNheight, 40,
			XmNwidth, 70,
			XmNy, 150,
			XmNx, 80,
			NULL );

	UxPutContext( textField2, (char *) UxEditShell1Context );

	label1 = XtVaCreateManagedWidget( "label1",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "Filter Name" ),
			XmNheight, 20,
			XmNwidth, 110,
			XmNy, 70,
			XmNx, 20,
			NULL );

	UxPutContext( label1, (char *) UxEditShell1Context );

	label2 = XtVaCreateManagedWidget( "label2",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "Filter" ),
			XmNheight, 20,
			XmNwidth, 140,
			XmNy, 120,
			XmNx, 110,
			NULL );

	UxPutContext( label2, (char *) UxEditShell1Context );

	pushButton1 = XtVaCreateManagedWidget( "pushButton1",
			xmPushButtonWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "Ok" ),
			XmNheight, 30,
			XmNwidth, 70,
			XmNy, 370,
			XmNx, 30,
			NULL );

	UxPutContext( pushButton1, (char *) UxEditShell1Context );

	pushButton2 = XtVaCreateManagedWidget( "pushButton2",
			xmPushButtonWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "Cancel" ),
			XmNheight, 30,
			XmNwidth, 80,
			XmNy, 370,
			XmNx, 110,
			NULL );

	UxPutContext( pushButton2, (char *) UxEditShell1Context );

	textField3 = XtVaCreateManagedWidget( "textField3",
			xmTextFieldWidgetClass, form2,
			XmNmaxLength, 4,
			XmNcolumns, 4,
			XmNheight, 40,
			XmNwidth, 70,
			XmNy, 150,
			XmNx, 250,
			NULL );

	UxPutContext( textField3, (char *) UxEditShell1Context );

	textField4 = XtVaCreateManagedWidget( "textField4",
			xmTextFieldWidgetClass, form2,
			XmNmaxLength, 4,
			XmNcolumns, 4,
			XmNheight, 40,
			XmNwidth, 70,
			XmNy, 190,
			XmNx, 80,
			NULL );

	UxPutContext( textField4, (char *) UxEditShell1Context );

	textField5 = XtVaCreateManagedWidget( "textField5",
			xmTextFieldWidgetClass, form2,
			XmNmaxLength, 4,
			XmNcolumns, 4,
			XmNheight, 40,
			XmNwidth, 70,
			XmNy, 190,
			XmNx, 250,
			NULL );

	UxPutContext( textField5, (char *) UxEditShell1Context );

	textField6 = XtVaCreateManagedWidget( "textField6",
			xmTextFieldWidgetClass, form2,
			XmNmaxLength, 4,
			XmNcolumns, 5,
			XmNheight, 40,
			XmNwidth, 70,
			XmNy, 230,
			XmNx, 80,
			NULL );

	UxPutContext( textField6, (char *) UxEditShell1Context );

	textField7 = XtVaCreateManagedWidget( "textField7",
			xmTextFieldWidgetClass, form2,
			XmNmaxLength, 4,
			XmNheight, 40,
			XmNwidth, 70,
			XmNy, 230,
			XmNx, 250,
			NULL );

	UxPutContext( textField7, (char *) UxEditShell1Context );

	textField8 = XtVaCreateManagedWidget( "textField8",
			xmTextFieldWidgetClass, form2,
			XmNmaxLength, 4,
			XmNheight, 40,
			XmNwidth, 70,
			XmNy, 270,
			XmNx, 80,
			NULL );

	UxPutContext( textField8, (char *) UxEditShell1Context );

	textField9 = XtVaCreateManagedWidget( "textField9",
			xmTextFieldWidgetClass, form2,
			XmNmaxLength, 4,
			XmNheight, 40,
			XmNwidth, 70,
			XmNy, 270,
			XmNx, 250,
			NULL );

	UxPutContext( textField9, (char *) UxEditShell1Context );

	textField10 = XtVaCreateManagedWidget( "textField10",
			xmTextFieldWidgetClass, form2,
			XmNmaxLength, 4,
			XmNheight, 40,
			XmNwidth, 70,
			XmNy, 310,
			XmNx, 80,
			NULL );

	UxPutContext( textField10, (char *) UxEditShell1Context );

	textField11 = XtVaCreateManagedWidget( "textField11",
			xmTextFieldWidgetClass, form2,
			XmNmaxLength, 4,
			XmNheight, 40,
			XmNwidth, 70,
			XmNy, 310,
			XmNx, 250,
			NULL );

	UxPutContext( textField11, (char *) UxEditShell1Context );

	label3 = XtVaCreateManagedWidget( "label3",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "n.1" ),
			XmNheight, 20,
			XmNwidth, 50,
			XmNy, 160,
			XmNx, 20,
			NULL );

	UxPutContext( label3, (char *) UxEditShell1Context );

	label4 = XtVaCreateManagedWidget( "label4",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "n.6" ),
			XmNheight, 20,
			XmNwidth, 50,
			XmNy, 240,
			XmNx, 190,
			NULL );

	UxPutContext( label4, (char *) UxEditShell1Context );

	label5 = XtVaCreateManagedWidget( "label5",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "n.10" ),
			XmNheight, 20,
			XmNwidth, 50,
			XmNy, 320,
			XmNx, 190,
			NULL );

	UxPutContext( label5, (char *) UxEditShell1Context );

	label6 = XtVaCreateManagedWidget( "label6",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "n.5" ),
			XmNheight, 20,
			XmNwidth, 50,
			XmNy, 240,
			XmNx, 20,
			NULL );

	UxPutContext( label6, (char *) UxEditShell1Context );

	label7 = XtVaCreateManagedWidget( "label7",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "n.7" ),
			XmNheight, 20,
			XmNwidth, 50,
			XmNy, 280,
			XmNx, 20,
			NULL );

	UxPutContext( label7, (char *) UxEditShell1Context );

	label8 = XtVaCreateManagedWidget( "label8",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "n.9" ),
			XmNheight, 20,
			XmNwidth, 50,
			XmNy, 320,
			XmNx, 20,
			NULL );

	UxPutContext( label8, (char *) UxEditShell1Context );

	label9 = XtVaCreateManagedWidget( "label9",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "n.3" ),
			XmNheight, 20,
			XmNwidth, 50,
			XmNy, 200,
			XmNx, 20,
			NULL );

	UxPutContext( label9, (char *) UxEditShell1Context );

	label10 = XtVaCreateManagedWidget( "label10",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "n.2" ),
			XmNheight, 20,
			XmNwidth, 50,
			XmNy, 160,
			XmNx, 190,
			NULL );

	UxPutContext( label10, (char *) UxEditShell1Context );

	label11 = XtVaCreateManagedWidget( "label11",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "n.4" ),
			XmNheight, 20,
			XmNwidth, 50,
			XmNy, 200,
			XmNx, 190,
			NULL );

	UxPutContext( label11, (char *) UxEditShell1Context );

	label12 = XtVaCreateManagedWidget( "label12",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "n.8" ),
			XmNheight, 20,
			XmNwidth, 50,
			XmNy, 280,
			XmNx, 190,
			NULL );

	UxPutContext( label12, (char *) UxEditShell1Context );

	XtAddCallback( editShell1, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxEditShell1Context );

	XtVaSetValues(editShell1,
			XmNmwmFunctions, MWM_FUNC_MOVE | MWM_FUNC_CLOSE,
			XmNmwmDecorations, MWM_DECOR_BORDER | MWM_DECOR_TITLE | MWM_DECOR_MENU,
			NULL );

	XtAddCallback( pushButton1, XmNactivateCallback,
			activateCB_pushButton1,
			(XtPointer) UxEditShell1Context );



	return ( editShell1 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_editShell1()
{
	Widget                  rtrn;
	_UxCeditShell1          *UxContext;

	UxEditShell1Context = UxContext =
		(_UxCeditShell1 *) XtMalloc( sizeof(_UxCeditShell1) );

	rtrn = _Uxbuild_editShell1();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_editShell1()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_editShell1();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/


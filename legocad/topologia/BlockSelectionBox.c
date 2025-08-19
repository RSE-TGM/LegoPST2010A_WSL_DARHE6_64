
/*******************************************************************************
	BlockSelectionBox.c
	(Generated from interface file BlockSelectionBox.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/TextF.h>
#include <Xm/LabelG.h>
#include <Xm/RowColumn.h>
#include <Xm/SelectioB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME

/*
   modulo BlockSelectionBox.i
   tipo 
   release 2.24
   data 3/30/95
   reserved @(#)BlockSelectionBox.i	2.24
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#endif

#include "errore.h"
#include "lg1.h"
#include <stdlib.h>
#include <ctype.h>

extern ERR_LEVEL err_level;
extern int num_modulo;
extern void add_block();

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
	Widget	UxBlockSelectionBox;
	Widget	UxBlockName1;
	Widget	UxlabelBlockName1;
	Widget	UxtextBlockName1;
	Widget	UxlabelBlockDescr1;
	Widget	UxtextBlockDescr;
} _UxCBlockSelectionBox;

#define BlockSelectionBox       UxBlockSelectionBoxContext->UxBlockSelectionBox
#define BlockName1              UxBlockSelectionBoxContext->UxBlockName1
#define labelBlockName1         UxBlockSelectionBoxContext->UxlabelBlockName1
#define textBlockName1          UxBlockSelectionBoxContext->UxtextBlockName1
#define labelBlockDescr1        UxBlockSelectionBoxContext->UxlabelBlockDescr1
#define textBlockDescr          UxBlockSelectionBoxContext->UxtextBlockDescr

static _UxCBlockSelectionBox	*UxBlockSelectionBoxContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_BlockSelectionBox();
void errore(const char*, ...);
int do_dialogo(void);

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/*
    block_selection_setitem: definisce gli item selezionabili
*/
   

int block_selection_setitem(int tipo_mod)
{
   extern MODULO moduli[];
   MODULO *lista_mod = moduli;        /*per ingannare l'interprete UIMX */
   Arg       arg[2];
   XmString *modu;
   int i,trovati;
  
   int nitem;   
   char riga[100];


   printf("tipo lista selezionata = %d\n",tipo_mod);

   if(tipo_mod == REGOLAZIONE)
   {
      UxPutListLabelString(BlockSelectionBox,"Regulation Block List");     
      XmTextFieldSetEditable(textBlockName1,False);
      XmTextFieldSetEditable(textBlockDescr,False);
/*
      UxPutEditable(textBlockName1,False);
      UxPutEditable(textBlockDescr,False);
*/
   } 
   else if(tipo_mod == PROCESSO)
   {
      UxPutListLabelString(BlockSelectionBox,"Module List");
      XmTextFieldSetEditable(textBlockName1,True);
      XmTextFieldSetEditable(textBlockDescr,True);
/*
      UxPutEditable(UxGetWidget(textBlockName1),True);
      UxPutEditable(UxGetWidget(textBlockDescr),True);
*/
   }


   nitem = num_tot_moduli;

   if ( nitem )
   {
     modu=(XmString *)malloc(nitem * sizeof(XmString));
     printf("alloco sufficiente memoria\n");


     trovati = 0;
     for(i=0;i<nitem;i++)
     {
       if(lista_mod[i].tipo == tipo_mod)
       {

          strcpy(riga,lista_mod[i].sigla);
          strcat(riga,"  ");
          strcat(riga,lista_mod[i].descr);
riga[strlen(riga) - 1]= '\0';
          modu[trovati]=XmStringCreateSimple(riga);
          trovati++;
       }
     }
          
   printf("moduli trovati %d\n",trovati);

   }

   if(trovati)
   {   
      XtSetArg(arg[0], XmNlistItems, modu);
      XtSetArg(arg[1], XmNlistItemCount, trovati);
      XtSetValues(UxGetWidget(BlockSelectionBox), arg, 2);

      printf("i have set %d argument values \n",trovati);

      for(i=0;i<trovati;i++)
        XmStringFree(modu[i]);

   }
   else
   {
     XtSetArg(arg[0], XmNlistItems, NULL);
     XtSetArg(arg[1], XmNlistItemCount, 0);
     XtSetValues(UxGetWidget(BlockSelectionBox), arg, 2);
   }

   printf("end subroutine block_selection_setitem\n");
}



int block_selection_activate(int tipo)
{
   
   extern swidget   lg1MainWindow;

   printf("call list for tipo = %d\n",tipo);
    
   block_selection_setitem(tipo);
   UxPopupInterface(BlockSelectionBox, no_grab);
   
   UxPutText(textBlockName1,"");
   UxPutText(textBlockDescr,"");
   UxPutTextString(BlockSelectionBox,"");   
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	applyCB_BlockSelectionBox( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCBlockSelectionBox   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxBlockSelectionBoxContext;
	UxBlockSelectionBoxContext = UxContext =
			(_UxCBlockSelectionBox *) UxGetContext( UxWidget );
	{
	extern int num_tot_moduli;
	extern char blockname[],blockdescr[],modulename[];
	extern int changes_in_F01;
	
	char *module_selected,verifica[9];
	int i,j,nitem;
	MODULO *mod = moduli;     /* serve a ingannare uimx */
	BLOCCO *bloc = blocchi;
	
	
	
	nitem = num_tot_moduli;
	
	strcpy(blockname,UxGetText(textBlockName1));
	strcpy(blockdescr,UxGetText(textBlockDescr));
	
	for(j=0;j< ( strlen(blockname) ) ;j++)
	{
	   blockname[j] = toupper(blockname[j]);
	}
	UxPutText(textBlockName1,blockname);
	
	module_selected = UxGetTextString(UxWidget);
	
	if(!(*module_selected))
	{
	   err_level = ERROR;
	   errore("No Module Selected");
	   UxPopdownInterface(UxWidget);
	   return;
	}
	
	for(j=0;j< 4  ;j++)
	{
	   module_selected[j] = toupper(module_selected[j]);
	}
	module_selected[4]=0;
	strcpy(modulename,module_selected);
	
	UxPutTextString(UxWidget,module_selected);
	
	printf("module selected %s\n",module_selected);
	for(i=0;i<nitem;i++)
	   if( !strcmp(mod[i].sigla,module_selected) )
	      break;
	   
	if(mod[i].tipo == PROCESSO) /* nelle reg. la descr. e il nome blocco non servono */
	   if(!(*blockname))  
	   {
	      err_level = ERROR;
	      errore("You must assign a block name");
	
	      return;
	   }
	
	
	printf("Module selected %s N.%d \n",module_selected,i);
	
	
	if( (strlen(blockname)) < 4 )
	   strncat(blockname,"   ",(4-strlen(blockname)));
	
	
	/***** verifico la duplicazione dei blocchi in base 
	       ai quattro caratteri del nome del blocco  che 
	       ho introdotto nel colloquio 
	******/
	strcpy(verifica,blockname);
	
	for(j=0;j<num_blocchi;j++)
	{
	   if(mod[i].tipo == PROCESSO)
	   {
	      if(!strcmp(verifica,bloc[j].sigla_blocco))
	      {
	         err_level=ERROR;
	         errore("Blocco gia' istanziato",verifica);
	         return;
	      }
	   }
	   else if(mod[i].tipo == REGOLAZIONE )
	   {
	      if(!strcmp(module_selected,bloc[j].sigla_modulo))
	      {
	         err_level=ERROR;
	         errore("Blocco gia' istanziato");
	         return;
	      }
	   }  
	}
	
	if(num_blocchi == MAX_BLOCCHI  )
	{
	   err_level=ERROR;
	   errore("Raggiunto il numero massimo dei blocchi");
	   return;
	}
	
	
	num_modulo = i+1;
	
	changes_in_F01 = True;
	
	if(mod[i].tipo == PROCESSO)
	   do_dialogo();
	else
	  add_block(REGOLAZIONE);
	
	   
	
	
	
	
	}
	UxBlockSelectionBoxContext = UxSaveCtx;
}

static void	okCallback_BlockSelectionBox( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCBlockSelectionBox   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxBlockSelectionBoxContext;
	UxBlockSelectionBoxContext = UxContext =
			(_UxCBlockSelectionBox *) UxGetContext( UxWidget );
	{
#ifdef VERSIONE_VECCHIA_ERRATA
	extern int num_tot_moduli;
	extern char blockname[],blockdescr[],modulename[];
	extern int changes_in_F01;
	/*
	extern void add_block();
	*/
	char *module_selected,verifica[9];
	int i,j,nitem;
	
	
	
	nitem = num_tot_moduli;
	
	strcpy(blockname,UxGetText(textBlockName1));
	strcpy(blockdescr,UxGetText(textBlockDescr));
	
	for(j=0;j< ( strlen(blockname) ) ;j++)
	{
	   blockname[j] = toupper(blockname[j]);
	}
	UxPutText(textBlockName1,blockname);
	
	module_selected = UxGetTextString(UxWidget);
	
	if(!(*module_selected))
	{
	   err_level = ERROR;
	   errore("No Module Selected");
	/*
	   UxPopdownInterface(UxWidget);
	*/
	   return;
	}
	
	for(j=0;j< 4 ;j++)
	{
	   module_selected[j] = toupper(module_selected[j]);
	}
	module_selected[4] = 0;
	strcpy(modulename,module_selected);
	
	UxPutTextString(UxWidget,module_selected);
	
	printf("module selected %s\n",module_selected);
	for(i=0;i<nitem;i++)
	   if( !strcmp(moduli[i].sigla,module_selected) )
	      break;
	   
	   
	if(moduli[i].tipo == PROCESSO) /* nelle reg. la descr. e il nome blocco non servono */
	   if(!(*blockname))  
	   {
	      err_level = ERROR;
	      errore("You must assign a block name");
	      UxPopdownInterface(UxWidget);
	      return;
	   }
	
	i++;
	printf("Module selected %s N.%d \n",module_selected,i);
	
	
	if( (strlen(blockname)) < 4 )
	   strncat(blockname,"   ",(4-strlen(blockname)));
	
	
	
	strcpy(verifica,module_selected);
	strcat(verifica,blockname);
	
	for(j=0;j<num_blocchi;j++)
	{
	   if(moduli[i].tipo == PROCESSO)
	   { 
	      if(!strcmp(verifica,blocchi[j].label))
	      {
	         if(j == (num_blocchi -1))  /* ultimo blocco applicato */
	         {
	            UxPopdownInterface(UxWidget); /* esco senza errori */
	            return;
	         }
	         err_level=ERROR;
	         errore("Blocco gia' istanziato",verifica);
	         return;
	      }
	   }
	   else if(moduli[i].tipo == REGOLAZIONE )
	   {
	      if(!strcmp(module_selected,blocchi[j].sigla_modulo))
	      {
	         if(!j )  /* ultimo blocco applicato */
	         {
	            UxPopdownInterface(UxWidget); /* esco senza errori */
	            return;
	         }
	         err_level=ERROR;
	         errore("Blocco gia' istanziato");
	         return;
	      }
	   }  
	}
	
	if(num_blocchi == MAX_BLOCCHI  )
	{
	   err_level=ERROR;
	   errore("Raggiunto il numero massimo dei blocchi");
	   return;
	}
	
	num_modulo = i;
	
	changes_in_F01 = True;
	
	if(moduli[i].tipo == PROCESSO)
	   do_dialogo();
	else
	   add_block(REGOLAZIONE);
	
	UxPopdownInterface(UxWidget);
	
#else                /******************* INIZIO VERSIONE BUONA ***********/
	
	extern int num_tot_moduli;
	extern char blockname[],blockdescr[],modulename[];
	extern int changes_in_F01;
	
	char *module_selected,verifica[9];
	int i,j,nitem;
	MODULO *mod = moduli;     /* serve a ingannare uimx */
	BLOCCO *bloc = blocchi;
	
	
	
	nitem = num_tot_moduli;
	
	strcpy(blockname,UxGetText(textBlockName1));
	strcpy(blockdescr,UxGetText(textBlockDescr));
	
	for(j=0;j< ( strlen(blockname) ) ;j++)
	{
	   blockname[j] = toupper(blockname[j]);
	}
	UxPutText(textBlockName1,blockname);
	
	module_selected = UxGetTextString(UxWidget);
	
	if(!(*module_selected))
	{
	   err_level = ERROR;
	   errore("No Module Selected");
	   UxPopdownInterface(UxWidget);
	   return;
	}
	
	for(j=0;j< 4  ;j++)
	{
	   module_selected[j] = toupper(module_selected[j]);
	}
	module_selected[4]=0;
	strcpy(modulename,module_selected);
	
	UxPutTextString(UxWidget,module_selected);
	
	printf("module selected %s\n",module_selected);
	for(i=0;i<nitem;i++)
	   if( !strcmp(mod[i].sigla,module_selected) )
	      break;
	   
	if(mod[i].tipo == PROCESSO) /* nelle reg. la descr. e il nome blocco non servono */
	   if(!(*blockname))  
	   {
	      err_level = ERROR;
	      errore("You must assign a block name");
	
	      return;
	   }
	
	
	printf("Module selected %s N.%d \n",module_selected,i);
	
	
	if( (strlen(blockname)) < 4 )
	   strncat(blockname,"   ",(4-strlen(blockname)));
	
	
	/***** verifico la duplicazione dei blocchi in base 
	       ai quattro caratteri del nome del blocco  che 
	       ho introdotto nel colloquio 
	******/
	strcpy(verifica,blockname);
	
	for(j=0;j<num_blocchi;j++)
	{
	   if(mod[i].tipo == PROCESSO)
	   {
	      if(!strcmp(verifica,bloc[j].sigla_blocco))
	      {
	         err_level=ERROR;
	         errore("Blocco gia' istanziato",verifica);
	         return;
	      }
	   }
	   else if(mod[i].tipo == REGOLAZIONE )
	   {
	      if(!strcmp(module_selected,bloc[j].sigla_modulo))
	      {
	         err_level=ERROR;
	         errore("Blocco gia' istanziato");
	         return;
	      }
	   }  
	}
	
	if(num_blocchi == MAX_BLOCCHI  )
	{
	   err_level=ERROR;
	   errore("Raggiunto il numero massimo dei blocchi");
	   return;
	}
	
	
	num_modulo = i+1;
	
	changes_in_F01 = True;
	
	if(mod[i].tipo == PROCESSO)
	   do_dialogo();
	else
	  add_block(REGOLAZIONE);
	
	   UxPopdownInterface(UxWidget);
	
	/************************ FINE VERSIONE BUONA *******************/
#endif
	}
	UxBlockSelectionBoxContext = UxSaveCtx;
}

static void	cancelCB_BlockSelectionBox( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCBlockSelectionBox   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxBlockSelectionBoxContext;
	UxBlockSelectionBoxContext = UxContext =
			(_UxCBlockSelectionBox *) UxGetContext( UxWidget );
	{
	UxPopdownInterface(UxWidget);   
	UxPutText(textBlockName1,"");
	UxPutText(textBlockDescr,"");
	UxPutTextString(UxWidget,"");
	
	}
	UxBlockSelectionBoxContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_BlockSelectionBox()
{
	Widget	BlockSelectionBox_shell;

	BlockSelectionBox_shell = XtVaCreatePopupShell( "BlockSelectionBox_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 618,
			XmNy, 388,
			XmNwidth, 700,
			XmNheight, 530,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "BlockSelectionBox",
			XmNiconName, "BlockSelectionBox",
			NULL );

	BlockSelectionBox = XtVaCreateManagedWidget( "BlockSelectionBox",
			xmSelectionBoxWidgetClass, BlockSelectionBox_shell,
			XmNtextColumns, 90,
			XmNnavigationType, XmTAB_GROUP,
			RES_CONVERT( XmNtextString, "" ),
			XmNwidth, 700,
			XmNdialogType, XmDIALOG_SELECTION,
			RES_CONVERT( XmNselectionLabelString, "Selected Module" ),
			RES_CONVERT( XmNlistLabelString, "Module List" ),
			RES_CONVERT( XmNdialogTitle, "Module Selection" ),
			XmNheight, 530,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( BlockSelectionBox, (char *) UxBlockSelectionBoxContext );

	BlockName1 = XtVaCreateManagedWidget( "BlockName1",
			xmRowColumnWidgetClass, BlockSelectionBox,
			XmNheight, 124,
			XmNwidth, 479,
			XmNy, 390,
			XmNx, 10,
			NULL );

	UxPutContext( BlockName1, (char *) UxBlockSelectionBoxContext );

	labelBlockName1 = XtVaCreateManagedWidget( "labelBlockName1",
			xmLabelGadgetClass, BlockName1,
			RES_CONVERT( XmNlabelString, "Block Name" ),
			XmNheight, 100,
			XmNwidth, 100,
			XmNy, 70,
			XmNx, 0,
			NULL );

	UxPutContext( labelBlockName1, (char *) UxBlockSelectionBoxContext );

	textBlockName1 = XtVaCreateManagedWidget( "textBlockName1",
			xmTextFieldWidgetClass, BlockName1,
			XmNcursorPosition, 1,
			XmNmaxLength, 4,
			XmNcolumns, 20,
			XmNheight, 35,
			XmNwidth, 97,
			XmNy, 30,
			XmNx, 0,
			NULL );

	UxPutContext( textBlockName1, (char *) UxBlockSelectionBoxContext );

	labelBlockDescr1 = XtVaCreateManagedWidget( "labelBlockDescr1",
			xmLabelGadgetClass, BlockName1,
			RES_CONVERT( XmNlabelString, "Block Descr" ),
			XmNheight, 20,
			XmNwidth, 250,
			XmNy, 60,
			XmNx, 0,
			NULL );

	UxPutContext( labelBlockDescr1, (char *) UxBlockSelectionBoxContext );

	textBlockDescr = XtVaCreateManagedWidget( "textBlockDescr",
			xmTextFieldWidgetClass, BlockName1,
			XmNcursorPosition, 1,
			XmNmaxLength, 73,
			XmNheight, 20,
			XmNwidth, 280,
			XmNy, 40,
			XmNx, 190,
			NULL );

	UxPutContext( textBlockDescr, (char *) UxBlockSelectionBoxContext );

	XtAddCallback( BlockSelectionBox, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxBlockSelectionBoxContext );

	XtAddCallback( BlockSelectionBox, XmNapplyCallback,
			applyCB_BlockSelectionBox,
			(XtPointer) UxBlockSelectionBoxContext );
	XtAddCallback( BlockSelectionBox, XmNokCallback,
			okCallback_BlockSelectionBox,
			(XtPointer) UxBlockSelectionBoxContext );
	XtAddCallback( BlockSelectionBox, XmNcancelCallback,
			cancelCB_BlockSelectionBox,
			(XtPointer) UxBlockSelectionBoxContext );



	return ( BlockSelectionBox );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_BlockSelectionBox()
{
	Widget                  rtrn;
	_UxCBlockSelectionBox   *UxContext;

	UxBlockSelectionBoxContext = UxContext =
		(_UxCBlockSelectionBox *) XtMalloc( sizeof(_UxCBlockSelectionBox) );

	rtrn = _Uxbuild_BlockSelectionBox();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_BlockSelectionBox()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_BlockSelectionBox();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/


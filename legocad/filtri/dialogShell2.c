
/*******************************************************************************
	dialogShell2.c
	(Generated from interface file dialogShell2.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/FileSB.h>
#include <Xm/DialogS.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo dialogShell2.i
   tipo 
   release 2.6
   data 3/20/95
   reserved @(#)dialogShell2.i	2.6
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#ifndef FILTRI_h
#include "filtri.h"
#endif

extern char filedf[];                 /* filename file di editing */
extern FILE *fpedf;                   /* file di edting */
extern FILTRI *filtri[];              /* vettore filtri */
extern short num_filtri;              /* numero di filtri definiti */

extern void add_items_list();         /* definita in filtri Shell1 */
extern void delete_all_items();       /* definita in filtri Shell1 */
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
	Widget	UxfileSelectionBox1;
} _UxCopendialogShell2;

#define fileSelectionBox1       UxOpendialogShell2Context->UxfileSelectionBox1

static _UxCopendialogShell2	*UxOpendialogShell2Context;

Widget	opendialogShell2;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_opendialogShell2();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

FILTRI *Afiltro_init()
{
   short j;
   FILTRI *ftr;

   printf("\n inizializzazione FILTRO \n");

   ftr = (FILTRI *)(malloc(DIM_FILTRO));
   memset(ftr,0,DIM_FILTRO);
   for(j=0;j<MAXPARFILTRO;j++)
   {
      ftr->var[j] = (char *)(malloc( DIM_PAR ));
      memset(ftr->var[j],0,DIM_PAR);
   }
   printf("\nterminata la inizializzaione \n");
   return(ftr);
}

/*===============================================================
|
|    swap_filtri: swap dei filtri
|
================================================================*/

void Aswap_filtri(int ind)
{
   int j;

   for(j=ind;j<num_filtri;j++)
   {
      filtri[j] = filtri[j+1];    
   }
}


/*================================================================
|
|    filtro_free:  libera la memoria allocata per un filtro 
|                  e ne ripulisce il contenuto
|
=================================================================*/

void Afiltro_free(int ind)
{
   int j;

   for(j=0;j<filtri[ind]->num_var;j++)
   {
      memset(filtri[ind]->var[j],0,DIM_PAR);
      free(filtri[ind]->var[j]);
   }
   memset(filtri[ind],0,DIM_FILTRO);
   free(filtri[ind]);         
   num_filtri--;
   swap_filtri(ind);
   
}




/*===================================================================
|
|  openedf:   apertura file di editing.  Il file pointer e' globale
|             cosi' come le definizioni di errore.            
|             Attualmente il nome del file e'cablato
|            
|
===================================================================*/

int Aopenedf()
{
   strcpy(filedf,UxGetTextString(fileSelectionBox1));
 
    if(fpedf != NULL)
      closedf();

   if( ( fpedf=fopen(filedf,"r+") ) == NULL)
   {
      printf("\n Apro file nuovo\n");
      if( ( fpedf=fopen(filedf,"w") ) == NULL)
         return(ERROPEN);
   }
   return(OK);
}
 
/*===================================================================
|
|  closedf:   chiusura file di editing. Il file pointer e' globale
|
====================================================================*/

int Aclosedf()
{
   fclose(fpedf);
   printf("\n terminata la closedf\n");
}

/*===================================================================
|
|  readedf:   lettura file di editing.  Il file pointer e' globale
|             
|             cosi come le condizioni di errore
|
===================================================================*/

int Areadedf()
{
   char *buff[MAXCHNAME];
   short i=0,j=0;

   printf("\ninizia la lettura filtri \n");

   /* reset dati filtri */

   for(i=0;i<num_filtri;i++)
   {
      for(j=0;j<filtri[i]->num_var;j++)
         memset(filtri[i]->var[j],0,DIM_PAR);
      strcpy(filtri[i]->nome_filtro,"");
      filtri[i]->num_var=0;
   }

   num_filtri = 0; /* inizializzo */

   while(1)
   {
      fscanf(fpedf,"%s",buff);
      if(feof(fpedf))
         break;

      if(!strcmp(buff,TAPPO))   /* inizio record */
      {
         filtri[num_filtri] =  Afiltro_init();
         fscanf(fpedf,"%s",buff);
         strcpy(filtri[num_filtri]->nome_filtro,buff);
         num_filtri++;
         j=0;
      }
      else
      {
         strcpy((filtri[num_filtri - 1])->var[j],buff);
         j++;
         filtri[num_filtri - 1]->num_var = j;
      }
   }

   printf("termina la lettura filtri \n");
}


/*===================================================================
|
|  writedf:   scrittura file di editing.  Il file pointer e' globale
|             
|             cosi come le condizioni di errore
|
===================================================================*/

int Awritedf()
{
   char *buff[MAXCHNAME];
   short i=0,j=0;

   if(fpedf == NULL)
   {
      printf("\nNESSUN FILE DI EDITING APERTO\n");
      return(-1);
   }

   fclose(fpedf);
   fpedf = fopen(filedf,"w");
   for(i=0;i<num_filtri;i++)
   {
      fprintf(fpedf,"%s","FILTRO ");
      printf("/n scrivo il tappo %s\n",TAPPO);
      fprintf(fpedf,"%s\n",filtri[i]->nome_filtro);
      printf("/n scrivo il nome filtro %s\n",filtri[i]->nome_filtro);
      for(j=0;j<filtri[i]->num_var;j++)
      {
         fprintf(fpedf,"%s\n",filtri[i]->var[j]);
         printf("/n scrivo il filtro %s\n",filtri[i]->var[j]);
      }
   }
   fclose(fpedf);
   printf("\nsalvataggio terminato\n");
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	cancelCB_fileSelectionBox1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCopendialogShell2    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxOpendialogShell2Context;
	UxOpendialogShell2Context = UxContext =
			(_UxCopendialogShell2 *) UxGetContext( UxWidget );
	{
	UxPopdownInterface(UxWidget);
	}
	UxOpendialogShell2Context = UxSaveCtx;
}

static void	okCallback_fileSelectionBox1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCopendialogShell2    *UxSaveCtx, *UxContext;

	UxSaveCtx = UxOpendialogShell2Context;
	UxOpendialogShell2Context = UxContext =
			(_UxCopendialogShell2 *) UxGetContext( UxWidget );
	{
	extern int operaz;
	short i=0,j=0,IER=0;
	char *nomi[MAXFILTRI];
	
	
	strcpy(filedf,UxGetTextString(UxWidget));
	
	
	IER = openedf();                           /* apertura file di editing */
	if( IER != OK)
	   printf("Errore apertura file di editing\n");
	else
	{
	   if(operaz == FILE_OPEN)
	   {
	      readedf();                             /* lettura file di editing */
	
	      for(i=0;i<num_filtri;i++)
	      {   
	         nomi[i] = (char *)(malloc(sizeof(char) * MAXCHNAME));
	         strcpy(nomi[i],filtri[i]->nome_filtro);
	      }
	
	      delete_all_items(scrolledList1);  /* elimino tutti gli items precedenti */
	      delete_all_items(scrolledList2);  
	      add_items_list(scrolledList1,nomi,num_filtri);  /* visualizzo la nuova lista */
	
	      closedf();
	
	      for(i=0;i<num_filtri;i++)
	         free(nomi[i]);
	   }
	   else if(operaz == FILE_SAVE)
	      writedf();
	
	}
	
	UxPopdownInterface(UxWidget);
	}
	UxOpendialogShell2Context = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_opendialogShell2()
{

	opendialogShell2 = XtVaCreatePopupShell( "opendialogShell2",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNheight, 170,
			XmNwidth, 380,
			XmNy, 329,
			XmNx, 389,
			NULL );

	UxPutContext( opendialogShell2, (char *) UxOpendialogShell2Context );

	fileSelectionBox1 = XtVaCreateWidget( "fileSelectionBox1",
			xmFileSelectionBoxWidgetClass, opendialogShell2,
			XmNlistVisibleItemCount, 4,
			RES_CONVERT( XmNpattern, "*.edf" ),
			RES_CONVERT( XmNnoMatchString, "None" ),
			RES_CONVERT( XmNdirMask, "/usr/users/legoroot/svil/legocad/filtri/*.edf" ),
			RES_CONVERT( XmNdialogTitle, "Editing File Selection" ),
			XmNdialogStyle, XmDIALOG_PRIMARY_APPLICATION_MODAL,
			XmNheight, 250,
			XmNwidth, 450,
			XmNy, 190,
			XmNx, 480,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( fileSelectionBox1, (char *) UxOpendialogShell2Context );

	XtAddCallback( opendialogShell2, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxOpendialogShell2Context );

	XtAddCallback( fileSelectionBox1, XmNcancelCallback,
			cancelCB_fileSelectionBox1,
			(XtPointer) UxOpendialogShell2Context );
	XtAddCallback( fileSelectionBox1, XmNokCallback,
			okCallback_fileSelectionBox1,
			(XtPointer) UxOpendialogShell2Context );



	return ( opendialogShell2 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_opendialogShell2()
{
	Widget                  rtrn;
	_UxCopendialogShell2    *UxContext;

	UxOpendialogShell2Context = UxContext =
		(_UxCopendialogShell2 *) XtMalloc( sizeof(_UxCopendialogShell2) );

	rtrn = _Uxbuild_opendialogShell2();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_opendialogShell2()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_opendialogShell2();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/


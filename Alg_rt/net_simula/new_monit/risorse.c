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
 * risorse.c
 *
 * funzioni relative alla inizializzazione e gestione delle risorse
 *				dell' applicazione
 */
#include <stdio.h>
#include <string.h>

#include <X11/Xlib.h>
#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Xm/Label.h>
#include <Xm/CascadeB.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>

#include "UxXt.h"

#include "resourceSetting.h"
#include "risorse.h"
#include "risorse_default.h"
#include "parametri.h"

extern RESOURCE_DEF *Rdef;

XrmDatabase NewXdb;
extern XrmDatabase Xdb;

extern Widget masterMenu;

#define N_ITEM_RES      4     /* numero di item che definiscono la risorsa */
static char *risorse[][N_ITEM_RES] =
   {
   {"Colors","Application background","",""} ,
   {"Colors","Malf. Color","",""} ,
   {"Colors","Frem Color","",""} ,
   {"Fonts","Generic lists","",""} ,
   {"categoria1","display1","risorsa1","classe1"} ,
   {"categoria3","display2","risorsa2","classe2"} ,
   {"categoria1","display3","risorsa3","classe3"} ,
   {"categoria3","display4","risorsa4","classe4"} ,
   {"NULL","NULL","NULL","NULL"}
   };

char *getCategoriaRes ();
char *getRisorsaRes ();
char *getRisorsaDis ();
char *getRisorsaValRes ();
char *getRisorsaValDefRes ();
char *getRisorsaClassRes ();
void selectResourceCategory ();

/********************************************************************/
/*
 * ritorna il database delle risorse correntemente attive
 */
XrmDatabase GetApplResDb (Display *d)
{
	return (XrmGetDatabase(d));
}
/********************************************************************/
/*
 * ritorna il database delle risorse inizializzato da file esterno
 */
XrmDatabase GetExtResDb (char *filename)
{
	return (XrmGetFileDatabase(filename));
}
/********************************************************************/	
/*
 * salva il database specificato nel file 
 */
void SaveResDatabase (XrmDatabase SourceDb, char *filename)
{
	XrmPutFileDatabase (SourceDb, filename);
}
/********************************************************************/
/*
 * attua la modifica del database delle risorse corrente
 *	modo:	MERGE or REPLACE
 */
void ApplyResDb (XrmDatabase SourceDb, XrmDatabase *Db, Display *d, int modo)
{
	switch (modo)
		{
		case MERGE:
			XrmMergeDatabases (SourceDb, Db);
			break;
		case REPLACE:
			XrmSetDatabase (d, SourceDb);
			break;
		}
	return;	
}
/********************************************************************/	
int switchDatabase ()
{
printf ("Funzione switchDatabase \n");

	Xdb = GetApplResDb (UxDisplay);
	NewXdb = GetExtResDb ("./RISORSEBANCO");
	ApplyResDb (NewXdb, &Xdb, UxDisplay, MERGE);
	XrmInitialize ();	
}
/********************************************************************/
/*
 * carica nelle strutture i dati fissi di configurazione
 */
int caricaDatiRisorse (Widget w)
{
int i,n,cat;
int size = 0;

/* ciclo per determinare le dimensioni dell' area da allocare */
/* alloca per il numero delle entries + 1 per il tappo			*/
	i = 0;
	n = 0;
	while (strcmp(risorse[i][n],"NULL"))
		i++;

	printf ("da allocare %d entries\n",i);
	Rdef = (RESOURCE_DEF *)malloc(sizeof(RESOURCE_DEF)*(i+1));

/* caricamento		*/

	i = 0;
	cat = 0;

   while (strcmp(risorse[i][0],"NULL"))
      {
		strcpy (Rdef[i].categoria,risorse[i][0]);
		strcpy (Rdef[i].label,risorse[i][1]);
		strcpy (Rdef[i].risorsa,risorse[i][2]);
		strcpy (Rdef[i].classe,risorse[i][3]);
		for (n=0; n<i; n++)
			{
			if (!strcmp(Rdef[i].categoria,Rdef[n].categoria)) /* gia visto */
				{
				Rdef[i].catIndx = Rdef[n].catIndx;	
				break;
				}
			}
		if (n == i)		/* new entry	*/
			{
			Rdef[i].catIndx = cat;
printf ("[%s] nuova categoria indx %d\n",Rdef[i].categoria,Rdef[i].catIndx);
			cat ++;
			}
      i++;
      }
/* tappo finale	*/
	strcpy (Rdef[i].categoria,risorse[i][0]);
   strcpy (Rdef[i].label,risorse[i][1]);
   strcpy (Rdef[i].risorsa,risorse[i][2]);
   strcpy (Rdef[i].classe,risorse[i][3]);
	Rdef[i].catIndx = -1;
/******
	i = 0;
	while (Rdef[i].catIndx >= 0)
		{
		printf ("%d %s %s %s %s \n",
				Rdef[i].catIndx, Rdef[i].categoria,Rdef[i].label,
				Rdef[i].risorsa,Rdef[i].classe);
		i++;
		}
*************/
}
/**************************************************************/
int displayRisorse (Widget w)
{
	displayCategorieRisorse (w);
}
/**************************************************************/
/*
 * genera le entries relative alla categoria "n"
 */
int displayItemRisorse (Widget w, int n)
{
_UxCresourceSetting *Ctx;
int i;
int n_entries;
int item;

	Ctx = (_UxCresourceSetting *)UxGetContext(w);
	
	n_entries =	getNumResCat (Rdef,n);
printf ("Richiesta cat. indice %d (%d items)\n",n,n_entries);

	Ctx->Uxn_entries = n_entries;
	
	Ctx->UxresForm = (Widget *)XtMalloc(sizeof(Widget)*n_entries);
	Ctx->UxresLabel = (Widget *)XtMalloc(sizeof(Widget)*n_entries);
	Ctx->UxresText = (Widget *)XtMalloc(sizeof(Widget)*n_entries);
	Ctx->UxresMoreButton = (Widget *)XtMalloc(sizeof(Widget)*n_entries);
	Ctx->Uxindx = (int *)malloc(sizeof(int)*n_entries);

	i = 0;
	item = 0;
	while (Rdef[i].catIndx >= 0)
		{
		if (Rdef[i].catIndx == n)
			{
			fprintf (stderr,"Creazione item %d\n",item);
			creaResEntry (w,Rdef,i,item);
			item ++;
			}
		i++;
		}
}
/**************************************************************/
int clearResourceList (Widget w)
{
_UxCresourceSetting *Ctx;
int i;

	Ctx = (_UxCresourceSetting *)UxGetContext(w);
/*
 * distrugge i widget
 */
printf ("N-entries = %d\n",Ctx->Uxn_entries);

	for (i=0; i<Ctx->Uxn_entries; i++)
		{
		DistruggiInterfaccia (Ctx->UxresForm[i]);
		DistruggiInterfaccia (Ctx->UxresLabel[i]);
		DistruggiInterfaccia (Ctx->UxresText[i]);
/*
		DistruggiInterfaccia (Ctx->UxresMoreButton[i]);
*/
		}
/* 
 * libera la memoria
 */
	if (Ctx->Uxn_entries > 0)
		{
		XtFree (Ctx->UxresForm);
		XtFree (Ctx->UxresLabel);
		XtFree (Ctx->UxresText);
		XtFree (Ctx->UxresMoreButton);
		free (Ctx->Uxindx);
		}
/*
 * azzera il contatore
 */
	Ctx->Uxn_entries = 0;

	return (0);
}
/**************************************************************/
/*
 * crea la entry n-esima relativa all' i-esimo elemento di *r
 */
int creaResEntry (Widget w, RESOURCE_DEF *r, int i, int n)
{
_UxCresourceSetting *Ctx;
Widget BaseWidget;

	Ctx = (_UxCresourceSetting *)UxGetContext(w);
	BaseWidget = Ctx->UxresourceSettingResRc;


	Ctx->Uxindx[n] = i;
	
	Ctx->UxresForm[n] = XtVaCreateManagedWidget("resForm",
         xmFormWidgetClass, BaseWidget,
         XmNresizePolicy, XmRESIZE_NONE,
         XmNx, 3,
         XmNy, 3,
         XmNwidth, 350,
         XmNheight, 25,
         NULL );
   UxPutContext( Ctx->UxresForm[n], (char *) Ctx );

   Ctx->UxresLabel[n] = XtVaCreateManagedWidget( "resLabel",
         xmLabelWidgetClass, Ctx->UxresForm[n],
         XmNleftAttachment  , XmATTACH_FORM,
         XmNy, 0,
         XmNwidth, 100,
         XmNborderWidth, 1,
         XmNmarginHeight, 1,
         XmNresizeHeight, True,
         XmNbottomAttachment, XmATTACH_FORM,
         XmNtopAttachment, XmATTACH_FORM,
         XmNrecomputeSize, False,
         RES_CONVERT( XmNlabelString, getRisorsaDis(Rdef,i)),
         XmNalignment, XmALIGNMENT_END,
         NULL );
    UxPutContext( Ctx->UxresLabel[n], (char *) Ctx );
	
	 Ctx->UxresText[n] = XtVaCreateManagedWidget( "resText",
			xmTextWidgetClass, Ctx->UxresForm[n],
			XmNleftAttachment  , XmATTACH_WIDGET,
			XmNleftWidget,	Ctx->UxresLabel[n],
			XmNleftOffset,	30,
			XmNbottomAttachment, XmATTACH_FORM,
         XmNtopAttachment, XmATTACH_FORM,
         XmNmarginHeight, 2,
         NULL );
	UxPutContext( Ctx->UxresText[n], (char *) Ctx );

	write_txt (Ctx->UxresText[n], getRisorsaValRes(Rdef,i));

	return (0);
}
/**************************************************************/
int displayCategorieRisorse (Widget w)
{
Widget BaseWidget;
_UxCresourceSetting *Ctx;
int n_categorie;
int i;
static int *pp;		/* pointer passato alla callback */

	Ctx = (_UxCresourceSetting *)UxGetContext(w);

	BaseWidget = Ctx->UxresourceSettingCategSelectForm;
	
	Ctx->UxoptMenuForm = XtVaCreateManagedWidget( "MenuForm",
         xmFormWidgetClass, BaseWidget,
         XmNresizePolicy, XmRESIZE_NONE,
         XmNx, 3,
         XmNy, 3,
         XmNwidth, 380,
         XmNheight, 25,
         NULL );
   UxPutContext( Ctx->UxoptMenuForm, (char *) Ctx );

   Ctx->UxoptMenuShell = XtVaCreatePopupShell ("optMenuShell",
         xmMenuShellWidgetClass, Ctx->UxoptMenuForm,
         XmNwidth, 1,
         XmNheight, 1,
         XmNallowShellResize, TRUE,
         XmNoverrideRedirect, TRUE,
         NULL );
	UxPutContext( Ctx->UxoptMenuShell, (char *) Ctx );

	Ctx->UxoptMenuRc = XtVaCreateWidget( "menu6_p2",
         xmRowColumnWidgetClass, Ctx->UxoptMenuShell,
         XmNrowColumnType, XmMENU_PULLDOWN,
         NULL );
   UxPutContext( Ctx->UxoptMenuRc, (char *) Ctx );

	n_categorie = getNumeroCategorieRes (Rdef);
	Ctx->UxoptMenuItem = (Widget *)XtMalloc(sizeof(Widget)*n_categorie);
	pp = (int *)malloc(sizeof(int)*n_categorie);
	for (i=0; i<n_categorie; i++)
		{
		Ctx->UxoptMenuItem[i] = 
            XtVaCreateManagedWidget( "menuItem",
            xmPushButtonWidgetClass,
            Ctx->UxoptMenuRc,
            RES_CONVERT( XmNlabelString,getCategoriaRes (Rdef,i)),
            NULL );
      UxPutContext(Ctx->UxoptMenuItem[i], (char *) Ctx ); 

		pp[i] = getIndxCategoriaRes (Rdef,i);
      XtAddCallback(Ctx->UxoptMenuItem[i],
               XmNactivateCallback, selectResourceCategory,
               (XtPointer) &(pp[i]));
		}
   Ctx->UxoptMenu = XtVaCreateManagedWidget( "optMenu",
         xmRowColumnWidgetClass,
         Ctx->UxoptMenuForm,
         XmNrowColumnType, XmMENU_OPTION,
         XmNsubMenuId,  Ctx->UxoptMenuRc,
         XmNleftAttachment, XmATTACH_FORM,
         XmNleftOffset, 30,
         XmNwidth, 150,
         XmNmarginHeight, 3,
         NULL );
   UxPutContext( Ctx->UxoptMenu, (char *) Ctx );

	return (0);
}
/**************************************************************/
/*
 * restituisce il numero di risorse per la categoria indicata
 */
int getNumResCat (RESOURCE_DEF *r, int n_indx)
{
int i;
int n;
	i = 0;
	n = 0;
	while (r[i].catIndx >= 0)
      {
		if (r[i].catIndx == n_indx)
			n++;
		i++;
		}
	return (n);
}
/**************************************************************/
int getNumeroCategorieRes (RESOURCE_DEF *r)
{
int i,n;
int n_cat = 0;

	i = 0;
	while (r[i].catIndx >= 0)
		{
		for (n=0; n<i; n++)
			{
			if (r[i].catIndx == r[n].catIndx)
				break;
			}
		if (n == i)		/* new entry		*/
			n_cat ++;
		i ++;
		}
	return (n_cat);
}
/**************************************************************/
/*
 * ritorna la stringa descrittiva della n-esima categoria
 */
char *getCategoriaRes (RESOURCE_DEF *r, int n_item)
{
int i,n;
int n_cat = 0;

   i = 0;
   while (r[i].catIndx >= 0)
      {
      for (n=0; n<i; n++)
         {
         if (r[i].catIndx == r[n].catIndx)
            break;
         }
      if (n == i)    /* new entry      */
			{
			if (n_item == n_cat)		/* elemento cercato	*/
				break;
         n_cat ++;
			}
      i ++;
      }
	return (r[i].categoria);
}
/**************************************************************/
/*
 * ritorna l' indice della n-esima categoria
 */
int getIndxCategoriaRes (RESOURCE_DEF *r, int n_item)
{
int i,n;
int n_cat = 0;

   i = 0;
   while (r[i].catIndx >= 0)
      {
      for (n=0; n<i; n++)
         {
         if (r[i].catIndx == r[n].catIndx)
            break;
         }
      if (n == i)    /* new entry      */
         {
         if (n_item == n_cat)    /* elemento cercato  */
            break;
         n_cat ++;
         }
      i ++;
      }
   return (r[i].catIndx);
}
/**************************************************************/
/*
 * ritorna la risorsa dell' n esimo item delle risorse
 */
char *getRisorsaRes (RESOURCE_DEF *r, int n_item)
{
   return (r[n_item].risorsa);
}
/**************************************************************/
/*
 * ritorna la risorsa dell' n esimo item delle risorse
 */
char *getRisorsaDis (RESOURCE_DEF *r, int n_item)
{
   return (r[n_item].label);
}
/**************************************************************/
/*
 * ritorna il valore della risorsa dell' n esimo item delle risorse
 */
char *getRisorsaValRes (RESOURCE_DEF *r, int n_item)
{
   return (r[n_item].valore);
}
/**************************************************************/
/*
 * ritorna il valore di default della risorsa dell' n esimo item delle risorse
 */
char *getRisorsaValDefRes (RESOURCE_DEF *r, int n_item)
{
   return (r[n_item].valoreDef);
}
/**************************************************************/
/*
 * ritorna la classe della risorsa dell' n esimo item delle risorse
 */
char *getRisorsaClassRes (RESOURCE_DEF *r, int n_item)
{
   return (r[n_item].classe);
}
/************************************************************/
/*
 *  Switch categoria risorse
 */
void selectResourceCategory (w, data, reason)
Widget w;
char *data;
XmPushButtonCallbackStruct *reason;
{
int item;
_UxCresourceSetting *Ctx;

	Ctx = (_UxCresourceSetting *)UxGetContext(w);
	item = *(int *)data;
	printf ("Selezionato item %d\n",item);
	Ctx->UxselectedCategory = item;
	clearResourceList (w);
	displayItemRisorse (w,item);
}
/************************************************************/
int applyResource (Widget w)
{
int n_entries;
int i;
_UxCresourceSetting *Ctx = (_UxCresourceSetting *)UxGetContext(w);

	n_entries = Ctx->Uxn_entries;
	
	for (i=0; i<n_entries; i++)
		strcpy (Rdef[Ctx->Uxindx[i]].valore, XmTextGetString(Ctx->UxresText[i]));

	return (0);
}

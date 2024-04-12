/**********************************************************************
*
*       C Source:               XlAnObjList.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 16 17:12:45 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: XlAnObjList.c,2 %  (%full_filespec: 1,csrc,XlAnObjList.c,2 %)";
#endif
/*
   modulo XlAnObjList.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlAnObjList.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)XlAnObjList.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <Xm/Xm.h>
#include <X11/Core.h>
#include <Xl/XlCoreP.h>
#include <Xl/XlManagerP.h>
#include <Xl/XlCompositeP.h>
#include <Xl/XlLedP.h>
#include <Xl/XlPortP.h>
#include <Xl/XlBottoneP.h>
#include <Xl/XlIndicP.h>
#include <Xl/XlIndicErrP.h>
#include <Xl/XlLabelP.h>
#include <Xl/XlAllarmiP.h>
#include <Xl/XlBitmapP.h>
#include <Xl/XlSetValoreP.h>
#include <Xl/XlGraficoP.h>

#define XtNnum_widget "num_widget"
#define XtCNum_widget "Num_widget"
#define XtNelenco_wid "elenco_wid0"
#define XtCElenco_wid "Elenco_wid0"

static XtResource res_num_widget[]= {
				       {
				          XtNnum_widget,
					  XtCNum_widget,
					  XmRInt,
					  sizeof(int),
					  0,
					  XmRImmediate,
        				  0
        				}
				     };

static XtResource res_elenco_widget[]= {
                                	  {
                               		     XtNelenco_wid,
                                             XtCElenco_wid,
                                             XmRString,
                                             sizeof(char *),
                                             0,
                                             XmRString,
                                             ""
                                           }
                                        };

/*------------------------------------------------------------------
 * Function Name:   XlGetAnObjList                                 *
 *                                                                 *
 * Parameter:                                                      *
 *      Widget w;   indice dello widget della top level Shell      *
 *                                                                 *
 * Description:   carica la lista di tipo AN_OBJ                   *
 *                conoscendo l'elenco dei nomi determinati dalle   *
 *                resource ricavate dal Widget w                   *
 *                e ritorna il puntatore alla lista AN_OBJ         *
 *                l'utente di questa routine si deve preoccupare   *
 *                di liberare la memoria occupata dalla AN_OBJ     *
 *                                                                 *
 * Date: 14 Gennaio 1993        Ver: 1.0                           *
 *-----------------------------------------------------------------*/
   
AN_OBJ *XlGetAnObjList( Widget w )
{
   int num_widget,i;
   AN_OBJ *plista_an_obj;
   char *ListaDaLiberare,*str_elenco,*str_type;
   char class_name[20];
   Display *Displ;
   XrmDatabase DB;
   XrmValue Val;

/*  Ricavo dallo widget il database associato  */
Displ = XtDisplay (w);
DB = XrmGetDatabase (Displ);

/*  Leggo dal database il numero degli oggetti  */
XrmGetResource (DB,XtNnum_widget,XtCNum_widget,&str_type,&Val);
sscanf (Val.addr,"%d",&num_widget);

/*  Leggo dal database l'elenco degli oggetti  */
XrmGetResource (DB,XtNelenco_wid,XtCElenco_wid,&str_type,&Val);
str_elenco = (char *)calloc ((int)Val.size,sizeof(char));
ListaDaLiberare = str_elenco;
strncpy (str_elenco, Val.addr, Val.size);

/*
 Alloca la lista degli oggetti da creare riservando l'ultimo 
 elemento per contenere un NULL come terminatore della lista
*/

   if( (plista_an_obj= (AN_OBJ *)calloc(num_widget+1,sizeof(AN_OBJ))) == NULL)
      return(NULL);

   for(i=0;i<num_widget;i++)
   {
      sscanf(str_elenco,"%s",plista_an_obj[i].nome);
      str_elenco+=(strlen(plista_an_obj[i].nome)+1);
      sscanf(str_elenco,"%s",class_name);
      str_elenco+=(strlen(class_name)+1);
      plista_an_obj[i].classe = XlGetClassWid(class_name);
   }
   free (ListaDaLiberare);
   return(plista_an_obj);
}

/*------------------------------------------------------------------
 * Function Name:   XlFreeAnObjList                                *
 *                                                                 *
 * Parameter:                                                      *
 *      AN_OBJ *lista;   puntatore alla lista AN_OBJ               *
 *                                                                 *
 * Description:   libera la memoria occupata dalla  lista AN_OBJ   *
 *                                                                 *
 * Date: 14 Gennaio 1993        Ver: 1.0                           *
 *-----------------------------------------------------------------*/
   
void XlFreeAnObjList(AN_OBJ *lista)
{
   if(lista != NULL)
      free(lista);
}

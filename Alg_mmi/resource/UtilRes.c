/**********************************************************************
*
*       C Source:               UtilRes.c
*       Subsystem:              2
*       Description:
*       %created_by:    lopez %
*       %date_created:  Tue Oct 22 09:54:31 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: UtilRes.c-2 %  (%full_filespec: UtilRes.c-2:csrc:2 %)";
#endif
/*
        Inizio sezione per SCCS
*/
/*
   modulo UtilRes.c
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)UtilRes.c	5.2
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)UtilRes.c	5.2\t2/13/96";
/*
        Fine sezione per SCCS
*/

/*
 UtilRes.c
 Contiene routines di utilita' per il resource editor ed editors 
 associati 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Xm/List.h>
#include <Xm/SelectioB.h>
#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>
#include <Xl/XlIconReg.h>
#include <Xl/XlPort.h>
#include <Xl/XlDispReg.h>

#include <Ol/OlForm.h>
#include "res_edit.h"

#include "libutilx.h"


/***************************************************************
	Funzione che setta la posizione dello Widget DaSpostare
	spiazzata rispetto alla posizione dello Widget Parente;
***************************************************************/
void InterfaceSetPos (Widget DaSpostare,Widget Parente)
{
Position PX,PY;

get_something (Parente, XmNx, (void*) &PX);
get_something (Parente, XmNy, (void*) &PY);

set_something_val (DaSpostare, XmNx, (XtArgVal)PX+SPIAZZAMENTO);
set_something_val (DaSpostare, XmNy, (XtArgVal)PY+SPIAZZAMENTO);
}

/***************************************************************
        Funzione che converte il valore di una stringa
        in un valore di pixel corrispondente;
***************************************************************/
Boolean CvtStrToPixel (Widget ogget,char *Stringa,Pixel *Pix)
{
        unsigned long piani[1];
        Colormap colmap;
        XColor xcol;


        colmap = DefaultColormap ( XtDisplay(ogget),
                        DefaultScreen (XtDisplay(ogget)) );
        if ( !XParseColor (XtDisplay(ogget) , colmap , Stringa , &xcol) )
           {
           printf("Errore XParseColor: colore inesistente\n");
           return(False);
           }
        if(!XAllocColor(XtDisplay(ogget),colmap,&xcol))
           {
           printf("Errore XAllocColor: impossibile allocare un nuovo colore\n");
           return(False);
           }
        *Pix = xcol.pixel;
        return(True);
}

/***************************************************************
        Funzione che converte il valore del pixel della
        risorsa passata come parametro nella stringa
        contenente le componenti Red,Green,Blue
***************************************************************/
char *CvtPixToStr (Widget wid,char *NomeRes)
{
        Arg args[3];
        XColor Colore;
        Colormap cmap;
        char *vstring;
        Display *Displ;

        /*  Ricavo il display dal widget passato come parametro */
        Displ = XtDisplay (wid);
        XtSetArg (args[0], NomeRes, &Colore.pixel);
        XtSetArg (args[1], XmNcolormap, &cmap);
        XtGetValues (wid, args, 2);
        XQueryColor (Displ, cmap, &Colore);
        vstring = (char *)XtCalloc (15, sizeof(char));
        sprintf (vstring,"#%04x%04x%04x",Colore.red,Colore.green,Colore.blue);
        return (vstring);
}

/************************************************
   Controlla se la stringa in input e' un float  
************************************************/
Boolean NumFloVerifica(char *Stringa)
{
int i,lunghezza,Ritorno1,Ritorno2;
float Valore;

lunghezza = strlen (Stringa);
for (i=0;i<lunghezza;i++)
 if ( (!isdigit(Stringa[i])) && (Stringa[i] != '.') && (Stringa[i] != '-') &&
	(Stringa[i] != 'e') && (Stringa[i] != 'E') && (Stringa[i] != '+') )
   return (False);
Ritorno1 = sscanf (Stringa,"%e",&Valore);
Ritorno2 = sscanf (Stringa,"%f",&Valore);
if ( (Ritorno1==0) || (Ritorno2==0) )
  return (False);
return (True);
}

/************************************************
   Controlla se la stringa in input e' un int 
************************************************/
Boolean NumIntVerifica(char *Stringa)
{
int i,lunghezza;

lunghezza = strlen (Stringa);
for (i=0;i<lunghezza;i++)
 if (!isdigit(Stringa[i])) return (False);
return (True);
}

/*
 Cariacamento di un bitmap: utilizzata per i bitmap dei bottoni dei
 comandi di Draw
*/
#ifndef ON_MMI
Boolean LoadBitmap(Widget w, Pixmap *stip, char * bits, int width, int height)
{
long cnero,cbianco;
Pixel background;

get_something(w,XmNbackground,(void*) &background);

if((*stip=XCreatePixmapFromBitmapData(XtDisplay(w),
            RootWindow(XtDisplay(w),DefaultScreen(XtDisplay(w))),bits,
            width,height,
            BlackPixel(XtDisplay(w),DefaultScreen(XtDisplay(w))), background,
            DefaultDepth(XtDisplay(w),DefaultScreen(XtDisplay(w)))))== False)
        {
        fprintf(stderr,"Error on Pixmap creation \n");
        exit(1);
        }
}
#endif

/*
 SettaBottoni
 Utilizzata nelle selection box di scelta file di icona animata:
 disabilita/abilita i bottoni di Import e Cancel per evitare 
 l'uscita dalla box mentre l'icona e' in editing
*/
void SettaBottoni (Boolean Valore,Widget Ogg)
{
Widget BottoneIMPORT,BottoneCANCEL;

BottoneIMPORT = (Widget )XmSelectionBoxGetChild (Ogg,
      XmDIALOG_OK_BUTTON);
BottoneCANCEL = (Widget )XmSelectionBoxGetChild (Ogg,
      XmDIALOG_CANCEL_BUTTON);

set_something_val (BottoneIMPORT, XmNsensitive, (XtArgVal)Valore);
set_something_val (BottoneCANCEL, XmNsensitive, (XtArgVal)Valore);
}

/*
 EseguiNuovoBitmap
 Richiama l'eseguibile per la creazione di un nuovo bitmap
 disabilitando i bottoni di Import e Cancel della selection box
 chiamante
*/
PROG_DATA *EseguiNuovoBitmap (char *Nomefile,char *Larghezza,char *Altezza,Widget Ogg)
{
PROG_DATA *pdata=NULL;
char Param[10],Misura[100];

#ifndef ON_MMI
strcpy (Misura,Larghezza);
strcat (Misura,"x");
strcat (Misura,Altezza);
#ifndef VMS
pdata = (PROG_DATA *)ActiveProgWithParameter ("bitmap",Nomefile,Misura,NULL);
#else
pdata = ActiveProgWithParameter (Ogg,"bitmap",Nomefile,Misura,NULL);
#endif
#endif 

SettaBottoni(False,Ogg);
return(pdata);
}

/*
 EseguiIcona
 Richiama l'eseguibile per l'editing dell'icona animata
 disabilitando i bottoni di Import e Cancel della selection box
 chiamante
*/
PROG_DATA *EseguiIcona (char *Nomefile,Widget Ogg,char *Colore,Widget OSel)
{
PROG_DATA *pdata= NULL;
int Snap=8;

#ifndef ON_MMI 
if (XlIsIconReg(OSel))
  {
  printf ("Esegui Icona su IconReg\n");
#ifndef VMS
  pdata = (PROG_DATA *)ActiveProgWithParameter ("draw",Nomefile,"8","-bg",Colore,NULL);
#else
  pdata = ActiveProgWithParameter (OSel,"draw",Nomefile,"8","-bg",Colore,NULL);
#endif
  }
else
  {
  printf ("Esegui Icona generica\n");
#ifndef VMS
  pdata = (PROG_DATA *)ActiveProgWithParameter ("draw","-bg",Colore,Nomefile,NULL);
#else
  pdata = ActiveProgWithParameter (OSel,"draw","-bg",Colore,Nomefile,NULL);
#endif
  }
SettaBottoni(False,Ogg);
#endif 
return(pdata);
}

/*
 EseguiBitmap
 Richiama l'eseguibile per l' editing di un bitmap
 disabilitando i bottoni di Import e Cancel della selection box
 chiamante
*/
PROG_DATA *EseguiBitmap (char *Nomefile,Widget Ogg)
{
PROG_DATA *pdata;
#ifndef ON_MMI 
#ifndef VMS
pdata = (PROG_DATA *)ActiveProgWithParameter ("bitmap",Nomefile,NULL);
#else
pdata = ActiveProgWithParameter (Ogg,"bitmap",Nomefile,NULL);
#endif
SettaBottoni(False,Ogg);
#endif 
return(pdata);
}

/*
 EseguiLoadBitmap
 Ricava dalla selection box il nome del file bitmap da editare
 e richiama l'editor del bitmap
*/
void EseguiLoadBitmap(Widget Ogg)
{
Widget Figlio;
char *appoggio,nomefile[100];

Figlio = (Widget )XmSelectionBoxGetChild (Ogg,XmDIALOG_TEXT);
appoggio = (char *)XmTextGetString (Figlio);
strcpy (nomefile,appoggio);
strcat (nomefile,".bmp");
EseguiBitmap(nomefile,Ogg);
XtFree (appoggio);
}

/*
 EseguiCaricaIcona
 Ricava dalla selection box il nome del file icona da editare
 e richiama l'editor del icona
*/
void EseguiCaricaIcona(Widget Ogg,char *Colore,Widget OggSe)
{
Widget Figlio;
char *appoggio,nomefile[100];

Figlio = (Widget )XmSelectionBoxGetChild (Ogg,XmDIALOG_TEXT);
appoggio = (char *)XmTextGetString (Figlio);
strcpy (nomefile,appoggio);
strcat (nomefile,".ico");
EseguiIcona (nomefile,Ogg,Colore,OggSe);
XtFree (appoggio);
}

/*********************************************************
	Funzione che dall'indice di Widget passato come 
	parametro restituisce l'indice della form associata
	se questa e' stata precedentemente allocata, altrimenti
	restituisce NULL
*********************************************************/
OlFormObject ResGetForm (Widget wid)
{
OlFormObject IndiceForm;
Widget WidgetPadre;

if ( XlIsIconReg (wid) )
  {
  /*  Prendo il puntatore alla form e lo restituisco
	se la form non e' allocata la risorsa XlNobjectForm
	e' settata a NULL  */
  get_something (wid, XlNobjectForm, (void*) &IndiceForm);
  return (IndiceForm);
  }
if ( (XlIsPort (wid)) || (XlIsDispReg (wid)) )
  {
  /*  Prendo il padre per verificare se e' la
	drawing area o se e' una IconReg  */
  WidgetPadre = XtParent (wid);
  /*  Controllo se e' una IconReg e se non lo e'
	viene ritornato NULL  */
  if ( XlIsIconReg (WidgetPadre) )
    {
    /*  Prendo il puntatore alla form e lo restituisco
        se la form non e' allocata la risorsa XlNobjectForm
        e' settata a NULL  */
    get_something (WidgetPadre, XlNobjectForm, (void*) &IndiceForm);
    return (IndiceForm);
    }
  else return (NULL);
  }
return (NULL);
}

#ifndef ON_PAGEDIT 
#ifndef ON_MMI
/********************************************************
	Routine che esamina se la tag in ingresso e' gia'
	stata utilizzata in altre porte dell'icona di
	regolazione passata come parametro
********************************************************/
Boolean is_tag_in_port(Widget wid, char *tag)
{
WidgetList childcomp;
int j;
char *nome_porta;
Cardinal num_childcomp;
Arg arg[4];

/*  Setto la risorsa nel vettore degli argomenti  */
XtSetArg(arg[0],XlNportName,&nome_porta);

/* recupero i figli di XlComposite */
get_something (wid,XmNchildren, (void*) &childcomp);
get_something (wid,XmNnumChildren, (void*) &num_childcomp);

/*  Controllo tutti i figli dell'IconReg  */
for(j=0;j<num_childcomp;j++)
  {
  /*  Se e' una porta ne controlla la tag  */
  if( XlIsPort(childcomp[j]) )
    {
    XtGetValues(childcomp[j],arg,1);
    if(strncmp(nome_porta,tag,2)==0)
      return(True);
    }
  }
return(False);
}
#endif
#endif

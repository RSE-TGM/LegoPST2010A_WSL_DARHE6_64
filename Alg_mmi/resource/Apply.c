/**********************************************************************
*
*       C Source:               Apply.c
*       Subsystem:              2
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Mon Jun  7 14:35:33 2004 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: Apply.c-5 %  (%full_filespec: Apply.c-5:csrc:2 %)";
#endif
/*
        Inizio sezione per SCCS
*/
/*
   modulo Apply.c
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)Apply.c	5.2
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)Apply.c	5.2\t2/13/96";
/*
        Fine sezione per SCCS
*/

/***************************************************************
		modulo:  Apply.c

	Routine che esegue i controlli sugli input del
	ResourceEditor quando l'utente esegue l'apply
        sul bottone centrale del resource editor.
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <Xm/Xm.h>
#include <Xm/TextF.h>
#include <Xl/Xl.h>
#include <Xl/XlIconReg.h>
#include <Xl/XlPort.h>
#include <Ol/OlForm.h>
#include <Rt/RtMemory.h>
#include "libutilx.h"
#include "res_edit.h"

OlFormObject ResGetForm (Widget );


/*
 Esegue un controllo su tutti i campi appartenenti al
 Row column passato come parametro (la routine dovra' essere chiamata 
 una volta per ogni row column presentei: ogni row col. corrisponde
 ad una categoria di risorse. Es: Geometric_RC,Specific_RC ecc..).
*/
int EseguiControlliInput (Confinfo,Database,WdgSel,RowCol)
XlConfInfo Confinfo;  /* punta alle confinfo dell'oggetto corrente */
XrmDatabase Database; /* database della pagina dove andranno settate le
                         risorse modificate */
Widget WdgSel; /* Widget in selezione nella drawing area */
Widget *RowCol; /* Row Column contenente tutte le righe delle risorse
                    appartenenti alla categoria ad esso associata */
{
static Boolean Modificata; /* utilizzato per rendere noto che e'
			      stata modificata la form associata ad un
                              oggetto icon reg e quindi prendere le misure
			      necessarie (Es: reset dei nomi delle variabili
                              associate alle porte) */
static Boolean Modificata_opt=False; /* utilizzato per rendere noto che e'
                              stato modificato  il tipo di porta e che quindi 
				e' necessario sbiancare il nome della porta */


int jj,NumeroForm,kk,NumPorte,Tipo,ValoreRitorno,k,Numero,new_valore;
char *ValoreStringa,*Confronto,*Buffer,*Appoggio,*Lista=NULL;
XColor PixAppo;
Widget VoceSel,Pane,*OptPane,*ListaPorte;
XmString NomeVoceSel,NomeVoce;
XFontStruct *FontInfo;
OlFormObject PuntForm;
int old_option;
float blink_rate;
char colore[300];
Boolean trasparent;
int trasparent_int;

/*  Inizializza la variabile che contiene il numero degli errori
	e che viene ritornata dalla funzione  */
ValoreRitorno = 0;

/*  Controlla il tipo della risorsa della confinfo per 
  individuare il tipo di dato da settare   */
if (Confinfo.confinfo_type > LOCKED_PAG) 
  Tipo = Confinfo.confinfo_type-LOCKED_PAG;
else
  Tipo = Confinfo.confinfo_type;
switch (Tipo)
  {
  case XlRAnimatedColor:
    /*  Legge il valore della risorsa   */
    ValoreStringa = (char *)XmTextFieldGetString (RowCol[2]);
    RtRecord(ValoreStringa);
if (strlen(ValoreStringa) > 1)
{
    sscanf(ValoreStringa,"%s%f%d",colore,&blink_rate,&trasparent_int);
}
else
{
    colore[0]=0;
    blink_rate=0.0;
    trasparent_int=0;
}
trasparent=(Boolean)trasparent_int;

// printf("EseguiControlliInput ValoreString=[%s] ",ValoreStringa );
// printf(" colore=[%s]", colore );
// printf(" blink_rate=[%f]", blink_rate );
// printf(" trasparent_int=[%d]\n",trasparent_int );
// printf(" trasparent=[%d]\n",trasparent );

    if (!CvtStrToPixel (RowCol[2],colore,(Pixel *)&PixAppo))
    {
      SettaErrore(RowCol[1]); /* Trasforma l'indicazione di risorsa
                                 modificata in indicazione di errore
				 cie' X sulla riga attuale */
      ValoreRitorno++;
    }
    else
    {
      /*  Setta la risorsa nel database  */
      XlSetResourceByWidget (&Database,WdgSel,
         Confinfo.resource_name,ValoreStringa);
    }
    XtFree (ValoreStringa);
  break;
  /*************
      *****************
	Informazione relativa ad un colore
      *****************
  *************/
  case XlRColor:
    /*  Legge il valore della risorsa   */
    ValoreStringa = (char *)XmTextFieldGetString (RowCol[2]);
    RtRecord(ValoreStringa);
    if (!CvtStrToPixel (RowCol[2],ValoreStringa,(Pixel *)&PixAppo))
      {
      SettaErrore(RowCol[1]); /* Trasforma l'indicazione di risorsa
                                 modificata in indicazione di errore
				 cie' X sulla riga attuale */
      ValoreRitorno++;
      }
    else
      {
      /*  Setta la risorsa nel database  */
      XlSetResourceByWidget (&Database,WdgSel,
         Confinfo.resource_name,ValoreStringa);
      }
    XtFree (ValoreStringa);
  break;
  /*************
      *****************
	Informazione relativa ad un'option menu
      *****************
  *************/
  case XlROption:
    /*  Legge l'indice della voce selezionata  */
    get_something (RowCol[2], XmNmenuHistory, (void*) &VoceSel);
    get_something (VoceSel, XmNlabelString, (void*) &NomeVoceSel);
    get_something (RowCol[2], XmNsubMenuId, (void*) &Pane);
    get_something (Pane, XmNnumChildren, (void*) &Numero);
    get_something (Pane, XmNchildren, (void*) &OptPane);
    for (k=0;k<Numero;k++)
      {
      get_something (OptPane[k], XmNlabelString, (void*) &NomeVoce);
      if (XmStringCompare (NomeVoce, NomeVoceSel))
        {
        ValoreStringa = (char *)XtCalloc (4,sizeof(char));
        sprintf (ValoreStringa,"%d",k);
        /*  Setta la risorsa nel database  */
        XlSetResourceByWidget (&Database,WdgSel,
        Confinfo.resource_name,ValoreStringa);
        XtFree (ValoreStringa); 
	/*
		se e' stato modificato il tipo di porta viene sbiancato
		il campo nome della porta
	*/
	if(XlIsPort(WdgSel) && strcmp(Confinfo.resource_name,XlNtipoPort)==0)
		{
    		get_something (WdgSel, Confinfo.resource_name, (void*) &old_option);
		if(old_option!=k)
			{
			Modificata_opt = True;
			}
		else
			Modificata_opt = False;
		}
/* MAURIC */
        XmStringFree(NomeVoce);
        }
      }
  break;
  /*************
      *****************
	Informazione relativa ad una dimensione
      *****************
  *************/
  case XlRDimension:
    /*  Controlla se l'oggetto selezionato e' un composite  */
    if (EComposite (WdgSel))
      {
      if ( strcmp (Confinfo.resource_name,XmNwidth) == 0)
        {
        /*  Legge il valore della risorsa   */
        ValoreStringa = (char *)XmTextFieldGetString (RowCol[2]);
        RtRecord(ValoreStringa);
        if (!NumIntVerifica (ValoreStringa))
          {
          SettaErrore(RowCol[1]);
          ValoreRitorno++;
          }
        else
          {
          new_valore = atoi(ValoreStringa);
          /*  Setta la risorsa nel database  */
          XlSetResourceByWidget (&Database,WdgSel,
                                    Confinfo.resource_name,ValoreStringa);
          /*  Ridimensiona la width e la x di tutti i figli
                      del composite  */
          XlSetResCompositeWidth (WdgSel, new_valore, Database);
          }
        }
      else
        {
        if ( strcmp (Confinfo.resource_name,XmNheight) == 0)
          {
          /*  Legge il valore della risorsa  */ 
          ValoreStringa = (char *)XmTextFieldGetString (RowCol[2]);
          RtRecord(ValoreStringa);
          if (!NumIntVerifica (ValoreStringa))
            {
            SettaErrore(RowCol[1]);
            ValoreRitorno++;
            }
          else
            {
            new_valore = atoi(ValoreStringa);
            /*  Setta la risorsa nel database  */
            XlSetResourceByWidget (&Database,WdgSel,
                                      Confinfo.resource_name,ValoreStringa);
            /*  Ridimensiona la height e la y di tutti i figli
                 del composite  */
            XlSetResCompositeHeight (WdgSel, new_valore, Database);
            }
          }
        else
          {
          /*  Legge il valore della risorsa   */
          ValoreStringa = (char *)XmTextFieldGetString (RowCol[2]);
          RtRecord(ValoreStringa);
          if (!NumIntVerifica (ValoreStringa))
            {
            SettaErrore(RowCol[1]);
            ValoreRitorno++;
            }
          else
            {
            /*  Setta la risorsa nel database  */
            XlSetResourceByWidget (&Database,WdgSel,
                       Confinfo.resource_name,ValoreStringa);
            }
          }
        }
      }
    else
      {
      /*  Legge il valore della risorsa   */
      ValoreStringa = (char *)XmTextFieldGetString (RowCol[2]);
      RtRecord(ValoreStringa);
      if (!NumIntVerifica (ValoreStringa))
        {
        SettaErrore(RowCol[1]);
        ValoreRitorno++;
        }
      else
        {
        /*  Setta la risorsa nel database  */
        XlSetResourceByWidget (&Database,WdgSel,
                      Confinfo.resource_name,ValoreStringa);
        }
      }
    XtFree (ValoreStringa);
  break;
  /*************
      *****************
	Informazione relativa ad una posizione
      *****************
  *************/
  case XlRPosition:
    /*  Legge il valore della risorsa   */
    ValoreStringa = (char *)XmTextFieldGetString (RowCol[2]);
    RtRecord(ValoreStringa);
    if (!NumIntVerifica (ValoreStringa))
      {
      SettaErrore(RowCol[1]);
      ValoreRitorno++;
      }
    else
      {
      /*  Setta la risorsa nel database  */
      XlSetResourceByWidget (&Database,WdgSel,
                     Confinfo.resource_name,ValoreStringa);
      }
    XtFree (ValoreStringa);
  break;
  /*************
      *****************
	Informazione relativa ad un valore float
      *****************
  *************/
  case XlRFloat:
    /*  Legge il valore della risorsa  */
    ValoreStringa = (char *)XmTextFieldGetString (RowCol[2]);
    RtRecord(ValoreStringa);
    if (!NumFloVerifica (ValoreStringa))
      {
      SettaErrore(RowCol[1]);
      ValoreRitorno++;
      }
    else
      {
      /*  Setta la risorsa nel database  */
      XlSetResourceByWidget (&Database,WdgSel,
                       Confinfo.resource_name,ValoreStringa);
      }
    XtFree (ValoreStringa);
  break;
  /*************
      *****************
	Informazione relativa ad un valore int
      *****************
  *************/
  case XlRInt:
    /*  Legge il valore della risorsa  */
    ValoreStringa = (char *)XmTextFieldGetString (RowCol[2]);
    RtRecord(ValoreStringa);
    if (!NumIntVerifica (ValoreStringa))
      {
      SettaErrore(RowCol[1]);
      ValoreRitorno++;
      }
    else
      {
      /*  Setta la risorsa nel database  */
      XlSetResourceByWidget (&Database,WdgSel,
                          Confinfo.resource_name,ValoreStringa);
      }
    XtFree (ValoreStringa);
  break;
  /*************
      *****************
	Informazione relativa ad un font
      *****************
  *************/
  case XlRFont:
    /*  Legge il valore della risorsa  */
    ValoreStringa = (char *)XmTextFieldGetString (RowCol[2]);
    RtRecord(ValoreStringa);
    if ( (FontInfo = XLoadQueryFont (XtDisplay(WdgSel),ValoreStringa))==NULL)
      {
      SettaErrore(RowCol[1]);
      ValoreRitorno++;
      }
    else
      {
      /*  Setta la risorsa nel database  */
      XlSetResourceByWidget (&Database,WdgSel,
				Confinfo.resource_name,ValoreStringa);
      }
    XtFree (ValoreStringa);
  break;
  /*************
      *****************
	Informazione relativa ad un file di form
      *****************
  *************/
  case XlRForm:
    /*  Legge il valore della risorsa  */
    ValoreStringa = (char *)XmTextFieldGetString (RowCol[2]);
    RtRecord(ValoreStringa);
    /*  Controllo se il nome del file e' uguale al precedente  */
    get_something (WdgSel, XlNmodulName, (void*) &Confronto);
    if (strcmp (Confronto,ValoreStringa) != 0)
      {
      set_something_val (WdgSel, XlNmodulName, (XtArgVal) ValoreStringa);
      Modificata = True; /* notifica la modifica della form associata */
      }
    else Modificata = False;
    /*  Setta la risorsa nel database  */
    XlSetResourceByWidget (&Database,WdgSel,
                 Confinfo.resource_name,ValoreStringa);
    XtFree (ValoreStringa);
  break;
  /*************
      *****************
	Informazione relativa alla stringa di definizione delle form
        (stringone)
      *****************
  *************/
  case XlRInputValue:
    if (Modificata == True)
/*
 E' stata modificata la form associata all'oggetto
*/
      {
      /*  Ricavo il puntatore alla form  */
      PuntForm = ResGetForm (WdgSel);
      if (PuntForm != NULL)
        {
        /*  Ricavo il numero delle form presenti */
        NumeroForm = OlGetNumForms (PuntForm);
        for (jj=0;jj<NumeroForm;jj++)
          {
          /*  Prendo le tags della form specificata  */
          Buffer = OlWriteStrInp (PuntForm,&Appoggio,jj);
          if (Buffer != NULL)
            {
            if (Lista == NULL)
              {
              Lista = XtCalloc (strlen(Buffer)+1,sizeof(char));
              strcpy (Lista,Buffer);
              }
            else
              {
              Lista = XtRealloc (Lista,
			(strlen(Lista)+strlen(Buffer)+2)*sizeof(char));
              strcat (Lista," ");
              strcat (Lista,Buffer);
              }
            XtFree (Buffer); 
            }
          }
        XmTextFieldSetString (RowCol[2],Lista);
        XlSetResourceByWidget (&Database,WdgSel,Confinfo.resource_name,Lista);
        XtFree (Lista);
        } 
      else
        {
        XmTextFieldSetString (RowCol[2],"no value");
        XlSetResourceByWidget (&Database,WdgSel,Confinfo.resource_name,
		"no value");
        }
      /*  
        Prende tutti i figli della IconReg che sono porte
	per azzerarne il nome della tag collegata  in
        quanto e' stato modificato il file della form e
        quindi le associazioni porte-variabili possono essere
        incongruenti. 
      */
      get_something (WdgSel, XmNchildren, (void*) &ListaPorte);
      get_something (WdgSel, XmNnumChildren, (void*) &NumPorte);
      for (kk=0;kk<NumPorte;kk++)
        {
        if ( XlIsPort(ListaPorte[kk]) )
	  XlSetResourceByWidget (&Database,ListaPorte[kk],XlNportName,"--");
        }
      }
    else
      {
      /*  Legge il valore della risorsa  */
      ValoreStringa = (char *)XmTextFieldGetString (RowCol[2]);
      RtRecord(ValoreStringa);
      /*  Setta la risorsa nel database  */
      XlSetResourceByWidget (&Database,WdgSel,
		Confinfo.resource_name,ValoreStringa);
      XtFree (ValoreStringa);
      }
    Modificata = False;
  break;
  /*************
      *****************
	Informazione relativa ad una risorsa generica 
      *****************
  *************/
  default:
    /*  Legge il valore della risorsa  */
    ValoreStringa = (char *)XmTextFieldGetString (RowCol[2]);
    RtRecord(ValoreStringa);
    get_something (WdgSel, Confinfo.resource_name, (void*) &Confronto);
    /*
	e' stato modificato il tipo di porta e viene quindi annullatto
	il campo nome della porta
    */
    if(Modificata_opt && strcmp(Confinfo.resource_name,XlNportName)==0
	&& strcmp(ValoreStringa,"--")!=0)
	{
    	XtFree (ValoreStringa);
	ValoreStringa=XtNewString("--");
        XmTextFieldSetString (RowCol[2],ValoreStringa);
	Modificata_opt = False;
	}
    if ( strcmp (Confronto,ValoreStringa) != 0 )
      /*  Setta la risorsa nel database  */
      XlSetResourceByWidget (&Database,WdgSel,
                 Confinfo.resource_name,ValoreStringa);
    XtFree (ValoreStringa);
  break;
  }
return (ValoreRitorno);
}

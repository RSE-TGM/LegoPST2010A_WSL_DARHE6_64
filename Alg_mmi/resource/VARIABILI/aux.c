/**********************************************************************
*
*       C Source:               aux.c
*       Subsystem:              1
*       Description:
*       %created_by:    lopez %
*       %date_created:  Fri Jan 17 14:29:10 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: aux.c-2 %  (%full_filespec: aux.c-2:csrc:1 %)";
#endif
/*
        Inizio sezione per SCCS
*/
/*
   modulo aux.c
   tipo 
   release 5.2
   data 2/6/96
   reserved @(#)aux.c	5.2
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)aux.c	5.2\t2/6/96";
/*
        Fine sezione per SCCS
*/

/*
			FILE:   aux.c

		Routine esterne di appoggio
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Xm/Xm.h>
#include <Xl/Xl.h>
#include <Xl/XlGraficoP.h>
#include "sim_param.h"
#include <Ol/OlDatabaseTopologia.h>
#include "VarEdit.h"
#include "ImpPert.h"

extern SELEZIONE_UNI_MIS SelUniMis[];

/********************************************************  
	Routine per la ricerca all'interno di una lista di compound string
	una sottocompound string:

int RicercaXmString
	(
	Lista			--> Lista di compound string;
	Stringa			--> Compound string da ricercare all'interno 
					della lista;
	NumeroItem		--> Numero degli elementi della lista;
	Direzione		--> Direzione della ricerca;
	PosizionePartenza  	--> Posizione di partenza della ricerca;
	)

	Valore di ritorno  	--> Posizione dell'elemento della lista 
					nel quale e' stata trovata la Stringa,
					viene ritornato 0 se non viene trovata
					la Stringa nella lista;
********************************************************/
int RicercaXmString (Lista,Stringa,NumeroItem,Direzione,PosizionePartenza)
XmString *Lista,Stringa;
int NumeroItem,Direzione,PosizionePartenza;
{
int i;
Boolean Trovata;

if (Direzione == SU)
	{
	for (i=(PosizionePartenza-2);i>-1;i--)
		{
		Trovata = XmStringHasSubstring (Lista[i],Stringa);
		if (Trovata) return (i+1);
		}
	}

if (Direzione == GIU)
	{
	for (i=(PosizionePartenza);i<NumeroItem;i++)
		{
		Trovata = XmStringHasSubstring (Lista[i],Stringa);
		if (Trovata) return (i+1);
		}
	}
return (0);
}

/*******************************************************
        Routine che visualizza una messageBox comunicando un messaggio di
        errore:

void VisualizzaMessageBox
        (
        TipoVis                 --> Parametro per la gestione del tasto di OK
                                        della messageBox;
        Padre                   --> ID dell'oggetto che chiama la messageBox;
        Messaggio               --> Stringa da visualizzare come messaggio
                                        della messageBox;
        )

        Valore di ritorno       --> Nessun valore di ritorno;
*******************************************************/
void VisualizzaMessageBox (int TipoVis,Widget Padre,char *Messaggio,Widget OggSel)
{
extern Widget Message,create_Message();

XmString XmMessaggio;
int no_grab;

XmMessaggio = XmStringCreateSimple (Messaggio);
Message = create_Message (TipoVis,Padre,OggSel);
set_something (Message,XmNmessageString, XmMessaggio);
set_something (Message,XmNdialogType, XmDIALOG_ERROR);
UxPopupInterface (Message, no_grab);
XmStringFree (XmMessaggio);
}

/******************************************************
	Routine che carica la lista di char * nella
	lista di XmString:

void CaricaLista
	(
	ListaWid		--> ID dell'oggetto della lista dove devono 
					essere inseriti gli item;
	ListaItem		--> Lista degli item che devono 
					essere visualizzati nell'oggetto
					lista; in testa alla lista e'
					memorizzato un int indicante il 
					numero di elementi della lista;
	Lunghezza		--> Numero di caratteri per ogni componente
					della ListaItem;
	Tipo 			--> Individuazione del tipo di lista;
	)

	Valore di ritorno	--> Nessun valore di ritorno; 
******************************************************/
void CaricaLista (ListaWid,ListaItem,Lunghezza,Tipo)
Widget ListaWid;
char *ListaItem;
int Lunghezza;
int Tipo;
{
XmString XmAppoggio;
char *Appoggio;
int i,NumeroElementi;

Appoggio = ListaItem;
memcpy (&NumeroElementi,Appoggio,sizeof(int));

Appoggio += sizeof(int);
for (i=0;i<NumeroElementi;i++)
	{
	XmAppoggio = XmStringCreateSimple (Appoggio);
	XmListAddItemUnselected (ListaWid, XmAppoggio, 0);
	XmStringFree (XmAppoggio);
	Appoggio += Lunghezza;
	}
}

/*****************************************************
	Routine che compone lo stringone contenente la definizione
	totale del nome della variabile di unput allo Widget, del nome
	del blocco e del nome modello e della descrizione della elaborazione con
	tutti i relativi parametri:

char *WriteInpVariableString 
	(
	DataB			--> Database della topologia del simulatore;
	Modello			--> Valore in input del nome del modello;
	Blocco			--> Valore in input del nome del blocco;
	Variabile		--> Valore in input del nome della variabile;
	Option			--> ID dell'Opt menu del tipo di elaborazione;
	)

	Valore di ritorno	--> Ritorna il puntatore ad una stringa 
					allocata contenente l'intera 
					definizione della risorsa della
					variabile;
*******************************************************/
char *WriteInpVariableString (DataB,Modello,Blocco,Variabile,Option)
OlDatabaseTopologiaObject DataB;
char *Modello,*Blocco,*Variabile;
Widget Option;
{
char *Appoggio,AppoggioBlocco[200],AppoggioVariabile[200],Elab[5];
char Appo[200];
int i,Lunghezza,Numero;
Widget VoceSel,Pane,*OptPane;
XmString NomeVoceSel,NomeVoce;
Boolean uguali;

i=0;
while (Variabile[i] != ' ')
	{
	AppoggioVariabile [i] = Variabile [i];
	i++;
	}
AppoggioVariabile[i] = '\0';

if ( strncmp (Blocco,"ALL",3)==0 )
  strcpy (Appo,OlGetBlockName (DataB,Modello,AppoggioVariabile));
else
  strcpy (Appo,Blocco);

i=0;
while (Appo[i] != ' ')
	{
	AppoggioBlocco [i] = Appo [i];
	i++;
	}
AppoggioBlocco[i] = '\0';

get_something (Option, XmNmenuHistory, &VoceSel);
get_something (VoceSel, XmNlabelString, &NomeVoceSel);
get_something (Option, XmNsubMenuId, &Pane);
get_something (Pane, XmNnumChildren, &Numero);
get_something (Pane, XmNchildren, &OptPane);
for (i=0;i<Numero;i++)
	{
	get_something (OptPane[i], XmNlabelString, &NomeVoce);
	uguali = XmStringCompare (NomeVoce,NomeVoceSel);
	if ( (uguali==True) && (i==0) )
		strcpy (Elab,"NOP");
	if ( (uguali==True) && (i==1) )
		strcpy (Elab,"NOT");
	}

Lunghezza = strlen (AppoggioVariabile) + 1;
Lunghezza += strlen (AppoggioBlocco) + 1;
Lunghezza += strlen (Modello) + 1;
Lunghezza += strlen (Elab) +1;

Appoggio = (char *)XtCalloc (Lunghezza,sizeof(char));

strcpy (Appoggio,AppoggioVariabile);
strcat (Appoggio," ");
strcat (Appoggio,AppoggioBlocco);
strcat (Appoggio," ");
strcat (Appoggio,Modello);
strcat (Appoggio," ");
strcat (Appoggio,Elab);

return (Appoggio);
}

/*****************************************************
	Routine che compone lo stringone contenente la definizione
	totale del nome della variabile di output allo Widget, del nome
	del blocco e del nome modello e della descrizione della
	perturbazione con tutti i relativi parametri:

char *WriteOutVariableString 
	(
	DataB			--> Database della topologia del simulatore;
	Modello			--> Valore in input del nome del modello;
	Blocco			--> Valore in input del nome del blocco;
	Variabile		--> Valore in input del nome della variabile;
	Perturba		--> Valore in input della descrizione
					della elaborazione operata sulla
					variabile;
	)

	Valore di ritorno	--> Ritorna il puntatore ad una stringa 
					allocata contenente l'intera 
					definizione della risorsa della
					variabile;
*******************************************************/
char *WriteOutVariableString (DataB,Modello,Blocco,Variabile,Perturba)
OlDatabaseTopologiaObject DataB;
char *Modello,*Blocco,*Variabile,*Perturba;
{
char *Appoggio,AppoggioBlocco[200],AppoggioVariabile[200],AppoggioPerturba[200];
char Appo[200];
char Pezzo[30];
int i,Lunghezza,parametri,LungPerturba;

strcpy (AppoggioPerturba,"");

i=0;
while (Variabile[i] != ' ')
	{
	AppoggioVariabile [i] = Variabile [i];
	i++;
	}
AppoggioVariabile[i] = '\0';

if ( strncmp (Blocco,"ALL",3)==0 )
  strcpy (Appo,OlGetBlockName (DataB,Modello,AppoggioVariabile));
else
  strcpy (Appo,Blocco);

i=0;
while (Appo[i] != ' ')
	{
	AppoggioBlocco [i] = Appo [i];
	i++;
	}
AppoggioBlocco[i] = '\0';

parametri = 0;
Appoggio = Perturba;
while ( ((sscanf (Appoggio,"%s",Pezzo)) > 0) && (parametri<3))
  {
  Appoggio += strlen(Pezzo)+1;
  strcat (AppoggioPerturba,Pezzo);
  strcat (AppoggioPerturba," ");
  parametri++;
  }

while (parametri < 3)
  {
  strcat (AppoggioPerturba,"0.0");
  strcat (AppoggioPerturba," ");
  parametri++;
  }

LungPerturba = strlen (AppoggioPerturba)-1;
AppoggioPerturba[LungPerturba] = '\0';
  
/* Calcolo la lunghezza della stringa totale  */
Lunghezza = strlen (AppoggioVariabile) + 1;
Lunghezza += strlen (AppoggioBlocco) + 1;
Lunghezza += strlen (Modello) + 1;
Lunghezza += LungPerturba + 1;

Appoggio = (char *)XtCalloc (Lunghezza,sizeof(char));

strcpy (Appoggio,AppoggioVariabile);
strcat (Appoggio," ");
strcat (Appoggio,AppoggioBlocco);
strcat (Appoggio," ");
strcat (Appoggio,Modello);
strcat (Appoggio," ");
strcat (Appoggio,AppoggioPerturba);

return (Appoggio);
}

/************************************************************
	Routine che appende in coda alla stringa della variabile
	l'unita' di misura selezionata con i parametri necessari:

char *WriteUniMisura
	(
	Input			-->  Stringa della definizionde della
					variabile;
	OptMenu			-->  Option menu delle unita' di
					misura;
	)

	Valore di ritorno	--> La Stringa passata in input con appesa
					in coda la definizione della unita'
					di misura;

*************************************************************/
char *WriteUniMisura (char *Input,Widget OptMenu)
{
Widget Settato;
XmString Etichetta;
char *Conf,Appoggio[50],*Appo;
int i,j;
Boolean Fatto;

/*  Leggo dall'optione menu delle unita di misura la selezione attiva  */
get_something (OptMenu, XmNmenuHistory, &Settato);
get_something (Settato, XmNlabelString, &Etichetta);
Conf = (char *)extract_string (Etichetta);

i=0;
Fatto=False;
#ifndef SCADA_MMI    /* nel caso SCADA_MMI non si considerano le
                        unita' di misura */
while ( (SelUniMis[i].type != '!') && (!Fatto) )
  {
  j=0;
  if ( SelUniMis[i].type == Input[0] )
    {
    Fatto = True;
    while ( strncmp ( SelUniMis[i].codm[j],Conf,strlen(Conf) ) != 0 )
	j++;
    strcpy (Appoggio,SelUniMis[i].A[j]);
    strcat (Appoggio," ");
    strcat (Appoggio,SelUniMis[i].B[j]);
    strcat (Appoggio," ");
    strcat (Appoggio,SelUniMis[i].codm[j]);
    }
  i++;
  }
#endif
if (!Fatto)
  {
  strcpy (Appoggio,SelUniMis[14].A[0]);
  strcat (Appoggio," ");
  strcat (Appoggio,SelUniMis[14].B[0]);
  strcat (Appoggio," ");
  strcat (Appoggio,SelUniMis[14].codm[0]);
  }

Appo = (char *)XtCalloc ((strlen(Input)+strlen(Appoggio)+2),sizeof(char));

strcpy (Appo,Input);
strcat (Appo," ");
strcat (Appo,Appoggio);
XtFree (Conf);
XtFree (Input);

printf ("Ritorno Stringa: [%s]\n",Appo);
return (Appo);
}

/***********************************************************
	Routine che controlla la costante passata come parametro
	e restituisce una XmString contenente la descrizione 
	per quel tipo di variabile:

XmString ControllaTipoVar
	(
	Tipo			--> Tipo di variabile in input;
	Bottone			--> pushButton del perturbazioni;
	)

	Valore di ritorno	--> Viene ritornata una compound string
					nella quale e' contenuta la
					descrizione del tipo di variabile
					in input; Viene utilizzata
                                        come titolo del variable editor

*************************************************************/
XmString ControllaTipoVar (int Tipo,Widget Bottone,Widget OpMenu)
{
XmString XmStringa;
char Appo[100];
Boolean ValOpt,ValBot;

switch (Tipo)
  {
  case XlRVarDA:
    strcpy ( Appo , "Digital Input Variable" );
    ValBot = False;
    ValOpt = True;
  break;
  case XlRVarDO:
    strcpy ( Appo , "Digital Output Variable" );
    ValBot = True;
    ValOpt = False;
  break;
  case XlRVarDX:
    strcpy ( Appo , "Digital Variable" );
    ValBot = False;
    ValOpt = False;
  break;
  case XlRVarAA:
    strcpy ( Appo , "Analog Input Variable" );
    ValBot = False;
    ValOpt = False;
  break;
  case XlRVarAO:
    strcpy ( Appo , "Analog Output Variable" );
    ValBot = True;
    ValOpt = False;
  break;
  case XlRVarAX:
    strcpy ( Appo , "Analog Variable" );
    ValBot = False;
    ValOpt = False;
  break;
  case XlRVarXA:
    strcpy ( Appo , "Input Variable" );
    ValBot = False;
    ValOpt = False;
  break;
  case XlRVarXO:
    strcpy ( Appo , "Output Variable" );
    ValBot = True;
    ValOpt = False;
  break;
  case XlRVarXX:
    strcpy ( Appo , "Generic Variable" );
    ValBot = False;
    ValOpt = False;
  break;
  case XlRVarAing:
    strcpy ( Appo , "Output Variable");
    ValBot = False;
    ValOpt = False;
  break;
  case XlRVarPlot:
    strcpy ( Appo , "Generic Variable");
    ValBot = False;
    ValOpt = False;
  break;
  default:
    strcpy ( Appo , "Unknown Variable Type" );
    ValBot = False;
    ValOpt = False;
  break;
  }

XmStringa = XmStringCreateSimple (Appo);
set_something (Bottone,XmNsensitive,ValBot);
set_something (OpMenu,XmNsensitive,ValOpt);

/*
XtFree (Appo);
*/

return (XmStringa);
}

/*********************************************************
	Routine che filtra la lista dei blocchi passata come parametro
	secondo la loro appartenenza al Componente interessato:

char *BlocksFilterFromComponent
	(
	ElencoBlocchi		--> Lista dei blocchi;
	ElencoModuli		--> ElencoModuliValidi;
	)

	Valore di ritorno	--> Viene ritornata la lista dei blocchi
					modificata secondo il componente;

**********************************************************/
char *BlocksFilterFromComponent (char *ElencoBlocchi,char *ElencoModuli)
{
int i,j,valido;
int NumValidi,NElencoBlocchi,NElencoModuli;
char *AppFilter,NomeModulo[5],*AppBlocco;
char *Appoggio,*ListaValida,*ListaAppo,*ListaPronta;
char *AppBlocchi,*AppModuli;

AppBlocchi = ElencoBlocchi;
AppModuli = ElencoModuli;

ListaValida = NULL;

memcpy (&NElencoBlocchi, ElencoBlocchi, sizeof(int));
memcpy (&NElencoModuli, ElencoModuli, sizeof(int));

ElencoBlocchi += sizeof(int);
ElencoModuli += sizeof(int);

AppFilter = ElencoModuli;
NumValidi = 1;

for (i=0;i<NElencoBlocchi;i++)
	{
	valido = 1;
	j=0;
	AppBlocco = ElencoBlocchi;
	AppBlocco += 32;
	strncpy (NomeModulo,AppBlocco,4);
	while ( (j<NElencoModuli) && (valido != 0) )
		{
		valido = strncmp (NomeModulo,AppFilter,4);
		if (valido == 0)
			{
			ListaValida = XtRealloc (ListaValida,(NumValidi*
					MAX_LUN_NOME_BLOCCO)*sizeof(char));
			ListaAppo = ListaValida;
			ListaAppo += (NumValidi-1)*MAX_LUN_NOME_BLOCCO;
			strcpy (ListaAppo,ElencoBlocchi);
			NumValidi++;
			}
		AppFilter += 5;
		j++;
		}
	ElencoBlocchi += MAX_LUN_NOME_BLOCCO;
	AppFilter = ElencoModuli;
	}

NumValidi--;
Appoggio = ListaValida;
ListaPronta = XtCalloc ( (sizeof(int)+(NumValidi*MAX_LUN_NOME_BLOCCO)),
							sizeof (char));
ListaAppo = ListaPronta;
memcpy (ListaAppo, &NumValidi, sizeof(int));
ListaAppo += sizeof(int);
for (i=0;i<NumValidi;i++)
	{
	strncpy (ListaAppo, ListaValida, strlen(ListaValida));
	ListaAppo += MAX_LUN_NOME_BLOCCO;
	ListaValida += MAX_LUN_NOME_BLOCCO;
	}
if(Appoggio)
	XtFree (Appoggio);
XtFree (AppBlocchi);
return (ListaPronta);
}

/**********************************************************
	Routine che filtra la lista passata come primo parametro con 
	la lista passata come secondo parametro:

char *FilterList
	(
	SourceList		--> Lista Sorgente da filtrare;
	Filter			--> Lista filtro;
	)

	Valore di ritorno	--> Viene ritornata la lista sorgente 
					modificata secondo la lista
					filtro;

***********************************************************/
char *FilterList (char *SourceList,char *Filter)
{
int i,j,valido;
int NumValidi,NSourceList,NFilter;
char *AppFilter,*Appoggio;
char *AppoggioSource,*ListaValida,*ListaAppo,*ListaPronta;

AppoggioSource = SourceList;
ListaValida = NULL;
memcpy (&NSourceList, SourceList, sizeof(int));
memcpy (&NFilter, Filter, sizeof(int));

SourceList += sizeof(int);
Filter += sizeof(int);

AppFilter = Filter;
NumValidi = 1;

for (i=0;i<NSourceList;i++)
	{
	valido = 1;
	j=0;
	while ( (j<NFilter) && (valido != 0) )
		{
		valido = strncmp (SourceList,AppFilter,4);
		if (valido == 0)
			{
			ListaValida = XtRealloc (ListaValida,(NumValidi*5)*
							sizeof(char));
			ListaAppo = ListaValida;
			ListaAppo += (NumValidi-1)*5;
			strncpy (ListaAppo,SourceList,4);
			NumValidi++;
			}
		AppFilter += 5;
		j++;
		}
	SourceList += 5;
	AppFilter = Filter;
	}

NumValidi--;
Appoggio = ListaValida;
ListaPronta = XtCalloc ( (sizeof(int)+(NumValidi*5)), sizeof (char));
ListaAppo = ListaPronta;
memcpy (ListaAppo, &NumValidi, sizeof(int));
ListaAppo += sizeof(int);
for (i=0;i<NumValidi;i++)
	{
	strncpy (ListaAppo, ListaValida, 4);
	ListaAppo += 5;
	ListaValida += 5;
	}
XtFree (Appoggio);
XtFree (AppoggioSource);
return (ListaPronta);
}

/**********************************************************
	Routine che nel caso di un oggetto della classe "Grafico"
	e di tipo ad una sola variabile, aggiorna per la parte runtime
	il puntatore alla nuova variabile in caso di nuova selezione:

void RisettaVariabile
	(
	Variab			--> Stringadella variabile da settare;
	OggSel			--> ID dell'oggetto selezionato da cui
					ricavare informazioni aggiuntive;
	) 

	Valore di ritorno	--> Nessun valore di ritorno; 

***********************************************************/
void RisettaVariabile(char *Variab,Widget OggSel)
{
XlGraficoWidget Wdg = (XlGraficoWidget)OggSel;
char NomeV[MAX_LUN_NOME_VAR],*Descrizione;
char P1[20],P2[20],P3[20],P4[20],DescrUM[MAX_LUN_UNIMIS];
float ParA,ParB;
char SSParA[20],SSParB[20];
int i,num;

/*  Setto il flag per la rilettura della variabile  */
Wdg->grafico.primo_refresh = True;

/*  Setto la nuova stringa nella risorsa dell'oggetto  */
XtFree (Wdg->grafico.nome_var[0]);
Wdg->grafico.nome_var[0] = XtNewString(Variab);

/*  Ricavo dalla stringa di descrizione della variabile i parametri
	relativi alla definizione della unita' di misura  */
num = sscanf (Variab,"%s %s %s %s %s %s %s",NomeV,P2,P3,P4,SSParA,SSParB,DescrUM);
if (num==7)
  {
  ParA = atof (SSParA);
  ParB = atof (SSParB);
  Wdg->grafico.input[0].unimis.a = ParA;
  Wdg->grafico.input[0].unimis.b = ParB;
  strcpy (Wdg->grafico.input[0].unimis.descr,DescrUM);
  Descrizione = OlGetNameVar (Wdg,NomeV,0);
  XtFree (Wdg->grafico.descr_var[0]);
  Wdg->grafico.descr_var[0] = XtNewString (Descrizione);
  XtFree (Descrizione);
  }

/*  Richiamo la routine per l'allineamento con la nuova variabile  */
OlChangePointInPage (Wdg, &Wdg->grafico.input[0], NomeV, 
			xlGraficoClassRec.xlmanager_class.database_topologia,
			xlGraficoClassRec.xlmanager_class.database);
}

/**********************************************************************
*
*       C Header:               Xl.h
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Wed May 16 17:29:00 2001 %
*
**********************************************************************/
/*
   modulo Xl.h
   tipo 
   release 5.2
   data 12/4/95
   reserved @(#)Xl.h	5.2
*/
/*
 Xl.h
 files di definizioni pubbliche per le estensioni per legommi al
 widget set dell'Xtoolkit
*/
#ifndef _Xl_h
#define _Xl_h
#include <Ol/OlCompiler.h>
#include <Ol/OlDatabaseTopologia.h>
#include <Ol/OlDatabasePunti.h>
#include <Xl/XlPrint.h>
#include <Rt/RtMemory.h>
/*
 Definizione delle confinfo cioe' delle risorse utilizzate in fase
 di configurazione e di compilazione per l'oggetto di una determinata classe

 vengono inoltre definite le informazioni relative alle
 attributi da leggere e scrivere su file binario:
  - in lettura:
	a)viene letto da file un numero di byte pari attribute_size
	b)per le risorse per le quali e' specificato il nome
          di risorsa viene chiamata la SetValues 
        c)se non e' specificato il nome della risorsa 
          il valore letto viene inserito all'offset specificato 
          da attribute_offset
  - in scrittura
	viene prelevato l'attributo in base al valore di offset
        specificato e scritto direttamente su file
*/
typedef struct _XlConfInfo {
	String resource_name;  /* nome della risorsa */
	String resource_class; /* classe della risorsa */
	String confinfo_name;  /* descrizione per esteso della risorsa */
	int    confinfo_type;  /* tipo usato nella rappresentazione da
				  parte del configuratore delle risorse */
	int    db_type;        /* indica il tipo di risorsa XlTipoVarXX
				  dal punto di vista del database dei punti:
				  ex: XlRVarDO, ecc...			*/
	String  enum_options;   /* stringa contenente (separate da virgole)
				   le possibili opzioni per la risorsa
                                   ( o NULL se confinfo_type non e'
                                   del tipo XlROption */
	int    confinfo_group;  /* tipo di gruppo cui la risorsa appartiene
                                   viene utilizzato per la visualizzazione
                                   nel configuratore delle risorse attuata
                                   per gruppi separati */
	Cardinal compiled_offset; /* offset della variabile compilata */
	Cardinal compiled_size;   /* dimensioni della variabile compilata 
                                     e' una informazione utilizzata in 
				     lettura/scrittura su file binario */
	} XlConfInfo, *XlConfInfoList; 

/*
 tipo utilizzato per le liste degli oggetti figli negli oggetti
 della classe XlComposite e derivati
*/
#define _LUN_NAME_CLASS  50 /* lunghezza di nome + classe */
#define L_NOME_OGGETTI   20
typedef struct an_obj{
                char nome[L_NOME_OGGETTI];
                WidgetClass classe;
                        } AN_OBJ;
#define XlRStringa "Stringa"

/*  Define per le risorse che devono essere locked  */
#define LOCKED_PAG	2000
#define LOCKED_LIB	3000
#define LOCKED_PAG_LIB	5000

/*
definizioni per trattamento stringhe per gerarchia
 */
#define NUMLIVELLI              6
#define GERARCHIA_KO         "errore"

/*
 Definizioni tipi di attributi gestiti dal configuratore
*/
#define XlRColor        18      /* colore */
#define XlROption       19      /* la risorsa e' un gruppo di opzioni */
#define XlRDimension    20      /* dimensioni (unsigned int)  */
#define XlRFloat        21      /* valore float   */
#define XlRFont         22      /* valore fontlist   */
#define XlRText         23      /* Stringa di testo  puntatore*/
#define XlRPosition     24      /* posizioni   */
#define XlRTipoVarOut   25      /* variabile di uscita dall'MMI verso
                                   il modello*/
#define XlRTipoVarInp   26      /* variabile acquisita dall'MMI */
#define XlRInt        	27      /* valore int   */
#define XlRFile		28      /* Definizione file */
#define XlRComponent    29      /* Definizione Component  */
#define XlRSubSystem    30      /* Definizione SubSystem  */
#define XlRForm         31      /* Definizione nome form associata  */
#define XlRInputValue   32      /* Definizione valori di input definiti
                                   nella form                       */
#define XlRTipoVarReg   33      /* variabile acquisita dall'MMI  negli
				   schemi di regolazione per i DispReg*/
#define XlRTipoVarPort  34      /* variabile acquisita dall'MMI  negli
				   schemi di regolazione per le Porte*/
#define XlRTextAlloc         45      /* Stringa di testo  allocata*/
#define XlRGerarchia	46	/* variabile contenente il valore della
				   situazione allarmi per una certa gerarchia*/
#define XlRAnimatedColor      47      /* Definizione tipo AnimatedColor */

/* definizione tipo AnimatedColor */
#define XtRAnimatedColor "animatedColor"

/* tipi di variabile modellistica 
	penultimo carattere:
              D -> variabile digitale
	      A -> variabile analogica
	ultimo carattere:
	      O -> variabile di attuazione (ingresso per il modello)
	      A -> variabile acquisita (di uscita per il modello)
*/
#define XlRVarDO 1          /* variabile modellistica di input verso
                               il modello */
#define XlRVarDA 2
#define XlRVarAO 4
#define XlRVarAA 8
#define XlRVarXO (XlRVarDO|XlRVarAO) /* variabile di input al modello di tipo
			                qualunque (analogico o digitale) */
#define XlRVarXA (XlRVarDA|XlRVarAA) /* variabile di output per il modello di
			                tipo qualunque */

#define XlRVarDX (XlRVarDO|XlRVarDA) /* variabile digitale di input o output */
#define XlRVarAX (XlRVarAO|XlRVarAA) /* variabile analogica di input o output */
 		/* variabile di qualunque tipo di input o output */
#define XlRVarXX (XlRVarDO|XlRVarAO|XlRVarDA|XlRVarAA)

#define XlRVarAing 20	/* tipo di variabile da utilizzare per righiamare le
			   stazioni di AING (tipicamente di output)         */
#define XlRVarPlot 21	/* tipo di variabile da utilizzare per righiamare le
			   stazioni di PLOT         */

/*
 definizione dei gruppi di risorse per la configurazione
*/
#define XlRGrGeom 1  /* la risorsa si riferisce ad un attributo
				  geometrico: posizione, dimensioni ,
                                  orientazione */
#define XlRGrIo    2 /* la risorsa e' un nome di una variabile */
#define XlRGrColor  3 /* la risorsa e' un colore */
#define XlRGrVCC1   4 /* la risorsa e' la prima variabile cambio colore */
#define XlRGrVCC2   5 /* la risorsa e' la seconda variabile cambio colore */
#define XlRGrVCC3   6 /* la risorsa e' la terza variabile cambio colore */
#define XlRGrVCC4   7 /* la risorsa e' la quarta variabile cambio colore */
/*
 Risorse di uso comune tra oggetti di classi differenti
        XlN....   nome della risorsa
        XlC....   nome della classe
        XlD....   descrizione per la configurazione ( inserita nella
                  struttura confinfo).
        XlO....   descrizioni delle opzioni disponibili (nel caso
                  di risorsa del tipo enumerated option
*/
/*
 risorsa nome (e' presente in tutti gli oggetti in LEGO-MMI e
 viene utilizzata in configurazione)
*/
#define XlNnome "nome"
#define XlCNome "Nome"
#define XlNselected "selected"
#define XlCSelected "Selected"
#define XlNselectedPixel "selectedPixel"
#define XlCSelectedPixel "SelectedPixel"
#define XlNselectable "selectable"
#define XlCSelectable "Selectable"
#define XlNconfig "config"
#define XlCConfig "Config"
#define XlNfattZoom "fattZoom"
#define XlCFattZoom "FattZoom"

#define XlNx0 "x0"
#define XlCX0 "X0"
#define XlDx0 "x (parent rotate=0)"

#define XlNy0 "y0"
#define XlCY0 "Y0"
#define XlDy0 "y (parent rotate=0)"

#define XlNwidth0 "width0"
#define XlCWidth0 "Width0"
#define XlDwidth0 "width (rotate=0)"

#define XlNheight0 "height0"
#define XlCHeight0 "Height0"
#define XlDheight0 "height (rotate=0)"

#define XlNinEdit "inEdit"
#define XlCInEdit "InEdit"

#define XlNwEdit  "wEdit"
#define XlCWEdit  "WEdit"

#define XlNerrore "errore"
#define XlCErrore "Errore"

#define XlNinheritBackground "inheritBackground"
#define XlCInheritBackground "InheritBackground"
#define XlDinheritBackground "Inherit parent background"
#define XlOinheritBackground "No,Yes"

#define XlNchildrenLayout "childrenLayout"
#define XlCChildrenLayout "ChildrenLayout"
#define XlDchildrenLayout "Children layout"
#define XlOchildrenLayout "No,Yes"

#define XlNcolorNorm "colorNorm"
#define XlCColorNorm "ColorNorm"
#define XlDcolorNorm "Color"

#define XlNnormFg "normFg"
#define XlCNormFg "NormFg"
#define XlDnormFg "Normal state foreground"

#define XlNnormBg "normBg"
#define XlCNormBg "NormBg"
#define XlDnormBg "Normal state background"

#define XlNcolorBlink "colorBlink"
#define XlCColorBlink "ColorBlink"
#define XlDcolorBlink "Blinking color"

#define XlDx "x coordinate"
#define XlDy "y coordinate"
#define XlDwidth "width"
#define XlDheight "height"
#define XlDborderWidth "border width"
#define XlDbackground "background"
#define XlDforeground "foreground"
#define XlDborderColor "border color"
#define XlNscalamento "scalamento"
#define XlCScalamento "Scalamento"
#define XlDscalamento "Scalamento della variabile di ingresso"
#define XlNvaloreMinimo "valoreMinimo"
#define XlCValoreMinimo "ValoreMinimo"
#define XlDvaloreMinimo "Fondo scala minimo della variabile di ingresso"
#define XlNvaloreMassimo "valoreMassimo"
#define XlCValoreMassimo "ValoreMassimo"
#define XlDvaloreMassimo "Fondo scala massimo della variabile di ingresso"
#define XlNoffset "offset"
#define XlCOffset "Offset"
#define XlDoffset "Offset della variabile di ingresso"
#define XlNscalamentoErr "scalamentoErr"
#define XlCScalamentoErr "ScalamentoErr"
#define XlDscalamentoErr "Scalamento della variabile di errore"
#define XlNvaloreMinimoErr "valoreMinimoErr"
#define XlCValoreMinimoErr "ValoreMinimoErr"
#define XlDvaloreMinimoErr "Fondo scala minimo della variabile di errore"
#define XlNvaloreMassimoErr "valoreMassimoErr"
#define XlCValoreMassimoErr "ValoreMassimoErr"
#define XlDvaloreMassimoErr "Fondo scala massimo della variabile di errore"
#define XlNoffsetErr "offsetErr"
#define XlCOffsetErr "OffsetErr"
#define XlDoffsetErr "Offset della variabile di errore"
#define XlNnumeroInt "numeroInt"
#define XlCNumeroInt "NumeroInt"
#define XlDnumeroInt "Numero di cifre intere rappresentate"
#define XlNnumeroDec "numeroDec"
#define XlCNumeroDec "NumeroDec"
#define XlDnumeroDec "Numero di cifre decimali rappresentate"
#define XlNnormalFont "normalFont"
#define XlCNormalFont "NormalFont"
#define XlDnormalFont "Font"
#define XlNfontID "fontID"
#define XlCFontID "FontID"
#define XlDfontID "Font ID"
#define XlNfontStruct "fontStruct"
#define XlCFontStruct "FontStruct"
#define XlDfontStruct "Font Struct"
#define XlNlabelText "labelText"
#define XlCLabelText "LabelText"
#define XlDlabelText "Label"

#define XlNcomponent "component"
#define XlCComponent "Component"
#define XlDcomponent "Component"

#define XlNsubsystem "subsystem"
#define XlCSubsystem "Subsystem"
#define XlDsubsystem "Subsystem"

#define XlNcompositeName "compositeName"
#define XlCCompositeName "CompositeName"
#define XlDcompositeName "Name"

#define XlNiconRegName "iconRegName"
#define XlCIconRegName "IconRegName"
#define XlDiconRegName "Name"

#define XlNtagName "tagName"
#define XlCTagName "TagName"
#define XlDtagName "Tag Name"


#define XlNnomeFile "nomeFile"
#define XlCNomeFile "NomeFile"
#define XlDnomeFile "Nome del file"


/*
	define per la prima variabile cambio colore
*/
#define XlNcoloreAutomatico1 "coloreAutomatico1"
#define XlCColoreAutomatico1 "ColoreAutomatico1"
#define XlDcoloreAutomatico1 "Colore flag automatico"
#define XlDefaultColoreAutomatico1 "cyan"

#define XlNcoloreStimato1 "coloreStimato1"
#define XlCColoreStimato1 "ColoreStimato1"
#define XlDcoloreStimato1 "Colore flag stimato"
#define XlDefaultColoreStimato1 "yellow"

#define XlNcoloreFuoriScansione1 "coloreFuoriScansione1"
#define XlCColoreFuoriScansione1 "ColoreFuoriScansione1"
#define XlDcoloreFuoriScansione1 "Colore fuori scansione"
#define XlDefaultColoreFuoriScansione1 "blue"

#define XlNcoloreFuoriAttendib1 "coloreFuoriAttendib1"
#define XlCColoreFuoriAttendib1 "ColoreFuoriAttendib1"
#define XlDcoloreFuoriAttendib1 "Colore fuori attendibilita'"
#define XlDefaultColoreFuoriAttendib1 "magenta"

#define XlNcoloreDigSet1 "coloreDigSet1"
#define XlCColoreDigSet1 "ColoreDigSet1"
#define XlDcoloreDigSet1 "Colore digitale On"
#define XlDefaultColoreDigSet1 "red"

#define XlNcoloreBassissimo1 "coloreBassissimo1"
#define XlCColoreBassissimo1 "ColoreBassissimo1"
#define XlDcoloreBassissimo1 "Colore fuori lim. basso sicurezza"
#define XlDefaultColoreBassissimo1 "red"
#define XlNvaloreBassissimo1 "valoreBassissimo1"
#define XlCValoreBassissimo1 "ValoreBassissimo1"
#define XlDvaloreBassissimo1 "Valore lim. basso sicurezza"
#define XlDefaultValoreBassissimo1 "0.0"

#define XlNcoloreBassissimoBasso1 "coloreBassissimoBasso1"
#define XlCColoreBassissimoBasso1 "ColoreBassissimoBasso1"
#define XlDcoloreBassissimoBasso1 "Colore fuori lim. basso conduzione"
#define XlDefaultColoreBassissimoBasso1 "yellow"
#define XlNvaloreBassissimoBasso1 "valoreBassissimoBasso1"
#define XlCValoreBassissimoBasso1 "ValoreBassissimoBasso1"
#define XlDvaloreBassissimoBasso1 "Valore lim. basso conduzione"
#define XlDefaultValoreBassissimoBasso1 "10.0"

#define XlNcoloreBassoAlto1 "coloreBassoAlto1"
#define XlCColoreBassoAlto1 "ColoreBassoAlto1"
#define XlDcoloreBassoAlto1 "Colore in conduzione"
#define XlDefaultColoreBassoAlto1 "green"
#define XlNvaloreBassoAlto1 "valoreBassoAlto1"
#define XlCValoreBassoAlto1 "ValoreBassoAlto1"
#define XlDvaloreBassoAlto1 "Valore lim. alto conduzione"
#define XlDefaultValoreBassoAlto1 "100.0"

#define XlNcoloreAltoAltissimo1 "coloreAltoAltissimo1"
#define XlCColoreAltoAltissimo1 "ColoreAltoAltissimo1"
#define XlDcoloreAltoAltissimo1 "Colore fuori lim. alto conduzione"
#define XlDefaultColoreAltoAltissimo1 "yellow"
#define XlNvaloreAltoAltissimo1 "valoreAltoAltissimo1"
#define XlCValoreAltoAltissimo1 "ValoreAltoAltissimo1"
#define XlDvaloreAltoAltissimo1 "Valore lim. alto sicurezza"
#define XlDefaultValoreAltoAltissimo1 "1000.0"

#define XlNcoloreAltissimo1 "coloreAltissimo1"
#define XlCColoreAltissimo1 "ColoreAltissimo1"
#define XlDcoloreAltissimo1 "Colore fuori lim. alto sicurezza"
#define XlDefaultColoreAltissimo1 "red"

/*
	define per la seconda variabile cambio colore
*/
#define XlNcoloreAutomatico2 "coloreAutomatico2"
#define XlCColoreAutomatico2 "ColoreAutomatico2"
#define XlDcoloreAutomatico2 "Colore flag automatico"
#define XlDefaultColoreAutomatico2 "cyan"

#define XlNcoloreStimato2 "coloreStimato2"
#define XlCColoreStimato2 "ColoreStimato2"
#define XlDcoloreStimato2 "Colore flag stimato"
#define XlDefaultColoreStimato2 "yellow"

#define XlNcoloreFuoriScansione2 "coloreFuoriScansione2"
#define XlCColoreFuoriScansione2 "ColoreFuoriScansione2"
#define XlDcoloreFuoriScansione2 "Colore fuori scansione"
#define XlDefaultColoreFuoriScansione2 "blue"

#define XlNcoloreFuoriAttendib2 "coloreFuoriAttendib2"
#define XlCColoreFuoriAttendib2 "ColoreFuoriAttendib2"
#define XlDcoloreFuoriAttendib2 "Colore fuori attendibilita'"
#define XlDefaultColoreFuoriAttendib2 "magenta"

#define XlNcoloreDigSet2 "coloreDigSet2"
#define XlCColoreDigSet2 "ColoreDigSet2"
#define XlDcoloreDigSet2 "Colore digitale On"
#define XlDefaultColoreDigSet2 "red"

#define XlNcoloreBassissimo2 "coloreBassissimo2"
#define XlCColoreBassissimo2 "ColoreBassissimo2"
#define XlDcoloreBassissimo2 "Colore fuori lim. basso sicurezza"
#define XlDefaultColoreBassissimo2 "red"
#define XlNvaloreBassissimo2 "valoreBassissimo2"
#define XlCValoreBassissimo2 "ValoreBassissimo2"
#define XlDvaloreBassissimo2 "Valore lim. basso sicurezza"
#define XlDefaultValoreBassissimo2 "0.0"

#define XlNcoloreBassissimoBasso2 "coloreBassissimoBasso2"
#define XlCColoreBassissimoBasso2 "ColoreBassissimoBasso2"
#define XlDcoloreBassissimoBasso2 "Colore fuori lim. basso conduzione"
#define XlDefaultColoreBassissimoBasso2 "yellow"
#define XlNvaloreBassissimoBasso2 "valoreBassissimoBasso2"
#define XlCValoreBassissimoBasso2 "ValoreBassissimoBasso2"
#define XlDvaloreBassissimoBasso2 "Valore lim. basso conduzione"
#define XlDefaultValoreBassissimoBasso2 "10.0"

#define XlNcoloreBassoAlto2 "coloreBassoAlto2"
#define XlCColoreBassoAlto2 "ColoreBassoAlto2"
#define XlDcoloreBassoAlto2 "Colore in conduzione"
#define XlDefaultColoreBassoAlto2 "green"
#define XlNvaloreBassoAlto2 "valoreBassoAlto2"
#define XlCValoreBassoAlto2 "ValoreBassoAlto2"
#define XlDvaloreBassoAlto2 "Valore lim. alto conduzione"
#define XlDefaultValoreBassoAlto2 "100.0"

#define XlNcoloreAltoAltissimo2 "coloreAltoAltissimo2"
#define XlCColoreAltoAltissimo2 "ColoreAltoAltissimo2"
#define XlDcoloreAltoAltissimo2 "Colore fuori lim. alto conduzione"
#define XlDefaultColoreAltoAltissimo2 "yellow"
#define XlNvaloreAltoAltissimo2 "valoreAltoAltissimo2"
#define XlCValoreAltoAltissimo2 "ValoreAltoAltissimo2"
#define XlDvaloreAltoAltissimo2 "Valore lim. alto sicurezza"
#define XlDefaultValoreAltoAltissimo2 "1000.0"

#define XlNcoloreAltissimo2 "coloreAltissimo2"
#define XlCColoreAltissimo2 "ColoreAltissimo2"
#define XlDcoloreAltissimo2 "Colore fuori lim. alto sicurezza"
#define XlDefaultColoreAltissimo2 "red"

/*
	define per la terza variabile cambio colore
*/
#define XlNcoloreAutomatico3 "coloreAutomatico3"
#define XlCColoreAutomatico3 "ColoreAutomatico3"
#define XlDcoloreAutomatico3 "Colore flag automatico"
#define XlDefaultColoreAutomatico3 "cyan"

#define XlNcoloreStimato3 "coloreStimato3"
#define XlCColoreStimato3 "ColoreStimato3"
#define XlDcoloreStimato3 "Colore flag stimato"
#define XlDefaultColoreStimato3 "yellow"

#define XlNcoloreFuoriScansione3 "coloreFuoriScansione3"
#define XlCColoreFuoriScansione3 "ColoreFuoriScansione3"
#define XlDcoloreFuoriScansione3 "Colore fuori scansione"
#define XlDefaultColoreFuoriScansione3 "blue"

#define XlNcoloreFuoriAttendib3 "coloreFuoriAttendib3"
#define XlCColoreFuoriAttendib3 "ColoreFuoriAttendib3"
#define XlDcoloreFuoriAttendib3 "Colore fuori attendibilita'"
#define XlDefaultColoreFuoriAttendib3 "magenta"

#define XlNcoloreDigSet3 "coloreDigSet3"
#define XlCColoreDigSet3 "ColoreDigSet3"
#define XlDcoloreDigSet3 "Colore digitale On"
#define XlDefaultColoreDigSet3 "red"

#define XlNcoloreBassissimo3 "coloreBassissimo3"
#define XlCColoreBassissimo3 "ColoreBassissimo3"
#define XlDcoloreBassissimo3 "Colore fuori lim. basso sicurezza"
#define XlDefaultColoreBassissimo3 "red"
#define XlNvaloreBassissimo3 "valoreBassissimo3"
#define XlCValoreBassissimo3 "ValoreBassissimo3"
#define XlDvaloreBassissimo3 "Valore lim. basso sicurezza"
#define XlDefaultValoreBassissimo3 "0.0"

#define XlNcoloreBassissimoBasso3 "coloreBassissimoBasso3"
#define XlCColoreBassissimoBasso3 "ColoreBassissimoBasso3"
#define XlDcoloreBassissimoBasso3 "Colore fuori lim. basso conduzione"
#define XlDefaultColoreBassissimoBasso3 "yellow"
#define XlNvaloreBassissimoBasso3 "valoreBassissimoBasso3"
#define XlCValoreBassissimoBasso3 "ValoreBassissimoBasso3"
#define XlDvaloreBassissimoBasso3 "Valore lim. basso conduzione"
#define XlDefaultValoreBassissimoBasso3 "10.0"

#define XlNcoloreBassoAlto3 "coloreBassoAlto3"
#define XlCColoreBassoAlto3 "ColoreBassoAlto3"
#define XlDcoloreBassoAlto3 "Colore in conduzione"
#define XlDefaultColoreBassoAlto3 "green"
#define XlNvaloreBassoAlto3 "valoreBassoAlto3"
#define XlCValoreBassoAlto3 "ValoreBassoAlto3"
#define XlDvaloreBassoAlto3 "Valore lim. alto conduzione"
#define XlDefaultValoreBassoAlto3 "100.0"

#define XlNcoloreAltoAltissimo3 "coloreAltoAltissimo3"
#define XlCColoreAltoAltissimo3 "ColoreAltoAltissimo3"
#define XlDcoloreAltoAltissimo3 "Colore fuori lim. alto conduzione"
#define XlDefaultColoreAltoAltissimo3 "yellow"
#define XlNvaloreAltoAltissimo3 "valoreAltoAltissimo3"
#define XlCValoreAltoAltissimo3 "ValoreAltoAltissimo3"
#define XlDvaloreAltoAltissimo3 "Valore lim. alto sicurezza"
#define XlDefaultValoreAltoAltissimo3 "1000.0"

#define XlNcoloreAltissimo3 "coloreAltissimo3"
#define XlCColoreAltissimo3 "ColoreAltissimo3"
#define XlDcoloreAltissimo3 "Colore fuori lim. alto sicurezza"
#define XlDefaultColoreAltissimo3 "red"

/*
	define per la quarta variabile cambio colore
*/
#define XlNcoloreAutomatico4 "coloreAutomatico4"
#define XlCColoreAutomatico4 "ColoreAutomatico4"
#define XlDcoloreAutomatico4 "Colore flag automatico"
#define XlDefaultColoreAutomatico4 "cyan"

#define XlNcoloreStimato4 "coloreStimato4"
#define XlCColoreStimato4 "ColoreStimato4"
#define XlDcoloreStimato4 "Colore flag stimato"
#define XlDefaultColoreStimato4 "yellow"

#define XlNcoloreFuoriScansione4 "coloreFuoriScansione4"
#define XlCColoreFuoriScansione4 "ColoreFuoriScansione4"
#define XlDcoloreFuoriScansione4 "Colore fuori scansione"
#define XlDefaultColoreFuoriScansione4 "blue"

#define XlNcoloreFuoriAttendib4 "coloreFuoriAttendib4"
#define XlCColoreFuoriAttendib4 "ColoreFuoriAttendib4"
#define XlDcoloreFuoriAttendib4 "Colore fuori attendibilita'"
#define XlDefaultColoreFuoriAttendib4 "magenta"

#define XlNcoloreDigSet4 "coloreDigSet4"
#define XlCColoreDigSet4 "ColoreDigSet4"
#define XlDcoloreDigSet4 "Colore digitale On"
#define XlDefaultColoreDigSet4 "red"

#define XlNcoloreBassissimo4 "coloreBassissimo4"
#define XlCColoreBassissimo4 "ColoreBassissimo4"
#define XlDcoloreBassissimo4 "Colore fuori lim. basso sicurezza"
#define XlDefaultColoreBassissimo4 "red"
#define XlNvaloreBassissimo4 "valoreBassissimo4"
#define XlCValoreBassissimo4 "ValoreBassissimo4"
#define XlDvaloreBassissimo4 "Valore lim. basso sicurezza"
#define XlDefaultValoreBassissimo4 "0.0"

#define XlNcoloreBassissimoBasso4 "coloreBassissimoBasso4"
#define XlCColoreBassissimoBasso4 "ColoreBassissimoBasso4"
#define XlDcoloreBassissimoBasso4 "Colore fuori lim. basso conduzione"
#define XlDefaultColoreBassissimoBasso4 "yellow"
#define XlNvaloreBassissimoBasso4 "valoreBassissimoBasso4"
#define XlCValoreBassissimoBasso4 "ValoreBassissimoBasso4"
#define XlDvaloreBassissimoBasso4 "Valore lim. basso conduzione"
#define XlDefaultValoreBassissimoBasso4 "10.0"

#define XlNcoloreBassoAlto4 "coloreBassoAlto4"
#define XlCColoreBassoAlto4 "ColoreBassoAlto4"
#define XlDcoloreBassoAlto4 "Colore in conduzione"
#define XlDefaultColoreBassoAlto4 "green"
#define XlNvaloreBassoAlto4 "valoreBassoAlto4"
#define XlCValoreBassoAlto4 "ValoreBassoAlto4"
#define XlDvaloreBassoAlto4 "Valore lim. alto conduzione"
#define XlDefaultValoreBassoAlto4 "100.0"

#define XlNcoloreAltoAltissimo4 "coloreAltoAltissimo4"
#define XlCColoreAltoAltissimo4 "ColoreAltoAltissimo4"
#define XlDcoloreAltoAltissimo4 "Colore fuori lim. alto conduzione"
#define XlDefaultColoreAltoAltissimo4 "yellow"
#define XlNvaloreAltoAltissimo4 "valoreAltoAltissimo4"
#define XlCValoreAltoAltissimo4 "ValoreAltoAltissimo4"
#define XlDvaloreAltoAltissimo4 "Valore lim. alto sicurezza"
#define XlDefaultValoreAltoAltissimo4 "1000.0"

#define XlNcoloreAltissimo4 "coloreAltissimo4"
#define XlCColoreAltissimo4 "ColoreAltissimo4"
#define XlDcoloreAltissimo4 "Colore fuori lim. alto sicurezza"
#define XlDefaultColoreAltissimo4 "red"


#define XlNanimatedColor "animatedColor"
#define XlCAnimatedColor "AnimatedColor"
#define XlDAnimatedColor "Colore Animato"
#define XlDefaultColoreAnimato "red 0"

/*
 nomi di risorse utilizzate in connessione con l'ambiente
 di simulazione
*/
#define XlNvarInputColore  "varInputColore"
#define XlCVarInputColore  "VarInputColore"
#define XlDvarInputColore  "Variabile di input"
#define XlNvarInputBlink   "varInputBlink"
#define XlCVarInputBlink   "VarInputBlink"
#define XlDvarInputBlink   "Variabile di blink"
#define XlNvarInputCambioColore1  "varInputCambioColore1"
#define XlCVarInputCambioColore1  "VarInputCambioColore1"
#define XlDvarInputCambioColore1  "Prima variabile cambio colore"
#define XlNvarInputCambioColore2  "varInputCambioColore2"
#define XlCVarInputCambioColore2  "VarInputCambioColore2"
#define XlDvarInputCambioColore2  "Seconda variabile cambio colore"
#define XlNvarInputCambioColore3  "varInputCambioColore3"
#define XlCVarInputCambioColore3  "VarInputCambioColore3"
#define XlDvarInputCambioColore3  "Terza variabile cambio colore"
#define XlNvarInputCambioColore4  "varInputCambioColore4"
#define XlCVarInputCambioColore4  "VarInputCambioColore4"
#define XlDvarInputCambioColore4  "Quarta variabile cambio colore"
#define XlNvarInput        "varInput"
#define XlCVarInput        "VarInput"
#define XlDvarInput        "Variabile di ingresso"
#define XlNvarInputErr        "varInputErr"
#define XlCVarInputErr        "VarInputErr"
#define XlDvarInputErr        "Variabile di errore"
#define XlNvarOutput       "varOutput"
#define XlCVarOutput       "VarOutput"
#define XlDvarOutput       "Variabile di attuazione"
#define XlNpaginaStazioni       "paginaStazioni"
#define XlCPaginaStazioni       "PaginaStazioni"
#define XlDpaginaStazioni       "Pagina di stazioni collegata"
#define XlNcompiled       "compiled"
#define XlCCompiled       "Compiled"
#define XlDcompiled       ""

/*
 nomi di risorse utilizzate per il database
*/
#define XlNnomeFile "nomeFile"
#define XlCNomeFile "NomeFile"
#define XlNshrKey "shrKey"
#define XlCShrKey "ShrKey"
#define XlNshrKeyS "shrKeyS"
#define XlCShrKeyS "ShrKeyS"
#define XlNfileSubSystem "fileSubS"
#define XlCFileSubSystem "FileSubS"
#define XlNfileComponent "fileComp"
#define XlCFileComponent "FileComp"
#define XlNfileVarCC "fileVarCC"
#define XlCFileVarCC "FileVarCC"
#define XlNrefreshFreq "refresh_freq"
#define XlCRefreshFreq "Refresh_freq"

/* define per XlPictograph
*/

/* prima zona animata
*/
#define XlNvarInputCambioColore1_1 "varInputCambioColore1_1"
#define XlCVarInputCambioColore1_1 "VarInputCambioColore1_1"
#define XlDvarInputCambioColore1_1 "Input Var (bit 0)"

#define XlNflagOffset1_1 "flagOffset1_1"
#define XlCFlagOffset1_1 "FlagOffset1_1"
#define XlDflagOffset1_1 "Flag Offset"

#define XlNvarInputCambioColore1_2 "varInputCambioColore1_2"
#define XlCVarInputCambioColore1_2 "VarInputCambioColore1_2"
#define XlDvarInputCambioColore1_2 "Input Var (bit 1)"

#define XlNflagOffset1_2 "flagOffset1_2"
#define XlCFlagOffset1_2 "FlagOffset1_2"
#define XlDflagOffset1_2 "Flag Offset"

#define XlNvarInputCambioColore1_3 "varInputCambioColore1_3"
#define XlCVarInputCambioColore1_3 "VarInputCambioColore1_3"
#define XlDvarInputCambioColore1_3 "Input Var (bit 2)"

#define XlNflagOffset1_3 "flagOffset1_3"
#define XlCFlagOffset1_3 "FlagOffset1_3"
#define XlDflagOffset1_3 "Flag Offset"

#define XlNvarInputCambioColore1_4 "varInputCambioColore1_4"
#define XlCVarInputCambioColore1_4 "VarInputCambioColore1_4"
#define XlDvarInputCambioColore1_4 "Input Var (bit 3)"

#define XlNflagOffset1_4 "flagOffset1_4"
#define XlCFlagOffset1_4 "FlagOffset1_4"
#define XlDflagOffset1_4 "Flag Offset"

#define XlNvarInputCambioColore1_5 "varInputCambioColore1_5"
#define XlCVarInputCambioColore1_5 "VarInputCambioColore1_5"
#define XlDvarInputCambioColore1_5 "Input Var (bit 4)"

#define XlNflagOffset1_5 "flagOffset1_5"
#define XlCFlagOffset1_5 "FlagOffset1_5"
#define XlDflagOffset1_5 "Flag Offset"

#define XlNvarInputCambioColore1_6 "varInputCambioColore1_6"
#define XlCVarInputCambioColore1_6 "VarInputCambioColore1_6"
#define XlDvarInputCambioColore1_6 "Input Var (bit 5)"


#define XlNflagOffset1_6 "flagOffset1_6"
#define XlCFlagOffset1_6 "FlagOffset1_6"
#define XlDflagOffset1_6 "Flag Offset"


/* seconda zona animata
*/
#define XlNvarInputCambioColore2_1 "varInputCambioColore2_1"
#define XlCVarInputCambioColore2_1 "VarInputCambioColore2_1"
#define XlDvarInputCambioColore2_1 "Input Var (bit 0)"

#define XlNflagOffset2_1 "flagOffset2_1"
#define XlCFlagOffset2_1 "FlagOffset2_1"
#define XlDflagOffset2_1 "Flag Offset"

#define XlNvarInputCambioColore2_2 "varInputCambioColore2_2"
#define XlCVarInputCambioColore2_2 "VarInputCambioColore2_2"
#define XlDvarInputCambioColore2_2 "Input Var (bit 1)"

#define XlNflagOffset2_2 "flagOffset2_2"
#define XlCFlagOffset2_2 "FlagOffset2_2"
#define XlDflagOffset2_2 "Flag Offset"

#define XlNvarInputCambioColore2_3 "varInputCambioColore2_3"
#define XlCVarInputCambioColore2_3 "VarInputCambioColore2_3"
#define XlDvarInputCambioColore2_3 "Input Var (bit 2)"

#define XlNflagOffset2_3 "flagOffset2_3"
#define XlCFlagOffset2_3 "FlagOffset2_3"
#define XlDflagOffset2_3 "Flag Offset"

#define XlNvarInputCambioColore2_4 "varInputCambioColore2_4"
#define XlCVarInputCambioColore2_4 "VarInputCambioColore2_4"
#define XlDvarInputCambioColore2_4 "Input Var (bit 3)"

#define XlNflagOffset2_4 "flagOffset2_4"
#define XlCFlagOffset2_4 "FlagOffset2_4"
#define XlDflagOffset2_4 "Flag Offset"

#define XlNvarInputCambioColore2_5 "varInputCambioColore2_5"
#define XlCVarInputCambioColore2_5 "VarInputCambioColore2_5"
#define XlDvarInputCambioColore2_5 "Input Var (bit 4)"

#define XlNflagOffset2_5 "flagOffset2_5"
#define XlCFlagOffset2_5 "FlagOffset2_5"
#define XlDflagOffset2_5 "Flag Offset"

#define XlNvarInputCambioColore2_6 "varInputCambioColore2_6"
#define XlCVarInputCambioColore2_6 "VarInputCambioColore2_6"
#define XlDvarInputCambioColore2_6 "Input Var (bit 5)"

#define XlNflagOffset2_6 "flagOffset2_6"
#define XlCFlagOffset2_6 "FlagOffset2_6"
#define XlDflagOffset2_6 "Flag Offset"

#define XlNcoloreDefault2  "coloreDefault2"
#define XlCColoreDefault2  "ColoreDefault2"
#define XlDcoloreDefault2 "Colore di Default"
#define XlDefaultColore2  "Blue 0 0"

/* terza zona animata
*/
#define XlNvarInputCambioColore3_1 "varInputCambioColore3_1"
#define XlCVarInputCambioColore3_1 "VarInputCambioColore3_1"
#define XlDvarInputCambioColore3_1 "Input Var (bit 0)"

#define XlNflagOffset3_1 "flagOffset3_1"
#define XlCFlagOffset3_1 "FlagOffset3_1"
#define XlDflagOffset3_1 "Flag Offset"

#define XlNvarInputCambioColore3_2 "varInputCambioColore3_2"
#define XlCVarInputCambioColore3_2 "VarInputCambioColore3_2"
#define XlDvarInputCambioColore3_2 "Input Var (bit 1)"

#define XlNflagOffset3_2 "flagOffset3_2"
#define XlCFlagOffset3_2 "FlagOffset3_2"
#define XlDflagOffset3_2 "Flag Offset"

#define XlNvarInputCambioColore3_3 "varInputCambioColore3_3"
#define XlCVarInputCambioColore3_3 "VarInputCambioColore3_3"
#define XlDvarInputCambioColore3_3 "Input Var (bit 2)"

#define XlNflagOffset3_3 "flagOffset3_3"
#define XlCFlagOffset3_3 "FlagOffset3_3"
#define XlDflagOffset3_3 "Flag Offset"

#define XlNvarInputCambioColore3_4 "varInputCambioColore3_4"
#define XlCVarInputCambioColore3_4 "VarInputCambioColore3_4"
#define XlDvarInputCambioColore3_4 "Input Var (bit 3)"

#define XlNflagOffset3_4 "flagOffset3_4"
#define XlCFlagOffset3_4 "FlagOffset3_4"
#define XlDflagOffset3_4 "Flag Offset"

#define XlNvarInputCambioColore3_5 "varInputCambioColore3_5"
#define XlCVarInputCambioColore3_5 "VarInputCambioColore3_5"
#define XlDvarInputCambioColore3_5 "Input Var (bit 4)"

#define XlNflagOffset3_5 "flagOffset3_5"
#define XlCFlagOffset3_5 "FlagOffset3_5"
#define XlDflagOffset3_5 "Flag Offset"

#define XlNvarInputCambioColore3_6 "varInputCambioColore3_6"
#define XlCVarInputCambioColore3_6 "VarInputCambioColore3_6"
#define XlDvarInputCambioColore3_6 "Input Var (bit 5)"

#define XlNflagOffset3_6 "flagOffset3_6"
#define XlCFlagOffset3_6 "FlagOffset3_6"
#define XlDflagOffset3_6 "Flag Offset"

#define XlNcoloreDefault3  "coloreDefault3"
#define XlCColoreDefault3  "ColoreDefault3"
#define XlDcoloreDefault3 "Colore di Default"
#define XlDefaultColore3  "Blue 0 0"

/* quarta zona animata
*/
#define XlNvarInputCambioColore4_1 "varInputCambioColore4_1"
#define XlCVarInputCambioColore4_1 "VarInputCambioColore4_1"
#define XlDvarInputCambioColore4_1 "Input Var (bit 0)"

#define XlNflagOffset4_1 "flagOffset4_1"
#define XlCFlagOffset4_1 "FlagOffset4_1"
#define XlDflagOffset4_1 "Flag Offset"

#define XlNvarInputCambioColore4_2 "varInputCambioColore4_2"
#define XlCVarInputCambioColore4_2 "VarInputCambioColore4_2"
#define XlDvarInputCambioColore4_2 "Input Var (bit 1)"

#define XlNflagOffset4_2 "flagOffset4_2"
#define XlCFlagOffset4_2 "FlagOffset4_2"
#define XlDflagOffset4_2 "Flag Offset"

#define XlNvarInputCambioColore4_3 "varInputCambioColore4_3"
#define XlCVarInputCambioColore4_3 "VarInputCambioColore4_3"
#define XlDvarInputCambioColore4_3 "Input Var (bit 2)"

#define XlNflagOffset4_3 "flagOffset4_3"
#define XlCFlagOffset4_3 "FlagOffset4_3"
#define XlDflagOffset4_3 "Flag Offset"

#define XlNvarInputCambioColore4_4 "varInputCambioColore4_4"
#define XlCVarInputCambioColore4_4 "VarInputCambioColore4_4"
#define XlDvarInputCambioColore4_4 "Input Var (bit 3)"

#define XlNflagOffset4_4 "flagOffset4_4"
#define XlCFlagOffset4_4 "FlagOffset4_4"
#define XlDflagOffset4_4 "Flag Offset"

#define XlNvarInputCambioColore4_5 "varInputCambioColore4_5"
#define XlCVarInputCambioColore4_5 "VarInputCambioColore4_5"
#define XlDvarInputCambioColore4_5 "Input Var (bit 4)"


#define XlNflagOffset4_5 "flagOffset4_5"
#define XlCFlagOffset4_5 "FlagOffset4_5"
#define XlDflagOffset4_5 "Flag Offset"

#define XlNvarInputCambioColore4_6 "varInputCambioColore4_6"
#define XlCVarInputCambioColore4_6 "VarInputCambioColore4_6"
#define XlDvarInputCambioColore4_6 "Input Var (bit 5)"


#define XlNflagOffset4_6 "flagOffset4_6"
#define XlCFlagOffset4_6 "FlagOffset4_6"
#define XlDflagOffset4_6 "Flag Offset"

#define XlNcoloreDefault4  "coloreDefault4"
#define XlCColoreDefault4  "ColoreDefault4"
#define XlDcoloreDefault4 "Colore di Default"
#define XlDefaultColore4  "Blue 0 0"

/* define per XlIndicTelep
*/

#define XlDvar   "Input variable"
#define XlDfault "Fault variable"
#define XlDfaultRi "Ack variable"

#define XlNcoloreVarOn "coloreVarOn"
#define XlCColoreVarOn "ColoreVarOn"
#define XlDcoloreVarOn "Color for status 1 "        
#define XlColoreVarOn "green 0 0"        

#define XlNcoloreVarOff "coloreVarOff"
#define XlCColoreVarOff "ColoreVarOff"
#define XlDcoloreVarOff "Color for status 0 "        
#define XlColoreVarOff "white 0 0"        

#define XlNcoloreFaultOn "coloreFaultOn"
#define XlCColoreFaultOn "ColoreFaultOn"
#define XlDcoloreFaultOn "Bkg Color for Fault"        
#define XlColoreFaultOn "Red 2.0 0"    

/* define per gestione frame oggetti Teleperm operable
*/
#define XlNtopBorder "topBorder"
#define XlCTopBorder "TopBorder"
#define XlDtopBorder "top border"

#define XlNbottomBorder "bottomBorder"
#define XlCBottomBorder "BottomBorder"
#define XlDbottomBorder "bottom border"

#define XlNleftBorder "leftBorder"
#define XlCLeftBorder "LeftBorder"
#define XlDleftBorder "left border"

#define XlNrightBorder "rightBorder"
#define XlCRightBorder "RightBorder"
#define XlDrightBorder "right border"

#define XlNowOpen "owOpen"
#define XlCOwOpen "OwOpen"

#define XlNframeWidth "frameWidth"
#define XlCFrameWidth "FrameWidth"
#define XlDframeWidth "Frame width"

#define XlNowFrameColor "owFrameColor"
#define XlCOwFrameColor "OwFrameColor"
#define XlDowFrameColor "O/W operation frame color"

#define XlNvarFrameColor "varFrameColor"
#define XlCVarFrameColor "VarFrameColor"
#define XlDvarFrameColor "Variable Frame color"

#define XlNvarInputFrame "varInputFrame"
#define XlCVarInputFrame "VarInputFrame"
#define XlDvarInputFrame "Variable frame control"

#define XlNcoloreDefault1  "coloreDefault1"
#define XlCColoreDefault1  "ColoreDefault1"
#define XlDcoloreDefault1 "Colore di Default"

#define XlDefaultColore1  "Blue 0.0 1"


/*
	define di uso generale
*/
#define NUMERO_INTERI_VISUALIZZATI	2  /* numero di interi visualizzati 
					      di default nei display numerici */
#define NUMERO_DECIMALI_VISUALIZZATI	1  /* numero di decimali visualizzati 
                                              di default nei display numerici */
#define VALORE_MINIMO		     "-99."  /* valore di default del fondo
			                     scala minimo                    */
#define VALORE_MASSIMO		     "99."  /* valore di default del fondo
			                      scala massimo                   */
#define VALORE_SCALAMENTO            "1."  /* valore di default dello 
					      scalamento                      */
#define VALORE_OFFSET                "0."  /* valore di default dell'offset   */

#define VALORE_MASSIMO_SCALA	     "100." /* valore di default per la scala 
						fissa dell'oggetto grafico  */
#define VALORE_MINIMO_SCALA	     "-100."  /* valore di default per la scala
						fissa dell'oggetto grafico  */

/*
	blink rate degli oggetti in millsimi di secondo
*/
#define BLINK_RATE		125
#define FREQUENZA_BASE		2

/******************************************************************
Valori blink per Cai tipi di allarmi per Cai e tipi di maschere
*******************************************************************/
#define BLINK_ON_FQZ1     2
#define BLINK_ON_FQZ2     3


/*
 Prototyping funzioni di libreria
*/

extern AN_OBJ * XlGetAnObjList(Widget );
extern void XlFreeAnObjList(AN_OBJ * );


extern int XlTransferResource(XrmDatabase *  , XrmDatabase *  , Widget  , char *  , char * );

extern char * XlGetClassName(WidgetClass );
extern WidgetClass XlGetClassWid(char * );

extern void gest_trasf_coor(Widget  , int *  , int * );
extern void gest_trasf_wh(Widget  , int *  , int *  , int *  , int * );
extern void gest_trasf_arc(Widget  , int *  , int * );
extern void XlTesto(Widget  , Drawable  , GC  , int  , int  , char *  , XFontStruct * );
extern void gest_trasf_testo(Widget  , int *  , int *  , char *  , XFontStruct * );
extern void XlRiempiRettangolo(Widget  , Drawable  , GC  , int  , int  , int  , int );
extern void XlRettangolo(Widget  , Drawable  , GC  , int  , int  , int  , int );
extern void XlArco(Widget  , Drawable  , GC  , int  , int  , int  , int  , int  , int );
extern void XlLinea(Widget  , Drawable  , GC  , int  , int  , int  , int );

extern Boolean OlDestroyCompiler(OlCompilerObject );

extern int XlSetResourceByName(XrmDatabase *  , String  , char *  , char * );
extern int XlSetChildResourceByName(XrmDatabase *  , String  , String  , char *  , char * );
extern int XlSetResourceByWidget(XrmDatabase *  , Widget  , char *  , char * );

extern XlConfInfo *XlGetConfinfoCore (Widget );
extern XlConfInfo *XlGetConfinfoWid (Widget );
extern Boolean XlIsXlCore(Widget);
extern Boolean XlIsXlComposite(Widget);
extern Boolean XlIsInEdit(Widget);
extern Boolean XlIsGraficoArch(Widget);
extern Boolean XlIsGraficoSingle(Widget);
extern Boolean XlGetCaiState();
Boolean XlIsIndic(Widget);

char *XlGetenv(char *);
Boolean XlPutenv(char *,char *);
char *XlGetDir(char *);
char *XlGetDir2(char *,char*);
Boolean XlRename(char *, char *);
Boolean XlCopy(char *, char *);
Boolean XlRemove(char *);
char *XlConvPathVms(char *);
char *XlConvDirVms(char *);
char *XlUnconvPathVms(char *);
char *XlUnconvDirVms(char *);
int XlChDir(char *);
void XlBlink();
float XlGetBlink(Widget, int);
#if defined VMS
double rint();
#endif
Boolean XlIsXlWidget();
Boolean XlAllocWidgetString(Widget, XtResourceList ,int );
Boolean XlFreeWidgetString(Widget, XtResourceList ,int );
Cursor XlCreateWaitCursor(Widget );
Cursor XlCreateErrCursor(Widget );
void XlSetCursor(Widget ,Cursor );
void XlUnsetCursor(Widget );
Boolean XlFreeCursor(Widget ,Cursor );
GC XlFlagToGC();
/* funzioni per trattamento stringhe gerarchie */

char *format_hierarchy_new(char *,char *);
char *hierarchy_format_new(char *,char * );

#endif  /* _Xl_h */

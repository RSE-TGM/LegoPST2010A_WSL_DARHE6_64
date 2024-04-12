/**********************************************************************
*
*       C Header:               XlOperableKeys.h
*       Subsystem:              1
*       Description:
*       %created_by:    carlo %
*       %date_created:  Mon Sep 29 11:18:25 1997 %
*
**********************************************************************/
/*
 * XlOperableKeys.h - file di include pubblico per l'utilizzo del widget
 *		   OperableKeys
 */
#ifndef _XlOperableKeys_h
#define _XlOperableKeys_h

/* tipo operable keys 
*/
#define OPKEY_DIRECT	0   /* gestione diretta perturbazione */
#define OPKEY_IMPULSE	1   /* gestione indiretta perturbazione Impulse */
#define OPKEY_EXEC	2   /* gestione indiretta perturbazione Execute  */
#define OPKEY_OPENEXT2	3   /* apre la extension2 (se verra' implementato) */

#define DRAW_BITMAP	0   /* bottone con pixmap */
#define DRAW_LABEL	1   /* bottone con label */

#define DRAWPUSH_OFF 0      /* bottone senza effetto push */
#define DRAWPUSH_ON  1      /* bottone con effetto push */


/* default 
*/
#define DEFAULT_TIPO 	OPKEY_DIRECT    /* tipo di default DIRECT */
#define DEFAULT_DRAW	DRAW_BITMAP     /* default bottone con bitmap */
#define DEFAULT_DRAWPUSH	DRAWPUSH_OFF     /* default effetto push */
#define DEFAULT_WIDTH	60              /* dimensioni di default */
#define DEFAULT_HEIGHT	60
#define DEFAULT_FILL	0
#define MAXLUNGBMP	256		/* max lung. nome bmp */	
/*

 nomi di risorse utilizzate internamente al operableKeys
 */
#define XlNnormFg     	  "buttonForeground"
#define XlCNormFg         "ButtonForeground"
#define XlDnormFg         "Button foreground"
 
#define XlNhstateBg "hstateBg"    /* definizioni bg su stato 1 var input */ 
#define XlCHstateBg "HstateBg"
#define XlDhstateBg "Bkg on hight state input var"

#define XlNlstateBg "lstateBg"    /* definizioni bg su stato 0 var input */
#define XlCLstateBg "LstateBg"
#define XlDlstateBg "Bkg on low state input var"
 
#define XlNoperableKeysType       "operableKeysType"
#define XlCOperableKeysType       "OperableKeysType"
#define XlDoperableKeysType       "Operable key type"
#define XlOoperableKeysType       " Direct , Impulse , Execute "

/* effetto bottone premuto switchando i colori di shadowing del bottone
*/
#define XlNoperableKeysDrawPush       "operableKeysDrawPush"
#define XlCOperableKeysDrawPush       "OperableKeysDrawPush"
#define XlDoperableKeysDrawPush       "Draw Push effect"
#define XlOoperableKeysDrawPush       " Motif Standard , PushIN/OUT "

/*
Risorsa per importare o un bitmap o una Label
*/
#define XlNoperableKeysDraw       "operableKeysDraw"
#define XlCOperableKeysDraw       "OperableKeysDraw"
#define XlDoperableKeysDraw       "Bitmap or String"
#define XlOoperableKeysDraw       " Bitmap , String "


/*
Nuova risorsa per abilitare il background del pushButton
Per disegnare il bordo rosso in config quando seleziono l' oggetto,
devo avero un bordo, intorno al bottone di dimensioni non nulle.
Questo bordo ha il colore norm_bg. Per renderlo compatibile con
precedenti versioni si introduce la risorsa fillButton
*/
#define XlNfillButton       "fillButton"
#define XlCFillButton       "FillButton"
#define XlDfillButton       "Enable Background Button"
#define XlOfillButton       " NO , YES "

#define XlNnameBmp     "bitmapName"
#define XlCNameBmp     "BitmapName"
#define XlDnameBmp     "Bitmap name"

#define XlNlabel         "label"
#define XlCLabel         "Label"
#define XlDlabel         "label under button"

#define XlNbuttonLabel     "buttonLabel"
#define XlCButtonLabel     "ButtonLabel"
#define XlDbuttonLabel     "Button label"

#define XlNvarInput   "varInput"
#define XlCVarInput   "VarInput"
#define XlDvarInput   "Input variable"

#define XlNvarOutput   "varOutput"
#define XlCVarOutput   "VarOutput"
#define XlDvarOutput   "Output variable"

#define XlNvarOutput2   "varOutput2"
#define XlCVarOutput2   "VarOutput2"
#define XlDvarOutput2   "Second Output variable"


/* declare the class constant */
extern WidgetClass xlOperableKeysWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di OperableKeys */
typedef struct _XlOperableKeysClassRec *XlOperableKeysWidgetClass;
typedef struct _XlOperableKeysRec *XlOperableKeysWidget;
 

Boolean XlIsOperableKeys(Widget w);

#endif 

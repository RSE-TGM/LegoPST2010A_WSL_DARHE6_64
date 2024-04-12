/**********************************************************************
*
*       C Header:               XlChangePage.h
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Thu Oct  9 18:13:49 1997 %
*
**********************************************************************/
/*
 * XlChangePage.h - file di include pubblico per l'utilizzo del widget
 *		   ChangePage
 */
#ifndef _XlChangePage_h
#define _XlChangePage_h

#define CHANGE_PAGE	0
#define NEW_PAGE	1
#define CLOSE_PAGE	2
#define SYSTEM		3
#define OPEN_EXT2	4
#define DRAW_BITMAP	0
#define DRAW_LABEL	1
#define DRAW_GIF	2
#define DEFAULT_CHANGE_MODE CHANGE_PAGE
#define DEFAULT_DRAW	DRAW_BITMAP
#define DEFAULT_WIDTH	60
#define DEFAULT_HEIGHT	60
#define DEFAULT_FILL	0
#define MAXLUNGBMP	256	
/*
 nomi di risorse utilizzate internamente al changePage
 */
#define XlNchangeType       "changeType"
#define XlCChangeType       "ChangeType"
#define XlDchangeType       "Change page or new page"
#define XlOchangeType       "Change page, New page, Close page, System , Open Extension2 "
/*
Nuove risorsa aggiunta per importare o un bitmap o una Label
*/
#define XlNchangeDraw       "changeDraw"
#define XlCChangeDraw       "ChangeDraw"
#define XlDchangeDraw       "Load Bitmap, String or GIF"
#define XlOchangeDraw       " Bitmap , String, GIF "
/*
Nuova risorsa per abilitare il background del pushButton
Per disegnare il bordo rosso in config quando seleziono l' oggetto,
devo avero un bordo, intorno al bottone di dimensioni non nulle.
Questo bordo ha il colore norm_bg. Per renderlo compatibile con
preecdenti versioni si introduce la risorsa fillButton
*/
#define XlNfillButton       "fillButton"
#define XlCFillButton       "FillButton"
#define XlDfillButton       "Enable Background Button"
#define XlOfillButton       " NO , YES "

#define XlNpageName     "pageName"
#define XlCPageName     "PageName"
#define XlDpageName     "Page name"

#define XlNnameBmp     "bitmapName"
#define XlCNameBmp     "BitmapName"
#define XlDnameBmp     "Bitmap name"

#define XlNcommand     "command"
#define XlCCommand     "command"
#define XlDcommand     "System Command"

#define XlNnameButton     "buttonName"
#define XlCNameButton     "ButtonName"
#define XlDnameButton     "Button label"

#define XlNnormBg     	  "buttonBackground"
#define XlCNormBg         "ButtonBackground"
#define XlDnormBg         "Button background"
/* declare the class constant */
extern WidgetClass xlChangePageWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di ChangePage */
typedef struct _XlChangePageClassRec *XlChangePageWidgetClass;
typedef struct _XlChangePageRec *XlChangePageWidget;
 
#endif 

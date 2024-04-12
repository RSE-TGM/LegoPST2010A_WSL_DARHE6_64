/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
   modulo XlIconReg.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlIconReg.h	5.1
*/
/*
 * XlIconReg.h - file di include pubblico per l'utilizzo del widget
 *             led
 */
#ifndef _XlIconReg_h
#define _XlIconReg_h


/*
 nomi di risorse utilizzate internamente all'oggetto
 */

#define XlNmodulName "modulName"
#define XlCModulName "ModulName"
#define XlDmodulName "Modul Name"

#define XlNiconDescr "iconDescr"
#define XlCIconDescr "IconDescr"
#define XlDiconDescr "Description"

#define XlNinputValue "inputValue"
#define XlCInputValue "InputValue"
#define XlDinputValue "Input Value"

#define XlNobjectForm "objectForm"
#define XlCObjectForm "ObjectForm"

#define XlNiconRegType "iconRegType"
#define XlCIconRegType "IconRegType"
#define XlDiconRegType "IconReg type"
#define XlOiconRegType "Normal,Input interface,Output interface"

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

#define NOME_ICONA_RIMANDO "INTE"

#define MAX_LUN_NOME_MODULO	4
#define MAX_LUN_NOME_SIGLA	4

#define NORMAL_ICONREG			0
#define INPUT_INTERFACE_ICONREG		1
#define OUTPUT_INTERFACE_ICONREG	2
#define DEFAULT_TYPE_ICONREG		NORMAL_ICONREG

/* declare the class constant */
extern WidgetClass xlIconRegWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di IconReg */
typedef struct _XlIconRegClassRec *XlIconRegWidgetClass;
typedef struct _XlIconRegRec *XlIconRegWidget;
 
/* dichiarazioni di funzioni visibile dall'esterno  */
Boolean XlIsIconReg(Widget );
Boolean XlIsInterfaceIconReg(Widget );
Boolean XlInterfaceIconRegIsConnected(Widget );
Boolean XlCheckIconReg(Widget );
char * XlGetInterfaceIconRegPagConnect(Widget);

#endif /* _XlIconReg_h */


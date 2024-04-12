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
   modulo XlLabel.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlLabel.h	5.1
*/
/*
 * XlLabel.h - file di include pubblico per l'utilizzo del widget
 *             label
 */
#ifndef _XlLabel_h
#define _XlLabel_h

/*
 nomi di risorse utilizzate internamente al label
 */
#define XlNtipoLabel "tipoLabel"
#define XlCTipoLabel "TipoLabel"
#define XlDtipoLabel "Label type"
#define XlOtipoLabel "Label norm,Label big,Page's name,Page's description (1),Page's description (2),Page's description (3),Page's description (4),Compilation time,Regolation time,Regolation tag,Scheme in use"
#define XlNnormalFont "normalFont"
#define XlCNormalFont "NormalFont"
#define XlDnormalFont "Font"



/* costanti utilizzabili per settare il tipo di XlLabel */

#define LABEL_NORM  0
#define LABEL_BIG  1
#define LABEL_NOME_PAGINA  2
#define LABEL_DESCR_PAGINA_1  3
#define LABEL_DESCR_PAGINA_2  4
#define LABEL_DESCR_PAGINA_3  5
#define LABEL_DESCR_PAGINA_4  6
#define LABEL_DATE_COMPILE  7
#define LABEL_DATE_REG      8
#define LABEL_TAG_REG       9
#define LABEL_IN_USE       10
#define _LABEL_MAX     	   10
#define NO_ROTABLE	0
#define ROTABLE		1


/* declare the class constant */
extern WidgetClass xlLabelWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Label */
typedef struct _XlLabelClassRec *XlLabelWidgetClass;
typedef struct _XlLabelRec *XlLabelWidget;

#endif /* _XlLabel_h */


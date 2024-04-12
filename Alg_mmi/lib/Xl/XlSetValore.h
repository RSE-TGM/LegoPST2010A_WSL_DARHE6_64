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
   modulo XlSetValore.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlSetValore.h	5.1
*/
/*
 * XlSetValore.h - file di include pubblico per l'utilizzo del widget
 *		   SetValore
 */
#ifndef _XlSetValore_h
#define _XlSetValore_h

/*
 nomi di risorse utilizzate internamente al setValore
 */
#define XlNvarInibitSetV       "varInibit"
#define XlCVarInibitSetV       "VarInibit"
#define XlDvarInibitSetV       "Variabile di inibizione pulsante"
#define XlNvarRltargetSetV     "varRltarget"
#define XlCVarRltargetSetV     "VarRltarget"
#define XlDvarRltargetSetV     "Variabile associata all'attuazione"



/* declare the class constant */
extern WidgetClass xlSetValoreWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di SetValore */
typedef struct _XlSetValoreClassRec *XlSetValoreWidgetClass;
typedef struct _XlSetValoreRec *XlSetValoreWidget;
 
#endif 


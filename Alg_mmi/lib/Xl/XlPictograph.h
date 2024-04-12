/**********************************************************************
*
*       C Header:               XlPictograph.h
*       Subsystem:              1
*       Description:
*       %created_by:    carlo %
*       %date_created:  Wed Jun  4 15:46:20 1997 %
*
**********************************************************************/
/*
   modulo XlPictograph_h.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlPictograph_h.h	5.1
*/
/*
 * XlPictograph_h.h - file di include pubblico per l'utilizzo del widget
 *             XlPictograph
 */
#ifndef _XlPictograph_h
#define _XlPictograph_h

/*
 nomi di risorse utilizzate internamente al pictograph
 */
#define XlNpictograph  "pictograph"
#define XlCPictograph  "Pictograph"
#define XlDpictograph  "Pictograph file"

#define XlNnomeFilePict "nomeFile"
#define XlCNomeFilePict "NomeFile"
#define XlDnomeFilePict "Icon file name (.ico)"

#define XlNnomeProgram "nomeProgram"
#define XlCNomeProgram "NomeProgram"
#define XlDnomeProgram "Program file name (.prg)"

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

extern WidgetClass xlPictographWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Pictograph */
typedef struct _XlPictographClassRec *XlPictographWidgetClass;
typedef struct _XlPictographRec *XlPictographWidget;

#endif /* _XlPictograph_h */


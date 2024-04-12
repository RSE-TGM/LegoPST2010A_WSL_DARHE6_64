/**********************************************************************
*
*       C Header:               XlPixvar.h
*       Subsystem:              1
*       Description:
*       %created_by:    carlo %
*       %date_created:  Mon Nov  3 16:33:16 1997 %
*
**********************************************************************/
/*
   modulo XlPixvar_h.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlPixvar_h.h	5.1
*/
/*
 * XlPixvar_h.h - file di include pubblico per l'utilizzo del widget
 *             XlPixvar
 */
#ifndef _XlPixvar_h
#define _XlPixvar_h

/*
 nomi di risorse utilizzate internamente al pixvar
 */
#define XlNpixvar  "pixvar"
#define XlCPixvar  "Pixvar"
#define XlDpixvar  "Pixvar file"

#define XlNpixType1	"pixType1"
#define XlCpixType1	"PixType1"
#define XlDpixType1	"Select String or Pixmap"
#define XlOpixType1     "Pixmap,String"

#define XlNnomeFilePix1 "nomePix1"
#define XlCNomeFilePix1 "NomePix1"
#define XlDnomeFilePix1 "String or Pixmap file name (1)"

#define XlNpixType2	"pixType2"
#define XlCpixType2	"PixType2"
#define XlDpixType2	"Select String or Pixmap"
#define XlOpixType2     "Pixmap,String"

#define XlNnomeFilePix2 "nomePix2"
#define XlCNomeFilePix2 "NomePix2"
#define XlDnomeFilePix2 "String or Pixmap file name (2)"

#define XlNpixType3	"pixType3"
#define XlCpixType3	"PixType3"
#define XlDpixType3	"Select String or Pixmap"
#define XlOpixType3     "Pixmap,String"

#define XlNnomeFilePix3 "nomePix3"
#define XlCNomeFilePix3 "NomePix3"
#define XlDnomeFilePix3 "String or Pixmap file name (3)"

#define XlNpixType4	"pixType4"
#define XlCpixType4	"PixType4"
#define XlDpixType4	"Select String or Pixmap"
#define XlOpixType4     "Pixmap,String"

#define XlNnomeFilePix4 "nomePix4"
#define XlCNomeFilePix4 "NomePix4"
#define XlDnomeFilePix4 "String or Pixmap file name (4)"


#define XlNnomeProgram "nomeProgram"
#define XlCNomeProgram "NomeProgram"
#define XlDnomeProgram "Program file name (.prx)"

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

#define XlNcoloreDefault1  "coloreDefault1"
#define XlCColoreDefault1  "ColoreDefault1"
#define XlDcoloreDefault1 "Colore di Default"

#define XlDefaultColore1  "Blue 0.0 1"

extern WidgetClass xlPixvarWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Pixvar */
typedef struct _XlPixvarClassRec *XlPixvarWidgetClass;
typedef struct _XlPixvarRec *XlPixvarWidget;

/* definisco i tipi stringa e pixmap */
#define STR  1
#define PIX  0

#endif /* _XlPixvar_h */


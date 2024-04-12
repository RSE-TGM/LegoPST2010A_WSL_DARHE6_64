! UIMX ascii 2.5 key: 2483                                                      

*ClipBoard.class: drawingArea
*ClipBoard.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo ClipBoard.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)ClipBoard.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <Xm/Xm.h>\
#include <Xd/Xd.h>\
#include "config.h"\
\
#define VMIN 100	/*tipo di calcolo sulle coordinate */\
#define VMAX 101 \
\
XrmDatabase CuttedDb = NULL;\

*ClipBoard.ispecdecl:
*ClipBoard.funcdecl: swidget create_ClipBoard()\

*ClipBoard.funcname: create_ClipBoard
*ClipBoard.funcdef: "swidget", "<create_ClipBoard>(%)"
*ClipBoard.icode: CreaClipboardList();
*ClipBoard.fcode: return(rtrn);\

*ClipBoard.auxdecl: /*---------------------------------------------------\
 * CBQuery\
 *\
 * verifica la esistenza di oggetti nella ClipBoard\
 *--------------------------------------------------*/  \
int CBQuery(Widget **CBChild,Cardinal *CBnumChild)\
{\
   extern void get_child();\
   Cardinal lnargs;\
   Arg args[3]; \
\
   *CBnumChild=0;\
\
   lnargs = 0;\
   XtSetArg( args[lnargs],XmNchildren,CBChild);lnargs++;\
   XtSetArg(args[lnargs],XmNnumChildren,CBnumChild);lnargs++;\
   XtGetValues(ClipBoard,args,lnargs);\
\
   if(*CBnumChild)\
      return(True);\
\
   return(False);\
}\
\
\
\
/* \
 * calc\
 *\
 * calcola tra tutti gli nele valori val il massimo o il minimo \
 * e lo restituisce in ret. \
 * if type = VMIN calcola il minimo\
 * if type = VMAX calcola il massimo \
 * \
*/\
void calc(int type,Position *ret,Position *val,Cardinal nele )\
{\
   int i;\
\
   *ret = val[0];\
   \
   if(type == VMIN)\
   {\
      for(i=0;i<nele;i++)\
        if(val[i] < *ret)\
          *ret = val[i];\
   }\
   else if(type == VMAX) \
   {\
      for(i=0;i<nele;i++)\
         if(val[i] > *ret)\
            *ret = val[i]; \
   }\
}\
\
/*--------------------------------------\
 *    \
 * determina le coordinate massime e minime \
 * tra tutti gli widget presenti nella clipboard\
 *  \
 --------------------------------------*/\
int CBGetCoordWid(Position *minX,Position *minY,Position *maxX,Position *maxY)\
{\
   extern void get_child();\
   Widget *wgtlst;\
   Position *x,*y;\
   Dimension *w,*h;\
   Cardinal numChild,i;\
\
/* recupero gli widget nella CB */\
\
   if(CBQuery(&wgtlst,&numChild))\
   {\
\
      if( (x = alloca_memoria(numChild,sizeof(Position))) == NULL)\
         return(False);\
\
      if( (y = alloca_memoria(numChild,sizeof(Position))) == NULL)\
         return(False);\
\
      if( (w = alloca_memoria(numChild,sizeof(Dimension))) == NULL)\
         return(False);\
\
      if( (h = alloca_memoria(numChild,sizeof(Dimension))) == NULL)\
         return(False);\
\
      for(i=0;i<numChild;i++)\
         get_geometry(wgtlst[i],&x[i],&y[i],&w[i],&h[i]);                    \
\
/* calcolo la x e la y minima */\
      calc(VMIN,minX,x,numChild);\
      calc(VMIN,minY,y,numChild);\
\
      for(i=0;i<numChild;i++)\
      {\
         x[i] += w[i];\
         y[i] += h[i];\
      }\
\
/* calcolo la x e la y massima */      \
      calc(VMAX,maxX,x,numChild);\
      calc(VMAX,maxY,y,numChild);\
\
      libera_memoria(x);\
      libera_memoria(y);\
      libera_memoria(w);\
      libera_memoria(h);\
   \
      return(True);\
   }\
   return(False);\
}\
\

*ClipBoard.name.source: public
*ClipBoard.static: false
*ClipBoard.name: ClipBoard
*ClipBoard.parent: NO_PARENT
*ClipBoard.defaultShell: topLevelShell
*ClipBoard.resizePolicy: "resize_none"
*ClipBoard.unitType: "pixels"
*ClipBoard.x: 400
*ClipBoard.y: 220
*ClipBoard.width: 570
*ClipBoard.height: 500
*ClipBoard.marginHeight: 0
*ClipBoard.marginWidth: 0


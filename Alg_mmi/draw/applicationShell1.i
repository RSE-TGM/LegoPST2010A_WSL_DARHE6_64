! UIMX ascii 2.5 key: 1862                                                      

*applicationShell1.class: applicationShell
*applicationShell1.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo applicationShell1.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)applicationShell1.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\
#include <draw.h>\
#include <Xd/XdLista.h>\
#include <Xd/XdUndo.h>\
extern swidget create_drawShell();\
extern char *nome_file_draw;\
extern int width_draw;\
extern int height_draw;\
extern int curr_step;\
#ifndef ON_PAGEDIT\
extern Widget FinestraDraw;\
#endif
*applicationShell1.ispecdecl: XdLista lista_draget;\
XdLista lista_draget_undo;\
XdListaUndo lista_liste_undo;\
ST_DRAW_WID st_draw; /* struttura descrivente scelte correnti e\
                        di default sul disegno */
*applicationShell1.ispeclist: lista_draget, lista_draget_undo, lista_liste_undo, st_draw
*applicationShell1.ispeclist.lista_draget: "XdLista", "%lista_draget%"
*applicationShell1.ispeclist.lista_draget_undo: "XdLista", "%lista_draget_undo%"
*applicationShell1.ispeclist.lista_liste_undo: "XdListaUndo", "%lista_liste_undo%"
*applicationShell1.ispeclist.st_draw: "ST_DRAW_WID", "%st_draw%"
*applicationShell1.funcdecl: swidget create_applicationShell1()\

*applicationShell1.funcname: create_applicationShell1
*applicationShell1.funcdef: "swidget", "<create_applicationShell1>(%)"
*applicationShell1.icode: lista_draget=XdCreateLista();\
lista_draget_undo=NULL;\
lista_liste_undo=undoCreateLists();\
/*\
 Inizializza a valori di default alcuni campi della\
 struttura descrivente gli attributi del disegno\
*/\
init_st_draw(&st_draw);\

*applicationShell1.fcode: /*\
 Se Draw e' richiamato da solo crea la draw shell\
*/\
#ifndef ON_PAGEDIT\
UxPopupInterface(create_drawShell(drawingArea3,nome_file_draw),no_grab);\
/*\
 Carica il file se e' stato specificato da linea di comando\
*/\
if(nome_file_draw)\
	{\
	ReadBackground(drawingArea3,nome_file_draw);\
	DrawSetSnap(drawingArea3,curr_step);\
	if(curr_step >1)\
		set_grid_on(drawingArea3,True);\
	}\
set_something(rtrn,XmNx,0);\
set_something(rtrn,XmNy,403);\
set_something(rtrn,XmNtitle,nome_file_draw);\
#endif\
return(rtrn);\

*applicationShell1.auxdecl: XdLista get_lista(w)\
Widget w;\
{\
XdLista ret_lista;\
#ifndef DESIGN_TIME\
        _UxCapplicationShell1   *UxSaveCtx, *UxContext;\
\
        UxSaveCtx = UxApplicationShell1Context;\
        UxApplicationShell1Context = UxContext =\
                        (_UxCapplicationShell1 *) UxGetContext( w );\
#endif\
ret_lista= lista_draget;\
#ifndef DESIGN_TIME\
 UxApplicationShell1Context = UxSaveCtx;\
#endif\
return(ret_lista);\
}\
\
\
XdLista get_lista_undo(w)\
Widget w;\
{\
XdLista ret_lista;\
#ifndef DESIGN_TIME\
        _UxCapplicationShell1   *UxSaveCtx, *UxContext;\
\
        UxSaveCtx = UxApplicationShell1Context;\
        UxApplicationShell1Context = UxContext =\
                        (_UxCapplicationShell1 *) UxGetContext( w );\
#endif\
ret_lista= lista_draget_undo;\
#ifndef DESIGN_TIME\
 UxApplicationShell1Context = UxSaveCtx;\
#endif\
return(ret_lista);\
}\
\
void CreaUndoList(w)\
Widget w;\
{\
#ifndef DESIGN_TIME\
        _UxCapplicationShell1   *UxSaveCtx, *UxContext;\
\
        UxSaveCtx = UxApplicationShell1Context;\
        UxApplicationShell1Context = UxContext =\
                        (_UxCapplicationShell1 *) UxGetContext( w );\
#endif\
if(lista_draget_undo != NULL)\
        XtFree(lista_draget_undo);\
\
lista_draget_undo=XdCreateLista();\
#ifndef DESIGN_TIME\
 UxApplicationShell1Context = UxSaveCtx;\
#endif\
}\
\
\
XdListaUndo get_lista_liste_undo(w)\
Widget w;\
{\
XdListaUndo ret_lista;\
#ifndef DESIGN_TIME\
        _UxCapplicationShell1   *UxSaveCtx, *UxContext;\
\
        UxSaveCtx = UxApplicationShell1Context;\
        UxApplicationShell1Context = UxContext =\
                        (_UxCapplicationShell1 *) UxGetContext( w );\
#endif\
ret_lista= lista_liste_undo;\
#ifndef DESIGN_TIME\
 UxApplicationShell1Context = UxSaveCtx;\
#endif\
return(ret_lista);\
}\
\
\
\
/*\
 restituisce o setta una risorsa tra quelle definite\
 nella struttura descrittiva delle risorse per il widget di disegno\
 (ST_DRAW_WID) definita in draw.h (in legommi/include)\
*/ \
int gs_draw_ris(Widget w,enum ris_draw_wid ris_num, void *ret,Boolean set)\
{\
int *retint;\
GC *retGC;\
Widget *retWid;\
float *retfloat;\
Region *retreg;\
#ifndef DESIGN_TIME\
        _UxCapplicationShell1   *UxSaveCtx, *UxContext;\
\
        UxSaveCtx = UxApplicationShell1Context;\
        UxApplicationShell1Context = UxContext =\
                        (_UxCapplicationShell1 *) UxGetContext( w );\
#endif\
switch(ris_num)\
	{\
        case DR_REGION:\
        retreg=ret;\
        if(set)\
                st_draw.region=*retreg;\
        else\
                *retreg=st_draw.region;\
        break;\
\
	case DR_LINE_STYLE:\
	retint=ret;\
	if(set)\
		st_draw.line_style=*retint;\
	else\
		*retint=st_draw.line_style;\
	break;\
	case DR_LINE_WIDTH:\
	retint=ret;\
	if(set)\
		st_draw.line_width=*retint;\
	else\
		*retint=st_draw.line_width;\
	break;\
	case DR_DEF_LINE_STYLE:\
	retint=ret;\
	if(set)\
		st_draw.def_line_style=*retint;\
	else\
		*retint=st_draw.def_line_style;\
	break;\
	case DR_DEF_LINE_WIDTH:\
	retint=ret;\
	if(set)\
		st_draw.def_line_width=*retint;\
	else\
		*retint=st_draw.def_line_width;\
	break;\
	case DR_GC:\
	retGC=ret;\
	if(set)\
		st_draw.gc=*retGC;\
	else\
		*retGC= st_draw.gc;\
	break;\
	case DR_GC_BG:\
	retGC=ret;\
	if(set)\
		st_draw.gc_bg=*retGC;\
	else\
		*retGC= st_draw.gc_bg;\
	break;\
	case DR_DEF_GC:\
	retGC=ret;\
	if(set)\
		st_draw.def_gc=*retGC;\
	else\
		*retGC= st_draw.def_gc;\
	break;\
	case DR_DEF_GC_BG:\
	retGC=ret;\
	if(set)\
		st_draw.def_gc_bg=*retGC;\
	else\
		*retGC= st_draw.def_gc_bg;\
	break;\
	case DR_STEP:\
	retint=ret;\
	if(set)\
		st_draw.step= *retint;\
	else\
		*retint=st_draw.step;\
	break;\
	case DR_GRID_ON:\
	retint=ret;\
	if(set)\
		st_draw.grid_on= *retint;\
	else\
		*retint=st_draw.grid_on;\
	break;\
	case DR_DEF_FILLED:\
	retint=ret;\
	if(set)\
		st_draw.def_filled= *retint;\
	else\
		*retint=st_draw.def_filled;\
	break;\
	case DR_DEF_ZOOM:\
	retfloat=ret;\
	if(set)\
		st_draw.def_zoom=*retfloat;\
	else\
		*retfloat=st_draw.def_zoom;\
	break;\
\
	case DR_BOTT_FILL:\
	retWid=ret;\
	if(set)\
		st_draw.bott_fill= *retWid;\
	else\
		*retWid= st_draw.bott_fill;\
	break;\
\
	case DR_BOTT_BORDER:\
	retWid=ret;\
	if(set)\
		st_draw.bott_border= *retWid;\
	else\
		*retWid= st_draw.bott_border;\
	break;\
	\
	case DR_DEF_BOTT_FILL:\
	retWid=ret;\
	if(set)\
		st_draw.def_bott_fill= *retWid;\
	else\
		*retWid= st_draw.def_bott_fill;\
	break;\
	\
	case DR_DEF_BOTT_BORDER:\
	retWid=ret;\
	if(set)\
		st_draw.def_bott_border= *retWid;\
	else\
		*retWid= st_draw.def_bott_border;\
	break;\
\
	case DR_BOTT_ARROW:\
	retWid=ret;\
	if(set)\
		st_draw.bott_arrow= *retWid;\
	else\
		*retWid= st_draw.bott_arrow;\
	break;\
	}\
\
#ifndef DESIGN_TIME\
 UxApplicationShell1Context = UxSaveCtx;\
#endif\
return(ret);\
}
*applicationShell1.static: true
*applicationShell1.name: applicationShell1
*applicationShell1.parent: NO_PARENT
*applicationShell1.x: 0
*applicationShell1.y: 403
*applicationShell1.width: 606
*applicationShell1.height: 520
*applicationShell1.title: "Editing Animated Icon"
*applicationShell1.iconName: "Editing Animated Icon"

*mainWindow1.class: mainWindow
*mainWindow1.static: true
*mainWindow1.name: mainWindow1
*mainWindow1.parent: applicationShell1
*mainWindow1.unitType: "pixels"
*mainWindow1.width: 491
*mainWindow1.height: 450

*scrolledWindow1.class: scrolledWindow
*scrolledWindow1.static: true
*scrolledWindow1.name: scrolledWindow1
*scrolledWindow1.parent: mainWindow1
*scrolledWindow1.scrollingPolicy: "automatic"

*drawingArea3.class: drawingArea
*drawingArea3.static: true
*drawingArea3.name: drawingArea3
*drawingArea3.parent: scrolledWindow1
*drawingArea3.resizePolicy: "resize_none"
*drawingArea3.x: 4
*drawingArea3.y: 4
*drawingArea3.width: XDisplayWidth(UxDisplay,UxScreen)
*drawingArea3.height: XDisplayHeight(UxDisplay,UxScreen)

*DrawMainMenu.class: rowColumn
*DrawMainMenu.static: true
*DrawMainMenu.name: DrawMainMenu
*DrawMainMenu.parent: drawingArea3
*DrawMainMenu.rowColumnType: "menu_popup"
*DrawMainMenu.menuAccelerator: "<KeyUp>F4"

*menu1_p1_title.class: label
*menu1_p1_title.static: true
*menu1_p1_title.name: menu1_p1_title
*menu1_p1_title.parent: DrawMainMenu
*menu1_p1_title.labelString: "Edit menu"

*UndoButton.class: pushButton
*UndoButton.static: true
*UndoButton.name: UndoButton
*UndoButton.parent: DrawMainMenu
*UndoButton.labelString: "Undo"
*UndoButton.mnemonic: "U"
*UndoButton.activateCallback: {\
#ifndef ON_PAGEDIT\
\
extern int undo_draget_paste();\
\
/* undo sulla ultima operazione effettuata\
*/\
\
undo_draget_paste( FinestraDraw );\
\
#endif\
\
}\
\


*DuplicateButton.class: pushButton
*DuplicateButton.static: true
*DuplicateButton.name: DuplicateButton
*DuplicateButton.parent: DrawMainMenu
*DuplicateButton.labelString: "Duplicate"
*DuplicateButton.activateCallback: {\
int dx,dy;\
extern int curr_step;\
\
if(curr_step > 1)\
	dx=dy=curr_step;\
else\
	dx=dy=5;\
\
#ifndef ON_PAGEDIT\
draget_duplicate(FinestraDraw,dx,dy);\
#endif\
}

*CutButton.class: pushButton
*CutButton.static: true
*CutButton.name: CutButton
*CutButton.parent: DrawMainMenu
*CutButton.labelString: "Cut"
*CutButton.activateCallback: {\
#ifndef ON_PAGEDIT\
draget_cut(FinestraDraw);\
#endif\
}

*CopyButton.class: pushButton
*CopyButton.static: true
*CopyButton.name: CopyButton
*CopyButton.parent: DrawMainMenu
*CopyButton.labelString: "Copy"
*CopyButton.activateCallback: {\
#ifndef ON_PAGEDIT\
draget_copy(FinestraDraw);\
#endif\
}

*PasteButton.class: pushButton
*PasteButton.static: true
*PasteButton.name: PasteButton
*PasteButton.parent: DrawMainMenu
*PasteButton.labelString: "Paste"
*PasteButton.activateCallback: {\
#ifndef ON_PAGEDIT\
draget_paste(FinestraDraw);\
#endif\
}

*DeleteButton.class: pushButton
*DeleteButton.static: true
*DeleteButton.name: DeleteButton
*DeleteButton.parent: DrawMainMenu
*DeleteButton.labelString: "Delete"
*DeleteButton.activateCallback: {\
#ifndef ON_PAGEDIT\
DrawDelete(FinestraDraw, NULL);\
#endif\
}

*Separator_b9.class: separator
*Separator_b9.static: true
*Separator_b9.name: Separator_b9
*Separator_b9.parent: DrawMainMenu

*TopButton.class: pushButton
*TopButton.static: true
*TopButton.name: TopButton
*TopButton.parent: DrawMainMenu
*TopButton.labelString: "Put Top"
*TopButton.activateCallback: {\
#ifndef ON_PAGEDIT\
DrawPutTop(FinestraDraw);\
#endif\
}

*BottomButton.class: pushButton
*BottomButton.static: true
*BottomButton.name: BottomButton
*BottomButton.parent: DrawMainMenu
*BottomButton.labelString: "Put Bottom"
*BottomButton.activateCallback: {\
#ifndef ON_PAGEDIT\
DrawPutBottom(FinestraDraw);\
#endif\
}

*Separator_b12.class: separator
*Separator_b12.static: true
*Separator_b12.name: Separator_b12
*Separator_b12.parent: DrawMainMenu

*GroupButton.class: pushButton
*GroupButton.static: true
*GroupButton.name: GroupButton
*GroupButton.parent: DrawMainMenu
*GroupButton.labelString: "Group"
*GroupButton.activateCallback: {\
DrawGroup(FinestraDraw);\
}

*UngroupButton.class: pushButton
*UngroupButton.static: true
*UngroupButton.name: UngroupButton
*UngroupButton.parent: DrawMainMenu
*UngroupButton.labelString: "Ungroup"
*UngroupButton.activateCallback: {\
DrawUngroup(FinestraDraw);\
}


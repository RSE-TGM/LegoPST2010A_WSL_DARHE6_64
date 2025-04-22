! UIMX ascii 2.5 key: 9814                                                      

*translation.table: lineTable
*translation.parent: drawShell
*translation.policy: replace
*translation.<Btn1Down>: first_point_line()
*translation.<Btn1Motion>: draw_draget()
*translation.<Btn1Up>: end_draw_draget()
*translation.<Key>F5: draw_delete()
*translation.<Key>Left: move_tasti()
*translation.<Key>Right: move_tasti()
*translation.<Key>Up: move_tasti()
*translation.<Key>Down: move_tasti()

*translation.table: rectTable
*translation.parent: drawShell
*translation.policy: replace
*translation.<Btn1Down>: first_point_rect()
*translation.<Btn1Motion>: draw_draget()
*translation.<Btn1Up>: end_draw_draget()
*translation.<Key>F5: draw_delete()
*translation.<Key>Left: move_tasti()
*translation.<Key>Right: move_tasti()
*translation.<Key>Up: move_tasti()
*translation.<Key>Down: move_tasti()

*translation.table: circleTable
*translation.parent: drawShell
*translation.policy: replace
*translation.<Btn1Down>: first_point_circle()
*translation.<Btn1Motion>: draw_draget()
*translation.<Btn1Up>: end_draw_draget()
*translation.<Key>F5: draw_delete()
*translation.<Key>Left: move_tasti()
*translation.<Key>Right: move_tasti()
*translation.<Key>Up: move_tasti()
*translation.<Key>Down: move_tasti()

*translation.table: arcTable
*translation.parent: drawShell
*translation.policy: replace
*translation.<Btn1Down>: first_point_arc()
*translation.<Btn1Motion>: draw_draget()
*translation.<Btn1Up>: end_draw_draget()
*translation.<Key>F5: draw_delete()
*translation.<Key>Left: move_tasti()
*translation.<Key>Right: move_tasti()
*translation.<Key>Up: move_tasti()
*translation.<Key>Down: move_tasti()

*translation.table: poliTable
*translation.parent: drawShell
*translation.policy: replace
*translation.<Btn1Down>: first_point_poli()
*translation.<Btn2Down>: end_draw_draget()
*translation.<Key>F5: draw_delete()
*translation.<Motion>: draw_draget()
*translation.<Key>Left: move_tasti()
*translation.<Key>Right: move_tasti()
*translation.<Key>Up: move_tasti()
*translation.<Key>Down: move_tasti()
*translation.<Btn3Down>: end_draw_draget()

*translation.table: textTable
*translation.parent: drawShell
*translation.policy: replace
*translation.<Btn1Down>: nothing()
*translation.<Btn1Motion>: nothing()
*translation.<Btn1Up>: first_text()
*translation.<Key>Return: next_line()
*translation.<Key>: draw_text()

*translation.table: pickTable
*translation.parent: drawShell
*translation.policy: replace
*translation.<Key>F5: draw_delete()
*translation.~Shift<Btn1Down>: start_pick()
*translation.<Btn1Motion>: move_pick()
*translation.<Btn1Up>: end_pick()
*translation.Shift<Btn1Down>: ext_pick()
*translation.~Shift<Btn2Down>: start_pick()
*translation.<Btn2Motion>: move_pick()
*translation.<Btn2Up>: end_pick()
*translation.<Key>Left: move_tasti()
*translation.<Key>Right: move_tasti()
*translation.<Key>Up: move_tasti()
*translation.<Key>Down: move_tasti()

*translation.table: freeTable
*translation.parent: drawShell
*translation.policy: replace
*translation.<Btn1Down>: first_point_poli()
*translation.<Btn2Down>: end_draw_draget()
*translation.<Key>F5: draw_delete()
*translation.<Btn1Motion>: first_point_poli()
*translation.<Motion>: draw_draget()
*translation.<Key>Left: move_tasti()
*translation.<Key>Right: move_tasti()
*translation.<Key>Up: move_tasti()
*translation.<Key>Down: move_tasti()

*drawShell.class: topLevelShell
*drawShell.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo drawShell.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)drawShell.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\
#include <draw.h>\
#ifndef DESIGN_TIME\
#include <math.h>\
#endif\
#include "res_edit.h"\
extern Boolean saving;\
extern swidget drawFsBD;\
extern swidget fileSelectionBox;\
extern swidget drawExitD;\
extern swidget create_drawFsBD();\
extern swidget create_drawExitD();\
extern swidget create_SaveSelection();\
extern char *nome_file_draw;\
extern Widget FinestraDraw;\
\
int curr_line_style;\
int curr_line_width;\
int curr_step=1;\
int grid_on=0;\
Window win_step; /* window su cui effettuare lo step */\
#ifndef ON_PAGEDIT\
Widget FinestraDraw;\
#endif
*drawShell.ispecdecl: swidget draw_wid;\
char str_title[150];\
XrmDatabase RisDbColori;\
swidget vett_colori[32];\
swidget *vett_fill;  /* punta all'inizio dei colori per fill */\
swidget *vett_border; /* punta all'inizio dei colori per bordo */\
swidget vett_draw[9];\

*drawShell.ispeclist: draw_wid, str_title, RisDbColori, vett_colori, vett_fill, vett_border, vett_draw
*drawShell.ispeclist.draw_wid: "swidget", "%draw_wid%"
*drawShell.ispeclist.str_title: "unsigned char", "%str_title%[150]"
*drawShell.ispeclist.RisDbColori: "XrmDatabase", "%RisDbColori%"
*drawShell.ispeclist.vett_colori: "swidget", "%vett_colori%[32]"
*drawShell.ispeclist.vett_fill: "swidget", "*%vett_fill%"
*drawShell.ispeclist.vett_border: "swidget", "*%vett_border%"
*drawShell.ispeclist.vett_draw: "swidget", "%vett_draw%[9]"
*drawShell.funcdecl: swidget create_drawShell(passed_wid,nome)\
swidget passed_wid;\
char *nome;\

*drawShell.funcname: create_drawShell
*drawShell.funcdef: "swidget", "<create_drawShell>(%)"
*drawShell.argdecl: swidget passed_wid;\
unsigned char *nome;
*drawShell.arglist: passed_wid, nome
*drawShell.arglist.passed_wid: "swidget", "%passed_wid%"
*drawShell.arglist.nome: "unsigned char", "*%nome%"
*drawShell.icode: draw_wid=passed_wid;\
#ifndef ON_PAGEDIT\
FinestraDraw = draw_wid;\
#endif\
win_step=XtWindow(draw_wid);\
curr_line_style= LineSolid;\
curr_line_width= 0;\
#ifdef ON_PAGEDIT\
printf("\n deselez draget\n");\
DeselectAllDraget(draw_wid,True);\
#else\
append_redraw(draw_wid);\
#endif\
RisDbColori = XrmGetFileDatabase("FileColoriDefault");\
UxDisplay->db = RisDbColori;\

*drawShell.fcode: vett_fill=&vett_colori[16];\
vett_border=&vett_colori[0];\
load_vett_draw();\
load_vett_colors();\
set_fill_colors();\
/*\
 memorizza nella struttura di draw wid i bottoni in selezione\
 corrente per i colori ed il bottone di arrow\
*/\
set_bott_border(draw_wid,vett_border[0]);\
set_bott_fill(draw_wid,vett_fill[0]);\
set_bott_arrow(draw_wid,vett_draw[0]);\
set_def_bott_border(draw_wid,vett_border[0]);\
set_def_bott_fill(draw_wid,vett_border[1]);\
/*\
 seleziona i bottoni graficamente\
*/\
selez_bott_border(0);\
selez_bott_fill(1);\
set_arrow_mode(draw_wid);\
set_current_gcs(draw_wid);\
#ifndef ON_PAGEDIT\
strcpy(str_title,"DRAW - on animated icon: ");\
strcat(str_title,nome);\
#else\
/*\
 Caso di utilizzo del Draw all'interno del PAGEDIT\
 - il titolo specifica su quale pagina si sta lavorando\
 - vengono disabilitati i menu di File Edit e View che sono\
   in parte riportati direttamente sulla pagina di pagedit\
*/\
strcpy(str_title,"DRAW - on page: ");\
strcat(str_title,nome);\
set_something(saveButton,XmNsensitive, False);\
set_something(saveAsButton, XmNsensitive, False);\
set_something(editCascade,XmNsensitive, False);\
set_something(viewCascade,XmNsensitive, False);\
#endif\
#if defined ON_PAGEDIT || !defined XPRINTER_USED\
set_something(prtButton,XmNsensitive, False);\
set_something(prtSetupButton, XmNsensitive, False);\
#endif\
set_something(rtrn,XmNtitle,str_title);\
return(rtrn);\

*drawShell.auxdecl: load_vett_colors()\
{\
vett_border[0]=drawnButton1;\
vett_border[1]=drawnButton2;\
vett_border[2]=drawnButton3;\
vett_border[3]=drawnButton4;\
vett_border[4]=drawnButton5;\
vett_border[5]=drawnButton6;\
vett_border[6]=drawnButton7;\
vett_border[7]=drawnButton8;\
vett_border[8]=drawnButton9;\
vett_border[9]=drawnButton10;\
vett_border[10]=drawnButton11;\
vett_border[11]=drawnButton12;\
vett_border[12]=drawnButton13;\
vett_border[13]=drawnButton14;\
vett_border[14]=drawnButton15;\
vett_border[15]=drawnButton16;\
\
vett_fill[0]=sdrawnButton1;\
vett_fill[1]=sdrawnButton2;\
vett_fill[2]=sdrawnButton3;\
vett_fill[3]=sdrawnButton4;\
vett_fill[4]=sdrawnButton5;\
vett_fill[5]=sdrawnButton6;\
vett_fill[6]=sdrawnButton7;\
vett_fill[7]=sdrawnButton8;\
vett_fill[8]=sdrawnButton9;\
vett_fill[9]=sdrawnButton10;\
vett_fill[10]=sdrawnButton11;\
vett_fill[11]=sdrawnButton12;\
vett_fill[12]=sdrawnButton13;\
vett_fill[13]=sdrawnButton14;\
vett_fill[14]=sdrawnButton15;\
vett_fill[15]=sdrawnButton16;\
\
}\
\
load_vett_draw()\
{\
int i;\
Pixmap vett_pix[8];\
\
vett_draw[0]= arrow_bt;\
vett_draw[1]= zoom_bt;\
vett_draw[2]= drawline_bt;\
vett_draw[3]= drawrect_bt;\
vett_draw[4]= drawcircle_bt;\
vett_draw[5]= drawarc_bt;\
vett_draw[6]= drawpoli_bt;\
vett_draw[7]= drawfree_bt;\
LoadDrawPixmap(vett_pix,vett_draw[0]);\
for(i=0; i<8 ; i++)\
	set_something(vett_draw[i],XmNlabelPixmap,vett_pix[i]);\
}\
\
\
set_fill_colors()\
{\
Pixel pixel;\
int i;\
\
for(i=0; i< 12; i++)\
	{\
	get_something(vett_border[i],XmNbackground,(char*)&pixel);\
	set_something(vett_fill[i],XmNbackground,(char*)pixel);\
	get_something(vett_border[i],XmNtopShadowColor,(char*)&pixel);\
	set_something(vett_fill[i],XmNtopShadowColor,(char*)pixel);\
	get_something(vett_border[i],XmNbottomShadowColor,(char*)&pixel);\
	set_something(vett_fill[i],XmNbottomShadowColor,(char*)pixel);\
	\
	}\
}\
\
selez_bott_fill(indice)\
int indice;\
{\
wselez_bott_fill(vett_fill[indice]);\
set_current_gcs(draw_wid); \
}\
\
selez_bott_border(indice)\
int indice;\
{\
wselez_bott_border(vett_border[indice]);\
set_current_gcs(draw_wid); \
}\
\
selez_bott_draw(indice)\
int indice;\
{\
int i;\
for(i=0; i< 8; i++)\
	{\
	set_something( vett_draw[i], XmNshadowType, XmSHADOW_OUT);\
	}\
set_something( vett_draw[indice], XmNshadowType, XmSHADOW_IN);\
}\
\
wselez_bott_fill(wid)\
swidget wid;\
{\
int i;\
for(i=0; i< 16; i++)\
	{\
	set_something( vett_fill[i], XmNshadowThickness, 2);\
	set_something( vett_fill[i], XmNshadowType, XmSHADOW_ETCHED_IN);\
	}\
set_something( wid , XmNshadowType, XmSHADOW_IN);\
set_something( wid , XmNshadowThickness, 4);\
/* bott_fill_selected=wid; */\
set_bott_fill(draw_wid,wid);\
}\
\
wselez_bott_border(wid)\
swidget wid;\
{\
int i;\
for(i=0; i< 16; i++)\
	{\
	set_something( vett_border[i], XmNshadowThickness, 2);\
	set_something( vett_border[i], XmNshadowType, XmSHADOW_ETCHED_IN);\
	}\
set_something( wid, XmNshadowThickness, 4);\
set_something( wid, XmNshadowType, XmSHADOW_IN);\
/* bott_border_selected = wid; */\
set_bott_border(draw_wid,wid);\
}\
\
reset_line_def(line_width,line_style,wid)\
int line_width,line_style;\
Widget wid;\
{\
#ifndef DESIGN_TIME\
_UxCdrawShell           *UxSaveCtx, *UxContext;\
UxSaveCtx = UxDrawShellContext;\
UxDrawShellContext = UxContext =\
                        (_UxCdrawShell *) UxGetContext( wid );\
#endif\
switch (line_width)\
	{\
	case 0:\
		set_something(thiny_bt, XmNset, True);\
		set_something(pix_1_bt, XmNset, False);\
		set_something(pix_2_bt, XmNset, False);\
		set_something(pix_3_bt, XmNset, False);\
		set_something(pix_6_bt, XmNset, False);\
	break;\
	case 1:\
		set_something(thiny_bt, XmNset, False);\
		set_something(pix_1_bt, XmNset, True);\
		set_something(pix_2_bt, XmNset, False);\
		set_something(pix_3_bt, XmNset, False);\
		set_something(pix_6_bt, XmNset, False);\
	break;\
	case 2:\
		set_something(thiny_bt, XmNset, False);\
		set_something(pix_1_bt, XmNset, False);\
		set_something(pix_2_bt, XmNset, True);\
		set_something(pix_3_bt, XmNset, False);\
		set_something(pix_6_bt, XmNset, False);\
	break;\
	case 3:\
		set_something(thiny_bt, XmNset, False);\
		set_something(pix_1_bt, XmNset, False);\
		set_something(pix_2_bt, XmNset, False);\
		set_something(pix_3_bt, XmNset, True);\
		set_something(pix_6_bt, XmNset, False);\
	break;\
	case 4:\
		set_something(thiny_bt, XmNset, False);\
		set_something(pix_1_bt, XmNset, False);\
		set_something(pix_2_bt, XmNset, False);\
		set_something(pix_3_bt, XmNset, False);\
		set_something(pix_6_bt, XmNset, True);\
	break;\
	}\
\
switch (line_style)\
	{\
	case LineSolid:\
		set_something(solid_bt, XmNset, True);\
		set_something(dashed_bt, XmNset, False);\
	break;\
	case LineOnOffDash:\
		set_something(solid_bt, XmNset, False);\
		set_something(dashed_bt, XmNset, True);\
	break;\
	}\
#ifndef DESIGN_TIME\
UxDrawShellContext = UxSaveCtx;\
#endif\
}\
\
\
set_draw_translations(wid)\
Widget wid;  /* widget della drawing area */\
{\
#ifndef DESIGN_TIME\
        add_def_translation(wid, pickTable);\
#endif\
}\
\
set_arrow_mode(wid)\
Widget wid;\
{\
Widget wbottone;\
#ifndef DESIGN_TIME\
_UxCdrawShell           *UxSaveCtx, *UxContext;\
#endif\
/*\
        Riporta Draw nella modalita' puntatore per selezione\
*/\
set_draw_translations(wid);\
\
#ifdef ON_PAGEDIT\
        aggiungi_pagedit_translation(wid);\
#endif\
\
/*\
 seleziona il bottone con la freccia\
 (attenzione !! la routine puo' essere stata chiamata da un'altra\
 interfaccia)\
*/\
/*\
 1. ricava l'indice di widget del bottone\
*/\
wbottone =  get_bott_arrow(wid);\
/*\
 2. esegue uno switch del context settando il context\
    di appartenenza del bottone-freccia\
*/\
#ifndef DESIGN_TIME\
UxSaveCtx = UxDrawShellContext;\
UxDrawShellContext = UxContext =\
                        (_UxCdrawShell *) UxGetContext( wbottone );\
#endif\
\
/*\
 3. seleziona graficamente il bottone\
 */\
selez_bott_draw(0);\
/*\
 4. ripristina il context\
*/\
#ifndef DESIGN_TIME\
UxDrawShellContext = UxSaveCtx;\
#endif\
}\
\

*drawShell.name.source: public
*drawShell.static: false
*drawShell.name: drawShell
*drawShell.parent: NO_PARENT
*drawShell.parentExpression: passed_wid
*drawShell.x: 0
*drawShell.y: 169
*drawShell.width: 606
*drawShell.height: 190
*drawShell.allowShellResize: "false"

*mainWindow.class: mainWindow
*mainWindow.static: true
*mainWindow.name: mainWindow
*mainWindow.parent: drawShell
*mainWindow.height: 190
*mainWindow.width: 606

*workAreaMgr.class: drawingArea
*workAreaMgr.static: true
*workAreaMgr.name: workAreaMgr
*workAreaMgr.parent: mainWindow
*workAreaMgr.marginHeight: 0
*workAreaMgr.marginWidth: 0

*workFrame.class: frame
*workFrame.static: true
*workFrame.name: workFrame
*workFrame.parent: workAreaMgr
*workFrame.x: 0
*workFrame.y: 0
*workFrame.width: 600
*workFrame.height: 496

*workDrArea.class: drawingArea
*workDrArea.static: true
*workDrArea.name: workDrArea
*workDrArea.parent: workFrame
*workDrArea.x: 2
*workDrArea.y: 2
*workDrArea.width: 588
*workDrArea.height: 148
*workDrArea.marginHeight: 0
*workDrArea.marginWidth: 0
*workDrArea.resizePolicy: "resize_none"

*drawline_bt.class: drawnButton
*drawline_bt.static: true
*drawline_bt.name: drawline_bt
*drawline_bt.parent: workDrArea
*drawline_bt.x: 110
*drawline_bt.y: 100
*drawline_bt.width: 60
*drawline_bt.height: 50
*drawline_bt.labelType: "pixmap"
*drawline_bt.activateCallback: {\
add_def_translation(draw_wid,  lineTable);\
#ifdef ON_PAGEDIT\
aggiungi_pagedit_translation(draw_wid);\
#endif\
selez_bott_draw(2);\
}
*drawline_bt.shadowThickness: 2
*drawline_bt.shadowType: "shadow_out"
*drawline_bt.recomputeSize: "true"

*drawrect_bt.class: drawnButton
*drawrect_bt.static: true
*drawrect_bt.name: drawrect_bt
*drawrect_bt.parent: workDrArea
*drawrect_bt.x: 160
*drawrect_bt.y: 100
*drawrect_bt.width: 76
*drawrect_bt.height: 76
*drawrect_bt.labelType: "pixmap"
*drawrect_bt.activateCallback: {\
add_def_translation(draw_wid, rectTable);\
#ifdef ON_PAGEDIT\
aggiungi_pagedit_translation(draw_wid);\
#endif\
selez_bott_draw(3);\
}
*drawrect_bt.shadowThickness: 2
*drawrect_bt.shadowType: "shadow_out"
*drawrect_bt.recomputeSize: "true"

*drawcircle_bt.class: drawnButton
*drawcircle_bt.static: true
*drawcircle_bt.name: drawcircle_bt
*drawcircle_bt.parent: workDrArea
*drawcircle_bt.x: 210
*drawcircle_bt.y: 100
*drawcircle_bt.width: 76
*drawcircle_bt.height: 76
*drawcircle_bt.labelType: "pixmap"
*drawcircle_bt.activateCallback: {\
add_def_translation(draw_wid, circleTable);\
#ifdef ON_PAGEDIT\
aggiungi_pagedit_translation(draw_wid);\
#endif\
selez_bott_draw(4);\
}
*drawcircle_bt.shadowThickness: 2
*drawcircle_bt.shadowType: "shadow_out"
*drawcircle_bt.recomputeSize: "true"

*drawpoli_bt.class: drawnButton
*drawpoli_bt.static: true
*drawpoli_bt.name: drawpoli_bt
*drawpoli_bt.parent: workDrArea
*drawpoli_bt.x: 310
*drawpoli_bt.y: 100
*drawpoli_bt.width: 76
*drawpoli_bt.height: 76
*drawpoli_bt.labelType: "pixmap"
*drawpoli_bt.activateCallback: {\
add_def_translation(draw_wid, poliTable);\
#ifdef ON_PAGEDIT\
aggiungi_pagedit_translation(draw_wid);\
#endif\
selez_bott_draw(6);\
}
*drawpoli_bt.shadowThickness: 2
*drawpoli_bt.shadowType: "shadow_out"
*drawpoli_bt.recomputeSize: "true"

*drawfree_bt.class: drawnButton
*drawfree_bt.static: true
*drawfree_bt.name: drawfree_bt
*drawfree_bt.parent: workDrArea
*drawfree_bt.x: 360
*drawfree_bt.y: 100
*drawfree_bt.width: 76
*drawfree_bt.height: 76
*drawfree_bt.labelType: "pixmap"
*drawfree_bt.activateCallback: {\
add_def_translation(draw_wid, freeTable);\
#ifdef ON_PAGEDIT\
aggiungi_pagedit_translation(draw_wid);\
#endif\
selez_bott_draw(7);\
}
*drawfree_bt.shadowThickness: 2
*drawfree_bt.shadowType: "shadow_out"
*drawfree_bt.recomputeSize: "true"

*frame1.class: frame
*frame1.static: true
*frame1.name: frame1
*frame1.parent: workDrArea
*frame1.x: 8
*frame1.y: 51
*frame1.width: 562
*frame1.height: 41
*frame1.shadowType: "shadow_etched_in"

*drawingArea1.class: drawingArea
*drawingArea1.static: true
*drawingArea1.name: drawingArea1
*drawingArea1.parent: frame1
*drawingArea1.resizePolicy: "resize_none"
*drawingArea1.x: 2
*drawingArea1.y: 2
*drawingArea1.width: 558
*drawingArea1.height: 38
*drawingArea1.marginHeight: 2
*drawingArea1.marginWidth: 2

*sdrawnButton1.class: drawnButton
*sdrawnButton1.static: true
*sdrawnButton1.name: sdrawnButton1
*sdrawnButton1.parent: drawingArea1
*sdrawnButton1.x: 76
*sdrawnButton1.y: 2
*sdrawnButton1.width: 30
*sdrawnButton1.height: 30
*sdrawnButton1.labelString: " "
*sdrawnButton1.activateCallback: {\
selez_bott_fill(0);\
}
*sdrawnButton1.shadowThickness: 2
*sdrawnButton1.recomputeSize: "false"

*sdrawnButton2.class: drawnButton
*sdrawnButton2.static: true
*sdrawnButton2.name: sdrawnButton2
*sdrawnButton2.parent: drawingArea1
*sdrawnButton2.x: 106
*sdrawnButton2.y: 2
*sdrawnButton2.width: 30
*sdrawnButton2.height: 30
*sdrawnButton2.labelString: " "
*sdrawnButton2.activateCallback: {\
selez_bott_fill(1);\
}
*sdrawnButton2.recomputeSize: "false"

*sdrawnButton3.class: drawnButton
*sdrawnButton3.static: true
*sdrawnButton3.name: sdrawnButton3
*sdrawnButton3.parent: drawingArea1
*sdrawnButton3.x: 136
*sdrawnButton3.y: 2
*sdrawnButton3.width: 30
*sdrawnButton3.height: 30
*sdrawnButton3.labelString: " "
*sdrawnButton3.activateCallback: {\
selez_bott_fill(2);\
}
*sdrawnButton3.recomputeSize: "false"

*sdrawnButton4.class: drawnButton
*sdrawnButton4.static: true
*sdrawnButton4.name: sdrawnButton4
*sdrawnButton4.parent: drawingArea1
*sdrawnButton4.x: 166
*sdrawnButton4.y: 2
*sdrawnButton4.width: 30
*sdrawnButton4.height: 30
*sdrawnButton4.labelString: " "
*sdrawnButton4.activateCallback: {\
selez_bott_fill(3);\
}
*sdrawnButton4.recomputeSize: "false"

*sdrawnButton5.class: drawnButton
*sdrawnButton5.static: true
*sdrawnButton5.name: sdrawnButton5
*sdrawnButton5.parent: drawingArea1
*sdrawnButton5.x: 196
*sdrawnButton5.y: 2
*sdrawnButton5.width: 30
*sdrawnButton5.height: 30
*sdrawnButton5.labelString: " "
*sdrawnButton5.activateCallback: {\
selez_bott_fill(4);\
}
*sdrawnButton5.recomputeSize: "false"

*sdrawnButton6.class: drawnButton
*sdrawnButton6.static: true
*sdrawnButton6.name: sdrawnButton6
*sdrawnButton6.parent: drawingArea1
*sdrawnButton6.x: 226
*sdrawnButton6.y: 2
*sdrawnButton6.width: 30
*sdrawnButton6.height: 30
*sdrawnButton6.labelString: " "
*sdrawnButton6.activateCallback: {\
selez_bott_fill(5);\
}
*sdrawnButton6.recomputeSize: "false"

*sdrawnButton7.class: drawnButton
*sdrawnButton7.static: true
*sdrawnButton7.name: sdrawnButton7
*sdrawnButton7.parent: drawingArea1
*sdrawnButton7.x: 256
*sdrawnButton7.y: 2
*sdrawnButton7.width: 30
*sdrawnButton7.height: 30
*sdrawnButton7.labelString: " "
*sdrawnButton7.activateCallback: {\
selez_bott_fill(6);\
}
*sdrawnButton7.recomputeSize: "false"

*sdrawnButton8.class: drawnButton
*sdrawnButton8.static: true
*sdrawnButton8.name: sdrawnButton8
*sdrawnButton8.parent: drawingArea1
*sdrawnButton8.x: 286
*sdrawnButton8.y: 2
*sdrawnButton8.width: 30
*sdrawnButton8.height: 30
*sdrawnButton8.labelString: " "
*sdrawnButton8.activateCallback: {\
selez_bott_fill(7);\
}
*sdrawnButton8.recomputeSize: "false"

*sdrawnButton9.class: drawnButton
*sdrawnButton9.static: true
*sdrawnButton9.name: sdrawnButton9
*sdrawnButton9.parent: drawingArea1
*sdrawnButton9.x: 316
*sdrawnButton9.y: 2
*sdrawnButton9.width: 30
*sdrawnButton9.height: 30
*sdrawnButton9.labelString: " "
*sdrawnButton9.activateCallback: {\
selez_bott_fill(8);\
}
*sdrawnButton9.recomputeSize: "false"

*sdrawnButton10.class: drawnButton
*sdrawnButton10.static: true
*sdrawnButton10.name: sdrawnButton10
*sdrawnButton10.parent: drawingArea1
*sdrawnButton10.x: 346
*sdrawnButton10.y: 2
*sdrawnButton10.width: 30
*sdrawnButton10.height: 30
*sdrawnButton10.labelString: " "
*sdrawnButton10.activateCallback: {\
selez_bott_fill(9);\
}
*sdrawnButton10.recomputeSize: "false"

*sdrawnButton11.class: drawnButton
*sdrawnButton11.static: true
*sdrawnButton11.name: sdrawnButton11
*sdrawnButton11.parent: drawingArea1
*sdrawnButton11.x: 376
*sdrawnButton11.y: 2
*sdrawnButton11.width: 30
*sdrawnButton11.height: 30
*sdrawnButton11.labelString: " "
*sdrawnButton11.activateCallback: {\
selez_bott_fill(10);\
}
*sdrawnButton11.recomputeSize: "false"

*sdrawnButton12.class: drawnButton
*sdrawnButton12.static: true
*sdrawnButton12.name: sdrawnButton12
*sdrawnButton12.parent: drawingArea1
*sdrawnButton12.x: 406
*sdrawnButton12.y: 2
*sdrawnButton12.width: 30
*sdrawnButton12.height: 30
*sdrawnButton12.labelString: " "
*sdrawnButton12.activateCallback: {\
selez_bott_fill(11);\
}
*sdrawnButton12.recomputeSize: "false"

*sdrawnButton13.class: drawnButton
*sdrawnButton13.static: true
*sdrawnButton13.name: sdrawnButton13
*sdrawnButton13.parent: drawingArea1
*sdrawnButton13.x: 434
*sdrawnButton13.y: 0
*sdrawnButton13.width: 30
*sdrawnButton13.height: 30
*sdrawnButton13.background: "#dddddd"
*sdrawnButton13.labelString: "1"
*sdrawnButton13.activateCallback: {\
selez_bott_fill(12);\
}
*sdrawnButton13.recomputeSize: "false"

*sdrawnButton14.class: drawnButton
*sdrawnButton14.static: true
*sdrawnButton14.name: sdrawnButton14
*sdrawnButton14.parent: drawingArea1
*sdrawnButton14.x: 464
*sdrawnButton14.y: 2
*sdrawnButton14.width: 30
*sdrawnButton14.height: 30
*sdrawnButton14.background: "#bbbbbb"
*sdrawnButton14.labelString: "2"
*sdrawnButton14.activateCallback: {\
selez_bott_fill(13);\
}
*sdrawnButton14.recomputeSize: "false"

*sdrawnButton15.class: drawnButton
*sdrawnButton15.static: true
*sdrawnButton15.name: sdrawnButton15
*sdrawnButton15.parent: drawingArea1
*sdrawnButton15.x: 494
*sdrawnButton15.y: 2
*sdrawnButton15.width: 30
*sdrawnButton15.height: 30
*sdrawnButton15.background: "#999999"
*sdrawnButton15.labelString: "3"
*sdrawnButton15.activateCallback: {\
selez_bott_fill(14);\
}
*sdrawnButton15.recomputeSize: "false"

*sdrawnButton16.class: drawnButton
*sdrawnButton16.static: true
*sdrawnButton16.name: sdrawnButton16
*sdrawnButton16.parent: drawingArea1
*sdrawnButton16.x: 524
*sdrawnButton16.y: 2
*sdrawnButton16.width: 30
*sdrawnButton16.height: 30
*sdrawnButton16.background: "#777777"
*sdrawnButton16.labelString: "4"
*sdrawnButton16.activateCallback: {\
selez_bott_fill(15);\
}
*sdrawnButton16.recomputeSize: "false"

*label2.class: label
*label2.static: true
*label2.name: label2
*label2.parent: drawingArea1
*label2.x: 7
*label2.y: 4
*label2.width: 62
*label2.height: 24
*label2.labelString: "Fill Color"

*frame2.class: frame
*frame2.static: true
*frame2.name: frame2
*frame2.parent: workDrArea
*frame2.x: 7
*frame2.y: 10
*frame2.width: 562
*frame2.height: 40

*drawingArea2.class: drawingArea
*drawingArea2.static: true
*drawingArea2.name: drawingArea2
*drawingArea2.parent: frame2
*drawingArea2.resizePolicy: "resize_none"
*drawingArea2.x: 2
*drawingArea2.y: 2
*drawingArea2.width: 558
*drawingArea2.height: 38
*drawingArea2.marginHeight: 2
*drawingArea2.marginWidth: 2

*drawnButton1.class: drawnButton
*drawnButton1.static: true
*drawnButton1.name: drawnButton1
*drawnButton1.parent: drawingArea2
*drawnButton1.x: 74
*drawnButton1.y: 1
*drawnButton1.width: 30
*drawnButton1.height: 30
*drawnButton1.labelString: " "
*drawnButton1.activateCallback: {\
selez_bott_border(0);\
}
*drawnButton1.recomputeSize: "false"

*drawnButton2.class: drawnButton
*drawnButton2.static: true
*drawnButton2.name: drawnButton2
*drawnButton2.parent: drawingArea2
*drawnButton2.x: 104
*drawnButton2.y: 1
*drawnButton2.width: 30
*drawnButton2.height: 30
*drawnButton2.labelString: " "
*drawnButton2.activateCallback: {\
selez_bott_border(1);\
}
*drawnButton2.recomputeSize: "false"

*drawnButton3.class: drawnButton
*drawnButton3.static: true
*drawnButton3.name: drawnButton3
*drawnButton3.parent: drawingArea2
*drawnButton3.x: 134
*drawnButton3.y: 1
*drawnButton3.width: 30
*drawnButton3.height: 30
*drawnButton3.labelString: " "
*drawnButton3.activateCallback: {\
selez_bott_border(2);\
}
*drawnButton3.recomputeSize: "false"

*drawnButton4.class: drawnButton
*drawnButton4.static: true
*drawnButton4.name: drawnButton4
*drawnButton4.parent: drawingArea2
*drawnButton4.x: 164
*drawnButton4.y: 1
*drawnButton4.width: 30
*drawnButton4.height: 30
*drawnButton4.labelString: " "
*drawnButton4.activateCallback: {\
selez_bott_border(3);\
}
*drawnButton4.recomputeSize: "false"

*drawnButton5.class: drawnButton
*drawnButton5.static: true
*drawnButton5.name: drawnButton5
*drawnButton5.parent: drawingArea2
*drawnButton5.x: 194
*drawnButton5.y: 1
*drawnButton5.width: 30
*drawnButton5.height: 30
*drawnButton5.labelString: " "
*drawnButton5.activateCallback: {\
selez_bott_border(4);\
}
*drawnButton5.recomputeSize: "false"

*drawnButton6.class: drawnButton
*drawnButton6.static: true
*drawnButton6.name: drawnButton6
*drawnButton6.parent: drawingArea2
*drawnButton6.x: 224
*drawnButton6.y: 1
*drawnButton6.width: 30
*drawnButton6.height: 30
*drawnButton6.labelString: " "
*drawnButton6.activateCallback: {\
selez_bott_border(5);\
}
*drawnButton6.recomputeSize: "false"

*drawnButton7.class: drawnButton
*drawnButton7.static: true
*drawnButton7.name: drawnButton7
*drawnButton7.parent: drawingArea2
*drawnButton7.x: 254
*drawnButton7.y: 1
*drawnButton7.width: 30
*drawnButton7.height: 30
*drawnButton7.labelString: " "
*drawnButton7.activateCallback: {\
selez_bott_border(6);\
}
*drawnButton7.recomputeSize: "false"

*drawnButton8.class: drawnButton
*drawnButton8.static: true
*drawnButton8.name: drawnButton8
*drawnButton8.parent: drawingArea2
*drawnButton8.x: 280
*drawnButton8.y: 2
*drawnButton8.width: 34
*drawnButton8.height: 28
*drawnButton8.labelString: " "
*drawnButton8.activateCallback: {\
selez_bott_border(7);\
}
*drawnButton8.recomputeSize: "false"

*drawnButton9.class: drawnButton
*drawnButton9.static: true
*drawnButton9.name: drawnButton9
*drawnButton9.parent: drawingArea2
*drawnButton9.x: 314
*drawnButton9.y: 1
*drawnButton9.width: 30
*drawnButton9.height: 30
*drawnButton9.labelString: " "
*drawnButton9.activateCallback: {\
selez_bott_border(8);\
}
*drawnButton9.recomputeSize: "false"

*drawnButton10.class: drawnButton
*drawnButton10.static: true
*drawnButton10.name: drawnButton10
*drawnButton10.parent: drawingArea2
*drawnButton10.x: 344
*drawnButton10.y: 1
*drawnButton10.width: 30
*drawnButton10.height: 30
*drawnButton10.labelString: " "
*drawnButton10.activateCallback: {\
selez_bott_border(9);\
}
*drawnButton10.recomputeSize: "false"

*drawnButton11.class: drawnButton
*drawnButton11.static: true
*drawnButton11.name: drawnButton11
*drawnButton11.parent: drawingArea2
*drawnButton11.x: 374
*drawnButton11.y: 1
*drawnButton11.width: 30
*drawnButton11.height: 30
*drawnButton11.labelString: " "
*drawnButton11.activateCallback: {\
selez_bott_border(10);\
}
*drawnButton11.recomputeSize: "false"

*drawnButton12.class: drawnButton
*drawnButton12.static: true
*drawnButton12.name: drawnButton12
*drawnButton12.parent: drawingArea2
*drawnButton12.x: 404
*drawnButton12.y: 1
*drawnButton12.width: 30
*drawnButton12.height: 30
*drawnButton12.labelString: " "
*drawnButton12.activateCallback: {\
selez_bott_border(11);\
}
*drawnButton12.recomputeSize: "false"

*drawnButton13.class: drawnButton
*drawnButton13.static: true
*drawnButton13.name: drawnButton13
*drawnButton13.parent: drawingArea2
*drawnButton13.x: 434
*drawnButton13.y: 1
*drawnButton13.width: 30
*drawnButton13.height: 30
*drawnButton13.background: "#dddddd"
*drawnButton13.labelString: "1"
*drawnButton13.activateCallback: {\
selez_bott_border(12);\
}
*drawnButton13.recomputeSize: "false"

*drawnButton14.class: drawnButton
*drawnButton14.static: true
*drawnButton14.name: drawnButton14
*drawnButton14.parent: drawingArea2
*drawnButton14.x: 464
*drawnButton14.y: 1
*drawnButton14.width: 30
*drawnButton14.height: 30
*drawnButton14.background: "#bbbbbb"
*drawnButton14.labelString: "2"
*drawnButton14.activateCallback: {\
selez_bott_border(13);\
}
*drawnButton14.recomputeSize: "false"

*drawnButton15.class: drawnButton
*drawnButton15.static: true
*drawnButton15.name: drawnButton15
*drawnButton15.parent: drawingArea2
*drawnButton15.x: 494
*drawnButton15.y: 1
*drawnButton15.width: 30
*drawnButton15.height: 30
*drawnButton15.background: "#999999"
*drawnButton15.labelString: "3"
*drawnButton15.activateCallback: {\
selez_bott_border(14);\
}
*drawnButton15.recomputeSize: "false"

*drawnButton16.class: drawnButton
*drawnButton16.static: true
*drawnButton16.name: drawnButton16
*drawnButton16.parent: drawingArea2
*drawnButton16.x: 524
*drawnButton16.y: 1
*drawnButton16.width: 30
*drawnButton16.height: 30
*drawnButton16.background: "#777777"
*drawnButton16.labelString: "4"
*drawnButton16.activateCallback: {\
selez_bott_border(15);\
}
*drawnButton16.recomputeSize: "false"

*label1.class: label
*label1.static: true
*label1.name: label1
*label1.parent: drawingArea2
*label1.x: 7
*label1.y: 5
*label1.width: 62
*label1.height: 24
*label1.labelString: "Line Color"

*arrow_bt.class: drawnButton
*arrow_bt.static: true
*arrow_bt.name: arrow_bt
*arrow_bt.parent: workDrArea
*arrow_bt.x: 10
*arrow_bt.y: 100
*arrow_bt.width: 60
*arrow_bt.height: 50
*arrow_bt.labelType: "pixmap"
*arrow_bt.activateCallback: {\
 add_def_translation(draw_wid, pickTable);\
#ifdef ON_PAGEDIT\
aggiungi_pagedit_translation(draw_wid);\
#endif\
 selez_bott_draw(0);\
}
*arrow_bt.shadowThickness: 2
*arrow_bt.shadowType: "shadow_out"
*arrow_bt.recomputeSize: "true"

*drawarc_bt.class: drawnButton
*drawarc_bt.static: true
*drawarc_bt.name: drawarc_bt
*drawarc_bt.parent: workDrArea
*drawarc_bt.x: 260
*drawarc_bt.y: 100
*drawarc_bt.width: 76
*drawarc_bt.height: 76
*drawarc_bt.labelType: "pixmap"
*drawarc_bt.activateCallback: {\
add_def_translation(draw_wid, arcTable);\
#ifdef ON_PAGEDIT\
aggiungi_pagedit_translation(draw_wid);\
#endif\
selez_bott_draw(5);\
}
*drawarc_bt.shadowThickness: 2
*drawarc_bt.shadowType: "shadow_out"
*drawarc_bt.recomputeSize: "true"

*zoom_bt.class: drawnButton
*zoom_bt.static: true
*zoom_bt.name: zoom_bt
*zoom_bt.parent: workDrArea
*zoom_bt.x: 60
*zoom_bt.y: 100
*zoom_bt.width: 60
*zoom_bt.height: 50
*zoom_bt.labelType: "pixmap"
*zoom_bt.activateCallback: {\
selez_bott_draw(1);\
}
*zoom_bt.shadowThickness: 2
*zoom_bt.shadowType: "shadow_out"
*zoom_bt.recomputeSize: "true"

*DrawDemoMainMenu.class: rowColumn
*DrawDemoMainMenu.static: true
*DrawDemoMainMenu.name: DrawDemoMainMenu
*DrawDemoMainMenu.parent: mainWindow
*DrawDemoMainMenu.borderWidth: 0
*DrawDemoMainMenu.menuHelpWidget: "helpCascade"
*DrawDemoMainMenu.rowColumnType: "menu_bar"
*DrawDemoMainMenu.menuAccelerator: "<KeyUp>F10"

*filePane.class: rowColumn
*filePane.static: true
*filePane.name: filePane
*filePane.parent: DrawDemoMainMenu
*filePane.rowColumnType: "menu_pulldown"

*saveButton.class: pushButtonGadget
*saveButton.static: true
*saveButton.name: saveButton
*saveButton.parent: filePane
*saveButton.labelString: "Save"
*saveButton.mnemonic: "S"
*saveButton.activateCallback: {\
#ifndef ON_PAGEDIT\
WriteBackground(draw_wid,nome_file_draw);\
#endif\
}

*saveAsButton.class: pushButtonGadget
*saveAsButton.static: true
*saveAsButton.name: saveAsButton
*saveAsButton.parent: filePane
*saveAsButton.labelString: "Save As ..."
*saveAsButton.mnemonic: "A"
*saveAsButton.activateCallback: {\
extern swidget drawShell;\
#ifndef ON_PAGEDIT\
UxPopupInterface ( create_SaveSelection(drawShell), no_grab);\
#endif\
}

*filePane_b8.class: separatorGadget
*filePane_b8.static: true
*filePane_b8.name: filePane_b8
*filePane_b8.parent: filePane

*prtButton.class: pushButton
*prtButton.static: true
*prtButton.name: prtButton
*prtButton.parent: filePane
*prtButton.labelString: "Print"
*prtButton.activateCallback: {\
#if !defined ON_PAGEDIT && defined XPRINTER_USED\
PrintPag(draw_wid);\
#endif\
}

*prtSetupButton.class: pushButton
*prtSetupButton.static: true
*prtSetupButton.name: prtSetupButton
*prtSetupButton.parent: filePane
*prtSetupButton.labelString: "Setup Printer..."
*prtSetupButton.activateCallback: {\
#if !defined ON_PAGEDIT && defined XPRINTER_USED\
PrintSetup(draw_wid);\
#endif\
}

*filePane_b7.class: separator
*filePane_b7.static: true
*filePane_b7.name: filePane_b7
*filePane_b7.parent: filePane

*exitButton.class: pushButtonGadget
*exitButton.static: true
*exitButton.name: exitButton
*exitButton.parent: filePane
*exitButton.labelString: "Exit"
*exitButton.mnemonic: "E"
*exitButton.activateCallback: {\
DeselectAllDraget(draw_wid,True);\
UxDestroyInterface(mainWindow);\
#ifndef ON_PAGEDIT\
exit(0);\
#endif\
#ifdef ON_PAGEDIT\
set_draw_translations(draw_wid);\
aggiungi_pagedit_translation(draw_wid);\
/*\
 resetta il flag che indica che sto disegnando sul\
 background\
*/\
reset_drawing_background(draw_wid);\
#endif\
}

*editPane.class: rowColumn
*editPane.static: true
*editPane.name: editPane
*editPane.parent: DrawDemoMainMenu
*editPane.rowColumnType: "menu_pulldown"

*undoButton.class: pushButton
*undoButton.static: true
*undoButton.name: undoButton
*undoButton.parent: editPane
*undoButton.labelString: "Undo"
*undoButton.mnemonic: "U"
*undoButton.activateCallback: {\
/* chiama la funzione di undo \
*/\
\
extern int undo_draget_paste();\
\
undo_draget_paste( draw_wid );\
}

*dupButton.class: pushButton
*dupButton.static: true
*dupButton.name: dupButton
*dupButton.parent: editPane
*dupButton.labelString: "Duplicate"
*dupButton.mnemonic: "D"
*dupButton.activateCallback: {\
int dx,dy;\
extern int curr_step;\
if(curr_step > 1)\
	dx=dy=curr_step;\
else\
	dx=dy=5;\
\
draget_duplicate(draw_wid,dx,dy);\
}

*cutButton.class: pushButtonGadget
*cutButton.static: true
*cutButton.name: cutButton
*cutButton.parent: editPane
*cutButton.accelerator: "Shift <Key>DeleteChar"
*cutButton.acceleratorText: "Shift+Del"
*cutButton.labelString: "Cut"
*cutButton.mnemonic: "t"
*cutButton.activateCallback: {\
  printf("Cut!\n");\
draget_cut(draw_wid);\
}

*copyButton.class: pushButtonGadget
*copyButton.static: true
*copyButton.name: copyButton
*copyButton.parent: editPane
*copyButton.accelerator: "Ctrl <Key>InsertChar"
*copyButton.acceleratorText: "Ctrl+Ins"
*copyButton.labelString: "Copy"
*copyButton.mnemonic: "C"
*copyButton.activateCallback: {\
  printf("Copy!\n");\
  draget_copy(draw_wid);\
}

*pasteButton.class: pushButtonGadget
*pasteButton.static: true
*pasteButton.name: pasteButton
*pasteButton.parent: editPane
*pasteButton.accelerator: "Shift <Key>InsertChar"
*pasteButton.acceleratorText: "Shift+Ins"
*pasteButton.labelString: "Paste"
*pasteButton.mnemonic: "P"
*pasteButton.activateCallback: {\
  printf("Paste!\n");\
  draget_paste(draw_wid);\
}

*deleteButton.class: pushButtonGadget
*deleteButton.static: true
*deleteButton.name: deleteButton
*deleteButton.parent: editPane
*deleteButton.labelString: "Delete"
*deleteButton.mnemonic: "D"
*deleteButton.activateCallback: { DrawDelete(draw_wid, NULL); }
*deleteButton.acceleratorText: "BackSpace"
*deleteButton.accelerator: "<Key>BackSpace"

*editPane_b12.class: separator
*editPane_b12.static: true
*editPane_b12.name: editPane_b12
*editPane_b12.parent: editPane

*topButton.class: pushButton
*topButton.static: true
*topButton.name: topButton
*topButton.parent: editPane
*topButton.labelString: "Put Top"
*topButton.activateCallback: {\
DrawPutTop(draw_wid);\
}

*bottomButton.class: pushButton
*bottomButton.static: true
*bottomButton.name: bottomButton
*bottomButton.parent: editPane
*bottomButton.labelString: "Put Bottom"
*bottomButton.activateCallback: DrawPutBottom(draw_wid);\


*editPane_b13.class: separator
*editPane_b13.static: true
*editPane_b13.name: editPane_b13
*editPane_b13.parent: editPane

*groupButton.class: pushButton
*groupButton.static: true
*groupButton.name: groupButton
*groupButton.parent: editPane
*groupButton.labelString: "Group"
*groupButton.mnemonic: "G"
*groupButton.activateCallback: {\
DrawGroup(draw_wid);\
}

*ungroupButton.class: pushButton
*ungroupButton.static: true
*ungroupButton.name: ungroupButton
*ungroupButton.parent: editPane
*ungroupButton.labelString: "Ungroup"
*ungroupButton.mnemonic: "U"
*ungroupButton.activateCallback: {\
DrawUngroup(draw_wid);\
}

*viewPane.class: rowColumn
*viewPane.static: true
*viewPane.name: viewPane
*viewPane.parent: DrawDemoMainMenu
*viewPane.radioBehavior: "true"
*viewPane.rowColumnType: "menu_pulldown"
*viewPane.entryClass: "toggleButton"

*view_normal.class: toggleButton
*view_normal.static: true
*view_normal.name: view_normal
*view_normal.parent: viewPane
*view_normal.labelString: "Normal view"
*view_normal.mnemonic: "N"
*view_normal.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
	DrawSetZoom(draw_wid,1.0);\
}
*view_normal.set: "true"

*viewPane_b20.class: separator
*viewPane_b20.static: true
*viewPane_b20.name: viewPane_b20
*viewPane_b20.parent: viewPane

*view_200.class: toggleButton
*view_200.static: true
*view_200.name: view_200
*view_200.parent: viewPane
*view_200.labelString: "200%"
*view_200.mnemonic: "0"
*view_200.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
	DrawSetZoom(draw_wid,2.0);\
}

*view_400.class: toggleButton
*view_400.static: true
*view_400.name: view_400
*view_400.parent: viewPane
*view_400.labelString: "400%"
*view_400.mnemonic: "4"
*view_400.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
	DrawSetZoom(draw_wid,4.0); \
}

*view_800.class: toggleButton
*view_800.static: true
*view_800.name: view_800
*view_800.parent: viewPane
*view_800.labelString: "800%"
*view_800.mnemonic: "8"
*view_800.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
	DrawSetZoom(draw_wid,8.0);\
}

*viewPane_b6.class: separator
*viewPane_b6.static: true
*viewPane_b6.name: viewPane_b6
*viewPane_b6.parent: viewPane

*grid_pb.class: pushButton
*grid_pb.static: true
*grid_pb.name: grid_pb
*grid_pb.parent: viewPane
*grid_pb.labelString: "Grid"
*grid_pb.mnemonic: "G"
*grid_pb.activateCallback: {\
DrawSetGrid(draw_wid);\
}

*drawPane.class: rowColumn
*drawPane.static: true
*drawPane.name: drawPane
*drawPane.parent: DrawDemoMainMenu
*drawPane.rowColumnType: "menu_pulldown"

*filled_bt.class: toggleButton
*filled_bt.static: true
*filled_bt.name: filled_bt
*filled_bt.parent: drawPane
*filled_bt.labelString: "Filled"
*filled_bt.mnemonic: "F"
*filled_bt.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
set_current_filled(draw_wid,pcall->set);\
}\

*filled_bt.set: "true"
*filled_bt.indicatorOn: "false"

*drawPane_b9.class: separator
*drawPane_b9.static: true
*drawPane_b9.name: drawPane_b9
*drawPane_b9.parent: drawPane

*line_bt.class: cascadeButton
*line_bt.static: true
*line_bt.name: line_bt
*line_bt.parent: drawPane
*line_bt.labelString: "Line Style"
*line_bt.mnemonic: "L"
*line_bt.subMenuId: "lineStylePane"

*line_width_bt.class: cascadeButton
*line_width_bt.static: true
*line_width_bt.name: line_width_bt
*line_width_bt.parent: drawPane
*line_width_bt.labelString: "Line Width"
*line_width_bt.mnemonic: "W"
*line_width_bt.subMenuId: "lineWidthPane"

*drawPane_b12.class: separator
*drawPane_b12.static: true
*drawPane_b12.name: drawPane_b12
*drawPane_b12.parent: drawPane

*snap_casc.class: cascadeButton
*snap_casc.static: true
*snap_casc.name: snap_casc
*snap_casc.parent: drawPane
*snap_casc.labelString: "Snap"
*snap_casc.mnemonic: "S"
*snap_casc.subMenuId: "snap_Pane"

*drawPane_b15.class: separator
*drawPane_b15.static: true
*drawPane_b15.name: drawPane_b15
*drawPane_b15.parent: drawPane

*drawPane_b16.class: cascadeButtonGadget
*drawPane_b16.static: true
*drawPane_b16.name: drawPane_b16
*drawPane_b16.parent: drawPane
*drawPane_b16.labelString: "Rotate"
*drawPane_b16.subMenuId: "rotatePane"

*lineStylePane.class: rowColumn
*lineStylePane.static: true
*lineStylePane.name: lineStylePane
*lineStylePane.parent: drawPane
*lineStylePane.rowColumnType: "menu_pulldown"
*lineStylePane.radioBehavior: "true"

*solid_bt.class: toggleButton
*solid_bt.static: true
*solid_bt.name: solid_bt
*solid_bt.parent: lineStylePane
*solid_bt.labelString: "Solid"
*solid_bt.set: "true"
*solid_bt.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
	{\
	set_line_style(draw_wid,LineSolid);\
	set_current_gcs(draw_wid);\
	}\
}

*dashed_bt.class: toggleButton
*dashed_bt.static: true
*dashed_bt.name: dashed_bt
*dashed_bt.parent: lineStylePane
*dashed_bt.labelString: "Dashed"
*dashed_bt.mnemonic: "D"
*dashed_bt.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
 {\
 set_line_style(draw_wid,LineOnOffDash);\
 set_current_gcs(draw_wid);\
 }\
}\


*linedot_bt.class: toggleButton
*linedot_bt.static: true
*linedot_bt.name: linedot_bt
*linedot_bt.parent: lineStylePane
*linedot_bt.labelString: "Line - dot"
*linedot_bt.mnemonic: "L"
*linedot_bt.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
 {\
 set_line_style(draw_wid,LineOnOffDash);\
 set_current_gcs(draw_wid);\
 }\
}\


*rotatePane.class: rowColumn
*rotatePane.static: true
*rotatePane.name: rotatePane
*rotatePane.parent: drawPane
*rotatePane.rowColumnType: "menu_pulldown"

*DrawDemoMainMenu_p14_b1.class: pushButton
*DrawDemoMainMenu_p14_b1.static: true
*DrawDemoMainMenu_p14_b1.name: DrawDemoMainMenu_p14_b1
*DrawDemoMainMenu_p14_b1.parent: rotatePane
*DrawDemoMainMenu_p14_b1.labelString: "Rotate Right"
*DrawDemoMainMenu_p14_b1.activateCallback.source: public
*DrawDemoMainMenu_p14_b1.activateCallback: 

*DrawDemoMainMenu_p14_b2.class: pushButton
*DrawDemoMainMenu_p14_b2.static: true
*DrawDemoMainMenu_p14_b2.name: DrawDemoMainMenu_p14_b2
*DrawDemoMainMenu_p14_b2.parent: rotatePane
*DrawDemoMainMenu_p14_b2.labelString: "Rotate Left"
*DrawDemoMainMenu_p14_b2.activateCallback.source: public
*DrawDemoMainMenu_p14_b2.activateCallback: 

*rotatePane_b5.class: separator
*rotatePane_b5.static: true
*rotatePane_b5.name: rotatePane_b5
*rotatePane_b5.parent: rotatePane

*DrawDemoMainMenu_p14_b3.class: pushButton
*DrawDemoMainMenu_p14_b3.static: true
*DrawDemoMainMenu_p14_b3.name: DrawDemoMainMenu_p14_b3
*DrawDemoMainMenu_p14_b3.parent: rotatePane
*DrawDemoMainMenu_p14_b3.labelString: "Rotate Vertical"
*DrawDemoMainMenu_p14_b3.activateCallback.source: public
*DrawDemoMainMenu_p14_b3.activateCallback: 

*DrawDemoMainMenu_p14_b4.class: pushButton
*DrawDemoMainMenu_p14_b4.static: true
*DrawDemoMainMenu_p14_b4.name: DrawDemoMainMenu_p14_b4
*DrawDemoMainMenu_p14_b4.parent: rotatePane
*DrawDemoMainMenu_p14_b4.labelString: "Rotate Horizontal"
*DrawDemoMainMenu_p14_b4.activateCallback.source: public
*DrawDemoMainMenu_p14_b4.activateCallback: 

*lineWidthPane.class: rowColumn
*lineWidthPane.static: true
*lineWidthPane.name: lineWidthPane
*lineWidthPane.parent: drawPane
*lineWidthPane.rowColumnType: "menu_pulldown"
*lineWidthPane.radioBehavior: "true"

*thiny_bt.class: toggleButton
*thiny_bt.static: true
*thiny_bt.name: thiny_bt
*thiny_bt.parent: lineWidthPane
*thiny_bt.labelString: "Thin"
*thiny_bt.mnemonic: "T"
*thiny_bt.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
 {\
 set_line_width(draw_wid,0);\
 set_current_gcs(draw_wid);\
 }\
\
}
*thiny_bt.set: "true"

*pix_1_bt.class: toggleButton
*pix_1_bt.static: true
*pix_1_bt.name: pix_1_bt
*pix_1_bt.parent: lineWidthPane
*pix_1_bt.labelString: "1 pixel"
*pix_1_bt.mnemonic: "1"
*pix_1_bt.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
 {\
 set_line_width(draw_wid,1);\
 set_current_gcs(draw_wid);\
 }\
\
}

*pix_2_bt.class: toggleButton
*pix_2_bt.static: true
*pix_2_bt.name: pix_2_bt
*pix_2_bt.parent: lineWidthPane
*pix_2_bt.labelString: "2 pixel"
*pix_2_bt.mnemonic: "2"
*pix_2_bt.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
 {\
 set_line_width(draw_wid,2);\
 set_current_gcs(draw_wid);\
 }\
}\


*pix_3_bt.class: toggleButton
*pix_3_bt.static: true
*pix_3_bt.name: pix_3_bt
*pix_3_bt.parent: lineWidthPane
*pix_3_bt.labelString: "3 pixel"
*pix_3_bt.mnemonic: "3"
*pix_3_bt.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
 {\
 set_line_width(draw_wid,3);\
 set_current_gcs(draw_wid);\
 }\
}\


*pix_6_bt.class: toggleButton
*pix_6_bt.static: true
*pix_6_bt.name: pix_6_bt
*pix_6_bt.parent: lineWidthPane
*pix_6_bt.labelString: "6 pixel"
*pix_6_bt.mnemonic: "6"
*pix_6_bt.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
 {\
 set_line_width(draw_wid,6);\
 set_current_gcs(draw_wid);\
 }\
}\


*width_other.class: toggleButton
*width_other.static: true
*width_other.name: width_other
*width_other.parent: lineWidthPane
*width_other.labelString: "other ..."
*width_other.mnemonic: "o"
*width_other.valueChangedCallback: {\
extern swidget create_line_width_dialog();\
static Widget wdialog=NULL;\
\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (wdialog == NULL)\
	wdialog= (Widget)create_line_width_dialog(draw_wid);\
\
if(pcall->set)\
	UxPopupInterface(wdialog, no_grab);\
\
}\


*snap_Pane.class: rowColumn
*snap_Pane.static: true
*snap_Pane.name: snap_Pane
*snap_Pane.parent: drawPane
*snap_Pane.rowColumnType: "menu_pulldown"
*snap_Pane.radioBehavior: "true"

*sn5.class: toggleButton
*sn5.static: true
*sn5.name: sn5
*sn5.parent: snap_Pane
*sn5.labelString: "5 pixel"
*sn5.mnemonic: "5"
*sn5.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
 DrawSetSnap(draw_wid,5);\
}

*sn10.class: toggleButton
*sn10.static: true
*sn10.name: sn10
*sn10.parent: snap_Pane
*sn10.labelString: "10 pixel"
*sn10.mnemonic: "1"
*sn10.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
 DrawSetSnap(draw_wid,10);\
}\


*sn15.class: toggleButton
*sn15.static: true
*sn15.name: sn15
*sn15.parent: snap_Pane
*sn15.labelString: "15 pixel"
*sn15.mnemonic: "1"
*sn15.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
 DrawSetSnap(draw_wid,15);\
}\


*snother.class: toggleButton
*snother.static: true
*snother.name: snother
*snother.parent: snap_Pane
*snother.labelString: "other ..."
*snother.mnemonic: "o"
*snother.valueChangedCallback: {\
extern swidget create_snap_width_dialog();\
static Widget wdialog=NULL;\
\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
\
if (wdialog == NULL)\
	wdialog= (Widget)create_snap_width_dialog(draw_wid);\
\
if(pcall->set)\
	UxPopupInterface(wdialog, no_grab);\
\
\
}\


*sn1.class: toggleButton
*sn1.static: true
*sn1.name: sn1
*sn1.parent: snap_Pane
*sn1.labelString: "Snap Off"
*sn1.mnemonic: "O"
*sn1.valueChangedCallback: {\
XmToggleButtonCallbackStruct *pcall;\
pcall=(XmToggleButtonCallbackStruct *)UxCallbackArg;\
if (pcall->set)\
 DrawSetSnap(draw_wid,1);\
}

*helpPane.class: rowColumn
*helpPane.static: true
*helpPane.name: helpPane
*helpPane.parent: DrawDemoMainMenu
*helpPane.rowColumnType: "menu_pulldown"

*onContextButton.class: pushButtonGadget
*onContextButton.static: true
*onContextButton.name: onContextButton
*onContextButton.parent: helpPane
*onContextButton.labelString: "On Context ..."
*onContextButton.mnemonic: "C"
*onContextButton.activateCallback.source: public
*onContextButton.activateCallback: 

*onWindowButton.class: pushButtonGadget
*onWindowButton.static: true
*onWindowButton.name: onWindowButton
*onWindowButton.parent: helpPane
*onWindowButton.labelString: "On Window ..."
*onWindowButton.mnemonic: "W"
*onWindowButton.activateCallback.source: public
*onWindowButton.activateCallback: 

*onKeysButton.class: pushButtonGadget
*onKeysButton.static: true
*onKeysButton.name: onKeysButton
*onKeysButton.parent: helpPane
*onKeysButton.labelString: "On Keys ..."
*onKeysButton.mnemonic: "K"
*onKeysButton.activateCallback.source: public
*onKeysButton.activateCallback: 

*onHelpButton.class: pushButtonGadget
*onHelpButton.static: true
*onHelpButton.name: onHelpButton
*onHelpButton.parent: helpPane
*onHelpButton.labelString: "On Help ..."
*onHelpButton.mnemonic: "H"
*onHelpButton.activateCallback.source: public
*onHelpButton.activateCallback: 

*helpPane_b8.class: separatorGadget
*helpPane_b8.static: true
*helpPane_b8.name: helpPane_b8
*helpPane_b8.parent: helpPane

*indexButton.class: pushButtonGadget
*indexButton.static: true
*indexButton.name: indexButton
*indexButton.parent: helpPane
*indexButton.labelString: "Index"
*indexButton.mnemonic: "I"
*indexButton.activateCallback.source: public
*indexButton.activateCallback: 

*tutorialButton.class: pushButtonGadget
*tutorialButton.static: true
*tutorialButton.name: tutorialButton
*tutorialButton.parent: helpPane
*tutorialButton.labelString: "Tutorial"
*tutorialButton.mnemonic: "T"
*tutorialButton.activateCallback.source: public
*tutorialButton.activateCallback: 

*helpPane_b9.class: separatorGadget
*helpPane_b9.static: true
*helpPane_b9.name: helpPane_b9
*helpPane_b9.parent: helpPane

*onVersionButton.class: pushButtonGadget
*onVersionButton.static: true
*onVersionButton.name: onVersionButton
*onVersionButton.parent: helpPane
*onVersionButton.labelString: "On Version ..."
*onVersionButton.mnemonic: "V"
*onVersionButton.activateCallback.source: public
*onVersionButton.activateCallback: 

*colorPane.class: rowColumn
*colorPane.static: true
*colorPane.name: colorPane
*colorPane.parent: DrawDemoMainMenu
*colorPane.rowColumnType: "menu_pulldown"

*edit_colors_bt.class: pushButton
*edit_colors_bt.static: true
*edit_colors_bt.name: edit_colors_bt
*edit_colors_bt.parent: colorPane
*edit_colors_bt.labelString: "Edit Colors..."
*edit_colors_bt.activateCallback: {\
XmString xm_str;\
xm_str=XmStringCreateSimple(" "); \
UxPopupInterface(create_ColorViewer(DRAW_VER,"#ffffffffffff",xm_str,\
			UxDisplay->db,\
			vett_colori,\
			vett_border[0]), no_grab);\
\
XmStringFree(xm_str);\
}

*fileCascade.class: cascadeButton
*fileCascade.static: true
*fileCascade.name: fileCascade
*fileCascade.parent: DrawDemoMainMenu
*fileCascade.labelString: "File"
*fileCascade.mnemonic: "F"
*fileCascade.subMenuId: "filePane"

*editCascade.class: cascadeButton
*editCascade.static: true
*editCascade.name: editCascade
*editCascade.parent: DrawDemoMainMenu
*editCascade.labelString: "Edit"
*editCascade.mnemonic: "E"
*editCascade.subMenuId: "editPane"

*viewCascade.class: cascadeButton
*viewCascade.static: true
*viewCascade.name: viewCascade
*viewCascade.parent: DrawDemoMainMenu
*viewCascade.labelString: "View"
*viewCascade.mnemonic: "V"
*viewCascade.subMenuId: "viewPane"

*pullDownMenu_top_b1.class: cascadeButton
*pullDownMenu_top_b1.static: true
*pullDownMenu_top_b1.name: pullDownMenu_top_b1
*pullDownMenu_top_b1.parent: DrawDemoMainMenu
*pullDownMenu_top_b1.labelString: "Draw"
*pullDownMenu_top_b1.subMenuId: "drawPane"
*pullDownMenu_top_b1.mnemonic: "d"

*helpCascade.class: cascadeButton
*helpCascade.static: true
*helpCascade.name: helpCascade
*helpCascade.parent: DrawDemoMainMenu
*helpCascade.labelString: "Help"
*helpCascade.mnemonic: "H"
*helpCascade.subMenuId: "helpPane"

*DrawDemoMainMenu_top_b4.class: cascadeButton
*DrawDemoMainMenu_top_b4.static: true
*DrawDemoMainMenu_top_b4.name: DrawDemoMainMenu_top_b4
*DrawDemoMainMenu_top_b4.parent: DrawDemoMainMenu
*DrawDemoMainMenu_top_b4.labelString: "Colors"
*DrawDemoMainMenu_top_b4.subMenuId: "colorPane"


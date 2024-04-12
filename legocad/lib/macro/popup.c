/**********************************************************************
*
*       C Source:               popup.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 12:17:02 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: popup.c,2 %  (%full_filespec: 1,csrc,popup.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)popup.c	2.9\t4/11/95";
/*
        Fine sezione per SCCS
*/

/* POPUP.C 		file di servizio per MACRO
			Crea gli widget dell'applicativo
			relativi ai popup menu dei macroblocchi e dei blocchi.
   Versione 0.1		16.11.92			Buffo & Calleri  */

#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/cursorfont.h>
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/LabelG.h>
#include <Xm/Text.h>
#include <Xm/SeparatoG.h>
#include <Xm/DialogS.h>
#include <Xm/RowColumn.h>
#include <Xm/Form.h>
#include <Xm/PushB.h>
#include <Xm/MenuShell.h>
#include <Xm/BulletinB.h>
#include <Xm/ToggleB.h>
#ifdef TOPOLOGIA
#include <Xm/CascadeB.h>
#include <Xm/CascadeBG.h>
#include <Xm/PushBG.h>
#endif
#include <macro.h>
#include <ico_mesg.h>

/* Variabili esterne dichiarate in MACRO.C ... */
extern Widget top_level;
extern Widget warning_widget;

/* Strutture per la gestione degli widgets */
extern MacroBlockType *macroblocks;
extern int num_macro;

extern XmString    stringa_nulla, cstring;

extern Display *display;
extern GC xorGC;

extern Pixel apix[];
extern Arg args[];
extern Cardinal nargs;

extern Widget popup_mcr, popup_blk, macro_tavola;

/*------------------------------------------------------------------*/
/*** popup_macro()
 ***  Parametri :
 *** Crea il popup menu dei macroblocchi. Viene visualizzato
 *** quando si preme il <Btn3> dopo aver selezionato il macroblocco
 *** con il <Btn1>.
 ***/
void popup_macro()
{
   Widget popup_title, separator; 
   extern Widget pop_edit_macro[7];
   extern XmString cstring;

/* Creazione del Popup MenuPane */
/* La chiamata crea automaticamente un parent MenuShell */
   nargs=0;
   popup_mcr = XmCreatePopupMenu (macro_tavola,"Edit_macro",args,nargs);

/* Creazione del titolo del Popup */
   nargs=0;
   cstring = CREATE_CSTRING("PAGE");
   XtSetArg(args[nargs],XmNlabelString, cstring); nargs++;
   popup_title = XmCreateLabelGadget (popup_mcr,"Edit_macro",args,nargs);
   XtManageChild (popup_title);
   XmStringFree(cstring);

/* Creazione del separatore */
   separator = XmCreateSeparatorGadget (popup_mcr,"Separator",NULL,0);
   XtManageChild (separator);

/* Chiamata alla funzione che crea le voci di menu */
   macro_edit_items (popup_mcr, pop_edit_macro);
   XtAddEventHandler( macro_tavola, ButtonPressMask, False, attiva_popup,
                      popup_mcr );
}

/*------------------------------------------------------------------*/
/*** popup_block()
 *** Parametri : 
 ***   int ind_macro : indice in macroblocks[].
 *** Crea il popup menu dei blocchi. Viene visualizzato
 *** quando si preme il <Btn3> dopo aver selezionato il blocco
 *** con il <Btn1>.
 ***/
void popup_block(ind_macro)
int ind_macro;
{
   extern XmString cstring;
   Widget popup_title, separator;
   MacroBlockType *macro;

   macro = &macroblocks[ind_macro];

/* Creazione del Popup MenuPane */
/* La chiamata crea automaticamente un parent MenuShell */
   nargs=0;
   macro->wpopup = XmCreatePopupMenu ( macro->wwinblock, "Edit_block",
				       args,nargs);

/* Creazione del titolo del Popup */
   nargs=0;
   cstring = CREATE_CSTRING("EDIT BLOCK");
   XtSetArg(args[nargs],XmNlabelString,cstring); nargs++;
   popup_title = XmCreateLabelGadget (macro->wpopup, "Edit_block",args,nargs);
   XtManageChild (popup_title);
   XmStringFree(cstring);

/* Creazione del separatore */
   separator = XmCreateSeparatorGadget (macro->wpopup, "Separator",NULL,0);
   XtManageChild (separator);

/* Chiamata alla funzione che crea le voci di menu */
   block_edit_items (macro->wpopup, ind_macro, macro->pop_edit_blocchi);
   XtAddEventHandler(macro->wwinblock, ButtonPressMask, False, attiva_popup,
                     macro->wpopup );
}

/*------------------------------------------------------------------*/
/*** void macro_edit_items(menu_padre, voci_wdg)
 *** PARAMETRI
 *** Widget menu_padre : ID del menu in cui inserire le voci
 ***			(pulldown oppure popup)
 *** Widget voci_wdg[]: widget delle voci del menu 
 *** Crea le voci di menu per l'EDIT dei MACROBLOCCHI.
 ***/
void macro_edit_items(menu_padre, voci_wdg)
Widget menu_padre;
Widget voci_wdg[];
{
   Widget items[8];

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, False); nargs++;
   items[0] = XmCreatePushButton (menu_padre,"Open",args, nargs);
   XtAddCallback(items[0], XmNactivateCallback, menu_macro, K_OPEN_MACRO);
   voci_wdg[K_OPEN_MACRO] = items[0];
#ifdef DATI
   XtManageChild(items[0]);
#else   /* voci non presenti nel caso di attivita' DATI */
/**** Lorenzo Gen.95 ***
   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, True); nargs++;
   items[1] = XmCreatePushButton (menu_padre,"Copy",args, nargs);
   XtAddCallback(items[1], XmNactivateCallback, menu_macro, K_COPY_MACRO);
   voci_wdg[K_COPY_MACRO] = items[1];
*****/

   items[1] = XmCreateSeparatorGadget (menu_padre,"Separator",NULL,0);

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, True); nargs++;
   items[2] = XmCreatePushButton (menu_padre,"New",args, nargs);
   XtAddCallback(items[2], XmNactivateCallback,
                 menu_macro, K_NEW_MACRO);
   voci_wdg[K_NEW_MACRO] = items[2];

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, False); nargs++;
   items[3] = XmCreatePushButton (menu_padre,"Modify",args, nargs);
   XtAddCallback(items[3], XmNactivateCallback, menu_macro, K_MODIFY_MACRO);
   voci_wdg[K_MODIFY_MACRO] = items[3];

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, False); nargs++;
   items[4] = XmCreatePushButton (menu_padre,"Delete",args, nargs);
   XtAddCallback(items[4], XmNactivateCallback, menu_macro, K_DELETE_MACRO);
   voci_wdg[K_DELETE_MACRO] = items[4];

   XtManageChildren (items, 5);
#endif
}

/*------------------------------------------------------------------*/
/*** void block_edit_items(menu_padre, ind_macro, voci_wdg)
 *** PARAMETRI
 *** Widget menu_padre: ID del menu in cui inserire le voci.
 ***			(pulldown oppure popup)
 *** int ind_macro : indice della macro di appartenenza.
 *** Widget voci_wdg[]: widget delle voci del menu 
 *** Crea le voci di menu per l'EDIT dei BLOCCHI.
 *** Modificata per TOPOLOGIA il 31-8-93
 *** Motivo: integrazione con LG1
 ***/
void block_edit_items(menu_padre, ind_macro, voci_wdg)
Widget menu_padre;
int ind_macro;
Widget voci_wdg[];
{
   Widget items[13];
#ifdef TOPOLOGIA
   Widget submenu1,sub1bt[3];
#endif
#ifdef DATI
   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, True); nargs++;
   items[0] = XmCreatePushButton (menu_padre,"Variables...",args, nargs);
   XtAddCallback(items[0], XmNactivateCallback, menu_dati_callb, K_VAR_BLOCK);
   voci_wdg[K_VAR_BLOCK] = items[0];

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, True); nargs++;
   items[1] = XmCreatePushButton (menu_padre,"Data...",args,nargs);
   XtAddCallback(items[1], XmNactivateCallback, menu_dati_callb, K_DATA_BLOCK);
   voci_wdg[K_DATA_BLOCK] = items[1];

   items[2] = XmCreateSeparatorGadget (menu_padre,"Separator",NULL,0);

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, True); nargs++;
   items[3] = XmCreatePushButton (menu_padre,"Known/Unknown...",args,nargs);
   XtAddCallback(items[3], XmNactivateCallback, menu_dati_callb, K_KNOW_BLOCK);
   voci_wdg[K_KNOW_BLOCK] = items[3];

   items[4] = XmCreateSeparatorGadget (menu_padre,"Separator",NULL,0);

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, True); nargs++;
   items[5] = XmCreatePushButton (menu_padre,"Normalization...",args,nargs);
   XtAddCallback(items[5], XmNactivateCallback, menu_dati_callb, K_NORM_BLOCK);
   voci_wdg[K_NORM_BLOCK] = items[5];

   XtManageChildren (items,6);
#elif TOPOLOGIA
   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, True); nargs++;
   items[0] = XmCreatePushButton (menu_padre,"Variables",args,nargs);
   XtAddCallback(items[0], XmNactivateCallback, variables_block, ind_macro);
   voci_wdg[K_VARIABLES_BLOCK] = items[0];

/* creazione sottomenu istanziazione nuovo blocco */
   submenu1 = XmCreatePulldownMenu(menu_padre,"Submenu1",NULL,0);
   
   nargs=0;
   XtSetArg(args[nargs],XmNsubMenuId,submenu1); nargs++;
   items[1] = XmCreateCascadeButtonGadget (menu_padre,"New Block",args,nargs);
   voci_wdg[K_NEW_BLOCK] = items[1]; 

/* definizione bottone istanziazione blocco processo */   
   sub1bt[0] = XmCreatePushButtonGadget (submenu1,"Process",NULL,0);
   XtAddCallback(sub1bt[0], XmNactivateCallback, add_process_block, NULL);
   voci_wdg[K_NEW_PROCESS_BLOCK] = sub1bt[0]; 
 
/* definizione bottone istanziazione blocco regolazione */
   sub1bt[1] = XmCreatePushButtonGadget (submenu1,"Regulation",NULL,0);
   XtAddCallback(sub1bt[1], XmNactivateCallback, add_regolation_block, NULL);
   voci_wdg[K_NEW_REGULATION_BLOCK] = sub1bt[1]; 

/* la manage e' necessaria in quanto il padre degli item e' diverso */
   XtManageChildren(sub1bt,2); 
   
   items[2] = XmCreateSeparatorGadget (menu_padre,"Separator",NULL,0);

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, False); nargs++;
   items[3] = XmCreatePushButton (menu_padre,"Modify ",args,nargs);
   XtAddCallback(items[3], XmNactivateCallback, modify_block, ind_macro);
   voci_wdg[K_MODIFY_BLOCK] = items[3]; 

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, False); nargs++;
   items[4] = XmCreatePushButton (menu_padre,"Delete",args,nargs);
   XtAddCallback(items[4], XmNactivateCallback, bl_del_cb,NULL);
   voci_wdg[K_DELETE_BLOCK] = items[4]; 

   XtManageChildren (items,5);
#else
   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, True); nargs++;
   items[0] = XmCreatePushButton (menu_padre,"Copy",args, nargs);
   voci_wdg[K_COPY_BLOCK] = items[0];

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, False); nargs++;
   items[1] = XmCreatePushButton (menu_padre,"Paste",args,nargs);
   voci_wdg[K_PASTE_BLOCK] = items[1];

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, False); nargs++;
   items[2] = XmCreatePushButton (menu_padre,"Connect",args,nargs);
   voci_wdg[K_CONNECT_BLOCK] = items[2];

   items[3] = XmCreateSeparatorGadget (menu_padre,"Separator",NULL,0);

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, False); nargs++;
   items[4] = XmCreatePushButton (menu_padre,"Modify",args,nargs);
   XtAddCallback(items[4], XmNactivateCallback, modify_block, ind_macro);
   voci_wdg[K_MODIFY_BLOCK] = items[4];

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, False); nargs++;
   items[5] = XmCreatePushButton (menu_padre,"Delete",args,nargs);
   XtAddCallback(items[5], XmNactivateCallback, delete_selected_blocks,
                                                ind_macro);
   voci_wdg[K_DELETE_BLOCK] = items[5];

   items[6] = XmCreateSeparatorGadget (menu_padre,"Separator",NULL,0);

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive, False); nargs++;
   items[7] = XmCreatePushButton (menu_padre,"Move",args,nargs);
   XtAddCallback(items[7], XmNactivateCallback, move_selected_blocks,
                                                ind_macro);
   voci_wdg[K_MOVE_BLOCK] = items[7];

   items[8] = XmCreateSeparatorGadget (menu_padre,"Separator",NULL,0);

   items[9] = XmCreatePushButton (menu_padre,"Add process block",NULL,0);
   XtAddCallback(items[9], XmNactivateCallback, new_block, TP_BLOCK);
   voci_wdg[K_ADD_PBLOCK] = items[9];

   items[10] = XmCreatePushButton (menu_padre,"Add scheme block",NULL,0);
   XtAddCallback(items[10], XmNactivateCallback, new_block, TP_BLOCK_REG);
   voci_wdg[K_ADD_SBLOCK] = items[10];

   items[11] = XmCreatePushButton (menu_padre,"Add symbol",NULL,0);
   XtAddCallback(items[11], XmNactivateCallback, add_symbol, ind_macro);
   voci_wdg[K_ADD_SYMBOL] = items[11];

   items[12] = XmCreatePushButton (menu_padre,"Add remark",NULL,0);
   XtAddCallback(items[12], XmNactivateCallback, add_remark, ind_macro);
   voci_wdg[K_ADD_REMARK] = items[12];

   XtManageChildren (items,13);
#endif
}

/* fine popup.c */

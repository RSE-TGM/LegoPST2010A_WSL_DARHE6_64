! UIMX ascii 2.0 key: 5213                                                      

*nnEdit.class: topLevelShell
*nnEdit.parent: NO_PARENT
*nnEdit.static: true
*nnEdit.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo nnEdit.i\
   tipo \
   release 1.13\
   data 11/13/95\
   reserved @(#)nnEdit.i	1.13\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
/* nnEdit.c\
* Scopo:       editare note / non-note\
* Dati:        dai files "f03.dat" ed "f14.dat": presunte in memoria;\
*              dal file "fpp.dat": legge;\
* Risultati:   salva "f14.dat" ed "fpp.dat"\
* Routines:    write_file_f14 (da libreria liblegocad.a),\
*              {read,write}_file_fpp (da file fpp.o)\
* Moduli:      dialogo nnFilter (in =.o), nnValue (in =.o)\
* Note:\
*  (1)     interfaccia, callback etc composta con AIC in modo Xt;\
*  (2)     variabili private e routines ausiliarie statiche;\
*  (3)     mono-sessione, chiusura controllata, monito privato;\
* Autore:      C.Lusso (CISE) 1994\
*/\
\
\
 /* include: */\
#include <stdio.h>\
#include <Xm/MessageB.h>\
#include "f03.h"\
#include "f14.h"\
#include "libutilx.h"\
#include "helpkit.h"\
#include "nn.h"\
#include "fpp.h"\
 /* define: */\
/* bit per opzioni di 'loStato':\
*	NN_LIBERO       valore iniziale;\
*	NN_OCCUPATO     On: dialogo occupato, Off: libero;\
*	NN_MODE_NN      On: Modo Normale, Off: Modo Paia;\
*	NN_CHG_NN       On: cambiate vars, Off: nessuna;\
*	NN_CHG_PP       On: cambiate paia, Off: nessuna;\
*/\
#define NN_LIBERO       0L\
#define NN_OCCUPATO     0x01L\
#define NN_MODE_NN      0x02L\
#define NN_VARS_ALL     0x10L\
#define NN_VARS_FILTER  0x20L\
#define NN_CHG_NN       0x100L\
#define NN_CHG_PP       0x200L\
 /* enum: */\
/* messaggi */\
enum {\
 ennEmsg_null,\
 ennEmsg_save_14_pp,\
 ennEmsg_save_14,\
 ennEmsg_save_pp,\
 ennEmsg_save_none,\
 ennEmsg_wait,\
 ennEmsg_values,\
 ennEmsg_itemK,\
 ennEmsg_itemUnk,\
 ennEmsg_badPair,\
 ennEmsg_pairDel,\
 ennEmsg_notavail,\
 ennEmsgs\
};\
 /* variabili: */\
extern VAL_VAR *valinp;\
extern VAL_VAR *valout;\
/* variabili statiche:\
	long\
 loStato;               stato della pagina\
	String\
 nnEzHpage,		pagina helpkit\
 nnEazMsgs[ennEmsgs],   messaggi all'utente\
 nnEszClose,            conferma uscita se modifiche pendenti\
 nnEszSetup;            conferma tutte inp-vars Note e tutte out-vars Non-note\
*/\
static long\
 loStato = NN_LIBERO;\
static String\
 nnEzHpage = "nnEdit",\
 nnEazMsgs[ennEmsgs] = {\
  "",\
  "saved file_14 and file_pp",\
  "saved file_14",\
  "saved file_pp",\
  "no file saved",\
  "Wait please...",\
  "no vars selected",\
  "item already marked Known",\
  "item already marked Unknown",\
  "conflicting selection",\
  "also the Pair will be deleted!",\
  "not available",\
 },\
 nnEszClose = "Do you want to save changes ?",\
 nnEszSetup = "Do you want ALL inp-var Known and ALL out-var Unknown ?";\
static /*XtCallbackProc*/ void\
 nnEcloseDlgCB(),\
 nnEsetupDlgCB();\
static Elenco_callback conferma_close = {\
 { "Yes",       nnEcloseDlgCB,  0 },\
 { "No" ,       nnEcloseDlgCB,  1 },\
 { "Cancel",    nnEcloseDlgCB,  2 } };\
static Elenco_callback conferma_setup = {\
 { "Ok",        nnEsetupDlgCB,  0 },\
 { "Cancel",    nnEsetupDlgCB,  1 },\
 { NULL,        NULL,           NULL } };\
static Find_struct\
 fsOut,\
 fsInp;\
/* funzioni: */\
\
\
extern swidget create_nnFilter( Widget, String);\
\
extern swidget create_nnValues( Widget, String, VAL_VAR *, int *);\
/*extern swidget create_nnGraph( void );*/\
\
/* variabili di istanza:\
Widget\
 nnE_labVars[8],\
 wgtFindOut,\
 wgtFindInp,\
 nnE_help;\
Find_struct\
 fsOut,\
 fsInp;\
VAL_VAR\
 *avvEdit;		[neqsis+nu] copia privata delle valout + valinp\
int\
 cKnown,		conta vars 'note'\
 cLinp, *aiLinp,	conta, [nu]    ipvrs di inp-vars Caricate;\
 cLout, *aiLout,	conta, [neqsis] ipvrs di out-vars Caricate;\
 cMinp, *aiMinp,	conta, [nu]     indici(0-) delle *aiLinp Marcate;\
 cMout, *aiMout,	conta, [neqsis] indici(0-) delle *aiLout Marcate;\
 cPair, mPair,		conta Paia totali, max Paia;\
 cPinp, *aiPinp,	conta, [mPair] posizioni(1-) delle *aiMinp Paiate;\
 cPout, *aiPout,	conta, [mPair] posizioni(1-) delle *aiMout Paiate;\
 iPinpSel, iPoutSel;	posizioni selezionate: =0 no, >0 si, <0 paio;\
char\
 **azPinp,      [mPair] nomi delle inp-vars Paiate in *aiMinp;\
 **azPout;      [mPair] nomi delle out-vars Paiate in *aiMout;\
XtIntervalId\
 idMsg;\
*/
*nnEdit.ispecdecl: /* variabili di istanza: */\
Widget\
 wCloseDlg,\
 wSetupDlg,\
 nnE_labVars[8],\
 wgtFindOut,\
 wgtFindInp,\
 nnE_help;\
String\
 nnEzH;\
VAL_VAR\
 *avvEdit;\
int\
 cKnown,\
 cLinp, *aiLinp,\
 cLout, *aiLout,\
 cMinp, *aiMinp,\
 cMout, *aiMout,\
 cPair, mPair,\
 cPinp, *aiPinp,\
 cPout, *aiPout,\
 iPinpSel, iPoutSel,\
 lastMsg;\
char\
 **azPinp,\
 **azPout;\
XtIntervalId\
 idMsg;\

*nnEdit.ispeclist: wCloseDlg, wSetupDlg, nnE_labVars, wgtFindOut, wgtFindInp, nnE_help, nnEzH, avvEdit, cKnown, cLinp, aiLinp, cLout, aiLout, cMinp, aiMinp, cMout, aiMout, cPair, mPair, cPinp, aiPinp, cPout, aiPout, iPinpSel, iPoutSel, lastMsg, azPinp, azPout, idMsg
*nnEdit.ispeclist.wCloseDlg: "Widget", "%wCloseDlg%"
*nnEdit.ispeclist.wSetupDlg: "Widget", "%wSetupDlg%"
*nnEdit.ispeclist.nnE_labVars: "Widget", "%nnE_labVars%[8]"
*nnEdit.ispeclist.wgtFindOut: "Widget", "%wgtFindOut%"
*nnEdit.ispeclist.wgtFindInp: "Widget", "%wgtFindInp%"
*nnEdit.ispeclist.nnE_help: "Widget", "%nnE_help%"
*nnEdit.ispeclist.nnEzH: "String", "%nnEzH%"
*nnEdit.ispeclist.avvEdit: "VAL_VAR", "*%avvEdit%"
*nnEdit.ispeclist.cKnown: "int", "%cKnown%"
*nnEdit.ispeclist.cLinp: "int", "%cLinp%"
*nnEdit.ispeclist.aiLinp: "int", "*%aiLinp%"
*nnEdit.ispeclist.cLout: "int", "%cLout%"
*nnEdit.ispeclist.aiLout: "int", "*%aiLout%"
*nnEdit.ispeclist.cMinp: "int", "%cMinp%"
*nnEdit.ispeclist.aiMinp: "int", "*%aiMinp%"
*nnEdit.ispeclist.cMout: "int", "%cMout%"
*nnEdit.ispeclist.aiMout: "int", "*%aiMout%"
*nnEdit.ispeclist.cPair: "int", "%cPair%"
*nnEdit.ispeclist.mPair: "int", "%mPair%"
*nnEdit.ispeclist.cPinp: "int", "%cPinp%"
*nnEdit.ispeclist.aiPinp: "int", "*%aiPinp%"
*nnEdit.ispeclist.cPout: "int", "%cPout%"
*nnEdit.ispeclist.aiPout: "int", "*%aiPout%"
*nnEdit.ispeclist.iPinpSel: "int", "%iPinpSel%"
*nnEdit.ispeclist.iPoutSel: "int", "%iPoutSel%"
*nnEdit.ispeclist.lastMsg: "int", "%lastMsg%"
*nnEdit.ispeclist.azPinp: "unsigned char", "**%azPinp%"
*nnEdit.ispeclist.azPout: "unsigned char", "**%azPout%"
*nnEdit.ispeclist.idMsg: "XtIntervalId", "%idMsg%"
*nnEdit.funcdecl: swidget create_nnEdit( String nnEzHfile)\

*nnEdit.funcname: create_nnEdit
*nnEdit.funcdef: "swidget", "<create_nnEdit>(%)"
*nnEdit.argdecl: String nnEzHfile;
*nnEdit.arglist: nnEzHfile
*nnEdit.arglist.nnEzHfile: "String", "%nnEzHfile%"
*nnEdit.icode: /* codice iniziale: */\
if (loStato & NN_OCCUPATO) {\
   fprintf( stderr, "\a");\
   return NULL;\
}\
/* legge file "f03.dat" per dati su blocchi e variabili */\
   if (read_file_f03()) {\
      printf( "\nCannot open file f03\n");\
      exit(1);\
   }\
/* legge file "f14.h" per valori e attributi delle variabili */\
   if (read_file_f14( neqsis, nu) ) {\
      printf( "Cannot open file f14\n");\
      exit(1);\
   }\
   printf( "\n");
*nnEdit.fcode: /* codice finale: */\
UxPopupInterface( rtrn, no_grab);\
\
{ char ahModel[22];\
   sprintf( ahModel, "Model name: %.8s", sigla);\
   UxPutStrRes( nnE_labModel, XmNlabelString, ahModel);\
}\
UxPutStrRes( nnE_dbMsg, XmNlabelString, nnEazMsgs[ennEmsg_null]);\
{ /* a[10] per find_kit() della libreria libutilx... */\
 Arg a[10];\
 Cardinal n;\
   n=0;\
   XtSetArg( a[n], XmNbottomAttachment, XmATTACH_FORM); n++;\
   XtSetArg( a[n], XmNleftAttachment, XmATTACH_WIDGET); n++;\
   XtSetArg( a[n], XmNleftOffset, 10); n++;\
   XtSetArg( a[n], XmNleftWidget, nnE_pbOdel ); n++;\
   wgtFindOut = find_kit( nnE_formOut, a, n, &fsOut );\
   fsOut.ID_lista = (Widget) nnE_sListLout;\
   n=0;\
   XtSetArg( a[n], XmNbottomAttachment, XmATTACH_FORM); n++;\
   XtSetArg( a[n], XmNleftAttachment, XmATTACH_WIDGET); n++;\
   XtSetArg( a[n], XmNleftOffset, 10); n++;\
   XtSetArg( a[n], XmNleftWidget, nnE_pbIdel ); n++;\
   wgtFindInp = find_kit( nnE_formInp, a, n, &fsInp );\
   fsInp.ID_lista = (Widget) nnE_sListLinp;\
}\
wCloseDlg = wSetupDlg = 0;\
nnEzH = strdup( nnEzHfile);\
nnE_help = helpkit_propInfo( nnE_mainWin, nnEzH, nnEzHpage);\
nnEloadCB( NULL, 0, 0);\
lastMsg = idMsg = 0;\
loStato |= NN_OCCUPATO;\
\
return(rtrn);\

*nnEdit.auxdecl: /* funzioni ausiliarie - prototipi: */\
static void libera_dati_privati( void);\
static void inizia_dati_privati( void);\
static void mostra_cLMP( void);\
static XtTimerCallbackProc msgOff( XtPointer data, XtIntervalId *id );\
static void msgOn( int e );\
static int ceInElencoInt( int iPos, int cElenco, int *aiElenco );\
static int ceInElencoStr( String zPos, int cElenco, String *azElenco );\
static void nnE_load_NN( void );\
static void nnE_load_PP( void );\
static void deletePair( int k );\
void fnnF_ritorna_E( int *);\
void fnnV_ritorna_E( Boolean);\
static void nnE_close_OK( void);\
static XtCallbackProc\
 nnEdestroyShellCB(),\
 nnEloadCB(),\
 nnEsaveCB(),\
 nnEcloseCB(),\
 nnEsetupCB(),\
 nnEsimpleCB_omuVars(),\
 nnEhelpCB();\
\
/* funzioni ausiliarie - definizioni: */\
/* ---------------------------------- */\
static void libera_dati_privati( void)\
{\
 int i;\
   XtFree( aiLinp);\
   XtFree( aiLout);\
   XtFree( aiMinp);\
   XtFree( aiMout);\
   XtFree( aiPinp);\
   XtFree( aiPout);\
   for (i=0; i<cPair; i++) {\
      XtFree( azPout[i]);\
      XtFree( azPinp[i]);\
   }\
   XtFree( azPinp);\
   XtFree( azPout);\
   XtFree( avvEdit);\
   if (idMsg)\
      XtRemoveTimeOut( idMsg);\
}\
\
/* ---------------------------------- */\
static void inizia_dati_privati( void)\
{\
 int i;\
   aiLinp = (int *) XtMalloc( sizeof(int) * nu);\
   aiLout = (int *) XtMalloc( sizeof(int) * neqsis);\
   aiMinp = (int *) XtMalloc( sizeof(int) * nu);\
   aiMout = (int *) XtMalloc( sizeof(int) * neqsis);\
   mPair = (neqsis > nu) ? nu : neqsis;\
   aiPinp = (int *) XtMalloc( sizeof(int) * mPair);\
   aiPout = (int *) XtMalloc( sizeof(int) * mPair);\
   azPinp = (char **) XtMalloc( sizeof(char *) * mPair);\
   azPout = (char **) XtMalloc( sizeof(char *) * mPair);\
   avvEdit = (VAL_VAR *) XtMalloc( sizeof(VAL_VAR) * (neqsis+nu) );\
   memcpy( &avvEdit[0], &valout[0], sizeof(VAL_VAR) * neqsis);\
   memcpy( &avvEdit[neqsis], &valinp[0], sizeof(VAL_VAR) * nu);\
   cKnown = 0;\
   for (i=0; i<neqsis+nu; i++)\
      if (avvEdit[i].noto)\
         cKnown++;\
   cPair = read_file_fpp( azPout, azPinp);\
   nnEsimpleCB_omuVars( NULL, NN_VARS_ALL, 0);\
   XmToggleButtonSetState( nnE_mu_pM_tN, True, True);\
}\
\
/* ---------------------------------- */\
static void mostra_cLMP( void)\
{\
 static char z[60], zF[] ="%d";\
   sprintf( z, zF, neqsis);\
   UxPutStrRes( nnE_labVars[4], XmNlabelString, z );\
   sprintf( z, zF, nu);\
   UxPutStrRes( nnE_labVars[6], XmNlabelString, z );\
   sprintf( z, zF, cKnown);\
   UxPutStrRes( nnE_labVars[7], XmNlabelString, z );\
   sprintf( z, zF, neqsis+nu-cKnown);\
   UxPutStrRes( nnE_labVars[5], XmNlabelString, z );\
   sprintf( z, "%d listed, %d unknown", cLinp, cMinp);\
   UxPutStrRes( nnE_labLinp, XmNlabelString, z );\
   sprintf( z, "%d listed, %d known", cLout, cMout);\
   UxPutStrRes( nnE_labLout, XmNlabelString, z );\
   sprintf( z, "%d paired (of %d)", cPinp, cPair);\
   UxPutStrRes( nnE_labMinp, XmNlabelString, z );\
   sprintf( z, "%d paired (of %d)", cPout, cPair);\
   UxPutStrRes( nnE_labMout, XmNlabelString, z );\
}\
\
/* ---------------------------------- */\
static XtTimerCallbackProc msgOff( XtPointer data, XtIntervalId *id )\
{\
   UxPutStrRes( nnE_dbMsg, XmNlabelString, nnEazMsgs[ennEmsg_null]);\
   idMsg = 0;\
}\
\
/* ---------------------------------- */\
static void msgOn( /*String z*/ int e )\
{\
 static unsigned long durata = 3000;\
   if (idMsg)\
      XtRemoveTimeOut( idMsg);\
   UxPutStrRes( nnE_dbMsg, XmNlabelString, nnEazMsgs[ lastMsg=e ]);\
   idMsg = XtAppAddTimeOut( UxAppContext, durata, msgOff, NULL);\
}\
\
/* ---------------------------------- */\
static int ceInElencoInt( int iPos, int cElenco, int *aiElenco )\
{\
 int i;\
   for (i=0; i<cElenco; i++)\
      if (iPos == aiElenco[i])\
         break;\
   return (i<cElenco) ? (i+1) : 0;\
}\
\
/* ---------------------------------- */\
static int ceInElencoStr( String zPos, int cElenco, String *azElenco )\
{\
 int i;\
   for (i=0; i<cElenco; i++)\
      if (strcmp( zPos, azElenco[i]) == 0)\
         break;\
   return (i<cElenco) ? (i+1) : 0;\
}\
\
/* ---------------------------------- */\
static void nnE_load_NN( void )\
{\
/* carica le liste nel modo Normal */\
 XmStringTable axsLout, axsLinp, axsMout, axsMinp;\
 char zL[2+100+1], zM[2+20];\
 int i, ibloc, j, ivj, ivk, k;\
   axsLout = (XmStringTable) XtMalloc( sizeof(XmString) * neqsis );\
   axsLinp = (XmStringTable) XtMalloc( sizeof(XmString) * nu );\
   axsMout = (XmStringTable) XtMalloc( sizeof(XmString) * neqsis );\
   axsMinp = (XmStringTable) XtMalloc( sizeof(XmString) * nu );\
   zL[1] =zM[1] =' ';\
   zL[2+100] ='\0';\
   for (i=0; i<cPair; i++)\
      aiPinp[i] =aiPout[i] =0;\
   for (i=0, cMout=cPout=0; i<cLout; i++) {\
      ivj =aiLout[i];\
      strncpy( zL +2, nom_sivar[ivj-1], 100);\
      if (avvEdit[ivj-1].noto) {\
         zL[0] = '*';\
         aiMout[cMout] =i;\
         strncpy( zM+2, sivar[ivj-1], 8);\
         zM[2+8] ='\0';\
         if (k = ceInElencoStr( zM+2, cPair, azPout)) {\
            zM[0] ='-';\
            strcat( zM, "-");\
            strcat( zM, azPinp[k-1]);\
            aiPout[k-1] = cMout +1;\
            cPout++;\
         } else\
            zM[0] =' ';\
         axsMout[cMout++] = XmStringCreateSimple( zM );\
      } else\
         zL[0] = ' ';\
      axsLout[i] = XmStringCreateSimple( zL );\
   }\
   for (i=0, cMinp=cPinp=0; i<cLinp; i++) {\
      ivj =aiLinp[i];\
      strncpy( zL +2, nom_vari[-ivj-1], 100);\
      if (! avvEdit[neqsis-ivj-1].noto) {\
         zL[0] = ' ';\
         aiMinp[cMinp] =i;\
         strncpy( zM+2, vari[-ivj-1], 8);\
         zM[2+8] ='\0';\
         if (k = ceInElencoStr( zM+2, cPair, azPinp)) {\
            zM[0] ='-';\
            strcat( zM, "-");\
            strcat( zM, azPout[k-1]);\
            aiPinp[k-1] = cMinp +1;\
            cPinp++;\
         } else\
            zM[0] =' ';\
         axsMinp[cMinp++] = XmStringCreateSimple( zM );\
      } else\
         zL[0] = '*';\
      axsLinp[i] = XmStringCreateSimple( zL );\
   }\
   for (i=0; i<cPair; i++) {\
      if (!aiPout[i]) {\
         for (k=0; k<neqsis; k++)\
            if (strncmp( sivar[k], azPout[i], 8) == 0)\
               break;\
         aiPout[i] = -k-1;\
      }\
      if (!aiPinp[i]) {\
         for (k=0; k<nu; k++)\
            if (strncmp( vari[k], azPinp[i], 8) == 0)\
               break;\
         aiPinp[i] = -k-1;\
      }\
   }\
   XmListDeleteAllItems( nnE_sListLinp);\
   XmListDeleteAllItems( nnE_sListMinp);\
   XmListDeleteAllItems( nnE_sListLout);\
   XmListDeleteAllItems( nnE_sListMout);\
   XtVaSetValues( nnE_sListLout,\
    XmNitemCount, cLout,\
    XmNitems, axsLout,\
    NULL );\
   XtVaSetValues( nnE_sListMout,\
    XmNitemCount, cMout,\
    XmNitems, axsMout,\
    NULL );\
   XtVaSetValues( nnE_sListLinp,\
    XmNitemCount, cLinp,\
    XmNitems, axsLinp,\
    NULL );\
   XtVaSetValues( nnE_sListMinp,\
    XmNitemCount, cMinp,\
    XmNitems, axsMinp,\
    NULL );\
   for (i=0; i<cLout; i++)\
      XmStringFree( axsLout[i]);\
   for (i=0; i<cLinp; i++)\
      XmStringFree( axsLinp[i]);\
   for (i=0; i<cMout; i++)\
      XmStringFree( axsMout[i]);\
   for (i=0; i<cMinp; i++)\
      XmStringFree( axsMinp[i]);\
   XtFree( axsLout);\
   XtFree( axsLinp);\
   XtFree( axsMout);\
   XtFree( axsMinp);\
   mostra_cLMP();\
   XtSetSensitive( nnE_pbIadd, False);\
   XtSetSensitive( nnE_pbIdel, False);\
   XtSetSensitive( nnE_pbOadd, False);\
   XtSetSensitive( nnE_pbOdel, False);\
}\
\
/* ---------------------------------- */\
static void nnE_load_PP( void )\
{\
/* carica le liste nel Modo PP */\
 XmStringTable axsMout, axsMinp;\
 char zM[20];\
 int ivj, ivk, k, i;\
   axsMout = (XmStringTable) XtMalloc( sizeof(XmString) * neqsis );\
   axsMinp = (XmStringTable) XtMalloc( sizeof(XmString) * nu );\
   zM[1] =' ';\
   cMinp =cMout =cPinp =cPout =0;\
   for (ivj=0; ivj<neqsis; ivj++) {\
      if (! avvEdit[ivj].noto)\
         continue;\
      aiMout[cMout] = ivj;\
      strncpy( zM+2, sivar[ivj], 8);\
      zM[2+8] ='\0';\
      for (k=0; k<cPair; k++)\
         if (strcmp( zM+2, azPout[k]) == 0)\
            break;\
      if (k<cPair) {\
         zM[0] ='-';\
         strcat( zM, "-");\
         strcat( zM, azPinp[k]);\
         aiPout[k] = cMout +1;\
         cPout++;\
      } else\
         zM[0] =' ';\
      axsMout[cMout++] = XmStringCreateSimple( zM );\
   }\
   for (ivj=0; ivj<nu; ivj++) {\
      if (avvEdit[neqsis+ivj].noto)\
         continue;\
      aiMinp[cMinp] = ivj;\
      strncpy( zM+2, vari[ivj], 8);\
      zM[2+8] ='\0';\
      for (k=0; k<cPair; k++)\
         if (strcmp( zM+2, azPinp[k]) == 0)\
            break;\
      if (k<cPair) {\
         zM[0] ='-';\
         strcat( zM, "-");\
         strcat( zM, azPout[k]);\
         aiPinp[k] = cMinp +1;\
         cPinp++;\
      } else\
         zM[0] =' ';\
      axsMinp[cMinp++] = XmStringCreateSimple( zM );\
   }\
   XmListDeselectAllItems( nnE_sListMinp);\
   XmListDeselectAllItems( nnE_sListMout);\
   XtVaSetValues( nnE_sListMout,\
    XmNitemCount, cMout,\
    XmNitems, axsMout,\
    NULL );\
   XtVaSetValues( nnE_sListMinp,\
    XmNitemCount, cMinp,\
    XmNitems, axsMinp,\
    NULL );\
   for (i=0; i<cMout; i++)\
      XmStringFree( axsMout[i]);\
   for (i=0; i<cMinp; i++)\
      XmStringFree( axsMinp[i]);\
   XtFree( axsMout);\
   XtFree( axsMinp);\
   mostra_cLMP();\
   XtSetSensitive( nnE_pbPadd, False);\
   XtSetSensitive( nnE_pbPdel, False);\
   iPinpSel =iPoutSel =0;\
}\
\
/* ---------------------------------- */\
static void deletePair( int k )\
{\
   XtFree( azPout[k-1]);\
   XtFree( azPinp[k-1]);\
   for (; k<cPair; k++) {\
      azPout[k-1] = azPout[k];\
      azPinp[k-1] = azPinp[k];\
      aiPout[k-1] = aiPout[k];\
      aiPinp[k-1] = aiPinp[k];\
   }\
   cPair--;\
   aiPinp[cPair] =aiPout[cPair] =0;\
}\
\
/* ---------------------------------- */\
void fnnF_ritorna_E( int *aiEsito)\
{\
 int i;\
   if (aiEsito) {\
      cLout =aiEsito[0];\
      cLinp =aiEsito[1];\
      for (i=0; i<cLout; i++)\
         aiLout[i] = aiEsito[2+i];\
      for (i=0; i<cLinp; i++)\
         aiLinp[i] = neqsis -aiEsito[2+cLout+i];\
      nnE_load_NN();\
   }\
}\
\
/* ---------------------------------- */\
void fnnV_ritorna_E( Boolean ok)\
{\
   if (ok)\
      loStato |= NN_CHG_NN;\
}\
\
/* ---------------------------------- */\
static void nnE_close_OK( void)\
{\
   UxDestroyInterface( nnEdit);\
   exit(0);\
}\
\
/* ---------------------------------- */\
static XtCallbackProc nnEdestroyShellCB(\
 Widget UxWidget, XtPointer pC, XmAnyCallbackStruct *pA )\
{ /* risponde a UxDestroyInterface() e a Close da Shell */\
   libera_dati_privati();\
   XtFree( nnEzH);\
   loStato = NN_LIBERO;\
   exit(0);\
}\
\
/* ---------------------------------- */\
static XtCallbackProc nnEloadCB(\
 Widget UxWidget, XtPointer pC, XmAnyCallbackStruct *pA )\
{ /* carica/ripristina marcature e paia */\
 int i;\
   if (loStato & NN_OCCUPATO)\
      libera_dati_privati();\
   inizia_dati_privati();\
   if (loStato & NN_OCCUPATO) {\
      if (loStato & NN_MODE_NN)\
         nnE_load_NN();\
      else\
         nnE_load_PP();\
   }\
   loStato &= (~NN_CHG_NN & ~NN_CHG_PP);\
}\
\
/* ---------------------------------- */\
static XtCallbackProc nnEsaveCB(\
 Widget UxWidget, XtPointer pC, XmAnyCallbackStruct *pA )\
{\
/* salva marcature e paia */\
 FILE *fp;\
 int bNN, bPP, e;\
   bNN = loStato & NN_CHG_NN;\
   bPP = loStato & NN_CHG_PP;\
   if (bNN) {\
      memcpy( &valout[0], &avvEdit[0], sizeof(VAL_VAR) * neqsis);\
      memcpy( &valinp[0], &avvEdit[neqsis], sizeof(VAL_VAR) * nu);\
      fp = fopen( FILE_F14, "w" );\
      write_file_f14( fp);\
      fclose( fp);\
   }\
   if (bPP) {\
      write_file_fpp( sigla, cPair, azPout, azPinp);\
   }\
   if (bNN) {\
      e = (bPP) ? ennEmsg_save_14_pp : ennEmsg_save_14;\
   } else {\
      e = (bPP) ? ennEmsg_save_pp : ennEmsg_save_none;\
   }\
   msgOn( e );\
   loStato &= (~NN_CHG_NN & ~NN_CHG_PP);\
}\
\
/* ---------------------------------- */\
static XtCallbackProc nnEcloseCB(\
 Widget UxWidget, XtPointer pC, XmAnyCallbackStruct *pA )\
{ /* chiude la pagina 'nnEdit' */\
   if (loStato & NN_CHG_NN || loStato & NN_CHG_PP) {\
      if (!wCloseDlg)\
         wCloseDlg = conferma( UxTopLevel, nnEszClose, conferma_close );\
      XtManageChild( wCloseDlg);\
   } else\
      nnE_close_OK();\
}\
\
/* ---------------------------------- */\
static /*XtCallbackProc*/ void nnEcloseDlgCB(\
 Widget UxWidget, int iC, XmAnyCallbackStruct *pA )\
{ /* risponde al WarningDialog aperto da Menu File->Close */\
   if (iC == 2) {\
      XtUnmanageChild( wCloseDlg );\
      return;\
   }\
   if (iC == 0)\
      nnEsaveCB( NULL, 0, 0);\
   nnE_close_OK();\
}\
\
/* ---------------------------------- */\
static XtCallbackProc nnEsetupCB(\
 Widget UxWidget, XtPointer pC, XmAnyCallbackStruct *pA )\
{ /* risponde a Menu Options->Setup */\
   if (!wSetupDlg)\
      wSetupDlg = conferma( UxTopLevel, nnEszSetup, conferma_setup );\
   XtManageChild( wSetupDlg);\
}\
\
/* ---------------------------------- */\
static /*XtCallbackProc*/ void nnEsetupDlgCB(\
 Widget UxWidget, int iC, XmAnyCallbackStruct *pA )\
{ /* risponde al Dialogo aperto da Menu Options->Setup */\
 int ivj;\
   if (iC == 0) {\
      for (ivj=0; ivj<neqsis; ivj++)\
         avvEdit[ivj].noto = False;\
      for (ivj=0; ivj<nu; ivj++)\
         avvEdit[neqsis+ivj].noto = True;\
      cKnown = nu;\
      loStato |= NN_CHG_NN;\
      while (cPair)\
         deletePair( cPair +1 );\
      cPair = 0;\
      loStato |= NN_CHG_PP;\
      nnEsaveCB( NULL, 0, 0);\
      nnE_load_NN();\
   }\
   XtUnmanageChild( wSetupDlg );\
}\
\
/* ---------------------------------- */\
static XtCallbackProc nnEsimpleCB_omuVars(\
 Widget UxWidget, int q, XmPushButtonCallbackStruct *pA )\
{\
/* carica variabili (tutte, o filtrate) */\
 int i;\
   switch (q) {\
   case NN_VARS_ALL:\
      cLout =neqsis;\
      cLinp =nu;\
      for (i=0; i<cLout; i++)\
         aiLout[i] = i+1;\
      for (i=0; i<cLinp; i++)\
         aiLinp[i] = -(i+1);\
      if (UxWidget)\
         nnE_load_NN();\
      break;\
   case NN_VARS_FILTER:\
\
      create_nnFilter( UxWidget, nnEzH);\
\
      break;\
   default:\
     break;\
   }\
}\
\
/* ---------------------------------- */\
static XtCallbackProc nnEhelpCB(\
 Widget wgt, XtPointer pC, XmPushButtonCallbackStruct *pA )\
{\
/* espone Aiuti in linea */\
   XtManageChild( nnE_help);\
}\
/* ---------------------------------- */
*nnEdit.name: nnEdit
*nnEdit.width: 806
*nnEdit.height: 648
*nnEdit.deleteResponse: "destroy"
*nnEdit.x: 314
*nnEdit.y: 151
*nnEdit.destroyCallback.source: public
*nnEdit.destroyCallback: nnEdestroyShellCB

*nnE_mainWin.class: mainWindow
*nnE_mainWin.parent: nnEdit
*nnE_mainWin.static: true
*nnE_mainWin.name: nnE_mainWin
*nnE_mainWin.unitType: "pixels"
*nnE_mainWin.helpCallback.source: public
*nnE_mainWin.helpCallback: nnEhelpCB

*nnE_mu.class: rowColumn
*nnE_mu.parent: nnE_mainWin
*nnE_mu.static: true
*nnE_mu.name: nnE_mu
*nnE_mu.rowColumnType: "menu_bar"
*nnE_mu.menuAccelerator: "<KeyUp>F10"
*nnE_mu.menuHelpWidget: "nnE_mu_top_bH"

*nnE_mu_pF.class: rowColumn
*nnE_mu_pF.parent: nnE_mu
*nnE_mu_pF.static: true
*nnE_mu_pF.name: nnE_mu_pF
*nnE_mu_pF.rowColumnType: "menu_pulldown"

*nnE_mu_pF_bL.class: pushButton
*nnE_mu_pF_bL.parent: nnE_mu_pF
*nnE_mu_pF_bL.static: true
*nnE_mu_pF_bL.name: nnE_mu_pF_bL
*nnE_mu_pF_bL.labelString: "Load"
*nnE_mu_pF_bL.activateCallback.source: public
*nnE_mu_pF_bL.activateCallback: nnEloadCB

*nnE_mu_pF_bS.class: pushButton
*nnE_mu_pF_bS.parent: nnE_mu_pF
*nnE_mu_pF_bS.static: true
*nnE_mu_pF_bS.name: nnE_mu_pF_bS
*nnE_mu_pF_bS.labelString: "Save"
*nnE_mu_pF_bS.activateCallback.source: public
*nnE_mu_pF_bS.activateCallback: nnEsaveCB

*nnE_mu_pF_bZ.class: pushButton
*nnE_mu_pF_bZ.parent: nnE_mu_pF
*nnE_mu_pF_bZ.static: true
*nnE_mu_pF_bZ.name: nnE_mu_pF_bZ
*nnE_mu_pF_bZ.labelString: "Close"
*nnE_mu_pF_bZ.activateCallback.source: public
*nnE_mu_pF_bZ.activateCallback: nnEcloseCB

*nnE_mu_pM.class: rowColumn
*nnE_mu_pM.parent: nnE_mu
*nnE_mu_pM.static: true
*nnE_mu_pM.name: nnE_mu_pM
*nnE_mu_pM.rowColumnType: "menu_pulldown"
*nnE_mu_pM.radioBehavior: "true"

*nnE_mu_pM_tN.class: toggleButton
*nnE_mu_pM_tN.parent: nnE_mu_pM
*nnE_mu_pM_tN.static: true
*nnE_mu_pM_tN.name: nnE_mu_pM_tN
*nnE_mu_pM_tN.labelString: "Normal"
*nnE_mu_pM_tN.valueChangedCallback: {\
/* imposta modo Normale */\
 XmToggleButtonCallbackStruct *pA =\
(XmToggleButtonCallbackStruct *)UxCallbackArg;\
   if (pA->set && !(loStato & NN_MODE_NN)) {\
      loStato |= NN_MODE_NN;\
      XtSetSensitive( nnE_mu_pO, True);\
      XtSetSensitive( nnE_pbPadd, False);\
      XtSetSensitive( nnE_pbPdel, False);\
      XtSetSensitive( nnE_omuVars, True);\
      nnE_load_NN();\
   }\
}

*nnE_mu_pM_tP.class: toggleButton
*nnE_mu_pM_tP.parent: nnE_mu_pM
*nnE_mu_pM_tP.static: true
*nnE_mu_pM_tP.name: nnE_mu_pM_tP
*nnE_mu_pM_tP.labelString: "Pairs"
*nnE_mu_pM_tP.valueChangedCallback: {\
/* imposta modo Paia */\
 XmToggleButtonCallbackStruct *pA =\
(XmToggleButtonCallbackStruct *)UxCallbackArg;\
   if (pA->set && (loStato & NN_MODE_NN)) {\
      loStato &= ~NN_MODE_NN;\
      XtSetSensitive( nnE_mu_pO, False);\
      XtSetSensitive( nnE_omuVars, False);\
      XmListDeleteAllItems( nnE_sListLinp);\
      XmListDeleteAllItems( nnE_sListLout);\
      XtSetSensitive( nnE_pbIadd, False);\
      XtSetSensitive( nnE_pbIdel, False);\
      XtSetSensitive( nnE_pbOadd, False);\
      XtSetSensitive( nnE_pbOdel, False);\
      nnE_load_PP();\
   }\
}

*nnE_mu_pO.class: rowColumn
*nnE_mu_pO.parent: nnE_mu
*nnE_mu_pO.static: true
*nnE_mu_pO.name: nnE_mu_pO
*nnE_mu_pO.rowColumnType: "menu_pulldown"

*nnE_mu_pO_bG.class: pushButton
*nnE_mu_pO_bG.parent: nnE_mu_pO
*nnE_mu_pO_bG.static: true
*nnE_mu_pO_bG.name: nnE_mu_pO_bG
*nnE_mu_pO_bG.labelString: "Graph"
*nnE_mu_pO_bG.activateCallback: {\
/* apre pagina grafica */\
   /*create_nnGraph();*/\
   msgOn( ennEmsg_notavail );\
}

*nnE_mu_pO_bV.class: pushButton
*nnE_mu_pO_bV.parent: nnE_mu_pO
*nnE_mu_pO_bV.static: true
*nnE_mu_pO_bV.name: nnE_mu_pO_bV
*nnE_mu_pO_bV.labelString: "Values"
*nnE_mu_pO_bV.activateCallback: {\
/* apre pagina ancillare 'nnValues' per editare valori */\
 int i, *aiI, cI, *aiO, cO, cValues, *aiValues;\
   if (!XmListGetSelectedPos( nnE_sListLinp, &aiI, &cI))\
      cI = 0;\
   if (!XmListGetSelectedPos( nnE_sListLout, &aiO, &cO))\
      cO = 0;\
   if (cValues = cI+cO) {\
      aiValues = (int *)XtMalloc( sizeof(int) * (1 + cValues) );\
      aiValues[0] = cValues;\
      if (cO) {\
         for (i=0; i<cO; i++)\
            aiValues[1+i] = aiLout[aiO[i]-1];\
         XtFree( aiO);\
      }\
      if (cI) {\
         for (i=0; i<cI; i++)\
            aiValues[1+cO+i] = aiLinp[aiI[i]-1];\
         XtFree( aiI);\
      }\
      create_nnValues( UxWidget, nnEzH, avvEdit, aiValues);\
      XtFree( aiValues);\
   } else\
      msgOn( ennEmsg_values );\
}

*nnE_mu_pO_sep.class: separator
*nnE_mu_pO_sep.parent: nnE_mu_pO
*nnE_mu_pO_sep.static: true
*nnE_mu_pO_sep.name: nnE_mu_pO_sep

*nnE_mu_pO_bK.class: pushButton
*nnE_mu_pO_bK.parent: nnE_mu_pO
*nnE_mu_pO_bK.static: true
*nnE_mu_pO_bK.name: nnE_mu_pO_bK
*nnE_mu_pO_bK.labelString: "all Var Startup"
*nnE_mu_pO_bK.activateCallback.source: public
*nnE_mu_pO_bK.activateCallback: nnEsetupCB

*nnE_mu_pH.class: rowColumn
*nnE_mu_pH.parent: nnE_mu
*nnE_mu_pH.static: true
*nnE_mu_pH.name: nnE_mu_pH
*nnE_mu_pH.rowColumnType: "menu_pulldown"

*nnE_mu_pH_bP.class: pushButton
*nnE_mu_pH_bP.parent: nnE_mu_pH
*nnE_mu_pH_bP.static: true
*nnE_mu_pH_bP.name: nnE_mu_pH_bP
*nnE_mu_pH_bP.labelString: "on Page"
*nnE_mu_pH_bP.activateCallback.source: public
*nnE_mu_pH_bP.activateCallback: nnEhelpCB

*nnE_mu_top_bF.class: cascadeButton
*nnE_mu_top_bF.parent: nnE_mu
*nnE_mu_top_bF.static: true
*nnE_mu_top_bF.name: nnE_mu_top_bF
*nnE_mu_top_bF.labelString: "File"
*nnE_mu_top_bF.subMenuId: "nnE_mu_pF"

*nnE_mu_top_bM.class: cascadeButtonGadget
*nnE_mu_top_bM.parent: nnE_mu
*nnE_mu_top_bM.static: true
*nnE_mu_top_bM.name: nnE_mu_top_bM
*nnE_mu_top_bM.labelString: "Mode"
*nnE_mu_top_bM.subMenuId: "nnE_mu_pM"

*nnE_mu_top_bO.class: cascadeButtonGadget
*nnE_mu_top_bO.parent: nnE_mu
*nnE_mu_top_bO.static: true
*nnE_mu_top_bO.name: nnE_mu_top_bO
*nnE_mu_top_bO.labelString: "Options"
*nnE_mu_top_bO.subMenuId: "nnE_mu_pO"

*nnE_mu_top_bH.class: cascadeButton
*nnE_mu_top_bH.parent: nnE_mu
*nnE_mu_top_bH.static: true
*nnE_mu_top_bH.name: nnE_mu_top_bH
*nnE_mu_top_bH.labelString: "Help"
*nnE_mu_top_bH.subMenuId: "nnE_mu_pH"

*nnE_form.class: form
*nnE_form.parent: nnE_mainWin
*nnE_form.static: true
*nnE_form.name: nnE_form
*nnE_form.marginHeight: 10
*nnE_form.marginWidth: 10

*nnE_labModel.class: label
*nnE_labModel.parent: nnE_form
*nnE_labModel.static: true
*nnE_labModel.name: nnE_labModel
*nnE_labModel.rightAttachment: "attach_form"
*nnE_labModel.leftAttachment: "attach_form"
*nnE_labModel.topAttachment: "attach_form"
*nnE_labModel.topOffset: 10

*nnE_formVars.class: form
*nnE_formVars.parent: nnE_form
*nnE_formVars.static: true
*nnE_formVars.name: nnE_formVars
*nnE_formVars.resizePolicy: "resize_none"
*nnE_formVars.height: 40
*nnE_formVars.leftAttachment: "attach_form"
*nnE_formVars.rightAttachment: "attach_form"
*nnE_formVars.topAttachment: "attach_widget"
*nnE_formVars.topWidget: "nnE_labModel"
*nnE_formVars.topOffset: 10
*nnE_formVars.createCallback: {\
 static String saz[8] = {\
  "Equations:", "Unknown:", "Input vars:", "Known:",\
  "EquationsD", "UnknownD", "Input varsD", "KnownD",\
 };\
 static Arg a[12] = {\
  { XmNtopAttachment, XmATTACH_POSITION },\
  { XmNbottomAttachment, XmATTACH_POSITION },\
  { XmNleftAttachment, XmATTACH_POSITION },\
  { XmNrightAttachment, XmATTACH_POSITION },\
  { XmNtopPosition, -1 },\
  { XmNbottomPosition, -1 },\
  { XmNleftPosition, -1 },\
  { XmNrightPosition, -1 },\
  { XmNborderWidth, -1 },\
  { XmNleftOffset, 10 },\
  { XmNrightOffset, 10 },\
  { XmNalignment, XmALIGNMENT_CENTER },\
 };\
 static int\
  saiTopBottom[3] = { 0, 50, 100 },\
  saiLeftRight[5] = { 0, 25, 50, 75, 100 },\
  saiBorderWidth[2] = { 0, 1 };\
 int i, j, k;\
   for (j=0, k=0; j<2; j++) {\
      a[4].value = saiTopBottom[j];\
      a[5].value = saiTopBottom[j+1];\
      a[8].value = saiBorderWidth[j];\
      for (i=0; i<4; i++, k++) {\
         a[6].value = saiLeftRight[i];\
         a[7].value = saiLeftRight[i+1];\
         nnE_labVars[k] = XtCreateWidget( saz[k],\
          xmLabelWidgetClass, UxWidget, a, 12 );\
      }\
   }\
   XtManageChildren( nnE_labVars, 8);\
}

*nnE_scale.class: scale
*nnE_scale.parent: nnE_form
*nnE_scale.static: true
*nnE_scale.name: nnE_scale
*nnE_scale.orientation: "horizontal"
*nnE_scale.topAttachment: "attach_widget"
*nnE_scale.topWidget: "nnE_formVars"
*nnE_scale.rightAttachment: "attach_form"
*nnE_scale.rightOffset: 10
*nnE_scale.maximum: 80
*nnE_scale.minimum: 60
*nnE_scale.value: 70
*nnE_scale.showValue: "true"
*nnE_scale.valueChangedCallback: {\
 XmScaleCallbackStruct *pA =\
(XmScaleCallbackStruct *)UxCallbackArg;\
/*\
 Arg a[1];\
   XtSetArg( a[0], XmNrightPosition, pA->value);\
   XtSetValues( nnE_sWinLout, a, 1);\
   XtSetValues( nnE_sWinLinp, a, 1);\
*/\
   set_something( nnE_sWinLout, XmNrightPosition, pA->value);\
   set_something( nnE_sWinLinp, XmNrightPosition, pA->value);\
}

*nnE_panedWin.class: panedWindow
*nnE_panedWin.parent: nnE_form
*nnE_panedWin.static: true
*nnE_panedWin.name: nnE_panedWin
*nnE_panedWin.bottomAttachment: "attach_form"
*nnE_panedWin.leftAttachment: "attach_form"
*nnE_panedWin.rightAttachment: "attach_form"
*nnE_panedWin.topAttachment: "attach_widget"
*nnE_panedWin.topWidget: "nnE_scale"
*nnE_panedWin.width: 790

*nnE_formOut.class: form
*nnE_formOut.parent: nnE_panedWin
*nnE_formOut.static: true
*nnE_formOut.name: nnE_formOut
*nnE_formOut.paneMinimum: 160
*nnE_formOut.x: 3
*nnE_formOut.y: 3
*nnE_formOut.height: 237
*nnE_formOut.shadowThickness: 2
*nnE_formOut.marginHeight: 5
*nnE_formOut.marginWidth: 5

*nnE_labOut.class: label
*nnE_labOut.parent: nnE_formOut
*nnE_labOut.static: true
*nnE_labOut.name: nnE_labOut
*nnE_labOut.leftAttachment: "attach_form"
*nnE_labOut.rightAttachment: "attach_form"
*nnE_labOut.labelString: "Output variables"
*nnE_labOut.topAttachment: "attach_form"

*nnE_labLout.class: label
*nnE_labLout.parent: nnE_formOut
*nnE_labLout.static: true
*nnE_labLout.name: nnE_labLout
*nnE_labLout.leftAttachment: "attach_form"
*nnE_labLout.leftOffset: 10
*nnE_labLout.topAttachment: "attach_widget"
*nnE_labLout.topWidget: "nnE_labOut"

*nnE_labMout.class: label
*nnE_labMout.parent: nnE_formOut
*nnE_labMout.static: true
*nnE_labMout.name: nnE_labMout
*nnE_labMout.topAttachment: "attach_opposite_widget"
*nnE_labMout.topWidget: "nnE_labLout"
*nnE_labMout.rightAttachment: "attach_form"
*nnE_labMout.rightOffset: 10

*nnE_pbOadd.class: pushButton
*nnE_pbOadd.parent: nnE_formOut
*nnE_pbOadd.static: true
*nnE_pbOadd.name: nnE_pbOadd
*nnE_pbOadd.leftAttachment: "attach_form"
*nnE_pbOadd.activateCallback: {\
/* marca 'note' le out-var selezionate a sx */\
 int *aiPos, cPos, iS, i;\
 char zL[2+100+1], zM[2+8+1];\
 XmString xsL, xsM;\
   XmListGetSelectedPos( nnE_sListLout, &aiPos, &cPos );\
   zL[0] ='*';\
   zL[1] =zM[0] =zM[1] =' ';\
   zL[2+100] =zM[2+8] ='\0';\
   while (cPos) {\
      iS = aiPos[--cPos] -1;\
      if (ceInElencoInt( iS, cMout, aiMout))\
         continue;\
      for (i=cMout; i>0; i--)\
         if (aiMout[i-1] > iS)\
            aiMout[i] =aiMout[i-1];\
         else\
            break;\
      aiMout[i] = iS;\
      strncpy( zL+2, nom_sivar[aiLout[iS]-1], 100);\
      xsL =XmStringCreateSimple( zL);\
      XmListReplaceItemsPos( nnE_sListLout, &xsL, 1, iS+1 );\
      strncpy( zM+2, sivar[aiLout[iS]-1], 8);\
      xsM =XmStringCreateSimple( zM);\
      XmListAddItem( nnE_sListMout, xsM, i +1);\
      for (i=0; i<cPout; i++)\
         if (aiPout[i] > iS)\
            aiPout[i]++;\
      XmStringFree( xsL);\
      XmStringFree( xsM);\
      cMout++;\
      avvEdit[ aiLout[iS]-1].noto = True;\
      cKnown++;\
      loStato |=NN_CHG_NN;\
   }\
   XtFree( aiPos);\
   set_something( nnE_sListMout, XmNvisibleItemCount, cMout);\
   mostra_cLMP();\
   XmListDeselectAllItems( nnE_sListLout);\
   XtSetSensitive( UxWidget, False);\
}
*nnE_pbOadd.height: 35
*nnE_pbOadd.bottomAttachment: "attach_form"
*nnE_pbOadd.bottomOffset: 5
*nnE_pbOadd.labelString: " Mark "

*nnE_pbOdel.class: pushButton
*nnE_pbOdel.parent: nnE_formOut
*nnE_pbOdel.static: true
*nnE_pbOdel.name: nnE_pbOdel
*nnE_pbOdel.leftAttachment: "attach_widget"
*nnE_pbOdel.activateCallback: {\
/* marca 'non-note' le out-var selezionate a dx */\
 int *aiPos, cPos, iS, iM, iP, jP, jM, i;\
 char zL[2+100+1], zM[2+8+1];\
 XmString xsL, xsM;\
if (XmListGetSelectedPos( nnE_sListMout, &aiPos, &cPos )) {\
   zL[1] = zM[0] = zM[1] = ' ';\
   zL[2+100] ='\0';\
   while (cPos) {\
      iS = aiPos[--cPos];\
      iM =aiMout[iS-1];\
      zL[0] = ' ';\
      strncpy( zL+2, nom_sivar[aiLout[iM]-1], 100);\
      xsL =XmStringCreateSimple( zL);\
      XmListReplaceItemsPos( nnE_sListLout, &xsL, 1, iM+1 );\
      XmStringFree( xsL);\
      XmListDeletePos( nnE_sListMout, iS );\
      for (i=iS; i<cMout; i++)\
         aiMout[i-1] =aiMout[i];\
      cMout--;\
      avvEdit[aiLout[iM]-1].noto = False;\
      cKnown--;\
      loStato |= NN_CHG_NN;\
      if (iP = ceInElencoInt( iS, cPair, aiPout)) {\
         if ((jP=aiPinp[iP-1]) > 0) {\
          int *ajPos, cjPos;\
            jM = aiLinp[aiMinp[jP-1]];\
            zL[0] ='*';\
            strncpy( zL+2, nom_vari[-jM-1], 100);\
            xsL =XmStringCreateSimple( zL);\
            XmListReplaceItemsPos( nnE_sListLinp, &xsL, 1, aiMinp[jP-1]+1 );\
            XmStringFree( xsL);\
            if (XmListGetSelectedPos( nnE_sListMinp, &ajPos, &cjPos)) {\
               if (i = ceInElencoInt( jP, cjPos, ajPos))\
                  XmListSelectPos( nnE_sListMinp, jP, True);\
               XtFree( ajPos);\
            }\
            XmListDeletePos( nnE_sListMinp, jP);\
            for (i=jP; i<cMinp; i++)\
               aiMinp[i-1] =aiMinp[i];\
            cMinp--;\
            for (i=0; i<cPair; i++)\
               if (aiPinp[i]>jP)\
                  aiPinp[i]--;\
            cPinp--;\
         } else\
            jM = jP;\
         deletePair( iP);\
         for (i=0; i<cPair; i++)\
            if (aiPout[i]>iS)\
               aiPout[i]--;\
         cPout--;\
         avvEdit[neqsis-jM-1].noto = True;\
         cKnown++;\
         loStato |= NN_CHG_PP;\
      }\
   }\
   XmListDeselectAllItems( nnE_sListMout);\
   set_something( nnE_sListMout, XmNvisibleItemCount, cMout ? cMout : 1);\
   set_something( nnE_sListMinp, XmNvisibleItemCount, cMinp ? cMinp : 1);\
   mostra_cLMP();\
   XtFree( aiPos);\
   }\
   XtSetSensitive( UxWidget, False);\
}
*nnE_pbOdel.leftWidget: "nnE_pbOadd"
*nnE_pbOdel.leftOffset: 10
*nnE_pbOdel.height: 35
*nnE_pbOdel.labelString: "Unmark"
*nnE_pbOdel.bottomAttachment: "attach_form"
*nnE_pbOdel.bottomOffset: 5

*nnE_sWinLout.class: scrolledWindow
*nnE_sWinLout.parent: nnE_formOut
*nnE_sWinLout.static: true
*nnE_sWinLout.name: nnE_sWinLout
*nnE_sWinLout.scrollingPolicy: "application_defined"
*nnE_sWinLout.visualPolicy: "variable"
*nnE_sWinLout.scrollBarDisplayPolicy: "static"
*nnE_sWinLout.topAttachment: "attach_widget"
*nnE_sWinLout.topWidget: "nnE_labLout"
*nnE_sWinLout.bottomAttachment: "attach_widget"
*nnE_sWinLout.bottomWidget: "nnE_pbOadd"
*nnE_sWinLout.leftAttachment: "attach_form"
*nnE_sWinLout.rightAttachment: "attach_position"
*nnE_sWinLout.rightPosition: 70
*nnE_sWinLout.bottomOffset: 5
*nnE_sWinLout.shadowThickness: 0

*nnE_sListLout.class: scrolledList
*nnE_sListLout.parent: nnE_sWinLout
*nnE_sListLout.static: true
*nnE_sListLout.name: nnE_sListLout
*nnE_sListLout.selectionPolicy: "single_select"
*nnE_sListLout.width: 390
*nnE_sListLout.height: 120
*nnE_sListLout.listSizePolicy: "resize_if_possible"
*nnE_sListLout.singleSelectionCallback: {\
/* sente selezioni di out-var da marcare 'note' */\
 XmListCallbackStruct *pA =\
(XmListCallbackStruct *)UxCallbackArg;\
   int cSel;\
   get_something( UxWidget, XmNselectedItemCount, &cSel );\
   XmListDeselectAllItems( nnE_sListMout);\
   XtSetSensitive( nnE_pbOdel, False);\
   if (cSel && ceInElencoInt( pA->item_position -1, cMout, aiMout))\
      msgOn( ennEmsg_itemK );\
   XtSetSensitive( nnE_pbOadd, cSel);\
}

*nnE_sWinMout.class: scrolledWindow
*nnE_sWinMout.parent: nnE_formOut
*nnE_sWinMout.static: true
*nnE_sWinMout.name: nnE_sWinMout
*nnE_sWinMout.scrollingPolicy: "application_defined"
*nnE_sWinMout.visualPolicy: "variable"
*nnE_sWinMout.scrollBarDisplayPolicy: "static"
*nnE_sWinMout.bottomAttachment: "attach_opposite_widget"
*nnE_sWinMout.bottomWidget: "nnE_sWinLout"
*nnE_sWinMout.topAttachment: "attach_opposite_widget"
*nnE_sWinMout.topWidget: "nnE_sWinLout"
*nnE_sWinMout.rightAttachment: "attach_form"
*nnE_sWinMout.leftAttachment: "attach_widget"
*nnE_sWinMout.leftOffset: 20
*nnE_sWinMout.leftWidget: "nnE_sWinLout"
*nnE_sWinMout.x: 426
*nnE_sWinMout.y: 38
*nnE_sWinMout.shadowThickness: 0

*nnE_sListMout.class: scrolledList
*nnE_sListMout.parent: nnE_sWinMout
*nnE_sListMout.static: true
*nnE_sListMout.name: nnE_sListMout
*nnE_sListMout.singleSelectionCallback: {\
/* sente selezione di 1 out-var */\
 XmListCallbackStruct *pA =\
(XmListCallbackStruct *) UxCallbackArg;\
if (loStato & NN_MODE_NN) {\
/* modo Normal: da marcare 'non-nota' */\
   int cSel;\
   get_something( UxWidget, XmNselectedItemCount, &cSel );\
   XmListDeselectAllItems( nnE_sListLout);\
   if (cSel && ceInElencoInt( pA->item_position, cPair, aiPout))\
      msgOn( ennEmsg_pairDel );\
   XtSetSensitive( nnE_pbOadd, False);\
   XtSetSensitive( nnE_pbOdel, cSel);\
} else {\
/* modo Pairs: */\
 int cS, iP;\
   get_something( UxWidget, XmNselectedItemCount, &cS);\
   iP =ceInElencoInt( pA->item_position, cPout, aiPout);\
   iPoutSel = (cS) ? ((iP) ? -iP : pA->item_position) : 0;\
   if (iPinpSel<0\
    || iPinpSel*iPoutSel<0) {\
      msgOn( ennEmsg_badPair );\
      XmListDeselectItem( UxWidget, pA->item);\
      iPoutSel =0;\
   } else {\
      XtSetSensitive( nnE_pbPadd, False);\
      XtSetSensitive( nnE_pbPdel, False);\
      if (iPinpSel>0 && iPoutSel>0)\
         XtSetSensitive( nnE_pbPadd, True);\
      else if (iPoutSel<0)\
         XtSetSensitive( nnE_pbPdel, True);\
   }\
}\
}
*nnE_sListMout.selectionPolicy: "single_select"
*nnE_sListMout.width: 140
*nnE_sListMout.height: 120
*nnE_sListMout.listSizePolicy: "resize_if_possible"

*nnE_pbPadd.class: pushButton
*nnE_pbPadd.parent: nnE_formOut
*nnE_pbPadd.static: true
*nnE_pbPadd.name: nnE_pbPadd
*nnE_pbPadd.rightAttachment: "attach_form"
*nnE_pbPadd.activateCallback: {\
/* crea 1 Paio */\
 char zM[20];\
 XmString xsM;\
   azPinp[cPair] =(char *) XtMalloc( 8+1);\
   azPout[cPair] =(char *) XtMalloc( 8+1);\
   strncpy( azPinp[cPair], vari[aiMinp[iPinpSel-1]], 8);\
   strncpy( azPout[cPair], sivar[aiMout[iPoutSel-1]], 8);\
   azPinp[cPair][8] =azPout[cPair][8] =zM[20] ='\0';\
   zM[0] =zM[10] ='-';\
   zM[1] =' ';\
   strncpy( zM+2, azPinp[cPair], 8);\
   strncpy( zM+11, azPout[cPair], 8);\
   xsM =XmStringCreateSimple( zM);\
   XmListReplaceItemsPos( nnE_sListMinp, &xsM, 1, iPinpSel);\
   XmStringFree( xsM);\
   strncpy( zM+2, azPout[cPair], 8);\
   strncpy( zM+11, azPinp[cPair], 8);\
   xsM =XmStringCreateSimple( zM);\
   XmListReplaceItemsPos( nnE_sListMout, &xsM, 1, iPoutSel);\
   XmStringFree( xsM);\
   cPair++;\
   aiPinp[cPinp++] =iPinpSel;\
   aiPout[cPout++] =iPoutSel;\
   mostra_cLMP();\
   loStato |=NN_CHG_PP;\
   iPinpSel =iPoutSel =0;\
   XmListDeselectAllItems( nnE_sListMinp);\
   XmListDeselectAllItems( nnE_sListMout);\
   XtSetSensitive( UxWidget, False);\
}
*nnE_pbPadd.height: 35
*nnE_pbPadd.bottomAttachment: "attach_form"
*nnE_pbPadd.bottomOffset: 5
*nnE_pbPadd.labelString: "Pcreate"

*nnE_formInp.class: form
*nnE_formInp.parent: nnE_panedWin
*nnE_formInp.static: true
*nnE_formInp.name: nnE_formInp
*nnE_formInp.paneMinimum: 160
*nnE_formInp.height: 220
*nnE_formInp.marginHeight: 5
*nnE_formInp.marginWidth: 5
*nnE_formInp.shadowThickness: 2

*nnE_labInp.class: label
*nnE_labInp.parent: nnE_formInp
*nnE_labInp.static: true
*nnE_labInp.name: nnE_labInp
*nnE_labInp.leftAttachment: "attach_form"
*nnE_labInp.rightAttachment: "attach_form"
*nnE_labInp.labelString: "Input variables"
*nnE_labInp.topAttachment: "attach_form"

*nnE_labLinp.class: label
*nnE_labLinp.parent: nnE_formInp
*nnE_labLinp.static: true
*nnE_labLinp.name: nnE_labLinp
*nnE_labLinp.leftAttachment: "attach_form"
*nnE_labLinp.leftOffset: 10
*nnE_labLinp.topAttachment: "attach_widget"
*nnE_labLinp.topWidget: "nnE_labInp"

*nnE_labMinp.class: label
*nnE_labMinp.parent: nnE_formInp
*nnE_labMinp.static: true
*nnE_labMinp.name: nnE_labMinp
*nnE_labMinp.rightAttachment: "attach_form"
*nnE_labMinp.rightOffset: 10
*nnE_labMinp.topAttachment: "attach_opposite_widget"
*nnE_labMinp.topWidget: "nnE_labLinp"

*nnE_pbIadd.class: pushButton
*nnE_pbIadd.parent: nnE_formInp
*nnE_pbIadd.static: true
*nnE_pbIadd.name: nnE_pbIadd
*nnE_pbIadd.leftAttachment: "attach_form"
*nnE_pbIadd.activateCallback: {\
/* marca 'non-note' le inp-vars selezionate a sx */\
 int *aiPos, cPos, iS, i;\
 char zL[2+100+1], zM[2+8+1];\
 XmString xsL, xsM;\
   XmListGetSelectedPos( nnE_sListLinp, &aiPos, &cPos );\
   zL[0] =zL[1] =zM[0] =zM[1] =' ';\
   zL[2+100] =zM[2+8] ='\0';\
   while (cPos) {\
      iS = aiPos[--cPos] -1;\
      if (ceInElencoInt( iS, cMinp, aiMinp))\
         continue;\
      for (i=cMinp; i>0; i--)\
         if (aiMinp[i-1] > iS)\
            aiMinp[i] =aiMinp[i-1];\
         else\
            break;\
      aiMinp[i] = iS;\
      strncpy( zL+2, nom_vari[-aiLinp[iS]-1], 100);\
      xsL =XmStringCreateSimple( zL);\
      XmListReplaceItemsPos( nnE_sListLinp, &xsL, 1, iS+1 );\
      strncpy( zM+2, vari[-aiLinp[iS]-1], 8);\
      xsM =XmStringCreateSimple( zM);\
      XmListAddItem( nnE_sListMinp, xsM, i +1);\
      for (i=0; i<cPinp; i++)\
         if (aiPinp[i] > iS)\
            aiPinp[i]++;\
      XmStringFree( xsL);\
      XmStringFree( xsM);\
      cMinp++;\
      avvEdit[ neqsis-aiLinp[iS]-1 ].noto = False;\
      cKnown--;\
      loStato |= NN_CHG_NN;\
   }\
   XtFree( aiPos);\
   set_something( nnE_sListMinp, XmNvisibleItemCount, cMinp);\
   mostra_cLMP();\
   XmListDeselectAllItems( nnE_sListLinp);\
   XtSetSensitive( UxWidget, False);\
}
*nnE_pbIadd.height: 35
*nnE_pbIadd.bottomAttachment: "attach_form"
*nnE_pbIadd.bottomOffset: 5
*nnE_pbIadd.labelString: "Unmark"

*nnE_pbIdel.class: pushButton
*nnE_pbIdel.parent: nnE_formInp
*nnE_pbIdel.static: true
*nnE_pbIdel.name: nnE_pbIdel
*nnE_pbIdel.leftAttachment: "attach_widget"
*nnE_pbIdel.activateCallback: {\
/* marca 'note' le inp-var selezionate a dx */\
 int *aiPos, cPos, iS, iM, iP, jP, jM, i;\
 char zL[2+100+1], zM[2+8+1];\
 XmString xsL, xsM;\
if (XmListGetSelectedPos( nnE_sListMinp, &aiPos, &cPos )) {\
   zL[1] =zM[0] =zM[1] =' ';\
   zL[2+100] ='\0';\
   while (cPos) {\
      iS = aiPos[--cPos];\
      iM =aiMinp[iS-1];\
      zL[0] ='*';\
      strncpy( zL+2, nom_vari[-aiLinp[iM]-1], 100);\
      xsL =XmStringCreateSimple( zL);\
      XmListReplaceItemsPos( nnE_sListLinp, &xsL, 1, iM+1 );\
      XmStringFree( xsL);\
      XmListDeletePos( nnE_sListMinp, iS );\
      for (i=iS; i<cMinp; i++)\
         aiMinp[i-1] =aiMinp[i];\
      cMinp--;\
      avvEdit[neqsis-aiLinp[iM]-1].noto = True;\
      cKnown++;\
      loStato |= NN_CHG_NN;\
      if (iP =ceInElencoInt( iS, cPair, aiPinp)) {\
         if ((jP=aiPout[iP-1]) > 0) {\
          int *ajPos, cjPos;\
            jM = aiLout[aiMout[jP-1]];\
            zL[0] =' ';\
            strncpy( zL+2, nom_sivar[jM-1], 100);\
            xsL =XmStringCreateSimple( zL);\
            XmListReplaceItemsPos( nnE_sListLout, &xsL, 1, aiMout[jP-1]+1 );\
            XmStringFree( xsL);\
            if (XmListGetSelectedPos( nnE_sListMout, &ajPos, &cjPos)) {\
               if (i = ceInElencoInt( jP, cjPos, ajPos))\
                  XmListSelectPos( nnE_sListMout, jP, True);\
               XtFree( ajPos);\
            }\
            XmListDeletePos( nnE_sListMout, jP);\
            for (i=jP; i<cMout; i++)\
               aiMout[i-1] =aiMout[i];\
            cMout--;\
            for (i=0; i<cPair; i++)\
               if (aiPout[i]>jP)\
                  aiPout[i]--;\
            cPout--;\
         } else\
            jM = -jP;\
         deletePair( iP);\
         for (i=0; i<cPair; i++)\
            if (aiPinp[i]>iS)\
               aiPinp[i]--;\
         cPinp--;\
         avvEdit[jM-1].noto = True;\
         cKnown--;\
         loStato |= NN_CHG_PP;\
      }\
   }\
   XmListDeselectAllItems( nnE_sListMinp);\
   set_something( nnE_sListMinp, XmNvisibleItemCount, cMinp ? cMinp : 1);\
   set_something( nnE_sListMout, XmNvisibleItemCount, cMout ? cMout : 1);\
   mostra_cLMP();\
   XtFree( aiPos);\
   }\
   XtSetSensitive( UxWidget, False);\
}
*nnE_pbIdel.leftWidget: "nnE_pbIadd"
*nnE_pbIdel.leftOffset: 10
*nnE_pbIdel.height: 35
*nnE_pbIdel.labelString: " Mark "
*nnE_pbIdel.bottomAttachment: "attach_form"
*nnE_pbIdel.bottomOffset: 5

*nnE_sWinLinp.class: scrolledWindow
*nnE_sWinLinp.parent: nnE_formInp
*nnE_sWinLinp.static: true
*nnE_sWinLinp.name: nnE_sWinLinp
*nnE_sWinLinp.scrollingPolicy: "application_defined"
*nnE_sWinLinp.visualPolicy: "variable"
*nnE_sWinLinp.scrollBarDisplayPolicy: "static"
*nnE_sWinLinp.leftAttachment: "attach_form"
*nnE_sWinLinp.rightAttachment: "attach_position"
*nnE_sWinLinp.rightPosition: 70
*nnE_sWinLinp.bottomAttachment: "attach_widget"
*nnE_sWinLinp.bottomWidget: "nnE_pbIadd"
*nnE_sWinLinp.topAttachment: "attach_widget"
*nnE_sWinLinp.topWidget: "nnE_labLinp"
*nnE_sWinLinp.bottomOffset: 5
*nnE_sWinLinp.x: 14
*nnE_sWinLinp.y: 38
*nnE_sWinLinp.shadowThickness: 0

*nnE_sListLinp.class: scrolledList
*nnE_sListLinp.parent: nnE_sWinLinp
*nnE_sListLinp.static: true
*nnE_sListLinp.name: nnE_sListLinp
*nnE_sListLinp.selectionPolicy: "single_select"
*nnE_sListLinp.width: 390
*nnE_sListLinp.height: 120
*nnE_sListLinp.listSizePolicy: "resize_if_possible"
*nnE_sListLinp.singleSelectionCallback: {\
/* sente selezioni di inp-var da marcare 'non-note' */\
 XmListCallbackStruct *pA =\
(XmListCallbackStruct *)UxCallbackArg;\
   int cSel;\
   get_something( UxWidget, XmNselectedItemCount, &cSel );\
   XmListDeselectAllItems( nnE_sListMinp );\
   XtSetSensitive( nnE_pbIdel, False);\
   if (cSel && ceInElencoInt( pA->item_position -1, cMinp, aiMinp))\
      msgOn( ennEmsg_itemUnk );\
   XtSetSensitive( nnE_pbIadd, cSel);\
}

*nnE_sWinMinp.class: scrolledWindow
*nnE_sWinMinp.parent: nnE_formInp
*nnE_sWinMinp.static: true
*nnE_sWinMinp.name: nnE_sWinMinp
*nnE_sWinMinp.scrollingPolicy: "application_defined"
*nnE_sWinMinp.visualPolicy: "variable"
*nnE_sWinMinp.scrollBarDisplayPolicy: "static"
*nnE_sWinMinp.bottomAttachment: "attach_opposite_widget"
*nnE_sWinMinp.bottomWidget: "nnE_sWinLinp"
*nnE_sWinMinp.topAttachment: "attach_opposite_widget"
*nnE_sWinMinp.topWidget: "nnE_sWinLinp"
*nnE_sWinMinp.leftAttachment: "attach_widget"
*nnE_sWinMinp.rightAttachment: "attach_form"
*nnE_sWinMinp.leftOffset: 20
*nnE_sWinMinp.leftWidget: "nnE_sWinLinp"
*nnE_sWinMinp.x: 426
*nnE_sWinMinp.y: 38
*nnE_sWinMinp.shadowThickness: 0

*nnE_sListMinp.class: scrolledList
*nnE_sListMinp.parent: nnE_sWinMinp
*nnE_sListMinp.static: true
*nnE_sListMinp.name: nnE_sListMinp
*nnE_sListMinp.singleSelectionCallback: {\
/* sente selezione di 1 inp-var */\
 XmListCallbackStruct *pA =\
(XmListCallbackStruct *) UxCallbackArg;\
if (loStato & NN_MODE_NN) {\
/* modo Normal: da marcare 'nota' */\
   int cSel;\
   get_something( UxWidget, XmNselectedItemCount, &cSel );\
   XmListDeselectAllItems( nnE_sListLinp);\
   if (cSel && ceInElencoInt( pA->item_position, cPair, aiPinp))\
      msgOn( ennEmsg_pairDel );\
   XtSetSensitive( nnE_pbIadd, False);\
   XtSetSensitive( nnE_pbIdel, cSel);\
} else {\
/* modo Pairs: */\
 int cS, iP;\
   get_something( UxWidget, XmNselectedItemCount, &cS);\
   iP =ceInElencoInt( pA->item_position, cPinp, aiPinp);\
   iPinpSel = (cS) ? ((iP) ? -iP : pA->item_position) : 0;\
   if (iPoutSel<0\
    || iPinpSel*iPoutSel<0) {\
      msgOn( ennEmsg_badPair );\
      XmListDeselectItem( UxWidget, pA->item);\
      iPinpSel =0;\
   } else {\
      XtSetSensitive( nnE_pbPadd, False);\
      XtSetSensitive( nnE_pbPdel, False);\
      if (iPinpSel>0 && iPoutSel>0)\
         XtSetSensitive( nnE_pbPadd, True);\
      else if (iPinpSel<0)\
         XtSetSensitive( nnE_pbPdel, True);\
   }\
}\
}
*nnE_sListMinp.selectionPolicy: "single_select"
*nnE_sListMinp.width: 140
*nnE_sListMinp.height: 120
*nnE_sListMinp.listSizePolicy: "resize_if_possible"

*nnE_pbPdel.class: pushButton
*nnE_pbPdel.parent: nnE_formInp
*nnE_pbPdel.static: true
*nnE_pbPdel.name: nnE_pbPdel
*nnE_pbPdel.rightAttachment: "attach_form"
*nnE_pbPdel.activateCallback: {\
/* cancella 1 Paio */\
 int iP;\
 char zM[2+8+1];\
 XmString xsM;\
   iP = (iPinpSel) ? -iPinpSel : -iPoutSel;\
   zM[0] =zM[1] =' ';\
   strcpy( zM+2, azPinp[iP-1]);\
   xsM =XmStringCreateSimple( zM);\
   XmListReplaceItemsPos( nnE_sListMinp, &xsM, 1, aiPinp[iP-1]);\
   XmStringFree( xsM);\
   strcpy( zM+2, azPout[iP-1]);\
   xsM =XmStringCreateSimple( zM);\
   XmListReplaceItemsPos( nnE_sListMout, &xsM, 1, aiPout[iP-1]);\
   XmStringFree( xsM);\
   deletePair( iP);\
   cPinp--;\
   cPout--;\
   mostra_cLMP();\
   loStato |=NN_CHG_PP;\
   iPinpSel =iPoutSel =0;\
   XmListDeselectAllItems( nnE_sListMinp);\
   XmListDeselectAllItems( nnE_sListMout);\
   XtSetSensitive( UxWidget, False);\
}
*nnE_pbPdel.height: 35
*nnE_pbPdel.bottomAttachment: "attach_form"
*nnE_pbPdel.bottomOffset: 5
*nnE_pbPdel.labelString: "Pdelete"

*nnE_omuVars.class: rowColumn
*nnE_omuVars.parent: nnE_form
*nnE_omuVars.static: true
*nnE_omuVars.name: nnE_omuVars
*nnE_omuVars.rowColumnType: "menu_option"
*nnE_omuVars.subMenuId: "nnE_omuV_p1"
*nnE_omuVars.labelString: "Show:"
*nnE_omuVars.bottomAttachment: "attach_opposite_widget"
*nnE_omuVars.leftAttachment: "attach_form"
*nnE_omuVars.bottomWidget: "nnE_scale"

*nnE_omuV_p1.class: rowColumn
*nnE_omuV_p1.parent: nnE_omuVars
*nnE_omuV_p1.static: true
*nnE_omuV_p1.name: nnE_omuV_p1
*nnE_omuV_p1.rowColumnType: "menu_pulldown"

*nnE_omuVAll.class: pushButton
*nnE_omuVAll.parent: nnE_omuV_p1
*nnE_omuVAll.static: true
*nnE_omuVAll.name: nnE_omuVAll
*nnE_omuVAll.labelString: "All"
*nnE_omuVAll.activateCallback.source: public
*nnE_omuVAll.activateCallback: nnEsimpleCB_omuVars
*nnE_omuVAll.activateCallbackClientData: (XtPointer) NN_VARS_ALL

*nnE_omuVFilter.class: pushButton
*nnE_omuVFilter.parent: nnE_omuV_p1
*nnE_omuVFilter.static: true
*nnE_omuVFilter.name: nnE_omuVFilter
*nnE_omuVFilter.labelString: "Filter"
*nnE_omuVFilter.activateCallback.source: public
*nnE_omuVFilter.activateCallback: nnEsimpleCB_omuVars
*nnE_omuVFilter.activateCallbackClientData: (XtPointer) NN_VARS_FILTER

*nnE_dbMsg.class: drawnButton
*nnE_dbMsg.parent: nnE_form
*nnE_dbMsg.static: true
*nnE_dbMsg.name: nnE_dbMsg
*nnE_dbMsg.x: 120
*nnE_dbMsg.y: 40
*nnE_dbMsg.width: 410
*nnE_dbMsg.height: 40
*nnE_dbMsg.bottomAttachment: "attach_opposite_widget"
*nnE_dbMsg.bottomWidget: "nnE_scale"
*nnE_dbMsg.leftAttachment: "attach_widget"
*nnE_dbMsg.leftWidget: "nnE_omuVars"
*nnE_dbMsg.rightAttachment: "attach_widget"
*nnE_dbMsg.rightWidget: "nnE_scale"
*nnE_dbMsg.topAttachment: "attach_widget"
*nnE_dbMsg.topWidget: "nnE_formVars"
*nnE_dbMsg.foreground: "Red"
*nnE_dbMsg.activateCallback: {\
   msgOn( lastMsg );\
}
*nnE_dbMsg.topOffset: 5
*nnE_dbMsg.leftOffset: 10
*nnE_dbMsg.rightOffset: 10


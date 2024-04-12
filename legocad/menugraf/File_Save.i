! UIMX ascii 2.0 key: 2776                                                      

*File_Save.class: form
*File_Save.parent: NO_PARENT
*File_Save.defaultShell: topLevelShell
*File_Save.static: false
*File_Save.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo File_Save.i\
   tipo \
   release 1.10\
   data 3/28/95\
   reserved @(#)File_Save.i	1.10\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
\
#include <stdio.h>\
#include "menu_graf.h"\
\
extern FILE *fpAPPO,*fpDAT;\
extern swidget Message;\
extern swidget create_Overwrite();\
extern int numero_temp;\
extern char Path_appo[];\
extern int nome_valido;\
extern int Modifica,Salvato;\
\
char *Nomefile; /* Nome file valido per i salvataggi */
*File_Save.ispecdecl: int SalvaCome;\
char *fileSave;
*File_Save.ispeclist: SalvaCome, fileSave
*File_Save.ispeclist.SalvaCome: "int", "%SalvaCome%"
*File_Save.ispeclist.fileSave: "unsigned char", "*%fileSave%"
*File_Save.funcdecl: swidget create_File_Save(int Opzione,Position PX,Position PY,char *NomeFile)\

*File_Save.funcname: create_File_Save
*File_Save.funcdef: "swidget", "<create_File_Save>(%)"
*File_Save.argdecl: int Opzione;\
Position PX;\
Position PY;\
unsigned char *NomeFile;
*File_Save.arglist: Opzione, PX, PY, NomeFile
*File_Save.arglist.Opzione: "int", "%Opzione%"
*File_Save.arglist.PX: "Position", "%PX%"
*File_Save.arglist.PY: "Position", "%PY%"
*File_Save.arglist.NomeFile: "unsigned char", "*%NomeFile%"
*File_Save.icode: SalvaCome = Opzione;\
fileSave = XtNewString (NomeFile);
*File_Save.fcode: set_something (File_Save, XmNx, PX+10);\
set_something (File_Save, XmNy, PY+10);\
return(rtrn);\

*File_Save.auxdecl:
*File_Save.name: File_Save
*File_Save.resizePolicy: "resize_none"
*File_Save.unitType: "pixels"
*File_Save.x: 624
*File_Save.y: 343
*File_Save.width: 334
*File_Save.height: 137

*name_save.class: textField
*name_save.parent: File_Save
*name_save.static: false
*name_save.name: name_save
*name_save.x: 10
*name_save.y: 35
*name_save.width: 315
*name_save.height: 40

*label5.class: label
*label5.parent: File_Save
*label5.static: true
*label5.name: label5
*label5.x: 5
*label5.y: 10
*label5.width: 140
*label5.height: 25
*label5.labelString: "Output file name"

*push_save.class: pushButton
*push_save.parent: File_Save
*push_save.static: false
*push_save.name: push_save
*push_save.x: 10
*push_save.y: 80
*push_save.width: 100
*push_save.height: 45
*push_save.labelString: "SAVE"
*push_save.activateCallback: {\
int risul;\
char cdo[100],stringa[100],*appoggio;\
XmString Messaggio;\
\
appoggio = XmTextFieldGetString (name_save);\
if (appoggio [0] == '\0')\
	{\
	strcpy (stringa,"File name is not valid !\0");\
	Messaggio = XmStringCreate (stringa, XmSTRING_DEFAULT_CHARSET);\
	set_something (Message, XmNdialogType, XmDIALOG_ERROR);\
	set_something (Message, XmNmessageString, Messaggio);\
	UxPopupInterface (Message, no_grab);\
	XmStringFree (Messaggio);\
	}\
else\
	{\
	risul = Controllo_gia_presente (appoggio);\
	if (risul == 0)\
		{\
		if (SalvaCome == NORMAL_SAVE)\
			{\
			Uccidi_grafics ();\
			fclose (fpAPPO);\
			fclose (fpDAT);\
			strcpy (cdo,"cp ");\
			strcat (cdo,fileSave);\
			strcat (cdo," ");\
			strcat (cdo,appoggio);\
			system (cdo);\
			nome_valido = 1;\
			Modifica = 0;\
			Salvato = 1;\
			Nomefile = XtNewString (appoggio);\
			}\
		if (SalvaCome == ASCII_SAVE)\
			{\
			Uccidi_grafics ();\
			strcpy (cdo, "cp ");\
			strcat (cdo, fileSave);\
			strcat (cdo, " ");\
			strcat (cdo, appoggio);\
			system (cdo);\
			strcpy (cdo, "rm ");\
			strcat (cdo, fileSave);\
			system (cdo);\
			}\
		UxDestroyInterface (File_Save);\
		}\
	else\
		{\
		if (SalvaCome == ASCII_SAVE)\
			UxPopupInterface (create_Overwrite(ASCII_SAVE,\
				fileSave,appoggio), no_grab);\
		else\
			UxPopupInterface (create_Overwrite(NORMAL_SAVE,\
				fileSave,appoggio), no_grab);\
\
		XmStringFree (Messaggio); \
		}\
	}\
}

*push_cancel.class: pushButton
*push_cancel.parent: File_Save
*push_cancel.static: false
*push_cancel.name: push_cancel
*push_cancel.x: 225
*push_cancel.y: 80
*push_cancel.width: 100
*push_cancel.height: 45
*push_cancel.labelString: "CANCEL"
*push_cancel.activateCallback: {\
UxDestroyInterface (File_Save);\
}


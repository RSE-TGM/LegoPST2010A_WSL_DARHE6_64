
/*******************************************************************************
       FontsEditor.c
       (Generated from interface file FontsEditor.i)
       Associated Resource file: FontsEditor.rf
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/Label.h>
#include <Xm/Text.h>
#include <Xm/Frame.h>
#include <Xm/PushBG.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo FontsEditor.i
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)FontsEditor.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <string.h>
#include "res_edit.h"

#define MAX_FONTS  2000
#define MAX_BUFSIZE 500

extern Display *UxDisplay;
extern void qsort();

static char ** load_list(); 
static void put_list_items(); 
static void free_list(); 
static void put_font (); 
static void load_list2 (); 
static void load_list3 ();


/*******************************************************************************
       The definition of the context structure:
       If you create multiple copies of your interface, the context
       structure ensures that your callbacks use the variables for the
       correct copy.

       For each swidget in the interface, each argument to the Interface
       function, and each variable in the Interface Specific section of the
       Declarations Editor, there is an entry in the context structure.
       and a #define.  The #define makes the variable name refer to the
       corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	Widget	UxFontsEditor;
	Widget	Uxform6;
	Widget	UxApply_pbFont;
	Widget	Uxdisplay_box;
	Widget	Uxdisplay_text;
	Widget	Uxfontname_text;
	Widget	Uxlist1_label;
	Widget	Uxfont_swin_3;
	Widget	Uxfont_list_3;
	Widget	Uxfont_swin_2;
	Widget	Uxfont_list_2;
	Widget	Uxfont_swin_1;
	Widget	Uxfont_list_1;
	Widget	Uxlist2_label;
	Widget	Uxlist3_label;
	Widget	UxOK_pbFont;
	Widget	UxClose_pbFont;
	unsigned char	**Uxfirst_list;
	unsigned char	**Uxsecond_list;
	unsigned char	**Uxthird_list;
	int	Uxfirst_len;
	int	Uxsecond_len;
	int	Uxthird_len;
	unsigned char	*Uxfirst_sel;
	unsigned char	*Uxsecond_sel;
	unsigned char	*Uxthird_sel;
	Widget	UxTextF;
	Widget	UxTextFont;
	Widget	UxChiamFonEd;
} _UxCFontsEditor;

static _UxCFontsEditor         *UxFontsEditorContext;
#define FontsEditor             UxFontsEditorContext->UxFontsEditor
#define form6                   UxFontsEditorContext->Uxform6
#define Apply_pbFont            UxFontsEditorContext->UxApply_pbFont
#define display_box             UxFontsEditorContext->Uxdisplay_box
#define display_text            UxFontsEditorContext->Uxdisplay_text
#define fontname_text           UxFontsEditorContext->Uxfontname_text
#define list1_label             UxFontsEditorContext->Uxlist1_label
#define font_swin_3             UxFontsEditorContext->Uxfont_swin_3
#define font_list_3             UxFontsEditorContext->Uxfont_list_3
#define font_swin_2             UxFontsEditorContext->Uxfont_swin_2
#define font_list_2             UxFontsEditorContext->Uxfont_list_2
#define font_swin_1             UxFontsEditorContext->Uxfont_swin_1
#define font_list_1             UxFontsEditorContext->Uxfont_list_1
#define list2_label             UxFontsEditorContext->Uxlist2_label
#define list3_label             UxFontsEditorContext->Uxlist3_label
#define OK_pbFont               UxFontsEditorContext->UxOK_pbFont
#define Close_pbFont            UxFontsEditorContext->UxClose_pbFont
#define first_list              UxFontsEditorContext->Uxfirst_list
#define second_list             UxFontsEditorContext->Uxsecond_list
#define third_list              UxFontsEditorContext->Uxthird_list
#define first_len               UxFontsEditorContext->Uxfirst_len
#define second_len              UxFontsEditorContext->Uxsecond_len
#define third_len               UxFontsEditorContext->Uxthird_len
#define first_sel               UxFontsEditorContext->Uxfirst_sel
#define second_sel              UxFontsEditorContext->Uxsecond_sel
#define third_sel               UxFontsEditorContext->Uxthird_sel
#define TextF                   UxFontsEditorContext->UxTextF
#define TextFont                UxFontsEditorContext->UxTextFont
#define ChiamFonEd              UxFontsEditorContext->UxChiamFonEd



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_FontsEditor();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

/* split_font_name() -  Extract one of the 3 list components from a font name. 
 *			The 'part' argument says which portion (1,2,or,3) to return. 
 *  			Splitting is done by counting dashes, so all abbreviated names
 *			like 'fixed' go in the first list.
 */ 
 
char* split_font_name (name, part) 
	char* name; 
	int   part; 
{ 
	static char* buff = NULL; 
	static int   buflen = 0; 
	char * bufptr; 
	char * result; 
	int i; 
 
	if (name == NULL) { 
		return ""; 
	} 

	if (buff == NULL) { 
		buff = malloc(buflen=128); 
	} 
	while (buflen <= strlen(name)) { 
		buff = realloc(buff, buflen*=2);  
	} 
 
	strcpy(buff,name); 

	if (! strchr(name,'-')) {    /* no dashes - simple name */
		if (part == 1) {
			return buff; 
		} else { 
			return ""; 
		} 
	} 
 
	bufptr = buff; 
	for (i=0; i<3; i++) { 	  /* first part, 3 dashes: -adobe-courier- */
		while (*bufptr && *bufptr != '-') 
			*bufptr++; 
		if (*bufptr == '-')  
			*bufptr ++; 
	} 
	if (part == 1) { 
	   *bufptr = '\000'; 
	   return buff; 
	} 
	result = bufptr; 
	for (i=0; i<4; i++) {     /* second part,4 dashes: bold-i-normal-- */
		while (*bufptr && *bufptr != '-') 
			*bufptr++; 
		if (*bufptr == '-')  
			*bufptr ++; 
	} 
	if (part == 2) { 
		*bufptr = '\000'; 
		return result; 
	} 
	else 
		return bufptr; 
}	 
 
/* unique_nth_parts () - given a list of fonts, build a list 
 *			 of the unique nth portions of each font string 
 *			 (the contents of our scrolled lists).
 *			 The length of the result is returned in result_len. 
 *			 ASSUMES lists from XListFontNames are sorted. 
 */ 
char ** unique_nth_parts (fonts, fonts_len, nth, result_len) 
	char	** fonts; 
	int 	fonts_len; 
	int 	nth; 
	int	* result_len; 
{ 
	int 	n = 0; 
	char	** result; 
	char 	* part; 
	char 	pattern[MAX_BUFSIZE]; 
	int  	i; 
 
	result    = (char**) malloc( sizeof(char*) * fonts_len); 
 
	for (i=0; i<fonts_len; i++) { 
		part = split_font_name (fonts[i], nth); 
		if (part[0] == '\000')  { 
		   	continue; 
		} else if ((n==0) || (strcmp(result[n-1], part)!=0)) { 
		    	/* test above assumes that fonts come sorted. */ 
		    	result [n++] = XtNewString (part); 
		} 
	} 
	*result_len = n; 
	return result; 
} 
 
/* load_list () - given a seed pattern (presumably the start of a font name) 
 * 		  build the list of font components containing the pattern. 
 *		  That is, given a selected font at one scrolled list, 
 *		  build the sublist of components for the next scrolled list. 
 */ 
 
/* compare the font strings. */ 
comp(arg1,arg2) 
        char **arg1; 
        char **arg2; 
{ 
        if ( (*arg1 == NULL) && (*arg2 == NULL)) { 
                return 0; 
        } 
        if ((*arg1 == NULL) || (*arg2 == NULL)) { 
                return 1; 
        } 
        if (*arg1 && *arg2) { 
                return strcmp(*arg1, *arg2); 
        } 
} 
 
static char **load_list (which_list, pattern, length) 
	int 	which_list; 
	char 	* pattern; 
	int  	* length; 
{ 
	char **fonts; 
	char **list; 
	char **sorted_fonts; 
	int  num_fonts; 
	int  i; 
 
        /* get the unsorted font list. */ 
	fonts = XListFonts(UxDisplay, pattern, MAX_FONTS, &num_fonts); 
 
        /* reserve space for the font list. */ 
        sorted_fonts = (char **) malloc(num_fonts * sizeof(char *)); 
        /* load the font list. */ 
        for (i=0; i < num_fonts; i++) 
                { 
                sorted_fonts[i] = (char *) malloc( strlen(fonts[i])+1 ); 
                strncpy(sorted_fonts[i],fonts[i], strlen(fonts[i])+1); 
                } 
 
        /* sort the font list. */ 
        qsort(sorted_fonts, num_fonts, sizeof(char *), comp); 
 
	if (num_fonts == MAX_FONTS) { 
	   	printf("Maximum number of fonts loaded; may be some missing.\n"); 
	} 
	list  = unique_nth_parts (sorted_fonts, num_fonts, which_list, length); 
 
	XFreeFontNames(fonts); 
        for (i=0; i < num_fonts; i++) { 
                free(sorted_fonts[i]); 
        } 
        free(sorted_fonts); 
 
	return list; 
} 
 
/*  put_list_items () - put the given list of strings as the item list 
 *			of the given XmList swidget.   
 *			Make the sel'th item the selection. 
 */ 
 
static void put_list_items (list, items, n, sel) 
	swidget list; 
	char    **items; 
	int	n; 
	int     sel; 
{ 
	Arg	arg[5]; 
	int  	i; 
	XmString * xm_items = (XmString*) malloc (n * sizeof(XmString)); 
 
	for (i=0; i<n; i++) { 
		xm_items[i] = XmStringCreateLtoR (items[i],  
						 XmSTRING_DEFAULT_CHARSET);  
	} 
 
	XtSetArg (arg[0], XmNitems, xm_items);  
      	XtSetArg (arg[1], XmNitemCount, n);
      	XtSetArg (arg[2], XmNselectedItems, &(xm_items[sel]));  
      	XtSetArg (arg[3], XmNselectedItemCount, n>0 ? 1 : 0);  
      	XtSetValues (UxGetWidget(list), arg, 4);  
 
	for (i=0; i<n; i++) { 
		XmStringFree(xm_items[i]); 
	} 
	free (xm_items); 
} 
 
/*  free_list() - free the dynamic space from one of our char** arrays. 
 */ 
 
static void free_list (list, n) 
	char **list; 
	int  n; 
{  
	while (--n > 0) { 
	  	free (list[n]); 
	} 
	free (list); 
} 
 
/*  put_font()  - use the current selection set as the font name 
 *		  for the display. 
 */  
 
static void put_font() 
{ 
	XFontStruct *StrutturaFont;
	char font[MAX_BUFSIZE]; 
	
	if (second_sel == NULL) { 
		sprintf(font, "%s", first_sel ); 
	} else if (third_sel == NULL) { 
		sprintf(font, "%s%s", first_sel, second_sel); 
	} else { 
		sprintf(font, "%s%s%s", first_sel, second_sel, third_sel); 
	} 

	StrutturaFont = XLoadQueryFont (UxDisplay, font);
	set_something (display_text, XmNfontList, (void*) XmFontListCreate (StrutturaFont,
			XmSTRING_DEFAULT_CHARSET));
	XmTextSetString (fontname_text, font); 
} 

/* in_list()  - find a string in an array of strings that matches a given string. 
 *		'matches' means equal in the first cmp_len characters. 
 *		returns the found index, or -1. 
 */ 

static int in_list (list, len, elem, cmp_len) 
	char	** list; 
	int	len; 
	char 	* elem; 
	int    cmp_len; 
{ 
	if (elem == NULL) return -1; 

	while (--len >= 0) { 
		if (strncmp(list[len], elem, cmp_len) == 0) { 
			return len; 
		} 
	} 
	return -1; 
} 

/* load_list2() -  given the current selection in list1, load list2. 
 */ 

static void load_list2 () 
{ 
	char* old_sel; 
	int   old_len; 
	char** old_list; 
	char pattern [MAX_BUFSIZE]; 
	int Numero,sel; 
	
	old_list = (char **)second_list; 
	old_sel  = (char *)second_sel; 
	old_len  = second_len; 
	
	if (first_sel==NULL) { 
		second_list = NULL; 
		second_len = 0; 
		second_sel = NULL; 
	} else { 
		sprintf(pattern, "%s*", first_sel); 
		second_list = (unsigned char **)load_list(2, pattern, &second_len); 
		if (second_len > 0) { 
		   second_sel = second_list[0]; 
		} else { 
		   second_sel = NULL; 
		} 
	} 
	
	/* If the previous selection is in this list, leave it. 
	 * The '128' is simply long enough to do a complete comparison. 
	 * If the list was and is empty, don't reset it. 
	 */ 
	if ((sel = in_list(second_list, second_len, old_sel, 128)) != -1)  {
		second_sel = second_list[sel]; 
	} else { 
		sel = 0; 
	}
	get_something (font_list_2, XmNitemCount, (void*) &Numero);
	if ( (second_len != 0) || (Numero != 0)) { 
		put_list_items (font_list_2, second_list, second_len, sel); 
	} 

	if (old_list) 
		free_list (old_list, old_len); 

} 
/* load_list3() -  given the current selection in list2, load list3. 
 */ 

static void load_list3 () 
{ 
	char* old_sel; 
	int   old_len; 
	char** old_list; 
	char pattern [MAX_BUFSIZE]; 
	int Numero,sel; 
	
	old_list = (char **)third_list; 
	old_sel  = (char *)third_sel; 
	old_len  = third_len; 
	
	if (second_sel==NULL) { 
		third_list = NULL; 
		third_len = 0; 
		third_sel = NULL; 
	} else { 
		sprintf(pattern, "%s%s*", first_sel, second_sel); 
		third_list = (unsigned char **)load_list(3, pattern, &third_len); 
		if (third_len > 0) { 
		   third_sel = third_list[0]; 
		} else { 
		   third_sel = NULL; 
		} 
	} 
	
	/* If the previous selection is in this list, leave it. 
	 * In this third portion of the font spec, the first field is 
	 * the point size, so the '3' to in_list() means we keep 
	 * the selection on the same point size if possible. 
	 * If the list was and is empty, don't reset it. 
	 */ 
	if ((sel =in_list(third_list, third_len, old_sel, 3)) != -1)  {
		third_sel = third_list[sel]; 
	} else { 
		sel = 0;
	}
	get_something (font_list_3, XmNitemCount, (void*) &Numero); 
	if ( (third_len != 0) || (Numero != 0)) { 
		put_list_items (font_list_3, third_list, third_len, sel); 
	} 

	if (old_list) 
		free_list (old_list, old_len); 

}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_Apply_pbFont( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsEditorContext;
	UxFontsEditorContext = UxContext =
			(_UxCFontsEditor *) UxGetContext( UxWidget );
	{
	char *Appoggio;
	
	Appoggio = XmTextGetString (fontname_text);
	
	XmTextFieldSetString (TextF,Appoggio);
	XtFree (Appoggio);
	}
	UxFontsEditorContext = UxSaveCtx;
}

static	void	singleSelectionCB_font_list_3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsEditorContext;
	UxFontsEditorContext = UxContext =
			(_UxCFontsEditor *) UxGetContext( UxWidget );
	{
		char pattern[MAX_BUFSIZE];
		XmListCallbackStruct *cbs = (XmListCallbackStruct *)UxCallbackArg;
	
		XmStringGetLtoR(cbs->item, XmSTRING_DEFAULT_CHARSET, &third_sel);
		put_font (); 
	}
	UxFontsEditorContext = UxSaveCtx;
}

static	void	singleSelectionCB_font_list_2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsEditorContext;
	UxFontsEditorContext = UxContext =
			(_UxCFontsEditor *) UxGetContext( UxWidget );
	{
		char pattern[MAX_BUFSIZE];
		XmListCallbackStruct *cbs = (XmListCallbackStruct *)UxCallbackArg;
	
		/* Small memory leak */ 
		XmStringGetLtoR(cbs->item, XmSTRING_DEFAULT_CHARSET, &second_sel);
		
		/* Set up list 3 */
		load_list3();
		
		put_font(); 
	}
	UxFontsEditorContext = UxSaveCtx;
}

static	void	singleSelectionCB_font_list_1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsEditorContext;
	UxFontsEditorContext = UxContext =
			(_UxCFontsEditor *) UxGetContext( UxWidget );
	{
		XmListCallbackStruct *cbs = (XmListCallbackStruct *)UxCallbackArg;
	
		XmStringGetLtoR(cbs->item, XmSTRING_DEFAULT_CHARSET, &first_sel);
		
		/* Set up list 2 */
		load_list2(); 
		
		/* Set up list 3 */
		load_list3();
		
		put_font(); 
	}
	UxFontsEditorContext = UxSaveCtx;
}

static	void	activateCB_OK_pbFont( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsEditorContext;
	UxFontsEditorContext = UxContext =
			(_UxCFontsEditor *) UxGetContext( UxWidget );
	{
	char *Appoggio;
	
	Appoggio = XmTextGetString (fontname_text);
	
	XmTextFieldSetString(TextF,Appoggio);
	XtFree (Appoggio);
	XtDestroyWidget (FontsEditor);
	}
	UxFontsEditorContext = UxSaveCtx;
}

static	void	activateCB_Close_pbFont( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsEditor         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsEditorContext;
	UxFontsEditorContext = UxContext =
			(_UxCFontsEditor *) UxGetContext( UxWidget );
	{
		XtDestroyWidget (FontsEditor);
	}
	UxFontsEditorContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_FontsEditor()
{
	Widget		_UxParent;


	/* Creation of FontsEditor */
	_UxParent = ChiamFonEd;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	FontsEditor = XtVaCreatePopupShell( "FontsEditor",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 547,
			XmNy, 41,
			XmNwidth, 620,
			XmNheight, 470,
			XmNallowShellResize, TRUE,
			NULL );
	UxPutContext( FontsEditor, (char *) UxFontsEditorContext );


	/* Creation of form6 */
	form6 = XtVaCreateManagedWidget( "form6",
			xmFormWidgetClass,
			FontsEditor,
			XmNwidth, 620,
			XmNheight, 470,
			XmNallowShellResize, TRUE,
			XmNallowOverlap, FALSE,
			RES_CONVERT( XmNdialogTitle, "Resource Font Editor" ),
			XmNhorizontalSpacing, 6,
			XmNverticalSpacing, 6,
			NULL );
	UxPutContext( form6, (char *) UxFontsEditorContext );


	/* Creation of Apply_pbFont */
	Apply_pbFont = XtVaCreateManagedWidget( "Apply_pbFont",
			xmPushButtonGadgetClass,
			form6,
			RES_CONVERT( XmNlabelString, "Apply" ),
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 6,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftPosition, 37,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 63,
			XmNx, 230,
			XmNy, 460,
			NULL );
	XtAddCallback( Apply_pbFont, XmNactivateCallback,
		(XtCallbackProc) activateCB_Apply_pbFont,
		(XtPointer) UxFontsEditorContext );

	UxPutContext( Apply_pbFont, (char *) UxFontsEditorContext );


	/* Creation of display_box */
	display_box = XtVaCreateManagedWidget( "display_box",
			xmFrameWidgetClass,
			form6,
			XmNshadowThickness, 1,
			XmNshadowType, XmSHADOW_ETCHED_OUT,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 8,
			XmNbottomWidget, Apply_pbFont,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 9,
			XmNresizable, FALSE,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 8,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 5,
			XmNtopPosition, 65,
			NULL );
	UxPutContext( display_box, (char *) UxFontsEditorContext );


	/* Creation of display_text */
	display_text = XtVaCreateManagedWidget( "display_text",
			xmTextWidgetClass,
			display_box,
			XmNx, 0,
			XmNy, 0,
			XmNshadowThickness, 2,
			XmNeditMode, XmMULTI_LINE_EDIT ,
			XmNvalue, "This is an example of working font\n\
abcdefghijklmnopqrstuvwxyz\n\
ABCDEFGHIJKLMNOPQRSTUVWXYZ\n\
! @ $ % ^ & * () [] {} : ; \" `' ~ , . ? / \\",
			NULL );
	UxPutContext( display_text, (char *) UxFontsEditorContext );


	/* Creation of fontname_text */
	fontname_text = XtVaCreateManagedWidget( "fontname_text",
			xmTextWidgetClass,
			form6,
			XmNeditable, FALSE,
			XmNhighlightThickness, 0,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 10,
			XmNbottomPosition, 65,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			NULL );
	UxPutContext( fontname_text, (char *) UxFontsEditorContext );


	/* Creation of list1_label */
	list1_label = XtVaCreateManagedWidget( "list1_label",
			xmLabelWidgetClass,
			form6,
			XmNborderWidth, 0,
			RES_CONVERT( XmNlabelString, "Family or Short Name" ),
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 8,
			XmNtopAttachment, XmATTACH_FORM,
			NULL );
	UxPutContext( list1_label, (char *) UxFontsEditorContext );


	/* Creation of font_swin_3 */
	font_swin_3 = XtVaCreateManagedWidget( "font_swin_3",
			xmScrolledWindowWidgetClass,
			form6,
			XmNborderWidth, 0,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			XmNvisualPolicy, XmVARIABLE,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomWidget, fontname_text,
			XmNresizable, FALSE,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 1,
			XmNtopWidget, list1_label,
			NULL );
	UxPutContext( font_swin_3, (char *) UxFontsEditorContext );


	/* Creation of font_list_3 */
	font_list_3 = XtVaCreateManagedWidget( "font_list_3",
			xmListWidgetClass,
			font_swin_3,
			RES_CONVERT( XmNitems, "font sizing (all aspects) and std character set" ),
			XmNitemCount, 1,
			XmNselectionPolicy, XmSINGLE_SELECT,
			NULL );
	XtAddCallback( font_list_3, XmNsingleSelectionCallback,
		(XtCallbackProc) singleSelectionCB_font_list_3,
		(XtPointer) UxFontsEditorContext );

	UxPutContext( font_list_3, (char *) UxFontsEditorContext );


	/* Creation of font_swin_2 */
	font_swin_2 = XtVaCreateManagedWidget( "font_swin_2",
			xmScrolledWindowWidgetClass,
			form6,
			XmNborderWidth, 0,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			XmNvisualPolicy, XmVARIABLE,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomWidget, fontname_text,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNrightWidget, font_swin_3,
			XmNresizable, FALSE,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 1,
			XmNtopWidget, list1_label,
			NULL );
	UxPutContext( font_swin_2, (char *) UxFontsEditorContext );


	/* Creation of font_list_2 */
	font_list_2 = XtVaCreateManagedWidget( "font_list_2",
			xmListWidgetClass,
			font_swin_2,
			XmNx, 0,
			XmNy, 0,
			RES_CONVERT( XmNitems, "any font description" ),
			XmNitemCount, 1,
			XmNselectionPolicy, XmSINGLE_SELECT,
			NULL );
	XtAddCallback( font_list_2, XmNsingleSelectionCallback,
		(XtCallbackProc) singleSelectionCB_font_list_2,
		(XtPointer) UxFontsEditorContext );

	UxPutContext( font_list_2, (char *) UxFontsEditorContext );


	/* Creation of font_swin_1 */
	font_swin_1 = XtVaCreateManagedWidget( "font_swin_1",
			xmScrolledWindowWidgetClass,
			form6,
			XmNx, 10,
			XmNy, 50,
			XmNborderWidth, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomWidget, fontname_text,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNresizable, FALSE,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNrightWidget, font_swin_2,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 1,
			XmNtopWidget, list1_label,
			NULL );
	UxPutContext( font_swin_1, (char *) UxFontsEditorContext );


	/* Creation of font_list_1 */
	font_list_1 = XtVaCreateManagedWidget( "font_list_1",
			xmListWidgetClass,
			font_swin_1,
			RES_CONVERT( XmNitems, "initial font foundry and family (by name)" ),
			XmNitemCount, 1,
			XmNlistMarginWidth, 2,
			XmNselectionPolicy, XmSINGLE_SELECT,
			NULL );
	XtAddCallback( font_list_1, XmNsingleSelectionCallback,
		(XtCallbackProc) singleSelectionCB_font_list_1,
		(XtPointer) UxFontsEditorContext );

	UxPutContext( font_list_1, (char *) UxFontsEditorContext );


	/* Creation of list2_label */
	list2_label = XtVaCreateManagedWidget( "list2_label",
			xmLabelWidgetClass,
			form6,
			XmNx, 330,
			XmNy, 10,
			XmNborderWidth, 0,
			RES_CONVERT( XmNlabelString, "Font" ),
			XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNleftOffset, 0,
			XmNleftWidget, font_swin_2,
			XmNtopAttachment, XmATTACH_FORM,
			NULL );
	UxPutContext( list2_label, (char *) UxFontsEditorContext );


	/* Creation of list3_label */
	list3_label = XtVaCreateManagedWidget( "list3_label",
			xmLabelWidgetClass,
			form6,
			XmNborderWidth, 0,
			RES_CONVERT( XmNlabelString, "Size and Charset" ),
			XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET,
			XmNleftOffset, 0,
			XmNleftWidget, font_swin_3,
			XmNtopAttachment, XmATTACH_FORM,
			NULL );
	UxPutContext( list3_label, (char *) UxFontsEditorContext );


	/* Creation of OK_pbFont */
	OK_pbFont = XtVaCreateManagedWidget( "OK_pbFont",
			xmPushButtonGadgetClass,
			form6,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNheight, 30,
			XmNwidth, 140,
			XmNy, 210,
			XmNx, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 6,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 5,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 31,
			NULL );
	XtAddCallback( OK_pbFont, XmNactivateCallback,
		(XtCallbackProc) activateCB_OK_pbFont,
		(XtPointer) UxFontsEditorContext );

	UxPutContext( OK_pbFont, (char *) UxFontsEditorContext );


	/* Creation of Close_pbFont */
	Close_pbFont = XtVaCreateManagedWidget( "Close_pbFont",
			xmPushButtonGadgetClass,
			form6,
			RES_CONVERT( XmNlabelString, "Cancel" ),
			XmNheight, 30,
			XmNwidth, 140,
			XmNy, 420,
			XmNx, 380,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 6,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 68,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 95,
			NULL );
	XtAddCallback( Close_pbFont, XmNactivateCallback,
		(XtCallbackProc) activateCB_Close_pbFont,
		(XtPointer) UxFontsEditorContext );

	UxPutContext( Close_pbFont, (char *) UxFontsEditorContext );


	XtAddCallback( FontsEditor, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxFontsEditorContext);


	return ( FontsEditor );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_FontsEditor( _UxTextFont, _UxChiamFonEd )
	Widget	_UxTextFont;
	Widget	_UxChiamFonEd;
{
	Widget                  rtrn;
	_UxCFontsEditor         *UxContext;
	static int		_Uxinit = 0;

	UxFontsEditorContext = UxContext =
		(_UxCFontsEditor *) UxNewContext( sizeof(_UxCFontsEditor), False );

	TextFont = _UxTextFont;
	ChiamFonEd = _UxChiamFonEd;

	if ( ! _Uxinit )
	{
		UxLoadResources( "FontsEditor.rf" );
		_Uxinit = 1;
	}

	{
		char pattern[MAX_BUFSIZE]; 
		
		TextF = TextFont;
		
		first_list = second_list = third_list = NULL; 
		first_len  = second_len  = third_len  = 0;
		first_sel  = second_sel  = third_sel  = NULL;
		rtrn = _Uxbuild_FontsEditor();

		first_list = (unsigned char **)load_list (1,"*",&first_len);         /* populate first list */
		
		first_sel = first_list[0]; 
		put_list_items (font_list_1, first_list, first_len, 0);   /* fill display */
		
		load_list2 ();
		load_list3 ();
		put_font ();
		
		/*  Setta la posizione dell'interfaccia rispetto al parent  */
		InterfaceSetPos (FontsEditor,ChiamFonEd);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/


! UIMX ascii 2.5 key: 8869                                                      

*FontsEditor.class: topLevelShell
*FontsEditor.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo FontsEditor.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)FontsEditor.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <string.h>\
#include "res_edit.h"\
\
#define MAX_FONTS  2000\
#define MAX_BUFSIZE 500\
\
extern Display *UxDisplay;\
extern void qsort();\
\
static char ** load_list(); \
static void put_list_items(); \
static void free_list(); \
static void put_font (); \
static void load_list2 (); \
static void load_list3 (); \
\

*FontsEditor.ispecdecl: /* The font viewer has three scrolled lists;\
 * Each contents a different portion of a font's name string.\
 * Each list contains only the completions of the partial string\
 * selected in the previous lists.\
 */\
\
char **first_list ;     /* first column  - foundry and family */\
char **second_list ;    /* second column - typeface          */\
char **third_list ;     /* third column  - size and charset  */\
\
int first_len; 	    /* lengths of the lists ... */\
int second_len; \
int third_len; \
\
char *first_sel; 	    /* current selection from each list */\
char *second_sel; \
char *third_sel; \
\
Widget TextF;\

*FontsEditor.ispeclist: first_list, second_list, third_list, first_len, second_len, third_len, first_sel, second_sel, third_sel, TextF
*FontsEditor.ispeclist.first_list: "unsigned char", "**%first_list%"
*FontsEditor.ispeclist.second_list: "unsigned char", "**%second_list%"
*FontsEditor.ispeclist.third_list: "unsigned char", "**%third_list%"
*FontsEditor.ispeclist.first_len: "int", "%first_len%"
*FontsEditor.ispeclist.second_len: "int", "%second_len%"
*FontsEditor.ispeclist.third_len: "int", "%third_len%"
*FontsEditor.ispeclist.first_sel: "unsigned char", "*%first_sel%"
*FontsEditor.ispeclist.second_sel: "unsigned char", "*%second_sel%"
*FontsEditor.ispeclist.third_sel: "unsigned char", "*%third_sel%"
*FontsEditor.ispeclist.TextF: "Widget", "%TextF%"
*FontsEditor.funcdecl: swidget create_FontsEditor(Widget TextFont,Widget ChiamFonEd)\

*FontsEditor.funcname: create_FontsEditor
*FontsEditor.funcdef: "swidget", "<create_FontsEditor>(%)"
*FontsEditor.argdecl: Widget TextFont;\
Widget ChiamFonEd;
*FontsEditor.arglist: TextFont, ChiamFonEd
*FontsEditor.arglist.TextFont: "Widget", "%TextFont%"
*FontsEditor.arglist.ChiamFonEd: "Widget", "%ChiamFonEd%"
*FontsEditor.icode: char pattern[MAX_BUFSIZE]; \
\
TextF = TextFont;\
\
first_list = second_list = third_list = NULL; \
first_len  = second_len  = third_len  = 0;\
first_sel  = second_sel  = third_sel  = NULL; \

*FontsEditor.fcode: first_list = (unsigned char **)load_list (1,"*",&first_len);         /* populate first list */\
\
first_sel = first_list[0]; \
put_list_items (font_list_1, first_list, first_len, 0);   /* fill display */\
\
load_list2 ();\
load_list3 ();\
put_font ();\
\
/*  Setta la posizione dell'interfaccia rispetto al parent  */\
InterfaceSetPos (FontsEditor,ChiamFonEd);\
\
return(rtrn);
*FontsEditor.auxdecl: /* split_font_name() -  Extract one of the 3 list components from a font name. \
 *			The 'part' argument says which portion (1,2,or,3) to return. \
 *  			Splitting is done by counting dashes, so all abbreviated names\
 *			like 'fixed' go in the first list.\
 */ \
 \
char* split_font_name (name, part) \
	char* name; \
	int   part; \
{ \
	static char* buff = NULL; \
	static int   buflen = 0; \
	char * bufptr; \
	char * result; \
	int i; \
 \
	if (name == NULL) { \
		return ""; \
	} \
\
	if (buff == NULL) { \
		buff = malloc(buflen=128); \
	} \
	while (buflen <= strlen(name)) { \
		buff = realloc(buff, buflen*=2);  \
	} \
 \
	strcpy(buff,name); \
\
	if (! strchr(name,'-')) {    /* no dashes - simple name */\
		if (part == 1) {\
			return buff; \
		} else { \
			return ""; \
		} \
	} \
 \
	bufptr = buff; \
	for (i=0; i<3; i++) { 	  /* first part, 3 dashes: -adobe-courier- */\
		while (*bufptr && *bufptr != '-') \
			*bufptr++; \
		if (*bufptr == '-')  \
			*bufptr ++; \
	} \
	if (part == 1) { \
	   *bufptr = '\000'; \
	   return buff; \
	} \
	result = bufptr; \
	for (i=0; i<4; i++) {     /* second part,4 dashes: bold-i-normal-- */\
		while (*bufptr && *bufptr != '-') \
			*bufptr++; \
		if (*bufptr == '-')  \
			*bufptr ++; \
	} \
	if (part == 2) { \
		*bufptr = '\000'; \
		return result; \
	} \
	else \
		return bufptr; \
}	 \
 \
/* unique_nth_parts () - given a list of fonts, build a list \
 *			 of the unique nth portions of each font string \
 *			 (the contents of our scrolled lists).\
 *			 The length of the result is returned in result_len. \
 *			 ASSUMES lists from XListFontNames are sorted. \
 */ \
char ** unique_nth_parts (fonts, fonts_len, nth, result_len) \
	char	** fonts; \
	int 	fonts_len; \
	int 	nth; \
	int	* result_len; \
{ \
	int 	n = 0; \
	char	** result; \
	char 	* part; \
	char 	pattern[MAX_BUFSIZE]; \
	int  	i; \
 \
	result    = (char**) malloc( sizeof(char*) * fonts_len); \
 \
	for (i=0; i<fonts_len; i++) { \
		part = split_font_name (fonts[i], nth); \
		if (part[0] == '\000')  { \
		   	continue; \
		} else if ((n==0) || (strcmp(result[n-1], part)!=0)) { \
		    	/* test above assumes that fonts come sorted. */ \
		    	result [n++] = XtNewString (part); \
		} \
	} \
	*result_len = n; \
	return result; \
} \
 \
/* load_list () - given a seed pattern (presumably the start of a font name) \
 * 		  build the list of font components containing the pattern. \
 *		  That is, given a selected font at one scrolled list, \
 *		  build the sublist of components for the next scrolled list. \
 */ \
 \
/* compare the font strings. */ \
comp(arg1,arg2) \
        char **arg1; \
        char **arg2; \
{ \
        if ( (*arg1 == NULL) && (*arg2 == NULL)) { \
                return 0; \
        } \
        if ((*arg1 == NULL) || (*arg2 == NULL)) { \
                return 1; \
        } \
        if (*arg1 && *arg2) { \
                return strcmp(*arg1, *arg2); \
        } \
} \
 \
static char **load_list (which_list, pattern, length) \
	int 	which_list; \
	char 	* pattern; \
	int  	* length; \
{ \
	char **fonts; \
	char **list; \
	char **sorted_fonts; \
	int  num_fonts; \
	int  i; \
 \
        /* get the unsorted font list. */ \
	fonts = XListFonts(UxDisplay, pattern, MAX_FONTS, &num_fonts); \
 \
        /* reserve space for the font list. */ \
        sorted_fonts = (char **) malloc(num_fonts * sizeof(char *)); \
        /* load the font list. */ \
        for (i=0; i < num_fonts; i++) \
                { \
                sorted_fonts[i] = (char *) malloc( strlen(fonts[i])+1 ); \
                strncpy(sorted_fonts[i],fonts[i], strlen(fonts[i])+1); \
                } \
 \
        /* sort the font list. */ \
        qsort(sorted_fonts, num_fonts, sizeof(char *), comp); \
 \
	if (num_fonts == MAX_FONTS) { \
	   	printf("Maximum number of fonts loaded; may be some missing.\n"); \
	} \
	list  = unique_nth_parts (sorted_fonts, num_fonts, which_list, length); \
 \
	XFreeFontNames(fonts); \
        for (i=0; i < num_fonts; i++) { \
                free(sorted_fonts[i]); \
        } \
        free(sorted_fonts); \
 \
	return list; \
} \
 \
/*  put_list_items () - put the given list of strings as the item list \
 *			of the given XmList swidget.   \
 *			Make the sel'th item the selection. \
 */ \
 \
static void put_list_items (list, items, n, sel) \
	swidget list; \
	char    **items; \
	int	n; \
	int     sel; \
{ \
	Arg	arg[5]; \
	int  	i; \
	XmString * xm_items = (XmString*) malloc (n * sizeof(XmString)); \
 \
	for (i=0; i<n; i++) { \
		xm_items[i] = XmStringCreateLtoR (items[i],  \
						 XmSTRING_DEFAULT_CHARSET);  \
	} \
 \
	XtSetArg (arg[0], XmNitems, xm_items);  \
      	XtSetArg (arg[1], XmNitemCount, n);\
      	XtSetArg (arg[2], XmNselectedItems, &(xm_items[sel]));  \
      	XtSetArg (arg[3], XmNselectedItemCount, n>0 ? 1 : 0);  \
      	XtSetValues (UxGetWidget(list), arg, 4);  \
 \
	for (i=0; i<n; i++) { \
		XmStringFree(xm_items[i]); \
	} \
	free (xm_items); \
} \
 \
/*  free_list() - free the dynamic space from one of our char** arrays. \
 */ \
 \
static void free_list (list, n) \
	char **list; \
	int  n; \
{  \
	while (--n > 0) { \
	  	free (list[n]); \
	} \
	free (list); \
} \
 \
/*  put_font()  - use the current selection set as the font name \
 *		  for the display. \
 */  \
 \
static void put_font() \
{ \
	XFontStruct *StrutturaFont;\
	char font[MAX_BUFSIZE]; \
	\
	if (second_sel == NULL) { \
		sprintf(font, "%s", first_sel ); \
	} else if (third_sel == NULL) { \
		sprintf(font, "%s%s", first_sel, second_sel); \
	} else { \
		sprintf(font, "%s%s%s", first_sel, second_sel, third_sel); \
	} \
\
	StrutturaFont = XLoadQueryFont (UxDisplay, font);\
	set_something (display_text, XmNfontList, XmFontListCreate (StrutturaFont,\
			XmSTRING_DEFAULT_CHARSET));\
	XmTextSetString (fontname_text, font); \
} \
\
/* in_list()  - find a string in an array of strings that matches a given string. \
 *		'matches' means equal in the first cmp_len characters. \
 *		returns the found index, or -1. \
 */ \
\
static int in_list (list, len, elem, cmp_len) \
	char	** list; \
	int	len; \
	char 	* elem; \
	int    cmp_len; \
{ \
	if (elem == NULL) return -1; \
\
	while (--len >= 0) { \
		if (strncmp(list[len], elem, cmp_len) == 0) { \
			return len; \
		} \
	} \
	return -1; \
} \
\
/* load_list2() -  given the current selection in list1, load list2. \
 */ \
\
static void load_list2 () \
{ \
	char* old_sel; \
	int   old_len; \
	char** old_list; \
	char pattern [MAX_BUFSIZE]; \
	int Numero,sel; \
	\
	old_list = (char **)second_list; \
	old_sel  = (char *)second_sel; \
	old_len  = second_len; \
	\
	if (first_sel==NULL) { \
		second_list = NULL; \
		second_len = 0; \
		second_sel = NULL; \
	} else { \
		sprintf(pattern, "%s*", first_sel); \
		second_list = (unsigned char **)load_list(2, pattern, &second_len); \
		if (second_len > 0) { \
		   second_sel = second_list[0]; \
		} else { \
		   second_sel = NULL; \
		} \
	} \
	\
	/* If the previous selection is in this list, leave it. \
	 * The '128' is simply long enough to do a complete comparison. \
	 * If the list was and is empty, don't reset it. \
	 */ \
	if ((sel = in_list(second_list, second_len, old_sel, 128)) != -1)  {\
		second_sel = second_list[sel]; \
	} else { \
		sel = 0; \
	}\
	get_something (font_list_2, XmNitemCount, &Numero);\
	if ( (second_len != 0) || (Numero != 0)) { \
		put_list_items (font_list_2, second_list, second_len, sel); \
	} \
\
	if (old_list) \
		free_list (old_list, old_len); \
\
} \
/* load_list3() -  given the current selection in list2, load list3. \
 */ \
\
static void load_list3 () \
{ \
	char* old_sel; \
	int   old_len; \
	char** old_list; \
	char pattern [MAX_BUFSIZE]; \
	int Numero,sel; \
	\
	old_list = (char **)third_list; \
	old_sel  = (char *)third_sel; \
	old_len  = third_len; \
	\
	if (second_sel==NULL) { \
		third_list = NULL; \
		third_len = 0; \
		third_sel = NULL; \
	} else { \
		sprintf(pattern, "%s%s*", first_sel, second_sel); \
		third_list = (unsigned char **)load_list(3, pattern, &third_len); \
		if (third_len > 0) { \
		   third_sel = third_list[0]; \
		} else { \
		   third_sel = NULL; \
		} \
	} \
	\
	/* If the previous selection is in this list, leave it. \
	 * In this third portion of the font spec, the first field is \
	 * the point size, so the '3' to in_list() means we keep \
	 * the selection on the same point size if possible. \
	 * If the list was and is empty, don't reset it. \
	 */ \
	if ((sel =in_list(third_list, third_len, old_sel, 3)) != -1)  {\
		third_sel = third_list[sel]; \
	} else { \
		sel = 0;\
	}\
	get_something (font_list_3, XmNitemCount, &Numero); \
	if ( (third_len != 0) || (Numero != 0)) { \
		put_list_items (font_list_3, third_list, third_len, sel); \
	} \
\
	if (old_list) \
		free_list (old_list, old_len); \
\
} 
*FontsEditor.static: true
*FontsEditor.name: FontsEditor
*FontsEditor.parent: NO_PARENT
*FontsEditor.parentExpression: ChiamFonEd
*FontsEditor.x: 547
*FontsEditor.y: 41
*FontsEditor.width: 620
*FontsEditor.height: 470
*FontsEditor.allowShellResize: "true"

*form6.class: form
*form6.static: true
*form6.name: form6
*form6.parent: FontsEditor
*form6.width: 620
*form6.height: 470
*form6.allowShellResize: "true"
*form6.allowOverlap: "false"
*form6.dialogTitle: "Resource Font Editor"
*form6.horizontalSpacing: 6
*form6.verticalSpacing: 6

*Apply_pbFont.class: pushButtonGadget
*Apply_pbFont.static: true
*Apply_pbFont.name: Apply_pbFont
*Apply_pbFont.parent: form6
*Apply_pbFont.labelString: "Apply"
*Apply_pbFont.activateCallback: {\
char *Appoggio;\
\
Appoggio = XmTextGetString (fontname_text);\
\
XmTextFieldSetString (TextF,Appoggio);\
XtFree (Appoggio);\
}
*Apply_pbFont.bottomAttachment: "attach_form"
*Apply_pbFont.bottomOffset: 6
*Apply_pbFont.leftAttachment: "attach_position"
*Apply_pbFont.leftPosition: 37
*Apply_pbFont.rightAttachment: "attach_position"
*Apply_pbFont.rightPosition: 63
*Apply_pbFont.x: 230
*Apply_pbFont.y: 460

*display_box.class: frame
*display_box.static: true
*display_box.name: display_box
*display_box.parent: form6
*display_box.shadowThickness: 1
*display_box.shadowType: "shadow_etched_out"
*display_box.bottomAttachment: "attach_widget"
*display_box.bottomOffset: 8
*display_box.bottomWidget: "Apply_pbFont"
*display_box.leftAttachment: "attach_form"
*display_box.leftOffset: 9
*display_box.resizable: "false"
*display_box.rightAttachment: "attach_form"
*display_box.rightOffset: 8
*display_box.topAttachment: "attach_position"
*display_box.topOffset: 5
*display_box.topPosition: 65

*display_text.class: text
*display_text.static: true
*display_text.name: display_text
*display_text.parent: display_box
*display_text.x: 0
*display_text.y: 0
*display_text.shadowThickness: 2
*display_text.editMode: "multi_line_edit"
*display_text.text: "This is an example of working font\n\\
abcdefghijklmnopqrstuvwxyz\n\\
ABCDEFGHIJKLMNOPQRSTUVWXYZ\n\\
! @ $ % ^ & * () [] {} : ; \" `' ~ , . ? / \\"   

*fontname_text.class: text
*fontname_text.static: true
*fontname_text.name: fontname_text
*fontname_text.parent: form6
*fontname_text.editable: "false"
*fontname_text.highlightThickness: 0
*fontname_text.fontList.source: public
*fontname_text.fontList: "-*-Helvetica-Medium-R-Normal--12-*"
*fontname_text.bottomAttachment: "attach_position"
*fontname_text.bottomOffset: 10
*fontname_text.bottomPosition: 65
*fontname_text.leftAttachment: "attach_form"
*fontname_text.leftOffset: 10
*fontname_text.rightAttachment: "attach_form"
*fontname_text.rightOffset: 10

*list1_label.class: label
*list1_label.static: true
*list1_label.name: list1_label
*list1_label.parent: form6
*list1_label.borderWidth: 0
*list1_label.labelString: "Family or Short Name"
*list1_label.leftAttachment: "attach_form"
*list1_label.leftOffset: 8
*list1_label.topAttachment: "attach_form"

*font_swin_3.class: scrolledWindow
*font_swin_3.static: true
*font_swin_3.name: font_swin_3
*font_swin_3.parent: form6
*font_swin_3.borderWidth: 0
*font_swin_3.shadowThickness: 0
*font_swin_3.scrollBarDisplayPolicy: "static"
*font_swin_3.scrollingPolicy: "application_defined"
*font_swin_3.visualPolicy: "variable"
*font_swin_3.bottomAttachment: "attach_widget"
*font_swin_3.bottomWidget: "fontname_text"
*font_swin_3.resizable: "false"
*font_swin_3.rightAttachment: "attach_form"
*font_swin_3.rightOffset: 10
*font_swin_3.topAttachment: "attach_widget"
*font_swin_3.topOffset: 1
*font_swin_3.topWidget: "list1_label"

*font_list_3.class: scrolledList
*font_list_3.static: true
*font_list_3.name: font_list_3
*font_list_3.parent: font_swin_3
*font_list_3.fontList.source: public
*font_list_3.fontList: "-*-Helvetica-Medium-R-Normal--10-*"
*font_list_3.items: "font sizing (all aspects) and std character set"
*font_list_3.itemCount: 1
*font_list_3.selectionPolicy: "single_select"
*font_list_3.singleSelectionCallback: {\
	char pattern[MAX_BUFSIZE];\
	XmListCallbackStruct *cbs = (XmListCallbackStruct *)UxCallbackArg;\
\
	XmStringGetLtoR(cbs->item, XmSTRING_DEFAULT_CHARSET, &third_sel);\
	put_font (); \
}

*font_swin_2.class: scrolledWindow
*font_swin_2.static: true
*font_swin_2.name: font_swin_2
*font_swin_2.parent: form6
*font_swin_2.borderWidth: 0
*font_swin_2.shadowThickness: 0
*font_swin_2.scrollBarDisplayPolicy: "static"
*font_swin_2.scrollingPolicy: "application_defined"
*font_swin_2.visualPolicy: "variable"
*font_swin_2.bottomAttachment: "attach_widget"
*font_swin_2.bottomWidget: "fontname_text"
*font_swin_2.rightAttachment: "attach_widget"
*font_swin_2.rightWidget: "font_swin_3"
*font_swin_2.resizable: "false"
*font_swin_2.topAttachment: "attach_widget"
*font_swin_2.topOffset: 1
*font_swin_2.topWidget: "list1_label"

*font_list_2.class: scrolledList
*font_list_2.static: true
*font_list_2.name: font_list_2
*font_list_2.parent: font_swin_2
*font_list_2.x: 0
*font_list_2.y: 0
*font_list_2.fontList.source: public
*font_list_2.fontList: "-*-Helvetica-Medium-R-Normal--10-*"
*font_list_2.items: "any font description"
*font_list_2.itemCount: 1
*font_list_2.selectionPolicy: "single_select"
*font_list_2.singleSelectionCallback: {\
	char pattern[MAX_BUFSIZE];\
	XmListCallbackStruct *cbs = (XmListCallbackStruct *)UxCallbackArg;\
\
	/* Small memory leak */ \
	XmStringGetLtoR(cbs->item, XmSTRING_DEFAULT_CHARSET, &second_sel);\
	\
	/* Set up list 3 */\
	load_list3();\
	\
	put_font(); \
}

*font_swin_1.class: scrolledWindow
*font_swin_1.static: true
*font_swin_1.name: font_swin_1
*font_swin_1.parent: form6
*font_swin_1.x: 10
*font_swin_1.y: 50
*font_swin_1.borderWidth: 0
*font_swin_1.scrollBarDisplayPolicy: "static"
*font_swin_1.scrollingPolicy: "application_defined"
*font_swin_1.bottomAttachment: "attach_widget"
*font_swin_1.bottomWidget: "fontname_text"
*font_swin_1.leftAttachment: "attach_form"
*font_swin_1.leftOffset: 10
*font_swin_1.resizable: "false"
*font_swin_1.rightAttachment: "attach_widget"
*font_swin_1.rightWidget: "font_swin_2"
*font_swin_1.topAttachment: "attach_widget"
*font_swin_1.topOffset: 1
*font_swin_1.topWidget: "list1_label"

*font_list_1.class: scrolledList
*font_list_1.static: true
*font_list_1.name: font_list_1
*font_list_1.parent: font_swin_1
*font_list_1.fontList.source: public
*font_list_1.fontList: "-*-Helvetica-Medium-R-Normal--10-*"
*font_list_1.items: "initial font foundry and family (by name)"
*font_list_1.itemCount: 1
*font_list_1.listMarginWidth: 2
*font_list_1.selectionPolicy: "single_select"
*font_list_1.singleSelectionCallback: {\
	XmListCallbackStruct *cbs = (XmListCallbackStruct *)UxCallbackArg;\
\
	XmStringGetLtoR(cbs->item, XmSTRING_DEFAULT_CHARSET, &first_sel);\
	\
	/* Set up list 2 */\
	load_list2(); \
	\
	/* Set up list 3 */\
	load_list3();\
	\
	put_font(); \
}

*list2_label.class: label
*list2_label.static: true
*list2_label.name: list2_label
*list2_label.parent: form6
*list2_label.x: 330
*list2_label.y: 10
*list2_label.borderWidth: 0
*list2_label.labelString: "Font"
*list2_label.leftAttachment: "attach_opposite_widget"
*list2_label.leftOffset: 0
*list2_label.leftWidget: "font_swin_2"
*list2_label.topAttachment: "attach_form"

*list3_label.class: label
*list3_label.static: true
*list3_label.name: list3_label
*list3_label.parent: form6
*list3_label.borderWidth: 0
*list3_label.labelString: "Size and Charset"
*list3_label.leftAttachment: "attach_opposite_widget"
*list3_label.leftOffset: 0
*list3_label.leftWidget: "font_swin_3"
*list3_label.topAttachment: "attach_form"

*OK_pbFont.class: pushButtonGadget
*OK_pbFont.static: true
*OK_pbFont.name: OK_pbFont
*OK_pbFont.parent: form6
*OK_pbFont.labelString: "OK"
*OK_pbFont.activateCallback: {\
char *Appoggio;\
\
Appoggio = XmTextGetString (fontname_text);\
\
XmTextFieldSetString(TextF,Appoggio);\
XtFree (Appoggio);\
XtDestroyWidget (FontsEditor);\
}
*OK_pbFont.height: 30
*OK_pbFont.width: 140
*OK_pbFont.y: 210
*OK_pbFont.x: 10
*OK_pbFont.bottomAttachment: "attach_form"
*OK_pbFont.bottomOffset: 6
*OK_pbFont.leftAttachment: "attach_position"
*OK_pbFont.leftOffset: 0
*OK_pbFont.leftPosition: 5
*OK_pbFont.rightAttachment: "attach_position"
*OK_pbFont.rightPosition: 31

*Close_pbFont.class: pushButtonGadget
*Close_pbFont.static: true
*Close_pbFont.name: Close_pbFont
*Close_pbFont.parent: form6
*Close_pbFont.labelString: "Cancel"
*Close_pbFont.activateCallback: {\
	XtDestroyWidget (FontsEditor);\
}
*Close_pbFont.height: 30
*Close_pbFont.width: 140
*Close_pbFont.y: 420
*Close_pbFont.x: 380
*Close_pbFont.bottomAttachment: "attach_form"
*Close_pbFont.bottomOffset: 6
*Close_pbFont.leftAttachment: "attach_position"
*Close_pbFont.leftOffset: 0
*Close_pbFont.leftPosition: 68
*Close_pbFont.rightAttachment: "attach_position"
*Close_pbFont.rightPosition: 95


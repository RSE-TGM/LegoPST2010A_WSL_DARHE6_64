/**********************************************************************
*
*       C Source:               clip.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 12:23:29 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: clip.c,2 %  (%full_filespec: 1,csrc,clip.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)clip.c	1.10\t3/28/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <stdlib.h>
#include <X11/Intrinsic.h>
#include <Xm/CutPaste.h>

int ScriviClipboard (data,Oggetto)
char *data;
Widget Oggetto;
{
	extern XmString nome_clip;
	extern Display  *UxDisplay;

	unsigned long 	item_id;
	int           	status;
	int  		cnt;
	Window		fin;

	cnt = 1;
	fin = XtWindowOfObject (Oggetto);
	do
		status = XmClipboardStartCopy (UxDisplay,fin,nome_clip,
			CurrentTime,NULL,NULL,&item_id);
	while (status == ClipboardLocked);
	do
		status = XmClipboardCopy (UxDisplay,fin,item_id,
			"STRING",data,(long)strlen(data)+1,cnt,NULL);
	while (status == ClipboardLocked);
	do
		status = XmClipboardEndCopy (UxDisplay,fin,item_id);
	while (status == ClipboardLocked);
	return (0);
}

LeggiClipboard (data,Oggetto)
char **data;
Widget Oggetto;
{
	extern Display  *UxDisplay;

	int 		status;
	int 		outlen;
	unsigned long 	length;
	Window		fin;

	fin = XtWindowOfObject (Oggetto);

	if (*data != NULL)
	{
		XtFree (*data);
	}
	*data = NULL;
	do
		status=XmClipboardInquireLength(UxDisplay,fin,
					"STRING",&length);
	while (status == ClipboardLocked);
	if (length != 0)
	{
		*data = XtMalloc (length+1);
		do
			status = XmClipboardRetrieve (UxDisplay,fin,
				"STRING",*data,length+1,&outlen,NULL);
		while (status == ClipboardLocked);
	}
	return (0);
}

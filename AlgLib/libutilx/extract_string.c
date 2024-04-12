/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)extract_string.c	5.1\t11/10/95";
/*
   modulo extract_string.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)extract_string.c	5.1
*/
#include <Xm/Xm.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>

/*** char *extract_string( compound )
 *** Parametri :
 ***            compound : compound string;
funzione che converte una compound string in un array di caratteri.
Ritorna il puntatore alla stringa */
char *extract_string(compound)
XmString compound;
{
  XmStringContext context;
  XmStringCharSet charset;
  XmStringDirection direction;
  Boolean separator;
  static char *primitive_string;

  XmStringInitContext (&context,compound);
  XmStringGetNextSegment (context,&primitive_string,
                          &charset,&direction,&separator);
  XmStringFreeContext (context);
  return ((char *) primitive_string);
}
/*-------------------------------------------------------------------*/

/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
   modulo aggiunte_Xt.h
   tipo 
   release 1.3
   data 3/23/95
   reserved @(#)aggiunte_Xt.h	1.3
*/
/* Include per MOTIF10 */

#ifdef MOTIF10

typedef char*  XtPointer;

#define XtOffsetOf(s_type,field) XtOffset(s_type*,field)
#define XtExposeCompressMultiple        2
#define XtUnspecifiedPixmap      ((Pixmap)2)

#endif

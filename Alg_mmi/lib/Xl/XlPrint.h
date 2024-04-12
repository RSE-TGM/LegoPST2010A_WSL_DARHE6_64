/**********************************************************************
*
*       C Header:               XlPrint.h
*       Subsystem:              1
*       Description:
*       %created_by:    lopez %
*       %date_created:  Wed Oct 23 11:27:40 2002 %
*
**********************************************************************/
/*
   modulo XlPrint.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlPrint.h	5.1
*/


#ifndef _XlPrint_h
#define _XlPrint_h
#if !defined LINUX
#if defined XPRINTER_USED
#include <Xp.h>
#include <PrinterB.h>
#include <XpMacros.h>
#define XP_UNLOCK_CODE "woejdksd"
#endif
#endif

Display *XlDisplay(Widget);
Window XlWindow(Widget);
Widget XlPrintSetup(Widget);
Boolean XlPrintOpen(Widget);
Boolean XlPrintClose();
Boolean XlPrint(Widget);
Boolean XlPrinterIsOn();
char * XlPrinterGetFont();
Position XlPrintOffsetX(Widget);
Position XlPrintOffsetY(Widget);
Pixel XlPrintGetPixel(Widget,Pixel);
Boolean XlHardCopyWidget(Widget);
Boolean XlPrintBackgroundAndBorder(Widget cw, int);

#endif


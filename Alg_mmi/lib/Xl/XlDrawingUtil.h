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
   modulo XlDrawingUtil.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlDrawingUtil.h	5.1
*/
#ifndef _XlDrawingUtil_h
#define _XlDrawingUtil_h

/* costanti utilizzabili per settare il tipo di XlCore */

#define ROTATE_0        0
#define ROTATE_90       1
#define ROTATE_180      2
#define ROTATE_270      3
#define ROTATE_COMPLETO 4
#define NO_Y_ASS_ROTATE 0
#define Y_ASS_ROTATE    1


void XlLinea();
void XlArco();
void XlRiempiArco();
void XlRiempiRettangolo();
void XlRettangolo();
void XlTesto();
void XlTestoRot();
void gest_trasf_coor();
void gest_trasf_arc();
void gest_trasf_wh();
void gest_trasf_testo();



#endif

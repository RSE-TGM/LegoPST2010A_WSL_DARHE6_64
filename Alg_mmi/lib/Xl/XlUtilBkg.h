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
   modulo XlUtilBkg.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlUtilBkg.h	5.1
*/
#ifndef _XL_BCK_OBJ
#define _XL_BCK_OBJ



#define TIPO_LINEA      	1
#define TIPO_CERCHIO    	2
#define TIPO_RETTANGOLO 	3
#define TIPO_POLIGONO   	4
#define TIPO_CONNESSIONE   	5

struct bck_obj_st
        {
        int tipo;
        int wi_c;
        int st_c;
        Pixel fg_c;
	unsigned short fg_c_red;
	unsigned short fg_c_green;
	unsigned short fg_c_blue;
        int fg_c_cc;
        Pixel bg_c;
	unsigned short bg_c_red;
	unsigned short bg_c_green;
	unsigned short bg_c_blue;
        int bg_c_cc;
        Pixel fg_f;
	unsigned short fg_f_red;
	unsigned short fg_f_green;
	unsigned short fg_f_blue;
        int fg_f_cc;
        int fill;
        int dati[6];
	XPoint *points;
        };
typedef struct bck_obj_st BCK_OBJ;

Boolean leggi_file_bck();
Boolean disegna_bck(Widget,BCK_OBJ *,XmDrawingAreaCallbackStruct *,
		Region *,Boolean );
Boolean disegna_bck_icon(Widget,BCK_OBJ *,Pixel,Pixel,Pixel,Pixel,Boolean);
Boolean libera_lista_bck();
Boolean ruota_bck();
Boolean XlEsisteCambioColore();
#endif

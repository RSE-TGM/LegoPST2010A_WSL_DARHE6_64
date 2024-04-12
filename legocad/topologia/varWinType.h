/**********************************************************************
*
*       C Header:               varWinType.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:05:26 1996 %
*
**********************************************************************/


#ifndef VARWINTYPEH
#define VARWINTYPEH


/*
#include "UxLib.h"
*/


typedef enum _tag_sel_status {
                SELEZIONATO, NON_SELEZIONATO,
                SEL_TEMP, SEL_ON, 
                MOVE_TEMP, MOVE_ON
} SEL_STATUS;

typedef struct _tag_var_list_status {
           SEL_STATUS  status;
           Widget      wid;
           int         var;
           int         conn;
           int         bloc;
}  VAR_SEL;    


typedef struct _tag_gost_win {
                 int primo;
                 int save_x;
                 int save_y;

                 int width;
                 int height;
                 int mouse_x;
                 int mouse_y;
} GOST_WIN;


#endif

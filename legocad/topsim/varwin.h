/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef VARWIN_H
#define VARWIN_H

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
           int         model;
}   VAR_SEL;

typedef struct _tag_gost_win {
                 int primo;
                 int save_x;
                 int save_y;
                 int width;
                 int height;
                 int mouse_x;
                 int mouse_y;
} GOST_WIN;

 
typedef struct _tag_var_win {
                   int       bloc;
                   swidget   swid;
#ifndef DESIGN_TIME
                   struct _tag_var_win *succ;
#else
                   int    *succ;
#endif
} VAR_WIN_TYPE;


typedef struct _tag_selection {
                   int num;
                   int  *pos;
} SELECTION;
 

#endif

/**********************************************************************
*
*       C Header:               lg1MainWindowType.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:05:13 1996 %
*
**********************************************************************/


#ifndef LG1MWTYPEH
#define LG1MWTYPEH


typedef struct _tag_var_win {
                   int                 bloc;
#ifdef DESIGN_TIME
                   swidget             swid;
#else
                   Widget             swid;
#endif
#ifndef DESIGN_TIME
                   struct _tag_var_win *succ;
#else
                   int    *succ;
#endif
} VAR_WIN_TYPE;


typedef struct _tag_selection {
                   int num, *pos;
} SELECTION;


#endif


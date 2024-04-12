/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef _SQLTableStruct_h_
#define _SQLTableStruct_h_

EXEC SQL define NAME_LEN        18;
EXEC SQL define MAX_FIELD        250;

EXEC SQL BEGIN DECLARE SECTION;
typedef struct app_struct_table_st
        {
        int type;
        int len;
        char name[NAME_LEN+1];
        } APP_STRUCT_TABLE;
EXEC SQL END DECLARE SECTION;


int SQLGetTableStruct(char *, APP_STRUCT_TABLE **, int *);

#endif

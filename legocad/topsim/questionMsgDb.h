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
   modulo questionMsgDb.h
   tipo 
   release 1.24
   data 8/29/95
   reserved @(#)questionMsgDb.h	1.24
*/
#ifndef questionMsgDb_H
#define questionMsgDb_H

typedef enum assegna_idop { BYEBYE = 0,CREASIM,OPENSIM,REMOVESIM,SAVESIM,MODTASK,DELTASK,ADDTASK,CONNTASK,DELCONN,DELALLCONN,MSGUSR } TIPO_OP;

static char *message[] = {"",
                          "Simulator Already Exist",
                          "S01 File Not Exist, Cannot Open",
                          "Cannot Remove Selected Simulator",
                          "Save Oper",
                          "",
                          "",
                          "Task Not Valid Or Not Found",
                          "",
                          "",
                          "",
                          "" };

static char *question[] = {"Do You Really Want Exit?",
                          "Crea Oper",
                          "S01 File Not Exist, Cannot Open",
                          "All files in directory will be destroyed.Do Yoy Really Want Remove Simulator?",
                          "Save Oper",
                          "",
                          "Do Yoy Really Want Remove Selected Task?",
                          "",
                          "",
                          "Do You Really Want Delete This Connection",
                          "Do Yoy Really Want Delete All Connections Of Selected Blocks",
                          "" };
#endif





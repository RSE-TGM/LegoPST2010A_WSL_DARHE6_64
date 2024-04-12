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
   modulo OlForm_regol.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)OlForm_regol.h	5.1
*/
#include <Rt/RtMemory.h>
/*
   Elenco di define per la suddivisione delle variabili delle forms
*/
#define VAR_IN         10
#define VAR_OUT        11
#define DEF_IN         "--IN--"
#define DEF_OUT        "--UA--"
#define VAR_ANALOG     12
#define VAR_DIGIT      13
#define VAR_DATI       14
#define VAR_COLLEG     15
#define VAR_NOCOLLEG   16
#define OFF_INI_TIPO    4
#define OFF_END_TIPO    9
#define LUN_TIPO        6
/*
   Elenco di define per la ilettura delle Tags delle forms variabili e dati
*/
#define LTAGS_VAR   4 
#define LTAGS_DAT   6

/*
    Definizioni per la selezione delle variabili delle form
*/
typedef struct elenco_acc_st
        {
        int num_tags;
        char first_ch_tag[10];
        }ELENCO_ACCETTAZIONI;

typedef struct acc_st
        {
        ELENCO_ACCETTAZIONI colleg;
        ELENCO_ACCETTAZIONI all;
        }ACCETTAZIONI;

char *OlFiltraTags(char *, int , int , int );
int OlNumTipiVar(char *, int *, int *, int *);
int PosTag(OlFormObject , char *, int, int , int *);
char *EstrTagVal(OlFormObject , int, char *, int, char *);
char *EstrTagDescr(OlFormObject , int, char *, int,  char *);
char *EstrDescr(OlFormObject , int, char *);
int InsTagVal(OlFormObject , int, char *, int , char **, char *);
int InsTagDescr(OlFormObject , int, char *, int , char **, char *);
char *PosStringForm(OlFormObject , int , char *);
char *OlEstrRegTaskName(char *, char *);
/* Fine file */

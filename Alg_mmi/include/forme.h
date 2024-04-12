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
   modulo forme.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)forme.h	5.1
*/
/* Macro definita per la lettura del file delle forms */
#define out_close(stringa,file_point,num)\
                  {fprintf(stderr,\
                   "La linea del file non riconosciuta corrisponde a:\
                    \n<%s>\nLinea numero <%d>\n",stringa,num);\
                    close(file_point);\
                    return(False);}

/*
   Elenco di define per la costruzione del file delle forms
*/
#define ESTENSIONE    ".frm"
#define UNOP          "1."
#define DUEP          "2."
#define NAME          "NameForm:"
#define NUME          "NumForms:"
#define NUMEL         "NumLines:"
#define TITLE         ".Title:"
#define TITLV         "1.Title:      block's variables"
#define TITLD         "2.Title:      block's data values"
#define TYPE          ".type:"
#define LABEL         ".label:"
#define FORMAT        ".format:"
#define VALUE         ".value:"
#define DESCR         ".descr:"
#define DESCRIZIONE   "descr"
#define INPUT         "input"
#define FLOAT         "%f"
#define ZERO          "0.00"
#define DESCDATI      "*   "
#define BLANK         "blank"
/* offset inizio valore numerico dato */
#define OFF_INI_DATO1 14
#define OFF_INI_DATO2 39
#define OFF_INI_DATO3 64
/* offset asterisco di fine dato */
#define OFF_END_DATO1 24 
#define OFF_END_DATO2 49
#define OFF_END_DATO3 74
/* offset inizio descrizione */
#define OFF_INI_DESC1 4
#define OFF_INI_DESC2 29
#define OFF_INI_DESC3 54
/* Usato da WriteStrInp */
#define APICI         "' '"
#define SEPARATORE    "| |"
/*
   Elenco di define per la costruzione del file delle forms
*/
#define INT 1
#define STR 2
#define LETT_STRIN 3
#define LETT_INPUT 4
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
#define LCAR_TAGS_VAR   4
#define LCAR_TAGS_DAT   8

/* Define per l'interpretazione del ritorno della system (tratte da <sys/wait.h>*/
#ifndef OSF1
/* evaluates to a non-zero value if status returned for normal termination */
#define W_IFEXITED(x)    ( !((x) & 0xff) )
/* evaluates to the low-order 8 bits of the child exit status   */
#define W_EXITSTATUS(x)  (int)(W_IFEXITED(x) ? (((x) >> 8) & 0xff) : -1)
/* Fine file */
#else
#include <sys/wait.h>
#define W_EXITSTATUS(x)  WEXITSTATUS(x)
#endif

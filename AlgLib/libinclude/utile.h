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
   modulo utile.h
   tipo 
   release 5.2
   data 1/11/96
   reserved @(#)utile.h	5.2
*/
/* utile.h */
/* Buffo Massimo, Calleri Nicola 11/06/1992 */
/* Prototipi delle funzioni definite in utile.h */

char *nzero();
char *trim_blank();
void s_warning();
void s_error();
void  tomaius();
void  tominus();

int IsNumeric(char*);
void riempi(char*,int);
void copy_n_car(char *,char *,int);
int     data (int*, int*, int*);
int     ora (int*, int*, int*);
int tempo_file_touch(char *);
int tempo_file_eq(char *,char *);




/* fine utile.h */


/*
   modulo curxy.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)curxy.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include "stdio.h"
#include "ctype.h"
curxy(x,y)
  int x;
  int y;
{
 printf("\033[%d;%dH",x,y);
}

/*
   modulo erase_sc.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)erase_sc.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include "stdio.h"
#include "ctype.h"

erase_screen ()
{
  printf("\033[2J");
}

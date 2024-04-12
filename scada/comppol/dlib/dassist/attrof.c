/*
   modulo attrof.c
   tipo 
   release 1.2
   data 6/10/96
   reserved @(#)attrof.c	1.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include "stdio.h"
#include "ctype.h"

/************************** ATTRIB_OFF **************************/
attrib_off()
{
  printf("\033[0m");
}


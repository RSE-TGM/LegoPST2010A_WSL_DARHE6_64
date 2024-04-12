/*
   modulo errvideo.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)errvideo.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include "stdio.h"
#include "ctype.h"

/* per versione in inglese 17.2.94 RL */
#ifdef INGLESE
#define STRerr "* err LIB_VIDEO, type=%d, values %d %d press <cr>    "
#else
#define STRerr "* err LIB_VIDEO, tipo=%d, valori %d %d premere <cr>  "
#endif

errvideo(ier,a,b)
  int ier,a,b;
{
  curxy(24,1);
  printf(STRerr,ier,a,b);
  getc(stdin);
}

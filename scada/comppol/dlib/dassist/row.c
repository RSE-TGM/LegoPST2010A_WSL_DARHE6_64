/*
   modulo row.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)row.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include "stdio.h"
#include "ctype.h"

row(x)
  int x;
{
  static char *u[]={"1","2","3","4","5","6","7","8","9","10","11","12",
                    "13","14","15","16","17","18","19","20","21","22",
                    "23","24","25"};
  int riga;

  if (x<1 || x>25)
      errvideo(1,riga,-1);
  else
      {
       riga=x-1;
       printf("\033[%s;0H",u[riga]);
      }
}


/*
   modulo fasc2bin.c
   tipo 
   release 1.3
   data 7/21/94
   reserved @(#)fasc2bin.c	1.3
*/
#include <stdio.h>

void leggi_testa_asc();
void scrivi_testa_bin_();
int leggi_corpo_asc();
void scrivi_corpo_bin_();

int  main (int argc, char *argv[])
{
   leggi_testa_asc();
   scrivi_testa_bin_();
   while ( leggi_corpo_asc() )
      scrivi_corpo_bin_();
}

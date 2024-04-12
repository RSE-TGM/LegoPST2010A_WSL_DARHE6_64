/*
   modulo fasc2bin.c
   tipo 
   release 1.3
   data 7/21/94
   reserved @(#)fasc2bin.c	1.3
*/
#include <stdio.h>
main(argc,argv)
{
   leggi_testa_asc();
   scrivi_testa_bin_();
   while ( leggi_corpo_asc() )
      scrivi_corpo_bin_();
}

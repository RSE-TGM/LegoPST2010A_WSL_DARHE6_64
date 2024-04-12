/*
   modulo fbin2asc.c
   tipo 
   release 1.3
   data 7/21/94
   reserved @(#)fbin2asc.c	1.3
*/
#include <stdio.h>
main(argc,argv)
{
   leggi_testa_bin();
   scrivi_testa_asc();
   while ( leggi_corpo_bin() )
      scrivi_corpo_asc();
}

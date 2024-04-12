/*
   modulo ConvAscii.c
   tipo 
   release 1.1
   data 5/14/96
   reserved @(#)ConvAscii.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>


main(argc,argv)
int argc;
char ** argv;
{
if(argc<2)
        {
        fprintf(stderr,
     "usa: ConvAscii <file input>\n");
        exit(1);
        }
to_ascii(argv[1]);
}


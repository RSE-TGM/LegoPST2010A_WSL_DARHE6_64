/*
   modulo strupr.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)strupr.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <ctype.h>

void *strupr(char *szBuffer)
{
	for(;*szBuffer;szBuffer++)
		*szBuffer=toupper(*szBuffer);
	return;
}

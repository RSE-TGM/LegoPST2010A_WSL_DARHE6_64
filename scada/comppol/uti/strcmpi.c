/*
   modulo strcmpi.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)strcmpi.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>

int strcmpi(const char *s1, const char *s2)
{
	return(strcasecmp(s1,s2));
}

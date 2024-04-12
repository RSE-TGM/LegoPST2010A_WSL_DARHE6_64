/*
   modulo isintero.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)isintero.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <malloc.h>


/*********************************************************************
*          							                                       *
*			Procedura isintero                                          *
*          							                                       *
* 	La procedura rende 1 se la stringa passata contiene un numero     *
*  intero, -1 altrimenti.				                                 *
*          							                                       *
*********************************************************************/

isintero(valore)

char valore[];

{

short ok=1,i;
float x;

for(i=0;valore[i]!=0x00;i++)
	if(!(valore[i]>=0x30 && valore[i]<=0x39
		 || (i==0 && (valore[0]==0x2b ||
		     valore[0]==0x2d))))
		ok=0;
if(ok==1 && ((x=(float)atof(valore))<32000 && x>-32000))
	return(1);
else
	return(-1);
}



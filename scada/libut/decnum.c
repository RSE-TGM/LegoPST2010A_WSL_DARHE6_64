/**********************************************************************
*
*       C Source:               decnum.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Wed Oct 26 11:57:10 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: decnum.c-3 %  (%full_filespec: decnum.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	la function decnum dato un valore intero o float lo 
	trasforma in stringa ascii in base al formato desiderato

	stringa char *	output stringa decodificata
	n_int	 short  n. cifre totali
	n_flo  short  n. cifre parte decimale (se -1 o -2 il numero e' intero)
					  se n_flo =-2 il numero intero messo in stringa preceduto
					  da 0 se il numero di cifre � inferire a quelle del formato
	v_int	  short valore intero
	v_flo	  float valore floating
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void decnum(stringa,n_int,n_flo,v_int,v_flo)
char *stringa;
short v_int,n_int,n_flo;
float v_flo;
{
char b_intero[30];
char *point;
union {
      float f;
      long  l;
         } un;

if(n_flo==-1 || n_flo== -2) 			/*	e' un intero	*/
{
	sprintf(b_intero, "%d", v_int);
	if(n_flo==-1)
		memset(stringa,' ',n_int);
	else 
		memset(stringa,'0',n_int);
	memcpy(&stringa[n_int-strlen(b_intero)],b_intero,strlen(b_intero));
	return;
}
else
{						/* e' un float			*/
	memset(stringa,' ',n_int);
   un.f=v_flo;
//   DecFl86(stringa,un.f,n_int,n_flo);
        sprintf(stringa, "%f", v_flo);
printf("decnum:stringa=|%s|\n", stringa);
	return;
}
}


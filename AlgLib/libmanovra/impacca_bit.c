/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
   modulo impacca_bit.c
   tipo 
   release 1.3
   data 7/12/95
   reserved @(#)impacca_bit.c	1.3
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)impacca_bit.c	1.3\t7/12/95";
/*
        Fine sezione per SCCS
*/
/*
	La seguente routine inserisce nel buffer un bit a 0 o 1 nella
        posizione indicata da posizione a seconda che il campo valore 
	sia pari o dispari
*/

#include <stdio.h>
#include <string.h>
#include "libmanovra.h"


int impacca_bit(char *buffer, float valore, int posizione)
{
int k;
int byte_n,bit_n;

	/* calcola il byte dove inserire il valore */
	byte_n=posizione/8;
	/* calcola il bit dove inserire il valore */
	bit_n=posizione-byte_n*8;
	/* setta il bit al valore */
	/*print_bit(&buffer[byte_n]);*/
	setta_bit(&buffer[byte_n],float_to_bin(valore),bit_n);
	/*print_bit(&buffer[byte_n]);
	printf("------------------------------\n");*/
}

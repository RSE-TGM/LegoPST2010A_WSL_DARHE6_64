/**********************************************************************
*
*       C Source:               bitset.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 24 15:28:30 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: bitset.c-5 %  (%full_filespec: bitset.c-5:csrc:1 %)";
#endif
#include <stdio.h>

/*-> bitset

     setto bit  in una word
     Parametri	buffer		word di cui si vuole settare il bit
     			indice		n. del bit da 0 a n
     			bit			0 o 1
	Se n> 15 vado allo short successivo     			
*/
#if defined OSF1 || defined LINUX

void bitset(short* buffer, short indice, short bit)
{

	short bitpos;
	short mask=0;
	short *pt;
	
	if(indice>31)
		{
		printf("ERROR:IMPOSSIBLE SET BIT\n");
		}
   	pt=(short*) buffer;
	if(indice>15 && indice<32) 
        	{
		bitpos=31-indice;
		pt=pt+1;
		}
	else
   		bitpos=15-indice;
   	mask=1 ;
   	mask=mask << bitpos ;   
   	if (bit) 
    		*pt=*pt | mask ;
   	else
    		*pt=*pt & ~mask ;
}
void bitset_int(int *buffer ,int indice , short bit)
{
int mask=1;

mask=mask  <<  indice;

if(bit)
	*buffer=*buffer | mask;
else
	*buffer=*buffer & ~mask ;
}

#endif

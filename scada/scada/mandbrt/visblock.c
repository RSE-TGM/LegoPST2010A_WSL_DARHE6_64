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
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/* ->VISBLOCK
 *		visualizza un blocco di 128 byte con i relativi indirizzi.
 *    si posiziona al blocco successivo.
 *    in input: puntatore all'indirizzo iniziale blocco.
 *    			 puntatore al buffer contenenti i byte da visualizzare
 */
#include <stdio.h>
#include <ctype.h>

#include "ansiscr.h"


#define XIN 13
#define XC  62
#define YIN 5
#define XFIN 52		  /* posizione ultimo valore inserito su una riga 	*/

visblock(unsigned int of,unsigned char *buf)
{
short i,j;
unsigned char servbuf[10];
							/* cancella il blocco visualizzato in precedenza */

for(j=0;j<8;j++)
	{
							/* scrive l'indirizzo									*/
//	sprintf(servbuf,"%.4X",seg);
//	servbuf[4]=':';
	sprintf(&servbuf[0],"%.8X",of);
	scrxy(YIN+j+1,2);
	printf("%s",servbuf);
								  /* incrementa l'indirizzo 								*/
	if(of>0xffffffff) of=0;	  /* se l'offset Š FFFFFFFF lo azzero */
	of+=16;
 
	for(i=0;i<16;i++)
		{
		if(i==7)
			sprintf(&servbuf[0],"%.2X-",buf[i+j*16]);
		else
			sprintf(&servbuf[0],"%.2X",buf[i+j*16]);
		scrxy(YIN+j+1,XIN+3*i);
		printf("%s",servbuf);
		}
	for(i=0;i<16;i++)
		{
		scrxy(YIN+j+1,XC+i);
		if(buf[i+j*16]<0x20 || buf[i+j*16]>=0x80) printf(".");
		else	printf("%1c",buf[i+j*16]);
		}

	}
}


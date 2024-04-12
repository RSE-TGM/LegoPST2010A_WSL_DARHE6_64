/**********************************************************************
*
*       C Source:               DecFl86.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Wed Oct 26 11:42:25 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: DecFl86.c-3 %  (%full_filespec: DecFl86.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	-> DecFl86()

	Converte un valore float in una stringa in formato decimale.
	
	Parametri:
	pcBuffer	buffer di caratteri in cui scrivere;
	fValue		valore da convertire;
	nMax		lunghezza massima della stringa;
	nDec		numero di cifre decimali.

	Valore restituito:
	il puntatore alla stringa.

*/

#include <stdio.h>

char *DecFl86(char *pcBuffer,float fValue,short nMax, short nDec)
{
	short nInt=nMax-nDec-1;
	
	// Spazio per il segno -
	if(fValue<0)
		nInt--;

printf("DecFl86:%*.*f",nInt,nDec,fValue);
	sprintf(pcBuffer,"%*.*f",nInt,nDec,fValue);
	
	if(nInt<=0 || nDec<0)
		return NULL;
	else
		return pcBuffer;
}


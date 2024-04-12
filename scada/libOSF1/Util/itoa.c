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
/*
	-> itoa()

	Converte un valore intero in una stringa in formato decimale.
	Se e' specificato un valore per la base numerica diverso da 
	viene segnalato con una printf() ed il numero viene interpre-
	tato in formato decimale.
	
	Parametri:
	iValue		valore da convertire;
	pcBuffer	buffer di caratteri in cui scrivere;
	iRadix		la base numerica in cui e' espresso il
			numero;

	Valore restituito:
	il puntatore alla stringa se tutto OK, altrimenti NULL.

*/

#include <stdio.h>

char *itoa(int iValue,char *pcBuffer,int iRadix)
{
	sprintf(pcBuffer,"%d",iValue);
	
	if(iRadix==10)
		return pcBuffer;
	else
		return NULL;
}

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
/* ->DECIND
 *		decodifica l'indirizzo scritto nella forma NNNNNNNN in un int
 *		input: stringa contenente l'indirizzo scritto in esadecimale 
 *				 puntatore a short alla variabile che conterr… 
 *				 il valore numerico dell'offset dell'indirizzo.
 *		ritorno: 1 se si Š trovato un carattere non accettabile.
 */

decind(char *com,int* of)
{
short i;
char csegm[5];
char coff[5];
i=0;

while (com[i]!=0)
	{
	coff[i]=com[i];
	i++; 
	}
coff[i]=0;
if(i>8) return(1);
if(sscanf(coff,"%x",of)!=1) return(1);
return(0);
}



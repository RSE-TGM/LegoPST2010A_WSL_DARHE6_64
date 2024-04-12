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
	-> FileLen()

	Calcola la dimensione in byte di un file a partire
	dal descrittore

	ritorno con errore 0
	

*/

#include <osf1.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int filelength(int fp)
{
struct stat statistica;
off_t size_ret = 0;

if(fp<0)
	return((int)size_ret);


if(fstat(fp,&statistica)==0)
	size_ret = statistica.st_size;

return((int)size_ret);
}


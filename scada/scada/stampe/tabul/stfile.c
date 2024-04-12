/**********************************************************************
*
*       C Source:               stfile.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Fri Dec 13 16:18:50 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: stfile.c-4 %  (%full_filespec: stfile.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	stfile.c

	Il modulo dato il nome di una file ascii provvede alla sua
	stampa.
	Per la lettura del file viene utilizzato il buffer fornito
	in input insieme alla sua dimensione

	Parametri

	char *	indirizzo nome del file
	char *	indirizzo buffer
	short		dimensione buffer
   short    stampante

	Ritorno

	nessuno

	1 Luglio 1993	Fc

   20 Giugno 1995
      Inserito un parametro per la scelta della stampante

*/
#include <osf1.h>
#include <stdio.h>
#include <fcntl.h>
#if defined OSF1 || defined LINUX
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>
#endif

#include "messcada.inc"
#include "print.inc"
#include "pscserr.inc"

#define l_stin		100					// buffer massimo da inviare in stampa

stfile(char *nfile, char *bfile, short dim, short prn)
{
   char *bfileo;
	short canale;
	short numbyte;
	long	offset;
	HEA_STA *hea;

   bfileo=bfile;
	if((canale=open(nfile,O_RDONLY|O_BINARY))==-1)
	{
	   pscserr(ERR_IO,TASK_STAMPE,ROU_STFILE,canale,SYS_CONT);
		return(0);
	}

	offset=0;
/*
	ciclo lettura file
*/
	while(numbyte=rbyte(canale,bfile+sizeof(HEA_STA),offset,dim-sizeof(HEA_STA)))
		{
			offset+=numbyte;			
/*
	ciclo esame stringhe ed inserimento header con lunghezza
*/
			while(numbyte > 0)
				{
					hea=(HEA_STA*) bfile;
					hea->lung=min(numbyte,l_stin)+sizeof(HEA_STA);
               hea->szvir=prn;
					invia(tpr_tabulato,bfile);
					bfile=bfile+hea->lung-sizeof(HEA_STA);
					numbyte-=l_stin;
				}
			bfile=bfileo;
		}
	close(canale);
 	invia(tpr_reset,(char*) 0);
	return(0);
}

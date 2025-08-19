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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fio.h"

#include "gpunt.inc"
#include "comunic.inc"
#include "g0strdb.inc"
#include "mesprocv.inc"

#include	"mesqueue.h"

/* Function prototypes */
extern int rbyte(int, char *, long, int);
extern void wbyte(int, char *, long, int);

void hostfio(bric)
	BRICFIO *bric;
	{
	FILE *fp;
	QUEUE_PACKET  spack;
	char fname[FILENAME_MAX+1];

	switch(bric->indice)
		{
		case READDATA:
			bric->indice=RREADDATA;
			fp=fopen(_fnamvar(bric->idfile,fname),"rb+");
		   if(!fp)
				{
				memset(bric->b,FILL_PATT,LRECFIO);		// clear buffer
//				printf(" ERR open FIO ");
				}
			else
				{
//				printf(" read FIO ");
				rbyte(fileno(fp),bric->b,(long)bric->recno * (long)LRECFIO,LRECFIO);
				}
			fclose(fp);
			break;
		case WRITEDATA:
			bric->indice=RWRITEDATA;
			fp=fopen(_fnamvar(bric->idfile,fname),"rb+");
			if(!fp)
				fp=fopen(_fnamvar(bric->idfile,fname),"wb+");

			if(!fp)
				{
//				printf("\n Errore apertura file POL");
				}
			else
				{
//				printf("\n write FIO");
				wbyte(fileno(fp),bric->b,(long)bric->recno * (long)LRECFIO,LRECFIO);
				fclose(fp);
				}
			break;
		case DELETEFILE:
			bric->indice=RDELETEFILE;
			remove(_fnamvar(bric->idfile,fname));		
			break;
		default:
			break;
		}
	spack.que = c_mmio;
	spack.flg = MSG_WAIT;
	spack.wto = 0;
	spack.lmsg=sizeof(BRICFIO);
	spack.amsg=(char *) bric;
	enqueue(&spack);
	}

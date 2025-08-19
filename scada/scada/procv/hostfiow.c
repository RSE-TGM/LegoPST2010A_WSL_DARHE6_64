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
	hostfiow
		Il modulo gestisce i messaggio assciati alle istruzioni FREAD,
		FDELETE e FWRITE del linguaggio POL di animazione delle pagine

		Parametri
			BRICFIO*	 puntatore al messaggio

		Ritorno
			nessuno

	20 Novembre 1994
*/
#include <osf1.h>
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
extern int DosRemove(char *);

/*
	la struttura del messaggio FREAD per MMI Window prevede l'elenco
	dei puntatori nel data base locale in cui inserire i dati successivamente
	letti da file

	Il blocco dati viene letto a partire dalla posizione successiva ai
	puntatori al data base locale

*/
typedef struct {			 					// definizione struttura per FREAD
          short nodo;
	       char  indice ;
	       char  classe ;
	       char  zona  ;
	       char  video;
	       char  pag[l_pagina];
	       short   idfile;
	       short   recno;
			 short   npoint;
			 short   pointDBL[1];
	        } BRICFIOREADW;


void hostfiow(bric)
	BRICFIO *bric;
	{
	FILE *fp;
	QUEUE_PACKET  spack;
	char fname[FILENAME_MAX+1];
  	BRICFIOREADW *pRead;
	short *pBuff;

	switch(bric->indice)					// indice messaggio
		{
		case FReadW:
			pRead=(BRICFIOREADW*) bric;
			pRead->indice=RREADDATA;
			pBuff=(&pRead->pointDBL[0])+pRead->npoint;
			fp=fopen(_fnamvar(pRead->idfile,fname),"rb+");
		   if(!fp)
				memset(pBuff,FILL_PATT,LRECFIO);		// clear buffer
			else
			{
				memset(pBuff,FILL_PATT,LRECFIO);		// clear buffer
				rbyte(fileno(fp),(char *)pBuff,(long)bric->recno * (long)LRECFIO,LRECFIO);
				fclose(fp);
			}
			spack.lmsg=sizeof(BRICFIOREADW)+(pRead->npoint-1)*2+LRECFIO;
			break;

		case FWriteW:
			bric->indice=RWRITEDATA;
			fp=fopen(_fnamvar(bric->idfile,fname),"rb+");
			if(!fp)
				fp=fopen(_fnamvar(bric->idfile,fname),"wb+");
			if(fp)
				{
				wbyte(fileno(fp),bric->b,(long)bric->recno * (long)LRECFIO,LRECFIO);
				fclose(fp);
				}
			spack.lmsg=LBRIC;
			break;

		case FDeleteW:
			bric->indice=RDELETEFILE;
			remove(_fnamvar(bric->idfile,fname));		
			spack.lmsg=LBRIC;
			break;

		default:
			return;
		}
	spack.que = c_mmio;
	spack.flg = MSG_WAIT;
	spack.wto = 0;
	spack.amsg=(char *) bric;
	enqueue(&spack);
	}

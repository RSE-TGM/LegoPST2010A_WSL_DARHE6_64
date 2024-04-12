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
   virttlbg.c

	la funzione virtlbg verifica se sono stati esauriti i files
	destinati come libro giornale
	questo avviene quando il file successivo a quello in uso non
	e' vuoto oppure non e' ancora stato copiato (bit FZ)

   Parametri:

   short indice della stampante virtuale da verificare

   Ritorno
      nessuno


	mbox_lbg	e' la mail box che impedisce che il task stampe
					e il task tabul agiscano contemporaneamente sulla
					diagnostica
*/

#include <osf1.h>
#include <stdio.h>

#include "print.inc"
#include "virtinv.h"
#include "dconf.inc"
#include "g2comdb.inc"
#include "diagnoan.inc"
#include "mesqueue.h"
#include "comunic.inc"
#include "mesprocv.inc"
#include "diagnodi.inc"


virttlbg(short nvirt)
{
short pros_file;
S_MDIA mess;
QUEUE_PACKET pack;
short nfile, dfile;

nfile=virtprn[nvirt].IFileU;
dfile=virtprn[nvirt].DFileP;
/*
	verifico che il file successivo sia gia' stato copiato su dischetto
	se non lo e' emetto l'allarme in caso contrario il rientro
*/
if(nfile>=max_n_allfile) pros_file=0;
else pros_file=nfile;
if(dbadv[dfile+pros_file]!=0.0 &&
	!bitvalue(&dbadf[dfile+pros_file],g2an_fz))	mess.a[0].condiz=1;
else mess.a[0].condiz=0;
mess.indice=mdia;
mess.a[0].allarme=pVirtFull+nvirt;
pack.wto=0;
pack.flg=MSG_WAIT;
pack.que=c_mmii;
pack.amsg=(char*)&mess;
pack.lmsg=h_dia+sizeof(S_ALDIA);
enqueue(&pack);
}





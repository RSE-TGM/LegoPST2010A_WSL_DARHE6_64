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
	la funzione testlbg verifica se sono stati esauriti i files
	destinati come libro giornale
	questo avviene quando il file successivo a quello in uso non
	e' vuoto oppure non e' ancora stato copiato (bit FZ)

	n_file e' il numero del file attualmente in uso

	mbox_lbg	e' la mail box che impedisce che il task stampe
					e il task tabul agiscano contemporaneamente sulla
					diagnostica
*/

#include <stdio.h>

#include "print.inc"
#include "dconf.inc"
#include "g2comdb.inc"
#include "diagnoan.inc"
#include "mesqueue.h"
#include "fileop.inc"
#include "mesprocv.inc"
#include "comunic.inc"
#include "diagnodi.inc"

extern int mbox_lbg;

testlbg(n_file)
short n_file;
{
short pros_file;
S_MDIA mess;
QUEUE_PACKET pack;
int ier;

rew(mbox_lbg,0,&ier);
/*
	verifico che il file successivo sia gia' stato copiato su dischetto
	se non lo e' emetto l'allarme in caso contrario il rientro
*/
if(n_file>=max_n_allfile) pros_file=0;
else pros_file=n_file;
if(dbadv[db_falco1+pros_file]!=0.0 &&
	!bitvalue(&dbadf[db_falco1+pros_file],g2an_fz))	mess.a[0].condiz=1;
else mess.a[0].condiz=0;
mess.indice=mdia;
mess.a[0].allarme=lbgfull;
pack.wto=0;
pack.flg=MSG_WAIT;
pack.que=c_mmii;
pack.amsg=(char*)&mess;
pack.lmsg=h_dia+sizeof(S_ALDIA);
enqueue(&pack);
tra(mbox_lbg,1);
}





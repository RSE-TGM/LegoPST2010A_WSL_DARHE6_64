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
	Calcau.c

	Gestione del messaggio maudi. Dato il puntatore in data base del
	digitale calcolato procede all'esame dei contribuenti per settare
   il bit AU.

	Il bit AU viene posto a 1 se almeno uno dei contribuenti ha settato
	a 1 o il bit AU o il bit RI.

	Se il bit AU cambia valore viene accodato il messaggio maudi per il 
   ricalcolo delle eventuali calcolate a cui contribuisce.

	Parametri

	point			short		puntatore in data base da esaminare


	Ritorno 

	nessuno

	12 Ottobre 1992	Fc

*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "mesqueue.h"
#include "comunic.inc"
#include "messcada.inc"

/* Function prototypes */
extern void bitset(short *, short, short);
extern int bitvalue(short *, short);

void calcau(point)
short point;
{
short i;
S_DCALC *calc;
short *flag;
short val_au;
QUEUE_PACKET pack;
S_TRATG mess;

calc=&dbdsde[point];

for(i=0;i<ds_cont;i++)
{
	if(calc->ext[i]==-1) break;         // fine contribuenti
	switch(calc->ext[i])
	{
		case g1tipda:
			flag=&dbda[calc->punt[i]];
		break;
		case g1tipds:
			flag=&dbds[calc->punt[i]];
		break;
		case g1tipdc:
			flag=&dbdc[calc->punt[i]];
		break;
		case g1tipdd:
			flag=&dbdd[calc->punt[i]];
		break;
	}
	val_au=bitvalue(flag,g2di_ri) | bitvalue(flag,g2di_au);
	if(val_au) break;
}
/*
	verifico se e' variato lo stato del bit AU
*/
if(val_au != bitvalue(&dbds[point],g2di_au))
{
	bitset(&dbds[point],g2di_au,val_au);
   pack.wto=-1;         // autoaccodamento
   pack.flg=MSG_NOWAIT;
   pack.que=c_digor;    
   pack.amsg=(char*)&mess;
   pack.lmsg=sizeof(S_TRATG);
   mess.ext=g1tipds;  mess.indice=point;
   mess.mess=maudi; 
   enqueue(&pack);        
}
}	
	

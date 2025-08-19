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
	routine per la stampa degli elenchi
	in ingresso viene fornito l'indice del flag
	da esaminare e i tipi di punti da testare

   11 Gennaio 1993
   Gestione trattamento - severita'
   Inserimento scelta zona
*/

#include <stdio.h>
#include <string.h>

#include "dconf.inc"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "mesqueue.h"
#include "video.inc"
#include "allar.inc"

/* Function prototypes */
extern void bitset(short *, short, short);
extern int bitvalue(short *, short);

extern DB_HEADER h_db;

void gesele(tipo_p, n_flag,zona)
short n_flag, tipo_p,zona;
{
QUEUE_PACKET pack;
short mask;
short *flag;		/* puntatore short alle tabelle in DBS             */
char  *pzona;		/* puntatore char alle tabelle in DBS             */
float *value;		/* puntatore al valore della misura analogica		*/
short dim;			/* n. dei punti nello specifico DBS                */
S_STELEN mess;
short i, trat;


mask=0;				/* maschera per isolare il bit da testare	*/
pack.que = c_stamp;
pack.flg = MSG_WAIT;				/* messaggio per processo stampe */
pack.wto = 0;						/* wait infinita						*/
pack.amsg = (char *) &mess;
pack.lmsg=sizeof(S_STELEN);

/*
	se alla fine del ciclo punt e' ancora a meno -1 invio
	un messaggio fittizio per forzare l'intestazione
*/
mess.mess=minel;					
mess.flag=n_flag;
mess.ext=tipo_p;
mess.punt=-1;
/*
	in base al tipo di punto mi posiziono con il puntatore sul data base
	dei flag, individuo la dimensione del dbs e setto la maschera dei
	flag
	il primo pacchetto si distingue dai successivi perche' nel campo flag
	c'e' il tipo di flag selezionato per la scrittura dell'intestazione
*/
switch (tipo_p)
{
case	g1tipaa:			  	/* analogici		*/
	flag=&dbaaf[0]; value=&dbaav[0];	dim=h_db.dimaa;   pzona=&dbaau[0];
   goto FLAG_ANA;
case	g1tipas:
	flag=&dbasf[0]; value=&dbasv[0];	dim=h_db.dimas;   pzona=&dbasu[0];
	goto FLAG_ANA;
case	g1tipac:
	flag=&dbacf[0]; value=&dbacv[0];	dim=h_db.dimac;   pzona=&dbacu[0];
	goto FLAG_ANA;
case	g1tipad:
	flag=&dbadf[0]; value=&dbadv[0];	dim=h_db.dimad;   pzona=NULL;
		
FLAG_ANA :

	switch(n_flag)
	{
	case ELE_FS: 	  
		bitset(&mask,g2an_fs,1);
		break;
	case ELE_FZ: 	  
		bitset(&mask,g2an_fz,1);
		break;
	case ELE_HC_HS_LC_LS:
		bitset(&mask,g2an_hc,1);
		bitset(&mask,g2an_hs,1);
		bitset(&mask,g2an_lc,1);
		bitset(&mask,g2an_ls,1);
		break;
	case ELE_AL: 	  
		bitset(&mask,g2an_al,1);
		break;
	case ELE_FA: 	  
		bitset(&mask,g2an_fa,1);
		break;
	default:
		return;
	}
	break;
case g1tipda:	 					/* digitale		*/
	flag=&dbda[0]; dim=h_db.dimda;
   goto FLAG_DIG;
case g1tipds:
	flag=&dbds[0]; dim=h_db.dimds;
   goto FLAG_DIG;
case g1tipdc:
	flag=&dbdc[0]; dim=h_db.dimdc;   pzona=&dbdcu[0];
   goto FLAG_DIG;
case g1tipdd:
	flag=&dbdd[0]; dim=h_db.dimdd;   pzona=NULL;

FLAG_DIG:

	switch(n_flag)
	{
	case ELE_FS: 	  
		bitset(&mask,g2di_fs,1);
		break;
	case ELE_FZ: 	  
		bitset(&mask,g2di_fz,1);
		break;
	case ELE_SL:
		bitset(&mask,g2di_sl,1);
		break;
	case ELE_FA:
		bitset(&mask,g2di_fa,1);
		break;
	default: return;
	}
	break;
case	g1tipor:		  					/* organi			*/
	flag=&dbosc[0]; dim=h_db.dimor;   pzona=&dbou[0];
	switch(n_flag)
	{
	case ELE_FS: 	  
		bitset(&mask,g2or_fs,1);
		break;
	case ELE_FZ: 	  
		bitset(&mask,g2or_fz,1);
		break;
	case ELE_FA:
		bitset(&mask,g2di_fa,1);
		break;
	default: return;
	}
	break;
default: return;
}

if(pzona == NULL)	zona =-1;

for(i=0;i<dim;i++,flag++,pzona++)
{
		if(mask & (*flag) && (zona == -1 || zona == *pzona))		 	/* il punto ha il bit settato		*/
		{
/*
	preparo pacchetto per stampa elenco
	nel caso di forzamento nel pacchetto viene inserito il valore
	come nel caso superamento delle soglie analogiche 
*/
			switch (n_flag)
			{
			 case ELE_SL:
				trat=(*flag) & M_TRATD;
				if(trat < 1 || trat == 7) continue;
				mess.value[0]=bitvalue(flag,g2di_sl);
				break;
			default:
				switch (tipo_p)
				{
				case g1tipaa: case g1tipas:  case g1tipac:  case g1tipad:
					memcpy(mess.value,(char*)(value+i),4);
					break;
				case g1tipda: case g1tipds:  case g1tipdc:  case g1tipdd:
					mess.value[0]=bitvalue(flag,g2di_sl);
					break;
				case g1tipor:
					mess.value[0]=(*flag) & 0x00FF;
					break;
				}
				break;
			}
			mess.punt=i;
			enqueue(&pack);
		}
}
if(mess.punt==-1) enqueue(&pack);
/*
	invio messaggio di fine tabulato per reset tabelle
*/
mess.flag=ELE_FINE;
enqueue(&pack);
return ;
}

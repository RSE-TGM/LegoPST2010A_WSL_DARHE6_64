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
	la funzione gestri setta o resetta il bit ri del punto
	indicato

   26 Giugno 1995
      Inserimento gestione flag AU=or dei flag RI degli eventuali
      digitali contribuenti
*/

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "mesqueue.h"

gestri(ext,punt,val)
short ext,punt,val;
{
short *tab;
short indbit;

S_TRATG mess;           // variabili per gestione bit AU
QUEUE_PACKET pack;
short flag;
short *dbtr;

switch (ext)
{
	case g1tipaa:
		indbit=g2an_ri;
		tab=&dbaaf[punt];
		break;
	case g1tipas:
		indbit=g2an_ri;
		tab=&dbasf[punt];
		break;
	case g1tipac:
		indbit=g2an_ri;
		tab=&dbacf[punt];
		break;
	case g1tipad:
		indbit=g2an_ri;
		tab=&dbadf[punt];
		break;
	case g1tipda:
		indbit=g2di_ri;
		tab=&dbda[punt];
      dbtr=&dbdatr[punt];
		break;
	case g1tipds:
		indbit=g2di_ri;
		tab=&dbds[punt];
      dbtr=&dbdstr[punt];
		break;
	case g1tipdc:
		indbit=g2di_ri;
		tab=&dbdc[punt];
      dbtr=&dbdctr[punt];
		break;
	case g1tipdd:
		indbit=g2di_ri;
		tab=&dbdd[punt];
      dbtr=&dbddtr[punt];
		break;
	case g1tipor:
		indbit=g2or_ri;
		tab=&dbosc[punt];
		break;
   default:
      return(0);
}

flag=*tab;              // salvo valore precedente

bitset(tab,indbit,val);
/*
 se il punto e' digitale, si imposta la gestione del bit di flag AU
 delle calcolate cui eventualmente contribuisce inviando il messaggio
 maudi  al task asinct. Il messaggio viene inviato solo se e' stata
 rilevata una variazione nei bit AU e RI e se il digitale contribuisce
 a calcoli
*/
if (ext==g1tipda || ext==g1tipds || ext==g1tipdc || ext==g1tipdd)
{
   if(!bitvalue(dbtr,g2di_ic)) return(0);    // non contribuisce a calcolo
   if(val != (bitvalue(&flag,g2di_au) | bitvalue(&flag,g2di_ri)))
   {
      pack.wto=10;         // il time out non e' infinito per evitare
      pack.flg=MSG_WAIT;   // dead lock con asinct
      pack.que=c_digor;    
      pack.amsg=(char*)&mess;
      pack.lmsg=sizeof(S_TRATG);
      mess.ext=ext;  mess.indice=punt;
      mess.mess=maudi;  mess.stato=val;
      enqueue(&pack);        
   }
}
return(0);
}

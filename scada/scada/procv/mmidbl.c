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
        mmidbl.c
        La funzione gestisce i messaggi di lettura e scrittura nel data
        base globale di posto operatore memorizzando i dati nei buffer
        relativi al posto operatore indicato.
        Il numero massimo di posti operatore e' uguale al numero massimo
        di video (max_video)
        Sia che il messaggio sia di Read che di Write e' previsto un mes-
        saggio di risposta con lo stesso indice e la stessa struttura di
        quello ricevuto
        
        Parametri

        S_MMIDBL*       struttura del messaggio

        Ritorno

        Nessuno

         18 Aprile 1995
*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include "messcada.inc"
#include "mesqueue.h"
#include "dconf.inc"

#include "mmidbl.h"
#include <string.h>
//
// definizione aree per posto operatore
//
struct s_db_postop {
      char an[chAN*nGbcAN];
      char in[chIN*nGbcIN];
      char di[chDI*nGbcDI];
      char or[chOR*nGbcOR];
      char st[chST*nGbcST];
      char pt[chPT*nGbcPT];
                  } dbpostop[max_video];
        
void mmidbl(S_MMIDBL* mess)
{
   QUEUE_PACKET pack;

   short dim;
   char *pbuf;

   switch (mess->idbl)
   {
   case iGbcAN:
      dim=chAN;   pbuf=(char *)dbpostop[mess->npostop-1].an;   break;
   case iGbcIN:
      dim=chIN;   pbuf=(char *)dbpostop[mess->npostop-1].in;   break;
   case iGbcDI:
      dim=chDI;   pbuf=(char *)dbpostop[mess->npostop-1].di;   break;
   case iGbcOR:
      dim=chOR;   pbuf=(char *)dbpostop[mess->npostop-1].or;   break;
   case iGbcST:
      dim=chST;   pbuf=(char *)dbpostop[mess->npostop-1].st;   break;
   case iGbcPT:
      dim=chPT;   pbuf=(char *)dbpostop[mess->npostop-1].pt;   break;
   default:
      return;
   }
   pbuf=pbuf+mess->iele*dim;
   if(mess->indice==mwdbl)
      memcpy(pbuf,mess->dati,dim);
   else
      memcpy(mess->dati,pbuf,dim);
//
// invio risposta
//
   pack.que= c_mmio;
   pack.flg = MSG_WAIT;
   pack.wto = 0;
   pack.lmsg=sizeof(S_MMIDBL);
   pack.amsg=(char *) mess;
   enqueue(&pack);
}



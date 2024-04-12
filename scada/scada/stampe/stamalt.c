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
/*-> stamalt

   Stamalt prepara il messaggio S_STALT per allarmi analogici e
   digitali acquisiti da linee telefoniche

   Parametri

   mess     *S_MALLAT      messaggio allarme

   Ritorno nessuno

   3 Dicembre 1992

*/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "print.inc"
#include "mesqueue.h"
#include "diagnoan.inc"

float vsoglia(short punt,char ext,char soglia);

stamalt(S_MALLAT *al)
{
S_STALLT  stalt;
QUEUE_PACKET  packs;

packs.que = c_stamp;
packs.flg = MSG_NOWAIT;		
packs.wto = -1;				
packs.amsg = (char *) &stalt;
packs.lmsg=sizeof(S_STALLT);

/*
        inserisco i campi che non subiscono variazioni
*/
stalt.m.mess=mstal;
stalt.m.ora=dbadv[db_ora] ;
stalt.m.sec=dbadv[db_secondi];
stalt.m.min=dbadv[db_minuti];
stalt.m.gior=dbadv[db_giorno];
stalt.m.mese=dbadv[db_mese];

if(dbadv[db_anno]>=2000) stalt.m.anno=dbadv[db_anno]-2000;
else 						    stalt.m.anno=dbadv[db_anno]-1900;

stalt.m.al.ertr=al->m.ertr;               /* emissione trattamento        */
stalt.m.al.ext=al->m.ext ;                /* estensione                   */
stalt.m.al.punt=al->m.punt ;              /* puntatore                    */
stalt.m.al.sprec=al->m.sprec;             /* stato precedente             */
stalt.m.al.satt =al->m.satt ;             /* stato attuale                */
stalt.m.al.vrif.c[0]=al->m.sogl1 ;        /* riferimento                  */
stalt.t=al->t;                           /* tempo                        */

switch(al->m.ext)
{
case g1tipda:
case g1tipds:
case g1tipor:
        stalt.m.al.vatt.c[0]=al->m.sogl2 ;
        break;
case g1tipaa:                   /* analogici acquisiti  */
        stalt.m.al.vatt.f=al->v;
        break ;
default :
        printf("\nSTMLT punto non previsto %d ",al->m.ext) ;
        return(0) ;
}
if(al->m.sogl1!=255)               /* se la soglia non e' -1 */
{                               /* e si tratta di analog. */
        switch(al->m.ext)          /* ricavo il valore float */
        {
        case g1tipaa:
             stalt.m.al.vrif.f= vsoglia(al->m.punt,al->m.ext,al->m.sogl1) ;
        }
}
if(!full_stampe) if(enqueue(&packs)) full_stampe=1;				//	coda piena
return(0) ;
}


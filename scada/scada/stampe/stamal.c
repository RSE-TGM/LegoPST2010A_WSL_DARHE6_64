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
/*-> stamal

        la function stamal prepara la struttura  S_STAL
        per l'invio al processo stampe degli allarmi
        da stampare sul libro giornale

        al      struttura che contiene le specifiche dell'
                allarme viene trasformata nella struttura
                S_STAL
        ritorna 
        0       punto non da accodare
        1       punto da accodare

*/
#include <stdio.h>
#include <string.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "print.inc"
#include "mesqueue.h"

float vsoglia(short punt,char ext,char soglia);

void stamal(S_MALLA *al)
{

QUEUE_PACKET  packs;

packs.que = c_stamp;
packs.flg = MSG_NOWAIT;				/* messaggio per processo stampe */
packs.wto = -1;						/* nowait altrimenti si riempiono le code*/
packs.amsg = (char *)  &us.stal;

/*
        inserisco i campi che non subiscono variazioni
*/
us.stal.al.ertr=al->ertr;               /* emissione trattamento        */
us.stal.al.ext=al->ext ;                /* estensione                   */
us.stal.al.punt=al->punt ;              /* puntatore                    */
us.stal.al.sprec=al->sprec;             /* stato precedente             */
us.stal.al.satt =al->satt ;             /* stato attuale                */
us.stal.al.vrif.c[0]=al->sogl1 ;        /* riferimento                  */

/*
        nel caso che il punto sia analogico devo inserire
        le soglie di allarme ed il valore di riferimento
        per digitali ed organi copio le soglie
*/

packs.lmsg=sizeof(S_STALL);

switch(al->ext)
{
case g1tipdd:           /* digitali ed organi   */
case g1tipda:
case g1tipdc:
case g1tipds:
case g1tipdo:
case g1tipor:
        us.stal.al.vatt.c[0]=al->sogl2 ;
        break;
case g1tipaa:                   /* analogici acquisiti  */
        us.stal.al.vatt.f=dbaav[al->punt] ;
        break ;
case g1tipas:                   /* analogici calc. standard */
        us.stal.al.vatt.f=dbasv[al->punt] ;
        break ;
case g1tipac:                   /* analogici calc. non stand. */
        us.stal.al.vatt.f=dbacv[al->punt] ;
        break ;
case g1tipad:                   /* analogici di diagnostica    */
        us.stal.al.vatt.f=dbadv[al->punt] ;
        break ;
case g1tipst:
		  packs.lmsg=sizeof(S_STALS);
		  memcpy(us.stal.al.vrif.c,&dbstv[al->punt*g0lunst],g0lunst);
		  break;
default :
        printf("\nSTML punto non previsto %d ",al->ext) ;
        return ;
}
if(al->sogl1!=255)               /* se la soglia non e' -1 */
{                               /* e si tratta di analog. */
        switch(al->ext)          /* ricavo il valore float */
        {
        case g1tipaa:
        case g1tipas:
        case g1tipac:
        case g1tipad:
             us.stal.al.vrif.f= vsoglia(al->punt,al->ext,al->sogl1) ;
        }
}
if(!full_stampe) if(enqueue(&packs)) full_stampe=1;				//	coda piena
return ;
}


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
        la function vsoglia fornisce il valore
        float del limite di allarme

        punt short puntatore della misura
        ext  char  estensione della misura
        soglia char n. della soglia limite di allarme
                0       alta sicurezza
                1       bassa sicurezza
                2       alta conduzione
                3       bassa conduzione
*/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include "messcada.inc"
#include	"mesqueue.h"
#include "diagnodi.inc"
#include "tipal.inc"

float vsoglia(punt,ext,soglia)
short punt;
char ext,soglia;
{

struct allarmi *all ;   /* puntatore allarme */
union valin  v    ;     /* valore allarme    */
/*
        seleziono il puntatore alla soglia
        di allarme
*/
switch (ext)
{
case g1tipaa :
        all= & dbaaal[punt] ;
        break;
case g1tipas :
        all= & dbasal[punt] ;
        break;
case g1tipac :
        all= & dbacal[punt] ;
        break;
case g1tipad :
        all= & dbadal[punt] ;
        break;
default:
		  return(0);
}
/*
        in base alla soglia individuo
        il valore floating dell`allarme
*/
switch (soglia)
{
case g1tiphs :
        v.fval=all->alto_sic.fval;
        break;
case g1tipls :
        v.fval=all->bass_sic.fval;
        break;
case g1tiphc :
        v.fval=all->alto_con.fval;
        break;
case g1tiplc :
        v.fval=all->bass_con.fval;
        break;
default :
        return(0);
}
/*
        se la soglia e` una misura ne ricerco il valore
*/
if(v.cval[0] == -1 )
{       switch(v.cval[1])
        {
        case g1tipaa: v.fval=dbaav[v.sval[1]]; break ;
        case g1tipas: v.fval=dbasv[v.sval[1]]; break ;
        case g1tipac: v.fval=dbacv[v.sval[1]]; break ;
        case g1tipad: v.fval=dbadv[v.sval[1]]; break ;
        }
}
if(v.cval[0] == -2 )	memset(v.cval,0xFF,4);			// soglia non esistente
return(v.fval) ;
}


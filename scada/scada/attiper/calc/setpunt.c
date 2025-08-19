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
/*******************************************************************
	Modulo:  SETPUNT.C 

        Setta i puntatori all' inizio della catena
        di link per classe di scansione
  
        Alla routine viene passato "indice" che rappresenta il
        punto in data base dove e' collocato il punto di inizio
        per classe di scansione.

	Creazione :  Antecedente 01.05.92
  
*******************************************************************/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "calas.inc"

void setpunt(indice)
short indice;
{
 switch(desc->a.periodo & 0x7F)
  {
        case 1:
                tab_cal[0].inizio=desc;
                tab_cal[0].corrente=desc;
                tab_cal[0].ncalt++;
                tab_cal[0].indice=indice;
					 tab_cal[0].addr_corrente=indice;
                break;
        case 5:
                tab_cal[1].inizio=desc;
                tab_cal[1].corrente=desc;
                tab_cal[1].ncalt++;
                tab_cal[1].indice=indice;
					 tab_cal[1].addr_corrente=indice;
                break;
        case 15:
                tab_cal[2].inizio=desc;
                tab_cal[2].corrente=desc;
                tab_cal[2].ncalt++;
                tab_cal[2].indice=indice;
					 tab_cal[2].addr_corrente=indice;
                break;
        case 30:
                tab_cal[3].inizio=desc;
                tab_cal[3].corrente=desc;
                tab_cal[3].ncalt++;
                tab_cal[3].indice=indice;
					 tab_cal[3].addr_corrente=indice;
                break;
        case 60:
                tab_cal[4].inizio=desc;
                tab_cal[4].corrente=desc;
                tab_cal[4].ncalt++;
                tab_cal[4].indice=indice;
					 tab_cal[4].addr_corrente=indice;
                break;
   }
}


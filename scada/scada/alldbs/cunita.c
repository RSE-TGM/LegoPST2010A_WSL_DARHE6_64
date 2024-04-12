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
	la function cunita fornisce il valore della zona di impianto dato
	il puntatore in data base ed il tipo di punto
*/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "messcada.inc"
#include "allar.inc"
#include "tipal.inc"
#include "mesqueue.h"

cunita(point,ext)
short point;
char ext;
{

switch(ext)
{
case g1tipaa:
	return(dbaau[point]);																									  
case g1tipas:
	return(dbasu[point]);																									  
case g1tipac:
	return(dbacu[point]);																									  
case g1tipad:
	return(dbadu[point]);																									  
case g1tipao:
	return(dbaou[point]);																									  
case g1tipda:
	return(dbdau[point]);																									  
case g1tipds:
	return(dbdsu[point]);																									  
case g1tipdc:
	return(dbdcu[point]);																									  
case g1tipdd:
	return(dbddu[point]);																									  
case g1tipdo:
	return(dbdou[point]);																									  
case g1tipor:
	return(dbou[point]);																									  
case g1tipst:
	return(dbstu[point]);																									  
}
}

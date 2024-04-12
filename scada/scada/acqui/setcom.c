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
#include <stdio.h>
/*
	la function setcom gestisce il messaggio mdcom proveniente da
	DAC :
		- attiva il time out dell' eventuale organo associato
		- invia la stampa del messaggio di invio comando
*/
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "mesest.inc"
#include "messcada.inc"
#include "tipal.inc"

setcom(com)

S_MDCOM *com;
{
S_MALLA mess;
QUEUE_PACKET pack;
short i;

pack.que=c_visall;
pack.amsg=(char*)&mess;
pack.lmsg=sizeof(S_MALLA);
pack.flg=MSG_WAIT;
pack.wto=0;


switch(com->tipo)
{
case 2:         			/* organo con un solo stato atteso */
        dboft[com->organo]=dboft[com->organo] | mask_tc ;
        dbosa[com->organo]=com->stat[0].st_fut ;
        dbto[com->organo]=com->time ;
        break ;
case 3:                /* organo con piu' stati attesi */
        dboft[com->organo]=dboft[com->organo] | mask_tc ;
        dbosa[com->organo]=com->stat[0].st_fut ;
     /*
        ricerca stato atteso in base a quello attuale dell'
        organo
     */
     for(i=0;i<st_com;i++)
     {
        if((dbosc[com->organo] & 0x00FF) == com->stat[i].st_att)
        {
                dbosa[com->organo]=com->stat[i].st_fut ;
                goto CONT ;
        }
     }
     return(0)  ;   /* non e'stato trovato */
CONT :
        dbto[com->organo]=com->time ;
        break ;
}
/*
        verifico se e` abilitata la stampa del comando
*/
switch(com->abili)
{
		case 1:										/* comando lanciato dalla stessa stop */
			mess.satt=emi_com;					
			break;
		case 2:										/* comando lanciato da un'altra stop  */
			mess.satt=com_stop;
			break;
		case 3:										/*  comando da PAS		  */
			mess.satt=com_pas;
			break;
		default:										 /* stampa non abilitata	*/
			return(0);
}
mess.ertr=0x81;  mess.ext=g1tipdo;    mess.punt=com->comando;
mess.sprec=mis_norm; 
mess.sogl1=(unsigned char) -1; mess.sogl2= (unsigned char) -1;
enqueue(&pack); 
return(0);
}

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
	Coman.c

	routine per l'invio dei comandi digitali su inet
	in ingresso viene fornito solo il puntatore in dbs

	Parametri

	puntdb	short	puntatore in data base

	Ritorno

	nessuno

	20 Aprile 1993
	
*/
#include "pscs.cfg"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "sepdati.inc"
#include "messcada.inc"
#include "tipal.inc"
#include "switch.inc"

coman(puntdb)
unsigned short puntdb ;
{
QUEUE_PACKET pack;
short i;
S_FDCOM des_com;				 	// descrittore comando
S_MSCDO_SEP mess;					// messaggio invio comando
S_MALLA malla;						// emissione allarme invio comando
   
pack.lmsg=sizeof(S_MSCDO_SEP);

pack.que=c_ut_tx;
pack.wto=0;
pack.flg=MSG_WAIT;
pack.amsg=(char*) & mess;

mess.hea.mess=mscdo;
mess.hea.prov=cl_scada;
mess.hea.dest=cl_dac;

/*
	lettura descrittore comando
*/
if(rbyte(fileno(fpp[fdcom]),&des_com,(long)puntdb*(long)sizeof(S_FDCOM),
		sizeof(S_FDCOM))==-1)	
         return(0);		// se nessun record letto

mess.hea.addr_nodo=des_com.micro*2+nodo_armadi;
mess.indice=des_com.usc1.s;
mess.temp=des_com.temp1 & 0x3FFF;
if(des_com.temp1 & 0x8000) 
   mess.valore=1;
else 
   mess.valore=0;

if((!SYS_DUALE)||(SYS_DUALE && sys_master))
    enqueue(&pack);

tra(mbox_inet,1);

switch(des_com.tipo)
{
case 2:         			/* organo con un solo stato atteso */
        dboft[des_com.organo]=dboft[des_com.organo] | mask_tc ;
        dbosa[des_com.organo]=des_com.stat[0].st_fut ;
        dbto[des_com.organo]=des_com.time ;
        break ;
case 3:                /* organo con piu' stati attesi */
        dboft[des_com.organo]=dboft[des_com.organo] | mask_tc ;
        dbosa[des_com.organo]=des_com.stat[0].st_fut ;
     /*
        ricerca stato atteso in base a quello attuale dell'
        organo
     */
     	  for(i=0;i<st_com;i++)
     	  {
        		if((dbosc[des_com.organo] & 0x00FF) == des_com.stat[i].st_att)
        		{
                dbosa[des_com.organo]=des_com.stat[i].st_fut ;
                goto CONT ;
        		}
	     }
   	  return(0)  ;   /* non e'stato trovato */
CONT:
        dbto[des_com.organo]=des_com.time ;
        break ;
}
/*
        verifico se e` abilitata la stampa 
*/
switch(des_com.abili)
{
		case 1:										/* comando lanciato dalla stessa stop */
			malla.satt=emi_com;					
			break;
		case 2:										/* comando lanciato da un'altra stop  */
			malla.satt=com_stop;
			break;
		case 3:										/*  comando da PAS		  */
			malla.satt=com_pas;
			break;
		default:										 /* stampa non abilitata	*/
			return(0);
}
pack.que=c_visall;
pack.amsg=(char*)&malla;
pack.lmsg=sizeof(S_MALLA);
pack.flg=MSG_WAIT;
pack.wto=0;

malla.ertr=0x81;  malla.ext=g1tipdo;    malla.punt=des_com.comando;
malla.sprec=mis_norm; 
malla.sogl1=-1; malla.sogl2=-1;
enqueue(&pack); 
return(0);
}




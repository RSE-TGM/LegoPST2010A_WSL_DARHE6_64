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
/*-> intesta
 *
 *   esegue l'intestazione per il tabulato degli allarmi
 *
 */
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "diagnoan.inc"
#include "diagnodi.inc"
#include "fileop.inc"
#include "messcada.inc"
#include "allar.inc"
#include "print.inc"
#include "intesta.inc"
#include "mesqueue.h"

intesta(coda,mess,ind,pagina)
short mess,pagina,ind,coda ;
{
QUEUE_PACKET pack;
short anno;

union u_intestazioni	{
								S_FFEED		ffeed;
								S_INTALL_2	int_2;
								S_INTALL_1	int_1;
								S_INTEAR    intear;
							 } ui;

pack.que=coda+ind;
pack.flg=MSG_WAIT;
pack.amsg=(char *) &ui;
pack.wto=0;

/*
	invio comunque un salto pagina
*/
   pack.lmsg=sizeof(S_FFEED);
   ui.ffeed.hea.lung=sizeof(S_FFEED);
   ui.ffeed.hea.linea=ind;
   ui.ffeed.ff[0]=' ';
   ui.ffeed.ff[1]=0x0c;
   if(ind == fis_disk)	stdisk(ui.ffeed.ff,ui.ffeed.hea.lung-sizeof(HEA_STA),no_fine);
   else enqueue(&pack);

switch(mess)
{
case mstal :            /* intestazione allarmi normali */
/*
        ricavo giorno
*/
		  memset(&ui,' ',sizeof(S_INTALL_1));
		  pack.lmsg=sizeof(S_INTALL_1);
		  ui.int_1.hea.lung=sizeof(S_INTALL_1);
		  ui.int_1.hea.linea=ind;
		  if(dbadv[db_anno]>=2000)	anno=dbadv[db_anno]-2000;
		  else 						   anno=dbadv[db_anno]-1900;

   if (INGLESE)
   {
        decnum(ui.int_1.data,2,-1,(short)dbadv[db_mese],0);
		  ui.int_1.data[2]='/';	
        decnum(&ui.int_1.data[3],2,-1,(short)dbadv[db_giorno],0);
		  ui.int_1.data[5]='/';
   }
   else
   {
        decnum(ui.int_1.data,2,-1,(short)dbadv[db_giorno],0);
		  ui.int_1.data[2]='/';	
        decnum(&ui.int_1.data[3],2,-1,(short)dbadv[db_mese],0);
		  ui.int_1.data[5]='/';
   }
        decnum(&ui.int_1.data[6],2,-1,anno,0);

        if (SYS_DUALE)
            {
            memcpy(ui.int_1.bmaster,"MASTER STOP ",12) ;
            if(bitvalue(&dbdd[sysab],g2di_sl))  ui.int_1.sys='B';
            else  ui.int_1.sys='A';
            }
      
        memcpy(ui.int_1.page,s_pag,4) ;
        decnum(ui.int_1.num,4,-1,pagina,0);
        ui.int_1.new= 0x0D0A ;
        ui.int_1.eos= 0x0D0A ;   
		  if(ind == fis_disk)	stdisk(ui.int_1.blank_1,ui.ffeed.hea.lung-sizeof(HEA_STA),no_fine);
        else	enqueue(&pack);
/*
        scrivo la seconda scritta di intestazione
*/
		  memset(&ui,' ',sizeof(S_INTALL_2));
		  pack.lmsg=sizeof(S_INTALL_2);
		  ui.int_2.hea.lung=sizeof(S_INTALL_2);
		  ui.int_2.hea.linea=ind;
		  memcpy(ui.int_2.stringa,intes_1,l_intall);
        ui.int_2.new= 0x0D0A ;
        ui.int_2.eos= 0x0D0A ;
		  if(ind == fis_disk)	stdisk(ui.int_2.stringa,ui.ffeed.hea.lung-sizeof(HEA_STA),no_fine);
        else enqueue(&pack);	 				 /* un solo newline */

        memcpy(ui.int_2.stringa,intes_2,l_intall);
		  if(ind == fis_disk)	stdisk(ui.int_2.stringa,ui.ffeed.hea.lung-sizeof(HEA_STA),no_fine);
        else enqueue(&pack);	 
        break ;
/*
	intestazione stampa allarmi in buffer archivio
*/
case mstar:
		  memset(ui.intear.stringa,' ',l_intear);
   if (INGLESE)
      {
		  decnum(&ui.intear.stringa[1],2,-1,(short)dbadv[db_mese],0);
		  ui.intear.stringa[3]='/';	
		  decnum(&ui.intear.stringa[4],2,-1,(short)dbadv[db_giorno],0);
      }
   else
      {
		  decnum(&ui.intear.stringa[1],2,-1,(short)dbadv[db_giorno],0);
		  ui.intear.stringa[3]='/';	
		  decnum(&ui.intear.stringa[4],2,-1,(short)dbadv[db_mese],0);
      }
		  ui.intear.stringa[6]='/';	
		  decnum(&ui.intear.stringa[7],4,-1,(short)dbadv[db_anno],0);
		  decnum(&ui.intear.stringa[13],2,-1,(short)dbadv[db_ora],0);
		  ui.intear.stringa[15]=':';	
		  decnum(&ui.intear.stringa[16],2,-1,(short)dbadv[db_minuti],0);
		  ui.intear.stringa[18]=':';	
		  decnum(&ui.intear.stringa[19],2,-1,(short)dbadv[db_secondi],0);
        if(infotesta[1]!=-1)
        {
   		  strcpy(&ui.intear.stringa[30],st_alpage);
        }
        else 
   		  strcpy(&ui.intear.stringa[30],st_alpage);
		  decnum(&ui.intear.stringa[49],2,-1,infotesta[0]+1,0);
        memcpy(&ui.intear.stringa[75],s_pag,4) ;
        decnum(&ui.intear.stringa[80],4,-1,pagina,0);
		  ui.intear.new_1=0x0D0A;
		  ui.intear.new_2=0x0D0A ;                  /* fine riga    */
		  ui.intear.hea.lung=sizeof(S_INTEAR);
	  	  ui.intear.hea.linea=ind;
		  pack.lmsg=sizeof(S_INTEAR);
		  enqueue(&pack);
		  memset(ui.intear.stringa,' ',l_intear);
		  strcpy(ui.intear.stringa,intar_1);
		  enqueue(&pack);
		  break;
/*
	intestazione elenchi fz fs fa e allarmi
*/
case minel:
		  memset(ui.intear.stringa,' ',l_intear);
if (INGLESE)
   {
		  decnum(&ui.intear.stringa[1],2,-1,(short)dbadv[db_mese],0);
		  ui.intear.stringa[3]='/';	
		  decnum(&ui.intear.stringa[4],2,-1,(short)dbadv[db_giorno],0);
   }
   else
   {
		  decnum(&ui.intear.stringa[1],2,-1,(short)dbadv[db_giorno],0);
		  ui.intear.stringa[3]='/';	
		  decnum(&ui.intear.stringa[4],2,-1,(short)dbadv[db_mese],0);
   }
		  ui.intear.stringa[6]='/';	
		  decnum(&ui.intear.stringa[7],4,-1,(short)dbadv[db_anno],0);
		  decnum(&ui.intear.stringa[13],2,-1,(short)dbadv[db_ora],0);
		  ui.intear.stringa[15]=':';	
		  decnum(&ui.intear.stringa[16],2,-1,(short)dbadv[db_minuti],0);
		  ui.intear.stringa[18]=':';	
		  decnum(&ui.intear.stringa[19],2,-1,(short)dbadv[db_secondi],0);
		  strcpy(&ui.intear.stringa[30],point_t);
	  	  strcpy(&ui.intear.stringa[36],s_tipu[infotesta[1]-1]);
	  	  strcpy(&ui.intear.stringa[60],s_tiel[infotesta[0]-1]);
        memcpy(&ui.intear.stringa[76],s_pag,4) ;
        decnum(&ui.intear.stringa[80],4,-1,pagina,0);
		  ui.intear.new_1=0x0D0A;
		  ui.intear.new_2=0x0D0A ;                  /* fine riga    */
		  ui.intear.hea.lung=sizeof(S_INTEAR);
	  	  ui.intear.hea.linea=ind;
		  pack.lmsg=sizeof(S_INTEAR);
		  enqueue(&pack);
		  memset(ui.intear.stringa,' ',l_intear);
		  if(infotesta[0]==ELE_HC_HS_LC_LS || infotesta[0]==ELE_AL)
			  	 strcpy(ui.intear.stringa,intel_3);
		  else if(infotesta[1]>=g1tipda) strcpy(ui.intear.stringa,intel_1);
		  		 else strcpy(ui.intear.stringa,intel_2);
		  enqueue(&pack);
}
}


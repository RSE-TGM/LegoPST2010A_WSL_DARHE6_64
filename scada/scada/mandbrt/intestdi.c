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
        la function intestdi visualizza le caratteristiche
        dei punti digitali di qualsiasi tipo
        sigla descrizione stato 0 e stato 1
        
        indice int in n. della misura in esame
        point  short in puntatore in data base della misura
*/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "tabelle.inc"
#include "dconf.inc"
#include "ansiscr.h"
#include "ctasti.inc"
#include "intestdi.inc"

extern DB_HEADER h_db;

#define lun_nome 10
#define lun_descr 24

intestdi(indice,punt,ext)
short indice;
short  punt ;
short ext ;
{
#define HI 0x0f	  		/* carattere ad alta intensit…	*/
#define N  0x07			/* carattere normale 				*/
#define REV 0x40			/* carattere in reverse				*/
short tot ;
char c;
long point;
long disp;
short ier ;
FILE *fp;
char nome[lun_nome+1], descr[lun_descr+1],stat0[lun_stato+1];
char stat1[lun_stato+1] ;
/*
        leggo nome descrizione e stati
*/

point=punt;
 
switch (ext)
 {
 case g1tipda:
  disp = of_fdda+point*rec_fdda; 
  break;
 case g1tipds:
  disp = of_fdds+point*rec_fdds; 
  break;
 case g1tipdd:
  disp = of_fddd+point*rec_fddd; 
  break;
 case g1tipdc:
  disp = of_fddc+point*rec_fddc; 
  break;
 case g1tipdo:
  disp = of_fddo+point*rec_fddo; 
  break;
  }

fp = fpp[fdde];

rbyte(fileno(fp),(short*)nome,disp,lun_nome);      
rbyte(fileno(fp),(short *)descr,disp+lun_nome,lun_descr);
nome[lun_nome]=0;
descr[lun_descr]=0;



if(ext != g1tipdo)              /* nessun stato per comandi */
	{
   rbyte(fileno(fp),(short*)stat0,disp+lun_nome+lun_descr,lun_stato);   stat0[lun_stato]=0 ;
   rbyte(fileno(fp),(short*)stat1,disp+lun_nome+lun_descr+lun_stato,lun_stato);   stat1[lun_stato]=0 ;
	stat0[lun_stato]=0 ;
	stat1[lun_stato]=0 ;
	}

tot=indice*num_righe+1 ;
scrxy(tot,nom_pos);
printf("%s",nome);
scrxy(tot,descr_pos);
printf("%s",descr);
scrxy(tot,tipo_pos);
printf("%s",tipodi[ext-g1tipda]);

/*
        scrittura stati solo se non si tratta di comandi
*/
if(ext != g1tipdo)
{
tot=indice*num_righe+1+off_stats ;
scrxy(tot,st0_pos);
printf("%s",stato_0);
scrxy(tot,st1_pos);
printf("%s",stato_1);

tot=indice*num_righe+1+off_statv ;
scrxy(tot,st0_pos);
printf("%s",stat0);
scrxy(tot,st1_pos);
printf("%s",stat1);
}
}






 

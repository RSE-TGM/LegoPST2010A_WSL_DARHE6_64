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
/******************************************************************
	Modulo:  INITCALC.C

        procedura di inizializzazione.
  
        Inizializza la struttura tab_cal[] e conta quante calcolate
        per classe di scansione sono state installate.
  
        inizializza reset ed attiva in modo che il periodo di reset
        non scada immediatamente (vengono salvati gli eventuali
        valori passati delle calcolate)

	Creazione :  Antecedente 01.05.92

******************************************************************/

#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "dconf.inc"
#include "diagnoan.inc"

#define _PUBLIC 0 

#include "calas.inc"
#include "converti.inc"

extern DB_HEADER h_db;

initcalc()
{
short i,j;

desc=&dbasde[0];
tab_cal[0].period=1;    tab_cal[0].count_periodo=1;
tab_cal[1].period=5;    tab_cal[1].count_periodo=5;
tab_cal[2].period=15;   tab_cal[2].count_periodo=15;
tab_cal[3].period=30;   tab_cal[3].count_periodo=30;
tab_cal[4].period=60;   tab_cal[4].count_periodo=60;
tab_cal[0].ncalt=0 ;
tab_cal[1].ncalt=0;
tab_cal[2].ncalt=0;
tab_cal[3].ncalt=0;
tab_cal[4].ncalt=0;


for(i=0;i<h_db.dimas;i++,desc++)
{
if(desc->a.periodo > 60)
	setpunt(i);
else
   {
   switch(desc->a.periodo)
		{
      case 1:
      	tab_cal[0].ncalt++;
      	break;
      case 5:
         tab_cal[1].ncalt++;
         break;
      case 15:
         tab_cal[2].ncalt++;
         break;
      case 30:
         tab_cal[3].ncalt++;
         break;
      case 60:
         tab_cal[4].ncalt++;
         break;
       }
   }
}
tab_cal[0].count=tab_cal[0].ncalt;
tab_cal[1].count=tab_cal[1].ncalt;
tab_cal[2].count=tab_cal[2].ncalt;
tab_cal[3].count=tab_cal[3].ncalt;
tab_cal[4].count=tab_cal[4].ncalt;

tab_cal[0].ncals=tab_cal[0].ncalt;
tab_cal[1].ncals=(tab_cal[1].ncalt/5)+1;
tab_cal[2].ncals=(tab_cal[2].ncalt/15)+1;
tab_cal[3].ncals=(tab_cal[3].ncalt/30)+1;
tab_cal[4].ncals=(tab_cal[4].ncalt/60)+1;

/*for(i=0;i<5;i++)
  printf("a= %d ",tab_cal[i].ncalt);*/
/*
         il vettore attiva posto a 0 permette l'inizializza
         zione di tutte le calcolate che hanno periodo di
         reset
*/

attiva[f_ora]=dbadv[db_ora];
attiva[f_gio]=dbadv[db_giorno];
attiva[f_mes]=dbadv[db_mese];
attiva[f_ann]=dbadv[db_anno];

for(i=0;i<4;i++)                /* inizializzato reset  */
  {
        for(j=0;j<n_periodi; j++)
                reset[j][i]=2;
  }
/*
	inizializzazione coefficienti calcolo fa con i valori di
	default
*/
coef_media=fcoef_media;
coef_filtro=fcoef_filtro;
coef_scarto=fcoef_scarto;
coef_mist=fcoef_mist;
coef_integrale=fcoef_integrale;
coef_somma=fcoef_somma;
reset_ut=-1;                        // reset utente non definito
}


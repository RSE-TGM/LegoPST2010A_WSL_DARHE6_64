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
   Modulo:  SIMCLDBS.C

	     Clear Data Base di Sistema (tabelle in memoria)
        - valori degli analogici a 0
        - stato e flag dei digitali a 0 (salvataggio trattamento)
        - stato organi a 0 
        - stringhe a 0

   04.08.92  -  Rel. 1.00  -  GM.Furlan

   27 Marzo 1995 Fc Porting a 32 Bit
      La funzione viene effettivamente eseguita solo in caso di
      AC_SIM_ENEL
*/
#include "g2comdb.inc"
#include "dconf.inc"


extern DB_HEADER h_db;

void simcldbs()
{
short i;
short mask;

// Analogici
// an. acq.
for(i=0;i<h_db.dimaa;i++)
{
   dbaav[i] =0;
   dbaaf[i] =0;
   dbaafa[i]=0;
}

// an. calc.
for(i=0;i<h_db.dimas;i++)
{
   dbasv[i] =0;
   dbasf[i] =0;
   switch(dbasde[i].a.tipoc)
   {
      case 1: case 2: case 3:
             dbasde[i].a.cont_err=0L;
             dbasde[i].a.cont_camp=0L;
             dbasde[i].a.savev=0.0;
             dbasde[i].a.savef=0;
      break;
      case 4: case 5:
             dbasde[i].i.cont_err=0L;
             dbasde[i].i.cont_camp=0L;
             dbasde[i].i.savev=0.0;
             dbasde[i].i.savef=0;
      break;
      case 6: case 7:
             dbasde[i].p.cont_err=0L;
      break;
      case 8:
             dbasde[i].f.cont_err=0L;
      break;
      case 9:
             dbasde[i].m.cont_err=0L;
      break;
      case 10:
             dbasde[i].o.cont_err=0L;
      break;
      case 11:
             dbasde[i].s.cont_err=0L;
      break;
      case 12:
             dbasde[i].q.somma_q=0.0;
             dbasde[i].q.somma_i=0.0;
             dbasde[i].q.cont_cv=0L;
             dbasde[i].q.cont_ctot=0L;
             dbasde[i].q.savev=0.0;
             dbasde[i].q.savef=0;
      break;
   }
}

// an. calc. nst.
for(i=0;i<h_db.dimac;i++)
{
   dbacv[i] =0;
   dbacf[i] =0;
}

// Digitali
mask= 0x000F;        // maschera per salvataggio tipo di trattamento digitali
// dig. acquisiti
for(i=0;i<h_db.dimda;i++)
   dbda[i]=dbda[i] & mask;

// dig. calcolati
for(i=0;i<h_db.dimds;i++)
   dbds[i]=dbds[i] & mask;

// dig. calcolati non stand.
for(i=0;i<h_db.dimdc;i++)
   dbdc[i]=dbdc[i] & mask;

// organi
for(i=0;i<h_db.dimor;i++)
{
   dbto[i]=0 ;
   dboft[i]=0 ;
   dbosp[i]=0 ;
   dbosc[i]=0 ;
}
}


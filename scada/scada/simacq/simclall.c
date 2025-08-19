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
   Modulo:  SIMCLALL.C
	         Clear Data Base Allarmi

   04.08.92  -  Rel. 1.00  -  GM.Furlan

   27 Marzo 1995 Fc Porting a 32 Bit
      La funzione viene eseguita solo in caso di AC_SIM_ENEL
*/

#include "messcada.inc"
#include "allar.inc"

void simclall()
{

short i,j;

   for (i=0;i<max_dbsall;i++)
   {
      if (bDbsAll[i].def)
      {
         bDbsAll[i].fchanga=1;
         *bDbsAll[i].db_al=0;
         *bDbsAll[i].db_ar=0;
         for(j=0;j<max_zone;j++)
         {
            bDbsAlu[j].n_al[i]=0;
            bDbsAlu[j].n_ar[i]=0;
         }
         bDbsAll[i].pout=0;
         bDbsAll[i].pin=0; 
         bDbsAll[i].pinv=0;
      }
   }
}

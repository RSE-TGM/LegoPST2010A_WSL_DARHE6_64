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
/*************************************************************
	Modulo: SOMMAIST.C
  
        SOMMA ISTANTANEA di un massimo di 8 misure.
  
        La somma non viene ritenuta valida e pertanto non viene
        aggiornato il suo valore se il numero di misure invalide
        e' superiore a quello delle misure valide moltiplicato un
        opportuno coefficiente. In tal caso viene anche settato
        il bit di fuori attendibilita'.
  
        Non vengono passati parametri alla routine.
  
        La definizione del coefficiente e' nel file di include
        "calas.inc" .
  
	Creazione :  Antecedente 01.05.92

	Revisioni :  18.05.92  -  GM Furlan
	             Calcoli in doppia precisione

*************************************************************/

#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "calas.inc"

sommaist()
{
int i, valide, nonvalide, totmisure;
double somma ,val[num_somma];
short *flag[num_somma];

somma=(double)0 ;
nonvalide=0 ;
totmisure=0 ;
valide=0 ;

for(i=0;i<num_somma;i++)
 {
  if(tab->corrente->s.tip_misure[i] !=-1)
   {
   switch(tab->corrente->s.tip_misure[i])
    {
        case g1tipaa:
                flag[i]=&dbaaf[tab->corrente->s.ind_misure[i]];
                val[i]=(double)dbaav[tab->corrente->s.ind_misure[i]];
                break;
        case g1tipac:
                flag[i]=&dbacf[tab->corrente->s.ind_misure[i]];
                val[i]=(double)dbacv[tab->corrente->s.ind_misure[i]];
                break;
        case g1tipas:
                flag[i]=&dbasf[tab->corrente->s.ind_misure[i]];
                val[i]=(double)dbasv[tab->corrente->s.ind_misure[i]];
                break;
        case g1tipad:
                flag[i]=&dbadf[tab->corrente->s.ind_misure[i]];
                val[i]=(double)dbadv[tab->corrente->s.ind_misure[i]];
                break;
    }   /*end switch */

   somma=somma+val[i];          /* si sommano tutte anche quelle fa */
   if(bitvalue(flag[i],g2an_fa) || bitvalue(flag[i],g2an_fs))
      {
        tab->corrente->s.cont_err++;
        nonvalide++;
      }
   else
        valide++;
  }     /* end if  */
 }      /* end for */

totmisure=valide+nonvalide;

dbasv[tab->addr_corrente]=somma;

if(nonvalide <= (totmisure*coef_somma))
        bitset(&dbasf[tab->addr_corrente],g2an_fa,0);
else
        bitset(&dbasf[tab->addr_corrente],g2an_fa,1);

tab->corrente->s.cont_err=0;
// printf("\ngenerata =%f",dbasv[tab->addr_corrente]);
}


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
/*****************************************************************
	Modulo: MEDIAIST.C
  
        Media istantanea.
  
        Mediaist.c calcola la media istantanea
        di un massimo di sei  misure.
        la media viene effettuata solo sulle misure
        effettivamente valide e se il numero di queste
        moltiplicato per un coefficiente e' superiore
        al numero delle misure invalide.
  
	Creazione :  Antecedente 01.05.92

	Revisioni :  18.05.92  -  GM Furlan
	             Calcoli in doppia precisione
*******************************************************************/

#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "calas.inc"

// External function declarations
extern int bitvalue(short *, short);
extern void bitset(short *, short, short);

void mediaist()
{
int i, nonvalide, valide, totmisure;
double somma;

nonvalide=0 ;
valide=0 ;
totmisure=0 ;
somma=(double)0.0 ;

for(i=0;i<num_media;i++)
  {
  if(tab->corrente->m.misura[i].ext != -1)
    {
    switch(tab->corrente->m.misura[i].ext)
      {
        case g1tipaa:
         if(bitvalue(&dbaaf[tab->corrente->m.misura[i].punt],
            g2an_fs)  ||
            bitvalue(&dbaaf[tab->corrente->m.misura[i].punt],
            g2an_fa))
                nonvalide++;
         else
            {
                valide++;
                somma=somma+dbaav[tab->corrente->m.misura[i].punt];
             }
         break;
        case g1tipac:
         if(bitvalue(&dbacf[tab->corrente->m.misura[i].punt],
            g2an_fs)  ||
            bitvalue(&dbacf[tab->corrente->m.misura[i].punt],
            g2an_fa))
                nonvalide++;
         else
            {
                valide++;
                somma=somma+dbacv[tab->corrente->m.misura[i].punt];
             }
         break;
        case g1tipas:
         if(bitvalue(&dbasf[tab->corrente->m.misura[i].punt],
            g2an_fs)  ||
            bitvalue(&dbasf[tab->corrente->m.misura[i].punt],
            g2an_fa))
                nonvalide++;
         else
            {
                valide++;
                somma=somma+dbasv[tab->corrente->m.misura[i].punt];
             }
         break;
        case g1tipad:
         if(bitvalue(&dbadf[tab->corrente->m.misura[i].punt],
            g2an_fs)  ||
            bitvalue(&dbadf[tab->corrente->m.misura[i].punt],
            g2an_fa))
                nonvalide++;
         else
            {
                valide++;
                somma=somma+dbadv[tab->corrente->m.misura[i].punt];
             }
         break;
        }       /*end switch */
      }
  }   /*end for */

totmisure=nonvalide+valide;

if(nonvalide >= (totmisure*coef_mist))
        bitset(&dbasf[tab->addr_corrente],g2an_fa,1);
else
   {
        bitset(&dbasf[tab->addr_corrente],g2an_fa,0);
        if(valide>0)
                dbasv[tab->addr_corrente]=somma/valide;
   }
/*
printf("\n nonvalide= %d",nonvalide);
printf("\n    valide= %d",valide);
printf("\n    somma = %f",somma);
printf("\ndbasv[]=%f",dbasv[tab->addr_corrente]);
*/
}

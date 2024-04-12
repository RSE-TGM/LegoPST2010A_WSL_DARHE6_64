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
	Modulo : FILTRO.C
  
        FILTRO. Determina il filtro del primo ordine per una
        misura.
  
        Se la contribuente e' fuori attendibilita' oppure
        fuori scansione incrementa il contatore di errori di una
        quantita' filtrata in rapporto al coefficiente di smt
        presente nel descrittore. La generata non e' valida e quindi
        messa F.A. se il contatore di errori supera un coefficiente
        coef_filtro stabilito a priori: se cio' avviene la
        calcolata non viene aggiornata.
  
        Alla routine non vengono passati parametri.
  
        La definizione del coefficiente coef_filtro e' nel file di
        include CALAS.INC nel medesimo direttorio di questa routine.

	Creazione :  Antecedente 01.05.92

	Revisioni :  18.05.92  -  GM Furlan
	             Calcoli in doppia precisione
  
**************************************************************/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "calas.inc"

filtro()
{
int i,counter;
double generata,val,cf;
short *flag, contr;

cf=(double)0.0001*(double)tab->corrente->f.cost1;
generata=(double)dbasv[tab->addr_corrente];
contr=tab->corrente->f.misura.punt;
counter=tab->corrente->f.cont_err;

switch(tab->corrente->f.misura.ext)
 {
  case g1tipaa:
        flag=&dbaaf[contr];
        val=(double)dbaav[contr];
        break;
  case g1tipac:
        flag=&dbacf[contr];
        val=(double)dbacv[contr];
        break;
  case g1tipas:
        flag=&dbasf[contr];
        val=(double)dbasv[contr];
        break;
  case g1tipad:
        flag=&dbadf[contr];
        val=(double)dbadv[contr];
        break;
 }

/*      se la contribuente e' F.A o F.S. la calcolata non e' aggior.*/

if(bitvalue(flag,g2an_fa) || bitvalue(flag,g2an_fs))
        counter=counter+cf*(1.0- counter);
else
    {
        val=generata+cf*(val-generata);
        counter=counter+cf*(0.0- counter);
        dbasv[tab->addr_corrente]=(float)val;

        if(counter >= coef_filtro)
                bitset(&dbasf[tab->addr_corrente],g2an_fa,1);
        else
                bitset(&dbasf[tab->addr_corrente],g2an_fa,0);
}
tab->corrente->f.cont_err=counter;

/*
printf("\ngenerata =%f ",val);
*/
}


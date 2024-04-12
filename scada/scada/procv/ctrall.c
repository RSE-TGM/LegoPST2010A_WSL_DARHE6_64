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
   routine per il controllo della validita' dei limiti di allarme
   Il controllo viene effettuato sulla struttura DBALL passata come 
   puntatore
   La funzione ritorna 0 se tutto ok
                       1 se i valori non sono accettabili
*/                   
#include "g0strdb.inc"


ctrall(all)
S_DBALL *all;
{
short num, i;
float val[4];

num=0;
if(all->bass_sic.cval[0]!=-1 && all->bass_sic.cval[0]!=-2)
{  val[num]=all->bass_sic.fval; num++; }
if(all->bass_con.cval[0]!=-1 && all->bass_con.cval[0]!=-2)
{  val[num]=all->bass_con.fval; num++; }
if(all->alto_con.cval[0]!=-1 && all->alto_con.cval[0]!=-2)
{  val[num]=all->alto_con.fval; num++; }
if(all->alto_sic.cval[0]!=-1 && all->alto_sic.cval[0]!=-2)
{  val[num]=all->alto_sic.fval; num++; }
/*
   ciclo di controllo
*/
for(i=0;i<num-1;i++)
{
     if(val[i]>=val[i+1]) return(1);
}
return(0);
}


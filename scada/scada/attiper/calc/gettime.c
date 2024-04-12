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
	Modulo: GETTIME.C
  
        verifica se e' cambiato ora/giorno/mese/anno per il
        reset dei contatori temporali.
        Verifica che ora/mese/anno/giorno siano identici a quelli
        conservati in "attiva[n_freset]". Se non lo sono pone a zero lo
        elemento corrispondente della matrice "reset" altrimenti
        incrementa tale elemento.
  
        Alla routine e' passato il periodo di scansione attuale.
  
        se il periodo e` 0 e reset e` posto a 1 viene fatto il
        flush delle calcolate prima che vengano azzerate
  
	Creazione :  Antecedente 01.05.92

	Revisioni :  18.05.92  -  GM Furlan
                Routine non gestisce piu' lo skip della pagina
                del libro giornale al cambio di data

                11 Luglio 1994   Fc
                Inserimento gestione reset calcolata impostata da utente

******************************************************************/

#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "calas.inc"
#include "diagnoan.inc"
#include "dconf.inc"

gettime(periodo)
int periodo;
{
int i,j, date[n_freset];
/*
   incremento contatori del periodo di scansione in esame
*/
for(i=0;i<n_freset;i++)
{
      {if(reset[periodo][i]<2) reset[periodo][i]++; }
}
/*
	il test di variazione di ora giorno mese o anno viene
	eseguito solo alla fine del ciclo quando si esamina il
	periodo a 60 secondi
*/
if(periodo < n_periodi-1) return(0);

date[f_ora]=dbadv[db_ora];
date[f_gio]=dbadv[db_giorno];
date[f_mes]=dbadv[db_mese];
date[f_ann]=dbadv[db_anno];
if(reset_ut!=-1) date[f_ut]=dbadv[db_minuti]/reset_ut;
else date[f_ut]=0;
/*
	reset[periodo][frequenza] assume solo i valori 0,1,2 con i seguenti 
	significati:
	1 :punti in reset.
	2 :punto in condizione normale.
*/
for(i=0;i<n_freset;i++)
  {
    if(date[i] == attiva[i])  
    {
//       for(j=0;j<n_periodi; j++) 
//         {if(reset[j][i]<2) reset[j][i]++; }
    }
    else
    {
        for(j=0;j<n_periodi; j++)
         reset[j][i]=0;	
    }
  }


for(i=0;i<n_freset;attiva[i]=date[i],i++);
/*
	ogni ora al minuto quindicesimo provvedo alla scrittura parziale
	del data base	e resetto il bit del digitale flush eseguito
*/
if((dbadv[db_minuti]==15.00))
{
		wrdb(wr_fl);
}
return(0);
}


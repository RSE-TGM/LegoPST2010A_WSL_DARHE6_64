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
	Modulo   : ARCRAC.C  (SCADA-Gestione archivi) 
	           Legge dal data base dei punti i valori istantanei dei punti 
	           attualmente in archiviazione e li memorizza in opportuni data
	           base di archivio (arcdbsNV, arcdbsL) le cui strutture sono 
	           definite in "arc.inc"
	           I punti in archiviazione sono quelli appartenenti agli archivi 
	           con periodo di campionamento pari a quello specificato in input.

	           La memorizzazione puo' essere:
	           - normale= Archivi N: in corrispondenza del periodo di archiviazione
	                      si memorizza il valore del campione.
	           - lenta  = Archivi L: in corrispondenza del periodo LENTO di
	                      archiviazione, si memorizza la media attuale degli 
	                      analogici ed il valore dei digitali.
	           - veloce = Archivi L: in corrispondenza del periodo VELOCE di
	                      archiviazione, si memorizza il valore di analogici 
	                      e dei digitali.
	                      La memorizzazione dei valori dei punti puo' essere
	                      totale o parziale, secondo quanto specificato in 
	                      configurazione, in base all'attivazione o meno del 
	                      trigger
	

	Parametri: long freq: periodo di acquisizione in secondi


	Creazione:  GM.Furlan  -  10.03.92  -  Rel. 1.0   

*/

#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "arc.inc"

// External function declarations
extern void arcana(PUNTDBS *, DATDBS *);
extern short arcave(PUNTDBS *, DATDBS *);
extern short arcdig(PUNTDBS *);
extern void bitset(short *, short, short);
extern short arctrig(short, short);

char tabmem[n_misarc];  // tabella memorizzazione misura

void arcrac(long freq)		// periodo di acquisizione in secondi
{

short i_arc;	 		// indice archivio attuale
short flagT;	 		// (memorizzazione veloce) trigger e' scattato
short flagL;	 		// flag tipo di archiviazione
register short i_des;// scorre le misure in archivio
register short j_dbs;// scorre le misure nel data base di archivio
PARCDES *p_des;		// puntatore al descrittore archivio corrente
DATDBS  *ini_dbs;		// puntatore al data base di archivio iniziale
DATDBS  *p_dbs;		// puntatore al data base di archivio progressivo
PUNTDBS *point;      // puntatore ad una misura
HEAD_CAMP *hea;      // puntatore all'header del dbs
short flag_dbs;      // word di flag per testare i trigger
char trig_A, trig_D; // codifica trigger
char trig_U;         // assume il valore o trig_A o trig_D

#if defined (DEBUG)
   printf("\n ** freq: %Ld ",freq);
#endif

/*
	ricerca nella tabella degli archivi di quelli (Normali o 
	Lenti/Veloci) aventi frequenza "freq" (normale,lenta o veloce).
*/
flagT=0;                      // nessuna misura in trigger
p_des=&arcdes[0];

for(i_arc=0;i_arc<n_arc;i_arc++,p_des++)
{
	if (arcdes[i_arc].hea.iarc==-1 || (arcdes[i_arc].hea.freqN!=freq)) continue;
	memset(tabmem,1,n_misarc);       // inizializzazione tabella memorizzazione
/*
   in base al tipo di archivio seleziono il data base opportuno
*/
	if (arcdes[i_arc].hea.tipo==arc_Norm) 		// archivio "Normale"
   { 
		flagL=0;                
		ini_dbs=arcdbsN[i_arc]->dbs;
      hea=&arcdbsN[i_arc]->hea;
#if defined (DEBUG)
   printf("\n n. %d norm.",i_arc);
#endif
	}
 	else		                                  // archivio "Lento/Veloce"
	{
		flagL=1;
		ini_dbs=arcdbsL[i_arc]->dbs;
      hea=&arcdbsL[i_arc]->hea;
      trig_A=p_des->hea.trigga;
      trig_D=p_des->hea.triggd;
#if defined (DEBUG)
   printf("\n n. %d lento ",i_arc);
#endif
	}

INIZIO: 		// per tutte le misure in archivio eseguo la raccolta dati
/*
   inizializzo l' header con data tempo
*/
 	memcpy(hea,&hea_camp,sizeof(HEAD_CAMP));
   hea->tipo=arcdes[i_arc].hea.tipo;
   
   point=p_des->mis;                         // punto alla prima misura
                                             // nel descrittore

	for(i_des=0,j_dbs=0;i_des<p_des->hea.n_mis;i_des++,point++)
	{
#if defined (DEBUG)
//   printf("mis %d ",i_des);
#endif
      p_dbs=ini_dbs+j_dbs;
		switch(point->ext)
		{
		case g1tipaa:	case g1tipas:	case g1tipac:  case g1tipad:					 
			if (!flagL)			// memorizzazione valore
			{	  if(tabmem[i_des]) arcana(point,p_dbs); }
			else					// memorizzazione media
			 {flag_dbs=arcave(point,p_dbs); trig_U=trig_A; }
         p_dbs->d.dtipo=p_dbs->d.dtipo & 0xFFFC;  // -1, -2, -3 riservati
 		break;
		case g1tipda: case g1tipds: case g1tipdc: case g1tipdd:
 	   if (tabmem[i_des])
	   {
			   p_dbs->d.dtipo=-1;
			   p_dbs->d.f_s=flag_dbs=arcdig(point);
/*
   nel caso di archiviazione lenta ad accumulo anche per i valori digitali
   setto il bit ST di stimato (per gli analogici vedi la routine arclen
*/
            if(flagL) bitset(&p_dbs->d.f_s,g2di_st,1);
            trig_U=trig_D;
#if defined (DEBUG)
//   printf(" dig %x ",p_dbs->d.f_s);
#endif
 	   }
		break;
		case g1tipor:
         trig_U=0;
		   if (tabmem[i_des])
 		   {
		      p_dbs->o.otipo=-2;
 		      p_dbs->o.f_s=dbosc[point->punt];
#if defined (DEBUG)
//   printf(" or %x ",p_dbs->d.f_s);
#endif
		   }
		break;
		case g1tipst:
         trig_U=0;
	      if (tabmem[i_des])
		   {
	  	   	p_dbs->d.dtipo=-3;
		      memcpy((char *)&p_dbs->d.f_s, 
				    	&dbstv[point->punt*g0lunst],g0lunst-1);   // escludo 0 finale
 		      j_dbs=j_dbs+2;		// il punto stringa occupa il posto di 3 misure
            p_dbs=p_dbs+2;
#if defined (DEBUG)
//   printf(" str %s ",p_dbs->d.f_s);
#endif
		   }
		break;
		default:
		break;	
 		}
/*
   se ho memorizzato aggirono il puntatore nel record j_dbs
   e se sono in archiviazione normale inserisco il n. progressivo
   nel record
*/
		if(tabmem[i_des])
      {
          if(!flagL) p_dbs->d.imis=i_des;
          j_dbs=j_dbs+1;
      }
/*
    se archivio "Lento/Veloce" 
*/
		if (flagL)
		{
           if(!flagT)  
            {
               flagT=arctrig(flag_dbs,trig_U);
               if(p_des->hea.t_mem==M_Par) tabmem[i_des]=flagT;
            }
            else  if(p_des->hea.t_mem==M_Par) 
                     tabmem[i_des]=arctrig(flag_dbs,trig_U);
		}
   }
/*
   inserisco il numero di misure archiviate (se archivio normale
   o in archiviazione lenta aggiorno n_mis altrimenti n_misvel)
*/
	if (arcdes[i_arc].hea.tipo==arc_Norm || flagL) hea->n_mis=j_dbs;
   else hea->n_misvel=j_dbs;
      
// se flagT=1, il trigger e' scattato archivio in modo normale

	if (flagT)	
	{	
 		flagL=0;
      flagT=0;
		ini_dbs=arcdbsN[i_arc]->dbs;
      hea=&arcdbsN[i_arc]->hea;
#if defined (DEBUG)
   printf("\n arch. vel.");
#endif
		goto INIZIO;
	}
/*
    Setting time out corrente per scrittura archivio
    solo se archiviazione normale o veloce
*/
   if(!flagL) 	t_N[i_arc].tco=t_N[i_arc].tin;
}
}













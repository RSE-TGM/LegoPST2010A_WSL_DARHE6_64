/**********************************************************************
*
*       C Source:               gdac.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Dec 16 12:05:38 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: gdac.c-3 %  (%full_filespec: gdac.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	il task gdac viene svegliato periodicamente
      	ogni secondo e provvede
	1. ad aggiornare le pagine video inviando
	   i dati con il messaggio vdasi
	2. ogni 10 sec. invia l'ora con il messaggio
	   vtime

	il tappo e` -1
	se il puntatore e` -2 si tratta della pagina allarmi
	caso digitale od organo bisogna saltare 6 bytes

	7 Settembre 1994 Fc.
	Modifica per gestione fine a 10 zone per compatibilita' com MMI-WIN

   14 Marzo 1994 Fc
   Inserita gestione ultimo allarme solo per sistemi con WINMMI
*/
#include <stdio.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include "messcada.inc"
#include	"mesqueue.h"
#include "diagnoan.inc"
#if defined OSF1 || defined LINUX
#include "diagnodi.inc"
#include "allstr.inc"
#endif
#include "pscs.cfg"
#include <all_1.h>
#include <string.h>

#define coeff_att 1
short cont_ora=1;
short gdac_sec;

/*
	struttura dei messaggi
*/
union u_messaggi {   S_VDASI   dmess;
	       	    		S_VTIME   omess; } mgadc;

float vsoglia();

// Function declarations
float fsoglia(short point, char tipo, char soglia);
void ter(void);
int bitvalue(short *buffer, short indice);
int alllast(char *buffer);

void gdac( )
{
S_ZONE *ptv ;

#define l_header 20

union valore { float fval;
	       long  lval ;
	       short sval[3];  /* 4 byte valore + 2 flag per an.*/
	       char  cval[g0lunst];} val;

char *p1,*p2;    /* puntatori per swapp */
short i,j,k,l,h ;
short ptipo, pdati ;
short ier,num ;
S_PUNT *scan ;
short soglia;
short dim;

QUEUE_PACKET pack;

pack.que = c_mmio;
pack.flg = MSG_WAIT;
pack.wto = 0;

#if 0
	if(gdac_sec == (short) dbadv[db_secondi]) ter();				// secondo non variato
	gdac_sec=dbadv[db_secondi];
#endif
/*
	esamino le tabelle video
	il decremento dei contatori e l'eventuale aggiornamento
	vengono eseguiti solo se l'input e` da data base
*/
for (j=0;j<num_video;j++)		/* per tutti i video */
{
for(i=0;i<n_zone;i++)			/* per tutte le zone */
{
	ptv= & tstv[j].tsv[i] ;
	if(ptv->v_input==inp_db)	/* se input e` da data base */
	{
	if(!(--ptv->v_cont))            /* se e` scaduto time_out   */
	{
/*
	la pagina deve essere aggiornata
*/
		ptv->v_cont=ptv->v_periodo * coeff_att ;

		mgadc.dmess.indice=vdasi;
      mgadc.dmess.zona=i+1 ;
		mgadc.dmess.video=j+1 ;
      mgadc.dmess.nodo=j;
		memcpy(&mgadc.dmess.pag[0],&ptv->v_pagina[0],10) ;
		h=0; 		    					/* indice di inserimento  messag.*/
		scan= & gdav[j][i*max_mis_zone] ;
		for(l=0; ;l++,scan++) 		/* ind. scans. puntatori 			*/
		{
		   if(scan->point == -1) break ;

/*
	se ext non e' 0 si tratta di una richiesta di soglie allarmi
*/
			if(scan->ext)
			{
				switch(scan->ext-1)
				{
					case m_anhs:  soglia=g1tiphs; break;
					case m_anls:  soglia=g1tipls; break;
					case m_anlc:  soglia=g1tiplc; break;
					case m_anhc:  soglia=g1tiphc; break;
				}
				val.fval=vsoglia(scan->point,scan->tipo,soglia);
				val.sval[2]=fsoglia(scan->point,scan->tipo,soglia);
				num=6;
			}
			else
			{
			ptipo=scan->tipo ;
			pdati=scan->point     ;
			switch (ptipo)
			{
			case -2 :				/* digitali e organi per pagina allarmi */
			val.lval=0xFFFFFFFF;
			num=6;
			break;

			case g1tipaa :   		/* an. acquisiti */
		   val.fval=dbaav[pdati];
		   val.sval[2]=dbaaf[pdati] ;
			num=6 ;break;

			case g1tipas :      /* an. cal st. */
			val.fval=dbasv[pdati];
			val.sval[2]=dbasf[pdati] ;
			num=6 ;break;

			case g1tipac :      /* an. cal n st*/
			val.fval=dbacv[pdati];
			val.sval[2]=dbacf[pdati] ;
			num=6 ;break;

			case g1tipad :      /* an. diagn . */
			val.fval=dbadv[pdati];
			val.sval[2]=dbadf[pdati] ;
			num=6 ;break;

			case g1tipao :      /* an. output. */
			val.fval=0;			  /* non ha senso il valore */
			val.sval[2]=dbaof[pdati] ;
			num=6 ;break;

			case g1tipda :		/* di. acquis. */
			num=1 ;
			mgadc.dmess.dati[h]=dbda[pdati] >> 8 ;
			break ;

			case g1tipds :		/* di. calcolati*/
			num=1 ;
			mgadc.dmess.dati[h]=dbds[pdati] >> 8 ;
			break ;

			case g1tipdc :		/* di. calc. ns*/
			num=1 ;
			mgadc.dmess.dati[h]=dbdc[pdati] >> 8 ;
			break ;

			case g1tipdd :		/* di. diagn. */
			num=1 ;
			mgadc.dmess.dati[h]=dbdd[pdati] >> 8 ;
			break ;

			case g1tipor :		/* organi     */
/*
	i valori per gli organi devono essere allineati
	alla word sempre
*/
			num=2 ;
			h=(h+1) & 0xFFFE ;  /* sempre pari */
			val.sval[0]=dbosc[pdati] ;
			break ;

			case g1tipst :      /* stringhe */
			h=(h+1) & 0xFFFE ;  /* sempre pari */
			memcpy(val.cval,&dbstv[pdati*g0lunst],g0lunst);
			num=g0lunst;
			break;
			}
			}
			p1=&val.cval[0] ;
			p2=&mgadc.dmess.dati[h] ;
			if(num != 1)memcpy(p2,p1,num) ;
			h=h+num ;
		}         /* fine do */
/*
	i bytes devono essere sempre pari
*/

		if( h % 2 ) h++ ;
		mgadc.dmess.num_dati=h ;

		pack.amsg = (char*) & mgadc.dmess;
		pack.lmsg= l_header+h ;
			
		enqueue(&pack) ;

	}
	}
}
}
if(--cont_ora) ter() ;
cont_ora= 2;                    /* mando giorno mese anno ora minuti*/
mgadc.omess.indice=vtime ;		/* secondi */

if(dbadv[db_anno]<1900) {ter();}

if(dbadv[db_anno]>=2000)
		mgadc.omess.anno=dbadv[db_anno]-2000;
else	mgadc.omess.anno=dbadv[db_anno]-1900;

mgadc.omess.mese=dbadv[db_mese];
mgadc.omess.giorno=dbadv[db_giorno];
mgadc.omess.ore=dbadv[db_ora];
mgadc.omess.minuti = dbadv[db_minuti];
mgadc.omess.secondi= dbadv[db_secondi];

#if defined OSF1 || defined LINUX
if(bitvalue(dbdd+stCicalino,g2di_sl))
	mgadc.omess.cicalino=tip_cic;
else
	mgadc.omess.cicalino=0;
#endif

#if defined (WINMMI)
   dim=alllast(((char*) &mgadc)+sizeof(S_VTIME));      // gestione ultimo allarme
#else
   dim=0;
#endif

pack.amsg = (char * ) & mgadc.omess;
pack.lmsg=sizeof(S_VTIME)+dim;
for(j=1;j<=num_video;j++)
{
   mgadc.omess.video=j ;
   mgadc.omess.nodo=j-1;
   enqueue(&pack);
}
ter() ;                
}



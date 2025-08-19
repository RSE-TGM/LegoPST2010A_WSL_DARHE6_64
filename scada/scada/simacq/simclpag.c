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
   Modulo:  SIMCLPAG.C

	     Richiama pagine Trend e Allarmi eventualmente visualizzate 
        in modo da reinizializzarle.

   17.11.92  -  Rel. 1.00  -  GM.Furlan

   27 Marzo 1995  Fc Porting 32Bit
      La funzione viene eseguita solo in caso di (AC_SIM_ENEL)
*/
#include <string.h>
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include	"mesqueue.h"
#include	"messcada.inc"
#include "simdia.inc"      // indirizzi in DB dei digitali di diagnostica per simulatore

void simclpag(clall, cltrd)
short clall;         // se 1: clear pagina allarmi
short cltrd;         // se 1: clear dei trend
{

short j,k;
S_VIDEO *ptstv;
S_ZONE  *ptv ;
union mess_out  { S_MCVAL mcval ; /* gestione allarmi  	              */
			      	S_VPAGV pag ;   /* richiesta pagina al micro         */
                } r ;
QUEUE_PACKET apack, tpack;

// coda pagine trend
	tpack.que = c_mmio;
	tpack.flg = MSG_WAIT;
	tpack.wto = 20;
	tpack.amsg=(char*)&r;
   tpack.lmsg=sizeof(S_VPAGV);

// coda pagine allarmi
	apack.que = c_cval;
	apack.flg = MSG_WAIT;
	apack.wto = 20;
	apack.amsg=(char*)&r;
   apack.lmsg=sizeof(S_MCVAL);

	ptstv=&tstv[0];
	for(j=0;j<num_video;j++,ptstv++)
	{
		ptv=&ptstv->tsv[0];
		for(k=0;k<n_zone;k++,ptv++)
		{
			if(ptv->v_pagina[0])
		   {
            // se clear dei trend
            if ( cltrd )
            {            
					if(ptv->v_tipo==trendo || ptv->v_tipo==trendv)		 // caso pagina trend
					{
						r.pag.zona=k+1;
						r.pag.video=j+1;
						r.pag.nodo=j;
						memset(r.pag.elen,-1,10);
						memcpy(r.pag.page,ptv->v_pagina,10);
						r.pag.input=inp_db;
						r.pag.indice=vpagv;
						enqueue(&tpack);
					}
				}
            // se clear pagina video
            if ( clall )
            {            
					if(ptv->v_tipo==p_al || ptv->v_tipo==p_ar)		 // caso pagina allarmi, archivio allarmi
					{
						r.mcval.video=j ;
						r.mcval.direz=0 ;
						r.mcval.zona=zonai ;
						r.mcval.indice=mpal;
						enqueue(&apack);
					}
   			}
			}
		}
	}
	r.mcval.indice=mall;
	enqueue(&apack);
}


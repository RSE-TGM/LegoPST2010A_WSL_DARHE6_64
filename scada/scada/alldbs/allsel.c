/**********************************************************************
*
*       C Source:               allsel.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Jan 29 15:45:06 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: allsel.c-3 %  (%full_filespec: allsel.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   allsel.c

   La routine esegue la selezione delle zone di impianto inserite
   nel messaggio msen con stringa $ALLARMI.
   Verifica che le zone di impianto siano comprese fra 0 e 31 e che
   la pagina allarmi richiesta sia definita.
	Il messaggio e' cosi' formato:
		  
	word 0		= -2	argomento intero
	word 1		n. data base allarmi da 1 a 6
   word 2      = -2  argomento intero
   word 3      codice pagina allarmi visualizzata
	word 4      = -2  argomento intero
	word 5		= 0 richiesta pagina allarmi
					= 1 richiesta pagina archivio
	word 6		= -2  argomento intero
	word 7		prima zona impianto selezionata (0-31)
	word 8		= -2 argomento intero
	word 9		seconda zona impianto selezionata  (0-31)
	......
	......
	word n		= -2 agomento intero
	word n+1		ennesima zona di impianto
	word n+2		= -1 tappo fine messaggio


   Parametri

   mess  short *     messaggio di selezione zone
	video	short			n. del video che ha richiesto la visualizzazione
							della pagina allarmi

   Ritorno

   0     short    visualizzare pagina allarmi
   1     short    visualizzare archivio allarmi
   -1    short    parametri non corretti richiesta non soddisfatta


   29 Maggio 1992    rel. 1.0    Fc.

   17 Ottobre 1994   rel. 1.1    Fc. (test su caso nessuna zona selezionata)
*/

#include "g2comdb.inc"
#include "messcada.inc"
#include "allar.inc"
#include "video.inc"

struct  sel_zon {
								short arg1;
							   short dbs;
                        short arg2;
                        short cod;
								short arg3;
								short pric;
								short arg4;
								short zona;
							} ;
			
allsel(mess,video)
struct sel_zon *mess;
short video;
{
S_DBS_ALL *all;
S_DBS_ALV *alv, *ali;
short *arg;
short mask[2], i;
/*
	verifico n. data base richiesto se compreso fra 1 e max_dbsall
	e se e' stato definita nel file fdesal.rtf
*/
if(mess->dbs<1 || mess->dbs>max_dbsall) return(-1);
all=&bDbsAll[mess->dbs-1];
if(!all->def) return(-1);

alv=&bDbsAlv[video-1];
/*
	resetto le maschere precedentemente selezionate ed inserisco
	le nuove specificate nel messaggio
*/
arg=&mess->arg4;
if(*arg==-1)
{
	mask[0]=alv->mask1;            // zone selezionate nessuna variazione
	mask[1]=alv->mask2;
}
else
{
	mask[0]=0;           // inizializzazione zone selezionate
	mask[1]=0;

   for(;(*arg)!=-1;)
   {
/*
		esamino la zona di impianto e verifico la correttezza
*/	
   	arg++; 
   	if((*arg)<0 || (*arg)>=max_zone) return(-1);	// non corretta
   	bitset(mask,*arg,1);
	   arg++;
   }
}
/*
   verifico che la pagina allarmi non sia gia' presente su altri
   video con lo stesso tipo di selezione
*/
ali=&bDbsAlv[0];
for(i=0;i<num_video;i++,ali++)
{
   if(i == (video-1)) continue;
   if(tstv[i].tsv[zonai].v_tipo != p_al && tstv[i].tsv[zonai].v_tipo != p_ar) continue;
   if(ali->pal == mess->dbs-1 && 
      ((ali->mask1 & mask[0]) || (ali->mask2 & mask[1]))) return(-1);
}
alv->pal=mess->dbs-1;             // data base selezionato
alv->mask1=mask[0];               // zone selezionate
alv->mask2=mask[1];               // zone selezionate
alv->cod=mess->cod;               // codice selezione
return(mess->pric);
}


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
	La routine esegue la selezione delle zone  e delle 
	gerarchie di impianto inserite nel messaggio msen 
	con stringa $ALLGERZO.
	Verifica che le zone di impianto siano comprese fra 
	0 e 31, che le gerarchie E (0-127, -3) e che
	la pagina allarmi richiesta sia definita.

	Il messaggio e' cosi' formato:
	word 0		-2 argomento intero
	word 1		data base allarmi da 1 a 6
	word 2		-2  argomento intero
	word 3		codice pagina allarmi 
	word 4		-2  argomento intero
	word 5		0=pagina allarmi 1=pagina archivio
	word 6		-2 argomento intero
	word 7		1a gerarchia selezionata
	word 8		-2 argomento intero
	word 9		2a gerarchia selezionata
	word 10		-2 argomento intero
	word 11		3a gerarchia selezionata
	word 12		-2 argomento intero
	word 13		4a gerarchia selezionata
	word 14		-2 argomento intero
	word 15		5a gerarchia selezionata
	word 16		-2 argomento intero
	word 17		6a gerarchia selezionata
	word 18		-2 argomento intero
	word 19		1a zona impianto selezionata (0-31)
	word 20		-2 argomento intero
	word 21		2a zona impianto selezionata (0-31)
	......
	......
	word n		-2 agomento intero
	word n+1	ennesima zona di impianto
	word n+2= 	-1 tappo fine messaggio

	Parametri:
	S_SELGERZO *mess	messaggio di selezione gerarchie e zone 
	short	video	n. del video che visualizza la pagina allarmi

	Ritorno:
	 0     visualizzare pagina allarmi
	 1     visualizzare archivio allarmi
	-1     parametri non corretti richiesta non soddisfatta
*/

#include <osf1.h>

#include "g0gerdb.inc"
#include "g2comdb.inc"
#include "messcada.inc"
#include "allar.inc"
#include "video.inc"

// External function declarations
extern void bitset(short* buffer, short indice, short bit);

#ifdef GERARC
typedef struct  s_selgerzo {
				short arg1;
				short dbs;
                        	short arg2;
                        	short cod;
				short arg3;
				short pric;
				short arg4;
				short ger1;
				short arg5;
				short ger2;
				short arg6;
				short ger3;
				short arg7;
				short ger4;
				short arg8;
				short ger5;
				short arg9;
				short ger6;
				short arg10;
				short zona;
		       	   }S_SELGERZO;
			
int allgerzo(mess,video)
S_SELGERZO *mess;
short video;
{
S_DBS_ALV *alv,*ali;
short *arg;
short mask[2],i;
char *pger;

/* Data base compreso fra 1 e max_dbsall e definito in fdesal.rtf */
if(mess->dbs<1 || mess->dbs>max_dbsall) 
{
	printf("[allgerzo.c] Indice data base impossibile \n");
	return(-1);
}
if(!bDbsAll[mess->dbs-1].def) 
{
	printf("[allgerzo.c] Data base non definito \n");
	return(-1);
}

alv=&bDbsAlv[video-1];
arg=&mess->arg10;

/* Zone selezionate nessuna variazione */
if(*arg==-1)
{
	mask[0]=alv->mask1; 
	mask[1]=alv->mask2;
}
/* Resetto le maschere precedentemente selezionate ed inserisco
   le nuove specificate nel messaggio			        */
else
{
	mask[0]=0;
	mask[1]=0;

   	for(;(*arg)!=-1;)
   	{
		/* Esamina zona e verifica correttezza */	
   		arg++; 
   		if((*arg)<0 || (*arg)>=max_zone)
		{
			printf("[allgerzo.c] Zona impossibile \n");
			return(-1);
		}
   			bitset(mask,*arg,1);
	   	arg++;
   	}
}

/* Verifica che la pagina allarmi non sia gia' presente su altri
   video con lo stesso tipo di selezione                         */
ali=&bDbsAlv[0];
for(i=0;i<num_video;i++,ali++)
{
	if(i == (video-1)) continue;
	if(tstv[i].tsv[zonai].v_tipo != p_al && tstv[i].tsv[zonai].v_tipo != p_ar) continue;
	if(ali->pal == mess->dbs-1 && ((ali->mask1 & mask[0]) || (ali->mask2 & mask[1]))) 
	{
		printf("[allgerzo.c] Pagina allarmi gia presente \n");
		return(-1);
	}
}

/* Decodifica gerarchie selezionate */
arg=&mess->arg4;
for(i=0,pger=alv->abgera+n_gerarchie-1;i<n_gerarchie;i++,pger--)
{
	/* Esamina gerarchia e verifica correttezza */	
	arg++;
	if((*arg<0 && *arg!=ger_default) || *arg>=n_liv_gerarchie) 
	{
		printf("[allgerzo.c] Gerarchia errata %d\n",*arg);
		return(-1);
	}
	*pger=*arg;
	arg++;
}
 
alv->pal=mess->dbs-1;             /* Data base selezionato */
alv->mask1=mask[0];               /* Zone selezionate */
alv->mask2=mask[1];               /* Zone selezionate */
alv->cod=mess->cod;               /* Codice seleziono */

return(mess->pric);
}
#endif

/**********************************************************************
*
*       C Source:               allinger.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Jul 25 17:43:58 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: allinger.c-4 %  (%full_filespec: allinger.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	Determina se un allarme soddisfa la gerarchia impostata
	dalla chiamata da pagina video send(...).

	Parametri:
	S_MALLA *pMalla;	punto nel database allarmi
	S_DBS_ALV *pAlv;	tabella del video corrente

	Ritorno:
	puntatore a gerarchia	il punto soddisfa la gerarchia;
	0	il punto non soddisfa la gerachia.
*/

#include <osf1.h>
#include <string.h>
#include <stdio.h>

#include "messcada.inc"
#include "allar.inc"
#include "g1tipdb.inc"
#include "g2comdb.inc"

#ifdef GERARC
/*
Viene aggiunto un parametro in piu' che restituisce la gerarchia dell' all.

Modificato da Fabio.
*/

short allinger(S_MALLA *pMalla,S_DBS_ALV *pAlv,char *gerarchia)
{

short i;
char *pcGerar,*pcPuntGerar;
pcGerar=pAlv->abgera;

switch(pMalla->ext)
{
	/* analogici acquisiti */
	case g1tipaa:
		pcPuntGerar=(char *)&dbaag[pMalla->punt];
		break;

	/* analogici calcolati non standard */
	case g1tipac:
		pcPuntGerar=(char *)&dbacg[pMalla->punt];
		break;

	/* analogici calcolati standard */
	case g1tipas:
		pcPuntGerar=(char *)&dbasg[pMalla->punt];
		break;

	/* analogici di diagnostica */
	case g1tipad:
		pcPuntGerar=(char *)&dbadg[pMalla->punt];
		break;

	/* analogici di uscita */
	case g1tipao:
		pcPuntGerar=(char *)&dbaog[pMalla->punt];
		break;

	/* digitali  acquisiti */
	case g1tipda:
		pcPuntGerar=(char *)&dbdag[pMalla->punt];
		break;

	/* digitali  calcolati standard */
	case g1tipds:
		pcPuntGerar=(char *)&dbdsg[pMalla->punt];
		break;

	/* digitali  calcolati non standard */
	case g1tipdc:
		pcPuntGerar=(char *)&dbdcg[pMalla->punt];
		break;

	/* digitali  di diagnostica */
	case g1tipdd:
		pcPuntGerar=(char *)&dbddg[pMalla->punt];
		break;

	/* digitali  di uscita */
	case g1tipdo:
		pcPuntGerar=(char *)&dbdog[pMalla->punt];
		break;

	/* organi */
	case g1tipor:
		pcPuntGerar=(char *)&dbog[pMalla->punt];
		break;

	/* stringhe */
	case g1tipst:
		pcPuntGerar=(char *)&dbstg[pMalla->punt];
		break;
	default:
		fprintf(stderr,"[allinger.c] tipo punto sconosciuto.\n");
		return 0;
}
if(gerarchia)
	{
	memcpy(gerarchia,pcPuntGerar,n_gerarchie);
/*
debug
*/
/*
	printf("Sto per stampare gerarchia all\n");
	printf("********************************\n");
for(i=0;i<n_gerarchie;i++)
	printf("|%d",pcPuntGerar[i]);
	printf("\n********************************\n");
*/

	}
for(i=0;i<n_gerarchie;i++,pcGerar++,pcPuntGerar++)
	{
	if(*pcGerar!=*pcPuntGerar && *pcGerar!=ger_default) return(0);
	}

return (1);
}
#endif

/**********************************************************************
*
*       C Source:               racdbs.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Dec 16 12:06:41 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: racdbs.c-4 %  (%full_filespec: racdbs.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/* ->RACDBS.C
 *		Raccoglie da data base di sistema a data base locale i punti
 *	   specificati nell'area dati	di FTAB.RTF
 *    In ingresso riceve l'indirizzo del buffer contenente l'area
 * 	dati di FTAB.RTF (che coincide con l'indirizzo dell'header
 *		dell'area dati) e l'indirizzo del data base locale.
 * 	Legge in DBS i valori delle variabili di link e li copia
 *	   in DBL.
 */
#include <osf1.h>
#include <string.h>
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "fileop.inc"

void racdbs(HEAD_DATAB *hdat, char *dbl)
{
short i;
struct punto { short ext;   // estensione punto di data base di sistema.				  
               short punt;   // puntatore     ,,        ,,              .
			     }*pdbs;
#define dim_pun sizeof(struct punto)
struct puntloc	{ unsigned short addr:11;
					  unsigned short bit:3;
					  unsigned short z:2;
					}*pdbl;

short *psh;		 // puntatori di servizio utilizzati per il trasf. dbs -> dbl
float *pfl;

// punta al primo puntatore in dbs
pdbs=(struct punto *)((char *)hdat+l_hdat);

// punta al primo puntatore in dbl
pdbl=(struct puntloc *)((char *)hdat+l_hdat+(hdat->n_link)*dim_pun);

/*
	raccoglie i valori delle variabili di link
*/
for(i=0;i<hdat->n_link;i++)
	{
	switch(pdbs->ext)
		{
		case g1tipaa:
			pfl=(float *)&dbl[pdbl->addr];
			psh=(short *)(&dbl[pdbl->addr]+sizeof(float));
//			printf("\nRACDBS"); 
//			printf("\n\n puntatore in dbl:%d    puntatore in dbs:%d",pdbl->addr,pdbs->punt); 
#if !defined OSF1 && !defined LINUX
			(*pfl)=dbaav[pdbs->punt];
#else
			memcpy(pfl,&dbaav[pdbs->punt],sizeof(float));
#endif
			(*psh)=dbaaf[pdbs->punt];
			break;

		case g1tipas:
			pfl=(float *)&dbl[pdbl->addr];
			psh=(short *)(&dbl[pdbl->addr]+sizeof(float));
#if !defined OSF1 && !defined LINUX
			(*pfl)=dbasv[pdbs->punt];
#else
			memcpy(pfl,&dbasv[pdbs->punt],sizeof(float));
#endif
			(*psh)=dbasf[pdbs->punt];
			break;

		case g1tipac:
			pfl=(float *)&dbl[pdbl->addr];
			psh=(short *)(&dbl[pdbl->addr]+sizeof(float));
#if !defined OSF1 && !defined LINUX
			(*pfl)=dbacv[pdbs->punt];
#else
			memcpy(pfl,&dbacv[pdbs->punt],sizeof(float));
#endif
			(*psh)=dbacf[pdbs->punt];
			break;

		case g1tipad:
			pfl=(float *)&dbl[pdbl->addr];
			psh=(short *)(&dbl[pdbl->addr]+sizeof(float));
#if !defined OSF1 && !defined LINUX
			(*pfl)=dbadv[pdbs->punt];
#else
			memcpy(pfl,&dbadv[pdbs->punt],sizeof(float));
#endif
			(*psh)=dbadf[pdbs->punt];
			break;

		case g1tipda:
			psh=(short *)&dbl[pdbl->addr];
			*((char*)psh)=*((char*)&dbda[pdbs->punt]+1);
			break;

		case g1tipds:
			psh=(short *)&dbl[pdbl->addr];
			*((char*)psh)=*((char*)&dbds[pdbs->punt]+1);
			break;

		case g1tipdc:
			psh=(short *)&dbl[pdbl->addr];
			*((char*)psh)=*((char*)&dbdc[pdbs->punt]+1);
			break;

		case g1tipdd:
			psh=(short *)&dbl[pdbl->addr];
			*((char*)psh)=*((char*)&dbdd[pdbs->punt]+1);
			break;

		case g1tipor:
			psh=(short *)&dbl[pdbl->addr];
			(*psh)=dbosc[pdbs->punt];
			break;

#if defined (g1tipst)
		case g1tipst:
			psh=(short *)&dbl[pdbl->addr];
			memcpy((char*) psh, (char*) & dbstv[pdbs->punt*g0lunst],g0lunst);
			break;
#endif
		}
	pdbs++;
	pdbl++;
	}
}

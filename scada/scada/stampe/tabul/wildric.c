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
/*	 -> WILDRIC.C
        la subroutine wildric verifica l'esistenza di un punto
        data la sigla pbuf sul file fnomi
		  La ricerca viene effettuata sequenzialmente; per confrontare
		  la sigla con la sigla contenente i wild characters viene 
		  utilizzata la funzione wilstrcmp riportata in questo stesso
		  file.
        il ritorno =0 se il punto e'stato trovato
                   =1 se il punto non e' stato trovato
*/
#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include <tag.h>
#include "gpunt.inc"
#include "g0strdb.inc"
#include "fileop.inc"
#include "mesprocv.inc"

// External function declarations
extern int rbyte(int, short *, long, int);
extern void wai(int);

// Forward declarations
int wildstrcmp(char *, char *);

/* 
	per la bufferizzazione viene utilizzato il buffer r_tamp definito
	per la routine RICERCA
*/
extern short r_tamp[SCD_FATBLK/2];	

int wildric(short *pbuf, short *point, short *ext, char bFirst, FILE *fp)
{
static long blocco;	// blocco a cui si e' arrivati nella
							// ricerca sequenziale
static short posiz;	// posizione all'interno del blocco
							// a cui si e' arrivati
char AppStr[SCD_SIGLA+1];

AppStr[SCD_SIGLA]=0;
if(bFirst)
	{
	blocco=0;
	posiz=SCD_BLK_OVER_FLOW;
	}
// caso di fine scansione
if(blocco==BLK_TOT) return(1);
for(;;)
	{
	rbyte(fileno(fp),r_tamp,blocco*SCD_FATBLK,SCD_FATBLK) ;
	while(posiz<(SCD_FATBLK/2))
		{
		strncpy(AppStr,(char*)&r_tamp[posiz],SCD_SIGLA);
		if(AppStr[0])				// stringa non nulla
			{
			if(!wildstrcmp(AppStr,(char*)pbuf))   /* trovata stringa */
				{
         	*point=r_tamp[posiz+SCD_SIGLA/2];
	         *ext =r_tamp[posiz+SCD_SIGLA/2+1];
				posiz+=SCD_RECORD;
				return(0);
				}
			}
		posiz+=SCD_RECORD;
		}
/*
	finito di esaminare il blocco: passa al blocco successivo
*/
	if(blocco<BLK_TOT)   
		{
		blocco++;
		wai(10);
		posiz=SCD_BLK_OVER_FLOW;
		}
	else
/*
	esaminati tutti i blocchi
*/
		return(1);
	}
}



/* -> wildstrcmp
        confronta una stringa con una stringa contenente wildcharacters;
		  ritorna 0 se la stringa contiene tutti i caratteri contenuti nella
							stringa con wildcharacters (esclusi i wildcharacters 
							stessi) e le posizioni di tali caratteri all'interno
							delle due stringhe sono corrispondenti.
		  ritorna 1 altrimenti


  Algoritmo: a) suddivide la stringa con wild characters in N (max.5)
					 sottostringhe non contenenti wild characters conservandone
					 le posizioni relative all'inizio della stringa.
				 b) verifica nella stringa da confrontare che siano presenti
					 tutte le sottostringhe e che le loro posizioni siano 
					 congruenti a quelle trovate per la stringa con wildch.

*/


int wildstrcmp(char *str, char *wildstr)
{
short i;
/*
	esce con stringhe diverse se la loro lunghezza e' diversa
*/
if(strlen(str)!=strlen(wildstr)) return(1);

for(i=0;i<strlen(str);i++)
{
	if(wildstr[i]==WILDCHAR) continue;
	if(wildstr[i]!=str[i]) return(1);
}
return(0);
}



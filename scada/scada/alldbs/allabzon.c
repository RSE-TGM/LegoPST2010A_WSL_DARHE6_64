/**********************************************************************
*
*       C Source:               allabzon.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Jul 25 17:43:51 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: allabzon.c-6 %  (%full_filespec: allabzon.c-6:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
                                                                                                                                             /*
   abzon.c

   La funzione data la maschera su 4 byte prepara la struttura
   S_ABIL_ZONE settando a 1 il byte corrispondente alle zone
   abilitate e calcolando il n. di allarmi da riconoscere e 
   riconosciuti.

   Parametri

   mask1    short*         maschera zone da 0 a 15
   mask2    short*         maschera zone da 16 a 32
   aldb     short          n. del data allarmi

   Ritorno

   modifica la struttura abzone  definita in allstr.inc

   nessuno

   22 Maggio 1992    Rel. 1.0    Fc
   Febbraio  1996    Aggiunta versione a 4 parametri per la gestione delle gerarchie.
		     ATTENZIONE! le modifiche fatte alla versione a tre parametri
		     essere riportate anche a quella a quattro.

*/
#include <stdio.h>
#include <string.h>

#include "messcada.inc"
#include "allar.inc"
S_ALL_PER_ZONE allxzone;

extern int bitvalue(void *, int);
extern int allinger(void *, void *, void *);

#ifndef GERARC
abzon(mask1,mask2,aldb)
short *mask1,*mask2,aldb;
{
short i,j;
short *mask;
char *zona;
S_DBS_ALU *alu;

alu=&bDbsAlu[0];
abilzo.n_al=0;        // allarmi da riconoscere =0
abilzo.n_ar=0;        // allarmi in archivio = 0

zona=&abilzo.abil_zone[0];
for(j=0,mask=mask1;j<2;mask=mask2,j++)
{
   for(i=0;i<16;i++,zona++,alu++)
   {
      if(bitvalue(mask,i)) *zona=1;
      else                 *zona=0;
      if(*zona) 
      {
         abilzo.n_al=abilzo.n_al+alu->n_al[aldb];
         abilzo.n_ar=abilzo.n_ar+alu->n_ar[aldb];
      }
   }
}
return(0);
}
#else
int abzon(mask1,mask2,aldb,gerarchie)
short *mask1,*mask2,aldb;
char *gerarchie;
{
short i,j;
short *mask,appMask;
char *zona;
S_DBS_ALU *alu;
struct buff_all *pall;
char gdefault[n_gerarchie]={-1,-1,-1,-1,-1,-1};

abilzo.n_al=0;
abilzo.n_ar=0;
alu=bDbsAlu;
zona=abilzo.abil_zone;

/* Gerarchia selettiva -> fa  test sulle zone */
if(!memcmp(gerarchie,gdefault,n_gerarchie))
{
	for(j=0,mask=mask1;j<2;mask=mask2,j++)
	   	for(i=0;i<16;i++,zona++,alu++)
	   	{
	      		if(bitvalue(mask,i)) *zona=1;
	      		else                 *zona=0;
	      		if(*zona)
	      		{
/*				allxzone.n_all_pen[i]=alu->n_al[aldb];
				allxzone.n_all_arc[i]=alu->n_ar[aldb];
*/
/*
				printf("gerarchie default:zona=%d\n",i);
				printf("n_all_pen[i]=%d\n",allxzone.n_all_pen[i]);
				printf("n_all_arc[i]=%d\n",allxzone.n_all_arc[i]);
*/
	         		abilzo.n_al+=alu->n_al[aldb];
	         		abilzo.n_ar+=alu->n_ar[aldb];
	      		}
/*
N.B.
il ciclo for (..;i<16...) viene eseguito due volte
quindi devo usare j+1
*/
			 allxzone.n_all_pen[i+(j*16)]=alu->n_al[aldb];
                         allxzone.n_all_arc[i+(j*16)]=alu->n_ar[aldb];
	   	} /* end for(i=0;i<16) */
}
else
{
        for(j=0,mask=mask1;j<2;mask=mask2,j++)
        	for(i=0;i<16;i++,zona++,alu++)
        	{
          	 	if(bitvalue(mask,i)) *zona=1;
              		else                 *zona=0;
        	}

        for(pall=bDbsAll[aldb].pall,j=0;j<bDbsAll[aldb].pout;j++,pall++)
	{
		appMask=pall->mask & ~0x8000;
		if(bitvalue(mask1,appMask) && allinger(&pall->m,&bDbsAlv[bDbsAll[aldb].video],NULL))
		{
			printf("Gerarchia non default\n");
			if(pall->mask & 0x8000)
				{
				printf("Incremento n_ar\n");
	         		abilzo.n_ar++;
				}
			else
				{
				printf("Incremento n_al\n");
	         		abilzo.n_al++;
				}
		}
	}
}
return(0);
}
#endif



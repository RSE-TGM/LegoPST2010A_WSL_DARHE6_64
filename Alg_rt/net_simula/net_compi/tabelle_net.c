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
static char SccsID[] = "@(#)tabelle_net.c	5.1\t11/7/95";
/*
   modulo tabelle_net.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)tabelle_net.c	5.1
*/
#include "sim_param.h"
#include "sim_types.h"

extern SCAMBIO scambio[MAX_MODEL][MAX_DT_DEC];
extern COLLEGAMENTO collegamento[MAX_MODEL][MAX_MODEL];
extern S02 s02_;

tabelle_net(
 int nmod,
 int nrip)
{
/*
int i, j, dt_millisec;
for (i=0; i<nmod; i++) {
  dt_millisec=model[i].dt*1000.;
  for (j=0; j<nrip; j++)
    if (j*100%dt_millisec == 0)
      tabel[i].inst[j]=1;
  }*/

int i,i1,j,j1;

/* ricerca per i write */
for (i=0; i<nmod; i++) 
{
   for (j=0; j<nrip; j++)
   {
      if(s02_.tabel[i].inst[j])
       {
         for(i1=0; i1<nmod;i1++)
          {
           if(i1!=i) 
           for(j1=j; j1<=(j+(int)(s02_.model[i].dt*10)-1); j1++)
	       {
                  if((s02_.tabel[i1].inst[j1])&&
			(collegamento[i1][i].numero_collegamenti))
                        {
			scambio[i][j].write[i1]=1;
			}

	       }
          }
       }
   }
}
/* riassunto write  */
/*
for (i=0; i<nmod; i++) 
{
   for (j=0; j<nrip; j++)
   {
   for (i1=0; i1<nmod; i1++)
      if(scambio[i][j].write[i1])
       printf("dt=%d  %d->%d\n",j,i,i1);
   }
}
*/

/* ricerca per read  */
for (i=0; i<nmod; i++)
{
   for (j=(nrip-1); j>=0; j--)
   {
      if(s02_.tabel[i].inst[j])
       {
         for(i1=0; i1<nmod;i1++)
          {
           if(i1!=i)
           for(j1=j; j1>=(j-(int)(s02_.model[i].dt*10)+1); j1--)
               {
                  if((s02_.tabel[i1].inst[j1])&&
			(collegamento[i][i1].numero_collegamenti))
                        {
                        scambio[i][j].read[i1]=1;
                        }

               }
          }
       }
   }
}
/* riassunto read */
/*
printf("processi di read\n");
for (i=0; i<nmod; i++)
{
  printf("task %d\n",i);
   for (j=0; j<nrip; j++)
   {
   for (i1=0; i1<nmod; i1++)
      if(scambio[i][j].read[i1])
       printf("dt=%d  %d<-%d\n",j,i,i1);
   }
}
*/
} /* FINE "tabella_net.c" */

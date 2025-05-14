/**********************************************************************
*
*       C Source:               co_snap.c
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 12:27:12 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: co_snap.c-4 %  (%full_filespec: co_snap.c-4:csrc:1 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)co_snap.c	5.1\t11/7/95";
/*
   modulo co_snap.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)co_snap.c	5.1
*/
#include <stdio.h>
#include <stdlib.h>
# include "sim_param.h"
# include "sim_types.h"
# include "libnet.h"

/* 
   Inserisce il flag di modificato nel file di snapshot 
   Per l'attribuzione del parametro _MAX_SNAP_SHOT ci si basa
   sulla lettura del file nella parte di header.
*/
void co_snap()
{
FILE *fp;
SNTAB *snapshot;
int i;
int app_int=1;
HEADER_REGISTRAZIONI hreg_snap;
int _MAX_SNAP_SHOT;


  printf("Lettura file snapshot.dat\n");
  if((fp=fopen("snapshot.dat","r"))!=NULL)
 	{
	fclose(fp);
	fp=fopen("snapshot.dat","r+");
/*      Lettura del nuovo header */
        fread(&hreg_snap,sizeof(HEADER_REGISTRAZIONI),1,fp);
        _MAX_SNAP_SHOT = hreg_snap.simulator.max_snap_shot;
        printf("\t co_snap ha letto _MAX_SNAP_SHOT=%d\n",_MAX_SNAP_SHOT);
	snapshot=(SNTAB*)calloc(_MAX_SNAP_SHOT,sizeof(SNTAB));
	fread(&snapshot[0],sizeof(SNTAB),_MAX_SNAP_SHOT,fp);
	for(i=0;i<_MAX_SNAP_SHOT;i++)
                {
/*
                printf("co_snap prg=%d stat=%d pos=%d mod=%d %s dat=%s t=%s\n",
                        snapshot[i].prog,  snapshot[i].stat,
                        snapshot[i].pos,   snapshot[i].mod,
                        snapshot[i].descr, snapshot[i].datasn,
                        snapshot[i].temposn);
*/
		if(snapshot[i].stat==1)
			snapshot[i].mod=1;
                }
	fseek(fp,sizeof(HEADER_REGISTRAZIONI),0);
	fwrite(&snapshot[0],sizeof(SNTAB),_MAX_SNAP_SHOT,fp);
	fclose(fp);
	free(snapshot);
	}
}

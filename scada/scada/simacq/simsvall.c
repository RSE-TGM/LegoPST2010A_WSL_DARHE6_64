/**********************************************************************
*
*       C Source:               simsvall.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 31 12:23:02 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: simsvall.c-3 %  (%full_filespec: simsvall.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	Modulo:  SIMSVALL.C
            Save/Restore su/da file ALLAR.SAV degli allarmi

   Parametri: short opz: flag operazione voluta: 

   03.08.92  -  Rel. 1.0  - GM.Furlan

   27 Marzo 1995 Fc Porting a 32Bit
*/

#include <osf1.h>
#include <stdio.h>
#include "messcada.inc"
#include "allar.inc"
#include "dconf.inc"
#include "simula.inc"
#include "pscserr.inc"


simsvall(opz)
short opz;     // opz=SAVE: salva Allarmi; opz=RESTORE: ripristino Allarmi
{

FILE *fp;
char filename[FILENAME_MAX+1];
short i,j;
short *ppall;
long offset;

strcpy(filename,conf[RTF]);
#if defined OSF1 || defined LINUX
strcat(filename,"/allar.sav");
#else
strcat(filename,"\\allar.sav");
#endif

switch (opz)
{
   case SAVE:      // salvataggio allarmi su ALLAR.SAV
      fp=fopen(filename,"wb");
      if(fp==NULL)
	   {
			// errore apertura file ALLAR.SAV
         pscserr(ERR_IO,TASK_SIMACQUI,ROU_SVALL,0,SYS_CONT);
			return(-1);
		}
      offset=(long)0;
      wbyte(fileno(fp),(short*)bDbsAll,offset,max_dbsall*sizeof(S_DBS_ALL));	  
      offset=offset+(long)(max_dbsall*sizeof(S_DBS_ALL));
      for(i=0;i<max_dbsall;i++)
      {
         if ((ppall=(short*)bDbsAll[i].pall)!=NULL)
         {
            wbyte(fileno(fp),ppall,offset,bDbsAll[i].dim*sizeof(struct buff_all));	  
            offset=offset+(long)(bDbsAll[i].dim*sizeof(struct buff_all));
         }
      }
      wbyte(fileno(fp),(short*)bDbsAlu,offset,max_zone*sizeof(S_DBS_ALU));	  
   break;
   
   case RESTORE:     // restore allarmi da ALLAR.SAV   
      fp=fopen(filename,"rb");
      if(fp==NULL)
	   {
			// errore apertura file ALLAR.SAV
         pscserr(ERR_IO,TASK_SIMACQUI,ROU_SVALL,0,SYS_CONT);
			return(-1);
		}
      offset=(long)0;
      rbyte(fileno(fp),(short*)bDbsAll,offset,max_dbsall*sizeof(S_DBS_ALL));	  
      offset=offset+(long)(max_dbsall*sizeof(S_DBS_ALL));
      for(i=0;i<max_dbsall;i++)
      {
         if ((ppall=(short*)bDbsAll[i].pall)!=NULL)
         {
            rbyte(fileno(fp),ppall,offset,bDbsAll[i].dim*sizeof(struct buff_all));	  
            offset=offset+(long)(bDbsAll[i].dim*sizeof(struct buff_all));
         }
      }
      rbyte(fileno(fp),(short*)bDbsAlu,offset,max_zone*sizeof(S_DBS_ALU));	  
   break;
}
fclose(fp);

return(0);	
}


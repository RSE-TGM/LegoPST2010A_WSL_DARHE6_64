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
#include "paglib.h"


static short ID;

PagIniDos1()
   {
   printf("\nInizializzazione DOS\n");
   }

TOKEN p1,p2,p3,pd1;

PagIniMarte1(short id)
   {
   ID=id;
   printf("\nInizializzazione Marte\n");
   if((p1=CnvTag("ICORREZ1A"))==-1)
      {
      printf("\nerrore in decodifica punto1\n");
      }
   if((p2=CnvTag("ICORREZ2A"))==-1)
      {
      printf("\nerrore in decodifica punto2\n");
      }
   if((p3=CnvTag("ICORREZ3A"))==-1)
      {
      printf("\nerrore in decodifica punto3\n");
      }
   if((pd1=CnvTag("STEP1"))==-1)
      {
      printf("\nerrore in decodifica punto3\n");
      }
   }

PagCorpo1()
   {
   short flag1,flag2,flag3;
   float v1,v2,v3;
   WaitForTimeout(20);
   F1();

/*
   WaitForEvent(0,1,&pd1);
   ReadDb(p1,&flag1,&v1);
   ReadDb(p2,&flag2,&v2);
   flag3 =(flag1 | flag2) & AN_FA;
   v3=v1+v2;
   WriteDb(p3,flag3,v3);
   */
   }

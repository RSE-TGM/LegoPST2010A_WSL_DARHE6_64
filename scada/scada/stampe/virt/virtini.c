/**********************************************************************
*
*       C Source:               virtini.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 31 14:06:44 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: virtini.c-4 %  (%full_filespec: virtini.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	VIRTINI.C
	
	Contiene la routine	leggifile() che inizializza le stampanti virtuali sulla 
	base del file di figurazione FVIRTPRN.RTF.

	Nessun parametro.
	Nessun valore restituito.
	
	Data di creazione:		12.6.1995
	Autore:					E.L.

   6 Settembre 1995
   Inserita lettura nome server per stampante remota e separazione
   fra n. linea stampante locale e remota
*/

#include <osf1.h>
#include <string.h>
#include <stdio.h>

#include "print.inc"
#include "pscserr.inc"
#include "virtinv.h"
#include "dconf.inc"
#include "g2comdb.inc"
#include "diagnodi.inc"

// External function declarations
extern void pscserr(int, int, int, int, int);
extern void bitset(short *, short, short);
extern void IniLine(void *);

int addrbb[2]={0x208,0x220};

char IsComment(char *pch);

void leggifile(void)
{
	// Dichiarazioni
	FILE *fp;
	char chBuffer[FILENAME_MAX+1], chApp[FILENAME_MAX+1], *pch;
	short i, shZona;
   short linea, data, bit;
   static char dig_prn[]={stprn1,stprn2,stprn3,stprn4,stprn5,stprn6,stprn7,stprn8};
   short lineal, linear;
   lineal=linear=0;           // n. linea locale e remota

	memset(fisdev,-1,n_fis*sizeof(S_PFIS));

	memset(virtprn,0,sizeof(virtprn));
	for(i=0;i<n_virt_lbg+n_virt_tab;i++)
   {
      memset(virtprn[i].indice,-1,n_DevFis*2);
      virtprn[i].DFileU=pDiaU+i;
      virtprn[i].DFileP=pDiaP+max_n_allfile*i;
   }

   // Apertura del file
	memset(chBuffer,0,FILENAME_MAX+1);
	strcpy(chBuffer,conf[RTF]);
	strcat(chBuffer,FVIRTPRN);
	if(!(fp=fopen(chBuffer,"r+")))
		pscserr(ERR_IO,ROU_LEGGIFIL,FILE_STRAT,0,SYS_HALT_DOS);
    
    // Scandisce tutto il file
	for(;fgets(chBuffer,FILENAME_MAX,fp);)
	{
		if(IsComment(chBuffer))
			continue;
			
		sscanf(chBuffer,"%s",chApp);
		
		if(!strcmp(chApp,"BEGIN_FIS_PER"))
			for(i=0;fgets(chBuffer,FILENAME_MAX,fp) && i<n_fis; i++)
			{
				if(IsComment(chBuffer))
					continue;

				sscanf(chBuffer,"%s",chApp);
				if(strcmp(chApp,"END_FIS_PER"))
				{
					fisdev[i].remota=-1;
   				sscanf(chBuffer,"%hd %s",&linea,chApp);
					if(!strcmp(chApp,"PRNR"))
               {
						fisdev[i].remota=1;
   					sscanf(chBuffer,"%hd %s %s",&linea,chApp,&fisdev[i].remname);
      		   	fisdev[i].linea=linear;
                  linear++;
               }
					else if(!strcmp(chApp,"PRNL"))
               {
						fisdev[i].remota=0;
   					sscanf(chBuffer,"%hd %s %hd %hd %hd %c",&linea,chApp,&fisdev[i].baud,&data,
						  &bit,&fisdev[i].parity);
      		   	fisdev[i].linea=lineal;
		   			fisdev[i].data=data;
                  fisdev[i].stbit=bit;
                  lineal++;
               }
#if defined OSF1 || defined LINUX
					else if(!strcmp(chApp,"PRNX"))
               {
						fisdev[i].remota=0;
   					sscanf(chBuffer,"%hd %s %hd %hd %hd %c",&linea,chApp,&fisdev[i].baud,&data,
						  &bit,&fisdev[i].parity);
      		   	fisdev[i].linea=lineal;
		   			fisdev[i].data=data;
                  fisdev[i].stbit=bit;
		  strcpy(fisdev[i].remname,"XTERM");
                  lineal++;
               }
					else if(!strcmp(chApp,"QUEUE"))
               {
						fisdev[i].remota=0;
   			sscanf(chBuffer,"%hd %s %s",
				&linea,chApp,&fisdev[i].remname);
			sprintf(fisdev[i].remname,"QUEUE_%s",fisdev[i].remname);
      		   	fisdev[i].linea=lineal;
                  lineal++;
               }
#endif
   		      fisdev[i].dig=&dbdd[dig_prn[i]];
   		      fisdev[i].idig=dig_prn[i];
               fisdev[i].stato=0;
         		bitset(fisdev[i].dig,g2di_sl,1);					// off line
				}
				else
					break;
			}
		else if(!strcmp(chApp,"BEGIN_FIS_TAB"))
			for(i=0;fgets(chBuffer,FILENAME_MAX,fp) && i<n_virt_tab;i++)
			{
				if(IsComment(chBuffer))
					continue;
					
				sscanf(chBuffer,"%s",chApp);
				if(strcmp(chApp,"END_FIS_TAB"))
					sscanf(chBuffer, "%s %hd %hd %hd %hd %hd",chApp,&virtprn[i+n_virt_lbg].indice[0],
                     &virtprn[i+n_virt_lbg].indice[1],
						   &virtprn[i+n_virt_lbg].indice[2],&virtprn[i+n_virt_lbg].indice[3]);
				else
					break;
			}
		else if(!strcmp(chApp,"BEGIN_FIS_LBG"))
			for(i=0;fgets(chBuffer,FILENAME_MAX,fp) && i<n_virt_lbg;i++)
			{
				if(IsComment(chBuffer))
					continue;
					
				sscanf(chBuffer,"%s",chApp);
				if(strcmp(chApp,"END_FIS_LBG"))
					sscanf(chBuffer, "%s %hd %hd %hd %hd %hd",chApp,&virtprn[i].indice[0],&virtprn[i].indice[1],
						   &virtprn[i].indice[2],&virtprn[i].indice[3]);
				else
					break;
			}
		else if(!strcmp(chApp,"BEGIN_GROUP_LBG"))
			for(i=0;fgets(chBuffer,FILENAME_MAX,fp) && i<n_virt_lbg;i++)
			{
				if(IsComment(chBuffer))
					continue;
					
				pch=strtok(chBuffer," \t\n");
				if(strcmp(pch,"END_GROUP_LBG"))
					for(;;)
					{
						pch=strtok(NULL," \t\n");
						if(strcmp(pch,"-1"))
						{
							sscanf(pch,"%hd",&shZona);
							virtprn[i].abzon|=(1 << shZona);
						}
						else
                  {
                     dbadv[pVirtZone+i*2]=virtprn[i].abzon & 0x0000FFFF;
                     dbadv[pVirtZone+i*2+1]=(virtprn[i].abzon & 0xFFFF0000) >> 16;
							break;
                  }
					}
				else   
					break;
			}
		else if(!strcmp(chApp,"DEF_TAB_VIRT"))
      {
			sscanf(chBuffer,"%s %hd",chApp,&gDefTabPrn);
         dbadv[pDefTab]=gDefTabPrn;
      }
   	else if(!strncmp(chApp,"ADDR_BB1",8))
   	{
	   	if(sscanf(chBuffer,"%s %x",chApp,&addrbb[0]) !=2)
            pscserr(ERR_CONF,ROU_INIT,ADDR_BB,0,SYS_HALT);
   	}
	   else if(!strncmp(chApp,"ADDR_BB2",8))
   	{
	   	if(sscanf(chBuffer,"%s %x",chApp,&addrbb[1]) !=2)
            pscserr(ERR_CONF,ROU_INIT,ADDR_BB,0,SYS_HALT);
   	}
		else
			pscserr(ERR_CONF,ROU_INIT,FILE_FVIRTPRN,0,SYS_HALT_DOS);
	}
	
   fisdev[fis_disk].flag=tpr_null;					// tabella per disco 
   fisdev[fis_disk].dig=&dbdd[sthdisk];			// assegnata di default
   fisdev[fis_disk].linea=fis_disk;			  
   fisdev[fis_disk].stato=0;	
   bitset(&dbdd[sthdisk],g2di_sl,0);		   // on line
   if(dbadv[pDefTab]==0.0) dbadv[pDefTab]=1.0;    // se la stampante non e' definita
                                                  // impongo la n. 1

	// Chiusura del file	
	fclose(fp);
   
   // inizializzazione linee
   for(i=0;i<n_fis-1;i++)
	{
		if(fisdev[i].linea==-1) continue;
		if(fisdev[i].baud)
		{
			IniLine(&fisdev[i]);
      }
   }
}

/**********************************************************************
*
*       C Source:               alldef.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug  1 10:33:20 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: alldef.c-4.2.1 %  (%full_filespec: alldef.c-4.2.1:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   Alldef.c

   La routine alldef legge i parametri che definiscono i database
   allarmi dal file fdesal.rtf. Alloca lo spazio necessario a
   ciascun dbs allarmi secondi la struttura buff_all.

   Parametri

   nessuno

   Ritorno

   1        se il file fdesal non esiste o contiene valori non accettabili
   0        se tutto ok

   19 Maggio 1992    Rel. 1.0 Fc.
   21 Gennaio 1993	Rel. 2.0 Fc.
   24 Agosto 1993             mp porting a 32 bit   
   
   Inseriti controlli ed inizializzazioni per gestione
   contatori allarmi per zona e da base

   10 Luglio 1994 Fc
   Inserita lettura parametro reset_ut per reset calcolate con periodo
   scelto da utente

   13 Febbraio 1995 Fc
   Inserita lettura parametri per definizione gruppo acquisizione

*/
#include <osf1.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

#include "switch.inc"         // contiene parametri di attivazione
#include "pscserr.inc"
#include "dconf.inc"
#include "tipal.inc"
#include "messcada.inc"
#include "allar.inc"
#include "diagnoan.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#define _PUBLIC 0      // per rendere questo modulo indipendente dalla versione
#include "sepdati.inc"  // includo qui le strutture SEPA
extern DB_HEADER h_db; // header del database, contienele dimensioni

extern short max_repall;
extern short max_repretry;

alldef()
{
FILE *fp;
char stringa[200];	 	// buffer in cui leggere il testo
char app[40];				// stringa appoggio per codifiche
short i, j;
char  st_trat[3];
char colore;
char fnome[FILENAME_MAX+1];
short leggi;
short num;
S_DBS_ALL *pal;         // puntatore dbs allarmi
S_DBS_ALV *pav;         // puntatore dbs allarmi per video
S_DBS_ALU *pau;         // puntatore dbs allarmi per unita' appartenenza
short ndbsal;           // n. data base allarmi
char *pzone[max_zone];  // puntatori al buffer bDbsAlu->pal per ciascuna unita' 
int priorita;           // appoggio per leggere priorit… allarmi   
short nGroup;           // n. gruppo in esame
S_GROUP_ACQ* pGroup;
char *arm;

char *punta_stringhe;
char str_appo[200];

pGroup=&bGroupAcq[0];
nGroup=0;
/*
   inizializzo il criterio di estrazione per i dbs allarmi
   di ciascun video
*/
for(i=0;i<num_video;i++) 
   {
   bDbsAlv[i].mask1= 0xFFFF;     // criterio = tutte le zone
   bDbsAlv[i].mask2= 0xFFFF;     // criterio = tutte le zone
   bDbsAlv[i].pal=0;              // dbs allarmi corrispondente
   bDbsAlv[i].nallco=16;          // n. allarmi da riconoscere (default)
#ifdef GERARC
   memset(bDbsAlv[i].abgera,-1,n_gerarchie);
#endif
   }
/*
   inizializzo il buffer dei dbs allarmi per ogni zona di impianto 
   a -1
*/
for(i=0,pau=&bDbsAlu[0];i<max_zone;i++,pau++) 
   {
   memset(pau->pal,-1,max_dbsall);
   pzone[i]=&pau->pal[0];
   }  
strcpy(fnome,conf[RTF]);
strcat(fnome,FDESAL);
fp=fopen(fnome,"r+");
if(!fp) 
   pscserr(ERR_IO,TASK_ALLARMI,ROU_ALLDEF,0,SYS_HALT);
/*
   reset contatori emissioni e rientri
*/
for(i=0;i<max_dbsall;i++)
   {
   dbadv[allemdb1+i*2]=0;
   dbadv[allridb1+i*2]=0;
   }
/*
   lettura file fdesal.rtf
*/   
for(;;)
   {
	leggi=1;
	for(;;)
	   {
		fgets(stringa,200,fp);
		if(feof(fp)) 
         goto FINE;
		if(stringa[0] != ';' && stringa[0]!=0x0A && stringa[0]!=0x0D) 
         break;
	   }
	if(!strncmp(stringa,"BEGIN_ALLAR_STR",15))
	   {
	   pscserr(ERR_CONF,TASK_ALLARMI,ROU_ALLTRAT,i,SYS_HALT);
		for(i=0;;i++)
		   {
			if(leggi) 
            fscanf(fp,"%s",stringa);
			if(!strncmp(stringa,"END_ALLAR_STR",13)) 
            break;
			if(i>=max_st) 
            pscserr(ERR_CONF,TASK_ALLARMI,ROU_ALLDEF,i,SYS_HALT);
			for(j=0;j<max_trat;j++)
		      {
				fscanf(fp,"%s",st_trat);
				if(!strcmp(st_trat,"NU")) 
               colore=0;
				else 
               if(!strcmp(st_trat,"VE")) 
                  colore=green;
				   else 
                  if(!strcmp(st_trat,"RO")) 
                     colore=red;
				      else 
                     if(!strcmp(st_trat,"MA")) 
                        colore=magenta;
				         else 
                        if(!strcmp(st_trat,"GI")) 
                           colore=yellow;
				            else 
                           if(!strcmp(st_trat,"CY")) 
                              colore=cyan;
				               else 
                              if(!strcmp(st_trat,"BI")) 
                                 colore=white;
				color[i][j]=colore;
			   }
			fscanf(fp,"%s",stringhe[i]);
			punta_stringhe = stringhe[i];
                        alsost(punta_stringhe);
			fscanf(fp,"%s",stringhe[i+max_st]);
			punta_stringhe = stringhe[i+max_st];
                        alsost(punta_stringhe);
			fscanf(fp,"%s",stringa);
			if(sscanf(stringa,"%1d",&priorita)==1)
            {
            pri_all[i]=(char)priorita;
            leggi=1;
            }
			else 
            leggi=0;
		   }
	   }
	else 
      if(!strncmp(stringa,"BEGIN_ALLAR_LIV",15))
	      {
		   for(i=0;;i++)
		      {
			   if(leggi) 
               fscanf(fp,"%s",stringa);
			   if(!strncmp(stringa,"END_ALLAR_LIV",13)) 
               break;
			   if(i>=max_st) 
               pscserr(ERR_CONF,TASK_ALLARMI,ROU_ALLDEF,i,SYS_HALT);
			   for(j=0;j<max_liv;j++)
		         {
				   fscanf(fp,"%s",st_trat);
				   if(!strcmp(st_trat,"NU")) 
                  colore=0;
				   else 
                  if(!strcmp(st_trat,"VE")) 
                     colore=green;
				      else 
                     if(!strcmp(st_trat,"RO")) 
                        colore=red;
				         else 
                        if(!strcmp(st_trat,"MA")) 
                           colore=magenta;
				            else 
                           if(!strcmp(st_trat,"GI")) 
                              colore=yellow;
				               else 
                              if(!strcmp(st_trat,"CY")) 
                                 colore=cyan;
				                  else 
                                 if(!strcmp(st_trat,"BI")) 
                                    colore=white;
				   color[i][j]=colore;
			      }
			   fscanf(fp,"%s",stringhe[i]);
			   punta_stringhe = stringhe[i];
                           alsost(punta_stringhe);
			   fscanf(fp,"%s",stringhe[i+max_st]);
			   punta_stringhe = stringhe[i+max_st];
                           alsost(punta_stringhe);
			   fscanf(fp,"%s",stringa);
			   if(sscanf(stringa,"%1d",&priorita)==1)
               {
               pri_all[i]=(char)priorita;
               leggi=1;
               }
			   else 
               leggi=0;
		      }
	      }
	   else 
         if(!strncmp(stringa,"BEGIN_GROUP_ACQ",15))
	         {
			   for(;;)
			      {
			   	fscanf(fp,"%s",stringa);
				   if(!strncmp(stringa,"END_GROUP_ACQ",13))  break;
               pGroup->def=1;       // definito
               strncpy(pGroup->nome,stringa,c_gacq_nome-1); // copio nome
               arm=&pGroup->arm[0];
               memset(arm,-1,max_zone);   // inizializzato con tappo
               for(;;)    // ciclo armadi inseriti
                  {
      				fscanf(fp,"%s",stringa);
   	      		sscanf(stringa,"%hd",&num);
                  if(num==-1) break;   // fine elenco
                  if(num<0 || num>=max_zone)   // zona accettabile ?
                  {
                     pscserr(ERR_CONF,TASK_ALLARMI,ROU_ALLDEF,num,SYS_HALT);
                   }
                   *arm=num;  // aggiorno associazione dbsal -> zona  
                   arm++;
                  }
                  nGroup++;
                  pGroup++;
			      }
	         }
         else if(!strncmp(stringa,"BEGIN_DBS_ALL",13))
	         {
			   for(;;)
			      {
			   	fscanf(fp,"%s",stringa);
				   if(!strncmp(stringa,"END_DBS_ALL",11)) 
                  break;
   			   sscanf(stringa,"%hd",&ndbsal);
               if(ndbsal < 1 || ndbsal > max_dbsall)
                  {
                  pscserr(ERR_CONF,TASK_ALLARMI,ROU_ALLDEF,ndbsal,SYS_HALT);
                  }
               ndbsal--;      

               // annullo i contatori di allarme ed archivio per zona e data base    
               if (CONT_ALL_ZONE)
                  {
                  num=first_cont_all+ndbsal*max_zone*2;
                  for(i=num;i<num+max_zone*2;i++)
                     {
                     if(i>=h_db.dimad) 
                        pscserr(ERR_CONF,TASK_ALLARMI,ROU_ALLDEF1,i,SYS_HALT);
                     dbadv[i]=0;            
                     bitset(&dbadf[i],g2an_s1,0);  // azzero flag di severita'
                     bitset(&dbadf[i],g2an_s2,0);  // azzero flag di severita'
                     bitset(&dbadf[i],g2an_s3,0);  // azzero flag di severita'
                     }
                  }
               pal=&bDbsAll[ndbsal];            // data base allarmi
               pal->def=ndbsal+1;               // definito n. (1-6)
               pal->mbox=mbox_all_0 + ndbsal;   // mail box associata
               pal->db_al=&dbadv[all_off+ndbsal];
               *pal->db_al=0;
               pal->db_ar=&dbadv[all_off+max_dbsall+ndbsal];
               *pal->db_ar=0;
				   fscanf(fp,"%s",stringa);
   			   sscanf(stringa,"%hd",&num);
               pal->dim=num;                 // n. di allarmi massimo
               pal->pall=(struct buff_all *)calloc(num,sizeof(struct buff_all));
               if(pal->pall==NULL)
                  {
                  pscserr(ERR_MEM,TASK_ALLARMI,ROU_ALLDEF,num,SYS_HALT);
                  }            
               for(;;)                       // ciclo codifica unita' di impianto
                  {
      				fscanf(fp,"%s",stringa);
   	      		sscanf(stringa,"%hd",&num);
                  if(num==-1) 
                     break;                   // fine elenco
                  if(num<0 || num>=max_zone)   // zona accettabile ?
                     {
                     pscserr(ERR_CONF,TASK_ALLARMI,ROU_ALLDEF,num,SYS_HALT);
                     }
                  *pzone[num]=ndbsal;  // aggiorno associazione dbsal -> zona  
                  pzone[num]++;
                  }
			      }
	         }
	      else 
            if(!strncmp(stringa,"FREQ_UT",7))
		         {
#if defined OSF1 || defined LINUX
			      if(sscanf(stringa,"%s %d",app,&reset_ut) !=2) 
#else
			      if(sscanf(stringa,"%s %hd",app,&reset_ut) !=2) 
#endif
                  pscserr(ERR_CONF,TASK_ALLARMI,RESET_UT,0,SYS_HALT);
		         }
	      else 
            if(!strncmp(stringa,"COEF_FA_MEDIAT",14))
		         {
			      if(sscanf(stringa,"%s %f",app,&coef_media) !=2) 
                  pscserr(ERR_CONF,TASK_ALLARMI,COEF_MEDIAT,0,SYS_HALT);
		         }
	         else 
               if(!strncmp(stringa,"COEF_FA_FILTRO",14))
		            {
			         if(sscanf(stringa,"%s %f",app,&coef_filtro) !=2) 
                     pscserr(ERR_CONF,TASK_ALLARMI,COEF_FILTRO,0,SYS_HALT);
		            }
	            else 
                  if(!strncmp(stringa,"COEF_FA_SCARTO",14))
		               {
			            if(sscanf(stringa,"%s %f",app,&coef_scarto) !=2) 
                        pscserr(ERR_CONF,TASK_ALLARMI,COEF_SCARTO,0,SYS_HALT);
		               }
	               else 
                     if(!strncmp(stringa,"COEF_FA_MEDIAI",14))
		                  {
			               if(sscanf(stringa,"%s %f",app,&coef_mist) !=2) 
                           pscserr(ERR_CONF,TASK_ALLARMI,COEF_MEDIAI,0,SYS_HALT);
		                  }
	                  else 
                        if(!strncmp(stringa,"COEF_FA_SOMMA",13))
		                     {
			                  if(sscanf(stringa,"%s %f",app,&coef_somma) !=2) 
                              pscserr(ERR_CONF,TASK_ALLARMI,COEF_SOMMA,0,SYS_HALT);
		                     }
	                     else 
                           if(!strncmp(stringa,"COEF_FA_INTEGRALE",17))
		                        {
			                     if(sscanf(stringa,"%s %f",app,&coef_integrale) !=2) 
                                 pscserr(ERR_CONF,TASK_ALLARMI,COEF_INTEGRALE,0,SYS_HALT);
		                        }
/*
	lettura tabella valori float per classi di conversione da normalizzato
	ad unita' ingegneristiche
*/
	                        else 
                              if(!strncmp(stringa,"BEGIN_TAB_K",11))
	                              {
			                        for(i=0;;i++)
			                           {
				                        fgets(stringa,200,fp);
				                        if(!strncmp(stringa,"END_TAB_K",9))    
                                       break;
   			                        if(sscanf(stringa,"%f",&tab_k[i]) != 1)
						                     pscserr(ERR_CONF,TASK_ALLARMI,TAB_K_COD,0,SYS_HALT);
				                        if(i>=n_tab_k) 
                                       pscserr(ERR_CONF,TASK_ALLARMI,TAB_K,0,SYS_HALT);
			                           }
	                              }
                              else 
                                 {
	                              if(!strncmp(stringa,"TIPO_CICALINO",13))
	                                 {
			                           if(sscanf(stringa,"%s %hd",app,&tip_cic) !=2) 
                                       pscserr(ERR_CONF,TASK_ALLARMI,TIP_CIC_,0,SYS_HALT);
	                                 }
	                              else 
                                    if(!strncmp(stringa,"SEV1_CICALINO",13))
	                                    {
			                              if(sscanf(stringa,"%s %hd",app,&tab_cic[0]) !=2)    
                                          pscserr(ERR_CONF,TASK_ALLARMI,TAB_CIC_,0,SYS_HALT);
	                                    }
	                                 else 
                                       if(!strncmp(stringa,"SEV2_CICALINO",13))
	                                       {
			                                 if(sscanf(stringa,"%s %hd",app,&tab_cic[1]) !=2) 
                                             pscserr(ERR_CONF,TASK_ALLARMI,TAB_CIC_,1,SYS_HALT);
	                                       }
	                                    else 
                                          if(!strncmp(stringa,"SEV3_CICALINO",13))
	                                          {
			                                    if(sscanf(stringa,"%s %hd",app,&tab_cic[2]) !=2) 
                                                pscserr(ERR_CONF,TASK_ALLARMI,TAB_CIC_,2,SYS_HALT);
	                                          }
	                                    else 
                                          if(!strncmp(stringa,"REP_RETRY",9))
	                                          {
			                                    if(sscanf(stringa,"%s %hd",app,&max_repretry) !=2) 
                                                pscserr(ERR_CONF,TASK_ALLARMI,REP_RETRY,SYS_HALT);
	                                          }
	                                    else 
                                          if(!strncmp(stringa,"REP_MESS",8))
	                                          {
			                                    if(sscanf(stringa,"%s %hd",app,&max_repall) !=2) 
                                                pscserr(ERR_CONF,TASK_ALLARMI,REP_MESS,SYS_HALT);
	                                          }
                                 }
   }
FINE:

fclose(fp);
}
/*
   funzione per la sostituzione del carattere '_' con blank
*/
alsost(str)
char *str;
{

for(;;)
{
   if((str=strstr(str,"_")) != (char*)0) 
   {  *str=' ';  str++; }        // trovato inserisco blank
   else break;                   // nessun _ ritorno
}
}




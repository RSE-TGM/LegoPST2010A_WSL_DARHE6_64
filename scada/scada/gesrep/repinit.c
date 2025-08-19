/**********************************************************************
*
*       C Source:               repinit.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 16:20:28 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: repinit.c-3 %  (%full_filespec: repinit.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/* 
	-> RepInit.c
	
	Rountine di inizializzazione del task dei reperibili
	Inizializza sulla base del file di configurazione FGESREP.RTF gli
	svincoli tra l'indice del punto reperibile e la sua posizione nel
	data base dinamico di sistema (DBS).
	Inizializza una struttura dati per le posizioni dei punti di dia-
	gnostica dei reperibili all'interno del DBS.
	
	Nessun parametro.
	Codici di errore:		1	OK
                        	0  	KO
	
	Data di creazione:		11.5.1995
	Autore:					E.L.
*/

#include "g1tipdb.inc"
#include "dconf.inc"
#define _PUBLIC 0
#include "defpub.h"
#include "gesrep.h"
#include "pscserr.inc"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

short StrnChar(char *pch, char ch);
char IsComment(char *pch);
char IsNull(char *pch);

// External function declarations
extern void pscserr(int, int, int, int, int);
extern int ricerca(short *, short *, short *, long *, short *, FILE *);


extern DB_HEADER h_db;

short RepInit(void)
{
	// Variabili locali
	short i,j;
	FILE *fp;
	char *pch, *pchfisse, *pchvar;
	char chBuffer[lLine];		// Buffer in cui vengono memorizzate le linee del file
	short point; 				// Indice in data base
	short ext; 					// Tipo di estensione
	long  blocco; 				// Blocco in cui andra' inserito o e' inserito
	short posiz; 				// Posizione all'interno del blocco
	char fnome[FILENAME_MAX+1];         	// File da aprire
  	short lung;

  	lung=strlen(conf[RTF]);

	// Inizializza il buffer dei reperibili
	for(i=0;i<sizeof(punrep);i++)
		*(((char *)punrep)+i)=FILPATT;
	
	// Apre il file di configurazione
  	strcpy(fnome,conf[RTF]);
  	strcpy(&fnome[lung],FGESREP) ;
	if(!(fp=fopen(fnome,"r")))
  	{
    	pscserr(ERR_IO,TASK_REP,ROU_REP_OPEN,0,SYS_HALT);
     	return 1;
	}

	// Scandisce tutto il file di configurazione nei limiti delle capacita' del buffer
	for(i=0;fgets(chBuffer,lLine,fp);)
	{
		// Se e' un commento considera la linea successiva
		if(IsComment(chBuffer))
			continue;

      if(i>=max_puntirep)
      {
       	pscserr(ERR_CONF,TASK_REP,ROU_INI_TABELLA,-1,SYS_HALT);
     	   return 1;
   	}

		// Decodifica la Tag
		pch=strtok(chBuffer," ;\t");
		strncpy(punrep[i].tag,pch,lun_tagrep);
		
		// Memorizza l'indirizzo delle voci fisse
		pchfisse=strtok(NULL,";");
		
		// Memorizza l'indirizzo delle voci variabili
		pchvar=strtok(NULL,";");
		
		// Decodifica il livello di severita'
		pch=strtok(NULL," ;\t");
		punrep[i].severita=*pch;
		
		// Decodifica l'indice del reperibile
		pch=strtok(NULL," ;\t\n");
		punrep[i].specrep=atoi(pch);
		
      // Eventuale errore di configurazione
      if(!(pch && pchvar && pchfisse))
     	{
       	pscserr(ERR_CONF,TASK_REP,ROU_INI_TABELLA,i,SYS_HALT);
     	   return 1;
   	}

		// Decodifica le voci fisse
		for(j=0;j<max_vfisse && strlen(pchfisse);j++)
		{
         pch=strchr(pchfisse,',');
         if(!pch)
         {
				punrep[i].vfisse[j]=atoi(pchfisse);
            break;
         }
         if(pch!=pchfisse)
         {
            *pch='\0';
				punrep[i].vfisse[j]=atoi(pchfisse);
         }
         pchfisse=++pch;
		}

		// Decodifica le voci variabili
		for(j=0;j<max_vvaria && strlen(pchvar);j++)
		{
         pch=strchr(pchvar,',');
         if(!pch)
         {
				punrep[i].vvaria[j]=atoi(pchvar);
            break;
         }
         if(pch!=pchvar)
         {
            *pch='\0';
				punrep[i].vvaria[j]=atoi(pchvar);
         }
         pchvar=++pch;
		}

		i++;
	}
	
	// Chiude il file di configurazione
	fclose(fp);
	
	// Allocazione memoria per gli svincoli data base - reperibili
	repaa=(short*)malloc(sizeof(short)*h_db.dimaa);
	repas=(short*)malloc(sizeof(short)*h_db.dimas);
	repac=(short*)malloc(sizeof(short)*h_db.dimac);
	repad=(short*)malloc(sizeof(short)*h_db.dimad);
	repda=(short*)malloc(sizeof(short)*h_db.dimda);
	repds=(short*)malloc(sizeof(short)*h_db.dimds);
	repdc=(short*)malloc(sizeof(short)*h_db.dimdc);
	repdd=(short*)malloc(sizeof(short)*h_db.dimdd);
	repor=(short*)malloc(sizeof(short)*h_db.dimor);
	
  	// Allocazione memoria per svincoli con i punti di diagnostica dei reperibili
	svrep=(S_SVREP *)malloc(sizeof(S_SVREP)*max_specrep);
   
  	// Out of Memory
  	if(!(repaa && repas && repac && repad  && repda && repds
       && repdc && repdd && repor && svrep))
  	{
    	pscserr(ERR_MEM,TASK_REP,ROU_REP_OUTOFMEM,0,SYS_HALT);
      	return 1;
	}
   

  	memset(repaa,FILPATT,sizeof(short)*h_db.dimaa);
	memset(repas,FILPATT,sizeof(short)*h_db.dimas);
	memset(repac,FILPATT,sizeof(short)*h_db.dimac);
	memset(repad,FILPATT,sizeof(short)*h_db.dimad);
	memset(repda,FILPATT,sizeof(short)*h_db.dimda);
	memset(repds,FILPATT,sizeof(short)*h_db.dimds);
	memset(repdc,FILPATT,sizeof(short)*h_db.dimdc);
	memset(repdd,FILPATT,sizeof(short)*h_db.dimdd);
	memset(repor,FILPATT,sizeof(short)*h_db.dimor);
	memset(svrep,FILPATT,sizeof(S_SVREP)*max_specrep);
	
	svRic[nNonRicTag]=FILPATT;
	svRic[nRicTag]=FILPATT;

   svDia[nTag]=FILPATT;
   svDia[nTel]=FILPATT;
   svDia[nPref]=FILPATT;
	
	// Apertura del file data base dei punti di sistema
	strcpy(fnome,conf[RTF]);
	strcpy(&fnome[lung],FNOMI) ;
	if(!(fp=fopen(fnome,"r")))
   {
    	   pscserr(ERR_IO,TASK_REP,ROU_REP_OPEN,0,SYS_HALT);
      	return 1;
	}

	
	// Assegnazione degli svincoli dei punti reperibili
	for(i=0;*punrep[i].tag!=FILPATT;i++)
	{
		if(!ricerca(((short*)punrep[i].tag),&point,&ext,&blocco,&posiz,fp))
			switch(ext)
			{
				// analogici acquisiti
				case g1tipaa:
					*(repaa+point)=i;
				break;
			
				// analogici calcolati standard
				case g1tipas:
					*(repas+point)=i;
				break;
			
				// analogici calcolati non standard
				case g1tipac:
					*(repac+point)=i;
				break;
			
				// analogici di diagnostica
				case g1tipad:
					*(repad+point)=i;
				break;
			
				// digitali acquisiti
    			case g1tipda:
					*(repda+point)=i;
				break;
			
				// digitali  calcolati standard
				case g1tipds:
					*(repds+point)=i;
				break;
			
				// digitali  calcolati non standard
				case g1tipdc:
					*(repdc+point)=i;
				break;
			
				// digitali  di diagnostica
				case g1tipdd:
					*(repdd+point)=i;
				break;
			
				// organi
				case g1tipor:
					*(repor+point)=i;
				break;
			
				default:
	         {
    	         pscserr(ERR_IO,TASK_REP,ROU_REP_PTUNKNOWN,0,SYS_HALT);
        	      return 1;
         	}
			}
		else
      {
      	pscserr(ERR_IO,TASK_REP,ROU_REP_PTNOTFOUND,0,SYS_HALT);
	     	return 1;
	   }
	}
	
	// Assegnazione degli svincoli dei punti di diagnostica dei reperibili
	for(i=1;i<=max_specrep;i++)
	{
		// Codice
      memset(chBuffer,0,lLine);
		sprintf(chBuffer,szForCod,i);
		if(ricerca(((short*)chBuffer),&point,&ext,&blocco,&posiz,fp))
     	{
        	pscserr(ERR_CONF,TASK_REP,ROU_INI_DIA,0,SYS_HALT);
        	return 1;
	  	}

		svrep[i-1].cod=point;
		
		// N . di chiamate
      memset(chBuffer,0,lLine);
		sprintf(chBuffer,szForChiam,i);
		if(ricerca(((short*)chBuffer),&point,&ext,&blocco,&posiz,fp))
     	{
        	pscserr(ERR_CONF,TASK_REP,ROU_INI_DIA,0,SYS_HALT);
        	return 1;
	  	}

		svrep[i-1].nchiam=point;
		
		// Intervallo tra una chiamata e l'altra
      memset(chBuffer,0,lLine);
		sprintf(chBuffer,szForInterv,i);
		if(ricerca(((short*)chBuffer),&point,&ext,&blocco,&posiz,fp))
      {
        	pscserr(ERR_CONF,TASK_REP,ROU_INI_DIA,0,SYS_HALT);
        	return 1;
	   }

		svrep[i-1].interv=point;
		
		
		// N. telefonici e prefissi
		for(j=1;j<=max_elesqu;j++)
		{
			// Telefoni
         memset(chBuffer,0,lLine);
			sprintf(chBuffer,szForTel,i,j);
			if(ricerca(((short*)chBuffer),&point,&ext,&blocco,&posiz,fp))
        	{
           	pscserr(ERR_CONF,TASK_REP,ROU_INI_DIA,0,SYS_HALT);
           	return 1;
	     	}

			svrep[i-1].ntel[j-1]=point;

			// Prefissi
        	memset(chBuffer,0,lLine);
			sprintf(chBuffer,szForPref,i,j);
			if(ricerca(((short*)chBuffer),&point,&ext,&blocco,&posiz,fp))
        	{
           	pscserr(ERR_CONF,TASK_REP,ROU_INI_DIA,0,SYS_HALT);
           	return 1;
	     	}

			svrep[i-1].npref[j-1]=point;
		}
	}

  	memset(chBuffer,0,lLine);
   strcpy(chBuffer,szNonRicTag);
	if(ricerca((short*)chBuffer,&point,&ext,&blocco,&posiz,fp))
   {
      pscserr(ERR_CONF,TASK_REP,ROU_INI_DIA,0,SYS_HALT);
      return 1;
   }
	svRic[nNonRicTag]=point;

  	memset(chBuffer,0,lLine);
   strcpy(chBuffer,szRicTag);
	if(ricerca((short*)chBuffer,&point,&ext,&blocco,&posiz,fp))
   {
     	pscserr(ERR_CONF,TASK_REP,ROU_INI_DIA,0,SYS_HALT);
     	return 1;
   }
	svRic[nRicTag]=point;
		
  	memset(chBuffer,0,lLine);
   strcpy(chBuffer,szTag);
	if(ricerca((short*)chBuffer,&point,&ext,&blocco,&posiz,fp))
   {
     	pscserr(ERR_CONF,TASK_REP,ROU_INI_DIA,0,SYS_HALT);
     	return 1;
   }
	svDia[nTag]=point;

  	memset(chBuffer,0,lLine);
   strcpy(chBuffer,szTel);
	if(ricerca((short*)chBuffer,&point,&ext,&blocco,&posiz,fp))
   {
     	pscserr(ERR_CONF,TASK_REP,ROU_INI_DIA,0,SYS_HALT);
     	return 1;
   }
	svDia[nTel]=point;

  	memset(chBuffer,0,lLine);
   strcpy(chBuffer,szPref);
	if(ricerca((short*)chBuffer,&point,&ext,&blocco,&posiz,fp))
   {
     	pscserr(ERR_CONF,TASK_REP,ROU_INI_DIA,0,SYS_HALT);
     	return 1;
   }
	svDia[nPref]=point;

   fclose(fp);
   return 0;
}

char IsComment(char *pch)
{
	for(;*pch==' ';pch++)
		;
	for(;*pch=='\t';pch++)
		;
	return(*pch==';' || *pch=='\n');
}


char IsNull(char *pch)
{
	for(;*pch==' ';pch++)
		;
	for(;*pch=='\t';pch++)
		;
	return(*pch==0);
}

short StrnChar(char *pch, char ch)
{
	short i;
	
	for(i=0;*pch;)
	{
		if(*pch==ch)
			i++;
		pch++;
	}
	
	return i;
}


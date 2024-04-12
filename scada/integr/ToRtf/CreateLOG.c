/*
   modulo CreateLOG.c
   tipo 
   release 2.10
   data 10/14/96
   reserved @(#)CreateLOG.c	2.10
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>

#include "ToRtf.h"
#include "db.h"
#include "CreateFdde.h" 
#include "CreateLOG.h" 
#include "g1tipdb.inc" 

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define MAX_SIGLE_SOST	5000
int sostLink(char *riga);
extern char path_txt[];

int prog_sost=0;
char var_sost[MAX_SIGLE_SOST][SCD_SIGLA];

int CreateLOG()
{

ID_TABLE *tabella;
VAL_RET valore;
int i,num_record;
S_LOGPROP logprop;

printf("Creazione file fdiztab.rtf e ftab.rtf\n");

if(!CreateFdiztab())
{
	fprintf(stderr,"Fallita inizializzazione fdiztab.rtf\n");
	return(0);
}

if(!CreateFtab())
{
	fprintf(stderr,"Fallita inizializzazione ftab.rtf\n");
	return(0);
}

tabella = OpenTablePath(path_txt,LOG);
if(tabella == NULL)
{
        fprintf(stderr,"CreateLOG: apertura tabella\n");
        return(0);
}

num_record = NumRecord(tabella);
for(i=0;i<num_record;i++)
{
	memset(&logprop,-1,sizeof(logprop));

        if(GetVal(tabella,"Nome",i,&valore)!=1)
        {
                fprintf(stderr,"CreateLOG: Errore GetVal Nome\n");
                return(0);
        }
	strcpy(logprop.szNome,valore.char_val);
	ToLower(logprop.szNome);

        if(GetVal(tabella,"Periodo",i,&valore)!=1)
        {
                fprintf(stderr,"CreateLOG: Errore GetVal Periodo\n");
                return(0);
        }
	logprop.iPeriodo=valore.int_val;

        if(GetVal(tabella,"Periodico",i,&valore)!=1)
        {
                fprintf(stderr,"CreateLOG: Errore GetVal Periodico\n");
                return(0);
        }
	logprop.bPeriodico=valore.int_val;

        if(GetVal(tabella,"Cicli",i,&valore)!=1)
        {
                fprintf(stderr,"CreateLOG: Errore GetVal Cicli\n");
                return(0);
        }
	logprop.nCicli=valore.int_val;

        if(GetVal(tabella,"Attesa",i,&valore)!=1)
        {
                fprintf(stderr,"CreateLOG: Errore GetVal Attesa\n");
                return(0);
        }
	logprop.nAttesa=valore.int_val;

        if(GetVal(tabella,"Tipo",i,&valore)!=1)
        {
                fprintf(stderr,"CreateLOG: Errore GetVal Tipo\n");
                return(0);
        }
	logprop.wTipo=valore.int_val;

	if(!LogCompila(&logprop))
	{
		fprintf(stderr,"CreateLOG: Errore di compilazione tabulato %s\n",logprop.szNome);
		return(0);
	}
	
        if(!LogInstalla(&logprop))
        {
                fprintf(stderr,"CreateLOG: Errore di installazione tabulato %s\n",logprop.szNome);
                return(0);
        }
	
	EliminaFileAppoggio(&logprop);
}

CloseTable(tabella);
return(1);
}

#define errore_SistemaPol(str) {fprintf(stderr,"SistemaPol: [%s]\n",str);return(0);}

int LogCompila(S_LOGPROP *logprop)
{
	char szBuffer[FILENAME_MAX+1];
	FILE *fp;

	// Elimina i file di precedenti compilazioni	
	remove("*.LST");                

	if(!SistemaPol(logprop->szNome))
		errore_SistemaPol("fallita");

	// Genera il file .SOR
	sprintf(szBuffer,"%s/%s.sor",path_txt,logprop->szNome);
	if(!(fp=fopen(szBuffer,"wb")))
	{
		perror(szBuffer);
		return(0);
	}
	fwrite(logprop->szNome,strlen(logprop->szNome),1,fp);
	fclose(fp);
	
	// Compila
	sprintf(szBuffer,"compila %s/%s /1 /ST /LO",path_txt,logprop->szNome);
	if(system(szBuffer))
	{
		perror("szBuffer");
		return(0);
	}
	
	// Se c'e' stato errore la funzione ritorna
	sprintf(szBuffer,"%s.lst",logprop->szNome);
	if(!access(szBuffer,F_OK))
		return(0);
		
	// Altrimenti prepara il file compilato
	if(!SetRecord(logprop) || !access(szBuffer,F_OK))
	{
		fprintf(stderr,"SetRecord o Installazione\n");
		return(0);
	}
	return(1);
}

/*
   SetRecord()

   Prepara il record per il file FTAB.RTF con le proprieta' del tabulato,
   il DBL per i DATA e alloca lo spazio per risolvere i link in fase
   di installazione scrive il risultato su un file pseudo compilato
   avente il nome del tabulato
   
   Restituisce:
  	1 	se tutto OK
  	0	altrimenti
*/
BOOL SetRecord(S_LOGPROP *logprop)
{
	int i;
	long offset;
	S_LOG log;			// Record per FTAB.RTF
	S_DATA *pData;			// puntatore ai byte allocati x LINK, DATA e costanti puntatori
	short shData;			// byte allocati x LINK, DATA e costanti puntatori
	char szBuffer[FILENAME_MAX+1];	// Buffer di appoggio
        short dimR;                     // dimensioni costanti su disco
        short dimL;                     // dimensioni costanti in data base locale
        char *pchVal;
        S_MAP heaMap;           	// struttura per leggere l'header del file FRAME.MAP
        S_DATA data, *pLocData;
	FILE *fpMap,*fpErr,*fpFRAME,*fp;
	short dimLink;	 	// area link
	short dimPointer;  	// area nomi puntatori costanti
	short dimPdbs;		// area puntatori in dbs
    	S_CODICE buff;
	BOOL bErr=0;
        HEAD_DATAB *pDATAB=(HEAD_DATAB *)log.chDBL;	// puntatore all'header del DBL
	
	// Header con le proprieta del tabulato
	memset(&log,0,sizeof(S_LOG));
	log.htab.tip_dat=logprop->wTipo;
	log.htab.arc_frq=logprop->nAttesa;
	log.htab.cicli=logprop->nCicli;
	
	// Apertura file Map per recupero link, costanti
	sprintf(szBuffer,"%s/%s.MAP",path_txt,logprop->szNome);
	if(!(fpMap=fopen(szBuffer,"rb")))
	{
		perror(szBuffer);
		return(0);
	}

	// Lettura header
	fread(&heaMap,sizeof(heaMap),1,fpMap);

	// Esame variabili di link : le inserisco nella struttura che sara' completata con
	// i puntatori in fase di installazione e le costanti di tipo puntatore
	dimLink=sizeof(S_DATA)*heaMap.link_var;	 // area link
	dimPointer=sizeof(S_DATA)*heaMap.pointer;  // area nomi puntatori costanti
	dimPdbs=sizeof(S_PDBS)*heaMap.link_var;    // area puntatori in dbs
	
	pDATAB->n_link=heaMap.link_var;
	pDATAB->n_point=(unsigned char)heaMap.pointer;
	
	// link + puntatori in DBS + puntatori costanti
	shData=dimLink+dimPointer+dimPdbs;
	
	// memorizza i link
	pData=(S_DATA *)malloc(shData);
	pLocData=pData;
	memset(pLocData,-1,shData);
   	fread(pLocData,dimLink,1,fpMap);
   	
   	// Punta inizio area costanti
	pLocData+=heaMap.link_var;
	offset=(long) heaMap.link_var*(long)DIM_LINK_VAR+(long) heaMap.define_var*(long)DIM_DEFINE_VAR+ sizeof(heaMap);
	fseek(fpMap,offset,SEEK_SET);

	// Creazione file errori di tipo incongruenza in definizione gruppi o
	// definizione di variabili di link non esistenti
	sprintf(szBuffer,"%s/_INSTALL_.LST",path_txt);
	if(!(fpErr=fopen(szBuffer,"w")))
	{
		perror(szBuffer);
		if(shData)
			free(pData);
		return(0);
	}
	
	// Legge tutte le  costanti
	for(i=0;i<heaMap.data_var;i++)
	{                              
		fread(&data,sizeof(data),1,fpMap); 

		// in base al tipo della costante dimensiono il buffer per contenere la costante
		switch (data.tipo & 0x0F)
		{
		case b_reale: 	
			dimR=dimL=4;
			pDATAB->l_data+=dimL;
		break;
		case b_intero:	
			dimR=dimL=2;
			pDATAB->l_data+=dimL;
		break;
		case b_logico:	
			dimR=dimL=1;
			pDATAB->l_data+=dimL;
		break;
		case b_stringa:	
			dimR=dimL=(data.tipo & 0xFFF0) >> 4;
			pDATAB->l_data+=dimL;
			
			// Per compensare errore del compilatore POL
			// che allinea la stringa piu' il suo terminatore 
			// alla WORD senza scrivere correttamente la 
			// lunghezza cosi'ottenuta
			if(dimL%2)
				pDATAB->l_data++;
		break;                                       

		//	Il valore delle costanti di tipo puntatore deve essere risolto in fase di installazione
		case b_pan:	case b_pdi:	case b_por:	case b_pst:  case b_pdo:
			dimR=10;	dimL=0;	
			pDATAB->l_data+=4;
		break;
		
		default:                     
			bErr=TRUE;               
			sprintf(szBuffer,"Tipo di variabile sconosciuto %s \n",data.name);
			fwrite(szBuffer,strlen(szBuffer),1,fpErr);
			dimL=dimR=-1;
		break;	
		}       
		         
		// Impossibile proseguire analisi mappa
		if(dimL==-1)
			break;
		
		pchVal=(char *) malloc(dimR);
		fread(pchVal,dimR,1,fpMap);
		
		// costante non puntatore
		if(dimL) 					
			memcpy(log.chDBL+(data.ind & 0x7FF), pchVal, dimL) ;
		else
		{
		 	memcpy(pLocData->name, pchVal, dimR); 
		 	pLocData->ind=data.ind;
		 	pLocData->tipo=data.tipo;
		 	pLocData++;
		}		 	
		free(pchVal);                                      
	}		                               

	sprintf(szBuffer,"%s/%s.AB",path_txt,logprop->szNome);
	if(!(fpFRAME=fopen(szBuffer,"rb")))
	{
		perror(szBuffer);
		if(shData)
			free(pData);
		return FALSE;
	}

	// Parametri del codice del tabulato
	fread(&buff,sizeof(buff),1,fpFRAME);
	memset(&log.hcod,-1,l_hcod);
	log.hcod.lung=buff.lung;
	log.hcod.percamp=buff.periodo;
	log.hcod.entryI=buff.entry[0];
	log.hcod.entry0=buff.entry[1];
	log.hcod.entry1=buff.entry[2];
	log.hcod.entryT=buff.entry[3];
	
	for(i=0;i<nSpare;i++)
		log.hcod.spare[i]=buff.spare[i];
	
	// Esegue controllo sulla lunghezza del codice
	if(buff.lung>l_codtab/2)
	{
		fprintf(stderr,"Dimensioni massime codice tabulato superate\n");
		return(0);
	}
	
	fclose(fpMap);
	fclose(fpErr);  

	if(!bErr)
	{
		sprintf(szBuffer,"%s/%s.tcf",path_txt,logprop->szNome);
		remove(szBuffer);
		if(!(fp=fopen(szBuffer,"wb")))
		{
			perror(szBuffer);
			if(shData)
				free(pData);
			return(0);
		}

		fwrite(&log,sizeof(log),1,fp);

		for(i=FILENAME_MAX+1;i==FILENAME_MAX+1;)
		{
			i=fread(szBuffer,1,FILENAME_MAX+1,fpFRAME);
			fwrite(szBuffer,i,1,fp);
		}
	
		if(shData)
			fwrite(pData,shData,1,fp);
		fclose(fp);
	}
	
	close(fpFRAME);
	
	if(shData)
		free(pData);
	
	return(!bErr);
}

int LogInstalla(S_LOGPROP *logprop)
{
	long i,j;
	S_DIZTAB rDizTab;		// record del file dizionario
	S_LOG    rTab;			// record del file operativo
	FILE *fpDIZTAB, *fpTAB;		// file FDIZTAB.RTF e FTAB.RTF
	char *pCode;
	char szBuffer[lLogNome];
	char szPathName[FILENAME_MAX];
	
	UINT lTab=sizeof(rTab);		// dimensione del record del file operativo

	rDizTab.nome[0]=0;
	
	// file FDIZTAB.RTF
	if(!(fpDIZTAB=fopen("fdiztab.rtf","r+b")))
	{
		perror("fdiztab.rtf");
		return(0);
	}
		
	// file FTAB.RTF
	if(!(fpTAB=fopen("ftab.rtf","r+b")))
	{
		perror("ftab.rtf");
		fclose(fpDIZTAB);
		return(0);
	}
		
	// Risolve i link
	pCode=(char *)malloc(l_codtab);
	memset(pCode,-1,l_codtab);
	if(!Link(&rTab,pCode,logprop->szNome))
	{
		fprintf(stderr,"Link() fallita vedere il file _INSTALL_.LST\n");
		free(pCode);
		return(0);
	}

	// Trova la prima posizione libera nel file dizionario
	for(i=0;i<n_tabu;i++)
	{
		fread(&rDizTab,rec_fdiztab,1,fpDIZTAB);
		if(rDizTab.nome[0]==-1)
			break;
    	}
    
	// Cerca se il tabulato e' gia' presente
	fseek(fpDIZTAB,0,SEEK_SET);
	for(j=0;j<n_tabu;j++)
	{
		fread(&rDizTab,rec_fdiztab,1,fpDIZTAB);
		if(!strcmp(logprop->szNome,rDizTab.nome))
			break;
    	}
    
	if(j<n_tabu)
		i=j;
	
	if(i<n_tabu)
	{
		memset(&rDizTab,0,rec_fdiztab);
		
		if(logprop->bPeriodico)
			rDizTab.periodo=logprop->iPeriodo+1;
		else
			rDizTab.periodo=-1;
			
		strcpy(szBuffer,logprop->szNome);
		ToUpper(szBuffer);
		memcpy(rDizTab.nome,szBuffer,strlen(logprop->szNome));
		
		fseek(fpDIZTAB,rec_fdiztab*i,SEEK_SET);
		fwrite(&rDizTab,rec_fdiztab,1,fpDIZTAB);
	}
	else
	{
		fprintf(stderr,"Superato il numero massimo di tabulati\n");
		fclose(fpDIZTAB);
		fclose(fpTAB);
		free(pCode);
		return(0);
	}
	fclose(fpDIZTAB);

	fseek(fpTAB,(lTab+l_codtab)*i,SEEK_SET);
	fwrite(&rTab,lTab,1,fpTAB);
	fwrite(pCode,rTab.hcod.lung*2,1,fpTAB);
	fclose(fpTAB);
	
	free(pCode);
	return(1);
}

int Link(S_LOG *pLog, char *pCodeBuff,const char *pchNome)
{
	FILE *fpTCF;	// file compilato
	FILE *fpFNOMI;	// file FNOMI.RTF
	FILE *fpINSTALL;// file errori di installazione
	long lLink,blocco;
	short i,tipo,indice,*psh,posiz,j;
	S_DATA *pDATA,*pDATAsave;
	S_PDBS *pDBS;
	BOOL bErrore=0;
	char szBuffer[FILENAME_MAX+1];	// Buffer di appoggio
	char szSigla[SCD_SIGLA+1];
	HEAD_DATAB *pDATAB=(HEAD_DATAB *)pLog->chDBL;
	char *app;
	int app_int;
	
	// Apre il file degli errori di installazione	
	sprintf(szBuffer,"%s/_INSTALL_.LST",path_txt);
	if(!(fpINSTALL=fopen(szBuffer,"wa")))
	{
		perror("_INSTALL_.LST");
		return(0);
    	}
    
	// Apre il file risultato della compilazione
	sprintf(szBuffer,"%s/%s.tcf",path_txt,pchNome);
	if(!(fpTCF=fopen(szBuffer,"rb")))
	{
		perror(szBuffer);
		fclose(fpINSTALL);
		return(0);
    	}
	
	// Apre il file operativo dei punti installati
	if(!(fpFNOMI=fopen("fnomi.rtf","rb")))
	{
		perror("fnomi.rtf");
		fclose(fpTCF);
		fclose(fpINSTALL);
		return FALSE;
    	}
	
	// Legge le proprieta' del tabulato
	fread(pLog,sizeof(S_LOG),1,fpTCF);
	
	// Legge il codice del tabulato
	fread(pCodeBuff,pLog->hcod.lung*2,1,fpTCF);
	
	// Legge i link da risolvere
	lLink=pDATAB->n_link*(sizeof(S_DATA)+sizeof(S_PDBS))+pDATAB->n_point*sizeof(S_DATA);
	pDATAsave=pDATA=(S_DATA *)malloc(lLink);
	fread(pDATA,lLink,1,fpTCF);
	
	pDBS=(S_PDBS *)(pLog->chDBL+l_hdat);
	psh=(short *)(pDBS+pDATAB->n_link);
	
	// Scandisce tutti i link trovati  
	for(i=0,szSigla[0]='\0';i<pDATAB->n_link+pDATAB->n_point; i++, pDATA++)
	{           
		memset(szSigla,0,SCD_SIGLA+1);
/* OLD VER
		for(j=0;j<SCD_SIGLA_CORTA && pDATA->name[j]!=' ';j++)
			szSigla[j]=pDATA->name[j];
*/
		app = pDATA->name+1;
		app_int = atoi(app);
		strcpy(szSigla,&var_sost[app_int][0]);
		ToUpper(szSigla);
		
		// Non ammette un nome tutto di spazi
		if(pDATA->name[0]==' ')
			tipo=0;
		else if(ricerca((short*)szSigla,&indice,&tipo,&blocco,&posiz,fpFNOMI))
		{
			sprintf(szBuffer,"Punto non trovato [%s] tipo %hd\n",szSigla,tipo);
			fputs(szBuffer,fpINSTALL);
			bErrore=1;
		}
 
			
		switch (tipo)
		{
		// Analogico
		case g1tipaa: case g1tipas: case g1tipad: case g1tipac: case g1tipao:  
			if(pDATA->tipo!=b_analogico && pDATA->tipo!=b_pan && pDATA->tipo!=g1tiplc 
			   && pDATA->tipo!=g1tipls && pDATA->tipo!=g1tiphc && pDATA->tipo!=g1tiphs)
			{
				sprintf(szBuffer,"Tipo errato [%s] tipo %hd\n",szSigla,tipo);
				fputs(szBuffer,fpINSTALL);
				bErrore=1;
			}
			break;   
		
		// Digitale
		case g1tipda: case g1tipds: case g1tipdc: case g1tipdd:
			if(pDATA->tipo!=b_digitale && pDATA->tipo!=b_pdi) 
			{
				sprintf(szBuffer,"Tipo errato [%s] tipo %hd\n",szSigla,tipo);
				fputs(szBuffer,fpINSTALL);
				bErrore=1;
			}
			break;         
		
		// Comando		
		case g1tipdo:   
			if(pDATA->tipo!=b_pdo)
			{
				sprintf(szBuffer,"Tipo errato [%s] tipo %hd\n",szSigla,tipo);
				fputs(szBuffer,fpINSTALL); 
				bErrore=1;
			}
			break;
		
		// Organo o Intero
		case g1tipor:
			if(pDATA->tipo!=b_intero && pDATA->tipo!=b_por && pDATA->tipo!=b_organo) 
			{
				sprintf(szBuffer,"Tipo errato [%s] tipo %hd\n",szSigla,tipo);
				fputs(szBuffer,fpINSTALL);
				bErrore=1;
			}
			break;
		
		// Stringa
		case g1tipst:
		    if(pDATA->tipo!=b_stringa && pDATA->tipo!=b_pst) 
			{
				sprintf(szBuffer,"Tipo errato [%s] tipo %hd\n",szSigla,tipo);
				fputs(szBuffer,fpINSTALL);
				bErrore=1;
			}
			break;
		
		default:
			if(pDATA->name[0]==' ')
				strcpy(szSigla,"Blank");
			{
				sprintf(szBuffer,"Punto [%s]\n",szSigla);
				fputs(szBuffer,fpINSTALL);
				bErrore=1;
			}
			break;
		}
		
		// Link
 		if(i<pDATAB->n_link)
 		{
 			// identifica soglie allarmi
 			if(pDATA->tipo>=g1tipls && pDATA->tipo<=g1tiphs)
 				pDBS->ext=(char) pDATA->tipo+1;
			else 
				pDBS->ext=0;
				
 			pDBS->tipo=(char) tipo;
 			pDBS->indice=indice;
 			*psh=pDATA->ind;
 			psh++;
 			pDBS++;
 		}
 		// Costante puntatore
 		else
 		{                
	 		memcpy(pLog->chDBL+(pDATA->ind & 0x7FF),&tipo,2); 
 			memcpy(pLog->chDBL+(pDATA->ind & 0x7FF)+2,&indice,2);
 		}                                                                        
	}

	// Chiude i file aperti
	fclose(fpINSTALL);
	fclose(fpTCF);
	fclose(fpFNOMI);
	
	// Libera la memoria
	if(lLink)
		free(pDATAsave);
	
	return(!bErrore);
}

int SistemaPol(char *nome)
{
char nome_file_input[FILENAME_MAX+1];
char nome_file_output[FILENAME_MAX+1];
FILE *fp_in,*fp_out;
char riga[MAXRIGA];

if(nome==NULL)
	errore_SistemaPol("tabulato nullo");

sprintf(nome_file_input,"%s/%s.%s",path_txt,nome,EXT_POL_IN);
sprintf(nome_file_output,"%s/%s",path_txt,nome);
printf("SistemaPol  [%s]->[%s]\n",nome_file_input,nome_file_output);

if((fp_in=fopen(nome_file_input,"r"))==NULL)
	errore_SistemaPol("nome_file_input");

if((fp_out=fopen(nome_file_output,"w"))==NULL)
	errore_SistemaPol("nome_file_output");

// sistema define
rewind(fp_in);
while(legge_riga(fp_in,riga))
	if(strncasecmp(riga,DEFINE,strlen(DEFINE))==0)
		fprintf(fp_out,"%s\n",riga);
// sistema data
rewind(fp_in);
while(legge_riga(fp_in,riga))
	if(strncasecmp(riga,DATA,strlen(DATA))==0)
		{
		if(!sostData(riga))
			errore_SistemaPol("errore sostData");
		fprintf(fp_out,"%s\n",riga);
		}
// sistema define
rewind(fp_in);
while(legge_riga(fp_in,riga))
	if(strncasecmp(riga,LINK,strlen(LINK))==0)
		{
		if(!sostLink(riga))
			errore_SistemaPol("errore sostLink");
		fprintf(fp_out,"%s\n",riga);
		}

// scrive il resto
rewind(fp_in);
while(legge_riga(fp_in,riga))
	if((strncasecmp(riga,LINK,strlen(LINK))!=0)&&
		(strncasecmp(riga,DATA,strlen(DATA))!=0) &&
			(strncasecmp(riga,DEFINE,strlen(DEFINE))!=0))
		{
		fprintf(fp_out,"%s\n",riga);
		if(strncasecmp(riga,ENTRY_INIT,strlen(ENTRY_INIT))==0)
			fprintf(fp_out,"%s\n",ENTRY_INIT_ADD);
		if(strncasecmp(riga,ENTRY_PERIODIC,strlen(ENTRY_PERIODIC))==0)
			fprintf(fp_out,"%s\n",ENTRY_PERIODIC_ADD);
		if(strncasecmp(riga,ENTRY_TERM,strlen(ENTRY_TERM))==0)
			fprintf(fp_out,"%s\n",ENTRY_TERM_ADD);

		}
fclose(fp_in);
fclose(fp_out);
return(1);
}

int legge_riga(FILE* fp,char *riga)
{
char cBuff[MAXRIGA],*pc;

memset(riga,0,MAXRIGA);
if(fgets(riga,MAXRIGA,fp)==NULL)
	return(0);
if(strlen(riga))
	riga[strlen(riga)-1]=0;

strcpy(cBuff,riga);
for(pc=cBuff;*pc==' ';pc++);
strcpy(riga,pc);
return(1);
}

void EliminaFileAppoggio(S_LOGPROP *logprop)
{
char szBuffer[FILENAME_MAX];

sprintf(szBuffer,"%s/%s",path_txt,logprop->szNome);
remove(szBuffer);

sprintf(szBuffer,"%s/%s.AB",path_txt,logprop->szNome);
remove(szBuffer);

sprintf(szBuffer,"%s/%s.MAP",path_txt,logprop->szNome);
remove(szBuffer);

sprintf(szBuffer,"%s/%s.OBJ",path_txt,logprop->szNome);
remove(szBuffer);

sprintf(szBuffer,"%s/%s.PLN",path_txt,logprop->szNome);
remove(szBuffer);

sprintf(szBuffer,"%s/%s.tcf",path_txt,logprop->szNome);
remove(szBuffer);

sprintf(szBuffer,"%s/%s.sor",path_txt,logprop->szNome);
remove(szBuffer);

}

void ToLower(char *szBuffer)
{
for(;*szBuffer;szBuffer++)
	*szBuffer=tolower(*szBuffer);
}

void ToUpper(char *szBuffer)
{
for(;*szBuffer;szBuffer++)
	*szBuffer=toupper(*szBuffer);
}

int sostLink(char *riga)
{
char *app;
char *var;
char nomeNew[SCD_SIGLA_CORTA];

if((app=strstr(riga,":"))==NULL)
	return(0);
++app;
while(*app==' ') ++app;
//printf("riga [%s]\n",riga);
var = malloc(strlen(app)+1);
strcpy(var,app);
for(app=var;*app;app++)
	if((*app==' ')||(*app==')'))
		break;
*app=0;
memset(var_sost[prog_sost],0,SCD_SIGLA);
memcpy(var_sost[prog_sost],var,strlen(var));
sprintf(nomeNew,"V%d",prog_sost);
++prog_sost;
if(prog_sost==MAX_SIGLE_SOST)
	{
	fprintf(stderr,
	"Raggiunto il massimo delle sigle sostituibili (MAX_SIGLE_SOST = %d)\n",
		MAX_SIGLE_SOST);
	return(0);
	}

if((app=strstr(riga,":"))==NULL)
	return(0);
++app;
*app=0;
strcat(riga,nomeNew);
strcat(riga,")");
//printf("Nuova riga = [%s] [%s]\n",riga,var);

return(1);
}

int sostData(char *riga)
{
char cBuff[MAXRIGA];
char szSep[]=" ";
char *token;

strcpy(cBuff,riga);
token=strtok(cBuff,szSep);
token=strtok(NULL,szSep);
if(token)
{
        if(!strncasecmp(token,UC_PA,strlen(UC_PA)) ||
           !strncasecmp(token,UC_PD,strlen(UC_PD)) ||
           !strncasecmp(token,UC_PO,strlen(UC_PO)) ||
           !strncasecmp(token,UC_PS,strlen(UC_PS)) ||
           !strncasecmp(token,UC_PC,strlen(UC_PC)))
                return(sostLink(riga));
}
  
return(1);
}

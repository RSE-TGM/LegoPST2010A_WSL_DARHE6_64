/*
 * File : Legoser.c
 * Abstract:
 *       Lego Model Server
 *       
 *       By: A. Guagliardi, G. Migliavacca
 */
 
#define SERVER     0
#define CLIENT     1
#define TERMINATOR 2

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "legoser.h"

HANDLE CreateMap(HANDLE,LPSTR, int);
LPVOID MapView(HANDLE);
HANDLE OpenMap(LPSTR);
int CercaInd(int, char *);
int leggiSimul(void);
int leggilinea( int modo, char *linea, char **token, int *numtoken);

extern void LGINISER();
extern void LGDYNSER();
extern void LGSERSTP();

int main(int argc,char **argv)
{
	int cliser;
	int i, j, k, jusc;
	FILE *fpp;
	
	static HANDLE hEveS,hEveC,hEveSINIT; //handle semafori server/client
	DWORD retWait;

	//static float *pShrMem1 = NULL; //puntatore shared memory
	static HANDLE hMem1    = NULL; //handle shared memory	
 

	HANDLE 	FileToBeMapped; //nome file condiviso (essendo in memoria
							//ha un nome convenzionale)
//	LPSTR MapName="SharedLego";   //nome dell'area di memoria shared
	char MapName[20]="SharedLego";   //nome dell'area di memoria shared
	char varsearch[9], var100[101];
	int PRIMO_PASSO;
	
	if(argc != 3) {
		printf("Pochi o troppi argomenti!\n");
		exit(0);
	}
	if (*argv[1]=='c')	cliser=CLIENT;
	else if (*argv[1]=='s') cliser=SERVER;
	else if (*argv[1]=='t')	cliser=TERMINATOR;
// leggo la stringa necessaria alla composizione dei nomi dei shared
	strcat(EVES,argv[2]);
	strcat(EVESINIT,argv[2]);
	strcat(EVEC,argv[2]);
	strcat(MapName,argv[2]);

	switch( cliser )
	{

	  case TERMINATOR:
		  if( (hMem1=OpenMap( (LPSTR) MapName)) == NULL) {  //aggancio a shared memory
			printf("provmap Client: Shared memory assente\n");
			return(1);
		}
		pShrMem1 = (MEMORIASHARED *) MapView(hMem1); //iniz. puntatore shared memory
        	pShrMem1->control[1]=1; //flag di terminazione
		CloseHandle(hMem1);
		break;

	  case SERVER:
		hEveS = CreateEvent( NULL ,TRUE,FALSE,EVES); 
		hEveC = CreateEvent( NULL ,TRUE,TRUE,EVEC); 
		FileToBeMapped = (HANDLE) 0xFFFFFFFF;	
		hMem1=CreateMap( FileToBeMapped, (LPSTR) MapName, sizeof(MEMORIASHARED));
		pShrMem1 = (MEMORIASHARED *) MapView(hMem1);
		pShrMem1->control[0]=0;
		pShrMem1->control[1]=0;

// INIZIALIZZAZIONE LEGO

		LGINISER();
		
		
// INIZIALIZZAZIONE SHARED MEMORY
		jusc=0;
		for (j=0,k=0;j<_CINPAR1.NEQSIS;j++,k+=8) {
			strncpy(varsearch,&_CC0LG5D.SIVAR[0][k],8);
			varsearch[8]='\0';
//			printf("usc ----  %s\n",varsearch);
			strcpy(pShrMem1->nomexy[j],varsearch);
//			printf("%s \n",pShrMem1->nomexy[j]);
			pShrMem1->xy[j]=_CC0LG5A.XY[j];
		}
		for (j=0,k=0;j<_CINPAR1.NU;j++,k+=8) {
			strncpy(varsearch,&_CC0LG5D.VARI[0][k],8);
			varsearch[8]='\0';
//			printf("ing ----  %s\n",varsearch);
			strcpy(pShrMem1->nomeuu[j],varsearch);
//			printf("%s \n",pShrMem1->nomeuu[j]);
			pShrMem1->uu[j]=_CC0LG5A.UU[j];
		}
		for (j=0;j<_CINPAR1.NDATI;j++) {
			pShrMem1->dati[j]=_CC0LG5A.DATI[j];
		}
//GUAG 6/4/2001 copia descrizioni in shared
		for(j=0,k=0;j<_CINPAR1.NU;j++,k+=100) {
			strncpy(var100,&_CSERDESC.NMVARI[0][k],100);
			var100[99]='\0';
//			printf("%d ingressi %d----  %s\n",j, k, var100);
			strcpy(pShrMem1->descruu[j],var100);
		}
		for(j=0,k=0;j<_CINPAR1.NEQSIS;j++,k+=100) {	
			strncpy(var100,&_CSERDESC.NMSIVA[0][k],100);
			var100[99]='\0';
//			printf("%d uscite %d----  %s\n",j, k, var100);
			strcpy(pShrMem1->descrxy[j],var100);
		} 

//GUAG 3/4/2001: carico in shared l passo di integrzione del lego
		pShrMem1->dtint=_CINTEGR.DTINT;
//		printf("%f passo di integrazione----\n",pShrMem1->dtint);	
// Scrittura numero uscite e numero ingressi nella shared mem
		pShrMem1->nxy=_CINPAR1.NEQSIS;
		pShrMem1->nuu=_CINPAR1.NU;
//GUAG 3/4/2001:   era 	pShrMem1->nuu=_CINPAR1.NU;	
		pShrMem1->ndati=_CINPAR1.NDATI;

// Copia nella shared mem delle vettore delle norm.		
		for(j=0;j<_CINPAR1.NEQSIS;j++) {
			pShrMem1->cnxy[j]=_CSERBIDO.CNXY[j];
//			printf(" _CSERBIDO.CNXY[%d]=%f\n", j, _CSERBIDO.CNXY[j]);
		} 
		for(j=0;j<_CINPAR1.NU;j++) {
			pShrMem1->cnuu[j]=_CSERBIDO.CNUU[j];
//			printf(" _CSERBIDO.CNUU[%d]=%f\n", j, _CSERBIDO.CNUU[j]);			
		} 

// libero il client perche' ho finito di l'init di LEGO
		hEveSINIT = CreateEvent( NULL ,TRUE,TRUE,EVESINIT); 
		
		while( pShrMem1->control[1] < 0.1 ) {		
			retWait = WaitForSingleObject(  hEveS,INFINITE); 		
//			ResetEvent(hEveC);
			if(pShrMem1->control[1] > 0.1 ) break;
			pShrMem1->control[0]+=1;	
//			printf("Elaborazioni del server...%d, NVART=%d, VAR\n",
//			       pShrMem1->control[0],_CINPAR1.NVART);	
// COPIA UU shared IN  Lego	 
		for(j=0;j<_CINPAR1.NU;j++) {
			_CC0LG5A.UU[j]=pShrMem1->uu[j];
		} 
// Guag 3/4/2001 aggiorno il passo d integrazione se viene modificato run time dall'utente 
		_CINTEGR.DTINT=pShrMem1->dtint;	
		PRIMO_PASSO = ((pShrMem1->tempo) == 0) ? 1 : 0;
		if (PRIMO_PASSO && RESTART) {
			for(j=0;j<_CINPAR1.NVART;j++) {
				_CC0LG5A.XY[j]=pShrMem1->xy[j];   		
			}
			for(j=0;j<_CINPAR1.NDATI;j++) {
				_CC0LG5A.DATI[j]=pShrMem1->dati[j];   		
			}
		}
// PASSO LEGO
//			printf("Elaborazioni del server...prima ALZA=%f\n",
//			       pShrMem1->uu[6]);	
			LGDYNSER();

// COPIA XY LEGO IN Shared
		for(j=0;j<_CINPAR1.NVART;j++) {
			pShrMem1->xy[j]=_CC0LG5A.XY[j];   
		} 
// Tempo e passo di integr.
		pShrMem1->tempo=_CINTEGR.TEMPO;
		
		printf("Elaborazioni del server num %d\n------> Tempo %f\n",
			pShrMem1->control[0],
			pShrMem1->tempo);	


// Guag 3/4/2001		pShrMem1->dtint=_CINTEGR.DTINT;			
//			if( retWait == WAIT_FAILED) printf( "WAIT_FAILED\n");
//			else if ( retWait == WAIT_ABANDONED ) printf( "WAIT_ABANDONED\n");
//			else if ( retWait == WAIT_OBJECT_0 ) printf( "WAIT_OBJECT_0 \n");
//			else if ( retWait == WAIT_TIMEOUT ) printf( "WAIT_TIMEOUT \n");
//			else if ( retWait == WAIT_IO_COMPLETION ) printf( "WAIT_IO_COMPLETION \n");
//			else printf( "retWait sconosciuto\n");
			ResetEvent(	hEveS);	
			SetEvent(hEveC);
		}		
		LGSERSTP();
		printf("Server: Fine programma\n");
		fflush(stdout);
		CloseHandle(hEveS);
		CloseHandle(hEveSINIT);
		CloseHandle(hEveC);
		UnmapViewOfFile( pShrMem1 );
		CloseHandle(hMem1);
		break;
	  case CLIENT:
		// Creazione event per l'attesa della fine dell'init del server
		while ((hEveSINIT = OpenEvent( EVENT_ALL_ACCESS  ,TRUE,EVESINIT) ) == NULL);
		retWait = WaitForSingleObject(  hEveSINIT,INFINITE); 		

		
		hEveS = OpenEvent( EVENT_ALL_ACCESS  ,TRUE,EVES); 
		hEveC = OpenEvent( EVENT_ALL_ACCESS  ,TRUE,EVEC); 
		if( (hMem1=OpenMap( (LPSTR) MapName)) == NULL) {
				printf("provmap Client: Shared memory assente\n");
				return(1);
		}
		pShrMem1 = (MEMORIASHARED *) MapView(hMem1);
//// Calcolo indirizzi nel vettore XY e UU delle variabili di scambio
//		strcpy(varsc_usc[0].nome,"PCOL0___");
//		if( (varsc_usc[0].ind=CercaInd(TIPOXY,varsc_usc[0].nome))<0) {
//			printf("Variabile di scambio %s inesistente\n",varsc_usc[0].nome);
//			return(1);
//		}		
//		num_usc=1;
//		strcpy(varsc_ing[0].nome,"ALZA2___");
//		if( (varsc_ing[0].ind=CercaInd(TIPOUU,varsc_ing[0].nome))<0) {
//			printf("Variabile di scambio %s inesistente\n",varsc_ing[0].nome);
//			return(1);
//		}			
//		num_ing=1;
// Calcolo indirizzi nel vettore XY e UU delle variabili di scambio
//		strcpy(varsc_usc[0].nome,"PCOL0___");
		 fpp=fopen("tasks.dat","r");
		 fscanf(fpp,"%s",modelPath);
		 fclose(fpp);
  	 
		 strcpy(nomefile,modelPath);
		 strcat(nomefile,fileDati);
    
//    printf("prima di leggiSim  %s\n",modelPath); 
      
//		printf("NOMEFILE: %s\n",nomefile);
		leggiSimul();
   
//    		printf("dopo  leggiSim    %d %d %s\n",num_ing,num_usc,modelPath);

		for(i=0;i<num_usc;i++){
		if( (varsc_usc[i].ind=CercaInd(TIPOXY,varsc_usc[i].nome))<0) {
			printf("Variabile di scambio %s inesistente\n",varsc_usc[i].nome);
			return;
		}
//		printf("mdlInitializeSizes: %s varsc_usc[%d].ind=%d \n",varsc_usc[i].nome,i,varsc_usc[i].ind);
		}		
//		num_usc=1;
//		strcpy(varsc_ing[0].nome,"ALZA2___");
		for(i=0;i<num_ing;i++){
		if( (varsc_ing[i].ind=CercaInd(TIPOUU,varsc_ing[i].nome))<0) {
			printf("Variabile di scambio %s inesistente\n",varsc_ing[i].nome);
			return;
		}
//		printf("mdlInitializeSizes: %s varsc_ing[%d].ind=%d \n",varsc_ing[i].nome,i,varsc_ing[i].ind);
		}			
//		num_ing=1;

		while(pShrMem1->control[1] < 0.1) {		
			retWait = WaitForSingleObject(  hEveC,INFINITE); 
			ResetEvent(hEveS);
			pShrMem1->control[0]+=1;	

//CONTROLLO PERTURBAZIONI
//			if(pShrMem1->tempo > 10) pShrMem1->uu[varsc_ing[0].ind]=1.0/pShrMem1->cnuu[varsc_ing[0].ind];
			printf("Elaborazioni del client num %d\n------> Tempo %f...ING(0)=%f USC(0)=%f\n",
			      pShrMem1->control[0],
			      pShrMem1->tempo,
			      (pShrMem1->uu[varsc_ing[0].ind])*(pShrMem1->cnuu[varsc_ing[0].ind]),
			      (pShrMem1->xy[varsc_usc[0].ind])*(pShrMem1->cnxy[varsc_usc[0].ind])
			);		
			ResetEvent(hEveC);
			SetEvent(hEveS);
		}
		CloseHandle(hEveS);
		CloseHandle(hEveSINIT);
		CloseHandle(hEveC);
		CloseHandle(hMem1);
		break;
	}
return(0);
}


int controlla_errore()
{
	LPVOID lpMsgBuf;

    FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
);

// Display the string.
//MessageBox( NULL, lpMsgBuf, "GetLastError", MB_OK|MB_ICONINFORMATION );
printf("massaggio di errore: %s\n",lpMsgBuf);
// Free the buffer.
LocalFree( lpMsgBuf );
return(0);
}


HANDLE CreateMap(HANDLE FileToBeMapped, LPSTR MapName, int dimshared)
{
   HANDLE MapHandle;

   MapHandle= CreateFileMapping(FileToBeMapped,
                                NULL,
                                PAGE_READWRITE,
                                0,
                                dimshared,
                                MapName);

   if (MapHandle == NULL)
   {
      fprintf(stderr,"CreateFileMapping\n");
      return(NULL);
   }
   else
      return(MapHandle);
}


LPVOID MapView(HANDLE hMap)
{
   LPVOID MappedPointer;

   MappedPointer= MapViewOfFile(hMap,
                                FILE_MAP_WRITE | FILE_MAP_READ,
                                0, 0, 0);
   if (MappedPointer == NULL)
   {
      fprintf(stderr,"MapViewOfFile\n");
      return(NULL);
   }
   else
      return(MappedPointer);
}
HANDLE OpenMap( LPSTR MapName)
{
   HANDLE hAMap;

   hAMap= OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
                          TRUE,
                          MapName);

   if (hAMap == NULL)
   {
      fprintf(stderr,"OpenFileMapping\n");
      return(NULL);
   }
   else
      return(hAMap);
}

int CercaInd(int tipo, char *nome) {
	int i;
	
//	printf("%d %d\n",pShrMem1->nxy,pShrMem1->nuu);
	
	switch (tipo)
	{
	 case TIPOXY:
		for (i=0;i< pShrMem1->nxy ; i++)
	     		if(!strcmp(nome,pShrMem1->nomexy[i])) return(i);
	     	break;
	 case TIPOUU:
	 	for (i=0;i< pShrMem1->nuu ; i++)
	     		if(!strcmp(nome,pShrMem1->nomeuu[i])) return(i);
	     	break;
	}
	printf("Client: Errore. la variabile %s non esiste\n",nome);
	return(-1);
}

int leggiSimul() {

   char linea[MAXRIGA];
   char *token[ MAXTOK ];
   int numtoken[1], k, retlegg;
   
//   printf("in LEGGISIMUL \n");

   retlegg=leggilinea( APRI,  linea, token, numtoken);
   if ( retlegg == EOF ) {
	printf("fallita apertura del file\n");
	return( EOF );
   }

//   printf("prima di LEGGILINEA\n");

   if (leggilinea( LEGGI,  linea, token, numtoken)== EOF ) return ( EOF );
   
//   printf("dopo LEGGILINEA\n");
   
   while( strstr(token[1],"END") == NULL) {
   	if( strstr(token[1],"TSTEP") != NULL) {
//   	   	printf("in TSTEP\n");
   		if (leggilinea( LEGGI,  linea, token, numtoken)== EOF ) return ( EOF );
   		tstep=atof(token[0]);
   	} else if( strstr(token[1],"INPUTS") != NULL) {
    		
   		num_ing=atoi(token[2]);
//   		printf("in INPUTS num_ing=%d\n",num_ing);
   		for( k=0; k< num_ing; k++){
   			 if (leggilinea( LEGGI,  linea, token, numtoken)== EOF ) return ( EOF );
//   			 printf("in INPUTS 1 %s\n",token[0]);
   			 strcpy(varsc_ing[k].nome,token[0]);
//   			 printf("in INPUTS 2 %s\n",varsc_ing[k].nome);
//   			 if( (varsc_ing[k].ind=CercaInd(TIPOUU,varsc_ing[k].nome))<0) {
//			  	printf("Variabile di scambio %s inesistente\n",varsc_ing[k].nome);
//			  	return(1);
//			 }
		}			   			
   	} else if( strstr(token[1],"MONITORED") != NULL) {
//   		printf("in OUTPUTS\n");
   		num_usc=atoi(token[2]);
   		for( k=0; k< num_usc; k++){
   			 if (leggilinea( LEGGI,  linea, token, numtoken)== EOF ) return ( EOF );
   			 strcpy(varsc_usc[k].nome,token[0]);
//   			 if( (varsc_usc[k].ind=CercaInd(TIPOXY,varsc_usc[k].nome))<0) {
//			  	printf("Variabile di scambio %s inesistente\n",varsc_usc[k].nome);
//			  	return(1);
//			 }			   			
		}  
 	}
 	if (leggilinea( LEGGI,  linea, token, numtoken)== EOF ) return ( EOF );
// 	for (k=0;k< *numtoken;k++) printf("--------------->%s\n",token[k]);
    }   	
   	
//  Chiusura del file 
    leggilinea( CLOSE,  linea, token, numtoken);
//    printf("in LEGGISIMUL 2    %d %d %s\n",num_ing,num_usc,modelPath);
    return(0);
}
//int leggilinea( int modo, char *linea, char **token, int *numtoken) {
//printf("leggilineaFinta:\n");
//fflush(stdout);
//printf("leggilineaFinta: %d EOF=%d linea=%s *numtoken=%d\n", modo, EOF, linea, *numtoken);
//}


int leggilinea( int modo, char *linea, char **token, int *numtoken) {

   static FILE *fp;
   static char delimiters[]=" ,;\t\n";
   char   *pstr ;
   int    c, k;
//printf("in leggilinea : %s %s \n",GetCurrentDirectory( CurDirLengthbuf, CurDir),nomefile);
//printf("in leggilinea : %s \n",nomefile);



   switch ( modo )
   {	 
    case APRI:
//    	   printf("in leggilinea (APRI):  %s \n", nomefile);
    	   fflush(stdout);
    	   fp = fopen(nomefile, "r" );
//    	   	printf("Aperto file\n");
		if (fp == NULL) return (EOF);
		return (0);
		break;

    case CLOSE:
		if (fp != NULL) fclose (fp);
		return (0);
		break;

    case LEGGI:	  
	   *numtoken=0;
           for (k=0; (c = fgetc( fp)) != '\n'; k++) {
	   if (c == EOF) {
//	    fprintf(stderr, "ATTENZIONE end_of_file del file %s\n",nomefile);
	    return ( EOF );
	   }
	   if (k == MAXRIGA-1) {
//	    fprintf(stderr, "ATTENZIONE riga %d supera %d caratteri.\n", linea, MAXRIGA);
//sprintf(buff, "Errore lettura file: la riga %d supera %d caratteri.\n", linea, MAXRIGA);
//MessageBox(hwnd, (LPCTSTR)buff , "ATTENZIONE", MB_OK | MB_ICONSTOP);
	    return ( 1 );
	   }
	   linea[k]=c;
	   }
	   linea[k]= (char)NULL;
//              printf("linea: %s\n",linea);
	   if ((pstr = strtok(linea, delimiters ))
	    != NULL) {
	   /* pstr points to the first token */
//	        printf("Token 1 is %s\n", pstr);
	   (*numtoken)++;
	   token[ *numtoken -1 ]= pstr;         
// 	   printf("token 1 : %s\n",token[ *numtoken -1 ]); 
	   while ((pstr = strtok((char *)NULL, delimiters )) != NULL) {
//	        printf("Token %d is %s\n", counter, pstr);
	     (*numtoken)++;
	     token[ *numtoken -1 ]= pstr;
//	        printf("token %d : %s\n",*numtoken, token[ *numtoken -1 ]); 
	     }
	  }
   }
}

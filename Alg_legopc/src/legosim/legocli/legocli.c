/*
 * File : LegoCli.c
 * Abstract:
 *       Lego Model Client
 *       
 *       By: A. Guagliardi, G. Migliavacca
 */

// Questa versione di LegoCli supporta al massimo 10 task per schema simulink. Se necessario aumentare #ifdef CLIn.
#ifdef CLI0
	#define S_FUNCTION_NAME  LegoCli
#endif
#ifdef CLI1
	#define S_FUNCTION_NAME  LegoCli1
#endif
#ifdef CLI2
	#define S_FUNCTION_NAME  LegoCli2
#endif
#ifdef CLI3
	#define S_FUNCTION_NAME  LegoCli3
#endif
#ifdef CLI4
	#define S_FUNCTION_NAME  LegoCli4
#endif
#ifdef CLI5
	#define S_FUNCTION_NAME  LegoCli5
#endif
#ifdef CLI6
	#define S_FUNCTION_NAME  LegoCli6
#endif
#ifdef CLI7
	#define S_FUNCTION_NAME  LegoCli7
#endif
#ifdef CLI8
	#define S_FUNCTION_NAME  LegoCli8
#endif
#ifdef CLI9
	#define S_FUNCTION_NAME  LegoCli9
#endif	

#define S_FUNCTION_LEVEL 2

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "simstruc.h"

#include "LegoClient.h"

//static MEMORIASHARED  *pShrMem1;

#define LUNGCURDIRBUF 100
DWORD CurDirLengthbuf=LUNGCURDIRBUF;
int CurDirLength;
static char modelPath[LUNGCURDIRBUF];
char CurDir[LUNGCURDIRBUF]; 

int primavolta=0;

float tstep;
char startServer[20];


#define MAXRIGA 100
#define MAXTOK 20

#define APRI 0
#define LEGGI 1
#define CLOSE 2

#define PARAM1(S) ssGetSFcnParam(S, 0)

char *fileDati;
static char nomefile[LUNGCURDIRBUF];

int leggilinea( int, char *, char **, int *);

void LegoClient( int);
int leggiSimul(void);
FILE *fpp;

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{
    int i, imodel;
    char MapName[20];   //nome dell'area di memoria shared    
    char strparamet[3];

// leggo il parametro (indice task nel file tasks.dat)
    ssSetNumSFcnParams(S, 1);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch will be reported by Simulink */
    }
    imodel=(int)mxGetPr(PARAM1(S))[0];
    sprintf(strparamet,"%i",imodel);
// leggo il path della task
    fpp=fopen(tasksname,"r");
    if(fpp==NULL) printf("Non riesco ad aprire il file tasks.dat \n");
    for (i=0;i<imodel;i++) fscanf(fpp,"%s",modelPath);
    fclose(fpp);
// salvo il path completo del file simul.dat
    strcpy(nomefile,modelPath);
    strcat(nomefile,simulname);
// appendo l'indice imodel alle risorse condivise    
    strcpy(EVES,evesbase);
    strcat(EVES,strparamet);
    
    strcpy(EVESINIT,evesinitbase);
    strcat(EVESINIT,strparamet);
    
    strcpy(EVEC,evecbase);    
    strcat(EVEC,strparamet);
    
    strcpy(MapName,sharelegobase);
    strcat(MapName,strparamet);
// preparo la frase di chiamata del server    
    strcpy(startServer,startserverbase);
    strcat(startServer, " ");
    strcat(startServer, strparamet);
    
    leggiSimul();
    
    if(num_ing > MAXING) {
       ssSetStopRequested(S,1); 
       ssSetErrorStatus(S,"Error: too many inputs");
       return;
    }
    if(num_usc > MAXUSC) {
       ssSetStopRequested(S,1);     
       ssSetErrorStatus(S,"Error: too many outputs");
       return;
    }
    
//    printf("mdlInitializeSizes parametro %f (stringa) %s\n",mxGetPr(PARAM1(S))[0], strparamet);
    
    if (!ssSetNumInputPorts(S, 1)) return;
    
//    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetInputPortWidth(S, 0, num_ing);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S,1)) return;
//    ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetOutputPortWidth(S, 0, num_usc);

    ssSetNumSampleTimes(S, 1);

    /* Take care when specifying exception free code - see sfuntmpl.doc */
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);

//	LegoClient( INIT);
	if(primavolta==0) {
		primavolta=1;
// Lancio di lgser, open shared memory e event, calcolo dei puntatori alle variabili XY e UU
		CurDirLength=GetCurrentDirectory( CurDirLengthbuf, CurDir);
 		SetCurrentDirectory(modelPath);
 		WinExec(startServer,SW_MINIMIZE);
 		SetCurrentDirectory(CurDir);
//    printf("in LEGGISIMUL 3   %s \n",startServer);
// Open event per l'attesa della fine dell'init del server
		while ((hEveSINIT = OpenEvent( EVENT_ALL_ACCESS  ,TRUE,EVESINIT) ) == NULL);
		retWait = WaitForSingleObject(  hEveSINIT,TASK_TIMEOUT);
		if(retWait == WAIT_TIMEOUT) {
		    ssSetStopRequested(S,1); 
		    ssSetErrorStatus(S,"LEGO Error: Task Aborted");
		    return;
		    }
		hEveS = OpenEvent( EVENT_ALL_ACCESS  ,TRUE,EVES); 
		hEveC = OpenEvent( EVENT_ALL_ACCESS  ,TRUE,EVEC); 
//		printf("provmap Client: hEveS=%d hEveC=%d\n",hEveS,hEveC);
		if( (hMem1=OpenMap( (LPSTR) MapName)) == NULL) {
				printf("provmap Client: Shared memory assente\n");
				return;
		}
		pShrMem1 = (MEMORIASHARED *) MapView(hMem1);
		RESTART = 1; // inizializzo il flag di restart a true
// Calcolo indirizzi nel vettore XY e UU delle variabili di scambio
//		strcpy(varsc_usc[0].nome,"PCOL0___");
	}
	for(i=0;i<num_usc;i++){
	if( (varsc_usc[i].ind=CercaInd(TIPOXY,varsc_usc[i].nome))<0) {
		printf("Variabile di scambio %s inesistente\n",varsc_usc[i].nome);
		return;
	}
//	printf("mdlInitializeSizes: %s varsc_usc[%d].ind=%d \n",varsc_usc[i].nome,i,varsc_usc[i].ind);
	}		
	for(i=0;i<num_ing;i++){
	if( (varsc_ing[i].ind=CercaInd(TIPOUU,varsc_ing[i].nome))<0) {
		printf("Variabile di scambio %s inesistente\n",varsc_ing[i].nome);
		return;
	}
//	printf("mdlInitializeSizes: %s varsc_ing[%d].ind=%d \n",varsc_ing[i].nome,i,varsc_ing[i].ind);
	
//Inizializzazione numero stati per restart (solo la prima volta)      
        ssSetNumDiscStates(S,pShrMem1->nxy+pShrMem1->nuu+pShrMem1->ndati+1);

	}			

}


/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy that we inherit our sample time from the driving block.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{	
//    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
//	printf("LegoCli: inizio mdlInitializeSampleTimes\n");    
    ssSetSampleTime(S, 0, tstep );   // chiamata alla S-Function ogni tstep secondi.
    ssSetOffsetTime(S, 0, 0.0);
//	printf("LegoCli: fine mdlInitializeSampleTimes\n");    
}

#define MDL_INITIALIZE_CONDITIONS
/* Function: mdlInitializeConditions ========================================
 * Abstract:
 *    Called if NOT restart
 */
static void mdlInitializeConditions(SimStruct *S)
{
    real_T 	      *xLEGO0   = ssGetRealDiscStates(S);
    *xLEGO0=0.;  // resetta il server di restart del client a false
}

/* Function: mdlOutputs =======================================================
 * Abstract:
 *    y = 2*u
 */
static int primo_passo=0;
char  buff[400];
char mess[4000];
static void mdlOutputs(SimStruct *S, int_T tid)
{
    int_T             i;
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);
    real_T            *y    = ssGetOutputPortRealSignal(S,0);
    int_T             input_width = ssGetInputPortWidth(S,0);
    int_T             output_width = ssGetOutputPortWidth(S,0);
    real_T 	      *xLEGO0   = ssGetRealDiscStates(S);
    float diff;
    int stop;
//	printf("LegoCli: inizio mdlOutputs input_width=%d output_width=%d\n",input_width,output_width);
//	printf("LegoCli: inizio mdlOutputs  %d %s \n", varsc_ing[0].ind,varsc_ing[0].nome);
	
    retWait = WaitForSingleObject(  hEveC,TASK_TIMEOUT);
    if(retWait == WAIT_TIMEOUT) {
		    ssSetStopRequested(S,1); 
		    ssSetErrorStatus(S,"LEGO Error: Task Aborted");
		    return;
    }
// Caricamento stati se prima volta e restart
        RESTART=(int)*xLEGO0++;
//        printf("--------------------------------->  RESTART=%d \n",RESTART);
    
        if(!primo_passo && RESTART) {
     	 for(i=0;i<pShrMem1->nxy;i++) {
    		pShrMem1->xy[i]=( float ) *xLEGO0++;
    	 }
    	 for(i=0;i<pShrMem1->nuu;i++) {
   		pShrMem1->uu[i]=( float ) *xLEGO0++;
    	 }
    	 
    	 strcpy(mess,"");
    	 for (i=0,stop=0; i<num_ing; i++)  {               
    		diff=(pShrMem1->uu[varsc_ing[i].ind] - (( float) *uPtrs[i])/pShrMem1->cnuu[varsc_ing[i].ind]);
    	        if( diff < -1.e-7 || diff > 1.e-7 ){
    	            stop=1;
		    sprintf(buff,"Ingresso %s = %f diverso dal valore di restart = %f\n",
		                     pShrMem1->nomeuu[varsc_ing[i].ind],
		                     ( float) *uPtrs[i],
		                     pShrMem1->uu[varsc_ing[i].ind]*pShrMem1->cnuu[varsc_ing[i].ind]);
		    strcat(mess,buff);
		}
 	 }
    	 if(stop) {
		strcat(mess,"\n\nContinuo?\n");
		if(MessageBox(GetFocus(), mess, "ATTENZIONE", MB_YESNO) == IDNO) {
		 ssSetErrorStatus(S,"Simulazione cancellata");
		 return;
		}
    	 }
    	 
    	 for(i=0;i<pShrMem1->ndati;i++) {
    		pShrMem1->dati[i]=( float ) *xLEGO0++;
    	 }    	 
//         printf("Stato LETTO=%f\n",*xLEGO0);
         primo_passo=1;
        }
// Copio le variabili calcolate da Simulink sulle variabili di ingresso di LEGO
    for (i=0; i<num_ing; i++) 
        pShrMem1->uu[varsc_ing[i].ind]=(*uPtrs[i])/pShrMem1->cnuu[varsc_ing[i].ind]; 
   
//    ResetEvent(hEveS);
    pShrMem1->control[0]+=1;
    for (i=0; i<num_usc; i++) 
	*y++ =  pShrMem1->xy[varsc_usc[i].ind]*pShrMem1->cnxy[varsc_usc[i].ind];	
//CONTROLLO PERTURBAZIONI
//    printf("Elaborazioni del client num %d\n------> Tempo %f...ING(0)=%f USC(0)=%f\n",
//			      pShrMem1->control[0],
//			      pShrMem1->tempo,
//			      pShrMem1->uu[varsc_ing[0].ind]*pShrMem1->cnuu[varsc_ing[0].ind],
//			      pShrMem1->xy[varsc_usc[0].ind]*pShrMem1->cnxy[varsc_usc[0].ind]);		
    ResetEvent(hEveC);
    SetEvent(hEveS);
}


/* Function: mdlmdlUpdate =====================================================
 * Abstract:
 *   States updating for restart
 */
#define MDL_UPDATE  /* Change to #undef to remove function. */
#if defined(MDL_UPDATE)
static void mdlUpdate(SimStruct *S,int_T tid)
{
    int i;
    real_T *xLEGO=ssGetRealDiscStates(S);//recupero stati per restart
//    printf("TFINAL=%f, TASKTIME=%f, GETT=%f,TID=%d\n",ssGetTFinal(S),ssGetTaskTime(S,tid),ssGetT(S),(int) tid);
//    printf("TEMPO=%f, DTINT=%f\n",pShrMem1->tempo,pShrMem1->dtint);
    if(ssGetTFinal(S) <= ssGetTaskTime(S,tid)+(pShrMem1->dtint)) {
        *xLEGO++=(real_T)1.;
    	for(i=0;i<pShrMem1->nxy;i++) {
    		*xLEGO++= (real_T)(pShrMem1->xy[i]);
    	}
    	for(i=0;i<pShrMem1->nuu;i++) {
    		*xLEGO++= (real_T)(pShrMem1->uu[i]);
    	}
    	printf("STATO SALVATO x(1)=%f\n",*xLEGO--);
    }
}
#endif /* MDL_UPDATE */ 
 
/* Function: mdlTerminate =====================================================
 * Abstract:
 *    No termination needed, but we are required to have this routine.
 */
static void mdlTerminate(SimStruct *S)
{

//	LegoClient( ENDLEGO );
//printf("LegoCli: Termino\n");

// 		WinExec("c:\\temp\\lgser\\lgser.exe t",SW_MINIMIZE);
		pShrMem1->control[1] = 1;  // Invio al server il comando di stop
		SetEvent(hEveS);
		primavolta=0;		
		primo_passo=0;
		RESTART = 1; 		// flag di restart a true

		CloseHandle(hEveSINIT);
		CloseHandle(hEveC);
		CloseHandle(hMem1);
		CloseHandle(hEveS);
}


#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif




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

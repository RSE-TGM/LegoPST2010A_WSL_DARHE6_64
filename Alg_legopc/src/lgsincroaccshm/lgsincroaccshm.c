
#include "windows.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LgShared.h"


MEMORIASHARED  *pShrMem1;

int main( int argc, char *argv[ ], char *envp[ ] )

{

/***  ATTENZIONE INSTANZA DELLA SHARED MEMORY UGUALE A 1  ( np ) 
	  Da modificare per un lgsincro multitask ***/
	strcat(MapName,"1");

	if( (hMem1=OpenMap( (LPSTR) MapName)) == NULL) 
	{
		MessageBox(NULL, "Shared memory assente!", "ATTENZIONE", MB_OK|MB_ICONINFORMATION);
		return (3);
	}
	pShrMem1 = (MEMORIASHARED *) MapView(hMem1);
	
//printf("Debug---->  argc=%d\n argv=%s NUU=%d\n",argc, argv[1], NUU);
    

    if(argc == 2) {
		if(strcmp(argv[1],"-pict") == 0) {
			pShrMem1->control[INDPICT] == 1;
				return(0);
		}
		if(strcmp(argv[1],"-nopict") == 0) {
			pShrMem1->control[INDPICT] == 0;
				return(0);
		}
        if(pShrMem1->control[INDACCSHM] == 1 ) {
printf("Debug---> pShrMem1->control[INDACCSHM] = %d pShrMem1->nomeuu[NUU-1]=%s\n", 
	   pShrMem1->control[3],pShrMem1->nomeuu[NUU-1]);		
			return(0);
		}
/*   Il nome della variabile di ingresso da perturbre è copiato in fondo al vettore nomeuu! 
     Non è una operazione a prova di errore ma l'errore è estremanmente improbabile: non funziona
	 con task con 1749 variabili di ingresso libere! 
	 L'operazione pulita avrebbe richiesto una modifica della shared memory con problemi 
	 con gli altri programmi della suite Legopc.*/

		strcpy(pShrMem1->nomeuu[NUU-1],argv[1]);
		pShrMem1->control[INDACCSHM] = 1;
//      return (pShrMem1->control[INDACCSHM]);
     return (0);
	}
    
	if(argc == 3) pShrMem1->control[INDACCSHM] = 0;
		

printf("Debug---> pShrMem1->control[INDACCSHM] = %d pShrMem1->nomeuu[NUU-1]=%s\n", 
	   pShrMem1->control[3],pShrMem1->nomeuu[NUU-1]);
    return (0);
//	return (pShrMem1->control[INDACCSHM]);

}

LPVOID MapView(HANDLE hMap)
{
   LPVOID MappedPointer;

   MappedPointer= MapViewOfFile(hMap,
                                FILE_MAP_WRITE | FILE_MAP_READ,
                                0, 0, 0);
   if (MappedPointer == NULL)
   {
//      AfxMessageBox("MapViewOfFile failed!");
MessageBox( NULL, "MapViewOfFile failed!", "ATTENZIONE", MB_OK|MB_ICONINFORMATION );
	   
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
//      AfxMessageBox("OpenFileMapping failed!");
MessageBox( NULL, "OpenFileMapping failed!", "ATTENZIONE", MB_OK|MB_ICONINFORMATION );
	   return(NULL);
   }
   else
      return(hAMap);
}

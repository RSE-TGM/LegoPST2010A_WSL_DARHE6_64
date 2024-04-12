

/** Scrittura del file f22.f22 leggibile in run-time da grafics per WinNT **/ 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>
#include <mmsystem.h>

#define N000 70
#define N001 N000*10
#define N002 N000*25 
#define N003 N000*50
#define N004 N000*25 
#define N005 N000*100 
#define N006 100
#define N007 N000*500
#define N008 40 
#define NR00 12 
#define NP00 10

#define M003 N002+1 
#define M004 N003+1
#define M005 N004+1
#define M001 N005-N003
#define M002 M001-N004

#define M006 N003*NR00
#define M007 2*M006
#define M008 5*N003
#define M009 8*N003

#define M010 N004+N003


#define MP01 NP00+1
#define MP02 NP00*200



double punti[M010+1];

void PREP_F22(int *param,int *nVAR,int *nsel, float *tempo, float *xyout[], char *syout, char *giasel)
{
	static char nomef22[100], var100[101], var8[9];
	static char titolo[100]={"titolazzo"}, str[200];
	static char nomef22tmp[]={".\\f22.f22"};

//	static int nVAR=pShrMem1->nuu+pShrMem1->nxy;
	int  i,j,k,k1;
	unsigned long bWrite;
	static HANDLE hf22;
printf("param=%d, nn=%d, nsel=%d, M002=%d TEMPO=%f\n", *param, *nVAR, *nsel, M002, *tempo);
	switch (*param)
	{
	case 1: //APRI
		strcat(nomef22,nomef22tmp);
printf("Creazione del file: %s\n", nomef22);
		hf22 = CreateFile(nomef22, GENERIC_READ | GENERIC_WRITE, 
			   	      FILE_SHARE_READ, 
					  (LPSECURITY_ATTRIBUTES) NULL, CREATE_ALWAYS,
				      FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);
		if (hf22 == INVALID_HANDLE_VALUE)
			return;

		WriteFile(hf22, titolo, 80, &bWrite, (LPOVERLAPPED) NULL);
		WriteFile(hf22, nVAR, sizeof(int), &bWrite, (LPOVERLAPPED) NULL);

		for(i=0, k=0;i< *nVAR;i++, k+=8)
		{
			strcpy(str," ");
			strncpy(str,&syout[k],8);
			strncpy(var8,str,8);
			var8[9]='\0';
			for( j=0, k1=0; j< *nsel; j++, k1+=100){
			      strncpy(var100,&giasel[k1],100);
			      var100[99]='\0';
			      if(strncmp(var8,var100,8) == 0) break;
			    }
			str[8]='\t';
			str[9]='\0';			
			strncat(str,var100+10,80);
			str[70]='\0';
//printf("%d-%d-%s\n",i,k1,str);			
			WriteFile(hf22, str, 80, &bWrite, (LPOVERLAPPED) NULL);
		}

		return ;

	case 2: //SCRIVI
		if (hf22 == INVALID_HANDLE_VALUE)
				return;

		SetFilePointer(hf22, 0, (PLONG) NULL, FILE_END);
		punti[0]=(double)(*tempo);
		for(i=0;i<(*nVAR);i++) 
		     punti[i+1]=(double)((*xyout)[i]);
//for(i=0;i<(10);i++) 
//   printf("xyout[%d]=%f tempo=%f\n",i,(*xyout)[i], *tempo);		
		WriteFile(hf22, punti, (*nVAR + 1)*sizeof(double), &bWrite, (LPOVERLAPPED) NULL);
//for(i=0;i<(15);i++) 
//   printf("xyout[%d]=%f tempo=%f\n",i,(*xyout)[i], *tempo);
   		return;
	case 3: //CHIUDI
	
   		CloseHandle(hf22);
   		return;
	}
return;
}



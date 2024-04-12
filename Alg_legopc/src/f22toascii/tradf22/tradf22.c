#define MAXVARS 5000
#define MAXVARSEL 100

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

char   titolo[81];
int    nVAR, nSel;
char   vsel[MAXVARSEL][9];
int    isel[MAXVARS];
char   simboli[MAXVARS][9];
double tempo; 
double misure[MAXVARS];
double mSel[MAXVARSEL];

static HWND hf22;

int leggi_testa_bin()
{
	int n, bRead;
	char str[80];
	
	ReadFile(hf22, titolo, 80, &bRead, (LPOVERLAPPED) NULL);
	ReadFile(hf22, &nVAR, sizeof(int), &bRead, (LPOVERLAPPED) NULL);
	
	for (n=0; n<nVAR; n++) {
		ReadFile(hf22, str, 80, &bRead, (LPOVERLAPPED) NULL);
	    strncpy(simboli[n],str,8);
	}

	return(0);
}


int leggi_corpo_bin()
{
   	int i, n, bRead;
	FILE *ASCII;
	
	ASCII=fopen("f22.asc","w");
	
	fprintf(ASCII,"  %s    ","Time");
	for (i=0; i< nSel; i++ ) fprintf(ASCII,"  %s ",vsel[i]);
	fprintf(ASCII,"\n");
	   
	for(;;) {
       ReadFile(hf22, misure, (nVAR+1)*sizeof(double), &bRead, (LPOVERLAPPED) NULL);
	   if (bRead != (int) ((nVAR+1)*sizeof(double)))  break; //EOF
	   tempo=misure[0];
	   
	   for(n=0;n<nVAR;n++) if (isel[n]>=0) mSel[isel[n]]=misure[n+1];
	   
	   fprintf(ASCII,"%10.2f ",tempo);
//	   for (i=0; i< nSel; i++ ) fprintf(ASCII,"%10.4g",mSel[i]);
	   for (i=0; i< nSel; i++ ) fprintf(ASCII,"%10.9g ",mSel[i]);
	   fprintf(ASCII,"\n");
	}
	
 	fclose(ASCII);

	return 0;
}

main() 
{
    int i,n;
	FILE *VSFILE;
	
	VSFILE=fopen("tradf22.inp","r");	
	nSel=0;
	while(!feof(VSFILE) && nSel<MAXVARSEL) {
		  fscanf(VSFILE,"%8s\n",vsel[nSel]);
	      nSel++;
	}
	fclose(VSFILE);
printf("nSel=%d\n",nSel);
	hf22 = CreateFile("f22.f22", GENERIC_READ, 
		               FILE_SHARE_READ,
					   (LPSECURITY_ATTRIBUTES) NULL, 
					   OPEN_EXISTING,
					   FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);

	if (hf22 == INVALID_HANDLE_VALUE) { printf( "errore in  apertura del file f22.f22");
	                return(-1);
	}
			 
	leggi_testa_bin();
	
	for (n=0;n<nVAR;n++) {
	    isel[n]=-1;
	    for(i=0;i<nSel;i++)
	        if (!strcmp(vsel[i],simboli[n])) isel[n]=i;
	}

    leggi_corpo_bin();

	CloseHandle(hf22);
	return(0);
}

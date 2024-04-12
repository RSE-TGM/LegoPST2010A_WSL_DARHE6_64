/* Conversion routines 
	from f22 FORTRAN format
	to   f22 C Tidea format

*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

extern struct {
                char simboli[1000][9];
                float misure[1000];
                float tempo;
                char titolo[80];
                int numvar;
                int numsimb;
                char model[8];
                char nomefile[80];
                int lun_nome;
                char labels[1000][71];
              } _Cvariabili;


static HWND hf22;
static char *simbolo;
double misura;

scrivi_testa_bin_()

   {
	int n, bWrite;
	int nVAR=_Cvariabili.numvar;
	
	hf22 = CreateFile("trad.f22",GENERIC_READ | GENERIC_WRITE,
			 FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES) NULL,
			 CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);
			 
	if (hf22 == INVALID_HANDLE_VALUE) return (-1);
	
	WriteFile(hf22, _Cvariabili.titolo, 80, &bWrite, (LPOVERLAPPED) NULL);
	WriteFile(hf22, &nVAR, sizeof(int), &bWrite, (LPOVERLAPPED) NULL);
	
	for (n=0; n<nVAR; n++)
	{
		simbolo=malloc(80*sizeof(char));
		strcpy(simbolo,_Cvariabili.simboli[n]);
		strcat(simbolo,"\t");
		strncat(simbolo,_Cvariabili.labels[n],65);
		WriteFile(hf22, simbolo, 80, &bWrite, (LPOVERLAPPED) NULL);
	}
	CloseHandle(hf22);
	return(0);
    }


scrivi_corpo_bin_()

   {
   	int n, bWrite;
   	int nVAR=_Cvariabili.numvar;
   	
   	hf22 = CreateFile("trad.f22",GENERIC_READ | GENERIC_WRITE,
			 FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES) NULL,
			 OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);
			 
	if (hf22 == INVALID_HANDLE_VALUE) return (-1);
	
	SetFilePointer(hf22,0, (PLONG) NULL, FILE_END);
	
	misura=(double) _Cvariabili.tempo;
	WriteFile(hf22, &misura, sizeof(double), &bWrite, (LPOVERLAPPED) NULL);
	
	for(n=0;n<nVAR;n++){
		misura=(double) _Cvariabili.misure[n];
		WriteFile(hf22, &misura, sizeof(double), &bWrite, (LPOVERLAPPED) NULL);
	}
	
	CloseHandle(hf22);	
   }

     

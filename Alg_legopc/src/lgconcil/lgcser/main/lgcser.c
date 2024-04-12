#include "LgCSer.h"

main ()
{
   int i, IER;
   
   DWORD retWait;

   hEveS = OpenEvent(EVENT_ALL_ACCESS,TRUE,"EVES");
   hEveC = OpenEvent(EVENT_ALL_ACCESS,TRUE,"EVEC");
   
   if( (hMem1=OpenMap( (LPSTR) MapName)) == NULL)  // Apertura memoria shared
   {
	MessageBox( NULL, "Shared memory nonexistent!", "WARNING", MB_OK|MB_ICONWARNING); 
	return(1);
   }
   
   pShrMem1 = (MEMORIASHARED *) MapView(hMem1);
   
   LEGO3(&IER);
   
   if (IER == 1)
       LGABRT();
   if (InitF22() == -1)
      MessageBox( NULL, "Couldn't initialize f22!", "WARNING", MB_OK|MB_ICONWARNING);
   if(_CCHISQUARE.iwzero > 0) {
      sprintf(s,"Warning: %d sensors have zero weight!",_CCHISQUARE.iwzero);
      MessageBox( NULL, s, "WARNING", MB_OK|MB_ICONWARNING); 
   }   	

   while (pShrMem1->control != 1) 
   {    
   	_CCFOR2.TEMPO    = pShrMem1->tempo;
   	_CSENS.SENSNUM   = pShrMem1->SensNum;
   	for (i=0;i<pShrMem1->SensNum;i++) 
   		_CSENS.SENSVALUE[i] = pShrMem1->SensValue[i];
   	for (i=0;i<pShrMem1->SensNum;i++) 
   		_CSENS.SENSORSON[i] = pShrMem1->SensorsON[i];
   	
   	LEGO34();

	pShrMem1->AlarmNum = _CALARM.ALARMNUM;
	for (i=0;i<_CALARM.ALARMNUM;i++)  {
   		pShrMem1->AlarmInd[i] = _CALARM.ALARMIND[i];
   		pShrMem1->AlarmVal[i] = _CALARM.ALARMVAL[i];
   	}
	  
   	if (WriteF22() == -1)
   	   MessageBox( NULL, "Couldn't write f22!", "WARNING", MB_OK|MB_ICONWARNING);

	VerifChiSquare();
   	
   	ResetEvent(hEveS);
	SetEvent(hEveC);
	
	retWait = WaitForSingleObject(  hEveS,INFINITE); 
   }

   CLOS90(); 
   LGSTOP();
   
   CloseHandle(hEveS);
   CloseHandle(hEveC);
   CloseHandle(hMem1);
   CloseHandle(hf22);   
}

HANDLE OpenMap( LPSTR SharedName)
{
   HANDLE hAMap;

   hAMap= OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
                          TRUE,
                          SharedName);

   if (hAMap == NULL)
   {
      MessageBox( NULL, "OpenMap failed!", "WARNING", MB_OK|MB_ICONWARNING); 
      return(NULL);
   }
   else
      return(hAMap);
}

LPVOID MapView(HANDLE hMap)
{
   LPVOID MappedPointer;

   MappedPointer= MapViewOfFile(hMap,
                                FILE_MAP_WRITE | FILE_MAP_READ,
                                0, 0, 0);
   if (MappedPointer == NULL)
   {
      MessageBox( NULL, "MapView failed!", "WARNING", MB_OK|MB_ICONWARNING);
      return(NULL);
   }
   else
      return(MappedPointer);
}

unsigned long bWrite;
static int nVAR;

int InitF22(void)
{
	static char str[200];
	int j,k,z;
 	
	nVAR = _CCFOR1.nuu+_CCFOR1.nxy+pShrMem1->SensNum;
	
	hf22 = CreateFile("lgconcil.f22", GENERIC_READ | GENERIC_WRITE, 
		   	  FILE_SHARE_READ, 
			  (LPSECURITY_ATTRIBUTES) NULL, CREATE_ALWAYS,
			  FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);
   
	if (hf22 == INVALID_HANDLE_VALUE)
		return(-1);
	WriteFile(hf22, "data reconciliation", 80, &bWrite, (LPOVERLAPPED) NULL);
	WriteFile(hf22, &nVAR, sizeof(int), &bWrite, (LPOVERLAPPED) NULL);

	for(j=0,k=0,z=10;j<_CCFOR1.nxy;j++,k+=8,z+=100)
	{
		memcpy(str,&_CCFOR1.nomexy[0][k],8);
		str[8]='\t';
		memcpy(str+9,"--UN",4);
		memcpy(str+13,&_CDESC.descrxy[0][z+4],65);
 		str[74]='\0';
		WriteFile(hf22, str, 80, &bWrite, (LPOVERLAPPED) NULL);
	}
	for(j=0,k=0,z=10;j<_CCFOR1.nuu;j++,k+=8,z+=100)
	{	
		memcpy(str,&_CCFOR1.nomeuu[0][k],8);
		str[8]='\t';
		memcpy(str+9,"--KN",4);
 		memcpy(str+13,&_CDESC.descruu[0][z+4],65);
  		str[74]='\0';
		WriteFile(hf22, str, 80, &bWrite, (LPOVERLAPPED) NULL);
	}
	for(j=0;j<pShrMem1->SensNum;j++)
	{
		sprintf(str,"SENS%-4d\t",j);
		strcat(str,"(");
		strncat(str,pShrMem1->SenVarName[j],8);
		strcat(str,")\t");
		strcat(str,pShrMem1->SensDesc[j]);
		WriteFile(hf22, str, 80, &bWrite, (LPOVERLAPPED) NULL);
	}
}

int WriteF22(void)
{
	double punti[N005+MAXSENS+1];
        int j,k;

	nVAR = _CCFOR2.nuu+_CCFOR2.nxy+pShrMem1->SensNum;
	
	if (hf22 == INVALID_HANDLE_VALUE)
		return(-1);
		SetFilePointer(hf22, 0, (PLONG) NULL, FILE_END);
		punti[0]=(double)_CCFOR2.TEMPO;
	for(j=0;j<_CCFOR2.nxy;j++)
		punti[j+1]=(double)(_CCFOR2.xy[j]*_CCFOR3.cnxy[j]);
	for(k=0;k<_CCFOR2.nuu;k++,j++)
		punti[j+1]=(double)(_CCFOR2.uu[k]*_CCFOR3.cnuu[k]);
	for(k=0;k<pShrMem1->SensNum;k++,j++)
		punti[j+1]=(double)(pShrMem1->SensValue[k]);
		WriteFile(hf22, punti, (nVAR + 1)*sizeof(double), &bWrite, (LPOVERLAPPED) NULL);
	return (0);
}

void VerifChiSquare()
{
   double Tmax, Tcurr;
   
   if (pShrMem1->tempo > 0 && pShrMem1->chiprob > 0) {

   	Tmax=critchi(1-pShrMem1->chiprob,(_CCHISQUARE.ngdl-_CSENS.NOTAVAIL));
   							//Calcolo Tmax chi-square
   	if (Tmax == -2.0)
      	MessageBox( NULL, "Chi-square right queue probability value is too high!", 
        	          "WARNING", MB_OK|MB_ICONWARNING);
        	          
        DoVerif=TRUE;
   	if (Tmax == -1.0 || Tmax == -2.0) DoVerif = FALSE;
      	if (DoVerif) Tcurr=_CCHISQUARE.xchi;
      	
   } else
   	DoVerif=FALSE;
                        
   QueueToTempFile(Tcurr,Tmax);
}	

void QueueToTempFile(double Tcurr,double Tmax)
{
	FILE *fp;
	int index=0;
	
	fp=fopen("temp.dat","r");
	fgets(s,200,fp);
	fclose(fp);

	while(s[index++] != '$');
	if(pShrMem1->tempo >0 && DoVerif) {
	   sprintf(s+index-1," Tcurr = %6.2f Tmax = %6.2f",Tcurr,Tmax);
	} else {
	   sprintf(s+index-1," ");
	}

	
	fp=fopen("temp.dat","w");
	fputs(s,fp);
	fclose(fp);	
}

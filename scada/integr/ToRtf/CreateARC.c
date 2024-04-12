/*
   modulo CreateARC.c
   tipo 
   release 2.6
   data 6/13/96
   reserved @(#)CreateARC.c	2.6
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include "tag.h"
#include "ToRtf.h"
#include "db.h"
#include "arcdef.inc"
#include "g0gerdb.inc"
#include "g3calcdb.inc"
#include "fileop.inc"
#include "g1tipdb.inc"
#include "dconf.inc"

static int      fzq[n_freq]= {5, 15, 30, 60, 300, 900, 1800, 3600, 28800, 86400, 600};
static char *szFreq[n_freq]= {"05S","15S","30S","01M","05M","15M","30M","01H","08H",
		       	      "24H","10M"};
static char  *szDur[n_freq]= {"08H","01G","07G","01M"};

extern DB_HEADER header_ToRtf;

#define h_db header_ToRtf

extern char path_txt[FILENAME_MAX+1];

int CreateARC()
{

FILE *fpFDARC,*fpDE_ARCxx;
ID_TABLE *tabella;
VAL_RET valore;
int j,i,num_record;
DES_ARC fdarc;
ARC_DESCR de_arcxx;
PUNTATORE punt;
char szBuffer[FILENAME_MAX+1];

// inizializza il file
fpFDARC=fopen("fdarc.rtf","wb");
memset(&fdarc,0,sizeof(fdarc));
for(i=0;i<n_arc;i++)
	fwrite(&fdarc,1,sizeof(fdarc),fpFDARC);
fclose(fpFDARC);

tabella = OpenTablePath(path_txt,ARC);
if(tabella == NULL)
{
        fprintf(stderr,"CreateARC: apertura tabella\n");
        return(0);
}

num_record = NumRecord(tabella);
fpFDARC=fopen("fdarc.rtf","r+");
for(i=0;i<num_record;i++)
{
	memset(&fdarc,0,sizeof(fdarc));
	memset(&de_arcxx,0,sizeof(de_arcxx));

	if(GetVal(tabella,"Indice",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateARC: Errore GetVal Indice\n");
        	return(0);
       	}
	fdarc.head.iarc=valore.int_val;
	sprintf(szBuffer,"%0*d",l_indice,fdarc.head.iarc);
	memcpy(de_arcxx.indice,szBuffer,l_indice);

	sprintf(szBuffer,"de_arc%02d.rtf",valore.int_val);
	fpDE_ARCxx=fopen(szBuffer,"wb");

	if(GetVal(tabella,"Descrizione",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateARC: Errore GetVal Descrizione\n");
        	return(0);
       	}
	sprintf(szBuffer,"%-*s",SCD_DESCRIZIONE,valore.char_val);
	memcpy(de_arcxx.descr,szBuffer,SCD_DESCRIZIONE);

	if(GetVal(tabella,"Tipo",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateARC: Errore GetVal Tipo\n");
        	return(0);
       	}
	fdarc.head.tipo=valore.int_val;
	if(fdarc.head.tipo==arc_Norm)
		de_arcxx.tipo='N';
	else
		de_arcxx.tipo='L';
	
	fdarc.head.flag=0;

	if(GetVal(tabella,"PeriodoL",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateARC: Errore GetVal PeriodoL\n");
        	return(0);
       	}
	fdarc.head.c_freqN=valore.int_val-1;
	fdarc.head.freqN=fzq[valore.int_val-1];

	if(fdarc.head.tipo==arc_Norm)
	{
		sprintf(szBuffer,"%-*s",l_freq,szFreq[fdarc.head.c_freqN]);
		memcpy(de_arcxx.freq_N,szBuffer,l_freq);
	}
	else
	{
		sprintf(szBuffer,"%-*s",l_freq,szFreq[fdarc.head.c_freqN]);
		memcpy(de_arcxx.freq_VL,szBuffer,l_freq);
	}

	if(fdarc.head.tipo==arc_Len)
	{
		fdarc.head.c_freqL=valore.int_val+3;
		fdarc.head.freqL=fzq[valore.int_val-1]*60;
		sprintf(szBuffer,"%-*s",l_freq,szFreq[fdarc.head.c_freqN*2+1]);
		memcpy(de_arcxx.freq_L,szBuffer,l_freq);

		if(GetVal(tabella,"TriggerA",i,&valore)!=1)
       		{
        		fprintf(stderr,"CreateARC: Errore GetVal TriggerA\n");
        		return(0);
       		}
		fdarc.head.trigga=valore.int_val;
		de_arcxx.trigga='0'+valore.int_val;

		fdarc.head.triggd=21;
		de_arcxx.triggd='5';

		if(GetVal(tabella,"TotPar",i,&valore)!=1)
       		{
        		fprintf(stderr,"CreateARC: Errore GetVal TotPar\n");
        		return(0);
       		}
		
		if(valore.int_val)
		{
			fdarc.head.t_mem=M_Par;
			de_arcxx.t_mem='P';
		}
		else
		{
			fdarc.head.t_mem=M_Tot;
			de_arcxx.t_mem='T';
		}
	}

	if(GetVal(tabella,"Durata",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateARC: Errore GetVal Durata\n");
        	return(0);
       	}
	fdarc.head.c_dur=valore.int_val-1;
	
	if(fdarc.head.tipo==arc_Norm)
	{
		sprintf(szBuffer,"%-*s",l_dur,szDur[valore.int_val-1]);
		memcpy(de_arcxx.dur_N,szBuffer,l_dur);
	}
	else
	{
		sprintf(szBuffer,"%-*s",l_dur,szDur[valore.int_val-1]);
		memcpy(de_arcxx.dur_L,szBuffer,l_dur);
	}

	if(GetVal(tabella,"NumeroFile",i,&valore)!=1)
       	{
        	fprintf(stderr,"CreateARC: Errore GetVal NumeroFile\n");
        	return(0);
       	}
	fdarc.head.n_file=valore.int_val;
	
	if(fdarc.head.tipo==arc_Len)
	{
		sprintf(szBuffer,"%-*d",l_fil,valore.int_val);
		memcpy(de_arcxx.n_fil_L,szBuffer,l_fil);
	}
	else
	{
		sprintf(szBuffer,"%-*d",l_fil,valore.int_val);
		memcpy(de_arcxx.n_fil_N,szBuffer,l_fil);
	}

	sprintf(szBuffer,"0ARC-ST%02d",i+1);
	SetPunt(szBuffer,&punt);
	fdarc.head.p_st=punt.punt;

	sprintf(szBuffer,"0ARC-NC%02d",i+1);
	SetPunt(szBuffer,&punt);
	fdarc.head.p_nc=punt.punt;

	sprintf(szBuffer,"0ARC-FC%02d",i+1);
	SetPunt(szBuffer,&punt);
	fdarc.head.p_fc=punt.punt;

	sprintf(szBuffer,"0ARC-MXF%02d",i+1);
	SetPunt(szBuffer,&punt);
	fdarc.head.p_nfmax=punt.punt;

	sprintf(szBuffer,"0ARC-01%02d",i+1);
	SetPunt(szBuffer,&punt);
	fdarc.head.p_1f=punt.punt;

	sprintf(szBuffer,"0ARC-PD%02d",i+1);
	SetPunt(szBuffer,&punt);
	fdarc.head.p_pd=punt.punt;

	for(j=0,fdarc.head.n_mis=0;j<n_misarc;j++,fdarc.head.n_mis++)
	{
		sprintf(szBuffer,"Campione%02d",j+1);
		if(GetVal(tabella,szBuffer,i,&valore)!=1)
       		{
        		fprintf(stderr,"CreateARC: Errore GetVal %s\n",szBuffer);
        		return(0);
       		}
		
		if(*valore.char_val=='\0')
			break;

		SetPunt(valore.char_val,&punt);
		fdarc.mis[j].ext=punt.ext;
		fdarc.mis[j].punt=punt.punt;
		
		arcinfop(&fdarc.mis[j],j,&de_arcxx);
	}

	de_arcxx.spare0=' ';

	fwrite(&fdarc,1,sizeof(fdarc),fpFDARC);
	fwrite(&de_arcxx,1,sizeof(de_arcxx),fpDE_ARCxx);

	fclose(fpDE_ARCxx);
}

CloseTable(tabella);
fclose(fpFDARC);

return(1);
}


/*
	-> arcinfop()
	Routine per la scrittura della sigla, della descrizione
        e degli eventuali stati dei punti in archivio.

        Parametri:  PUNTDBS   *mis      puntatore alla struttura del record del file
                                        FDARC.RTF con informazioni punti in archivio
                    short     jmis      indice che scorre i punti in archivio
		    ARC_DESCR *de_arcxx puntatore al record file descrittore ASCII

        Ritorno  :  0 errore
                    1 OK
*/
int arcinfop(PUNTDBS *mis,int jmis,ARC_DESCR *de_arcxx)
{

short scelta, point;
long tot;
char szBuffer[SCD_DESCRIZIONE];
int  blank=' ';
FILE *fpFDDE;

   if(!(fpFDDE=fopen("fdde.rtf","rb")))
   {
	fprintf(stderr,"arcinfop() errore apertura fdde.rtf\n");
	return(0);
   }

   point = mis->punt;
   scelta = mis->ext;
   switch(scelta)
   {
      case g1tipaa:	// analogico acquisito
         {
         tot = of_fdaa+(long)point*rec_fdaa;
         goto ANALEV;
         }
      case g1tipas:	// analogico calcolato standard
         {
         tot = of_fdas+(long)point*rec_fdas;
         goto ANALEV;
         }
      case g1tipac:	// analogico calcolato non standard   
         {
         tot = of_fdac+(long)point*rec_fdac;
         goto ANALEV;
         }
      case g1tipad:	// analogico di diagnostica
         {
         tot = of_fdad+(long)point*rec_fdad;

ANALEV:			// lettura da file FDDE.RTF informazioni punto
         if (fseek(fpFDDE,tot,0)!=0)   goto  FINE1;
         if (!fread(szBuffer,SCD_SIGLA,1,fpFDDE))   goto  FINE2;
         memcpy(de_arcxx->p[jmis].sigla,szBuffer,SCD_SIGLA);
         if (!fread(szBuffer,SCD_DESCRIZIONE,1,fpFDDE))    goto FINE2;
         memcpy(de_arcxx->p[jmis].descr,szBuffer,SCD_DESCRIZIONE);
         if (!fread(szBuffer,SCD_UNIMIS,1,fpFDDE))    goto FINE2;
         szBuffer[SCD_UNIMIS]=0;
         memcpy(de_arcxx->p[jmis].st_umis,szBuffer,SCD_UNIMIS);
         break;
         }
      case g1tipda:   	// digitale acquisito
         {
         tot = of_fdda+(long)point*rec_fdda;
         goto DIGITEV;
         }
      case g1tipds:   	// digitale calcolato standard
         {
         tot = of_fdds+(long)point*rec_fdds;
         goto DIGITEV;
         }
      case g1tipdc:   	// digitale calcolato non standard   
         {
         tot = of_fddc+(long)point*rec_fddc;
         goto DIGITEV;
         }
      case g1tipdd:   	// digitale di diagnostica
         {
         tot = of_fddd+(long)point*rec_fddd;

DIGITEV:		// lettura da file FDDE.RTF informazioni punto
         if(fseek(fpFDDE,tot,0))      goto FINE1;
         if(!fread(szBuffer,SCD_SIGLA,1,fpFDDE)) goto FINE2;
         memcpy(de_arcxx->p[jmis].sigla,szBuffer,SCD_SIGLA);
         if (!fread(szBuffer,SCD_DESCRIZIONE,1,fpFDDE)) goto FINE2;
         memcpy(de_arcxx->p[jmis].descr,szBuffer,SCD_DESCRIZIONE);
         if (!fread(szBuffer,SCD_UNIMIS,1,fpFDDE))    goto FINE2;
         szBuffer[SCD_UNIMIS]=0;
         memcpy(de_arcxx->p[jmis].st_umis,szBuffer,SCD_UNIMIS);
         if (!fread(szBuffer,SCD_UNIMIS,1,fpFDDE))    goto FINE2;
         szBuffer[SCD_UNIMIS]=0;
         memcpy(de_arcxx->p[jmis].stato1,szBuffer,SCD_UNIMIS);
         break;
         }
      case g1tipor:   	// tipo organo
         {
         tot = of_fdor+(long)point*rec_fdor;
         if (fseek(fpFDDE,tot,0)!=0)      goto FINE1;
         if (!fread(szBuffer,SCD_SIGLA,1,fpFDDE)) goto FINE2;
         memcpy(de_arcxx->p[jmis].sigla,szBuffer,SCD_SIGLA);
         if (!fread(szBuffer,SCD_DESCRIZIONE,1,fpFDDE))       goto FINE2;
         memcpy(de_arcxx->p[jmis].descr,szBuffer,SCD_DESCRIZIONE);
         memset(szBuffer,blank,SCD_UNIMIS);
         if (!fread(szBuffer,SCD_UNIMIS,1,fpFDDE))    goto FINE2;
         szBuffer[SCD_UNIMIS]=0;
         memcpy(de_arcxx->p[jmis].st_umis,szBuffer,SCD_UNIMIS);
         memcpy(de_arcxx->p[jmis].stato1,szBuffer,SCD_UNIMIS);
		break;
         }
      case g1tipst:   	// tipo stringa
         {
         tot = of_fdst+(long)point*rec_fdst;
         if (fseek(fpFDDE,tot,0)!=0)      goto FINE1;
         if (!fread(szBuffer,SCD_SIGLA,1,fpFDDE)) goto FINE2;
         memcpy(de_arcxx->p[jmis].sigla,szBuffer,SCD_SIGLA);
         if (!fread(szBuffer,SCD_DESCRIZIONE,1,fpFDDE))       goto FINE2;
         memcpy(de_arcxx->p[jmis].descr,szBuffer,SCD_DESCRIZIONE);
         memset(szBuffer,blank,SCD_UNIMIS);
         szBuffer[SCD_UNIMIS]=0;
         memcpy(de_arcxx->p[jmis].st_umis,szBuffer,SCD_UNIMIS);
         memcpy(de_arcxx->p[jmis].stato1,szBuffer,SCD_UNIMIS);
         }
   }
	fclose(fpFDDE);
	return(1);

FINE1:
FINE2:
	fclose(fpFDDE);
	return(0);
}


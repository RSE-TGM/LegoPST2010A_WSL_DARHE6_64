/*
   modulo installa_arc.c
   tipo 
   release 1.9
   data 5/20/96
   reserved @(#)installa_arc.c	1.9
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>

#include "db.h"
#include "tag.h"
#include "installa.h"
#include "installa_variabili.h"
#include "arc.inc"
#include "editarc.h"
#include "g1tipdb.inc"

#define errore_arc(stringa) { \
			    fprintf(stderr,"installa_arc: [%s]\n",stringa); \
			    return(0); \
			    }

extern char *path_input;
extern char *path_output;

extern int num_record_tag;
extern APP_TAG *app_tag;

int crea_arc()
{
return(scrivi_header(path_output,"editarc",editarc,NUM_CAMPI_EDITARC));
}

int installa_arc(void)
{
int i,j,num_rec,num_rec_nomi,iArc;
S_EDITARC arc[n_arc+1];
int iFullIndex[n_arc+1];
ID_TABLE *tabella,*tabella_nomi;
VAL_RET valore;
RECORD record;
char sigla_ricerca[SCD_SIGLA+1];

#define l_szcampo 256
char szCampo[l_szcampo];

if(!crea_arc())
	return 0;

// Inizializzazione
memset(arc,0,sizeof(arc));
for(i=0;i<n_arc+1;i++)
{
	iFullIndex[i]=0;
	arc[i].Indice=-1;
}

// Legge la tabella iniziale degli archivi
tabella=OpenTablePath(path_input,HDR_TABLE);
if(!tabella)
{
        fprintf(stderr,"installa_arc: apertura tabella [%s]\n",HDR_TABLE);
        return(0);
}
num_rec=NumRecord(tabella);
for(i=0;i<num_rec;i++)
{
	if(GetVal(tabella,"HDR_CODE",i,&valore)!=1)
        {
                fprintf(stderr,"installa_arc: Errore GetVal HDR_CODE\n");
                return(0);
        }
	if(valore.int_val==-1) continue;
	iArc=arc[valore.int_val].Indice=valore.int_val;

        if(GetVal(tabella,"HDR_DESCR",i,&valore)!=1)
        {
                fprintf(stderr,"installa_arc: Errore GetVal HDR_DESCR\n");
                return(0);
        }
	strncpy(arc[iArc].Descrizione,valore.char_val,SCD_DESCRIZIONE);

        if(GetVal(tabella,"HDR_TYPE",i,&valore)!=1)
        {
                fprintf(stderr,"installa_arc: Errore GetVal HDR_TYPE\n");
                return(0);
        }
	arc[iArc].Tipo=valore.int_val;

        if(GetVal(tabella,"HDR_PERIOD",i,&valore)!=1)
        {
                fprintf(stderr,"installa_arc: Errore GetVal HDR_PERIOD\n");
                return(0);
        }
	arc[iArc].PeriodoL=valore.int_val;

        if(GetVal(tabella,"HDR_LENGTH",i,&valore)!=1)
        {
                fprintf(stderr,"installa_arc: Errore GetVal HDR_LENGTH\n");
                return(0);
        }
	arc[iArc].Durata=valore.int_val;

        if(GetVal(tabella,"HDR_NUM_FILE",i,&valore)!=1)
        {
                fprintf(stderr,"installa_arc: Errore GetVal HDR_NUM_FILE\n");
                return(0);
        }
	arc[iArc].NumeroFile=valore.int_val;

        if(GetVal(tabella,"HDR_PARTIAL",i,&valore)!=1)
        {
                fprintf(stderr,"installa_arc: Errore GetVal HDR_PARTIAL\n");
                return(0);
        }
	arc[iArc].TotPar=valore.int_val;

        if(GetVal(tabella,"HDR_TRIGGER",i,&valore)!=1)
        {
                fprintf(stderr,"installa_arc: Errore GetVal HDR_TRIGGER\n");
                return(0);
        }
	arc[iArc].TriggerA=valore.int_val;
}
//CloseTable(tabella);

// Scandisce tutti i punti configurati

if(!(tabella_nomi=OpenTablePath(path_output,"editNomi")))
{
	fprintf(stderr,"IsInstalled: [editNomi]");
	return 0;
}

num_rec_nomi=NumRecord(tabella_nomi);
for(i=0;i<num_record_tag;i++)
{
	if(!app_tag[i].TAG_SCADA_USE) continue;
	
	if(app_tag[i].HDR_CODE==-1) continue;
	iArc=app_tag[i].HDR_CODE;

	strcpy(sigla_ricerca,app_tag[i].TAG_NAME);
	if(app_tag[i].TAG_ALARM != ' ')
		{
		// e' un allarme
		sprintf(sigla_ricerca,"%s%s%c",
			sigla_ricerca,TAG_SIGNAL,app_tag[i].TAG_ALARM);
		}

/*
	printf("%d/%d [%s] [%c] -> [%s]\n",
		i,num_record_tag,app_tag[i].TAG_NAME,
			app_tag[i].TAG_ALARM,sigla_ricerca);
*/
	if(!IsInstalled(sigla_ricerca,tabella_nomi,num_rec_nomi))
		{
		installa_err(sigla_ricerca,ARC_TAG_NOT_FOUND);
		continue;
		}

	if(iFullIndex[iArc]<n_misarc)
	{
		strncpy(arc[iArc].Campione[iFullIndex[iArc]],
			sigla_ricerca, SCD_SIGLA);
		iFullIndex[iArc]++;
	}
	else
	{
		fprintf(stderr,"installa_arc: Superato N. max misure arc %d [%s]\n",
			iArc,sigla_ricerca);
	}
}
CloseTable(tabella);
CloseTable(tabella_nomi);

// Scrive tutti i campi sulla tabella
for(i=0;i<n_arc+1;i++)
{
	if(arc[i].Indice<1)
		continue;

	if(!init_record(&record,editarc,NUM_CAMPI_EDITARC))
		errore_arc("init_record");

	if(!ins_campo_int("Indice",arc[i].Indice,&record))
		errore_arc("ins_campo_int \"Indice\"");

	if(!ins_campo_char("Descrizione",arc[i].Descrizione,&record))
		errore_arc("ins_campo_char \"Descrizione\"");

	if(!ins_campo_int("Tipo",arc[i].Tipo,&record))
		errore_arc("ins_campo_int \"Tipo\"");

	if(!ins_campo_int("PeriodoL",arc[i].PeriodoL,&record))
		errore_arc("ins_campo_int \"PeriodoL\"");

	if(!ins_campo_int("Durata",arc[i].Durata,&record))
		errore_arc("ins_campo_int \"Durata\"");

	if(!ins_campo_int("NumeroFile",arc[i].NumeroFile,&record))
		errore_arc("ins_campo_int \"NumeroFile\"");

	if(!ins_campo_int("TriggerA",arc[i].TriggerA,&record))
		errore_arc("ins_campo_int \"TriggerA\"");

	if(!ins_campo_int("TriggerD",arc[i].Trigger,&record))
		errore_arc("ins_campo_int \"TriggerD\"");

	if(!ins_campo_int("TotPar",arc[i].TotPar,&record))
		errore_arc("ins_campo_int \"TotPar\"");

	if(!ins_campo_int("DatiVet",arc[i].DatiVet,&record))
		errore_arc("ins_campo_int \"DatiVet\"");

	for(j=0;j<n_misarc;j++)
	{
		sprintf(szCampo,"Campione%02d",j+1);

		if(!ins_campo_char(szCampo,arc[i].Campione[j],&record))
			errore_arc(szCampo);
	}

	if(!scrivi_record(path_output,"editarc",&record))
		errore_arc("scrivi_record");
}

return 1;
}

int IsInstalled(char *sigla,ID_TABLE *tabella,int num_rec)
{
char pathname[FILENAME_MAX];
VAL_RET valore;
int i;

for(i=0;i<num_rec;i++)
{
	if(!GetVal(tabella,"Sigla",i,&valore))
	{
                fprintf(stderr,"IsInstalled: Errore GetVal Sigla\n");
                return(0);
        }
	if(!strcmp(sigla,valore.char_val))
		return 1;
}

return 0;
}

/*
   modulo installa_variabili.c
   tipo 
   release 1.19
   data 10/14/96
   reserved @(#)installa_variabili.c	1.19
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "db.h"
#include "installa.h"
#include "g0gerdb.inc"
#include "sim_param.h"
#include "sim_types.h"
#include "tag.h"
#include "installa_variabili.h"
#include "g3calcdb.inc"    /* aggiunta per calcolate PEN e ARC*/

#define errore(stringa) { \
	fprintf(stderr,"Attenzione !!!\nErrore lettura variabili.rtf [%s]\n",stringa); \
	exit(1); \
	}

VARIABILI *variabili;          /* database variabili di tutti i modelli */
char *ind_sh_top;          /* puntatore inizio shared memory sh_var */
int id_sh;                 /* identificatore sh_var */
int nmod;
int tot_variabili;

extern S_DBGERA gerarchie[MAX_GERARCHIE];
extern int zone_gerarchie[MAX_GERARCHIE];
extern int numero_gerarchie;

extern char *path_input;
extern char *path_output;
extern char *path_variabili;


static int IsNomeScada(char *,int);
static int GetTagScada(char *,char *);
static int GetTagSim(char *,char *);
static int GetDescScada(char *,char *);
static int GetAlarmMeasureTag(APP_TAG *,int, char *,ID_TABLE *, int, int *);
static int GetSignalFromType(int tipo,char *signal);
static int GetStato01(int tipo,char *desc,char *stato0, char *stato1);
static int GetGerarchie(ID_TABLE *tabella,int record,S_DBGERA *gerarchia,char *fieldPrefix);
static int to_upper(char *);


extern int num_codici_allaras;
extern STRUCT_ALLARAS *allaras;

int num_record_tag;
APP_TAG *app_tag;

int installa_variabili()
{
int shr_usr_key;                /* chiave utente per shared     */
int i,j,k;
char nome_scada[SCD_SIGLA+1];
char nome_scada1[SCD_SIGLA+1];
char nome_scada2[SCD_SIGLA+1];
char desc_scada[SCD_DESCRIZIONE+1];
char desc_scada1[SCD_DESCRIZIONE+1];
char desc_scada2[SCD_DESCRIZIONE+1];
char nome_sim[MAX_LUN_NOME_VAR];
char gerar[30];
char umis[SCD_UNIMIS+1];
int prog_ana;
int prog_com;
int prog_dig;
ID_TABLE *tabella_alarm;
ID_TABLE *tabella_measure;
ID_TABLE *tabella_tag;
VAL_RET valore;
int num_record_alarm;
int num_record_measure;
int record;
int alarm_type;
char alarm_signal[LUN_SIGNAL+1];
S_DBGERA gerarchia;
int zona,trattamento,severita;
int alarm_state,BandaMorta,Contatto;
float LalBS,LalBC,LalAC,LalAS;
char stato0[SCD_STATO+1];
char stato1[SCD_STATO+1];
char SignDesc[100];
char *path_locale;
int rec_found;
int point_inst;
char *tag_alarm_type;


// recupera il path locale
path_locale = getcwd(NULL,FILENAME_MAX);
// va nel direttorio di variabili.rtf
if(chdir(path_variabili)!=0)
         {
         fprintf(stderr,"installa: il path [%s] non esiste\n",path_variabili);
         exit(1);
         }
/* aggancio shared memory sh_var */
costruisci_var(&ind_sh_top,&variabili,&id_sh);
// torna indietro
if(chdir(path_locale)!=0)
         {
         fprintf(stderr,"installa: il path [%s] non esiste\n",path_locale);
         exit(1);
         }
/* legge numero dei modelli */
nmod=numero_modelli(ind_sh_top);
tot_variabili=numero_variabili(ind_sh_top);

// inizializza la struttura delle gerarchie
InitGerarchie();

// INSTALLAZIONE ANALOGICI E DIGITALI 
if(crea_aa()!=1)
	errore("crea_aa");
if(crea_ac()!=1)
	errore("crea_ac");
if(crea_da()!=1)
	errore("crea_da");
if(crea_ds()!=1)
	errore("crea_ds");
if(crea_dc()!=1)
	errore("crea_dc");

// Apertura tabella ALARM
tabella_alarm = OpenTablePath(path_input,ALARM_TABLE);
if(tabella_alarm == NULL)
        {
        fprintf(stderr,"installa_variabili: apertura tabella [%s]\n",ALARM_TABLE);
        return(0);
        }
num_record_alarm = NumRecord(tabella_alarm);

// Apertura tabella MEASURE
tabella_measure = OpenTablePath(path_input,MEASURE_TABLE);
if(tabella_measure == NULL)
        {
        fprintf(stderr,"installa_variabili: apertura tabella [%s]\n",MEASURE_TABLE);
        return(0);
        }
num_record_measure = NumRecord(tabella_measure);

// Apertura tabella TAG
tabella_tag = OpenTablePath(path_input,TAG_TABLE);
if(tabella_tag == NULL)
        {
        fprintf(stderr,"installa_variabili: apertura tabella [%s]\n",TAG_TABLE);
        return(0);
        }
num_record_tag = NumRecord(tabella_tag);
app_tag = (APP_TAG*)malloc(sizeof(APP_TAG)*num_record_tag);
for(i=0;i<num_record_tag;i++)
    {
       //  TAG_NAME
        if(GetVal(tabella_tag,"TAG_NAME",i,&valore)!=1)
                {
                fprintf(stderr,"installa_variabili: Errore GetVal TAG_NAME\n");
                return(0);
                }
	memset(app_tag[i].TAG_NAME,0,SCD_SIGLA+1);
	memcpy(app_tag[i].TAG_NAME,valore.char_val,strlen(valore.char_val));
       //  TAG_ID
        if(GetVal(tabella_tag,"TAG_ID",i,&valore)!=1)
                {
                fprintf(stderr,"installa_variabili: Errore GetVal TAG_ID\n");
                return(0);
                }
	app_tag[i].TAG_ID=valore.int_val;
       //  TAG_SCADA_USE
        if(GetVal(tabella_tag,"TAG_SCADA_USE",i,&valore)!=1)
                {
                fprintf(stderr,"installa_variabili: Errore GetVal TAG_SCADA_USE\n");
                return(0);
                }
	app_tag[i].TAG_SCADA_USE=valore.int_val;
	//  HDR_CODE
        if(GetVal(tabella_tag,"HDR_CODE",i,&valore)!=1)
                {
                fprintf(stderr,"installa_variabili: Errore GetVal HDR_CODE\n");
                return(0);
                }
        app_tag[i].HDR_CODE=valore.int_val;
        // Azzero il campo TAG_ALARM
        app_tag[i].TAG_ALARM=' ';
    }
CloseTable(tabella_tag);


// Scandisce tutte le variabili del simulatore
for(i=0;i<tot_variabili;i++)
  if(IsNomeScada(variabili[i].descr,i))
    {
    GetTagScada(variabili[i].descr,nome_scada);
    rec_found = -2;
    point_inst = 0;
    
    // Punto ALLARME
    if((record=GetAlarmMeasureTag(app_tag,num_record_tag,nome_scada,
				tabella_alarm,num_record_alarm,&rec_found))>=0)
       { 
       GetTagSim(variabili[i].nome,nome_sim);
       // prelevo Designation
       if(GetVal(tabella_alarm,"AL_DESIGNATION",record,&valore)!=1)
          {
          fprintf(stderr,"installa_variabili: Errore GetVal AL_DESIGNATION\n");
          return(0);
          }
       valore.char_val[SCD_DESCRIZIONE]=0;
       strcpy(desc_scada,valore.char_val);
       // prelevo SignDescription
       if(GetVal(tabella_alarm,"AL_SIGN_DESCR",record,&valore)!=1)
          {
          fprintf(stderr,"installa_variabili: Errore GetVal AL_SIGN_DESCR\n");
          return(0);
          }
       // se c'e' spazio la concateno
       if(strlen(desc_scada)+strlen(valore.char_val)+strlen(COD_SIGLA_SCADA)*2
				<SCD_DESCRIZIONE)
          sprintf(desc_scada,"%s %s%s%s",
		desc_scada,COD_SIGLA_SCADA,valore.char_val,COD_SIGLA_SCADA);
       strcpy(SignDesc,valore.char_val);


       // prelevo il tipo di allarme
       // prelevo Type
       if(GetVal(tabella_alarm,"ALTYPE_ID",record,&valore)!=1)
          {
          fprintf(stderr,"installa_variabili: Errore GetVal ALTYPE_ID\n");
          return(0);
          }
       alarm_type = valore.int_val;
       if(GetSignalFromType(alarm_type,alarm_signal)!=1)
          {
	  installa_err(nome_scada,SIGNAL_NOT_FOUND);
          continue;
          }
       // verifica che la sigla scada possa contenere il segnale di allarme
       if(strlen(nome_scada)>=(SCD_SIGLA-LUN_SIGNAL))
          {
          fprintf(stderr,
		"installa_variabili: Errore [%s] troppo lunga\n",nome_scada);
          return(0);
          }
       strcat(nome_scada,alarm_signal);
       if(rec_found>=0)
        	app_tag[rec_found].TAG_ALARM=alarm_signal[LUN_SIGNAL-1];

       // prelevo lo stato di allarme
       // prelevo AlarmState
       if(GetVal(tabella_alarm,"AL_STATE",record,&valore)!=1)
          {
          fprintf(stderr,"installa_variabili: Errore GetVal AL_STATE\n");
          return(0);
          }
       alarm_state = valore.int_val;
       if(GetStato01(alarm_type,SignDesc,stato0,stato1)<0)
           return(0);

       if(GetGerarchie(tabella_alarm,record,&gerarchia,"AL")<0)
           return(0);

       // prelevo Zone
       if(GetVal(tabella_alarm,"AL_ZONE",record,&valore)!=1)
          {
          fprintf(stderr,"installa_variabili: Errore GetVal AL_ZONE\n");
          return(0);
          }
       zona = valore.int_val;

       // prelevo Treatment
       if(GetVal(tabella_alarm,"AL_TREATMENT",record,&valore)!=1)
          {
          fprintf(stderr,"installa_variabili: Errore GetVal AL_TREATMENT\n");
          return(0);
          }
       trattamento = valore.int_val;

       // prelevo Severity
       if(GetVal(tabella_alarm,"AL_SEVERITY",record,&valore)!=1)
          {
          fprintf(stderr,"installa_variabili: Errore GetVal AL_SEVERITY\n");
          return(0);
          }
       severita = valore.int_val;

       installa_da(nome_scada,desc_scada,nome_sim,
		stato0,stato1,"","","",alarm_state,
                zona,trattamento,severita,
		gerarchia.chLivello[0],
		gerarchia.chLivello[1],
		gerarchia.chLivello[2],
		gerarchia.chLivello[3],
		gerarchia.chLivello[4],
		gerarchia.chLivello[5]);
	point_inst = 1;
      }
   // Punto MEASURE
   else if((record=GetAlarmMeasureTag(app_tag,num_record_tag,nome_scada,
                          tabella_measure,num_record_measure,&rec_found))>=0)
      {
      GetTagSim(variabili[i].nome,nome_sim);

      if(GetVal(tabella_measure,"MEAS_DESCR",record,&valore)!=1)
         {
         fprintf(stderr,"installa_variabili: Errore GetVal MEAS_DESCR\n");
         return(0);
         }
      strncpy(desc_scada,valore.char_val,SCD_DESCRIZIONE);

      if(GetVal(tabella_measure,"MEAS_ZONE",record,&valore)!=1)
         {
         fprintf(stderr,"installa_variabili: Errore GetVal MEAS_ZONE\n");
         return(0);
         }
      zona=valore.int_val;

      if(GetVal(tabella_measure,"MEAS_TREATMENT",record,&valore)!=1)
         {
         fprintf(stderr,"installa_variabili: Errore GetVal MEAS_TREATMENT\n");
         return(0);
         }
      trattamento=valore.int_val;

      if(GetVal(tabella_measure,"MEAS_SEVERITY",record,&valore)!=1)
         {
         fprintf(stderr,"installa_variabili: Errore GetVal MEAS_SEVERITY\n");
         return(0);
         }
      severita=valore.int_val;

      if(GetGerarchie(tabella_measure,record,&gerarchia,"MEAS")<0)
         return(0);

      if(GetVal(tabella_measure,"MEAS_ANDIG",record,&valore)!=1)
         {
         fprintf(stderr,"installa_variabili: Errore GetVal MEAS_ANDIG\n");
         return(0);
         }

      // Misura DIGITALE
      if(valore.int_val)
         {
         if(GetVal(tabella_measure,"MEAS_STATE_0",record,&valore)!=1)
            {
            fprintf(stderr,"installa_variabili: Errore GetVal MEAS_STATE_0\n");
            return(0);
            }
	    strncpy(stato0,valore.char_val,SCD_STATO);

         if(GetVal(tabella_measure,"MEAS_STATE_1",record,&valore)!=1)
            {
            fprintf(stderr,"installa_variabili: Errore GetVal MEAS_STATE_1\n");
            return(0);
            }
	    strncpy(stato1,valore.char_val,SCD_STATO);

         if(GetVal(tabella_measure,"MEAS_ALARM_STATE",record,&valore)!=1)
            {
            fprintf(stderr,"installa_variabili: Errore GetVal MEAS_ALARM_STATE\n");
            return(0);
            }
	    Contatto=valore.int_val;

printf("DEBUG:inst_da:nome_scada=%*s\n",SCD_SIGLA,nome_scada);
         installa_da(nome_scada,desc_scada,nome_sim,
		stato0,stato1,"","","",Contatto,
                zona,trattamento,severita,
                gerarchia.chLivello[0],
                gerarchia.chLivello[1],
                gerarchia.chLivello[2],
                gerarchia.chLivello[3],
                gerarchia.chLivello[4],
                gerarchia.chLivello[5]);
	point_inst = 1;
         }
      // Misura ANALOGICA
      else
         {
         CostruisciUniMis(nome_scada,umis);

         if(GetVal(tabella_measure,"MEAS_DEADZONE",record,&valore)!=1)
            {
            fprintf(stderr,"installa_variabili: Errore GetVal MEAS_DEADZONE\n");
            return(0);
            }
         BandaMorta=valore.int_val;

         if(GetVal(tabella_measure,"MEAS_HH",record,&valore)!=1)
            {
            fprintf(stderr,"installa_variabili: Errore GetVal MEAS_HH\n");
            return(0);
            }
         LalAS=valore.float_val;

         if(GetVal(tabella_measure,"MEAS_H",record,&valore)!=1)
            {
            fprintf(stderr,"installa_variabili: Errore GetVal MEAS_H\n");
            return(0);
            }
         LalAC=valore.float_val;

         if(GetVal(tabella_measure,"MEAS_L",record,&valore)!=1)
            {
            fprintf(stderr,"installa_variabili: Errore GetVal MEAS_L\n");
            return(0);
            }
         LalBC=valore.float_val;

         if(GetVal(tabella_measure,"MEAS_LL",record,&valore)!=1)
            {
            fprintf(stderr,"installa_variabili: Errore GetVal MEAS_LL\n");
            return(0);
            }
         LalBS=valore.float_val;

printf("DEBUG:inst_aa:nome_scada=%*s\n",SCD_SIGLA,nome_scada);
         installa_aa(nome_scada,desc_scada,umis,nome_sim,
		LalBS,LalBC,LalAC,LalAS,
                zona,BandaMorta,trattamento,severita,
                gerarchia.chLivello[0],
                gerarchia.chLivello[1],
                gerarchia.chLivello[2],
                gerarchia.chLivello[3],
                gerarchia.chLivello[4],
                gerarchia.chLivello[5]);
	point_inst = 1;
         }
      }
   if(rec_found == -3)
	  installa_err(nome_scada,TAG_NOT_IN_SCADA);
   if((point_inst == 0)&&(rec_found >=0))
	  installa_err(nome_scada,TAG_NOT_FOUND_IN_MEASURE_OR_ALARM);
   if(rec_found == -1)
	  installa_err(nome_scada,TAG_NOT_FOUND_IN_TAG);
   }

CloseTable(tabella_alarm);
CloseTable(tabella_measure);

#if defined OLD
for(i=0;i<tot_variabili;i++)
  if(IsNomeScada(variabili[i].descr,i))
    {
        if(IsAna(variabili[i].nome))
	{
/*
	printf("%d) %s %s\n",i,
		variabili[i].nome,variabili[i].descr);
*/
	GetTagScada(variabili[i].descr,nome_scada);
	GetDescScada(variabili[i].descr,desc_scada);
	GetTagSim(variabili[i].nome,nome_sim);
	CostruisciUniMis(variabili[i].nome,umis);
	installa_aa(nome_scada,desc_scada,umis,nome_sim,
		LIM_BS_AA,LIM_BC_AA,LIM_AC_AA,LIM_AS_AA,
                ZONA_AA,SEV_AA,TRAT_AA,BANDA_AA,
		variabili[i].mod,variabili[i].blocco,
		NO_GER,NO_GER,NO_GER,NO_GER);
	}
    else
	{
/*
	printf("%d) %s %s\n",i,
		variabili[i].nome,variabili[i].descr);
*/
	GetTagScada(variabili[i].descr,nome_scada);
	GetDescScada(variabili[i].descr,desc_scada);
	GetTagSim(variabili[i].nome,nome_sim);
printf("DEBUG:inst_da:nome_scada=%*s\n",SCD_SIGLA,nome_scada);
	installa_da(nome_scada,desc_scada,nome_sim,
		STATO0_DA,STATO1_DA,"","","",0,
                ZONA_AA,SEV_AA,TRAT_AA,
		variabili[i].mod,variabili[i].blocco,
		NO_GER,NO_GER,NO_GER,NO_GER);
	}
    }
#endif
/*
Modifica fatta per calcolate sulla situazione allarmi:

Calcolata indipendente dalla zona di impianto
    "     dipendente solo da gerarchia 
    "     utilizzata PEN$A10_ per ogni gerarchia
by Fabio
*/



//	INSTALLAZIONE ANALOGICI CALCOLATI STANDARD
if(crea_as()!=1)
	errore("crea_as");
/*
printf("installa_variabili:numero_gerarchie=%d\n",numero_gerarchie);
*/
for(j=0;j<numero_gerarchie;j++)
   for(i=0;i<num_codici_allaras;i++)
	{
	//sprintf(nome_scada,"%s_%4d",allaras[i].CodiceAll,j);
/*	printf("installa_variabili:nome calcolata=%s-zone_gerarchie=%x\n",allaras[i].CodiceAll,zone_gerarchie[j]);
*/      

/*
Installa variabili che sono solo PEN$A (in cui c' e' la situazione allarmi)
Se la calcolata e' di tipo ARC o i(e' PEN ma non e' $A) o ( non ha
zone_gerarchie[j]==0) 
le altre calcolate di tipo as sono installate come prima.
*/
	/* Trovo il tipo di allarme */
        tag_alarm_type=strchr(allaras[i].CodiceAll,'$');

	if(( (allaras[i].TipoCalc != AS_GERARCHIA_ALLARCHIVIATI) &&
           (allaras[i].TipoCalc != AS_GERARCHIA_ALLPENDENTI) )   ||
	    ( (allaras[i].TipoCalc==AS_GERARCHIA_ALLPENDENTI) && 
           ( *(tag_alarm_type+1)=='A') && 
	   (zone_gerarchie[j]!=0) )   )
		{
		if (allaras[i].TipoCalc!=AS_GERARCHIA_ALLPENDENTI)
		  sprintf(nome_scada,"%s%x%x_",allaras[i].CodiceAll,
			DBALL_MONITOR,zone_gerarchie[j]);
		else
		   sprintf(nome_scada,"%s%x%x_",allaras[i].CodiceAll,
			DBALL_MONITOR,0);

		for(k=0;k<6;k++)
			if(gerarchie[j].chLivello[k] == -1)
				sprintf(nome_scada,"%sFF",nome_scada);
			else
				sprintf(nome_scada,"%s%2x",
	        			nome_scada,gerarchie[j].chLivello[k]);
	
		for(k=0;k<strlen(nome_scada);k++)
			if(nome_scada[k]==' ')
				nome_scada[k]='0';
		to_upper(nome_scada);
		sprintf(desc_scada,"%s [%3d|%3d|%3d|%3d|%3d|%3d]",
			allaras[i].DescrAll,
			gerarchie[j].chLivello[0],
			gerarchie[j].chLivello[1],
			gerarchie[j].chLivello[2],
			gerarchie[j].chLivello[3],
			gerarchie[j].chLivello[4],
			gerarchie[j].chLivello[5]);
		installa_as(nome_scada,desc_scada,"allarm",allaras[i].PeriodoCalc,
			allaras[i].TipoCalc,
			LIM_BS_AS,LIM_BC_AS,LIM_AC_AS,LIM_AS_AS,
                	ZONA_AS,SEV_AS,TRAT_AS,BANDA_AS,
			NO_GER,NO_GER,NO_GER,NO_GER,NO_GER,NO_GER,
			gerarchie[j].chLivello[0],
			gerarchie[j].chLivello[1],
			gerarchie[j].chLivello[2],
			gerarchie[j].chLivello[3],
			gerarchie[j].chLivello[4],
			gerarchie[j].chLivello[5],
			zone_gerarchie[j],1);
		} /* end if var == PEN$A */
	} /* end for num codici as */

//	INSTALLAZIONE ANALOGICI E DIGITALI DI USCITA
if(crea_ao()!=1)
	errore("crea_ao");
if(crea_do()!=1)
	errore("crea_do");

prog_ana = 0;
prog_dig = 0;
prog_com = 0;
#if defined OLD
for(i=0;i<tot_variabili;i++)
{
   if(IsAna(variabili[i].nome)&&variabili[i].tipo==INGRESSO_NC)
	if(IsNomeScada(variabili[i].descr,i))
	{
	//printf("Ingresso %s\n",variabili[i].nome);
	GetTagScada(variabili[i].descr,nome_scada);
	sprintf(desc_scada,"STEP COMMAND ON [%s]",nome_scada);
	GetTagScada(variabili[i].descr,nome_sim);
	CostruisciUniMis(variabili[i].nome,umis);
	sprintf(nome_scada,"INPUT_%4d",prog_ana);
	for(k=0;k<strlen(nome_scada);k++)
		if(nome_scada[k]==' ')
			nome_scada[k]='0';
	installa_ao(nome_scada,desc_scada,umis,nome_sim,
                ZONA_AO,PRINT_AO,
		variabili[i].mod,variabili[i].blocco,
		NO_GER,NO_GER,NO_GER,NO_GER);

	++ prog_ana;
	}
if(IsDig(variabili[i].nome)&&variabili[i].tipo==INGRESSO_NC)
	if(IsNomeScada(variabili[i].descr,i))
	{
	//printf("Ingresso digitale %s\n",variabili[i].nome);
	GetTagScada(variabili[i].descr,nome_scada);
	sprintf(desc_scada,"PULSE COMMAND ON [%s]",nome_scada);
	sprintf(desc_scada1,"COMMAND TO 0 ON [%s]",nome_scada);
	sprintf(desc_scada2,"COMMAND TO 1 ON [%s]",nome_scada);
	GetTagScada(variabili[i].descr,nome_sim);
	sprintf(nome_scada,"PULSE_COMMAND_%4d",prog_com);
	for(k=0;k<strlen(nome_scada);k++)
		if(nome_scada[k]==' ')
			nome_scada[k]='0';
	sprintf(nome_scada1,"ZERO_COMMAND_%4d",prog_com);
	for(k=0;k<strlen(nome_scada1);k++)
		if(nome_scada1[k]==' ')
			nome_scada1[k]='0';
	sprintf(nome_scada2,"ONE_COMMAND_%4d",prog_com);
	for(k=0;k<strlen(nome_scada2);k++)
		if(nome_scada2[k]==' ')
			nome_scada2[k]='0';
	installa_do(nome_scada,desc_scada,nome_sim,  // impulsivo
                ZONA_DO,255,PRINT_DO,
		variabili[i].mod,variabili[i].blocco, 
		NO_GER,NO_GER,NO_GER,NO_GER);
	installa_do(nome_scada1,desc_scada1,nome_sim, // comando a 0
                ZONA_DO,0,PRINT_DO,
		variabili[i].mod,variabili[i].blocco,
		NO_GER,NO_GER,NO_GER,NO_GER);
	installa_do(nome_scada2,desc_scada2,nome_sim, // comando a 1
                ZONA_DO,1,PRINT_DO,
		variabili[i].mod,variabili[i].blocco,
		NO_GER,NO_GER,NO_GER,NO_GER);

	prog_dig +=3;
	++ prog_com;
	}
}
#endif


return(1);
}

static int IsNomeScada(char *descr,int ind)
{
char *app;
int i;

app=strstr(descr,COD_SIGLA_SCADA);
if(app == NULL)
	return(0);
else 
	{
	// verifica che il punto non sia gia' stato esaminato
	// la connessione fra blocchi replica il nome e la descrizione
	// viene fatto il controllo sull'indirizzo della variabile
	for(i=ind-1;i>=0;i--)
		if(variabili[i].addr == variabili[ind].addr)
			return(0);
	return(1);
	}

}

static int GetTagScada(char *descr,char *nome)
{
char *app;
int i;

memset(nome,0,SCD_SIGLA+1);
app=strstr(descr,COD_SIGLA_SCADA);
if(app == NULL)
	return(0);
app +=strlen(COD_SIGLA_SCADA);
for(i=0;(i<SCD_SIGLA+1)&&(*app!=' ')&&(app!=NULL);i++,app++)
	nome[i]=*app;
nome[SCD_SIGLA]=0;	
}

static int GetTagSim(char *nome_rtf,char *nome)
{
char *app;

strcpy(nome,nome_rtf);
if((app=strstr(nome," "))!=NULL)
	*app=0;
}
static int GetDescScada(char *descr_sim,char *descr_scada)
{
char sim[MAX_LUN_DESCR_VAR];
int i;
char *app1;
char *app2;
char *app3;

strcpy(sim,descr_sim);
app1=sim;
app2=strstr(sim,COD_SIGLA_SCADA);
app3=strstr(app2," ");
*app2=0;
strcpy(sim,app1);
if(app3!=NULL)
	strcat(sim,app3);
sim[SCD_DESCRIZIONE]=0;
strcpy(descr_scada,sim);
}

static int GetAlarmMeasureTag(APP_TAG * app_tag,int num_record,char * sigla,
		ID_TABLE *tabella,int num_tab, int *rec_found)
{
VAL_RET valore;
int ret = -1;
int i;
int tag_id = -1;

for(i=0;i<num_record;i++)
    {

	if(!strcmp(sigla,app_tag[i].TAG_NAME))
                {
		tag_id = app_tag[i].TAG_ID;
		if(app_tag[i].TAG_SCADA_USE!=1)
        		{
			*rec_found = -3;
			return(-1);
        		}
		*rec_found = i;
		break;
                }
    }
if(tag_id == -1)
        {
	
	*rec_found = -1;
	return(-1);
        }
for(i=0;i<num_tab;i++)
    {
        //  TAG_ID
        if(GetVal(tabella,"TAG_ID",i,&valore)!=1)
                {
                fprintf(stderr,"GetAlarmTag: Errore GetVal TAG_ID\n");
                return(-1);
                }
	if(valore.int_val == tag_id)
		return(i);
    }
return(-1);
}
	
static int GetSignalFromType(int tipo,char *signal)
{
ID_TABLE *tabella;
VAL_RET valore;
int num_record;
int i;

// Apertura tabella AlarmType
tabella = OpenTablePath(path_input,ALARMTYPE_TABLE);
if(tabella == NULL)
        {
        fprintf(stderr,"GetSignalFromType: apertura tabella [%s]\n",ALARMTYPE_TABLE);
        return(0);
        }
num_record = NumRecord(tabella);
for(i=0;i<num_record;i++)
        {
        //  Type
        if(GetVal(tabella,"ALTYPE_ID",i,&valore)!=1)
                {
                fprintf(stderr,"GetAlarmTag: Errore GetVal Type\n");
		CloseTable(tabella);
                return(0);
                }
	if(valore.int_val == tipo)
                {
        	//  Signal
        	if(GetVal(tabella,"ALTYPE_SIGNAL",i,&valore)!=1)
                    {
                    fprintf(stderr,"GetAlarmTag: Errore GetVal Signal\n");
		    CloseTable(tabella);
                    return(0);
                    }
		sprintf(signal,"%s%s",TAG_SIGNAL,valore.char_val);
		CloseTable(tabella);
		return(1);
                }
        }
CloseTable(tabella);
return(0);
}

static int GetGerarchie(ID_TABLE *tabella,int record,S_DBGERA *gerarchia,char *fieldPrefix)
{
VAL_RET valore;
char szBuff[MAX_LUN_NOME_CAMPO];
int j;

for(j=0;j<n_gerarchie;j++)
{
   sprintf(szBuff,"%s_HIER%d",fieldPrefix,j);
   if(GetVal(tabella,szBuff,record,&valore)!=1)
      {
      fprintf(stderr,"GetGerarchie: Errore GetVal [%s]\n",szBuff);
      return(0);
      }
   gerarchia->chLivello[j]=valore.int_val;
}

return(1);
}

static int GetStato01(int tipo,char *desc,char *stato0, char *stato1)
{
	sprintf(stato0,"NORMAL");
	strncpy(stato1,desc,SCD_STATO);
	stato0[SCD_STATO]=0;
	stato1[SCD_STATO]=0;
return(1);
}

static int to_upper(char *t)
{
int i;
if(t == NULL)
        return(0);
for(i=0;i<strlen(t);i++)
        t[i]=toupper(t[i]);
return(1);
}

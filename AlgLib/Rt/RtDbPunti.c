/**********************************************************************
*
*       C Source:               RtDbPunti.c
*       Subsystem:              6
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug 29 13:58:55 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: RtDbPunti.c-6 %  (%full_filespec: RtDbPunti.c-6:csrc:6 %)";
#endif
/*
Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)RtDbPunti.c	5.1\t11/10/95";
/*
modulo RtDbPunti.c
tipo 
release 5.1
data 11/10/95
reserved @(#)RtDbPunti.c	5.1
*/
/*
*
* Oggetto RtDbPunti :
*			oggetto per la gestione del database del simulatore.
*	
*		Ver: 1.0
*		13 giugno 1995
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>


#include <Rt/Rt.h>
#include <Rt/RtDbPuntiP.h>  /* inclusione header privato */

char *crea_shrmem(int,int,int *);

/* dichiarazioni funzioni varie interne (statiche) */
static int sizeFromHead(RtDbPuntiOggetto);
static void showErrorNoDb(char *);
static int sizeDati(RtDbPuntiOggetto);
extern int sgancia_shrmem(char *);
extern void elimina_shrmem(int,char*,int);


/* dichiarazioni di strutture ad uso interno  */

/* dichiarazione dei metodi */
static Boolean InitializeDbPunti(RtDbPuntiOggetto, RtErroreOggetto ,char *,
	                         int, SIMULATOR *);
static Boolean CloseDbPunti(RtDbPuntiOggetto );


/* Inizializzazione del class record */

/* Inizializzazione del class record */
RtDbPuntiClassRec rtDbPuntiClassRec = {
{ /* dbPunti fields */
/* initialize               */      InitializeDbPunti,
/* close                    */      CloseDbPunti,
}
};


OggettoClass rtDbPuntiOggettoClass = (OggettoClass) &rtDbPuntiClassRec;


/****************************************************************************
*                                                                           *
*          Metodi dell'oggetto RtDbPunti                                       *
*                                                                           *
*****************************************************************************/

/*
Metodo InitializeDbPunti  dell'oggetto RtDbPunti.
File:    S02_$SO   lo legge per agganciarsi alla SHM header ed inserisce una
                   chiave identificativa.
         NULL      si aggancia controllando l'inserimento di una chiave 
                   identificativa.
         TEST      si aggancia e se la chiave non corrisponde si sgancia.
*/
static Boolean InitializeDbPunti(RtDbPuntiOggetto dbpunti, 
	                         RtErroreOggetto errore, char *file_top, 
                                 int tipo, SIMULATOR *sim)
{
int key,size,i;
S02 *top;
FILE*fp_top;
int condizione;

// printf("RtDbPunti: pid=%d metodo InitializeDbPunti \n\t file=%s tipo=%d\n",
//        getpid(),file_top,tipo);

/*
	gestione dell'oggetto errore
*/
if(errore == NULL)
	{
	dbpunti->rtDbPunti.errore_privato = True;
	dbpunti->rtDbPunti.errore=RtCreateErrore(RT_ERRORE_TERMINALE,
						NULL);
	}
else
	{
	dbpunti->rtDbPunti.errore_privato = False;
	dbpunti->rtDbPunti.errore=errore;
	}

/*
    Condizione: 0 se deve leggere il file della topologia;
    2 se caso test, 1 se NULL.
*/
    if ( file_top == NULL )
         condizione=1;
    else
       if ( strcmp(file_top,"TEST")==0 )
         condizione=2;
       else
         condizione=0;
    if( condizione>0 )
	{
/*      Allocazione della shared memory header */
	key = atoi(getenv("SHR_USR_KEY")); 
	dbpunti->rtDbPunti.punt_head = (HEAD_DBPUNTI *)
	crea_shrmem(key+ID_SH_HEAD_SIM+2*tipo,sizeof(HEAD_DBPUNTI),
		&(dbpunti->rtDbPunti.id_head));
        /*
        printf("\t\t Prima shm id=%ld size=%d\n",
                dbpunti->rtDbPunti.punt_head,sizeof(HEAD_DBPUNTI));
         */
/*
            Verifica della chiave di riconoscimento.
            Se file_top==TEST e la chiave non corrisponde si sgancia.
*/
            if(dbpunti->rtDbPunti.punt_head->key_head != KEY_HEAD)
               {
               if( condizione==1 )
                   RtShowErrore(errore,RT_ERRORE_NO_ATTACH,
                                "InitializeDbPunti");
               else
                   {
                   sgancia_shrmem((char*)dbpunti->rtDbPunti.punt_head);
                   }
               return(False);
               }
            else
               if( condizione==2 )
                   printf("\t file_top==TEST: SHARED AGGANCIATA\n");
	}
else
	{
/*      Lettura file della topologia  (s02) */
	if((fp_top=fopen(file_top,"r"))!=NULL)
		{
		top = (S02*)malloc(sizeof(S02));
		fread( &(top->nmod), sizeof( int), 1, fp_top);
		fread( &(top->model[0]), sizeof( MODEL), top->nmod, fp_top);
		fclose(fp_top);
		}
	else
		{
		RtShowErrore(errore,RT_ERRORE_NO_FILE_TOP,
			"InitializeDbPunti");
		return(False);
		}

/*      Allocazione della shared memory header */
	key = atoi(getenv("SHR_USR_KEY")); 
	dbpunti->rtDbPunti.punt_head = (HEAD_DBPUNTI *)
	crea_shrmem(key+ID_SH_HEAD_SIM+2*tipo,sizeof(HEAD_DBPUNTI),
		&(dbpunti->rtDbPunti.id_head));
	memset(dbpunti->rtDbPunti.punt_head,0,sizeof(HEAD_DBPUNTI));

/*      Inserisco in memoria i parametri della sessione */
        memcpy(&(dbpunti->rtDbPunti.punt_head->hdrg.simulator),sim,
               sizeof(SIMULATOR));

        /*
        printf("\t\t Prima shm id=%ld size=%d\n",
                dbpunti->rtDbPunti.punt_head,sizeof(HEAD_DBPUNTI));
         */


	/*
		inserimento della chiave di riconoscimento
	*/
	dbpunti->rtDbPunti.punt_head->key_head=KEY_HEAD;

	/*
		riempimento della shared memory allocata
	*/
	dbpunti->rtDbPunti.punt_head->n_task=top->nmod;
	for(i=0;i<dbpunti->rtDbPunti.punt_head->n_task;i++)
		{
		dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].stati=
			top->model[i].punt_ivin-top->model[i].punt_ivus;
		dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].ingressi=
			top->model[i].punt_ider-top->model[i].punt_ivin;
		dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].derivate=
		   top->model[i].punt_idati-top->model[i].punt_ider;
		dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].dati=
		   top->model[i].punt_ifine-top->model[i].punt_idati;
		/********
		printf("Stati=%d Ingressi=%d Derivate=%d Dati=%d\n",
		   dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].stati,
		   dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].ingressi,
		   dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].derivate,
		   dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].dati);
		********/
		}


	/*
		libero la struttura top
	*/
	free(top);
	}


dbpunti->rtDbPunti.size = sizeFromHead(dbpunti);
dbpunti->rtDbPunti.punt_data = (float *)
crea_shrmem(key+ID_SH_SIM+2*tipo,dbpunti->rtDbPunti.size,
	&(dbpunti->rtDbPunti.id_data));

dbpunti->rtDbPunti.punt_statistics=(STAT_DBPUNTI*)
     ( (long)(dbpunti->rtDbPunti.punt_data)+
       (long)(sizeDati(dbpunti)) );

dbpunti->rtDbPunti.perturbazioni =  (TIPO_PERT*)
     ( (long)(dbpunti->rtDbPunti.punt_statistics) + 
       (long)(sizeof(STAT_DBPUNTI)) );

dbpunti->rtDbPunti.perturbazioni_att = (TIPO_PERT*)
    ( (long)(dbpunti->rtDbPunti.perturbazioni)+
      (long)(sizeof(TIPO_PERT)*
             dbpunti->rtDbPunti.punt_head->hdrg.simulator.max_pertur) );

dbpunti->rtDbPunti.snapshot          = (SNTAB*)
    ( (long)(dbpunti->rtDbPunti.perturbazioni_att) +
      (long)(sizeof(TIPO_PERT)*
             dbpunti->rtDbPunti.punt_head->hdrg.simulator.max_pertur) );

#if defined BACKTRACK
dbpunti->rtDbPunti.backtrack         = (BKTAB*)
    ( (long)(dbpunti->rtDbPunti.snapshot) +
      (long)(sizeof(SNTAB)*
             dbpunti->rtDbPunti.punt_head->hdrg.simulator.max_snap_shot) );
#endif

/*******
printf("\t\t Seconda shm id=%ld size=%d STAT_DBPUNTI=%d\n",
        dbpunti->rtDbPunti.punt_data,dbpunti->rtDbPunti.size,
        sizeof(STAT_DBPUNTI));
printf("\n\t statistics       =%d",
        dbpunti->rtDbPunti.punt_statistics);
printf("\n\t perturbazioni    =%d\n",
        dbpunti->rtDbPunti.perturbazioni);
printf("\t perturbazioni_att=%d\n",
        dbpunti->rtDbPunti.perturbazioni_att);
printf("\t snapshot         =%ld\n",
        dbpunti->rtDbPunti.snapshot);
printf("\t backtrack        =%d\n",
        dbpunti->rtDbPunti.backtrack);
*******/
return(True);
}

/*
Metodo CloseDbPunti  dell'oggetto conn
*/
static Boolean CloseDbPunti(RtDbPuntiOggetto dbpunti)
{
// printf("RtDbPunti: metodo CloseDbPunti\n");
/*
	gestione dell'oggetto errore
*/
if(dbpunti->rtDbPunti.errore_privato)
	RtDestroyErrore(dbpunti->rtDbPunti.errore);

/*
	cancella le shared memory
*/
elimina_shrmem(dbpunti->rtDbPunti.id_head,
	(char*)dbpunti->rtDbPunti.punt_head, sizeof(HEAD_DBPUNTI));
elimina_shrmem(dbpunti->rtDbPunti.id_data,
	(char*)dbpunti->rtDbPunti.punt_data, dbpunti->rtDbPunti.size);
		
if(dbpunti != NULL)
	{
	free(dbpunti);
	return(True);
	}
else
	return(False);
}

/****************************************************************************
*                                                                           *
*                          Funzioni private                                 *
*                                                                           *
*****************************************************************************/

static int sizeDinamica(RtDbPuntiOggetto dbpunti)
{
int size;

    size   = 2*sizeof(TIPO_PERT)*
             dbpunti->rtDbPunti.punt_head->hdrg.simulator.max_pertur +
#if defined BACKTRACK
             dbpunti->rtDbPunti.punt_head->hdrg.simulator.max_back_track * 
             sizeof(BKTAB) +
#endif
             dbpunti->rtDbPunti.punt_head->hdrg.simulator.max_snap_shot  *  
             sizeof(SNTAB);

    return(size);
}

static int sizeDati(RtDbPuntiOggetto dbpunti)
{
int size=0;
int i;

   for(i=0;i<dbpunti->rtDbPunti.punt_head->n_task;i++)
      {
      size += dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].stati 
		*sizeof(float);
      size += dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].ingressi 
		*sizeof(float);
      size += dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].derivate 
		*sizeof(float);
      size += dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].dati 
		*sizeof(float);
      }

return(size);
}

static int sizeFromHead(RtDbPuntiOggetto dbpunti)
{
int i;
int size=0;
int sizedati=0;
int sizedinamica=0;

size         = sizeof(STAT_DBPUNTI);
sizedati     = sizeDati(dbpunti);
sizedinamica = sizeDinamica(dbpunti);

size = sizedati + size + sizedinamica;
/*
printf("\t size=%d (dati=%d+strutt=%d+dinamica=%d)\n",
         size,sizedati,sizeof(STAT_DBPUNTI),sizedinamica);
*/
return(size);
}

static void showErrorNoDb(char *proc)
{
RtErroreOggetto errore=NULL;

errore=RtCreateErrore(RT_ERRORE_TERMINALE, NULL);
RtShowErrore(errore,RT_ERRORE_NO_DBP_LOAD,proc);
if(errore)
	RtDestroyErrore(errore);
}

/****************************************************************************
*                                                                           *
*       Funzioni richiamabili dall'esterno per la gestione                  *
*       dell'oggetto RtDbPunti                                              *
*                                                                           *
*****************************************************************************/
RtDbPuntiOggetto RtCreateDbPunti(RtErroreOggetto errore, char *file_top,
	                         int tipo, SIMULATOR *sim)
{
RtDbPuntiOggetto newdb = NULL;

newdb = (RtDbPuntiRec*) malloc(sizeof (RtDbPuntiRec));

if(newdb == NULL)
	{
	RtShowErrore(errore,RT_ERRORE_MALLOC,"RtCreateDbPunti");
	return(NULL);
	}
memset(newdb,0,sizeof (RtDbPuntiRec));

if((rtDbPuntiClassRec.rtDbPunti_class.initialize)
			(newdb,errore,file_top,tipo,sim))
	return(newdb);
else
	return(NULL);

}


Boolean RtDestroyDbPunti(RtDbPuntiOggetto dbpunti)
{
// printf("RtDestroyDbPunti\n");

if((rtDbPuntiClassRec.rtDbPunti_class.close)(dbpunti))
return(True);
else
return(False);
}

int RtDbPNumeroModelli(RtDbPuntiOggetto dbpunti)
{
if(dbpunti==NULL)
{
showErrorNoDb("RtDbPNumeroModelli");
return(-1);
}

return(dbpunti->rtDbPunti.punt_head->n_task);
}

int RtDbPInizioModelli(RtDbPuntiOggetto dbpunti,int mod)
{
int iniz = 0;
int i;

if(dbpunti==NULL)
{
showErrorNoDb("RtDbPInizioModelli");
return(-1);
}

if((mod>=dbpunti->rtDbPunti.punt_head->n_task)||(mod <0))
{
RtShowErrore(dbpunti->rtDbPunti.errore,
	RT_ERRORE_NO_MODEL,"RtDbPInizioModelli");
return(-1);
}

for(i=0;i<mod;i++)
{
iniz += dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].stati;
iniz += dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].ingressi;
iniz += dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].derivate;
iniz += dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[i].dati;
}

return(iniz);
}



int RtDbPGetHeaderReg(RtDbPuntiOggetto dbpunti,
                                          HEADER_REGISTRAZIONI *hdreg)
{

    if(dbpunti==NULL)
       {
       showErrorNoDb("RtDbPGetHeaderReg");
       return(-1);
       }
    memcpy(hdreg, &(dbpunti->rtDbPunti.punt_head->hdrg),
           sizeof(HEADER_REGISTRAZIONI));

    return(0);
}
/************************************************************
************************************************************/



int RtDbPNumStatiModelli(RtDbPuntiOggetto dbpunti,int mod)
{
int numero = 0;

if(dbpunti==NULL)
{
showErrorNoDb("RtDbPInizioModelli");
return(-1);
}

if((mod>=dbpunti->rtDbPunti.punt_head->n_task)||(mod <0))
{
RtShowErrore(dbpunti->rtDbPunti.errore,
	RT_ERRORE_NO_MODEL,"RtDbPInizioModelli");
return(-1);
}

numero = dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[mod].stati;

return(numero);
}


int RtDbPNumIngModelli(RtDbPuntiOggetto dbpunti,int mod)
{
int numero = 0;

if(dbpunti==NULL)
{
showErrorNoDb("RtDbPInizioModelli");
return(-1);
}

if((mod>=dbpunti->rtDbPunti.punt_head->n_task)||(mod <0))
{
RtShowErrore(dbpunti->rtDbPunti.errore,
	RT_ERRORE_NO_MODEL,"RtDbPInizioModelli");
return(-1);
}

numero = dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[mod].ingressi;

return(numero);
}


int RtDbPNumDerivModelli(RtDbPuntiOggetto dbpunti,int mod)
{
int numero = 0;

if(dbpunti==NULL)
{
showErrorNoDb("RtDbPInizioModelli");
return(-1);
}

if((mod>=dbpunti->rtDbPunti.punt_head->n_task)||(mod <0))
{
RtShowErrore(dbpunti->rtDbPunti.errore,
	RT_ERRORE_NO_MODEL,"RtDbPInizioModelli");
return(-1);
}

numero = dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[mod].derivate;

return(numero);
}


int RtDbPNumDatiModelli(RtDbPuntiOggetto dbpunti,int mod)
{
int numero = 0;

if(dbpunti==NULL)
{
showErrorNoDb("RtDbPInizioModelli");
return(-1);
}

if((mod>=dbpunti->rtDbPunti.punt_head->n_task)||(mod <0))
{
RtShowErrore(dbpunti->rtDbPunti.errore,
	RT_ERRORE_NO_MODEL,"RtDbPInizioModelli");
return(-1);
}

numero = dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[mod].dati;

return(numero);
}


int RtDbPSizeModelli(RtDbPuntiOggetto dbpunti,int mod)
{
int size = 0;

if(dbpunti==NULL)
{
showErrorNoDb("RtDbPInizioModelli");
return(-1);
}

if((mod>=dbpunti->rtDbPunti.punt_head->n_task)||(mod <0))
{
RtShowErrore(dbpunti->rtDbPunti.errore,
	RT_ERRORE_NO_MODEL,"RtDbPInizioModelli");
return(-1);
}

size += dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[mod].stati;
size += dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[mod].ingressi;
size += dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[mod].derivate;
size += dbpunti->rtDbPunti.punt_head->hdrg.num_modelli[mod].dati;

size = size*sizeof(float);

return(size);
}

int RtDbPSizeHeader(RtDbPuntiOggetto dbpunti)
{
int size = 0;

if(dbpunti==NULL)
{
showErrorNoDb("RtDbPSizeHeader");
return(-1);
}

return(sizeof(HEAD_DBPUNTI));
}



int RtDbPSizeData(RtDbPuntiOggetto dbpunti)
{
int size;

if(dbpunti==NULL)
{
showErrorNoDb("RtDbPNumeroModelli");
return(-1);
}

size = sizeDati(dbpunti);
return(size);
/*return(dbpunti->rtDbPunti.size-sizeof(STAT_DBPUNTI));*/
}


Boolean RtDbPGetValue(RtDbPuntiOggetto dbpunti,int ind, float *val)
{
if(dbpunti==NULL)
{
showErrorNoDb("RtDbPGetValue");
return(False);
}

memcpy(val,&dbpunti->rtDbPunti.punt_data[ind],sizeof(float));

return(True);
}

float RtDbPGetValueD(RtDbPuntiOggetto dbpunti,int ind)
{
if(dbpunti==NULL)
	{
	showErrorNoDb("RtDbPGetValueD");
	return(0);
	}

return(dbpunti->rtDbPunti.punt_data[ind]);
}


Boolean RtDbPPutValue(RtDbPuntiOggetto dbpunti,int ind, float val)
{
static float val_in;
if(dbpunti==NULL)
	{
	showErrorNoDb("RtDbPPutValue");
	return(False);
	}

val_in = val;

memcpy(&(dbpunti->rtDbPunti.punt_data[ind]),&val_in,sizeof(float));
return(True);
}

Boolean RtDbPCopyValue(RtDbPuntiOggetto dbpunti,int out, int in)
{
if(dbpunti==NULL)
	{
	showErrorNoDb("RtDbPCopyValue");
	return(False);
	}

memcpy(&dbpunti->rtDbPunti.punt_data[out],
	&dbpunti->rtDbPunti.punt_data[in],sizeof(float));
return(True);
}

Boolean RtDbPClearData(RtDbPuntiOggetto dbpunti)
{
int sizedati=0;

if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPClearData");
        return(False);
        }
/*
memset(dbpunti->rtDbPunti.punt_data,0,
	dbpunti->rtDbPunti.size-sizeof(STAT_DBPUNTI));
*/
sizedati = sizeDati(dbpunti);
memset(dbpunti->rtDbPunti.punt_data,0,sizedati);

return(True);
}

Boolean RtDbPGetTime(RtDbPuntiOggetto dbpunti, float * tempo)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPGetTime");
        return(False);
        }

memcpy(tempo,&(dbpunti->rtDbPunti.punt_statistics->tempo),sizeof(float));

return(True);
}

Boolean RtDbPPutTime(RtDbPuntiOggetto dbpunti, float tempo)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPPutTime");
        return(False);
        }

dbpunti->rtDbPunti.punt_statistics->tempo = tempo;

return(True);
}

Boolean RtDbPGetDelay(RtDbPuntiOggetto dbpunti, float * ritardo)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPGetDelay");
        return(False);
        }

memcpy(ritardo,&(dbpunti->rtDbPunti.punt_statistics->ritardo),sizeof(float));

return(True);
}

Boolean RtDbPPutDelay(RtDbPuntiOggetto dbpunti, float ritardo)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPPutDelay");
        return(False);
        }

dbpunti->rtDbPunti.punt_statistics->ritardo = ritardo;

return(True);
}

Boolean RtDbPGetTimeScaling(RtDbPuntiOggetto dbpunti, float * timescaling)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPGetTimeScaling");
        return(False);
        }

memcpy(timescaling,&(dbpunti->rtDbPunti.punt_statistics->timescaling),
		sizeof(float));

return(True);
}

Boolean RtDbPPutTimeScaling(RtDbPuntiOggetto dbpunti, float timescaling)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPPutTimeScaling");
        return(False);
        }

dbpunti->rtDbPunti.punt_statistics->timescaling = timescaling;

return(True);
}

Boolean RtDbPGetStepScaling(RtDbPuntiOggetto dbpunti, float * stepscaling)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPGetStepScaling");
        return(False);
        }

memcpy(stepscaling,&(dbpunti->rtDbPunti.punt_statistics->stepscaling),sizeof(float));

return(True);
}

Boolean RtDbPPutStepScaling(RtDbPuntiOggetto dbpunti, float stepscaling)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPPuStepScaling");
        return(False);
        }

dbpunti->rtDbPunti.punt_statistics->stepscaling = stepscaling;

return(True);
}

Boolean RtDbPCopyDb(RtDbPuntiOggetto out,RtDbPuntiOggetto in)
{
if((out == NULL)||(in == NULL))
        {
        showErrorNoDb("RtDbPCopyDb");
        return(False);
        }
if(out->rtDbPunti.size != in->rtDbPunti.size)
	{
	RtShowErrore(in->rtDbPunti.errore,RT_ERRORE_NO_ATTACH,"RtCopyDb");
	RtShowErrore(out->rtDbPunti.errore,RT_ERRORE_NO_ATTACH,"RtCopyDb");
	return(False);
	}

memcpy(out->rtDbPunti.punt_data,in->rtDbPunti.punt_data,
		out->rtDbPunti.size);

return(True);
}

NUMERI_MODELLI *RtDbPGetPuntHeadmodelli(RtDbPuntiOggetto dbpunti)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbGetPuntHeadmodelli");
        return(NULL);
        }

return(dbpunti->rtDbPunti.punt_head->hdrg.num_modelli);
}


TIPO_PERT *RtDbPGetPuntPert(RtDbPuntiOggetto dbpunti)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbGetPuntPert");
        return(NULL);
        }

/*printf("\t\t RtDbPGetPuntPert ritorna=%d\n",
        dbpunti->rtDbPunti.perturbazioni);*/
return(dbpunti->rtDbPunti.perturbazioni);
}

TIPO_PERT *RtDbPGetPuntPertAtt(RtDbPuntiOggetto dbpunti)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbGetPuntPertAtt");
        return(NULL);
        }

/* printf("\t\t RtDbPGetPuntPertAtt ritorna=%d\n",
        dbpunti->rtDbPunti.perturbazioni_att);*/

return(dbpunti->rtDbPunti.perturbazioni_att);
}

Boolean RtDbPGetStepCr(RtDbPuntiOggetto dbpunti, int * stepcr)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPGetStepCr");
        return(False);
        }

memcpy(stepcr,&(dbpunti->rtDbPunti.punt_statistics->stepcr),sizeof(int));

return(True);
}

Boolean RtDbPPutStepCr(RtDbPuntiOggetto dbpunti, int stepcr)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPPuStepCr");
        return(False);
        }

dbpunti->rtDbPunti.punt_statistics->stepcr = stepcr;

return(True);
}

Boolean RtDbPGetStepDb(RtDbPuntiOggetto dbpunti, int * stepdb)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPGetStepDb");
        return(False);
        }

memcpy(stepdb,&(dbpunti->rtDbPunti.punt_statistics->stepdb),sizeof(int));

return(True);
}

Boolean RtDbPPutStepDb(RtDbPuntiOggetto dbpunti, int stepdb)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPPuStepDb");
        return(False);
        }

dbpunti->rtDbPunti.punt_statistics->stepdb = stepdb;

return(True);
}

Boolean RtDbPGetNumCr(RtDbPuntiOggetto dbpunti, int * numcr)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPGetNumCr");
        return(False);
        }

memcpy(numcr,&(dbpunti->rtDbPunti.punt_statistics->numcr),sizeof(int));

return(True);
}

Boolean RtDbPPutNumCr(RtDbPuntiOggetto dbpunti, int numcr)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPPutNumCr");
        return(False);
        }

dbpunti->rtDbPunti.punt_statistics->numcr = numcr;

return(True);
}

Boolean RtDbPGetStato(RtDbPuntiOggetto dbpunti, int * stato)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPGetStato");
        return(False);
        }

memcpy(stato,&(dbpunti->rtDbPunti.punt_statistics->stato),sizeof(int));

return(True);
}

Boolean RtDbPPutStato(RtDbPuntiOggetto dbpunti, int stato)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPPutStato");
        return(False);
        }

dbpunti->rtDbPunti.punt_statistics->stato = stato;

return(True);
}

Boolean RtDbPGetDt(RtDbPuntiOggetto dbpunti, int mod, float * dt)
{

if(dbpunti==NULL)
	{
	showErrorNoDb("RtDbPGetDt");
	return(False);
	}

if((mod>=dbpunti->rtDbPunti.punt_head->n_task)||(mod <0))
	{
	RtShowErrore(dbpunti->rtDbPunti.errore,
		RT_ERRORE_NO_MODEL,"RtDbPGetDt");
	return(False);
	}

memcpy(dt,&dbpunti->rtDbPunti.punt_statistics->dt[mod],sizeof(float));

return(True);
}

Boolean RtDbPPutDt(RtDbPuntiOggetto dbpunti, int mod, float dt)
{

if(dbpunti==NULL)
	{
	showErrorNoDb("RtDbPPutDt");
	return(False);
	}

if((mod>=dbpunti->rtDbPunti.punt_head->n_task)||(mod <0))
	{
	RtShowErrore(dbpunti->rtDbPunti.errore,
		RT_ERRORE_NO_MODEL,"RtDbPPutDt");
	return(False);
	}

dbpunti->rtDbPunti.punt_statistics->dt[mod] = dt;

return(True);
}

STAT_PROC *RtDbPGetPuntTaskStat(RtDbPuntiOggetto dbpunti, int mod)
{
STAT_PROC *ret;


if(dbpunti==NULL)
	{
	showErrorNoDb("RtDbGetPuntTaskStat");
	return(NULL);
	}

if((mod>=dbpunti->rtDbPunti.punt_head->n_task)||(mod <0))
	{
	RtShowErrore(dbpunti->rtDbPunti.errore,
		RT_ERRORE_NO_MODEL,"RtDbGetPuntTaskStat");
	return(NULL);
	}

return(&dbpunti->rtDbPunti.punt_statistics->task_statistics[mod]);
}


STAT_PROC *RtDbPGetPuntAusStat(RtDbPuntiOggetto dbpunti, int process)
{
STAT_PROC *ret;


if(dbpunti==NULL)
	{
	showErrorNoDb("RtDbGetPuntAusStat");
	return(NULL);
	}

if((process>=MAX_PROC_AUS)||(process <0))
	{
	RtShowErrore(dbpunti->rtDbPunti.errore,
		RT_ERRORE_NO_MODEL,"RtDbGetPuntAusStat");
	return(NULL);
	}

return(&dbpunti->rtDbPunti.punt_statistics->aus_statistics[process]);
}

Boolean RtDbPGetTimeTask(RtDbPuntiOggetto dbpunti, int mod, float * tempo)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPGetTimeTask");
        return(False);
        }

if((mod>=dbpunti->rtDbPunti.punt_head->n_task)||(mod <0))
	{
	RtShowErrore(dbpunti->rtDbPunti.errore,
		RT_ERRORE_NO_MODEL,"RtDbPGetTimeTask");
	return(False);
	}

memcpy(tempo,&(dbpunti->rtDbPunti.punt_statistics->tempo_task[mod]),
		sizeof(float));

return(True);
}

Boolean RtDbPPutTimeTask(RtDbPuntiOggetto dbpunti, int mod, float tempo)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPPutTimeTask");
        return(False);
        }

if((mod>=dbpunti->rtDbPunti.punt_head->n_task)||(mod <0))
	{
	RtShowErrore(dbpunti->rtDbPunti.errore,
		RT_ERRORE_NO_MODEL,"RtDbPPutTimeTask");
	return(False);
	}

dbpunti->rtDbPunti.punt_statistics->tempo_task[mod] = tempo;

return(True);
}

float * RtDbPPuntData(RtDbPuntiOggetto dbpunti)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPPuntData");
        return(NULL);
        }

return(dbpunti->rtDbPunti.punt_data);
}

SNTAB * RtDbPGetPuntSnapshot(RtDbPuntiOggetto dbpunti)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPPuntSnapshot");
        return(NULL);
        }

return(dbpunti->rtDbPunti.snapshot);
}


#if defined BACKTRACK
BKTAB * RtDbPGetPuntBacktrack(RtDbPuntiOggetto dbpunti)
{
if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPPuntBacktrack");
        return(NULL);
        }

return(dbpunti->rtDbPunti.backtrack);
}
#endif

int RtDbPGetModelFromInd(RtDbPuntiOggetto dbpunti ,int ind)
{
int max_ind;
int num_mod;
int i;
int app_ind;

if(dbpunti==NULL)
        {
        showErrorNoDb("RtDbPGetModelFromInd");
        return(-1);
	}
if(ind < 0)
	{
	RtShowErrore(dbpunti->rtDbPunti.errore,
		RT_ERRORE_LOW_IND,"RtDbPGetModelFromInd");
	return(-1);
	}

max_ind = RtDbPSizeData(dbpunti)/sizeof(float);
if(ind > max_ind)
	{
        RtShowErrore(dbpunti->rtDbPunti.errore,
                RT_ERRORE_HIGHT_IND,"RtDbPGetModelFromInd");
        return(-1);
        }
num_mod = RtDbPNumeroModelli(dbpunti);
app_ind = 0;

for(i=0;i<num_mod;i++)
	{
	app_ind += RtDbPSizeModelli(dbpunti,i)/sizeof(float);
	if(ind < app_ind)
		return(i);
	}
RtShowErrore(dbpunti->rtDbPunti.errore,
                RT_ERRORE_MODEL_NOT_FOUND,"RtDbPGetModelFromInd");
return(-1);
}
/* Fine File */

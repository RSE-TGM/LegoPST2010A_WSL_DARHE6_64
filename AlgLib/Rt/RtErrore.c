/**********************************************************************
*
*       C Source:               RtErrore.c
*       Subsystem:              4
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug 29 13:57:06 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: RtErrore.c-2 %  (%full_filespec: RtErrore.c-2:csrc:4 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)RtErrore.c	5.1\t11/10/95";
/*
   modulo RtErrore.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)RtErrore.c	5.1
*/
/*
 *
 * Oggetto RtErrore :
 *			oggetto per la gestione del database del simulatore.
 *	
 *		Ver: 1.0
 *		13 giugno 1995
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>

#include <Rt/Rt.h>
#include <Rt/RtErroreP.h>  /* inclusione header privato */


/* dichiarazioni funzioni varie interne (statiche) */


/* dichiarazioni di strutture ad uso interno  */

/* dichiarazione dei metodi */
static Boolean InitializeErrore(RtErroreOggetto , int, char *);
static Boolean CloseErrore(RtErroreOggetto );
static void VisualizzaErrore(RtErroreOggetto , int, char *);


/* Inizializzazione del class record */

/* Inizializzazione del class record */
RtErroreClassRec rtErroreClassRec = {
  { /* errore fields */
    /* initialize               */      InitializeErrore,
    /* close                    */      CloseErrore,
    /* visualizza               */      VisualizzaErrore,
  }
};


OggettoClass rtErroreOggettoClass = (OggettoClass) &rtErroreClassRec;


static RtErroreInfo ele_errori[] = {
	{
	RT_ERRORE_GENERIC,
	"error",
	"none",
	RT_ERRORE_SEV_WARNING,
	RT_ERRORE_NO_EXIT,
	},
	{
	RT_ERRORE_UNKNOWN,
	"error unknown",
	"none",
	RT_ERRORE_SEV_WARNING,
	RT_ERRORE_NO_EXIT,
	},
	{
	RT_ERRORE_MALLOC,
	"error allocating memory",
	"none",
	RT_ERRORE_SEV_FATAL,
	RT_ERRORE_EXIT,
	},
	{
	RT_ERRORE_NO_FILE_TOP,
	"error reading topology file",
	"verify path",
	RT_ERRORE_SEV_FATAL,
	RT_ERRORE_NO_EXIT,
	},
	{
	RT_ERRORE_NO_DBP_LOAD,
	"error point database not found",
	"none",
	RT_ERRORE_SEV_FATAL,
	RT_ERRORE_NO_EXIT,
	},
	{
	RT_ERRORE_NO_DBT_LOAD,
	"error topology database not found",
	"none",
	RT_ERRORE_SEV_FATAL,
	RT_ERRORE_NO_EXIT,
	},
	{
	RT_ERRORE_NO_MODEL,
	"error model not found",
	"none",
	RT_ERRORE_SEV_FATAL,
	RT_ERRORE_NO_EXIT,
	},
	{
	RT_ERRORE_NO_ATTACH,
	"error shared-memory not attached",
	"none",
	RT_ERRORE_SEV_FATAL,
	RT_ERRORE_NO_EXIT,
	},
	{
	RT_ERRORE_DIFFERENT_DB,
	"error databases are different",
	"none",
	RT_ERRORE_SEV_FATAL,
	RT_ERRORE_NO_EXIT,
	},
	{
	RT_ERRORE_LOW_IND,
	"error ind < 0",
	"none",
	RT_ERRORE_SEV_FATAL,
	RT_ERRORE_NO_EXIT,
	},
	{
	RT_ERRORE_HIGHT_IND,
	"error ind > max ind",
	"none",
	RT_ERRORE_SEV_FATAL,
	RT_ERRORE_NO_EXIT,
	},
	{
	RT_ERRORE_MODEL_NOT_FOUND,
	"error model not found",
	"none",
	RT_ERRORE_SEV_FATAL,
	RT_ERRORE_NO_EXIT,
	},
};

int num_ele_errori = sizeof(ele_errori)/sizeof(RtErroreInfo);


/****************************************************************************
*                                                                           *
*          Metodi dell'oggetto RtErrore                                       *
*                                                                           *
*****************************************************************************/

/*
        Metodo InitializeErrore  dell'oggetto conn
*/
static Boolean InitializeErrore(RtErroreOggetto errore, int tipo_output,
		char * applicazione)
{
//        printf("RtErrore: metodo InitializeErrore\n");

	/*
		setto le info errori
	*/
	errore->rtErrore.info_err = ele_errori;
	errore->rtErrore.num_info_err = num_ele_errori;
	/*
		setto il tipo di output
	*/
	errore->rtErrore.tipo_output = tipo_output;

	/*
		setto l'applicazione 
	*/
	if(applicazione == NULL)
		{
		errore->rtErrore.applicazione=(char *)malloc(strlen("unknown")+1);
		strcpy(errore->rtErrore.applicazione,"unknown");
		}
	else
		{
		errore->rtErrore.applicazione=(char *)malloc(strlen(applicazione)+1);
		strcpy(errore->rtErrore.applicazione,applicazione);
		}

	return(True);
}

/*
        Metodo CloseErrore  dell'oggetto conn
*/
static Boolean CloseErrore(RtErroreOggetto errore)
{
//        printf("RtErrore: metodo CloseErrore\n");
	if(errore != NULL)
		{
		free(errore);
		return(True);
		}
	else
		return(False);
}

static void VisualizzaErrore(RtErroreOggetto errore, int codice, 
	char *procedura)
{
char *proc;
static char *int_proc="unknow procedure";
int i;
FILE *output;

output = stdout;

/******
for(i=0;i<errore->rtErrore.num_info_err;i++)
	fprintf(output,"codice [%d] descr [%s] solving [%s]\n",
		errore->rtErrore.info_err[i].codice,
		errore->rtErrore.info_err[i].descr,
		errore->rtErrore.info_err[i].solving);
***/



if(procedura == NULL)
	proc = int_proc;
else
   	proc = procedura;

/*
 * 	trova l'errore in base al codice
 */
for(i=0;i<errore->rtErrore.num_info_err;i++)
	if(errore->rtErrore.info_err[i].codice == codice)
		break;
if(i == errore->rtErrore.num_info_err)
	for(i=0;i<errore->rtErrore.num_info_err;i++)
		if(errore->rtErrore.info_err[i].codice == RT_ERRORE_UNKNOWN)
			break;

fprintf(output,"[process: %s][pid: %d][procedure: %s]\n", 
		errore->rtErrore.applicazione,getpid(),proc);
fprintf(output,"   description: [%s]\n",errore->rtErrore.info_err[i].descr);
fprintf(output,"   solving: [%s]\n",errore->rtErrore.info_err[i].solving);

if(errore->rtErrore.info_err[i].exit_on_error == RT_ERRORE_EXIT)
	{
	fprintf(output,"process: %s - finished - exit(%d)\n",
			 errore->rtErrore.applicazione,
			errore->rtErrore.info_err[i].codice);
	exit(errore->rtErrore.info_err[i].codice);
	}
}

/****************************************************************************
*                                                                           *
*                          Funzioni private                                 *
*                                                                           *
*****************************************************************************/


/****************************************************************************
*                                                                           *
*       Funzioni richiamabili dall'esterno per la gestione                  *
*       dell'oggetto RtErrore                                                 *
*                                                                           *
*****************************************************************************/

RtErroreOggetto RtCreateErrore(int tipo_output, char *applicazione)
{
RtErroreOggetto newerr;

	newerr = (RtErroreRec*) malloc(sizeof (RtErroreRec));
	memset(newerr,0,sizeof (RtErroreRec));

	if((rtErroreClassRec.rtErrore_class.initialize)(newerr,tipo_output,
			applicazione))
		return(newerr);
	else
		return(NULL);

// printf("RtCreateErrore\n");
}


Boolean RtDestroyErrore(RtErroreOggetto errore)
{
// printf("RtDestroyErrore\n");

if((rtErroreClassRec.rtErrore_class.close)(errore))
	return(True);
else
	return(False);
}

void RtShowErrore(RtErroreOggetto errore, int codice, char *procedura)
{
if(errore == NULL)
	{
	fprintf(stderr,"RtShowErrore: oggetto errore non allocato\n");
	return;
	}
(rtErroreClassRec.rtErrore_class.visualizza)(errore,codice,procedura);
}

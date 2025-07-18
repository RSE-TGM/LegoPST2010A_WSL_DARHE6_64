/*********************************************************************
*
*       C Source:               OlDatabasePunti.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Jul  2 08:39:54 2004 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: OlDatabasePunti.c-40 %  (%full_filespec: OlDatabasePunti.c-40:csrc:1 %)";
#endif


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <Xl/XlResources.h>
#include <Xl/XlCoreP.h>
#include <Xl/XlManagerP.h>
#include <Xl/XlAllarmiP.h>
#if defined SCADA_MMI
#include <Xl/XlGrafico.h>
#endif
#include <Cs/Cs.h>

#include <Ol/OlDatabasePuntiP.h>
#include <Ol/OlDatabasePunti.h>
#include <Ol/OlTree.h>
#include <Cs/Cs.h>

#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/shm.h>
# include <sys/stat.h>
# include <sys/param.h>
#endif
#if defined VMS
# include <stat.h>
# include "vmsipc.h"
#endif
#include <time.h>
#include "sim_types.h"
#include "libipc.h"
#include "libutilx.h"


Boolean XlIsAllarmi(Widget );

char path_sim_correct[FILENAME_MAX];
/* lista delle risorse  */
static XlResources resources[]= {
        {
        XlNnome,
        XlCNome,
        XmRString,
        sizeof(char *),
        XtOffsetOf(OlDatabasePuntiRec,oldatabasePunti.nome_database),
        XmRString,
        "olrtf"
        },
        {
        XlNshrKey,
        XlCShrKey,
        XmRInt,
        sizeof(int),
        XtOffsetOf(OlDatabasePuntiRec,oldatabasePunti.shr_key),
        XmRInt,
        0
        },
        {
        XlNshrKeyS,
        XlCShrKeyS,
        XmRInt,
        sizeof(int),
        XtOffsetOf(OlDatabasePuntiRec,oldatabasePunti.shr_keyS),
        XmRInt,
        0
        }
	};

/* dichiarazioni funzioni varie */
static Boolean init_db();
static Boolean init_db_simul();
Boolean SettaFlag(Widget, float*, PUNT_VARINP *,XlConfInfo *,int ,int );
static int database_type( OlDatabasePuntiObject , char *, char *);         

/* dichiarazione dei metodi (methods) */
static Boolean Initialize();
static float ValVar();
static Boolean RefreshConfinfo();
static float GetTime();
static int AddPage();
static int AddPageHier();
static Boolean DelPage();
static Boolean GetDataAllarmi();
static Boolean CommandAllarmi(OlDatabasePuntiObject , int ,int );
static Boolean estraiPunti();
static Boolean contaPunti();
static Boolean GetHierAll();
static Boolean attiva_client();
static Boolean elimina_client();
static Boolean richiediAllarmi(int,Widget,int);
static Boolean teleperm_richiediAllarmi();
static int DatabasePuntiType();
static int verify_sim(int, char *);
#if defined SCADA_MMI
static int richiediTrend();
#endif
extern int OlInizia_shmMiniASD();
/* Inizializzazione del class record */
OlDatabasePuntiClassRec olDatabasePuntiClassRec = {
  { /* database fields */
    /* initialize               */      Initialize,
    /* valvar                   */      ValVar,
    /* refreshconfinfo          */      RefreshConfinfo,
    /* getTime                  */      GetTime,
    /* addPage                  */      AddPage,
    /* delPage                  */      DelPage,
    /* getDataAllarmi           */      GetDataAllarmi,
    /* commandAllarmi           */      CommandAllarmi,
  }
};

ObjectClass olDatabasePuntiObjectClass = (ObjectClass) &olDatabasePuntiClassRec;


/*
	Metodo di inizializzazioene dell'oggetto database
*/
static Boolean Initialize(OlDatabasePuntiObject database) 
{
/*
Inizializzo puntatore a primo elemento OlTree
*/
	database->oldatabasePunti.root_oltree=NULL;
/*
Inizializzo gli indici dei pid client e delle code di messaggi con client
*/
	database->oldatabasePunti.pid_client=0;
	database->oldatabasePunti.pid_clientS=0;
	database->oldatabasePunti.id_msg_client=0;
	database->oldatabasePunti.id_msg_clientS=0;
/* 
first two cases: client_mmi not on
*/

	if((database->oldatabasePunti.tipo_db==DB_XLSIMUL))
		{
		if(!init_db(database))
			{
			return(False);
			}
		return(True);
		}
/*
altri casi rimasti 
*/
	if((database->oldatabasePunti.tipo_db==DB_XLSIMUL_CLIENT)||
        (database->oldatabasePunti.tipo_db==DB_XLSCADA_CLIENT) ||
	(database->oldatabasePunti.tipo_db==DB_XLCLIENTS))
		return(True);
	XlWarning("OlDatabasePunti","Initialize","database inesistente");
	return(False);
}
/********************************************************************* 
Funzione che:
	se no hostname e no hostnameS 	    -> database = DB_XLSIMUL
	se solo hostname                    -> database = DB_XLSIMUL_CLIENT
	se solo hostnameS                   -> database = DB_XLSCADA_CLIENT
	se hostname e hostnameS             -> database = DB_XLCLIENTS
N.B.
Dopo hostname e hostnameS si puo' inserire un codice (int) che indica il 
numero di connessione client.

Es:  Se devo lanciare un secondo mmi per Simulatore, dopo <hostname>, digito
 nel Context un '2'
***********************************************************************/
static int database_type(OlDatabasePuntiObject database,char * hostname,char * hostnameS)
{
char *s,localhost[MAXHOSTNAMELEN +1],token1[MAXHOSTNAMELEN+1],token3[MAXHOSTNAMELEN+1],token2[MAXCODE],token4[MAXCODE];
register int i;
int ret=-1;

/* 	
Inizializzo contenitori stringhei e contenitori codice
*/

memset(token1,0,MAXHOSTNAMELEN+1);
memset(token3,0,MAXHOSTNAMELEN+1);
memset(token2,0,MAXCODE);
memset(token4,0,MAXCODE);
memset(localhost,0,MAXHOSTNAMELEN +1);

database->oldatabasePunti.codice_host=-1;
database->oldatabasePunti.codice_hostS=-1;
database->oldatabasePunti.shared_set=-1;
database->oldatabasePunti.client_mmi_on=0;
database->oldatabasePunti.client_scada_on=0;
database->oldatabasePunti.hostname=NULL;
database->oldatabasePunti.hostnameS=NULL;

/* 
Se non scrivo niente nel Simulator on e Scada on del Context allora
mmi in locale con simulatore
*/
if( ((hostname==NULL)||(!strlen(hostname))) && 
	((hostnameS==NULL)||(!strlen(hostnameS))) ) 
	{
	return(DB_XLSIMUL);
	}
/*
	Inizio analisi campo Simulator on del Context
*/
if((hostname!=NULL)&&(strlen(hostname)!=0))
	{
	s=hostname;
	sscanf(hostname,"%s",token1);
	s=hostname + strlen(token1);
	if(*s)
		{	
		sscanf(s,"%s",token2);
		}
	if(getindbyname(token1)==-1) /* controllo che hostname sia noto */
		{
		printf("database_type:OlDatabasePunti:hostname inesistente\n");
		return(-1);
		}
/*
	Copio nella struttura Ol il nome dell' host per client_mmi
*/
	else
		{
		database->oldatabasePunti.client_mmi_on=1;
		database->oldatabasePunti.hostname=
		(char*)XtMalloc(strlen(hostname)+1);
		printf("Valore puntatore %lx\n",database->oldatabasePunti.hostname);
		printf("Valore puntatore database %lx\n",database);
		strcpy(database->oldatabasePunti.hostname,token1);
		}
	if(strlen(token2))
		{
		database->oldatabasePunti.codice_host=atoi(token2);
		}
	}/* fine parte Simulator on */
/*
	Inizio analisi campo Scada on del Context
*/

printf("database_type hostnameS=%s strlen(hostnameS)=%d\n",hostnameS,strlen(hostnameS));
if((hostnameS!=NULL)&&(strlen(hostnameS)!=0))
	{
	s=hostnameS;
	sscanf(hostnameS,"%s",token3);
	s=hostnameS + strlen(token3);
	if(*s)
		{	
		sscanf(s,"%s",token4);
		}
	if(getindbyname(token3)==-1) /* controllo che hostnameS sia noto */
		{
		printf("database_type:OlDatabasePunti:hostnameS inesistente\n");
		return(-1);
		}
/*
	Copio nella struttura Ol il nome dell' host per client_scada
*/
	else
		{
		database->oldatabasePunti.client_scada_on=1;
		database->oldatabasePunti.hostnameS=
		(char*)XtMalloc(strlen(hostnameS)+1);
		strcpy(database->oldatabasePunti.hostnameS,token3);
		if(strlen(token4))
			{
			database->oldatabasePunti.codice_hostS=atoi(token4);
			}
/*
Segue un controllo sul codice hostS per compatibilita' con i parametri 
che devono essre passati al client_scada di Marcello.
*/
		if(database->oldatabasePunti.codice_hostS<1) 
			database->oldatabasePunti.codice_hostS=1;
		}
	}/* fine parte Scada on */
printf("database_type:token1=%s token2=%s token3=%s token4=%s\n",token1,token2,token3,token4);
/*
	Decido il tipo di database in funzione dei riusultati ottenuti
*/
	if((database->oldatabasePunti.client_mmi_on) && 
	   (!database->oldatabasePunti.client_scada_on))
		return(DB_XLSIMUL_CLIENT);
	if((!database->oldatabasePunti.client_mmi_on) && 
           (database->oldatabasePunti.client_scada_on))
		return(DB_XLSCADA_CLIENT);
	if((database->oldatabasePunti.client_mmi_on) &&
           (database->oldatabasePunti.client_scada_on))
                return(DB_XLCLIENTS);
	
return(ret);

}
/**********************************************************************

	Funzione che restituisce il tipo di database

***********************************************************************/
int OlDatabasePuntiType(OlDatabasePuntiObject database)
{
if(database==NULL)
	return(-1);
else
	return(database->oldatabasePunti.tipo_db);
}

/**************************************************************************
	Creazione oggetto database a cui vengono passati:
		nome database
		striga con hostname+(eventuale) codice [*hostname]
		shared_user_keys per simulatore e scada
                ris per risultato errore
		
	Restituisce NULL se database non allocato
****************************************************************************/
OlDatabasePuntiObject OlCreateDatabasePunti(char *nome_database, 
				char *hostname, char *hostnameS,
			        int shr_key, int shr_keyS,
				OlTreeObject root_oltree,
                                int port_daemon,
                                int *ris )
{
OlDatabasePuntiObject database=NULL;
char localhost[256],app_host[256];
char *app_char;
int id_shm_allarmi, shmvid_allarmi;
int sem_key;                            /* key di identificaz. del semaforo */
int nres=((Cardinal) (sizeof(resources) / sizeof(resources[0]))); /* numero di 
								risorse */
int k;

*ris=1;




/*
Controlla che le shr_usr_key siano differenti
*/
if(shr_key==shr_keyS)
	{
	XlWarning("OlDatabasePunti","OlCreateDatabase",
                "SHR_USR_KEY e SHR_USR_KEYS sono identiche !!!\n");
	XlWarning("OlDatabasePunti","OlCreateDatabase",
                "Impossibile allocare il database\n");
        return(NULL);
	}

database=(OlDatabasePuntiRec*) XtMalloc (sizeof (OlDatabasePuntiRec));
if(database==NULL)
	{
	XlWarning("OlDatabasePunti","OlCreateDatabase",
		"Impossibile allocare il database\n");
	return(NULL);
	}


	/*
		allocazione e riempimento risorse 
	*/
for(k=0;k<nres;k++)
  {
  if(!strcmp(resources[k].resource_name,"nome"))
    {
    if(nome_database==NULL)
	{
        database->oldatabasePunti.nome_database=(char*)
		XtMalloc (strlen(resources[k].default_addr)+1);
	strcpy(database->oldatabasePunti.nome_database,
		resources[k].default_addr);
	}
    else
	{
        database->oldatabasePunti.nome_database=(char*)
		XtMalloc (strlen(nome_database)+1);
	strcpy(database->oldatabasePunti.nome_database,
		nome_database);
	}

/*
Inizializzo porta su cui client_mmi comunica con demone_mmi
*/
        database->oldatabasePunti.port_daemon=port_daemon;

/*
Richiama la funzione "database_type" 
che in base al contenuto di hostname determina quali client lanciare.
*/
	if((database->oldatabasePunti.tipo_db=database_type(database,hostname,hostnameS))==-1)
		{
		XlWarning("OlDatabasePunti","OlCreateDatabase",
                        "Opzioni del campo hostname non corrette !!!");
		XtFree((char *)database);
		return(NULL);
		}

	    }
	  if(!strcmp(resources[k].resource_name,"shrKey"))
		 database->oldatabasePunti.shr_key=shr_key;
          if(!strcmp(resources[k].resource_name,"shrKeyS"))
                 database->oldatabasePunti.shr_keyS=shr_keyS;
	} /* fine ciclo for */

	/*
		inizializzazione del database
	*/

	if(!(olDatabasePuntiClassRec.oldatabasePunti_class.initialize)(database))
		{
		XlWarning("OlDatabasePunti","OlCreateDatabase",
			"database non allocato");
		XtFree((char *)database);
		return(NULL);
		}
/*
		Invocazione funzione per attivazione dei client
*/

		if(!attiva_client(database,root_oltree,ris))
			{
			XlWarning("OlDatabasePunti","OlCreateDatabase",
				"attiva_client fallita:database non allocato");
			XtFree((char *)database);
			return(NULL);
			}
	/*
		allocazione dell'area contenete i dati degli allarmi
	*/
	if((getenv("SHR_USR_KEYS"))==NULL)
        	{
		printf("OlCreateDatabasePunti: SHR_USR_KEYS non definita !!!\n");
		return(NULL);
		}
	id_shm_allarmi=atoi(getenv("SHR_USR_KEYS"))+OFFSET_SHM_ALLARMI;
	database->oldatabasePunti.allarm_data=
		(char*)crea_shrmem(id_shm_allarmi,sizeof(DATI_ALLARMI_SHM),
                                           &shmvid_allarmi);
	database->oldatabasePunti.allarm_data_id=shmvid_allarmi;
	database->oldatabasePunti.allarm_flag=0;
	if(database->oldatabasePunti.allarm_data==NULL)
	   {
	   XlWarning("OlDatabasePunti","OlCreateDatabase",
		   "allocazione area shared allarmi");
	   XtFree((char *)database);
	   return(NULL);
	   }
       /*
       Crea semaforo per sincronizzazione miniASD
       */
       sem_key=atoi(getenv("SHR_USR_KEYS"))+OFFSET_SEM_SCADA;
       database->oldatabasePunti.sem_scada = sem_open(sem_key);
       sem_key=atoi(getenv("SHR_USR_KEYS"))+OFFSET_SEM_MMI;
       database->oldatabasePunti.sem_mmi = sem_open(sem_key);

       OlInizia_shmMiniASD(database);  

return(database);
}

/*
	Metodo di inizializzazione del database.
*/
static Boolean init_db(OlDatabasePuntiObject database)
{

	if(((database->oldatabasePunti.tipo_db)==(DB_XLSIMUL)) ){
		printf("initdb:sto per lanciare init_db_simul\n");
		return(init_db_simul(database));
	  }
	XlWarning("OlDatabasePunti","init_db","database inesistente");
	return (False);
}


/*
	Inizializzazione database tipo olsimul
*/
static Boolean init_db_simul(OlDatabasePuntiObject database)
{
RtErroreOggetto errore;
SIMULATOR *simpar;

	/*
		creazione oggetto errore
	*/
	errore = RtCreateErrore(RT_ERRORE_TERMINALE,NULL);

	/* aggancio o creazione shared memory  */
	
        simpar = (SIMULATOR*)calloc(1,sizeof(SIMULATOR));
#if defined SCO_UNIX
   	database->oldatabasePunti.dbpunti = 
		RtCreateDbPunti(errore,"S02_SCO",DB_PUNTI_SHARED,simpar);
#endif
#if defined OSF1 || LINUX
   	database->oldatabasePunti.dbpunti = 
		RtCreateDbPunti(NULL,NULL,DB_PUNTI_SHARED,simpar);
#endif
#if defined AIX
   	database->oldatabasePunti.dbpunti = 
		RtCreateDbPunti(errore,"S02_AIX",DB_PUNTI_SHARED,simpar);
#endif
#if defined VMS
   	database->oldatabasePunti.dbpunti = 
		RtCreateDbPunti(errore,"S02_VMS",DB_PUNTI_SHARED,simpar);
#endif
        free(simpar);
	if(database->oldatabasePunti.dbpunti==NULL)
		return(False);
	else
		return(True);
}



/*
	estrae dal database  il valore in funzione 
	dell'indirizzo
*/
static float ValVar(OlDatabasePuntiObject database, PUNT_VARINP varinp)
{
float ret=0;
int ind=varinp.pdb.indice;
int ind_rel=varinp.pdb.indice_rel;
int ind_relS=varinp.pdb.indice_relS;

if(database==NULL)
	{
	XlWarning("OlDatabasePunti","ValVar","database non allocato");
	return(ret);
	}
/*
	campo non compilato: ritorna 0
*/
if((database->oldatabasePunti.tipo_db==DB_XLSIMUL)) 
	{
	if(ind <0)
		return(ret);
	}
else			/* caso client (mmi) o (scada)  on */
	{
	if(varinp.pdb.origin==SIMULAID)
		{
		if(ind_rel <0)
			return(ret);
		if(!database->oldatabasePunti.client_mmi_on)
			return(ret);
		}
	else if(varinp.pdb.origin==SCADAID)
		{
		if(ind_relS <0)
                        return(ret);
		if(!database->oldatabasePunti.client_scada_on)
                        return(ret);
		}
	}
	

/*
	Se solo simulatore locale
*/
if(database->oldatabasePunti.tipo_db==DB_XLSIMUL)
	ret = RtDbPGetValueD(database->oldatabasePunti.dbpunti,ind);
else	
/*
	Se client on controlla quale variabile prendere
*/
	{
	if((varinp.pdb.origin==SCADAID) && (database->oldatabasePunti.varS))
		{
		ret= database->oldatabasePunti.varS[ind_relS*2];
		}
	else if((varinp.pdb.origin==SIMULAID) && (database->oldatabasePunti.var))
		ret= database->oldatabasePunti.var[ind_rel];
	}
return(ret);
}
/*
Funzione che restituisce l' indice della pagina nello
elenco delle pagine data la gerarchia.
*/
int OlJumpPage(OlDatabasePuntiObject database,char *hierar,char tipo_all)
{
OlTreeObject start_page; /* pagina di partenza  */
float *pagina_fittizia;  /* puntatore alla shared_memory della pag sit allarmi */

int shmvidS,progress,pos_info_page,num_page;
/*
Per prima cosa mi aggancio alla shared_memory della pagina fittizia
*/
pagina_fittizia=(float *)crea_shrmem(
  database->oldatabasePunti.pagine_db[PAGINA_CAI].id_shmS,
 (database->oldatabasePunti.pagine_db[PAGINA_CAI].num_puntiS*2+1)*sizeof(float),
 &shmvidS);
if(pagina_fittizia==NULL)
	{
	 XlWarning("OlDatabasePunti","OlJumpPage",
                                "Impossibile accedere shm PAGINA_CAI");
	return(-1);
	}
/*
Vado a trovare la pagina da cui iniziare ricerca situazione allarmi
Devo infatti trovare, a partire dal nodo con gerarchia hierar
l' unico nodo (se esiste) dove si e' verificato l' allarme,
oppure il nodo corrispondente al livello decisionale (nodo con piu' di un
figlio con allarmi).
*/
if(!OlTreeGetPage(database->oldatabasePunti.root_oltree,&start_page,
             &progress,&pos_info_page,hierar))
	{
         XlWarning("OlDatabasePunti","OlJumpPage",
                   "Impossibile accedere al nodo cercato");
        return(-1);
        }


/*
Chiamo metodo di OlTree che, dalla gerarchia mi restituisce indice pagina
*/

printf("OlJumpPage:POS_INFO_PAGE=%d\n",pos_info_page);
OlTreeJumpPage(start_page,pagina_fittizia,&num_page,tipo_all);
if(sgancia_shrmem((char*)pagina_fittizia)==-1)
	{
	 XlWarning("OlDatabasePunti","OlJumpPage",
                   "Impossibile accedere shm PAGINA_CAI");
	return(-1);
	}
return(num_page);
}

/*
Funzione per acquisire valori variabili con situazione allarmi.
Utilizzata nel refresh dei Cai
*/
static Boolean GetHierAll(OlDatabasePuntiObject database,ALL_HIERARCHY *varall)
{
OlTreeObject page_found;
int pos_info_page,progress,shmvidS,statusCai;

progress=-1;
if((database==NULL) || (!(database->oldatabasePunti.client_scada_on)))
        {
        XlWarning("OlDatabasePunti","GetHierAll","database non allocato");
        return(False);
        }

/*
Aggancio alla shared memory della pagina Cai
*/
if(database->oldatabasePunti.pagine_db[PAGINA_CAI].id_shmS<0)
        {
	printf("GetHierAll:id_shmS <0 !!!\n");
	return(False);
	}
database->oldatabasePunti.varCai=(float *)crea_shrmem(
                database->oldatabasePunti.pagine_db[PAGINA_CAI].id_shmS,
		(database->oldatabasePunti.pagine_db[PAGINA_CAI].num_puntiS*2+1)*sizeof(float),
		&shmvidS);
if(database->oldatabasePunti.varCai==NULL)
	{
	printf("GetHierAll:errore nell' aggancio di SHMS\n");
	return(False);
        }

/* 
Controllo stato della pagina Cai
*/
if(database->oldatabasePunti.varCai)
                statusCai=database->oldatabasePunti.varCai
                   [database->oldatabasePunti.pagine_db[PAGINA_CAI].num_puntiS*2];
/* Acquisito stato lo controllo e acquisisco situaz. allarmi */
if(statusCai==1)
	{
	/* ricavo indice progress*/
	OlTreeGetPage(database->oldatabasePunti.root_oltree,&page_found,
			&progress,&pos_info_page,varall->str_input);

	if(progress<0) /* controllo che pagina con allarmi esista */
		{   
		/*
		Il nodo con la data gerarchia non ha allarmi.
		Il Cai rimane spento.(In alternativa messaggio di Warning).
		*/

        	/*XlWarning("OlDatabasePunti","GetHierAll","hierarchy allarm not set");*/
        	if(sgancia_shrmem((char *)database->oldatabasePunti.varCai)<0)
                	{
                	printf("GetHierAll:sgancia_shrmem di varCai ko\n");
                	return(False);
                	}
        		database->oldatabasePunti.varCai=NULL;
			varall->input_valore=0;  /* Cai spento */
		return(True);
		} /* end if progress */

	/* acquisisco valore */
	varall->input_valore=database->oldatabasePunti.varCai[progress*2];

/*
printf("GetHierAll:gerar=%s\n",varall->str_input);
printf("GetHierAll:progress=%d\n",progress);
printf("GetHierAll:valore=%f\n\n",varall->input_valore);
*/
	}

/*
Mi sgancio dalla pagina Cai
*/
if((database->oldatabasePunti.pagine_db[PAGINA_CAI].id_shmS!=-1))
        {
        if(sgancia_shrmem((char *)database->oldatabasePunti.varCai)<0)
                {
                printf("GetHierAll:sgancia_shrmem di varCai ko\n");
                return(False);
                }
        database->oldatabasePunti.varCai=NULL;
        }

return(True);

}
/*
Metodo per acquisire tempo simulazione
*/
float OlGetTime(OlDatabasePuntiObject database)
{
return(GetTime(database));
}
/*
        estrae dal database DB_XLSIMUL il tempo
*/
static float GetTime(OlDatabasePuntiObject database)
{
float ret=0;
int old_shared_set;

if(database==NULL)
        {
        XlWarning("OlDatabasePunti","ProgToVar","database non allocato");
        return(ret);
        }
if(database->oldatabasePunti.tipo_db==DB_XLSIMUL)
	{
	RtDbPGetTime(database->oldatabasePunti.dbpunti,&ret);
	}
else
	{
	old_shared_set = database->oldatabasePunti.shared_set;
	if(database->oldatabasePunti.shared_set != -1)
		{
		if(!OlUnsetDataPage(database,old_shared_set))
			{
                	ret=0;
			}
		}
	if(!OlSetDataPage(database,0))
		{
        	return(ret);
		}
	if(OlGetDataStatus(database,0))
		{
		if(database->oldatabasePunti.client_mmi_on)
			ret=database->oldatabasePunti.var[0];
		else
			ret=database->oldatabasePunti.varS[0];
		}
	if(!OlUnsetDataPage(database,0))
		{
		ret=0;
		}
	if(old_shared_set != -1)
		if(!OlSetDataPage(database,old_shared_set))
			{
                	return(ret);
			}
	}

return(ret);
}
Boolean elimina_client(OlDatabasePuntiObject database)
{
if(database->oldatabasePunti.pid_client>0)
        {
        printf("OlDestroy: Sto per eliminare client_mmi-pid=%d\n",database->oldatabasePunti.pid_client);
        kill(database->oldatabasePunti.pid_client,SIGALRM);
        }
if(database->oldatabasePunti.pid_clientS>0)
        {
        printf("OlDestroy: Sto per eliminare client_scd-pid=%d\n",database->oldatabasePunti.pid_clientS);
        kill(database->oldatabasePunti.pid_clientS,SIGKILL);
        }

/*
        elimina le code di comunicazione
*/
if(database->oldatabasePunti.id_msg_client!=0)
        msg_close(database->oldatabasePunti.id_msg_client);
if(database->oldatabasePunti.id_msg_clientS!=0)
        msg_close(database->oldatabasePunti.id_msg_clientS);


}

Boolean OlDestroyDatabasePunti(OlDatabasePuntiObject database)
{
struct shmid_ds buf;
int flag_del_time=0;
if(database==NULL)
	{
	XlWarning("OlDatabasePunti","OlDestroyDatabasePunti","database inesistente");
	kill(0,SIGKILL); /* elimino processi stesso idgroup */
	return(False);
	}

if(database->oldatabasePunti.nome_database)
	XtFree((char *)database->oldatabasePunti.nome_database);
/*
	elimina la pagina contenente il tempoaggiornato da client_mmi,
	(priorita' piu' alta) o eventualmente da client_scada
*/
/* if(database->oldatabasePunti.tipo_db==DB_XLSIMUL_CLIENT) */
if(database->oldatabasePunti.client_mmi_on)
	{
	/*
		verifica lo stato del processo client
	*/
	if(stato_processo(database->oldatabasePunti.pid_client)<=0)
	     {
	     XlWarning("OlDatabasePunti","OlDestroyDatabasePunti",
			"stato processo client_mmi: OFF");
             database->oldatabasePunti.pid_client= -1;
	     database->oldatabasePunti.client_mmi_on=0;
	     }
	database->oldatabasePunti.pagine_db[0].stato = -1;
	database->oldatabasePunti.pagine_db[0].drawing = NULL;
	if(database->oldatabasePunti.pid_client >0)
           {
	   if(!CsPrepMsgDel(database->oldatabasePunti.id_msg_client,
        	database->oldatabasePunti.pagine_db[0].id_shm)==1)
			XlWarning("OlDatabasePunti","OlDestroyDatabasePunti",
				"errore cancellazione pagina tempo");
	   /* si sospende  al max per 10 sec per dare i tempo al processo
	      client di distruggere la pagina    */
	   flag_del_time=0;
	   while(shresist( database->oldatabasePunti.pagine_db[0].id_shm )&& (flag_del_time)<TIME_DEL_PAG)
		{
		sleep(1);
		flag_del_time++;
		}
	    if(flag_del_time==TIME_DEL_PAG)/* devo eliminare pag STATO da solo*/
		{
		 XlWarning("OlDatabasePunti","OlDestroyDatabasePunti",
                                "errore cancellaz.pag Stato da client_mmi");
		 XlWarning ("OlDatabasePunti","OlDestroyDatabasePunti",
                                "Eliminare shrmem pagina Stato da linea di comando");
		}
	   }/* end if pid_client */
	} /* end if client_mmi on */
if(database->oldatabasePunti.client_scada_on)
	{
	/*
                verifica lo stato del processo client
        */
        if(stato_processo(database->oldatabasePunti.pid_clientS)<=0)
             {
             XlWarning("OlDatabasePunti","OlDestroyDatabasePunti",
                        "stato processo client_scada: OFF");
             database->oldatabasePunti.pid_clientS= -1;
	     database->oldatabasePunti.client_scada_on=0;
             }
        database->oldatabasePunti.pagine_db[0].stato = -1;
        database->oldatabasePunti.pagine_db[0].drawing = NULL;
        if(database->oldatabasePunti.pid_clientS >0)
           {
           if(!CsPrepMsgDel(database->oldatabasePunti.id_msg_clientS,
                database->oldatabasePunti.pagine_db[0].id_shmS)==1)
                        XlWarning("OlDatabasePunti","OlDestroyDatabasePunti",
                                "errore cancellazione pagina tempo");
           /* si sospende al max per 10 sec. per dare i tempo al processo
              client di disptruggere la pagina    */
	   
	   flag_del_time=0;
	   while(shresist( database->oldatabasePunti.pagine_db[0].id_shmS )&& (flag_del_time)<TIME_DEL_PAG)
		{
		sleep(1);
		flag_del_time++;
		}
	    if(flag_del_time==TIME_DEL_PAG)/* devo eliminare pag STATO da solo*/
		{
		 XlWarning("OlDatabasePunti","OlDestroyDatabasePunti",
                                "Eliminare shrmem pagina StatoS da linea di comando ");
		}
/* 
Distruggo la pagina fittizia con situazione allarmi
*/
           if(!CsPrepMsgDel(database->oldatabasePunti.id_msg_clientS,
                database->oldatabasePunti.pagine_db[PAGINA_CAI].id_shmS)==1)
                        XlWarning("OlDatabasePunti","OlDestroyDatabasePunti",
                                "errore cancellazione pagina situazione allarmi");
           /* si sospende al max per 10 sec. per dare i tempo al processo
              client di distruggere la pagina situazione allarmi   */
	   
	   flag_del_time=0;
	   while(shresist( database->oldatabasePunti.pagine_db[PAGINA_CAI].id_shmS )&& (flag_del_time)<TIME_DEL_PAG)
		{
		sleep(1);
		flag_del_time++;
		}
	    if(flag_del_time==TIME_DEL_PAG)/* devo eliminare pag STATO da solo*/
		{
		 XlWarning("OlDatabasePunti","OlDestroyDatabasePunti",
                     "Eliminare shrmem pagina situazione allarmi da linea di comando ");
		}

           } /* end if pid > 0 */
        /*
        Elimino i semafori
        */
        sem_rm(database->oldatabasePunti.sem_mmi);
        sem_rm(database->oldatabasePunti.sem_scada);
	}
else if(database->oldatabasePunti.tipo_db==DB_XLSIMUL)
	{
	RtDestroyDbPunti(database->oldatabasePunti.dbpunti);
        return(True);
	}
/*
 elimina la memoria shr per allarmi
N.B.
Prima di eliminare la shm_allarmi, mi sgancio per avere un num. di 
attachments <=1. Solo cosi' la distruggi_shrmem puo' eliminare la shm allarmi
*/
if(sgancia_shrmem(database->oldatabasePunti.allarm_data)<0)
	printf("OlDestroyPunti:Impossibile sgancia_shrmem su allarmi\n");
else
	distruggi_shrmem(database->oldatabasePunti.allarm_data_id);
/*
	termina il processo client
*/
elimina_client(database);

if((database->oldatabasePunti.hostnameS) && strlen(database->oldatabasePunti.hostnameS))
	{
	XtFree((char *)database->oldatabasePunti.hostnameS);
	}
if((database->oldatabasePunti.hostname) && strlen(database->oldatabasePunti.hostname))
	{
        XtFree((char *)database->oldatabasePunti.hostname);
	}
XtFree((char *)database->oldatabasePunti.pagine_db);
XtFree((char *)database);

return(True);
}

/*****
 * 02-10-97 modifica introdotta da carlo
 * oggetto modifica: effettuo test su indice db anche prima
 * 	del calcolo dei flag, i quali non devono essere fatti
 * 	se l'indice della variabile non e' valido
 * oggetto modifica: MODIFICA DELICATA -- al posto di effettuare due
 *	memcpy assegno un puntatore sulla PUNT_VARIMP 
 *      per verifiche vedere differenze con versione precedente
 *****/
static Boolean RefreshConfinfo(OlDatabasePuntiObject database, Widget w,
				XlConfInfo *confinfo,int num_confinfo)
{
PUNT_DB pdb;
PUNT_VARINP *varinp;
ALL_HIERARCHY *varall;
int i;

for(i=0;i<num_confinfo;i++)
        switch(confinfo[i].confinfo_type){
          case XlRTipoVarInp:
          case XlRTipoVarReg:
          case XlRTipoVarInp+LOCKED_PAG:
          case XlRTipoVarReg+LOCKED_PAG:
             {
             /*
                carica dall'oggetto la struttura PUNT_VAROUT
             */
             varinp = (PUNT_VARINP *)(confinfo[i].compiled_offset+(char *)w);

             /*
                verifica che la risorsa sia stata compilata
              */
             if(varinp->pdb.indice<0)
		{
	        /*
		   azzera comunque il valore della variabile
	        */
	        varinp->valore = 0;
		}
	     else
	        {
                /*
                   richiama il metodo di estrazione dal database
                 */
                varinp->valore=(olDatabasePuntiClassRec.oldatabasePunti_class.valvar)
                           (database,*varinp)*varinp->unimis.a+
			   varinp->unimis.b;

	        /*
		   trattazione punto digitale
	        */
	        if(OlIsDigital(varinp->pdb.tipo,varinp->pdb.origin))
		   {
		   if(varinp->valore>0.5)
			   varinp->valore=1.;
		   else
			   varinp->valore=0.;
		   }
   
	        /*
		   eventuale trattamento negato della variabile
	        */
	        if(varinp->tipo_elab==INP_NEG)
		   varinp->valore=(float)nega(varinp->valore);
		}
             /*
		Setta i flag
                02-10-97 carlo aggiunto condizione if(varinp.pdb.indice>=0)
                         e controllo su tipo_db congruente con origin
	     */
             if(varinp->pdb.indice>=0 && (varinp->pdb.origin==SCADAID))
             {
/*
printf("RefreshConfinfo trova indice>0 origin=SCADA wname=%s\n",XtName(w));
*/
			if( (database->oldatabasePunti.tipo_db == DB_XLSCADA_CLIENT) ||
			    (database->oldatabasePunti.tipo_db == DB_XLCLIENTS))
			     	if(!SettaFlag(w,database->oldatabasePunti.varS,
					varinp,confinfo,num_confinfo,i))
					XlWarning("OlDatabasePunti","RefreshConfinfo",
					"errore assegnamento flag per SCADA");
             }
	     else   if(varinp->pdb.origin==SIMULAID)
		{
/*
printf("RefreshConfinfo trova indice>0 origin=SIMULA wname=%s\n",XtName(w));
*/
			if( database->oldatabasePunti.tipo_db != DB_XLSCADA_CLIENT)
                                {
				if(!SettaFlag(w,database->oldatabasePunti.var,
                                        varinp,confinfo,num_confinfo,i))
               			         XlWarning("OlDatabasePunti","RefreshConfinfo",
                                	"errore assegnamento flag per SIMULA");
                                }
		}
             /*
               Ricarica nell'oggetto la struttura dopo il refresh
             */
             break;
             }
	  case XlRGerarchia:
		{
		/* Controllo che i CAI siano abilitati */
		if(!database->oldatabasePunti.client_scada_on)
		    break;
		if(database->oldatabasePunti.pagine_db[PAGINA_CAI].stato==-1)
			break;
	        /*
	        Carico risorsa gerarchia
	        */
                varall = (ALL_HIERARCHY *) (confinfo[i].compiled_offset+(char *)w);

	        /* Acquisisco valore della variabile calcolata 
		   solo se gerarchia non nulla */
                if(varall->str_input[0]!='-') /* test se primo campo=-1 */
                        {
// printf("OlDatabasePunti:varall->str_input=|%s| \n",varall->str_input);
                        if(!GetHierAll(database,varall))
                                {
                                XlWarning("OlDatabasePunti","RefreshConfinfo",
                                        "Impossibile acquisire situazione allarmi");
                                }
                        }
/*****************************************************************
N.B.
La parte relativa ai flag della calcolata non viene utilizzata
******************************************************************/
		else
			varall->input_valore=0; /* gerarchia nulla -> cai off */
/*
Ricopio il valore della calcolata con la situazione allarmi per
quella gerarchia nelle confinfo
*/
		break;
		}
          default:
                break;
        }
return(True);
}
/*
Metodo OlAddPage per che richiama AddPage
*/
int OlAddPage(database,nome_pagina,w,num,t_refresh)
OlDatabasePuntiObject database;
char *nome_pagina;
WidgetList w;
int num;
int t_refresh;
{
return(AddPage(database,nome_pagina,w,num,t_refresh));
}
/*
Funzione che inserisce una pagina nel database con parametri settati
*/
static int AddPage(database,nome_pagina,w,num,t_refresh)
OlDatabasePuntiObject database; 
char *nome_pagina;
WidgetList w; 
int num; 
int t_refresh;
{
int ret = 1;
int i,j;
int num_punti=0,num_puntiS=0;
int prog_punti = 0;
int prog_puntiS = 0;
int t_agg;
MSG_NEW_PAGE_MMI_RET msg_ret,msg_retS;
int database_allarmi=0;

if(database==NULL)
	return(-1);

if((database->oldatabasePunti.tipo_db==DB_XLSIMUL))
	return(1);
if(!num)                     /* pagina senza alcun oggetto */
	return(1);
num_punti=0;
num_puntiS=0;   /* inizializzo contatori No punti della pagina */
/*
	verifica lo stato del processo client
*/

if(database->oldatabasePunti.client_mmi_on)
	if(stato_processo(database->oldatabasePunti.pid_client)<=0)
		{
		XlWarning("OlDatabasePunti","AddPage",
				"stato processo client");
		database->oldatabasePunti.pid_client = -1;
		database->oldatabasePunti.client_mmi_on=0;
		return( -1 );
		}
if(database->oldatabasePunti.client_scada_on)
        if(stato_processo(database->oldatabasePunti.pid_clientS)<=0)
                {
                XlWarning("OlDatabasePunti","AddPage",
                                "stato processo client");
                database->oldatabasePunti.pid_clientS = -1;
		database->oldatabasePunti.client_scada_on=0;
                return( -1 );
                }

/*
	calcolo il t_agg
*/
t_agg=t_refresh;

/*
	cerco la prima locazione libera
*/
for(i=0;i<MAX_PAGINE_IN_REFRESH;i++)
	if(database->oldatabasePunti.pagine_db[i].stato == -1)
		break;
if(i==MAX_PAGINE_IN_REFRESH)
	return( -1 );
/*printf("AddPage:Ho trovato la prima locazione libera a ind=%d\n",i);*/

/*
		Inizializzo la iesima pagina
*/

database->oldatabasePunti.pagine_db[i].stato = 1;
database->oldatabasePunti.pagine_db[i].var = NULL;
database->oldatabasePunti.pagine_db[i].varS = NULL;
database->oldatabasePunti.pagine_db[i].drawing = XtParent(w[0]);
ret = i;

/*
	estraggo oggetto per oggetto i puntatori ai
	punti acquisisti e li comunico al client
	Numero di punti SCADA e SIMULATORE
*/
if(!contaPunti(w,num,&num_punti,&num_puntiS))
	{
	XlWarning("OlDatabasePunti","AddPage-contaPunti","Origine variabile non corretta");
	return(-1);
	}

/*
	verifica che non ci sia piu' di una pagina allarmi aperta
*/
printf("DEBUG: Verifico pagAll\n");
for(j=0;j<num;j++)
        {
	if(XlIsAllarmi(w[j]))
           printf("DEBUG: Allarmi con flag=%d\n",database->oldatabasePunti.allarm_flag);
	if(XlIsAllarmi(w[j])&&(database->oldatabasePunti.allarm_flag==1))
		{
		XlWarning("OlDatabasePunti","AddPage",
			"Apertura pagina allarmi");
		return( -1);
		}
        }

database->oldatabasePunti.pagine_db[i].num_punti = num_punti;
database->oldatabasePunti.pagine_db[i].num_puntiS = num_puntiS;

/*
printf("AddPage:punti trovati nella %desima pag:num_punti=%d--num_puntiS=%d\n",
	i,num_punti,num_puntiS);
*/

if((num_punti==0)&&(num_puntiS==0))	/* pagina allarmi  */
   {
   database->oldatabasePunti.pagine_db[i].num_punti = 0; /* modificato */
   database->oldatabasePunti.pagine_db[i].num_puntiS = 1; /* verificare */

/*
Chiedi aggiornamento da client_mmi (priorita' maggiore) o da client_scada
Usato un if (client_mmi_on) else ... perche' cosi' acquisisco il tempo solo da client_mmise entrambi i client sono usati
*/

if(database->oldatabasePunti.client_scada_on)
   CsPrepMsgS(nome_pagina,database->oldatabasePunti.id_msg_clientS,10,
                0,1,0,1);

   }
else
   {
   estraiPunti(w,num,nome_pagina,t_agg,database->oldatabasePunti.id_msg_client,
	      database->oldatabasePunti.id_msg_clientS,&prog_punti,&prog_puntiS,
	      num_punti,num_puntiS,ELENCO_PUNTI_ANALOGICI);
   estraiPunti(w,num,nome_pagina,t_agg,database->oldatabasePunti.id_msg_client,
	      database->oldatabasePunti.id_msg_clientS,&prog_punti,&prog_puntiS,
	      num_punti,num_puntiS,ELENCO_PUNTI_DIGITALI);
   }

/*
	attende l'ack dai processi client_mmi e/o client_scada
		
*/
if((database->oldatabasePunti.client_mmi_on) && 
	(database->oldatabasePunti.pagine_db[i].num_punti))
	if(msg_rcv(database->oldatabasePunti.id_msg_client,&msg_ret,
		sizeof(MSG_NEW_PAGE_MMI_RET)-sizeof(long),
		(long)NEW_PAGE_MMI_RET,!IPC_NOWAIT,20)<0)
		{
		printf("AddPage:Messaggio da client_mmi ko");
		ret= -1;
		}
	else
		{
/*
msg ricevuto: setto la SHM della pagina per comunicazione con client mmi 
*/
		database->oldatabasePunti.pagine_db[ret].id_shm=msg_ret.id_shm;
		}
/*
Aspetto messaggio di ritorno (msg_retS)da client SCADA sulla coda id_msg_clientS
*/
/*
printf("AddPage id=%d cl_scada_on=%d num_puntis=%d\n",i,database->oldatabasePunti.client_scada_on,database->oldatabasePunti.pagine_db[i].num_puntiS);
*/
if((database->oldatabasePunti.client_scada_on) && 
	(database->oldatabasePunti.pagine_db[i].num_puntiS))
	{
     	if(msg_rcv(database->oldatabasePunti.id_msg_clientS,&msg_retS,
             sizeof(MSG_NEW_PAGE_MMI_RET)-sizeof(long),
             (long)NEW_PAGE_MMI_RET,!IPC_NOWAIT,20)<0)
              {
              printf("AddPage:Messaggio da client_scada ko");
              ret= -1;
              }
	
      	else
            {
/*
msg ricevuto: setto la SHM della pagina per comunicazione con client scada 
*/
         database->oldatabasePunti.pagine_db[ret].id_shmS=msg_retS.id_shm;
	/*
		verifico la presenza dell'oggetto allarmi
	*/
	     for(j=0;j<num;j++)
		if(XlIsAllarmi(w[j]))
		  {
		  database->oldatabasePunti.allarm_flag=1;
                  database_allarmi=XlAllarmiGetDb(w[j]);
		  if(richiediAllarmi(database->oldatabasePunti.id_msg_clientS,
				w[j],database_allarmi)<0)
		  	XlWarning("OlDatabasePunti","AddPage",
				"richiesta pagina allarmi");
                  }
#if defined SCADA_MMI
	/*
		verifico la presenza di trend storici
	*/
	    for(j=0;j<num;j++)
		if(XlIsGraficoArch(w[j]))
		  {
		  if(richiediTrend(database->oldatabasePunti.id_msg_client,
				w[j],nome_pagina,msg_ret.id_shm)<0)
		  	XlWarning("OlDatabasePunti","AddPage",
				"richiesta trend storico");
                  }
#endif
	    } /* end msg_retS ricevuto da client_scada */
	} /* end if (database->oldatabasePunti.client_scada_on ... */
/*
printf("AddPage:aggiunta pagina con SHM=%d--SHMS=%d\n",database->oldatabasePunti.pagine_db[ret].id_shm,database->oldatabasePunti.pagine_db[ret].id_shmS);
*/
return(ret);
}

static Boolean estraiPunti(WidgetList w, int num, char *nome, int t_agg, 
	int coda, int codaS,int *prog_punti,int *prog_puntiS,
	int tot_punti,int tot_puntiS,
	int tipo_punti)
{
int i,j;
XlCoreClassRec * wclass; /* puntatore alla widget class del widget */
XlManagerClassRec * wclassM; /* puntatore alla widget class del widget */
XlConfInfo *confinfo;
int num_confinfo;
PUNT_VARINP varinp;
WidgetList widget_figli;
int num_figli;

for(i=0;i<num;i++)
   {
   if(XlIsXlCore(w[i]))
     {
     wclass=(XlCoreClassRec*)XtClass(w[i]);
     confinfo=wclass->xlcore_class.confinfo;
     num_confinfo=wclass->xlcore_class.num_confinfo;
     }
   else
     {
     if(XlIsXlComposite(w[i]))
	{
        XtVaGetValues( w[i], XmNnumChildren, &num_figli,
                        XmNchildren, &widget_figli, NULL );
        estraiPunti(widget_figli,num_figli,nome,t_agg,
			coda,codaS,prog_punti,prog_puntiS,tot_punti,
			tot_puntiS,tipo_punti);
	}
     wclassM=(XlManagerClassRec*)XtClass(w[i]);
     confinfo=wclassM->xlmanager_class.confinfo;
     num_confinfo=wclassM->xlmanager_class.num_confinfo;
     }

     for(j=0;j<num_confinfo;j++)
	   if((confinfo[j].confinfo_type==XlRTipoVarInp)||
	     (confinfo[j].confinfo_type==XlRTipoVarInp+LOCKED_PAG)||
	     (confinfo[j].confinfo_type==XlRTipoVarReg)||
	     (confinfo[j].confinfo_type==XlRTipoVarReg+LOCKED_PAG))
	 {
             memcpy(&varinp,(char*)(confinfo[j].compiled_offset+(char *)w[i]),
                           confinfo[j].compiled_size);
	     if(((tipo_punti==ELENCO_PUNTI_ANALOGICI)&&
			(!OlIsDigital(varinp.pdb.tipo,varinp.pdb.origin)))||
    		((tipo_punti==ELENCO_PUNTI_DIGITALI)&&
			(OlIsDigital(varinp.pdb.tipo,varinp.pdb.origin))))
		{
		if(varinp.pdb.origin==SIMULAID)
			{
/*
Crea messaggio per client_mmi
*/
/*printf("estraiPunti:Msg to client_mmi nome[%s] coda=%d-varinp.pdb.indice=%d-varinp.pdb.tipo=%d\n",nome,coda,varinp.pdb.indice,varinp.pdb.tipo);*/
             		CsPrepMsg(nome,coda,t_agg,varinp.pdb.indice,
				varinp.pdb.tipo,*prog_punti,tot_punti);
			varinp.pdb.indice_rel= *prog_punti;
			varinp.pdb.indice_relS= -1;
               	        memcpy((char*)(confinfo[j].compiled_offset+(char *)w[i]),
                       		 &varinp, confinfo[j].compiled_size);
                		++(*prog_punti);

			}
		else if(varinp.pdb.origin==SCADAID)
			{
/*
Crea messaggio per client_scada
*/
/*printf("estraiPunti:Msg to client_scada nome[%s] codaS=%d-varinp.pdb.indice=%d-varinp.pdb.tipo=%d\n",nome,codaS,varinp.pdb.indice,varinp.pdb.tipo);*/

			CsPrepMsgS(nome,codaS,t_agg,varinp.pdb.indice,
                                varinp.pdb.tipo,*prog_puntiS,tot_puntiS);
			varinp.pdb.indice_relS= *prog_puntiS;
			varinp.pdb.indice_rel= -1;
                	memcpy((char*)(confinfo[j].compiled_offset+(char *)w[i]),
                        	&varinp, confinfo[j].compiled_size);
                	++(*prog_puntiS);
			}
		} /* end controllo ELENCO_PUNTI_ANALOGICI ELENCO_PUNTI_DIGITALI*/
	     } /* end for ... num_confinfo */
   
   } /* for ... num widget */
}
/*
	Funzione che conta quanti punti di tipo scada e di tipo simulatore 
	vi sono nella pagina.Il numero dei punti e' restituito in num_punti
	ed in num_puntiS.num e' il numero di widget presenti nella pagina.
*/
static Boolean contaPunti(WidgetList w, int num,int *num_punti, int *num_puntiS)
{
int i,j;
XlCoreClassRec * wclass; /* puntatore alla widget class del widget */
XlManagerClassRec * wclassM; /* puntatore alla widget class del widget */
XlConfInfo *confinfo;
int num_confinfo;
PUNT_VARINP varinp;
WidgetList widget_figli;
int num_figli;


for(i=0;i<num;i++)
   {
   if(XlIsXlCore(w[i]))
     {
     wclass=(XlCoreClassRec*)XtClass(w[i]);
     confinfo=wclass->xlcore_class.confinfo;
     num_confinfo=wclass->xlcore_class.num_confinfo;
     }
   else
     {
     if(XlIsXlComposite(w[i]))
	{
        XtVaGetValues( w[i], XmNnumChildren, &num_figli,
                        XmNchildren, &widget_figli, NULL );
        contaPunti(widget_figli,num_figli,num_punti,num_puntiS);
	}
     wclassM=(XlManagerClassRec*)XtClass(w[i]);
     confinfo=wclassM->xlmanager_class.confinfo;
     num_confinfo=wclassM->xlmanager_class.num_confinfo;
     }
       for(j=0;j<num_confinfo;j++)
           {
	   if((confinfo[j].confinfo_type==XlRTipoVarInp)||
	     (confinfo[j].confinfo_type==XlRTipoVarInp+LOCKED_PAG)||
	     (confinfo[j].confinfo_type==XlRTipoVarReg+LOCKED_PAG)||
	     (confinfo[j].confinfo_type==XlRTipoVarReg))
                {
/*
Devo controllare se il punto e' di origine scada o simula:
devo copiare la confinfo nella varinp.
*/
		memcpy(&varinp,(char*)(confinfo[j].compiled_offset+(char *)w[i]),
                           confinfo[j].compiled_size);
		if(varinp.pdb.origin==SCADAID)
			{
			++(*num_puntiS);
			}
		else if(varinp.pdb.origin==SIMULAID)
			{
			++(*num_punti);
			}
		else return(False);    /* verificare se corretto */
                }
           } /* end for ... num_confinfo */
   }/* end for num widget */
return(True);
}
/***************************************************************

	Inizio parte gestione situazione allarmi gerarchia

*****************************************************************/
/*
Funzione che permette di creare una pagina fittizia nella quale
vengono inserite le situazioni relative agli allarmi in gerarchia.
*/
static int AddPageHier(database,t_refresh,root)
OlDatabasePuntiObject database;
int t_refresh;
OlTreeObject root;    /* radice gerarchia */
{
int num_nodi=0;         /* # nodi OlTree */
int progress=0;	      /* indice progressivo dei nodi */
/*
Controlli preliminari: in particolare controllo che vi sia lo scada
*/

if(database==NULL)
        return(False);
if(database->oldatabasePunti.client_scada_on)
        if(stato_processo(database->oldatabasePunti.pid_clientS)<=0)
                {
                XlWarning("OlDatabasePunti","AddPageHierar",
                                "stato processo client");
                database->oldatabasePunti.pid_clientS = -1;
                database->oldatabasePunti.client_scada_on=0;
                return( False );
                }
/*
Vado a contare il numero di nodi dell' oggetto OlTree
*/
OlTreeCountNodes(root,&num_nodi);
printf("\nAddPageHier: Num_nodi=%d\n",num_nodi);

/*
Percorro l' OlTree, e per ogni nodo estraggo indice e tipo della
calcolata (PEN$A) relativa a quel nodo.
Spedisco un messaggio come nella funzione estrai_punti e attendo la
risposta, aggiornando il progressivo punti e il valore del campo
di tipo puntatore relativo ad ogni nodo.
*/
if(num_nodi)
	{
	OlEstraiNodi(root,database->oldatabasePunti.id_msg_clientS,
			t_refresh,&progress,num_nodi);
	return(num_nodi);
	}
else
	return(num_nodi); 
}
/*
Creazione metodo per allarmi
*/
Boolean OlGetDataAllarmi(OlDatabasePuntiObject database, 
				DATI_ALLARMI_SHM *dati)
{
return(GetDataAllarmi(database,dati));
}
static Boolean GetDataAllarmi(OlDatabasePuntiObject database, 
				DATI_ALLARMI_SHM *dati)
{
int i,kk;
if(database==NULL)
	return(False);

memcpy(dati, database->oldatabasePunti.allarm_data,
		sizeof(DATI_ALLARMI_SHM));

if(dati->dati_validi == DATI_ALLARMI_VALIDI)
	{
	return(True);
	}
else
	{
	memset(dati,0,sizeof(DATI_ALLARMI_SHM));
	return(False);
	}
}
/*
Costruisco metodo per chaimata esterna
*/
Boolean OlCommandAllarmi(OlDatabasePuntiObject database, int comando)
{
return(CommandAllarmi(database,comando,DBMASTER));
}
static Boolean CommandAllarmi(OlDatabasePuntiObject database, int comando,int db)
{
int kk;
DATI_ALLARMI_SHM *shmp;
if(database==NULL)
	{
	XlWarning("OlDatabasePunti","CommandAllarmi",
			"database dei punti non definito");
	return(False);
	}

switch(comando)
	{
	case OL_MODO_ARCHIVIO:
		{
		CsPrepMsgAllCommand(database->oldatabasePunti.id_msg_clientS,
			ALL_REQ_ARCHIVI,db);
		break;
		}
	case OL_MODO_ALLARMI:
		{
		CsPrepMsgAllCommand(database->oldatabasePunti.id_msg_clientS,
			ALL_REQ_ALLARMI,db);
		break;
		}
	case OL_RICONOSCI_ALLARMI:
		{
		CsPrepMsgAllCommand(database->oldatabasePunti.id_msg_clientS,
			ALL_REQ_RIC,db);
		break;
		}
	case OL_AVANTI_ALLARMI:
		{
		CsPrepMsgAllCommand(database->oldatabasePunti.id_msg_clientS,
			ALL_REQ_AVANTI,db);
		break;
		}
	case OL_INDIETRO_ALLARMI:
		{
                printf("OlCommand: Sto per spedire msg di comando\n");
		CsPrepMsgAllCommand(database->oldatabasePunti.id_msg_clientS,
			ALL_REQ_INDIETRO,db);
		break;
		}
	case OL_CHIUDI_ALLARMI:
		{
		/*database->oldatabasePunti.allarm_flag=0;*/
		CsPrepMsgAllCommand(database->oldatabasePunti.id_msg_clientS,
			ALL_REQ_CHIUDI,db);
		printf("OlDatabasePunti: settata a zero DATI_ALLAR\n");
		shmp=(DATI_ALLARMI_SHM *)database->oldatabasePunti.allarm_data;
/*
Pulisco le stringhe
*/
		for(kk=0;kk<N_ALL_STR;kk++)
			{
			strcpy(shmp->descr[kk],"");		
			strcpy(shmp->data[kk],"");		
			shmp->emission[kk]=3;
			}
		printf("EFFETTUATO zero DATI_ALLAR\n");

		
		break;
		}
	default:
		{
		XlWarning("OlDatabasePunti","CommandAllarmi",
			"comando non definito");
		return(False);
		}
	}

return(True);
}
/*
Metodo OlDelPage per eliminazione pagine
*/
Boolean OlDelPage(OlDatabasePuntiObject database, int key)
{
return(DelPage(database,key));
}
/*
Funzione che determina l' eliminazione della pagina e delle shrm 
ad essa associate
*/
static Boolean DelPage(OlDatabasePuntiObject database, int key)
{
if(database==NULL)
	return(False);

if(database->oldatabasePunti.tipo_db==DB_XLSIMUL) /* nessun client */
	return(True);

/*
	verifica lo stato dei processi client
*/
if(database->oldatabasePunti.client_mmi_on)
	if(stato_processo(database->oldatabasePunti.pid_client)<=0)
		{
		XlWarning("OlDatabasePunti","DelPage",
			"stato processo client_mmi OFF");
		database->oldatabasePunti.pid_client = -1;
		database->oldatabasePunti.client_mmi_on=0;
		return(False);
		}
if(database->oldatabasePunti.client_scada_on)
        if(stato_processo(database->oldatabasePunti.pid_clientS)<=0)
                {
                XlWarning("OlDatabasePunti","DelPage",
                        "stato processo client_scada OFF");
                database->oldatabasePunti.pid_clientS = -1;
                database->oldatabasePunti.client_scada_on=0;
                return(False);
                }


database->oldatabasePunti.pagine_db[key].stato = -1;
database->oldatabasePunti.pagine_db[key].drawing = NULL;


printf("Elimino la pagina %d id_shm = %d id_shmS = %d\n",key,
		database->oldatabasePunti.pagine_db[key].id_shm,
		database->oldatabasePunti.pagine_db[key].id_shmS);
if(database->oldatabasePunti.pagine_db[key].id_shm!=-1)
	{
	if(CsPrepMsgDel(database->oldatabasePunti.id_msg_client,
		database->oldatabasePunti.pagine_db[key].id_shm)!=1)
		{
		return(False);
		}
	database->oldatabasePunti.pagine_db[key].id_shm=-1;
	}
if(database->oldatabasePunti.pagine_db[key].id_shmS!=-1)
	{
	if(CsPrepMsgDel(database->oldatabasePunti.id_msg_clientS,
		database->oldatabasePunti.pagine_db[key].id_shmS)!=1)
		{
		return(False);
		}
	database->oldatabasePunti.pagine_db[key].id_shmS=-1;
	}
return(True);
}

/****************************************************************************
Funzione che determina in base al tipo di database quali client attivare.
Setta le variabili di ambiente e i parametri per l' invocazione dei clients;
lancia i client e chiede l' aggiornamento della pagina stato.

Parametri:
	database : database dei punti
        root_oltree : nodo root oggetto OlTree
        *ris : risultato connessione fra mmi e schedulatore
Ritorna True se tutto OK, False altrimenti
******************************************************************************/

static Boolean attiva_client(OlDatabasePuntiObject database,OlTreeObject root_oltree,int *ris)
{
register int i;
char *proc_argv[4];
char *proc_argvS[4];   /* argv dell' eventuale processo client_scada */
char *proc_envp[5];
char *proc_envpS[5];

char proc_name[FILENAME_MAX]; /* Stringhe contenenti nomi processi client */
char proc_nameS[FILENAME_MAX];
char *path_client;		/* path dove risiedono eseguibili client */
int ret;
MSG_NEW_PAGE_MMI_RET msg_ret,msg_retS;
int tot_nodi;			/* totale nodi OlTree */
int codice_host=0;
char *app_char;
time_t time_start,time_fine;
time(&time_start);
/*
Inizializzo puntatore a primo elemento OlTree
*/
if(root_oltree!=NULL);
	database->oldatabasePunti.root_oltree=(OlTreeObject)root_oltree;

/*
	Per prima cosa verifico se e' un simulatore locale
*/
if((database->oldatabasePunti.tipo_db==DB_XLSIMUL))
	return(True);

printf("attiva_client:attivazione client %s\n",database->oldatabasePunti.hostname);

/*
	attivazione processo PROCESSO_CLIENT
*/
/* allocazione spazio per var nomi processi e variabili di ambiente */

for (i=0;i<4;i++)
	{
	proc_argv[i]=(char*)malloc(FILENAME_MAX);
	proc_argvS[i]=(char*)malloc(FILENAME_MAX);
	}
for(i=0;i<6;i++)
	{
	proc_envp[i]=(char*)malloc(FILENAME_MAX);
	proc_envpS[i]=(char*)malloc(FILENAME_MAX);
	}
/*
	Verifica quali client attivare	in base al tipo di simulatore
*/


printf("attiva_client:database->oldatabasePunti.client_mmi_on=%d--database->oldatabasePunti.client_scada_on=%d\n",database->oldatabasePunti.client_mmi_on,database->oldatabasePunti.client_scada_on);

/* 
controllo sui client 
*/
if((!database->oldatabasePunti.client_mmi_on) && (!database->oldatabasePunti.client_scada_on))
	return(False);

/*
Setto i valori delle variabili di ambiente
*/
if(database->oldatabasePunti.client_mmi_on)
	{
	sprintf(proc_envp[0],"SHR_USR_KEY=%s\00",getenv("SHR_USR_KEY"));
	sprintf(proc_envp[1],"LEGORT_BIN=%s\00",getenv("LEGORT_BIN"));
	sprintf(proc_envp[2],"LEGOMMI_BIN=%s\00",getenv("LEGOMMI_BIN"));
	sprintf(proc_envp[3],"FORMATO_DATI=%s\00",getenv("FORMATO_DATI"));
        free(proc_envp[4]);
	proc_envp[4]=NULL;
	}
if(database->oldatabasePunti.client_scada_on)
	{
	sprintf(proc_envpS[0],"SHR_USR_KEYS=%s\00",getenv("SHR_USR_KEYS"));
	sprintf(proc_envpS[1],"LEGORT_BIN=%s\00",getenv("LEGORT_BIN"));
	sprintf(proc_envpS[2],"LEGOMMI_BIN=%s\00",getenv("LEGOMMI_BIN"));
	sprintf(proc_envpS[3],"FORMATO_DATI=%s\00",getenv("FORMATO_DATI"));
	sprintf(proc_envpS[4],"LD_LIBRARY_PATH=%s\00",getenv("LD_LIBRARY_PATH"));
        if(proc_envp[5])
           free(proc_envp[5]);
	proc_envp[5]=NULL;
	}

/*
Determino dove risiedono gli eseguibili per lanciare client 
*/
path_client=getenv("LEGOMMI_BIN");
sprintf(proc_name,"%s/%s\00",path_client,PROCESSO_CLIENT);
sprintf(proc_nameS,"%s/%s\00",path_client,PROCESSO_CLIENTS);

/***
N.B.
Parte di lancio client_mmi viene spostata prima della parte di lancio
client_scada, per verificare in anticipo aggancio di mmi allo stesso
database (variabili.rtf) dello skedulatore
***/

/*
Setto i parametri per lanciare il client_mmi
*/
if(database->oldatabasePunti.client_mmi_on)
	{
	sprintf(proc_argv[0],"%s\00",PROCESSO_CLIENT);
	if(database->oldatabasePunti.codice_host<1)	
		{
		printf("attiva_client:client_mmi senza parametri\n");
		printf("attiva_client:hostname=%s\n",
			database->oldatabasePunti.hostname);
		sprintf(proc_argv[1],"%s\00",database->oldatabasePunti.hostname);
		}
	else
		{
		 printf("attiva_client:client_mmi con parametro=%d\n",
			database->oldatabasePunti.codice_host);
		sprintf(proc_argv[1],"%d\00",
			database->oldatabasePunti.codice_host);

		}

/*
Passo a client_mmi la porta demone_mmi
*/               
                sprintf(proc_argv[2],"%d\00",
                        database->oldatabasePunti.port_daemon);
                free(proc_argv[3]);
                proc_argv[3]=NULL;


/*
Verifico che la coda dei messaggi non esista gia'.Se esiste significa che:
	uno stesso utente cerca di lanciare una seconda versione di mmi sulla
	stessa macchina.
	la coda di msg non e' stata eliminata da un mmi terminato non 
	correttamente
*/
printf("coda msgS=%d\n",(atoi(getenv("SHR_USR_KEY")))+FROM_MMI_MSG);
        if(msgesist((atoi(getenv("SHR_USR_KEY")))+FROM_MMI_MSG))
                {
                XlWarning("OlDatabasePunti","attiva_client",
                                "coda per messaggi client_mmi esiste gia'");
                XlWarning("OlDatabasePunti","attiva_client",
                                "Probabile causa:mmi lanciato da stesso utente su stessa macchina");
		return(False);

                }
	database->oldatabasePunti.id_msg_client=msg_create((atoi(getenv("SHR_USR_KEY")))+FROM_MMI_MSG,1);
/*
Lancio processo client_mmi
*/
	database->oldatabasePunti.pid_client = vfork();
	if ( database->oldatabasePunti.pid_client == 0 )
      		{
		printf("attiva_client:proc_name=%s\n",proc_name);
      		execve(proc_name,proc_argv,proc_envp);
      		perror("execve PROCESSO_CLIENT");
      		exit(0);
      		}
        if((*ris=verify_sim(database->oldatabasePunti.id_msg_client,
            database->oldatabasePunti.nome_database))<=0)
                {
                /*
                Chiudi le code
                */
                if(database->oldatabasePunti.id_msg_client!=0)
                   msg_close(database->oldatabasePunti.id_msg_client);
                if(database->oldatabasePunti.id_msg_clientS!=0)
                   msg_close(database->oldatabasePunti.id_msg_clientS);
                return(False);
                }
	}         /* end if client_mmi on */

/*
	Istruzioni per lanciare client scada 
*/
if(database->oldatabasePunti.client_scada_on)
	{
	sprintf(proc_argvS[0],"%s\00",PROCESSO_CLIENTS);
	if((database->oldatabasePunti.hostnameS==NULL)||
	   (!strlen(database->oldatabasePunti.hostnameS)))
		{
		printf("attiva_client:Errore nell' hostname di client_scada\n");
		return(False);
		}
	else
		sprintf(proc_argvS[1],"%s\00",database->oldatabasePunti.hostnameS);
/*
Verifica se vi sono + mmi agganciati ad un solo scada 
*/
	if(database->oldatabasePunti.codice_hostS>0)
		{
		sprintf(proc_argvS[2],"%d\00",
			database->oldatabasePunti.codice_hostS);
                free(proc_argvS[3]);
		proc_argvS[3]=NULL;
		}
	else
		{
		printf("attiva_client:codice host per scada non corretto\n");
		return(False);
		}

/*
Verifico che la coda dei messaggi non esista gia'.Se esiste significa che:
	uno stesso utente cerca di lanciare una seconda versione di mmi sulla
	stessa macchina.
	la coda di msg non e' stata eliminata da un mmi terminato non 
	correttamente
*/
printf("coda msgS=%d\n",(atoi(getenv("SHR_USR_KEYS")))+FROM_MMI_MSGS);
        if(msgesist((atoi(getenv("SHR_USR_KEYS")))+FROM_MMI_MSGS))
                {
                XlWarning("OlDatabasePunti","attiva_client",
                                "coda per messaggi client_scada esiste gia'");
                XlWarning("OlDatabasePunti","attiva_client",
                                "Probabile causa:mmi lanciato da stesso utente su stessa macchina");
		return(False);

                }
        database->oldatabasePunti.id_msg_clientS=msg_create(
                        (atoi(getenv("SHR_USR_KEYS")))+FROM_MMI_MSGS,1);

/*
	Lancio il client_scada
*/
	database->oldatabasePunti.pid_clientS = vfork();
	if ( database->oldatabasePunti.pid_clientS == 0 )
      		{
	printf("attiva_client:proc_nameS=%s\n",proc_nameS);
      		execve(proc_nameS,proc_argvS,proc_envpS);
      		perror("execve PROCESSO_CLIENTSCADA");
      		exit(0);
      		}
	
	}/*if database->oldatabasePunti.client_scada_on */

/*
	allocazione dello spazio per le pagine
*/
database->oldatabasePunti.pagine_db=(PAGINE_IN_REFRESH*)
	XtMalloc(sizeof(PAGINE_IN_REFRESH)*(MAX_PAGINE_IN_REFRESH+1));
for(i=0;i<MAX_PAGINE_IN_REFRESH+1;i++)
	{
	database->oldatabasePunti.pagine_db[i].id_shm= -1;
	database->oldatabasePunti.pagine_db[i].id_shmS= -1;
	database->oldatabasePunti.pagine_db[i].stato= -1;
	database->oldatabasePunti.pagine_db[i].drawing= NULL;
	}

/*****************************************************************************
	Parte critica: aggiornamento del tempo (dai 2 client)	
*****************************************************************************/
if(database->oldatabasePunti.client_mmi_on)
	{
/*
Verifico stato del processo 
*/
	if(stato_processo(database->oldatabasePunti.pid_client)<=0)
		{
		XlWarning("OlDatabasePunti","attiva_client",
				"attivazione processo client");
		database->oldatabasePunti.pid_client = -1;
		database->oldatabasePunti.client_mmi_on=0;
		return(False);
		}
/*
Richiedo aggiornamento della pagina stato
*/
/*printf("attiva_client:Sto per spedire msg per aggiornamento pag stato\n");*/
	CsPrepMsg("Stato",database->oldatabasePunti.id_msg_client,10,REQ_TIME,
                        ANALOGICO,0,1);
/*
        attende l'ack dal processo client
*/
	if((ret=msg_rcv(database->oldatabasePunti.id_msg_client,&msg_ret,
                sizeof(MSG_NEW_PAGE_MMI_RET)-sizeof(long),
                (long)NEW_PAGE_MMI_RET,!IPC_NOWAIT,20))<0)
        	{
        printf("ATTIVA CLIENT: Errore ricevimento msg ACK su richiesta pagTEMPO per client_mmi\n");
		kill(database->oldatabasePunti.pid_client,SIGTERM);
		kill(database->oldatabasePunti.pid_clientS,SIGTERM);
        	return(False);
        	}
	else
        	{
        	database->oldatabasePunti.pagine_db[0].stato = 1;
        	database->oldatabasePunti.pagine_db[0].drawing = NULL;
        	database->oldatabasePunti.pagine_db[0].id_shm=msg_ret.id_shm;
        	database->oldatabasePunti.pagine_db[0].num_punti=1;
        	database->oldatabasePunti.pagine_db[0].var=NULL;
        	}
printf("MMI: Ritorno richiesta client[TIME] ret = %d id_shm = %d punti = %d\n",ret,
                /*database->oldatabasePunti.pagine_db[ret].id_shm,1);*/
                database->oldatabasePunti.pagine_db[0].id_shm,1);
	
	} /* end if database->oldatabasePunti.client_mmi_on */
if(database->oldatabasePunti.client_scada_on)
	{
/* 
Verifico lo stato del processo client
*/
	if(stato_processo(database->oldatabasePunti.pid_clientS)<=0)
		{
		XlWarning("OlDatabasePunti","attiva_client",
			"attivazione processo client scada");
		database->oldatabasePunti.pid_clientS = -1;
		database->oldatabasePunti.client_scada_on=0;
		return(False);
		}
/*
Richiedo aggiornamento della pagina stato da parte del client
*/
	CsPrepMsgS("StatoS",database->oldatabasePunti.id_msg_clientS,10,REQ_TIME,
                        ANALOGICO,0,1);
/*
 attende l'ack dal processo client_scada
*/
	if((ret=msg_rcv(database->oldatabasePunti.id_msg_clientS,&msg_retS,
                sizeof(MSG_NEW_PAGE_MMI_RET)-sizeof(long),
                (long)NEW_PAGE_MMI_RET,!IPC_NOWAIT,20))<0)
        	{
        	printf("ATTIVA CLIENT: Errore ricevimento msg ACK su richiesta pag.TEMPO per client_scada\n");
		kill(database->oldatabasePunti.pid_client,SIGTERM);
                kill(database->oldatabasePunti.pid_clientS,SIGTERM);
        	return(False);
        	}
else
        {
        database->oldatabasePunti.pagine_db[0].stato = 1;
        database->oldatabasePunti.pagine_db[0].drawing = NULL;
        database->oldatabasePunti.pagine_db[0].id_shmS=msg_retS.id_shm;
        printf("attiva_client:valore di id_shmS=%d\n",msg_retS.id_shm);
        database->oldatabasePunti.pagine_db[0].num_puntiS=1;
        database->oldatabasePunti.pagine_db[0].varS=NULL;
        }
printf("MMI: Ritorno richiesta client_scada[TIME] ret = %d id_shm = %d punti = %d\n",ret,
                /*database->oldatabasePunti.pagine_db[ret].id_shm,1);*/
                database->oldatabasePunti.pagine_db[0].id_shmS,1);
/*
Inserisco parte per creazione pagina fittizia
*/
tot_nodi=AddPageHier(database,T_REFRESH_CAI,root_oltree);
/* 
Se non esistono calcolate per quei nodi, va avnti ugualmente ma
non abilita i CAI 
*/
if(!tot_nodi)
	{
	XlWarning("OlDatabasePunti","attiva_client",
                        "Num nodes for alarms situation =0 ; CAI NOT ENABLED");
	database->oldatabasePunti.pagine_db[PAGINA_CAI].stato = -1;
	return(True);
	}
	
printf("\n\tattiva_client:OlDataP NUM_NODI=%d\n",tot_nodi);

if((tot_nodi<0) || ((ret=msg_rcv(database->oldatabasePunti.id_msg_clientS,&msg_retS,
                sizeof(MSG_NEW_PAGE_MMI_RET)-sizeof(long),
                (long)NEW_PAGE_MMI_RET,!IPC_NOWAIT,20))<0) )
                {
                printf("ATTIVA CLIENT: Errore ricevimento msg ACK su richiesta pag.ALLARMI_CAI per client_scada\n");
                kill(database->oldatabasePunti.pid_client,SIGTERM);
                kill(database->oldatabasePunti.pid_clientS,SIGTERM);
                return(False);
                }
else
        {
        database->oldatabasePunti.pagine_db[PAGINA_CAI].stato = 1;
        database->oldatabasePunti.pagine_db[PAGINA_CAI].drawing = NULL;
        database->oldatabasePunti.pagine_db[PAGINA_CAI].id_shmS=msg_retS.id_shm;
        database->oldatabasePunti.pagine_db[PAGINA_CAI].id_shm=-1;
        printf("attiva_client:valore di id_shmS per pag_cai=%d\n",msg_retS.id_shm);
        database->oldatabasePunti.pagine_db[PAGINA_CAI].num_puntiS=tot_nodi;
        database->oldatabasePunti.pagine_db[PAGINA_CAI].varS=NULL;
        }

	
	}/* end if client_scada on */

for (i=0;i<4;i++)
	{
        if(proc_argv[i])
	   free(proc_argv[i]);
        if(proc_argvS[i])
	   free(proc_argvS[i]);
	}
for(i=0;i<5;i++)
	{
        if(proc_envp[i])
	    free(proc_envp[i]);
        if(proc_envpS[i])
	    free(proc_envpS[i]);
	}
time(&time_fine);
printf("atiiva_client:time_start=%ld time_fine=%ld \n",time_start,time_fine);
printf("atiiva_client:TEMPO_TOT=%ld \n",(time_fine-time_start));
return(True);
}

/*
Funzione che crea ( o aggancia ) una shr_memory alla variabile var
*/
Boolean OlSetDataPage(database,indice)
OlDatabasePuntiObject database; 
int indice;
{
int shmvid,shmvidS;
if(database==NULL)
	return(False);

if(database->oldatabasePunti.tipo_db==DB_XLSIMUL)
	return(True);

/*printf("OlSetDataPage indice = %d  id_sh=%d id_shS=%d num_punti=%d num_puntiS=%d\n",indice,
	database->oldatabasePunti.pagine_db[indice].id_shm,
	database->oldatabasePunti.pagine_db[indice].id_shmS,
	database->oldatabasePunti.pagine_db[indice].num_punti,
	database->oldatabasePunti.pagine_db[indice].num_puntiS);
*/

/*
	registro l'indice di pagina settato
*/

database->oldatabasePunti.shared_set = indice;
if(database->oldatabasePunti.pagine_db[indice].id_shm!=-1)
	{
	database->oldatabasePunti.var=(float *)crea_shrmem(
		database->oldatabasePunti.pagine_db[indice].id_shm,
	(database->oldatabasePunti.pagine_db[indice].num_punti+1)*sizeof(float),
		&shmvid);
	if((database->oldatabasePunti.var==NULL)) 
		{
		printf("OlSetDataPage:errore nell' aggancio di SHM\n");
                return(False);
		}
	}
if(database->oldatabasePunti.pagine_db[indice].id_shmS!=-1)
	{
	database->oldatabasePunti.varS=(float *)crea_shrmem(
		database->oldatabasePunti.pagine_db[indice].id_shmS,
       (database->oldatabasePunti.pagine_db[indice].num_puntiS*2+1)*sizeof(float),
	&shmvidS);

	if((database->oldatabasePunti.varS==NULL))
		{
		printf("OlSetDataPage:errore nell' aggancio di SHMS\n");
		return(False);
		}
	}
return(True);	

}
/*
	Funzione che sgancia le shm associate ad una pagina (in posizione indice)
	e resetta gli indici di shms della pagina
*/
Boolean OlUnsetDataPage(database,indice)
OlDatabasePuntiObject database; 
int indice;
{
if(database->oldatabasePunti.tipo_db==DB_XLSIMUL)
	return(True);

/*printf("OlUnSetDataPage indice = %d  id_sh=%d id_shS=%d\n",indice,
	database->oldatabasePunti.pagine_db[indice].id_shm,
	database->oldatabasePunti.pagine_db[indice].id_shmS);*/

database->oldatabasePunti.shared_set = -1;
/*
	Sgancia le shm che sono state create
*/
if(indice!=-1)
  if((database->oldatabasePunti.pagine_db[indice].id_shmS!=-1))
	{
/*printf("OlUn:ind=%d id_shmS=%d\n",indice,database->oldatabasePunti.pagine_db[indice].id_shmS);*/
	if(sgancia_shrmem((char*)database->oldatabasePunti.varS)<0)
		{
		printf("OlUnsetDataPage:sgancia_shrmem di varS ko\n");
		return(False);
		}
	database->oldatabasePunti.varS=NULL;
	}
if(indice!=-1)
  if((database->oldatabasePunti.pagine_db[indice].id_shm!=-1))
	{
/*printf("OlUn:ind=%d id_shm=%d\n",indice,database->oldatabasePunti.pagine_db[indice].id_shm);*/
	if(sgancia_shrmem((char*)database->oldatabasePunti.var)<0)
                {
                printf("OlUnsetDataPage:sgancia_shrmem di varS ko\n");
                return(False);
                }
	database->oldatabasePunti.var=NULL;
	}

return(True);
}

Boolean OlGetDataStatus(database,indice)
OlDatabasePuntiObject database;
int indice;
{
int status,statusS;

status=0;
statusS=0;

if(database->oldatabasePunti.tipo_db==DB_XLSIMUL)
	return(True);
/*
Ricavo lo stato (ultimo punto) della pagina 
*/
if(database->oldatabasePunti.pagine_db[indice].id_shmS!=-1)
	{
	if(database->oldatabasePunti.varS)
		statusS=database->oldatabasePunti.varS
		   [database->oldatabasePunti.pagine_db[indice].num_puntiS*2];
	else return(False);
	}
if(database->oldatabasePunti.pagine_db[indice].id_shm!=-1)
	{
	if(database->oldatabasePunti.var)
		status=database->oldatabasePunti.var
		   [database->oldatabasePunti.pagine_db[indice].num_punti];
	else return(False);    /* modifica */
	}
/*
Se da una delle due shrm lo stato e' attivo ritorna Vero
*/
if((status == 1)||(statusS == 1))
	{
	return(True);
	}
else
	return(False);
}

/*
Funzione che cambia la posizione di un punto nella topologia 
*/
Boolean OlChangePointInPage(Widget w, PUNT_VARINP *varinp, char *tag,
		OlDatabaseTopologiaObject database_topologia,
		OlDatabasePuntiObject database)
{
int ind = -1,tipo,i;


if(varinp->pdb.origin==SIMULAID)
      {
      (olDatabaseTopologiaClassRec.oldatabaseTopologia_class.tagtoind)
		(database_topologia,tag,&ind,&tipo);

/*
	setto il nuovo indirizzo e tipo in varinp
*/
     varinp->pdb.indice=ind;
     varinp->pdb.tipo=tipo;

printf("OlChangePointInPage new ind = %d\n",varinp->pdb.indice);

/*
	nella versione client - server deve comunicare la variazione di
	indirizzo
*/
     if(database->oldatabasePunti.tipo_db!=DB_XLSIMUL)
	{
	/*
		verifica lo stato del processo client
	*/
	if(stato_processo(database->oldatabasePunti.pid_client)<=0)
		{
		XlWarning("OlDatabasePunti","OlChangePointInPage",
				"stato processo client");
		database->oldatabasePunti.pid_client = -1;
		database->oldatabasePunti.client_mmi_on=0;
		return(False);
		}
	   for(i=0;i<MAX_PAGINE_IN_REFRESH;i++)
           	if(database->oldatabasePunti.pagine_db[i].drawing == XtParent(w))
                	break;
		if(i==MAX_PAGINE_IN_REFRESH)
        		return( False);
		CsChangePoint(database->oldatabasePunti.id_msg_client,
		database->oldatabasePunti.pagine_db[i].id_shm,
		varinp->pdb.indice_rel,varinp->pdb.tipo,ind);
		}
	} /* end if(varinp->pdb.origin==SIMULAID) */
else if(varinp->pdb.origin==SCADAID)
	{
	 (olDatabaseTopologiaClassRec.oldatabaseTopologia_class.tagtoinds)
                (database_topologia,tag,&ind,&tipo);

/*
        setto il nuovo indirizzo e tipo in varinp
*/
     varinp->pdb.indice=ind;
     varinp->pdb.tipo=tipo;

printf("OlChangePointInPage new ind = %d\n",varinp->pdb.indice);

/*
        nella versione client - server deve comunicare la variazione di
        indirizzo
*/
        /*
                verifica lo stato del processo client
        */
        if(stato_processo(database->oldatabasePunti.pid_clientS)<=0)
                {
                XlWarning("OlDatabasePunti","OlChangePointInPage",
                                "stato processo client");
                database->oldatabasePunti.pid_clientS = -1;
                database->oldatabasePunti.client_scada_on=0;
                return(False);
                }
           for(i=0;i<MAX_PAGINE_IN_REFRESH;i++)
                if(database->oldatabasePunti.pagine_db[i].drawing == XtParent(w))
                        break;
                if(i==MAX_PAGINE_IN_REFRESH)
                        return( False);
                CsChangePoint(database->oldatabasePunti.id_msg_clientS,
                database->oldatabasePunti.pagine_db[i].id_shmS,
                varinp->pdb.indice_rel,varinp->pdb.tipo,ind);
	} /* end if(varinp->pdb.origin==SCADAID) */
}

/*
Funzione che non e' utilizzata da nessuno 
*/
int OlAddSinglePoint(OlDatabasePuntiObject database,
		OlDatabaseTopologiaObject database_topologia,
		char *tag)
{
int ret = -1;
int ind = -1,tipo,i;

if(database->oldatabasePunti.tipo_db!=DB_XLSIMUL)
	return(ret);

(olDatabaseTopologiaClassRec.oldatabaseTopologia_class.tagtoind)
	(database_topologia,tag,&ind,&tipo);

}


Boolean SettaFlag(Widget w,float *var,PUNT_VARINP *varinp,
		XlConfInfo * confinfo,int num_confinfo,int st)
{
float soglie[NUMERO_SOGLIE];
int i,j;
char *punt;
float valore;
FLAG_DIGITALE flag_digitale;
FLAG_ANALOGICO flag_analogico;

if((confinfo[st].confinfo_group==XlRGrVCC1)||
  (confinfo[st].confinfo_group==XlRGrVCC2)||
  (confinfo[st].confinfo_group==XlRGrVCC3)||
  (confinfo[st].confinfo_group==XlRGrVCC4))
  {
  /* Annulla il campo flag */
  memset(&(varinp->flag),0,sizeof(FLAG_MMI));
  if(varinp->pdb.indice < 0)
    {
    /* punto fuori scansione */
    if(OlIsDigital(varinp->pdb.tipo,varinp->pdb.origin))
    	varinp->flag.flag_digitale.fs = 1;
    else
	varinp->flag.flag_analogico.fs = 1;
    }
  else
   {
   if(varinp->pdb.origin==SCADAID) /* var di tipo SCADA */
       {
       memcpy(&(varinp->flag),&var[varinp->pdb.indice_relS*2+1],
		sizeof(FLAG_MMI));
/****************************************************************
if(OlIsDigital(varinp->pdb.tipo,varinp->pdb.origin))
	{
memcpy(&flag_digitale,&(varinp->flag),sizeof(FLAG_MMI));
printf("flag_digitale mmi %d %d %d %d %d %d %d %d\n",
	flag_digitale.sl,flag_digitale.ri,flag_digitale.au,flag_digitale.in,
	flag_digitale.st,flag_digitale.fz,flag_digitale.fa,flag_digitale.fs);	
	}
else
	{
memcpy(&flag_analogico,&(varinp->flag),sizeof(FLAG_MMI));
printf("flag_analogico mmi %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
	flag_analogico.lc,flag_analogico.hc,flag_analogico.ls,flag_analogico.hs,
	flag_analogico.dl,flag_analogico.dh,flag_analogico.ri,flag_analogico.s3,
	flag_analogico.au,flag_analogico.s2,flag_analogico.al,flag_analogico.s1,
	flag_analogico.st,flag_analogico.fz,flag_analogico.fa,flag_analogico.fs);	
	}
**************************************************************/
        } /* end if(varinp->pdb.origin==SCADAID) */
    else if(varinp->pdb.origin==SIMULAID) /* var di tipo SIMULA */
        {
        valore = varinp->valore;
        if(OlIsDigital(varinp->pdb.tipo,varinp->pdb.origin))
	   /* punto digitale */
	   {
	   if(valore == 1.0)
		   varinp->flag.flag_digitale.sl = 1;
	   }
        else
	/* punto analogico */
	   {
    	/* cerca i valori delle soglie */
    	   for(i=st+1,j=0; i<num_confinfo; i++)
      	       if((confinfo[i].confinfo_type == XlRFloat) ||
		   (confinfo[i].confinfo_type == XlRFloat+LOCKED_PAG))
/*&&
		(confinfo[i].confinfo_group == confinfo[st].confinfo_group))
*/
	           {
		   punt = (char*)w;
		   punt += confinfo[i].compiled_offset;
		   memcpy(&soglie[j++],punt,confinfo[i].compiled_size);
		   if(j == NUMERO_SOGLIE) break;
		   }
           /* fa' questo solo se le soglie nell'oggetto esistono
           */
           if( j == NUMERO_SOGLIE)
           {
	/* fuori limite alto di sicurezza */
	   if(valore>=soglie[3]) 
    	      varinp->flag.flag_analogico.hs = 1;
        /* fuori limite alto di conduzione */
           if((valore>=soglie[2])&&(valore<soglie[3]))
	      varinp->flag.flag_analogico.hc = 1;
        /* fuori limite basso di conduzione */
           if((valore>=soglie[0])&&(valore<soglie[1]))
	      varinp->flag.flag_analogico.lc = 1;
	/* fuori limite basso di sicurezza */
	   if(valore<soglie[0]) 
    	      varinp->flag.flag_analogico.ls = 1;
           }
	   }
        } /* end else if(varinp->pdb.origin==SIMULAID) */
    }  /* fine assegnamento flag */
  return(True);
  }
  else
  {
  return(True);
  }
}
/*
Funzione che restituisce True se la variabile in esame e' di tipo digitale
*/
Boolean OlIsDigital(int tipo,int origin)
{
if(origin==SCADAID)
	{
	if((tipo==P_AA)||(tipo==P_AS)||(tipo==P_AC)||(tipo==P_AD)||(tipo==P_AO))
		{
		return(False);
		}
	else
		{
		return(True); 
		}
	}
if(origin==SIMULAID)
	{
	if(tipo==DIGITALE)
		return(True);
	else
		return(False);
	}
}

#if defined SCADA_MMI
static int richiediTrend(int coda, Widget w,char* nome_pagina,int id_shm)
{
int codice_trend=0;
char *nome_trend[MAX_LUN_NOME_FILE_TREND];
Arg args[5];
char *nome_file;
char *s1, *s2, *s3, *s4;
char sigla_1[MAX_LUN_NOME_VAR];
char sigla_2[MAX_LUN_NOME_VAR];
char sigla_3[MAX_LUN_NOME_VAR];
char sigla_4[MAX_LUN_NOME_VAR];
char *app;
char app_var[300];
int num_mis;

 
 get_something(w,XlNarchiveFile, (void*) &nome_file);
 codice_trend=atoi(nome_file);
 printf("richiediTrend  %s  %d\n",nome_file,codice_trend);
 if(codice_trend<=0)
	return(-1);
 get_something(w,XlNvarName1, (void*) &s1);
 strcpy(app_var,s1);
 app=strstr(app_var," ");
 if(app!=NULL) *app=NULL;
 strcpy(sigla_1,app_var);
 
 get_something(w,XlNvarName2, (void*) &s2);
 strcpy(app_var,s2);
 app=strstr(app_var," ");
 if(app!=NULL) *app=NULL;
 strcpy(sigla_2,app_var);
 
 get_something(w,XlNvarName3, (void*) &s3);
 strcpy(app_var,s3);
 app=strstr(app_var," ");
 if(app!=NULL) *app=NULL;
 strcpy(sigla_3,app_var);
 
 get_something(w,XlNvarName4, (void*) &s4);
 strcpy(app_var,s4);
 app=strstr(app_var," ");
 if(app!=NULL) *app=NULL;
 strcpy(sigla_4,app_var);

 num_mis =4;
 if(strlen(sigla_4)==0)
	num_mis=3;
 if(strlen(sigla_3)==0)
	num_mis=2;
 if(strlen(sigla_2)==0)
	num_mis=1;
 if(strlen(sigla_1)==0)
	num_mis=0;
	
  if(num_mis==0)
	{
	printf(" Attenzione   Num_mis = 0\n");
	return(1);
	}
 

 sprintf(nome_trend,"Archivio_%d_%s_%s_%d.dat",
		codice_trend,nome_pagina,XtName(w),id_shm);
 set_something_val(w,XlNarchiveFile,(XtArgVal)nome_trend);
 printf("Richiedo i dati del trend widget %s pagina %s id = %d <%s>\n",
		XtName(w),nome_pagina,id_shm,nome_trend);
 printf("s1 = <%s> - s2 = <%s> - s3 = <%s> - s4 = <%s> \n",
		sigla_1,sigla_2,sigla_3,sigla_4);
 if(CsPrepMsgTrendReq(coda,id_shm,nome_pagina,codice_trend,nome_trend,
		num_mis,sigla_1,sigla_2,sigla_3,sigla_4)>0)
 	return(1);
 else
	{
	printf("Attenzione ritorno -1 da CsPrepMsgTrendReq\n");
	return(-1);
	}
}
#endif

/*
Funzione che testa lo stato dei processi client
*/
Boolean OlCheckDatabasePuntiStatus(OlDatabasePuntiObject database) 
{

if(database->oldatabasePunti.tipo_db!=DB_XLSIMUL)
	{
	/*
		verifica gli stati dei processi client
	*/
    if(database->oldatabasePunti.client_mmi_on)
	if(stato_processo(database->oldatabasePunti.pid_client)<=0)
	     {
	     XlWarning("OlDatabasePunti","OlCheckDatabasePunti",
			"stato processo client_mmi OFF");
             database->oldatabasePunti.pid_client= -1;
	     database->oldatabasePunti.client_mmi_on=0;
	     return(False);
	     }
    if(database->oldatabasePunti.client_scada_on)
	if(stato_processo(database->oldatabasePunti.pid_clientS)<=0)
             {
             XlWarning("OlDatabasePunti","OlCheckDatabasePunti",
                        "stato processo client scada OFF");
             database->oldatabasePunti.pid_client= -1;
             database->oldatabasePunti.client_scada_on=0;
             return(False);
             }

	}
else
	return(True);

}
/*
Metodo per richiesta allarmi per paginaAll Teleperm
Invocato all' atto dell' apertura della pagina Allarmi
*/
Boolean OlTeleperm_richiediAllarmi(OlDatabasePuntiObject database,
					int *zone_status)
{
return(teleperm_richiediAllarmi(database,zone_status));
}
/*
Funzione che invia messaggio per pagina Allarmi di tipo teleperm
Viene passatto parametro database per coda msgS e array di int
contenente le zone attivate.
Ritorna True se il messaggio e' stato inviato correttamente
*/
static Boolean teleperm_richiediAllarmi(OlDatabasePuntiObject database,
					int *zone_status)
{
/*
Spedisco messaggio di richiesta allarmi per teleperm che 
ha la pagina allarmi apribile solo sul db 1 cioe'
quello principale 
*/
if(CsPrepMsgAllReq(database->oldatabasePunti.id_msg_clientS,zone_status,DBMASTER))
	{
	return(True);
	}
else
	return(False);

}

/*
Funzione che permette di inoltrare la richiesta allarmi
in base al database richiesto.
Utilizzabile solo da pagAll tipo SDI e non teleperm.
Parameter:
	int coda:     coda
	Widget w:     widget pagAllarmi
        int db  :     db allarmi richiesto
Return :
          true if msg correctly sent
          else false.
*/
static Boolean  richiediAllarmi(int coda,Widget w,int db)
{
XlAllarmiWidget cw= (XlAllarmiWidget)w;

 if(CsPrepMsgAllReq(coda,cw->allarmi.zone,db)>0)
	{
 	return(True);
	}
 else
	{
	printf("Attenzione ritorno -1 da CsPrepMsgAllReq\n");
	return(False);
	}
}

Boolean OlCanOpenAllarmPage(OlDatabasePuntiObject database) 
{

if(database->oldatabasePunti.allarm_flag==0)
	return(True);
else
	return(False);
}


/*
Funzione che setta flag pagAllarmi gia' aperta per evitare interferenze
fra pagine allarmi di tipo Teleperm e quelle di vecchio tipo
Parameters:
	OlDatabasePuntiObject database; database Punti
        int flagVal;                    valore da assegnare a flag
                                        (0 esco pagAll 1 entro)
*/
Boolean OlSetOpeningAllarmPage(OlDatabasePuntiObject database, int flagVal)
{

if(((database->oldatabasePunti.allarm_flag==0) && (flagVal==0)) ||
    ((database->oldatabasePunti.allarm_flag==1) && (flagVal==1)))
        return(False);
else
       {
       printf("DEBUG: Setto il flag a= %d \n",flagVal);
       database->oldatabasePunti.allarm_flag= flagVal;
       return(True);
       }
}



/*
Funzione che verifica se il simulatore e l' mmi
sono agganciati allo stesso variabili.rtf
Parametri:
	int id_coda : coda fra mmi e client_mmi
        char *nome_database : path dove risiede db a cui e' agganciato mmi
Return:
       0  -> connessione fallita
       -1 -> db mmi e db skedulatore diversi
       1  -> db mmi = db skedulatore
	
*/
static int verify_sim(int id_coda, char *nome_database)
{
int ris;
char path_sim_rcv[FILENAME_MAX];

/*
Attesa del messaggio da parte di client_mmi con path_sim comunicato da demone
*/

if(CsRcvMsgSimID(id_coda,path_sim_rcv)<0)
   {  
   printf("ERROR:OlDbPunti:verify_sim: Error waiting OK from SIMID from MMI\n");
   return 0; 
   }  


if (strcmp(nome_database,path_sim_rcv))
   {
   /*
   popup ERROR dialog
   */
   strcpy(path_sim_correct,path_sim_rcv);
   ris=-1;
   }
else
   ris=1;

if(!CsPrepMsgSimIDAck(id_coda,ris))
   {
   printf("ERROR::verify_sim: Impossible to send a msg to mmi \n");
   return 0;
   }
 
return ris;
}

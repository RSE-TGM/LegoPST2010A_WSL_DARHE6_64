/*********************************************************************
*
*       C Source:               OlDatabasePunti.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Mon Mar  2 14:53:44 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: OlDatabaseP_func.c-8 %  (%full_filespec: OlDatabaseP_func.c-8:csrc:1 %)";
#endif


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <Xl/XlResources.h>
#include <Xl/XlCoreP.h>
#include <Xl/XlManagerP.h>
#include <Xl/XlAllarmiP.h>

#include <Ol/OlDatabasePuntiP.h>
#include <Ol/OlTree.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/shm.h>
# include <sys/stat.h>
# include <sys/param.h>
static Boolean richiediAllarmiMiniASD(OlDatabasePuntiObject,unsigned char *,int,short,short);
static Boolean riconosciAllarmiMiniASD(OlDatabasePuntiObject,unsigned char *,int,short,short,int,int);
static Boolean riconosciManualiMiniASD(OlDatabasePuntiObject,unsigned char *,int,short,short,int,int);
static Boolean GetDatiMiniASD(OlDatabasePuntiObject ,
        DATI_ALLARMI_SHM *, DATI_ALLARMI_SHM *,int );
/*
Funzione che inizializza strutture shm associate alla OW
Passo database Punti.
Nessun ritorno
*/
int OlInizia_shmMiniASD(OlDatabasePuntiObject database)
{
int i;

for(i=0;i<MAX_NUM_OW;i++)
   {
   database->oldatabasePunti.shmMiniASD[i].allarm_data=NULL;
   database->oldatabasePunti.shmMiniASD[i].manual_data=NULL;
   database->oldatabasePunti.shmMiniASD[i].indice=-1;
   }
printf("OlInizia_shmMiniASD:Ho inizializzato shmMiniASD\n");
}
/*
Funzione per assegnare ad una OW le sua shared memory
Restituisce i puntatori di puntatori alle shm se create
Restituisce l' indice all' interno di shmMiniASD dello
oggetto database


Return: Restituisce -1 se fallisce
*/
int OlInserisci_shmMiniASD(OlDatabasePuntiObject database,char **allarm_data, char **manual_data,int *indice)
{
int i=0;
int id_all_shmMiniASD;
int id_man_shmMiniASD;
int shmvid_allarm,shmvid_manual;

/*
Trova prima posizione libera indice =-1 e shm memory gia' distrutta 
da client_scada
*/
while(((database->oldatabasePunti.shmMiniASD[i].indice!=-1) && (i<MAX_NUM_OW))
       || ((shresist(database->oldatabasePunti.shmMiniASD[i].id_manual_data))||
          (shresist(database->oldatabasePunti.shmMiniASD[i].id_allarm_data)) )
      )
   i++;
if(i==MAX_NUM_OW)
   {
   fprintf(stderr,"WARNING: Impossible to open a new shm for a OW indice=%d\n",i);
   return(-1);
   }

/*
Assegno id shm alle due shm
La prima shm sara' OFFSET_SHM_MINIASD
La seconda sara' OFFSET_SHM_MINIASD+1
*/
printf("init_shmminiASD indice=%d\n",i);
id_all_shmMiniASD=atoi(getenv("SHR_USR_KEYS"))+OFFSET_SHM_MINIASD+(i*2);
id_man_shmMiniASD=atoi(getenv("SHR_USR_KEYS"))+OFFSET_SHM_MINIASD+(i*2)+1;

/*
Alloco shm relativa agli allarmi miniASD
*/
database->oldatabasePunti.shmMiniASD[i].allarm_data=
         (char*)crea_shrmem(id_all_shmMiniASD,sizeof(DATI_ALLARMI_SHM),
         &shmvid_allarm);
if(database->oldatabasePunti.shmMiniASD[i].allarm_data==NULL)
    {

    XlWarning("OlDatabasePunti","OlInserisciMiniASD",
                   "allocazione area shared allarmi KO");
    return(-1);
    }
   
   
/*
Alloco shm relativa agli allarmi manual
*/
database->oldatabasePunti.shmMiniASD[i].manual_data=
         (char*)crea_shrmem(id_man_shmMiniASD,sizeof(DATI_ALLARMI_SHM),
         &shmvid_manual);
if(database->oldatabasePunti.shmMiniASD[i].manual_data==NULL)
    {

    XlWarning("OlDatabasePunti","OlInserisciMiniASD",
                   "allocazione area shared manual KO");
    return(-1);
    }

/*
Assegno i valori degli identificatori delle shm allocate
*/
database->oldatabasePunti.shmMiniASD[i].id_allarm_data=id_all_shmMiniASD;
database->oldatabasePunti.shmMiniASD[i].id_manual_data=id_man_shmMiniASD;
database->oldatabasePunti.shmMiniASD[i].shmvid_allarm=shmvid_allarm;
database->oldatabasePunti.shmMiniASD[i].shmvid_manual=shmvid_manual;

*allarm_data=database->oldatabasePunti.shmMiniASD[i].allarm_data;
*manual_data=database->oldatabasePunti.shmMiniASD[i].manual_data;
/*printf("OlInserisci_shmMiniASD:allarm_data=%ld manual_data=%ld\n",*allarm_data,*manual_data);
*/

if(sgancia_shrmem(database->oldatabasePunti.shmMiniASD[i].allarm_data)<0)
   {
   printf("OlEliminaMiniASD:Impossibile sgancia_shrmem su miniASD\n");
   }
if(sgancia_shrmem(database->oldatabasePunti.shmMiniASD[i].manual_data)<0)
   {
   printf("OlEliminaMiniASD:Impossibile sgancia_shrmem su miniASD\n");
   }

/*
Inserisco indice della O.W. chiamante, nella lista delle O.W. aperte 
*/
database->oldatabasePunti.shmMiniASD[i].indice=i;
*indice=i;

return(1);
}

/*
Funzione che dall' indice ricava la shm associata alla OW
da eliminare.
L' operazione di eliminazione della shm viene effettuata da client_scada,
per evitare di avere la situazione in cui O.W. chiude le shm associate
ma client_scada sta ancora elaborando le richieste di ricon. allarmi 

Parametri: database
	   indice -> indice O.W.

Return:-1 se fallisce.
*/
int OlElimina_shmMiniASD(OlDatabasePuntiObject database,int indice)
{
int id_allarm,id_manual;

if(indice <0 || indice>= MAX_NUM_OW)
   {
   fprintf(stderr,"OlEliminaMiniASD indice non corretto !!! \n");
   return(-1);
   }

id_allarm=database->oldatabasePunti.shmMiniASD[indice].id_allarm_data;
id_manual=database->oldatabasePunti.shmMiniASD[indice].id_manual_data;

/*printf("Sto per spedire msg id_allarm=%d id_manual=%d\n",id_allarm,id_manual);*/

if(CsPrepMsgMiniASDDes(database->oldatabasePunti.id_msg_clientS,id_allarm,
                       id_manual))
        {
        /*
        Inserisco -1 come indice per poter riutilizzare questo elemento dello
        array
        */
        database->oldatabasePunti.shmMiniASD[indice].indice=-1;
        return(1);
        }
else
        return(-1);

}

/*
Metodo per richiesta  Riconoscimento allarmi per miniASD
Invocato all' atto dell' apertura della extension1 della O.W.
Parametri:
	gerarchia: gerarchia O.W. e allarme da ric.
	indiceOW: indice della OW.
	filtro: per riconoscimento  (future operazioni) [NON USATO]
        tipo_allarme: tipo allarme per filtro [NON USATO]
	n_all: No tot allarmi da riconoscere
	indice_all: indice dell' allarme da ric. nell' elenco all in shm

*/
Boolean OlRiconosciAllarmiMiniASD(OlDatabasePuntiObject database,
                                        unsigned char *gerarchia,
                                        int indiceOW,short filtro, 
                                        short tipo_allarme,
                                        int n_all, int indice_all)
{
return(riconosciAllarmiMiniASD(database,gerarchia,indiceOW,
           filtro,tipo_allarme,n_all,indice_all));
}

/*
Funzione che invia messaggio per riconoscimento di tipo teleperm
Ritorna True se il messaggio e' stato inviato correttamente
*/
static Boolean riconosciAllarmiMiniASD(OlDatabasePuntiObject database,
                               unsigned char *gerarchia,
                               int indiceOW,short filtro, 
                               short tipo_allarme,int n_all,int indice_all)
{
int id_data_all;
id_data_all=database->oldatabasePunti.shmMiniASD[indiceOW].id_allarm_data;

if(CsPrepMsgMiniASDRic(database->oldatabasePunti.id_msg_clientS,gerarchia,
                       id_data_all,filtro,tipo_allarme,n_all,indice_all))
        {
        return(True);
        }
else
        return(False);
}

/*
Metodo per richiesta Ric. Manuali per miniASD
Invocato all' atto dell' apertura della extension1 della O.W.
Parametri:
	gerarchia: gerarchia O.W. e allarme da ric.
	indiceOW: indice della OW.
	filtro: per riconoscimento  (future operazioni) [NON USATO]
        tipo_allarme: tipo allarme per filtro [NON USATO]
        n_all: No tot di allarmi da ric.
	indice_all: indice dell' allarme da ric. nell' elenco all in shm

*/
Boolean OlRiconosciManualiMiniASD(OlDatabasePuntiObject database,
                                        unsigned char *gerarchia,
                                        int indiceOW,short filtro, 
                                        short tipo_allarme,
                                        int n_all,int indice_all)
{
return(riconosciManualiMiniASD(database,gerarchia,indiceOW,
           filtro,tipo_allarme,n_all,indice_all));
}

/*
Funzione che invia messaggio per riconoscimento di tipo teleperm
Ritorna True se il messaggio e' stato inviato correttamente
*/
static Boolean riconosciManualiMiniASD(OlDatabasePuntiObject database,
                               unsigned char *gerarchia,
                               int indiceOW,short filtro, 
                               short tipo_allarme,
                               int n_all,int indice_all)
{
int id_data_all;
id_data_all=database->oldatabasePunti.shmMiniASD[indiceOW].id_manual_data;

if(CsPrepMsgMiniASDRic(database->oldatabasePunti.id_msg_clientS,gerarchia,
                       id_data_all,filtro,tipo_allarme,n_all,indice_all))
        {
        return(True);
        }
else
        return(False);
}







/*
Metodo per richiesta allarmi per miniASD
Invocato all' atto dell' apertura della extension1 della O.W.
*/
Boolean OlRichiediAllarmiMiniASD(OlDatabasePuntiObject database,
                                        unsigned char *gerarchia,
                                        int indiceOW, 
                                        short filtro,short tipo_allarme)
{
return(richiediAllarmiMiniASD(database,gerarchia,indiceOW,filtro,tipo_allarme));
}


/*
Funzione che invia messaggio per pagina Allarmi di tipo teleperm
Viene passatto parametro database per coda msgS e array di char
contenente la gerarchia della O.W. per richiesta allarmi.
	filtro: per individuare tipo richiesta (considera o meno all di tipo 
                tipo_allarme).
        tipo_allarme: tipo allarme da ricercare o da non considerare 
Ritorna True se il messaggio e' stato inviato correttamente
*/
static Boolean richiediAllarmiMiniASD(OlDatabasePuntiObject database,
                               unsigned char *gerarchia,
                               int indiceOW,short filtro,
                               short tipo_allarme)
{
int id_allarm_data,id_manual_data;
/*
Vado a ricavare l' indice di shm per le 2 shm associate alla OW di indice indiceOW
*/
id_allarm_data=database->oldatabasePunti.shmMiniASD[indiceOW].id_allarm_data;
id_manual_data=database->oldatabasePunti.shmMiniASD[indiceOW].id_manual_data;

if(CsPrepMsgMiniASDReq(database->oldatabasePunti.id_msg_clientS,gerarchia,id_allarm_data,id_manual_data,filtro,tipo_allarme))
        {
        return(True);
        }
else
        return(False);

}


/*
Funzione per acquisizione dati allarmi miniASD
Parametri: database
	   dati_allarm punt variabile di tipo DATI_ALLARMI_SHM
	   dati_manual punt variabile di tipo DATI_ALLARMI_SHM
(In dati_allarm e dati_manual vengono ricopiati i dati letti da shm
ed ivi inseriti da client_scada)

Return: False se accesso shm ko
        True se tutto OK
*/
/*
Creazione metodo per allarmi
*/
Boolean OlGetDatiMiniASD(OlDatabasePuntiObject database,
        DATI_ALLARMI_SHM *dati_allarm, DATI_ALLARMI_SHM *dati_manual,int indice)
{
return(GetDatiMiniASD(database,dati_allarm,dati_manual,indice));
}
static Boolean GetDatiMiniASD(OlDatabasePuntiObject database,
        DATI_ALLARMI_SHM *dati_allarm, DATI_ALLARMI_SHM *dati_manual,int indice)
{
int i,kk;
int shmvid_allarmi,shmvid_manual;
int id_all_shmMiniASD,id_man_shmMiniASD;
if(database==NULL)
        return(False);

id_all_shmMiniASD=atoi(getenv("SHR_USR_KEYS"))+OFFSET_SHM_MINIASD+(indice*2);
id_man_shmMiniASD=atoi(getenv("SHR_USR_KEYS"))+OFFSET_SHM_MINIASD+(indice*2)+1;
/*
Prima di agganciare il database condiviso con il client_scada
devo mettermi in attesa che il semaforo sia libero  semaforo
*/
sem_wait(database->oldatabasePunti.sem_mmi);

/*
Aggancio shm relativa agli allarmi miniASD
*/
database->oldatabasePunti.shmMiniASD[indice].allarm_data=
         (char*)crea_shrmem(id_all_shmMiniASD,sizeof(DATI_ALLARMI_SHM),
         &shmvid_allarmi);


if(database->oldatabasePunti.shmMiniASD[indice].allarm_data==NULL)
    {

    XlWarning("OlDatabasePunti","OlGetDatiMoniASD",
                   "allocazione area shared allarmi KO");
    return(False);
    }
   
/*
Aggancio shm relativa agli allarmi manual
*/
database->oldatabasePunti.shmMiniASD[indice].manual_data=
         (char*)crea_shrmem(id_man_shmMiniASD,sizeof(DATI_ALLARMI_SHM),
         &shmvid_manual);
if(database->oldatabasePunti.shmMiniASD[indice].manual_data==NULL)
    {

    XlWarning("OlDatabasePunti","OlGetDatiMiniASD",
                   "allocazione area shared manual KO");
    return(False);
    }

/*
Copio contenuto delle shm nelle variabli restituite
*/
memcpy(dati_allarm, database->oldatabasePunti.shmMiniASD[indice].allarm_data,
                sizeof(DATI_ALLARMI_SHM));
memcpy(dati_manual, database->oldatabasePunti.shmMiniASD[indice].manual_data,
                sizeof(DATI_ALLARMI_SHM));

if(sgancia_shrmem(database->oldatabasePunti.shmMiniASD[indice].allarm_data)<0)
   {
   printf("OlEliminaMiniASD:Impossibile sgancia_shrmem su miniASD\n");
   }
if(sgancia_shrmem(database->oldatabasePunti.shmMiniASD[indice].manual_data)<0)
   {
   printf("OlEliminaMiniASD:Impossibile sgancia_shrmem su miniASD\n");
   }
if((dati_manual->dati_validi == DATI_ALLARMI_VALIDI) && 
             (dati_allarm->dati_validi == DATI_ALLARMI_VALIDI))
        {
        sem_signal(database->oldatabasePunti.sem_scada);
        return(True);
        }
else
        {
        memset(dati_allarm,0,sizeof(DATI_ALLARMI_SHM));
        memset(dati_manual,0,sizeof(DATI_ALLARMI_SHM));
        sem_signal(database->oldatabasePunti.sem_scada);
        return(False);
        }
}


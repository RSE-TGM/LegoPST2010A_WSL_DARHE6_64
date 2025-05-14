/**********************************************************************
*
*       C Source:               net_prova.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Tue Oct 22 12:24:39 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: net_prova.c-5 %  (%full_filespec: net_prova.c-5:csrc:1 %)";
#endif
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include "sim_param.h"
# include "sim_types.h"
# include "sim_ipc.h"
# include "comandi.h"
# include "sked.h"
# include "dispatcher.h"
# include <Rt/RtDbPunti.h>
# include <Rt/RtMemory.h>

#define NUMPAR 40

int shr_usr_key;
int   stato_sked;	/* definisce lo stato dello sked */
int   tipo_sked;	/* definisce il tipo di sked SLAVE=0 MASTER=1  */
char            nodo_master[MAX_LUN_HOST];	/* nome del nodo MASTER   */
char            nodo_dispatcher[MAX_LUN_HOST];	/* nome del nodo DISPATCHER   */
int             fp_from_dispatcher;
int             fp_to_dispatcher;
int             fp_perturba;
int             nodo_dispatcher_attivo;


extern int      fp_ordini[MAX_MODEL];	/* puntatori dei socket a cui spedire
					 * i comandi, solo per sked master */

extern S02      s02_;		/* struttura modelli e var  */
extern int      nrip;		/* numero di ripetizioni della tabella di
				 * ripetizione */
extern int      nmod;		/* numero delle task */

RtDbPuntiOggetto dbpunti;
RtDbPuntiOggetto dbpunti_ext;
RtErroreOggetto errore;

/*
 * tutti i tempi sono indicati in millisecondi       
 */
double          tempo_task;	/* tempo impiegato dalle task per un ciclo */
double          tempo_rete;	/* tempo impiegato dalla rete per un ciclo */
double          tempo_sim = 0;	/* tempo della simulazione   */
double          tempo_reale = 0;/* tempo reale   */
double          tempo_iniziale = 0;	/* tempo iniziale della simulazione   */
double          tempo_freeze = 0;	/* tempo per conteggio freeze  */
double          ritardo_sim = 0;/* ritardo accumulato        */
float           velocita = 1;	/* velocita della simulazione */
float           passo_grafica = 1;	/* passo registrazione grafica */
float           passo_legograf = 1;	/* passo aggiornamento legograf su
					 * macchina MASTER   */

int             itab;		/* indice variabile tabella sincronizzazione */

int             indice_macchina;/* indice della macchina  */


MSG_NET         messaggio_master;	/* messaggio da master */

int             iterazione_successiva = 0;

int             demone_attivo = 0;

int    _MAX_SNAP_SHOT;
int    _MAX_BACK_TRACK;
int    _MAX_CAMPIONI;
int    _NUM_VAR;
int    _MAX_PERTUR;
int    _SPARE_SNAP;
int    _PERT_CLEAR;


double          gettim();
char *io_sono(void);
static int replay();
int msg_close_fam_sim(int);
void init_area_pert();

int main(argc, argv)
   int             argc;
   char           *argv[];
{
#if defined OSF1
char *fileS02={"S02_OSF1"};
#endif
#if defined LINUX
char *fileS02={"S02_LINUX"};
#endif
#if defined AIX
char *fileS02={"S02_AIX"};
#endif

int      i;
int      par1;
int      ret;
div_t    rapporto;

char *task_argv[6];
char  Argv[6][FILENAME_MAX];
char  path[FILENAME_MAX+1];
int   pidgr;
char *task_envp[NUMPAR];
char  envp[NUMPAR][FILENAME_MAX];
char  task_name[300];
SIMULATOR *sim;
FILE *fphd;
HEADER_REGISTRAZIONI hreg;
int ChiusuraSHM=0;
int ChiusuraIPC=0;


   shr_usr_key = atoi((char *) getenv("SHR_USR_KEY"));
   if(!GetParLego())
 	exit( fprintf(stderr, 
		"ATTENZIONE: i parametri del LEGO non sono definiti"));

/* Identificazione tipo di schedulatore  */
   if (argc > 1)
      {
      par1 = atoi(argv[1]);
      if (atoi(argv[1]) >= 1)
         {
	 tipo_sked = 1;
	 strcpy(nodo_master, io_sono());
	 if (atoi(argv[1]) == 2)
	    demone_attivo = 1;
         }
      else
         {
	 tipo_sked = 0;
	 strcpy(nodo_master, argv[1]);
	 printf("MASTER --> %s\n", nodo_master);
	 indice_macchina = atoi(argv[2]);
	 printf("Indice della macchina = %d\n", indice_macchina);
         }
      if( ((argc > 2)&&(tipo_sked==1)) || 
          ((argc > 3)&&(tipo_sked==0))  )
         {
         for(i=1;i<argc-1;i++)
            {
            if(strcmp(argv[i],ARGV_N_SNAP)==0)
                  _MAX_SNAP_SHOT  = atoi(argv[i+1]);
            if(strcmp(argv[i],ARGV_N_BKTK)==0)
                  _MAX_BACK_TRACK = atoi(argv[i+1]);
            if(strcmp(argv[i],ARGV_N_CAMP_CR)==0)
                  _MAX_CAMPIONI   = atoi(argv[i+1]);
            if(strcmp(argv[i],ARGV_N_VAR_CR)==0)
                  _NUM_VAR        = atoi(argv[i+1]);
            if(strcmp(argv[i],ARGV_N_PERT_ACTIVE)==0)
                  _MAX_PERTUR     = atoi(argv[i+1]);
            if(strcmp(argv[i],ARGV_N_SPARE)==0)
                  _SPARE_SNAP     = atoi(argv[i+1]);
            if(strcmp(argv[i],ARGV_N_PERTCL)==0)
                  _PERT_CLEAR     = atoi(argv[i+1]);
            }
         printf("\t Letto =%d\n",_MAX_SNAP_SHOT);
         printf("\t Letto =%d\n",_MAX_BACK_TRACK);
         printf("\t Letto =%d\n",_MAX_CAMPIONI);
         printf("\t Letto =%d\n",_NUM_VAR);
         printf("\t Letto =%d\n",_MAX_PERTUR);
         printf("\t Letto =%d\n",_SPARE_SNAP);
         printf("\t Letto =%d\n",_PERT_CLEAR);
         }
      }
    else
      {
      printf("Fornisci i parametri a net_prova !!!!\n");
      exit(0);
      }

   printf("\t net_prova %d\n", par1);
   errore = RtCreateErrore(RT_ERRORE_TERMINALE,"net_prova");
   sim = (SIMULATOR*)calloc(1,sizeof(SIMULATOR));
   sim->max_snap_shot  = _MAX_SNAP_SHOT;
   sim->max_back_track = _MAX_BACK_TRACK;
   sim->max_campioni   = _MAX_CAMPIONI;
   sim->num_var        = _NUM_VAR;
   sim->max_pertur     = _MAX_PERTUR;
   sim->spare_snap     = _SPARE_SNAP;
   sim->pert_clear     = _PERT_CLEAR;

   switch (par1)
      {
      case 0:
         {
         printf("Significato primo parametro : net_prova <num> -num_snap ... \n");
         printf("<1> aggancio SH1,  <2> aggancio SH2  <3> aggancio entrambe\n");
         printf("<4> creo SH1,      <5> creo SH2      <6> creo entrambe\n");
         printf("<7> distruggo SH1, <8> distruggo SH2 <9> distruggo entrambe\n");
         printf("<10> ALTRO\n");
         break;
         }
      case 1:
         {
         dbpunti     = RtCreateDbPunti(errore,NULL,DB_PUNTI_INT,sim);
         break;
         }
      case 2:
         {
         dbpunti_ext = RtCreateDbPunti(errore,NULL,DB_PUNTI_SHARED,sim);
         break;
         }
      case 3:
         {
         dbpunti     = RtCreateDbPunti(errore,NULL,DB_PUNTI_INT,sim);
         dbpunti_ext = RtCreateDbPunti(errore,NULL,DB_PUNTI_SHARED,sim);
         break;
         }
      case 4:
         {
         dbpunti     = RtCreateDbPunti(errore,fileS02,DB_PUNTI_INT,sim);
         RtDestroyDbPunti(dbpunti);
         break;
         }
      case 5:
         {
         dbpunti_ext = RtCreateDbPunti(errore,fileS02,DB_PUNTI_SHARED,sim);
         break;
         }
      case 6:
         {
         dbpunti     = RtCreateDbPunti(errore,fileS02,DB_PUNTI_INT,sim);
         dbpunti_ext = RtCreateDbPunti(errore,fileS02,DB_PUNTI_SHARED,sim);
         break;
         }
      case 7:
         {
         dbpunti     = RtCreateDbPunti(errore,NULL,DB_PUNTI_INT,sim);
         RtDestroyDbPunti(dbpunti);
         break;
         }
      case 8:
         {
         dbpunti_ext = RtCreateDbPunti(errore,NULL,DB_PUNTI_SHARED,sim);
         RtDestroyDbPunti(dbpunti_ext);
         break;
         }
      case 9:
         {
float tempo;
         dbpunti     = RtCreateDbPunti(errore,NULL,DB_PUNTI_INT,sim);
         dbpunti_ext = RtCreateDbPunti(errore,NULL,DB_PUNTI_SHARED,sim);
printf("\t\t Prima di RtDbPGetTime\n");
    RtDbPGetTime(dbpunti,&tempo);
printf("\t\t Dopo di RtDbPGetTime tempo=%f\n\n",tempo);

         RtDestroyDbPunti(dbpunti);
         RtDestroyDbPunti(dbpunti_ext);
         break;
         }
      case 10:
         {
         int a=198;
         int b=50;
         int c;
         c = (int)a / (int)b;
         printf("\t\t a=%d b=%d   c=%d\n",a,b,c);
/*
         fphd = fopen("f22circ.hd","r");
         fread(&hreg, sizeof(HEADER_REGISTRAZIONI), 1, fphd);
         fclose(fphd);
         printf("\t\t Ho letto pf22 hreg %d %d %d %d %d %d (size=%d)\n",
                hreg.simulator.max_snap_shot,
                hreg.simulator.max_back_track,
                hreg.simulator.max_campioni,
                hreg.simulator.num_var,
                hreg.simulator.max_pertur,
                hreg.simulator.spare_snap,
                sizeof(HEADER_REGISTRAZIONI));
         printf("\t\t FACCIO snaf14\n");
         system("xterm -T SNAF14 -sb -e snaf14 ");
*/
         break;
         }
      case 11:
         {
         dbpunti     = RtCreateDbPunti(errore,fileS02,DB_PUNTI_INT,sim);
         replay();
         system("cp perturbazioni.dat.legor2 perturbazioni.dat");
         break;
         }
      } /* Fine switch */
   free(sim);

/*  Operazioni di chiusura */
    if( ChiusuraIPC==1 )
        {
        msg_close_fam();
        msg_close_fam_sim(nmod);
        }
    if( ChiusuraSHM==1 )
        {
        RtDestroyDbPunti(dbpunti);
        RtDestroyDbPunti(dbpunti_ext);
        }

    printf("\nFINE net_prova\n");
}/* main */


void init_area_pert()
{
   int             k;
   TIPO_PERT *pert, *pert_att;

   if((pert=RtDbPGetPuntPert(dbpunti))==NULL)
                return;

   if((pert_att=RtDbPGetPuntPertAtt(dbpunti))==NULL)
                return;
printf(" \t pert=%ld pert_att=%ld\n",pert,pert_att);

   for (k = 0; k < _MAX_PERTUR; k++)
   {
      pert[k].tipo = -1;
      if( (k==0)||(k==_MAX_PERTUR-1) )
         printf("pert[k=%d].tipo=%d pert[k].posizione=%d\n",
                 k,pert[k].tipo,pert[k].posizione);
      pert[k].posizione = k + 1;
   }
   for (k = 0; k < _MAX_PERTUR; k++)
   {
      if( (k==0)||(k==_MAX_PERTUR-1) )
        printf("pert_att[k=%d].tipo=%d pert_att[k].posizione=%d\n",
                k,pert_att[k].tipo,pert_att[k].posizione);
      pert_att[k].tipo = -1;
      pert_att[k].posizione = k + 1;
   }
}


int ParAttesa()
{
int ret;
double fret;
double coef=10.0/7000000.0;
int num=_MAX_CAMPIONI * _NUM_VAR;
float numf=_MAX_CAMPIONI * _NUM_VAR;

   fret = coef * num;
/*
   printf("\t\t ParAttesa coef=%f num=%d prod=%f\n",
              coef,num,fret);
*/
   fret += 1;
   if( fret> 10 )
       fret=11;
   return((int)fret);
}



int replay()
{
FILE           *fp_pert=NULL;
TIPO_PERT       perturbazione;
int             k = 0;
int             pos;
float           tempo;
int             ret;
fpos_t          posizione;
int conta=0;

printf("\t\t REPLAY\n\n\n");

         if (fp_pert != NULL)
            fclose(fp_pert);
         if (!(fp_pert = fopen("perturbazioni.dat", "r+")))
         {
            if (!(fp_pert = fopen("perturbazioni.dat", "a")))
               return (-1);
            else
               return (1);
         }

         k = 0;
         fgetpos(fp_pert,&posizione);
         while ( (ret=fread(&perturbazione, sizeof(TIPO_PERT), 1, fp_pert))>0) 
         {
conta++;
if( conta==10 )
   return(1);
            printf ("sked_replay 3 legge item=%d  perturbazione.t=%f",
                     ret,perturbazione.t);
            ret=0;
            RtDbPGetTime(dbpunti,&tempo);
            tempo =2.5;
            printf ("\t tempo=%f (k=%d)\n",tempo,k);
            if (perturbazione.t > tempo)
            {
            printf ("sked_replay: 3 [%d] legge pert.t=%f (%d item) tempo=%f\n",
                     k,perturbazione.t,ret,tempo);

               fsetpos(fp_pert,&posizione);
               perturbazione.t = -1;
               if (fwrite(&perturbazione, sizeof(TIPO_PERT), 1, fp_pert) == 0)
                  {
                  printf("sked_replay[3]: Errore scrittura perturbazioni\n");
                  }
               else
                  printf("sked_replay[3]: Scrittura perturbazione\n");
            }
            k++;
            fgetpos(fp_pert,&posizione);
         }
         fclose(fp_pert);
         if (!(fp_pert = fopen("perturbazioni.dat", "a")))
            return (-1);
}

/**********************************************************************
*
*       C Source:               aux.c
*       Subsystem:              3
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Tue Jan  7 10:47:27 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: aux.c-4 %  (%full_filespec: aux.c-4:csrc:3 %)";
#endif

/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)aux.c	1.27\t2/16/96";
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "topsim.h"
#include "lg1_topsim.h"
/*#include "../../legort/include/sim_param.h" */
#include "sim_param.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

extern SIMULATORE *simulatore;
char *TIPO_MOD_STR[] = {"R","P","N"};
char *OS_STR[] = {"OS","AIX","OSF1","VMS","SCO","LINUX"};


/*----------------------------------------------------------------
 *
 * check_file_status 
 *
 * determina lo stato del file (read,write permission)
 *
 * Parametri:   char *path;  /nome del file comprensivo di path/
 *
 *----------------------------------------------------------------*/
 
int check_file_status(char *path)
{
    struct stat stato; 

    if( stat(path,&stato) != 0 )
    {
      printf("Errore nella check_file_status\n");
      return(FALSE);
    }

    if( ( stato.st_mode & S_IRUSR) && ( stato.st_mode & S_IWUSR) )
    {
        printf("permesso di lettura e scrittura sul file %s\n",path); 
        return(R_OK+W_OK);
    }

    if( stato.st_mode & S_IRUSR)
    {
        printf("permesso di sola lettura sul file %s\n",path); 
        return(R_OK); 
    }

    if( stato.st_mode & S_IWUSR)
    {
        printf("permesso di scrittura sul file %s\n",path); 
        return(W_OK); 
    }
}

/*-------------------------------------------------
 * check_delta_time
 *
 * verifica la congruenza dei valori dei tempi 
 * dei modelli del simulatore 
 *
 *-----------------------------------------------*/ 
int check_delta_time()
{
   extern void show_message();
   int i,j,nmod;
   float deltat[MAX_MODELLI],temp;
   int dt_msec,dt_msec_prec;
   
   nmod = simulatore->nmodelli;

/* non ci sono ancora modelli, considero
   questa situazione Ok */

   if( !nmod )
      return(TRUE); 

/* memorizzo tutti i dati */
   for(i=0;i<nmod;i++)
      deltat[i]=simulatore->modelli[i]->activation_interval;

/* ordino i dati in modo crescente */
   for(i=0;i<nmod;i++)
      for(j=i+1;j<nmod;j++)
         if( deltat[j] > deltat[i] )
         {
             temp=deltat[i];
             deltat[i]=deltat[j];
             deltat[j]=temp;
         }
 
   
   /* verifico il limite massimo */
   if( deltat[0] > MAX_DT_DEC/10.0)
   {
       show_message("ERROR activation interval out of limits\n");  
       printf("\nERRORE activation_interval maggiore del massimo consentito\n"); 
       return(FALSE);
   }

   /* verifico che siano multipli di 0.1s */
   dt_msec = deltat[nmod-1]*1000.;
   if( deltat[nmod-1] == 0 || dt_msec%100 != 0)
   {
      show_message("ERROR activation interval must be multiple of 0.1s\n");  
      printf("\nERRORE i tempi devono essere multipli di 0.1s\n");
      return(FALSE); 
   }


   /* verifico che siano multipli tra di loro */
   for(i=1;i<nmod;i++)
   {
      dt_msec_prec=deltat[i-1]*1000.0;
      dt_msec=deltat[i]*1000.0; 
      if( dt_msec_prec%dt_msec != 0)
      {
          show_message("ERROR activation interval must be multiple between them\n");  
          printf("\nERRORE i tempi devono essere multipli tra loro\n");
          return(FALSE);
      }
   } 
   return(TRUE);
}

/*------------------------------------------
 *
 * libera la memoria occupata dalle variabili 
 *
 *------------------------------------------*/

void libera_variabili(VAR  *var)
{
   if( var != NULL)
      free(var);
}


/*------------------------------------------
 *
 * libera la memoria occupata da un blocco 
 *
 * del blocco devo liberare solo le variabili
 * allocate
 *------------------------------------------*/

void libera_blocco(BLOCCO bl)
{
   libera_variabili(bl.variabili);
}


/*------------------------------------------
 *
 * libera la memoria occupata da un modello 
 *
 *------------------------------------------*/

void libera_modello(MODELLO *model)
{
   int i;

   if( model != NULL)
   {
      for(i=0;i<model->num_blocchi;i++)
         libera_blocco(model->blocchi[i]);

      free(model);
   }
}

/*------------------------------------------
 *
 * libera la memoria occupata da un simulatore 
 *
 *------------------------------------------*/

void libera_simulatore(SIMULATORE *sim)
{
   int i;
  
   if( sim != NULL)
   {
      for(i=0;i<sim->nmodelli;i++)
         libera_modello(sim->modelli[i]);

      free(sim);
   }
}

/*------------------------------------------
 *
 *  allocazione di un modello 
 *
 *------------------------------------------*/

MODELLO *alloca_modello()
{
   return( calloc(1,sizeof(MODELLO) ));
}

/*--------------------------------------------
 *
 * allocazione del simulatore 
 *
 *-------------------------------------------*/

SIMULATORE  *alloca_simulatore()
{
   return( calloc(1,sizeof(SIMULATORE)) );
} 


/*------------------------------------------
 *
 *  salva su file S01
 *
 *------------------------------------------*/

int save_S01(char *path)
{
   FILE *fp;
   int i,j,k,len;
   char filename[STRLONG];
   char *pattern={"****"};
   MODELLO *mod=NULL;
   CONNMODEL *conn;
/* 6-2-96 Micheletti */
   char *matrice;              /* per ordinamento alfabetico connessioni */
   int nr,nrighe,size_riga=500;   /* definizione riga matrice */


/* condizione di errore */ 
   if( simulatore == NULL)
   {
      printf("ERRORE Simulatore == NULL !!!\n");
      return(FALSE);
   }


   sprintf(filename,"%s/%s",path,"S01");

   printf("save_S01 filename=%s\n",filename);

   if( check_file_status(filename) == R_OK )
   {
      printf("S01 e' in read only\n");
      return(FALSE);
   }

/* condizione di errore */
   if( (fp=fopen(filename,"w")) == NULL)
   {
      printf("Cannot open %s for write, it can be in read_only\n",filename);
      fclose(fp);
      return(FALSE);
   }


   fprintf(fp,"%s\n",pattern);
   fprintf(fp,"%s %s\n",simulatore->nome,simulatore->descr);
   fprintf(fp,"%s\n",pattern);

   for(i=0;i<simulatore->nmodelli;i++)
   {
      mod=simulatore->modelli[i];
      fprintf(fp,"%s %s\n",mod->nome,mod->descr);
   }

   fprintf(fp,"%s\n",pattern);
   for(i=0;i<simulatore->nmodelli;i++)
   {
      mod=simulatore->modelli[i];
      len = strlen(mod->local_path);
      if( mod->local_path[len-1] != '/')
         strcat( mod->local_path,"/");

      fprintf(fp,"%s %s\n",mod->local_path,TIPO_MOD_STR[mod->tipo_task] );
   }   

   fprintf(fp,"%s\n",pattern);

   for(i=0;i<simulatore->nmodelli;i++)
   {
      mod=simulatore->modelli[i];
      len = strlen(mod->remote_path);
      if( mod->remote_path[len-1] != '/')
         strcat( mod->remote_path,"/");
      fprintf(fp,"%s %s %s %s\n",mod->OS,mod->host,mod->guest,mod->remote_path);
   }

   fprintf(fp,"%s\n",pattern);

   for(i=0;i<simulatore->nmodelli;i++)
   {
      mod=simulatore->modelli[i];
      fprintf(fp,"%f\n",mod->activation_interval);
   }

   fprintf(fp,"%s\n",pattern);

/* adesso devo descrivere le connessioni tra le task *
/* per momento le ignoro e scrivo solo i nomi delle singole task */
 
#ifdef IN_MODIFICA
   for(i=0;i<simulatore->nmodelli;i++)
   {
      mod=simulatore->modelli[i];
      fprintf(fp,"%s\n",mod->nome);
      /* cerco per ciascun blocco le connesioni */
      for(j=0;j<mod->num_blocchi;j++)
      {
         conn = mod->blocchi[j].var_conn_task;    
         while( conn != NULL)
         {
            if(mod->blocchi[j].variabili[conn->var_interna].tipo == INGRESSO)
            {
               fprintf(fp,"%s %s  %s\n",
                    mod->blocchi[j].variabili[conn->var_interna].nome,
                    simulatore->modelli[conn->modello_esterno]->nome,
                    simulatore->modelli[conn->modello_esterno]->blocchi[conn->blocco_esterno].variabili[conn->var_esterna].nome); 
            }
            conn = conn->succ;
         } 
      } 
      fprintf(fp,"%s\n",pattern);
   }
#endif

/* 6-2-96 Micheletti prova di ordinamento alfabetico connessioni */

   for(i=0;i<simulatore->nmodelli;i++)
   {
      mod=simulatore->modelli[i];
      fprintf(fp,"%s\n",mod->nome);

      /* cerco per ciascun blocco le connessioni */
      for(j=0;j<mod->num_blocchi;j++)
      {
         /* conto le connessioni */
         nrighe = 0;
         conn = mod->blocchi[j].var_conn_task;    
         while( conn != NULL)
         {
            if(mod->blocchi[j].variabili[conn->var_interna].tipo == INGRESSO)
               nrighe++;

            conn = conn->succ;
         }

         /* ho almeno una connessione da ordinare 
            nella matrice
         */
         if( nrighe > 0 )
         {
            /* alloco una matrice */
            if( (matrice = calloc(1,nrighe*size_riga)) == NULL)
            {
               printf("Errore in malloc matrice\n");
               return(FALSE);
            }

            /* print della connessione in matrice */
            nr=0;
            conn = mod->blocchi[j].var_conn_task;    
            while( conn != NULL)
            {
               if(mod->blocchi[j].variabili[conn->var_interna].tipo == INGRESSO)
               {
                  sprintf(matrice+(nr*size_riga),"%s %s %s\n",
                    mod->blocchi[j].variabili[conn->var_interna].nome,
                    simulatore->modelli[conn->modello_esterno]->nome,
                    simulatore->modelli[conn->modello_esterno]->blocchi[conn->blocco_esterno].variabili[conn->var_esterna].nome); 
                  nr++;
               }
               conn = conn->succ;
            }
            
            /* ordinamento alfabetico matrice */
            qsort(matrice,nrighe,size_riga,strcmp);

            /* stampa su S01 delle connessioni ordinate */
            for(nr=0;nr<nrighe;nr++)
               fprintf(fp,"%s",matrice+(nr*size_riga));

            /* lebero la memoria occupata */
            if( matrice != NULL ) 
               free(matrice);
         }
         
      }
      fprintf(fp,"%s\n",pattern);
   }

/*---- fine prova ---*/

   if( strlen(simulatore->bm) )
      fprintf(fp,"%s\n",simulatore->bm); 
   else
      fprintf(fp,"%s\n","BM");

   if( strlen(simulatore->scada) )
      fprintf(fp,"%s\n",simulatore->scada);
   else
      fprintf(fp,"%s\n","SCADA");

   if( strlen(simulatore->bi) )
      fprintf(fp,"%s\n",simulatore->bi); 
   else
      fprintf(fp,"%s\n","BI"); 

   fprintf(fp,"%s\n",pattern);

   fclose(fp);

   printf("save_S01 terminata correttamente\n");

   return(TRUE);
}


/*-------------------------------
 *
 * skip di una riga           
 *
 *-------------------------------*/

void skip_riga(FILE *fp)
{
   char scarta[100];

   fgets(scarta,80,fp);
}

/*----------------------------------------------
 *
 * elimina i blank in fondo ad una stringa
 * e il new line 
 *
 *---------------------------------------------*/
 
void elimina_nl(char *str)
{
   char *appo;
   trim_blank(str);
   if( (appo=strchr(str,'\n')) != NULL)
      *appo=0;
}

/*------------------------------------------------
 *
 * conta il numero di modelli che sono
 * descritti in un S01 
 *
 *------------------------------------------------*/

int conta_modelli(int *num,FILE *fp)
{
   int i;
   char riga[100];

   /* leggo la riga di astrischi */
   if( fgets(riga,80,fp) == EOF)
       return(FALSE);

   i=0;
   while(TRUE)
   {
      if( fgets(riga,80,fp) == EOF)
         return(FALSE);

      /* se trovo come primo car un aesterisco non c'e'
         in questa riga un modello, QUINDI HO FINITO. 
      */
      if( riga[0] == '*')
         break;
      else
         i++;
   }
   *num = i;
}

/*-----------------------------------------------
 * 
 * legge il file S01 
 *
 *-----------------------------------------------*/

int read_S01data(char *filename,SIMULATORE *sim)
{
/* filename = nome del file comprensivo di path */
/* sim  = puntatore alla struttura SIMULATORE */

   extern int make_task_connection();
   extern int init_modello();
   extern int simulator_changed;
   FILE *fp;
   char riga[100];
   char *appo,*appo2;
   char conn1[100],conn2[100],modconn1[100],modconn2[100];
   int ind_mod1,ind_bl1,ind_var1,ind_mod2,ind_bl2,ind_var2;
   int num_modelli;
   int i,j,k,m;
   TIPO_MOD tipo;
   MODELLO *newmod;
   int num_mod;
   long int offset;
   int conn_found;
   int var_found;
   int conn_errore;

   
   /* apertura file S01 */
   if( (fp = fopen(filename,"r")) == NULL )
   {
      fclose(fp);
      return(FALSE);
   }

   /* skip riga asterischi */
   skip_riga(fp);

/* get NOME e DESCRIZIONE(Opzionale) SIMULATORE */
   fgets(riga,80,fp);

   /* verifico se esiste la descrizione */
   if( (appo=strchr(riga,' ')) != NULL )
   {
      strncpy(sim->nome,riga,(appo-riga));
      while( *appo == ' ')
         appo++;
      strcpy(sim->descr,appo);
   }
   else
      strcpy(sim->nome,riga);


/* conto i MODELLI */
   num_modelli = sim->nmodelli =  0;

   /* salvo e ripristino (dopo aver contato i modelli)
      la posizione del file pointer */
   offset = ftell(fp);
   conta_modelli(&num_modelli,fp);
   fseek(fp,offset,0);

   sim->nmodelli = num_modelli;

   /* skip riga asterischi */
   skip_riga(fp);

   /* leggo le descrizioni del modello 
      N.B il nome lo traggo dal file F01.dat
    */
   for(i=0;i<num_modelli;i++)
   {
       /* per ogni modello alloco memoria */
       if( (newmod = alloca_modello()) == NULL)
       {
           printf("errore allocazione modelli\n");
           return(FALSE);
       }
       else
          sim->modelli[i] = newmod;

       fgets(riga,80,fp);

       /* verifico che esiste la descrizione */
       if( (appo=strchr(riga,' ')) != NULL )
       {
          /* skip dei blank */
          while( *appo == ' ' )
             appo++;

/***
          printf("\n\ntdescrizione=[%s]\n",appo);
***/
          strcpy((sim->modelli[i])->descr,appo);
          elimina_nl((sim->modelli[i])->descr);
       }
   }

   /* skip riga asterischi */
   skip_riga(fp);

/* get PATH LOCALE e TIPO TASK  
   P = task di preocesso
   R = task di regolazione
   N = task non legocad
*/

   for(i=0;i<num_modelli;i++)
   {
       /* leggo la riga */
       fgets(riga,80,fp);

       /* verifico se esiste il tipo */
       if( (appo=strchr(riga,' ')) != NULL )
       {
             strncpy((sim->modelli[i])->local_path,riga,(appo-riga));
             if( strchr(appo,'P') )
                sim->modelli[i]->tipo_task=PROCESSO;
             else if( strchr(appo,'R') )
                sim->modelli[i]->tipo_task=REGOLAZIONE;
             else if( strchr(appo,'N') )
                sim->modelli[i]->tipo_task=NOLEGO;
             else 
                sim->modelli[i]->tipo_task=PROCESSO;
       }
       else
       {
            strcpy((sim->modelli[i])->local_path,riga);
            elimina_nl((sim->modelli[i])->local_path);
            sim->modelli[i]->tipo_task=PROCESSO;
       }

       /* inializzo il modello.
          solamente adesso lo posso fare perche' 
          solo adesso conosco la path del modello.
          N.B. nella init_modello leggo anche l'F01.dat
       */
       if( init_modello(sim->modelli[i]) != TRUE)
       {
           printf("ERRORE la init_modello [%s] e' terminata restituendo un FALSE\n", 
                    sim->modelli[i]->local_path);
           break;
       }
 
   }


   /* skip riga asterischi */
   skip_riga(fp);

/* get OS + HOST + UTENTE + PATH_REMOTO */
   for(i=0;i<num_modelli;i++)
   {
       fscanf(fp,"%s",(sim->modelli[i])->OS);
       fscanf(fp,"%s",(sim->modelli[i])->host);
       fscanf(fp,"%s",(sim->modelli[i])->guest);
       fscanf(fp,"%s",(sim->modelli[i])->remote_path);
   }

   /* skip del new line */
   skip_riga(fp);

   /* skip della riga di asterischi  */
   skip_riga(fp);

/* get ACTIVATION INTERVAL */
   for(i=0;i<num_modelli;i++)
   {
      char  appo[100];
      fscanf(fp,"%s",appo);
      (sim->modelli[i])->activation_interval=(float)atof(appo);
   }


   /* skip del new line */
   skip_riga(fp);
   /* skip della riga di asterischi  */
   skip_riga(fp);


   /* adesso sono descritte le connessioni   
      per ogni task esiste almeno un record contenente il nome
      della task
      La descrizione delle connessioni di una task
      terminano quando incontro la riga di asterischi  
   */

   for(i=0;i<num_modelli;i++)
   {
      /* mi aspetto di leggere il nome della task */
      fgets(modconn1,80,fp);
      elimina_nl(modconn1);
       
      /* adesso leggo o asterischi o una connessione */
      fgets(riga,80,fp);

      /* finche leggo una connessione continuo a leggere  */
      while( (appo = strstr(riga,"**")) == NULL)
      {

         sscanf(riga,"%s%s%s",conn1,modconn2,conn2);

/* per debug
         printf("connessione: ingresso %s del modello %s  e l'uscita %s del modello  %s\n", conn1,modconn1,conn2,modconn2);
*/

         ind_mod1 = i;

         /* trovo il secondo modello */
         for(j=0;j<num_modelli;j++)
            if( strcmp(modconn2,sim->modelli[j]->nome) == NULL)
               ind_mod2=j;

         if( strlen(conn1)<8  )
            strncat(conn1,"        ",8-strlen(conn1));


         /* scorro le variabili dei blocchi del primo modello  
           e verifico se il nome concide con quello letto */

         var_found = FALSE;

         for(j=0;j<sim->modelli[ind_mod1]->num_blocchi;j++)
            for(k=0;k<sim->modelli[ind_mod1]->blocchi[j].num_variabili;k++)
               if( strcmp(conn1,sim->modelli[ind_mod1]->blocchi[j].variabili[k].nome) == NULL) 
               {
                   var_found = TRUE;
                   ind_bl1=j; 
                   ind_var1=k;
               }

         if( !var_found )
         {
            conn_errore = TRUE;
            printf("\nERROR INPUT VARIABLE NOT FOUND: model %s variable %s\n",
                    sim->modelli[ind_mod1]->nome,conn1);
            
            simulator_changed = FALSE;
         }
         else
         {

           if(strlen(conn2)<8)
               strncat(conn2,"        ",8-strlen(conn2));


            /* scorro le variabili dei blocchi del secondo modello
              e verifico se il nome concide con quello letto 
              e se lo trovo faccio la connessione */

            conn_found = FALSE;

            for(j=0;j<sim->modelli[ind_mod2]->num_blocchi;j++)
               for(k=0;k<sim->modelli[ind_mod2]->blocchi[j].num_variabili;k++)
                  if( strcmp(conn2,sim->modelli[ind_mod2]->blocchi[j].variabili[k].nome) == NULL)
                  {
                     conn_found = TRUE;
                     ind_bl2=j;
                     ind_var2=k;
                     make_task_connection(ind_mod1,ind_bl1,ind_var1,ind_mod2,ind_bl2,ind_var2);
                  }

            if( !conn_found )
            {
               conn_errore = TRUE;
               printf("\nERROR VARIABLE NOT FOUND: model %s variable %s\n",
                    sim->modelli[ind_mod2]->nome,conn2);
            }
         }
          
         /* continuo a leggere */ 
         fgets(riga,80,fp);
      }
   }


   /* get BI,SCADA,BM */
   if( fgets(riga,80,fp) != NULL)
   {
      strcpy(sim->bm,riga);
      fgets(riga,80,fp);
      strcpy(sim->scada,riga);
      fgets(riga,80,fp);
      strcpy(sim->bi,riga);
   }

/* elimino i new_line che possono esserci nelle stringhe */
   elimina_nl(sim->nome);
   elimina_nl(sim->descr);
   for(i=0;i<num_modelli;i++)
   {
      elimina_nl(sim->modelli[i]->nome);
      elimina_nl(sim->modelli[i]->descr);
      elimina_nl(sim->modelli[i]->local_path);
   }
   elimina_nl(sim->bm);
   elimina_nl(sim->scada);
   elimina_nl(sim->bi);

   fclose(fp);

   if( conn_errore == TRUE )
   {
      simulator_changed = FALSE;
      return(FALSE);
   }

   return(TRUE);
       
}


/*-----------------------------------------------
 *
 * apre il file lo legge e ritorna il contenuto
 * in una stringa
 *
 *-----------------------------------------------*/

int view_file(char *filename,char **text_to)
{
   FILE *fp;
   struct stat s01;
   char *stringa = NULL;
   char *ptr2 = NULL;

   fp = fopen (filename,"r");
   if (fp == NULL)
   {
      printf ("Can't open file %s\n", filename);
      return(FALSE);
   }  
   else
   {

 /* Recupera la dimensione del file */
 /* Lettura del file */
      if ( !fstat(fileno(fp),&s01))
      {
         stringa = (char *) malloc ((unsigned) s01.st_size+1);
      }
      else
         stringa = (char *) malloc (sizeof(char) * 100000);

      ptr2 = stringa;
      while (fgets(ptr2,140,fp) != NULL)
         ptr2 = ptr2+strlen(ptr2);
   }

   (*text_to) = stringa;

   fclose(fp);
   return(TRUE);
}

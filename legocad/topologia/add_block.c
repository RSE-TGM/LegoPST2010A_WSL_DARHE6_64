/**********************************************************************
*
*       C Source:               add_block.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Thu Mar 11 17:55:20 2004 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: add_block.c-3 %  (%full_filespec: add_block.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)add_block.c	2.28\t5/31/95";
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "lg1.h"
#include "errore.h"

/* Function declarations */
void errore(const char*, ...);

#define SIZE_RIGA 85

extern ERR_LEVEL err_level;
extern int num_modulo;

FILE *fp;

int LEGGI_RIGA(char *buff)
  {
    int i;
    char strapp[300];

    memset(strapp, 0, 300);
    if ( !fgets( strapp, 300 , fp ) )
      {
        if ( feof( fp) )
          ;
        else
         ;
        return(0);
      }
 
   memcpy(buff,strapp,SIZE_RIGA);

/* sostiruisco gli 0 che si trovano in mezzo alla riga */
   for(i=0;i<SIZE_RIGA-1;i++)
{
     if(buff[i] == '\0')
        buff[i] = ' ';
}

/* sostituisco il terminatore new_line con 0 */
   for(i=0;i<SIZE_RIGA;i++)
     if(buff[i] == '\n')
        buff[i] = '\0';

/* il new_line potrebbe non esserci
   quindi mi assicuro che sia
   terminata correttamente */

   buff[SIZE_RIGA-1] = '\0';
   return(1);
}



/* READ_PROCESS 
 * routine di lettura modulo di processo
 */
int read_process()
{
  extern int graphics_on;
  extern int Icrea_ico();
  extern void add_item();
  BLOCCO new_block;
  char riga[SIZE_RIGA],mappa[300][SIZE_RIGA];
  int i,j,num_righe,indice_mappa;
  char *getenv(),*getcwd(),*var_env,var_cwd[300];
  char fname[300],*puntatore, strappo[100]; 
  char nome_modulo[5],label[10];
  VAR *var; 
  CONN *conn;

/* 6-4-95 Micheletti */
   BLOCCO prevblk,saveblk;

/***** inizializzo la struttura di appoggio che conterra il blocco */
   new_block.variabili = NULL;
   new_block.variabili_connesse = NULL;
   new_block.num_variabili = 0;
   new_block.modulo =0;


/* acquisisco la stringa della directory attuale */
  strcpy(var_cwd , getcwd( (char *)NULL,128));
  if( getcwd( (char *)NULL,128)  == NULL)
  {
     err_level = ERROR;
     printf("errore getcwd ha restituito un NULL\n");
     errore("error on getcwd");
     return -1;
  }

/* genero il nome del file da aprire comprensivo della path */
  strcpy(fname,var_cwd);
  strcat(fname,"/fort.77");

/* apro il file in lettura */
  if( (fp = fopen(fname,"r")) == NULL)
  {
     printf("File %s not generated or not found",fname);
     err_level = ERROR;
     errore("File %s not generated or not found",fname);
     return -1;
  }
  
/* leggo tutto il file e lo mappo in memoria */
  i=0;
  while( (j=LEGGI_RIGA(riga)) != 0 )
  {
     strcpy(mappa[i],riga);
     i++;
  }

/* dopodiche lo chiudo */
  fclose(fp);
  num_righe = i;

/* stampa di controllo - sempre utile  */
  printf("righe lette = %d\n",i);
  for(i=0;i<num_righe;i++)
     printf("mappa[%d] = %s\n",i,mappa[i]);


/* adesso traggo le informazioni necessarie a ricavare 
   la prima riga ha questo aspetto   (non sono rispettate le posizioni)
   FUMG  BL.-- **** MODULO FUMG -
   le altre righe descrivono le variabili che sono num_righe -1
*/
 
/* nome del modulo */
   puntatore = &(mappa[0][32]);         
   strncpy(nome_modulo,puntatore,4);
   nome_modulo[4]=0;

/* meta' della label */
   puntatore = &mappa[0][0];
   strncpy(label,puntatore,4);
   label[4]=0;

/* dati generali del nuovo blocco  */

/* 6-4-95 Micheletti */
if( strstr(mappa[0],"REGOL") )
   new_block.tipo = REGOLAZIONE;
else
   new_block.tipo = PROCESSO;

   strcpy(new_block.sigla_modulo,nome_modulo);
   strcpy(new_block.sigla_blocco,blockname);
   strcpy(new_block.label,label);
   strcat(new_block.label,new_block.sigla_blocco);
   strcpy(new_block.descr_blocco,blockdescr);
   new_block.modulo = num_modulo;
   new_block.num_variabili = (num_righe -1);
   new_block.variabili = var = (VAR *) calloc( new_block.num_variabili , sizeof(VAR) );
   
   for( i=0; i < new_block.num_variabili; i++) 
   {
      indice_mappa = i+1;
/* leggo il nome della variabile */
      puntatore = &(mappa[indice_mappa][0]);
      strncpy(var[i].nome,puntatore,4);
      var[i].nome[4]=0;

/* se trovo al suo interno dei blank 
   li sostituisco con underscore */
      if((char *)strchr(var[i].nome,' ') != NULL )
         for( j=0; j<4; j++)
            if( var[i].nome[j] == ' ' )
               var[i].nome[j] = '_';

/* concateno il nome della variabile con il nome del blocco */
      strcat(var[i].nome,blockname);
/* se la lunghezza risultante e' minore di 8ch aggiungo blcnk */
      if(strlen(var[i].nome) < 8)
         strncat(var[i].nome,"        ",(8 - strlen(var[i].nome)));

/* aggiungo la descrizione della variabile */
      strncpy(var[i].descr,&(mappa[indice_mappa][17]),63);
      var[i].descr[63]=0;

/* set del tipo ingresso-uscita-stato */
      switch(mappa[indice_mappa][13])
      {
         case 'S':
            var[i].tipo = STATO;
         break;
        case 'A':
            var[i].tipo = USCITA;
         break;
         case 'N':
            var[i].tipo = INGRESSO;
         break;
         default:
            err_level = WARNING;
            errore(TIPO_VAR_ERR, var[i].nome,new_block.sigla_modulo, new_block.sigla_blocco);
         break;
      }

/* inizializzo a 0 le connessioni */
      var[i].connessioni = 0;
   }

/* 6-4-95 Micheletti */
/* metto il blocco di regolazione sempre al primo posto 
   quindi e' necessario riordinare gli altri blocchi 
*/
/* 31-5-95 Micheletti */
/* ATTENZIONE alle connessioni. La struttura delle connessioni
   contiene l'indice al blocco 'esterno' a cui e' connesso il blocco
   come indice nel vettore dei blocchi. Shiftando i blocchi anche
   questo indice deve essere incrementato.
*/

if( new_block.tipo == REGOLAZIONE )
{
   num_blocchi++;

   prevblk = new_block;
   for(i=0;i<num_blocchi;i++)
   {
      if( blocchi[i].variabili_connesse != NULL)
      {
         conn = blocchi[i].variabili_connesse;
         while ( conn != NULL)
         {
            conn->blocco_esterno++;
            conn = conn->succ;
         }
      }

      saveblk = blocchi[i];
      blocchi[i] = prevblk;
      prevblk = saveblk;
   }
}
else
{
   new_block.variabili_connesse = NULL;
   blocchi[num_blocchi] = new_block;
   num_blocchi++;
}

/* costruisco l'item per la lista */
   memset(strappo, 0, 100);
   strcpy(strappo,new_block.sigla_modulo);
   strcat(strappo," (");
   strcat(strappo,new_block.sigla_blocco);
   strncat(strappo,"   ",(4 - strlen(blockname)) );
   strcat(strappo,")  ");
   strcat(strappo,new_block.descr_blocco);


/* 6-4-95 Micheletti */
if( new_block.tipo == REGOLAZIONE )
   add_item(strappo,1);
else
   add_item(strappo,0);

   if( graphics_on )
      Icrea_ico();
   remove(fname);
}




/* READ_REGOL 
 * routine di lettura modulo di regolazione
 */
int read_regol()
{
   extern void add_item();
   char path[300],modname[10],fname[300];
   char *getenv(),*puntatore,buffappo[100];
   BLOCCO new_block,prevblk,saveblk;
   char riga[SIZE_RIGA],mappa[300][SIZE_RIGA];
   int i,j,indice_mappa,num_righe;
   VAR *var;  


/* imposto la path ove aprire il file */
   strcpy(path,getenv("LEGOCAD_USER"));
   strcat(path,"/legocad/libut_reg/");

/* se il nome del modulo e' maisculo lo converto */
/* per farlo roconoscere alla fopen */
      strcpy(modname,modulename);
      for(i=0;i<4;i++)
         if(isupper( modname[i]) )
           modname[i] = tolower(modname[i]);
           
   modname[i]=0;

/* setto il nome del file comprensivo della path */
   strcat(path,modname);
   strcat(path,".dat");
   strcpy(fname,path);
  
     
/* apro il file in lettura */
  if( (fp = fopen(fname,"r")) == NULL)
  {
     printf("File %s not generated or not found",fname);
     err_level = ERROR;
     errore("File %s not generated or not found",fname);
     return -1;
  }

   strcpy(new_block.sigla_modulo,modulename);
   new_block.tipo = REGOLAZIONE;
   new_block.modulo = num_modulo;
   new_block.variabili_connesse = NULL;

/* leggo tutto il file e lo mappo in memoria */
  i=0;
  while( (j=LEGGI_RIGA(riga)) != 0 )
  {
     strcpy(mappa[i],riga);
     i++;
  }

/* dopodiche lo chiudi */
  fclose(fp);

  num_righe = i;

/* stampa di controllo 
  printf("righe lette = %d\n",i);
  for(i=0;i<num_righe;i++)
     printf("mappa[%d] = %s\n",i,mappa[i]);
*/

/* adesso inizio a leggere le informazioni necessarie
   alla istanziazione del regolatore 
   la prima e terza riga della mappa contengono asterischi
*/

/* carico la sigla  e la descrizione blocco dalla riga n.2 */
    puntatore = &mappa[1][18];
    strncpy(new_block.sigla_blocco,puntatore,4);
    new_block.sigla_blocco[4]=0;

    puntatore = &mappa[1][25];
    strncpy(new_block.descr_blocco,puntatore,54);
    new_block.descr_blocco[54] = 0;

/* inserisco la label */
    puntatore = &mappa[3][0]; 
    strncpy(new_block.label,puntatore,8);
    new_block.label[8] = 0;

/* determino il numero di variabili in base al numero di righe lette  
   eliminando le 3 righe di asterisci piu la riga del nome del blocco 
   e la riga della label 
*/
    new_block.num_variabili = num_righe - 5;

/* alloco e inizializzo memoria per le variabili */
    new_block.variabili = var = (VAR *) calloc( new_block.num_variabili,sizeof(VAR) );

/* assegno i valori alle variabili 
   l'indice della mappa viene shiftato di 5 righe */
    for(i=0;i<new_block.num_variabili;i++)
    {
/* assegno il nome della variabille */
       indice_mappa = i + 4;
       puntatore = &mappa[indice_mappa][0];
       strncpy(var[i].nome,puntatore,8);
       var[i].nome[8]=0;

/* la descrizione */
       puntatore = &mappa[indice_mappa][17];
       strncpy(var[i].descr,puntatore,63);
       var[i].descr[63] = 0;

/* determino il tipo, uscita,stato,ingresso */
       puntatore = &mappa[indice_mappa][10];
       strncpy(buffappo,puntatore,6);
       buffappo[6] = 0;
       if( !strcmp(buffappo,"--UA--") )
          var[i].tipo = USCITA;
       else if( !strcmp(buffappo,"--US--") )
          var[i].tipo = STATO;
       else if( !strcmp(buffappo,"--IN--" ) )
          var[i].tipo = INGRESSO;
       else
       {
          printf("Tipo variabile non riconosciuta %s\n",var[i].nome);
          err_level = ERROR;
          errore("tipo variabile non riconosciuto %s",var[i].nome); 
       }

   }

/* metto il blocco di regolazione sempre al primo posto 
   quindi e' necessario riordinare gli altri blocchi 
*/

   num_blocchi++;

   prevblk = new_block;
   for(i=0;i<num_blocchi;i++)
   {
      saveblk = blocchi[i];
      blocchi[i] = prevblk;
      prevblk = saveblk;
   }
       

/* aggiungo l'item nella lista */
   strcpy(buffappo,new_block.sigla_modulo);
   strcat(buffappo," (");
   strcat(buffappo,new_block.sigla_blocco);
   strncat(buffappo,"   ",(4 - strlen(new_block.sigla_blocco)) );
   strcat(buffappo,")  ");
   strcat(buffappo,new_block.descr_blocco);

   add_item(buffappo,1);

   return 0;
}



/* ADD_PROCESS
 * reoutine di istanziazione nuovo blocco */
void add_block(int tipo)
{

  if(tipo == REGOLAZIONE)
     read_regol();
  else if(tipo == PROCESSO)
     read_process();
}



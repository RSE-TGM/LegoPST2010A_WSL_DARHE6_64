/**********************************************************************
*
*       C Source:               read_f01.c
*       Subsystem:              2
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Tue Jan  7 10:49:17 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: read_f01.c-2 %  (%full_filespec: read_f01.c-2:csrc:2 %)";
#endif

/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)read_f01.c	1.26\t2/5/96";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "topsim.h"
#include "lg1_topsim.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define PATREGVAR "@#"

int tipo_modello;
int num_reg_var;

static int leggi_f01_var( MODELLO *task, FILE *fp );
extern char *trim_blank(char *str);

/***
   legge una riga dal file 
***/
int read_riga(FILE *f01,char *riga)
{
   if ( !fgets( riga, 85, f01 ) ) 
      { 
        if ( feof( f01) ) 
          printf("errore incontrata fine del file f01.dat\n"); 
        else 
          printf("errore in lettura riga fine del file f01.dat\n"); 
        return(FALSE); 
      } 
    
    *((char*) strrchr(riga,'\n')) = '\0'; 
    return(TRUE);
}



/* Lettura della prima parte del file F01 contenente la lista dei blocchi
 * con le loro descrizioni
 */
int leggi_f01_bl( MODELLO *task,FILE *fp )
{
   char riga[200];

   read_riga(fp,riga); 

  /* Lettura della prima parte del file F01 contenente la lista dei blocchi
   * con le loro descrizioni
   */
   for ( task->num_blocchi=0; ; )
   {

      /* Lettura della riga corrente del file */
      read_riga(fp,riga); 


      /* Controlla se e' terminata la prima parte del file F01 */
      if ( ! strncmp ( riga, "****", 4 ) )
         break;
 

      /* Prima degli asterischi ci devono essere solo righe contenenti
       * la keyword BLOCCO.
       */
      if ( strncmp ( riga+10, "BLOCCO", 6 ) )
      {
         printf("ERRORE FORMATO F01\n");
         return(FALSE);
      }

      /* Controlla lo sforamento per il vettore dei blocchi. */
      if ( task->num_blocchi == MAX_BLOCCHI )
      {
         printf("ERRORE NUMERO_BLOCCHI SUPERATO MASSIMO NUMERO AMMESSO\n");
         return(FALSE);
      }


      /* Sistema i campi del descrittore del blocco tranne quelli riguardanti
       * le variabili i quali verranno sistemati successivamente.
       */

      strncpy( (task->blocchi[task->num_blocchi]).sigla_modulo, riga, 4 );
      (task->blocchi[task->num_blocchi]).sigla_modulo[4] = '\0';

      strncpy( (task->blocchi[task->num_blocchi]).sigla_blocco, riga+18, 4 );
      (task->blocchi[task->num_blocchi]).sigla_blocco[4] = '\0';

      strncpy( (task->blocchi[task->num_blocchi]).descr_blocco, riga+26, 54 );
      (task->blocchi[task->num_blocchi]).descr_blocco[54] = '\0';
      (task->blocchi[task->num_blocchi]).variabili_connesse = NULL;
      (task->blocchi[task->num_blocchi]).var_conn_task = NULL;

/**** DEBUG PRINT
       printf("Ho letto da f01.dat %s%s  %s\n",
       (task->blocchi[task->num_blocchi]).sigla_modulo,
       (task->blocchi[task->num_blocchi]).sigla_blocco,
       (task->blocchi[task->num_blocchi]).descr_blocco);
*****/

      task->num_blocchi++;

   }

   if( task->num_blocchi == 0 )
      return(FALSE);

   return(TRUE);
}

 
/* Conteggio delle variabili */
int cont_var (FILE *fp)
{
    char riga[STRLONG];
    int num_var, pos;

    num_reg_var=0;

    pos = ftell ( fp );
    for ( num_var=0; ; )
    {
      read_riga(fp,riga); 

       if ( ! strncmp( riga, "****", 4 ) )
         break;

       if( tipo_modello == REGOLAZIONE)
       {
          if( strstr(riga,PATREGVAR) != NULL )
             num_reg_var++ ;
       }
      
       num_var ++ ;

    }

    fseek ( fp, pos, 0 );
    return( num_var );
}

/* Lettura delle variabili di ogni blocco */
static int leggi_f01_var( MODELLO *task, FILE *fp )
{
  char riga[200];
  int  i, j, num_var,posreg;
  VAR  *var;

   /* lettura del nome del modello */
      read_riga(fp,riga); 
      strcpy(task->nome,riga);
      trim_blank(task->nome);

  /* Skip della riga di asterischi */
      read_riga(fp,riga); 

 /* Lettura delle variabili di ogni blocco */
  for ( i=0; ; i++ )
  {
    /* Lettura dell'intestazione del blocco */
      read_riga(fp,riga); 

    /* Controlla la corretta sequenza dei blocchi. */
    if ( strncmp( riga+14, (task->blocchi[i]).sigla_blocco, 4 ) ||
         strncmp( riga+32, (task->blocchi[i]).sigla_modulo, 4 ) )
    {
        printf("ERRORE SEQUENZA BLOCCHI IN MODELLO %s\n",task->nome);
    }


    if( !strncmp(riga+25,"REGOL.",6) )
        (task->blocchi[i]).tipo = REGOLAZIONE;
    else if( !strncmp(riga+25,"MODULO",6) )
        (task->blocchi[i]).tipo = PROCESSO;
    else
    {
        printf("ERRORE TIPO BLOCCHI IN MODELLO %s\n",task->nome);
    }

/*****
    tipo_modello = (task->blocchi[i]).tipo;
******/

     /* Memorizzazione label blocco */
    strncpy( (task->blocchi[i]).label, riga, 8 );
    (task->blocchi[i]).label[8] = '\0';

    /* Conteggio delle variabili */
    num_var = cont_var(fp);

    
    if( tipo_modello != REGOLAZIONE )
    {
       (task->blocchi[i]).num_variabili = num_var; 
       (task->blocchi[i]).variabili = var = (VAR *) calloc( num_var , sizeof( VAR ) );
    }
    else
    {
       (task->blocchi[i]).num_variabili = num_reg_var; 
       (task->blocchi[i]).variabili = var = (VAR *) calloc( num_reg_var , sizeof( VAR ) );
    }

    posreg=0;
    for ( j=0; j<num_var; j++ )
    {

       /* Lettura della riga corrente del file */
       read_riga(fp,riga); 

       if( tipo_modello == REGOLAZIONE )
       {
          if( strstr(riga,PATREGVAR) != NULL)
          {
             strncpy ( var[posreg].nome, riga, 8 );
             var[posreg].nome[8] = '\0';

             strncpy ( var[posreg].descr, riga + 17, 63 );
             var[posreg].descr[63] = '\0';

             var[posreg].connessioni = 0;

             if ( riga[12] != 'U' && riga[12] != 'I' )
             {
                printf("ERRORE TIPO VARIABILE %s del blocco %s%s\n",
                var[posreg].nome, (task->blocchi[i]).sigla_modulo,(task->blocchi[i]).sigla_blocco);
             }

             switch ( riga[13] )
             {
                case 'S':
                    var[posreg].tipo = STATO;
                break;
                case 'A':
                    var[posreg].tipo = USCITA;
                break;
                case 'N':
                    var[posreg].tipo = INGRESSO;
                break;
                default:
                    printf("ERRORE TIPO VARIABILE %s del blocco %s%s\n",
                    var[posreg].nome, (task->blocchi[i]).sigla_modulo,(task->blocchi[i]).sigla_blocco);
                break;
             }
        
             posreg++;
          }
       }
       else
       {
          strncpy ( var[j].nome, riga, 8 );
          var[j].nome[8] = '\0';

          strncpy ( var[j].descr, riga + 17, 63 );
          var[j].descr[63] = '\0';

          var[j].connessioni = 0;

          if ( riga[12] != 'U' && riga[12] != 'I' )
          {
             printf("ERRORE TIPO VARIABILE %s del blocco %s%s\n",
             var[j].nome, (task->blocchi[i]).sigla_modulo,(task->blocchi[i]).sigla_blocco);
          }

          switch ( riga[13] )
          {
             case 'S':
                 var[j].tipo = STATO;
             break;
             case 'A':
                 var[j].tipo = USCITA;
             break;
             case 'N':
                 var[j].tipo = INGRESSO;
             break;
             default:
                 printf("ERRORE TIPO VARIABILE %s del blocco %s%s\n",
                 var[j].nome, (task->blocchi[i]).sigla_modulo,(task->blocchi[i]).sigla_blocco);
             break;
          }
 
       }
    }

    /* Skip della riga di asterischi */
    read_riga(fp,riga); 

    /* Skip della riga di asterischi */
    read_riga(fp,riga); 
 
 
    /* Verifica della terminazione della seconda parte del file. */
    if ( ! strncmp( riga+10, ">>>>>>", 6 ) )
      break;
                        

   }

   if ( i+1 != task->num_blocchi )
     printf("ERRORE NUMERO BLOCCHI, HO CONTATO %d BLOCCHI E HO LETTO VARIABILI DI %d BLOCCHI\n",task->num_blocchi,i);
    
    return(TRUE);
}
        

/***
  scorre la lista degli ingressi 
***/
static LISTA_ING *search_ing(LISTA_ING *lista,char *ing )
{
  for ( ; lista; lista = lista->succ )
     if ( ! lista->visitato  &&  ! strcmp( lista->nome, ing ) )
     {
       lista->visitato = 1;
       return ( lista );
     }

  return( NULL );
}



static void libera ( lista )
LISTA_ING *lista;
{
  if ( lista )
    libera( lista->succ );
  free ( lista );
}
 


int make_connessione (MODELLO *task, int in_bl, int in_var, int out_bl, int out_var )
{

  CONN *new_con;

  /* Connessione ingresso uscita */
  new_con = (CONN*) calloc ( 1,sizeof( CONN ) );
  new_con->var_interna    = in_var;
  new_con->var_esterna    = out_var;
  new_con->blocco_esterno = out_bl;

  new_con->succ = (task->blocchi[in_bl]).variabili_connesse;
  (task->blocchi[in_bl]).variabili_connesse = new_con;
  ((task->blocchi[in_bl]).variabili[in_var]).connessioni = 1;

  /* Connessione uscita ingresso */
  new_con = (CONN*) calloc (1, sizeof( CONN ) );
  new_con->var_interna    = out_var;
  new_con->var_esterna    = in_var;
  new_con->blocco_esterno = in_bl;
  new_con->succ = (task->blocchi[out_bl]).variabili_connesse;
  (task->blocchi[out_bl]).variabili_connesse = new_con;
  ((task->blocchi[out_bl]).variabili[out_var]).connessioni ++;

}
 

static void ins_lista (LISTA_ING **lista, char *riga )
{
    LISTA_ING *new_entry;

    new_entry = (LISTA_ING*) calloc (1, sizeof( LISTA_ING ) );
    strncpy( new_entry->nome, riga, 8 );
    new_entry->nome[8]  = '\0';
    strncpy( new_entry->descr, riga+17, 63 );
    new_entry->descr[63]  = '\0';
    new_entry->succ     = *lista;
    new_entry->visitato = 0;
    *lista = new_entry;

}


/* Lettura degli ingressi di ogni blocco */
int leggi_f01_ing( MODELLO *task, FILE *fp )
{
  int       in_bl, out_bl, in_var, out_var;
  char      riga[STRLONG], ing[9], usc[9], mod[9];
  LISTA_ING *lista_ing=NULL, *lista_con=NULL, *ingresso;
  LISTA_ING *search_ing();

  for ( ;; )
  {
    if ( !fgets( riga, 85, fp ) )
    {
      if ( feof( fp) )
        break;
      else
      {
        printf("ERRORE LETTURA F01.dat DEL MODELLO %s\n",task->nome);
        return(FALSE);
      }
    }

    *((char*) strrchr(riga,'\n')) = '\0';

    if ( *riga == '*' )
      continue;

    if ( riga[12] == 'I' )
      ins_lista ( &lista_ing, riga );

    if ( riga[12] == 'C' )
      ins_lista ( &lista_con, riga );

  }

  for ( in_bl = 0; in_bl<task->num_blocchi; in_bl++ )
    for ( in_var=0; in_var<(task->blocchi[in_bl]).num_variabili; in_var++ )
       if ( ((task->blocchi[in_bl]).variabili[in_var]).tipo == INGRESSO  &&
            ((task->blocchi[in_bl]).variabili[in_var]).descr[0] != '#'  &&
            !search_ing( lista_ing, ((task->blocchi[in_bl]).variabili[in_var]).nome ) )
       {
         printf("ERRORE INPUT VARIABLE NOT FOUND");
       }


  for ( in_bl = 0; in_bl<task->num_blocchi; in_bl++ )
     for ( in_var=0; in_var<(task->blocchi[in_bl]).num_variabili; in_var++ )

        if ( (task->blocchi[in_bl]).variabili[in_var].descr[0] == '#' )
        {
          strncpy(ing, (((task->blocchi[in_bl]).variabili[in_var]).descr)+1, 8);
          ing[8] = '\0';
          strcpy (usc, ((task->blocchi[in_bl]).variabili[in_var]).nome );
          strncpy(mod, (((task->blocchi[in_bl]).variabili[in_var]).descr)+34, 8);
          mod[8]= '\0';

          if ( ! (ingresso = search_ing( lista_con, ing )) )
          {
            printf("ERRORE INCOGRUENCE IN CONNESSION");
            continue;
          }

          strcpy( ((task->blocchi[in_bl]).variabili[in_var]).nome, ingresso->nome);
          strcpy( ((task->blocchi[in_bl]).variabili[in_var]).descr, ingresso->descr);

          for ( out_bl=0; out_bl<task->num_blocchi; out_bl++ )
             if ( !strcmp ( (task->blocchi[out_bl]).label, mod ) )
               break;

          if ( out_bl == task->num_blocchi )
          {
            printf("MODULE %s INCONGRUENCE", mod);
            continue;
          }

          for ( out_var = 0;
                out_var < (task->blocchi[out_bl]).num_variabili;
                out_var++ )
             if ( ! strcmp( ((task->blocchi[out_bl]).variabili[out_var]).nome, usc ) )
               break;

          if ( out_var == (task->blocchi[out_bl]).num_variabili )
          {
            printf("ERRORE OUTPUT VARIABLE NOT FOUND, LA USCITA NON TROVATA E' %s\n",usc);
            continue;
          }

          make_connessione (task, in_bl, in_var, out_bl, out_var );

        }
 
/****
Questo loop verifica che esistano gli ingressi relativi 
alle connessioni interne al modello
****/

  for ( ingresso = lista_con; ingresso; ingresso = ingresso->succ )
    if ( ! ingresso->visitato )
    {
      printf("CONNESSION INCONGRUENCES entry 1\n");
    }


/********
Questo loop serve a controllare che gli ingressi letti siano
tutti inseriti nella lista degli ingressi posta alla fine
dell'f01. Avendo inserito il filtro in lettura per le variabili
relative a modelli di regolazione per questi ultimi non viene piu' 
effettuato
*********/

  if( tipo_modello == PROCESSO )
     for ( ingresso = lista_ing; ingresso; ingresso = ingresso->succ )
       if ( ! ingresso->visitato )
       {
         printf("Input Variables List Incongruences \n");
       }


  libera ( lista_ing );
  libera ( lista_con );
 
  return(TRUE);

}



/***
    lettura del file f01.dat
***/
int read_f01(MODELLO *task)
{
   char filename[STRLONG];
   char appo[100];
   FILE *f01;

   sprintf(filename,"%s/f01.dat",task->local_path);

   if( (f01=fopen(filename,"r")) == NULL)
   {
      printf("errore apertura file F01\n");
      fclose(f01); 
      return(FALSE);
   }
     
  tipo_modello = task->tipo_task;

  /* Lettura della prima parte del file F01 contenente la lista dei blocchi
   * con le loro descrizioni
   */
  if( leggi_f01_bl( task, f01 ) == FALSE)
  {
      printf("ERROR ON leggi_f01_bl\n");
      return(FALSE);
  }

  /* Lettura delle variabili del blocco */
  if( leggi_f01_var( task, f01 ) == FALSE)
  {
     printf("ERROR ON leggi_f01_var\n");
     return(FALSE);
  }
  
  /* Lettura degli ingressi del modulo */
  if( leggi_f01_ing ( task, f01 ) == FALSE)
  {
     printf("ERROR ON leggi_f01_ing\n");
     return(FALSE);
  }

  return(TRUE);
}

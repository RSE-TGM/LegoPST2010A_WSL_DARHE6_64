/**********************************************************************
*
*       C Source:               read_f01.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Nov  7 16:05:51 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: read_f01.c-3 %  (%full_filespec: read_f01.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)read_f01.c	2.25\t3/30/95";
/*
        Fine sezione per SCCS
*/



#include <stdio.h>
#include "lg1.h"
#include "errore.h"


#define READ_RIGA() \
  { \
    if ( !fgets( riga, 85, f01 ) ) \
      { \
        err_level = ERROR; \
        if ( feof( f01) ) \
          errore ( EOF_F01_ERR, modello.nome ); \
        else \
          errore ( READ_F01_ERR, modello.nome ); \
        return; \
      } \
    \
    *((char*) strrchr(riga,'\n')) = '\0'; \
  }


extern ERR_LEVEL err_level;

static ins_lista ();

static FILE *f01;



read_f01()
{
  char path[1024];


  /* Apertura del file F01 */
  strcpy ( path, modello.path_legocad );
  strcat ( path, modello.nome );
  strcat ( path, "/f01.dat" );
  if ( !(f01=fopen (  path, "r" )) )
  {
    /** siamo nel caso di un nuovo modello ***/
    return;
  }


  /* Lettura della prima parte del file F01 contenente la lista dei blocchi
   * con le loro descrizioni
   */
  leggi_f01_bl ();



  if ( err_level == ERROR )
  {
    fclose(f01);
    return;
  }



  if ( num_blocchi == 0 )
  {
    fclose(f01);
    return;
  }



  /* Lettura delle variabili di ogni blocco */
  leggi_f01_var ();



  if ( err_level == ERROR )
  {
    fclose(f01);
    return;
  }



  /* Lettura degli ingressi del modulo */
  leggi_f01_ing ();


  if ( err_level == WARNING )
  { 
    err_level = ERROR;
    errore( "Found warnings parsing F01 file" );
    fclose(f01);
    return;
  }


  fclose(f01);

}



/* Lettura della prima parte del file F01 contenente la lista dei blocchi
 * con le loro descrizioni
 */
leggi_f01_bl ()
{

  char riga[86];
  int  i;


  /* Skip della riga di asterischi */
  READ_RIGA();




  /* Lettura della prima parte del file F01 contenente la lista dei blocchi
   * con le loro descrizioni
   */
  for ( num_blocchi=0; ; )
  {

     /* Lettura della riga corrente del file */
     READ_RIGA();
       

     /* Controlla se e' terminata la prima parte del file F01 */
     if ( ! strncmp ( riga, "****", 4 ) ) 
       break;
  

     /* Prima degli asterischi ci devono essere solo righe contenenti
      * la keyword BLOCCO.
      */
     if ( strncmp ( riga+10, "BLOCCO", 6 ) )
     {
       err_level = ERROR;
       errore ( FORMATO_F01_ERR, modello.nome );
       return;
     }


     /* Controlla lo sforamento per il vettore dei blocchi. */
     if ( num_blocchi == MAX_BLOCCHI )
     {
       err_level = ERROR;
       errore ( MAX_BL_ERR, modello.nome, MAX_BLOCCHI );
       return;
     }


     /* Sistema i campi del descrittore del blocco tranne quelli riguardanti
      * le variabili i quali verranno sistemati successivamente.
      */

     strncpy( blocchi[num_blocchi].sigla_modulo, riga, 4 );
     blocchi[num_blocchi].sigla_modulo[4] = '\0';

     strncpy( blocchi[num_blocchi].sigla_blocco, riga+18, 4 );
     blocchi[num_blocchi].sigla_blocco[4] = '\0';

     strncpy( blocchi[num_blocchi].descr_blocco, riga+26, 54 );
     blocchi[num_blocchi].descr_blocco[54] = '\0';
     blocchi[num_blocchi].variabili_connesse = NULL;


     /* Controlla l'esistenza in libreria del modulo associato al blocco */
     for ( i=0; i<num_tot_moduli; i++ )
       if ( !strncmp(riga, moduli[i].sigla, 4 ) )
         break;

     if ( i == num_tot_moduli )
       {
         err_level = WARNING;
         errore ( NO_MODULO_ERR, blocchi[num_blocchi].sigla_modulo );
       }
     else
       {
         blocchi[num_blocchi].tipo   = moduli[i].tipo;  
         blocchi[num_blocchi].modulo = i;  
       }


     num_blocchi++;
  }
  if( err_level == WARNING)
       {
         err_level = FATAL_ERROR;
         errore ( "Module used in this model not in library. See librarian." );
       }
}



/* Lettura delle variabili di ogni blocco */
leggi_f01_var ()
{

  char riga[86];
  int  i, j, num_var;
  VAR  *var;


  /* Skip del nome del modello */
  READ_RIGA();

  /* Skip della riga di asterischi */
  READ_RIGA();

  /* Lettura delle variabili di ogni blocco */
  for ( i=0; ; i++ )
  {
    /* Lettura dell'intestazione del blocco */
    READ_RIGA();

    /* Controlla la corretta sequenza dei blocchi. */
    if ( strncmp( riga+14, blocchi[i].sigla_blocco, 4 ) ||
         strncmp( riga+32, blocchi[i].sigla_modulo, 4 ) )
    {
       riga[8]  = '\0';
       riga[36] = '\0';
       err_level = WARNING;
       errore ( BL_SEQ_ERR, riga, riga+32 );
    }

    if( !strncmp(riga+25,"REGOL.",6) )
        blocchi[i].tipo = REGOLAZIONE;
    else if( !strncmp(riga+25,"MODULO",6) )
        blocchi[i].tipo = PROCESSO;
    else
    {
        err_level = ERROR;
        errore( BL_SEQ_ERR,riga+26);
    }


    /* Memorizzazione label blocco */
    strncpy( blocchi[i].label, riga, 8 );
    blocchi[i].label[8] = '\0';


    /* Conteggio delle variabili */
    num_var = cont_var ();


    /* Allocazione del vettore delle variabili. */
    blocchi[i].num_variabili = num_var;
    blocchi[i].variabili = var = (VAR *) calloc( num_var , sizeof( VAR ) );


    for ( j=0; j<num_var; j++ )
    {

       /* Lettura della riga corrente del file */
       READ_RIGA();

       strncpy ( var[j].nome, riga, 8 );
       var[j].nome[8] = '\0';
     
       strncpy ( var[j].descr, riga + 17, 63 );
       var[j].descr[63] = '\0';
 
       var[j].connessioni = 0;

       if ( riga[12] != 'U' && riga[12] != 'I' )
       {
         err_level = WARNING;
         errore( TIPO_VAR_ERR, var[j].nome,
                 blocchi[i].sigla_modulo, blocchi[i].sigla_blocco);
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
                    err_level = WARNING;
                    errore(TIPO_VAR_ERR, var[j].nome,
                           blocchi[i].sigla_modulo, blocchi[i].sigla_blocco);
                    break;
       }
 
       
    }

    /* Skip della riga di asterischi */
    READ_RIGA();

    /* Skip della riga di asterischi */
    READ_RIGA();

    /* Verifica della terminazione della seconda parte del file. */
    if ( ! strncmp( riga+10, ">>>>>>", 6 ) )
      break;

  }

  if ( i+1 != num_blocchi )
  {
    err_level = ERROR;
    errore ( DIFF_BL_CONT_ERR, num_blocchi, i );
  }
}


typedef struct _tag_lista_ing {
                    char                  nome[9];
                    char                  descr[64];
                    int                   visitato;
                    struct _tag_lista_ing *succ;
} LISTA_ING;

static LISTA_ING *search_ing( LISTA_ING *, char * );
static libera ( LISTA_ING * );


leggi_f01_ing ()
{

  int       in_bl, out_bl, in_var, out_var;
  char      riga[85], ing[9], usc[9], mod[9];
  LISTA_ING *lista_ing=NULL, *lista_con=NULL, *ingresso;
  LISTA_ING *search_ing();


  for ( ;; )
  {
    if ( !fgets( riga, 85, f01 ) ) 
    { 
      if ( feof( f01) ) 
        break;
      else 
      { 
        err_level = ERROR; 
        errore ( READ_F01_ERR, modello.nome ); 
        return; 
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


  for ( in_bl = 0; in_bl<num_blocchi; in_bl++ )
    for ( in_var=0; in_var<blocchi[in_bl].num_variabili; in_var++ )
       if ( blocchi[in_bl].variabili[in_var].tipo == INGRESSO  &&
            blocchi[in_bl].variabili[in_var].descr[0] != '#'  &&
            !search_ing( lista_ing, blocchi[in_bl].variabili[in_var].nome ) )
       {
         err_level = WARNING;
         errore("input variable not found");
       }


  for ( in_bl = 0; in_bl<num_blocchi; in_bl++ )
     for ( in_var=0; in_var<blocchi[in_bl].num_variabili; in_var++ )

        if ( blocchi[in_bl].variabili[in_var].descr[0] == '#' )
        {

          strncpy(ing, (blocchi[in_bl].variabili[in_var].descr)+1, 8);
          ing[8] = '\0';
          strcpy (usc, blocchi[in_bl].variabili[in_var].nome );
          strncpy(mod, (blocchi[in_bl].variabili[in_var].descr)+34, 8);
          mod[8]= '\0';

          if ( ! (ingresso = search_ing( lista_con, ing )) )
          {
            err_level = WARNING; 
            errore("incogruence in connession");
            continue;
          }

          strcpy(blocchi[in_bl].variabili[in_var].nome, ingresso->nome);
          strcpy(blocchi[in_bl].variabili[in_var].descr, ingresso->descr);
            
          for ( out_bl=0; out_bl<num_blocchi; out_bl++ )
             if ( !strcmp ( blocchi[out_bl].label, mod ) )
               break;
   
          if ( out_bl == num_blocchi )
          {
            err_level = WARNING; 
            errore("module %s incongruence", mod);
            continue;
          }
                 
          for ( out_var = 0;
                out_var < blocchi[out_bl].num_variabili;
                out_var++ ) 
             if ( ! strcmp( blocchi[out_bl].variabili[out_var].nome, usc ) )
               break;

          if ( out_var == blocchi[out_bl].num_variabili )
          {
            err_level = WARNING; 
            errore("output variable not found");
            printf("La uscita non trovata e' %s\n",usc);
            continue;
          }

          make_connessione ( in_bl, in_var, out_bl, out_var );

        }      

  for ( ingresso = lista_con; ingresso; ingresso = ingresso->succ )
    if ( ! ingresso->visitato )
    {
      err_level = WARNING;
      errore("connession incogruences");
    }


  for ( ingresso = lista_ing; ingresso; ingresso = ingresso->succ )
    if ( ! ingresso->visitato )
    {
      err_level = WARNING;
      errore("connession incongruences");
    }

  libera ( lista_ing );
  libera ( lista_con );
}






static ins_lista ( lista, riga )
LISTA_ING **lista;
char *riga;
{
    LISTA_ING *new_entry;

    new_entry = (LISTA_ING*) calloc (1, sizeof( LISTA_ING ) );
    strncpy( new_entry->nome, riga, 8 );
    new_entry->nome[8]  = '\0';
    strncpy( new_entry->descr, riga+17, 63 );
    new_entry->nome[63]  = '\0';
    new_entry->succ     = *lista;
    new_entry->visitato = 0;
    *lista = new_entry;

}



static LISTA_ING *search_ing( lista, ing )
LISTA_ING *lista;
char *ing;
{
  for ( ; lista; lista = lista->succ )
     if ( ! lista->visitato  &&  ! strcmp( lista->nome, ing ) ) 
     {
       lista->visitato = 1;
       return ( lista );
     }

  return( NULL );
}



static libera ( lista )
LISTA_ING *lista;
{
  if ( lista )
    libera( lista->succ );
  free ( lista );
}


/* Conteggio delle variabili */
int cont_var ()
{
    int num_var, pos;
    char riga[86];

    pos = ftell ( f01 );
    for ( num_var=0; ; )
    {
       READ_RIGA();

       if ( ! strncmp( riga, "****", 4 ) )
         break;

       num_var ++ ;
    }

    fseek ( f01, pos, 0 );     
    return( num_var );
}


make_connessione ( in_bl, in_var, out_bl, out_var )
int in_bl, in_var, out_bl, out_var;
{

  CONN *new_con;

  /* Connessione ingresso uscita */
  new_con = (CONN*) calloc ( 1,sizeof( CONN ) );
  new_con->var_interna    = in_var;
  new_con->var_esterna    = out_var;
  new_con->blocco_esterno = out_bl;

  new_con->succ = blocchi[in_bl].variabili_connesse;
  blocchi[in_bl].variabili_connesse = new_con;
  blocchi[in_bl].variabili[in_var].connessioni = 1;

  /* Connessione uscita ingresso */
  new_con = (CONN*) calloc (1, sizeof( CONN ) );
  new_con->var_interna    = out_var;
  new_con->var_esterna    = in_var;
  new_con->blocco_esterno = in_bl;
  new_con->succ = blocchi[out_bl].variabili_connesse;
  blocchi[out_bl].variabili_connesse = new_con;
  blocchi[out_bl].variabili[out_var].connessioni ++;
}



delete_connessione( bl, var, conn )
int bl, var, conn;
{
   CONN *cor, *prec;
   int  i, sec_bl, sec_var;

   for ( i=0, prec=NULL, cor=blocchi[bl].variabili_connesse;
         ;
         prec=cor, cor=cor->succ )
     if ( cor->var_interna == var )
       if ( ++i == conn )
         break;

   sec_bl = cor->blocco_esterno;
   sec_var = cor->var_esterna;

   if ( !prec )
   {
     blocchi[bl].variabili_connesse = cor->succ;
     free ( cor );
   }
   else
   {
     prec->succ = cor->succ;
     free ( cor );
   }

   blocchi[bl].variabili[var].connessioni --;

   for ( prec=NULL, cor=blocchi[sec_bl].variabili_connesse;
         cor;
         prec=cor, cor=cor->succ )
      if ( cor->blocco_esterno == bl  &&  cor->var_esterna == var )
        break;

   if ( !prec )
   {
     blocchi[sec_bl].variabili_connesse = cor->succ;
     free ( cor );
   }
   else
   {
     prec->succ = cor->succ;
     free ( cor );
   }  

   blocchi[sec_bl].variabili[sec_var].connessioni --;
}

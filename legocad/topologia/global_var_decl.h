/**********************************************************************
*
*       C Header:               global_var_decl.h
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Jul 20 12:01:08 2001 %
*
**********************************************************************/


#include <stdio.h>
#include "lg1.h"
#include "errore.h"


#define read_riga \
  if ( !fgets( riga, 85, f01 ) ) \
    { \
      err_level = ERROR; \
      if ( feof( f01) ) \
        errore ( EOF_F01_ERR, modello.nome ); \
      else \
        errore ( READ_F01_ERR, modello.nome ); \
      return; \
    }


#define MAX_BLOCCHI 1000
#define MAX_MODULI  300

typedef struct _tag_modello {
         char nome[80];
         char path_legocad[1024];
} MODELLO;
typedef struct _tag_modulo {
        TIPO_MOD tipo;
        char     sigla[5];
} MODULO;

MODELLO modello;
BLOCCO  blocchi[MAX_BLOCCHI];
MODULO  moduli[MAX_MODULI];
int     num_blocchi;
int     num_moduli;


extern ERR_LEVEL err_level;




init_modello(nome_modello, path_legocad)
char *nome_modello, *path_legocad;
{

   err_level = NO_ERROR;

   libera_modello( num_blocchi, blocchi, num_moduli, moduli );
   num_blocchi = num_moduli = 0;

   strcpy(modello.nome, nome_modello);
   strcpy(modello.path_legocad, path_legocad);
   if ( modello.path_legocad[strlen(modello.path_legocad)-1] != '/' )
     strcat ( modello.path_legocad, "/" );

   read_moduli( modello, &num_moduli, moduli );

   if (err_level == NO_ERROR)
     read_f01( modello, &num_blocchi, blocchi, num_moduli, moduli );

   if (err_level == ERROR)
   {
     libera_modello( num_blocchi, blocchi, num_moduli, moduli );
     num_blocchi = num_moduli = 0;
   }

}




read_moduli( modello, num_moduli, moduli )
MODELLO modello;
int     *num_moduli;
MODULO  moduli[];
{
  FILE *lis_mod;
  char path[1024];


  /* Apertura del file lista_moduli.dat. */
  strcpy( path, modello.path_legocad );
  strcat( path, "libut/lista_moduli.dat" );
  if ( !(lis_mod=fopen ( path, "r" )) )
  {
    err_level = ERROR;
    errore ( OPEN_LIS_MOD_ERR, modello.nome );
    return;
  }
   
  get_moduli( lis_mod, num_moduli, moduli );


  /* Apertura del file lista_schemi.dat. */
  strcpy( path, modello.path_legocad );
  strcat( path, "libut_reg/lista_schemi.dat" );
  if ( !(lis_mod=fopen ( path, "r" )) )
  {
    err_level = ERROR;
    errore ( OPEN_LIS_SCH_ERR, modello.nome );
    return;
  }
   
  get_moduli( lis_mod, num_moduli, moduli );


}



get_moduli( lis_mod, num_moduli, moduli )
FILE    *lis_mod;
int     *num_moduli;
MODULO  moduli[];
{
   char riga[85];

   for ( ;; (*num_moduli)++ )
   {
   
      if ( fgets( riga, 85, lis_mod ) )
      {
        if ( *num_moduli == MAX_MODULI )
        {
          err_level = ERROR;
          errore ( MAX_MOD_ERR, modello.nome );
          return;
        }

        strcpy ( moduli[*num_moduli].sigla, riga, 4 );
        moduli[*num_moduli].sigla[4] = '\0';  
      }
      else
        break;

   }

}






read_f01( modello, num_blocchi, blocchi, num_moduli, moduli )
MODELLO modello;
int     *num_blocchi;
BLOCCO  blocchi[];
int     num_moduli;
MODULO  moduli[];
{
  FILE *f01;
  char path[1024];


  /* Apertura del file F01 */
  strcpy ( path, modello.path_legocad );
  strcat ( path, modello.nome );
  strcat ( path, "/f01.dat" );
  if ( !(f01=fopen (  path, "r" )) )
  {
    err_level = ERROR;
    errore ( OPEN_F01_ERR, modello.nome );
    return;
  }


  /* Lettura della prima parte del file F01 contenente la lista dei blocchi
   * con le loro descrizioni
   */
  leggi_f01_bl ( f01, modello, num_blocchi, blocchi, num_moduli, moduli );



  if ( err_level == ERROR )
    return;



  if ( *num_blocchi == 0 )
    return;



  /* Lettura delle variabili di ogni blocco */
  leggi_f01_var ( f01, modello, *num_blocchi, blocchi );



  if ( err_level == WARNING )
  { 
    err_level = ERROR;
    errore( "Found warnings parsing F01 file" );
    return;
  }


}












/* Lettura della prima parte del file F01 contenente la lista dei blocchi
 * con le loro descrizioni
 */
leggi_f01_bl ( f01, modello, num_blocchi, blocchi, num_moduli, moduli )
FILE    *f01;
MODELLO modello;
int     *num_blocchi;
BLOCCO  blocchi[];
int     num_moduli;
MODULO  moduli[];
{

  char riga[86];
  int  i;


  /* Skip della riga di asterischi */
  read_riga




  /* Lettura della prima parte del file F01 contenente la lista dei blocchi
   * con le loro descrizioni
   */
  for ( *num_blocchi=0; ; )
  {


     /* Lettura della riga corrente del file */
     read_riga
       

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
     if ( *num_blocchi == MAX_BLOCCHI )
     {
       err_level = ERROR;
       errore ( MAX_BL_ERR, modello.nome, MAX_BLOCCHI );
       return;
     }



     /* Sistema i campi del descrittore del blocco tranne quelli riguardanti
      * le variabili i quali verranno sistemati successivamente.
      */

     strncpy( blocchi[*num_blocchi].sigla_modulo, riga, 4 );
     blocchi[*num_blocchi].sigla_modulo[4] = '\0';

     strncpy( blocchi[*num_blocchi].sigla_blocco, riga+18, 4 );
     blocchi[*num_blocchi].sigla_blocco[4] = '\0';

     strncpy( blocchi[*num_blocchi].descr_blocco, riga+26, 54 );
     blocchi[*num_blocchi].descr_blocco[54] = '\0';

     blocchi[*num_blocchi].variabili_connesse = NULL;



     /* Controlla l'esistenza in libreria del modulo associato al blocco */
     for ( i=0; i<num_moduli; i++ )
       if ( !strncmp(riga, moduli[i].sigla, 4 ) )
         break;

     if ( i == num_moduli )
       {
         err_level = WARNING;
         errore ( NO_MODULO_ERR, blocchi[*num_blocchi].sigla_modulo );
       }
     else
       {
         blocchi[*num_blocchi].tipo   = moduli[i].tipo;  
         blocchi[*num_blocchi].modulo = i;  
       }



     (*num_blocchi)++;


  }
     

}









/* Lettura delle variabili di ogni blocco */
leggi_f01_var ( f01, modello, num_blocchi, blocchi )
FILE    *f01;
MODELLO modello;
int     num_blocchi;
BLOCCO  blocchi[];
{

  char riga[86];
  int  i, j, num_var;
  VAR  *var;



  /* Skip del nome del modello */
  read_riga


  /* Skip della riga di asterischi */
  read_riga



  /* Lettura delle variabili di ogni blocco */
  for ( i=0; ; i++ )
  {
 

    /* Lettura dell'intestazione del blocco */
    read_riga


    /* Controlla la corretta sequenza dei blocchi. */
    if ( strncmp( riga+4, blocchi[i].sigla_blocco, 4 ) ||
         strncmp( riga, blocchi[i].sigla_modulo, 4 ) )
    {
       riga[8]  = '\0';
       riga[36] = '\0';
       err_level = WARNING;
       errore ( BL_SEQ_ERR, riga, riga+32 );
    }


    /* Conteggio delle variabili */
    num_var = cont_var ( f01, modello );


    /* Allocazione del vettore delle variabili. */
    blocchi[i].num_variabili = num_var;
    blocchi[i].variabili = var = (VAR *) malloc ( num_var * sizeof( VAR ) );


    for ( j=0; j<num_var; j++ )
    {

       /* Lettura della riga corrente del file */
       read_riga

       strncpy ( var[j].nome, riga, 8 );
       var[j].nome[8] = '\0';
     
       strncpy ( var[j].descr, riga + 17, 63 );
       var[j].descr[63] = '\0';
 
       var[j].connessione = NULL;

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
                    errore ( TIPO_VAR_ERR, var[j].nome,
                             blocchi[i].sigla_modulo, blocchi[i].sigla_blocco);
                    break;
       }
 
       
    }

    /* Skip della riga di asterischi */
    read_riga

    /* Skip della riga di asterischi */
    read_riga

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




/*



{
   for ( in_bl = 0; in_bl<num_blocchi; in_bl++ )
      for ( in_var=0; in_var<blocchi[in_bl].num_variabili; in_var++ )
         if ( blocchi[in_bl].variabili[in_var].descr[0] == '#' )
           {
             strncpy(ing, (blocchi[in_bl].variabili[in_var].descr)+1, 8);
             ing[8] = '\0';
             strcpy (usc, blocchi[in_bl].variabili[in_var].nome );
             strncpy(mod, (blocchi[in_bl].variabili[in_var].descr)+34, 4);
             mod[5]= '\0';
             strncpy(bl, (blocchi[in_bl].variabili[in_var].descr)+34, 4);
             bl[5]= '\0';
             if ( ! search_and_del_var( conn_list, ing, &ingresso ) )
             {
               errore();
               goto continua;
             }
             strcpy(blocchi[in_bl].variabili[in_var].nome, ingresso->nome);
             strcpy(blocchi[in_bl].variabili[in_var].descr, ingresso->descr);
               
             for ( out_bl=0; out_bl<num_blocchi; out_bl++ )
                if ( strcmp ( blocchi[out_bl].sigla_modulo, mod ) &&
                     strcmp ( blocchi[out_bl].sigla_blocco, bl ) )
                  break;
    
             if ( out_bl == num_blocchi )
             {
               errore();
               goto continua;
             }
                 

             for ( out_var = 0;
                   out_var < blocchi[out_bl].num_variabili;
                   out_var++ ) 
                if ( strcmp( blocchi[in_bl].variabili[in_var].nome, usc ) 
                  break;


             if ( out_var == blocchi[out_bl].num_variabili )
             {
               errore();
               goto continua;
             }

             make_conn ( in_bl, in_var, out_bl, out_var );

           }      

   if ( conn )
     errore();


   for ( in_bl = 0; in_bl<num_blocchi; in_bl++ )
   {
      for ( in_var=0; in_var<blocchi[in_bl].num_variabili; in_var++ )
         if ( ! search_and_del_var( ing_list, blocchi[in_bl].variabili[in_var],
                                    &ingresso ) )
           break;

      if ( in_bl==num_blocchi )
        errore();
   }

}


*/



/* Conteggio delle variabili */
int cont_var ( f01, modello )
FILE *f01;
MODELLO modello;
{
    int num_var, pos;
    char riga[86];


    pos = ftell ( f01 );

    for ( num_var=0; ; )
    {
       read_riga

       if ( ! strncmp( riga, "****", 4 ) )
         break;

       num_var ++ ;
    }

    fseek ( f01, pos, 0 );     
       
    return( num_var );

}







libera_modello( num_blocchi, blocchi, num_moduli, moduli )
int     num_blocchi;
BLOCCO  blocchi[];
int     num_moduli;
MODULO  moduli[];
{
}


/*
 * pagcompiler.c
 *
 * Description:
 *
 * compiled resource builder.
 *
 * Date:
 *
 * 1997-07-18
 *
 * Functions:
 *
 * FetchAttribs
 * PagCompiler
 */
# include "widgets.h"
# include "edfdb.h"
# include "util.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <ndbm.h>
# include <errno.h>
# include <malloc.h>
# define KWNUM 4
# define DIM_CACHE 1000
# define LAST_CACHEITEM ( DIM_CACHE - 1 )
static struct Edf * Cache [ DIM_CACHE + 1 ] ;
static const char Help [ ] = "\n\
pagcompiler  - compila basename.pag in basename.rtf.\n\
\n\
Uso:  pagcompiler  basename\n";
/*--------------------------------variabile-blocco---task------------------
*26w27c.varInputCambioColore2:  U20ZKYGT  G604KYGT GTSREG0 NOP 1.0 0.0 ---*/
static void FetchAttribs ( char * CompiledString ,
                           struct WidgetAttrib * Attribs ,
                           DBM * dbmHandle ) ;
static void FetchAttribs ( char * CompiledString ,
                           struct WidgetAttrib * Attribs ,
                           DBM * dbmHandle )
  {
  struct WidgetAttrib * CurrentAttrib = Attribs -> Next ;
# ifdef DEBUG
  DEBUG_ENTERFUNC("FetchAttributes");
# endif
  while ( CurrentAttrib != NULL )
    {
    struct Edf Data ;
    char KeyString [ KEYSTRINGDIM ] ;
    char ConString [ CONSTRINGDIM ] ;
    static char Input1String [ 200 ] = " | -1 -1 -1 0 0 1.000000 0.000000 -- |" ,
                Input2String [ 200 ] = " | -1 -1 -1 0 0 1.000000 0.000000 -- |" ,
                OutputString [ 200 ] = " | -1 -1 -1 0 0 1.000000 0.000000 -- | | -1 -1 -1 0 0 1.000000 0.000000 -- |" ;
    datum Key ;
    datum Con ;
    datum Rkey ;
    int dbmErr ;
    int i = 0 ;
    memset ( & Data ,
             0 ,
             sizeof ( struct Edf ) ) ;
    /* || strcmp ( "varInputCambioColore2" ,
                     CurrentAttrib -> Name ) == 0
         || strcmp ( "varOutput" ,
                     CurrentAttrib -> Name ) == 0 */
    if ( strcmp ( "varInputCambioColore1" ,
                  CurrentAttrib -> Name ) == 0 )
      {
      static int First1 = 0 ;
      struct Edf * CacheCursor = 0 ;
      int FoundInCache = 0 ;
      int j = sscanf ( CurrentAttrib -> Value ,
                       "%s %s %s" ,
                       Data . VarName ,
                       Data . Block ,
                       Data . Model ) ;
      if ( j < 3 )
        {
        CurrentAttrib = CurrentAttrib -> Next ;
        continue ;
        }
      /**/
      /* Look in Cache. */
    for ( i = 0 ,
          CacheCursor = Cache [ i ] ;
            CacheCursor != 0 ;
              CacheCursor = Cache [ ++ i ] )
      {
      if ( strcmp ( CacheCursor -> Model ,
                    Data . Model ) == 0
           && strcmp ( CacheCursor -> Block ,
                       Data . Block ) == 0
           && strcmp ( CacheCursor -> VarName ,
                       Data . VarName ) == 0 )
        {
        if ( CacheCursor -> Tagged )
          {
          struct Edf * Saved = CacheCursor ;
          memmove ( & Cache [ 1 ] ,
                    & Cache [ 0 ] ,
                    i * sizeof ( struct Edf * ) ) ;
          Cache [ 0 ] = Saved ;
          if ( i > First1 )
            {
            ++ First1 ;
            }
          }
        else
          {
          struct Edf * Saved = CacheCursor ;
          memmove ( & Cache [ First1 + 1 ] ,
                    & Cache [ First1 ] ,
                    ( i - First1 ) * sizeof ( struct Edf * ) ) ;
          Cache [ First1 ] = Saved ;
          if ( First1 )
            {
            -- First1 ;
            }
          }
        FoundInCache = 1 ;
        }
      }
    if ( FoundInCache )
      {
      printf ( "found in cache\n" ) ;
      printf ( "In Cache: %s/%s/%s\n"
               "Tagged: %d\n"
               "Offset: %d\n" ,
               CacheCursor -> Model ,
               CacheCursor -> Block ,
               CacheCursor -> VarName ,
               CacheCursor -> Tagged ,
               CacheCursor -> Offset ) ;
      CurrentAttrib = CurrentAttrib -> Next ;
      continue ;
      }
    CreateKeyString ( KeyString ,
                      & Data ) ;
    Key . dptr = KeyString ;
    Key . dsize = KEYSTRINGDIM ;
    errno = 0 ;
    Con = dbm_fetch ( dbmHandle ,
                      Key ) ;
    memset ( ConString ,
             0 ,
             sizeof ( ConString ) ) ;
    if ( Con . dptr != NULL )
      {
      strncpy ( ConString ,
                Con . dptr ,
                Con . dsize ) ;
      SplitConString ( ConString ,
                       & Data ) ;
      printf ( "In db: %s/%s/%s\n"
               "Tagged: %d\n"
               "Offset: %d\n" ,
               Data . Model ,
               Data . Block ,
               Data . VarName ,
               Data . Tagged ,
               Data . Offset ) ;
      if ( Data . Tagged )
        {
        /* Priority 0. */
        free ( Cache [ LAST_CACHEITEM ] ) ;
        memmove ( & Cache [ 1 ] ,
                  & Cache [ 0 ] ,
                  DIM_CACHE * sizeof ( struct Edf * ) ) ;
        Cache [ 0 ] = ( struct Edf * ) malloc ( sizeof ( struct Edf ) ) ;
        memcpy ( Cache [ 0 ] ,
                 & Data ,
                 sizeof ( struct Edf ) ) ;
        if ( First1 < LAST_CACHEITEM )
          {
          ++ First1 ;
          }
        }
      else
        {
        /* Priority 1. */
        free ( Cache [ LAST_CACHEITEM ] ) ;
        memmove ( & Cache [ First1 + 1 ] ,
                  & Cache [ First1 ] ,
                  ( DIM_CACHE - First1 ) * sizeof ( struct Edf * ) ) ;
        Cache [ First1 ] = ( struct Edf * ) malloc ( sizeof ( struct Edf ) ) ;
        memcpy ( Cache [ First1 ] ,
                 & Data ,
                 sizeof ( struct Edf ) ) ;
        if ( First1 )
          {
          -- First1 ;
          }
        }
      }
    else
      {
      printf ( "Non trovato in db" ) ;
      }
      /**/
      }
    CurrentAttrib = CurrentAttrib -> Next ;
    }
  }
int PagCompiler ( char * CompiledString ,
                  struct WidgetAttrib * Attribs )
  {
  DBM * dbmHandle ;
  char dbmName [ ] = "edfdb" ;    /* dbm basename                 */
  int dbmFlags ;
  int dbmMode ;
# ifdef DEBUG
  DEBUG_ENTERFUNC("PagCompiler");
# endif
  errno = 0 ;
  dbmFlags = S_IRUSR
             | S_IWUSR
             | S_IRGRP
             | S_IROTH ;
  dbmMode = O_RDWR
            | O_CREAT ;
  dbmHandle = dbm_open ( dbmName ,
                         dbmMode ,
                         dbmFlags ) ;   /* manpage errata ! */
  if ( dbmHandle == 0 )
    {
    fprintf ( stderr ,
              "Impossibile aprire edfdb  - errno: %d\n" ,
              errno ) ;
    return - 1 ;
    }
  FetchAttribs ( CompiledString ,
                 Attribs ,
                 dbmHandle ) ;
  dbm_close ( dbmHandle ) ;
  return 0 ;
  }
/* EOF. */

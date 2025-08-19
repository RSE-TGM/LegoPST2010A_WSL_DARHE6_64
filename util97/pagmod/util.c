/*
 * util.c
 *
 * Description:
 *
 * Contains utility functions used in various pagmod modules.
 *
 * Date:
 *
 * 1997-07-18
 *
 * Functions:
 *
 * Chop
 * Malloc
 * CopyField
 * CopyPipeField
 * SkipPipeFields
 * SkipFields
 * SkipWhiteSpaces
 * OpenFile
 * CloseFile
 */

# include "util.h"

# include <stdio.h>

# include <malloc.h>

# include <stdlib.h>

# include <ctype.h>

# include <string.h>

# include <errno.h>

char * PageFileName = NULL ;

char help_V [ ] = "pagmod: Versione 1.4 - 1997-07-18" ;

int ExitAfterScanScript = 0 ;

int QuietMode = 0 ; 

int DoNotWriteModFile = 0 ;

int UseListFileName = 0 ;

int UsePageFileName = 0 ;

int BehaveAsFilter = 0 ;

# ifdef DEBUG
char * DebugPattern = NULL ;
# endif

int DoGrep = 0 ;

int DoAfterGrep = 0 ;

int AskConfirm = 0 ;

int Kchg = 0 ; /* @/ ChangeAttribs counter. */

int Knew = 0 ; /* @> NewAttribs counter. */

int Krep = 0 ; /* @* CompiledReplace counter. */

int Kins = 0 ; /* @! CompiledInsert counter. */

int Kadd = 0 ; /* @+ CompiledAdd counter. */

int Ktot = 0 ; /* @# Total counter. */

int Gpag = 0 ; /* */

int Gtot = 0 ; /* */

void Chop ( char * const String ) {
/*
 * Pop the newline of String.
 */
 
  char * NewLineChar = NULL ;
  
# ifdef DEBUG
  DEBUG_ENTERFUNC("Chop");
# endif
  
  NewLineChar = strchr ( String ,
                         LF ) ;
  if ( NewLineChar ) {
  
    * NewLineChar = '\0' ;
  
  }

}

void * Malloc ( size_t size ) {
/*
 * Call malloc to allocate size bytes of memory.
 * If memory allocation fails, exit with failure.
 *
 * Return:  address of allocated memory.
 */
 
  void * ptr = NULL ;
  
# ifdef DEBUG
  DEBUG_ENTERFUNC("Malloc");
# endif
  
  ptr = malloc ( size ) ;

  if ( ptr == NULL ) {

    sprintf ( pagmod_logbf ,
              "Errore: Memoria insufficiente ( %ld bytes ) !" ,
              size ) ;

    pagmod_log ( pagmod_logbf ) ;

    fprintf ( stderr ,
              "%s\n" ,
              pagmod_logbf ) ;

    exit ( EXIT_FAILURE ) ;

  }

  return ptr ;

}

void CopyField ( char * * Cursor ,
                 char * Dest ) {

# ifdef DEBUG
  DEBUG_ENTERFUNC("CopyField");
# endif

  while ( ( ! isspace ( * * Cursor ) )
          && * * Cursor != '\0' ) {
  
    * Dest = * * Cursor ;
  
    ++ * Cursor ;
    
    ++ Dest ;
  
  }
  
  * Dest = '\0' ;

}

void CopyPipeField ( char * * Cursor ,
                     char * Dest ) {
  
# ifdef DEBUG
  DEBUG_ENTERFUNC("CopyPipeField");
# endif
  
  ++ * Cursor ;

  while ( * * Cursor != '|' ) {
  
    * Dest = * * Cursor ;
    
    ++ * Cursor ;
    
    ++ Dest ;
  
  }
  
  ++ * Cursor ;
    
  * Dest = '\0' ;

}

void SkipPipeFields ( int n ,
                      char * * ch ) {
/*
 * Skip n fields in the string pointed to by ch
 * and advances ch to (n+1)-th field.
 *
 * NOTES: ch can point to the terminating '\0' if the field is the last.
 */

  int i = 0 ;
  
# ifdef DEBUG
  DEBUG_ENTERFUNC("SkipPipeFields");
# endif

  for ( i = 0 ;
        i < n ; 
        ++ i ) {

    int FirstPipeFound = 0 ;

    SkipWhiteSpaces ( ch ) ;

    while ( ( * * ch ) != '\0' ) {

      if ( ( * * ch ) == '|' ) {

        if ( FirstPipeFound ) {

          /* It's the second pipe. */
          
          ++ ( * ch ) ;

          break ;
          
        } else {

          ++ FirstPipeFound ;

        }

      }

      ++ ( * ch ) ;

    }

    if ( ( * * ch ) == '\0' ) {

      break ;

    }
  
  }

}

void SkipFields ( char * type ,
                  int n ,
                  char * * ch ) {
/*
 * Skip n fields in the string pointed to by ch
 * and advances ch to (n+1)-th field.
 *
 * NOTES: ch can point to the terminating '\0' if the field is the last.
 */

# ifdef DEBUG
  DEBUG_ENTERFUNC("SkipFields");
# endif

  if ( strcmp ( type ,
                "compiled" ) == 0 ) {
  
    int i = 0 ;
  
    SkipWhiteSpaces ( ch ) ;

    for ( i = 0 ;
          i < n ;
          ++ i ) {
          
      while ( ! isspace ( * * ch )
	      && * * ch != '\0' ) {

        ++ ( * ch ) ;
  
      }

      if ( * * ch == '\0' ) {

        break ;
  
      }

      SkipWhiteSpaces ( ch ) ;
    
    }
  
  } else {
  
    if ( strcmp ( type ,
                  "inputValue" ) == 0 ) {

      int i = 0 ;

      for ( i = 0 ;
            i < n ;
            ++ i ) {
            
        int FirstPipeFound = 0 ;

        SkipWhiteSpaces ( ch ) ;

        while ( * * ch != '\0' ) {
        
          if ( * * ch == '|' ) {

            if ( FirstPipeFound ) {

              ++ ( * ch ) ;

              break ;
            
            } else {
            
              FirstPipeFound = 1 ;
            
            }
          
          }

          ++ ( * ch ) ;

        }

        if ( * * ch == '\0' ) {

          break ;

        }

      }

    }

  }

}

void SkipWhiteSpaces ( char * * ch ) {
/*
 * Skip white spaces till the first non-space character.
 */
  
# ifdef DEBUG
  DEBUG_ENTERFUNC("SkipWhiteSpaces");
# endif
  
  while ( isspace ( * * ch ) ) {

    ++ ( * ch ) ;

  }

}

FILE * OpenFile ( const char * Path ,
                  const char * Mode ) {

  FILE * fd = NULL ;
  
# ifdef DEBUG
  DEBUG_ENTERFUNC("OpenFile");
# endif
  
  errno = 0 ;
  
  fd = fopen ( Path ,
               Mode ) ;

  if ( fd == NULL ) {
  
    sprintf ( pagmod_logbf ,
              "Errore apertura file %s - errno=%d" ,
              Path ,
              errno ) ;
  
    pagmod_log ( pagmod_logbf ) ;
    
    fprintf ( stderr ,
              "%s\n" ,
              pagmod_logbf ) ;
  
  }
  
  return fd ;

}

void CloseFile ( FILE * fd ) {

# ifdef DEBUG
  DEBUG_ENTERFUNC("CloseFile");
# endif

  fclose ( fd ) ;

}

/* EOF. */

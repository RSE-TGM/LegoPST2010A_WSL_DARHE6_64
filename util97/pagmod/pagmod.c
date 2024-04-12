/* 
 * pagmod.c
 *
 * Description:
 * 
 * Main file of the pagmod utility for the LEGOCAD sistem.
 *
 * Date:
 *
 * 1997-07-18
 *
 * Functions:
 *
 * main
 * GetOptions
 * PagMod
 * PrintUsage
 */ 

# include <stdio.h>

# include <stdlib.h>

# include <string.h>

# include <unistd.h>

# include "widgets.h"

# include "page.h"

# include "script.h"

# include "util.h"

# include "flist.h"

/* Prototypes. */

static int GetOptions ( int argc ,
                        char * * argv ) ;
                        
static int PagMod ( void ) ;

static void PrintUsage ( int Level ) ;

/* Functions. */

void main ( int argc ,
            char * * argv ) {
            
  if ( argc < 2 ) {
  
    PrintUsage ( 1 ) ;
  
  }
  
  if ( - 1 == GetOptions ( argc ,
                          argv ) )
    {
    PrintUsage ( 1 ) ;
    }

  /* Start logging. */

  atexit ( log_stop ) ;

  log_start ( argc ,
              argv ) ;

  if ( - 1 == ScanScriptFile ( ) ) {
  
    exit ( EXIT_FAILURE ) ; 
  
  }

  if ( ExitAfterScanScript ) {
  
    exit ( EXIT_SUCCESS ) ;
  
  }

  if ( UseListFileName ) {
  
    if ( - 1 == ReadListFile ( ) ) {
    
      exit ( EXIT_FAILURE ) ;
    
    }
  
  } else { 
  
    if ( UsePageFileName ) {
    
      FileListHandle . Next = ( struct FileList * ) Malloc ( sizeof ( struct FileList ) ) ;

      FileListHandle . Next -> Path = PageFileName ;
    
      FileListHandle . Next -> Next = NULL ;
  
    } else {
    
      if ( BehaveAsFilter ) {
  
        PageFileName = "<stdin>" ;
  
        strcpy ( ModFileName , "<stdout>" ) ;
  
      }
    
    }
    
  }

  if ( BehaveAsFilter ) {
  
    if ( - 1 == PagMod ( ) ) {
    
      exit ( EXIT_FAILURE ) ;
    
    }
  
  } else {
  
    FLH = FileListHandle . Next ;
    
    if ( ! FLH ) {
    
      fprintf ( stderr ,
                "pagmod: Specificare il file pagina.\n" ) ;
                  
      PrintUsage ( 1 ) ;

    }
  
    while ( FLH ) {
    
      PageFileName = FLH -> Path ;

      strcpy ( ModFileName , PageFileName ) ;
    
      strcat ( ModFileName , ".mod" ) ;
      
      if ( - 1 == PagMod ( ) ) {
      
        exit ( EXIT_FAILURE ) ;
        
      }

      FLH = FLH -> Next ;
    
    }
  
  }

  exit ( EXIT_SUCCESS ) ;

}

static int GetOptions ( int argc , char * * argv ) {
/*
 * Scan the command line for execution options.
 *
 * Return:  0 if successful.
 *         -1 on failure.
 */
 
  char Args [ ] = "agGcd:Hhil:nPp:qSs:tV" ;
 
  int c ;

  while ( - 1 != ( c = getopt ( argc ,
                                argv ,
                                Args ) ) ) {
    
    switch ( c ) {
    
      case 'h' : {
      
        PrintUsage ( 1 ) ;
        
        break ;
   
      }

      case 'H' : {
      
        PrintUsage ( 2 ) ;

        break ;

      }

      case 'V' : {
      
        PrintUsage ( 3 ) ;
        
        break ;

      }

      case 'c' : {

        ExitAfterScanScript = 1 ;
        
        break ;
      
      }

      case 'n' : {

        DoNotWriteModFile = 1 ;
      
        break ;

      }

      case 'l' : {

        ListFileName = optarg ;
	
        UseListFileName = 1 ;
       	
       	break ;

      }
        
      case 'q' : {

        QuietMode = 1 ;
        
        break ;
      
      }
  
      case 's' : {

        ScriptFileName = optarg ;
        
        break ;
      
      }
      
      case 'p' : {
        
        PageFileName = optarg ;
        
        UsePageFileName = 1  ;
        
        break ;
        
      }

      case 'i' : {
     
        BehaveAsFilter = 1 ;
        
        break ;

      }
	    
# ifdef DEBUG
      case 'd' : {
      
        DebugPattern = optarg ;
      
        break ;
      
      }
# endif
      
      case 'g' : {
      
        DoGrep = 1 ;
        
        break ;
      
      }
      
      case 'G' : {
      
        DoAfterGrep = 1 ;
        
        break ;
      
      }
     
      case 'a' : {
      
        AskConfirm = 1 ;
      
        break ;
      
      }

      default : {

        return - 1 ;
      
      }
    
    }
    
  }

  /* Test for the right combination. */

  if ( ! ScriptFileName ) {
  
    fprintf ( stderr ,
              "pagmod: Specificare il file di script!\n" ) ;

    return - 1 ;

  }
  
  if ( ( UseListFileName && UsePageFileName ) 
       || ( UseListFileName && BehaveAsFilter ) 
       || ( UsePageFileName && BehaveAsFilter ) ) {

    fprintf ( stderr , 
              "Specificare un file risorse o un file lista.\n" ) ;

    return - 1 ;

  }

  return 0 ;

}

static int PagMod ( void ) {
/*
 * Modifies a single page.
 *
 * Return:  0 if successful.
 *         -1 on failure.
 */

  if ( - 1 == ScanPageFile ( ) ) {

    return - 1 ;

  }

  if ( - 1 == ApplyQuery ( ) ) {
 
    return - 1 ;
 
  }

  if ( - 1 == WriteModFile ( ) ) {

    return - 1 ;

  }

  DestroyPageWidgetHandle ( PageWidgetHandleList ) ;

  return 0 ;

}

static void PrintUsage ( int Level ) {
/*
 * Print usage information and exit.
 *
 * If level is 1, sintetic info are displayed.
 * If level is 2, detailed info are displayed.
 * If level is 3, version information.
 */

  char help_h [ ] = "\n\
uso:   pagmod -s script [-a] [-c]"
# ifdef DEBUG
" [-d pattern]"
# endif
" [-g] [-G] [-i] [-l list] [-n]\n\
               [-p page] [-q]\n\
       pagmod [-h -H -V]\n\
\n" ;

  char help_H [ ] = "\n\
uso:   pagmod -s script [-a] [-c]"
# ifdef DEBUG
" [-d pattern]"
# endif
" [-g] [-G] [-i] [-l list] [-n]\n\
              [-p page] [-q]\n\
       pagmod [-h -H -V]\n\
\n\
       -a         chiede conferma prima della modifica\n\
       -c         effettua solo il controllo dello script\n"
# ifdef DEBUG
"       -d pattern seleziona gli output (condizionati dai caratteri del pattern)\n\
                  per il debug su stderr\n"
# endif
"       -h         help sintetico\n\
       -H         help esteso (questo testo)\n\
       -g         grep degli attributi selezionati (prima della modifica)\n\
                  su stderr\n\
       -G         grep degli attributi selezionati (dopo la modifica)\n\
                  su stderr\n\
       -i         legge il file di risorse dallo standard input\n\
                  e fornisce il risultato su standard output\n\
       -l list    specifica il file che contiene l'elenco\n\
                  dei file risorse (1 per linea)\n\
       -n         non effettua le modifiche (non crea i file *.mod)\n\
       -p page    specifica il file pagina\n\
       -q         non effettua log (nel file pagmod.log)\n\
       -s script  specifica il file script\n\
       -V         fornisce la versione del programma\n\
\n" ;

  switch ( Level ) {

    case 1 : {

      fprintf ( stderr ,
                help_h );
    
      break ;
    
    }

    case 2 : {
    
      fprintf ( stderr , help_H );
    
      break ;
    
    }
    
    case 3 : {
    
      fprintf ( stderr , "\n%s\n\n" , help_V ) ;
      
      break ;
    
    }
      
  }

  exit ( EXIT_FAILURE ) ;

}

/* EOF. */

/*
 * script.c
 *
 * Description:
 *
 * Script file management.
 *
 * Date:
 *
 * 1997-07-18
 *
 * Functions:
 *
 * ApplyQuery
 * CheckWidget
 * CheckWidgetHasAttribs
 * UpadateMatrixAttribs
 * ScanScriptFile
 * WhichKeyword
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <ctype.h>
#include "script.h"
#include "widgets.h"
#include "util.h"
#include "iconregmod.h"
#include "pagcompiler.h"

void	AppendToFileList( char* );


enum Keyword 
  {
  ANYVALUEKEY ,
  ANYWIDGETKEY ,
  ATTRIBNAMEKEY ,
  ATTRIBVALUEKEY ,
  COMPILEDKEY ,
  COMPILED7ADDKEY ,
  COMPILED8ADDKEY ,
  COMPILED7HASKEY ,
  COMPILED8HASKEY ,
  COMPILED7INSKEY ,
  COMPILED8INSKEY ,
  COMPILED7REPKEY ,
  COMPILED8REPKEY ,
  HASATTRIBNAMEKEY ,
  INPUTINSKEY ,
  INPUTREPKEY ,
  INPUTVALUEKEY ,
  NEWATTRIBNAMEKEY ,
  PAGEKEY ,
  SAMEVALUEKEY ,
  WIDGETCHILDOFKEY ,
  WIDGETCLASSKEY ,
  WIDGETNAMEKEY ,
  NOKEY
  } ;
struct KeyToken
  {
  enum Keyword Key ;
  char * Token ;
  } ;
static struct KeyToken KeyTokenTable [ ] =
  {
    /* Key */            /* Token */
  { ANYVALUEKEY        , "anyvalue"      } ,
  { ANYWIDGETKEY       , "anywidget"     } ,
  { ATTRIBNAMEKEY      , "attrib"        } ,
  { ATTRIBVALUEKEY     , "value"         } ,
  { COMPILEDKEY        , "compiled"      } ,
  { COMPILED7ADDKEY    , "compiled7add"  } ,
  { COMPILED8ADDKEY    , "compiled8add"  } ,
  { COMPILED7HASKEY    , "compiled7has"  } ,
  { COMPILED8HASKEY    , "compiled8has"  } ,
  { COMPILED7INSKEY    , "compiled7ins"  } ,
  { COMPILED8INSKEY    , "compiled8ins"  } ,
  { COMPILED7REPKEY    , "compiled7rep"  } ,
  { COMPILED8REPKEY    , "compiled8rep"  } ,
  { HASATTRIBNAMEKEY   , "hasattrib"     } ,
  { INPUTINSKEY        , "inputins"      } ,
  { INPUTREPKEY        , "inputrep"      } ,
  { INPUTVALUEKEY      , "inputvalue"    } ,
  { NEWATTRIBNAMEKEY   , "newattrib"     } ,
  { PAGEKEY            , "page"          } ,
  { SAMEVALUEKEY       , "samevalue"     } ,
  { WIDGETCHILDOFKEY   , "widgetchildof" } ,
  { WIDGETCLASSKEY     , "widgetclass"   } , 
  { WIDGETNAMEKEY      , "widgetname"    } ,
  { NOKEY              , NULL            }
  } ;
char * ScriptFileName = NULL ; /* Path name of script file. */
struct ScriptWidget * ScriptWidgetList = NULL ; /* Head of list of widgets in the script. */
static int CheckWidget ( struct PageWidget * ,
                         struct ScriptWidget * ) ;
static void UpdateMatrixAttribs ( struct PageWidget * ,
                                  struct WidgetAttrib * ,
                                  struct MatrixAttrib * ) ;
static enum Keyword WhichKeyword ( const char * ) ;
int ApplyQuery ( void ) {
/*
 * Apply query to the database.
 *
 * Return:  0 success.
 *         -1 failure.
 */
  struct ScriptWidget * QueryWidget = ScriptWidgetList -> Next ;
# ifdef DEBUG
  DEBUG_ENTERFUNC("ApplyQuery");
# endif
  Kchg = Knew = Krep = Kins = Kadd = Ktot = 0 ;
  while ( QueryWidget != NULL ) {
    struct PageWidgetHandle * Handle = PageWidgetHandleList -> Next ;
    while ( Handle != NULL ) {
      if ( CheckWidget ( Handle -> Widget ,
                         QueryWidget ) == - 1 ) {
        Handle = Handle -> Next ;
        continue ;
      }
      {
        struct WidgetAttrib * NewAttrib = QueryWidget -> NewAttribs -> Next ;
        while ( NewAttrib ) {
          struct WidgetAttrib * NextAttrib = Handle -> Widget -> Attribs -> Next ;
          struct WidgetAttrib * OldAttrib = Handle -> Widget -> Attribs -> Next ;
          while ( OldAttrib ) {
            if ( strcmp ( OldAttrib -> Name ,
                          NewAttrib -> Name ) == 0 ) {
              break ;
            }
            OldAttrib = OldAttrib -> Next ;
          }
          if ( ! OldAttrib ) {
            if ( AskConfirm ) {
              char Answer [ 2 ] ;
              printf ( "in %s\n"
                       "aggiungere: *%s.%s:\t%s\n"
                       "? " ,
                       PageFileName ,
                       Handle -> Widget -> Name ,
                       NewAttrib -> Name ,
                       NewAttrib -> Value ) ;
              fgets ( Answer ,
                      sizeof ( Answer ) ,
                      stdin ) ;
              fflush ( stdin ) ;
              Chop ( Answer ) ;
              if ( Answer [ 0 ] != 'y' ) {
                break ;
              }
            }
            Handle -> Widget -> Attribs -> Next = CreateWidgetAttrib ( ) ;
            Handle -> Widget -> Attribs -> Next -> Name = ( char * ) Malloc ( strlen ( NewAttrib -> Name ) + 1 ) ;
            Handle -> Widget -> Attribs -> Next -> Value = ( char * ) Malloc ( strlen ( NewAttrib -> Value ) + 1 ) ;
            Handle -> Widget -> Attribs -> Next -> Next = NextAttrib ;
            strcpy ( Handle -> Widget -> Attribs -> Next -> Name ,
                     NewAttrib -> Name ) ;
            strcpy ( Handle -> Widget -> Attribs -> Next -> Value ,
                     NewAttrib -> Value ) ;
# ifdef DEBUG
            DEBUG_NEWATTRIB(Handle -> Widget -> Attribs -> Next -> Name);
# endif
            ++ Knew ;
          } else {
            sprintf ( logbf ,
                      "newattrib=%s attributo gia' presente in *%s" ,
                      NewAttrib -> Name ,
                      Handle -> Widget -> Name  ) ;
            log ( logbf ) ;
          }
          NewAttrib = NewAttrib -> Next ;
        }
      }
      if ( QueryWidget -> InputValue ) {
        struct WidgetAttrib * InputValueAttrib = Handle -> Widget -> Attribs -> Next ,
                            * ModuleNameAttrib = Handle -> Widget -> Attribs -> Next ;
        int Found = 0 ;
        while ( ModuleNameAttrib ) {
          if ( strcmp ( ModuleNameAttrib -> Name ,
                        "modulName" ) == 0 ) {
            break ;
          }
          ModuleNameAttrib = ModuleNameAttrib -> Next ;
        }
        if ( ! ModuleNameAttrib ) {
          Handle = Handle -> Next ;
          continue ;
        }
        while ( InputValueAttrib ) {
          if ( 0 == strcmp ( InputValueAttrib -> Name ,
                             "inputValue" ) ) {
            char * NewInputValue = ( char * ) Malloc ( INPUTVALUELEN ) ;
            char OldModule [ PATHNAMELEN ] = "" ,
                 NewModule [ PATHNAMELEN ] = "" ,
                 NewModuleTemp [ PATHNAMELEN ] = "" ,
                 * OldModuleDirName = NULL ;
            DEBUG_GREP("inputValue",InputValueAttrib -> Value);
            strcpy ( NewModule ,
                     QueryWidget -> InputValue ) ;
            strcpy ( NewModuleTemp , NewModule ) ;
            OldModuleDirName = ( char * ) dirname ( NewModuleTemp ) ;
            if ( OldModuleDirName ) {
              strcpy ( OldModule ,
                       OldModuleDirName ) ;
              strcat ( OldModule ,
                       "/" ) ;
            }
            strcat ( OldModule ,
                     ModuleNameAttrib -> Value ) ;
            if ( - 1 == IconRegMod ( OldModule ,
                                     NewModule ,
                                     InputValueAttrib -> Value ,
                                     NewInputValue ) ) {
              sprintf ( logbf , 
                        "Errore modifica risorsa *%s.inputValue" ,
                        Handle -> Widget -> Name ) ;
              log ( logbf ) ;
              fprintf ( stderr ,
                        "pagmod: %s\n" ,
                        logbf ) ;
              break ;
            }
            if ( AskConfirm ) {
              char Answer [ 2 ] ;
              printf ( "in %s\n"
                       "da: *%s.%s:\t%s\n"
                       " a: *%s.%s:\t%s\n"
                       "? " ,
                       PageFileName ,
                       Handle -> Widget -> Name ,
                       "inputValue" ,
                       InputValueAttrib -> Value ,
                       Handle -> Widget -> Name ,
                       "inputValue" ,
                       NewInputValue ) ;
              fgets ( Answer ,
                      sizeof ( Answer ) ,
                      stdin ) ;
              fflush ( stdin ) ;
              Chop ( Answer ) ;
              if ( 'y' != Answer [ 0 ] ) {
                break ;
              }
            }
            free ( InputValueAttrib -> Value ) ;
            InputValueAttrib -> Value = ( char * ) Malloc ( strlen ( NewInputValue ) + 1 ) ;
            strcpy ( InputValueAttrib -> Value ,
                     NewInputValue ) ;
            free ( NewInputValue ) ;
            DEBUG_AFTERGREP("inputValue",InputValueAttrib -> Value);
            ++ Kchg ;
# ifdef DEBUG
            DEBUG_CHGATTRIB("inputValue");
# endif
            break ;
          }
          InputValueAttrib = InputValueAttrib -> Next ;
        }
      }
      if ( QueryWidget -> Compiled )
        {
        char CompiledString [ 1000 ] ;
        PagCompiler ( CompiledString ,
                      Handle -> Widget -> Attribs ) ;
        }
      {
        struct WidgetAttrib * ChangeAttrib = QueryWidget -> ChangeAttribs -> Next ;
        while ( ChangeAttrib ) {
          struct WidgetAttrib * AttribToChange = Handle -> Widget -> Attribs -> Next ;
          while ( AttribToChange ) {
            if ( 0 == strcmp ( AttribToChange -> Name ,
                               ChangeAttrib -> Name ) ) {
              DEBUG_GREP(AttribToChange -> Name,AttribToChange -> Value);
              if ( ChangeAttrib -> IgnoreValue )
                {
                break ;
                }
              if ( AskConfirm ) {
                char Answer [ 2 ] ;
                printf ( "in %s\n"
                         "da: *%s.%s:\t%s\n"
                         " a: *%s.%s:\t%s\n"
                         "? " ,
                         PageFileName ,
                         Handle -> Widget -> Name ,
                         AttribToChange -> Name ,
                         AttribToChange -> Value ,
                         Handle -> Widget -> Name ,
                         ChangeAttrib -> Name ,
                         ChangeAttrib -> Value ) ;
                fgets ( Answer ,
                        sizeof ( Answer ) ,
                        stdin ) ;
                fflush ( stdin ) ;
                Chop ( Answer ) ;
                if ( Answer [ 0 ] != 'y' ) {
                  break ;
                }
              }
              free ( AttribToChange -> Value ) ;
              AttribToChange -> Value = ( char * ) Malloc ( strlen ( ChangeAttrib -> Value ) + 1 ) ;
              strcpy ( AttribToChange -> Value , ChangeAttrib -> Value ) ;
              DEBUG_AFTERGREP(AttribToChange -> Name,AttribToChange -> Value);
              ++ Kchg ;
# ifdef DEBUG
              DEBUG_CHGATTRIB(AttribToChange -> Name);
# endif
              break ;
            }
            AttribToChange = AttribToChange -> Next ;
          }
          ChangeAttrib = ChangeAttrib -> Next ;
        }
      }
      {
        struct WidgetAttrib * CurrentWidgetAttrib = Handle -> Widget -> Attribs -> Next ;
        while ( CurrentWidgetAttrib ) {
          struct MatrixAttrib * QueryMatrixAttrib = QueryWidget -> MatrixAttribs -> Next ; 
          while ( QueryMatrixAttrib ) {
            if ( strcmp ( CurrentWidgetAttrib -> Name ,
                          QueryMatrixAttrib -> Name ) == 0 ) {
              DEBUG_GREP(CurrentWidgetAttrib -> Name,CurrentWidgetAttrib -> Value);
              UpdateMatrixAttribs ( Handle -> Widget ,
                                    CurrentWidgetAttrib ,
                                    QueryMatrixAttrib ) ;
              DEBUG_AFTERGREP(CurrentWidgetAttrib -> Name,CurrentWidgetAttrib -> Value);
# ifdef DEBUG
              DEBUG_CHGATTRIB(CurrentWidgetAttrib -> Name);
# endif
            }
            QueryMatrixAttrib = QueryMatrixAttrib -> Next ;
          }
          CurrentWidgetAttrib = CurrentWidgetAttrib -> Next ;
        }
      }
      Handle = Handle -> Next ;
    }
    QueryWidget = QueryWidget -> Next ;
  }
  Ktot = Kchg + Knew + Kins + Krep + Kadd ;
  Gtot += Ktot ;
  if ( Ktot > 0 ) {
    ++ Gpag ;
  }
  sprintf ( logbf , 
            "% 4d +% 4d +% 4d +% 4d +% 4d =%4d.  %s" ,
            Kchg ,
            Knew ,
            Kins ,
            Krep ,
            Kadd ,
            Ktot ,
            PageFileName ) ;
  log ( logbf ) ;
  return 0 ;
}
static int CheckWidget ( struct PageWidget * HandleWidget , 
                         struct ScriptWidget * QueryWidget )
  {
  /*
   * Check if the two widgets have the same name, class, parent.
   *
   * Return:  0 if the name, class, parent are the same or if the QueryWidget
   *            does not have neither attributes (i.e. any widget is to match ).
   *         -1 otherwise.
   */
  int AnyWidget = 1 ;
# ifdef DEBUG
  DEBUG_ENTERFUNC("CheckWidget");
# endif
  if ( QueryWidget -> Name )
    {
    if ( strcmp ( HandleWidget -> Name ,
                  QueryWidget -> Name ) != 0 )
      {
      return - 1 ;
      }
    AnyWidget = 0 ;
    }
  if ( QueryWidget -> Class )
    {
    if ( strcmp ( HandleWidget -> Class ,
                  QueryWidget -> Class ) != 0 )
      {
      return - 1 ;
      }
    AnyWidget = 0 ;
    }
  if ( QueryWidget -> ChildOf )
    {
    if ( ! HandleWidget -> Parent )
      {
      return - 1 ;
      }
    if ( strcmp ( HandleWidget -> Parent -> Name ,
                  QueryWidget -> ChildOf ) != 0 )
      {
      return - 1 ;
      }
    AnyWidget = 0 ;
    }
  if ( AnyWidget )
    {
    if ( strcmp ( HandleWidget -> Name ,
                  "PAGE" ) == 0 )
      {
      return - 1 ;
      }
    }
  {
  
  struct WidgetAttrib * HasAttrib = QueryWidget -> HasAttribs -> Next ;

  struct MatrixAttrib * MatrixHasAttrib = QueryWidget -> MatrixHasAttribs -> Next ;

  while ( HasAttrib ) {
  
    struct WidgetAttrib * AttribToCheck = HandleWidget -> Attribs -> Next ;
  
    int Found = 0 ;
  
    while ( AttribToCheck ) {
    
      if ( strcmp ( AttribToCheck -> Name , 
                    HasAttrib -> Name ) == 0 ) {
                    
        ++ Found ;
                    
        if ( ! HasAttrib -> IgnoreValue 
             && strcmp ( AttribToCheck -> Value , 
                         HasAttrib -> Value ) != 0 ) {
                      
          return - 1 ;
          
        }
        
        break ;
   
      }

      AttribToCheck = AttribToCheck -> Next ;

    }
    
    if ( ! Found ) {
    
      return - 1 ;
      
    }

    HasAttrib = HasAttrib -> Next ;

  }
  
  while ( MatrixHasAttrib ) {
  
    struct WidgetAttrib * AttribToCheck = HandleWidget -> Attribs -> Next ;
    
    int Found = 0 ;
    
    while ( AttribToCheck ) {
    
      if ( strcmp ( AttribToCheck -> Name ,
                    MatrixHasAttrib -> Name ) == 0 ) {
                    
        char * ItemToCheck = AttribToCheck -> Value ,
             * HasItem = MatrixHasAttrib -> Value ;
        
        int i ;
      
        ++ Found ;
        
        if ( strcmp ( MatrixHasAttrib -> Name ,
                      "compiled" ) == 0 ) {
                      
          ++ ItemToCheck ; /* Avoid initial '#'. */
    
        }
    
        SkipWhiteSpaces ( & ItemToCheck ) ;
  
        for ( i = 1 ; 
              i < MatrixHasAttrib -> Index ; 
              ++ i ) {
              
          SkipFields ( MatrixHasAttrib -> Name ,
                       MatrixHasAttrib -> NumFields ,
                       & ItemToCheck ) ;
    
        }

        SkipFields ( MatrixHasAttrib -> Name ,
                     MatrixHasAttrib -> Offset - 1 ,
                     & ItemToCheck ) ;
                     
        while ( ( ! isspace ( * ItemToCheck )
                  || * ItemToCheck != '\0' ) 
                && * HasItem != '\0' ) {

          if ( * ItemToCheck != * HasItem ) {
          
            return - 1 ; /* Found difference. */
          
          }
          
          ++ ItemToCheck ;
          
          ++ HasItem ;
                
        }
        
        break ;
        
      }
      
      AttribToCheck = AttribToCheck -> Next ;
    
    }
    
    if ( ! Found ) {
    
      return - 1 ;
      
    }
    
    MatrixHasAttrib = MatrixHasAttrib -> Next ;
  
  }
  
  }
  return 0 ;
  }

static void UpdateMatrixAttribs ( struct PageWidget * HandleWidget ,
                                  struct WidgetAttrib * WidgetAttribToUpdate ,
                                  struct MatrixAttrib * QueryMatrixAttrib ) {

  int i = 0 ;

  char * Buffer = NULL ; 

  char * dest_c = NULL ,
       * src_c = WidgetAttribToUpdate -> Value ;

# ifdef DEBUG
  DEBUG_ENTERFUNC("UpdateMatrixAttribs");
# endif

  Buffer = ( char * ) Malloc ( 10000 ) ;
  
  dest_c = Buffer ;

  if ( strcmp ( QueryMatrixAttrib -> Name ,
                "compiled" ) == 0 ) {
                
    ++ src_c ; /* Avoid initial '#'. */

  }
  
  SkipWhiteSpaces ( & src_c ) ;

  /* If Value is void no action must be taken. */
  
  if ( * src_c == '\0' ) {
  
    return ;
    
  }
  
  /* We skip fields every time till the user's wished index. */
  for ( i = 1 ; 
        i < QueryMatrixAttrib -> Index ; 
        ++ i ) {
        
    SkipFields ( QueryMatrixAttrib -> Name ,
                 QueryMatrixAttrib -> NumFields ,
                 & src_c ) ;

  }

  SkipFields ( QueryMatrixAttrib -> Name ,
               QueryMatrixAttrib -> Offset - 1 ,
               & src_c ) ;
  
  strncpy ( dest_c , 
            WidgetAttribToUpdate -> Value ,
            src_c - WidgetAttribToUpdate -> Value ) ;

  dest_c += src_c - WidgetAttribToUpdate -> Value ;

  if ( QueryMatrixAttrib -> IsAddValue ) {

    char NewValue [ 50 ] ;

    long OrigNumValue = 0L ;

    long NumValueToAdd = 0L ;

    OrigNumValue = atol ( src_c ) ;

    NumValueToAdd = atol ( QueryMatrixAttrib -> Value ) ;

    sprintf ( NewValue ,
              "%ld" , 
              OrigNumValue + NumValueToAdd ) ;

    strcpy ( dest_c ,
             NewValue ) ;

    dest_c += strlen ( NewValue ) ;
  
  } else {
  
    strcpy ( dest_c , 
             QueryMatrixAttrib -> Value ) ;

    dest_c += strlen ( QueryMatrixAttrib -> Value ) ;
  
  }
  
  if ( QueryMatrixAttrib -> Offset > 0 ) {
  
    SkipFields ( QueryMatrixAttrib -> Name ,
                 1 ,
                 & src_c ) ;
  
  }

  if ( ! isspace ( * ( dest_c - 1 ) ) ) {

    * dest_c = ' ' ; /* Add a space. */

    ++ dest_c ;

  }

  strcpy ( dest_c ,
           src_c ) ; 

  /* Update the real widget value. */
  
  if ( AskConfirm ) {
            
    char Answer [ 2 ] ;
            
    printf ( "in %s\n"
             "da: *%s.%s:\t%s\n"
             " a: *%s.%s:\t%s\n"
             "? " ,
             PageFileName ,
             HandleWidget -> Name ,
             WidgetAttribToUpdate -> Name ,
             WidgetAttribToUpdate -> Value ,
             HandleWidget -> Name ,
             WidgetAttribToUpdate -> Name ,
             Buffer ) ;
           
    fgets ( Answer ,
            sizeof ( Answer ) ,
            stdin ) ;
                      
    fflush ( stdin ) ;
                      
    Chop ( Answer ) ;
              
    if ( Answer [ 0 ] != 'y' ) {
              
      free ( Buffer ) ;
      
      return ;
              
    }
              
  }

  if ( WidgetAttribToUpdate -> Value != NULL) {  
     free ( WidgetAttribToUpdate -> Value ) ;
  }
  WidgetAttribToUpdate -> Value = ( char * ) Malloc ( strlen ( Buffer ) * 100 ) ;
  
  strcpy ( WidgetAttribToUpdate -> Value , 
           Buffer ) ;

  free ( Buffer ) ;

  if ( QueryMatrixAttrib -> Offset == 0 ) {

    ++ Kins ;

  } else {
  
    if ( QueryMatrixAttrib -> IsAddValue ) {

      ++ Kadd ;
    
    } else {
    
      ++ Krep ;
    
    }
  
  }
  
}

int ScanScriptFile ( void )
  {
  /*
   * Scan the script file and build the query structure.
   *
   * Return:  0 if successful.
   *         -1 on failure.
   */
  FILE * ScriptFile = NULL ;
  struct ScriptWidget * LastWidget = NULL ;
  struct WidgetAttrib * LastChangeAttrib = NULL ,
                      * LastHasAttrib = NULL ,
                      * LastNewAttrib = NULL ;
  struct MatrixAttrib * LastMatrixAttrib = NULL ,
                      * LastMatrixHasAttrib = NULL ;
  char * ScriptLine = NULL ,
       * Token = NULL , 
       * Arg = NULL ;
  enum Keyword PrevKeyword = NOKEY , 
               CurrentKeyword = NOKEY ;
  int LineNumber = 0 ;
  int ScriptError = 0 ;
  int QueryComplete = 0 ;
# ifdef DEBUG
  DEBUG_ENTERFUNC("ScanScriptFile");
# endif
  ScriptWidgetList = CreateScriptWidget ( ) ;
  LastWidget = ScriptWidgetList ;
  ScriptFile = OpenFile ( ScriptFileName , "r" ) ; 
  if ( ScriptFile == NULL )
    {
    return - 1 ;
    }
  ScriptLine = ( char * ) Malloc ( 10000 ) ;
  Token = ( char * ) Malloc ( 30 ) ;
  Arg = ( char * ) Malloc ( 10000 ) ;
  while ( fgets ( ScriptLine ,
                  10000 ,
                  ScriptFile ) != NULL ) {
                  
    char * src_c = ScriptLine ,
         * dest_c = NULL ;
         
    int ArgLen = 0 ;

    int TokenError = 0 ,
        ArgError = 0 ;

    ++ LineNumber ;

    Chop ( ScriptLine ) ;

    SkipWhiteSpaces ( & src_c ) ;

    if ( * src_c == '#' 
         || * src_c == '\0' ) {
         
      /* Comment line. Skip. */

      continue ;

    }

    /* Get the keyword and check for the correctness of the line. */

    for ( dest_c = Token ;
          * src_c != '=' 
          && * src_c != '\0' ;
          ++ src_c ,
          ++ dest_c ) {

      * dest_c = * src_c ;

    }

    * dest_c = '\0' ;

    if ( * src_c == '\0' ) {
      
      ++ ScriptError ;

      sprintf ( logbf , 
                "#% 6d - Token non riconosciuto: %s" ,
                LineNumber ,
                Token ) ;

      log ( logbf ) ;

      fprintf ( stderr ,
                "pagmod: %s\n" ,
                logbf ) ;

      continue ;
    
    }

    ++ src_c ;

    strcpy ( Arg ,
             src_c ) ;

    ArgLen = strlen ( Arg ) ;

    /* Parsing and Lexical analysing. */ 

    CurrentKeyword = WhichKeyword ( Token ) ;

    if ( CurrentKeyword == NOKEY ) {
    
      ++ ScriptError ;

      sprintf ( logbf , 
                "#% 6d - Token non riconosciuto: %s" ,
                LineNumber ,
                Token ) ;

      log ( logbf ) ;

      fprintf ( stderr ,
                "pagmod: %s\n" ,
                logbf ) ;

      continue ;
    
    }

    if ( CurrentKeyword != ANYWIDGETKEY 
         && CurrentKeyword != COMPILEDKEY 
         && CurrentKeyword != SAMEVALUEKEY 
         && CurrentKeyword != ANYVALUEKEY ) {
    
      if ( Arg [ 0 ] == '\0' ) {
      
        ++ ScriptError ;
        
        sprintf ( logbf , 
                  "#% 6d - Argomento nullo: %s=" ,
                  LineNumber ,
                  Token ) ;

        log ( logbf ) ;
 
        fprintf ( stderr ,
                  "pagmod: %s\n" ,
                  logbf ) ;

        break ;
      
      }
      
      if ( CurrentKeyword != ATTRIBVALUEKEY )
        {
        /* Eliminate trailing blanks from the Argument. */
        char * arg_c = strchr ( Arg ,
                                '\0' ) ;
        do
          {              
          -- arg_c ;
          }
        while ( isspace ( * arg_c ) ) ;
        * ++ arg_c = '\0' ;
        }
    
    }
    
    switch ( CurrentKeyword ) {

      case PAGEKEY : {
      
        QueryComplete = 0 ;
        
        switch ( PrevKeyword ) {
        
          case NOKEY :
          case PAGEKEY : {

            if ( ScriptError ) {

              break ;

            }

            if ( ! UseListFileName
                 && ! UsePageFileName
                 && ! BehaveAsFilter ) {
                 
              AppendToFileList ( Arg ) ;

            }
            
            break ;

          }
          
          default : {

            ++ TokenError ;
            
            break ;
          
          }
        
        }
        
        break ;
      
      }

      case WIDGETNAMEKEY : {
      
        QueryComplete = 0 ;

        switch ( PrevKeyword ) {
        
          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY :
          case ANYVALUEKEY :
          case PAGEKEY :
          case NOKEY : {
          
            if ( ScriptError ) {

              break ;

            }
            
            LastWidget -> Next = CreateScriptWidget ( ) ;

            LastWidget = LastWidget -> Next ;

            LastChangeAttrib = LastWidget -> ChangeAttribs ;

            LastHasAttrib = LastWidget -> HasAttribs ;

            LastNewAttrib = LastWidget -> NewAttribs ;

            LastMatrixAttrib = LastWidget -> MatrixAttribs ;

            LastMatrixHasAttrib = LastWidget -> MatrixHasAttribs ;

            LastWidget -> Name = ( char * ) Malloc ( ArgLen + 1 ) ;

            strcpy ( LastWidget -> Name ,
                     Arg ) ;
            
            break ;

          }
          
          default: {

            ++ TokenError ;
            
            break ;

          }
        
        }  
        
        break ;
          
      }

      case WIDGETCLASSKEY : {
        
        QueryComplete = 0 ;
        
        switch ( PrevKeyword ) {
        
          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY :
          case ANYVALUEKEY :
          case PAGEKEY :
          case NOKEY : {
          
            if ( ScriptError ) {

              break ;

            }

            LastWidget -> Next = CreateScriptWidget ( ) ;

            LastWidget = LastWidget -> Next ;

            LastChangeAttrib = LastWidget -> ChangeAttribs ;

            LastHasAttrib = LastWidget -> HasAttribs ;

            LastNewAttrib = LastWidget -> NewAttribs ;

            LastMatrixAttrib = LastWidget -> MatrixAttribs ;

            LastMatrixHasAttrib = LastWidget -> MatrixHasAttribs ;

            LastWidget -> Class = ( char * ) Malloc ( ArgLen + 1 ) ;

            strcpy ( LastWidget -> Class ,
                     Arg ) ;

            break ;
          
          }

          default : {

            ++ TokenError ;
            
            break ;

          }
        
        }

        break ;
      
      }

      case WIDGETCHILDOFKEY : {
      
        QueryComplete = 0 ;
        
        switch ( PrevKeyword ) {
        
          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY :
          case ANYVALUEKEY :
          case WIDGETCLASSKEY :
          case WIDGETNAMEKEY :
          case ANYWIDGETKEY :
          case PAGEKEY :
          case NOKEY : {
          
            if ( ScriptError ) {
            
              break ;
            
            }

            free ( LastWidget -> ChildOf ) ;
            
            LastWidget -> ChildOf = ( char * ) Malloc ( ArgLen + 1 ) ;
           
            strcpy ( LastWidget -> ChildOf ,
                     Arg ) ;
            
            break ;
           
          }

          default : {
          
            ++ TokenError ;
            
            break ;
          
          }
            
        }
        
        break ;
      
      }
      
      case ANYWIDGETKEY : {

        QueryComplete = 0 ;
        
        switch ( PrevKeyword ) {
        
          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY :
          case ANYVALUEKEY :
          case PAGEKEY :
          case NOKEY : {
          
            if ( ScriptError ) {

              break ;

            }

            LastWidget -> Next = CreateScriptWidget ( ) ;

            LastWidget = LastWidget -> Next ;

            LastChangeAttrib = LastWidget -> ChangeAttribs ;

            LastHasAttrib = LastWidget -> HasAttribs ;

            LastNewAttrib = LastWidget -> NewAttribs ;

            LastMatrixAttrib = LastWidget -> MatrixAttribs ;

            LastMatrixHasAttrib = LastWidget -> MatrixHasAttribs ;
            
            break ;

          }

          default : {

            TokenError ;
            
            break ;

          }
          
        }
        
        break ;
        
      }
        
      case INPUTVALUEKEY : {
      
        QueryComplete = 0 ;
        
        switch ( PrevKeyword ) {

          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case WIDGETNAMEKEY :
          case WIDGETCLASSKEY :
          case WIDGETCHILDOFKEY :
          case ANYWIDGETKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY :
          case ANYVALUEKEY : {
          
            if ( ScriptError ) {

              break ;

            }
            
            free ( LastWidget -> InputValue ) ;
            
            LastWidget -> InputValue = ( char * ) Malloc ( ArgLen + 1 ) ;
           
            strcpy ( LastWidget -> InputValue ,
                     Arg ) ;
            
            break ;

          }

          default : {

            ++ TokenError ;
           
            break ; 

          }
        
        }
        
        break ;
      
      }

      case COMPILEDKEY :
        {
        QueryComplete = 1 ;
        switch ( PrevKeyword )
          {
        case INPUTVALUEKEY :
        case COMPILEDKEY :
        case WIDGETNAMEKEY :
        case WIDGETCLASSKEY :
        case WIDGETCHILDOFKEY :
        case ANYWIDGETKEY :
        case ATTRIBVALUEKEY :
        case SAMEVALUEKEY :
        case ANYVALUEKEY :
          {
          if ( ScriptError )
            {
            break ;
            }
          LastWidget -> Compiled = 1 ;
          break ;
          }
        default :
          {
          ++ TokenError ;
          break ; 
          }
          }
        break ;
        }
      
      case ATTRIBNAMEKEY : {
      
        QueryComplete = 0 ;
        
        switch ( PrevKeyword ) {
        
          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case WIDGETNAMEKEY :
          case WIDGETCLASSKEY :
          case WIDGETCHILDOFKEY :
          case ANYWIDGETKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY :
          case ANYVALUEKEY : {
          
            if ( ScriptError ) {

              break ;

            }

            LastChangeAttrib -> Next = CreateWidgetAttrib ( ) ;

            LastChangeAttrib = LastChangeAttrib -> Next ;

            LastChangeAttrib -> Name = ( char * ) Malloc ( ArgLen + 1 ) ;

            strcpy ( LastChangeAttrib -> Name ,
                     Arg ) ;

            break ;

          }

          default : {

            ++ TokenError ;

            break ;

          }

        }
        
        break ;
        
      }

      case HASATTRIBNAMEKEY : {
      
        QueryComplete = 0 ;
        
        switch ( PrevKeyword ) {
        
          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case WIDGETNAMEKEY :
          case WIDGETCLASSKEY :
          case WIDGETCHILDOFKEY :
          case ANYWIDGETKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY :
          case ANYVALUEKEY : {
          
            if ( ScriptError ) {

              break ;

            }

            LastHasAttrib -> Next = CreateWidgetAttrib ( ) ;

            LastHasAttrib = LastHasAttrib -> Next ;

            LastHasAttrib -> Name = ( char * ) Malloc ( ArgLen + 1 ) ;

            strcpy ( LastHasAttrib -> Name ,
                     Arg ) ;
            
            break ;

          }

          default : {

            ++ TokenError ;

            break ;

          }

        }

        break ;
      
      }

      case NEWATTRIBNAMEKEY : {

        QueryComplete = 0 ;
        
        switch ( PrevKeyword ) {
        
          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case WIDGETNAMEKEY :
          case WIDGETCLASSKEY :
          case WIDGETCHILDOFKEY :
          case ANYWIDGETKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY :
          case ANYVALUEKEY : {
          
            if ( ScriptError ) {

              break ;

            }

            LastNewAttrib -> Next = CreateWidgetAttrib ( ) ;

            LastNewAttrib = LastNewAttrib -> Next ;

            LastNewAttrib -> Name = ( char * ) Malloc ( ArgLen + 1 ) ;

            strcpy ( LastNewAttrib -> Name ,
                     Arg ) ;

            break ;

          }

          default : {
          
            ++ TokenError ;
            
            break ;
          
          }
        
        }
        
        break ;
      
      }

      case ATTRIBVALUEKEY : {
      
        QueryComplete = 1 ;
      
        switch ( PrevKeyword ) {
        
          case ATTRIBNAMEKEY : {
          
            if ( ScriptError ) {
            
              break ;
            
            }

            LastChangeAttrib -> Value = ( char * ) Malloc ( ArgLen + 1 ) ;
            
            strcpy ( LastChangeAttrib -> Value ,
                     Arg ) ;
          
            break ;
          
          }

          case HASATTRIBNAMEKEY : {

            if ( ScriptError ) {

              break ;

            }

            LastHasAttrib -> Value = ( char * ) Malloc ( ArgLen + 1 ) ;

            strcpy ( LastHasAttrib -> Value ,
                     Arg ) ;

            break ;

          }

          case NEWATTRIBNAMEKEY : {
          
            if ( ScriptError ) {
            
              break ;
            
            }

            LastNewAttrib -> Value = ( char * ) Malloc ( ArgLen + 1 ) ;
            
            strcpy ( LastNewAttrib -> Value ,
                     Arg ) ;

            break ;
            
          }

          case COMPILED8INSKEY :
          case COMPILED7INSKEY :
          case COMPILED8REPKEY :
          case COMPILED7REPKEY :
          case COMPILED8ADDKEY :
          case COMPILED7ADDKEY :
          case INPUTINSKEY :
          case INPUTREPKEY : {
          
            if ( ScriptError ) {
            
              break ;
            
            }

            LastMatrixAttrib -> Value = ( char * ) Malloc ( ArgLen + 1 ) ;

            strcpy ( LastMatrixAttrib -> Value ,
                     Arg ) ;

            break ;

          }

          case COMPILED8HASKEY :
          case COMPILED7HASKEY : {
          
            if ( ScriptError ) {
            
              break ;
           
            }

            LastMatrixHasAttrib -> Value = ( char * ) Malloc ( ArgLen + 1 ) ;
           
            strcpy ( LastMatrixHasAttrib -> Value ,
                     Arg ) ;

            break ;
          
          }
            
          default : {
          
            ++ TokenError ;

            break ;

          }

        }

        break ;
      
      }
      
      case SAMEVALUEKEY : {
      
        QueryComplete = 1 ;
      
        switch ( PrevKeyword ) {
        
          case ATTRIBNAMEKEY : {
          
            if ( ScriptError ) {
            
              break ;
            
            }

            LastChangeAttrib -> IgnoreValue = 1 ;
            
            break ;
          
          }

          default : {
          
            ++ TokenError ;

            break ;

          }

        }

        break ;
      
      }

      case ANYVALUEKEY : {
      
        QueryComplete = 1 ;
      
        switch ( PrevKeyword ) {
        
          case HASATTRIBNAMEKEY : {
          
            if ( ScriptError ) {
            
              break ;
            
            }

            LastHasAttrib -> IgnoreValue = 1 ;
            
            break ;
          
          }

          default : {
          
            ++ TokenError ;

            break ;

          }

        }

        break ;
      
      }
      
      case COMPILED8INSKEY :
      case COMPILED7INSKEY : {
        
        QueryComplete = 0 ;
        
        switch ( PrevKeyword ) {
        
          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case WIDGETNAMEKEY :
          case WIDGETCLASSKEY :
          case WIDGETCHILDOFKEY :
          case ANYWIDGETKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY : {
          
            if ( ScriptError ) {

              break ;

            }

            LastMatrixAttrib -> Next = CreateMatrixAttrib ( ) ;

            LastMatrixAttrib = LastMatrixAttrib -> Next ;

            LastMatrixAttrib -> Name = ( char * ) Malloc ( sizeof ( "compiled" ) ) ;

            strcpy ( LastMatrixAttrib -> Name ,
                     "compiled" ) ;

            if ( sscanf ( Arg ,
                          "%d" ,
                          & LastMatrixAttrib -> Index ) != 1 ) {
                          
              ++ ArgError ;
              
              break ;
              
            }
            
            LastMatrixAttrib -> NumFields = ( CurrentKeyword == COMPILED8INSKEY )
                                              ? 9
                                              : 8 ;
            
            LastMatrixAttrib -> IsAddValue = 0 ;

            break ;

          }

          default : {
          
            ++ TokenError ;

            break ;

          }

        }

        break ;
      
      }

      case COMPILED8REPKEY :
      case COMPILED7REPKEY : {
      
        QueryComplete = 0 ;
      
        switch ( PrevKeyword ) {
        
          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case WIDGETNAMEKEY :
          case WIDGETCLASSKEY :
          case WIDGETCHILDOFKEY :
          case ANYWIDGETKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY : {
          
            if ( ScriptError ) {
            
              break ;
            
            }

            LastMatrixAttrib -> Next = CreateMatrixAttrib ( ) ;
            
            LastMatrixAttrib = LastMatrixAttrib -> Next ;

            LastMatrixAttrib -> Name = ( char * ) Malloc ( sizeof ( "compiled" ) ) ;
            
            strcpy ( LastMatrixAttrib -> Name ,
                     "compiled" ) ;
            
            if ( sscanf ( Arg ,
                          "%d,%d" , 
                          & LastMatrixAttrib -> Index ,
                          & LastMatrixAttrib -> Offset ) != 2 ) {
            
              ++ ArgError ;
              
              break ;
              
            }

            LastMatrixAttrib -> NumFields = ( CurrentKeyword == COMPILED8REPKEY )
                                              ? 9
                                              : 8 ;
            
            LastMatrixAttrib -> IsAddValue = 0 ;

            break ;

          }

          default : {
          
            ++ TokenError ;

            break ;

          }

        }

        break ;
      
      }

      case COMPILED8ADDKEY :
      case COMPILED7ADDKEY : {
      
        QueryComplete = 0 ;
        
        switch ( PrevKeyword ) {
        
          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case WIDGETNAMEKEY :
          case WIDGETCLASSKEY :
          case WIDGETCHILDOFKEY :
          case ANYWIDGETKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY : {
          
            if ( ScriptError ) {
            
              break ;
            
            }

            LastMatrixAttrib -> Next = CreateMatrixAttrib ( ) ;
            
            LastMatrixAttrib = LastMatrixAttrib -> Next ;

            LastMatrixAttrib -> Name = ( char * ) Malloc ( sizeof ( "compiled" ) ) ;
            
            strcpy ( LastMatrixAttrib -> Name ,
                     "compiled" ) ;
            
            if ( sscanf ( Arg ,
                          "%d,%d" , 
                          & LastMatrixAttrib -> Index ,
                          & LastMatrixAttrib -> Offset ) != 2 ) {
            
              ++ ArgError ;
              
              break ;
              
            }
            
            LastMatrixAttrib -> NumFields = ( CurrentKeyword == COMPILED8ADDKEY )
                                              ? 9
                                              : 8 ;
            
            ++ LastMatrixAttrib -> IsAddValue ;

            break ;

          }

          default : {
          
            ++ TokenError ;

            break ;
          
          }
        
        }
        
        break ;
        
      }

      case COMPILED8HASKEY :
      case COMPILED7HASKEY : {
      
        QueryComplete = 0 ;
        
        switch ( PrevKeyword ) {
        
          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case WIDGETNAMEKEY :
          case WIDGETCLASSKEY :
          case WIDGETCHILDOFKEY :
          case ANYWIDGETKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY : {
          
            if ( ScriptError ) {
            
              break ;
            
            }
              
            LastMatrixHasAttrib -> Next = CreateMatrixAttrib ( ) ;
            
            LastMatrixHasAttrib = LastMatrixHasAttrib -> Next ;

            LastMatrixHasAttrib -> Name = ( char * ) Malloc ( sizeof ( "compiled" ) ) ;
            
            strcpy ( LastMatrixHasAttrib -> Name ,
                     "compiled" ) ;
            
            if ( sscanf ( Arg ,
                          "%d,%d" , 
                          & LastMatrixHasAttrib -> Index ,
                          & LastMatrixHasAttrib -> Offset ) != 2 ) {
            
              ++ ArgError ;
              
              break ;
              
            }
            
            LastMatrixHasAttrib -> NumFields = ( CurrentKeyword == COMPILED8HASKEY )
                                               ? 9
                                               : 8 ;

            break ;

          }

          default : {
          
            ++ TokenError ;

            break ;
          
          }
          
        }

        break ;
        
      }

      case INPUTINSKEY : {
      
        QueryComplete = 0 ;
        
        switch ( PrevKeyword ) {
        
          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case WIDGETCLASSKEY :
          case WIDGETNAMEKEY :
          case WIDGETCHILDOFKEY :
          case ANYWIDGETKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY : {
         
            if ( ScriptError ) {
            
              break ;
            
            }

            LastMatrixAttrib -> Next = CreateMatrixAttrib ( ) ;
            
            LastMatrixAttrib = LastMatrixAttrib -> Next ;

            LastMatrixAttrib -> Name = ( char * ) Malloc ( sizeof ( "inputValue" ) ) ;
            
            strcpy ( LastMatrixAttrib -> Name ,
                     "inputValue" ) ;
            
            if ( sscanf ( Arg ,
                          "%d" ,
                          & LastMatrixAttrib -> Index ) != 1 ) {
                          
              ++ ArgError ;
                          
            }
            
            LastMatrixAttrib -> NumFields = 2 ;

            break ;

          }

          default : {
          
            ++ TokenError ;

            break ; 
          
          }
        
        }

        break ;
        
      }

      case INPUTREPKEY : {
      
        QueryComplete = 0 ;
        
        switch ( PrevKeyword ) {
        
          case INPUTVALUEKEY :
          case COMPILEDKEY :
          case WIDGETCLASSKEY :
          case WIDGETNAMEKEY :
          case WIDGETCHILDOFKEY :
          case ANYWIDGETKEY :
          case ATTRIBVALUEKEY :
          case SAMEVALUEKEY : {
          
            if ( ScriptError ) {
            
              break ;
            
            }

            LastMatrixAttrib -> Next = CreateMatrixAttrib ( ) ;
            
            LastMatrixAttrib = LastMatrixAttrib -> Next ;

            LastMatrixAttrib -> Name = ( char * ) Malloc ( sizeof ( "inputValue" ) ) ;
            
            strcpy ( LastMatrixAttrib -> Name ,
                     "inputValue" ) ;
            
            if ( sscanf ( Arg ,
                          "%d,%d" , 
                          & LastMatrixAttrib -> Index ,
                          & LastMatrixAttrib -> Offset ) != 2 ) {
                          
              ++ ArgError ;
              
            }
            
            LastMatrixAttrib -> NumFields = 2 ;

            break ;

          }
          
          default : {
          
            ++ TokenError ;

            break ;

          }
        
        }
        
        break ;
      
      }

    }

    if ( TokenError 
         || ArgError ) {
         
      ++ ScriptError ;

      if ( TokenError ) {
      
        sprintf ( logbf , 
                  "#% 6d - Token inatteso: %s=%s" ,
                  LineNumber ,
                  Token ,
                  Arg ) ;

      }
      
      if ( ArgError ) {
      
        sprintf ( logbf , 
                  "#% 6d - Argomento errato: %s=%s" ,
                  LineNumber ,
                  Token ,
                  Arg ) ;
      
      }
      
      log ( logbf ) ;

      fprintf ( stderr ,
                "pagmod: %s\n" ,
                logbf ) ;

    }

    PrevKeyword = CurrentKeyword ;

  }

  CloseFile ( ScriptFile ) ;

  free ( ScriptLine ) ;

  free ( Token ) ;

  free ( Arg ) ;

  if ( ScriptError 
       || ! QueryComplete ) {
  
    fprintf ( stderr ,
              "Script errato.\n" ) ;

    return - 1 ;
  
  }
  
  return 0 ;

}

static enum Keyword WhichKeyword ( const char * Token ) {
/*
 * Compare Token with predefined keywords.
 *
 * Return: the Keyword.
 */

  int i = 0 ;
  
# ifdef DEBUG
  DEBUG_ENTERFUNC("WhichKeyword");
# endif

  for ( i = 0 ;
        KeyTokenTable [ i ] . Key != NOKEY ;
        ++ i ) {
        
    if ( strcmp ( Token ,
                  KeyTokenTable [ i ] . Token ) == 0 ) {
                  
      return KeyTokenTable [ i ] . Key ;

    }

  }
  
  /* Unrecognized token. */

  return NOKEY ;

}

/* EOF. */

#ifndef PAGMOD_UTIL_H
#define PAGMOD_UTIL_H

/*
 * Date:
 *
 * 1997-07-18
 */

# include <stdio.h>

# include <malloc.h>

# include "log.h"


# define LF 0x0a

# define PATH_SZ ( 1024 + 1 )

# define PATHNAMELEN ( 1024 + 1 ) /* Posix Standard Limit. */

# define FILENAMELEN ( 256 + 1 ) /* Posix Standard Limit. */

# define LINELEN ( 10000 + 1 ) /* All arbitrary limits. */

# define WIDGETNAMELEN ( 50 + 1 ) 

# define INPUTVALUELEN ( 10000 + 1 )

# define LABELLEN ( 10 + 1 )

# define VALUELEN ( 20 + 1 ) 

# define DESCRLEN ( 100 + 1 )

extern char help_V [ ] ;

extern int ExitAfterScanScript ;

extern int QuietMode ;

extern int DoNotWriteModFile ;

extern int UseListFileName ;

extern int UsePageFileName ;

extern int BehaveAsFilter ;

# ifdef DEBUG
extern char * DebugPattern ;
# endif

extern int DoGrep ;

extern int DoAfterGrep ;

extern int AskConfirm ;

# define DEBUG_ENTERFUNC(str)\
if ( DebugPattern )\
  {\
  if ( strchr ( DebugPattern ,\
                'f' ) != NULL )\
    {\
    fprintf ( stderr ,\
              "f: %s\n" ,\
              str ) ;\
    }\
  } 

# define DEBUG_NEWATTRIB(AttribName)\
if ( DebugPattern )\
  {\
  if ( strchr ( DebugPattern ,\
                'a' ) != NULL )\
    {\
    fprintf ( stderr ,\
              "a: %-30s *%-10s.%s\n" ,\
              PageFileName ,\
              Handle -> Widget -> Name ,\
              AttribName ) ;\
    }\
  } 

# define DEBUG_CHGATTRIB(AttribName)\
if ( DebugPattern )\
  {\
  if ( strchr ( DebugPattern ,\
                'm' ) != NULL )\
    {\
    fprintf ( stderr ,\
              "m: %-30s *%-10s.%s\n" ,\
              PageFileName ,\
              Handle -> Widget -> Name ,\
              AttribName ) ;\
    }\
  }

#define DEBUG_GREP(AttribName,AttribValue)\
if ( DoGrep )\
  {\
  fprintf ( stderr ,\
            "*%s.%s:\t%s\n" ,\
            Handle -> Widget -> Name ,\
            AttribName ,\
            AttribValue ) ;\
  }

#define DEBUG_AFTERGREP(AttribName,AttribValue)\
if ( DoAfterGrep )\
  {\
  fprintf ( stderr ,\
            "*%s.%s:\t%s\n" ,\
            Handle -> Widget -> Name ,\
            AttribName ,\
            AttribValue ) ;\
  }

extern int Kchg ; /* ChangeAttribs counter. */

extern int Knew ; /* NewAttribs counter. */

extern int Krep ; /* CompiledReplace counter. */

extern int Kins ; /* CompiledInsert counter. */

extern int Kadd ; /* CompiledAdd counter. */

extern int Ktot ; /* Total counter. */

extern int Gpag ; /* */

extern int Gtot ; /* */

extern char * PageFileName ;

extern void Chop ( char * const String ) ;

extern void * Malloc ( size_t size ) ;

extern void CopyField ( char * * Cursor ,
                        char * Dest ) ;

extern void CopyPipeField ( char * * Cursor ,
                            char * Dest ) ;

extern void SkipPipeFields ( int ,
                             char * * ) ;
extern void SkipFields ( char * , int , char * * ) ;

extern void SkipWhiteSpaces ( char * * ) ;

extern FILE * OpenFile ( const char * Path ,
                         const char * Mode ) ;

extern void CloseFile ( FILE * fd ) ;

#endif /* PAGMOD_UTIL_H */

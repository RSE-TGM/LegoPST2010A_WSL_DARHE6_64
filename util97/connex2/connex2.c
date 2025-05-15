/*
 * connex2.c
 *
 * Date:
 *
 * 1997-07-08
 *
 * Version: 
 *
 * 1.2
 *
 * Description:
 *
 * Build the file 'S01.new' from a list of task files.
 * Make connections between input and output variables of the
 * tasks by matching each variable's tag name.
 * Require the file 'al_sim.conf'.
 * 
 * Functions:
 *
 * main
 * AddTaskListEntry
 * BuildConnections
 * SkipWhiteSpaces
 * CopyField
 * DeleteTrailingBlanks
 * GuessLineType
 * ProcessFiles
 * Process_f01_dat
 * Process_n04_dat
 * Read_list_file
 * SearchBackAndFore
 * VarComparef
 * Write_S01_Header
 * Write_S01_Tail
 */
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <getopt.h>
# include <string.h>
# include <errno.h>
# include <string.h>
#include <ctype.h>

# ifndef LINE_LEN
#   define LINE_LEN 500 /* Buffer for fgets. */
# endif
# ifndef TITLE_LEN 
#   define TITLE_LEN 100
# endif
# ifndef TASK_NAME_LEN 
#   define TASK_NAME_LEN 256  /* Posix limits for the file name */
# endif
# ifndef TASK_PATH_LEN
#   define TASK_PATH_LEN 1025 /* and complete path name.        */
# endif
# ifndef TASK_SPEC_LEN 
#   define TASK_SPEC_LEN 10
# endif
# ifndef TASK_TIME_LEN 
#   define TASK_TIME_LEN 10
# endif
# ifndef TASK_DESCR_LEN 
#   define TASK_DESCR_LEN 100
# endif
# ifndef TASK_COUNT 
#   define TASK_COUNT 100 /* Tasks. */
# endif
# ifndef VAR_COUNT
#   define VAR_COUNT 10000 /* Variables per task. */
# endif
# ifndef VAR_TAG_LEN 
#   define VAR_TAG_LEN 50
# endif
# ifndef VAR_NAME_LEN 
#   define VAR_NAME_LEN 9
# endif
# ifndef VAR_DESCR_LEN 
#   define VAR_DESCR_LEN 100 
# endif
# define OptionLinesTableDim 13
# define TaskLinesTableDim 3
enum LineType
  {
  /*
   * Types of line in the list file.
   */
  UNRECOGNIZED_LINE ,
  TITLE_LINE ,
  BASEPATH_LINE ,
  KEY_LINE ,
  HOST0_LINE ,
  AUTOM_TO_PROC_CONN_LINE ,
  PROC_TO_PROC_CONN_LINE ,
  INTERACTIVE_LINE ,
  IGNORE_NUMBERSIGN_LINE ,
  COMMENT_LINE ,
  MMI_HOSTNAME_SCADA_LINE ,
  S01_BM_LINE ,
  S01_BI_LINE ,
  MMI_LINE ,
  P_TASK_LINE ,
  R_TASK_LINE ,
  N_TASK_LINE 
  } ;
struct TypeKeyEntry
  {
  /*
   * Line type , Keyword pair.
   */
  enum LineType Type ;
  const char * Key ;
  } ;
struct TaskEntry
  {
  /*
   * Each task in the list file has these members.
   */
  char Type ;                     /* Type of task. */
  char Name [ TASK_NAME_LEN ] ;   /* Task name. */
  char Path [ TASK_PATH_LEN ] ;   /* Path name of the data file relative to the task. */
  char Time [ TASK_TIME_LEN ] ;   /* Time of execution. */
  char Descr [ TASK_DESCR_LEN ] ; /* Description. */
  } ;
struct VarEntry
  {
  /*
   * Each variable has these attributes.
   */
  char Tag [ VAR_TAG_LEN ] ;     /* Complete tag including Key. */
  char Name [ VAR_NAME_LEN ] ;   /* Var name. */
  char Descr [ VAR_DESCR_LEN ] ; /* Description including Tag. */
  int Connected ;                /* How many connections? */
  } ;
struct MatchEntry
  {
  /*
   * Matching output variable.
   */
  struct VarEntry * Var ; /* Points to the OutVarList entry. */
  int TaskIndex ;         /* Index in the TaskList. */
  } ;
static const char LIST_FILE_FN [ ] = "al_sim.conf" ; /* Input file. */
static const char OUT_LOG_FN [ ] = "connex2.out" ;        /* Logging. */
static const char S01_FN [ ] = "S01.new" ;                /* Output file. */
static const char F01_DAT_FN [ ] = "f01.dat" ;            /* Data file for type P task. */
static const char N04_DAT_FN [ ] = "proc/n04.dat" ;       /* Data file for type N task. */
static const char VAR_IN_KEY [ ] = "--IN--" ;
static const char VAR_UA_KEY [ ] = "--UA--" ;
static const char VAR_US_KEY [ ] = "--US--" ;
static const char HelpText [ ] = "\
\n\
connex2 - versione 1.2 1997-07-08\n\
\n\
         Abbinamento di ingressi e uscite delle task in base alle tag.\n\
\n\
File di input:  al_sim.conf			( File Lista )\n\
File di output: S01.new\n\
                connex2.out\n\
\n\
Opzioni riconosciute nel File Lista:\n\
\n\
TITLE=titolo   descrizione			( ammessi gli spazi )\n\
BASEPATH=basepath				( default: ../../legocad )\n\
KEY=identificatore delle tag			( default: @#K@ )\n\
HOST0=stringa stazione				( default: OS host guest )\n\
AUTOM_TO_PROC_CONN=[ENABLE | DISABLE]		( default: ENABLE )\n\
PROC_TO_PROC_CONN=[ENABLE | DISABLE]		( default: ENABLE )\n\
INTERACTIVE=[YES | NO]				( default: YES )\n\
IGNORE_NUMBERSIGN=[YES | NO]			( default: NO )\n\
MMI_HOSTNAME_SCADA=host name\n\
S01_BM=\n\
S01_BI=\n\
\n\
Commenti:\n\
rige che iniziano con # (numbersign)\n\
\n\
Formato delle task nel File Lista:\n\
#tipo nome      directory    filespec tempo    descrizione\n\
P     HPS000NG  HPS000NG     -        0.500000 High Pressure System - NG15.000\n\
R     HPSREG0   r_hpsreg0    H???     1.000000 High Pressure System - Regolation Task\n\
N     GASI      n_gasi       -        1.000000 Prova N04\n\
\n\
" ;
static struct TypeKeyEntry OptionLinesTable [ OptionLinesTableDim ] =
  {
    /* Line type. */          /* Keyword. */
  { TITLE_LINE              , "TITLE="              } ,
  { BASEPATH_LINE           , "BASEPATH="           } ,
  { KEY_LINE                , "KEY="                } ,
  { HOST0_LINE              , "HOST0="              } ,
  { AUTOM_TO_PROC_CONN_LINE , "AUTOM_TO_PROC_CONN=" } ,
  { PROC_TO_PROC_CONN_LINE  , "PROC_TO_PROC_CONN="  } ,
  { INTERACTIVE_LINE        , "INTERACTIVE="        } ,
  { IGNORE_NUMBERSIGN_LINE  , "IGNORE_NUMBERSIGN="  } ,
  { MMI_HOSTNAME_SCADA_LINE , "MMI_HOSTNAME_SCADA=" } ,
  { S01_BM_LINE             , "S01_BM="             } ,
  { S01_BI_LINE             , "S01_BI="             } ,
  { MMI_LINE                , "MMI_"                } ,
  { COMMENT_LINE            , "#"                   }
  } ;
static struct TypeKeyEntry TaskLinesTable [ TaskLinesTableDim ] =
  {
    /* Line type. */    /* Keyword. */
  { P_TASK_LINE       , "P"            } ,
  { R_TASK_LINE       , "R"            } ,
  { N_TASK_LINE       , "N"            } ,
  } ;
/* All the followings are initialized with default suitable values. */
static char Title [ TITLE_LEN ] ,
            Basepath [ 1025 ] = "../../legocad/" ,
            Key [ 10 ] = "@#K@" ,
            Host0 [ 50 ] = "OS host guest " ,
            Bm [ 100 ] = "" ,
            Bi [ 100 ] = "" ,
            Scada [ 100 ] = "" ;
static int AutomToProcConn = 1 ,
           ProcToProcConn = 1 ,
           Interactive = 1 ,
	   IgnoreNumbersign = 0 ;
static struct TaskEntry TaskList [ TASK_COUNT ] ;
static struct VarEntry * InVarList [ TASK_COUNT ] [ VAR_COUNT ] ,
                       * OutVarList [ TASK_COUNT ] [ VAR_COUNT ] ;
static int TaskCount ,
	   InVarCount [ TASK_COUNT ] ,
	   OutVarCount [ TASK_COUNT ] ;
static void AddTaskListEntry ( const char * ) ;
static int BuildConnections ( void ) ;
static void SkipWhiteSpaces ( const char * * ) ;
static void CopyField ( char * , 
			const char * * ) ;
static void DeleteTrailingBlanks ( char * ) ;
static enum LineType GuessLineType ( const char * ) ;
static int ProcessFiles ( void ) ;
static int Process_f01_dat ( FILE * ,
		             int ) ;
static int Process_n04_dat ( FILE * ,
			     int ) ;
static int Read_list_file ( void ) ;
static void SearchBackAndFore ( struct VarEntry * * ,
				struct VarEntry * * * ,
				struct VarEntry * * * ,
				int ) ;
static int VarComparef ( const void * ,
			 const void * ) ;
static int Write_S01_Header ( void ) ;
static int Write_S01_Tail ( void ) ;
int main ( int argc ,
           char * * argv )
  {
  /* Init global counters. */
  TaskCount = 0 ;
  memset ( InVarCount , 
	   0 ,
	   sizeof ( InVarCount ) ) ;
  memset ( OutVarCount ,
	   0 ,
	   sizeof ( OutVarCount ) ) ;
  memset ( InVarList ,
	   0 ,
	   sizeof ( InVarList ) ) ;
  memset ( OutVarList ,
	   0 ,
	   sizeof ( OutVarList ) ) ;
  /* Real stuff. */
  if ( argc > 1 )
    { 
    fprintf ( stderr ,
              HelpText ) ;
    return 1 ;
    }
  if ( Read_list_file ( ) == - 1 )
    {
    return 2 ; 
    }
  if ( Write_S01_Header ( ) == - 1 )
    { 
    return 3 ; 
    }
  if ( ProcessFiles ( ) == - 1 )
    { 
    return 4 ; 
    }
  if ( BuildConnections ( ) == - 1 )
    { 
    return 5 ; 
    }
  if ( Write_S01_Tail ( ) == - 1 )
    { 
    return 6 ; 
    }
  return 0 ;
  }
static void AddTaskListEntry ( const char * Line )
  {
  /*
   * Add the task specified in the list file to the table of tasks TaskList.
   */
  char FileName [ 256 ] ;
  char Spec [ TASK_SPEC_LEN ] ;
  TaskList [ TaskCount ] . Type = * Line ;
  ++ Line ;
  SkipWhiteSpaces ( & Line ) ;
  CopyField ( TaskList [ TaskCount ] . Name , 
	      & Line ) ;
  SkipWhiteSpaces ( & Line ) ;
  CopyField ( FileName , 
	      & Line ) ;
  sprintf ( TaskList [ TaskCount ] . Path , 
	    "%s/%s" ,
	    Basepath ,
	    FileName ) ;
  SkipWhiteSpaces ( & Line ) ;
  CopyField ( Spec ,
              & Line ) ;
  SkipWhiteSpaces ( & Line ) ;
  CopyField ( TaskList [ TaskCount ] . Time , 
	      & Line ) ;
  SkipWhiteSpaces ( & Line ) ;
  strcpy ( TaskList [ TaskCount ] . Descr , 
	   Line ) ;
  ++ TaskCount ;
  }
static int BuildConnections ( void )
  {
  /*
   * Scan the InVarList and OutVarList for tag matches.
   *
   * Return:  0, success.
   *         -1, failure.
   */
  FILE * S01File ,
       * outFile ;
  int t ;
  errno = 0 ;
  S01File = fopen ( S01_FN ,
		    "a" ) ;
  outFile = fopen ( OUT_LOG_FN ,
		    "w" ) ;
  if ( S01File == NULL 
       || outFile == NULL )
    {
    fprintf ( stderr ,
	      "connex2: Errore apertura file %s - errno %d\n" ,
	      ( S01File == NULL )
	      ? S01_FN
	      : OUT_LOG_FN ,
	      errno ) ;
    return - 1 ;
    }
  if ( Interactive )
    {
    printf ( "connex2: Elaborating interface tables...\n" ) ;
    }
  fprintf ( outFile ,
            "\n ------>> MULTIPLE CONNECTED INPUTS <<------ \n" ) ;
  /* For every task. */
  for ( t = 0 ;
	t < TaskCount ;
	++ t )
    {
    int i ;
    fprintf ( S01File ,
	      "****\n"
	      "%s\n" ,
	      TaskList [ t ] . Name ) ; 
    /* For every input. */
    for ( i = 0 ;
	  i < InVarCount [ t ] ;
	  ++ i )
      {
      int j ;
      struct MatchEntry MatchList [ 30 ] ;
      int MatchIndex = 0 ,
          k ;
      memset ( MatchList ,
	       0 ,
	       sizeof ( MatchList ) ) ;
      /* Search in every task outputs. */
      for ( j = 0 ;
	    j < TaskCount ;
            ++ j )
        {
        struct VarEntry * * FoundEntry = NULL ,
		        * * FirstEntry = NULL ,
		        * * LastEntry = NULL ,
			* * ActualEntry = NULL ;
        if ( j == t )
          {
          continue ; /* Skip the same task. */
          } 
	if ( ! ProcToProcConn 
             && TaskList [ t ] . Type == 'P'
             && TaskList [ j ] . Type == 'P' )
          {
          continue ;
          }
	if ( ! AutomToProcConn
             && TaskList [ t ] . Type == 'P'
             && TaskList [ j ] . Type == 'R' )
          {
          continue ;
          }
        FoundEntry = ( struct VarEntry * * ) bsearch ( & ( InVarList [ t ] [ i ] ) ,
	                                               OutVarList [ j ] ,
	                                               OutVarCount [ j ] ,
	                                               sizeof ( struct VarEntry * ) ,
	                                               VarComparef ) ; 
        if ( FoundEntry == NULL )
          {
          continue ; /* Skip to next task. */
          }
        /* 
         * bsearch found a matching entry. But if there are two or more
         * matching entries, we don't know which entry was found.
         * We know it is a sorted list, so from the found index
         * we search back and fore to find the whole range of matches.
         */
        SearchBackAndFore ( FoundEntry ,
			    & FirstEntry ,
			    & LastEntry ,
			    j ) ;
        ActualEntry = FirstEntry ;
	while ( ActualEntry <= LastEntry )
	  {
          MatchList [ MatchIndex ] . Var = ( * ActualEntry ) ;
	  MatchList [ MatchIndex ] . TaskIndex = j ;
	  ++ MatchIndex ;
	  ++ ActualEntry ;
	  }
        }
      /* An input can receive only from one output. */
      if ( MatchIndex > 0 )
        {
        char Output [ LINE_LEN ] ;
        memset ( Output ,
                 0 ,
                 sizeof ( Output ) ) ;
        ++ InVarList [ t ] [ i ] -> Connected ;
        sprintf ( Output ,
		  "%-10s%-10s%-10s ! %s" ,
		  InVarList [ t ] [ i ] -> Name ,
		  TaskList [ MatchList [ 0 ] . TaskIndex ] . Name ,
		  MatchList [ 0 ] . Var -> Name ,
		  MatchList [ 0 ] . Var -> Descr ) ;
        if ( Output [ 79 ] != '\0' )
          {
	  /* Warning. */
	  fprintf ( stderr ,
	            "connex2: Descrizione lunga: %s.\n" ,
	            Output ) ;
	  Output [ 79 ] = '\0' ;
	  }
        fprintf ( S01File ,
		  "%s\n" ,
		  Output ) ;
        ++ MatchList [ 0 ] . Var -> Connected ;
        if ( MatchIndex > 1 )
          {
          for ( k = 0 ;
	        k < MatchIndex ;
	        ++ k )
	    {
	    fprintf ( outFile ,
		      "M/I %-10s%-10s%-10s%-10s ! %s\n" ,
		      TaskList [ t ] . Name ,
		      InVarList [ t ] [ i ] -> Name ,
		      TaskList [ MatchList [ k ] . TaskIndex ] . Name ,
		      MatchList [ k ] . Var -> Name ,
		      MatchList [ k ] . Var -> Descr ) ;
            ++ MatchList [ k ] . Var -> Connected ;
            ++ InVarList [ t ] [ i ] -> Connected ;
            }
          }
        }
      else
        {
        InVarList [ t ] [ i ] -> Connected = 0 ;
        }
      }
    }
  {
  int t ;
  fprintf ( outFile ,
            "\n ------>>  NON CONNECTED INPUTS  <<------ \n" ) ;
  for ( t = 0 ;
        t < TaskCount ;
        ++ t )
    {
    int i ;
    for ( i = 0 ;
          i < InVarCount [ t ] ;
          ++ i )
      {
        if ( ! InVarList [ t ] [ i ] -> Connected )
          {
	  fprintf ( outFile ,
                    "N/I %-10s%-10s ! %s\n" ,
                    TaskList [ t ] . Name ,
                    InVarList [ t ] [ i ] -> Name ,
                    InVarList [ t ] [ i ] -> Descr ) ;
          }
      }
    }
    fprintf ( outFile ,
              "\n ------>>  CONNECTED INPUTS  <<------ \n" ) ;
    for ( t = 0 ;
          t < TaskCount ;
          ++ t )
      {
      int i ;
      for ( i = 0 ;
            i < InVarCount [ t ] ;
            ++ i )
        {
        if ( InVarList [ t ] [ i ] -> Connected )
          {
	  fprintf ( outFile ,
                    "C/I %-10s%-10s ! %s\n" ,
                    TaskList [ t ] . Name ,
                    InVarList [ t ] [ i ] -> Name ,
                    InVarList [ t ] [ i ] -> Descr ) ;
          }
        }
      }
    fprintf ( outFile ,
              "\n ------>>  NON CONNECTED OUTPUTS  <<------ \n" ) ;
    for ( t = 0 ;
          t < TaskCount ;
          ++ t )
      {
      int i ;
      for ( i = 0 ;
	    i < OutVarCount [ t ] ;
	    ++ i )
	{
        if ( ! OutVarList [ t ] [ i ] -> Connected )
          {
	  fprintf ( outFile ,
                    "N/O %-10s%-10s ! %s\n" ,
                    TaskList [ t ] . Name ,
                    OutVarList [ t ] [ i ] -> Name ,
                    OutVarList [ t ] [ i ] -> Descr ) ;
          }
        }
      }
    fprintf ( outFile ,
              "\n ------>>  CONNECTED OUTPUTS  <<------ \n" ) ;
    for ( t = 0 ;
          t < TaskCount ;
          ++ t )
      {
      int i ;
      for ( i = 0 ;
            i < OutVarCount [ t ] ;
            i ++ )
        {
        if ( OutVarList [ t ] [ i ] -> Connected )
          {
          fprintf ( outFile ,
                    "C/O %-10s%-10s ! %s\n" ,
                    TaskList [ t ] . Name ,
                    OutVarList [ t ] [ i ] -> Name ,
                    OutVarList [ t ] [ i ] -> Descr ) ;
          }
        }
      }
    }
  fclose ( S01File ) ;
  fclose ( outFile ) ;
  return 0 ;
}
static void SkipWhiteSpaces ( const char * * String )
  {
  /*
   * Forwards the String pointer skipping Locale space characters.
   */
  while ( isspace ( * * String  ) )
    {
    ++ ( * String ) ;
    }
  }
static void CopyField ( char * Field , 
			const char * * String )
  {
  /*
   * Copies all Locale non-space characters of String into Field
   * and forwards the String pointer.
   * Field is null-terminated.
   */
  while ( ! isspace ( * * String ) 
          && * * String != '\0' )
    {
    * Field = * * String ;
    Field ++ ;
    ++ ( * String ) ;
    }
  * Field = '\0' ;
  }
static void DeleteTrailingBlanks ( char * String )
  {
  /*
   * Delete final stream of blanks in String.
   */
  String += strlen ( String ) ;
  while ( isspace ( * ( String - 1 ) ) )
    {
    String -- ;
    }
  * String = '\0' ;
  }
static enum LineType GuessLineType ( const char * Line )
  {
  /*
   * Parses Line.
   *
   * Return: the LineType of Line.
   */
  if ( Line [ 0 ] == '\0' )
    {
    return COMMENT_LINE ;
    }
  {
  int i = 0 ;
  for ( i = 0 ;
        i < OptionLinesTableDim ;
        ++ i )
    {
    if ( strncmp ( OptionLinesTable [ i ] . Key ,
                   Line ,
                   strlen ( OptionLinesTable [ i ] . Key ) ) == 0 )
      {
      return OptionLinesTable [ i ] . Type ;
      }
    }
  }
  /* The line is a task entry. */
  {
  int i = 0 ;
  for ( i = 0 ;
        i < TaskLinesTableDim ;
        ++ i )
    {
    int j = 0 ;
    int Match = 0 ;
    for ( j = 0 ;
          j < strlen ( TaskLinesTable [ i ] . Key ) ;
          ++ j )
      {
      if ( TaskLinesTable [ i ] . Key [ j ] == Line [ j ] )
        {
        Match = 1 ;
        }
      else
        {
        Match = 0 ;
        break ;
        }
      }
    if ( Match )
      {
      if ( isspace ( Line [ j + 1 ] ) )
        {
        return TaskLinesTable [ i ] . Type ;
        }
      else
        {
        break ;
        }
      }
    }
  }
  /* No match found. */
  return UNRECOGNIZED_LINE ;
  }
static int ProcessFiles ( void )
  {
  /*
   * Process every task file.
   *
   * Return:  0, success.
   *         -1, failure.
   */
  int Ret = 0 ;
  int t ;
  if ( Interactive )
    {
    printf ( "connex2: Preparing interface variable tables.\n" ) ;
    }
  for ( t = 0 ;
        t < TaskCount ;
        ++ t )
    {
    FILE * TaskFile = NULL ;
    char PathName [ 1026 ] ;
    errno = 0 ;
    sprintf ( PathName ,
	      "%s/%s" ,
	      TaskList [ t ] . Path ,
	      ( TaskList [ t ] . Type == 'P' )
	      ? F01_DAT_FN 
	      : ( ( TaskList [ t ] . Type == 'R' )
	        ? F01_DAT_FN
	        : ( ( TaskList [ t ] . Type == 'N' )
	          ? N04_DAT_FN : "" ) ) ) ;
    TaskFile = fopen ( PathName ,
		       "r" ) ;
    if ( TaskFile == NULL )
      { 
      fprintf ( stderr ,
		"connex2: Errore apertura file %s - errno %d\n" ,
		PathName ,
		errno ) ;
      return - 1 ;
      }
    /* Process file. */
    if ( TaskList [ t ] . Type == 'P'
         && Process_f01_dat ( TaskFile , 
                              t ) == - 1 )
      { 
      Ret = - 1 ; 
      }
    else
      {
      if ( TaskList [ t ] . Type == 'R'
           && Process_f01_dat ( TaskFile ,
                                t ) == - 1 )
        {
        Ret = - 1 ;
        }
      else
        {
        if ( TaskList [ t ] . Type == 'N'
             && Process_n04_dat ( TaskFile ,
                                  t ) == - 1 )
          { 
          Ret = - 1 ;
          }
        }
      }
    fclose ( TaskFile ) ;
    if ( Ret == - 1 )
      { 
      return - 1 ; 
      }
    }
  /* 
   * Have all in and out variables.
   * Sort the Var lists. 
   */
  for ( t = 0 ;
        t < TaskCount ;
        ++ t )
    {
    qsort ( InVarList [ t ] ,
            InVarCount [ t ] ,
            sizeof ( struct VarEntry * ) ,
            VarComparef ) ;
    qsort ( OutVarList [ t ] ,
            OutVarCount [ t ] ,
            sizeof ( struct VarEntry * ) ,
            VarComparef ) ;
    }
  return 0 ;
  }
static int Process_f01_dat ( FILE * DatFile ,
                             int TaskIndex )
  {
  /*
   * Retrieve every tagged input and output variable from the f01.dat file.
   *
   * Return:  0, success.
   *         -1, failure.
   */
  char Line [ LINE_LEN ] ;
  while ( fgets ( Line ,
                  sizeof ( Line ) , 
                  DatFile ) != NULL )
    {
    const char * KeyIndex = NULL ;
    const char * LineCursor = Line ;
    if ( strstr ( Line , 
                 "INGRESSI DI TUTTI I MODULI" ) )
      {
      break ; /* End of variable definitions. */
      }
    KeyIndex = strstr ( Line ,
			Key ) ;
    if ( KeyIndex == NULL )
      {
      continue ; /* Not a tagged variable. */ 
      }
    if ( strstr ( KeyIndex ,
                  "_X" ) )
      {
      continue ;
      }
    Line [ strlen ( Line ) - 1 ] = '\0' ; /* Chop terminating new-line. */
    if ( strstr ( Line , 
                  VAR_IN_KEY ) )
      { 
      /* Input IN variable. */
      InVarList [ TaskIndex ] [ InVarCount [ TaskIndex ] ] = ( struct VarEntry * ) malloc ( sizeof ( struct VarEntry ) ) ;
      memset ( InVarList [ TaskIndex ] [ InVarCount [ TaskIndex ] ] ,
               0 ,
               sizeof ( struct VarEntry ) ) ;
      CopyField ( InVarList [ TaskIndex ] [ InVarCount [ TaskIndex ] ] -> Name ,
		  & LineCursor ) ;
      LineCursor = KeyIndex ;
      CopyField ( InVarList [ TaskIndex ] [ InVarCount [ TaskIndex ] ] -> Tag ,
		  & LineCursor ) ;
      /* Tip: have to delete the final #. */
      if ( IgnoreNumbersign )
        {
        char * NumbersignIndex = strrchr ( InVarList [ TaskIndex ] [ InVarCount [ TaskIndex ] ] -> Tag ,
				           '#' ) ;
	if ( * ( NumbersignIndex + 1 ) == '\0' )
	  {
	  * NumbersignIndex = '\0' ;
	  }
        }
      DeleteTrailingBlanks ( ( char * ) KeyIndex ) ;
      strcpy ( InVarList [ TaskIndex ] [ InVarCount [ TaskIndex ] ] -> Descr ,
	       KeyIndex ) ;
      ++ InVarCount [ TaskIndex ] ;
      }
    else
      {
      if ( strstr ( Line , 
                    VAR_UA_KEY ) 
           || strstr ( Line , 
                       VAR_US_KEY ) )
        {
        /* Output US-UA variable. */
        OutVarList [ TaskIndex ] [ OutVarCount [ TaskIndex ] ] = ( struct VarEntry * ) malloc ( sizeof ( struct VarEntry ) ) ;
        memset ( OutVarList [ TaskIndex ] [ OutVarCount [ TaskIndex ] ] ,
	         0 ,
	         sizeof ( struct VarEntry ) ) ;
        CopyField ( OutVarList [ TaskIndex ] [ OutVarCount [ TaskIndex ] ] -> Name ,
	            & LineCursor ) ;
        LineCursor = KeyIndex ;
        CopyField ( OutVarList [ TaskIndex ] [ OutVarCount [ TaskIndex ] ] -> Tag ,
	            & LineCursor ) ;
        /* Tip: have to delete the final #. */
        if ( IgnoreNumbersign )
          {
          char * NumbersignIndex = strrchr ( OutVarList [ TaskIndex ] [ OutVarCount [ TaskIndex ] ] -> Tag ,
                                             '#' ) ;
          if ( * ( NumbersignIndex + 1 ) == '\0' )
            {
            * NumbersignIndex = '\0' ;
            }
          }
        DeleteTrailingBlanks ( ( char * ) KeyIndex ) ;
        strcpy ( OutVarList [ TaskIndex ] [ OutVarCount [ TaskIndex ] ] -> Descr ,
	         KeyIndex ) ;
        ++ OutVarCount [ TaskIndex ] ;
        }
      }
    }
  return 0 ;
  }
static int Process_n04_dat ( FILE * DatFile ,
                             int TaskIndex )
  {
  /*
   * Retrieve every tagged input and output variable from the 'proc/n04.dat' file.
   *
   * Return:  0, success.
   *         -1, failure.
   */
  enum LoopState
    {
    BLOCK_NAME_LOOP ,
    NUM_INPUT_LOOP ,
    INPUT_LOOP ,
    NUM_OUTPUT_LOOP ,
    OUTPUT_LOOP ,
    STARS_LOOP
    } ;
  char Line [ LINE_LEN ] ;
  enum LoopState State ;
  int BlockNum = 0 , 
      VarNum = 0 ;
  /* Skip the first line. */
  fgets ( Line ,
	  sizeof ( Line ) ,
	  DatFile ) ;
  /* Get the number of blocks. */ 
  fgets ( Line ,
	  sizeof ( Line ) , 
	  DatFile ) ;
  BlockNum = atoi ( Line ) ;
  /* Begin the real stuff. */
  State = BLOCK_NAME_LOOP ;
  VarNum = 0 ;
  while ( ( fgets ( Line ,
		    sizeof ( Line ) ,
		    DatFile ) ) 
	  && ( BlockNum > 0 ) )
    {
    Line [ strlen ( Line ) - 1 ] = '\0' ; /* Chop terminating new-line. */
    switch ( State )
      {
    case BLOCK_NAME_LOOP :
      {
      /* Block name... ignore. */
      State = NUM_OUTPUT_LOOP ;
      break ;
      }
    case NUM_INPUT_LOOP :
      {
      /* Number of input variables. */
      VarNum = atoi ( Line ) ;
      if ( VarNum == 0 )
        {
        State = STARS_LOOP ;
        }
      else
        {
        State = INPUT_LOOP ;
        }
      break ;
      }
    case INPUT_LOOP :
      {
      const char * LineCursor = Line ,
                 * KeyIndex = NULL ;
      -- VarNum ;
      /* Is it tagged? */
      KeyIndex = strstr ( Line ,
                          Key ) ;
      if ( KeyIndex == NULL )
        {
        if ( VarNum == 0 )
          {
          /* Input variables finished. */
	  State = STARS_LOOP ;
	  }
	  break ;
	}
      /* Add input variable to list. */
      InVarList [ TaskIndex ] [ InVarCount [ TaskIndex ] ] = ( struct VarEntry * ) malloc ( sizeof ( struct VarEntry ) ) ;
      memset ( InVarList [ TaskIndex ] [ InVarCount [ TaskIndex ] ] ,
               0 ,
               sizeof ( struct VarEntry ) ) ;
      CopyField ( InVarList [ TaskIndex ] [ InVarCount [ TaskIndex ] ] -> Name ,
                  & LineCursor ) ;
      SkipWhiteSpaces ( & LineCursor ) ;
      strcpy ( InVarList [ TaskIndex ] [ InVarCount [ TaskIndex ] ] -> Descr ,
               LineCursor ) ;
      CopyField ( InVarList [ TaskIndex ] [ InVarCount [ TaskIndex ] ] -> Tag ,
                  & KeyIndex ) ;
      ++ InVarCount [ TaskIndex ] ;
      if ( VarNum == 0 )
        {
        /* Input variables finished. */
	State = STARS_LOOP ;
	}
	break ;
      }
    case NUM_OUTPUT_LOOP :
      {
      /* Number of output variables. */
      VarNum = atoi ( Line ) ;
      if ( VarNum == 0 )
        {
        State = NUM_INPUT_LOOP ;
        }
      else
        {
        State = OUTPUT_LOOP ;
        }
      break ;
      }
    case OUTPUT_LOOP :
      {
      const char * LineCursor = Line ,
                 * KeyIndex = NULL ;
      -- VarNum ;
      /* Is it tagged? */
      KeyIndex = strstr ( Line ,
                          Key ) ;
      if ( KeyIndex == NULL )
        { 
	if ( VarNum == 0 )
	  {
	  State = NUM_INPUT_LOOP ;
	  }
	break ; 
	} 
      /* Add output variable to list. */
      OutVarList [ TaskIndex ] [ OutVarCount [ TaskIndex ] ] = ( struct VarEntry * ) malloc ( sizeof ( struct VarEntry ) ) ;
      memset ( OutVarList [ TaskIndex ] [ OutVarCount [ TaskIndex ] ] ,
               0 ,
      sizeof ( struct VarEntry ) ) ;
      CopyField ( OutVarList [ TaskIndex ] [ OutVarCount [ TaskIndex ] ] -> Name ,
                  & LineCursor ) ;
      SkipWhiteSpaces ( & LineCursor ) ;
      strcpy ( OutVarList [ TaskIndex ] [ OutVarCount [ TaskIndex ] ] -> Descr ,
               LineCursor ) ;
      CopyField ( OutVarList [ TaskIndex ] [ OutVarCount [ TaskIndex ] ] -> Tag ,
                  & KeyIndex ) ;
      OutVarCount [ TaskIndex ] ++ ;
      if ( VarNum == 0 )
        {
        /* Output variables finished. */
        State = NUM_INPUT_LOOP ;
        }
      break ;
      }
    case STARS_LOOP :
      {
      /* Four stars... ignore. */
      -- BlockNum ;
      State = BLOCK_NAME_LOOP ;
      break ;
      }
      }
    }
  return 0 ;
  }
static int Read_list_file ( void )
  {
  /*
   * Read FILE_LIST_FN to initialize the program.
   *
   * Return:  0, success.
   *         -1, failure.
   */
  FILE * ListFile ;
  char Line [ LINE_LEN ] ;
  int TitleLinePresent = 0 ;
  errno = 0 ;
  ListFile = fopen ( LIST_FILE_FN , 
		     "r" ) ;
  if ( ListFile == NULL )
    { 
    fprintf ( stderr ,
	      "connex2: Impossibile aprire il file %s - errno: %d\n" , 
	      LIST_FILE_FN , 
	      errno ) ;
    return - 1 ; 
    }
  if ( Interactive )
    { 
    printf ( "connex2: Reading %s...\n" ,
             LIST_FILE_FN ) ; 
    }
  while ( fgets ( Line ,
		  sizeof ( Line ) ,
		  ListFile ) != NULL )
    {
    enum LineType Type ; 
    char * Argument ;
    Line [ strlen ( Line ) - 1 ] = '\0' ; /* Chop terminating new-line. */
    Type = GuessLineType ( Line ) ;
    Argument = strchr ( Line , '=' ) + 1 ;
    switch ( Type )
      {
    case TITLE_LINE :
      {
      strcpy ( Title , 
               Argument ) ;
      TitleLinePresent = 1 ;
      break ;
      }
    case BASEPATH_LINE :
      {
      strcpy ( Basepath , 
	       Argument ) ;
      break ;
      }
    case KEY_LINE :
      {
      strcpy ( Key , 
               Argument ) ;
      break ;
      }
    case HOST0_LINE :
      {
      strcpy ( Host0 , 
	       Argument ) ;
      break ;
      }
    case AUTOM_TO_PROC_CONN_LINE :
      {
      if ( strcmp ( "DISABLE" , 
	            Argument ) == 0 )
	{
	AutomToProcConn = 0 ;
	}
      else
        {
        if ( strcmp ( "ENABLE" , 
	              Argument ) == 0 )
	  {
	  AutomToProcConn = 1 ;
	  }
	else
	  {
	  fprintf ( stderr ,
		    "connex2: %s: riga %s non valida.\n" ,
		    LIST_FILE_FN , 
		    Line ) ;
	  }
	}
      break ;
      }
    case PROC_TO_PROC_CONN_LINE :
      {
      if ( strcmp ( "DISABLE" , 
	            Argument ) == 0 )
        {
        ProcToProcConn = 0 ;
        }
      else
        {
        if ( strcmp ( "ENABLE" , 
		      Argument ) == 0 )
          {
          ProcToProcConn = 1 ;
          }
        else
          {
          fprintf ( stderr ,
	            "connex2: %s: riga %s non valida.\n" ,
                    LIST_FILE_FN , 
                    Line ) ;
          }
        }
      break ;
      }
    case INTERACTIVE_LINE :
      {
      if ( strcmp ( "YES" , 
                    Argument ) == 0 )
        {
        Interactive = 1 ;
        }
      else
        {
        if ( strcmp ( "NO" , 
		      Argument ) == 0 )
          {
          Interactive = 0 ;
          }
        else
          {
          fprintf ( stderr ,
                    "connex2: %s: riga %s non valida.\n" ,
                    LIST_FILE_FN ,
                    Line ) ;
          }
        }
      break ;
      }
    case IGNORE_NUMBERSIGN_LINE :
      {
      if ( strcmp ( "YES" , 
	            Argument ) == 0 )
        {
        IgnoreNumbersign = 1 ;
        }
      else
        {
        if ( strcmp ( "NO" , 
		      Argument ) == 0 )
          {
          IgnoreNumbersign = 0 ;
          }
        else
          {
          fprintf ( stderr ,
	            "connex2: %s: riga %s non valida.\n" ,
	            LIST_FILE_FN ,
	            Line ) ;
          }
        }
      break ;
      }
    case MMI_HOSTNAME_SCADA_LINE :
      {
      strcpy ( Scada ,
               Argument ) ;
      break ;
      }
    case S01_BM_LINE :
      {
      strcpy ( Bm ,
               Argument ) ;
      break ;
      }
    case S01_BI_LINE :
      {
      strcpy ( Bi ,
               Argument ) ;
      break ;
      }
    case P_TASK_LINE : 
    case R_TASK_LINE :
    case N_TASK_LINE :
      {
      AddTaskListEntry ( Line ) ;
      break ;
      }
    case COMMENT_LINE :
      {
      break ; /* Skip... */
      }
    case UNRECOGNIZED_LINE :
      {
      fprintf ( stderr ,
                "connex2: %s: Linea non riconosciuta: %s\n" ,
                LIST_FILE_FN ,
                Line ) ;
      break ;
      }
      }
    }
  fclose ( ListFile ) ;
  if ( ! TitleLinePresent )
    {
    fprintf ( stderr ,
              "connex2: %s: Manca il campo TITLE\n" ,
              LIST_FILE_FN ) ;
    return - 1 ;
    }
  return 0 ;
  }
static void SearchBackAndFore ( struct VarEntry * * FoundEntry ,
				struct VarEntry * * * FirstEntry ,
				struct VarEntry * * * LastEntry ,
				int TaskIndex )
  {
  /*
   * Fetch the table for the same tag before and after the found entry.
   * Note: check the table boundaries.
   */
  struct VarEntry * * BackLimit = & ( OutVarList [ TaskIndex ] [ 0 ] ) - 1 ,
                  * * ForeLimit = & ( OutVarList [ TaskIndex ] [ OutVarCount [ TaskIndex ] - 1 ] ) + 1 ;
  * FirstEntry = FoundEntry ;
  while ( ( ( * FirstEntry ) - 1 ) > BackLimit )
    {
    if ( strcmp ( ( ( * ( ( * FirstEntry ) - 1 ) ) ) -> Tag ,
                  ( * FoundEntry ) -> Tag ) != 0 )
      {
      break ;
      }
    ( * FirstEntry ) -- ;
    }
  * LastEntry = FoundEntry ;
  while ( ( ( * LastEntry ) + 1 ) < ForeLimit )
    {
    if ( strcmp ( ( ( * ( ( * LastEntry ) + 1 ) ) ) -> Tag ,
                  ( * FoundEntry ) -> Tag ) != 0 )
      {
      break ;
      }
    ( * LastEntry ) ++ ;
    }
  }
static int VarComparef ( const void * Var1 ,
			 const void * Var2 )
  {
  struct VarEntry * * Entry1 = ( struct VarEntry * * ) Var1 ,
		  * * Entry2 = ( struct VarEntry * * ) Var2 ;
  return strcmp ( ( * Entry1 ) -> Tag ,
		  ( * Entry2 ) -> Tag ) ;
  }
static int Write_S01_Header ( void )
  {
  /* 
   * Write the Head of the S01 file. 
   *
   * Return:  0, success.
   *         -1, failure.
   */
  FILE * S01File ;
  int i = 0 ;
  errno = 0 ;
  S01File = fopen ( S01_FN , 
		    "w" ) ;
  if ( S01File == NULL )
    {
    fprintf ( stderr ,
	      "connex2: Impossibile aprire il file %s - errno: %d\n" , 
	      S01_FN , 
	      errno ) ;
    return - 1 ; 
    }
  fputs ( "****\n" , 
	  S01File ) ;
  fprintf ( S01File , 
	    "%s\n" ,
	    Title ) ;
  fputs ( "****\n" , 
	  S01File ) ;
  for ( i = 0 ;
	i < TaskCount ;
	i ++ )
    {
    fprintf ( S01File ,
	      "%s %s\n" ,
              TaskList [ i ] . Name ,
              TaskList [ i ] . Descr ) ;
    }
  fputs ( "****\n" , 
	  S01File ) ;
  for ( i = 0 ;
	i < TaskCount ;
	i ++ )
    {
    if ( TaskList [ i ] . Type == 'P' )
      {
      fprintf ( S01File ,
	        "%s/\tP\n" ,
                TaskList [ i ] . Path ) ;
      }
    else
      {
      if ( TaskList [ i ] . Type == 'R' )
        {
        FILE * RTaskFile ;
        char RTaskPathName [ 1025 ] ;
        char Line [ LINE_LEN ] ;
        sprintf ( RTaskPathName ,
                  "%s/%s" ,
		  TaskList [ i ] . Path ,
		  F01_DAT_FN ) ;
        RTaskFile = fopen ( RTaskPathName ,
			    "r" ) ;
        if ( RTaskFile == NULL )
          {
	  fprintf ( stderr ,
		    "connex2: Errore apertura file %s - errno: %d\n" ,
		    RTaskPathName ,
		    errno ) ;
	  fclose ( S01File ) ;
          return - 1 ;
          }
        /* Read the RTask file for the MMI field. */
        fgets ( Line ,
	        sizeof ( Line ) ,
	        RTaskFile ) ;
        fgets ( Line ,
	        sizeof ( Line ) ,
	        RTaskFile ) ;
        fclose ( RTaskFile ) ;
        fprintf ( S01File ,
	          "%s/\tR\t%s\t%c\n" ,
                  TaskList [ i ] . Path ,
                  TaskList [ i ] . Name ,
		  Line [ 0 ] ) ;
        }
      else
        {
        if ( TaskList [ i ] . Type == 'N' )
          {
          fprintf ( S01File ,
	            "%s/\tN\t%s\n" ,
                    TaskList [ i ] . Path ,
		    TaskList [ i ] . Name ) ;
          }
        }
      }
    }
  fputs ( "****\n" , 
	  S01File ) ;
  for ( i = 0 ;
	i < TaskCount ;
	i ++ )
    {
    fprintf ( S01File ,
	      "%s\t%s/\n" ,
	      Host0 ,
	      TaskList [ i ] . Path ) ;
    }
  fputs ( "****\n" , 
	  S01File ) ;
  for ( i = 0 ;
	i < TaskCount ;
        i ++ )
    {
    fprintf ( S01File ,
	      "%s\n" ,
	      TaskList [ i ] . Time ) ;
    }
  fclose ( S01File ) ;
  return 0 ;
  }
static int Write_S01_Tail ( void )
  {
  /* 
   * Write the Tail of the S01 file. 
   *
   * Return:  0, success.
   *         -1, failure.
   */
  FILE * S01File ;
  int i = 0 ;
  errno = 0 ;
  S01File = fopen ( S01_FN , 
		    "a" ) ;
  if ( S01File == NULL )
    {
    fprintf ( stderr ,
	      "connex2: Impossibile aprire il file %s - errno: %d\n" , 
	      S01_FN , 
	      errno ) ;
    return - 1 ; 
    }
  fputs ( "****\n" , 
	  S01File ) ;
  fprintf ( S01File , 
	    "BM %s\nSCADA %s\nBI %s\n" ,
	    Bm ,
	    Scada ,
	    Bi ) ;
  fputs ( "****\n" , 
	  S01File ) ;
  fclose ( S01File ) ;
  return 0 ;
  }
/* EOF. */

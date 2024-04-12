/*
 * iconregmod.c
 *
 * Description:
 *
 * Comparing the two '.frm' files and retrieving values
 * from inputValue in 'old.pag' creates an inputValue resource for 'new.pag'.
 *
 * Date:
 *
 * 1997-07-18
 *
 * Functions:
 *
 * IconRegMod
 * CreateInputValueString
 * AddVariableToInputValue
 * GetFrm
 */

# include "iconregmod.h"

# include <stdio.h>

# include <stdlib.h>

# include <sys/types.h>

# include <sys/stat.h>

# include <ctype.h>

# include <unistd.h>

# include <errno.h>

# include <string.h>

# include "util.h"

#define	SP 040

#define	LVDTBL_DIM 500

struct LVDTBL {

 char label [ LABELLEN ] ;
 
 char value [ VALUELEN ] ;
 
 char descr [ DESCRLEN ] ;
 
 int index ;

} ;

static struct LVDTBL OldLvdTbl [ LVDTBL_DIM ] ;

static struct LVDTBL NewLvdTbl [ LVDTBL_DIM ] ;

static void CreateInputValueString ( char * OldInputValue ,
                                     char * NewInputValue ,
                                     int OldVarNum ,
                                     int NewVarNum ) ;

static void AddVariableToInputValue ( char * * InputValueCursor ,
                                      char * Value ,
                                      char * Descr ) ;

static int GetFrm ( char * frmbn ,
                    struct LVDTBL * tblp ,
                    int s_sw ) ;

int IconRegMod ( char * OldModuleName ,
                 char * NewModuleName ,
                 char * OldInputValue ,
                 char * NewInputValue ) {
/*
 * Creates a new inputValue string as specified in new module.
 * Starting from the side difference between OldModuleName.frm
 * and NewModuleName.frm, for all the variables that are the same
 * copy in NewInputValue the entry in OldInputValue.
 * Add the new variables with defaults from NewModuleName.frm.
 *
 * Return:  0 success.
 *         -1 failure.
 */
                  
  int OldVarNum ,
      NewVarNum ;
      
# ifdef DEBUG
  DEBUG_ENTERFUNC("IconRegMod");
# endif

  OldVarNum = GetFrm ( OldModuleName ,
                       OldLvdTbl ,
                       1 ) ;
                       
  if ( OldVarNum == - 1 ) {
  
    return - 1 ;
  
  }

  NewVarNum = GetFrm ( NewModuleName ,
                       NewLvdTbl ,
                       0 ) ;
           
  if ( NewVarNum == - 1 ) {
  
    return - 1 ;
  
  }

  CreateInputValueString ( OldInputValue ,
                           NewInputValue ,
                           OldVarNum ,
                           NewVarNum ) ;

  return 0 ;
    
}

static void CreateInputValueString ( char * OldInputValue ,
                                     char * NewInputValue ,
                                     int OldVarNum ,
                                     int NewVarNum ) {
/*
 * As we find that a new lvd variable is in old lvd ,
 * we add the OldInputValue entry in the NewInputValue.
 * If the description in the two lvd is different,
 * we get that in new lvd.
 */
   
  char * NewInputValueCursor = NewInputValue ;
   
  struct LVDTBL * NewLvdTblCursor = NewLvdTbl ;
  
  int NewVarCounter = 0 ;
  
  char NewValue [ INPUTVALUELEN ] ,
       NewDescr [ DESCRLEN ] ;
   
# ifdef DEBUG
  DEBUG_ENTERFUNC("CreateInputValueString");
# endif

  while ( NewVarCounter < NewVarNum ) {
  
    char * OldInputValueCursor = OldInputValue ;
    
    struct LVDTBL * OldLvdTblCursor ;
    
    OldLvdTblCursor = ( struct LVDTBL * ) bsearch ( NewLvdTblCursor ,
                                                    OldLvdTbl ,
                                                    OldVarNum ,
                                                    sizeof ( struct LVDTBL )  ,
                                                    ( int ( * ) ( const void * ,
                                                                  const void * ) ) strcmp ) ;
    
    if ( OldLvdTblCursor != NULL ) {
       
      char * OldInputValueCursor = OldInputValue ;
      
      SkipPipeFields ( OldLvdTblCursor -> index * 2 ,
                       & OldInputValueCursor ) ;
                       
      SkipWhiteSpaces ( & OldInputValueCursor ) ;
      
      CopyPipeField ( & OldInputValueCursor ,
                      NewValue ) ;
      
      /*
       * If the description in the two .frm are the same,
       * we must use that in the OldInputValue.
       * Otherwise use that from the new.frm.
       */
       
      if ( strcmp ( OldLvdTblCursor -> descr ,
                    NewLvdTblCursor -> descr ) == 0 ) {
      
        SkipWhiteSpaces ( & OldInputValueCursor ) ;
        
        CopyPipeField ( & OldInputValueCursor ,
                        NewDescr ) ;
    
      } else {
      
        strcpy ( NewDescr ,
                 NewLvdTblCursor -> descr ) ;
      
      }
    
    } else {
    
      strcpy ( NewValue ,
               NewLvdTblCursor -> value ) ;
               
      strcpy ( NewDescr ,
               NewLvdTblCursor -> descr ) ;
    
    }
    
    AddVariableToInputValue ( & NewInputValueCursor ,
                              NewValue ,
                              NewDescr ) ;
    ++ NewVarCounter ;
    
    ++ NewLvdTblCursor ;

  }
  
}

static void AddVariableToInputValue ( char * * InputValueCursor ,
                                      char * Value ,
                                      char * Descr ) {

# ifdef DEBUG
  DEBUG_ENTERFUNC("AddVariableToInputValue");
# endif

  * * InputValueCursor = '|' ;
  
  ++ * InputValueCursor ;

  while ( * Value != '\0' ) {
  
    * * InputValueCursor = * Value ;
    
    ++ * InputValueCursor ;
    
    ++ Value ;
  
  }
  
  * * InputValueCursor = '|' ;
  
  ++ * InputValueCursor ;

  * * InputValueCursor = ' ' ;
  
  ++ * InputValueCursor ;
  
  * * InputValueCursor = '|' ;
  
  ++ * InputValueCursor ;

  while ( * Descr != '\0' ) {
  
    * * InputValueCursor = * Descr ;
    
    ++ * InputValueCursor ;
    
    ++ Descr ;
  
  }

  * * InputValueCursor = '|' ;
  
  ++ * InputValueCursor ;
  
  * * InputValueCursor = ' ' ;
  
  ++ * InputValueCursor ;

  * * InputValueCursor = '\0' ;

}

/*----------------------------------------------------------------------*/
/*	GetFrm()	Legge e analizza il file passato in arg. e
			riempie la tabella di cui e' dato il puntatore.
			Ritorna il numero di elementi della tabella	*/

static int GetFrm ( char * frmbn ,
                    struct LVDTBL * tblp ,
                    int s_sw ) {
FILE*	frmfp;
char	frmfn[256];
char	frmbf[256];
int	frmn;
struct	LVDTBL*	tblpsv;
char*	ppp;
char*	sss;
char*	ttt;
char*	vvv;

# ifdef DEBUG
  DEBUG_ENTERFUNC("GetFrm");
# endif

	tblpsv	= tblp;
	
	memset ( tblp ,
	         0 ,
	         sizeof ( struct LVDTBL ) * LVDTBL_DIM ) ;

/*......................................................................*/
/*	Open file *.frm							*/

	strcpy( frmfn, frmbn );
	strcat( frmfn, ".frm" );

	frmn	= 0;
	errno	= 0;
	frmfp	= OpenFile ( frmfn, "r" );
	if( frmfp == NULL )
	{
		return	(-1);
	}
/*----------------------------------------------------------------------*/
/*	Loop di lettura 						*/

	while( (ppp = fgets( frmbf, sizeof(frmbf), frmfp )) != NULL )
	{
		Chop ( ppp ) ;
		/* if( (ppp = strchr( frmbf, LF )) != NULL ) *ppp = 0; */

/*......................................................................*/
		ttt	= strstr( frmbf, "label:" );
		if( ttt != NULL )
		{
			ttt	+= strlen( "label:" );
			SkipWhiteSpaces ( & ttt ) ;
			CopyField ( & ttt , (*tblp).label ) ;
			continue;
		}

/*......................................................................*/
		ttt	= strstr( frmbf, "value:" );
		if( ttt != NULL )
		{
			ttt	+= strlen( "value:" );
			SkipWhiteSpaces ( & ttt ) ;
			CopyField ( & ttt , (*tblp).value ) ;
			continue;
		}

/*......................................................................*/
		ttt	= strstr( frmbf, "descr:" );
		if( ttt != NULL )
		{
			if( strlen( (*tblp).label ) == 0 ) {
			  continue;
			}
			ttt	+= strlen( "descr:" );
			SkipWhiteSpaces ( & ttt ) ;
			strcpy( (*tblp).descr, ttt );
			(*tblp).index = frmn;
			++ frmn;
/*printf( "% 4d - %-6s %-12s %s\n", frmn, (*tblp).label, (*tblp).value, (*tblp).descr );*/
			++ tblp;
			continue;
		}
	}

	if( s_sw )
	{
		qsort( tblpsv, (size_t)frmn, sizeof(struct LVDTBL), ( int ( * ) ( const void * , const void * ) ) strcmp );
	}
/*	memset( (*tblp).label, 0, sizeof(struct LVDTBL) ); */

	CloseFile ( frmfp );
	return	frmn;

}					/* GetFrm()			*/

/* EOF. */

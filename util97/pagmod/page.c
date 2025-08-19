/*
 * page.c
 *
 * Description:
 *
 * Handle all Page file management.
 *
 * Date:
 *
 * 1997-07-18
 *
 * Functions:
 *
 * BuildHierarchy 
 * ScanPageFile
 * WriteModFile
 */

# include "page.h"

# include "widgets.h"

# include "util.h"

# include <stdio.h>

# include <string.h>

# include <ctype.h>

# include <malloc.h>

/* Global variables. */

char ModFileName [ PATHNAMELEN ] ;

/* Prototypes. */

static int BuildHierarchy ( void ) ;

/* Functions. */

static int BuildHierarchy ( void ) {

  struct PageWidgetHandle * Handle = NULL ;
  
  struct PageWidget * Parent = NULL ,
                    * Widget = NULL ,
                    * LastWidget = NULL ;
                    
  struct WidgetAttrib * Attrib = NULL ;

  char * WidgetName = NULL ,
       * WidgetClass = NULL ;
       
  int WidgetClassLen = 0 ;

  char * src_c = NULL ,
       * dest_c = NULL ;
  
# ifdef DEBUG
  DEBUG_ENTERFUNC("BuildHierarchy");
# endif

  WidgetName = ( char * ) Malloc ( 100 ) ;

  WidgetClass = ( char * ) Malloc ( 100 ) ;

  Handle = PageWidgetHandleList -> Next ;

  while ( Handle != NULL ) {
  
    Parent = Handle -> Widget ;

    Attrib = Parent -> Attribs -> Next ;

    while ( Attrib != NULL ) {
    
      if ( strcmp ( Attrib -> Name , "listChildren" ) == 0 ) {

        src_c = Attrib -> Value ;

        break ;

      } else {
      
        if ( strcmp ( Attrib -> Name ,
                      "elenco_wid0" ) == 0 ) {
                           
          Parent -> Class = ( char * ) Malloc ( 5 ) ;
        
          strcpy ( Parent -> Class ,
                   "PAGE" ) ;

          src_c = Attrib -> Value + 2 ; /* Avoiding the initial back-slash. */

          break ;
      
        }
        
      }

      Attrib = Attrib -> Next ;
    
    }

    if ( Attrib == NULL ) {
    
      Handle = Handle -> Next ;

      continue ; /* Have no children. */
    
    }

    Parent -> Children = CreatePageWidget ( ) ;

    LastWidget = Parent -> Children ;

    while ( * src_c != '\0' ) /* Till end of list. */ {

      SkipWhiteSpaces ( & src_c ) ;

      for ( dest_c = WidgetName ;
	    * src_c != '\0'
	    && ! isspace ( * src_c ) ;
	    ++ src_c , 
	    ++ dest_c ) {

        * dest_c = * src_c ;

      }

      * dest_c = '\0' ;

      WidgetClassLen = 0 ;

      SkipWhiteSpaces ( & src_c ) ;

      for ( dest_c = WidgetClass ;
            * src_c != ' '
            && * src_c != '\0' ;
            ++ src_c ,
            ++ dest_c ) {

        * dest_c = * src_c ;

        ++ WidgetClassLen ;
     
      }

      * dest_c = '\0' ;

      Widget = FetchPageWidgetHandleList ( WidgetName ) -> Widget ;

      Widget -> Class = ( char * ) Malloc ( WidgetClassLen + 1 ) ;

      strcpy ( Widget -> Class ,
               WidgetClass ) ;

      Widget -> Parent = Parent ;

      LastWidget -> Next = Widget ;

      LastWidget = Widget ;

    }

    Handle = Handle -> Next ;

  }

  free ( WidgetName ) ;

  free ( WidgetClass ) ;

  return 0 ;

}

int ScanPageFile ( void ) {
/*
 * Scan the Page file to build the list of PageWidgetHandle's with their WidgetAttrib's.
 *
 * Return:  0 if successful.
 *         -1 on failure.
 */

  FILE * PageFile = NULL ;

  char * PageLine = NULL ;

  char * WidgetName = NULL ;

  char * AttribName = NULL ,
       * AttribValue = NULL ;

  int LineNumber = 0 ;
  
# ifdef DEBUG
  DEBUG_ENTERFUNC("ScanPageFile");
# endif

  /*
   * The page file contains attributes relevant to:
   *
   *  - page-level widget;
   *  - parent-level widgets;
   *  - child-level widgets;
   *
   * The format for the page-level widget is as follows:
   *
   *   *<page_attr_name>:\t<attr_value>
   *
   * For the parent-level widgets is:
   *
   *   *<object_name>.<attr_name>:\t<attr_value>
   *
   * And for child-level widgets is:
   *
   *   *<parent_name><object_name>.<attr_name>:\t<attr_value>
   */
  
  if ( BehaveAsFilter ) {

    PageFile = stdin ;
  
  } else {
  
    PageFile = OpenFile ( PageFileName ,
                          "r" ) ;
  
  }
  
  if ( PageFile == NULL ) {

    return - 1 ;

  }

  PageWidgetHandleList = CreatePageWidgetHandle ( ) ;

  /* Scan each line for attributes. */

  /*
   * Since a dot can be inside <attr_value>, and so the attribute NOT
   * for the page, it does not suffice to test for a dot in the line.
   * We are certain the first star is before <attr_name> and the first colon
   * is immediately after <attr_name>.
   */

  PageLine = ( char * ) Malloc ( 10000 ) ; /* Hope will suffice!!! */

  WidgetName = ( char * ) Malloc ( 100 ) ;

  AttribName = ( char * ) Malloc ( 100 ) ;

  AttribValue = ( char * ) Malloc ( 10000 ) ;

  while ( fgets ( PageLine ,
                  10000 ,
                  PageFile ) != NULL ) {
    /* 
     * Test if there is a dot between the star and the colon.
     * Test also for the tab after the colon.
     */

    char * StarIndex = NULL ,
         * DotIndex = NULL ,
         * ColonIndex = NULL ;

    struct PageWidgetHandle * Handle = NULL ;
    
    char * src_c = NULL ,
         * dest_c = NULL ;

    ++ LineNumber ;

    Chop ( PageLine ) ;

    StarIndex = strchr ( PageLine ,
                         '*' ) ;
    
    DotIndex = strchr ( PageLine ,
                        '.' ) ;
                        
    ColonIndex = strchr ( PageLine ,
                          ':' ) ;

    /*
     * The star and the colon must exist, and the tab immediately after
     * the colon.
     * This is not a secure test, but only for debug.
     */

    if ( StarIndex == NULL
         || ColonIndex == NULL ) {
         
      sprintf ( pagmod_logbf , 
                "%s: Linea %d: non riconosciuta:\n%s" , 
                PageFileName ,
                LineNumber ,
                PageLine ) ;

      continue ;

    }

    /* 
     * Now test the order of the chars ( * . : ).
     * If there is not a dot it is surely a page-level attr.
     */

    if ( DotIndex != NULL
         && StarIndex < DotIndex
         && DotIndex < ColonIndex ) {
         
      /* Parent-level or child-level widget attribute. */

      /* From the star to the dot is the widget name. */

      for ( src_c = StarIndex + 1 ,
            dest_c = WidgetName ;
            * src_c != '.' ;
            ++ src_c ,
            ++ dest_c ) {

        * dest_c = * src_c ;
   
      }

      * dest_c = '\0' ;

      /* From the dot to the colon is the attrib name. */

      for ( src_c = DotIndex + 1 ,
            dest_c = AttribName ;
            * src_c != ':' ;
            ++ src_c ,
            ++ dest_c ) {

        * dest_c = * src_c ;
  
      }

      * dest_c = '\0' ;

      /* Then the attrib value. */

      ++ src_c ;

      SkipWhiteSpaces ( & src_c ) ;

      strcpy ( AttribValue ,
               src_c ) ;
               
    } else {
    
      /* Page attribute. */

      /* The page-level widget name is "PAGE". */

      strcpy ( WidgetName ,
               "PAGE" ) ;

      /* From the star to the colon is the attrib name. */

      for ( src_c = StarIndex + 1 ,
            dest_c = AttribName ;
            * src_c != ':' ;
            ++ src_c , 
            ++ dest_c ) {

       	* dest_c = * src_c ;
  
      }

      * dest_c = '\0' ;

      /* Then the attrib value. */

      ++ src_c ;

      SkipWhiteSpaces ( & src_c ) ;

      strcpy ( AttribValue ,
               src_c ) ;
    
    }

    /* Add attrib to the page widget. */

    Handle = FetchPageWidgetHandleList ( WidgetName ) ;

    AddAttribToPageWidgetHandle ( Handle ,
                                  AttribName ,
                                  AttribValue ) ;

  }

  free ( PageLine ) ;

  free ( WidgetName ) ;

  free ( AttribName ) ;

  free ( AttribValue ) ;

  if ( ! BehaveAsFilter ) {

    CloseFile ( PageFile ) ;

  }

  return BuildHierarchy ( ) ;

}

int WriteModFile ( void ) {
/*
 * Write the widgets hierarchy to ModFileName.
 * 
 * Return:  0 if successful.
 *         -1 on failure.
 */

  FILE * ModFile = NULL ;

  struct PageWidget * PageLevelWidget = NULL ,
		    * ParentLevelWidget = NULL ,
		    * ChildLevelWidget = NULL ;

  struct WidgetAttrib * Attrib = NULL ;

# ifdef DEBUG
  DEBUG_ENTERFUNC("WriteModFile");
# endif

  if ( DoNotWriteModFile ) {

    return 0 ;

  }

  if ( BehaveAsFilter ) {
    
    ModFile = stdout ;
  
  } else {
  
    ModFile = OpenFile ( ModFileName ,
                         "w" ) ;
  
  }

  if ( ModFile == NULL ) {
  
    return - 1 ;
  
  }

  PageLevelWidget = FetchPageWidgetHandleList ( "PAGE" ) -> Widget ;

  while ( PageLevelWidget ) {
  
    Attrib = PageLevelWidget -> Attribs -> Next ;

    while ( Attrib != NULL ) {

      fprintf ( ModFile,
                "*%s:\t%s\n" ,
                Attrib -> Name ,
                Attrib -> Value ) ;

      Attrib = Attrib -> Next ;
   
    }

    if ( PageLevelWidget -> Children == NULL ) {
    
      PageLevelWidget = PageLevelWidget -> Next ;

      continue ;
    
    }
    
    ParentLevelWidget = PageLevelWidget -> Children -> Next ;

    while ( ParentLevelWidget != NULL ) {
    
      Attrib = ParentLevelWidget -> Attribs -> Next ;

      while ( Attrib != NULL ) {

        fprintf ( ModFile ,
                  "*%s.%s:\t%s\n" ,
                  ParentLevelWidget -> Name ,
                  Attrib -> Name ,
                  Attrib -> Value ) ;

        Attrib = Attrib -> Next ;
      
      }

      if ( ParentLevelWidget -> Children == NULL ) {
      
        ParentLevelWidget = ParentLevelWidget -> Next ;

        continue ;
        
      }

      ChildLevelWidget = ParentLevelWidget -> Children -> Next ;

      while ( ChildLevelWidget != NULL ) {
      
        Attrib = ChildLevelWidget -> Attribs -> Next ;

        while ( Attrib != NULL ) {
        
          fprintf ( ModFile ,
                    "*%s.%s:\t%s\n" ,
                    ChildLevelWidget -> Name ,
                    Attrib -> Name ,
                    Attrib -> Value ) ;
          
          Attrib = Attrib -> Next ;
        
        }

        ChildLevelWidget = ChildLevelWidget -> Next ;
   
      }

      ParentLevelWidget = ParentLevelWidget -> Next ;

    }

    PageLevelWidget = PageLevelWidget -> Next ;

  }

  if ( ! BehaveAsFilter ) {
  
    CloseFile ( ModFile ) ;

  }

  return 0 ;

}

/* EOF. */

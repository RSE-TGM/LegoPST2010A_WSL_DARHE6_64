/*
 * widgets.c
 *
 * Description:
 *
 * Handle widgets management.
 *
 * Date:
 *
 * 1997-07-18
 *
 * Functions:
 *
 * CreateWidgetAttrib
 * CreateMatrixAttrib
 * CreatePageWidget
 * CreateScriptWidget
 * CreatePageWidgetHandle
 * DestroyWidgetAttrib
 * DestroyMatrixAttrib
 * DestroyPageWidget
 * DestroyScriptWidget
 * DestroyPageWidgetHandle
 * FetchPageWidgetHandleList
 * AddAttribToPageWidgetHandle
 */
# include "widgets.h"
# include "util.h"
# include <stdio.h>
# include <string.h>
struct PageWidgetHandle * PageWidgetHandleList = NULL ;
struct WidgetAttrib * CreateWidgetAttrib ( void )
  {
  struct WidgetAttrib * Attrib ;
# ifdef DEBUG
  DEBUG_ENTERFUNC("CreateWidgetAttrib");
# endif
  Attrib = ( struct WidgetAttrib * ) Malloc ( sizeof ( struct WidgetAttrib ) ) ;
  Attrib -> Name = NULL ;
  Attrib -> Value = NULL ;
  Attrib -> Next = NULL ;
  Attrib -> IgnoreValue = 0 ;
  return Attrib ;
  }
struct MatrixAttrib * CreateMatrixAttrib ( void )
  {
  struct MatrixAttrib * Attrib ;
# ifdef DEBUG
  DEBUG_ENTERFUNC("CreateMatrixAttrib");
# endif 
  Attrib = ( struct MatrixAttrib * ) Malloc ( sizeof ( struct MatrixAttrib ) ) ;
  Attrib -> Name = NULL ;
  Attrib -> NumFields = 0 ;
  Attrib -> Index = 0 ;
  Attrib -> Offset = 0 ;
  Attrib -> IsAddValue = 0 ;
  Attrib -> Value = NULL ;
  Attrib -> Next = NULL ;
  Attrib -> IgnoreValue = 0 ;
  return Attrib ;
  }
void DestroyWidgetAttrib ( struct WidgetAttrib * Attrib )
  {
# ifdef DEBUG
  DEBUG_ENTERFUNC("DestroyWidgetAttrib");
# endif
  free ( Attrib -> Name ) ;
  free ( Attrib -> Value ) ;
  if ( Attrib -> Next ) 
    {
    DestroyWidgetAttrib ( Attrib -> Next ) ;
    }
  free ( Attrib ) ;
  }
void DestroyMatrixAttrib ( struct MatrixAttrib * Attrib ) 
  {
# ifdef DEBUG
  DEBUG_ENTERFUNC("DestroyMatrixAttrib");
# endif
  free ( Attrib -> Name ) ;
  free ( Attrib -> Value ) ;
  if ( Attrib -> Next )
    {
    DestroyMatrixAttrib ( Attrib -> Next ) ;
    }
  free ( Attrib ) ;
  }
struct ScriptWidget * CreateScriptWidget ( void )
  {
  struct ScriptWidget * Widget ;
# ifdef DEBUG
  DEBUG_ENTERFUNC("CreateScriptWidget");
# endif
  Widget = ( struct ScriptWidget * ) Malloc ( sizeof ( struct ScriptWidget ) ) ;
  Widget -> Name = NULL ;
  Widget -> Class = NULL ;
  Widget -> ChildOf = NULL ;
  Widget -> ChangeAttribs = CreateWidgetAttrib ( ) ;
  Widget -> HasAttribs = CreateWidgetAttrib ( ) ;
  Widget -> NewAttribs = CreateWidgetAttrib ( ) ;
  Widget -> MatrixAttribs = CreateMatrixAttrib ( ) ;
  Widget -> MatrixHasAttribs = CreateMatrixAttrib ( ) ;
  Widget -> InputValue = NULL ;
  Widget -> Compiled = 0 ;
  Widget -> Parent = NULL ;
  Widget -> Children = NULL ;
  Widget -> Next = NULL ;
  return Widget ;
  }
void DestroyScriptWidget ( struct ScriptWidget * Widget )
  {
# ifdef DEBUG
  DEBUG_ENTERFUNC("DestroyScriptWidget");
# endif
  free ( Widget -> Name ) ;
  free ( Widget -> Class ) ;
  free ( Widget -> ChildOf ) ;
  DestroyWidgetAttrib ( Widget -> ChangeAttribs ) ;
  DestroyWidgetAttrib ( Widget -> HasAttribs ) ;
  DestroyWidgetAttrib ( Widget -> NewAttribs ) ;
  DestroyMatrixAttrib ( Widget -> MatrixAttribs ) ;
  DestroyMatrixAttrib ( Widget -> MatrixHasAttribs ) ;
  free ( Widget -> InputValue ) ;
  free ( Widget ) ;
  }
struct PageWidget * CreatePageWidget ( void )
  {
  struct PageWidget * Widget ;
# ifdef DEBUG
  DEBUG_ENTERFUNC("DestroyMatrixAttrib");
# endif
  Widget = ( struct PageWidget * ) Malloc ( sizeof ( struct PageWidget ) ) ;
  Widget -> Name = NULL ;
  Widget -> Class = NULL ;
  Widget -> Attribs = CreateWidgetAttrib ( ) ;
  Widget -> Parent = NULL ;
  Widget -> Children = NULL ; 
  Widget -> Next = NULL ;
  return ( Widget ) ;
  }
void DestroyPageWidget ( struct PageWidget * Widget )
  {
# ifdef DEBUG
  DEBUG_ENTERFUNC("DestroyPageWidget");
# endif
  free ( Widget -> Name ) ;
  free ( Widget -> Class ) ;
  DestroyWidgetAttrib ( Widget -> Attribs ) ;
  free ( Widget ) ;
  }
struct PageWidgetHandle * CreatePageWidgetHandle ( void )
  {
  struct PageWidgetHandle * Handle ;
# ifdef DEBUG
  DEBUG_ENTERFUNC("CreatePageWidgetHandle");
# endif
  Handle = ( struct PageWidgetHandle * ) Malloc ( sizeof ( struct PageWidgetHandle ) ) ;
  Handle -> Widget = CreatePageWidget ( ) ;
  Handle -> LastAttrib = Handle -> Widget -> Attribs ;
  Handle -> Next = NULL ;
  return ( Handle ) ;
  }
void DestroyPageWidgetHandle ( struct PageWidgetHandle * Handle )
  {
# ifdef DEBUG
  DEBUG_ENTERFUNC("DestroyPageWidgetHandle");
# endif
  DestroyPageWidget ( Handle -> Widget ) ;
  if ( Handle -> Next )
    {
    DestroyPageWidgetHandle ( Handle -> Next ) ;
    } 
  free ( Handle ) ;
  }
struct PageWidgetHandle * FetchPageWidgetHandleList ( char * WidgetName )
  {
  /*
   * Fetch the Widget List for a widget with name WidgetName.
   * If found, return its handle.
   * Otherwise, return a new handle.
   */
  struct PageWidgetHandle * Handle ,
                          * LastHandle ;
# ifdef DEBUG
  DEBUG_ENTERFUNC("FetchPageWidgetHandleList");
# endif
  Handle = PageWidgetHandleList -> Next ;
  LastHandle = PageWidgetHandleList ;
  while ( Handle != NULL )
    {
    if ( strcmp ( Handle -> Widget -> Name ,
                  WidgetName ) == 0 ) 
      {
      return Handle ;
      }
    LastHandle = Handle ;
    Handle = Handle -> Next ;
    }
  /* No handle found. Add an handle at end of list. */
  LastHandle -> Next = CreatePageWidgetHandle ( ) ;
  LastHandle -> Next -> Widget -> Name = ( char * ) Malloc ( strlen ( WidgetName ) + 1 ) ;
  strcpy ( LastHandle -> Next -> Widget -> Name ,
           WidgetName ) ;
  return LastHandle -> Next ;
  }
void AddAttribToPageWidgetHandle ( struct PageWidgetHandle * Handle ,
                                   char * NewAttribName ,
                                   char * NewAttribValue )
  {
  struct WidgetAttrib * Attrib  = NULL ;
  int NewAttribNameLen = 0 ,
      NewAttribValueLen = 0 ;
# ifdef DEBUG
  DEBUG_ENTERFUNC("AddAttribToPageWidgetHandle");
# endif
  Handle -> LastAttrib -> Next = CreateWidgetAttrib ( ) ;
  Handle -> LastAttrib = Handle -> LastAttrib->Next ;
  Attrib = Handle -> LastAttrib ;
  NewAttribNameLen = strlen ( NewAttribName ) ;
  NewAttribValueLen = strlen ( NewAttribValue ) ;
  Attrib -> Name = ( char * ) Malloc ( NewAttribNameLen + 1 ) ;
  Attrib -> Value = ( char * ) Malloc ( NewAttribValueLen + 1 ) ;
  strcpy ( Attrib -> Name , NewAttribName ) ;
  strcpy ( Attrib -> Value , NewAttribValue ) ;
  }
/* EOF. */

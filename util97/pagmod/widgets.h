# ifndef pagmod_widgets_h_included
# define pagmod_widgets_h_included
/*
 * Date:
 *
 * 1997-07-17
 */
struct WidgetAttrib
  {
  int IgnoreValue ;
  char * Name ,
       * Value ;
  struct WidgetAttrib * Next ; /* Next attribute in the list. */
} ;
extern struct WidgetAttrib * CreateWidgetAttrib ( void ) ;
extern void DestroyWidgetAttrib ( struct WidgetAttrib * ) ;
struct MatrixAttrib
  {
  int IgnoreValue ;
  char * Name ,
       * Value ;
  int NumFields ;
  int Index ;
  int Offset ;
  int IsAddValue ;
  struct MatrixAttrib * Next ;
  } ;
extern struct MatrixAttrib * CreateMatrixAttrib ( void ) ;
extern void DestroyMatrixAttrib ( struct MatrixAttrib * ) ;
struct PageWidget
  {
  char * Name ,
       * Class ; 
  struct WidgetAttrib * Attribs ; /* Head of list of attributes. */ 
  struct PageWidget * Parent ,
                    * Children , /* Head of list of children. */
                    * Next ;
  } ;
extern struct PageWidget * CreatePageWidget ( void ) ;
extern void DestroyPageWidget ( struct PageWidget * ) ;
struct ScriptWidget
  {
  char * Name ,
       * Class ,
       * ChildOf ;
  struct WidgetAttrib * ChangeAttribs , /* Head of list of attributes to modify. */
                      * HasAttribs , /* Head of list of attributes to match. */
                      * NewAttribs ; /* Head of list of attributes to add. */
  struct MatrixAttrib * MatrixHasAttribs , /* Head of list of matrix attribs to match. */
                      * MatrixAttribs ; /* Head of list of matrix attribs. */
  char * InputValue ; /* Module to which to transform the widget. */
  int Compiled ; /* Compiled attrib must be built. */
  struct ScriptWidget * Parent , 
                      * Children , /* Head of list of children. */
                      * Next ; /* Next same-level widget. */
  } ;
extern struct ScriptWidget * CreateScriptWidget ( void ) ;
extern void DestroyScriptWidget ( struct ScriptWidget * ) ;
struct PageWidgetHandle
  {
  struct PageWidget * Widget ;
  struct WidgetAttrib * LastAttrib ;
  struct PageWidgetHandle * Next ; /* Next PageWidget handle. */
  } ;
extern struct PageWidgetHandle * PageWidgetHandleList ; /* Head of list of PageWidget handles. */
extern struct PageWidgetHandle * CreatePageWidgetHandle ( void ) ;
extern void DestroyPageWidgetHandle ( struct PageWidgetHandle * ) ;
extern struct PageWidgetHandle * FetchPageWidgetHandleList ( char * ) ;
extern void AddAttribToPageWidgetHandle ( struct PageWidgetHandle * , char * , char * ) ;
# endif /* pagmod_widgets_h_included */
/* EOF. */

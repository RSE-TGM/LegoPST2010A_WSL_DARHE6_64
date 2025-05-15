/**********************************************************************
*
*       C Source:               pixmap_cursor.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 14:11:05 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: pixmap_cursor.c,2 %  (%full_filespec: 1,csrc,pixmap_cursor.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)pixmap_cursor.c	2.2\t2/13/95";
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <X11/Intrinsic.h>


typedef struct _tag_lista_cursori {
                   char                      *nome;
                   Cursor                    cur;
                   struct _tag_lista_cursori *succ;
} LISTA_CURSORI;

static LISTA_CURSORI *lista_cursori=NULL;



void make_pixmap_cursor( wid, name, fg_color, bg_color )
Widget wid;
char *name, *fg_color, *bg_color;
{

   char     *path, path_name[1024], *getenv();
   int      width_bm, height_bm, width_msk, height_msk; 
   int      x, y, dummy_x, dummy_y;
   Cursor   cursor;
   Display  *display;
   Colormap colormap;
   XColor   bg, fg, dummy_color;
   Pixmap   bm, msk;
   LISTA_CURSORI *new_entry;
   struct stat buf;


   display = XtDisplay( wid );
 

   /* Costruzione del path del pixmap */
   if ( path = getenv( "LEGOCAD_ICO" ) )
   {
     strcpy ( path_name, path );
     strcat ( path_name, "/" );
   }
   else 
     strcpy ( path_name, "" );
   strcat ( path_name, name );
   strcat ( path_name, ".bmp" );


   /* Lettura Pixmap */ 
   if ( stat( path_name, &buf ) )
   {
     printf ( "\nERRORE make_pixmap_cursor: il cursore %s non e' definito",
               path_name );
     return;
   }
   
   XReadBitmapFile( display, XtWindow( wid ), path_name, 
                    &width_bm, &height_bm, &bm, &x, &y );

 
   /* Sistema le coordinate del Hot Spot */
   if ( x == -1 )
     x = width_bm/2;

   if ( y == -1 )
     y = height_bm/2;

   
   /* Alloca i colori del pixmap */ 
   colormap = DefaultColormap( display, DefaultScreen( display ) );

   XAllocNamedColor( display, colormap, fg_color, &fg, &dummy_color );
   XAllocNamedColor( display, colormap, bg_color, &bg, &dummy_color );


   /* Costuisce il path della maschera */
   *(strstr ( path_name, ".bmp" )) = '\0';
   strcat ( path_name, "_mask.bmp" );

   if ( ! stat( path_name, &buf ) )
   {
     /* Legge la maschera */
     XReadBitmapFile( display, XtWindow( wid ), path_name, 
                      &width_msk, &height_msk, &msk, &dummy_x, &dummy_y );

     if ( width_bm != width_msk || height_bm != height_msk )
     {
       printf ( "\nERRORE make_pixmap_cursor: il pixmap del cursore %s\n",
                name );
       printf ( "e quello della maschera hanno dimensioni diverse " );
       return;
     }
   }
   else
     msk = (Pixmap)NULL;
   

   /* Setta il corsore */
   cursor = XCreatePixmapCursor( display, bm, msk, &fg, &bg, x, y );


   /* Libera i pixmap */
   if ( msk )
     XFreePixmap( display, msk );  
   XFreePixmap( display, bm );  


   /* Inserisce il cursore nella lista dei cursori disponibili */
   new_entry       = (LISTA_CURSORI*) malloc ( sizeof(LISTA_CURSORI) );
   new_entry->nome = (char*) malloc ( sizeof(char) * strlen(name)+1 );
   strcpy ( new_entry->nome, name );
   new_entry->cur  = cursor;
   new_entry->succ = lista_cursori;
   lista_cursori   = new_entry;

}





void set_pixmap_cursor ( wid, cursor )
Widget wid;
char   *cursor;
{
   LISTA_CURSORI *scan_cur;

   for ( scan_cur=lista_cursori; scan_cur; scan_cur = scan_cur->succ )
     if ( ! strcmp( scan_cur->nome, cursor ) )
     {
       XDefineCursor( XtDisplay( wid ), XtWindow( wid ), scan_cur->cur );
       XSync(XtDisplay(wid),False);
       return;
     }

   printf ( "\nERRORE sel_pixmap_cursor: il cursore %s non e' definito\n",
            cursor );
}






void get_pixmap_cursor ( cur_name, cursor )
char   *cur_name;
Cursor *cursor;
{
   LISTA_CURSORI *scan_cur;

   for ( scan_cur=lista_cursori; scan_cur; scan_cur = scan_cur->succ )
     if ( ! strcmp( scan_cur->nome, cur_name ) )
     {
       *cursor = scan_cur->cur;
       return;
     }

   printf ( "\nERRORE sel_pixmap_cursor: il cursore %s non e' definito\n",
            cursor );
}


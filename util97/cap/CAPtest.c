/*@(#) CAPtest.c						1997-03-21	*/

# include "CAP.h"

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>


int main ( int argc , 
	   char * * argv ) {

  char Buffer [ ENELINFO_LEN + 1 ] ;

  if ( argc < 2 ) {

    fprintf ( stderr , "Uso:  CAPtest  ProgramID\n" ) ;
    return ( 1 ) ;

  }

  if ( strlen ( argv [ 1 ] ) != 5 ) {

    fprintf ( stderr , "CAPtest: ProgramID deve essere di 5 caratteri.\n" ) ;
    return ( 1 ) ;

  }

  if ( CAP ( argv [ 1 ] , Buffer ) == -1 ) {

    printf ( "CAPtest: Errore CAP\n" ) ;
    return ( 1 ) ;

  }

  if ( Buffer [ 0 ] == '\0' ) {

    printf ( "\nCAPtest: <Accesso negato>\n" ) ;

  } else {

    printf ( "\nCAPtest: Programma: %s, Autorizzazione: |%s|\n" , argv [ 1 ] , Buffer ) ;

  }

}


/* EOF. */

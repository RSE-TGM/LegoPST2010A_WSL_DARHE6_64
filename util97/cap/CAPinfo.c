/*@(#) - CAPinfo.c					1997-03-26	*/

# include "CAP.h"

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>


int main ( int argc , char * * argv ) {

  struct CAPinfo Info ;
  FILE * CAPfile ;
  unsigned char * Buffer ;

  errno = 0 ;

  if ( argc > 1 ) {

    if ( strcmp ( argv [ 1 ] , "-V" ) == 0 ) {

      PrintVersion ( ) ;

    } else {

      fprintf ( stderr ,
		"Unrecognized option %s\n" ,
		argv [ 1 ] ) ;

    }

    exit ( 0 ) ;

  }

  if ( InitEnv ( ) == -1)
     return ( 1 );

  if ( cap_info ( & Info ) == 0 ) {
     printf("\n****** Recupero informazioni macchina OK ******\n");
  }

printf("\nAddress:\t%s\n", Info.Address);

  CAPfile = fopen ( CAPINFO_FN , "w" ) ;

  if ( CAPfile == NULL ) {

    fprintf ( stderr , "CAPinfo: Errore apertura file %s - errno: %d\n" , CAPINFO_FN, errno ) ;
    return ( 1 ) ;

  }

  strncpy ( Info . ProgramID , "prgid" , PROGRAMID_LEN ) ;
  strncpy ( Info . EnelInfo , "EnelInfo!!" , ENELINFO_LEN ) ;

  if ( AZencode ( ( unsigned char * ) & Info , &Buffer ) == -1 ) {

    fprintf ( stderr, "CAPinfo: Errore AZencode!\n" ) ;
    fclose ( CAPfile ) ;
    return ( 1 ) ;

  }

  fprintf ( CAPfile , "%s\n" , Buffer ) ;

  fclose ( CAPfile ) ;

  return ( 0 ) ;

}

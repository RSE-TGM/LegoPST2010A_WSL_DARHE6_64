/*@(#)flist.c Legge una file-list e crea una lista dei file 1997-04-21	*/

/*----------------------------------------------------------------------*/
/*	Include								*/

#include	<stdio.h>
#include	<string.h>
#include	<ctype.h>
#ifndef LINUX
#include	<sys/mode.h>
#endif
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<errno.h>
#include	"flist.h"
#include        "util.h"

/*----------------------------------------------------------------------*/
/*	Define								*/

/*----------------------------------------------------------------------*/
/*	Variabili							*/

struct FileList FileListHandle = 
  { 
  NULL , 
  NULL 
  } ;	/* NB: solo i file ACCESSIBILI	*/
struct	FileList*	FLH = &FileListHandle;		/* FileList Head		*/
struct	FileList*	FLT = &FileListHandle;		/* FileList Tail		*/
char*	ListFileName;			/* Nome del file-list		*/

/*----------------------------------------------------------------------*/
/*	Prototypes							*/

/*----------------------------------------------------------------------*/
/*	Functions							*/

int	ReadListFile( void )
{
FILE*		ListFile;
char		Path[PATH_SZ];

	ListFile	= fopen( ListFileName, "r" );
	if( ListFile == NULL )
	{
    sprintf ( logbf , 
              "Errore apertura file lista  : %s" ,
														ListFileName ) ;

				log ( logbf ) ;
    fprintf ( stderr , "pagmod: %s\n" , logbf ) ;
		return ( -1 ) ;
	}

	FileListHandle.Path	= NULL;
	FileListHandle.Next	= NULL;
	FLH			= &FileListHandle;
	FLT			= &FileListHandle;

/*......................................................................*/
/*	Lettura della file-list						*/

	FreeFileList ( ) ;

	while( fgets( Path, sizeof(Path), ListFile ) != NULL )
	{
		AppendToFileList( Path );
	}
	fclose( ListFile ) ;
	return( 0 ) ; 
}					/* ReadListFile()		*/

void	AppendToFileList( Path )
char*	Path;
{

struct	stat	buf;
int	sts;
char*	ppp;

	if( (ppp = strchr( Path, LF )) != NULL ) *ppp = 0;
	buf.st_mode	= 0;
	errno	= 0;
	sts	= stat( Path, &buf );
	if( sts != 0 )
	{
		sprintf( logbf, "File NON esistente  : %s", Path );
		log( logbf );
		return;
	}
	if( ! S_ISREG( buf.st_mode ) )
	{
		sprintf( logbf, "File NON regolare   : %s", Path );
		log( logbf );
		return;
	}

	sts	= access( Path, R_OK );
	if( sts == 0 )
	{
/*+		printf( "OK |%-32s|% 4d.\n", Path, errno );	*/
	}
	else
	{
/*+		printf( "KO |%-32s|% 4d.\n", Path, errno );	*/
		sprintf( logbf, "File NON accessibile: %s", Path );
		log( logbf );
		return;
	}

	FLT -> Next	= (struct FileList*) Malloc( sizeof(struct FileList) );
        FLT = FLT -> Next ;
	FLT -> Path	= (char*) Malloc( strlen( Path )+1 );
	strcpy( FLT -> Path, Path );
	FLT -> Next = NULL ;
}					/* AppendToFileList()		*/

void FreeFileList ( void )
{
  struct FileList * Handle = FileListHandle . Next ;
  struct FileList * PrevHandle = NULL ;

  while ( Handle )
    {
    PrevHandle = Handle ;
    Handle = Handle -> Next ;
    free ( PrevHandle -> Path ) ;
    free ( PrevHandle ) ;
    }
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#ifdef ESEMPIO
main( argc, argv )
int	argc;
char**	argv;
{
int	k;
struct	stat	buf;
int	sts;

	if( argc < 2 ) exit( 1 );
	ListFileName = argv [ 1 ] ;
	k	= ReadListFile( );
	printf( "main: %d\n", k );
	if( k != 0 ) exit( 2 );

	FLH	= &FileListHandle;
	do
	{
		printf( "{%-32s}\t", FLH->Path );

/*	Le due righe seguenti per verificare che il path e` corretto	*/
sts	= stat( FLH->Path, &buf );
printf( "st_size:% 8ld.", buf.st_size );

		printf( "\n" );
		free( FLH->Path );
		FLT	= FLH;
		FLH	= FLH->Next;
		free( FLT );
	}
	while( FLH->Next != NULL );
}
#endif

/*@(#)log.c	Routine di log per pagmod		1997-04-21

/*----------------------------------------------------------------------*/
/*		INCLUDE 						*/

#include	<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<errno.h>
#include	"util.h"

/*----------------------------------------------------------------------*/
/*		DEFINE							*/

#define		LF	0x0a
#define		CR	0x0d
#define		FALSE	0
#define		TRUE	1

extern	char*	datetime();

/*----------------------------------------------------------------------*/
/*		VARIABILI						*/

FILE*	logfp;
char	logfn[] = "pagmod.log";
char	logbf[256];
char	logsep[] = "\n\
=============================================================================";

/*======================================================================*/
/*		CODE							*/

void	log( ppp )
char*	ppp;
{
	if( logfp == NULL ) return;
	fprintf( logfp, "%s %s\n", datetime(), ppp );
	fflush( logfp );
}					/* log()			*/

/*======================================================================*/
void	log_start( Argc, Argv )
int	Argc;
char*	Argv[];
{
int	jj;

	if( QuietMode ) return;
	errno	= 0;
	logfp	= fopen( logfn, "a" );
	if( logfp == NULL )
	{
		printf( "Errore in apertura file di log: %s - errno: %d\n",
						logfn, errno );
	}
	fprintf( logfp, "%s\n%s - Inizio Pid:% 6d %s\n\t\t      ",
				logsep, datetime(), getpid(), help_V );
	for( jj = 0; jj < Argc; jj++ )
	{
		fprintf( logfp, " %s", Argv[jj] );
	}
	fprintf( logfp, "\n" );
	fflush( logfp );

}					/* log_start()			*/

/*======================================================================*/
void	log_stop()
{
	if( logfp == NULL ) return;
	
	fprintf( logfp, 
										"%s - Fine   Pid:% 6d #Modif.:% 6d   #Pagine:% 5d\n",
										datetime(), getpid() , Gtot, Gpag );
	fflush( logfp );
	fclose( logfp );
}					/* log_stop()			*/

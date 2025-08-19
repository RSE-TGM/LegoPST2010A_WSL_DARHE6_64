/*@(#)dbmins.c						1997-07-04	*/

/*----------------------------------------------------------------------*/
#include	<fcntl.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<string.h>
#include	<errno.h>
#include	<ndbm.h>
#include	<stdio.h>
#include	<stdlib.h>

/*----------------------------------------------------------------------*/
DBM*	dbp;
int	flags;
mode_t	mode;
int	dbmerr;
char	dbmbn[60];

datum	key;
datum	con;
datum	YP_MASTER_NAME;
datum	rkey;

int	status;
int	j, k;
char	Key[128];
char	Con[1024];


/*----------------------------------------------------------------------*/
int main( argc, argv )
int	argc;
char**	argv;
{

/*......................................................................*/
	if( argc < 4 )
	{
		printf( "Uso:   dbmins  db  key-len  record\n" );
		exit( 1 );
	}

	strcpy( dbmbn, argv[1] );
	key.dsize	= atoi( argv[2] );
	key.dptr	= argv[3];
	con.dptr	= argv[3];
	con.dsize	= strlen( argv[3] );

/*......................................................................*/
	errno	= 0;
	mode	= O_RDWR;
	flags	= DBM_REPLACE;
	flags	= DBM_INSERT;
	dbp	= dbm_open( dbmbn, mode, flags );   /* manpage errata !	*/
	printf( "dbm_open()  - errno: %d dbp: %X mode: %s\n",
		errno, dbp, flags == DBM_REPLACE ? "DBM_REPLACE" : "DBM_INSERT" );
	if( errno != 0 ) exit( 2 );

/*......................................................................*/
	memset( Key, 0, sizeof(Key) );
	strncpy( Key, key.dptr, key.dsize );
	memset( Con, 0, sizeof(Con) );
	strncpy( Con, con.dptr, con.dsize );

	errno	= 0;
	rkey	= dbm_fetch( dbp, key );
/*+	printf( "% 3d) K:[% 4d] {%s} C:[% 4d] {%s}\n", j, key.dsize, Key, con.dsize, Con );	*/
	printf( "% 7d) K:[%03d] {%s} C:[%03d] {%s}\n",
			j, key.dsize, Key, con.dsize, Con );

	errno	= 0;
	status	= dbm_store( dbp, key, con, flags );
	dbmerr	= dbm_error( dbp );
	printf( "dbm_store() - status: %d errno: %d dbmerr: %d >>> %s\n",
		status, errno, dbmerr, status == 0 ? " OK" : "NOK" );

	dbm_clearerr( dbp );
/*......................................................................*/
	dbm_close( dbp );

}					/* main()			*/

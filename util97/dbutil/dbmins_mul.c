/*@(#)dbmins_mul.c						1997-07-04	*/

/*----------------------------------------------------------------------*/
#include	<stdio.h>
#include	<fcntl.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<string.h>
#include	<errno.h>
#include	<ndbm.h>

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
char	Buffer1[1024];
char	Buffer2[1024];


/*----------------------------------------------------------------------*/
main( argc, argv )
int	argc;
char**	argv;
{

/*......................................................................*/
	if( argc != 2 )
	{
		printf( "Uso:   dbmins_mul  db  \n" );
		exit( 1 );
	}

	strcpy( dbmbn, argv[1] );

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
     while (scanf( "%s %s" , Buffer1, Buffer2 ) != EOF )
        {
	key.dptr	= Buffer1;
  	key.dsize	= strlen( Buffer1 );
	con.dptr	= Buffer2;
  	con.dsize	= strlen( Buffer2 );
	printf("%s - %s\n" , Buffer1,Buffer2);

/*	con.dsize	= strlen( Buffer2 );
	memset( Key, 0, sizeof(Key) );
	strncpy( Key, key.dptr, key.dsize );
	memset( Con, 0, sizeof(Con) );
	strncpy( Con, con.dptr, con.dsize );
*/

	errno	= 0;
	status	= dbm_store( dbp, key, con, flags );
	dbmerr	= dbm_error( dbp );
	printf( "dbm_store() - status: %d errno: %d dbmerr: %d >>> %s\n",
		status, errno, dbmerr, status == 0 ? " OK" : "NOK" );

        }
/*......................................................................*/
	dbm_clearerr( dbp );
	dbm_close( dbp );
	exit(0);

}					/* main()			*/

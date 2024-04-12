/*@(#)dbmrea.c						1997-07-04	*/

/*----------------------------------------------------------------------*/
#include	<fcntl.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<string.h>
#include	<errno.h>
#include	<ndbm.h>

/*----------------------------------------------------------------------*/
DBM*	dbp;
int	flags;
int	mode;
int	dbmerr;
char	dbmbn[60];

datum	key;
datum	con;
datum	rkey;

int	status;
int	j, k;
char	Key[128];
char	Con[1024];


/*----------------------------------------------------------------------*/
main( argc, argv )
int	argc;
char**	argv;
{

	if( argc < 2 )
	{
		printf( "Uso:   dbmrea  dbm-basename\n" );
		exit( 1 );
	}
	strcpy( dbmbn, argv[1] );

/*......................................................................*/
	errno	= 0;
	flags	= DBM_INSERT;
	mode	=  O_CREAT;
	mode	=  O_CREAT | O_RDWR | O_TRUNC;
	mode	=  O_RDWR ;
	mode	=  O_RDONLY ;
	dbp	= dbm_open( dbmbn, flags, mode );
	printf( "dbm_open()  - errno: %d dbp: %X\n", errno, dbp );
	if( errno != 0 ) exit( 2 );

/*......................................................................*/
	con.dptr	= "????";
	j	= 0;
	key.dsize	= 0;
	for( key = dbm_firstkey(dbp); key.dptr != NULL; key = dbm_nextkey(dbp))
	{
		j++;
		memset( Key, 0, sizeof(Key) );
		strncpy( Key, key.dptr, key.dsize );
/*+		printf( "% 3d) K:[%5d] {%s}\n", j, key.dsize, Key );	*/

		errno	= 0;
		con	= dbm_fetch( dbp, key );
/*+		printf( "dbm_fetch() - status: %d errno: %d dbmerr: %d\n", status, errno, dbmerr ); */
		memset( Con, 0, sizeof(Con) );
		strncpy( Con, con.dptr, con.dsize );
/*+		printf( "% 3d) C:[%5d] {%s}\n", j, con.dsize, Con );	*/
		printf( "% 7d) K:[%03d] {%s} C:[%03d] {%s}\n",
			j, key.dsize, Key, con.dsize, Con );
	}
/*......................................................................*/
	dbm_close( dbp );
	printf( "dbm_close() - dbmerr: %d\n", dbmerr );

}					/* main()			*/

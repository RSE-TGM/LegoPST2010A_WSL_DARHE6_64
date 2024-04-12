/*@(#)dbmtch.c						1997-07-04	*/

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
int	mode;
int	dbmerr;
char	dbmbn[60];

datum	key;
datum	con;

int	status;
int	j, k;
char*	result;
char	Key[128];
char	Con[1024];


/*----------------------------------------------------------------------*/
main( argc, argv )
int	argc;
char**	argv;
{

	if( argc < 3 )
	{
		fprintf(stderr, "Uso:   dbmtch  dbm-basename  key\n" );
		exit( 1 );
	}
	strcpy( dbmbn, argv[1] );
	strcpy( Key, argv[2] );

/*......................................................................*/
	errno	= 0;
	flags	= DBM_INSERT;
	mode	=  O_CREAT;
	mode	=  O_CREAT | O_RDWR | O_TRUNC;
	mode	=  O_RDWR ;
	mode	=  O_RDONLY ;
	dbp	= dbm_open( dbmbn, flags, mode );
/*+	fprintf(stderr,  "dbm_open()  - errno: %d dbp: %X\n", errno, dbp );	*/
	if( errno != 0 ) exit( 2 );

/*......................................................................*/
	j		= 1;
	key.dptr	= Key;
	key.dsize	= strlen( Key );

	errno	= 0;
	con	= dbm_fetch( dbp, key );
/*+		fprintf(stderr,  "dbm_fetch() - status: %d errno: %d dbmerr: %d\n", status, errno, dbmerr ); */
	if( con.dptr != NULL )
	{
		memset( Con, 0, sizeof(Con) );
		strncpy( Con, con.dptr, con.dsize );
		result	= "";
	}
	else
	{
		result	= " Record not found!";
	}
/*+		fprintf(stderr,  "% 3d) C:[%5d] {%s}\n", j, con.dsize, Con );	*/
	fprintf(stderr,  "% 7d) K:[%03d] {%s} C:[%03d] {%s}%s\n",
		j, key.dsize, Key, con.dsize, Con, result );
                fprintf(stdout,"{%s} | {%s}\n", Key,Con);

/*......................................................................*/
	dbm_close( dbp );
/*+	fprintf(stderr,  "dbm_close() - dbmerr: %d\n", dbmerr );			*/

}					/* main()			*/

/*@(#)dbmrea.c						1997-07-04	*/

/*----------------------------------------------------------------------*/
#include	<stdio.h>
#include <stdlib.h>
#include	<fcntl.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<string.h>
#include	<errno.h>
#include	<ndbm.h>
#include        "sqlite3.h" 

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

/* AGGIUNTE PER GESTIRE SCRITTURA NEL DB NETCOMPI */
char    dbNameNet_Compi[64];
char    query[2048];
char    *zErrMsg = 0;
sqlite3* dbNet_Compi;  /* handle sqlite3 */


/*----------------------------------------------------------------------*/
/* CALLBACK QUERY SQLITE */
static int callbackSqlite(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int main( argc, argv )
int	argc;
char**	argv;
{
	int rc = 0;
	

	memset(dbNameNet_Compi,0,sizeof(dbNameNet_Compi));
	memset(query,0,sizeof(query));

	if( argc < 3 )
	{
		printf( "Uso:   dbm2sql  dbm-basename db-net_compiName\n" );
		exit( 1 );
	}
	strcpy( dbmbn, argv[1] );	
	strcpy( dbNameNet_Compi, argv[2] );
	

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

	
	
	/* APERTURA DB NET_COMPI */
	rc = sqlite3_open(dbNameNet_Compi, &dbNet_Compi);
	if( rc != SQLITE_OK){
		fprintf(stderr, "Error: Impossible open database: %s\n\n", sqlite3_errmsg(dbNet_Compi));
		sqlite3_close(dbNet_Compi);
		exit(-1);
	}

	
	/* INIZIO TRANSAZIONE SQLITE */ 
	sprintf(query, "BEGIN");
	rc = sqlite3_exec(dbNet_Compi, query, callbackSqlite, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "Errore SQL: %s\n", zErrMsg);			
	} 
	
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


		/* SCRITTURA DB NET_COMPI SQLITE */
		memset(query,0,sizeof(query));
		sprintf(query, "INSERT INTO PORTE_CONNESSE(ingresso_connesso, uscita_utilizzata) VALUES (\"%s\",\"%s\");",Key, Con);
		rc = sqlite3_exec(dbNet_Compi, query, callbackSqlite, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);			
		} 
 		
	}
	/* FINE TRANSAZIONE SQLITE */ 
	memset(query,0,sizeof(query));
	sprintf(query, "COMMIT");
	rc = sqlite3_exec(dbNet_Compi, query, callbackSqlite, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "Errore SQL: %s\n", zErrMsg);			
	}	
/*......................................................................*/
	dbm_close( dbp );
	printf( "dbm_close() - dbmerr: %d\n", dbmerr );

	sqlite3_close(dbNet_Compi); /* chiusura db netcompi*/

}					/* main()			*/










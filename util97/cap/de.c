/*@(#)de.c	decode()				1997-03-26	*/

#include	<stdio.h>
#include	<ctype.h>
#include	<fcntl.h>
#include	<sys/stat.h>
#include	<stdlib.h>
#include	<unistd.h>
#include 	<netdb.h>
#include	<string.h>
#include	<errno.h>

void	decode( unsigned char* , int );
void	encode( unsigned char* , int );

/*----------------------------------------------------------------------*/
/*	Define								*/

#define	OK		0
#define	NOK		(-1)
#define	LF		0x0a
#define	MOD256		0x100L

/*----------------------------------------------------------------------*/
/*	Variabili							*/

unsigned	short	xsubi[3] = { RANDSEED1, RANDSEED2, RANDSEED3 };

int	h, j, k;


long	delta;
int	bc;
int	ll;

FILE*		isp;
char		ifn[40];
unsigned char	ibf[2000];
int		LFofs[10];
int		LFofsn;

FILE*		osp;
char		ofn[40];
unsigned char	obf[2000];

char		optstr[] = "dhl:";
char		hlp_txt[] = "\n\
Uso:   de  [ -d ] -l ##  <file-in>  <file-out>\n\
\n\
 -l ##	lunghezza della linea (escluso linefeed) - Argomento richiesto.\n\
 -d	debug\n\
";

int		d_sw;

/*======================================================================*/
void	decode( bbb, lll )
unsigned char*	bbb;
int	lll;
{
unsigned char	chx;
unsigned char	chy;
char		chc;
int		k;

	xsubi [ 0 ] = RANDSEED1 ;
	xsubi [ 1 ] = RANDSEED2 ;
	xsubi [ 2 ] = RANDSEED3 ;

	for( k = 0; k < lll; k++ )
	{
#define	SUPER_SMART
#ifdef	SUPERSMART
		*(bbb+k)	= *(bbb+k) - nrand48( xsubi );
#else
		chx	= *(bbb+k);
		chc	= isprint( chx )  == 0 ? '.' : chx ;
if( d_sw ) printf( "% 3d/% 3d)  %02x {%c} -> ", k, lll, chx, chc );
		delta	= nrand48( xsubi ) ;
		chy	= delta;
		chx	-= chy;
		*(bbb+k)= chx;
		chc	= isprint( chx )  == 0 ? '.' : chx ;
if( d_sw ) printf( " %02x {%c}\n", chx, chc );
#endif
	}

}					/* decode()			*/


/*----------------------------------------------------------------------*/
void main( argc, argv )
int	argc;
char**	argv;
{
int		c;

/*----------------------------------------------------------------------*/
/*	Acquisizione e controllo degli argomenti			*/

	j	= 0;
	while( (c = getopt( argc, argv, optstr )) != EOF )
	{
		j++;
/*+ printf( "% 2d\toptind: %d\toptarg: {%s}\n", j, optind, optarg );	*/
		switch( c )
		{
		case	'd':
			d_sw	= 1;
			break;

		case	'l':
			ll	= atoi( optarg );
			break;

		case 'h':
			printf( "%s\n", hlp_txt );
			exit( 8 );

		case '?':
			fprintf( stderr, "Errore nell' argomento: %s - exiting ....\n",
						argv[optind-1] );
			fprintf( stderr, "%s\n", hlp_txt );
			exit( 9 );	/* Opzione errata		*/
			break;
		}
	}

	if( (argc - optind) < 2 || ll == 0 )
	{
		printf( "%s\n", hlp_txt );
		exit( 1 );
	}

	strcpy( ifn, argv[optind+0] );
	strcpy( ofn, argv[optind+1] );

	errno	= 0;
	isp	= fopen( ifn, "r" );
	if( isp == NULL )
	{
		printf( "Errore fopen(%s) - errno: %d\n", ifn, errno );
		exit( 2 );
	}

	errno	= 0;
	osp	= fopen( ofn, "w" );
	if( osp == NULL )
	{
		printf( "Errore fopen(%s) - errno: %d\n", ofn, errno );
		exit( 2 );
	}

/*......................................................................*/
	bc	= 7;
	while( bc > 0 )
	{
		bc	= fread( (void*)ibf, 1, ll, isp );
		if( bc < 1 ) break;
		decode( &ibf[0], ll );
ibf[ll]	= 0;
if( d_sw ) printf( "[% 3d] |%s|\n", bc, ibf );
		fwrite( (void*)ibf, 1, ll, osp );
		fputc( LF, osp );
		bc	= fread( (void*)ibf, 1, 1, isp );
	}
/*......................................................................*/

	fclose( isp );
	fclose( osp );
}					/* main()			*/

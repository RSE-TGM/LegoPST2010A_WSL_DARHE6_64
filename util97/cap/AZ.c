/*@(#)AZrout.c Codifica/Decodifica di una stringa su A...Z   1997-03-25	*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<memory.h>
#include	<ctype.h>
#include	<errno.h>

#define		PLAINTEXT_MAX	100
#define		LF		0x0a

void	do_AZ();

/*----------------------------------------------------------------------*/
/*	Variabili							*/

char	pbf[PLAINTEXT_MAX+1];		/* Plaintext  buffer		*/
int	pbfj;
char	cbf[PLAINTEXT_MAX*2+1];		/* Cyphertext buffer		*/
int	cbfj;
char	abf[PLAINTEXT_MAX*2+1];

char	cbf2[PLAINTEXT_MAX*2+1];

FILE*	isp;
char	ifn[60];

/*----------------------------------------------------------------------*/
/*	Variabili relative alle opzioni					*/

extern char	*optarg;
extern int	optind;
extern int	opterr;
extern void	do_h2c( );

char		optstr[] = "dhV";
int		c;
char		hlp_txt[] = "\n\
Uso:\n\
	AZ  [ -h | -d ] <file-1>  [ <file-2> ... ]\n\
oppure:\n\
	AZ  [ -h | -d ] < <file>\n\
\n\
	-d	debug (su stderr)\n\
";

int		d_sw;


/*======================================================================*/
/* az()		Mappa la codifica (hex) del carattere su A-Z		*/
/*
 Cypher  :  A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
 Plain   :  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 A B C D E F
 */
char*	az( chx )
unsigned char	chx;
{
static	char	azstr[4];
char		hex02[4];
int		y;
char		chi, cho;

	memset( azstr, 0, sizeof(azstr) );
	sprintf( hex02, "%02X", chx );
	for( y = 0; y < 2; y++ )
	{
		chi	= hex02[y];
		cho	= chi;
		if( isdigit( chi ) )
		{
			if( mrand48() & 2 )
			{
				cho	= chi + 'A' - '0';
			}
			else
			{
				cho	= chi + 'K' - '0';
			}
		}
		else
		{
			if( isxdigit( chi ) )
				cho	= chi + 'U' - 'A';
		}
		azstr[y]	= cho;
	}
		y	= chx;
		cho	= isprint( y )  == 0 ? '.' : chx ;
if( d_sw ) fprintf( stderr, "chx: %02x chx: {%c} -> %s\n", chx, cho, azstr );
	return	azstr;
}					/* az()				*/


/*======================================================================*/
void	do_AZ()
{
int		chi;
unsigned char	chc;
char*		ptr;


	while( (chi = fgetc( isp )) != EOF )
	{
		if( chi == LF )
		{
			putchar( chi );
			continue;
		}
		chc	= chi;
		ptr	= az( chc );
		putchar( *(ptr+0) );
		putchar( *(ptr+1) );
	}

}					/* do_AZ()			*/

/*======================================================================*/
void main( argc, argv )
int	argc;
char**	argv;
{
int	j, k;

/*----------------------------------------------------------------------*/
/*	Acquisizione delle opzioni					*/

	j		= 0;
	while( (c = getopt( argc, argv, optstr )) != EOF )
	{
		j++;
		switch( c )
		{
		case 'd':
			d_sw	= 1;
			break;

		case 'h':
		case 'H':
			printf( "%s\n", hlp_txt );
			exit( 0 );
			break;

		case '?':
			fprintf( stderr, "Errore nell' argomento: %s - exiting ....\n",
						argv[optind-1] );
			fprintf( stderr, "%s\n", hlp_txt );
			exit( 9 );	/* Opzione errata		*/
			break;
		}
	}

	if( optind >= argc )
	{
		strcpy( ifn, " " );
		isp	= stdin;
		do_AZ();
	}
	else
	{
		for( k = optind; k < argc; k++ )
		{
			strcpy( ifn, argv[k] );
			isp	= freopen( ifn, "r", stdin );
			if( isp == NULL )
			{
				fprintf( stderr, "Errore freopen() %s - errno : %d.\n",
							ifn, errno );
				continue;
				exit( 1 );	/* =1 : NOK		*/
			}
			do_AZ();
			fclose( isp );
		}
	}

	exit( 0 );

}					/* main()			*/

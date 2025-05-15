/*@(#)ZArout.c Codifica/Decodifica di una stringa su A...Z   1997-03-25	*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<memory.h>
#include	<ctype.h>
#include	<errno.h>
#include <getopt.h>

#define		PLAINTEXT_MAX	100
#define		LF		0x0a

void	do_ZA();

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

char		optstr[] = "dhHV";
int		c;
char		hlp_txt[] = "\n\
Uso:\n\
	ZA  [ -h | -d ] <file-1>  [ <file-2> ... ]\n\
oppure:\n\
	ZA  [ -h | -d ] < <file>\n\
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
unsigned	char	chx;
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
	return	azstr;
}					/* az()				*/


/*======================================================================*/
void	do_ZA()
{
int		chi;
int		chy;
int		chz;
unsigned char	chc;
char		ch0, ch1;
int		cnt = 0;


	while( (chi = fgetc( isp )) != EOF )
	{
		if( chi == LF )
		{
			putchar( chi );
			continue;
		}

		cnt++;
		chc	= chi;
		if( cnt % 2 )
		{
			if( chc <= 'J' )               ch0 = chc - 'A';
			if( chc >= 'K' && chc <= 'T' ) ch0 = chc - 'K';
			if( chc >= 'U' )               ch0 = chc - 'U' + 0xa;
if( d_sw ) fprintf( stderr, "chi: %02X {%c} - ch0: %02x /", chi, chc, ch0 );
		}
		else
		{
			if( chc <= 'J' )               ch1 = chc - 'A';
			if( chc >= 'K' && chc <= 'T' ) ch1 = chc - 'K';
			if( chc >= 'U' )               ch1 = chc - 'U' + 0xa;
			chy	= (ch0 << 4) + ch1;
chz	= chy;
			chc	= isprint( chz )  == 0 ? '.' : chz ;
if( d_sw ) fprintf( stderr, " ch1: %02x -> chy:%02X {%c}\tcnt:% 4d\n", ch1, chy, chc, cnt );
			putchar( chy );
		}
	}

}					/* do_ZA()			*/

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
		do_ZA();
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
			do_ZA();
			fclose( isp );
		}
	}

	exit( 0 );

}					/* main()			*/

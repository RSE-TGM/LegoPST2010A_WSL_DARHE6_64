#define	BINARY_SEARCH
/*@(#)S01_2_f01.c Aggiunta tag (in f01.S01) in base all' S01 1997-05-27	*/

#ifdef	REF_ONLY
<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
****
CC_PUERTO                 Puertollano_Combined_Cycle
****
CALCUL	High Pressure System - Regolation Task
COLU	Simplified Process
****
../../legocad/r_calcul/	R	CALCUL	F
../../legocad/r_colu/	R	COLU	D
****
OS ucin7 guest 	../../legocad/r_calcul/
OS ucin7 guest 	../../legocad/r_colu/
****
1.000000
1.000000
****
CALCUL
II060TCA	COLU	UU0D0GCO	! @#K@0TNL03CF636#XQ02#0CAL00FF007#
II0411CA	COLU	UU0E0GCO	! @#K@0TNL03CF636#XQ02#0CAL00FF008#
****
COLU
II1U0WCO	CALCUL	UU1Z0RCA	! @#K@0CAL00FF005#XQ01#0TAL02DF632#
II1T0YCO	CALCUL	UU1W0RCA	! @#K@0CAL00FF005#XQ01#0TEB03DL604#
II1T0UCO	CALCUL	UU1V0RCA	! @#K@0CAL00FF005#XQ01#0TEK01DL601#
II2417CO	CALCUL	UU1X0RCA	! @#K@0CAL00FF005#XQ01#0TLP01DF604#
II2D19CO	CALCUL	UU200RCA	! @#K@0CAL00FF005#XQ01#0TLP03DF633#
II2A1BCO	CALCUL	UU1Y0RCA	! @#K@0CAL00FF005#XQ01#0TLR02DF631#
II1W1DCO	CALCUL	UU210RCA	! @#K@0CAL00FF005#XQ01#0TNL02DF634#
JI1U0YCO	CALCUL	VU2P0RCA	! @#K@0CAL00FF005#XV01#0TEB03DL604
JI2M0XCO	CALCUL	VU2P0RCA	! @#K@0CAL00FF005#XV01#0TEB03DL604
JI290ZCO	CALCUL	VU2P0RCA	! @#K@0CAL00FF005#XV01#0TEB03DL604
JI2M0TCO	CALCUL	VU2O0RCA	! @#K@0CAL00FF005#XV01#0TEK01DL601
JI1U0UCO	CALCUL	VU2O0RCA	! @#K@0CAL00FF005#XV01#0TEK01DL601
II1Y1ECO	CALCUL	UU0911CA	! @#K@0CAL00FF008#XQ01#0TNL03DF636#
****
BM
SCADA
BI
****
<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif

/*----------------------------------------------------------------------*/
/*		INCLUDE							*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<ctype.h>
#include	<unistd.h>
#include	<getopt.h>
#include	<memory.h>
#include	<errno.h>
#include	<string.h>


/*----------------------------------------------------------------------*/
/*	DEFINE								*/

#define		LF	012
#define		SLASH	'/'

#define		INPUT	0
#define		OUTPUT	1

#define		REG_TYPE	'R'
#define		TASK_COUNT	100
#define		TASK_NAME_LEN	256
#define		TASK_PATH_LEN	1025
#define		TASK_DESCR_LEN	100
#define		TASK_SPEC_LEN	10
#define		TASK_TIME_LEN	10
#define		VAR_COUNT	10000
/*+ #define	VAR_TAG_LEN	50	<<< IN REALTA' ARRIVANO A 56	*/
#define		VAR_TAG_LEN	60
#define		VAR_NAME_LEN	9
#define		VAR_DESCR_LEN	100 

#define		TKNTBL_DIM	20

#define		IF( o )	if( (strchr( d_opt, (int)'*' ) != NULL) || (strchr( d_opt, (int)o ) != NULL) )

char*	get_str();
char*	get_tag();
void	tokens();
int	Varcmp( const void*, const void* );

/*----------------------------------------------------------------------*/
/*	STRUTTURE							*/

/*......................................................................*/
/*
 * Each task in the list file has these members.
 */
struct TaskEntry
{
	char	Type;			/* Type of task. */
	char	Name  [TASK_NAME_LEN];	/* Task name. */
	char	Path  [TASK_PATH_LEN];	/* Path name of the data file relative to the task. */
	char	Spec  [TASK_SPEC_LEN];	/* Regular expression ... */
	char	Time  [TASK_TIME_LEN];	/* Time of execution. */
	char	Descr [TASK_DESCR_LEN];	/* Description. */
};

/*......................................................................*/
/*
 * Each variable has these attributes.
 */
struct VarEntry
{
	char	TName [TASK_NAME_LEN];	/*+Task name. */
	char	Name  [VAR_NAME_LEN];	/*@Var name. */
	char	Tag   [VAR_TAG_LEN];	/*@Complete tag including Key. */
	char	Descr [VAR_DESCR_LEN];	/* Description including Tag. */
	int	Type;			/* INPUT, OUTPUT
	int	Connected;		/* How many connections? */
};


/*----------------------------------------------------------------------*/
/*	VARIABILI							*/

char	optstr[] = "d:hiV";
char		hlp_txt[] = "\n\
S01_2_f01 - Aggiunta o sostituzione di tag e commenti dei file 'f01.dat' , relativi a\n\
	    task (che NON siano di regolazione), in base al contenuto di un file 'S01'.\n\
            I file prodotti hanno nome: 'f01.S01' .\n\
\n\
Uso: S01_2_f01  [ -hiV -d 'xxx' ] \n\
Opzioni e argomenti:\n\
  -d 'xxx'	Stampe di debug (ogni carattere seleziona un corrispondente output\n\
  -d '*'	Per avere tutti gli output di debug\n\
  -h		Questo testo di help\n\
  -i		Non introduce modifiche (crea una copia identica)\n\
  -V		Fornisce la versione\n\
";

char	ver_txt[] = "S01_2_f01: Versione 1.1    1997-05-27";

int	i_opt;
char	d_opt[20];

/*......................................................................*/
char	S01fn[]	= "S01";
FILE*	S01fp;
char	S01bf[512];
int	S01ln;

char	f01ibn[] = "/f01.dat";
char	f01ifn[80];
FILE*	f01ifp;
char	f01ibf[512];
int	f01iln;

char	f01obn[] = "/f01.S01";
char	f01ofn[80];
FILE*	f01ofp;
char	f01obf[512];
int	f01oln;
char	fputsbf[512];

struct	stat	statbf;

char*	star	= "****";
int	starno;
int	starofs;
int	modcnt;
int	Rflg;		/* = 0/1 : la task NON e'/E' di regolazione	*/
char*	tkntbl[TKNTBL_DIM];
char*	tknsep	= "	 ";	/* Caratteri separatori: <TAB> , <SP>	*/

struct	TaskEntry	TaskTbl[TASK_COUNT];
int			TaskTbln;		/* # entry    / TaskTbl	*/
int			TaskTblx;		/* entry corr./ TaskTbl	*/
struct	VarEntry	VarTbl[VAR_COUNT];
int			VarTbln;

char			TaskName[TASK_NAME_LEN];
char			VarName[VAR_NAME_LEN];
char			Tag[VAR_TAG_LEN];
int			Var_type;
char	TaskCrnt[TASK_NAME_LEN];	/* Current-Task name		*/


/*======================================================================*/
/*		SUBROUTINE						*/

/*----------------------------------------------------------------------*/
/*	Individuazione di una stringa					*/

char*
get_str( bbb, sss )
char*	bbb;			/* Buffer in cui ricercare		*/
char*	sss;			/* Stringa da    ricercare		*/
{
char*		ppp;
char*		qqq;

	if( sss == NULL ) return NULL;		/* sanity check		*/

	ppp	= bbb;
	while( strlen( ppp ) > strlen( sss ) )
	{
		qqq	= strchr( ppp, *sss );
		if( qqq == NULL ) break;
		if( strncmp( qqq, sss, strlen( sss ) ) == 0 ) break;
		ppp	= qqq;
		ppp++;
	}
	return	qqq;		/* Ritorna il puntatore alla stringa	*/

}					/* get_str()			*/


/*----------------------------------------------------------------------*/
/*	Individuazione della tag					*/

char*
get_tag( sss )
char*	sss;
{
char*		ppp;
char*		qqq;

	ppp	= sss;
	while( strlen( ppp ) > 3 )
	{
		qqq	= strchr( ppp, '@' );
		if( qqq == NULL ) break;
		if( strncmp( qqq, "@#K@", 4 ) == 0 ) break;
		ppp	= qqq;
		ppp++;
	}
	return	qqq;		/* Ritorna il puntatore alla tag	*/

}					/* get_tag()			*/


/*----------------------------------------------------------------------*/
/*	Interpretazione della linea del file f01 ed event. modifica	*/
/*	N.B. - Le linee contenute sono del tipo:

UU0501CO  --UA-- smtr05 @#K@0TAL02CF632_XQ01  TEK02 INLET AL FLOW  %
VH1E0ICO  --UA-- sicc1E MEMPULOP : Memory for command output PULSE OPEN
IB0501CO  --IN-- smtr05 IB    : Bias
VF040CCO  --IN-- #JI1G0HCO#....................<===D0120CCO.-D012-
UU0401CO  --UA-- saio04 0TAL02CF632  TEK02 INLET AL FLOW  kg/sec

 */

void filter_f01()
{
struct	VarEntry	Varkey;
struct	VarEntry*	Varppp;
char*		ppp;
int		jj;
int		task_flg;

	strcpy( f01obf, f01ibf );	/* Copia l' input sull' output	*/
	if( i_opt ) return;

/*......................................................................*/
/*	Le modifiche si applicano solo dopo 3 '****'			*/
/*	e se il 2^ token e`: --IN-- , --UA-- , --US--			*/

	tokens( f01ibf, &tkntbl );
	if( strncmp( tkntbl[0], star, strlen(star) ) == 0 )
	{
		starno++;
		return;
	}
	if( starno < 3 ) return;
	if( strcmp( tkntbl[1], "--IN--" ) != 0 &&
	    strcmp( tkntbl[1], "--UA--" ) != 0 &&
	    strcmp( tkntbl[1], "--US--" ) != 0 ) return;

/*......................................................................*/
/*	Ricerca in VarTbl match per task-name e var-name		*/


	strcpy( VarName, tkntbl[0] );
	IF( 'm' ) printf( "mmm % 6d. filter_f01 TaskName:%-8s - VarName:%-8s\n",
		f01iln, TaskName, VarName );

/*	Inizializza la chiave per la ricerca binaria			*/
	memset( (char*)&Varkey, 0, sizeof(Varkey) );
	strcpy( Varkey.TName, TaskName );
	strcpy( Varkey.Name,  VarName );

	Varppp	= bsearch( (void*)&Varkey, (void*)&VarTbl[0],
			(size_t)VarTbln, sizeof(VarTbl[0]), Varcmp );

	if( Varppp == NULL ) {
/*
           printf("filter_f01 DEBUG: ricerca fallita per %s\n", VarName);
*/
           return;		/* ricerca fallita	*/
        }
/*
printf("filter_f01 DEBUG: trovata variabile %s in S01!!!!\n", VarName);
*/
	strcpy( Tag, (*Varppp).Tag );
	Var_type = (*Varppp).Type;
	if( strcmp( tkntbl[1], "--IN--" ) == 0 &&
	     Var_type == OUTPUT ) return;  /* Non scrive TAG sulle Var interne collegate  */

	IF( '~' ) printf( "~~~ % 6d. filter_f01 TaskName:%-8s - VarName:%-8s - Tag:%s - Var_type:%d\n",
		f01iln, TaskName, VarName, Tag, Var_type );

/*+!	ppp	= get_str( f01obf, tkntbl[3] );				*/
	ppp	= get_str( f01obf, tkntbl[2] );
	if( ppp == NULL )
	{
		strcat( f01obf, " " );	/* aggiunge uno spazio		*/
	}
	else
	{
		*ppp = 0;		/* tronca la stringa		*/
	}
	strcat( f01obf, Tag );		/* aggiunge la tag		*/
	modcnt++;
	IF( '!' ) printf( "!!! % 6d. filter_f01 TaskName:%-8s - VarName:%-8s\n",
		f01iln, TaskName, VarName, Tag );

}					/* filter_f01()			*/


/*----------------------------------------------------------------------*/
/*	Interpretazione della linea del file S01
|
|	- Dopo la 3^ riga con '****' estrae e memorizza path e task-name
|	  nella tabella TaskTbl :
|		../../legocad/r_calcul/ R       CALCUL  F
|		../../legocad/r_colu/   R       COLU    D
|
|	- Dopo la 6^ riga con '****' , e fino alla 6+Numero/Task :
|		estrae e memorizza i nomi degli ingressi CON commento
|		(cioe' dal 4^ token in poi) nella tabella VarTbl.
|		Le righe sono del tipo:
IN_1HAU1  GTS000NG  WTOTGCX1  ! @#K@XMBA26CF701 Flue Gas Mass Flow : INPUT N. 
IN_4IOJ1  GTS000NG  WTUBGJK3  ! @#K@XHAH81CF701 NOx ADDITIVE STEAM TO GAS TURB
OMPMLCDF  LPSREG0   UD0O37LP  ! @#K@0HAG61AP001 ROTATIONAL SPEED "ACTUATOR"
WE_1ICR2  STS000NG  WVALSCR3  ! @#K@XLBC80CF701
*/

void parse_S01()
{
char*		ppp;
char*		iii;
int		jj;
int		ii;

	if( strncmp( S01bf, star, strlen(star) ) == 0 )
	{
		starno++;
		starofs	= 0;
		IF( '#' ) printf( "###% 6d. - starno:% 3d\n", S01ln, starno );
		return;
	}

	switch( starno )
	{
	case	3:
		tokens( S01bf, &tkntbl );
		IF( '#' ) printf( "###% 6d. - starno:% 3d\n", S01ln, starno );
/*+		IF( '.' ) printf( "...% 6d. - Directory: %-30s Type: %s Task-name: %-8s\n",
 *+				S01ln, tkntbl[0], tkntbl[1], tkntbl[2] );	*/
		strcpy( TaskTbl[TaskTbln].Path, tkntbl[0] );
		TaskTbl[TaskTbln].Type	= *tkntbl[1];
#ifdef	VALIDO_SOLO_PER_TASK_REGOLAZIONE
		if( tkntbl[2] != NULL ) strcpy( TaskTbl[TaskTbln].Name, tkntbl[2] );
#else
/*	Estrae il nome della task dal 1^ token (del tipo: ./STS000NG/ )		*/
		iii	= strrchr( tkntbl[0], SLASH );
		if( iii == NULL )
		{
			fprintf( stderr, "Impossibile determinare il nome della task\n" );
			fprintf( stderr, "%6d. - %s\n", S01ln, S01bf );
			exit( 99 );
		}
		*iii	= 0;
		ppp	= strrchr( tkntbl[0], SLASH );
		ppp++;
		strcpy( TaskTbl[TaskTbln].Name, ppp );
#endif
		IF( '.' ) printf( "...% 6d. - Directory: %-30s Type: %c Task-name: %-8s\n",
				S01ln, TaskTbl[TaskTbln].Path,
				TaskTbl[TaskTbln].Type, TaskTbl[TaskTbln].Name );
		TaskTbln++;
		break;

	default:
		if( TaskTbln == 0 ) break;
		if( starno < 6 ) break;
		if( starno > (TaskTbln+5) ) break;

		starofs++;
		if( starofs == 1 )
		{
			IF( 'k' ) printf( "kkk% 6d. [%02d] %s\n", S01ln, starno, S01bf );
			tokens( S01bf, &tkntbl );
			strcpy( TaskCrnt, tkntbl[0] );
			Rflg	= 1;
			for( jj = 0; jj < TaskTbln; jj++ )
			{
				if( strcmp( TaskCrnt, TaskTbl[jj].Name ) == 0 )
				{
					TaskTblx	= jj;
/*+!					if( TaskTbl[jj].Type == REG_TYPE ) Rflg = 1;	*/
					if( TaskTbl[jj].Type != REG_TYPE ) Rflg = 0;
			IF( 'k' ) printf( "kkk% 6d. %c\n", S01ln,  TaskTbl[jj].Type );
					break;
				}
			}
			IF( 'R' ) printf( "RRR% 6d. - La task [%-8s] %-6s di regolazione [%d]\n",
				S01ln, TaskCrnt, Rflg ? "E'" : "NON e'" ,Rflg  );
		}
		
		{
/*+!			if( TaskTbl[TaskTblx].type != REG_TYPE ) break;	*/
			if( TaskTbl[TaskTblx].Type == REG_TYPE ) break;
			IF( '?' ) printf( "???% 6d. [%02d] %s\n", S01ln, starno, S01bf );
			tokens( S01bf, &tkntbl );
/*......................................................................*/
/*+/+			se NON e` presente la tag IGNORA la variabile	*/
/*			se NON e` presente 4^ token IGNORA la variabile	*/
			if( tkntbl[3] != NULL )
			{
				IF( '@' ) printf( "@@@% 6d. [%02d] %s\n", S01ln, starno, S01bf );
				strcpy( VarTbl[VarTbln].TName, TaskCrnt );
				strcpy( VarTbl[VarTbln].Name, tkntbl[0] );
				VarTbl[VarTbln].Type=INPUT;
/*+/+				ppp	= get_tag( S01bf );			*/
				ppp	= get_str( S01bf, tkntbl[3] );
				if( ppp != NULL )
				{
					strcpy( VarTbl[VarTbln].Tag, ppp );
				}
				VarTbln++;
				strcpy( VarTbl[VarTbln].TName, tkntbl[1] );
				strcpy( VarTbl[VarTbln].Name, tkntbl[2] );
				VarTbl[VarTbln].Type=OUTPUT;
				if( ppp != NULL )
				{
					strcpy( VarTbl[VarTbln].Tag, ppp );
				}
                                ii=1;
                                while (ii < VarTbln)
                                {
                                  if(strcmp(VarTbl[VarTbln].Name,VarTbl[ii].Name) == 0)
                                  {
printf("**********   WARNING!!! Duplicazione variabili!!!   **********\n");
printf("%s   %s   %s   %s\n",VarTbl[ii-1].Name, VarTbl[ii].TName,
       VarTbl[ii].Name, VarTbl[ii].Tag);
printf("%s   %s   %s   %s\n\n",VarTbl[VarTbln-1].Name, VarTbl[VarTbln].TName,
       VarTbl[VarTbln].Name, VarTbl[VarTbln].Tag);
                                  break; 
                                  }
                                  ii=ii+2;
                                }
				VarTbln++;
			}
			else
			{
				IF( '/' ) printf( "///% 6d. [%02d] %s\n", S01ln, starno, S01bf );
			}
		}
		break;
	}
}					/* parse_S01()			*/


/*----------------------------------------------------------------------*/
/*	Lettura f01.dat / aggiunta tag / scrittura f01.S01		*/

void rdwr_f01( tname, fpath )
char*	tname;
char*	fpath;
{
int		status;
char*		ppp;

/*......................................................................*/
/*	Costruzione file-name di input					*/
	memset( f01ifn, 0, sizeof(f01ifn) );
	strcpy( f01ifn, fpath );
	strcat( f01ifn, f01ibn );
	IF( 'o' ) printf( "ooo open(%s) [read]  ...\n", f01ifn );

/*	Costruzione file-name di output					*/
	memset( f01ofn, 0, sizeof(f01ofn) );
	strcpy( f01ofn, fpath );
	strcat( f01ofn, f01obn );
	IF( 'o' ) printf( "ooo open(%s) [write] ...\n", f01ofn );

/*......................................................................*/
	errno	= 0;
	status	= stat( f01ifn, &statbf );
	if( status != 0 )
	{
		fprintf( stderr, "Errore stat(%s) - errno: %d\n", f01ifn, errno );
		return;
	}

/*......................................................................*/
/*	Open file di input ( f01.dat )					*/
	f01iln	= 0;
	errno	= 0;
	f01ifp	= fopen( f01ifn, "r" );
	if( f01ifp == NULL )
	{
		fprintf( stderr, "Errore fopen() %s - errno : %d.\n", f01ifn, errno );
		return;
	}
	starno	= 0;
	modcnt	= 0;

/*......................................................................*/
/*	Open file di output ( f01.S01 )					*/
	f01oln	= 0;
	errno	= 0;
	f01ofp	= fopen( f01ofn, "w" );
	if( f01ofp == NULL )
	{
		fprintf( stderr, "Errore fopen() %s - errno : %d.\n", f01ofn, errno );
		fclose( f01ifp );
		return;
	}

/*......................................................................*/
/*	Loop di lettura - (eventuale) modifica - scrittura		*/
	while( (ppp = fgets( f01ibf, sizeof(f01ibf), f01ifp )) != NULL )
	{
		f01iln++;
		if( (ppp = strchr( f01ibf, LF )) != NULL ) *ppp = 0;

		filter_f01();			/* eventuale modifica	*/

		sprintf( fputsbf, "%-80s\n", f01obf );
		fputs( fputsbf, f01ofp );
		f01oln++;
	}

	IF( 'K' ) printf( "KKK %-40s f01iln:% 6d. - f01oln:% 6d. - modcnt:% 6d.\n",
		f01ifn, f01iln, f01oln, modcnt );
	fclose( f01ifp );
	fclose( f01ofp );

}					/* rdwr_f01()			*/


/*----------------------------------------------------------------------*/
/*	Lettura e analisi del file S01					*/

void read_S01()
{
char*		ppp;

	errno	= 0;
	S01fp	= fopen( S01fn, "r" );
	if( S01fp == NULL )
	{
		fprintf( stderr, "Errore fopen() %s - errno : %d.\n", S01fn, errno );
		exit( 1 );	/* =1 : NOK		*/
	}
	while( (ppp = fgets( S01bf, sizeof(S01bf), S01fp )) != NULL )
	{
		S01ln++;
		if( (ppp = strchr( S01bf, LF )) != NULL ) *ppp = 0;
		parse_S01();
	}
	fclose( S01fp );

}					/* read_S01()			*/



/*----------------------------------------------------------------------*/
/*	Routine di utilita' per estrarre i token da una stringa		*/

void
tokens( sss, tp )
char*	sss;			/* Stringa da suddividere		*/
char**	tp;			/* Array di puntatori per i token	*/
{
char	tknbf[512];
char*	s1;
char*	ppp;
int	jj;

	for( jj = 0; jj < TKNTBL_DIM; jj++ ) tkntbl[jj] = NULL;
	strcpy( tknbf, sss );

	jj	= 1;
	ppp	= tknsep;
	s1	= tknbf;
	while( ppp != NULL )
	{
		ppp	= strtok( s1, tknsep );
		if( ppp == NULL ) break;
/*+		printf( "% 2d : ppp: |%s|\n", jj, ppp );		*/
		*tp	= ppp;
		tp++;
		s1	= NULL;
		jj++;
	}
}					/* tokens()			*/


/*----------------------------------------------------------------------*/
int
Varcmp(  const void * Var1 , const void * Var2 )
{
int	rv;
/*+
 *	struct VarEntry** Entry1 = (struct VarEntry**)Var1;
 *	struct VarEntry** Entry2 = (struct VarEntry**)Var2;
 */
struct	VarEntry*	E1;
struct	VarEntry*	E2;
char    str1[TASK_NAME_LEN+VAR_NAME_LEN];
char    str2[TASK_NAME_LEN+VAR_NAME_LEN];

	E1	= (struct VarEntry*)Var1;
	E2	= (struct VarEntry*)Var2;

        strcpy(str1, (*E1).TName);
        strcat(str1, (*E1).Name);

        strcpy(str2, (*E2).TName);
        strcat(str2, (*E2).Name);
/*
           printf("Varcmp DEBUG: str1 = %s   str2 = %s\n",
                  str1, str2);
*/
        rv = strcmp( str1, str2);

        IF( ':' ) printf( "::: % 4d [%-8s/%-8s] :: [%-8s/%-8s]\n", rv,
                        (*E1).TName, (*E1).Name, (*E2).TName, (*E2).Name );

        if(rv == 0) {
/*
           printf("Varcmp DEBUG: TROVATO task = %s   VAR = %s\n",
                  (*E1).TName, (*E1).Name);
*/
        }

        return rv;

}					/* Varcmp()			*/


/*======================================================================*/
/*		MAIN							*/

int main( argc, argv )
int	argc;
char**	argv;
{
int		c;
int		j;


/*----------------------------------------------------------------------*/
/*	Acquisizione e controllo degli argomenti			*/

	j	= 0;
	while( (c = getopt( argc, argv, optstr )) != EOF )
	{
		j++;
/*+ printf( "% 2d\toptind: %d\toptarg: {%s}\n", j, optind, optarg );	*/
		switch( c )
		{
		case 'd':
			strcpy( d_opt, optarg );
			break;

		case 'h':
			printf( "%s\n", hlp_txt );
			exit( 0 );

		case 'i':
			i_opt	= 1;
			break;

		case 'V':
			printf( "%s\n", ver_txt );
			exit( 0 );

		case '?':
			fprintf( stderr, "Errore nell' argomento: %s - exiting ....\n",
						argv[optind-1] );
			fprintf( stderr, "%s\n", hlp_txt );
			exit( 1 );
		}
	}

/*......................................................................*/
/*	Lettura file: S01						*/

	void read_S01();

	IF( 'T' )
	{
		printf( "\nTTT Tabella: TaskTbl[%d]\n", TaskTbln );
		for( j = 0; j < TaskTbln; j++ )
		{
			printf( "TTT % 5d) |%-8s|%c|%s|\n",
				j, TaskTbl[j].Name, TaskTbl[j].Type, TaskTbl[j].Path );
		}
	}

	IF( 'T' )
	{
		printf( "\nTTT Tabella: VarTbl[%d]\n", VarTbln );
		for( j = 0; j < VarTbln; j++ )
		{
			printf( "TTT % 5d] |%-8s|%-8s|%s|\n", j,
			 VarTbl[j].TName, VarTbl[j].Name, VarTbl[j].Tag );
		}
	}

/*......................................................................*/
/*	Sort della tabella delle variabili				*/

	qsort( (void*)&VarTbl[0], (size_t)VarTbln, sizeof(VarTbl[0]), Varcmp );

	IF( 'T' )
	{
		printf( "\nTTT Tabella: VarTbl[%d] (QSORTED)\n", VarTbln );
		for( j = 0; j < VarTbln; j++ )
		{
			printf( "TTT % 5d] |%-8s|%-8s|%s|\n", j,
			 VarTbl[j].TName, VarTbl[j].Name, VarTbl[j].Tag );
		}
	}

/*......................................................................*/
/*	Lettura file: r_.../f01.dat e output su r_.../f01.S01		*/

	for( j = 0; j < TaskTbln; j++ )
	{
/*+!		if( TaskTbl[j].Type != REG_TYPE ) continue;		*/
		if( TaskTbl[j].Type == REG_TYPE ) continue;
		strcpy( TaskName, TaskTbl[j].Name );
		rdwr_f01( TaskTbl[j].Name, TaskTbl[j].Path );
	}

}					/* main()			*/

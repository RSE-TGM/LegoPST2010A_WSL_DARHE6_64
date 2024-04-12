/*@(#)CAPmngr.c Main per il Controllo Accesso Programmi 1997-03-24	*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<ctype.h>
#include	<fcntl.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<string.h>
#include	<errno.h>
#include	"CAP.h"

/*----------------------------------------------------------------------*/
/*	Define								*/

#define	OK		0
#define	NOK		(-1)
#define	LF		0x0a

/*----------------------------------------------------------------------*/
/*	Variabili							*/

char	* fni = NULL ;
FILE*	fpi = NULL ;
char	* fno = NULL ;
FILE*	fpo = NULL ;
char * IniFileName = NULL ;
FILE * IniFilefp = NULL ;
unsigned char	line[2001];
int	linel;
unsigned char	vvv[PLAINTEXT_MAX];

/*----------------------------------------------------------------------*/
/*	Variabili relative alle opzioni					*/

extern void	do_cap( );

char		hlp_txt[] = "\n\
        CAPmngr - Controllo Accesso Programmi\n\
Uso:\n\
	CAPmngr  [ -hV ] -c | -d | -i\n\
  -c		codifica\n\
  -d		decodifica\n\
  -f file	file di inizializzazione\n\
  -i            recupera informazioni dal file CAP.info\n\
  -h		questo testo di help\n\
  -V		fornisce la versione\n\
";
int	d_sw;
int	c_sw;
int     i_sw;

/*======================================================================*/
/* Funzione che recupera dal file CAP.info le informazioni seguenti:    */
/*   - SysName: nome del sistema oprativo                                                          */
/*   - Machine: nome della macchina                                                          */
/*   - Address: indirizzo IP oppure MAC address                                                          */
/*======================================================================*/

/*----------------------------------------------------------------------*/
void    get_CAPinfo(unsigned char *info, short type)
{
struct CAPinfo     *NewInfo = NULL ;
struct CAPinfo_IP  *NewInfo_IP = NULL; 
unsigned char      *ppp;
char               PrintAddress[ADDRESS_LEN+1];
char               PrintSysName[SYSNAME_LEN+1];
char               PrintMachine[MACHINE_LEN+1];

char               PrintProgramID[100];
char               PrintEnelInfo[100];


   AZdecode( info, &ppp );      
      
   if( type == 0 ) {
      NewInfo = ( struct CAPinfo * ) ppp ;
      strncpy(PrintAddress,
              NewInfo->Address,
              ADDRESS_LEN);

      strncpy(PrintSysName,
              NewInfo->SysName,
              SYSNAME_LEN);

      strncpy(PrintMachine,
              NewInfo->Machine,
              MACHINE_LEN);

      strncpy(PrintProgramID,
              NewInfo->ProgramID,
              PROGRAMID_LEN);

      strncpy(PrintEnelInfo,
              NewInfo->EnelInfo,
              ENELINFO_LEN);

      PrintAddress[ADDRESS_LEN] = '\0';      
   }
   else {
      NewInfo_IP = ( struct CAPinfo_IP * ) ppp ;
      strncpy(PrintAddress,
              NewInfo_IP->Address,
              ADDRESS_LEN_IP);
    
      strncpy(PrintSysName,
              NewInfo_IP->SysName,
              SYSNAME_LEN);

      strncpy(PrintMachine,
              NewInfo_IP->Machine,
              MACHINE_LEN);

      strncpy(PrintProgramID,
              NewInfo_IP->ProgramID,
              PROGRAMID_LEN);

      strncpy(PrintEnelInfo,
              NewInfo_IP->EnelInfo,
              ENELINFO_LEN);
      
      PrintAddress[ADDRESS_LEN_IP] = '\0';
   }

   PrintProgramID[PROGRAMID_LEN] = '\0';
   PrintEnelInfo[ENELINFO_LEN] = '\0';   
   
   PrintSysName[SYSNAME_LEN] = '\0';
   PrintMachine[MACHINE_LEN] = '\0';

   printf("\n****************** CAP.info ****************\n");
   printf("Address: %s\n", PrintAddress);
   printf("SysName: %s\n", PrintSysName);
   printf("Machine: %s\n", PrintMachine);

   printf("ProgramID: %s\n", PrintProgramID);
   printf("EnelInfo: %s\n", PrintEnelInfo);

return;
}


/*----------------------------------------------------------------------*/
void	do_cap()
{
unsigned char*	lll;
unsigned char*	ppp;		/* plain  (dopo     la AZdecode)	*/
unsigned char*	ccc;		/* cypher (prima della AZencode)	*/
int		bc;
short           type_info = 0;


	linel	= CAPINFO_SZ * 2 +1;
	lll	= line;
	errno	= 0;
	while( 1 )
	{
/* Leggo la riga del file CAP.info */
		bc	= fread( lll, 1, (CAPINFO_SZ*2+1), fpi );
		if( bc == 0 ) return;
	        if( bc != linel )
		{
/* Il numero di caratteri costituenti la riga è diverso da quello che
   ci si aspetta. Se l'opzione è '-i' rileggo la linea e controllo se il
   numero di caratteri è quello che si ha con indirizzo IP presente. */
                   if( i_sw )
                   {    
                      rewind(fpi);
                      bc = fread( lll, 1, (CAPINFO_IP_SZ*2+1), fpi );
                      if( bc != (CAPINFO_IP_SZ*2+1))
                      {
			  printf( "Lunghezza linea (%d)diversa da: %d !\n",  bc,
                                  (CAPINFO_IP_SZ*2+1) );
			  exit( 9 );
                      }
                      else
                      {
/* Caso in cui è presente l'indirizzo IP */ 
                         line[CAPINFO_IP_SZ*2+1-1]	= '\0';
                         type_info = 1;
                      }
                   }
                   else
                   {
                      printf( "Lunghezza linea (%d)diversa da: %d !\n",  bc,
                                  (CAPINFO_SZ*2+1) );
		      exit( 9 );
                   }
		}
                else
                {
/* Caso in cui è presente il MAC address */
		   line[CAPINFO_SZ*2+1-1]	= '\0';
                   type_info = 0;
                }
                
                if( i_sw ) {
/* Chiamata alla funzione che restituisce le informazioni presenti 
   in CAP.info */
                   get_CAPinfo(line, type_info);
                   return;
                }

if ( Debug ) {
printf( "lll |%s|\n", lll );
}

		if( c_sw ) {

		  /*
		   * For every line in the Ini file build an entry in the conf file.
		   * Every line in the Ini file has the format: "ProgramID\tEnelInfo".
		   */
#ifdef NUTC
                  char IniFileLine [ PROGRAMID_LEN + 1 + ENELINFO_LEN + 3 ] ;
#else
                  char IniFileLine [ PROGRAMID_LEN + 1 + ENELINFO_LEN + 2 ] ;
#endif
                  memset(IniFileLine, ' ', (PROGRAMID_LEN + 1 + ENELINFO_LEN + 2));

		  while ( fgets ( IniFileLine , sizeof ( IniFileLine ) , IniFilefp ) != NULL ) {

		    /* Modify ppp entry. */

		    struct CAPinfo * NewInfo = NULL ; 

		    AZdecode( lll, &ppp );
                    
		    NewInfo = ( struct CAPinfo * ) ppp ;
/*
printf("Licenza: %s\n", IniFileLine);
*/
		    memset ( NewInfo -> ProgramID , ' ' , PROGRAMID_LEN ) ;
		    memset ( NewInfo -> EnelInfo , ' ' , ENELINFO_LEN ) ;

		    strncpy ( NewInfo -> ProgramID , 
			      IniFileLine , 
			      PROGRAMID_LEN ) ;
#ifdef NUTC
		    strncpy ( NewInfo -> EnelInfo , 
			      IniFileLine + PROGRAMID_LEN + 1 , 
			      (strlen ( IniFileLine + PROGRAMID_LEN + 1 ) - 2) /* No trailing newline. */ ) ;
#else
                    strncpy ( NewInfo -> EnelInfo , 
			      IniFileLine + PROGRAMID_LEN + 1 , 
			      (strlen ( IniFileLine + PROGRAMID_LEN + 1 ) - 1) /* No trailing newline. */ ) ;
#endif

		    encode( ppp, CAPINFO_SZ );

		    AZencode( ppp, &ccc );

if ( Debug ) {
printf( "ccc  %02x %02x %02x %02x\n", *(ccc+0), *(ccc+1), *(ccc+2), *(ccc+3) );
printf( "ccc |%s|\n", ccc );
}
		ccc[CAPINFO_SZ*2+1-1]	= LF;
		fwrite( ccc, 1, (CAPINFO_SZ*2+1), fpo );

/*......................................................................*/
/*	Verifica che la AZencode ha lavorato correttamente		*/
		ccc[CAPINFO_SZ*2+1-1]	= 0;
		AZdecode( ccc, &ppp );
if ( Debug ) {
printf( "ppp? %02x %02x %02x %02x\n", *(ppp+0), *(ppp+1), *(ppp+2), *(ppp+3) );
printf( "ppp?|%s|\n", ppp );
}
/*......................................................................*/

		  }

		  return ;

		}

		AZdecode( lll, &ppp );
             
		decode( ppp, CAPINFO_SZ );
                
if ( Debug ) {
printf( "ppp2 %02x %02x %02x %02x\n", *(ppp+0), *(ppp+1), *(ppp+2), *(ppp+3) );
printf( "ppp!|%s|\n", ppp );
}

/*......................................................................*/
/*	Verifica che applicando la decode si ha quanto prima della encode */

		memcpy( vvv, ppp, CAPINFO_SZ );
		vvv[CAPINFO_SZ]	= 0;
		if( c_sw )
		{
			decode( vvv, CAPINFO_SZ );
if ( Debug ) {
printf( "vvv |%s|\n", vvv );
}
		}
/*......................................................................*/
		AZencode( ppp, &ccc );
if ( Debug ) {
printf( "ccc  %02x %02x %02x %02x\n", *(ccc+0), *(ccc+1), *(ccc+2), *(ccc+3) );
printf( "ccc |%s|\n", ccc );
}
		if( c_sw ) {
		   ccc[CAPINFO_SZ*2+1-1]	= LF;
		   fwrite( ccc, 1, (CAPINFO_SZ*2+1), fpo );
                }
/*......................................................................*/
/*	Verifica che la AZencode ha lavorato correttamente		*/
		ccc[CAPINFO_SZ*2+1-1]	= 0;
		AZdecode( ccc, &ppp );
if ( Debug ) {
printf( "ppp? %02x %02x %02x %02x\n", *(ppp+0), *(ppp+1), *(ppp+2), *(ppp+3) );
printf( "ppp?|%s|\n", ppp );
}
/*......................................................................*/
	}

}					/* do_cap()			*/


/*======================================================================*/
void main( argc, argv )
int	argc;
char**	argv;
{
char	optstr[] = "cdhiVf:";
int	c;
int	j;

/*----------------------------------------------------------------------*/
/*	Inizializzazioni						*/

	InitEnv ( ) ;

	if ( Debug ) {
	  printf( "CAPINFO_SZ: %d CAPSTRC_SZ: %d\n", CAPINFO_SZ, CAPSTRC_SZ );
        }
/*----------------------------------------------------------------------*/
/*	Acquisizione delle opzioni					*/

	j		= 0;
	while( (c = getopt( argc, argv, optstr )) != EOF )
	{
		j++;
		switch( c )
		{
		case 'c':
			c_sw	= 1;
			/*
			strcpy( fni, CAPINFO_FN );
			strcpy( fno, CAPCONF_FN );
			*/
			fni = CAPINFO_FN ;
			fno = CAPCONF_FN ;
			break;

		case 'd':
			d_sw	= 1;
			/*
			strcpy( fni, CAPCONF_FN );
			strcpy( fno, CAPINFO_FN );
			
			fni = CAPCONF_FN ;
			fno = CAPINFO_FN ;
                        */
                        fni = CAPINFO_FN ;
			break;

		case 'h':
			printf( "%s\n", hlp_txt );
			exit( 0 );

                case 'i':
                        i_sw = 1;
                        fni = CAPINFO_FN ;
                        printf("Recupero informazioni dal file CAP.info\n");
                        break;

		case 'V':
			PrintVersion ( ) ;
			exit( 8 );

		case '?':
			fprintf( stderr, "Errore nell' argomento: %s - exiting ....\n",
						argv[optind-1] );
			fprintf( stderr, "%s\n", hlp_txt );
			exit( 9 );	/* Opzione errata		*/
			break;
		case 'f' : 
		  IniFileName = optarg ;
		  break ;
		}
	}

	if( ((! d_sw && ! c_sw) && ( ! i_sw )) ||
	    (  d_sw &&  c_sw) ||
            (  c_sw &&  i_sw) ||
            (  d_sw &&  i_sw) ||
            (( c_sw &&  d_sw) && ( i_sw)) ||
	    ( c_sw && ( IniFileName == NULL ) ) )
	{
		printf( "%s\n", hlp_txt );
		printf( "Specificare o l' opzione -c o l' opzione -d\n"
			"e indicare il nome del file di inizializzazione.\n" );
		exit( 1 );
	}

/*----------------------------------------------------------------------*/
/*	Lavora								*/

	fpi	= fopen( fni, "r" );
	if( fpi == NULL )
	{
		fprintf( stderr, "Errore fopen() %s - errno : %d.\n",
					fni, errno );
		exit( 1 );	/* =1 : NOK		*/
	}
        if( c_sw ) { 
	   fpo	= fopen( fno, "w" );
	   if( fpo == NULL )
	   {
	   	   fprintf( stderr, "Errore fopen() %s - errno : %d.\n",
					fno, errno );
		   exit( 1 );	/* =1 : NOK		*/
	   }
	   if ( IniFileName != NULL ) {
	     IniFilefp = fopen ( IniFileName , "r" ) ;
	     if ( IniFilefp == NULL ) {
	       fprintf ( stderr , 
	   	         "Errore fopen() %s - errno : %d.\n" ,
		         IniFileName , errno ) ;
	       exit ( 1 ) ;
	     }
           }
        }

/*----------------------------------------------------------------------*/
/*+++	bld();		*/

	do_cap();
	fclose( fpi );
        if( c_sw ) { 
	   fclose( fpo );
	   fclose ( IniFilefp ) ;
        }

printf("\nExecution OK\n");

	exit( 0 );

}					/* main()			*/

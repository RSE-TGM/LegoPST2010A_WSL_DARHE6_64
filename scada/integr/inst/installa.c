/*
   modulo installa.c
   tipo 
   release 1.20
   data 10/14/96
   reserved @(#)installa.c	1.20
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)installa.c	1.20\t10/14/96";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>

#include <db.h>
#include <installa.h>
#include <sqlite3.h>

extern char *path_input;
extern char *path_output;
char *path_rtf;
char *path_variabili;

extern int usa_informix;
extern int start_informix;

sqlite3 *db;


main(argc,argv)
int argc;
char ** argv;
{
int i;
RECORD record;
char nome[15];
char nome_s[15];
char comando [255];

usa_informix=1;
start_informix=0;
if(argc<5)
        {
        fprintf(stderr,
     	"Usage: %s <path input> <path output> <path_rtf> <path_variabili> [-noinformix -startinformix]\n",
	argv[0]);
        exit(1);
        }
// Assegna i path
path_input = argv[1];
path_output = argv[2];
path_rtf = argv[3];
path_variabili = argv[4];

printf("installa %s -> %s -> %s (%s)\n",path_input,path_output,path_rtf,
	path_variabili);

gest_argv(argc,argv);

// inizializza il file degli errori
installa_err(NULL,CREATE_FILE_ERR);
if(scarica_informix()!=1)
	{
        fprintf(stderr,"Errore accesso INFORMIX\n");
        exit(1);
        }

if(CreateAllarAs()!=1)
        {
        fprintf(stderr,"Errore CreateAllarAs\n");
        exit(1);
        }
/*
	costruisce l'header della tabella editnomi
*/
crea_nomi();

if(installa_variabili()!=1)
        {
        fprintf(stderr,"Errore installa_variabili\n");
        exit(1);
        }
if(installa_ad()!=1)
        {
        fprintf(stderr,"Errore installa_ad\n");
        exit(1);
        }
if(installa_dd()!=1)
        {
        fprintf(stderr,"Errore installa_dd\n");
        exit(1);
        }

if(installa_ConfDB()!=1)
        {
        fprintf(stderr,"Errore installa_AllarDB\n");
        exit(1);
        }


if(installa_AllarDB()!=1)
        {
        fprintf(stderr,"Errore installa_AllarDB\n");
        exit(1);
        }

if(installa_AllarLin()!=1)
        {
        fprintf(stderr,"Errore installa_AllarLin\n");
        exit(1);
        }

if(installa_AllarLiv()!=1)
        {
        fprintf(stderr,"Errore installa_AllarLiv\n");
        exit(1);
        }

if(installa_AllarStr()!=1)
        {
        fprintf(stderr,"Errore installa_AllarStr\n");
        exit(1);
        }

if(installa_AllarSer()!=1)
        {
        fprintf(stderr,"Errore installa_AllarStr\n");
        exit(1);
        }

if(installa_TabPeri()!=1)
        {
        fprintf(stderr,"Errore installa_TabPeri\n");
        exit(1);
        }
if(installa_CPerif()!=1)
        {
        fprintf(stderr,"Errore installa_CPerif\n");
        exit(1);
        }
if(installa_DescriSc()!=1)
        {
        fprintf(stderr,"Errore installa_DescriSc\n");
        exit(1);
        }
if(installa_MisTabK()!=1)
        {
        fprintf(stderr,"Errore installa_MisTabK\n");
        exit(1);
        }
if(installa_TDIZST()!=1)
        {
        fprintf(stderr,"Errore installa_TDIZST\n");
        exit(1);
        }

if(installa_arc()!=1)
        {
        fprintf(stderr,"Errore installa_arc\n");
        exit(1);
        }

if(installa_log()!=1)
        {
        fprintf(stderr,"Errore installa_log\n");
        exit(1);
        }

if(crea_or()!=1)
        {
        fprintf(stderr,"Errore crea_or\n");
        exit(1);
        }

if(crea_st()!=1)
        {
        fprintf(stderr,"Errore crea_st\n");
        exit(1);
        }

if(crea_to()!=1)
        {
        fprintf(stderr,"Errore crea_to\n");
        exit(1);
        }

// Ordina la tabella PointInstErr.txt
sprintf(comando,"SortTable %s/PointInstErr.txt",path_output);
printf("%s\n",comando);
system(comando);


if(carica_informix()!=1)
	{
        fprintf(stderr,"Errore accesso INFORMIX\n");
        exit(1);
        }

exit(0);
}


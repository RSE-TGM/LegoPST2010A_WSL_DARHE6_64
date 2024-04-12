/*
   modulo %M%
   tipo %Y%
   release %I%
   data %G%
   reserved %W%
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>

EXEC SQL define NAME_LEN        18;
EXEC SQL define MAX_FIELD        30;

#define DUMP 	0
#define LOAD 	1

main(int argc, char **argv)
{
EXEC SQL BEGIN DECLARE SECTION;
    int i;
    int desc_count;
    char dynamic_query[80];
    char colname[19];
    char *result_char;
    char result_int;
    char result_float;
    int max_field=MAX_FIELD;
    char tabella[50];
    char tabella_txt[50];
    FILE *fp;
    int modo = -1;
EXEC SQL END DECLARE SECTION;

    if(argc<3)
	{
	fprintf(stderr,"Usa: GestAscii [nome tabella] [DUMP/LOAD]\n");
	exit(0);
	}

    strcpy(tabella,argv[1]);
    if(strcmp(argv[2],"DUMP")==0)
	modo=DUMP;
    if(strcmp(argv[2],"LOAD")==0)
	modo=LOAD;
    if(modo == -1)
	{
	fprintf(stderr,"Usa: GestAscii [nome tabella] [DUMP/LOAD]\n");
	exit(0);
	}


    // Connessione al database
    if(!DbConnect("online","Online"))
	{
	fprintf(stderr,"Errore connessione database\n");
	exit(1);
	}

if(!SQLIsTable(tabella))
	{
	printf("Errore: la tabella %s non esiste\n",tabella);
    	// Sconnessione al database
    	DbDisconnect();
	exit(0);
	}

EXEC SQL BEGIN WORK;

    
    /*
	crea il file ASCII
    */
    if(modo == DUMP)
    	SQLTableToAscii(tabella,tabella,NULL);

    /*
	Copia il file ASCII nel database
    */
    if(modo == LOAD)
    	SQLAsciiToTable(tabella,tabella);

EXEC SQL COMMIT WORK;

    // Sconnessione al database
    DbDisconnect();
// Terminazione corretta
exit(0); 
}



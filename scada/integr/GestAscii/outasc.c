#include <sqlhdr.h>
#include <sqlca.h>
extern _SQCURSOR *_iqnprep();

#if !defined(__STDC__)
#define const 
#endif

#line 1 "outasc.ec"
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

/* 
 * EXEC SQL define NAME_LEN        18;
 */
#line 18 "outasc.ec"
/* 
 * EXEC SQL define MAX_FIELD        30;
 */
#line 19 "outasc.ec"

#define DUMP 	0
#define LOAD 	1

main(int argc, char **argv)
{
/*
 * EXEC SQL BEGIN DECLARE SECTION;
 */
#line 26 "outasc.ec"

#line 27 "outasc.ec"
int i;
int desc_count;
char dynamic_query[80];
char colname[19];
char *result_char;
char result_int;
char result_float;
int max_field = 30;
char tabella[50];
char tabella_txt[50];
char *fp;
int modo =  -1;
/*
 * EXEC SQL END DECLARE SECTION;
 */
#line 39 "outasc.ec"


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

/*
 * EXEC SQL BEGIN WORK;
 */
#line 74 "outasc.ec"
  {
#line 74 "outasc.ec"
  _iqbeginwork();
#line 74 "outasc.ec"
  }


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

/*
 * EXEC SQL COMMIT WORK;
 */
#line 89 "outasc.ec"
  {
#line 89 "outasc.ec"
  _iqcommit();
#line 89 "outasc.ec"
  }

    // Sconnessione al database
    DbDisconnect();
// Terminazione corretta
exit(0);
}



#line 97 "outasc.ec"

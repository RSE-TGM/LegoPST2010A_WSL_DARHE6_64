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
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "loadump.h"
#include "SQLError.h"

EXEC SQL include sqltypes;
EXEC SQL include locator;

long exp_chk2();

main(argc, argv)
int argc;
char *argv[];
{
char file_name[FILENAME_MAX+1];
int operation;
int fd;
long ret;

EXEC SQL BEGIN DECLARE SECTION;
	char db_msg[BUFFSZ+1];
	char value[DB_COLUMN_SIZE+1];
	char blob_column[DB_COLUMN_SIZE+1];
	char table_name[DB_TABLE_NAME+1];
	char keyword[DB_COLUMN_NAME+1]; 
        loc_t blob;
EXEC SQL END DECLARE SECTION;

/* Check parameters number */
if(argc<FIX_PAR_NUM+1)
{
	fprintf(stderr,"Usage: %s table column [clause] operation(LOAD,DUMP)\n",argv[0]);
	exit(1);
}

fprintf(stderr,"LOADUMP Program running.\n");

if(!DbConnect("online","Online"))
{
	fprintf(stderr,"LOADUMP Program over.\n");
        exit(1);
}

if((operation=ParseCommandLine(db_msg,argc,argv))==-1)
{
	fprintf(stderr,"Unable to parse command line\n");
	DbDisconnect();
	fprintf(stderr,"LOADUMP Program over.\n");
        exit(1);
}

/* build file name */
strcpy(file_name,"blobdump.txt");

/* LOAD operation */
if(operation==LOAD)
{
	/* Perform ASCII conversion */
	AsciiUnixToDos(file_name);

	if((fd = open(file_name,O_RDONLY))<0)
	{
		perror(file_name);
        	DbDisconnect();
		exit(1);
	}

	blob.loc_oflags = LOC_RONLY;	/* set loc_oflags to read */
	blob.loc_size=GetFileLength(file_name);
	printf("[%s] %d\n",file_name,blob.loc_size);
	blob.loc_loctype = LOCFILE;	/* set loctype for open file */
	blob.loc_fd = fd;		/* load the file descriptor */
}
/* DUMP operation */
else if(operation==DUMP)
{
	if((fd = creat(file_name,0666))<0)
	{
		perror(file_name);
        	DbDisconnect();
		exit(1);
	}

	blob.loc_oflags = LOC_APPEND;	/* set loc_oflags to append */
	blob.loc_loctype = LOCFILE;	/* set loctype for open file */
	blob.loc_fd = fd;		/* load the file descriptor */
}
else
{
	fprintf(stderr,"Operation invalid [%s]\n",operation);
	DbDisconnect();
	fprintf(stderr,"LOADUMP fopen Program over.\n");
	exit(1);
}

/* prepare SQL statement */
EXEC SQL prepare dyn_sql from :db_msg;
if(SQLError("prepare"))
{
	printf("DYNAMIC SQL: [%s]\n",db_msg);
	DbDisconnect();
	exit(1);
}

/* execute SQL statement */
if(operation==LOAD)
	EXEC SQL execute dyn_sql using :blob;
else
	EXEC SQL execute dyn_sql into :blob;
if(SQLError("execute"))
{
	printf("DYNAMIC SQL: [%s]\n",db_msg);
	DbDisconnect();
	exit(1);
}
EXEC SQL free dyn_sql;

/* if not found */
if((ret = exp_chk2("SELECT", WARNNOTIFY)) == 100)
	fprintf(stderr,"[%s] entry not found in [%s] table\n",
		keyword,table_name);
else
{
        if(ret < 0)
	{
		fprintf(stderr,"Select for [%s] failed\n",keyword);
            	close(fd);
            	DbDisconnect();
            	fprintf(stderr,"LOADUMP Program over.\n");
            	exit(1);
	}
}

/* 
 *  Deallocate file resources and terminate database connection
 */
close(fd);

/* Perform ASCII conversion */
if(operation=DUMP)
	to_ascii(file_name);

DbDisconnect();
fprintf(stderr,"LOADUMP Program over.\n");
exit(0);
}

int GetFileLength(char *path)
{
	struct stat file_info;

        if(stat(path,&file_info))
		perror(path);
        return file_info.st_size;
}

int ParseCommandLine(char *db_msg,int argc,char **argv)
{
int i;
int operazione;
char table_name[DB_TABLE_NAME];
char blob_column[DB_COLUMN_NAME];
char commandline[BUFFSZ],*pc;

commandline[0]='\0';
for(i=FIX_PAR_NUM;i<argc;i++)
{
	if(strlen(commandline)+strlen(argv[i])<BUFFSZ)
	{
		strcat(commandline," ");
		strcat(commandline,argv[i]);
	}
	else
	{
		fprintf(stderr,"Command line exceeds dimension %d\n",
			BUFFSZ);
		return -1;
	}
}

/* Table name must be present */
if(!GetTableName(table_name,argc,argv))
{
	fprintf(stderr,"Table name missing\n");
	return -1;
}

/* Blob column must be present */
if(!GetBlobColumn(blob_column,argv))
{
	fprintf(stderr,"Blob column missing\n");
	return -1;
}

if(pc=strstr(commandline,"DUMP"))
{
	operazione=DUMP;
	sprintf(db_msg,"select %s from %s",blob_column,table_name);
}
else if(pc=strstr(commandline,"LOAD"))
{
	operazione=LOAD;
	sprintf(db_msg,"update %s set %s=?",table_name,blob_column);
}
else
{
	fprintf(stderr,"Operation missing\n");
	return -1;
}

/* Trim off "DUMP" or "LOAD" */
*(pc-1)='\0';
if(strlen(db_msg)+strlen(commandline)<BUFFSZ)
	strcat(db_msg,commandline);
else
{
	fprintf(stderr,"Command line exceeds dimension %d\n",
		BUFFSZ);
	return -1;
}

if(!strchr(db_msg,';') && strlen(db_msg)<BUFFSZ-1)
	strcat(db_msg,";");

/*return operazione;*/
return operazione;
}

int GetTableName(char *table_name,int argc,char **argv)
{
*table_name='\0';
if(argc>1)
	strcpy(table_name,argv[1]);
return *table_name;
}

int GetBlobColumn(char *blob_column,char **argv)
{
*blob_column='\0';
strcpy(blob_column,argv[2]);
return *blob_column;
}


/**********************************************************************
*
*       C Source:               tempo_file.c
*       Subsystem:              2
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Thu Jan 14 11:00:19 1999 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: tempo_file.c-2 %  (%full_filespec: tempo_file.c-2:csrc:2 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)tempo_file.c	5.1\t11/10/95";
/*
   modulo tempo_file.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)tempo_file.c	5.1
*/
/* confronta tempo di scrittura file 
   restituisc 1 quando il file_1 e' piu' recente del file_2   */

# include <stdio.h>
# include <errno.h>
# include <sys/time.h>
# include <utime.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/stat.h>
#endif
#ifdef VMS
# include <stat.h>
#endif


int tempo_file(file_1,file_2)
char *file_1;
char *file_2;
{
struct stat buf_1;
struct stat buf_2;

/*
Inserisco controlli
*/
if(stat(file_1,&buf_1)<0)
   {
   fprintf(stderr,"WARNING:tempo_file.c:buf_1 Impossible to retrieve  file stat\n");
   return 1;
   }
if(stat(file_1,&buf_2)<0)
   {
   fprintf(stderr,"WARNING:tempo_file.c:buf_2 Impossible to retrieve  file stat\n");
   return 1;
   }
if(buf_1.st_mtime>buf_2.st_mtime)
	return(1);
else
	return(0);

}



/*
    Analoga alla routine precedente sostituisce
    il test sulla data del file (in secondi) con
    un test maggiore o uguale.
    Ritorna 1 se file1 e' piu' recente o contemporaneo
    di file2.
*/
int tempo_file_eq(file_1,file_2)
char *file_1;
char *file_2;
{
struct stat buf_1;
struct stat buf_2;

stat(file_1,&buf_1);
stat(file_2,&buf_2);

/*printf("t1=%d  t2=%d\n\n",buf_1.st_mtime,buf_2.st_mtime);*/
if(buf_1.st_mtime>=buf_2.st_mtime)
	return(1);
else
	return(0);
}


/*
   Modifica la data (ultimo accesso-modificazione) di un file.
   Ritorna 0 se corretto.
*/
int tempo_file_touch(file)
char *file;
{
int ret=-1;

    ret=utime(file,NULL);
    if( ret!=0 )
      fprintf(stderr,"Fallita modifica data per %s\n",file); 
    return(ret);
}

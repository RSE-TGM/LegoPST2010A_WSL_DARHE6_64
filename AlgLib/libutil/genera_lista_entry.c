/**********************************************************************
*
*       C Source:               genera_lista_entry.c
*       Subsystem:              2
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Oct 21 11:39:01 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: genera_lista_entry.c-2 %  (%full_filespec: genera_lista_entry.c-2:csrc:2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)genera_lista_entry.c	5.1\t11/10/95";
/*
   modulo genera_lista_entry.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)genera_lista_entry.c	5.1
*/
/*
  genera_lista_entry( path, filter, nitems, items )
  Genera la lista dei files (directory) contenuti in path e filtrati dalla 
  funzione filter definita dall'utente secondo la sintassi:

		int dir_filter ( path )
		char *path;   

 Il valore di ritorno e' TRUE se la entry e' da inserire nella lista items.
 items e' un array allocato dinamicamente costituito da nitems elementi.
 L'array items viene allocato internamente alla funzione e deve essere 
 esplicitamente deallocato tramite la chiamata alla funzione 
 libera_lista_entry.

 Esempio di utilizzo:
 {
 char *items,path[1024];
 int nitems,i;  
 int filter(char *);
 genera_lista_entry( path, filter,&nitems, &items );
 for(i=0;i<nitems;i++)
	{
	printf("\n elemento lista = %s",items[i]);
	}
 libera_lista_entry(items);
 }

*/
#ifdef VMS
#include <stdio.h>
genera_lista_entry( path, filter, nitems, items )
char *path;
int  (*filter)( char* );
int  *nitems;
char ***items;
{
printf("\n FUNZIONE genera_lista_entry NON ANCORA IMPLEMENTATA IN VMS");
exit(1);
}
#else

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <Xm/Xm.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>



void genera_lista_entry( path, filter, nitems, items )
char *path;
int  (*filter)( char* );
int  *nitems;
char ***items;
{
   int short i, j, k, nu_entry;
   DIR *dirp;
   struct dirent *dp;
   char **tmp_items;
   char local_path[200];
   char *name;


   strcpy ( local_path, path );
#ifndef VMS
   strcat ( local_path, "/" );
#endif
   name = local_path + strlen( local_path );

/* Conta le entry della directory */

   dirp = opendir ( path );
   for ( nu_entry = 0; readdir(dirp); nu_entry++)
    ;
   closedir(dirp);


/* Alloca i puntatori per tutte le entry. */
   tmp_items = (char **) malloc ( nu_entry * sizeof(char*) );


/* Legge i nomi delle entry e le inserisce in tabella filtrate */

   dirp = opendir ( path );

   for (*nitems=0, dp = readdir(dirp); dp != NULL; dp = readdir(dirp))
   {
     strcpy ( name, dp->d_name );
     if ( (*filter)( local_path ) )
       {
#if defined SCO_UNIX || defined LINUX
         tmp_items[*nitems] =
                         (char*) malloc ( (MAXNAMLEN+1) * sizeof( char ) );
#else
         tmp_items[*nitems] =
                         (char*) malloc ( (dp->d_namlen+1) * sizeof( char ) );
#endif
         strcpy (  tmp_items[*nitems], dp->d_name );
         (*nitems)++;
       }
   }

   closedir(dirp);


/* Creazione della tabella vuota */
   *items = (char **) malloc ( *nitems * sizeof(char *) );
   for (i=0; i< *nitems; i++ )
      (*items)[i] = NULL;


/* Ordina gli items inserendoli nella tabella di uscita */
   for ( i=0; i < *nitems; i++ )
   {
     for ( k=0, j=0; j < *nitems; j++ )
        if ( i!=j && strcmp ( tmp_items[i], tmp_items[j] ) > 0 )
           k++; 
     (*items)[k] = (char *)malloc((strlen(tmp_items[i])+1)*sizeof(char));
     strcpy((*items)[k],tmp_items[i]);
   }
/* Libera la tabella di appoggio */
   for ( i=0; i<*nitems; i++ )
     free( tmp_items[i] );
   free ( tmp_items );
}



void libera_lista_entry(items,nitems)
char **items;
int nitems;
{
int i;
for(i=0;i<nitems;i++)
	free(items[i]);
free(items);
}



int no_filter ( path )
char *path;
{
  return (1);
}




int dir_filter ( path )
char *path;
{
  struct stat st;

  stat ( path, &st );

  if ( S_ISDIR( st.st_mode ) )
    return (1);

  return (0);
}





int file_no_exe_filter( path )
char *path;
{
  struct stat st;

  stat ( path, &st );

  if ( S_ISREG( st.st_mode ) && ! ( st.st_mode & S_IXUSR ) &&
       ! (  st.st_mode & S_IXGRP ) && ! (  st.st_mode & S_IXOTH ) )
    return (1);

  return (0);
}



/*
 model_filter
   filtra dai nomi dei sotto direttori di legocad libut... e lib_graf
*/

int model_filter ( path )
char *path;
{
  struct stat st;
  char *name;
  char lib[6];
  char lib2[9];

#ifdef VMS
  strcpy ( lib, "LIBUT" );
  strcpy ( lib2, "LIB_GRAF" );
#else
  strcpy ( lib, "libut" );
  strcpy ( lib2, "lib_graf" );
#endif

  stat ( path, &st );
#ifdef VMS
  name = strrchr( path, ']' ) + 1;
#else
  name = strrchr( path, '/' ) + 1;
#endif
 
  if ( S_ISDIR( st.st_mode )  &&  *name != '.'  &&  strncmp( name, lib, 5 ) 
	&& strncmp( name, lib2, 8))
    return (1);

  return (0);
}

#endif


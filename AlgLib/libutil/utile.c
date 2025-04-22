/**********************************************************************
*
*       C Source:               utile.c
*       Subsystem:              2
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Nov 29 12:13:23 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: utile.c-3 %  (%full_filespec: utile.c-3:csrc:2 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)utile.c	5.1\t11/10/95";
/*
   modulo utile.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)utile.c	5.1
*/
/* utile.c */

/* Buffo Massimo, Calleri Nicola 11/06/1992 */

/* routine di utilita' generale */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <X11/Intrinsic.h>
#if defined UNIX
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/file.h>
#elif defined VMS
#include <unixio.h>
#include <file.h>
#include <processes.h>
#define R_OK 4
#endif
#include "utile.h"

int path_rel_to_abs(char *,char *);

/*-----------------------------------------------------------------------*/
/* funzione IsNumeric(str)
  str : stringa di caratteri (r)
 ritorna 1 se la stringa contiene solo caratteri numerici tipo 1..9,.
 altrimenti 0 */
int IsNumeric(str)
char *str;
{
  for ( ; *str ; str++ )
     switch ( *str )  {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case 'e':
      case 'E':
      case ' ':
      case '.':
      case '-':
      case '+': break;
     default: return(0); }
  return(1);
}

/*-----------------------------------------------------------------------*/
/* funzione Empty(stringa)
 stringa : stringa di caratteri da controllare (r)
 controlla se una stringa e' vuota (cioe' contiene solo blank o tab)
 la stringa viene controllata fino al terminatore '\0' oppure fino al
 carattere di newline '\n' */
int Empty(stringa)
char *stringa;
{
   for(; *stringa && *stringa != '\n';stringa++)
     if( *stringa != ' ' && *stringa != '\t' )
        return(0);
   return(1);
}

/*-----------------------------------------------------------------------*/
/* funzione copy_n_car(str1,str2,n)
  str1 : stringa destinazione        (w)
  str2 : stringa sorgente            (r)
  n    : numero caratteri da copiare (r)
  copia n caratteri della stringa str2 in str1 terminando str1 con il
  terminatore ( '\0' ). Il newline e' considerato fine-stringa. */
void copy_n_car(str1,str2,n)
char *str1,*str2;
int n;
{
   while( n-- && *str2 != '\n' && (*(str1++) = *(str2++)));
   *str1='\0';
}

/*-----------------------------------------------------------------------*/
/* funzione app_n_car(str1,str2,n)
  str1 : stringa destinazione        (w)
  str2 : stringa sorgente            (r)
  n    : numero caratteri da copiare (r)
  appende n caratteri della stringa str2 alla fine di str1 terminando str1
  con il terminatore */
void app_n_car(str1,str2,n)
char *str1,*str2;
int n;
{
   while( *(str1++) );
   str1--;
   while( n-- && (*(str1++) = *(str2++)));
   *str1='\0';
}


/*-----------------------------------------------------------------------*/
/*** trim_zero(stringa)
 *** parametri:
 ***            stringa: stringa di caratteri numerici
la funzione rimuovi gli zeri finali di una stringa numerica decimale */
void trim_zero(stringa)
char *stringa;
{
   int i, point = 0;
   char *tmp;

   for(i = 0; *stringa ; stringa++, i++ )
     if ( *stringa == '.' )
        point = i; 

   if ( !point )
      return;

   while ( --i && *(--stringa) == '0' );
   *(++stringa) = '\0';
}

/*-----------------------------------------------------------------------*/
/*** cerca_elemento( ar,num,el)
 *** parametri:
 ***    ar : array ordinato di interi
 ***   num : numero di elementi in ar 
 ***    el : numero da cercare in ar
Funzione che esegue la ricerca dicotomica in un array ( l'array deve essere
 ordinato!). La funzione ritorna il numero della posizione nell'array se 
l'elemento e' stato trovato, altrimenti ritorna -1 */
int cerca_elemento( ar,num, el)
int ar[], num, el;
{
   int i, imin, imax;

   imin = 0;
   imax = num-1;

   for( i = imax/2; ar[i] != el && (imax-imin) ; i = imin+(imax-imin)/2 )
   {
      if ( ar[ i ] < el )  
         if (( imax - imin ) > 1 )
            imin = i;
         else
            {
               i = imax;
               break;
            }
      else
         imax = i;
   }

/* Se l'elemento e' stato trovato ed eventualmente e' duplicato */
/* allora mi posiziono sul primo della serie */
   if ( ar[i] == el )
   {
      while( i > 0 && ar[--i] == el );
      if ( ar[i] != el)
         return(i+1);
      else
         return(i);
   }
   else
      return(-1); /* elemento non trovato! */
}

/*-----------------------------------------------------------------------*/
/* funzione app_n_blank(str,lunghezza)
   str       : stringa da riempire
   lunghezza : lunghezza finale della stringa
 ritorna 0 se sono stati "appesi" dei caratteri blank alla fine della 
 stringa altrimenti ritorna 1.
 appende una serie di blank alla fine di una stringa finquando la 
 stringa str non raggiunge la lunghezza 'lunghezza' */
int app_n_blank(str,lunghezza)
char *str;
short lunghezza;
{
  int prec_lung;

  prec_lung = strlen(str);
  if (lunghezza <= prec_lung)
    return(1);
  while( *(str++) );
  riempi(--str,lunghezza-prec_lung);
  return(0);
}

/*-----------------------------------------------------------------------*/
/* funzione riempi(str,nBlank)
 str    : stringa di caratteri da riempire con caratteri blank ' ' (w)
 nBlank : numero di spazi vuoti                                    (r)

funzione che riempe una stringa di blank e la termina con '\0' */
void riempi(str,nBlank)
char *str;
int nBlank;
{
   for(;nBlank--;*(str++)=' ');
   *str='\0';
}

/*-----------------------------------------------------------------------*/
/*** copy_file( file_sorg, file_dest )
/*** parametri:
 ***     file_sorg : file sorgente.
 ***     file_dest : file destinazione.
copia il file sorgente nel file destinazione.Ritorna 0 se tutto e' OK,
altrimenti ritorna -1 (se c'e' stato qualche errore.. ). */
int copy_file(file_sorg, file_dest)
char *file_sorg, *file_dest;
{
   FILE *fp_sorg, *fp_dest;
   int  car;

   if ( access(file_sorg,R_OK) )
      return(-1);

   fp_sorg = fopen(file_sorg,"r");
   fp_dest = fopen(file_dest,"w");
   if ( fp_sorg == NULL || fp_dest == NULL )
      return(-1);

   while( (car = fgetc(fp_sorg)) != EOF ) fputc(car,fp_dest);
   fclose(fp_sorg);
   fclose(fp_dest);
   return(0);
}

/*-----------------------------------------------------------------------*/
/*** char *nzero(str,val, formato, strzero)
 *** parametri:
 ***     str : stringa di destinazione
 ***     val : valore da convertire in stringa
 *** formato : formato di stampa del valore
permette di stampare su di una stringa un valore numerico nel formato stabilito
se diverso da zero, altrimenti stampa la stringa zero */
char *nzero(str,val,formato,zero)
char   *str;
double val;
char   *formato,*zero;
{
   sprintf(str,formato,val);
   if ( val == 0.0 )
   {
      int len;

      len = strlen(str);
      strcpy(str,zero);
      app_n_blank(str,len);
   }
   return(str);
}

/*-----------------------------------------------------------------------*/
int print_file (filename)
char * filename;
{
   char *command;  /*  'command' = "lp " + filename + null terminator  */
   short errore = 0;

   command = (char *) XtMalloc(strlen(filename) + 4);
   sprintf(command, "lp %s", filename);
   if (system(command) != 0)
   {
      fprintf(stderr, "Print failed.");
      errore = -1;
   }
   XtFree (command);
   return( errore );   
}
/*-----------------------------------------------------------------------*/
/*** ordinale( num, suffisso)
     Trasforma un numero da cardinale (es:13) in ordinale (es:13th)
     secondo la sintassi anglosassone
 *** PARAMETRI:
 *** int num	  
 *** char *suffisso
 ***/
char *ordinale ( num,suffisso )
int num;
char *suffisso;
{
   if (num == 1)
       sprintf (suffisso,"%dst",num); 
   else if (num == 2)
       sprintf (suffisso,"%dnd",num); 
   else if (num == 3)
       sprintf (suffisso,"%drd",num); 
   else
       sprintf (suffisso,"%dth",num); 
   return (suffisso);
}

/*-----------------------------------------------------------------------*/
/*** char *trim_blank (str)
 ***  PARAMETRI
 *** char *str: stringa da epurare
 *** Toglie i blank eventualmente presenti alla fine di una stringa.
 ***/
char *trim_blank(str)
char *str;
{
   int n;

   n = strlen(str)-1;
   while ((str[n] == ' ' || str[n] == '\n' || str[n] == '\t') && n-- );
   str[n+1] = '\0';
   return(str);
}

/*-----------------------------------------------------------------------*/
/* funzione copia_file(file1, file2)
 file1: file sorgente
 file2: file destinazione
copia il file1 in file2 */
int copia_file(file1, file2)
char *file1, *file2;
{
#define BUFFER_SIZE	512

   int fd1, fd2, i;
   char buffer[BUFFER_SIZE];

   if ((fd1 = open (file1, O_RDONLY, 0004)) == -1)
      return(-1);
   if ((fd2 = creat(file2, 0666)) == -1)
      return(-1);

   while( (i = read(fd1, buffer, BUFFER_SIZE)) > 0)
      write(fd2, buffer, i);

   close(fd1);
   close(fd2);
   if ( i == -1 )
      return(-1);
   else
      return(0);
}

/*-----------------------------------------------------------------------*/
/* tominus(stringa)
 *** Parametri:
 *** char *stringa: stringa di caratteri
converte una stringa in caratteri minuscoli */
void tominus(stringa)
char *stringa;
{
   for( ; *stringa ; stringa++ )
      *stringa = tolower(*stringa);
}

/*-----------------------------------------------------------------------*/
/* tomaius(stringa)
 *** Parametri:
 *** char *stringa: stringa di caratteri
converte una stringa in caratteri maiuscoli */
void tomaius(stringa)
char *stringa;
{
   for( ; *stringa ; stringa++ )
      *stringa = toupper(*stringa);
}
  
/*-----------------------------------------------------------------------*/
/* funzione contiene_blanks(stringa)
 stringa : stringa di caratteri da controllare (r) */
int contiene_blanks(stringa)
char *stringa;
{
   for(; *stringa ;stringa++)
     if( *stringa == ' ' )
        return(1);
   return(0);
}

/*-----------------------------------------------------------------------*/
/*** shift_file_bytes(fp, num_bytes)
 ***   Parametri :
 ***     FILE *fp;
 ***     int num_bytes;
Crea una area vuota di num_bytes nel file puntato da FP nella posizione
corrente (il resto viene shiftato). ***/
int shift_file_bytes(fp, num_bytes)
FILE *fp;
int num_bytes;
{
   char buffer[512];
   int n, m;
   long pos1, pos2;

   pos1=ftell(fp)+num_bytes;
   pos2=ftell(fp);

   while(1)
   {
      lseek(fileno(fp),pos2,0);
      n=read(fileno(fp),buffer,512);
      pos2=lseek(fileno(fp),0,1);
      if ( !n || n == -1)
          break;

      lseek(fileno(fp),pos1,0);
      m=write( fileno(fp),buffer,n);
      pos1=lseek(fileno(fp),0,1);
      if ( !m || m == -1)
         return(-1);

      if ( n < 512 )
         break;
   }
   return(0);
}

/*** char *sottodir_vms(nuova_dir, direttorio, sottodir)
 ***  Parametri :
 ***     char *nuova_dir : nuovo direttorio
 ***     char *direttorio: direttorio iniziale
 ***     char *sottodir  : sottodirettorio da aggiungere a direttorio
Funzione utilizzata per la costruzione dei percorsi in VMS.
Il direttorio nel formato VMS "[dir1.dir2.dir3]" viene aggiornato con il
sottodirettorio "dir4.dir5" ed il nuovo direttorio (nuova_dir) sara' :
"[dir1.dir2.dir3.dir4.dir5]" ***/
char *sottodir_vms(nuova_dir, direttorio, sottodir)
char *nuova_dir, *direttorio, *sottodir;
{
   int i;

   i = strlen(direttorio);

   while ( i && direttorio[i] != '[' && direttorio[i] != ']' )
      i--;

   if (direttorio[i] == '[')
      i = strlen(direttorio)-1;

   if (i == 0)
      direttorio[i++] = '[';

   strncpy(nuova_dir, direttorio, i);
   nuova_dir[i] = '.';
   nuova_dir[i+1] = '\0';
   strcat(nuova_dir,sottodir);
   strcat(nuova_dir,"]");

   return(nuova_dir);
}




/*
Funzione che dato un path relativo ne restituisce uno assoluto
Parameters:
                char *path_rel: path relativo (stringa gia' allocata)
                char *path_abs: path restituito assoluto (stringa gia' allocata)
Return:
       -1 se fallisce
*/

int path_rel_to_abs(char *path_rel,char *path_abs)
{
char pathPWD[FILENAME_MAX];


/*
Verifica che il path sia assoluto
*/
if(strchr(path_rel,'.'))
   {
   printf("NOME IN RELATIVO =%s\n",path_rel);

   if(!getwd(pathPWD))
      {
      printf("regol_util.c: directory not retrieved \n");
      return(-1);
      }
   if(chdir(path_rel)<0)
      {
      printf("regol_util.c: directory not found !!!\n");
      return(-1);
      }

   if(!getwd(path_abs))
      {
      printf("regol_util.c: directory not retrieved \n");
      return(-1);
      }
   if(chdir(pathPWD)<0)
      {
      printf("regol_util.c: reentrydirectory not found !!!\n");
      return(-1);
      }
   }
else
   strcpy(path_abs,path_rel);
return(0);
}

/*** fine utile.c ***/

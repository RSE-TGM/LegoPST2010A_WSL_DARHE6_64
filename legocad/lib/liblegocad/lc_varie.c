/**********************************************************************
*
*       C Source:               lc_varie.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Jul 19 10:19:18 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: lc_varie.c-3 %  (%full_filespec: lc_varie.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)lc_varie.c	2.2\t2/13/95";
/*
        Fine sezione per SCCS
*/
/*
 lc_varie.c
	utilita' varie.
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
#include <stdarg.h>

#include "legocad.h"  /* definizioni generali per legocad e le sue
                         sottoattivita' */

esiste_file(path)
char *path;
{
struct stat buf;
if(stat(path,&buf)==0)
	return(1);   /* file esistente  */
else
	return(0);   /* file non esistente */
}

/*
        estr_nome_modello(path)
        estrae dal path name (path) l'ultima directory e assume che essa
        indichi il nome del modello selezionato
*/
char *estr_nome_modello(path)
char *path;
{
int i;
i=strlen(path)-1;
/*
 il path name potrebbe comprendere il carattere / finale:
 viene skippato ed eliminato dal path_name
*/
if(path[i]=='/')
        {
        path[i]=0;
        i--;
        }
while(i>0 && path[i]!='/')
        i--;
i++;
if(strlen(&path[i])==0)
        return(NULL);
else
        return(&path[i]);
}

/*
 str_toupper(str)
        trasforma una stringa in uppercase
*/
char *str_toupper(str)
char *str;
{
int i;
for(i=0;i<strlen(str);i++)
        {
        str[i]=toupper(str[i]);
        }
}
    
/*
 str_cut(str)
        elimina eventuali blank in coda ad una stringa
*/
str_cut(str)
char *str;
{
int i;
i=strlen(str)-1;
while (str[i]==' ' && i>=0)
        {
        str[i]=0;
        i--;
        }
}

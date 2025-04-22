/**********************************************************************
*
*       C Source:               chdefaults.c
*       Subsystem:              2
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Sep 25 09:29:31 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: chdefaults.c,2 %  (%full_filespec: 2,csrc,chdefaults.c,2 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)chdefaults.c	5.1\t11/10/95";
/*
   modulo chdefaults.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)chdefaults.c	5.1
*/
/* chdefaults.c
 si posiziona nel direttorio contenente i DEFAULTS se esiste altrimenti
 lo crea. Il direttorio e' localizzato a valle del path espresso dalla variabile
 logica HOME cioe' e' definito da $HOME/defaults
 In questo direttorio vengono posizionati i files:
	uni_misc.dat     defaults per le unita' di misura
	f22_files.dat    memorizzazione path names dei files di grafica 
                         visualizzati dall'utente con la utility grafics
*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h> 
#if defined UNIX 
#include <sys/types.h>
#include <sys/stat.h>
#endif
#if defined VMS
#include <types.h>
#include <stat.h>
#endif

void chdefaults()
{
char *home_dir;
char path_defaults[FILENAME_MAX];
home_dir=getenv("HOME");
if(home_dir==NULL)
        {
        printf("\n logical variable HOME not defined");
        exit(1);
        }
strcpy(path_defaults,home_dir);
#if defined VMS || defined VMS_FORTRAN
strcpy(&path_defaults[strlen(path_defaults)-1],".defaults]");
#else
strcat(path_defaults,"/defaults");
#endif
printf("direttorio def. [%s]\n",path_defaults);
if(chdir(path_defaults)==-1)
        {
#if defined VMS || defined VMS_FORTRAN
        if(mkdir(path_defaults,0)==-1)
#else
        if(mkdir(path_defaults,S_IRWXU|S_IRGRP|S_IROTH)==-1)
#endif
                {
                perror("\n creazione direttorio defaults");
                exit(0);
                }
        if(chdir(path_defaults)==-1)
                {
                perror("\n spostamento in direttorio defaults");
                exit(1);
                }
        }
}

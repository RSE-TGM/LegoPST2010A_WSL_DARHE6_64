/**********************************************************************
*
*       C Source:               lc_util.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Jul 19 10:21:33 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: lc_util.c-5 %  (%full_filespec: lc_util.c-5:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)lc_util.c	2.4\t7/13/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <sys/wait.h>
#ifdef OSF1
#include <sys/types.h>
#endif


void close_prog_legocad();
int attiva_programma(nome)
char *nome;
{
int pid;
#ifndef DESIGN_TIME
signal(SIGCHLD,close_prog_legocad);
if((pid=vfork())==0)
        {
        execlp(nome,nome,(char *)0);
        }
else
        return(pid);
#else
printf("\n simula attivazione %s",nome);
return(1);
#endif
}

void close_prog_legocad(segnale,code,scp)
int segnale,code;
struct sigcontext *scp;
{
extern int chiudi_prog_legocad(); /* funzione definita a livello di
                                     applicativo */
#ifdef ULTRIX
union wait status;
#elif AIX
int status;
#elif OSF1
int status;
#else
int status;
#endif

if (segnale == SIGCHLD)
        {
        wait(&status);
        signal(SIGCHLD,(SIG_DFL) );
        chiudi_prog_legocad();
        }
}
/* attiva_prog_par
  permette di lanciare un programma passandogli un numero arbitrario
  di parametri
  La sintassi per l'utilizzo e':
                attiva_prog_par(nome_eseguibile,par1,par2, ...,(char *)0);
*/

int attiva_prog_par(char * nome_programma, ...)
{
int pid;
int i;
char *argomento; /* puntatore di appoggio per contenere di volta in volta
                    un nuovo argomento */
#define MAX_ARGOMENTI 10  /* numero massimo di argomenti di chiamata per
                             la function attiva_prog_par */
char *argv[MAX_ARGOMENTI];
va_list args;

argv[0]=nome_programma;
va_start(args, nome_programma);
i=1;
while ((argomento=va_arg(args,char *))!=0)
        {
        argv[i]=argomento;
        i++;
        if(i==MAX_ARGOMENTI)
                {
                printf("attiva_prog_par: massimo numero di arg. passati");
                exit(1);
                }
        }
argv[i]=argomento;
va_end(args);
#ifndef DESIGN_TIME
signal(SIGCHLD,close_prog_legocad);
if((pid=vfork())==0)
        {
        execvp(argv[0],argv);
        }
else
        return(pid);
#else
printf("\n simula attivazione ");
#endif
return(1);
}

/*
 uccisione di processo
*/
uccidi_processo(pid)
pid_t pid;
{
kill(pid,SIGKILL);
}




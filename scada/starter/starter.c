/*
   modulo starter.c
   tipo 
   release 1.5
   data 6/14/96
   reserved @(#)starter.c	1.5
*/
/*
        Variabile per identificazione della versione
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>
#include <sys/signal.h>

int stato_processo(pid_t pid);
void attiva_figlio(void);
void messaggio_scada(int sig);
void StrTime(char * nowstr);

int pid_figlio;
int num_parametri;
char par[100][255];
char nome_exe[255];
char path_exe[255];

int main(int argc, char **argv)
{
int i;
	if(argc <3)
		exit(printf("starter [path_exe] [nome_file] [...]\n"));
	/*
		verifico che questo processo abbia i diritti di 
		root. Questo per permettere al processo scada di
		modificare le priorita' dei thread
	*/
	if(geteuid()!=0)
	  {
	  fprintf(stderr,
		"******************************************************\n");
	  fprintf(stderr,
		"*                                                    *\n");
	  fprintf(stderr,
		"*  Il processo starter deve avere i diritti di root  *\n");
	  fprintf(stderr,
		"*  dare da root i seguenti comandi:                  *\n");
	  fprintf(stderr,
		"*  chown root starter                                *\n");
	  fprintf(stderr,
		"*  chmod +s starter                                  *\n");
	  fprintf(stderr,
		"*                                                    *\n");
	  fprintf(stderr,
		"*  il processo scada non gestira' le priorita'       *\n");
	  fprintf(stderr,
		"*                                                    *\n");
	  fprintf(stderr,
		"******************************************************\n");
	  }
	strcpy(path_exe,argv[1]);
	strcpy(nome_exe,argv[2]);
	num_parametri = argc -3;
	for(i=0;i<num_parametri;i++)
		strcpy(par[i],argv[i+3]);
	par[i][0]=0;
#if defined VMS
	printf("%s%s",path_exe,nome_exe);
#else
	printf("%s/%s",path_exe,nome_exe);
#endif
	for(i=0;i<num_parametri;i++)
		printf(" %s",par[i]);
	printf("\n");
	
	signal(SIGALRM,(void(*)(int))messaggio_scada);

	attiva_figlio();
	while(1)
		{
		sleep(1);
		if(stato_processo(pid_figlio)<=0)
			attiva_figlio();
		}
}


void attiva_figlio(void)
{
char *proc_envp[9];
char proc_name[255];
char *proc_argv[100];
int i;
FILE *fp_log;
char str_time[80];


for(i=0;i<=num_parametri;i++)
	proc_argv[i]=(char*)malloc(255);
	
sprintf(proc_argv[0],"%s\00",nome_exe);
for(i=1;i<=num_parametri;i++)
	sprintf(proc_argv[i],"%s\00",par[i-1]);
proc_argv[i]=NULL;

proc_envp[0]=(char*)malloc(255);
proc_envp[1]=(char*)malloc(255);
proc_envp[2]=(char*)malloc(255);
proc_envp[3]=(char*)malloc(255);
proc_envp[4]=(char*)malloc(255);
proc_envp[5]=(char*)malloc(255);
proc_envp[6]=(char*)malloc(255);
proc_envp[7]=(char*)malloc(255);
proc_envp[9]=(char*)malloc(255);


if(getenv("SCADA_BIN")!=NULL)
	sprintf(proc_envp[0],"SCADA_BIN=%s\00",getenv("SCADA_BIN"));
else
	exit(fprintf(stderr,"definire SCADA_BIN\n"));

if(getenv("HOME")!=NULL)
	sprintf(proc_envp[1],"HOME=%s\00",getenv("HOME"));
else
	exit(fprintf(stderr,"definire HOME\n"));

if(getenv("DISPLAY")!=NULL)
	sprintf(proc_envp[2],"DISPLAY=%s\00",getenv("DISPLAY"));
else
	exit(fprintf(stderr,"definire DISPLAY\n"));

if(getenv("OFFSET_SCADA_PORT")!=NULL)
	sprintf(proc_envp[3],"OFFSET_SCADA_PORT=%s\00",
			getenv("OFFSET_SCADA_PORT"));
else
	sprintf(proc_envp[3],"OFFSET_SCADA_PORT=0\00");

if(getenv("DEBUG_NET")!=NULL)
	sprintf(proc_envp[4],"DEBUG_NET=%s\00",getenv("DEBUG_NET"));
else
	sprintf(proc_envp[4],"DEBUG_NET=0\00");
/* 
Tempo per innescare calcolate vedi SynSim.c
*/
if(getenv("OFFSETTIMESIM")!=NULL)
        sprintf(proc_envp[5],"OFFSETTIMESIM=%s\00",getenv("OFFSETTIMESIM"));
else
        sprintf(proc_envp[5],"OFFSETTIMESIM=0\00");

if(getenv("ALG_LICENSE_FREE")!=NULL)
        sprintf(proc_envp[6],"ALG_LICENSE_FREE=%s\00",getenv("ALG_LICENSE_FREE"));
else
        sprintf(proc_envp[6],"OFFSETTIMESIM=0\00");

if(getenv("LOADCIRICALL")!=NULL)
        sprintf(proc_envp[7],"LOADCIRICALL=%s\00",getenv("LOADCIRICALL"));
else
        sprintf(proc_envp[7],"LOADCIRICALL=0\00");
if(getenv("SCDCOMPACTALL")!=NULL)
        sprintf(proc_envp[8],"SCDCOMPACTALL=%s\00",getenv("SCDCOMPACTALL"));
else
        proc_envp[8]=NULL;
proc_envp[9]=NULL;

sprintf(proc_name,"%s/%s\00",path_exe,nome_exe);

pid_figlio=vfork();
if ( pid_figlio == 0 )
      {
      execve(proc_name,proc_argv,proc_envp);
      perror("execve processo figlio");
      exit(0);
      }

/*
	registro il log dell'attivazione
*/
StrTime(str_time);
fp_log = fopen("starter.log","a");
fprintf(fp_log,"starter [%s]\n",str_time);
fprintf(fp_log,"    attivazione [%s] pid = %d\n",proc_name,pid_figlio);
fclose(fp_log);

}


int stato_processo(pid)
pid_t pid;
{
int ritorno;
int status;

if(pid<=0)
        return(0);

if(pid==1)
        return(1);

        ritorno=waitpid(pid,&status,WNOHANG);

if(ritorno<0)
        return(0);
else
        return(1);
}

void StrTime(char * nowstr)
{
          time_t nowbin;
           struct tm *nowstruct;

           (void)setlocale(LC_ALL, "");

           if (time(&nowbin) == (time_t) - 1)
               printf("Could not get time of day from time()\n");

           nowstruct = localtime(&nowbin);

           if (strftime(nowstr, 80, "%A %d/%m/%y %H:%M:%S", nowstruct) == (size_t) 0)
               printf("Could not get string from strftime()\n");
}


void messaggio_scada(int sig)
{
char str_time[80];
FILE *fp_log;

StrTime(str_time);
fp_log = fopen("starter.log","a");
fprintf(fp_log,"starter [%s]\n",str_time);
fprintf(fp_log,"    richiesta restart\n");
fclose(fp_log);
}

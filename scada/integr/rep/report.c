/*
   modulo report.c
   tipo 
   release 1.2
   data 6/13/96
   reserved @(#)report.c	1.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>

#define MAXRIGA 255

int legge_riga(FILE* fp,char *riga)
{
int ret;

memset(riga,0,MAXRIGA);
ret = fgets(riga,MAXRIGA,fp);
if(strlen(riga))
        riga[strlen(riga)-1]=0;
return(ret);
}

int togli_apici(char *riga)
{
int i;
for(i=0;i<strlen(riga);i++)
	if(riga[i]=='\"')
		riga[i]=' ';
}


main(argc,argv)
int argc;
char ** argv;
{
char *path;
char *path_log;
char riga[MAXRIGA];
FILE *fp;
FILE *fp_out;
FILE *fp_test;
char nome_file[FILENAME_MAX+1];
char nome_file_log[FILENAME_MAX+1];
char nome_old[FILENAME_MAX+1];
char versione[FILENAME_MAX+1];
char *app;
char dir_or[FILENAME_MAX+1];
char nuovo[FILENAME_MAX+1];

path = getcwd(NULL,FILENAME_MAX);
app=strstr(path,"pscs32");
strcpy(dir_or,"/usr/users/scada/pscs32_DOS_20_11_95");
strcat(dir_or,&app[6]);

printf("Report SCCS direttorio [%s]\n",path);

system("sccs prs SCCS > qq");
fp=fopen("qq","r");
path_log=getenv("HOME");
strcpy(nome_file_log,path_log);
strcat(nome_file_log,"/report.log");
if((fp_out=fopen(nome_file_log,"r"))==NULL)
	{
	fp_out=fopen(nome_file_log,"w");
	fprintf(fp_out,
"\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
			"path","file","versione","nuovo",
			"C1","C2","C3","C4","C5","C6","C7","C8",
			"C9","C10","C11","C12","C13","C14","C15");
	}
else
	fp_out=fopen(nome_file_log,"a");

while(legge_riga(fp,riga))
	if(strncmp(riga,"SCCS",4)==0)
	{
	strcpy(nome_file,&riga[7]);
	app=strstr(nome_file,":");
	*app=0;
	legge_riga(fp,riga);  // riga bianca
	legge_riga(fp,riga);  // riga versione
	strcpy(versione,&riga[2]);
	app=strstr(versione," ");
	*app=0;
	strcpy(nome_old,dir_or);
	strcat(nome_old,"/");
	strcat(nome_old,nome_file);
	strcpy(nuovo,"precedente");
	if((fp_test=fopen(nome_old,"r"))==NULL)
		strcpy(nuovo,"nuova");
	else
		fclose(fp_test);
	
	app=strstr(path,"pscs32");
	fprintf(fp_out,"\"%s\";\"%s\";\"%s\";\"%s\"",
			app,nome_file,versione,nuovo);
	if(strcmp(nuovo,"nuova")!=0)
		{
		char comando[255];
		FILE *fp_prs;
		int commenti=0;

		//printf("file %s leggo i commenti\n",nome_file);
		sprintf(comando,"sccs prs %s > qq1",nome_file);
		system(comando);
		fp_prs=fopen("qq1","r");
		while(legge_riga(fp_prs,riga))
		   if(
			(commenti < 16)&&
			(strlen(riga)>0)&&
			(strncmp(riga,"SCCS",4)!=0)&&
			(strncmp(riga,"D ",2)!=0)&&
			(strncmp(riga,"MRs:",4)!=0)&&
			(strncmp(riga,"COMMENTS",8)!=0)
			)
			{
			commenti ++;
			togli_apici(riga);
			fprintf(fp_out,";\"%s\"",riga);	
			}
		unlink("qq1");
		}
		fprintf(fp_out,"\n");
	}

fclose(fp);
fclose(fp_out);
unlink("qq");
exit(0);
}


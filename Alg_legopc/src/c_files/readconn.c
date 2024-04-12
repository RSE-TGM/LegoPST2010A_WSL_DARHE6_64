#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 500
#define MAXCONN 100

int FPORTNTYPE=0;
int fpvnum[MAXCONN];

void read_conn(void) {

FILE *fp;
int i, countlines=0;
char *tixvar;
char path[MAXLINE],line[MAXLINE];

//tixvar = getenv( "LG_TIX" );
tixvar = getenv( "LG_LIBGRAPH" );
strcpy(path,tixvar);
strcat(path,"/connect.dat");
fp=fopen(path,"r");

while(fgets(line,500,fp) != NULL) {
	if (strstr(line,"****") == NULL) {		 
	    countlines++;
	} else {
	    fpvnum[FPORTNTYPE++]=countlines-4; //input port nvars
	    fpvnum[FPORTNTYPE++]=countlines-4; //output port nvars
	    countlines=0;
	}
}

fclose(fp);

printf("%d\n",FPORTNTYPE);
for(i=0;i<FPORTNTYPE;i++)
	printf("%d ",fpvnum[i]);
}

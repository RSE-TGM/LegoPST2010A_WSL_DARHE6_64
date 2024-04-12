/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
        Variabile per identificazione della versione
*/
#include <stdio.h>
#include <string.h>

main(argc,argv)
int argc;
char *argv[];
{
int num;
char nome_out[FILENAME_MAX+1];
FILE *fp = NULL;
char nome_file[FILENAME_MAX+1]; 

if(argc<2)
	return;
num = atoi(argv[1]);
sprintf(nome_out,"tty >apptty%d\n",num);
system(nome_out);
sprintf(nome_file,"apptty%d",num);
while(1)
	{
	sleep(1);
	if( (fp=fopen(nome_file,"r"))== NULL)
		exit(0);
	fclose(fp);
	}
}

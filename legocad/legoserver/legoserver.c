/**********************************************************************
*
*       C Source:               legoserver.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Wed Mar 17 17:42:36 2004 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: legoserver.c-3 %  (%full_filespec: legoserver.c-3:csrc:1 %)";
#endif

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
char buff[1024];
char buf4[4];
char buf80[80];

main(argc,argv)
int     argc;
char    *argv[];
{
int fn; /* file number */
int num_modulo;
if(argc < 2)
	{
	printf("\n errore: chiamata corretta= legoserver N (numero modulo)");
	exit(1);
	}
printf("-------------------------------------------------------------------------------------------- \n");
fn=77;    /* canale utilizzato dalla routine XXXXI4 per l'output */
num_modulo=atoi(argv[1]);
modi3_(&num_modulo,&fn,buf4,buf80);
printf("-------------------------------------------------------------------------------------------- \n");
close(fn);
sleep(1);
exit(0);
}

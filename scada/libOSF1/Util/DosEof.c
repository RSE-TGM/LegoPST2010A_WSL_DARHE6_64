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
#include <stdio.h>

int DosFeof(FILE *fp)
{
	int ch;

	ch=getc(fp);
	ungetc(ch,fp);
	printf("%d %d\n",ch, EOF);
	return (ch==EOF);
}


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
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_DIM_BUFFER_RETE 100000


int readn(fd,ptr,nbytes)
int fd;
char *ptr;
int nbytes;
{
int nleft,nread;
nleft=nbytes;
while(nleft>0)
	{
	if(nleft>MAX_DIM_BUFFER_RETE)
		nread=read(fd,ptr,MAX_DIM_BUFFER_RETE);
	else
		nread=read(fd,ptr,nleft);
	if(nread<0)
		return(nread);
	else if (nread==0)
		break;
	nleft-=nread;
	ptr+=nread;
	}
return(nbytes-nleft);
}

int writen(fd,ptr,nbytes)
int fd;
char *ptr;
int nbytes;
{
int nleft,nwrite;
nleft=nbytes;
while(nleft>0)
        {
	if(nleft>MAX_DIM_BUFFER_RETE)
        	nwrite=write(fd,ptr,MAX_DIM_BUFFER_RETE);
	else
        	nwrite=write(fd,ptr,nleft);
        if(nwrite<=0)
                return(nwrite);
        nleft-=nwrite;
        ptr+=nwrite;
        }
return(nbytes-nleft);
}

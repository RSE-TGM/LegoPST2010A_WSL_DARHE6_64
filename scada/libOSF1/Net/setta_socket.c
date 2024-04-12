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
#include <errno.h>
#if defined UNIX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif

#if defined VMS
# include <iodef.h>
#include <types.h>
#include <socket.h>
#include <in.h>
#include <netdb.h>
#include <inet.h>
#include <ucx$inetdef.h>
#endif


setta_dim_buffer(int fp, int size)
{

	if(setsockopt(fp,SOL_SOCKET,SO_SNDBUF,(char*) &size,sizeof(int))<0)
	{
	fprintf(stderr,"setta_dim_buffer: impossibile settare parametro size\n");
	return( -1);
	}
else
	return(1);
}

setta_attesa_close(int fp, int time)
{
struct linger linger;

linger.l_onoff=1;
linger.l_linger=time;

if(setsockopt(fp,SOL_SOCKET, SO_LINGER, (char*) &linger,sizeof(linger))<0)
	{
	fprintf(stderr,"setta_attesa_close: impossibile settare parametro\n");
	return( -1);
	}
else
	return(1);

}

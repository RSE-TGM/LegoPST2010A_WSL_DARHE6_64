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
   modulo test_host.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)test_host.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)test_host.c	5.1\t11/7/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
# include <string.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
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

int test_host(host)
char *host;
{
struct hostent *hostptr;

	hostptr=gethostbyname(host);
	if(hostptr==NULL)
		return(0);
	else
		return(1);
}

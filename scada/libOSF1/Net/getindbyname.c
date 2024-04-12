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
# include <stdio.h>
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

int getindbyname();
int pr_inet();


int getindbyname(macchina)
char *macchina;
{
struct hostent *hostptr;
int indirizzo;

hostptr=gethostbyname(macchina);
indirizzo=pr_inet(hostptr->h_addr_list);
return(indirizzo);
}

int pr_inet(listptr)
char **listptr;
{
        struct in_addr *ptr;
        while((ptr=(struct in_addr*) *listptr++)!=NULL)
                return(inet_lnaof(*ptr));
}

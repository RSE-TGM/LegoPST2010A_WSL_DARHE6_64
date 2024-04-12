/**********************************************************************
*
*       C Source:               getindbyname.c
*       Subsystem:              3
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Feb 11 11:37:39 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: getindbyname.c-2 %  (%full_filespec: getindbyname.c-2:csrc:3 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)getindbyname.c	5.1\t11/7/95";
/*
   modulo getindbyname.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)getindbyname.c	5.1
*/
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>

int getindbyname();
int pr_inet();


int getindbyname(macchina)
char *macchina;
{
struct hostent *hostptr;
int indirizzo=-1;

/*
Dal nome della macchina ricavo il puntatore alla struttura degli addresses 
*/

if(( hostptr=gethostbyname(macchina) ) == NULL)
	{
	printf("Getindbyname: errore nel nome macchina\n");
	return(-1);
	}
switch (hostptr->h_addrtype)   /* deve essere di tipo internet */
	{
	case AF_INET:
	indirizzo=pr_inet(hostptr->h_addr_list);
	break;
	
	default: 
	printf("Getindbyname: errore nel tipo di indirizzo \n");
	return(-1);
	break;
	}
return(indirizzo);
}

int pr_inet(listptr)
char **listptr;
{
        struct in_addr *ptr;
        while((ptr=(struct in_addr*) *listptr++)!=NULL)
                return(inet_lnaof(*ptr));
}

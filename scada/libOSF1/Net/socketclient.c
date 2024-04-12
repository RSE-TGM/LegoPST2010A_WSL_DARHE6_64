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
#include <string.h>
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

char   *io_sono ();


int     socketclient (macchina, server_port)
char   *macchina;
int     server_port;
{
int     fp;
struct sockaddr_in  client;
struct hostent *hp;
#if defined UNIX
struct hostent *gethostbyname ();
#endif
char    io[255];
int     tentativi = 0;

    printf ("Inizio apertura socket in scrittura verso %s\n", macchina);
    while (1)
    {
/* apertura socket */
	fp = socket (AF_INET, SOCK_STREAM, 0);
	if (fp < 0)
	{
	    perror ("opening stream socket");
	    exit (0);
	}

	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;

	hp = gethostbyname (macchina);
	if (hp == 0)
	{
	    printf ("%s: unknown host\n", macchina);
	    exit (0);
	}
	strcpy (io, io_sono ());
	memcpy ((char *) & client.sin_addr, (char *) hp -> h_addr, hp -> h_length);
	client.sin_port = htons (server_port);
	if (connect (fp, (struct sockaddr  *) & client, sizeof (client)) < 0)
	{
	                                        sleep (1);
	    if (++tentativi == 20)
		exit (printf ("Connessione con %s fallita\n", macchina));
	}
	else
	{
	    printf ("Fine apertura socket in scrittura verso %s porta %d id %d \n",
		    macchina, server_port, fp);
	    return (fp);
	}
    }
}

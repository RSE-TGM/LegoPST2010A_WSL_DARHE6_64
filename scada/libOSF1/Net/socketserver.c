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
   modulo %M%
   tipo %Y%
   release %I%
   data %G%
   reserved %W%
*/
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
#include <sys/signal.h>
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



int     socketserver (server_port,fp_in)
int     server_port;
int     *fp_in;
{
int     fp;
int     prova;
int     qq;
struct sockaddr_in  server;




printf ("Inizio apertura socket in lettura da %d fp_in = %d\n", 
		server_port,*fp_in);

if(*fp_in < 0)
	{
	/* apertura socket */
    	fp = socket (AF_INET, SOCK_STREAM, 0);
    	if (fp < 0)
    		{
		perror ("opening stream socket");
		return(-1);
    		}

    	server.sin_family = AF_INET;
    	server.sin_addr.s_addr = INADDR_ANY;
    	server.sin_port = htons (server_port);
    	if (bind (fp, (struct sockaddr *) & server, sizeof (server)) < 0)
    		{
		perror ("binding datagram socket");
		return(-1);
    		}
	memcpy(fp_in,&fp,sizeof(int));
	}
else
	{
	fp = *fp_in;
	}

    listen (fp, 5);

    qq = sizeof (server);
    if ((fp = accept (fp, &server, &qq)) < 0)
    {
	perror ("Errore accept");
	return(-1);
    }

/*
    printf ("Fine apertura socket in lettura porta %d id %d\n", 
	    server_port, fp);
*/
    return (fp);
}

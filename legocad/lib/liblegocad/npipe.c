/**********************************************************************
*
*       C Source:               npipe.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 14:11:00 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: npipe.c,2 %  (%full_filespec: 1,csrc,npipe.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)npipe.c	2.3\t4/26/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
typedef char byte;

typedef struct {
                  char applicativo[8];
                  int  codice;
                  int  lunghezza;
               } header_mesg;

char *messaggio;

int uscita;
void attesa();

extern int send_message( int, char*, int, char*, int );


int wr_pipe_(cod,msg)
int *cod;
char *msg;
{
int ret;
   static int fd = -1;

   if ( fd == -1 )
      fd=open("to_calcstaz",O_WRONLY);

   if ( fd == -1 )
      return(1);

   if (strlen(msg) > 70 )
      msg[70]='\0';

   ret=send_message(fd,"LG3",*cod,msg,strlen(msg)+1);
   return(ret);
}

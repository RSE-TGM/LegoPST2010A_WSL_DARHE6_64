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
static char SccsID[] = "@(#)msg_create.c	5.1\t11/7/95";
/*
   modulo msg_create.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)msg_create.c	5.1
*/
#include <stdio.h>

#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <errno.h>
# include <setjmp.h>
# include <sys/signal.h>
# include <unistd.h>
#endif

#if defined VMS
#include <ssdef.h>
#include <psldef.h>
#include <iodef.h>
#include <descrip.h>
#include "vmsipc.h"
#endif



int msg_create();

int msg_create(key,master)
int key;
int master;
{
int id;
#if defined UNIX
int i;

/* creazione coda */
if((id=msgget(key, 0777 | IPC_CREAT))==(-1))
	{
	/* errore nella creazione della coda */
	printf("Coda (%d) ",key);
	perror("->");
	return(-1);
	}
#endif
#if defined VMS
unsigned short canale_0;
unsigned short canale_1;
char *nome_mailbox_0;
char *nome_mailbox_1;
struct dsc$descriptor_s name_desc_0;
struct dsc$descriptor_s name_desc_1;
int stato_0=0;
int stato_1=0;
char appoggio[4];

/* allocazione nome mailbox */
nome_mailbox_0=(char*)malloc(30);
nome_mailbox_1=(char*)malloc(30);

sprintf(nome_mailbox_0,"MAIL_BOX_1_%d",key);
sprintf(nome_mailbox_1,"MAIL_BOX_2_%d",key);

/*printf("%s %s\n",nome_mailbox_0,nome_mailbox_1);*/

/* allocazione descrittore del nome della mailbox */
name_desc_0.dsc$b_class=DSC$K_CLASS_S;
name_desc_0.dsc$b_dtype=DSC$K_DTYPE_T;
name_desc_0.dsc$a_pointer=nome_mailbox_0;
name_desc_0.dsc$w_length=strlen(nome_mailbox_0);
name_desc_1.dsc$b_class=DSC$K_CLASS_S;
name_desc_1.dsc$b_dtype=DSC$K_DTYPE_T;
name_desc_1.dsc$a_pointer=nome_mailbox_1;
name_desc_1.dsc$w_length=strlen(nome_mailbox_1);

/* libera la stringa contenente il nome della mailbox */
free(nome_mailbox_0);
free(nome_mailbox_1);

stato_0=SYS$ASSIGN(&name_desc_0,&canale_0,PSL$C_USER,0);
if(stato_0!=SS$_NORMAL)
{
        /*printf("Creo la mail box\n");*/
        stato_0=SYS$CREMBX(0,&canale_0,sizeof(STRUTTURA_MESSAGGIO_BASE),
               sizeof(STRUTTURA_MESSAGGIO_BASE)+100
		,NULL,PSL$C_USER,&name_desc_0);
        if(stato_0!=SS$_NORMAL)
                {
                /* impossibile creare la mailbox */
                LIB$SIGNAL(stato_0);
                /* ritorna codice di errore */
                return(-1);
                }
        stato_1=SYS$CREMBX(0,&canale_1,sizeof(STRUTTURA_MESSAGGIO_BASE),
               sizeof(STRUTTURA_MESSAGGIO_BASE)+100,
		NULL,PSL$C_USER,&name_desc_1);
        if(stato_1!=SS$_NORMAL)
                {
                /* impossibile creare la mailbox */
                LIB$SIGNAL(stato_1);
                /* ritorna codice di errore */
                return(-1);
                }
}
else
{
        /*printf("Mi aggancio alla mail_box\n");*/
        stato_1=SYS$ASSIGN(&name_desc_1,&canale_1,PSL$C_USER,0);
        if(stato_1!=SS$_NORMAL)
                {
                /* impossibile agganciare la mailbox */
                LIB$SIGNAL(stato_1);
                /* ritorna codice di errore */
                return(-1);
                }
}
if(master==1)
{
/* costruzione id */
memcpy(&appoggio[0],&canale_0,sizeof(short));
memcpy(&appoggio[2],&canale_1,sizeof(short));
memcpy(&id,&appoggio[0],sizeof(int));
}
else
{
/* costruzione id */
memcpy(&appoggio[0],&canale_1,sizeof(short));
memcpy(&appoggio[2],&canale_0,sizeof(short));
memcpy(&id,&appoggio[0],sizeof(int));
}
#endif
return(id);
}

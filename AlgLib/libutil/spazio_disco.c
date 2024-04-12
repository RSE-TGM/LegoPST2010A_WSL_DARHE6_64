/**********************************************************************
*
*       C Source:               spazio_disco.c
*       Subsystem:              2
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Oct 21 09:58:13 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: spazio_disco.c-3 %  (%full_filespec: spazio_disco.c-3:csrc:2 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)spazio_disco.c	5.1\t11/10/95";
/*
   modulo spazio_disco.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)spazio_disco.c	5.1
*/
#include <stdio.h>
#if defined UNIX
#include <sys/types.h>
#include <sys/stat.h>
extern char *getwd(char *);
#endif
#if defined VMS 
#include <types.h>
#include <stat.h>
#endif
#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>
#if defined AIX || defined LINUX
#include <sys/statfs.h>
#endif
#if defined OSF1 || defined SCO
#include <sys/mount.h>
#endif
#if defined ULTRIX
#include <sys/param.h>
#include <sys/mount.h>
#endif
#if defined VMS
#include <iodef.h>
#include <psldef.h>
#include <ssdef.h>
#include <secdef.h>
#include <descrip.h>
#include <dvidef.h>
#include <stdlib.h>
#endif

#include "libutilx.h"

int spazio_disco(path)
	char *path; /* parametro inutilizzato */
{
int spazio;
#if defined AIX || defined OSF1 || defined SCO || defined LINUX
char path_aix[FILENAME_MAX+1];
char *retwd;
struct statfs buf;
#endif
#if defined ULTRIX
struct fs_data buf;
#endif
#if defined VMS
unsigned int stato;
int app_1;
struct dsc$descriptor_s name_desc_0;
struct dsc$descriptor_s des_ret;
unsigned short lun;
char nome_disco[30];
#endif

#if defined AIX || defined OSF1 || defined SCO || defined LINUX
	retwd=getwd(path_aix);
	if(retwd == 0) 
		{
		printf("\n spazio disco: errore in getwd");
		spazio=-1;
		}
	else
		{
        	statfs(path_aix,&buf);
		spazio=(int)buf.f_bavail*4 ;   /* Kbytes
                                     consumabili dall'utente */
		}
#endif
#if defined ULTRIX
        getmnt(0, &buf, 0, STAT_ONE, path);
	spazio=(int)buf.fd_req.bfreen ;   /* Kbytes
                                     consumabili dall'utente */
#endif

#if defined VMS

sprintf(nome_disco,"SYS$DISK:");

name_desc_0.dsc$b_class=DSC$K_CLASS_S;
name_desc_0.dsc$b_dtype=DSC$K_DTYPE_T;
name_desc_0.dsc$a_pointer=nome_disco;
name_desc_0.dsc$w_length=strlen(nome_disco);

des_ret.dsc$b_class=DSC$K_CLASS_S;
des_ret.dsc$b_dtype=DSC$K_DTYPE_T;
des_ret.dsc$a_pointer=(char*)malloc(15);
des_ret.dsc$w_length=15;

app_1=DVI$_FREEBLOCKS;

stato=LIB$GETDVI(&app_1,0,&name_desc_0,0,&des_ret,&lun);
        if(stato!=SS$_NORMAL)
        {
        LIB$SIGNAL(stato);
        }
spazio=atoi(des_ret.dsc$a_pointer)*1024/2;
#endif


return(spazio);
}

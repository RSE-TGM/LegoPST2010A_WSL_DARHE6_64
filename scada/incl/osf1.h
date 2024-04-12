/**********************************************************************
*
*       C Header:               osf1.h
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Fri Dec 13 15:21:06 2002 %
*
**********************************************************************/
#if defined OSF1 || defined LINUX
#include <stdio.h>
#include <pthread.h>

FILE *DosFopen(char *, char *);

#define strnicmp(a,b,c)		strncasecmp(a,b,c)
#define fopen(a,b)		DosFopen(a,b)
#define remove(a)		DosRemove(a)
#define rename(a,b)		DosRename(a,b)
#define visch(a)                printf("%c\n",a)

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

#ifndef O_BINARY
#define O_BINARY 0x0000
#endif

#endif

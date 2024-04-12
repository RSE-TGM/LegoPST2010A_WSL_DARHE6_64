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
static char SccsID[] = "@(#)utstrstr.c	5.1\t11/10/95";
/*
   modulo utstrstr.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)utstrstr.c	5.1
*/
/*
  Versione della routine strstr case insensitive
*/
#include <string.h>
#include <ctype.h>

char *Utstrstr(s1,s2)
char *s1;
char *s2;
{
int i, l1, l2;

l1 = strlen(s1);
l2 = strlen(s2);

if(l1<l2) return(NULL);
for(i=0;i<=(l1-l2);i++)
        {
        if(strncasecmp(s2,(s1+i),l2)==0)
                return((s1+i));
        }
return(NULL);
}

#if defined (VMS)
strncasecmp(str1,str2,lun)
char *str1;
char *str2;
int lun;
{
int i;
for(i=0;i<lun;i++)
	{
	if(_toupper(str1[i])!=_toupper(str2[i]))
		return(1);
	}
return(0);
}
strcasecmp(str1,str2)
char *str1;
char *str2;
{
int lun;
int i;

if(strlen(str1)!=strlen(str2))
        return(1);
lun=strlen(str1);
for(i=0;i<lun;i++)
        {
        if(_toupper(str1[i])!=_toupper(str2[i]))
                return(1);
        }
return(0);
}
#endif

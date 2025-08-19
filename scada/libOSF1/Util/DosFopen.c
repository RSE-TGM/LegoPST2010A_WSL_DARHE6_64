/**********************************************************************
*
*       C Source:               DosFopen.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 11:06:57 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: DosFopen.c-3 %  (%full_filespec: DosFopen.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

static void ToLower(char *psz)
{
        int i;
#ifdef FABIO
        for(i=0;psz[i];i++)
                psz[i]=tolower(psz[i]);
#endif
}

static void NoBackSlash(char *psz)
{
        int i;

        for(i=0;psz[i];i++)
		if(psz[i] == '\\')
			psz[i] = '/';
}

int DosRemove( char *path)
{
	ToLower(path);
	NoBackSlash(path);
	return(remove(path));
}

int DosRename(char *path1, char *path2)
{
	ToLower(path1);
	ToLower(path2);
	NoBackSlash(path1);
	NoBackSlash(path2);
	return(rename(path1,path2));
}

FILE *DosFopen( char *path, char *mode)
{
FILE *fp;


ToLower(path);
NoBackSlash(path);
//printf("apertura file DosFopen [%s]\n",path);
fp = fopen(path,mode);

return (fp);
}

/* 
   to_ascii()

   Funzione che effettua la conversione dal formato
   ascii DOS a quello UNIX (DOS->UNIX)              
*/
void to_ascii(char *nome)
{
FILE *fp = NULL;
FILE *fp_out = NULL;
char c;

fp = fopen(nome,"r");
fp_out = fopen("kk__kk.kkk","w");
if(fp == NULL)
        return;
while(1)
        {
        c=getc(fp);
        if(c==0x0D)
                continue;
        if(feof(fp)==0)
                putc(c,fp_out);
        else
		{
                putc(0x0A,fp_out);
                break;
		}
        }
fclose(fp);
fclose(fp_out);
remove(nome);
rename("kk__kk.kkk",nome);
}

/*
   AsciiUnixToDos()

   Funzione che effettua la conversione dal formato
   ascii UNIX a quello DOS (UNIX->DOS)              
*/
void AsciiUnixToDos(char *nome)
{
	FILE *fp = NULL;
	FILE *fp_out = NULL;
	int c;

	if(!(fp=fopen(nome,"r")))
		return;

	fp_out=fopen("kk__kk.kkk","w");

	for(;(c=getc(fp))!=EOF;)
	{
        	if(c==0x0A)
                	putc(0x0D,fp_out);
               	putc(c,fp_out);
	}

	fclose(fp);
	fclose(fp_out);
	remove(nome);
	rename("kk__kk.kkk",nome);
}

void TrimOffTrailingBlanks(char *pch)
{
	short l=strlen(pch)-1;
	for(;pch[l]==' ';l--)
		pch[l]='\0';
}

int DosOpen( char *path,int oflag,mode_t mode)
{
        ToLower(path);
        NoBackSlash(path);
	TrimOffTrailingBlanks(path);
        //printf("apertura file DosOpen [%s]\n",path);
        return open(path,oflag,mode);
}

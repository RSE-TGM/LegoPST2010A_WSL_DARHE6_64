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
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


/*
	funzioni per accesso al disco
	rbyte e wbyte utilizzano  read & write
	frbyte e fwbyte utilizzano  fread & fwrite
	entrambe tornano 	nbyte: operazione riuscita
				-1: error
*/

int rbyte(int file_handle,void * buffer,size_t offset,size_t nbyte)
{ 
/**
printf("rbyte file_handle = %d size = %d offset = %d\n",
		file_handle,nbyte,offset);
**/
ssize_t rrbyte;

if(lseek(file_handle,offset,SEEK_SET) == -1)
	{   
	fprintf(stderr,"rbyte: errore lseek\n");
	return(-1);
	}

if((rrbyte=read(file_handle, buffer,nbyte)) == -1)
        fprintf(stderr,"rbyte: errore read\n ");

return(rrbyte);
}

int wbyte(int file_handle,void * buffer,size_t offset,size_t nbyte)
{
/**
printf("wbyte file_handle = %d size = %d offset = %d\n",
		file_handle,nbyte,offset);
**/
ssize_t wwbyte;

if(lseek(file_handle,offset,SEEK_SET) == -1)
	{   
	fprintf(stderr,"wbyte: errore lseek\n");
	return(-1);
	}

if((wwbyte=write(file_handle, buffer,nbyte)) == -1)
        fprintf(stderr,"wbyte: errore write\n");

return(wwbyte);
}

int frbyte(FILE * fp,void * buffer,size_t offset,size_t nbyte)
{ 
/**
printf("rbyte fp = %d size = %d offset = %d\n",
		fp,nbyte,offset);
**/
ssize_t rrbyte;

if(fseek(fp,offset,SEEK_SET) == -1)
	{   
	fprintf(stderr,"frbyte: errore fseek\n");
	return(-1);
	}

if((rrbyte=fread(buffer,1,nbyte,fp)) == -1)
        fprintf(stderr,"frbyte: errore read\n ");

return(rrbyte);
}

int fwbyte(int fp,void * buffer,size_t offset,size_t nbyte)
{
/**
printf("fwbyte fp = %d size = %d offset = %d\n",
		fp,nbyte,offset);
**/
ssize_t wwbyte;

if(fseek(fp,offset,SEEK_SET) == -1)
	{   
	fprintf(stderr,"fwbyte: errore fseek\n");
	return(-1);
	}

if((wwbyte=fwrite(buffer,1,nbyte,fp)) == -1)
        fprintf(stderr,"fwbyte: errore write\n");

return(wwbyte);
}

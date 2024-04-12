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
/*
	la routine readiz legge gli stati in chiaro degli organi dal file
	dizionario fdizst in un buffer

	buff	char * buffer in cui leggere gli stati
	fp		file pointer file dizionario
*/
#include <stdio.h>

#include "fileop.inc"

readiz(buff,fp)
FILE *fp ;
char *buff ;
{
char stringa[132] ;
char *p1;
short i;

memset(buff,' ',rec_fdizst) ;						  /* inizializzo a blank */
p1= buff;
for(i=0;i<rec_fdizst;i=i+lun_stato )
{
	if(!fgets(stringa,132,fp)) break ;
	memcpy(p1,stringa,lun_stato) ;
	p1=p1+lun_stato ;
}
return ;
}																									  


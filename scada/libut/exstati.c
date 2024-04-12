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
	la function exstati verifica se lo stato in chiaro e' presente nel
	file dizionario

	fp		file pointer file dizionario
   stato char *	stato in chiaro da ricercare
	buf_stati char * buffer di stati
*/

#include <stdio.h>
#include "fileop.inc"

exstati(stato,buf_stati)
char *stato;
char *buf_stati ;
{

char *p1 ;
short i ;

p1= buf_stati ;
for(i=0;i<rec_fdizst/lun_stato;i++)
{
	if(! strncmp(p1,stato,lun_stato)) return(i) ;
	p1=p1+lun_stato;
}																									  
return(-1) ;
}

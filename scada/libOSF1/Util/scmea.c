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
/*->scmea	
	routine generale di scodamento
	codall	indice della  coda
	buff    char *  buffer
*/
#include <pthread.h>
#ifdef DOS
#include <pscs\rtime.inc>
#endif
#include <code.h>
#include <memory.h>
#include <string.h>

scmea(coda  ,buff)
char *buff      ;
int coda ;
{
char *p1,*p2 ;
int parz ;
struct s_code *cod ;

union llg {          /* definisco valori di lettura lunghezza */
          short   x ;  /* prima era un intero  */
          char  c[2] ;
          } lung ;

scd()  ;             /* disabilito lo scheduling dei TASK */
cod=& cd[coda] ;
pthread_mutex_lock(&(cod->mutex));
if( !cod->occup  )
{
   sce()  ;          /* riabilito lo scheduling dei TASK */
pthread_mutex_unlock(&(cod->mutex));
	return(1);		   /* coda vuota */
}
if(cod->sco == cod->fine) cod->sco=cod->init ;
p1= &buff_code[cod->sco] ;
if(!cod->passo) 
  {
  if(cod->sco+1 == cod->fine)
    p2=&buff_code[cod->init];
  else
    p2=p1+1 ;
  lung.c[0]= *p1 ;     /* leggo byte basso della lunghezza */
  lung.c[1]= *p2 ;     /* leggo byte alto della lunghezza */
  }
else   lung.x=cod->passo    ;

cod->occup=cod->occup-lung.x ;		/* occupazione */
cod->sco=cod->sco+lung.x   ;
if(cod->sco > cod->fine )
	{
	parz=cod->sco - cod->fine  ; /* bytes */
	memcpy(buff,p1,(lung.x-parz));
	p1=& buff_code[cod->init] ;
	memcpy(buff+(lung.x-parz),p1,parz);
	cod->sco = cod->init+parz ;
	}			
else
	{
	memcpy(buff,p1,lung.x);               /* trasf. messaggio*/
	}
sce()  ;                                 /* riabilito lo scheduling dei TASK */
pthread_mutex_unlock(&(cod->mutex));
return(0) ;
}

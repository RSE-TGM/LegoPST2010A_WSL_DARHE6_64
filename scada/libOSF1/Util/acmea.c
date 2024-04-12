/**********************************************************************
*
*       C Source:               acmea.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Dec 16 16:10:53 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: acmea.c-4 %  (%full_filespec: acmea.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*-> acmea
	routine generale di accodamento
	coda   int indice della coda in cui inserire il messaggio
	buff   puntatore *char buffer da accodare
	lung   int numero bytes del messaggio
*/
#include <pthread.h>
#ifdef DOS
#include <pscs\rtime.inc>
#include code
#endif
#if defined OSF1 || defined LINUX
#include <code.h>
#endif

#include <memory.h>
#include <string.h>

acmea(coda,buff,lung)
char *buff      ;
int   coda ;
int   lung ;
{
char *p1 ;
int   data ;	/* buffer di appoggio */
int   parz ;
struct s_code *cod ;


scd() ;                 /*  blocco lo scehdulig dei TASK */
cod=& cd[coda] ;

pthread_mutex_lock(&(cod->mutex));

data=cod->occup+lung  ;
if(data >= cod->dim )
{	
   sce() ;                 /* riabilito lo scheduling */
	pthread_mutex_unlock(&(cod->mutex));
	return(1);			      /* coda piena */
}
cod->occup =data  ; 			      /* occupazione */
p1= &buff_code[cod->acc] ;
cod->acc=cod->acc+lung   ;
if(cod->acc > cod->fine)
	{
	parz=cod->acc - cod->fine   ; /* bytes */
	memcpy(p1,buff,(lung-parz));
	p1=& buff_code[cod->init] ;
	memcpy(p1,buff+(lung-parz),parz);
	cod->acc=cod->init+parz ;
	}			
else
	{
	memcpy(p1,buff,lung);               /* trasf. messaggio*/
	}
sce() ;                                /* riabilito lo scheduling */
pthread_mutex_unlock(&(cod->mutex));
return(0) ;
}

/*@(#)datetime.c	Date-Time			1997-04-21	*/

#include	<errno.h>
#include	<time.h>
#include	<sys/types.h>
#include	<sys/time.h>
#include	<sys/timeb.h>

/*
+-----------------------------------------------------------------------
|	datetime()
| Restituisce un puntatore ad una stringa di 20 caratteri + 1 null finale
| contenente data e ora (con centesimi di sec) in sort-format :
| 97-02-25 16:32:27.24         
| yy-mm-dd hh:mm:ss.cc
+-----------------------------------------------------------------------
*/

char*	datetime(void)
{
long*		time_p;
#ifndef LINUX
ushort_t	millitm;
#else
unsigned short	millitm;
#endif
struct	timeb	tpbf;
static	char	tmbf[22];
struct	tm 	*tm_p;

	ftime( &tpbf );
	tm_p	 	= localtime( &tpbf.time );
	(*tm_p).tm_mon++;
	millitm	= tpbf.millitm;
	millitm	/= 10;

	sprintf( tmbf, "%.2d-%.2d-%.2d %.2d:%.2d:%.2d.%.2d",
		tm_p->tm_year, tm_p->tm_mon, tm_p->tm_mday,
		tm_p->tm_hour, tm_p->tm_min, tm_p->tm_sec, millitm );

	return	tmbf;
}					/* datetime()			*/

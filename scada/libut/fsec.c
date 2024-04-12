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
#include <stdio.h>
#include <string.h>
#include <math.h>

#define GE      31
#define FE  28
#define MR      31
#define AP  30
#define MG  31
#define GI      30
#define LU      31
#define AG  31
#define SE      30
#define OT  31
#define NO  30
#define DI      31

static short coefmese_fsec[12]={ 
	0, GE, GE+FE, GE+FE+MR, GE+FE+MR+AP, GE+FE+MR+AP+MG,
       GE+FE+MR+AP+MG+GI, GE+FE+MR+AP+MG+GI+LU, GE+FE+MR+AP+MG+GI+LU+AG,
      GE+FE+MR+AP+MG+GI+LU+AG+SE, GE+FE+MR+AP+MG+GI+LU+AG+SE+OT,
                        GE+FE+MR+AP+MG+GI+LU+AG+SE+OT+NO};


double fsec_double(double,double,double,double,double,double);

/*
	restituisce i secondi in un double a partire dal 1/1/1900.
	
	ex: 12:03:47    3/4/1965

	fsec(12.0,3.0,47.0,2.0,3.0,65.0);
*/

double fsec_double(double secondi, double minuti, double ora, 
		double giorno, double mese, double anno)
{
double secondi_ret=(double)secondi;
/*
printf("fsec_double: %d:%d:%d    %d/%d/%d  ",
	(int)ora,(int)minuti,(int)secondi,(int)giorno,(int)mese, (int)anno);
*/
// test anno su due cifre
if(anno>1900)
	anno -= 1900;

// test per cambio secolo, funzionera' fino al 2050
if(anno<50)
	anno +=100;

secondi_ret = secondi_ret + 60.0*minuti;
secondi_ret = secondi_ret + 3600.0*ora;
secondi_ret = secondi_ret + giorno * 3600.0 * 24.0;
secondi_ret = secondi_ret + coefmese_fsec[(int)mese]*3600.0 * 24.0;
secondi_ret = secondi_ret + anno * 3600.0 * 24.0 * 365.0;
if((mese>1)&&(!((int)anno%4)))
	{
	//printf("calcolo bisestile ");
	secondi_ret = secondi_ret + 3600 * 24;
	}

//printf("fsec = %f\n",secondi_ret);
return(secondi_ret);
}

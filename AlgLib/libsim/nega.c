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
static char SccsID[] = "@(#)nega.c	5.1\t11/7/95";
/*
   modulo nega.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)nega.c	5.1
*/
# include <stdio.h>
# include <math.h>
#include <Rt/RtMemory.h>

int nega(float);

int nega(valore)
float valore;
{
int app;

if((int)(fabs((double)valore)+0.1)==0)
        return(1);
app=(int)(fabs((double)valore)+5.1);
app=app%2;
return(app);
}

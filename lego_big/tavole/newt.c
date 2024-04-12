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

/* ***************************************************************** *
 * ***  ROUTINE PER IL CALCOLO DELLE PROPRIETA' TERMODINAMICHE   *** *
 * ***************************************************************** */

# include <stdio.h>
# include <errno.h>
# include <math.h>
# include "tavpar.h"           /* strutture common delle tavole      */


/* ************* DEFINIZIONE VARIABILI GLOBALI ********************* */

   float (*valda)[];

   extern struct K
    {
     int id;
     int ip;
     float x[2];
     float y[2];
     int incr;
     float pae;
     float pai;
    } inte_ ;


   /* ************  DEFINIZIONE DELLA SUBROUTINE  ****************** */

 newt_(new,fonc)

   int *new;
   float *fonc;

   {
    int jj,i,j;
    float fx[2],fon[3];

    jj=inte_.id;
    if (*new>0) jj=jj+12;
    i=0;
    for (j=inte_.id; j<=jj; j+=6)
      {
       i++;
       fx[0] = ( (*valda)[j+inte_.ip-1]-(*valda)[j-1] )
               *inte_.x[0]*inte_.pai;
       fx[1] = ( (*valda)[j+2*inte_.ip-1]-(*valda)[j+inte_.ip-1] )
               *inte_.x[0]*inte_.pai;
       fon[i-1] = (*valda)[j-1]+fx[0]+(fx[1]-fx[0])
                  *inte_.x[1]*.5*inte_.pai;
      }
    if (*new>0)
      {
       fx[0] = (fon[1]-fon[0])*inte_.y[0]*inte_.pae;
       fx[1] = (fon[2]-fon[1])*inte_.y[0]*inte_.pae;
       *fonc = fon[0]+fx[0]+(fx[1]-fx[0])
               *inte_.y[1]*.5*inte_.pae;
      }
    else
      {
       *fonc=fon[0];
      }

   }   /* FINE DELLA newt_ */


   /* --------------- FINE del sorgente --------------------------- */

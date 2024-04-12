/**********************************************************************
*
*       C Source:               trova.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Wed Jun  7 12:31:06 2006 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: trova.c-10 %  (%full_filespec: trova.c-10:csrc:1 %)";
#endif

/* **************************************************************** *
 * ***  ROUTINE PER IL CALCOLO DELLE PROPRIETA' TERMODINAMICHE  *** *
 * **************************************************************** */

# include <stdio.h>
# include <errno.h>
# include <math.h>
# include "tavpar.h"           /* strutture common delle tavole     */


/* ************* DEFINIZIONE VARIABILI GLOBALI ******************** */

   float (*valda)[];

    CCO cont_ ;

   struct K
    {
     int id;
     int ip;
     float x[2];
     float y[2];
     int incr;
     float pae;
     float pai;
    } inte_ ;


   /* ************  DEFINIZIONE DELLA SUBROUTINE  ***************** */

 trova_(hd,s0)

   float *hd,*s0;

   {
    int i,j,jj;
    float aa,bb,cc,csi;
    float fx[2],fon[3];
    float sgn,qdr,rdc;
    double rdcdb;

   /* Calcola H(P0), H(P1), H(P2)                                   */
    jj=inte_.id+12;
    i=0;
    for (j=inte_.id; j<=jj; j+=6)
       {
        i=i+1;
        fx[0]=((*valda)[j+inte_.ip-1]-
               (*valda)[j-1])*inte_.x[0]*inte_.pai;
        fx[1]=((*valda)[j+2*inte_.ip-1]-
               (*valda)[j+inte_.ip-1])*inte_.x[0]*inte_.pai;
        fon[i-1]=(*valda)[j-1]+fx[0]+
                 (fx[1]-fx[0])*inte_.x[1]*.5*inte_.pai;
       }

   /* Inversione interpolazione in s
      Calcola sd, y[0], y[1]                                        */

    aa=fon[2]-2.*fon[1]+fon[0];
    bb=(-aa)+2.*fon[1]-2.*fon[0];
    cc=(-2.)*(*hd-fon[0]);
    if (bb<0.)   sgn=(-1.);
    else         sgn=1.;
    qdr=bb*bb-4.*aa*cc;
    rdcdb=sqrt((double) qdr);
    rdc=rdcdb;
    csi=(-2.)*cc/(bb+sgn*rdc);
    cont_.sd=(*s0)+csi/inte_.pae;
    inte_.y[0]=cont_.sd-(*s0);
    inte_.y[1]=inte_.y[0]-1./inte_.pae;

   }   /* FINE DELLA trova_ */


   /* --------------- FINE del sorgente --------------------------- */

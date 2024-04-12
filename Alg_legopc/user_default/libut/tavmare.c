/***********************************************************************/
//
// TAVOLE DELL'ACQUA DI MARE -  09.01.2001
//
// Last modified:  06/02/01 
// Last modified:  09/02/01 Introduction of the FISIA correlation in the
//                          Tmare_H subroutine
//
/***********************************************************************/

#include <stdio.h>
#include <math.h>

#include "tavmare.h"

/***********************************************************************/

/* Calcolo della viscosita' cinematica in CS */

float VISCmare_T() {

/* in gradi K */

float visc;

 visc = 463.e-6;

 return(visc);

}

/***********************************************************************/

/* Calcolo del calore specifico a pressione costante = calore specifico a
   volume costante in funzione della frazione massica di NaCl*/

float CSmare_F( float fnacl )
{
   
 float cs;
 
 cs = c0 + c1 * fnacl + c2 * fnacl * fnacl;
 
 return(cs);
}

/***********************************************************************/

/* Calcolo del calore specifico a pressione costante tramite la 
   correlazione della FISIA                                            */

float Cp_FISIA( float fnacl, float t ) {

/* fnacl  Frazione massica di NaCl nella salamoia  [kg/kg]   
   t      Temperatura della salamoia               [K]       
   Cp     Calore specifico a pressione costante    [J/kg/.C] 
   Tc     Temperatura della salamoia               [.C]      
   S      Frazione massica di NaCl nella salamoia  [g/kg]    */

 float Cp , Tc , S                                                   ;
 
 S  = 1000 * fnacl                                                   ;
 
 Tc = t - 273.15                                                     ;
 
 Cp = (   ( 4.185E+0 - 5.381E-3 * S + 6.260E-6 * S * S ) 
        - ( 3.055E-5 + 2.774E-6 * S - 4.318E-8 * S * S ) * Tc
        + ( 8.844E-7 + 6.527E-8 * S - 4.003E-10* S * S ) * Tc * Tc
      ) * 1000.                                                      ;
 
 return(Cp)                                                          ;
}

/***********************************************************************/

/* Calcolo dell'energia interna per unita' di massa in funzione della
   temperatura  e della frazione massica di NaCl */

float Umare_F( float t, float f ) {

/* in gradi K */


 float u, cs, temp_c;

 cs = CSmare_F(f);

 temp_c = t - ZERO_C;
 
 u = URIF  + cs * (temp_c - TRIF)  + K * f;

 return(u);
}

/***********************************************************************/

/* Calcolo dell'entalpia specifica in funzione della temperatura e della
   frazione massica di NaCl 
   La correlazione utilizzata viene scelta in funzione del parametro 
   FISIA definito nel file tavmare.h                                   */

float Hmare( float temp,
             float p,
             float ro,
             float fnacl) {

/* temp   Temperatura della salamoia               [K]    
   p      Pressione della salamoia                 [Pa]   
   ro     Densita della salamoia                   [kg/m3]   
   fnacl  Frazione massica di NaCl nella salamoia  [kg/kg]   
   u      Energia interna per unita' di massa      [J/kg]
   h      Entalpia specifica per unita' di massa   [J/kg]
   Tc     Temperatura della salamoia               [.C]     
   Cp     Calore specifico a pressione costante    [J/kg/.C] */


 float h, u, Cp, Tc                ;

 
 if      ( FISIA == 0. )  {
 
    u  = Umare_F(temp,fnacl)       ;

    h  = HRIF + (u-URIF) + p/ro    ;
 
 }
 
 else if ( FISIA == 1. )  {   
 
    Tc =  temp - 273.15            ; 
 
    Cp = Cp_FISIA(fnacl,temp)      ;
    
    h  = Cp * Tc                   ; 
 
 }                                 

 return(h)                         ;

}

/***********************************************************************/

/* Calcolo della densita' in funzione della frazione massica di NaCl
   nell'ipotesi di fluido incomprimibile */

float ROmare_F( float fnacl ) {

 float v, ro;

 v = a0 + a1 * fnacl + a2 * fnacl * fnacl;

 ro = 1/v;

 return(ro);
}

/***********************************************************************/

/* Calcolo della densita' in funzione della frazione massica di NaCl
   nell'ipotesi di fluido comprimibile */

float ROcmare_F( float fnacl, float t, float p ) {

 float v, ro, temp_c;
 float beta, k, dummy;

/* p in Pa, t in K */

/* comprimibilita' isoterma in [Pa^-1] */
 k = 3.2E-10;

/* dilatazione volumetrica in [C^-1] */
 beta = 4.82E-4;

 temp_c = t - ZERO_C;

 dummy = beta*(temp_c-60)-k*(p-PRIF);

 v = (a0+a1*fnacl+a2*fnacl*fnacl)*exp(dummy);

 ro = 1/v;

 return(ro);
}

/***********************************************************************/

/* Calcolo dell'entropia per unita' di massa in funzione della
   temperatura */

float Smare_T( float temp, float fnacl ) {

/* in gradi K */


 float s, cv, dummy;

 cv = CSmare_F(fnacl);

 dummy = temp / (TRIF+ZERO_C);

 s = SRIF  + cv * log( dummy );

 return(s);

}

/***********************************************************************/

/* Calcolo della temperatura in funzione dell'entalpia specifica */

float Tmare_H( float press, float ental, float fnacl ) {

/* in gradi K */


 float t, cv, ro, pbar;
 float S,H1,Tc,dhdt1,t2;
 int i;

 cv = CSmare_F(fnacl);
 ro = ROmare_F(fnacl);
 t = (ental - K * fnacl - press / ro) / cv + TRIF + ZERO_C;
 
 if (FISIA == 1) {
  
    S  = 1000 * fnacl;  
    for (i=0;i<2;i++) {
       H1    = Hmare(t,press,ro,fnacl);
       Tc    = t - 273.15;
       dhdt1 = (   ( 4.185E+0 - 5.381E-3 * S + 6.260E-6 * S * S ) 
           -   2 * ( 3.055E-5 + 2.774E-6 * S - 4.318E-8 * S * S ) * Tc
           +   3 * ( 8.844E-7 + 6.527E-8 * S - 4.003E-10* S * S ) * Tc * Tc
               ) * 1000.;
       t2    = t + (ental - H1) / dhdt1;
       t     = t2;
    }
 }

 return(t);
}

/***********************************************************************/

/* Calcolo della temp. saturaz. in funz. della press. e di fnacl */

float Tsatmare( float press, float fnacl ) {

/* in gradi K */

 float t, dummy, dummy2;

 dummy = 1 - (2*fnacl/PMNaCl)/(2*fnacl/PMNaCl+(1-fnacl)/PMH2O);

 dummy2 = press / (1.E5 * dummy);

 t = B / (A - log( dummy2 )) - C + ZERO_C;

 return(t);
}

/***********************************************************************/

/* Calcolo della temperatura salamoia in funzione di entropia e fnacl */

float TSmare( float s, float fnacl ) {

/* in gradi K */

 float ts, cv;

 cv = CSmare_F(fnacl);
 ts = (TRIF+ZERO_C)*exp(s/cv);

 return(ts);

}

/***********************************************************************/

/* Calcolo della derivata della densita' rispetto alla pressione k in Pa^-1 */

float DRODPmare_F( float ro )
 {

/* temp in gradi K; ro in kg/m^3 */


 float drodp, k;

/* k in [Pa^-1] */
 k = 3.2E-10;

 drodp = ro * k;

 return(drodp);
}

/***********************************************************************/

/* Calcolo della derivata della densita' rispetto all'entropia */

float DRODSmare ( float ro,
                  float t,
                  float fnacl )
 {

/* temp in gradi K; ro in kg/m^3 */


 float drods, beta, cv;

 beta = 4.82E-4;
 cv = CSmare_F ( fnacl );
 drods = - ro * beta * t / cv;

 return(drods);
}

/***********************************************************************/

/* Calcolo della derivata della Tsat rispetto alla pressione */

float DTsatDPmare( float press, float fnacl ) {

/* in gradi K */

 float dtdp, dummy, pbar, dummy2, dummy3;

 pbar = press / 1.E5;

 dummy = 1 - (2*fnacl/PMNaCl)/(2*fnacl/PMNaCl+(1-fnacl)/PMH2O);

 dummy2 = pbar / dummy;

 dummy3 = A - log( dummy2 );

 dtdp = B / (press*dummy3*dummy3);

 return(dtdp);
}

/***********************************************************************/

/* Calcolo della derivata della Tsat rispetto alla fraz. massica */

float DTsatDFmare( float press, float fnacl ) {

/* in gradi K */

 float dtdf, dummy, dummy2, pbar, dummy3, dummy4, dummy25;

 pbar = press / 1.E5;

 dummy25 = 2*fnacl/PMNaCl+(1-fnacl)/PMH2O;
 
 dummy = 1 - (2*fnacl/PMNaCl)/dummy25;

 dummy2 = (2/PMNaCl)/((1-fnacl)*dummy25);

 dummy3 = pbar / dummy;
 
 dummy4 = A - log( dummy3 );

 dtdf = (B*dummy2) / (dummy4*dummy4);

 return(dtdf);
}

/***********************************************************************/

/* Calcolo della derivata della energia interna di saturazione rispetto
   alla pressione */

float DUDPmaresat ( float press, float fnacl )
 {

 float dudp, cv, dtdp;

 cv = CSmare_F(fnacl);
 dtdp = DTsatDPmare (press,fnacl);
 dudp = cv * dtdp;

 return(dudp);
}

/***********************************************************************/

/* Calcolo della derivata dell'entalpia di saturazione rispetto alla
   pressione */

float DHsatDFmare( float press, float temp, float fnacl ) {

 float dtdf, dcvdf, dv0df, pbar, dhdf, cv, tsal;
 float dcpdf,dcpdt,S,Tc,Cp;

 if (FISIA == 0) {

    pbar = press / 1.E5;
    dcvdf = c1 + 2 * c2 * fnacl;
    dv0df = a1 + 2 * a2 * fnacl;
    dtdf = DTsatDFmare(press,fnacl);
    cv = CSmare_F(fnacl);
    tsal = Tsatmare(press,fnacl);
    dhdf = cv * dtdf + (tsal - ZERO_C - TRIF) * dcvdf + K + pbar * dv0df;
 
 } else if (FISIA == 1) {
 
    S  = 1000 * fnacl;
    Tc = temp - 273.15;
    dcpdf = (   ( - 5.381E-3 + 2 * 6.260E-6 * S )
              - (  2.774E-6 - 2 * 4.318E-8 * S ) * Tc
              + (  6.527E-8 - 2 * 4.003E-10* S ) * Tc * Tc
            ) * 1.E6;
    dcpdt = ( - ( 3.055E-5 + 2.774E-6 * S - 4.318E-8 * S * S ) 
              + 2 * ( 8.844E-7 + 6.527E-8 * S - 4.003E-10* S * S ) * Tc
            ) * 1000.;  
    dtdf = DTsatDFmare(press,fnacl);
    Cp=Cp_FISIA(fnacl,temp);
    dhdf=(dcpdf+dcpdt*dtdf)*Tc+Cp*dtdf;
 
 }

 return(dhdf);

}

/*********** FORTRAN INTERFACE FUNCTIONS *******************************/

void VISC_FOR( float *visc )
{
 *visc = VISCmare_T();
}

/***********************************************************************/

void CS_FOR( float *fnacl, float *cs )
{
 *cs = CSmare_F(*fnacl);
}

/***********************************************************************/

void CP_FOR( float *fnacl, float *t, float *Cp )
{
 *Cp = Cp_FISIA(*fnacl, *t);
}

/***********************************************************************/

void U_FOR( float *t, float *fnacl, float *u )

{
 *u = Umare_F(*t, *fnacl);
}

/***********************************************************************/

void H_FOR( float *t, float *p, float *ro, float *fnacl, float *h )

{
 *h = Hmare(*t, *p, *ro, *fnacl);
}

/***********************************************************************/

void RO_FOR( float *fnacl, float *ro )

{
 *ro = ROmare_F(*fnacl);
}

/***********************************************************************/

void ROC_FOR( float *fnacl, float *t, float *p, float *ro)

{
 *ro = ROcmare_F(*fnacl, *t, *p);
}

/***********************************************************************/

void S_FOR(float *t, float *fnacl, float *s)

{
 *s = Smare_T(*t, *fnacl);
}
 
/***********************************************************************/

void T_FOR( float *p, float *h, float *fnacl, float *t )

{
 *t = Tmare_H( *p, *h, *fnacl );
}

/***********************************************************************/

void TSAT_FOR( float *p, float *fnacl, float *tsat )

{
 *tsat = Tsatmare(*p, *fnacl);
}

/***********************************************************************/

void TS_FOR(float *s, float *fnacl, float *ts)

{
 *ts = TSmare( *s, *fnacl );
}

/***********************************************************************/

void DRDP_FOR(float *ro, float *drdp)

{
 *drdp = DRODPmare_F( *ro );
}

/***********************************************************************/

void DRDS_FOR(float *ro, float *t, float *fnacl, float *drds)

{
 *drds = DRODSmare( *ro, *t, *fnacl);
}

/***********************************************************************/

void DTSATDP_FOR(float *p, float *fnacl, float *dtsatdp)

{
 *dtsatdp = DTsatDPmare( *p, *fnacl );
}

/***********************************************************************/

void DTSATDF_FOR(float *p, float *fnacl, float *dtsatdf)

{
 *dtsatdf = DTsatDFmare( *p, *fnacl );
}

/***********************************************************************/

void DUSATDP_FOR(float *p, float *fnacl, float *dusatdp)

{
 *dusatdp = DUDPmaresat ( *p, *fnacl );
}

/***********************************************************************/

void DHSATDF_FOR(float *p, float *t, float *fnacl, float *dhsatdf)

{
 *dhsatdf = DHsatDFmare ( *p, *t, *fnacl );
}

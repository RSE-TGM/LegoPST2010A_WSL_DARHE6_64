/*
   modulo tavpar.h
   tipo 
   release 1.2
   data 2/6/95
   reserved @(#)tavpar.h	1.2
*/
/* ***************************************************************** *
 * ***     DEFINIZIONI DELLE STRUTTURE COMMON DELLE TAVOLE       *** *
 * ***************************************************************** */

   struct B
    {
     float prt[33];
     float pap[32];
     int ic[32];
     int ioffset[32];
    };

   struct common_cont
    {
     float pd;
     float sd;
    };

   struct D
    {
     int ii;
     int kk;
     int klim;
     int i0;
     float s[5];
    };

   struct E
    {
     double a[5];
     double b[3];
     double c[3];
     double d[3];
     double coe1;
     double coe2;
     double coe3;
     double eta1;
     double eta2;
     float et1[14];
     float et2[14];
     float et3[14];
     float et4[10];
    };

   struct F
    {
     float pts[23];
     float tes[14];
    };

   struct G
    {
     double ck[9];
    };

   struct H
    {
     double pa[5];
     double pb[4];
     double pc[4];
     float ale[9];
     float alv[10];
     float al2[21];
     double alam;
     double albm;
     double alcm;
    };

typedef struct common_cont  CCO ;


   /* ------------------------------------------------------------- */

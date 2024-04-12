/***********************************************************************/
//
// TAVOLE DELL'ACQUA DI MARE -  09.01.2001
//
// Modificata il 26/01/01 per introduzione del parametro FISIA
//
/***********************************************************************/

# define ZERO_C     273.15          /* zero ^C in K */

# define TRIF       0.01            /* temp. di rif. in ^C */
# define PRIF       1.e5            /* pressione di rif. in Pascal */
# define URIF       0.0             /* energia interna per t = TRIF */
# define SRIF       0.0             /* entropia per t = TRIF */
# define HRIF       0.0             /* entalpia per t = TRIF e p = PRIF */

# define FISIA      1.              /* Correlazione utilizzata per il 
                                       calcolo dell'entalpia 
                                       0 = correlazione CESI
                                       1 = correlazione FISIA          */

# define c0        4186
# define c1       -4340.96
# define c2        5165.45

# define K        83390.45

# define a0       0.001017
# define a1      -0.0006841
# define a2       0.0001823

# define ba       2509508.905
# define b0       1662.512

# define d0       1886.9833
# define d1      -1.3644
# define d2       0.0263

# define A        11.739
# define B        3857.196
# define C        228.911

# define PMNaCl   58.43
# define PMH2O    18

# define e0       0.320781
# define e1       -0.017206
# define e2       0.000306

# define i0       10.395
# define i1       -3560.323
# define i2       226.343

// Prototipi funzioni effettive (di calcolo)

float CSmare_F(float);
float Cp_FISIA(float,float);
float Umare_F(float,float);
float Hmare( float, float, float, float); 
float ROmare_F( float );
float ROcmare_F( float, float, float );
float Smare_T( float, float );
float Tmare_H( float, float, float );
float VISCmare_T(void);
float Tsatmare(float,float);
float TSmare(float, float);
float DRODPmare_F(float);
float DRODSmare(float,float,float);
float DTsatDPmare(float,float);
float DTsatDFmare(float,float);
float DUDPmaresat (float,float);
float DHsatDFmare(float,float,float);

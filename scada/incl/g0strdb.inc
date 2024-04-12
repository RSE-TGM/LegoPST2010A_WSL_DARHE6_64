/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
	definizione delle strutture delle tabelle
	di data base
*/

#include "g0gerdb.inc"
#include "g3calcdb.inc"
#include "all_1.h"

union valin {
                float  fval;
                short  sval[2];
                char   cval[4];} ;
/*
        definizione struttura tabelle allarmi
*/
typedef struct allarmi {
                short tr_bdm ;
        union   valin alto_sic ;
        union   valin alto_con ;
        union   valin bass_con ;
        union   valin bass_sic ; } S_DBALL;  

#define di_cont 4     /* contribuenti */
#define di_inib 2     /* inibiti */

typedef struct cal_in  {
                char tipo_cont[di_cont] ;
                short cont [di_cont];
                char tipo_inib[di_inib];
                short tin_an;        	    /*tipo di inibi. analogici*/
                short inib[di_inib];  } S_CALIN ;

/*
	analogici acquisiti
*/	
#define S_DBAAV  float         /* valori        */
#define S_DBAAF  short         /* flag         */
#define S_DBAAU  char          /* zona impianto*/
#define S_DBAAFA char          /* flag acquisizione */

#define t_dbaa   (sizeof(S_DBAAV)+sizeof(S_DBAAF)+sizeof(S_DBAAU)+sizeof(S_DBAAFA)+sizeof(S_DBALL))
/*
        analogici calcolati standard
*/
#define S_DBASV  float          /* valori        */
#define S_DBASF  short          /* flag         */
#define S_DBASU  char           /* zona impianto*/

#define t_dbas   (sizeof(S_DBASV)+sizeof(S_DBASF)+sizeof(S_DBASU)+sizeof(S_DBALL)+sizeof(DES))
/*
        analogici calcolati non standard
*/
#define S_DBACV  float          /* valori        */
#define S_DBACF  short          /* flag         */
#define S_DBACU  char           /* zona impianto*/

#define t_dbac   (sizeof(S_DBACV)+sizeof(S_DBACF)+sizeof(S_DBACU)+sizeof(S_DBALL))
/*
        analogici di diagnostica
*/
#define S_DBADV  float          /* valori        */
#define S_DBADF  short          /* flag         */
#define S_DBADU  char           /* zona impianto*/

#define t_dbad   (sizeof(S_DBADV)+sizeof(S_DBADF)+sizeof(S_DBADU)+sizeof(S_DBALL))
/*
        analogici di uscita
*/
#define S_DBAOF  short          /* flag         */
#define S_DBAOU  char           /* zona impianto*/
#define S_DBAOM  char           /* indice star assosiata */

#define t_dbao   (sizeof(S_DBAOF)+sizeof(S_DBAOU)+sizeof(S_DBAOM))

#define ds_cont  4                      /* contribuenti ai calcolati */

typedef struct s_dcalc {
        short   tipc;           /*tipo calcolata        */
        char    ext[ds_cont];   /*tipo contribuenti     */
        short   punt[ds_cont];  /*puntatore contribuenti        */
        } S_DCALC;

/*
        digitali acquisiti
*/
#define S_DBDA   short          /* flag e trattamento        */
#define S_DBDATR short          /* trattamento               */
#define S_DBDAU  char        	 /* zona impianto             */

#define t_dbda   (sizeof(S_DBDA)+sizeof(S_DBDATR)+sizeof(S_DBDAU)+sizeof(S_CALIN))
/*
        digitali calcolati standard
*/
#define S_DBDS   short          /* flag e trattamento        */
#define S_DBDSTR short          /* trattamento               */
#define S_DBDSU  char        	 /* zona impianto             */

#define t_dbds   (sizeof(S_DBDS)+sizeof(S_DBDSTR)+sizeof(S_DBDSU)+sizeof(S_CALIN)+sizeof(S_DCALC))
/*
        digitali calcolati non standard
*/
#define S_DBDC   short          /* flag e trattamento        */
#define S_DBDCTR short          /* trattamento               */
#define S_DBDCU  char        	 /* zona impianto             */

#define t_dbdc   (sizeof(S_DBDC)+sizeof(S_DBDCTR)+sizeof(S_DBDCU)+sizeof(S_CALIN))
/*
        digitali di diagnostica
*/
#define S_DBDD   short          /* flag e trattamento        */
#define S_DBDDTR short          /* trattamento               */
#define S_DBDDU  char        	 /* zona impianto             */

#define t_dbdd   (sizeof(S_DBDD)+sizeof(S_DBDDTR)+sizeof(S_DBDDU)+sizeof(S_CALIN))
/*
        digitali di uscita
*/
#define S_DBDO   char           /* flag e trattamento        */
#define S_DBDOU  char        	 /* zona impianto             */
#define S_DBDOM  char           /* indice star associata     */

#define t_dbdo   (sizeof(S_DBDO)+sizeof(S_DBDOU)+sizeof(S_DBDOM))
/*
        definizione della struttura del descrittore degli
        organi
*/
#define or_inib 2               /* n. max. misure inibite       */
#define or_cont 5               /* n. max digitali contribuenti */
struct punto_inibito {  char tipin ;
                        char ext ;
                        short punt ;};
typedef struct s_desorg {  char trat;
                           char tipo ;
                           char ext[or_cont];
                           char spare;
                           short punt[or_cont] ;
                           char  stprot ;
                           char  time_out ;
                           char  funz ;
                           char  stinib ;
               struct punto_inibito pinib[or_inib] ;
                           short attiv  ;
                        } S_DESORG ;
#if defined (g0dimor)
typedef union u_time    {  char tc[g0dimor] ;
                           int ti[g0dimor/4] ;} U_TIME ;
#endif
/*
        organi
*/
#define S_DBOSC	short         /* stato corr. e flag */
#define S_DBOSA char          /* stato atteso       */
#define S_DBOSP char          /* stato precedente   */
#define S_DBTO  char          /* time out     */
#define S_DBOU  char          /* zona impianto */
#define S_DBOFT char          /* flag time-out */

#define t_dbor   (sizeof(S_DBOSC)+sizeof(S_DBOSA)+sizeof(S_DBOSP)+sizeof(S_DBTO)+sizeof(S_DBOU)+sizeof(S_DBOFT)+sizeof(S_DESORG))
/*
	stringhe
*/
#define g0lunst 16			/* lunghezza max. stringa */

#define S_DBSTTR char           	/* trattamento */
#define S_DBSTU  char			/* zona di impianto       */
#define S_DBSTV  char			/* valore	      */

#define t_dbst   (sizeof(S_DBSTTR)+sizeof(S_DBSTU)+(sizeof(S_DBSTV)*g0lunst))
#include "all_16.h"

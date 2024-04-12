/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*      file di include g3calcdb.inc contiene la
        definizione delle strutture che definiscono
        i diversi tipi di calcolata per gli analogici
        calcolati standard

        sono inoltre messi in union
        
	Revisioni :  1.06.92  -  GM Furlan
	             Strutture C_AMMM e C_INTEGRALE in doppia precisione

*/

#include <all_1.h>
#define num_somma 8
#define num_media 6
#undef long 
#define long int
typedef struct  puntatore {     short ext ;
                                short punt;} PUNTATORE;

/*      descrittore della calcolata:    1_ media
                                        2_ massimo
                                        3_ minimo
*/
typedef struct c_ammm {         unsigned char    periodo ;       /* scansione*/
                                char    tipoc ;
                                short   link;
                                PUNTATORE indice;       /*contribuente*/
                                short   freq ;
                                long    cont_err;
                                long    cont_camp;      /*cont.campioni*/
				   double  savev;     	   /* valore salvato */
				   short   savef;	   /* fa salvato	  */
               }C_AMMM ;

/*      descrittore della calcolata :   4_ integrale
                                        5_ accumulo
*/
typedef struct c_integrale {    unsigned char    periodo;
                                char    tipoc ;
                                short   link;
                                PUNTATORE  indice ;
                                short   freq ;
                                long    cont_err ;
				   double  savev;     	    /* valore salvato */
				   short   savef;	    /* fa salvato	  */
                                short   time;
                                long    cont_camp;       /*cont.campioni*/
               }C_INTEGRALE ;

/*      descrittore della calcolata :   6 - 7 portata
*/
typedef struct c_portata   {    unsigned char periodo;
                                char tipoc ;
                                short   link;
                                PUNTATORE  Dp ;
                                PUNTATORE  press ;
                                PUNTATORE  temper;
                                float cost1;
                                float cost2;
                                long  cont_err ;
                   }C_PORTATA;

/*      descrittore calcolata : 8_ filtro
*/
typedef struct c_filtro    {    unsigned char periodo;
                                char tipoc ;
                                short   link;
                                PUNTATORE misura;
                                short cost1;
                                long  cont_err ;
                   }C_FILTRO;

/*      descrittore della calcolata: 9_ media
*/
typedef struct c_media     {    unsigned char periodo;
                                char tipoc ;
                                short   link;
                                PUNTATORE misura[num_media];
                                long  cont_err ;
                   }C_MEDIA;

/*      descrittore della calcolata :   10_ operazioni
*/
typedef struct c_operaz    {    unsigned char periodo;
                                char tipoc ;
                                short   link;
                                PUNTATORE  misura;
                          union cost_mis{PUNTATORE  misura;
                                        float cost; } c_m;
                                short oper ;
                                long  cont_err ;
                   }C_OPERAZ;

/*      descrittore della calcolata :   11_ somma
*/
typedef struct c_somma     {    unsigned char periodo;
                                char tipoc ;
                                short   link;
                                short ind_misure[num_somma];
                                char tip_misure[num_somma];
                                long  cont_err ;
                   }C_SOMMA;

/*      descrittore della calcolata :   12_ scarto quadratico
*/
typedef struct c_scarto    {    unsigned char periodo;
                                char tipoc ;
                                short   link;
                                PUNTATORE  misura;
                                short freq;
                                float somma_q ;
                                float somma_i ;
                                long cont_cv; /*cont. contrib.validi*/
                                long cont_ctot ;/*contrib. totali*/
				float savev;     	/* valore salvato */
				short savef;		/* fa salvato	  */
                   }C_SCARTO;

/*      descrittore della calcolata :   13_ organi
*/
typedef struct c_organi    {    unsigned char periodo;
                                char tipoc ;
                                short   link ;
                                PUNTATORE  organo ;
                                short stato;
                   }C_ORGANO;

/*      descrittore della calcolata :   14_ ore misura
*/
typedef struct c_oremisura {    unsigned char periodo;
                                char tipoc ;
                                short   link;
                                PUNTATORE  misura;
                          union val_so{PUNTATORE  soglia;
                                      float  val; } v_s;
                   }C_OREMISURA;

/*	descrittore della calcolata:	15_ gerarchia allarmi pendenti
					16_ gerarchia allarmi in archivio
*/
#ifdef GERARC

#define AS_GERARCHIA_ALLPENDENTI	15
#define AS_GERARCHIA_ALLARCHIVIATI	16

typedef struct c_gerarchia {	unsigned char periodo;
                                char          tipoc ;
                                short         link;  	/*indice della calcolata */
				S_DBGERA      gerac;	/* Livelli della gerarchia */
				char	      sZona;	/* Zona */
				char	      sDbAll;	/* N. data base allarmi */
                                long  cont_err ;
#ifdef ALARM_SIGNAL
				char          sTipoAll; /* eventuale tipo di 
							   allarme/segnale
							   -1 funzionamento
							   normale           */
#endif
} C_GERARCHIA;
#endif

typedef union des {     struct c_ammm       a ;
                        struct c_integrale  i ;
                        struct c_portata    p ;
                        struct c_filtro     f ;
                        struct c_media      m ;
                        struct c_operaz     o ;
                        struct c_somma      s ;
                        struct c_scarto     q ;
                        struct c_organi     r ;
                        struct c_oremisura  h ;
#ifdef GERARC
                        struct c_gerarchia  g ;
#endif
          } DES ;

#include <all_16.h>
#undef long
#define long long

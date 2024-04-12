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
        mesestel.inc

        Include le strutture per i messaggi di acquisizione analogica
        e digitale provenienti da linea telefonica Samp

        1 Dicembre 1992
*/
#define MESESTEL_INCL

#ifndef FILEOP_INCL
#include "fileop.inc"
#endif
#ifndef MESEST_INCL
#include "mesest.inc"
#endif

typedef struct mistime { char mese,dd,hh,mm,ss,tick;} MISTIME;

#define mdanatime 74        /* invio dati analogici	 con tempo	    */
#define mddigtime 75	/* invio dati digitali		    */
#define mdanavett 76        /* invio dati analogici   vettoriali    */

#define max_analogtime 16
#define max_digittime 17                /*  22/3/93 Catenacci era 16, corretto su input Biancalana */
#define max_analogvet 54

/*
        struttura dati analogici
*/
union f_it {	float f;
		long  l;
                char  c[4]; };
typedef struct s_dtaat {
		short point ;
		union f_it val ;
      MISTIME time;} S_DTAAT ;

typedef struct s_mdanat {
		HEASCA hea ;	
		S_DTAAT  dati[max_analogtime]; } S_DANAT ;

/*
	struttura record digitali 
*/

typedef struct s_dtdat {
                union DIG_VAL d;
                MISTIME time;} S_DTDAT ;

typedef struct s_dtdigt {
		HEASCA hea;
		S_DTDAT dig_val[max_digittime]; } S_DDIGT ;
/*
        dati vettoriali
*/
typedef struct s_dvval {
		float val ;
      short flag ;} S_DVVAL;

typedef struct s_mdanavet {
		HEASCA hea ;	
                short point;
                short camp;
                long  passo;
                MISTIME time;
       		S_DVVAL  dati[max_analogvet]; } S_DANAVET ;

#define  h_danavet (sizeof(S_DANAVET)-(sizeof(S_DVVAL)*max_analogvet))		

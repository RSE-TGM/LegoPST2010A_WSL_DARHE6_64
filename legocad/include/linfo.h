/**********************************************************************
*
*       C Header:               linfo.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:04:19 1996 %
*
**********************************************************************/
/*------------------------------------------------------
 * nome modulo:   LINFO.h
 *
 * include applicativo linfo
 *
 *------------------------------------------------------*/

#ifndef LINFO_H
#define LINFO_H

#define FNAME_CREALTM   "crealtm.dat" /* nome del file contenente la lista moduli */
#define FNAME_DESCR     "descr.dat"   /* nome del file descrizione e note modello */
#define FNAME_FORAUS_USER  "foraus.for"   /* nome fortran ausiliario utente */

#define L_NOMEMODULO    4          /* lunghezza nome del modulo */
#define L_DESCRMODULO   80         /* lunghezza max descrizione modulo */
#define L_DESCRMODELLO  80         /* lunghezza max descrizione modello */

#define PATTERN_START "C~FORAUS_"
#define PATTERN_END  "~C"

typedef struct {
                  char nome_modulo[L_NOMEMODULO+1];     /* nome del modulo */
                  char descr_modulo[L_DESCRMODULO+1];   /* descrizione */
                  char *auxftn_modulo;                    /* pointer al fortran ausiliario */
                  int rout_std;                         /* True se e' associato al modulo una routine standard */ 
                  int foraus;                         /* True se la routine std e' in foraus.for */
               } LTM; 

/* Contiene la descrizione del modello */
typedef struct {
                  char *descrizione;
               } DESCRMODELLO;


/* Contiene il file foraus.for */
typedef struct {
                  char *foraus;
               } FORAUS;

#endif

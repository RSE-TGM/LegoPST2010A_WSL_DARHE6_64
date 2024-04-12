/**********************************************************************
*
*       C Header:               OlDatabaseTopologia.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Jul 17 13:43:41 1998 %
*
**********************************************************************/
/*
   modulo OlDatabaseTopologia.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)OlDatabaseTopologia.h	5.1
*/
/*
 * OlDatabaseTopologia.h - file di include pubblico per l'utilizzo del database
 */
#ifndef _OlDatabaseTopologia_h
#define _OlDatabaseTopologia_h

#include <Rt/RtMemory.h>
#include <sim_param.h>
/*
 nomi di risorse utilizzate internamente a OlDatabaseTopologia
 */

/* costanti utilizzabili per settare i tipi di OlDatabaseTopologia */
#define DB_XLRTF	1          /* database topologia tipo *.rtf e *.edf */
#define DB_XLORACLE	2          /* database topologia sotto ORACLE       */
#define DB_XLSCADA	3          /* database topologia "light" x  SCADA   */

/* costanti per ricerca tipo e indirizzo var estratte da fnomi.rtf */
#define SCD_SIGLA               (MAX_LUN_NOME_VARS-1)      /* lunghezza della sigla dei punti*/
#define SCD_DESCRIZIONE         60  /* lunghezza della descrizione dei punti*/
#define SCD_DESCRIZIONE_ALL     24  /* lunghezza della descrizione dei punti*/
                                                     /* nella pagina allarmi */
#define SCD_DESCRIZIONE_LBG     32  /* lunghezza della descrizione dei punti*/
                                                   /* sul libro giornale */
#define SCD_UNIMIS              8
#define SCD_STATO               SCD_UNIMIS
#define SCD_TIPOR               10
/* costanti utilizzate da funzione ricerca */
#define SCD_FATBLK              512*4   /* Dimensione di un blocco */
#define SCD_BLK_OVER_FLOW   4           /* Word iniziali per overflow */
#define SCD_OVERF               0       /* Blocco di overflow cui si rimanda */
#define BLK_OVER                        16      /* N.blocchi di oberflow */
#define BLK_NORM                        541             /* N. blocchi normali */
#define BLK_TOT BLK_OVER+BLK_NORM        /* N. blocchi complessivi */
#define SCD_RECORD   (SCD_SIGLA/2+2)     /* Lunghezza record all'interno del bloco*/
#define CHAR_BIT                        8
#define BITS_IN                 (sizeof(short)*CHAR_BIT)
#define THREE_QUARTERS  ((short)((BITS_IN*3)/4))
#define ONE_EIGHT               ((short)(BITS_IN/4))
#define HIGH_BITS               (~((unsigned short)(~0)>>ONE_EIGHT))

/* dichiarazione tipi per Classe e Instanziazione di OlDatabaseTopologia */
typedef struct _OlDatabaseTopologiaClassRec *OlDatabaseTopologiaObjectClass;
typedef struct _OlDatabaseTopologiaRec *OlDatabaseTopologiaObject;

/*
	procedure utilizzabili per la creazione e la distruzione
	dell'oggetto OlDatabaseTopologia
*/
OlDatabaseTopologiaObject OlCreateDatabase();
Boolean OlDestroyDatabase();
Boolean OlGetModelBlockName();
Boolean OlVarIsFreeInput();
Boolean OlTagToIndS(OlDatabaseTopologiaObject , char * ,int *, int *);
Boolean OlTagToInd(OlDatabaseTopologiaObject , char * ,int *, int *);


#endif /* _OlDatabaseTopologia_h */


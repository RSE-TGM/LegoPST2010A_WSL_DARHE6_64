/**********************************************************************
*
*       C Header:               tag.h
*       Subsystem:              1
*       Description:
*       %created_by:    joby %
*       %date_created:  Mon Nov 10 17:04:13 1997 %
*
**********************************************************************/
/*
   Contiene le definizioni della lunghezza del nome e della descrizione
   dei punti dello SCADA; contiene i parametri per effettuare la 
   ricerca di un punto nel file fnomi.rtf.
*/
#ifndef _tag_h_
#define _tag_h_

#define SCD_SIGLA 		32  	// lunghezza della sigla dei punti
#define SCD_DESCRIZIONE		60  // lunghezza della descrizione dei punti
#ifdef OLDALARM
#define SCD_DESCRIZIONE_ALL	24  // lunghezza della descrizione dei punti
				    			// nella pagina allarmi
#endif
/*
Nuova lunghezza descriz. allarmi peer teleperm
*/
#define SCD_DESCRIZIONE_ALL	60  // lunghezza della descrizione dei punti
				    			// nella pagina allarmi
#define SCD_DESCRIZIONE_LBG	32  // lunghezza della descrizione dei punti
				    			// sul libro giornale
#define SCD_UNIMIS		8
#define SCD_STATO		SCD_UNIMIS
#define SCD_TIPOR		10

//  Per il metodo Ricerca e costruzione del file fnomi
#ifdef OLD_RICERCA

#define SCD_FATBLK  		512*4   /* Dimensione di un blocco */
#define BLK_OVER   			16    	/* N.blocchi di oberflow */
#define BLK_NORM   			256		/* N. blocchi normali */
#define BLK_TOT BLK_OVER+BLK_NORM	/* N. blocchi complessivi */

#else

#define SCD_FATBLK  		512*4   /* Dimensione di un blocco */
#define SCD_BLK_OVER_FLOW   4  		/* Word iniziali per overflow */
#define SCD_OVERF     		0     	/* Blocco di overflow cui si rimanda */
#define BLK_OVER   			16    	/* N.blocchi di oberflow */
#define BLK_NORM   			541		/* N. blocchi normali */
#define BLK_TOT BLK_OVER+BLK_NORM	/* N. blocchi complessivi */
#define SCD_RECORD   SCD_SIGLA/2+2 	/* Lunghezza record all'interno del blocco*/
#define CHAR_BIT			8
#define BITS_IN			(sizeof(short)*CHAR_BIT)
#define THREE_QUARTERS	((short)((BITS_IN*3)/4))
#define ONE_EIGHT		((short)(BITS_IN/4))
#define HIGH_BITS		(~((unsigned short)(~0)>>ONE_EIGHT))

#endif // OLD_RICERCA
#endif // _tag_h_

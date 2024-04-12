/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef RISORSE_DEFAULT_H
#define RISORSE_DEFAULT_H

#define MAX_RES_STR_LUN		50		/* max lunghezza stringa risorse */
/*
 * definizione della struttura risorse
 */
struct resDefSt
	{
	char categoria[MAX_RES_STR_LUN];	/* categoria per display	*/
	int  catIndx;							/* indice di categoria		*/
	char label[MAX_RES_STR_LUN];		/* stringa per display 		*/
	char risorsa[MAX_RES_STR_LUN];	/* nome della risorsa		*/
	char classe[MAX_RES_STR_LUN];		/* nome della classe			*/
	char valore[MAX_RES_STR_LUN];		/* valore di settaggio		*/
	char valoreDef[MAX_RES_STR_LUN];	/* valore di default			*/
	};
typedef struct resDefSt RESOURCE_DEF;

#endif

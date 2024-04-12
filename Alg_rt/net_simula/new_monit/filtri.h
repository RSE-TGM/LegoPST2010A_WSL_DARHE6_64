/**********************************************************************
*
*       C Header:               filtri.h
*       Subsystem:              3
*       Description:
*       %created_by:    zanna %
*       %date_created:  Fri Jun  6 16:38:21 1997 %
*
**********************************************************************/
/*
 * filtri.h
 */
/*
#ifndef FILTRI_INCLUDED_
#define FILTRI_INCLUDED_
*/
/*********************************************************************/
#include "malfunzioni.h"

#define PREVIEW_CALLING			MAX_CODICE_MALF + 1
#define AING_CALLING				MAX_CODICE_MALF + 2


#define FILTER_ALL_VAR        1
#define FILTER_MOD_BLOC       2
#define FILTER_MOD_ONLY       3
#define FILTER_KKS            4
#define FILTER_TYPE           5

#define MAX_NUM_TIPI 			12

#define FLAG_TIPO_PRESSIONE	"P"
#define FLAG_TIPO_TEMPERATURA	"T"
#define FLAG_TIPO_TEMPERATURA_X	"X"
#define FLAG_TIPO_ENTALPIA		"H"
#define FLAG_TIPO_PORTATA		"W"
#define FLAG_TIPO_POTENZA		"Q"
#define FLAG_TIPO_GIRI			"OM"
#define FLAG_TIPO_GIRI_RPM		"RPM"
#define FLAG_TIPO_ALZVALV		"ALZ"

#define FLAG_TIPO_INPUT       "--IN--"
#define FLAG_TIPO_OUTPUT      "--UA--"

struct filtro_tipi_st
	{
	int pressione;
	int temperatura;
	int entalpia;
	int portata;
	int potenza;
	int giri;
	int alzvalv;
	int ingressi;
	int uscite;
	int aingabili;
	};
typedef struct filtro_tipi_st FILTRO_TIPI;

#define FILTRO_CR			1	/* chiamata da selVarCr	*/
#define FILTRO_CR2		3	/* chiamata da selVarCr	da frame (non menu)*/
#define FILTRO_VAR      2  /* chiamata da selVar   */
#define FILTRO_VAR2     4  /* chiamata da selVar da frame (non menu)  */
#define FILTRO_MALF 		5	/* chiamata da selVar per malfunz.			 */
#define FILTRO_FREM 		6  /* chiamata da selVar per frem             */
/*********************************************************************/
/*#endif */

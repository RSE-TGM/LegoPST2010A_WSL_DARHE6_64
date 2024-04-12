/**********************************************************************
*
*       C Header:               buffer_mffr.h
*       Subsystem:              3
*       Description:
*       %created_by:    carlo %
*       %date_created:  Fri Nov 15 12:05:58 1996 %
*
**********************************************************************/
/*
   modulo buffer_mffr.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)buffer_mffr.h	5.1
*/
/*********************************************************************/
/*
 *  buffer_mffr.h             buffer dati per malfunzioni e funzioni
 *                            remote per comunicazione con skedulatore
 *
 *  struttura dati relativa a bi legograf
 * 30jan95 :modifiche per bi monit 
 *          non viene salvata la descrizione delle variabili
 *          le strutture sono relative ai dati salvati con gli snapshot
 */
#ifndef MAX_FR_SOMM
#define MAX_FR_SOMM    40         /* max numero fr in sommario       */
#define MAX_MF_SOMM    40         /* max numero mf in sommario       */
#endif
/*                                                                   */
/*  segmento readfr  (sommario fr)                                   */
/*                                                                   */

struct readfr_st
	{
	char nome_fr [MAX_FR_SOMM] [9];  /* nome funzione remota in sommario */
	int address[MAX_FR_SOMM];        /* puntatore in shared memory       */
	float vdef_fr [MAX_FR_SOMM];     /* valore di default                */
	float ramp_fr[MAX_FR_SOMM];      /* rampa                            */
	float sevf_fr[MAX_FR_SOMM];      /* valore target                    */
	float vatt_fr [MAX_FR_SOMM];     /* valore attuale                   */
	char satt_fr [MAX_FR_SOMM] [4];  /* stato attuale                    */
	int  occupato [MAX_FR_SOMM];     /* posizione usata                  */
	int ul_fr;                       /* numfr in sommario                */
	int flg_modf;                    /* flag sommario modificato         */

/**	char vatt_fr [MAX_FR_SOMM] [9];*/  /* valore attuale                   */
/**	short vmin_fr [MAX_FR_SOMM];  */   /* valore minimo                    */
/**	short vmax_fr [MAX_FR_SOMM];  */   /* valore massimo                   */
/**	short ia_fr   [MAX_FR_SOMM];  */   /* indice array per stampe          */
/**	short ia_frb  [MAX_FR_SOMM];  */   /* puntatore in b-lego.dat          */
/**	short flg_frca[MAX_FR_SOMM];  */   /* marcatura fr per delete          */
/**	short flg_frdi[MAX_FR_SOMM];  */   /* marcatura per disattivazione     */
/**	short ramp_fr[MAX_FR_SOMM];   */  /* rampa                            */
/**	char des_fr  [MAX_FR_SOMM] [25];*/ /* descrizione                      */
/**	char um_fr   [MAX_FR_SOMM] [9]; */ /* unita' di misura                 */
/**	char vdef_fr [MAX_FR_SOMM] [9]; */ /* valore di default                */
/*	short sevf_fr[MAX_FR_SOMM]; */    /* valore target                    */
/**	short ul_fr;            */   /* numfr in sommario               */
/**	short flg_modf;         */   /* flag sommario modificato            */
	} ;
/*                                                                   */
/*  segmento readmf  (sommario mf)                                   */
/*                                                                   */

struct readmf_st
	{
	char nome_mf [MAX_MF_SOMM] [9];  /* nome funzione remota in sommario*/
	int address[MAX_MF_SOMM];        /* puntatore in shared memory      */
	float vdef_mf[MAX_MF_SOMM];      /* valore di default               */
	float dstr_mf[MAX_MF_SOMM];      /* delay allo start                */
	float dur_mf [MAX_MF_SOMM];      /* durata                          */
	float ramp_mf[MAX_MF_SOMM];      /* rampa                           */
	float sevf_mf[MAX_MF_SOMM];      /* severita' finale                */
	float vatt_mf [MAX_MF_SOMM];     /* valore attuale                  */
	int  occupato [MAX_MF_SOMM];     /* posizione usata                  */
	char satt_mf [MAX_MF_SOMM] [4];  /* stato attuale                   */
	int ul_mf;                       /* numero mf in sommario           */
	int flg_modm;                    /* flag sommario modificato        */

/**	short ia_mf   [MAX_MF_SOMM]; */   /* indice array per stampe         */
/**	short ia_var  [MAX_MF_SOMM]; */   /* indice array variabili associate*/
/**	short ia_mfb  [MAX_MF_SOMM]; */   /* puntatore in b-lego.dat         */
/**	short flg_mfca[MAX_MF_SOMM]; */   /* marcatura mf per delete         */
/**	short flg_mfin[MAX_MF_SOMM]; */   /* marcatura mf per inserimento    */
/**	short flg_mfdi[MAX_MF_SOMM]; */   /* marcatura per disattivazione    */
/**	char des_mf  [MAX_MF_SOMM] [25];*//* descrizione                     */
/*	char vatt_mf [MAX_MF_SOMM] [9]; */ /* valore attuale                  */
/**	float vvar_mf[MAX_MF_SOMM]; */    /* valore var. associata           */
/**	char escl_mf [MAX_MF_SOMM] [9];*/ /* malfunzione esclusa             */
/*	short sevf_mf[MAX_MF_SOMM]; */    /* severita' finale                */
/**	short ramp_mf[MAX_MF_SOMM]; */    /* rampa                           */
/**	short trig_mf[MAX_MF_SOMM]; */    /* indice di trigger               */
/**	short dstr_mf[MAX_MF_SOMM];  */   /* delay allo start                */
/**	short dur_mf [MAX_MF_SOMM];  */   /* durata                          */
/**	short ul_mf;                 */    /* numero mf in sommario          */
/**	short flg_modm;               */   /* flag sommario modificato       */
	} ;

/** le strutture modfr e modmf servivano per comunicare con legograf **/
/**
struct modfr_st
	{
	char nome_fr[9];           
	char spare1[3];           
	int pointer;             
	int tipo_pert;          
	};
typedef struct modfr_st MODFR;

struct modmf_st
	{
	char nome_mf[9];       
	char spare1[3];       
	int pointer;         
	int tipo_pert;      
	};
typedef struct modmf_st MODMF;
**/
/*********************************************************************/

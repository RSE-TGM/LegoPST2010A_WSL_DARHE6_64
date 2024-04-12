/**********************************************************************
*
*       C Header:               f14.h
*       Subsystem:              2
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Apr 12 16:15:25 1996 %
*
**********************************************************************/
/*
   modulo f14.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)f14.h	5.1
*/
/* Nomi dei file di topologia e di dati geometrici */
#define FILE_F14                "f14.dat"
#define FILE_F14_TMP            "f14.tmp"
#define FILE_F24                "proc/f24.dat"

#define L_RIGA_F14		140  /* lunghezza riga f14.dat */
/*
 parole chiave utilizzate per la decodifica del file ASCII f14.dat
*/
#define HEADER_F14	"*LG*NOME IMPIANTO"
#define HEADER_NORM_F14	"*LG*DATI DI NORMALIZZAZIONE"
#define HEADER_VAR_OUT	"*LG*CONDIZIONI INIZIALI VARIABILI DEL SISTEMA (MKS)"
#define HEADER_VAR_INP	"*LG*CONDIZIONI INIZIALI VARIABILI DI INGRESSO"
#define HEADER_BLOCCO_F14       "*LG*DATI DEL BLOCCO "
#define VAR_NOTA		"NOTO"
#define EOF_F14                 "*LG*EOF"

/*
 offset di campi di interesse all'interno della singola riga del file
 f14.dat
*/
#define OFF_SIGLA   4   /* offset inizio sigla variabile */
#define OFF_VAL     14  /* offset valore assegnato alla variabile */
#define OFF_NOTO    39  /* offset scritta noto/non noto */
#define OFF_SELUMIS 131 /* offset indice per unita' di misura */
/*
 strutture per la memorizzazione temporanea dei dati letti dal file
 f14.dat
*/ 
typedef struct {
		float val;
		char noto;
		unsigned char ind_umis;
		unsigned char sel_umis;
		} VALORE;
typedef struct {
		char titolo[133];
		int inizio;
		int num_dati;
		} HEAD_DATI;
typedef struct {
		char descr[9];
		float val;
		} DATO;

VALORE *valout;
VALORE *valinp;
DATO *dati;
HEAD_DATI *head_dati;


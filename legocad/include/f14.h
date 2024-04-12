/**********************************************************************
*
*       C Header:               f14.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:02:05 1996 %
*
**********************************************************************/
#ifndef _F14_H_
#define _F14_H_

/* Nomi dei file di topologia e di dati geometrici */
#define FILE_F14                "f14.dat"
#define FILE_F14_TMP            "f14.tmp"
#define FILE_F24                "proc/f24.dat"

#define L_RIGA_F14		133  /* lunghezza riga f14.dat
                                        (compreso terminatore) */
/*
 parole chiave utilizzate per la decodifica del file ASCII f14.dat
*/
#define HEADER_F14	"*LG*NOME IMPIANTO"
#define HEADER_NORM_F14	"*LG*DATI DI NORMALIZZAZIONE"
#define HEADER_VAR_OUT	"*LG*CONDIZIONI INIZIALI VARIABILI DEL SISTEMA (MKS)"
#define HEADER_VAR_INP	"*LG*CONDIZIONI INIZIALI VARIABILI DI INGRESSO"
#define HEADER_SEZ_DATI "*LG*DATI FISICI E GEOMETRICI DEL SISTEMA SUDDIVISI A BLOCCHI"
#define HEADER_BLOCCO_F14       "*LG*DATI DEL BLOCCO "
#define DESCRIZIONE_IN_DATI     "*   "
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
#define OFF_INI_DATO1 14 /* offset inizio valore numerico dato */
#define OFF_INI_DATO2 39 
#define OFF_INI_DATO3 64
#define OFF_INI_DESC1 4  /* offset inizio descrizione */
#define OFF_INI_DESC2 29
#define OFF_INI_DESC3 54
#define OFF_END_DATO1 24 /* offset asterisco di fine dato */
#define OFF_END_DATO2 49
#define OFF_END_DATO3 74
#define OFF_NOME_BLO_DAT 20 /* offset nome blocco nella intestazione della
                               sezione dati ad esso relativa 
			     */
#define MAX_DATI_NORM 10
#define DATI_NORM_BLANK "      "
#define DATI_NORM_P0    "2.E+07"
#define DATI_NORM_H0    "1.E+06"
#define DATI_NORM_W0    "1.E+03"
#define DATI_NORM_T0    "1.E+03"
#define DATI_NORM_R0    "1.E+02"
#define DATI_NORM_L0    "1.E+01"
#define DATI_NORM_V0    "5.E+01"
#define DATI_NORM_DP0   "1.E+05"

/*
 strutture per la memorizzazione temporanea dei dati letti dal file
 f14.dat
*/ 
struct s_val_var {
		float val;
		char noto;
		unsigned char ind_umis;
		unsigned char sel_umis;
		}; 
typedef struct s_val_var VAL_VAR;

struct s_header_dati {
		char titolo[L_RIGA_F14];
		int inizio;
		int num_righe_dati;
		int inizio_descr;
		int num_descr;
		}; 
typedef struct s_header_dati HEADER_DATI;


struct s_header_var {
		int inizio;
		int num_righe_var;
		};
typedef struct s_header_var HEADER_VAR;


struct s_dato_blo {
		char descr[9];
		char val[11];    /* il valore viene memorizzato come ASCII
                                  in quanto non e' detto possa essere un
                                  valore numerico */
		};
typedef struct s_dato_blo DATO_BLO;

struct s_dato_riga {
		int num_dati;
		DATO_BLO dato[3];
		};
typedef struct s_dato_riga DATO_RIGA;

struct s_dato_descr {
		char descr[L_RIGA_F14];
		unsigned short dato_seguente;
		short continua;
			};
typedef struct s_dato_descr DATO_DESCR;

#endif

/**********************************************************************
*
*       C Header:               installa.h
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Wed Dec 18 17:20:38 2002 %
*
**********************************************************************/
/*
   modulo %M%
   tipo %Y%
   release %I%
   data %G%
   reserved %W%
*/
#ifndef h_installa_h
#define h_installa_h
#include <math.h>

#if defined LINUX
#include <values.h>
#endif

// Nomi delle tabelle utilizzate
#define ALARM_TABLE       	"ALARM"
#define HDR_TABLE         	"HDR"
#define SCDCONF_TABLE     	"SCDCONF"
#define SCDTAB_TABLE	  	"SCDTAB"
#define LOG_TABLE         	"LOG"
#define SCDDBA_TABLE      	"SCDDBA"
#define TAG_TABLE	  	"TAG"
#define ALARMTYPE_TABLE   	"ALARMTYPE"
#define MEASURE_TABLE     	"MEASURE"
#define SCDLBG_TABLE	  	"SCDLBG"
#define POINTINSTERR_TABLE	"POINTINSTERR"

// database allarmi monitorizzato
#define DBALL_MONITOR	1

#define NO_GER 	-1
#define NO_SOGLIA	MAXFLOAT
#define INT_NODEF	9999999

#define MAX_GERARCHIE 5000	// massimo numero di gerarchie gestite

#define COD_SIGLA_SCADA "@#K@"

// default per AA
#define ZONA_AA	0
#define SEV_AA	0
#define TRAT_AA	2
#define BANDA_AA 0
#define LIM_BS_AA	0.0		// NO_SOGLIA
#define LIM_BC_AA	100.0		// NO_SOGLIA
#define LIM_AC_AA	200.0		// NO_SOGLIA
#define LIM_AS_AA	300.0		// NO_SOGLIA

// default per AS
#define ZONA_AS	0
#define SEV_AS	0
#define TRAT_AS	0
#define BANDA_AS 0
#define LIM_BS_AS	-2.0		// NO_SOGLIA
#define LIM_BC_AS	-1.0		// NO_SOGLIA
#define LIM_AC_AS	0.1		// NO_SOGLIA
#define LIM_AS_AS	0.2		// NO_SOGLIA

// default per AO
#define ZONA_AO		0
#define PRINT_AO	1

// default per DA
#define ZONA_DA	0
#define SEV_DA	0
#define TRAT_DA	1
#define STATO0_DA   "Off"
#define STATO1_DA   "On"

// default per DO
#define ZONA_DO		0
#define PRINT_DO	1


scrivi_header(char *,char *,STRUCT_TABLE *, int);
init_record(RECORD *,STRUCT_TABLE *, int);
scrivi_record(char *,char *,RECORD * );
ins_campo_char(char *,char *,RECORD *);
ins_campo_int(char *,int ,RECORD *);
int crea_aa();
int installa_aa(
        char *, // Sigla sigla del punto sullo SCADA
        char *, // Descrizione del punto
        char *, // Unita' di misura del punto
        char *, // SiglaSim del punto nel simulatore
        float , // LalBS      bassa sicurezza, non definita = NO_SOGLIA
        float , // LalBC      bassa conduzione, non definita = NO_SOGLIA
        float , // LalAC      alta conduzione, non definita = NO_SOGLIA
        float , // LalAS      alta sicurezza, non definita = NO_SOGLIA
        int ,    // Zona impianto
        int ,    // BandaMorta % banda morta
        int ,    // Trattamento Trattamento del punto
        int ,    // Severita   livello di severita'
        int ,    // livello di gerarchia 0 non definita = NO_GER
        int ,    // livello di gerarchia 1 non definita = NO_GER
        int ,    // livello di gerarchia 2 non definita = NO_GER
        int ,    // livello di gerarchia 3 non definita = NO_GER
        int ,    // livello di gerarchia 4 non definita = NO_GER
        int    // livello di gerarchia 5 non definita = NO_GER
        );

int crea_ao();
int installa_ao(
        char * , // Sigla sigla del punto sullo SCADA
        char * , // Descrizione del punto
        char * , // Unita' di misura del punto
        char * , // Sigla sigla del punto sul simulatore
        int ,    // Zona di impianto
        int ,    // flag per stampa comando
        int ,    // livello di gerarchia 0 non definita = NO_GER
        int ,    // livello di gerarchia 1 non definita = NO_GER
        int ,    // livello di gerarchia 2 non definita = NO_GER
        int ,    // livello di gerarchia 3 non definita = NO_GER
        int ,    // livello di gerarchia 4 non definita = NO_GER
        int    // livello di gerarchia 5 non definita = NO_GER
        );

int crea_as();
int installa_as(
        char * , // Sigla sigla del punto sullo SCADA
        char * , // Descrizione del punto
        char * , // Unita' di misura del punto
        int ,    // Periodo della calcolata
        int ,    // TipoCalc della calcolata
        float , // LalBS      bassa sicurezza, non definita = NO_SOGLIA
        float , // LalBC      bassa conduzione, non definita = NO_SOGLIA
        float , // LalAC      alta conduzione, non definita = NO_SOGLIA
        float , // LalAS      alta sicurezza, non definita = NO_SOGLIA
        int ,    // Zona di impianto
        int ,    // BandaMorta % banda morta
        int ,    // Trattamento Trattamento del punto
        int ,    // Severita   livello di severita'
        int ,    // livello di gerarchia 0 non definita = NO_GER
        int ,    // livello di gerarchia 1 non definita = NO_GER
        int ,    // livello di gerarchia 2 non definita = NO_GER
        int ,    // livello di gerarchia 3 non definita = NO_GER
        int ,    // livello di gerarchia 4 non definita = NO_GER
        int ,   // livello di gerarchia 5 non definita = NO_GER
        int ,    // livello di gerarchia calc 0 non definita = NO_GER
        int ,    // livello di gerarchia calc 1 non definita = NO_GER
        int ,    // livello di gerarchia calc 2 non definita = NO_GER
        int ,    // livello di gerarchia calc 3 non definita = NO_GER
        int ,    // livello di gerarchia calc 4 non definita = NO_GER
        int ,   // livello di gerarchia calc 5 non definita = NO_GER
        int ,    // database allarmi per la calcolata
        int      // zona di impianto per la calcolata
        );


int crea_da();
int installa_da(
        char * , // Sigla sigla del punto sullo SCADA
        char * , // Descrizione del punto
        char * , // Sigla sigla del punto sul simulatore
        char * , // descrizione stato 0
        char * , // descrizione stato 0
        char * , // Sigla punto protezione 1
        char * , // Sigla punto protezione 2
        char * , // Sigla punto inibizione
	int ,    // 0 normale 1 negato
        int ,    // Zona di impianto
        int ,    // Trattamento Trattamento del punto
        int ,    // Severita   livello di severita'
        int ,    // livello di gerarchia 0 non definita = NO_GER
        int ,    // livello di gerarchia 1 non definita = NO_GER
        int ,    // livello di gerarchia 2 non definita = NO_GER
        int ,    // livello di gerarchia 3 non definita = NO_GER
        int ,    // livello di gerarchia 4 non definita = NO_GER
        int    // livello di gerarchia 5 non definita = NO_GER
        );

int installa_ad();

int installa_dd();

int crea_do();

int installa_do(
        char * , // Sigla sigla del punto sullo SCADA
        char * , // Descrizione del punto
        char * , // Sigla sigla del punto sul simulatore
        int ,    // Zona di impianto
        int ,    // Tipo di Azione -1 imp, 0 a zero , 1 a uno
        int ,    // flag per stampa comando
        int ,    // livello di gerarchia 0 non definita = NO_GER
        int ,    // livello di gerarchia 1 non definita = NO_GER
        int ,    // livello di gerarchia 2 non definita = NO_GER
        int ,    // livello di gerarchia 3 non definita = NO_GER
        int ,    // livello di gerarchia 4 non definita = NO_GER
        int    // livello di gerarchia 5 non definita = NO_GER
        );

int CreaAllarAs();


int installa_err(char *,int);
// Codici di errori non fatali  e nome file Errore
#define NOME_FILE_ERR	"PointInst.err"
#define CREATE_FILE_ERR				0
#define TAG_NOT_FOUND_IN_TAG			1
#define TAG_NOT_IN_SCADA			2
#define TAG_NOT_FOUND_IN_MEASURE_OR_ALARM	3
#define ARC_TAG_NOT_FOUND			4
#define SIGNAL_NOT_FOUND			5

#endif

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
	ARCMSG.INC
	Strutture messaggi trasmissione files di archivio da STOP 386 a
	PC Config

	Creazione:  GM.Furlan   -  18.03.92
*/
#include <all_1.h>
#undef long
#define long int
#define SER 0                  // codice comunicazione via linea seriale
#define ETH 1                  // codice comunicazione via rete Ethernet

// Codici Messaggi

#define mapr  1    // cod. msg. richiesta archivi presenti
#define maps  2    // cod. msg. risposta  archivi presenti
#define mefr  3    // cod. msg. richiesta elenco files d'archivio
#define mefs  4    // cod. msg. risposta  elenco files d'archivio
#define mtfdr 5    // cod. msg. richiesta trasmissione file descrittore archivio
#define mtfar 6    // cod. msg. richiesta trasmissione file d'archivio
#define mtfs  7    // cod. msg. risposta  trasmissione file d'archivio
#define msinc 8    // cod. msg. sinzronizzazione per messaggio mtfs
                   // per ogni blocco scada attende la risposta

#define CL_ARC 10              // classe messaggio

// Strutture Messaggi

// 1: richiesta archivi presenti
typedef struct {
               char mess;     // cod. msg.	
               char classe;   // classe msg.	
               } M_APR;
#define l_apr sizeof(M_APR)


// 2: risposta archivi presenti
typedef struct {
                char num;    // numero archivio
                char tipo;   // tipo archivio
                } ARC_INF;
typedef struct {
               char mess;          // cod. msg.	
               char classe;   // classe msg.	
               short tot_arc;       // numero totale archivi installati
               ARC_INF arc[n_arc];  // informazioni archivi installati
               } M_APS;
#define l_aps sizeof(M_APS)


// 3: richiesta elenco files singolo archivio 
typedef struct {
               char mess;          // cod. msg.	
               char classe;   // classe msg.	
               short iarc;          // indice archivio
               } M_EFR;
#define l_efr sizeof(M_EFR)


// 4: risposta elenco files singolo archivio
typedef struct {
               char mess;          // cod. msg.	
               char classe;        // classe msg.	
               short num_file;     // numero file esistenti per l'archivio
               ARCNOME arcnomi[n_farc];     // nomi dei file
               } M_EFS;            
#define l_efs sizeof(M_EFS)


// 5: richiesta trasmissione singolo file
typedef struct {
               char mess;          // cod. msg.	
               char classe;   // classe msg.	
               short iarc;          // indice archivio
               ARCNOME arcnome;     // nome del file
               char  spare;        // allineamento alla word
               } M_TFR;
#define l_tfr sizeof(M_TFR)


// 6: risposta trasmissione singolo file
#define l_buf 512
typedef struct h_tfs {
               char mess;          // cod. msg.	
               char classe;   // classe msg.	
               short err;           // cod. errore
               short num_bl;        // numero blocco in trasmissione
               short lung_bl;       // lunghezza blocco in trasmissione
               short last_bl;       // flag ultimo blocco
                } H_TFS;

typedef struct {
               H_TFS hea; 
               char dati_bl[l_buf]; // buffer in trasmisssione
               } M_TFS;
#define l_tfs sizeof(M_TFS)

#include <all_16.h>
#undef long
#define long long

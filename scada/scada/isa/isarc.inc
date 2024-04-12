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
	ISARC.INC
	Strutture messaggi trasmissione files di archivio da STOP-NET a
	PC Config.

	Creazione:  E.Locatelli   -  15.12.93
        Revisione:  D.Cristiani   -  22.03.94
*/

#include "arc.inc"

#define SER 0                  // codice comunicazione via linea seriale
#define ISO 1                  // codice comunicazione via rete Ethernet protocollo ISO/OSI
#define TCP 2                  // codice comunicazione via rete Ethernet protocollo TCP/IP

#define l_lbgnet_buff 132

// Codici Messaggi

#define mapr    1    // cod. msg. richiesta archivi presenti
#define maps    2    // cod. msg. risposta  archivi presenti
#define mefr    3    // cod. msg. richiesta elenco files d'archivio
#define mtfdr   5    // cod. msg. richiesta trasmissione file descrittore archivio
#define mtfar   6    // cod. msg. richiesta trasmissione file d'archivio
#define mtfs    7    // cod. msg. risposta  trasmissione file d'archivio
#define msinc   8    // cod. msg. sinzronizzazione per messaggio mtfs
                  	  // per ogni blocco scada attende la risposta
#define mflbgpr 9    // cod. msg. richiesta file libro giornale presenti
#define mflbgps 10   // cod. msg. risposta file libro giornale presenti e
                     	  // file libro giornale attualmente in uso
#define mflbnet 11   // cod. msg. invio stringhe allarmi libri giornale
#define meflgs  12   // cod. msg. risposta elenco files d'archivio con lungh.

#define CL_ARC 10              // classe messaggio
#define CL_FLG 10              // classe messaggio

// Strutture Messaggi

// 1: richiesta archivi presenti
typedef struct {
	       short conn;    // indice della connessione
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
	       short conn;    	    // indice della connessione
               char mess;           // cod. msg.	
               char classe;         // classe msg.	
               short tot_arc;       // numero totale archivi installati
               ARC_INF arc[n_arc];  // informazioni archivi installati
               } M_APS;
#define l_aps sizeof(M_APS)


//3: richiesta elenco files singolo archivio 
typedef struct {
	       short conn;    	   // indice della connessione
               char mess;          // cod. msg.	
               char classe;   	   // classe msg.	
               short iarc;         // indice archivio
               } M_EFR;
#define l_efr sizeof(M_EFR)




// 5: richiesta trasmissione singolo file
typedef struct {
	       short conn;    		// indice della connessione
               char mess;          	// cod. msg.	
               char classe;   		// classe msg.	
               short iarc;          	// indice archivio
               ARCNOME arcnome;     	// nome del file
               char  spare;        	// allineamento alla word
               } M_TFR;
#define l_tfr sizeof(M_TFR)


// 6: risposta trasmissione singolo file
#define l_buf 512
typedef struct h_tfs {
	       short conn;    	    // indice della connessione
               char mess;           // cod. msg.	
               char classe;   	    // classe msg.	
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

// 9: richiesta file libro giornale presenti
typedef struct {
	       short conn;    // indice della connessione
               char mess;     // cod. msg.	
               char classe;   // classe msg.	
               } M_FLGPR;
#define l_flbgpr sizeof(M_FLGPR)

// 10: risposta file libro giornale presenti
typedef struct {
	       short conn;    		// indice della connessione
               char mess;           	// cod. msg.	
               char classe;         	// classe msg.	
               short tot_flbg;       	// numero totale archivi installati
               short dbfileal;       	// nø file allarmi in uso
               } M_FLGPS;
#define l_flbgps sizeof(M_FLGPS)

// 11: invio stringhe allarmi
typedef struct {
	       short conn;    			// indice della connessione
               char mess;                       // cod. msg.	
               char classe;                     // classe msg.	
               char buffer[l_lbgnet_buff];      // string buffer
               } M_LBGNET;
#define l_lbgnet 2              // solo header


// 12: risposta elenco files singolo archivio con indicazione lunghezza
typedef struct {
	       short conn;   	   // indice della connessione
               char mess;          // cod. msg.	
               char classe;        // classe msg.	
               short num_file;     // numero file esistenti per l'archivio
               ARCNOME arcnomi[n_farc];     // nomi dei file
               long flength[n_farc];         // lunghezza dei file 
               } M_EFLGS;            
#define l_eflgs sizeof(M_EFLGS)

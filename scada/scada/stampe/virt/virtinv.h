/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*-> 
        VirtInv.inc

        Il file contiene le strutture associate alla definizione
        di stampanti virtuali

        Le stampanti fisiche sono definite nel file print.inc
*/
/*
        definizione della struttura delle stampanti virtuali per
        libro giornale e tabualti
*/

#define n_DevFis  4
typedef struct s_Prn_Virt {
            	   	unsigned char page_a;	// n. pagine libro giornale
	   	            unsigned char page_g;	// n. pagine attivita' generiche
                     unsigned char righe_a;  // n. righe libro giornale
                     unsigned char righe_g;  // n. righe attivita' generiche
                     short indice[n_DevFis]; // indice device fisici associati
                     short prev;		         // corrente device fisico utilizzato
                     long abzon;             // maschera per zone da inserire nel libro giornale 
                     long ByteOcc;           // solo per disco n. byte scritti
                     short DFileU;           // punto diagnostica file in  uso 
                     short IFileU;           // indice file in uso
                     short DFileP;           // punto diagnostica data file utilizzatoi
                        } S_PVIRT;

#define l_prn_rem    20
typedef struct s_Prn_Fis    {
                     short  baud;   // baud rate
                     char   data;   // data bit
                     char   stbit;  // stop bit
                     char   parity; // parita
                     char   linea;  // n. linea associata
               		char   flag ;  // allarmi o tabulato ?
                     char   nvirt;  // n. stampante virtuale associata
                     char   stato;  // stato del device
                     char   remota; // flag stampante locale/remota
               		short   *dig;	// puntatore in data base logico
                     char   remname[l_prn_rem];    // nome stampante remota
                     short   idig;  // indice digiatale di diagnostica di stato
                        } S_PFIS;

pub S_PFIS fisdev[n_fis];           // definizione stampanti fisiche

#define n_virt_lbg 8            // n. stampanti virtuali per libro giornale
#define n_virt_tab 4            // n. stampanti virtuali per tabulati

pub S_PVIRT  virtprn[n_virt_lbg+n_virt_tab];

/*
   variabili destinate alla gestione del libro giornale
   su disco
*/
#define  max_byte_LbgOcc  (132000L)    // dimensione massima file libro giornale
pub FILE* LbgFp;                             // file pointer LBG in uso
pub short NLbgVirt;             // n. della stampante virtuale a cui si riferisce il 
                            // il nuovo allarme
pub short PLbgVirt;             // n. della stampante virtuale a cui si riferisce il 
                             // file pointer LbgFp

pub short   gDefTabPrn;       // stampante virtuale di defaut per tabulati

//
//    Punti di diagnostica gestione file libro giornale
//
#define  pDiaP    769         // progressivi per ciascun file e ciascuna stampante
#define  pDiaU    833         // file in uso

#define  pVirtFull  180          // indice file libro giornale completo

#define  pVirtZone   841         // indice primo analogico per associazione zone impianto- stampanti
#define  pDefTab     857         // indice analogico per stampante tabulati di default

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
   AGGCFG.INC 
	il file di include aggcfg.inc contiene
	i buffer per i messaggi verso il task tlink.
	(configurazione e aggiornamento sistemi)

   14.10.92  -  Rev. 1.00  -  GM.Furlan

        11 Novembre 1994 
        Inserimento messaggio per installazione e
        disinstallazione pagina MMI Win
*/

/*
	messaggi aggiornamento pagine per MMI Window
*/
#include <all_1.h>
#define mWinIFile	29		// installazione
#define mWinDFile	30		// cancellazione
#define DIM_NOMEPAGINA  (8+1+3+1)
#define DIM_BLOCCO	512
typedef struct s_WinFile {
		short nodo;
		short mess;
		char  nome[DIM_NOMEPAGINA];
		char  bAck;
		char  bLast;
		char  blocco[DIM_BLOCCO];
			} S_WINFILE;

typedef struct s_conf  {
			short mess;
			char  release[6];
			}S_CONF;

#define dim_headb	4		// short mess + short lung

union  u_messaggi { 
		    TXTESTA_FILE_ETH i;
		    TXDATI_FILE_ETH  d;
		    TXFINE_FILE_ETH  x;
                    struct trasm_fmmi_eth mmi;    // messaggio struttura trasmissione file FMMI*.RTF
		    S_WINFILE winFile;
		  } mconfig;

/*
  struttura buffer per messaggio aggiornamento pagine verso MMI
*/
struct s_buff_mmi { short nodo;
                    char  indice;
                    char  spare1;
                    char  micro;
                    char  video;
                    char  spare[12];
                    short indfile;
                    short indblocco;
                    char  blocco[512];
                  } ;

union  u_mmi { 
		    struct s_buff_mmi buff_mmi;
		    short buff[3];                      // buffer messaggio fine comunicazione
		  } uconf;


#include <all_16.h>

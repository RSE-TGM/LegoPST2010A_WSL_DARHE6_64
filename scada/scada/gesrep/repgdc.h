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
   repgdc.h
   Il file contiene i parametri che definiscono le caratteristiche
   dei messaggi di interrogazione verso il gestore delle chiamate

*/

#define max_BRx   256   //   N. massimo caratteri messaggio

#define linea_Gdc 3     //   quarta linea 507
#define retry_Gdc 3
#define trisp_Gdc (2*20)      // 2 secondi 
#define timer_que (30*20)     // 30 secondi
#define tquery_Gdc (5*20)     // 5 secondi

#define som_Gdc 0x24h       // '$'     
#define eom1_Gdc  0x0d     
#define eom2_Gdc  0x0a     
#define sep_Gdc   0x3b       // ;     
#define n_campi   6          // n. massimo di campi che compongono la risposta da gdc

typedef struct Header_replay {
         char dollaro;
         char codice;
         char virg0;
         char comando;
         char virg1;
         char statA1[2];
         char virg2;
         char statA2[2];
         char virg3;
         } GDC_RPL_HEA;

typedef struct Replay_status {
         GDC_RPL_HEA hea;
         char statL;
         char virg4;
         char dati[max_BRx];
         } GDC_RPL;
/*
   definizione posizione Tag e Telefono nei vari campi
*/
#define gdc_cTag     1           // tag primo campo dopo lo stato
#define gdc_cTel     5           // n. del telefono
/*
   definizione maschere per interpretazione diagnostica GDC statA1
*/
#define gdc_mStatus  0x01        // stato funzionamento Gdc
#define gdc_mL1      0x02        // stato funzionamento linea 1
#define gdc_mL2      0x04        // stato funzionamento linea 2
#define gdc_mL3      0x08        // stato funzionamento linea 3
#define gdc_mL4      0x10        // stato funzionamento linea 4

#define gdc_mCMD     0x20        // comando ricevuto correttamente
#define gdc_mER      0xC0        // codice errore ultimo comando
/*
   posizione digitali di diagnostica
*/
#define gdc_dStatus  170        // stato funzionamento Gdc
#define gdc_dL1      171        // stato funzionamento linea 1
#define gdc_dL2      172        // stato funzionamento linea 2
#define gdc_dL3      173        // stato funzionamento linea 3
#define gdc_dL4      174        // stato funzionamento linea 4

#define gdc_dAbil    175        // abilitazione gestione reperibili
#define gdc_dConn    176        // stato della connessione con GDC

/*
   definizione maschere per interpretazione diagnostica GDC statL
*/
#define gdc_mST      0x0F        // stato sequenza di chiamata
#define gdc_mRI      0x20        // maschera bit riconoscimento avvenuto
#define gdc_mS       0x10        // maschera bit sequenza terminata

/*
   posizione analogici di diagnostica
*/
#define gdc_aERCMD   46         // codice ultimo errore
#define gdc_aStatoL  47         // stato sequenza

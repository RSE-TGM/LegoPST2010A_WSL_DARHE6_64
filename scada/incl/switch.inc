/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
// switch.inc
//
// contiene le definizioni per gli switch di attivazione

#include "defpub.h"                // definizioni pubbliche

pub short TABUL;                   // tabulati
pub short ARCHIVI_NV;              // archivi
pub short ISA;                     // host su ethernet
pub short SYS_DUALE;               // sistema duale
pub short NET_ABIL;                // abilitazione rete ethernet
pub short HCPY;                // abilitazione hard copy (solo per pag. diag.)
pub short GESREP;


pub short SEGNALA_RIC_ALLARMI;     // ricon.allarmi su stampante
pub short SKR_ALL;                 // visita di tutta la pagina allarmi
pub short RIC_SI;                  // riconoscimento singolo in pagina allarmi
pub short CONT_ALL_ZONE;           // contatori allarmi per zone e database
pub short BUZZER;                  // abilitazione comando contatto buzzer
pub short RESET_LBGSETT;           // abilitazione reset libro giornale settimanale
pub short SEC_FORMAT;              // formato stringa allarmi HH/MM/SS

pub char  PER_GDAC;                // frequenza pagine video          
#define MAXPER_GDAC     2          // frequenza massima     

pub short PAS_STOP;                // presenza pas     
pub short NPC_PAS;                 // numero pas
#define NMAX_PAS        4          // numero massimo pas
pub short PAS_INI;                 // pas 1 attivo subito

pub short num_video;               // numero mmi collegabili     
#define max_video       16         // numero mmi massime

pub short DEBUG;                   // per debugger

pub short INGLESE;

/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/* File di include contenente le istruzioni di define */

#define DIM_PR     20*1024    // dimensione area codice descrittori SCB
#define DIMDBL     2048       // dimensione Data Base Locale DBL
#define DIMPCB     20         // dimensione struttura PCB
#define DIMSCB     200        // dimensione struttura SCB
#define DIMMES	   256         // dimensione buffer messaggi
#define DIMPAC	   32         // dimensione packet messaggi
#define DIMAB      1000       // max dimensione file codice.ab
#define NMENTRY    64         // numero max entry possibili
#define OFFENTRY   32         // offset indirizzi entry in codice.ab

#define IDLE	0x00	// stato PCB definito IDLE LOADED
#define RUN	0x01	// stato PCB definito RUN
#define FREEZE	0x02	// stato PCB definito FREEZE
#define UNLOAD	0x03	// stato PCB non caricata


#define	SEQTERM 2	// stato SCB sequenza terminata 
#define	SEQSOSP 1	// stato SCB sequenza sospesa
#define	SEQATTI 0	// stato SCB sequenza attiva

#define MSGTRIG 1	// codice messaggio di trigger sequenza
#define MSGSTOP 2	// codice messaggio di stop sequenza
#define MSGSTAR 3	// codice messaggio di start sequenza
#define MSATTIV 4       // codice messaggio di attivazione sincrona

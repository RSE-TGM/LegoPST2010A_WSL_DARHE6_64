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
	SIMDIA.INC
        contiene i puntatori dei digitali di diagnostica legati 
        al SSC di un SIMULATORE
	N.B. i valori sotto riportati devono corrispondere ai puntatori
	ai digitali di stato corrispondenti.

        Settembre '92  -  GM.Furlan
*/

/*	       
	diagnostica supervisione simulatore
*/
#define sscstop         139             // simulatore in STOP
#define sscwait         140             // simulatore in WAIT
#define sscready        141             // simulatore in READY TO GO
#define	sscrun          142             // stato simulatore in RUN o FREEZE
#define sscfreeze       143             // simulatore in FREEZE
#define sscbktk         144             // simulatore in BACKTRACK
#define sscreplay       145             // simulatore in REPLAY
#define sscsimon        146             // simulatore connesso in rete
#define sscnocom        147             // fallito comando verso simulatore 
#define sscrest         148             // restart task archiviazione

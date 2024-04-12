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
	Rceintes.h

	File di include con stringhe intestazione stampa perturbografica
*/
#define max_rcest	86				// lunghezza massima stringa
extern char *rcest1;			// ="S T A M P A   P E R T U R B O G R A F I C A ";
extern char *rcest3;			// ="  Prg   hh:mm:ss,mil Arm.    Sigla  Cat.   Descrizione        Val Stato";
extern char *rcest4;			// =" *** EVENTO SGANCIATORE *** ";
extern char *rcest5;			// =" *** R C E   C O N C L U S A *** ";
extern char *rcedate;
extern char *rcetime;
extern char *rceRCE;

#define rce_testa	1
#define rce_sgancio	2
#define rce_fine	3

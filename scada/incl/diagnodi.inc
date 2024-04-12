/**********************************************************************
*
*       C Header:               diagnodi.inc
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 24 14:59:46 2002 %
*
**********************************************************************/
/*
	Diagnodi.inc

	l`include diagnodi.inc  contiene i puntatori
	di tutti i digitali di diagnostica
	N.B. i valori sotto riportati devono corrispondere ai puntatori
	ai digitali di stato corrispondenti.

	22 Aprile 1993
	Inserimento diagnostica duale e riorganizzazione
*/
#define  stvide1	0	 	// 9 video
#define  stvide2	1	 
#define  stvide3	2	 
#define  stvide4	3
#define  stvide5	4	 
#define  stvide6	5	 
#define  stvide7	6	 
#define  stvide8	7
#define  stvide9	8	 


#define  stprn5 	9 		// 6 stampanti
#define  stprn6		10
#define  stprn4		11
#define  stprn3		12
#define  stprn1		13		// per compatibilita'
#define  stprn2		14

#define  sthard		15		// hardcopy
#define  config		16		// config
#define  diskerr	17		// errore dischetto
#define	 sthdisk	18		// hard disk pieno
#define	 lbgfull	19		// esauriti file libro giornale
	
#define  lockarc        20             // lock attivita' archivi (tab, trend o copia)
#define	arc_st01        21             // primo digitale stato archivi
					       // riservate 8 locazioni		
#define arc_st02	22
#define arc_st03	23
#define arc_st04	24
#define arc_st05	25
#define arc_st06	26
#define arc_st07	27
#define arc_st08	28

#define  stosta1       	32	       // PAS
#define  runfre1       	33
#define  stosta2       	34
#define  runfre2       	35
	
#define  stnod01	36		// stato nodo ISA 01
#define  stnod02	37		// stato nodo ISA 02
#define  stnod03	38		// stato nodo ISA 03
#define  stnod04	39		// stato nodo ISA 04

#define	ricall		42		// flag riconosciuti allarmi * 6 data base
#define noall		48		// flag nessun allarme in data base allarmi
						// le successive 5 locazioni sono riservate	
#define oldsysdate      54		// segnalazione cambio data				  
#define newsysdate      55		// e ora				  
	
#define stcom		56				// riservati per 8 fino a 63
#define stint31   stcom+8		// stato int31
#define stdou		stint31+1	// stato dou
#define master		stdou+1		// master o slave
#define stwdb		master+1		// watch dog B
#define stwda		stwdb+1 		// watch dog A
#define sysab		stwda+1	 	// A o B

#define abcom		sysab+1		// fino a 73

#define macom		abcom+8		// fino a 81

#define stdint1   macom+8				  
        
#define  stprn7         94              // stato stampante 7
#define  stprn8         95              // stato stampante 8

#define  slaveiniz	100		// slave in inizializz.
#define  slaveagg	101		// slave aggiornato
#define  slaveon	102		// slave in linea
#define  stlink		103		// collegamento con slave

#define	rcestampa	104		// abilitazione stampa rce
	
#define	sys_d   	106		// configurazione duale 

#if defined OSF1 || defined LINUX
#define stCicalino	150		// stato del cicalino ON, OFF
#endif
        

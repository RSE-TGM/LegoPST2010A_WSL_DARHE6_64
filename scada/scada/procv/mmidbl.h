/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
///////////////////////////////////////////////////////////////////////
//
//	mmiDbl.h		definizione data base locali pagine, video operatore
//					posto operatore
//                                             

//	Definizione dimensione singolo elemento in byte
#define chAN	6			// analogici
#define chIN	2			// interi
#define chDI	1			// digitali
#define chOR	2			// organi
#define chST   80			// stringhe
#define chPT	4			// puntatori

//	N. elementi per tipo nel data base Globale di video operatore
#define iGbkAN	6  		// analogici
#define iGbkIN	7	  	// interi
#define iGbkDI	8  		// digitali
#define iGbkOR	9  		// organi
#define iGbkST	10 		// stringa
#define iGbkPT	11 		// puntatori

#define nGbkAN	32  	// analogici
#define nGbkIN	32  	// interi
#define nGbkDI	32  	// digitali
#define nGbkOR	32  	// organi
#define nGbkST	32  	// stringa
#define nGbkPT	32  	// puntatori

//	posizioni gia' assegnate
//	Interi
#define iVideoCorr			0
#define iNumPostoOp			1
#define iVideoPostoOp		2
#define iNumVideoPostoOp	3
#define iAnno				4
#define iMese				5
#define iGiorno				6
#define iOre				7
#define iMinuti				8
#define iSecondi			9                                       

//	le prossime 12 locazioni sono riservate ai colori dell'asterisco e delle stringhe degli ultimi allarmi dei 6 
//	data base allarmi possibili
#define iColAstDBA1			10			// colore asterisco stringa ultimo allarme DBA 1
#define iColStDBA1			 11			// colore stringa ultimo allarme DBA 1

//	stringhe

// le prossime 6 locazioni sono riservate alle stringhe allarmi degli ultimi allarmi dei 6 DBA
#define sStrDBA1		0			  // stringa ultimo allarme DBA 1

//	digitali
#define	bStatoVideo			0
#define bComScada			1
#define bTastFunz			2
#define bMouse				3
#define bDisallTxTab       4	// diagnostica disallineamento tavole trasmissione (serialLink)
#define bHardcopyFull	5	  // esauriti file di hardcopy disponibili
#define bAll1				7
#define bAll2				8
#define bAll3				9
#define bAll4				10
#define bAll5				11
#define bAll6				12 

//	N. elementi per tipo nel data base Globale di posto operatore
#define iGbcAN	12  	// analogici
#define iGbcIN	13  	// interi
#define iGbcDI	14  	// digitali
#define iGbcOR	15  	// organi
#define iGbcST	16  	// stringa
#define iGbcPT	17  	// puntatori

#define nGbcAN	32  	// analogici
#define nGbcIN	32  	// interi
#define nGbcDI	32  	// digitali
#define nGbcOR	32  	// organi
#define nGbcST	32  	// stringa
#define nGbcPT	32  	// puntatori

//	N. elementi per tipo nel data base Globale della pagina
#define iGblAN	0  	// analogici
#define iGblIN	1  	// interi
#define iGblDI	2  	// digitali
#define iGblOR	3  	// organi
#define iGblST	4  	// stringa
#define iGblPT	5  	// puntatori

#define nGblAN	32  	// analogici
#define nGblIN	32  	// interi
#define nGblDI	32  	// digitali
#define nGblOR	32  	// organi
#define nGblST	16  	// stringa
#define nGblPT	32  	// puntatori              
              
// $ALLARMI posti gia' assegnati nel GblAN
#define iDataBase		17	// n. DBS degli allarmi
#define iCodice			18	// n. codice della pagina
#define iPall			19	// n. allarmi da riconoscere
#define iParch			20	// n. allarmi in archivio
#define iAll			21	// n. allarmi nel mess.
#define iArch			22	// punt. allarme in archivio
#define iFunzione		23	// tipo di funzione 0 1 2 3
#define iCicalino		24	// cicalino da emettere

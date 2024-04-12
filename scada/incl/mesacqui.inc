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
	il file di include mesacqui contiene tutte le strutture dei
	pacchetti da e verso la rete
*/
typedef struct s_heainet {	short 	lun;
				char 	codice;
				char	classe;
				short	nodo_sorg;
				short   nodo_dest;
				short	spare; 
			 }  S_HEAINET;

/*
	descrizione pacchetti acquisizione per
	tipo byte
*/
typedef struct s_vabyte  {	short	id_sdi;		// indice dbs
				char	valore;		// valore byte
				char    spare; 
			  } S_VABYTE;

#define max_vbyte	100
typedef struct s_acbyte  {    S_HEAINET hea;		
			      short	n_byte;		// n. punti byte
			      S_VABYTE	vbyte[max_vbyte];
			 } S_ACBYTE;
				

/*
	descrizione pacchetti acquisizione per
	tipo digitale
*/
#define max_vdig	4
#define max_pdig	40
typedef struct s_vadigi  {	short	id_sdi[max_vdig]; // indice dbs
				short	valore; 	  // valore digitali
			  } S_VADIGI;

typedef struct s_acdigi {    S_HEAINET hea;		
			      short	n_pack;		// n. pacchetti digitali
			      S_VADIGI	vdigi[max_pdig];
			 } S_ACDIGI;
				

/*
	descrizione pacchetti acquisizione per
	tipo analogico
*/
#define max_vana	50
typedef struct s_vana  {	short	id_sdi; 	// indice dbs
				char    flag;		// flag analogico
				char	valore[4];      // valore analogico
				char	spare;	
			  } S_VANA;

typedef struct s_acana {    S_HEAINET hea;		
			      short	n_vana;		// n. misure analogiche
			      S_VANA	vana[max_vana];
			 } S_ACANA;
				
#define mdana	7		// messaggio acquisizione analogici
#define mddig	8	        // messaggio acquisizione digitali
#define mdbyt   9		// messaggio acquisizione byte

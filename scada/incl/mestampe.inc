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
        l'include mestampe.inc contiene la dichiarazione dei
        messaggi che il processo stampe riconosce e tratta

        7 Novembre 1994 Fc
        Inserita definizione messaggio masc stampa libro
        giornale una qulasiasi stringa ASCII
*/
/*
        messaggio stampa allarmi
*/
typedef union u_sogl  { float  f ;
                        unsigned char   c[4] ; } U_SOGL ;
typedef struct s_ppal  { unsigned char  ertr ;
                        unsigned char  ext ;
                        short punt ;
                        unsigned char  sprec ;
                        unsigned char  satt ;
                      U_SOGL  vrif ;
                      U_SOGL  vatt ; } S_PPAL ;

typedef struct s_stall {
			short mess ;	   		
                        unsigned char  anno ;
                        unsigned char  mese ;
                        unsigned char  gior ;
                        unsigned char  ora  ;
                        unsigned char  min ;
                        unsigned char  sec ;
                        S_PPAL   al; } S_STALL ;
#ifndef MESESTEL_INCL
#include "mesestel.inc"
#endif
/*
        stampa allarmi con doppio tempo
*/
typedef struct s_stallt {
                        S_STALL m;
                        MISTIME t;
                        } S_STALLT;
/*
	stringa allarmi per punto stringa
*/
#define al_stringa (sizeof(S_PPAL)+8)
typedef struct s_stals {
			short mess ;
                        unsigned char  anno ;
                        unsigned char  mese ;
                        unsigned char  gior ;
                        unsigned char  ora  ;
                        unsigned char  min ;
                        unsigned char  sec ;
                        char valst[al_stringa]; } S_STALS ;

#define  mstal  5               /* stampa allarmi       */
#define  mskip  6               /* newline              */
#define  mmasc  7               /* stampa stringa ascii */
#define lmasc 60		// lunghezza stringa ascii 
typedef struct str_stamp {
	   short mess;
           char message[lmasc];
                  } S_STSTR;
/*
        definizione messaggi per stampa allarmi in archivio
        nel campo flag occorre specificare se si tratta del
        ultimo pacchetto (reset n. pagina e riga) oppure  di
	uno intermedio
*/
#define mstar   8               /* stampa allarmi in archivio   		*/
#define mstar_a 0               /* pacchetto intermedio allarmi da riconoscere	*/
#define mstar_r 1               /* pacchetto intermedio archivio		*/
#define mstar_f 2               /* pacchetto fine trasmissione 		        */

typedef struct s_star    {      short mess;
				short flag;
                                short peri;
			struct buff_all al;
                          } S_STAR ;

#define minar	9		/* setta pagina allarmi e archivio */

typedef struct s_inar    {      short mess;
				char  pagina;
				char  archivio;
                          } S_INAR ;

#define minel	10		/* stampa elenchi		    */

#define ELE_FINE  -1
#define ELE_FS	 1
#define ELE_FZ 	 2
#define ELE_HC_HS_LC_LS	 3
#define ELE_SL		 4
#define ELE_AL		 5
#define ELE_FA		 6

typedef struct s_stelen   {      short mess;
				 char  flag;
				 char  ext;
				 short punt;
				 char  value[4];
                          } S_STELEN ;
/*
        definizione messaggio per richiesta stampa tabulato
*/
#define mstab      39
#define mstabarc   40
#define mtrasfarc  41
#define mvisarc    42
#define mtrasfpol  43
#define mtrasfall  44
#define msfile	   45		// stampa file ASCII

#define l_tnome 10      /*      lunghezza nome tabulato   */
#define r_procv 0       /*      richiesta da micro op.    */
#define r_loged 4       /*      tabulato normale          */

typedef struct s_stab { short   lung;
			short   mess;
                        char    nome[l_tnome] ;
                        unsigned char video ;
                        unsigned char zona;
                        unsigned char richiesta ;
                        char archivio ;
			unsigned short anno;
			unsigned char giorno;    // parte per tabulato da archivio
			unsigned char mese;
 			unsigned char secondi;
 			unsigned char minuti;
   			unsigned char ore;
			short ncamp;		 // numero campioni di archivio da stampare
                      } S_STAB ;

/*
	Messaggio inviato a tabul per visualizzazione archivi
*/
#define lun_hpag   16   // lunghezza in bytes dell'header dei messaggi
			// verso STOP
typedef struct s_visarc { 
			short lung;
			short mess;
			char h[lun_hpag];  // header mess. verso STOP contenente
				           // nome pag. ecc.
			char quadr;   // quadrante
			char n_mis;   // numero di misure
			short numarc; // numero dell'archivio da cui estrarre
				      // i campioni.
			char posarc[4]; // posizione nell'archivio 
                                        // del campione da estrarre 
		       } S_VISARC;		

#define l_sfile		40
typedef struct s_sfile{ short   lung;
			short   mess;
                        char    nome[l_sfile] ;
                        short   richiesta;
                      } S_SFILE;

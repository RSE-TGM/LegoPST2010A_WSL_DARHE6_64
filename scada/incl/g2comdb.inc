/**********************************************************************
*
*       C Header:               g2comdb.inc
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri May 14 10:45:12 1999 %
*
**********************************************************************/
/*
        30 Dicembre  1992

        Inserimento livelli di severita'
*/
#include "gpunt.inc"
/*
        definizione del canale utilizzato per la open del
        data base di sistema
*/
#include "defpub.h"
pub int chan_dbs ;          /* viene inizializzato dalla function legdb */
/*
	includo il file che descrive le strutture delle calcolate
*/

#include "g0strdb.inc"

/*
        
        L'include g2comdb.inc descrive la struttura
        del data base di sistema
*/
/*
        analogici acquisiti
*/
        pub	S_DBAAV  *dbaav ;        /* valori        */
        pub	S_DBAAF  *dbaaf ;        /* flag         */
        pub	S_DBAAU  *dbaau ;        /* zona impianto*/
	pub	S_DBALL  *dbaaal;        /* struttura allarmi */
        pub	S_DBAAFA *dbaafa;        /* flag acquisizione */
#ifdef GERARC
        pub	S_DBGERA *dbaag;         /* gerarchia allarmi*/
#endif

/*
        analogici calcolati standard
*/
        pub	S_DBASV   *dbasv ;        /* valori        */
        pub	S_DBASF   *dbasf ;        /* flag         */
        pub	S_DBASU   *dbasu;         /* zona impianto*/
	pub	S_DBALL   *dbasal;	  /* struttura allarmi */
        pub	DES       *dbasde;        /* descrittore calcolata */
#ifdef GERARC
        pub	S_DBGERA  *dbasg;         /* gerarchia allarmi*/
#endif

/*
        analogici calcolati non standard
*/
        pub	S_DBACV  *dbacv ;        /* valori        */
        pub	S_DBACF  *dbacf ;        /* flag         */
        pub	S_DBACU  *dbacu ;        /* zona impianto*/
	pub	S_DBALL  *dbacal;/* struttura allarmi */
#ifdef GERARC
        pub	S_DBGERA *dbacg;         /* gerarchia allarmi*/
#endif

/*
        analogici di diagnostica
*/
        pub	S_DBADV  *dbadv ;        /* valori        */
        pub	S_DBADF  *dbadf ;        /* flag         */
        pub	S_DBADU  *dbadu;        /* zona impianto*/
	pub	S_DBALL  *dbadal;       /* struttura allarmi */
#ifdef GERARC
        pub     S_DBGERA *dbadg;         /* gerarchia allarmi*/
#endif

/*
        analogici di uscita
*/
        pub	S_DBAOF *dbaof ;        /* flag         */
        pub	S_DBAOU *dbaou ;        /* zona impianto*/
	pub	S_DBAOM *dbaom ;        /* indice star associata     */
#ifdef GERARC
        pub     S_DBGERA *dbaog;         /* gerarchia allarmi*/
#endif

/*
        digitali acquisiti
*/
        pub	S_DBDA   *dbda;          /* flag e trattamento        */
        pub	S_DBDATR *dbdatr;        /* trattamento               */
        pub	S_DBDAU  *dbdau ;        /* zona impianto             */
	pub	S_CALIN  *dbdaco;   /* calc. e inbiz.            */
#ifdef GERARC
        pub     S_DBGERA *dbdag;         /* gerarchia allarmi*/
#endif

/*
        digitali calcolati standard
*/
        pub	S_DBDS   *dbds;          /* flag e trattamento */
        pub	S_DBDSTR *dbdstr;        /* trattamento */
        pub	S_DBDSU  *dbdsu ;        /* zona impianto */
	pub	S_CALIN  *dbdsco;        /* calc. e inbiz. */
        pub	S_DCALC  *dbdsde;        /* descrittore calcolata */
#ifdef GERARC
        pub     S_DBGERA *dbdsg;         /* gerarchia allarmi*/
#endif

/*
        digitali calcolati non standard
*/
        pub	S_DBDC   *dbdc;          /* flag e trattamento */
        pub	S_DBDCTR *dbdctr;        /* trattamento */
        pub	S_DBDCU  *dbdcu ;        /* zona impianto */
	pub	S_CALIN  *dbdcco;        /* calc. e inbiz. */
#ifdef GERARC
        pub     S_DBGERA *dbdcg;         /* gerarchia allarmi*/
#endif

/*
        digitali di diagnostica
*/
        pub	S_DBDD   *dbdd;          /* flag e trattamento */
        pub	S_DBDDTR *dbddtr;        /* trattamento */
        pub	S_DBDDU  *dbddu ;        /* zona impianto */
	pub	S_CALIN  *dbddco;        /* calc. e inbiz. */
#ifdef GERARC
        pub     S_DBGERA *dbddg;         /* gerarchia allarmi*/
#endif

/*
        digitali di uscita
*/
	pub	S_DBDO	*dbdo;		/* flag comandi	 */
        pub	S_DBDOU *dbdou ;        /* zona impianto */
	pub	S_DBDOM	*dbdom;	/* indice star associata	*/
#ifdef GERARC
        pub     S_DBGERA *dbdog;        /* gerarchia allarmi*/
#endif

/*
        organi
*/
        pub	S_DBOSC  *dbosc;         /* stato corr. e flag */
        pub	S_DBOSA  *dbosa;         /* stato atteso       */
        pub	S_DBOSP  *dbosp;         /* stato precedente   */
        pub	S_DBTO   *dbto;          /* time out     */
        pub	S_DBOU   *dbou;          /* zona impianto */
        pub	S_DBOFT  *dboft;         /* flag time-out */
        pub	S_DESORG *dbode;        /* descrittore        */
#ifdef GERARC
        pub     S_DBGERA *dbog;          /* gerarchia allarmi*/
#endif

/*
	stringhe
*/
        pub	S_DBSTTR  *dbsttr;        /* trattamento */
	pub	S_DBSTU   *dbstu;	 /* zona di impianto       */
	pub	S_DBSTV   *dbstv;    	 /* valore	      */
#ifdef GERARC
        pub     S_DBGERA  *dbstg;        /* gerarchia allarmi*/
#endif

/*
        definizione dei flag
*/
#define g2aa_gv 1               /* flag della acquisizione */
#define g2aa_fh 2
#define g2aa_fl 3
#define g2aa_ca 4          
#define g2aa_gf 5          

#define g2an_fs 0               /* flag analogici */
#define mask_afs 0x8000
#define g2an_fa 1
#define mask_afa 0x4000
#define g2an_fz 2
#define mask_afz 0x2000
#define g2an_st 3
#define g2an_au 7
#define g2an_ri 9
#define mask_ari        0x0040
#define g2an_al 5
#define g2an_dh 10
#define mask_adh        0x0020
#define g2an_dl 11
#define mask_adl        0x0010
#define g2an_hs 12
#define mask_ahs        0x0008
#define g2an_ls 13
#define mask_als        0x0004
#define g2an_hc 14
#define mask_ahc        0x0002
#define g2an_lc 15
#define mask_alc        0x0001
/*
        Definizione maschere per estrarre trattamento e livello
        di severita' (data base analogico)
        Definizione bit per analogici di diagnostica contatori
        allarmi per livello di severita'
*/
#define M_TRATA         0xF000
#define M_LSEVA         0x0C00
#define M_TRSEA         0xFC00
#define M_BMORA         0x03FF
#define g2an_s1 4
#define g2an_s2 6
#define g2an_s3 8

#define g2di_fs 0               /* flag digitali  */
#define mask_dfs 0x8000
#define g2di_fa 1
#define mask_dfa 0x4000
#define g2di_fz 2
#define mask_dfz 0x2000
#define g2di_st 3
#define mask_dst 0x1000
#define g2di_in 4
#define g2di_au 5
#define g2di_ri 6
#define g2di_sl 7
#define mask_sl 0x0100
#define g2di_asl 8		/* stato acquisito	       */
#define g2di_afa 9		/* stato fa di acquisizione    */
			
                                /* flag trattamento digitali   */
#define g2di_ip 0               /* flag inversione polarita'   */
#define g2di_io 1               /* inibisce                    */
#define g2di_ic 3               /* contribuisce a calcolate    */
#define g2di_fo 4               /* in uso a fonia              */
#define g2di_id 5               /* ricalcolo periferica di     */
                                /* acquisizione                */

#define g2di_cA	6		/* categoria A		       */	
#define mask_cA 0x0200
#define g2di_cB	7		/* categoria B		       */	
#define mask_cB 0x0100
#define g2di_cC	8		/* categoria C		       */	
#define mask_cC 0x0080
/*
        Definizione maschere per estrarre trattamento e livello
        di severita' (data base digitale)
*/
#define M_TRATD         0x000F
#define M_LSEVD         0x0030
#define M_TRSED         0x003F
#define M_FLAGD         0xFC00

#define g2or_fs 0               /* flag organi     */
#define g2or_fa 1
#define g2or_fz 2
#define g2or_st 3
#define g2or_au 6
#define g2or_ri 7

#define g2or_it 0               /* flag timer var. spontanea */
#define g2or_ta 14              /* protezione                */
#define g2or_tc 15              /* comando                   */
#define mask_it 0xff80          /* maschera per it           */
#define mask_ta 0x02            /* maschera per ta           */
#define mask_tc 0x01            /* maschera per tc           */
/*
        Definizione maschere per estrarre trattamento e livello
        di severita' (data base organi)
*/
#define M_TRATO         0x0F    /* per avere trat. organi    */
#define M_LSEVO         0x30    /* per avere l_sever. organi */
/*
	definizione codici per inibizioni misure analogiche
*/
#define	g2in_all 0		/* inibiti sicurezza e conduzione	*/
#define	g2in_al	 1		/* inibiti limiti alti sic e con	*/
#define g2in_ba  2		/* inibiti limiti bassi sic e con	*/


/*
Definizione forzamento riconoscimento fase di startup
Set del bit 13
*/
#define ric13start  2    // set 2 because of bitset(..) function.(15-2 = 13)

/*
Define of the mask to acknowledge the alarms relative to the same point
Used for SICRE in order to maintain the alarms on the alarmPage compact.
Set del bit 6
*/
#define ric6compact 9    // set 9 because of bitset(..) function.(15-9 = 6)


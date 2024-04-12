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
	l`include diagnoan.inc contiene i puntatori
	di tutti gli analogici di diagnostica
*/
/*
	definizione area da azzerare prima di salvare 
	su disco i contatori di archivio
*/
#define ini_zero_ad	49 		// db_gio_set
#define fin_zero_ad	127
/*
	diagnostica archivi
*/
#define	arc_nc01	 0
#define	arc_nc02	 1
#define	arc_nc03	 2
#define	arc_nc04	 3
#define	arc_nc05	 4
#define	arc_nc06	 5
#define	arc_nc07	 6
#define	arc_nc08	 7
#define	arc_nc09 	 8
#define	arc_nc10	 9
#define	arc_nc11        10
#define	arc_nc12        11
#define	arc_nc13        12
#define	arc_nc14        13
#define	arc_nc15        14
#define	arc_nc16        15
#define	arc_nc17        16
#define	arc_nc18        17
#define	arc_nc19        18
#define	arc_nc20        19

#define	arc_fc01	20
#define	arc_fc02	21
#define	arc_fc03	22
#define	arc_fc04	23
#define	arc_fc05	24
#define	arc_fc06	25
#define	arc_fc07	26
#define	arc_fc08	27
#define	arc_fc09 	28
#define	arc_fc10	29
#define	arc_fc11        30
#define	arc_fc12        31
#define	arc_fc13        32
#define	arc_fc14        33
#define	arc_fc15        34
#define	arc_fc16        35
#define	arc_fc17        36
#define	arc_fc18        37
#define	arc_fc19        38
#define	arc_fc20        39
/*
	definizione locazioni per memorizzare data e ora e num. video
*/

#define num_vdummi      48

#define db_gioset       49
#define db_anno		50
#define db_mese		51
#define db_giorno 	52
#define db_ora		53
#define db_minuti	54
#define db_secondi	55
#define db_numgio	56
#define db_numset	57

#define err_code	58		// errori comunicazione ethernet
#define db_fileal	59		// n. file allarmi in uso

#define all_off		60		// primo indice in data base libero
					// per i contatori di allarme
					// il n. di analogici necessari
					// dipende dal n. di pagine e di archivi

#define db_falco1	110		// n. giorno e ora associato
				        // ad ogni file allarmi
#define db_falco2	111		// n. giorno e ora associato
#define db_falco3	112		// n. giorno e ora associato
#define db_falco4	113		// n. giorno e ora associato
#define db_falco5	114		// n. giorno e ora associato
#define db_falco6	115		// n. giorno e ora associato
#define db_falco7	116		// n. giorno e ora associato
#define db_falco8	117		// n. giorno e ora associato
/*
        definizione punti utilizzati nella copia
        files archivio su floppy 
*/
#define arccopy   36
#define arccorr   37

/*
        definizione offset iniziale punti per contatori allarmi da riconoscere
        in emissione ed in rientro (2 per ogni data base totale 12)
*/
#define allemdb1  72            /* allarmi in emissione data base 1 */
#define allridb1  73            /* allarmi in rientro   data base 1 */


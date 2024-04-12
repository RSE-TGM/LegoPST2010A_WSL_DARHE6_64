/**********************************************************************
*
*       C Header:               tipal.inc
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug  1 11:14:08 2003 %
*
**********************************************************************/
/* -> TIPAL.INC
 *       contiene i codici associati ai diversi tipi di allarme
        
        30 Dicembre 1992
        Inserimento livelli di severita'
 */

#include "defpub.h"


#define var_dig 	0
#define dia_sys 	1
#define mod_st  	2
#define com_ok  	3
#define sic_al  	4	
#define sic_ba  	5
#define con_al  	6
#define con_ba  	7
#define pun_forz 	8
#define non_att 	9
#define fuori_scan 	10
#define gr_var   	11
#define range_al 	12
#define range_ba 	13
#define ch_fser  	14
#define giun_fred 	15
#define mis_norm 	16
#define emi_com   	17
#define non_esi   	18
#define al_blank  	19
#define var_org  	20
#define com_fall 	21
#define prot_fall 	22
#define com_stop  	23
#define com_pas  	24
#define mod_hs   	25
#define mod_hc   	26
#define mod_ls   	27
#define mod_lc   	28
#if defined ALARM_SIGNAL
#define signal_a   	29
#define signal_b   	30
#define signal_c   	31
#define signal_d   	32
#define signal_e   	33
#define signal_f   	34
#define signal_g   	35
#define signal_h   	36
#define signal_i   	37
#define signal_j   	38
#define signal_k   	39
#define signal_l   	40
#define signal_m   	41
#define signal_n   	42
#define signal_o   	43
#define signal_p   	44
#define signal_q   	45
#define signal_r   	46
#define signal_s   	47
#define signal_t   	48
#define signal_u   	49
#define signal_v   	50
#define signal_w   	51
#define signal_x   	52
#define signal_y   	53
#define signal_z   	54
#endif
/*
        definizione dei tipi di allarme analogici; le inizializzazioni 
	delle tabelle seguenti sono contenute in ttipal.inc
*/
pub unsigned char all_an[] ; /* all. analogici */
pub unsigned char all_ac[] ; /* allarmi analogici acquisizione */

#if defined ALARM_SIGNAL
#define max_st  	55
#define max_st_no_sig  	29
#else
#define max_st  	29
#endif
#define max_trat	 7
#define max_liv 	 3
//pub char *stringhe[];  /* stringhe visualizzate a seconda del tipo di allarme */
pub char stringhe[][8];  /* stringhe visualizzate a seconda del tipo di allarme */

#define red 		1
#define green 		2
#define yellow 		3
#define blue 		4
#define magenta 	5
#define cyan 		6
#define white 		7

pub unsigned char color[max_st][max_trat]; 
pub char pri_all[];		/* priorita' stringhe allarmi		 */
				/* =0 stampante allarmi			 */
				/* =1 stampante tabulati		 */
#define trat_op 1               /* trattamento fs fz   		 	 */
#define trat_ac 1               /* trattamento flag acquisizione 	 */
#define trat_ne 4               /* tratamento punto non installato su fi */

#define first_trat      2	// primo trattamento associato ai colori



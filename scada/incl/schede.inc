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
	il file di include schede.inc	contiene i limiti
	associati ai diversi tipi di schede e la codifica
	di tali schede

        13 Luglio 1992
        Eliminate dichiarazioni short (DB_CONFIGURATORI)
*/
/*
	codifica tipi di schede	 analogiche
*/
#define		num_ts		11		/* numero massimo tipi schede */
#define 	ts_mux8		1
#define 	ts_mux24	2
#define		ts_loop  	3
#define		ts_conhw	4		/* contatori hardware	*/
#define		ts_consw	5		/* contatori software	*/
#define 	ts_diagno	6		/* di diagnostica	*/
#define		ts_logici	7		/* logici		*/
#define		ts_selta14	8		/* da STCR 14 bit	*/
#define		ts_selta20	9		/* da STRC 20 bit	*/
#define		ts_plc1		8		/* da plc tipo 1	*/
#define		ts_plc2		9		/* da plc tipo 2	*/
#define		ts_plc3		10		/* da plc tipo 3	*/
#define		ts_plc4		11		/* da plc tipo 4	*/
#define         ts_ch1          8               /* canale 1 Enel La Casella     */
#define         ts_ch2          10              /* canale 2 Enel La Casella     */
#define         td_ch           1               /* le schede di tipo ch occupano */
                                                /* 2 locazioni da 2048           */
/*
	definizione range schede e canali
  
		analogici
*/
#define		n_camux8	8		/* n. canali per mux8	*/
#define		n_camux24	24		/* n. canali per mux24	*/
#define		n_caloop	16		/* n. canali per loop	*/
#define		n_cacsw		6		/* n. canali per cont. soft */
#define		n_cachw		6		/* n. canali per cont. hard */
/*
	codifica tipi di schede	 digitali
*/
#define		num_td		9		/* numero massimo tipi schede */
#define 	td_int32	1
#define		td_int24	2
#define		td_loop  	3
#define 	td_diagno	4		/* di diagnostica	*/
#define		td_logici	5		/* logici		*/
#define		td_seltas	6		/* da STRC TS	*/
#define		td_seltac	7		/* da STRC TC	*/
/*
        nel caso selta se l'indice supera max_fisici vengono
        incrementati i tipi di td_offselta in modo da utilizzare
        oltre ai tipi 6 e 7 anche 8 e 9
*/
#define         td_offselta     2               
                                                
#define		td_plc1		6		/* da plc tipo 1	*/
#define		td_plc2		7		/* da plc tipo 2	*/
#define		td_plc3		8		/* da plc tipo 3	*/
#define		td_plc4		9		/* da plc tipo 4	*/

/*
		digitali
*/
#define		n_cdint32	32		/* n. canali per int	*/
#define		n_cdint24	24		/* n. canali per int	*/
#define		n_cdloop	32		/* n. canali per loop	*/


/*
	codifica tipi di schede	 digitali di uscita
*/
#define		num_tdo		9		/* numero massimo tipi schede */
#define 	tdo_dou32	1
#define		tdo_dou24	2
#define		tdo_loop  	3
#define		tdo_logici	4		/* logici		*/
#define		tdo_selta	6		/* da STCR */
#define		tdo_plc1  	6		/* da plc tipo 1	*/
#define		tdo_plc2  	7		/* da plc tipo 2	*/
#define		tdo_plc3  	8		/* da plc tipo 3	*/
#define		tdo_plc4  	9		/* da plc tipo 4	*/

/*
		digitali di uscita
*/
#define		n_cddou32	32		/* n. canali per int	*/
#define		n_cddou24	24		/* n. canali per int	*/
#define		n_cdoloop	32		/* n. canali per loop	*/

/*
	codifica tipi di schede	 analogici di uscita
*/
#define		num_tao		8		/* numero massimo tipi schede */
#define 	tao_ao8		1
#define		tao_ao4		2
#define		tao_loop  	2
#define		tao_logici	4		/* logici		*/
#define		tao_selta14	5		/* da STCR 14 bit	*/
#define		tao_selta20	6		/* da STRC 20 bit	*/
#define		tao_plc1  	5		/* da plc tipo 1	*/
#define		tao_plc2  	6		/* da plc tipo 2	*/
#define		tao_plc3  	7		/* da plc tipo 3	*/
#define		tao_plc4  	8		/* da plc tipo 4	*/
/*
		analogici di uscita
*/
#define		n_cao8		 8		/* n. canali per ao	*/
#define		n_cao4		 4		/* n. canali per int	*/
#define		n_caoloop	16		/* n. canali per loop	*/


/*
	definisco il numero massimo di punti per ogni
	tipo di scheda
*/
#define 	max_fisici	2048

/*	
	definisco il numero massimo di periferiche
*/

#define		maxperi		32


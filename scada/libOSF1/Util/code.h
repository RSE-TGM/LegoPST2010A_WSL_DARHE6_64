/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef _code_h
#define _code_h


#define num_code 40		/* numero code associate al processo	*/

#define dim_0	9000
#define dim_1	9000
#define dim_2	9000
#define dim_3	9000
#define dim_4	9000
#define dim_5	9000
#define dim_6	9000
#define dim_7	9000
#define dim_8	9000
#define dim_9	9000
#define dim_10	9000
#define dim_11	9000
#define dim_12	9000
#define dim_13	9000
#define dim_14	9000
#define dim_15	9000
#define dim_16	9000
#define dim_17	9000
#define dim_18	9000
#define dim_19	9000
#define dim_20	9000
#define dim_21	9000
#define dim_22	9000
#define dim_23	9000
#define dim_24	9000
#define dim_25	9000
#define dim_26	9000
#define dim_27	9000
#define dim_28	9000
#define dim_29	9000
#define dim_30	9000
#define dim_31	9000
#define dim_32	9000
#define dim_33	9000
#define dim_34	9000
#define dim_35	9000
#define dim_36	9000
#define dim_37	9000
#define dim_38	9000
#define dim_39	9000

/* dimensione globale delle code */

#define tot_dim dim_0+dim_1+dim_2+dim_3+dim_4+dim_5+dim_6+dim_7+dim_8+dim_9+dim_10+dim_11+dim_12+dim_13+dim_14+dim_15+dim_16+dim_17+dim_18+dim_19+dim_20+dim_21+dim_22+dim_23+dim_24+dim_25+dim_26+dim_27+dim_28+dim_29+dim_30+dim_31+dim_32+dim_33+dim_34+dim_35+dim_36+dim_37+dim_38+dim_39

char  buff_code[tot_dim];      /* buffer coda                      */

struct s_code {	int	dim ;	/* dimensione			*/
		int	passo;	/* passo			*/
		int	occup;  /* occupazione			*/
		int	init;	/* word inizio			*/
		int	fine;	/* word fine			*/
		int	acc ;	/* puntatore accodamento	*/
		int	sco ;	/* puntatore scodamento		*/
		pthread_cond_t  condition_r;       /* condition per attesa sulla
						      coda in ricezione  */
        	pthread_mutex_t mutex_condition_r; /* mutex per attesa sulla
						      coda in ricezione  */
		pthread_cond_t  condition_s;       /* condition per attesa sulla
						      coda in trasmissione  */
        	pthread_mutex_t mutex_condition_s; /* mutex per attesa sulla
						      coda in trasmissione  */
        	pthread_mutex_t mutex;             /* mutex per il lock di 
					              accesso alla coda */
	       } cd[num_code] ;

#endif

/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#define NTRENDOPR 20
#define trend_num 20

// struttura del header di descrizione della trend
typedef struct _tren {
                        char nome[SCD_SIGLA+1];
                        char descr[SCD_DESCRIZIONE+1];
                        } TRENDEDT;
// struttura del descrittore delle trend su file operativo
typedef struct _trenopr {
                        char nome[SCD_SIGLA+1];
                        char descr[SCD_DESCRIZIONE+1];
                        char sigla[trend_num][SCD_SIGLA+1];
								short tipo[trend_num];
                        short indice[trend_num];
                        } TRENDOPR;

typedef struct 	_trenstat{
						int atti_trend;	/* flag trend in corso	*/
						int ini_atti;		/* flag inizializzazione trend  */
						int	trendcurr;	/* indice trend corrente	*/
						int perio_trend;	/* periodo aggiornamento trend (in minuti)	*/
						TRENDOPR trendwork; /* descrittore trend	*/
						} TRENSTAT;

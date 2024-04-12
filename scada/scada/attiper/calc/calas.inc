/**********************************************************************
*
*       C Header:               calas.inc
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Oct  1 16:23:29 1997 %
*
**********************************************************************/
/***************************************************************
**      include calas.inc definisce :
**      - puntatori alla primo descrittore per classe
**        di scansione
**      - coefficienti per il calcolo di :
**              - media
**              - filtro
**              - integrale
**              - scarto quadratico medio
**              - media istantanea
**              - somma
**      - coefficienti per il calcolo del polinomio per le portate
**        UNI/AGA.
**
**      - matrice "reset" : n. righe= n_periodi
**                          n. colonne= n_freset
**              periodo  01 : ore - mesi - anni - giorni
**              periodo  05 : ore - mesi - anni - giorni
**              periodo  15 : ore - mesi - anni - giorni
**              periodo  30 : ore - mesi - anni - giorni
**              periodo  60 : ore - mesi - anni - giorni
**
****************************************************************/

#include "defpub.h"

#define n_periodi 5
#define n_freset  5             // ora, giorno, mese, anno, utente

#define x0 -0.40771769
#define x1  0.0094312288
#define x2 -0.0079245458
#define x3 -0.000015545434
#define x4  0.0000070988867
#define x5  0.000018355684

/*
definisco tipi di allarme
*/
#define  ALL_A    0
#define  ALL_N    13
#define  ALL_W    22
#define  ALL_M    12
#define  ALL_T    19
#define  ALL_S    18
#define  ALL_F    5
#define  PACK_DIMENSION     8      
#define  PRIE_DIMENSION     16    /* 
				     dimensioni in bit di un pacchetto
				     per classe di allarme (PEN e ARC)
				  */

// gi… definiti in comunic.inc, qui li forzo extern:

extern float coef_media;			
extern float coef_filtro;
extern float coef_scarto;
extern float coef_mist;
extern float coef_integrale ;
extern float coef_somma;
extern int   reset_ut;

#define fcoef_media     0.4		// valori di default
#define fcoef_filtro    0.4
#define fcoef_scarto    0.6
#define fcoef_mist	0.4
#define fcoef_integrale 0.4
#define fcoef_somma	0.4


pub short   reset[n_periodi][n_freset], attiva[n_freset];

pub DES     *desc;
pub short   boxcalc;        /*box per sincronizzazione*/
pub struct periodo_scan {
                char period ;           /*per. 1 5 15 30 60     */
                char count_periodo;     /* contatore periodo    */
                DES  *inizio;           /* punt. inizio classe  */
                DES  *corrente;         /* punt. calc. corrente */
                short ncalt;            /* n. calc. classe      */
                short ncals;            /* n. calc. classe al sec */
                short count;            /* contatore calcolate    */
                short indice;           /* indice in data base    */
                                        /* calcolata inizio classe*/
                short addr_corrente;    /* indice in data base    */
                                        /* calcolata corrente     */
                    } tab_cal[n_periodi],
                      *tab;
/*
        parametri reset frequenza
*/

#define f_ora 0
#define f_gio 1
#define f_mes 2
#define f_ann 3
#define f_ut  4


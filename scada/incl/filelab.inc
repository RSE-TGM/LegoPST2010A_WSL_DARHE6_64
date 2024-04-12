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
        file filelab.inc
        contiene le informazioni relative ai file delle
        eleborazioni fel-<aa as ac da dc ds ao ad do dd or>

        il file viene incluso dalla function modfel che
        modifica i contatori
        e da tutti i processi per la open dei file

*/
#include "defpub.h"


pub FILE *fpfelaa,*fpfelas, *fpfelac, *fpfelad, *fpfelao ;
pub FILE *fpfelda,*fpfelds, *fpfeldc, *fpfeldd, *fpfeldo ;
pub FILE *fpfelor,*fpfelst ;
#define rec_felab       32   /* 14 cont. + 4 byte flags */
#define b_flag 4             /* n. bytes per flag */
/*
        definizione bit per i file felab
*/
#define b_def 0
#define b_agg 1
#define b_arcl 2
#define b_arcv 3
#define num_cont 14   /* n. contatori */
/*
        definizione contatori
*/
#define c_calcstd  0    /* calcolate standard           */
#define c_calcnstd 1    /* calcolate non standard       */
#define c_tabul   2     /* tabulati                     */
#define c_pagine    3   /* pagine video                 */
#define c_allarme   4   /* limiti allarmi               */
#define c_giunto   5    /* giunto freddo                */
#define c_inibi    6    /* inibizioni                   */
#define c_setpoint 7    /* set point                    */
#define c_pas      9    /* processi applicativi         */
#define c_comandi  10   /* comandi                      */
#define c_archivi 11    /* archivi                      */
#define c_byte    12    /* contribuenti a byte          */

#define c_off_flag  (b_flag/2)    /* offset word flags          */

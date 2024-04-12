/**********************************************************************
*
*       C Header:               filtri.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:03:04 1996 %
*
**********************************************************************/
/*=====================================================================================
 |                                                                                    |
 | Filtri.h   	                                                                      |
 |                                                                                    |
 | In questo modulo sono contenute le definizioni utilizzate dalla applicazione per   |
 | la creazione e gestione dei filtri.                                                |
 |                                                                                    |
 | 31-5-93                                                                            |
 |                                                                                    |
 ====================================================================================*/

#ifndef FILTRI_H
#define FILTRI_H

#define MAXCHNAME      20                /* numero massimo caratteri nome filtro */
#define MAXPARFILTRO   10                /* numero massimo parametri filtro */
#define MAXCHARPAR      4                /* numero massimo caratteri parametri filtro */
#define MAXPATHLEN     100               /* lunghezza massima filepath */
#define MAXFILTRI     100                /* numero massimo filtri */
   
typedef struct {
                     char nome_filtro[MAXCHNAME];
                     short num_var;
                     char *var[MAXPARFILTRO];
               }FILTRI;                                          /* struttura filtro */ 

#define DIM_FILTRO sizeof(FILTRI)                                /* dimensione struttura FILTRO */
#define DIM_PAR sizeof( (sizeof(char) * MAXCHARPAR) )            /* dimensione vettore var del FILTRO */

#define TAPPO "FILTRO"                    /* stringa di tappo in lettura file di editing */

/*==================== DEFINIZIONE ERRORI ================================*/     

#define OK           1             
#define ERROPEN    -10            /* errore apertura file */

#define NEW_FILTRO  80  /* operazione di inserimento nuovo filtro */
#define OPEN_FILTRO 90  /* operazione di aggiornamento di un filtro */
#define FILE_SAVE   70  /* operazione di salva file */
#define FILE_OPEN   60  /* operazione di open file */
#define NOMEFILEDIEDITING "filtri.edf"               /* nome del file di editing */


#endif

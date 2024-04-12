/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#define NPAGOPR 200
#include "tag.h"
#define pnt_num 16

// struttura del header di descrizione della pagina
typedef struct _pagina {
                        char nome[SCD_SIGLA+1];
                        char descr[SCD_DESCRIZIONE+1];
                        } PAGEDT;
// struttura del descrittore delle pagine su file operativo
typedef struct _pageopr {
                        char nome[SCD_SIGLA+1];
                        char descr[SCD_DESCRIZIONE+1];
                        char sigla[pnt_num][SCD_SIGLA+1];
								short tipo[pnt_num];
                        short indice[pnt_num];
                        } PAGEOPR;

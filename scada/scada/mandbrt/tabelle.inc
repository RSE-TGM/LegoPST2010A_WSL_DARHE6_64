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
        nell'include tabelle.inc vengono definite
        le posizioni del cursore per i vari elementi
        ed i puntatori delle misure da visualizzare
*/

#include "defpub.h"

#define num_punti 4
#define num_righe 5

#define nom_pos 3          /* off_...  riga */
#define descr_pos 14       /* ..._pos  colonna */
#define umis_pos  39
#define off_allv 3
#define off_alls 2
#define off_flag 1
#define off_tipo 1
#define tipo_pos 65
#define sa_pos   1
#define sb_pos   20
#define ca_pos   40
#define cb_pos   60
#define off_flaa 1
#define off_val  0
#define val_pos  48
#define flaa_pos 55
#define flag_pos 1
#define st0_pos  40
#define st1_pos  60
#define off_stats 2
#define off_statv 3
#define off_tipor 2
#define tiporg_pos 14
#define tiporgdes_pos 40
#define flat_pos  55
#define dbus_pos   3
#define dims_pos   14
#define elems_pos  25
/*
        tabella che contiene i puntatori delle misure
        ed i loro tipo
*/
pub struct vis
{
       short  punt[num_punti];
        unsigned char ext[num_punti];
}
  vispun ;
pub S_FSTATO  tab_stato[g0dimtip] ;         /* stati ammissibili tipi organi */
pub short     n_elem[num_punti];      /* per punti utente:numero dell'elemento
                                  da  visualizzare              */



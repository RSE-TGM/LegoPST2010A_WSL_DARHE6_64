/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*-> frange

     Tabella dei valoro di fuori range associati agli analogici
     acquisiti in millivolt

*/
#include "defpub.h"

static  short  frange[] = {    /* valore fr. basso e fr. alto */

        1000, 5000,  /* codice  0 */
        1100, 5000,  /* codice  1 */
        0000, 5000,  /* codice  2 */
         100, 5000,  /* codice  3 */
         200, 5000,  /* codice  4 */
         300, 5000,  /* codice  5 */
         400, 5000,  /* codice  6 */
         500, 5000,  /* codice  7 */
         600, 5000,  /* codice  8 */
         700, 5000,  /* codice  9 */
         800, 5000,  /* codice 10 */
         900, 5000,  /* codice 11 */
        1000, 4900,  /* codice 12 */
        1000, 4800,  /* codice 13 */
        1000, 4700,  /* codice 14 */
        1000, 4600,  /* codice 15 */
        1000, 4500,  /* codice 16 */
        1000, 4400,  /* codice 17 */
        1000, 4300,  /* codice 18 */
        1000, 4200,  /* codice 19 */
        1000, 4100,  /* codice 20 */
        1000, 4000,  /* codice 21 */
        1000, 4500,  /* codice 22 */
        2000, 5000,  /* codice 23 */
        2000, 4500,  /* codice 24 */
        1000, 3000,  /* codice 25 */
        3000, 5000,  /* codice 26 */
        4000, 5000,  /* codice 27 */
        1000, 2000,  /* codice 28 */
        3000, 4000,  /* codice 29 */
           0,    0,  /* codice 30 */
           0,    0,   /* codice 31 */
        } ;

#define nvrange (sizeof(frange)/2) 

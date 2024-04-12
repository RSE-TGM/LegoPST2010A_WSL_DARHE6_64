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
        il file di include g1tipdb.inc contiene
        i tipi di data base ammessi
*/
#define g1tipaa   1       /* analogici acquisiti                 */
#define g1tipas   2       /* analogici calcolati standard        */
#define g1tipac   3       /* analogici calcolati non standard    */
#define g1tipad   4       /* analogici di diagnostica            */
#define g1tipao   5       /* analogici di uscita                 */

#define g1tipda   7       /* digitali  acquisiti                 */
#define g1tipds   8       /* digitali  calcolati standard        */
#define g1tipdc   9       /* digitali  calcolati non standard    */
#define g1tipdd   10      /* digitali  di diagnostica            */
#define g1tipdo   11      /* digitali  di uscita                 */
#define g1tipby   16      /* aggregato byte                      */

#define g1tipto   12      /* tipo organo                         */
#define g1tipor   13      /* organi                              */
#define g1tipst   14      /* stringhe                            */


#define g0dimtip    32    /* tipi di organi                      */

/*
	attenzione i tipi di soglia devono essere nell'ordine
	sotto specificato altrimenti la routine verifall e'
	da rivedere
*/
#define g1tiphs	 0	/* 	alta sicurezza			*/
#define g1tipls	 1	/* 	bassa sicurezza			*/
#define g1tiphc	 2	/* 	alta conduzione			*/
#define g1tiplc	 3	/* 	bassa conduzione		*/


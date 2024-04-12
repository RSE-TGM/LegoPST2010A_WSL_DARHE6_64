/**********************************************************************
*
*       C Header:               fpp.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:07:51 1996 %
*
**********************************************************************/

/* fpp.h
 scopo:
   registrare le paia (o-var Known, i-var Unknown)
 Nota:
   il file "fpp.dat" deve trovarsi nella directory corrente.
 Autore: C.Lusso(CISE) 1994/05/03
 */

/* nome:	int read_file_fpp( 3 arg )
 *	routine per leggere il file FPP_NAME;
 * return:	ritorna n. paia lette, 0 altrimenti;
 * arg	1 -O-   tabella nomi out-vars in paia
 *	2 -O-   tabella nomi inp-vars in paia
 * NOTA: gli arg 2 e 3 devono essere preparati dal chiamante !!!
 */
int read_file_fpp( char **azPout, char **azPinp );

/* nome:	void write_file_fpp( 4 arg )
 *	routine per scrivere il file FPP_NAME;
 * return:	;
 * arg	1 -I-   nome modello;
 *	2 -I-   n. paia;
 *	3 -I-   tabella nomi out-vars in paia
 *	4 -I-   tabella nomi inp-vars in paia
 */
void write_file_fpp( char *zModel, int cPair, char **azPout, char **azPinp);

/**********************************************************************
*
*       C Header:               backtrack.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Mon Jun 16 17:37:53 1997 %
*
**********************************************************************/
/*
 * backtrack.h
 */
#ifndef BACKTRACK_H
#define BACKTRACK_H
/*******************************************************************/
/******** rendere parametrico 8apr97 fm
Widget BtScrollForm[MAX_BACK_TRACK];
Widget BtNumber[MAX_BACK_TRACK];
Widget BtDate[MAX_BACK_TRACK];
Widget BtSimtime[MAX_BACK_TRACK];
char n_entry[MAX_BACK_TRACK][4];
int punt_rec_backtrack[MAX_BACK_TRACK+1];
int punt_rec_bt[MAX_BACK_TRACK+1];      
************************************/

Widget *BtScrollForm;
Widget *BtNumber;
Widget *BtDate;
Widget *BtSimtime;
char *n_entry;
int *punt_rec_backtrack; 					/* per la lista      */
int *punt_rec_bt;        					/* per bt management */

void BtSelActivate();
int bt_punt;                        /* entry attualmente puntata */
int bt_sel;                         /* entry sel. in bt mngmnt */

int contatore_sessioni;
int background_backtrack; /* colore sfondo background management */

int direzione_bt;
int modo_bt;
int numero_step;       /* numero bt registrati                          */

#define BT_FORWARD   0 /* direzione backtrack avanti                    */
#define BT_REVERSE   1 /* direzione backtrack indietro                  */
#define BT_MANUAL    0 /* modo backtrack manuale                        */
#define BT_AUTO      1 /* modo backtrack automatico                     */
/*********************************************************************/
#endif

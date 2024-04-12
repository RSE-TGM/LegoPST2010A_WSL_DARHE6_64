/**********************************************************************
*
*       C Header:               parametri.h
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Tue Jul 14 16:45:18 1998 %
*
**********************************************************************/
/*
 * parametri.h
 *
 * parametri comuni dell' applicazione
 */
#ifndef PARAMETRI_H
#define PARAMETRI_H
/***************************************************************/
#define MAX_COLORS 	15

static char *nomi_colori[] = 
	{
	"Red","Green","Medium Blue","Slate Gray", "Gray", "Light Sea Green", 
	"Forest Green","Yellow","Yellow Green","black",
	"NULL"
	};

int colore_app[MAX_COLORS];     /* colori utilizzabili dall' applicazione */
#define COLORE_FREEZE	7   /* colore_app[6]      */
#define COLORE_RUN      6
#define COLORE_STOP     0
#define COLORE_ERROR    0
#define COLORE_BACKTRACK 8
#define COLORE_REPLAY    1      

#define COLORE_INSERTED	7
#define COLORE_REMOVED	8
#define COLORE_ACTIVE	0

#define COLORE_BLINK    7      
#define COLORE_MODIFY   2      

#define MAX_TITLE_LUN 	40  /* titolo di sessione */


#define MESS_FILE    "banco.log"
#define VIEW_FILE    ".preview"

#define FAILED       "FAILED"
#define LIVELLO_1 	1
#define LIVELLO_2    2
#define LIVELLO_3    3

#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN  200
#endif
/*
 * parametri per tipi dialogo
 */
#define DIALOG_ERROR  XmDIALOG_ERROR
#define DIALOG_INFORMATION XmDIALOG_INFORMATION
#define DIALOG_MESSAGE XmDIALOG_MESSAGE
#define DIALOG_QUESTION XmDIALOG_QUESTION
#define DIALOG_WARNING XmDIALOG_WARNING
#define DIALOG_WORKING XmDIALOG_WORKING

#define COLORE_DIALOG_ERROR 0

#define TMP_FILE_SNAP  ".tmp_fileSnap"/* file tmp per funzioni di stampa snap */
/***************************************************************/
#endif

/**********************************************************************
*
*       C Header:               note.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:07:37 1996 %
*
**********************************************************************/
/* file header note.h */

struct header_note {
                      char nota[6];
                      char *testo;
                      struct header_note *next_header;
                   };

typedef struct header_note HeaderNote;

/* struttura per le note di calcolo dei blocchi */
typedef struct {
		  ModelBlockStruct *pblock;
		  HeaderNote *note_di_calcolo;
	       } NoteDelBlocco;

HeaderNote *cerca_testo();
HeaderNote *cerca_elem_prec();
HeaderNote *appendi_lista();

void aggiorna_testi();

/* fine note.h */

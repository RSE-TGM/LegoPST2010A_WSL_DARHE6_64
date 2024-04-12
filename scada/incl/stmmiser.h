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
	strutture dati per mmi su linea seriale LA CASELLA  */


#define len_index 2
#define len_header 11
#define BLK_NUM 40
#define MAX_BLK   42

typedef struct  {
				short indice;
				short tipo;} PNT;

typedef struct {
				  char  header[len_header+1];
				  PNT   punto[BLK_NUM];} BLKOPR ;


/* definizione area dati operativa del task  caricata da init in attivazione */

BLKOPR  blkser[MAX_BLK];

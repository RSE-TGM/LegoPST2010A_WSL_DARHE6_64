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
   modulo snap_sked.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)snap_sked.h	5.1
*/
/**************************************************************************/
/*
 *   snap_sked.h         definizioni dati da e verso lo skeduler
 *                       per esecuzione snapshot
 */

/*
 *   SNAPSHOT
 *   verso sked:         sommario mf
 *                       sommario fr
 *
 *   da sked   :         data dello snap
 *                       ora dello snap
 *
 */
/*
 *  struttura dati per skeduler
 *
 */

struct dati_snap_sked
	{
	int somm_snappati;		    /* se e' uguale a SNAP i sommari
					       sono snappati               */
	struct readfr_st readfr;            /* sommario funzioni remote    */
	struct readmf_st readmf;            /* sommario malfunzioni        */
	};

typedef struct dati_snap_sked SNAP_SKED;



#define SOMMARI_SNAPPATI	1234

/**************************************************************************/

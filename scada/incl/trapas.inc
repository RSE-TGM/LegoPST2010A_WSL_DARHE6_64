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
	il file di include trapas contiene le tabelle di trigger
	per i processi applicativi
	1 word per ogni tipo di punto
*/

typedef struct s_trigger_pas   {unsigned char seq;
				unsigned char pas; } S_TRIGGER_PAS ;
#include "defpub.h"

pub  S_TRIGGER_PAS *pasaa;
pub  S_TRIGGER_PAS *pasas;
pub  S_TRIGGER_PAS *pasac;
pub  S_TRIGGER_PAS *pasad;
pub  S_TRIGGER_PAS *pasao;
pub  S_TRIGGER_PAS *pasda;
pub  S_TRIGGER_PAS *pasds;
pub  S_TRIGGER_PAS *pasdc;
pub  S_TRIGGER_PAS *pasdd;
pub  S_TRIGGER_PAS *pasdo;
pub  S_TRIGGER_PAS *pasor;


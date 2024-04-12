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
	il file di include organi.inc contiene le tabelle per la suddivisione
	dei timer degli organi
*/
#include "defpub.h"

pub short inizio_or ;
pub struct s_or { short iniz;
              short num ;} or_tab[5] ;

#define st_trans	0
#define st_incon	1


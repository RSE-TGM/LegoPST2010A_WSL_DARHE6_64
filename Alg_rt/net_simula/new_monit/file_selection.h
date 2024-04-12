/**********************************************************************
*
*       C Header:               file_selection.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:36:48 1997 %
*
**********************************************************************/
/*
 * file_select.h
 */
#ifndef _FILE_SELECT_INCLUDED
#define _FILE_SELECT_INCLUDED
/*****************************************************************/
#define VAR_FOR_CR	1 /* applicazione chiamante fileSelection */
#define PREVIEW_FILE	2 /* applicazione chiamante fileSelection */
#define SCENARIO_MALF	3 /* applicazione chiamante fileSelection */

#ifndef VAR_FOR_CR_PATTERN
#define VAR_FOR_CR_PATTERN		"*.c_rec"
#endif
#ifndef PREVIEW_FILE_PATTERN
#define PREVIEW_FILE_PATTERN  "*.view"
#endif

#define FILE_ERRORE	"NO_FILE"


/*****************************************************************/
#endif

/**********************************************************************
*
*       C Header:               mainOptions.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:39:33 1997 %
*
**********************************************************************/
/*
 * mainOptions.h
 *
 * elenco opzioni del processo banco
 */
#ifndef MAIN_OPTIONS_INCLUDED_
#define MAIN_OPTIONS_INCLUDED_
/********************************************************************/
#define MAX_MAINOPTIONS	4       /* max numero di opzioni del main   */

#define USER_POSITION  	1		  /* user definition in posizione 2   */
#define SPARE1_POSITION 2       /* spare                            */
#define SPARE2_POSITION 3       /* spare                            */
#define SPARE3_POSITION 4       /* spare                            */

#define SUPERUSER_KEY   "SUPERUSER"

static Pixmap nullSpace;        /* vuoto                            */
static Pixmap LockedIc;         /* lucchetto                        */
static Pixmap ModifiedIc;       /* previous topology                */
/********************************************************************/
#endif

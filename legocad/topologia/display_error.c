/**********************************************************************
*
*       C Source:               display_error.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 13:58:29 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: display_error.c,2 %  (%full_filespec: 1,csrc,display_error.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)display_error.c	2.24\t3/30/95";
/*
        Fine sezione per SCCS
*/

/*
 * display_error.c
 *
 * Il modulo contiene le routine utilizzate dal modulo errore.c
 * per visualizzare un errore o un warning
 */




show_warnings( mess )
char *mess;
{
   write_message( mess );
}


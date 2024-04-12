/**********************************************************************
*
*       C Header:               sdi_fileop.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Jun 20 14:18:45 1996 %
*
**********************************************************************/
#define FILEOP_INCL
/*
        file fileop.inc

        contiene la definizione dei record dei file
        operativi
	Modificato da Fabio 20/6/96 per aggiornamento con nuove dimensioni
	dimensioni tag:8->20
	e dimensioni descrizioni: 24->60
*/
#define rec_fdaa        88   /* 20 punto 60 desc 8 unita' mis. */
#define rec_fdas        88   /* 20 punto 60 desc 16 stati 0 e 1*/
#define rec_fdac        88   /* 20 punto 60 desc 10 impianto */
#define rec_fdad        88   /* 20 punto 60 desc 8 unita' mis. */
#define rec_fdao        88   /* 20 punto 60 descrizione     */
#define rec_fdda        96   /* 20 punto 60 desc 16 stati 0 e 1*/
#define rec_fdds        96   /* 20 punto 60 desc 16 stati 0 e 1*/
#define rec_fddc        96   /* 20 punto 60 desc 16 stato 0 e 1*/
#define rec_fddd        96   /* 20 punto 60 desc 16 stati 0 e 1*/
#define rec_fddo        80   /* 20 punto 60 descrizione     */
#define rec_fdor        90   /* 20 punto 60 desc 10 tipo organo */
#define rec_fdst        80   /* 20 punto 60 desc  */

/*
	definizione offset per file descrittore unico
	fdde
*/
#define of_fdaa 	0
#define of_fdas		((long)of_fdaa+(long)rec_fdaa*(long)h_db.dimaa)
#define of_fdac		((long)of_fdas+(long)rec_fdas*(long)h_db.dimas)
#define of_fdad		((long)of_fdac+(long)rec_fdac*(long)h_db.dimac)
#define of_fdao		((long)of_fdad+(long)rec_fdad*(long)h_db.dimad)
#define of_fdda		((long)of_fdao+(long)rec_fdao*(long)h_db.dimao)
#define of_fdds		((long)of_fdda+(long)rec_fdda*(long)h_db.dimda)
#define of_fddc		((long)of_fdds+(long)rec_fdds*(long)h_db.dimds)
#define of_fddd		((long)of_fddc+(long)rec_fddc*(long)h_db.dimdc)
#define of_fddo		((long)of_fddd+(long)rec_fddd*(long)h_db.dimdd)
#define of_fdor		((long)of_fddo+(long)rec_fddo*(long)h_db.dimdo)
#define of_fdst		((long)of_fdor+(long)rec_fdor*(long)h_db.dimor)


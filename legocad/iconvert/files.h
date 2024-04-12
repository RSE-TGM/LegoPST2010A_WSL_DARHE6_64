/**********************************************************************
*
*       C Header:               files.h
*       Subsystem:              2
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:04:50 1996 %
*
**********************************************************************/
/* files.h - costanti e tipi utilizzati in files.c */

/* Buffo Massimo, Calleri Nicola 10/11/1992 */

/* nomi di files utilizzati */
#define FILE_MACROBLOCKS	"macroblocks.dat"
#define FILE_MACROBLOCKS_TMP	"macroblocks.tmp"
#define FILE_F01		"f01.dat"

/* posizioni delle informazioni nel file macroblocks.dat */
#define OFFS_NOME_MACRO		0
#define OFFS_POSIZ_MACRO	15
#define OFFS_DESCR_MACRO	25

/* Prototipi di funzione */
char *calloc_mem();
char *realloc_mem();

/* fine files.h */

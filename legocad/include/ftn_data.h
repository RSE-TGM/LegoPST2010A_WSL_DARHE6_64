/**********************************************************************
*
*       C Header:               ftn_data.h
*       Subsystem:              2
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:02:14 1996 %
*
**********************************************************************/
/* file ftn_data.h
 Contiene le definizioni delle variabili e degli array utilizzati
 nella lettura dei file fortran F03.DAT e F11.DAT */
#ifdef DOUBLE_PREC
typedef double _REAL;
#else
typedef float _REAL;
#endif

#define   FILE_F03	"proc/f03.dat"
#define   FILE_F11	"proc/f11.dat"

#define   TRUE	1
#define   FALSE 0

#define BUFSIZE	512 /* dimensione massima per lettura da file fortran
			*/

#define DIMTIPO(tipo,n)	((n)*(sizeof(tipo)))


/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
//	********************************************************
//  fio.h
//
//  Definizioni per File I/O dal P.O.L.
//
//	Versione: 	1.00    data: 10 - 01 - 90  by Stefanini
//
//	Revisioni:	xxxx    data: xx - xx - xx  by        
//
//	********************************************************

#define	LRECFIO 			256 	// lunghezza in byte buffer di i/o e record file
#define  LRECFIO_EXP2	8		// exp di base 2

//#define	FIO_NULL 		0 	
#define	FIO_ANALOG 		0 	
#define	FIO_DIGIT 		1 	
#define	FIO_ORGANO 		2 	
#define	FIO_REAL 		3 	
#define	FIO_INT 			4 	
#define	FIO_LOG 			5 	
#define	FIO_STRING 		7 	

#define FILL_PATT	-1			// pattern di riempimento spazio disponibile

/***
	elemento vettore lista argomenti (ultimo elemento, campi a -1)
	alle routine _fread e _fwrite
***/
struct ARGLIST		
{
	char	td;		// tipo di dato 
	char	sz;		// lunghezza dato in byte
	char  *pd;		// indirizzo
};


extern  int __fwrite(struct ARGLIST *arglist);
extern  int __fread(struct ARGLIST *arglist);
extern  int __fdelete(struct ARGLIST *arglist);
extern  char *_fnamvar(short fileid,char *filename);
extern  char _fchks(char *b,short l);
void	fiodosw(char *fname,long recno,char *buffer,short len);
void	fiodosr(char *fname,long recno,char *buffer,short len);


/**********************************************************************
*
*       C Source:               fio.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Fri Dec 13 14:39:00 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: fio.c-3 %  (%full_filespec: fio.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
//	********************************************************
//  fio.c
//
//  Comandi per File I/O dal P.O.L.
//
//	Versione: 	1.00    data: 10 - 01 - 90  by Stefanini
//
//	Revisioni:	1.01    data: 21 - 11 - 91  by FC
//                     per problemi stack (?) portato in common
//                     buffer       
//
// 17/09/93 mp porting a 32 bit
//
// 16 Marzo 1995 FC
//    Corretta Open in caso di creazione file non veniva inserita
//    l'opzione read/write
//
//	********************************************************

#include <osf1.h>
#include <stdlib.h>
//#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "dconf.inc"
#include "fio.h"
#include "pscs.cfg"

#ifdef ETH
#include "gpunt.inc"
#include "mesprocv.inc"
#include "mesqueue.h"
extern short cc_scadao;
extern short privato;

BRICFIO	bric;

#endif

__fwrite(arglist)
	struct ARGLIST *arglist;	// lista argomenti
	{
   char 	buffer_fio[LRECFIO+2];			
//	FILE *fp;
   int hf;
	char 	fname[FILENAME_MAX+1];			
	short lbuff=0;
	register larg;
	short fileid,recno;
   long pos;
   char  *pbload;
	short dfh;		/* handle file disco */

	fileid=*(short *)((arglist++)->pd);		// primo argomento
	recno=*(short *)((arglist++)->pd);			// secondo argomento

	pbload=buffer_fio;							// save indirizzo iniziale buffer
	while ((larg=arglist->sz)!=-1) 	// per tutti gli argomenti
		{

		if ((lbuff+larg)<(LRECFIO-1))	 	// overflow ?
			{
			*(pbload)=arglist->td;		// load tipo di dato in buffer
			pbload++; 				 	  
			*(pbload)=larg; 		 		// load lunghezza in buffer
         pbload++;		 		 	  
			lbuff+=(larg+2);
			memcpy(pbload,(arglist++)->pd,larg);	//trasf. dato
			pbload+=larg;							// prossimo byte libero
			}
		else
			break;									// overflow, tronc. buffer
		}

	memset(pbload,FILL_PATT,LRECFIO-lbuff);	// clear resto del buffer
	pbload=buffer_fio+LRECFIO-1;
	*pbload=_fchks(buffer_fio,LRECFIO-1);

#ifdef ETH
	if(fileid < MAXFILESCADA)
		{
		QUEUE_PACKET pack;

		bric.nodo=0;
		bric.indice= WRITEDATA;
		bric.idfile=fileid;
		bric.recno=recno;
		memcpy(bric.b,buffer_fio,LRECFIO);
		pack.que=cc_scadao;
		pack.amsg=(char *) &bric;
		pack.lmsg=sizeof(BRICFIO);
		pack.flg=MSG_WAIT;
		pack.wto=0;
		enqueue(&pack);
		pack.que=privato;
		pack.amsg=(char *) &bric;
		pack.flg=MSG_WAIT;
		pack.wto=40;
		do
			{
			if(dequeue(&pack))
				{  printf("\n Errore connessione SCADA");  return(1); }
			}while(bric.recno != recno || bric.indice != RWRITEDATA);
		}
	else
#endif
		{
/*		fp=fopen(_fnamvar(fileid,fname),"rb+");
		if(!fp)
			fp=fopen(_fnamvar(fileid,fname),"wb+");

		if(!fp)
         */
      hf=open(_fnamvar(fileid,fname),O_RDWR|O_BINARY);
      if(hf==-1)
         hf=open(_fnamvar(fileid,fname),O_CREAT|O_BINARY|O_RDWR,S_IREAD|S_IWRITE);
      if(hf==-1)
         {  printf("\n Errore apertura file POL");  return(1); }

      pos = recno;
      pos *= LRECFIO;
   	wbyte(hf,buffer_fio,pos ,128);
      pos += 128;
		wbyte(hf,&buffer_fio[128],pos ,128);
		close(hf);
		}
	}



__fread(arglist)
	struct ARGLIST *arglist;	// lista argomenti
	{
   char 	buffer_fio[LRECFIO];			
	FILE *fp;
	char 	fname[70];			
	short lbuff=0;
	register larg;
	short fileid,recno;
	short dfh;					/* handle file disco */
	char  *pbload;

	pbload=buffer_fio;

	fileid=*(short*)((arglist++)->pd);			// primo argomento
	recno=*(short*)((arglist++)->pd);			// secondo argomento

	memset(buffer_fio,FILL_PATT,LRECFIO);		// clear buffer

#ifdef ETH
	if(fileid < MAXFILESCADA)
		{
		QUEUE_PACKET pack;
		short endfio=0;

		bric.nodo=0;
		bric.indice= READDATA;
		bric.idfile=fileid;
		bric.recno=recno;
		pack.que=cc_scadao;
		pack.amsg=(char *) &bric;
		pack.lmsg=LBRIC;
		pack.flg=MSG_WAIT;
		pack.wto=0;
		enqueue(&pack);
		pack.que=privato;
		pack.amsg=(char *)&bric;
		pack.flg=MSG_WAIT;
		pack.wto=40;
		do
			{
			if(dequeue(&pack))
				{
				printf("\n Errore connessione SCADA");  return(1);
				endfio=1;
				}
			else
				{
				if(bric.recno == recno && bric.indice == RREADDATA)
					{
					endfio=1;
					memcpy(buffer_fio,bric.b,LRECFIO);
					}
				}
			}while(!endfio);
		}
	else
#endif
		{
		fp=fopen(_fnamvar(fileid,fname),"rb+");
	   if(!fp) { printf(" ERR open FPOL ");  return(1); }
			rbyte(fileno(fp),buffer_fio,(long)recno * (long)LRECFIO,LRECFIO);
		fclose(fp);
		}
	while ((larg=arglist->sz)!=-1) 	// per tutti gli argomenti
		{
		if (lbuff+larg<LRECFIO-1 &&	 	// se non c'e overflow 
			arglist->td==*pbload)		 	// e tipo di dato uguale
			{
			pbload++;		 		 	  
			larg=arglist->sz=*pbload; 		// load lunghezza in output
			pbload++;		 		 	  
			lbuff+=(larg+2);
			memcpy((arglist++)->pd,pbload,larg);	//trasf. dato
			pbload+=larg;						// prossimo byte
			}
		else
			break;								// errore interrompe lettura
		}
	}


/***
_fnamvar	- creazione nome di file dati POL
***/
char * _fnamvar(fileid,filename)
	short fileid;
	char *filename;
	{
	strcpy(filename,&conf[RTF][0]);
	strcat(filename,"/FPOL");
	itoa(fileid,filename+strlen(filename),10);
	strcat(filename,".VAR");
	return (filename);
	}


/***
_fchks	- checksum del buffer
***/
char _fchks(b,l)
	char *b;
	short	l;
	{
	char	c=0;
	register i;

	for (i=0; i<l; i++,b++)
		c+=*b;
	return(c);
	}


/***

 __fdelete  -  cancellazione di un file

***/
__fdelete(arglist)
	struct ARGLIST *arglist;	// lista argomenti
	{
	short fileid;
	char 	fname[70];			

	fileid=*(short*)((arglist++)->pd);			// primo argomento

#ifdef ETH
	if(fileid < MAXFILESCADA)
		{
		QUEUE_PACKET pack;

		bric.nodo=0;
		bric.indice= DELETEFILE;
		bric.idfile=fileid;
		bric.recno=0;
		pack.que=cc_scadao;
		pack.amsg=(char *) &bric;
		pack.lmsg=LBRIC;
		pack.flg=MSG_WAIT;
		pack.wto=0;
		enqueue(&pack);
		pack.que=privato;
		pack.amsg=(char *)&bric;
		pack.flg=MSG_WAIT;
		pack.wto=40;
		do
			{
			if(dequeue(&pack))
				{  printf("\n Errore connessione SCADA");  return(1); }
			}while(bric.indice != RDELETEFILE);
		}
	else
#endif
		{
		remove(_fnamvar(fileid,fname));		
		}
	}


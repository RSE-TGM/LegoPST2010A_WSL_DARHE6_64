/**********************************************************************
*
*       C Source:               trfile.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Fri Dec 13 14:18:01 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: trfile.c-3 %  (%full_filespec: trfile.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   trfile
      modulo per la gestione dei messaggi da e per MMI relativi al 
      trasferimento di un file da SCADA

      La funzione gestisce i seguenti tipi di messaggi:
         
         mricfile   richiesta di invio di un nuovo file
            Se non ci sono invii in corso viene immediatamente trattato,
            altrimenti viene inserito nel buffer associato al video

         mackfile  richiesta di continuazione di invio di file

      Il messaggio utilizzato per l'invio dei dati e' minvfile

      Parametri:

         char*    messaggio da trattare
*/
#include <string.h>
#include <fcntl.h>
#if defined OSF1 || defined LINUX
#include <sys/types.h>
#include <sys/stat.h>
#define open(a,b)               DosOpen(a,b)
#else
#include <sys\types.h>
#include <sys\stat.h>
#endif
#include <io.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "video.inc"
#include "mesprocv.inc"
#include "messcada.inc"
#include "allar.inc"
#include	"mesqueue.h"
#include "dconf.inc"

struct s_messfile {
         short tipo;             // tipo di operazione
         char nfile[FILENAME_MAX+1]; // nome del file in uso
         char video;
         char zona;
         char pag[l_pagina];
         short nObj;
                  } InTrFile[max_video];
short CaTrFile=-1;   // canale I/O utilizzato per la trasmissione del file
short ViTrFile=-1;   // video che ha richiesto il messaggio
long  OfTrFile=0L;

extern FILE* LbgFp;

trfile (mess)
char *mess;
{
S_ACKFILE *ack;      // ack
S_RICHFILE *rich;    // richiesta dati file
S_INVFILE  *inv;     // richiesta stampa file 

S_INVFILE risp;      // messaggio di risposta  per invio file
S_ACKFILE rispack;   // messaggio di risposta per stampa file
short i;

ack=(S_ACKFILE*) mess;
rich=(S_RICHFILE*) mess;
inv=(S_INVFILE*) mess;

switch (ack->indice)
{
   case mricfile:         // nuovo trasferimento file
      if(CaTrFile!=-1)     // gia' in corso memorizzo richiesta
      {           
         memcpy(InTrFile[rich->video-1].nfile,rich->nfile,dim_chfile);
         InTrFile[rich->video-1].nObj=rich->nObj;
         InTrFile[rich->video-1].zona=rich->zona;
         InTrFile[rich->video-1].video=rich->video;
         InTrFile[rich->video-1].tipo=mricfile;
         memcpy(InTrFile[rich->video-1].pag, rich->pag, l_pagina);
         return;
      }
//
//  Verifico esistenza file, se non e' specificato l'intero
//  path utilizzo il default 
//
      ViTrFile=rich->video-1;   // video che ha richiesto il messaggio
      OpenTrFile(rich->nfile, O_RDONLY | O_BINARY);
      risp.bInizio=1;
      ReadTrFile(&risp, rich);
      if(risp.bLast)
         CheckTrFile(&risp, rich);
   break;

   case mackfile:         // ack
      if(ack->bStop)      // richiesto stop trasmissioni
      {
         CloseTrFile(ack->video-1);
         return;
      }
      risp.bInizio=0;
      ReadTrFile(&risp, rich);
      if(risp.bLast)    // se e' l'ultimo messaggio verifico eventuali pendenze
         CheckTrFile(&risp, rich);
   break;
   case minvfile:         // nuovo trasferimento file
      if(!inv->nByte)     // primo messaggio
      {
         if(CaTrFile!=-1)     // gia' in corso memorizzo richiesta
         {           
            InTrFile[inv->video-1].nObj=inv->nObj;
            InTrFile[inv->video-1].zona=inv->zona;
            InTrFile[inv->video-1].video=inv->video;
            InTrFile[inv->video-1].tipo=minvfile;
            memcpy(InTrFile[inv->video-1].pag, inv->pag, l_pagina);
            return;
         }
//
//  Apro il file di appoggio MMI.0v  (v=video da 0 a n)    
//
         ViTrFile=inv->video-1;   // video che ha richiesto il messaggio
         strcpy(InTrFile[inv->video-1].nfile,"MMI.");
         decnum(&InTrFile[inv->video-1].nfile[4],2,-2,ViTrFile);
         OpenTrFile(&InTrFile[inv->video-1].nfile, O_CREAT|O_BINARY|O_WRONLY|O_TRUNC);
         rispack.bInit=1;
      }
      else
         rispack.bInit=0;
      WriteTrFile(&rispack, inv);
      if(inv->bLast)    // se e' l'ultimo messaggio verifico eventuali pendenze
      {
         for(i=0;i<max_video;i++)
         {
            if(InTrFile[i].nfile[0] && InTrFile[i].tipo==minvfile)
            {
               rispack.nObj=InTrFile[i].nObj;
               rispack.zona=InTrFile[i].zona;
               rispack.video=InTrFile[i].video;
               ViTrFile=InTrFile[i].video-1;
               memcpy(rispack.pag,InTrFile[i].pag, l_pagina);
               strcpy(InTrFile[i].nfile,"MMI.");
               decnum(&InTrFile[i].nfile[4],2,-2,ViTrFile);
               OpenTrFile(&InTrFile[i].nfile, O_CREAT|O_BINARY|O_WRONLY|O_TRUNC);
               rispack.bInit=1;
               inv->bLast=0;     // invio solo ACK
               inv->nByte=0;
               WriteTrFile(&rispack, inv);
               InTrFile[i].nfile[0]=0;         // soddisfatta la richiesta
               break;
            }
         }
      }
   break;
}
return;
}
/*
   OpenTrFile

   Apre il file associato al file indicato nel messaggio

   Parametri

      char *   nome del file
      int      flag per open
*/
OpenTrFile(name, flag)
char *name;
int flag;
{
char path[FILENAME_MAX+1];
#if !defined OSF1 && !defined LINUX
union _REGS inregs, outregs;
#endif

if(strchr(name,'\\')==NULL)
{
   strcpy(path,conf[RTF]);
   strcat(path,"\\");
   strcat(path,name);
}
else strncpy(path,name,dim_chfile);
if(strstr(path,"FPRN"))
{
//
//  se si tratta di un file di libro giornale eseguo flush
//
#if !defined OSF1 && !defined LINUX
   inregs.h.ah=0x68;
   inregs.x.ebx=fileno(LbgFp);
   intdos(&inregs, &outregs);
#else
fflush(LbgFp);
#endif
}

CaTrFile=open(path, flag);
OfTrFile=0L;
}
/*
   ReadTrFile

   Legge i dati ed invia il messaggio dati file

   Parametri

      S_INVFILE* mess      messaggio da inviare
      S_RICHFILE *rich     messaggio di richiesta
*/
ReadTrFile(mess, rich)
S_INVFILE* mess;
S_RICHFILE *rich;
{
char path[FILENAME_MAX+1];
QUEUE_PACKET pack;

if(CaTrFile!=-1)
{
	mess->nByte=rbyte(CaTrFile,mess->buff,OfTrFile,dim_invfile);
   OfTrFile=OfTrFile+dim_invfile;
   if(mess->nByte<dim_invfile)
   {
      mess->bLast=1;
      CloseTrFile(ViTrFile);
   }
   else mess->bLast=0;
}
else
{
   mess->bLast=-1;
   mess->bInizio=-1;
}

mess->nodo=rich->video-1;
mess->indice=minvfile;
mess->classe=0;
mess->zona=rich->zona;
mess->video=rich->video;
memcpy(mess->pag, rich->pag, l_pagina);
mess->nObj=rich->nObj;

pack.que = c_mmio;            // accodo messaggio di risposta
pack.flg = MSG_WAIT;
pack.wto = 0;
pack.amsg=(char*)mess;
pack.lmsg=sizeof(S_INVFILE);
enqueue(&pack);
}
/*
   WriteTrFile

   Scrive i dati ed invia il messaggio ack per il prossimo

   Parametri

      S_ACKFILE* mess      messaggio di risposta
      S_INVFILE *rich     messaggio ricevuto
*/
WriteTrFile(mess, inv)
S_ACKFILE* mess;
S_INVFILE *inv;
{
QUEUE_PACKET pack;
S_SFILE sfile;

if(CaTrFile!=-1)
{
	wbyte(CaTrFile,inv->buff,OfTrFile,inv->nByte);
   OfTrFile=OfTrFile+inv->nByte;
   if(inv->bLast)                  // fine scrittura
   {                                // accodo richiesta di stampa
 	   memset(sfile.nome,0,l_sfile); 
      strcpy(sfile.nome,conf[RTF]); // inserisco nome del file da stampare
      strcat(sfile.nome,"\\");
      strcat(sfile.nome, InTrFile[ViTrFile].nfile);
      CloseTrFile(inv->video-1);
      if (TABUL)     //richiesta lancio tabulato
      {
         pack.que = c_tabul;
         pack.flg = MSG_WAIT;
         pack.wto = 0;
         pack.amsg=(char *)&sfile;
		   pack.lmsg=sizeof(S_SFILE);
	   	sfile.lung=sizeof(S_SFILE);
		   sfile.mess=msfile;
         sfile.richiesta=-1;          // stampante di default
         enqueue(&pack);
      }
   }
   else                       // invio ACK
   {
      mess->nodo=inv->video-1;
      mess->indice=mackfile;
      mess->classe=0;
      mess->zona=inv->zona;
      mess->video=inv->video;
      mess->bStop=0;
      memcpy(mess->pag, inv->pag, l_pagina);
      mess->nObj=inv->nObj;

      pack.que = c_mmio;            // accodo messaggio di risposta
      pack.flg = MSG_WAIT;
      pack.wto = 0;
      pack.amsg=(char*)mess;
      pack.lmsg=sizeof(S_INVFILE);
      enqueue(&pack);
   }
}
return;
}
/*
   CloseTrFile

   Chiudo il file in trasmissione se il video indicato
   coincide con MMI che sta effettuando la trasmissione

   Parametri
   short video
*/
CloseTrFile(video)
short video;
{
if(ViTrFile==video)    // coincidono
{
   close(CaTrFile);    // chiusura file
   CaTrFile=-1;        // annullo parametri
   ViTrFile=-1; 
   memset(InTrFile[video].nfile,0,dim_chfile);
}
}
/*
   Routine verifica pendenze da soddisfare

   Parametri

      S_INVFILE* mess      messaggio da inviare
      S_RICHFILE *rich     messaggio di richiesta
*/
CheckTrFile(risp, rich)
S_INVFILE *risp;
S_RICHFILE *rich;    // richiesta dati file
{
short i;

   for(i=0;i<max_video;i++)
   {
      if(InTrFile[i].nfile[0] && (InTrFile[i].tipo==mricfile))
      {
         rich->nObj=InTrFile[i].nObj;
         rich->zona=InTrFile[i].zona;
         rich->video=InTrFile[i].video;
         ViTrFile=InTrFile[i].video-1;
         memcpy(rich->pag,InTrFile[i].pag, l_pagina);
         OpenTrFile(InTrFile[i].nfile, O_RDONLY | O_BINARY);       // attivo successiva richiesta
         risp->bInizio=1;
         ReadTrFile(risp, rich);
         InTrFile[i].nfile[0]=0;         // soddisfatta la richiesta
         if(!risp->bLast) break;         // terninato ?
       }
   }
}

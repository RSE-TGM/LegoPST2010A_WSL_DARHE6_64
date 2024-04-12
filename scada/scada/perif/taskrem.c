/**********************************************************************
*
*       C Source:               taskrem.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Dec 16 15:43:09 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: taskrem.c-4 %  (%full_filespec: taskrem.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/****************************************************************************/
/*                                                                          */
/* Scope:                                                                   */
/*    Task gestione comunicazione sulla porta destinata alla                */
/*    trasmissione con MMI remoto con protocollo monodirezionale.           */
/*                                                                          */
/* History:                                                                 */
/* ********                                                                 */
/* Date       Author   Description                                          */
/* ---------- -------- ----------------------------------------------       */
/* 10/10/1994 MAB      Created                                              */
/* 22/05/1995 Fc       Sostituita la routine StrSend con RepSend            */
/*                     per compatibilita' con driver Reperibili             */
/*                     Le due routine sono identiche eccetto per la strutt. */
/*                     dati_507                                             */
/****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>

#if !defined OSF1_40 && !defined LINUX
#pragma pack(1)
#endif

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "dconf.inc"
#include "print.inc"
#include "pscserr.inc"
#include "switch.inc"
#include "pscs.cfg"

typedef struct s_pdbs         // Struttura dei TAGS
   {
   char           tipo;
   char           ext;
   unsigned short indice;
   } S_PDBS;

#define  N_LINE        2 // Indice della linea RS232 del 507 utilizzata (validi 0:3)
#define  TX_MAX_TABS  10 // Numero massiomo di tabelle di trasmissione

short Versione_DB;
short Versione_TX;

short numtabs = 0;           // Numero di tabelle attive in trasmissione
short currtab = 0;           // Indice della tabella corrente in trasmissione
S_PDBS *txtags[TX_MAX_TABS]; // Tabelle tags in trasmissione
short  numtags[TX_MAX_TABS] = {0,0,0,0,0,0,0,0,0,0}; // Numero di punti in trasmissione per tabella
static short dimmess[TX_MAX_TABS]; // Dimensione corpo messaggio di ogni tabella
static short dimtip[15] = {0,6,6,6,6,6,0,1,1,1,1,1,0,2,16};  // occupazione dei singoli punti


#define  TX_RATE       300   // Frequenza di trasmissione dati di aggiornamento (in ticks!)
                             // N.B. questo valore deve essere identico a quello
                             // definito come periodo d'attivazione per questo
                             // task nel modulo "pscsini.c"
#define  BAUD_RATE     600   // Baud Rate di trasmissione della linea seriale
#define  MAX_BODY      ((TX_RATE * 50 / 1000) * (BAUD_RATE / 10))  // dimensione massima corpo messaggio
struct TxMess                // Buffer per la trasmissione del messaggio
   {
   struct TxHead
      {
      unsigned short head;
      short          nbyte;
      short          versione;
      char           npacchetto;
      } h;
   unsigned char  body[MAX_BODY];
   } mess;

/* Definizione della lunghezza dell'header e del checksum. */

#define  LHEADER      (sizeof(struct TxHead))  // dimensione header
#define  LCHECKS      (sizeof(mess.body[0]))   // dimensione checksum (un byte del corpo messaggio)


void lnkrem(void)
{
unsigned short off,typ;
short pnt,j;


/* Se non e` stato installato alcun punto in trasmissione termina */
/* immediatamente il task. */

if(!numtabs) ter();


/* Rialloca la memoria sufficiente per preparare il messaggio di */
/* aggiornamento dell'host remoto e presetta l'header. */

mess.h.head       = 0x5AA5;
mess.h.nbyte      = dimmess[currtab] - sizeof(mess.h.head) - sizeof(mess.h.nbyte);
mess.h.versione   = Versione_TX;
mess.h.npacchetto = currtab;

/* Legge i valori dal Data Base e li inserisce nel messaggio. */

for(j = pnt = 0; j < numtags[currtab]; j++)
   {
   typ = txtags[currtab][j].tipo;
   off = txtags[currtab][j].indice;
   switch(typ)
      {
      case g1tipaa:                    // Analogici acquisiti
         memcpy(&mess.body[pnt],  &dbaav[off],4);
         memcpy(&mess.body[pnt+4],&dbaaf[off],2);
      break;

      case g1tipas:                    // Analogici Calcolati Standard
         memcpy(&mess.body[pnt],  &dbasv[off],4);
         memcpy(&mess.body[pnt+4],&dbasf[off],2);
      break;

      case g1tipac:                    // Analogici Calcotai non Standard
         memcpy(&mess.body[pnt],  &dbacv[off],4);
         memcpy(&mess.body[pnt+4],&dbacf[off],2);
      break;

      case g1tipad:                    // Analogici di Diagnostica
         memcpy(&mess.body[pnt],  &dbadv[off],4);
         memcpy(&mess.body[pnt+4],&dbadf[off],2);
      break;

      case g1tipao:                    // Analog Output
         memset(&mess.body[pnt],0            ,4);  // (non ha senso il valore!)
         memcpy(&mess.body[pnt+4],&dbaof[off],2);
      break;

      case g1tipda:                    // Digitali Acquisiti
         mess.body[pnt] = dbda[off] >> 8;
      break;
      
      case g1tipds:                    // Digitali Calcolati
         mess.body[pnt] = dbds[off] >> 8;
      break;

      case g1tipdc:                    // Digitali Calcolati non Standard
         mess.body[pnt] = dbdc[off] >> 8;
      break;

      case g1tipdd:                    // Digitali di Diagnostica
         mess.body[pnt] = dbdd[off] >> 8;
      break;

      case g1tipor:                    // Organi
         memcpy(&mess.body[pnt],&dbosc[off],2);
      break;

      case g1tipst:                    // Stringhe
         memcpy(&mess.body[pnt],&dbstv[off * g0lunst],g0lunst);
      break;
      }
   pnt = pnt + dimtip[typ];
   }

/* Calcola il checksum del messaggio appena preparato. */

for(j = -3, mess.body[pnt] = 0; j < pnt; j++)
   mess.body[pnt] = mess.body[pnt] + mess.body[j];

#if defined (REPERIBILI)
   RepSend(N_LINE,dimmess[currtab],(char *) &mess); // Trasmette il messaggio preparato
#else
   StrSend(N_LINE,dimmess[currtab],(char *) &mess); // Trasmette il messaggio preparato
#endif

currtab = ++currtab % numtabs;     // Prepara l'indice di tabella della prossima
                                   // scansione.

ter();
}


/****************************************************************************/
/*	InitTxRem                                                                */
/*                                                                          */
/*	Routine che inizializza la linea seriale di trasmissione verso l'MMI     */
/*	remoto.                                                                  */
/*                                                                          */
/*	Parametri                                                                */
/*                                                                          */
/****************************************************************************/
InitTxRem(void)
{
S_FIS stlin;
char  pathrtf[FILENAME_MAX+1];
FILE  *prem;
unsigned short head;
short j;


/* Legge dal file Txsend.rtf i TAG dei punti in trasmissione. Se il file */
/* non esiste (ossia non e` richiesta la trasmissione) ritorna con flag  */
/* di errore. */

sprintf(pathrtf,"%s\\txsend.rtf",conf[RTF]);
if( (prem = fopen(pathrtf,"rb")) == NULL ) return 1;
fread(&head       ,1,2,prem);      // Header di controllo
fread(&Versione_DB,1,2,prem);      // Numero Versione Data Base
fread(&Versione_TX,1,2,prem);      // Numero Versione TXSEND
if(head != 0xA55A) return 1;       // File non valido!

for(numtabs = 0; numtabs < TX_MAX_TABS; numtabs++)
   {
   fread(&j,1,2,prem);      // Indicatore tabella (# negativo dei TAGs presenti)
   if(j >= 0 || feof(prem)) break;
   numtags[numtabs] = -j;
   txtags[numtabs]  = (S_PDBS *) malloc(numtags[numtabs] * sizeof(S_PDBS)); // alloca spazio per ogni tabella
   dimmess[numtabs] = (LHEADER + LCHECKS);

   for(j = 0; j < numtags[numtabs]; j++)
      {
      fread(&txtags[numtabs][j],1,sizeof(S_PDBS),prem);        // Legge i singoli TAGS
      dimmess[numtabs] = dimmess[numtabs] + dimtip[txtags[numtabs][j].tipo];
      }

/* Se uno dei buffer di trasmissione e` troppo grosso abortisce SCADA. */

   if(dimmess[numtabs] > (MAX_BODY + LHEADER + LCHECKS))
      {
      printf("\nTxRemoto: Overflow TxMess %d (should be %d)",dimmess[numtabs],(MAX_BODY + LHEADER + LCHECKS));
      pscserr(ERR_TASK,TASK_TXREM,ROU_TXREMINIT,END_ERR,SYS_HALT);
      }

   }

fclose(prem);


/* Inizializza la linea seriale di trasmissione al remoto. */

stlin.linea  = N_LINE;
stlin.baud   = BAUD_RATE;
stlin.data   = 8;
stlin.stbit  = 1;
stlin.parity = 'N';
IniLine(&stlin);
DisableRx(N_LINE);                  // Disabilita Ricezione Caratteri e Status
SetInt();                           // Abilita interrupt

return 0;
}

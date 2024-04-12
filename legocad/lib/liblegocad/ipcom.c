/**********************************************************************
*
*       C Source:               ipcom.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 14:10:26 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: ipcom.c,2 %  (%full_filespec: 1,csrc,ipcom.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)ipcom.c	2.2\t2/13/95";
/*
        Fine sezione per SCCS
*/
/*** Libreria ipcom ***/

/* Buffo Massimo, Calleri Nicola 22/06/1992 */

/* funzioni per utilizzate per le comunicazioni tra processi tramite le */
/* named pipe */
#include "ipcdata.h"
#include <string.h>

/*** send_message( fd, appl, codice, mesg )
 *** parametri:
 ***             fd : descrittore della named pipe utilizzata per la comunic.
 ***           appl : nome dell' applicativo
 ***         codice : codice del messaggio 
 ***           mesg : messaggio
scrive un messaggio nella named pipe. Ritorna OK_MESG se il messaggio e'
stato mandato correttamente (il controllo e' eseguito sulle WRITE), 
altrimenti ritorna NOT_OK. */
send_message( fd, appl, codice, mesg, mesg_len )
int  fd;
char *appl;
int  codice;
char *mesg;
int mesg_len;
{
    header_mesg hmsg;
    int status;
    byte buffer[ BUFFER_SIZE ];

    strcpy( hmsg.applicativo, appl);
    hmsg.codice = codice;
    hmsg.lunghezza = mesg_len;

    memcpy(buffer, (byte *) &hmsg, sizeof(header_mesg));
    memcpy(buffer+sizeof(header_mesg), (byte *) mesg, mesg_len );
    status=write(fd, (byte *) buffer, sizeof(header_mesg)+mesg_len);
    if ( status == -1)
       return(NOT_OK);

    return(OK_MESG);
}

/*** recv_message( fd, mesg, hmsg )
 *** parametri:
 ***             fd : descrittore della named pipe utilizzata per la comunic.
 ***           mesg : messaggio letto
 ***           hmsg : puntatore all'header del messaggio
funzione utilizzata per la lettura di un messaggio nella named pipe.
La funzione ritorna -1 (NOT_OK) se la coda e' vuota oppure c'e' stato
un errore nella lettura dei messaggi, altrimenti 0 (MESG_OK) se e' stato
letto un messaggio nella FIFO */ 
recv_message(fd, messaggio, hmsg)
int fd;
char *messaggio;
header_mesg *hmsg;
{
   int n;

   if (read_pipe( fd, hmsg, sizeof(header_mesg)) == NOT_OK)
   {
      hmsg->codice = -1;
      return(NOT_OK);
   }

   if (read_pipe( fd, messaggio, hmsg->lunghezza) == NOT_OK)
   {
      hmsg->codice = -1;
      return(NOT_OK);
   }

   return(OK_MESG);
}


/*** read_pipe( fd, element, size )
 *** parametri:
 ***            fd : descrittore della named pipe utilizzata per la comunic.
 ***        buffer : array di caratteri utilizzato nella lettura dalla pipe
 ***          size : dimensione del buffer
La funzione viene utilizzata per leggere un messaggio di dimensioni size
(quindi COMPLETO)  nel file FIFO.*/
read_pipe( fd, element, size )
int fd;
char *element;
int size;
{
   int n, count=0;
   
/* Esegui il primo tentativo di lettura , se nella pipe non c'e' niente */
/* allora ritorna */
   if ( (n = read(fd,element,size)) == 0 || n == -1 )
      return(NOT_OK);

/* Se la lettura precedente e' stata completa, ritorna segnalando il */
/* ricevimento del messaggio */
   if ( n == size )
      return(OK_MESG);

/* Se e' stata eseguita una lettura parziale, allora prova a rileggere nella */
/* pipe. Se il numero di letture vuote consecutive e' > 5 allora ritorna con */
/* codice di errore */
   size -= n;
   element += n;
   for ( ; (n = read(fd,element,size)) != size && n != -1 && count < 5
         ; size = size-n, element = element+n )
       if ( n == 0) count++;
       else count=0;

   if ( n == -1 || count >= 5 ) return(NOT_OK);
   else return(OK_MESG);
}

/*** fine ipcom.c ***/

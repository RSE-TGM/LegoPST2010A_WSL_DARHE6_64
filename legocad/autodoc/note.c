/**********************************************************************
*
*       C Source:               note.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 11:54:57 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: note.c,2 %  (%full_filespec: 1,csrc,note.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)note.c	1.12\t3/31/95";
/*
        Fine sezione per SCCS
*/
/* file NOTE.C
 funzione per la gestione del campo note */

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>

#include <Xm/Xm.h>
#include "UxXt.h"


#include "autodoc.h"

/*** HeaderNote *cerca_testo(testi,cmp_note)
 ***   Parametri:
 ***      HeaderNote *testi: puntatore alla lista contenente i testi
 ***                               delle note
 ***      char *cmp_note : campo note
 ***
 ***   Descrizione:
 ***      Cerca nella lista *testi l'header relativo alla nota 'nota'.
 ***      Ritorna il puntatore all'header se la ricerca ha avuto esito
 ***      positivo , altrimenti ritorna NULL 
 ***/
HeaderNote *cerca_testo(testi,cmp_note)
HeaderNote *testi;
char *cmp_note;
{
   HeaderNote *header;

   for( header=testi ;header != NULL && strcmp(cmp_note,header->nota)
        ; header=header->next_header);
   return(header);
}

/*** canc_testo(addr_testi,header)
 ***    Parametri:
 ***       HeaderNote *addr_testo : indirizzo del puntatore alla lista
 ***                                       dei testi delle note.
 ***       HeaderNote *header : elemento della lista da cancellare.
 ***
 ***    Descrizione:
 ***       Ritorna 0 se l'elemento e' stato cancellato altrimenti ritorna 1
 ***       cancella l'header di un testo dalla lista testi
 ***/
canc_testo( addr_testi,header )
HeaderNote **addr_testi,*header;
{
   HeaderNote *prec_head;

   if ( header == NULL)
      return(1);

/* Se l'elemento da cancellare e' il primo ... */
   if ( header == *addr_testi )
   {
       *addr_testi = (*addr_testi)->next_header;
       free( header );
       return(0);
   }

/* Altrimenti cerca l'elemento precedente */
   prec_head = cerca_elem_prec(*addr_testi,header);

/* Se trovato ... */
   if (prec_head->next_header == header )
   {
       prec_head->next_header = header->next_header;
       free( header );
       return(0);
   }
   return(1);
}

/*** HeaderNotecerca_elem_prec(testi,header)
 ***    Parametri:
 ***       HeaderNote *testi : puntatore alla testa della lista delle
 ***                                 note.
 ***       HeaderNote *header: elemento della lista di cui si vuole
 ***                                 trovare l'elemento precedente.
 ***
 ***    Descrizione:
 ***       Cerca l'elemento precedente nella lista testi di un dato elemento
 ***       ( ritorna NULL se la ricerca e' fallita ) 
 ***/
HeaderNote *cerca_elem_prec(testi,header)
HeaderNote *testi,*header;
{
  HeaderNote *prec_head;

  if (header == NULL)
     return(NULL);

  for( prec_head=testi; prec_head->next_header != header && 
                        prec_head->next_header != NULL ;
       prec_head = prec_head->next_header );
  return(prec_head);
}

/*** HeaderNote *appendi_lista(addr_testi,nota)
 ***   Parametri:
 ***      HeaderNote *addr_testi: indirizzo del puntatore alla lista
 ***                                    contenente i testi delle note.
 ***      char *nota : valore del campo note.
 ***
 ***   Descrizione:
 ***      Appende una nota in fondo alla lista *testi e ritorna il puntatore
 ***      alla lista creata.
 ***/
HeaderNote *appendi_lista(addr_testi,nota)
HeaderNote **addr_testi;
char *nota;
{
  HeaderNote *header,*ultimo;

/* Se la lista non e' ancora stata creata allora viene creata */
   if ( *addr_testi == NULL)
   {
       *addr_testi  = (HeaderNote *) malloc(sizeof(HeaderNote));
       header = *addr_testi;
   }
   else
   {
       header = (HeaderNote *) malloc(sizeof(HeaderNote));
    /* posiziona il puntatore all'ultimo elemento della lista */
       for (ultimo = *addr_testi; ultimo->next_header != NULL;
            ultimo=ultimo->next_header);
           ultimo->next_header=header;
   }

   if (header == NULL)
      fprintf(stderr,"errore nella allocazione della memoria");
   
   strcpy(header->nota, nota);
   header->next_header = NULL;
   header->testo = NULL;
   return(header);
}

/*** void aggiorna_testi(fp, nome_blocco, offs_blocco, addr_testi)
 ***    Parametri:
 ***       FILE *fp : file pointer relativo al file contente le informazioni
 ***                  aggiuntive.
 ***       char *nome_blocco : nome del blocco.
 ***       long offs_blocco : posizione del record relativo al blocco nel
 ***                          file delle informazioni aggiuntive.
 ***       HeaderNote **addr_testi: indirizzo della lista dei testi
 ***                                      delle note.
 ***
 ***    Descrizione:
 ***       Verifica se nel file che contiene le informazioni aggiuntive
 ***       esistono delle note.
 ***       Se esistono allora recupera le note dal file ed inseriscile nella
 ***       lista *testi altrimenti la lista viene inizializzata a NULL 
 ***/
void aggiorna_testi(fp, nome_blocco, offs_blocco, addr_testi)
FILE *fp;
char *nome_blocco;
long offs_blocco;
HeaderNote **addr_testi;
{
   HeaderNote *header;
   char buffer[90], int_note[40], *ptr, nota[6];
   long offs;

   *addr_testi = NULL;

   if ( offs_blocco == -1)
      return;

   sprintf(int_note, "*LG*NOTE DEL BLOCCO %s NOTA ",nome_blocco);
   printf("int_note: %s\n", int_note);

   fseek(fp, offs_blocco, SEEK_SET);
   ptr = fgets(buffer,81,fp);
   ptr = fgets(buffer,81,fp);

   while( (ptr = fgets(buffer,81,fp)) != NULL && 
           strncmp(buffer,"*LG*DATI DEL BLOCCO ",20) &&
           strncmp(buffer,"*LG*EOF",7))       
   {
   /* Cerca il testo della nota considerata */

      if ( !strncmp(buffer,int_note,strlen(int_note)) )
      {
          copy_n_car(nota, buffer+34, 
                     (strlen(buffer) > 40) ? 5 : strlen(buffer)-35);
          taglia(nota);  /* <--- toglie i blank finali della stringa */
          header = appendi_lista(addr_testi, nota);
          printf("trovato !!! b: %s nota: %s\n", buffer, nota);
          copia_testo_nota(fp, &header->testo);
       }
   }
   fseek(fp, offs_blocco, SEEK_SET);
}

/*** void cancella_testi(addr_testi)
 ***   Parametri:
 ***      HeaderNote *addr_testi: indirizzo della lista dei testi delle
 ***                                    note.
 ***
 ***   Descrizione:
 ***      Cancella la lista dei testi dalla memoria 
 ***/
void cancella_testi(addr_testi)
HeaderNote **addr_testi;
{
   HeaderNote *prec_header = NULL;

   for (; *addr_testi != NULL; prec_header = *addr_testi,
          *addr_testi = (*addr_testi)->next_header)
   {
         free((*addr_testi)->testo);
         if (prec_header != NULL)
           free(prec_header);
   }
   free(prec_header);
}

/* fine note.c */

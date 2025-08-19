/**********************************************************************
*
*       C Source:               unita.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 11:56:47 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: unita.c,2 %  (%full_filespec: 1,csrc,unita.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)unita.c	1.12\t3/31/95";
/*
        Fine sezione per SCCS
*/
/*** file unita.c : gestione delle unita di misura ***/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "unita.h"

/************************************************************************/
/* VARIABILI ESTERNE							*/
/************************************************************************/

extern UnitaMisura unimis[];
extern int num_unita_misura;

int copia_file(char*, char*);

/*** leggi_file_unita()
 ***
 ***    Descrizione:
 ***      legge dal file unimis_doc.dat le unita di misura selezionate
 ***      per ogni tipo di variabile 
 ***/
int leggi_file_unita()
{
   int n, i, fd;
   RecordUmis rec_umis;

   fd = open(FILE_UNITA_MISURA, O_RDONLY, 700);
   if (fd == -1)
   {
      fprintf(stderr, "error while opening %s\n", FILE_UNITA_MISURA);
      return(1);
   }

   while ( n = read(fd, &rec_umis, sizeof(RecordUmis)) && n != -1 )
   {
printf("conf. %s\n", rec_umis.nome_tipo);
       for (i = 0; i < num_unita_misura; i++ )
          if (!strcmp(unimis[i].nome_tipo, rec_umis.nome_tipo))
          {
              unimis[i].ind_selez = rec_umis.ind_selez;
              break;
          }
   }
   close(fd);
}

/*** int salva_unita_misura()
 ***
 ***    Descrizione:
 ***       Salva nel file unimis_doc.dat le unita di misura selezionate
 ***       per ogni tipo di variabile.
 ***/
int salva_unita_misura()
{
   int fd, i, n;
   RecordUmis rec_umis;

#ifdef VMS
   remove(FILE_UNITA_MISURA);
#else
   unlink(FILE_UNITA_MISURA);
#endif

   fd = creat(FILE_UNITA_MISURA, 0666);

   if (fd == -1)
   {
      fprintf(stderr,"ERROR! cannot open file %s for writing.\n",
		     FILE_UNITA_MISURA);
      return(1);
   }

   for ( i = 0; i < num_unita_misura && n > 0 ; i++ )
   {
       strncpy(rec_umis.nome_tipo,unimis[i].nome_tipo,8);
       rec_umis.ind_selez = unimis[i].ind_selez;
       n = write(fd, (char *) &rec_umis, sizeof(RecordUmis));
   }

   close(fd);
}

/*** fine unita.c ***/

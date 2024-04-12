/**********************************************************************
*
*       C Source:               file_icone.c
*       Subsystem:              1
*       Description:
*       %created_by:    lopez %
*       %date_created:  Fri Oct 25 14:00:10 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: file_icone.c-4 %  (%full_filespec: file_icone.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)file_icone.c	2.5\t2/13/95";
/*
        Fine sezione per SCCS
*/
/* FILE_ICONE.C		gestione dei file per EDICOLE / MACRO / LIBRARIAN
   Bulfus ac Callerus fecerunt	1992			*/

/*** Funzioni definite :

MODULI DI PROCESSO:

   FILE *apri_file_icoproc( char flag_crea, char flag_lib);
   int  scrivi_empty_record_file_ico( FILE *fp, IconFileRec *record )
   int  scrivi_record_file_ico( FILE *fp, IconFileRec *record )
   int  leggi_record_file_ico( FILE *fp, IconFileRec *record )
   long cerca_modulo_proc( FILE *fp, IconFileRec *record, char *nome_modulo )
   int  cancella_record_file_ico( char *nome_modulo, char flag_lib )
   int  aggiungi_record_file_ico( char *nome_modulo, IconFileRec *new_record, 
                                  char flag_lib )

MODULI DI REGOLAZIONE:

   FILE *apri_file_icoscheme( char flag_lib )
   int  leggi_file_regola( FILE *fp, SchemeFileRec *record )
   long cerca_modulo_regola( FILE *fp, SchemeFileRec *record,
                             char *nome_modulo )

ICONA STANDARD:

   FILE *apri_file_std( char flag_crea, char flag_lib )
   int  scrivi_file_std_ico( FILE *fp, IconStdRec *record )
   long leggi_file_std_ico( FILE *fp, IconStdRec *record, int tipo_modulo )

SIMBOLI:

   FILE *apri_file_symb( SymbolFileRec *record, char flag_crea, flag_lib )
   int  scrivi_file_simboli( FILE *fp, SymbolFileRec *record )
   int  leggi_file_simboli( FILE *fp, SymbolFileRec *record )

ALTRE FUNZIONI:

   int  recupera_dim_icona( char *nome_modulo, int num_icona, int *width,
			    int *height, char flag_lib)
   int  prima_icona_disponibile( char *nome_modulo, int *width, int *height,
                                 char flag_lib )

REVISIONI:  

	11-7-94 Micheletti S.d.I.    
                
	Modificati test su tutti i valori di ritorno delle fprint
	che ritornano 0 se non riescono a scrivere correttamente
                                             
	e.s. vers prec.    if( fprintf(...) != 0) return(ERROR);
	     vers att.     if( fprintf(...) == 0) return(ERROR);

***/

#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifndef VMS
#include <X11/Intrinsic.h>

#if defined LINUX
#include <unistd.h>
#else
#include <sys/file.h>
#endif


#else
#include <unixio.h>
#define F_OK	0
#define W_OK	2
#define R_OK	4
#endif

#include "file_icone.h"
#include "aggiunte.h"

#define APPLICATION_NAME	"LIBICOFILE"

/* codici messaggi di errore */
#define EOPENLSTMOD     0
#define ECREALSTICOP    1
#define EOPENLSTICOP    2
#define EOPENLSTSCH     3
#define EOPENICOSTD     4
#define EOPENSIMB       5

/* codici messaggi di warning */
#define WOPENFILETMP    0

static char *icofile_error[] = {
			          "Open file module list failed!",
                                  "Icon file list creation failed!",
                                  "Open icon list file failed!",
                                  "Open scheme list file failed!",
                                  "Open icon standard file failed!",
                                  "Open symbol file failed!"
		       	       };

static char *icofile_warning[] = {
			           "can't open temporary file!",
		       	         };

/*-----------------------------------------------------------------------*/
/*** FILE *apri_file_icoproc(flag_crea, flag_lib)
 *** Parametri:
 ***   char flag_crea: indica se il file icon_list.dat deve essere creato
 ***	               nel qual caso non esista.
 ***   char flag_lib : indica se il file icon_list.dat si trova nella libreria
 ***                   utente oppure nella libreria standard.
 ***
apre il file icone moduli di processo. Se il flag_crea e' True ed il file non
esiste allora viene creato ex-novo altrimenti ritorna un codicino di errore.
Questa funzione controlla la congruenza dei file icon_list.dat e
libut/lista_moduli.dat: se lista_moduli.dat e' piu' recente di icon_list.dat
viene effettuato l'aggiornamento (cancellazione/aggiunta di moduli in 
icon_list.dat). In ogni caso l'aggiornamento viene effettuato se flag_crea
e' posto a True. Ultima cosa: l'apertura del file viene effettuato in
modalita' "r+" cioe lettura/scrittura. */
FILE *apri_file_icoproc(flag_crea, flag_lib)
char flag_crea, flag_lib;
{
   long date1, date2;
   char buffer[DIM_BUFFER], nome_modulo[5], descr_modulo[51];
   char *path_lib, *path_libgraf, *path_libut; 
   char path_file_ico[256], path_lista_mod[256];
   int i, out1, out2;
   struct stat file_info;
   IconFileRec record;
   FILE *fp_moduli, *fp_tmp, *fp_modp;

/* recupera il percorso della libreria dei moduli di processo */
   if (flag_lib == LIB_UTENTE)
   {
      path_lib = (char *) getenv("LEGOCAD_USER");
      path_libgraf = PATH_LIBGRAF_UTE;
      path_libut = PATH_LIBUT_UTE;
   }
   else
   {
      path_lib = (char *) getenv("PROCLIB");
/*
      path_libgraf = PATH_LIBGRAF_STD;
      path_libut = PATH_LIBUT_STD;
*/
      if( flag_lib == LIB_STANDARD_GENERAL )
      {
         printf("apri_file_icoproc: %s invalid directory \n",
                                         PATH_LIBUT_STD_GENERAL);
            s_error( APPLICATION_NAME, icofile_error, EOPENLSTMOD, 1 );
      }
      else if( flag_lib == LIB_STANDARD_BASE )
         path_libgraf = path_libut = PATH_LIBUT_STD_BASE;
      else if( flag_lib == LIB_STANDARD_AUXILIARY )
         path_libgraf = path_libut = PATH_LIBUT_STD_AUXILIARY;
      else if( flag_lib == LIB_STANDARD_NUCLEAR )
         path_libgraf = path_libut = PATH_LIBUT_STD_NUCLEAR;
      else if( flag_lib == LIB_STANDARD_SPECIAL )
         path_libgraf = path_libut = PATH_LIBUT_STD_SPECIAL;

   }

   if (path_lib == NULL)
#ifdef VMS
      path_lib = "[]";
#else
      path_lib = ".";
#endif

/* file lista icone */
#ifdef VMS
   sottodir_vms(path_file_ico, path_lib, path_libgraf ); 
#else
   sprintf(path_file_ico,"%s/%s/", path_lib, path_libgraf );
#endif
   strcat(path_file_ico, FILE_ICONE_MODP);

/* file lista dei moduli */
#ifdef VMS
   sottodir_vms(path_lista_mod, path_lib, path_libut);
#else
   sprintf(path_lista_mod,"%s/%s/", path_lib, path_libut);
#endif
   strcat(path_lista_mod, FILE_DATI_LIBUT);

   printf("apro file %s\n", path_lista_mod);
   printf("apro file %s\n", path_file_ico);

/* controlla se il file moduli / icone icon_list.dat esiste. */
/* se non esiste crea il file icone icon_list.dat leggendo i dati dal file */
/* lista_moduli.dat , altrimenti apri in lettura/modifica tale file */
   if ( access(path_file_ico, F_OK ) != 0)
   {
      if (flag_crea)    /* crea il file ex-novo, se richiesto */
      {
      /* apertura del file lista moduli */
         if ((fp_moduli = fopen(path_lista_mod, "r")) == NULL)
            s_error( APPLICATION_NAME, icofile_error, EOPENLSTMOD, 1 );

      /* creazione del file moduli / icone */
         if ((fp_modp = fopen(path_file_ico, "w")) == NULL)
            s_error( APPLICATION_NAME, icofile_error, ECREALSTICOP, 1 );

      /* ciclo di lettura moduli e scrittura nel file moduli/icone */
         while ( fgets(buffer,DIM_BUFFER,fp_moduli) != NULL )
         {
             buffer[strlen(buffer)-1] = '\0'; /* Cancella il \n alla fine */
             sprintf(record.nome_modulo, "%.4s", buffer);
             if (strlen(buffer) > 6)    /* Se c'e' la descrizione ... */
                sprintf(record.descr_modulo, "%.50s", buffer+6);
             else
                record.descr_modulo[0] = '\0';

             scrivi_empty_record_file_ico( fp_modp, &record );
         }
         fclose(fp_moduli);
         fclose(fp_modp);
      }
      else
         s_error( APPLICATION_NAME, icofile_error, EOPENLSTICOP, 1 );
   }

   if (flag_crea)  /* aggiorna il file icon_list.dat, se richiesto */
   {
   /* recupera la data di ultima modifica del file lista delle icone */
      out1 = stat(path_file_ico, &file_info);
      date1 = file_info.st_mtime;

   /* recupera la data di ultima modifica del file lista_moduli.dat */
      out2 = stat(path_lista_mod, &file_info);
      date2 = file_info.st_mtime;

   /* se libut/lista_moduli.dat e' piu' recente di icon_list.dat */
   /* allora bisogna aggiornare icon_list.dat */
      if ( !out1 && !out2 && date2 > date1 )
      {
         char path_ico_tmp[256];
         fprintf(stdout, "Updating file icon_list.dat. Wait please.\n");
      /* recupera il nome del file temporaneo */
	 tmpnam(path_ico_tmp);

         if ((fp_moduli = fopen(path_lista_mod, "r")) == NULL)
            s_error( APPLICATION_NAME, icofile_error, EOPENLSTMOD, 1 );

         if ((fp_modp = fopen(path_file_ico, "r")) == NULL)
            s_error( APPLICATION_NAME, icofile_error, EOPENLSTICOP, 1 );

         if ((fp_tmp = fopen(path_ico_tmp, "w+")) != NULL)
         { 
        /* ciclo di lettura moduli e scrittura nel file moduli/icone */
            while ( fgets(buffer,DIM_BUFFER,fp_moduli) != NULL )
            {
               buffer[strlen(buffer)-1] = '\0'; /* Cancella il \n alla fine */
               sprintf(nome_modulo, "%.4s", buffer);

	   /* Se il modulo esiste in icon_list.dat allora ricopia i dati, */
	   /* altrimenti crea un record vuoto */
               if ( cerca_modulo_proc( fp_modp, &record, nome_modulo ) == 
								RETURN_ERROR )
               {
                  strcpy(record.nome_modulo, nome_modulo);
                  if (strlen(buffer) > 6)    /* Se c'e' la descrizione ... */
                     sprintf(record.descr_modulo, "%.50s", buffer+6);
                  else
                     record.descr_modulo[0] = '\0';
                  scrivi_empty_record_file_ico( fp_tmp, &record );
               }
               else
               {
                  if (strlen(buffer) > 6)    /* Se c'e' la descrizione ... */
                     sprintf(record.descr_modulo, "%.50s", buffer+6);
                  else
                     record.descr_modulo[0] = '\0';
                  scrivi_record_file_ico( fp_tmp, &record );
               }
            }
            fclose( fp_tmp );
            fclose( fp_modp );
            fclose( fp_moduli );

       /* copia il file temporaneo sull'originale */
            copia_file( path_ico_tmp, path_file_ico );

#ifndef VMS
            unlink( path_ico_tmp );
#else
            remove( path_ico_tmp );
#endif
         }
         else 
            s_warning(NULL, NULL, APPLICATION_NAME, icofile_warning,
		      WOPENFILETMP );
      }
   }

/* apri i files per la lettura / scrittura */
   if ((fp_modp = fopen(path_file_ico, "r+")) == NULL) {
      if ((fp_modp = fopen(path_file_ico, "r")) == NULL)
         s_error( APPLICATION_NAME, icofile_error, EOPENLSTICOP, 1 );
   }

   return(fp_modp);
}

/*-----------------------------------------------------------------------*/
/*** FILE *apri_file_icoscheme(flag_lib)
 *** Parametri:
 ***   char flag_lib : indica se il file icon_list.dat si trova nella libreria
 ***                   utente oppure nella libreria standard.
apre il file libut_reg/lista_schemi.dat. Per i moduli di schema (ricordiamo
per gli ignoranti in materia) non e' stato previsto un file di icone 
grafiche in quanto i moduli di regolazione si riferiscono ad una unica
icona grafica standard (vedere file icon_std.dat).
il file libut_reg/lista_schemi.dat viene utilizzato per recuperare la lista
dei moduli di schema. */
FILE *apri_file_icoscheme(flag_lib)
char flag_lib;
{
   FILE *fp_modsch;
   char *path_lib, *path_libsch, path_lista_sch[256];

/* recupera il percorso della directory utente */
   if (flag_lib == LIB_UTENTE) 
   {
      path_lib = (char *) getenv("LEGOCAD_USER");
      path_libsch = PATH_LIBUTREG_UTE;
   }
   else
   {
      path_lib = (char *) getenv("PROCLIB");
      path_libsch = PATH_LIBUTREG_STD;
   }

   if (path_lib == NULL)
#ifdef VMS
      path_lib = "[]";
#else
      path_lib = ".";
#endif

/* percorso file lista_schemi.dat */
#ifdef VMS
   sottodir_vms(path_lista_sch, path_lib, path_libsch ); 
#else
   sprintf(path_lista_sch,"%s/%s/", path_lib, path_libsch );
#endif
   strcat(path_lista_sch, FILE_DATI_LIBUTREG);

   printf("apro file %s\n", path_lista_sch);

   if ((fp_modsch = fopen(path_lista_sch, "r")) == NULL)
      s_error( APPLICATION_NAME, icofile_error, EOPENLSTSCH, 1 );
   return(fp_modsch);
}

/*-----------------------------------------------------------------------*/
/*** scrivi_empty_record_file_ico( fp, record )
 ***    Parametri:
 ***        FILE *fp;
 *** IconFileRec record: record da scrivere.
scrive un record del tipo IconFileRec nel file puntato da *fp.
Il record deve avere settato il nome del modulo e la sua descrizione, la
funzione azzera i record delle icone e salva nel file. */
scrivi_empty_record_file_ico( fp, record )
FILE *fp;
IconFileRec *record;
{
   int i;
   char nome_mod_file[5];

   strcpy(nome_mod_file,record->nome_modulo),
   tominus(nome_mod_file);

   record->num_icone = 0;

   for(i = record->num_icone; i < MAX_ICON_X_PMODULE ;i++)
   {
       sprintf(record->bmap_record[i].nome_file,"%s%1d.bmp",
               nome_mod_file,i);
       record->bmap_record[i].colore_fg = 0,
       record->bmap_record[i].colore_bg = 0,
       record->bmap_record[i].base = 0,
       record->bmap_record[i].altezza = 0;
       record->bmap_record[i].esiste = FALSE;
    }
    if ( scrivi_record_file_ico( fp, record ) == RETURN_OK )
       return(RETURN_OK);
    else
       return(RETURN_ERROR);
}

/*-----------------------------------------------------------------------*/
/*** FILE *apri_file_std(flag_crea, flag_lib)
 *** Parametri:
 ***   Boolean flag_crea: indica se il file deve essere creato nel qual caso
 ***		          non esista.
 ***   char flag_lib : indica se il file icon_list.dat si trova nella libreria
 ***                   utente oppure nella libreria standard.
apre il file che contiene la configurazione delle icone standard dei moduli
di processo e di schema. Se il flag e' settato a True ed il file non esiste
allora viene creato altrimenti esce con un errore */
FILE *apri_file_std(flag_crea, flag_lib)
char flag_crea, flag_lib;
{
   IconStdRec record;
   FILE *fp_std;
   char *path_lib, *path_libgraf, path_ico_std[256];

/* recupera il percorso della directory utente */
   if (flag_lib == LIB_UTENTE)
   {
      path_lib = (char *) getenv("LEGOCAD_USER");
      path_libgraf = PATH_LIBGRAF_UTE;
   }
   else
   {
      path_lib = (char *) getenv("LEGO");
/*
      path_libgraf = PATH_LIBGRAF_STD;
*/
      path_libgraf = PATH_LIBUT_STD_GENERAL;
   }

   if (path_lib == NULL)
#ifdef VMS
      path_lib = "[]";
#else
      path_lib = ".";
#endif

/* percorso file lista_schemi.dat */
#ifdef VMS
   sottodir_vms(path_ico_std, path_lib, path_libgraf ); 
#else
   sprintf(path_ico_std,"%s/%s/", path_lib, path_libgraf );
#endif
   strcat(path_ico_std, FILE_ICONE_STD);

   printf("apro file %s\n", path_ico_std);

/* se il file delle icone standard non esiste allora viene creato */
   if ( access(path_ico_std, F_OK) != 0 )
   {
      if (flag_crea)
      {
         if ((fp_std = fopen(path_ico_std, "w")) == NULL)
            s_error( APPLICATION_NAME, icofile_error, EOPENICOSTD, 1 );
         record.num_icone = 0;
         record.bmap_record.colore_fg = DEFAULT_FOREGROUND;
         record.bmap_record.colore_bg = DEFAULT_BACKGROUND;
         record.bmap_record.base      = DEFAULT_WIDTH;
         record.bmap_record.altezza   = DEFAULT_HEIGHT;
         strcpy(record.bmap_record.nome_file, BMAP_STD_MODP);
         record.tipo_modulo = MODULE_PROCESS;
         scrivi_file_std_ico( fp_std, &record );
         strcpy(record.bmap_record.nome_file, BMAP_STD_MODNP);
         record.tipo_modulo = MODULE_SCHEME;
         scrivi_file_std_ico( fp_std, &record );
         fclose( fp_std );
      }
      else
         s_error( APPLICATION_NAME, icofile_error, EOPENICOSTD, 1 );
   }

/* apri il file in lettura/scrittura */
   if ((fp_std = fopen(path_ico_std, "r+")) == NULL) {
      if ((fp_std = fopen(path_ico_std, "r")) == NULL)
         s_error( APPLICATION_NAME, icofile_error, EOPENICOSTD, 1 );
   }

   return(fp_std);
}

/*-----------------------------------------------------------------------*/
/*** int scrivi_record_file_ico(fp, record)
 *** Parametri:
 ***     IconFileRec *record: record del file icon_file_?p.dat 
 ***     FILE *fp           : file pointer del file icon_file_?p.dat
scrive un record nel file alla posizione corrente 
Modifica del 11/7/94 su test valore di ritorno fprintf cerca REVISIONI */
int scrivi_record_file_ico(fp, record)
FILE *fp;
IconFileRec *record;
{
   int i;

   if (fprintf(fp, "%-4.4s %-50.50s %2d\n", 
               record->nome_modulo, record->descr_modulo,
               record->num_icone ) == 0)
      return(RETURN_ERROR); 

   for(i = 0; i < 10 ;i++)
      if (fprintf(fp, "%-14.14s %2d %2d %3d %3d %1d\n", 
                  record->bmap_record[i].nome_file,
                  record->bmap_record[i].colore_fg,
                  record->bmap_record[i].colore_bg,
                  record->bmap_record[i].base,
                  record->bmap_record[i].altezza,
                  record->bmap_record[i].esiste) == 0)
         return(RETURN_ERROR);

   fflush(fp);
   return(RETURN_OK);
}

/*-----------------------------------------------------------------------*/
/*** leggi_record_file_ico(fp, record)
 *** Parametri:
 ***     IconFileRec *record: record del file icon_file_?p.dat 
 ***     FILE *fp           : file pointer del file icon_file_?p.dat
legge un record nel file alla posizione corrente */
leggi_record_file_ico(fp, record)
FILE *fp;
IconFileRec *record;
{
   int i;
   char buffer[DIM_BUFFER];

   if (fgets(buffer,DIM_BUFFER,fp) == NULL)
      return(RETURN_ERROR);

   sprintf(record->nome_modulo, "%.4s", buffer);
   sprintf(record->descr_modulo,"%.50s", buffer+5);
   sscanf(buffer+56,"%2d\n", &record->num_icone );

   for(i = 0; i<10 ;i++)
      if (fscanf(fp, "%14s %2d %2d %3d %3d %1d\n", 
                 record->bmap_record[i].nome_file,
                 &record->bmap_record[i].colore_fg,
                 &record->bmap_record[i].colore_bg,
                 &record->bmap_record[i].base,
                 &record->bmap_record[i].altezza,
                 &record->bmap_record[i].esiste) == EOF)
         return(RETURN_ERROR);
      else
         tominus(record->bmap_record[i].nome_file);

   return(RETURN_OK);
}

/*-----------------------------------------------------------------------*/
/*** cerca_modulo_proc( fp, record, nome_modulo )
 *** Parametri:
 ***    FILE *fp : file pointer del file icon_list.dat.
 ***  IconFileRec *record: record file icon_list.dat.
 ***    char *nome_modulo: nome del modulo.
Funzione per la ricerca del modulo nel file icon_list.dat. La funzione
restituisce l'offset del modulo se tale modulo e' stato trovato ,
altrimenti restituisce RETURN_ERROR */
long cerca_modulo_proc( fp, record, nome_modulo )
FILE *fp;
IconFileRec *record;
char *nome_modulo;
{
   long pos;
   char trovato = 0;

/* ciclo di lettura moduli e ricerca */
   pos = 0;
   fseek(fp, 0L, SEEK_SET);
   while ( !trovato && leggi_record_file_ico(fp, record) == 0 )
   {
      if ( strncmp(record->nome_modulo, nome_modulo, 4) == 0)
         return(pos); 
      else
         pos = ftell(fp);
   } 
   return(RETURN_ERROR);  /* modulo non trovato o lettura file fallita. */
}

/*-----------------------------------------------------------------------*/
/*** cancella_record_file_ico(nome_modulo, flag_lib)
 ***   Parametri :
 ***    char nome_modulo : nome modulo da cancellare dal file delle icone
 ***    char flag_lib : indica se libreria utente o libreria standard
Cancella il record relativo al nome_modulo ***/
int cancella_record_file_ico(nome_modulo,flag_lib)
char *nome_modulo, flag_lib;
{
   int i, flag;
   char *path_lib, *path_libgraf;
   char icon_to_cancel[256], iconlistfile[256], file_tmp[256];
   IconFileRec record;
   long offs;
   FILE *fp, *fp_tmp;

   fp = apri_file_icoproc(CREA_FALSE, flag_lib);
   if (fp == NULL)
      return(RETURN_ERROR);

   offs = cerca_modulo_proc (fp, &record, nome_modulo);
   if (offs == RETURN_ERROR)
   {
      fprintf(stderr, "The module %s doesn't exist.\n", nome_modulo);
      return(RETURN_ERROR);
   }

   fseek (fp, offs, SEEK_SET);
   if (leggi_record_file_ico (fp,&record) == RETURN_ERROR)
   {
      fprintf(stderr, "Can't get icon module information.\n");
      return(RETURN_ERROR);
   }

/* recupera il percorso della directory utente */
   if (flag_lib == LIB_UTENTE)
   {
      path_lib = (char *) getenv("LEGOCAD_USER");
      path_libgraf = PATH_LIBGRAF_UTE;
   }
   else
   {
      path_lib = (char *) getenv("LEGO");
      path_libgraf = PATH_LIBGRAF_STD;
   }

   if (path_lib == NULL)
#ifdef VMS
      path_lib = "[]";
#else
      path_lib = ".";
#endif

   for (i=0 ; i<MAX_ICON_X_PMODULE ; i++)
   {
      printf ("%d FILE BITMAP: %s\n", i+1, record.bmap_record[i].nome_file);
      if ( record.bmap_record[i].esiste == True )
      {
#ifdef VMS
          sottodir_vms (icon_to_cancel, path_lib, path_libgraf);
#else
          sprintf (icon_to_cancel,"%s/%s/", path_lib, path_libgraf);
#endif
          strcat(icon_to_cancel, record.bmap_record[i].nome_file);

          if ( !access (icon_to_cancel,F_OK) )
#ifdef VMS
             remove(icon_to_cancel);
#else
             unlink(icon_to_cancel);
#endif
      }
   }

/* Creazione file temporaneo per l'aggiornamento del file icon_list.dat */
   tmpnam (file_tmp);

   if ((fp_tmp = fopen(file_tmp,"w+")) == NULL)
   {
      fprintf(stderr, "Can't open temporary file for deleting record.");
      return (RETURN_ERROR);
   }

   printf ("CANCELLA_RECORD_ICONA: record.nome_modulo = %s\n",
            record.nome_modulo);

   fseek (fp, 0L, SEEK_SET);
   while ( leggi_record_file_ico (fp,&record) != RETURN_ERROR )
      if (strcmp(record.nome_modulo,nome_modulo))
          scrivi_record_file_ico (fp_tmp,&record);

   fclose (fp);
   fclose (fp_tmp);

#ifdef VMS
   sottodir_vms(iconlistfile, path_lib, path_libgraf );
#else
   sprintf(iconlistfile, "%s/%s/", path_lib, path_libgraf);
#endif
   strcat(iconlistfile,FILE_ICONE_MODP);
   printf("canc.: percorso file icone: %s\n", iconlistfile);

   flag = copia_file (file_tmp,iconlistfile);

#ifdef VMS
   remove (file_tmp);
#else
   unlink (file_tmp);
#endif

   if ( flag != 0)
   {
      fprintf (stderr,"Couldn't update icon_list.dat. Failure.");
      return (RETURN_ERROR);
   }
   else
      return (RETURN_OK);
}

/*-----------------------------------------------------------------------*/
/*** int aggiungi_record_file_ico(nome_modulo, record, flag_lib)
 ***   Parametri :
 ***    char nome_modulo : nome modulo da aggiungere 
 ***    IconFileRec *new_record : record icona da aggiungere;
 ***    char flag_lib : indica se libreria utente o libreria standard
 ***   
Aggiunge un record vuoto relativo al nome_modulo e restituisce l'offset 
del file pointer ***/
int aggiungi_record_file_ico(nome_modulo, new_record, flag_lib)
char *nome_modulo;
IconFileRec *new_record;
char flag_lib;
{
   FILE *fp, *fp_tmp;
   int record_inserito, found, flag, i;
   char *path_lib, *path_libgraf, fileicone[256], file_tmp[256];
   IconFileRec record;

   if ((fp = apri_file_icoproc(CREA_FALSE,flag_lib)) == NULL)
      return (RETURN_ERROR);

/***
   if (cerca_modulo_proc(fp, &record, nome_modulo ) == RETURN_OK)
      return(RETURN_OK);
***/

   if ((fp_tmp = fopen(tmpnam(file_tmp),"w+")) == NULL)
   {
      fprintf(stderr,"Can't open temporary file for inserting record.");
      return (RETURN_ERROR);
   }

/* recupera il percorso della directory utente */
   if (flag_lib == LIB_UTENTE)
   {
      path_lib = (char *) getenv("LEGOCAD_USER");
      path_libgraf = PATH_LIBGRAF_UTE;
   }
   else
   {
      if( flag == LIB_STANDARD_GENERAL )
         path_libgraf = PATH_LIBUT_STD_GENERAL;
      else if( flag == LIB_STANDARD_BASE )
         path_libgraf = PATH_LIBUT_STD_BASE;
      else if( flag == LIB_STANDARD_AUXILIARY )
         path_libgraf = PATH_LIBUT_STD_AUXILIARY;
      else if( flag == LIB_STANDARD_NUCLEAR )
         path_libgraf = PATH_LIBUT_STD_NUCLEAR;
      else if( flag == LIB_STANDARD_SPECIAL )
         path_libgraf = PATH_LIBUT_STD_SPECIAL;
/*
      path_lib = (char *) getenv("LEGO");
      path_libgraf = PATH_LIBGRAF_STD;
*/
   }

   if (path_lib == NULL)
#ifdef VMS
      path_lib = "[]";
#else
      path_lib = ".";
#endif

   record_inserito = 0;
   while ( leggi_record_file_ico (fp,&record) != RETURN_ERROR )
   {
      if ( !record_inserito &&
           (found = strcmp(record.nome_modulo,new_record->nome_modulo)) >= 0 )
      {
          if (new_record->num_icone == 0)
             scrivi_empty_record_file_ico (fp_tmp,new_record);
          else
             scrivi_record_file_ico (fp_tmp,new_record);
          record_inserito = 1;

       /* Se il modulo e' inedito  scrivere il record in ordine alfabetico */
       /* rispetto al modulo precedente */
          if (found != 0)
             scrivi_record_file_ico (fp_tmp,&record);
      }
      else
         scrivi_record_file_ico (fp_tmp,&record);
   }

/* Se il nuovo record va inserito dopo l'ultimo */
   if ( !record_inserito)
      if (new_record->num_icone == 0)
          scrivi_empty_record_file_ico (fp_tmp,new_record);
      else
          scrivi_record_file_ico (fp_tmp,new_record);

   fclose (fp);
   fclose (fp_tmp);

#ifdef VMS
   sottodir_vms(fileicone, path_lib, path_libgraf );
#else
   sprintf(fileicone, "%s/%s/", path_lib, path_libgraf);
#endif
   strcat(fileicone,FILE_ICONE_MODP);

   flag = copia_file (file_tmp,fileicone);

#ifdef VMS
   remove(file_tmp);
#else
   unlink(file_tmp);
#endif

   if (flag)
   {
      fprintf (stderr,"Couldn't update icon_list.dat. Failure.");
      return (RETURN_ERROR);
   }
   else
      return (RETURN_OK);
}

/*-----------------------------------------------------------------------*/
/*** int leggi_file_regola(fp, record)
 *** Parametri:
 ***     SchemeFileRec *record: record del file icon_file_?p.dat 
 ***     FILE *fp           : file pointer del file icon_file_?p.dat
legge un record nel file alla posizione corrente */
int leggi_file_regola(fp, record)
FILE *fp;
SchemeFileRec *record;
{
   char buffer[DIM_BUFFER];

   if (fgets(buffer,DIM_BUFFER,fp) == NULL)
      return(RETURN_ERROR);

   buffer[strlen(buffer)-1] = '\0'; /* Cancella il \n alla fine */
   sprintf(record->nome_modulo, "%.4s", buffer);
   sprintf(record->descr_modulo,"%.50s", buffer+5);
   return(RETURN_OK);
}

/*-----------------------------------------------------------------------*/
/*** cerca_modulo_regola( fp, record, nome_modulo )
 *** Parametri:
 ***    FILE *fp : file pointer del file libut_reg/lista_schemi.dat
 ***  SchemeFileRec *record: record file libut_reg/lista_schemi.dat
 ***    char *nome_modulo: nome del modulo.
Funzione per la ricerca del modulo nel file libut_reg/lista_schemi.dat.
La funzione restituisce l'offset del modulo se tale modulo e' stato trovato,
altrimenti restituisce -1 */
long cerca_modulo_regola( fp, record, nome_modulo )
FILE *fp;
SchemeFileRec *record;
char *nome_modulo;
{
   long pos;
   char trovato = 0;

/* ciclo di lettura moduli e ricerca */
   pos = 0;
   fseek(fp, 0L, SEEK_SET);
   while ( !trovato && leggi_file_regola(fp, record) == 0 )
   {
      if ( strncmp(record->nome_modulo, nome_modulo, 4) == 0)
         return(pos); 
      else
         pos = ftell(fp);
   } 
   return(RETURN_ERROR);  /* modulo non trovato o lettura file fallita. */
}

/*-----------------------------------------------------------------------*/
/*** int scrivi_file_std_ico(fp, record)
 *** Parametri:
 ***     IconStdRec *record: record del file icon_file_?p.dat 
 ***     FILE *fp           : file pointer del file icon_file_?p.dat
scrive un record nel file alla posizione corrente 
Modifica del 11/7/94 su test valore di ritorno fprintf cerca REVISIONI */
int scrivi_file_std_ico(fp, record)
FILE *fp;
IconStdRec *record;
{
   char buffer[80];

   if (fprintf(fp, "%1d %1d %-14.14s %2d %2d %3d %3d\n", 
               record->tipo_modulo, record->num_icone,
               record->bmap_record.nome_file,
               record->bmap_record.colore_fg,
               record->bmap_record.colore_bg,
               record->bmap_record.base,
               record->bmap_record.altezza) == 0)
      return(RETURN_ERROR);

   fflush(fp);
   return(RETURN_OK);
}

/*-----------------------------------------------------------------------*/
/*** leggi_file_std_ico(fp, record, tipo_modulo)
 *** Parametri:
 ***     StdFileRec *record: record del file icon_std.dat
 ***     FILE *fp           : file pointer del file icon_std.dat
legge un record nel file alla posizione corrente */
long leggi_file_std_ico(fp, record, tipo_modulo)
FILE *fp;
IconStdRec *record;
int tipo_modulo;
{
   char buffer[DIM_BUFFER];
   long offs_std;

   fseek( fp, 0L, SEEK_SET );

/* icona standard moduli di processo alla prima riga */
/* icona standard moduli di schema alla seconda riga */
   if ( tipo_modulo == MODULE_SCHEME )
      if (fgets(buffer, DIM_BUFFER, fp ) == NULL) /* salta la prima riga */
          return(RETURN_ERROR);

   offs_std = ftell(fp);

   if (fgets(buffer,DIM_BUFFER,fp) == NULL)
      return(RETURN_ERROR);

   if (sscanf(buffer, "%1d %1d %14s %2d %2d %3d %3d\n", 
              &record->tipo_modulo, &record->num_icone,
              record->bmap_record.nome_file,
              &record->bmap_record.colore_fg,
              &record->bmap_record.colore_bg,
              &record->bmap_record.base,
              &record->bmap_record.altezza) == -1)
       return(RETURN_ERROR);

   tominus(record->bmap_record.nome_file);
   return(offs_std);
}

/*-----------------------------------------------------------------------*/
/*** FILE *apri_file_symb( record, flag_crea, flag_lib )
 *** Parametri:
 ***    SymbolFileRec *record : puntatore ad una strettura SymbolFileRec
 ***    char flag_crea : crea il file se non esiste.
 ***    char flag_lib : indica se il file icon_list.dat si trova nella libreria
 ***                    utente oppure nella libreria standard.
 ***   
Apre il file che contiene la configurazione dei simboli (symbol.dat).
Il file viene creato se non esiste ed il flag e' True */
FILE *apri_file_symb( record, flag_crea, flag_lib )
SymbolFileRec *record;
char flag_crea;
int  flag_lib;
{
   int i;
   FILE *fp_symb;
   char *path_lib, *path_libgraf, path_file_symb[256];

/* recupera il percorso della directory utente */
   if (flag_lib == LIB_UTENTE)
   {
      path_lib = (char *) getenv("LEGOCAD_USER");
      path_libgraf = PATH_LIBGRAF_UTE;
   }
   else
   {
      path_lib = (char *) getenv("LEGO");
/*
      path_libgraf = PATH_LIBGRAF_STD;
*/
      path_libgraf = PATH_LIBGRAF_STDGENERAL;
   }

   if (path_lib == NULL)
#ifdef VMS
      path_lib = "[]";
#else
      path_lib = ".";
#endif

/* percorso file symbol.dat */
#ifdef VMS
   sottodir_vms(path_file_symb, path_lib, path_libgraf ); 
#else
   sprintf(path_file_symb,"%s/%s/", path_lib, path_libgraf );
#endif
   strcat(path_file_symb, FILE_SIMBOLI);

   printf("apro file %s\n", path_file_symb);

/* se il file dei simboli non esiste allora viene creato */
   if ( access(path_file_symb, F_OK) != 0 )
   {
      if (flag_crea)
      {
         if ((fp_symb = fopen(path_file_symb, "w")) == NULL)
            s_error( APPLICATION_NAME, icofile_error, EOPENSIMB, 1 );
         record->num_simboli = 0;
         for (i=0; i<MAX_SYMBOL; i++)
         {
   	    sprintf (record->bmap_record[i].nome_file, "SYMB%02d.bmp", i+1);
            record->bmap_record[i].colore_fg = DEFAULT_FOREGROUND;
            record->bmap_record[i].colore_bg = DEFAULT_BACKGROUND;
            record->bmap_record[i].base = DEFAULT_SYMBOL_WIDTH;
            record->bmap_record[i].altezza = DEFAULT_SYMBOL_HEIGHT;
            record->bmap_record[i].esiste = FALSE;

            scrivi_file_simboli( fp_symb, &record->bmap_record[i] );
         }
         fclose( fp_symb );

         if ((fp_symb = fopen(path_file_symb, "r+")) == NULL)
            s_error( APPLICATION_NAME, icofile_error, EOPENSIMB, 1 );
      }
      else
         s_error( APPLICATION_NAME, icofile_error, EOPENSIMB, 1 );
   }
   else
   /* Se il file esiste, viene aperto in lettura/scrittura */
   {
      if ((fp_symb = fopen(path_file_symb, "r+")) == NULL) {
         if ((fp_symb = fopen(path_file_symb, "r")) == NULL)
            s_error( APPLICATION_NAME, icofile_error, EOPENSIMB, 1 );
      }

      record->num_simboli = 0;
      for (i=0; i < MAX_SYMBOL; i++)
      {
         if (leggi_file_simboli( fp_symb, &record->bmap_record[i]) != 0)
             break;

         if (record->bmap_record[i].esiste)
             record->num_simboli++;
      }
      fseek( fp_symb, 0L, SEEK_SET );
   }
   return(fp_symb);
}

/*-----------------------------------------------------------------------*/
/*** int scrivi_file_simboli(fp, record)
 *** Parametri:
 ***     FILE *fp           : file pointer del file symbol.dat
 ***     BitmapFileRec *record: record del file symbol.dat 
 *** Scrive un record nel file alla posizione corrente 
Modifica del 11/7/94 su test valore di ritorno fprintf cerca REVISIONI */
int scrivi_file_simboli(fp, record)
FILE *fp;
BitmapFileRec *record;
{
   if (fprintf(fp, "%-14.14s %2d %2d %3d %3d %1d\n", 
                    record->nome_file,
                    record->colore_fg,
                    record->colore_bg,
                    record->base,
                    record->altezza,
       	            record->esiste ) == 0)
      return(RETURN_ERROR);

   fflush(fp);
   return(RETURN_OK);
}

/*-----------------------------------------------------------------------*/
/*** int leggi_file_simboli(fp, record)
 *** Parametri:
 ***     FILE *fp : file pointer del file symbol.dat
 ***     BitmapFileRec *record: record del file symbol.dat 
 *** legge un record nel file alla posizione corrente */
int leggi_file_simboli(fp, record)
FILE *fp;
BitmapFileRec *record;
{
   if (fscanf (fp, "%14s %2d %2d %3d %3d %1d\n", 
               record->nome_file,
               &record->colore_fg,
               &record->colore_bg,
               &record->base,
               &record->altezza,
       	       &record->esiste ) == EOF)
       return(RETURN_ERROR);

   tominus(record->nome_file);
   return(RETURN_OK);  
}

/*-----------------------------------------------------------------------*/
/*** int recupera_dim_icona( nome_modulo, num_icona, width, height, flag_lib )
 ***   Parametri:
 ***   char nome_modulo : nome modulo;
 ***   int num_icona : numero icona del modulo;
 ***   int *width, *height: dimensioni dell'icona;
 ***   char flag_lib : indica se il file icon_list.dat si trova nella libreria
 ***                   utente oppure nella libreria standard.
Restituisce le dimensioni di una icona. La funzione ritorna 0 se le dimensioni
sono state recuperate, altrimenti ritorna 0 e vengono settate le dimensioni
di defaults (50x50) ***/
int recupera_dim_icona( nome_modulo, num_icona, width, height, flag_lib )
char *nome_modulo;
int num_icona;
int *width, *height;
char flag_lib;
{
   FILE *fp_modp, *fp_std;
   IconFileRec rec_modp;
   IconStdRec rec_std;
   int cod = 0;
   
   fp_modp = apri_file_icoproc(CREA_FALSE, flag_lib);
  
   if ( cerca_modulo_proc( fp_modp,&rec_modp,nome_modulo ) == RETURN_ERROR )
      cod = 1;
   else
      if ( !rec_modp.num_icone )
      {
         fp_std = apri_file_std(CREA_FALSE, flag_lib);
         if (leggi_file_std_ico(fp_std,&rec_std,MODULE_PROCESS) != RETURN_ERROR)
            cod = 1;
         else
         {
            *width = rec_std.bmap_record.base;
            *height = rec_std.bmap_record.altezza;
         }
         fclose(fp_std);
      }
      else
      {
          *width = rec_modp.bmap_record[num_icona].base;
          *height = rec_modp.bmap_record[num_icona].altezza;
      }
   if ( cod )  /* dimensioni di default(s) */
   {
      *width = 50;
      *height = 50;
   }
   fclose(fp_modp);
   return(cod);
}

/*-----------------------------------------------------------------------*/
/*** int prima_icona_disponibile( nome_modulo, width, height, flag_lib )
 ***   Parametri:
 ***    char *nome_modulo: nome del modulo;
 ***    int *width, *height: dimensioni dell'icona;
 ***    char flag_lib : indica se il file icon_list.dat si trova nella libreria
 ***                    utente oppure nella libreria standard.
Recupera la prima icona disponibile del modulo e restituisce le sue
dimensioni. La funzioni ritorna il numero dell'icona (un numero > 0 e < 10),
altrimenti ritorna 0 e vengono settate le dimensioni di defaults (50x50) */
int prima_icona_disponibile( nome_modulo, width, height, flag_lib )
char *nome_modulo;
int *width, *height;
char flag_lib;
{
   FILE *fp_modp, *fp_std;
   IconFileRec    rec_modp;
   IconStdRec     rec_std;
   int cod = 0, i;
   
   fp_modp = apri_file_icoproc(CREA_FALSE, flag_lib);
  
   if ( cerca_modulo_proc( fp_modp,&rec_modp,nome_modulo ) == RETURN_ERROR )
   {
      cod = 0;
      *width = 50;
      *height = 50;
   }
   else
   {
      if ( !rec_modp.num_icone )
      {
         fp_std = apri_file_std(CREA_FALSE, flag_lib);
         cod = 0;
         if (leggi_file_std_ico(fp_std,&rec_std,MODULE_PROCESS) != RETURN_ERROR)
         {
            *width = 50;
            *height = 50;
         }
         else
         {
            *width = rec_std.bmap_record.base;
            *height = rec_std.bmap_record.altezza;
         }
         fclose(fp_std);
      }
      else
      {
          for (i=0 ; i<10 && !rec_modp.bmap_record[i].esiste ; i++);
          if ( i >= 10)   /* impossibile ... */
          {
            cod = 0;
            *width = 50;
            *height = 50;
          }
          else
          {
            *width = rec_modp.bmap_record[i].base;
            *height = rec_modp.bmap_record[i].altezza;
	    cod = i;
          }
      }
   }
   fclose(fp_modp);
   return(cod);
}
/* fine file_icone.c */

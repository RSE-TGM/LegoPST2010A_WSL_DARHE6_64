/**********************************************************************
*
*       C Source:               document.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 11:59:19 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: document.c,2 %  (%full_filespec: 1,csrc,document.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)document.c	1.10\t3/31/95";
/*
        Fine sezione per SCCS
*/
/*** file document.c -
 ***
 ***    routine per la creazione automatica della documentazione
 ***
 ***    Creato da : Buffo Massimo (21/02/1994)
 ***    Societa'  : Genova Innovazione In liquidazione... (si salvi chi puo'!)
 ***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>

#include <Xm/Xm.h>

#include "UxXt.h"

#include "autodoc.h"
#include "unita.h"

extern ModelBlockStruct *lista_blocchi;
extern int num_blocchi;

extern char nome_modello[];

extern char page_prefix_dati[], page_prefix_var[];

extern int num_lines_vert, num_lines_horiz;

/*** crea_docdati(pag_document, pag_index)
 ***    Parametri:
 ***       int *pag_document: ritorna il numero di pagine della documentazione.
 ***       int *pag_index: ritorna il numero di pagine dell'indice della doc.
 ***
 ***    Descrizione:
 ***       creazione della documentazione relativa ai dati geometrici del
 ***       modello.
 ***/
int crea_docdati(pag_document, pag_index)
int *pag_document, *pag_index;
{
   FILE *fp_doc, *fp_ind;
   int pag_doc, pag_ind, riga_doc, riga_ind, i, j;
   char intest[50][81], tmp[20];
   NoteDelBlocco *note_blocchi;

/* dimensiona l'array delle note dei blocchi */
   note_blocchi = (NoteDelBlocco *) calloc(num_blocchi,sizeof(NoteDelBlocco));

/* Apri in scrittura il file di documentazione dati */
   if ( (fp_doc = fopen(DOC_DATI_MODELLO, "w+")) == NULL )
   {
      fprintf(stderr, "Can't create documentation file!\n");
      return(-1);
   }

   if ( (fp_ind = fopen(IND_DATI_MODELLO, "w+")) == NULL )
   {
      fprintf(stderr, "Can't create documentation file!\n");
      return(-1);
   }

   pag_doc = 1;
   pag_ind = 1;
   riga_doc = 0;
   riga_ind = 0;

/* calcola il numero di pagina nell'indice della documentazione dati */
   pag_doc = pag_ind+conta_pagine_ind(num_blocchi, num_lines_vert);

/* Nel primo foglio la descrizione del modello */
   i = descr_modello(intest);
   FoglioIntest(fp_ind, num_lines_vert, MAX_COL_VER, intest, i, "");

   StampaIntIndice(fp_ind, &riga_ind);

/* stampa la documentazione blocco x blocco */
   for (i=0 ; i<num_blocchi; i++)
       doc_dati_blocco( &lista_blocchi[i], fp_doc, fp_ind,
			&riga_doc, &pag_doc, &riga_ind, &pag_ind,
			num_lines_vert, &note_blocchi[i] );

   sprintf(tmp,"Pag. %s %d", page_prefix_dati, pag_doc);
   FinePagina(fp_doc, num_lines_vert-riga_doc, MAX_COL_VER, tmp);

   sprintf(tmp,"Pag. %s %d",page_prefix_dati, pag_ind);
   FinePagina(fp_ind, num_lines_vert-riga_ind, MAX_COL_VER, tmp);
   fclose(fp_ind);

/* stampa la documentazione dei moduli utilizzati */
   pag_doc += StampaDocModuli(fp_doc, num_lines_vert);

/* stampa le note di calcolo riporate in SORGENTE_DATI.TXT */
   pag_doc += StampaNoteCalcolo(fp_doc, note_blocchi, num_blocchi,MAX_COL_VER,
	 		        num_lines_vert);

   fclose(fp_doc);

   *pag_document = pag_doc+1;
   *pag_index = pag_ind+1;

   for (i=0 ; i<num_blocchi ; i++)
       dealloca_note(note_blocchi[i].note_di_calcolo);
   free(note_blocchi);
}

/*** crea_docvar(pag_document, pag_index)
 ***    Parametri:
 ***       int *pag_document: ritorna il numero di pagine della documentazione.
 ***       int *pag_index: ritorna il numero di pagine dell'indice della doc.
 ***
 ***    Descrizione:
 ***       creazione della documentazione relativa alle variabili dei blocchi
 ***       del modello.
 ***/
int crea_docvar(pag_document, pag_index)
int *pag_document, *pag_index;
{
   FILE *fp_doc, *fp_ind;
   int pag_doc, pag_ind, riga_doc, riga_ind, i, j;
   char intest[50][81], tmp[20];

/* Apri in scrittura il file di documentazione dati */
   if ( (fp_doc = fopen(DOC_VAR_MODELLO, "w+")) == NULL )
   {
      fprintf(stderr, "Can't create documentation file!\n");
      return(-1);
   }

   if ( (fp_ind = fopen(IND_VAR_MODELLO, "w+")) == NULL )
   {
      fprintf(stderr, "Can't create documentation file!\n");
      return(-1);
   }

   pag_doc = 1;
   pag_ind = 1;
   riga_doc = 0;
   riga_ind = 0;

/* calcola il numero di pagina nell'indice della documentazione dati */
   pag_doc = pag_ind+conta_pagine_ind(num_blocchi, num_lines_vert);

/* Nel primo foglio la descrizione del modello */
   i = descr_modello(intest);
   FoglioIntest(fp_ind, num_lines_vert, MAX_COL_VER, intest, i, "");

   StampaIntIndice(fp_ind, &riga_ind);

/* stampa la documentazione blocco x blocco */
   printf("stampa variabili blocco x blocco\n");
   for (i=0 ; i<num_blocchi; i++)
       doc_var_blocco( &lista_blocchi[i], fp_doc, fp_ind,
		       &riga_doc, &pag_doc, &riga_ind, &pag_ind,
			num_lines_vert, num_lines_horiz );

   sprintf(tmp,"Pag. %s %d", page_prefix_var, pag_doc);
   FinePagina(fp_doc, num_lines_horiz-riga_doc, MAX_COL_HOR, tmp);

   sprintf(tmp,"Pag. %s %d",page_prefix_var, pag_ind);
   FinePagina(fp_ind, num_lines_vert-riga_ind, MAX_COL_VER, tmp);

   *pag_document = pag_doc+1;
   *pag_index = pag_ind+1;

   fclose(fp_ind);
   fclose(fp_doc);
}

/*** crea_sstate_doc(pag_document)
 ***    Parametri:
 ***       int *pag_document: ritorna il numero di pagine della documentazione.
 ***
 ***    Descrizione:
 ***       creazione della documentazione relativa ai risultati di piu'
 ***       calcoli dello stazionario.
 ***/
int crea_sstate_doc(pag_document)
int *pag_document;
{
   FILE *fp_doc;
   int num_f14, pag_doc, riga_doc, i, j;
   char intest[5][81], tmp[150], buff[150];
   InfoBlock *dati_blocco;
   BlockVarNmod *bvarN;

   extern StructVarianti varianti_modello[];
   extern byte num_varianti;

   int num_dati, num_var_out;

/* Apri in scrittura il file di documentazione dati */
   if ( (fp_doc = fopen(DOC_SSTATE_MODELLO, "w+")) == NULL )
   {
      fprintf(stderr, "Can't create documentation file!\n");
      *pag_document = -1;
      return(-1);
   }

   pag_doc = 1;
   riga_doc = 0;

   leggi_all_var_f14(tmp, &dati_blocco, &num_dati, &num_var_out);

   for ( i = 0, j = 0 ; i < num_varianti ; i++ )
      if (varianti_modello[i].abilitato)
	 strcpy(intest[j++], varianti_modello[i].titolo);

   num_f14 = j;

   for ( ; j < num_varianti ; j++ )
      strcpy(intest[j], "< NONE >");

   StampaIntestSteadyState(fp_doc, intest, num_f14, &riga_doc);

   for (i=0 ; i<num_dati; i++)
   {
       bvarN = &dati_blocco[i].varN;
       sprintf(tmp,"%c%8.8s |%3.3s|%7.7s|", (bvarN->noto) ? '*':' ',
		    bvarN->nome, (i >= num_var_out) ? "IN" : "OUT",
		    dim_unita_misura(bvarN->nome[0]));

       for (j=0 ;j<num_f14 ; j++)
       {
	   sprintf(buff, "%-14.14s|", bvarN->valori[j]);
	   strcat(tmp, buff);
       }

       copy_n_car(buff, bvarN->descrizione, 132 - strlen(tmp));
       strcat(tmp, buff);

       StampaStrInTabella(fp_doc, 0, MAX_COL_HOR, tmp);
       riga_doc++;

       if (riga_doc+2 >= num_lines_horiz-2)
       {
	   StampaTrattoOrizzontale(fp_doc, 0, MAX_COL_HOR);
	   sprintf(tmp,"Pag. %s %d", "", pag_doc++);
	   FinePagina(fp_doc, num_lines_horiz-riga_doc-1, MAX_COL_HOR, tmp);
	   riga_doc = 0;
	   StampaIntestSteadyState(fp_doc, intest, num_f14, &riga_doc);
       }
   }

   StampaTrattoOrizzontale(fp_doc, 0, MAX_COL_HOR);
   sprintf(tmp,"Pag. %s %d", "", pag_doc);
   FinePagina(fp_doc, num_lines_horiz-riga_doc-1, MAX_COL_HOR, tmp);
   fclose(fp_doc);

   *pag_document = pag_doc;

   free(dati_blocco);
}


/*** StampaIntestSteadyState(fp_doc, intest, num_varianti, &riga_doc);
 ***    Parametri:
 ***       FILE *fp_doc: file pointer documentazione.
 ***       char intest[][21]: intestazione colonne valori
 ***       int num_varianti: numero file f14.dat
 ***       int *riga_doc: (indirizzo) riga corrente
 ***
 ***   Descrizione:
 ***       Stampa l'intestazione della tabella relativa ai calcoli dello
 *+*       stazionario riferiti a piu' file f14.dat
 ***/
StampaIntestSteadyState(fp_doc, intest, num_varianti, riga_doc)
FILE *fp_doc;
char intest[][81];
int num_varianti;
int *riga_doc;
{
    int i;
    char buff[143], buff2[80];

    StampaTrattoOrizzontale(fp_doc, 0, MAX_COL_HOR);
    sprintf(buff, "NOME VAR. |TYP| UNITA |");

    for (i=0 ; i<num_varianti ; i++)
    {
       sprintf(buff2, "%-14.14s|",intest[i]);
       strcat(buff, buff2);
    }

    strcat(buff, "  DESCRIZIONE");

    StampaStrInTabella(fp_doc, 0, MAX_COL_HOR, buff);
    StampaTrattoOrizzontale(fp_doc, 0, MAX_COL_HOR);
    (*riga_doc) += 3;
}

/*** int descr_modello(stringhe)
 ***    Parametri:
 ***      char  stringhe[][81] : array di stringhe che conterranno il nome e
 ***                             la descrizione del modello.
 ***    Descrizione:
 ***      aggiorna l'array di stringhe con il nome del modello e la sua 
 ***      descrizione. ritorna il numero di stringhe che sono state inserite
 ***      nell'array  ( max 50 )
 ***/
int descr_modello(stringhe)
char stringhe[][81];
{
   int i = 1;
   FILE *fp;

   strcpy(stringhe[0],"MODELLO : ");
   strcat(stringhe[0],nome_modello);

   if ((fp=fopen("descr.dat","r")) != NULL)
   {
      for ( i=1 ; fgets(stringhe[i],80,fp) != NULL && i<5; i++);
      fclose(fp);
   }

   if ((fp=fopen(FILE_NOTE_MODELLO,"r")) == NULL)
      return(i);
   for ( ; fgets(stringhe[i],80,fp) != NULL && i<50; i++);
   fclose(fp);

   return(i);
}

/*** StampaIntBlocco(fp, blocco, riga)
 ***   Parametri:
 ***      FILE *fp: file pointer documentazione
 ***      ModelBlockStruct *blocco: struttura che contiene i dati del blocco
 ***      int *riga: numero di riga da aggiornare
 ***
 ***   Descrizione:
 ***      Stampa l'intestazione di un blocco nel file di documentazione
 ***/
StampaIntBlocco(fp, blocco, riga)
FILE *fp;
ModelBlockStruct *blocco;
int *riga;
{
   fprintf(fp, "Descrizione componente: %s\n",blocco->descr);
   fprintf(fp, "Sigla componente: %s\n",blocco->nome);
   fprintf(fp, "Modulo libreria: %s\n\n",blocco->nome_mod);
   (*riga) += 4;
}

/*** int conta_pagine_ind(num_blocchi, max_righe)
 ***    Parametri:
 ***       int num_blocchi: numero blocchi del modello
 ***       int max_righe: numero di righe per foglio.
 ***
 ***    Descrizione:
 ***       La funzione calcola il numero di pagine occupato dall'indice della
 ***       documentazione. E' utile per il fatto che posso sapere la pagina
 ***       da cui partire per la documentazione.
 ***       Ritorna il numero di pagina iniziale della documentazione
 ***/
int conta_pagine_ind(num_blocchi, max_righe)
int num_blocchi, max_righe;
{
   return((int) 3*num_blocchi/(max_righe-3) + 1 );
}

/*** void FinePagina(fp, num_righe, lung_riga, pedice)
 ***    Parametri:
 ***       FILE *fp: file pointer documentazione
 ***       int num_righe: numero di righe da saltare
 ***       int lung_riga: lunghezza della riga.
 ***       char *pedice: stringa da stampare in fondo alla pagina (centrato)
 ***
 ***   Descrizione:
 ***       termina una pagina con la stampa del pedice
 ***/
void FinePagina(fp, num_righe, lung_riga, pedice)
FILE *fp;
int num_righe, lung_riga;
char *pedice;
{
   int dummy = 0;
   int lung;
   char temp[140];

   if (num_righe >= 1)
   {
      if ( pedice != NULL && !Empty(pedice) )
      {
	 StampaBlankLine(fp, &dummy, num_righe-1);

      /* Stampa la stringa pedice centrata nell'ultima linea */
	 lung = strlen(pedice);
	 if (lung > lung_riga)
	 {
	     pedice[lung_riga-1] = '\f';
	     pedice[lung_riga  ] = '\n';
	     pedice[lung_riga+1] = '\0';
	     strcpy(temp, pedice);
	 }
	 else
	 {
	     centra(temp, pedice, lung_riga);
	     strncpy(temp, nome_modello, strlen(nome_modello));
	     strcat(temp,"\f\n");
	 }
	 fputs(temp,fp);
      }
      else
	 StampaBlankLine(fp, &dummy, num_righe);
   }
}

/***
 *** StampaBlankLine(fp, riga, num_righe)
 ***    Parametri:
 ***       FILE *fp : file pointer
 ***       int *riga: (indirizzo) riga corrente della documentazione
 ***       int num_righe: numero righe "blank"
 ***
 ***    Descrizione:
 ***       Stampa n righe vuote.
 ***/
StampaBlankLine(fp, riga, num_righe)
FILE *fp;
int *riga;
int num_righe;
{
   *riga = *riga + num_righe;
   while ( num_righe-- ) fprintf(fp,"\n");
}

/*** void StampaStrInTabella(fp, left_marg, lung_riga, stringa)
 ***    Parametri:
 ***       FILE *fp: file pointer documentazione
 ***       int lung_riga : lunghezza della riga in caratteri
 ***       int left_mar  : margine sinistro
 ***       char *stringa : stringa da stampare tra i due '|'
 ***
 ***    Descrizione:
 ***       inserisce nel file puntato da 'fp' una 'stringa' tra due '|' di
 ***       lunghezza 'lung_riga' (nella tabella della documentazione del
 ***       blocco)
 ***/
void StampaStrInTabella(fp, left_marg, lung_riga, stringa)
FILE *fp;
int left_marg, lung_riga;
char *stringa;
{
   char buff[150];
   int n;

   riempi(buff, lung_riga);
   buff[left_marg] = '|';
   buff[lung_riga-1] = '|';
   buff[lung_riga  ] = '\n';
   buff[lung_riga+1] = '\0';

   if ( stringa[strlen(stringa)-1] == '\n')
      stringa[strlen(stringa)-1] = ' ';

   n = strlen(stringa);
   strncpy(buff+left_marg+2, stringa, (n>lung_riga-3) ? lung_riga-3 : n);
   fputs(buff, fp);
}

/*** void StampaTrattoOrizzontale(fp, left_marg, lung_riga)
 ***   Parametri:
 ***      FILE *fp : file pointer
 ***      int left_marg : margine sinistro
 ***      int lung_riga :lunghezza della riga in caratteri
 ***
 ***   Descrizione:
 ***      stampa una riga di trattini '-'
 ***/
void StampaTrattoOrizzontale(fp, left_marg, lung_riga)
FILE *fp;
int left_marg, lung_riga;
{
   int i;
   char buff[140];

   riempi(buff, left_marg);

   buff[left_marg] = '|';

   for(i = left_marg; i<lung_riga-1; i++)
      buff[i+1] = '-';

   buff[lung_riga-1]= '|';
   buff[lung_riga  ]='\n';
   buff[lung_riga+1]='\0';

   fputs(buff,fp);
}

/*** FoglioIntest(fp, lung_riga, str, n_str, pedice)
 ***   Parametri:
 ***     FILE *fp : file pointer del file di documentazione
 ***     int max_righe: num righe per pagina
 ***     int lung_riga : lunghezza della riga in caratteri
 ***     char str[][] : array di stringhe da stampare al centro del foglio
 ***     int n_str : numero di stringhe in 'str'
 ***     char *pedice : stringa da stampare in fondo alla pagina
 ***
 ***  Descrizione:
 ***     stampa la pagina di intestazione documento
 ***/
FoglioIntest(fp, max_righe, lung_riga, str, n_str, pedice)
FILE *fp;
int max_righe, lung_riga;
char str[][81];
int n_str;
char *pedice;
{
   int riga = 0, i;
   char buff[81];

   if (n_str == 0)
      return;

   StampaBlankLine(fp, &riga, max_righe/2-n_str/2);
   for (i=0; i<n_str && riga < max_righe; i++)
   {
       centra(buff, str[i], lung_riga);
       StampaRiga(fp, &riga, lung_riga, buff);
   }

   FinePagina(fp, max_righe-riga, lung_riga, pedice);
}

/*** void StampaRiga(fp, riga, lung_riga, stringa)
 ***    Parametri:
 ***       FILE *fp : file pointer file di documentazione
 ***       int *riga: (indirizzo) riga corrente della doc.
 ***       int lung_riga: lunghezza della riga
 ***       char *stringa : stringa da stampare
 ***
 ***    Descrizione:
 ***       inserisce nel file puntato da 'fp' la stringa di caratteri
 ***       'stringa' */
void StampaRiga(fp, riga, lung_riga, stringa)
FILE *fp;
int *riga;
int lung_riga;
char  *stringa;
{
   int lung_str;

   lung_str = strlen(stringa);

/* tronca la stringa se la sua lunghezza e' maggiore della lunghezza */
/* della riga */
   if (lung_str > lung_riga)
   {
	stringa[lung_riga-1] = '\n';
	stringa[lung_riga] = '\0';
   }

/* Se in fondo alla riga non c'e' il newline .... */
   if ( stringa[lung_str-1] != '\n')
      strcat(stringa,"\n");

   fputs(stringa, fp);
   (*riga)++;
}

/*** StampaIntIndice(fp, riga)
 ***    Parametri:
 ***       FILE *fp :file pointer del file indice della documentazione.
 ***       int *riga:(indirizzo) numero righe intestazione
 ***
 ***    Descrizione:
 ***       Stampa l'intestazione nel file indice della documentazione dati
 ***/
StampaIntIndice(fp, riga)
FILE *fp;
int *riga;
{
   StampaTrattoOrizzontale( fp, 0, MAX_COL_VER );
   StampaStrInTabella(fp, 0, MAX_COL_VER, "Blocco   |Modulo| Pag.  |");
   StampaTrattoOrizzontale( fp, 0, MAX_COL_VER );

   *riga = 3;
}

/*** ScriviIndice(fp, pblock, riga, pagina, max_righe, pag_blocco, strpref)
 ***    Parametri:
 ***       FILE *fp: file pointer relativo al file indice documentazione
 ***       ModelBlockStruct *pblock: info del blocco.
 ***       int *riga : (indirizzo) riga corrente nel file indice
 ***                               documentazione
 ***       int *pagina : (indirizzo) numero della pagina corrente
 ***       int max_righe : numero massimo di righe nel file indice
 ***       int pag_blocco: numero di pagina dove si trova la doc. del blocco
 ***       char *strpref: prefisso, stringa di caratteri da stampare in fondo
 ***                      alla pagina.
 ***
 ***    Descrizione:
 ***       Prende il nome del blocco,la sua descrizione ed il nome del modulo
 ***       dalla struttura DatiBlocco ed aggiorna il file indice della
 ***       documentazione
 ***/
ScriviIndice(fp, pblock, riga, pagina, max_righe, pag_blocco, strpref)
FILE *fp;
ModelBlockStruct *pblock;
int *riga, *pagina;
int max_righe, pag_blocco;
char *strpref;
{
   char tmp[82];

/* Se si e' arrivati in fondo alla pagina dell'indice della doc. */
   if ( (*riga)+3 >= max_righe-2 )
   {
       sprintf(tmp, "Pag. %s %d", strpref, (*pagina)++);
       FinePagina(fp, max_righe-(*riga), MAX_COL_VER, tmp);
       StampaIntIndice(fp);
       *riga = 3;
   }

   sprintf(tmp, "%8.8s | %4.4s | %-5d | %52.52s",
		pblock->nome, pblock->nome_mod, pag_blocco, pblock->descr);
   StampaStrInTabella(fp, 0, MAX_COL_VER, tmp);
   StampaStrInTabella(fp, 0, MAX_COL_VER, "         |      |       |");
   StampaTrattoOrizzontale(fp, 0, MAX_COL_VER);
   *riga = *riga + 3;
}

/*** centra(dest,sorg,lung_riga)
 ***    Parametri:
 ***       char *dest     : stringa destinazione
 ***       char *sorg     : stringa sorgente
 ***       int lung_riga: numero di caratteri della riga
 ***
 ***    Descrizione:
 ***       Copia in dest la stringa sorg centrata rispetto alla lunghezza
 ***       della riga
 ***/
centra(dest,sorg,lung_riga)
char *sorg,*dest;
int lung_riga;
{
    riempi(dest,(int) (lung_riga-strlen(sorg))/2);
    strcat(dest,sorg);
}

/*** cerca_str(buf,n,str)
 ***    Parametri:
 ***       char *buf : buffer in cui ricercare la stringa 'str'
 ***       int  n : numero di caratteri da considerare in 'buf'
 ***       char *str : stringa da ricercare
 ***
 ***    Descrizione:
 ***       controlla se nel buffer ' buf' e' contenuta la stringa 'str'
 ***       ritorna -1 se non e' stata trovata
 ***/
cerca_str(buf,n,str)
char buf[];
int n;
char str[];
{
   int i, j, lung_str;

   lung_str = strlen(str);

   for (i = 0 ; i < n-(lung_str-1) ; i++)
   {
       for(j = 0 ; buf[j+i] == str[j] && j<lung_str ; j++);
       if (j == lung_str)
	  return(i);
   }
   return(-1);
}

/*** int StampaNoteCalcolo(fp_doc,note_blocchi,num_blocchi,lung_riga,max_righe)
 ***    Parametri:
 ***       FILE *fp_doc: file pointer documentazione
 ***       ArrayNote *note_blocchi: note dei blocchi del modello
 ***       int num_blocchi: numero blocchi del modello
 ***       int lung_riga: lunghezza della riga
 ***       int max_righe: numero di rirghe per pagina
 ***
 ***    Uscita:
 ***        ritorna il numero di pagine utilizzate
 ***
 ***    Descrizione:
 ***       funzione per la stampa dei testi delle note sul file di
 ***       documentazione
 ***/
int StampaNoteCalcolo(fp_doc, note_blocchi, num_blocchi, lung_riga, max_righe)
FILE *fp_doc;
NoteDelBlocco *note_blocchi;
int num_blocchi;
int lung_riga, max_righe;
{
   char *str, buffer[90], appendice[80], intest[2][81];
   HeaderNote *ptr;
   int i, riga = 0, pag = 0;

/* stringa da stampare in fondo ad ogni foglio */
   strcpy(appendice,"Appendice 2: note di calcolo");

   strcpy(intest[0],"APPENDICE 2");
   strcpy(intest[1],"NOTE DI CALCOLO");

   FoglioIntest(fp_doc, max_righe, lung_riga, intest, 2, "..NOTE.." );
   pag++;

/* Ciclo di lettura dei testi e scrittura della documentazione */
   for ( i=0 ; i < num_blocchi; i++ )
   {
       if (note_blocchi[i].note_di_calcolo == NULL)
	  continue;

       if (riga+5 >= max_righe-2)
       {
	   FinePagina( fp_doc, max_righe-riga, lung_riga, appendice );
	   riga = 0;
           pag++;
       }

       fprintf(fp_doc, "NOTE DI CALCOLO RELATIVE AL BLOCCO %s\n",
		       note_blocchi[i].pblock->nome );
       fprintf(fp_doc, "\n");
       riga += 2;

       for ( ptr = note_blocchi[i].note_di_calcolo ;
	     ptr != NULL ;
	     ptr = ptr->next_header )
       {
	   if (riga+3 >= max_righe-2)
	   {
	       FinePagina( fp_doc, max_righe-riga, lung_riga, appendice );
	       riga = 0;
               pag++;
	   }

	   fprintf(fp_doc, "NOTA DI CALCOLO %s\n", ptr->nota );
	   fprintf(fp_doc, "\n");
	   riga += 2;

	   str = ptr->testo;
	   while ( (str = StampaNota(fp_doc, str, lung_riga, &riga)) != NULL )
	   {
	       if (riga+2 >= max_righe-2)
	       {
		  FinePagina( fp_doc, max_righe-riga, lung_riga, appendice );
		  riga = 0;
                  pag++;
	       }
	   }
       }
   }

   if (riga)
   {
       FinePagina( fp_doc, max_righe-riga, lung_riga, appendice );
      pag++;
   }
   return(pag);
}

/*** int ContaRigheNota(testo)
 ***    Parametri:
 ***       char *testo;
 ***
 ***    Descrizione:
 ***       conta il nmumero di righe che occupa il testo della nota di
 ***       calcolo o la nota del blocco.
 ***/
int ContaRigheNota(testo)
char *testo;
{
   int num = 0;

   if (testo == NULL)
      return (0);

   for ( ; *testo != '\0' ; testo++ )
      if ( *testo == '\n' )
	 num++;

   if ( *(testo-1) != '\n' )
      num++;

   return(num);
}

/*** char *StampaNota(fp_doc,testo,lung_riga,riga)
 ***    Parametri:
 ***       FILE *fp_doc: file pointer documentazione
 ***       char *testo: testo da stampare
 ***       int lung_riga: lunghezza della riga nel foglio di doc.
 ***       int *riga: (indirizzo) riga corrente
 ***
 ***    Uscita:
 ***       testo rimanente da stampare oppure NULL
 ***
 ***    Descrizione:
 ***       stampa una riga del testo della nota
 ***/
char *StampaNota(fp_doc, testo, lung_riga, riga)
FILE *fp_doc;
char *testo;
int lung_riga, *riga;
{
   char buffer[140];
   int i;

   if (testo == NULL)
      return(NULL);

   for (i=0 ; (buffer[i] = testo[i])  && testo[i] != '\n' ; i++);

   (*riga)++;

   if (buffer[i])
   {
      buffer[i+1] = '\0';
      fprintf(fp_doc, "%s", buffer);
      return(testo+i+1);
   }
   else
   {
      if (buffer[i-1] != '\n')
	 strcat(buffer, "\n");
      fprintf(fp_doc, "%s", buffer);
      return(NULL);
   }
}

/*** void dealloca_note(ptr_note)
 ***    Parametri:
 ***       HeaderNote *ptr_note: lista delle note
 ***
 ***    Descrizione:
 ***       dealloca la memoria utilizzata nella lista delle note.
 ***/
void dealloca_note(ptr_note)
HeaderNote *ptr_note;
{
   HeaderNote *tmp;

   while ( ptr_note != NULL )
   {
      tmp = ptr_note->next_header;

      free( ptr_note->testo );
      free( ptr_note );

      ptr_note = tmp;
   }
}

/*** funzioni di utilita' per la stampa ***/

long vai_alla_pagina(fp, max_righe, page_no)
FILE *fp;
int max_righe, page_no;
{
    int i;
    char buffer[256];

    fseek(fp, 0L, SEEK_SET);
    for ( i=0 ; i<max_righe * (page_no-1); i++ )
	if (fgets(buffer, 256, fp) == NULL)
	    return(-1);
    return( ftell(fp) );
}

char *leggi_pagina(fp, max_righe)
FILE *fp;
int max_righe;
{
    int i, size;
    char buffer[256], *page;

    size = 1;
    page = NULL;

    for ( i=0 ; i < max_righe ; i++ )
       if (fgets(buffer, 256, fp) == NULL)
	  break;
       else
       {
	   size += strlen(buffer);
	   page = (char *) realloc(page, size);

	   if ( i == 0 )
	      strcpy(page, buffer);
	   else
	      strcat(page, buffer);
       }

       return(page);
}

long pagina_prec(fp, max_righe, offs_doc)
FILE *fp;
int max_righe;
long offs_doc;
{
    char c;
    long offs, i;

    for ( i=2 ; max_righe > 0 && offs_doc > i ; i++ )
    {
	if (fseek(fp, offs_doc-i, SEEK_SET) == -1)
	   return(-1);

	if ((c = fgetc(fp)) == NULL)
	    return(-1);
	else
	    if ( c == '\n' )
	       max_righe--;
    }

    if (offs_doc == i)
    {
       fseek(fp, 0, SEEK_SET);
       offs = 0L;
    }
    else
       offs = ftell(fp);

    return( offs );
}

long pagina_succ(fp, max_righe, offs_doc)
FILE *fp;
int max_righe;
long offs_doc;
{
    char *str, buffer[256];
    int  i;

    if (fseek (fp, offs_doc, SEEK_SET) == -1)
       return(-1);

    for ( i=0 ; i<max_righe; i++ )
	if ((str = fgets(buffer, 256, fp)) == NULL)
	    break;

    if (str == NULL)
       return(-1);
    else
       return( ftell(fp) );
}

/*** int conta_pagine_doc(nome_file, max_righe, num_pag)
 ***   Parametri:
 ***     char *nome_file: nome file documentazione
 ***     int max_righe: max righe per pagina
 ***
 ***   Uscita:
 ***     ritorna il numero di pagine della documentazione
 ***
 ***   Descrizione:
 ***     vedi uscita.
 ***/
int conta_pagine_doc(nome_file, max_righe)
char *nome_file;
int max_righe;
{
   FILE *fp;
   int i, num;
   char buffer[256];

   if ((fp = fopen(nome_file, "r")) == NULL)
      return(-1);

   for ( i=0, num=0 ;  fgets(buffer, 256, fp) != NULL ; i++ )
      if ( i >= max_righe) 
      {
         i = 0;
         num++;
      }

   fclose(fp);

   return(num+1);
}

/*** fine document.c ***/

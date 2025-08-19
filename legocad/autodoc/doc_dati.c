/**********************************************************************
*
*       C Source:               doc_dati.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 11:57:35 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: doc_dati.c,2 %  (%full_filespec: 1,csrc,doc_dati.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)doc_dati.c	1.10\t3/31/95";
/*
        Fine sezione per SCCS
*/
/*** file doc_dati.c

 creazione della documentazione relativa ai dati geometrici e tisici

 Creato da Buffo Max (ex-G.I.I.) il 25/07/1994

***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <unistd.h>

#include <Xm/Xm.h>

#include "UxXt.h"

#include "autodoc.h"
#include "unita.h"

int conta_righe_doc_dati(InfoBlock*, int, char*);
void ScriviIndice(FILE*, ModelBlockStruct*, int*, int*, int, int, char*);
void StampaIntBlocco(FILE*, ModelBlockStruct*, int*);
void StampaBlankLine(FILE*, int*, int);
int ContaRigheNota(char*);
void riempi(char*, int);
void FoglioIntest(FILE*, int, int, char[][81], int, char*);
char* tominus(char*);
int CercaDocModuloDatiG(FILE*);
int LineaFileDoc(char*, int, FILE*);
int cerca_str(char[], int, char[]);

extern char page_prefix_dati[];

/*** doc_dati_blocco(pblock)
 ***    Parametri:
 ***       ModelBlockStruct *pblock: info del blocco.
 ***
 ***    Descrizione:
 ***       stampa la documentazione relativa ad un blocco
 ***/
int doc_dati_blocco(ModelBlockStruct *pblock, FILE *fp_doc, FILE *fp_ind, int *riga_doc, int *pag_doc, int *riga_ind, int *pag_ind, int max_righe, NoteDelBlocco *note_blocco)
{
   short righe_blocco, num=0;
   InfoBlock *dati_blocco;
   char *nome_blocco;
   int num_dati;
   HeaderNote *ptr_note;
   char *nota_blocco;
   BlockData *bdata;
   char  stringa[100], tmp[20], *str;
   short i, j, tratto = 1, commento=0;

   note_blocco->pblock = pblock;

   leggi_record_f14(pblock->nome,&dati_blocco, &num_dati,
		    &note_blocco->note_di_calcolo, &nota_blocco);

/* controlla il numero di righe che occupa il blocco */
   righe_blocco = conta_righe_doc_dati(dati_blocco, num_dati, nota_blocco);

/* Verifica se la documentazione del blocco puo' stare nella pagina */
/* corrente */
   if ( *riga_doc+righe_blocco > max_righe-2 && *riga_doc > 1)
   {
	sprintf(tmp, "Pag. %s %d", page_prefix_dati, (*pag_doc)++);
	FinePagina(fp_doc, max_righe - *riga_doc, MAX_COL_VER, tmp);
	*riga_doc = 0;
   }

/* indice del blocco */
   ScriviIndice(fp_ind, pblock, riga_ind, pag_ind, max_righe,
		*pag_doc, page_prefix_dati);

/* Stampa l'intestazione del blocco */
   StampaIntBlocco(fp_doc, pblock, riga_doc);

/* Stampa la nota relativa al blocco in generale  */
   str = nota_blocco;
   while( (str = StampaNota(fp_doc, str, MAX_COL_VER, riga_doc)) != NULL)
   {
	if ( *riga_doc >= max_righe-2 )
	{
	   sprintf(tmp, "Pag. %s %d", page_prefix_dati, (*pag_doc)++);
	   FinePagina(fp_doc, max_righe - *riga_doc, 79, tmp);
	   *riga_doc = 0;
	}
   }

/* stampa dei parametri costanti del blocco */
   if ( *riga_doc + 5 >= max_righe-2 )
   {
      sprintf(tmp, "Pag. %s %d", page_prefix_dati, (*pag_doc)++);
      FinePagina(fp_doc, max_righe - *riga_doc, MAX_COL_VER, tmp);
      *riga_doc = 0;
   }
/* Se il blocco non ha parametri costanti allora notificare nella doc. */
   if ( !num_dati )
   {
	StampaBlankLine(fp_doc, riga_doc, 1);
	strcpy(stringa, "NON ESISTONO PARAMETRI COSTANTI");
	StampaRiga(fp_doc, riga_doc, MAX_COL_VER, stringa);
   }
   else
	StampaIntestDati(fp_doc, riga_doc);

   for (j=0 ; j<num_dati ; j++)
   {
       switch (dati_blocco[j].flag)
       {
	   case DATI_GEOMETRICI:
		bdata = &dati_blocco[j].dati;
		if ( tratto && commento )
		{
		    StampaTrattoOrizzontale(fp_doc, 0, MAX_COL_VER);
		    (*riga_doc)++;
		}

		tratto = 0;
		sprintf(stringa,
			"%8.8s | %10.10s |%27.27s|%5.5s|%3.3s |%8.8s |%4.4s",
			 bdata->nome, bdata->valore, bdata->sorgente,
			 bdata->release, bdata->pagina, bdata->data,
			 bdata->note);
		StampaStrInTabella(fp_doc, 0, MAX_COL_VER, stringa);
		(*riga_doc)++;
		break;

	   case COMMENTO:
		commento = 1;
		if ( !tratto )
		{
		    StampaTrattoOrizzontale(fp_doc, 0, MAX_COL_VER);
		    (*riga_doc)++;
		}
		StampaStrInTabella(fp_doc, 0, MAX_COL_VER,
				   dati_blocco[j].comment.commento);
		tratto = 1;
		(*riga_doc)++;
		break;
       }

       if ( *riga_doc + 2 >= max_righe-2 )
       {
	   StampaTrattoOrizzontale(fp_doc, 0, MAX_COL_VER);
	   fputs("( continua nella pagina successiva )\n", fp_doc);
	   sprintf(tmp, "Pag. %s %d", page_prefix_dati, (*pag_doc)++);
	   (*riga_doc) += 2;
	   FinePagina(fp_doc, max_righe - (*riga_doc), MAX_COL_VER, tmp);
	   *riga_doc = 1;
	   fputs("( continua dalla pagina precedente )\n", fp_doc);
	   StampaIntestDati(fp_doc, riga_doc);
       }
   }

   if (num_dati)
   {
       StampaTrattoOrizzontale(fp_doc, 0, MAX_COL_VER);
       (*riga_doc)++;
   }

/* Se non si e' arrivati alla fine del foglio allora stampa due linee */
/* vuote per separare la stampa della documentazione del blocco */
/* successivo */
   if ( *riga_doc + 2 < max_righe - 2)
      StampaBlankLine(fp_doc, riga_doc, 2);

   free(dati_blocco);
   free(nota_blocco);
}

/*** void StampaIntestDati(riga)
 ***    Parametri:
 ***       FILE *fp_doc: file pointer docunmentazione
 ***       int *riga: (indirizzo) numero di righe della documentazione
 ***
 ***    Descrizione:
 ***       stampa l'intestazione della tabella della documentazione di un
 ***       blocco.
 ***/
void StampaIntestDati(fp_doc, riga)
FILE *fp_doc;
int *riga;
{
   StampaTrattoOrizzontale(fp_doc, 0, MAX_COL_VER);
   StampaStrInTabella(fp_doc, 0, MAX_COL_VER,
		    "  Sigla  |   Valore   |        Sorgente dato      | Rel.|Pag.|  Data   |Note");
   StampaStrInTabella(fp_doc, 0, MAX_COL_VER,
		    "  dato   |            |                           |     |    |         |cal.");
   StampaTrattoOrizzontale(fp_doc, 0, MAX_COL_VER);
   *riga = *riga + 4;
}

/*** int conta_righe_doc_dati(dati_blocco, num_dati, nota_blocco)
 ***    Parametri:
 ***        InfoBlock *dati_blocco: info del blocco.
 ***        int num_dati :numero di elementi in lista
 ***        char *nota_blocco: nota del blocco
 ***
 ***    Descrizione:
 ***        conta il numero delle righe che occupa la documentazione di un
 ***        blocco.
 ***/
int conta_righe_doc_dati(InfoBlock *dati_blocco, int num_dati, char *nota_blocco)
{
   short i, tratto=1, commento=0, numero;

   for (numero=11, i=0; i < num_dati ; i++)
   {
     /* Se si considera una linea di commento .. */
	if ( dati_blocco[i].flag == COMMENTO )
	{
	    commento=1;
	    if ( !tratto )
		numero++;
	    numero++;
	    tratto=1;
	}
	else
	/* Altrimenti si considera un record di dati geometrici e fisici */
	{
	    if ( tratto && commento )
	       numero++;
	    tratto=0;
	    numero++;
	}
   }

   numero += ContaRigheNota(nota_blocco)+1;
   return(numero);
}


/*** int StampaDocModuli(fp, max_righe)
 ***    Parametri:
 ***       FILE *fp_doc: file pointer doc. dati
 ***       int max_righe: numero massimo di righe per pagina
 ***
 ***    Uscita:
 ***        ritorna il numero di pagine utilizzate
 ***
 ***    Descrizione:
 ***       Stampa la documentazione relativa ai dati geometrici dei moduli.
 ***       La lista dei moduli viene recupera dalla struttura globale
 ***       ModelBlockStruct.
 ***/
int StampaDocModuli(fp_doc, max_righe)
FILE *fp_doc;
int max_righe;
{
   FILE *fp_mod;
   int riga_doc;
   char mod_prec[5], file_doc[256], buff[82], intest[20], intest2[2][81];
   short i, out, stampato=0;
   int pag = 0;
   char path_modulo[256], *path_lego;

   extern ModelBlockStruct *lista_blocchi;
   extern int num_blocchi;

   path_lego = getenv("LEGO");
   sprintf(path_modulo,"%s/sorgmodu/processo", path_lego);

   riempi(mod_prec, 4);
   riga_doc = 0;

/* Stampa il foglio d'intestazione dell'appendice 1 - significato simboli */
   strcpy(intest2[0], "APPENDICE 1");
   strcpy(intest2[1], "SIGNIFICATO DEI SIMBOLI");
   FoglioIntest(fp_doc, max_righe, MAX_COL_VER, intest2, 2, "..SIMBOLI..");
   pag++;

   for (i=0; i<num_blocchi; i++)
   /* Se il modulo non e' stato considerato ... */
      if ( strcmp(mod_prec, lista_blocchi[i].nome_mod))
      {
	  strcpy(mod_prec, lista_blocchi[i].nome_mod);
          strcpy(buff, lista_blocchi[i].nome_mod);
          tominus(buff); /* nome del modulo in caratteri minuscoli */
#ifdef VMS
	  sprintf(file_doc, "LG_MODULI_DOC:%s.doc", buff);
#else
       /* inserire il percorso del file di documentazione modulo */
	  sprintf(file_doc, "%s/%s.doc", path_modulo, buff);
printf("file documentazione: %s\n", file_doc);
#endif

       /* Se il file della documentazione non esiste oppure c'e' un errore */
       /* nell'apertura del file allora ignora e considera il modulo */
       /* successivo */
	  if ( access(file_doc, 0) )
	      continue;

	  if ( (fp_mod = fopen(file_doc,"r")) == NULL )
	      continue;

       /* Cerca la parte relativa ai dati geometrici e fisici */
	  if ( !CercaDocModuloDatiG(fp_mod) )
	  {
	    /* scrivi l'intestazione del modulo */
	       sprintf(intest, "MODULO %s", lista_blocchi[i].nome_mod);
	       if (riga_doc+3 >= max_righe-2)
	       {
		    FinePagina(fp_doc, max_righe-riga_doc, MAX_COL_VER,
				APPENDICE_1);
		    riga_doc = 0;
                    pag++;
	       }

	       StampaRiga(fp_doc, &riga_doc, MAX_COL_VER, intest);
	       StampaBlankLine(fp_doc, &riga_doc, 1);

	    /* Stampa il testo della documentazione */
	       while ( !LineaFileDoc(buff,80,fp_mod) )
	       {
		  if (cerca_str(buff,strlen(buff)," MODULO ") != -1 &&
		      cerca_str(buff,strlen(buff)," SCHEDA ") != -1)
		      break;

		  StampaRiga(fp_doc, &riga_doc, MAX_COL_VER, buff);
		  if (riga_doc >= max_righe-2)
		  {
		     FinePagina(fp_doc, max_righe-riga_doc, MAX_COL_VER,
					APPENDICE_1);
		     riga_doc = 0;
                     pag++;
		  }
	       }

	       if (riga_doc+2 >= max_righe-2)
	       {
		  FinePagina(fp_doc, max_righe-riga_doc, MAX_COL_VER,
			     APPENDICE_1);
		  riga_doc = 0;
                  pag++;
	       }
	       else
		  StampaBlankLine(fp_doc, &riga_doc, 2);

	    /* notifica che almeno una documentazione e' stata stampata */
	       stampato=1;
	  }

          fclose(fp_mod);
      }

   /* Se almeno una documentazione e' stata stampata allora termina la */
   /* pagina */
   if (stampato && riga_doc)
   {
      FinePagina(fp_doc, max_righe-riga_doc, MAX_COL_VER, APPENDICE_1);
      pag++;
   }
   return(pag);
}

/*** SkipLine(fp, n)
 ***    Parametri::
 ***       FILE *fp : file pointer
 ***       short n : numero di linee da saltare
 ***
 ***    Descrizione:
 ***       posiziona il puntatore 'fp' alle n linee successive.Ritorna EOF
 ***       se si arrivati alla fine del file 
 ***/
int SkipLine(FILE *fp, short n)
{
   char buff[81];
   short j, out;

   for (j=0 ;j<n ;j++)
      if ((out = LineaFileDoc(buff,80,fp)) == EOF)
        break;
   return(out);
}

/*** CercaDocModuloDatiG(fp)
 ***   Parametri:
 ***     FILE *fp : file pointer del file di documentazione del modulo
 ***
 ***   Descrizione:
 ***     cerca nella file di documentazione del modulo la sezione relativa ai
 ***     dati geometrici e fisici posizionando il puntatore alla prima linea
 ***     di informazioni da considerare. Ritorna 0 se e' stata trovata la 
 ***     sezione ,EOF altrimenti
 ***/
int CercaDocModuloDatiG(FILE *fp)
{
   short out;
   int i;
   char buff[82], c;
   long pos;

   while ( (out = LineaFileDoc(buff,80,fp)) != EOF )
      if (cerca_str(buff,strlen(buff)," DATI GEOMETRICI E FISICI ") != -1 &&
	  cerca_str(buff,strlen(buff)," SCHEDA C") != -1)
      {
	/* Salta l'intestazione iniziale */
	   if (SkipLine(fp, 5) == EOF)
	      return(EOF);

	   pos=ftell(fp);

	/* Cerca la prima riga che comincia per '['  */
	   while ( (out = LineaFileDoc(buff,80,fp)) != EOF )
	   {
	      for ( i=0 ; buff[i] && buff[i] == ' ' && buff[i] != '[' ; i++);
	      if ( buff[i] == '[')
	      {
		   fseek(fp,pos,0);
		   return(0);
	      }
	      else
		   pos=ftell(fp);
	   }
      }

   return(EOF);
}

/*** int LineaFileDoc(buffer, n, fp)
 ***    Parametri:
 ***       char *buffer : puntatore ad una stringa
 ***       short n : numero massimo di caratteri da scrivere in stringa
 ***       FILE *fp : file pointer
 ***
 ***    Descrizione:
 ***       funzione per leggere linea per linea i file di documentazione dei
 ***       moduli lego ( es.: COLN.DOC,TUBO.DOC ...).
 ***       Viene utilizzata questa funzione in quanto sono presenti dei
 ***       caratteri da filtrare opportunamente (VMS)
 ***       Ritorna : 0  : tutto ok
 ***                 1  : e' stato trovato il carattere di codifica ASCII 12
 ***                      (la linea comunque  viene copiata senza tale
 ***                       carattere)
 ***                 EOF: si e' raggiunti la fine del file
 ***/
int LineaFileDoc(buffer,n,fp)
char *buffer;
int  n;
FILE *fp;
{
   short car, out=0;
   int ind=0;

/* ciclo di lettura carattere per carattere */
   for (ind=0; (car=getc(fp)) != EOF && ind < n-1 && car != '\n' ; ind++)
      if ( car == 12 )
	 out=1;
      else
	 if ( car != '\r' )
	    *(buffer++)=car;
	 else
	    break;

/* Se la linea e' piu' lunga di n-1 allora posiziona il puntatore alla */
/* linea successiva */
   for (; car != EOF && ind >= n-1 && car != '\n' && car != '\r';car=getc(fp));

/* tratta <CR><NL> o <CR> come <NL> */
   if ( car == '\r' )
      if ((car = getc(fp)) != '\n')
	 ungetc(car,fp);

   *buffer    ='\0';
/*
   *(buffer+1)='\0';
*/
   if (car == EOF)
      return(EOF);
   else
      return(out);
}

/*** fine doc_dati.c ***/

/**********************************************************************
*
*       C Source:               doc_var.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 11:58:18 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: doc_var.c,2 %  (%full_filespec: 1,csrc,doc_var.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)doc_var.c	1.10\t3/31/95";
/*
        Fine sezione per SCCS
*/
/*** file doc_var.c

 creazione della documentazione relativa alle variabili

 Creato da Buffo Max il 25/07/1994

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

extern char page_prefix_var[];

/*** doc_var_blocco(pblock, fp_doc, fp_ind, riga_doc, pag_doc, riga_ind,
 ***                 pag_ind, max_righe_p, max_righe_l)
 ***    Parametri:
 ***       ModelBlockStruct *pblock: info del blocco.
 ***       FILE *fp_doc: file pointer documentazione
 ***       FILE *fp_ind: file pointer indice della documentazione
 ***       int riga_doc: (indirizzo) riga corrente documentazione
 ***       int pag_doc: (indirizzo) pagina corrente documentazione
 ***       int riga_ind: (indirizzo) riga corrente indice doc.
 ***       int pag_ind: (indirizzo) pagina corrente indice doc.
 ***       int max_righe_p: numero massimo righe per pagina (portrait)
 ***       int max_righe_l: numero massimo righe per pagina (landscape)
 ***
 ***    Descrizione:
 ***       stampa la documentazione di un blocco relativa alle variabili
 ***/
doc_var_blocco(pblock, fp_doc, fp_ind, riga_doc, pag_doc, riga_ind, pag_ind,
		max_righe_p, max_righe_l)
ModelBlockStruct *pblock;
FILE *fp_doc, *fp_ind;
int *riga_doc, *pag_doc,*riga_ind, *pag_ind, max_righe_p, max_righe_l;
{
   InfoBlock *dati_blocco;
   int i, j, num_var, righe_blocco;
   char *nota_blocco, *str, stringa[256], tmp[256];
   BlockVar *bvar;

/* leggi le variabili del blocco */
   leggi_var_f01(pblock->nome, &dati_blocco, &num_var, &nota_blocco);

/* controlla il numero di righe che occupa il blocco */
   righe_blocco = conta_righe_var(dati_blocco, num_var, nota_blocco);

/* Verifica se la documentazione del blocco puo' stare nella pagina */
/* corrente */
   if ( *riga_doc+righe_blocco >= max_righe_l-2 && *riga_doc > 1)
   {
	sprintf(tmp, "Pag. %s %d", page_prefix_var, (*pag_doc)++);
	FinePagina(fp_doc, max_righe_l - *riga_doc, MAX_COL_HOR, tmp);
	*riga_doc = 0;
   }

   ScriviIndice(fp_ind, pblock, riga_ind, pag_ind, max_righe_p,
		*pag_doc, page_prefix_var);

   StampaIntBlocco(fp_doc, pblock, riga_doc);

/* Stampa la nota relativa al blocco in generale  */
   str = nota_blocco;
   while( (str = StampaNota(fp_doc, str, MAX_COL_HOR,riga_doc)) != NULL)
   {
	if ( *riga_doc >= max_righe_l-2 )
	{
	   sprintf(tmp, "Pag. %s %d", page_prefix_var, (*pag_doc)++);
	   FinePagina(fp_doc, max_righe_l - *riga_doc, MAX_COL_HOR, tmp);
	   *riga_doc = 0;
	}
   }

/* stampa delle variabili del blocco */
   if ( *riga_doc + 5 >= max_righe_l-2 )
   {
      sprintf(tmp, "Pag. %s %d", page_prefix_var, (*pag_doc)++);
      FinePagina(fp_doc, max_righe_l - *riga_doc, MAX_COL_HOR, tmp);
      *riga_doc = 0;
   }

   StampaIntestVar(fp_doc, riga_doc);

   for (i=0 ; i<num_var ; i++)
   {
       if (dati_blocco[i].flag != VARIABILI)
	  continue;

       bvar = &dati_blocco[i].var;

    /* Componi la stringa di stampa */
       sprintf(stringa,
	       " %8.8s |%39.39s| %10.10s | %7.7s |%27.27s| %5.5s| %3.3s|%8.8s",
	       bvar->nome,bvar->descrizione,bvar->valore,
	       dim_unita_misura(bvar->nome[0]),bvar->sorgente,
	       bvar->release,bvar->pagina,bvar->data);

       if ((*riga_doc)+2 >= max_righe_l-2)
       {
	   StampaTrattoOrizzontale(fp_doc, 0, 126);
	   (*riga_doc)++;
	   fputs("( continua nella pagina successiva )\n",fp_doc);
	   (*riga_doc)++;
	   sprintf(tmp, "Pag. %s %d", page_prefix_var, (*pag_doc)++);
	   FinePagina(fp_doc, max_righe_l - *riga_doc, MAX_COL_HOR, tmp);
	   fputs("( continua dalla pagina precedente )\n",fp_doc);
	   (*riga_doc) = 1;
	   StampaIntestVar(fp_doc, riga_doc);
       }

       StampaStrInTabella(fp_doc, 0, 126, stringa);
       (*riga_doc)++;
   }

   StampaTrattoOrizzontale(fp_doc, 0, 126);
   (*riga_doc)++;

/* Stampa le variabili di connessione del blocco in esame */
   if ( *riga_doc + 9 >= max_righe_l-2)
   {
       sprintf(tmp, "Pag. %s %d", page_prefix_var, (*pag_doc)++);
       FinePagina(fp_doc, max_righe_l - *riga_doc, MAX_COL_HOR, tmp);
       *riga_doc = 0;
   }

   StampaIntestConnect(fp_doc, riga_doc);

   for (i=0 ; i<num_var ; i++)
   {
       if (dati_blocco[i].flag != VARIABILI)
	  continue;

       bvar = &dati_blocco[i].var;

       if (Empty(bvar->blocco_co))
	  continue;

    /* Componi la stringa di stampa */
       sprintf(stringa,
	       "      %8.8s       | %8.8s| %50.50s   ",
	       bvar->nome, bvar->blocco_co,
	       cerca_descr_blocco(bvar->blocco_co, tmp));

       if ((*riga_doc)+2 >= max_righe_l-2)
       {
	   StampaTrattoOrizzontale(fp_doc, 20, 110);
	   (*riga_doc)++;
	   fputs("( continua nella pagina successiva )\n",fp_doc);
	   (*riga_doc)++;
	   sprintf(tmp, "Pag. %s %d", page_prefix_var, (*pag_doc)++);
	   FinePagina(fp_doc, max_righe_l - *riga_doc, MAX_COL_HOR, tmp);
	   fputs("( continua dalla pagina precedente )\n",fp_doc);
	   (*riga_doc) = 1;
	   StampaIntestConnect(fp_doc, riga_doc);
       }

       StampaStrInTabella(fp_doc, 20, 110, stringa);
       (*riga_doc)++;
   }
   StampaTrattoOrizzontale(fp_doc, 20, 110);
   (*riga_doc)++;

/* Se non si e' arrivati alla fine del foglio allora stampa due linee */
/* vuote per separare la stampa della documentazione del blocco */
/* successivo */
   if ( *riga_doc + 2 < max_righe_l-2)
      StampaBlankLine(fp_doc, riga_doc, 2);

   free(dati_blocco);
   free(nota_blocco);
}

/*** conta_righe_var(dati_blocco, num_dati, nota_blocco)
 ***    Parametri:
 ***       InfoBlock *dati_blocco: variabili del blocco
 ***       int num_dati:: numero variabili.
 ***       char *nota_blocco: nota generale del blocco
 ***
 ***    Descrizione:
 ***       calcola il numero di righe che occupa la documentazione relativa
 ***       alle variabili di un blocco
 ***/
int conta_righe_var(dati_blocco, num_var, nota_blocco)
InfoBlock *dati_blocco;
char *nota_blocco;
int num_var;
{
   int i, num = 0;

   num = 4;   /* intestazione blocco */

   num += ContaRigheNota(nota_blocco)+1; /* note del blocco */

   num += 4; /* intestazione variabili blocco */

   for (i=0 ; i<num_var ; i++)
       if (dati_blocco[i].flag != VARIABILI)
	  continue;
       else
	  num++;
   num++;

   num = num + 7; /* intestazione connessioni variabili */

   for (i=0 ; i<num_var ; i++)
   {
       if (dati_blocco[i].flag != VARIABILI)
	  continue;

       if (!Empty(dati_blocco[i].var.blocco_co))
	  num++;
   }
   num++;

   return(num);
}

/*** void StampaIntestVar(fp, riga)
 ***    Parametri:
 ***       FILE *fp: file pointer documentazione variabili
 ***       int *riga: (indirizzo) riga corrente
 ***
 ***    Descrizione:
 ***       Stampa l'intestazione della tabella della documentazione
 ***       delle variabili.
 ***/
void StampaIntestVar(fp, riga)
FILE *fp;
int *riga;
{
   char stringa[133];

   riempi(stringa,126);
   strcpy(stringa," sigla   |              descrizione               ");
   strcat(stringa,"|   valore   |  unita` |         sorgente          ");
   strcat(stringa,"| rel. |pag.|   data");
   StampaTrattoOrizzontale(fp, 0, 126);
   StampaStrInTabella(fp, 0, 126, stringa);
   strcpy(stringa,"variabile|               variabile                ");
   strcat(stringa,"|  numerico  |di misura|         del dato          ");
   strcat(stringa,"|      |    |");
   StampaStrInTabella(fp, 0, 126, stringa);
   StampaTrattoOrizzontale(fp, 0, 126);
   (*riga) += 4;
}

/*** void StampaIntestConnect(fp, riga)
 ***       FILE *fp: file pointer documentazione variabili
 ***       int *riga: (indirizzo) riga corrente
 ***
 ***    Descrizione:
 ***       Stampa l'intestazione della tabella della connessioni delle
 ***       variabili
 ***/
void StampaIntestConnect(fp, riga)
FILE *fp;
int *riga;
{
   StampaTrattoOrizzontale(fp, 20, 110);
   StampaStrInTabella(fp, 20, 110,
   "                                CONNESSIONE   VARIABILI");
   StampaTrattoOrizzontale(fp, 20, 110);
   StampaStrInTabella(fp, 20, 110,
   "                     |            proviene dal blocco");
   StampaStrInTabella(fp, 20, 110, "    la  variabile    |");
   StampaStrInTabella(fp, 20, 110,
   "                     |   sigla                          descrizione");
   StampaTrattoOrizzontale(fp, 20, 110);
   (*riga) += 7;
}

/*** char *cerca_descr_blocco(nome_blocco)
 ***    Parametri:
 ***       char *nome_blocco: nome del blocco
 ***       char *buffer: (uscita) contiene la descrizione del blocco
 ***
 ***    Descrizione:
 ***       recupera la descrizione relativa ad un blocco.
 ***/
char *cerca_descr_blocco(nome_blocco, buffer)
char *nome_blocco, *buffer;
{
   int i;
   extern int num_blocchi;
   extern ModelBlockStruct *lista_blocchi;

   for (i=0 ; i<num_blocchi ; i++)
       if (strcmp(lista_blocchi[i].nome, nome_blocco) == 0)
	  break;

   if (i<num_blocchi)
       strcpy(buffer, lista_blocchi[i].descr);
   else
       strcpy(buffer, "");
   return(buffer);
}

/*** fine doc_var.c ***/

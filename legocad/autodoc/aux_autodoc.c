/**********************************************************************
*
*       C Source:               aux_autodoc.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 11:53:47 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: aux_autodoc.c,2 %  (%full_filespec: 1,csrc,aux_autodoc.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)aux_autodoc.c	1.12\t3/31/95";
/*
        Fine sezione per SCCS
*/
/*** file aux_autodoc.c
 ***
 *** Creato da Buffo & Calleri 06/12/1993
 ***
 *** File di supporto all'applicativo autodoc (documentazione automatica
 *** di un modello LEGOCAD).
 ***/

/****************************************************************/
/* FILE DI INCLUDE						*/
/****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

#include <X11/Xlib.h>
#include <X11/Intrinsic.h>

#include <Xm/Xm.h>

#include "UxXt.h"

#include <libutilx.h>

#include "autodoc.h"
#include "unita.h"

/****************************************************************/
/* VARIABILI GLOBALI ESTERNE					*/
/****************************************************************/
extern Arg args[];
extern Cardinal nargs;

extern XmString cstring;

extern char nome_modello[];

extern char file_tempdati[], file_tempvar[];

extern StructVarianti varianti_modello[];
extern byte num_varianti;

extern ModelBlockStruct *lista_blocchi;
extern int num_blocchi;

extern UnitaMisura unimis[];
extern int num_unita_misura;

extern void free_array_XmString( XmString*, int );

void copy_n_car(char*, char*, int);
int Empty(char*);
void riempi(char*, int);
void app_n_blank(char*, int);
int IsNumeric(char*);

/****************************************************************/
/* VARIABILI GLOBALI						*/
/****************************************************************/

/*** get_blocchi_modello(blocchi, n_blocchi)
 ***   Parametri:
 ***      ModelBlockStruct **blocchi : blocchi del modello. (uscita)
 ***      int *n_blocchi : numero dei blocchi. (uscita)
 ***
 ***   Descrizione:
 ***      recupera dai file f14.dat e f01.dat i blocchi del modello ed 
 ***      aggiorna la struttura blocchi.
 ***/
int get_blocchi_modello(ModelBlockStruct **blocchi, int *n_blocchi)
{
   FILE *fp_f14, *fp_f01;
   char buffer[151], temp[50];
   int ind, size;

   *n_blocchi = 0;

   printf("leggo i blocchi dai file f01.dat ed f14.dat.\n");

   fp_f14=fopen(FILE_F14,"r");
   fp_f01=fopen(FILE_F01,"r");

   if (fp_f14 == NULL || fp_f01 == NULL)
     return(1);

   while(fgets(buffer,150,fp_f14) != NULL && strncmp(buffer,"*LG*EOF",7))
      if ( !strncmp(buffer,"*LG*DATI DEL BLOCCO",19) )
      {
         ind = *n_blocchi;
         size = ++(*n_blocchi) * sizeof(ModelBlockStruct);
         *blocchi = (ModelBlockStruct *) realloc_mem(*blocchi, size);
         copy_n_car((*blocchi+ind)->nome, buffer+20,8);
         copy_n_car((*blocchi+ind)->nome_mod, buffer+37,4);
         copy_n_car((*blocchi+ind)->descr, buffer+44,50);
         (*blocchi+ind)->offs_f14 = ftell(fp_f14)-strlen(buffer);

      /* cerca il blocco nel file f01.dat */
         fseek(fp_f01, 0L, SEEK_SET);
         sprintf(temp, "%-8s  BL.-", (*blocchi+ind)->nome);
         (*blocchi+ind)->offs_f01 = -1;
         while(fgets(buffer,150,fp_f01) != NULL)
            if (strncmp(buffer, temp, strlen(temp)) == 0)
            {
               (*blocchi+ind)->offs_f01 = ftell(fp_f01)-strlen(buffer);
               break;
            }
         strcpy(buffer,"");
      }

   fclose(fp_f14);
   fclose(fp_f01);
   printf("fine lettura...\n");

   return(0);
}

/*** ordina_blocchi(blocchi, n_blocchi)
 ***   Parametri:
 ***      ModelBlockStruct *blocchi : blocchi del modello.
 ***      int n_blocchi : numero dei blocchi.
 ***
 ***   Descrizione:
 ***      Ordina per modulo la lista dei blocchi.
 ***/
void ordina_blocchi(blocchi, n_blocchi)
ModelBlockStruct *blocchi;
int n_blocchi;
{
   int i, j;
   ModelBlockStruct temp;

   printf("ordinamento blocchi per modulo\n");
   for (i=0 ; i<n_blocchi-1 ; i++)
      for (j=i+1 ; j<n_blocchi ; j++)
         if (strcmp(blocchi[i].nome_mod, blocchi[j].nome_mod) > 0 )
         {
             memcpy((char *)&temp,(char *)(blocchi+i),sizeof(ModelBlockStruct));
             memcpy((char *)(blocchi+i),(char *)(blocchi+j),
                                      sizeof(ModelBlockStruct));
             memcpy((char *)(blocchi+j),(char *)&temp,sizeof(ModelBlockStruct));
         }
   printf("fine ordinamento blocchi\n");
}

/*** update_blocks_list(blocchi, n_blocchi, wlist)
 ***   Parametri:
 ***      ModelBlockStruct *blocchi : blocchi del modello.
 ***      int n_blocchi : numero dei blocchi.
 ***      Widget wlist : widget della scroll-list dei blocchi
 ***
 ***   Descrizione:
 ***      Aggiorna la scroll-list relativa alla lista dei blocchi del modello.
 ***     Ritorna il numero dei blocchi del modello.
 ***/
int update_blocks_list(ModelBlockStruct *blocchi, int n_blocchi, Widget wlist)
{
   int i;
   char item[100];
   XmString *list_items = NULL;

   list_items = (XmString *) calloc_mem(n_blocchi, sizeof(XmString));

   for (i=0 ; i<n_blocchi ; i++ )
   {
       sprintf(item, "%.8s %.4s %s", blocchi[i].nome, blocchi[i].nome_mod,
				     blocchi[i].descr);
       list_items[i] = CREATE_CSTRING(item);
   }

   nargs = 0;
   XtSetArg(args[nargs], XmNitems, list_items); nargs++;
   XtSetArg(args[nargs], XmNitemCount, n_blocchi); nargs++;
   XtSetValues(wlist, args, nargs);

   free_array_XmString(list_items, n_blocchi);
   free(list_items);

   return(0);
}

/*** void cerca_descr_f01(fp_f01,nome_blocco,nome_modulo,descr_blocco);
 ***   Parametri:
 ***      FILE *fp_f01  : file pointer del F01.DAT
 ***      char *nome_blocco: nome del blocco
 ***      char *nome_modulo: nome del modulo
 ***      char *descr_blocco: descrizione del blocco (uscita)
 ***
 ***   Descrizione: 
 ***      cerca nel file f01 la descrizione del blocco 'nome_blocco' modulo
 ***      'nome_modulo'.
 ***/
void cerca_descr_f01(fp_f01,nome_blocco,nome_modulo,descr_blocco)
FILE *fp_f01;
char *nome_blocco, *nome_modulo, *descr_blocco;
{
   char trovato = 0,buff_f01[90],blocco[4],mod[4];
   short n_mod = 4;
   long salva_pos;

/* Se il nome del modulo non esiste allora devo recuperare il nome */
/* del modulo dalla sigla del componente facendo attenzione che il primo */
/* carattere potrebbe non corrispondere. Allora confronto se il primo  */
/* carattere e' alfabetico o no */
   if (Empty(nome_modulo))
   {
   /* Se il nome del blocco inizia con un carattere non alfabetico */
   /* allora prendi i tre caratteri successivi per il confronto */
      if (isalpha(nome_blocco[0]))
      {
         strncpy(mod,nome_blocco+1,3);
         n_mod = 3;
      }
      else
         strncpy(mod,nome_blocco,4);
   }
   else
      strncpy(mod,nome_modulo,4);

   strncpy(blocco,nome_blocco+4,4);
   salva_pos = ftell(fp_f01);
   fseek(fp_f01,0L,0);

   riempi(descr_blocco,51);

/* cerca la linea che comincia con **** e successivamente cerca il blocco */
/* da considerare finche' non si trova oppure non si trova di nuovo una */
/* riga di **** oppure si e' raggiunti la fine del file */
   while( fgets(buff_f01,90,fp_f01) != NULL)
   {
      if (!strcmp(buff_f01,"****\n"))
      {
         if (trovato)
           break;
         else
         {
            trovato = 1;
            continue;
         }
      }
      if (trovato)
         if (!strncmp(mod,buff_f01,n_mod) && !strncmp(blocco,buff_f01+18,4))
         {
            copy_n_car(descr_blocco,buff_f01+26,51);
            taglia(descr_blocco);
            break;
         }
   }
   fseek(fp_f01,salva_pos,0);
}

/*** int leggi_record_f14(nome_blocco, dati_blocco, num_dati, nota_blocco)
 ***   Parametri:
 ***     char *nome_blocco: nome del blocco.
 ***     InfoBlock **dati_blocco : dati geometrici del blocco (uscita)
 ***     int *num_dati : numero dati geometrici (uscita)
 ***     HeaderNote **ptr_note_blocco: note del blocco (uscita)
 ***     char **nota_blocco : nota generale del blocco (uscita)
 ***
 ***   Descrizione:
 ***     recupera i dati geometrici di un blocco.
 ***/
int leggi_record_f14(nome_blocco, dati_blocco, num_dati, ptr_note_blocco, 
                     nota_blocco)
char *nome_blocco;
InfoBlock **dati_blocco;
int *num_dati;
HeaderNote **ptr_note_blocco;
char **nota_blocco;
{
   FILE *fp_f14, *fp_tmp;
   char buffer[141],nome_modulo[5], *head_blocco = "*LG*DATI DEL BLOCCO ";
   char blocco = 0;
   int i, colonne;
   long offs_blocco;

   *num_dati = 0;
   *dati_blocco = NULL;

   if ( (fp_f14 = fopen(FILE_F14,"r+")) == NULL)
   {
      fprintf(stderr,"ERROR! Cannot open f14.dat.\n");
      return(1);
   }

/* file temporaneo delle informazioni aggiuntive */
   if ( (fp_tmp = fopen(file_tempdati,"r+")) == NULL)
   {
      fprintf(stderr,"ERROR! Cannot open information data file.\n");
      return(1);
   }

   offs_blocco = cerca_blocco_info(fp_tmp, nome_blocco);

   for ( i=0 ; i<num_blocchi ; i++ )
      if ( strcmp(nome_blocco, lista_blocchi[i].nome) == 0)
         break;

/***
   printf("nome: <%s> , %d , item: %d\n", nome_blocco, num_blocchi, i);
***/
   if ( i >= num_blocchi )
      return(1);

   fseek( fp_f14, lista_blocchi[i].offs_f14, SEEK_SET );
   fgets( buffer, 140, fp_f14 );
   while (fgets( buffer, 140, fp_f14 ) != NULL && 
	  strncmp(buffer, head_blocco, strlen(head_blocco)) &&
          strncmp(buffer, "*LG*EOF", 7))
   {
      buffer[strlen(buffer)-1]='\0';

      app_n_blank(buffer, 80); /* pulisci il buffer dal terminatore all'80 car. */
      esamina_rec_f14(nome_blocco, buffer, 0, dati_blocco, num_dati,
		    fp_tmp, offs_blocco);
   }

/* recupera le note del blocco */
   aggiorna_testi(fp_tmp, nome_blocco, offs_blocco, ptr_note_blocco);

   recupera_nota_blocco(fp_tmp, nota_blocco, offs_blocco, nome_blocco, NULL);

   fclose(fp_tmp);
   fclose(fp_f14);
}

/*** void esamina_rec_f14(record_f14, cellizzato, dati_blocco, num_dati,
 ***			  fp_info, offs_blocco)
 ***   Parametri:
 ***     char *nome_blocco : nome del blocco
 ***     char *record_f14    : record del file F14 del blocco considerato.
 ***     char cellizzato : Booleano.Indica se il modulo e' cellizzato.
 ***     InfoBlock **dati_blocco : dati geometrici e informazioni 
 ***                               relative (sorgente del dato, note, ecc.)
 ***                               (uscita).
 ***     FILE *fp_info : puntatore al file informazioni aggiuntive.
 ***     long offs_blocco : posizione del record relativo al blocco nel
 ***			    file delle informazioni aggiuntive.
 ***
 ***   Descrizione:
 ***     Prende una riga dal file F14 del blocco selezionato e recupera i nomi
 ***     dei parametri costanti in righe separate (le linee di commento
 ***     vengono considerate come unica riga).
 ***     I parametri costanti vengono ricercati nel file SORGDATI per
 ***     recuperare la sorgente del dato,la release,le note, la data 
 ***/
void esamina_rec_f14(nome_blocco, record_f14, cellizzato, dati_blocco,
                     num_dati, fp_info, offs_blocco)
char *nome_blocco, *record_f14;
char cellizzato;
InfoBlock **dati_blocco;
int *num_dati;
FILE *fp_info;
long offs_blocco;
{
   short int i, j, num;

   if ( *record_f14 != '*' )
   {
   /* recupero il numero di parametri costanti nella riga del file F14 */
   /* ( controllo il numero di * nelle posizioni 24,49,74 ) */
      num = (*(record_f14+24) == '*') + (*(record_f14+49) == '*') +
            (*(record_f14+74) == '*');

      *num_dati += num;
      *dati_blocco = (InfoBlock *) XtRealloc((char*)*dati_blocco, 
 					   *num_dati * sizeof(InfoBlock));

      for (i = 0; i < num ; i++)
      {
         j = *num_dati - num + i;

         (*dati_blocco+j)->dati.flag = DATI_GEOMETRICI;
         copy_n_car((*dati_blocco+j)->dati.nome,record_f14+(4+i*25),8);
         copy_n_car((*dati_blocco+j)->dati.valore,record_f14+(14+i*25),10);

      /* toglie i blank finali della stringa */
         taglia((*dati_blocco+j)->dati.nome);
         taglia((*dati_blocco+j)->dati.valore);

      /* cerca nel file info_datigeom.dat se esiste il blocco caricando */
      /* le informazioni aggiuntive */
         info_aggiuntive(fp_info, nome_blocco, offs_blocco, 
			 &(*dati_blocco+j)->dati, DATI_GEOMETRICI);
      }
   }
   else  /* commento */
   {
      (*num_dati)++;
      *dati_blocco = (InfoBlock *) realloc_mem(*dati_blocco, 
 					   *num_dati * sizeof(InfoBlock));
      (*dati_blocco+(*num_dati)-1)->dati.flag = COMMENTO;
      copy_n_car((*dati_blocco+(*num_dati)-1)->comment.commento,record_f14,80);
   }
}

/*** int leggi_all_var_f14(nome_blocco,dati_blocco,num_dati)
 ***   Parametri:
 ***      char *nome_blocco : nome del blocco
 ***      InfoBlock **dati_blocco : variabili del blocco e informazioni
 ***                                relative (sorgente del dato, ...) (uscita)
 ***      int *num_dati : numero variabili (uscita)
 ***      int *num_var_out : numero variabili di uscita (uscita)
 ***
 ***   Descrizione:
 ***      Legge dal file f14.dat tutte le variabili del modello e vengono
 ***      inserite nella struttura dati_blocco.
 ***      Questa funzione viene chiamata per avere i confronti dei risultati
 ***      di piu' file f14.dat.
 ***/
int leggi_all_var_f14(nome_blocco,dati_blocco,num_dati,num_var_out)
char *nome_blocco;
InfoBlock **dati_blocco;
int *num_dati;
int *num_var_out;
{
   FILE *fp_f14, *fp;
   char buffer[180];
   char *strcomp, strval[12];
   double fval;
   int i, j, ind, ind_f14;
   short valore_vuoto;
   BlockVarNmod *varN;
   long offs;

   *num_dati = 0;
   *dati_blocco = NULL;

   strcomp = "*LG*DATI FISICI E GEOMETRICI DEL SISTEMA";

   for ( ind_f14 = 0 ; ind_f14 < num_varianti ; ind_f14++ )
      if (varianti_modello[ind_f14].abilitato)
         break;

   fp_f14 = fopen(varianti_modello[ind_f14].percorso,"r");

   if (fp_f14 == NULL)
   {
      fprintf(stderr,"Error while opening file f14.dat");
      return(-1);
   }

/* lettura delle variabili */

/* Salta l'intestazione iniziale */
   fgets(buffer,180,fp_f14);
   fgets(buffer,180,fp_f14);
   fgets(buffer,180,fp_f14);

   while ( fgets(buffer,180,fp_f14) != NULL &&
           strncmp(buffer, strcomp, strlen(strcomp)))
   {
       if (!strncmp(buffer,"*LG*",4))
       {
          *num_var_out = ind;
          continue;
       }

       offs = ftell(fp_f14) - strlen(buffer);

       ind = (*num_dati)++;
       *dati_blocco = (InfoBlock *) realloc_mem(*dati_blocco, 
 	 			         *num_dati * sizeof(InfoBlock));

       (*dati_blocco+ind)->flag = VARIABILI_N_F14;
       varN = &(*dati_blocco+ind)->varN;

       copy_n_car(varN->nome, buffer+4, 8);
       copy_n_car(varN->nome_blk, buffer+29, 8);
       copy_n_car(varN->descrizione, buffer+45, 50);
       varN->noto = !strncmp(buffer+39 ,"NOTO", 4);
       copy_n_car(strval, buffer+14, 10);
       varN->fval_mks[0] = ascii_to_float(strval);
       fval = converti_val( *varN->nome, varN->fval_mks[0]);
       sprintf( varN->valori[0], "%10.4e", fval);

       for ( i=ind_f14+1, j=1 ; i < num_varianti ; i++ )
          if (varianti_modello[i].abilitato)
          {
             fp = fopen(varianti_modello[i].percorso,"r");

             if (fp == NULL)
                continue;

             fseek( fp, offs, SEEK_SET );
             if (fgets(buffer,180,fp) != NULL)
             {
                copy_n_car(strval, buffer+14, 10);
                varN->fval_mks[j] = ascii_to_float(strval);
                fval = converti_val( *varN->nome, varN->fval_mks[j]);
                sprintf( varN->valori[j++], "%10.4e", fval);
             }
             fclose(fp);
          }

       varN->num_valori = j;

       for ( ; j < num_varianti ; j++ )
           strcpy(varN->valori[j], "");
   }
   fclose(fp_f14);
}

/*** int leggi_var_f01(nome_blocco,dati_blocco,num_dati)
 ***   Parametri:
 ***      char *nome_blocco : nome del blocco
 ***      InfoBlock **dati_blocco : variabili del blocco e informazioni
 ***                                relative (sorgente del dato, ...) (uscita)
 ***      int *num_dati : numero variabili (uscita)
 ***      char **nota_blocco : nota generale del blocco (uscita)
 ***
 ***   Descrizione:
 ***     Legge dal file f01.dat le variabili del blocco selezionato che vengono
 ***     inserite nella struttura dati_blocco insieme alle informazioni 
 ***     aggiuntive relative (sorgente del dato, pagina, release razz, ecc..).
 ***/
int leggi_var_f01(nome_blocco,dati_blocco,num_dati,nota_blocco)
char *nome_blocco;
InfoBlock **dati_blocco;
int *num_dati;
char **nota_blocco;
{
   FILE *fp_f01, *fp_f14, *fp_var, *fp_tmp;
   char buffer[140], asterix = 0, trovato = 0, temp[81], nome_var[21];
   char variabile, blk[9], sorg[28];
   int i, j, noto, ind;
   short valore_vuoto;
   long offs_var_CO, offs_blocco;
   BlockVar *vars;

/***
   printf("leggi var f01\n");
***/
   *num_dati = 0;
   *dati_blocco = NULL;

/* offs_var_CO e' la variabile che contiene la posizione della prima */
/* variabile  di tipo --CO-- all'interno del file f01.dat */
   offs_var_CO = -1;

   fp_f01=fopen(FILE_F01,"r");
   fp_f14=fopen(FILE_F14,"r");

   if (fp_f01 == NULL || fp_f14 == NULL)
   {
      fprintf(stderr,"Error while opening file f01.dat or f14.dat");
      return(-1);
   }

/* file temporaneo delle informazioni aggiuntive */
   if ( (fp_tmp = fopen(file_tempvar,"r+")) == NULL)
   {
      fprintf(stderr,"ERROR! Cannot open information data file.\n");
      return(1);
   }

   offs_blocco = cerca_blocco_info(fp_tmp, nome_blocco);
   for ( i=0 ; i<num_blocchi ; i++ )
      if ( strcmp(nome_blocco, lista_blocchi[i].nome) == 0)
         break;

   if ( i >= num_blocchi )
      return(1);
   fseek(fp_f01, lista_blocchi[i].offs_f01, SEEK_SET);
   fgets(buffer,140,fp_f01);

/* lettura delle variabili */
   while ( fgets(buffer,140,fp_f01) != NULL && strncmp(buffer,"****",4))
   {
      ind = (*num_dati)++;
      *dati_blocco = (InfoBlock *) XtRealloc((char*)*dati_blocco, 
 	 			             *num_dati * sizeof(InfoBlock));
      vars = &(*dati_blocco+ind)->var;

      copy_n_car(nome_var,buffer,16);

      vars->flag = VARIABILI;
      copy_n_car(vars->nome,nome_var,8);

   /* Se la variabile e' connessa prendi il nome del blocco a cui e' */
   /* collegato */
      if ( buffer[17] == '#' && buffer[26] == '#' )
      {
         copy_n_car(blk,buffer+51,8);
         strcpy(vars->blocco_co, blk);
         copy_n_car(vars->old_name, buffer+18, 8);
      }
      else
      {
         strcpy(blk,nome_blocco);
         vars->blocco_co[0] = '\0';
         vars->old_name[0] = '\0';
      }

      copy_n_car(vars->tipovar,buffer+12,2);
      vars->noto = copia_valori(fp_f14,nome_var,vars->valore,blk,&vars->fval_mks);
      vars->fval_mks = ascii_to_float(vars->valore);
      copia_descr_var(fp_f01,&offs_var_CO,nome_var,buffer, vars->descrizione);

      info_aggiuntive(fp_tmp, nome_blocco, offs_blocco, vars, VARIABILI);
/***
      strncpy(temp+21,"Calcolato in regime staz.",25);
***/
   }

/* recupera la nota generale del blocco */
   recupera_nota_blocco(fp_tmp, nota_blocco, offs_blocco, nome_blocco, NULL);

   fclose(fp_f01);
   fclose(fp_f14);
   fclose(fp_tmp);
}

/*** int copia_valori( fp_f14,var,valore,blocco,val_mks )
 ***    Parametri:
 ***       fp_f14 : file pointer F14.DAT
 ***       var    : nome della variabile considerata nel blocco
 ***       valore : valore della variabile
 ***       blocco : nome del blocco a cui si riferisce la variabile
 ***       val_mks: (indirizzo) valore della variabile in MKS
 ***
 ***   Descrizione:
 ***      Ritorna 0 se la variabile e' stata trovata e non e' nota,
 ***      ritorna 1 se e' nota, -1 se la variabile non e' stata trovata.
 ***      legge dal file F14.DAt il valore di una particolare variabile 
 ***      all'interno del blocco selezionato.
 ***/
int copia_valori(fp_f14,var,valore,blocco,val_mks)
FILE  *fp_f14;
char  *var;
char  *valore;
char  *blocco;
double *val_mks;
{
   char temp[141],trovato = 0;
   double fval;

   fseek(fp_f14,0L,0);

   riempi(valore,10);

   *val_mks = 0l;
   while( fgets(temp,140,fp_f14) != NULL )
   {
      if (!trovato)
      {
         if ( !strncmp(temp,"*LG*CONDIZIONI INIZIALI",22) )
            trovato = 1;
      }
      else
      {
         if ( !strncmp(temp,"*LG*DATI FISICI E GEOMETRICI",28) )
            break;
         else
            if ( !strncmp(temp+4 ,var,8) && !strncmp(temp+29,blocco,8) )
            {
               copy_n_car(valore,temp+14,10);

            /* conversione nell'unita di misura selezionata */
               fval = ascii_to_float(valore);
               *val_mks = fval;
               fval = converti_val( *var, fval );
               sprintf( valore, "%10.4e", fval);
               
            /* Verifica se la variabile e' nota */
               if ( strncmp(temp+39,"NOTO",4))
                  return(0);
               else
                  return(1);
            }
      }
   }

   taglia(valore);
   return(-1);
}



/*** void copia_descr_var( fp_f01,offs_var_CO,var,buffer,descr )
 ***    Parametri:
 ***      fp_f01 : file pointer F01.DAT
 ***      offs_var_CO : offset in byte della posizione delle variabili di 
 ***                    tipo --CO-- nel file f01.dat
 ***      var    : variabile del blocco considerato
 ***      buffer : riga del file F01.DAT
 ***      descr  : stringa in cui scrivere la descrizione 
 ***
 ***   Descrizione:
 ***      In riferimento alla variabile considerata viene cercata la sua 
 ***      descrizione.
 ***/
void copia_descr_var(fp_f01,offs_var_CO,var,buffer,descr)
FILE *fp_f01;
long *offs_var_CO;
char *var,*buffer,*descr;
{
   long offset;
   char temp[90],nome_var[18];

   riempi(descr,40);

   if ( *(buffer+17) == '#' && *(buffer+26) == '#' )
   {
      copy_n_car(nome_var,buffer+18,8);
      strcat(nome_var,"  --CO--");

   /* la variabile e' di un altro blocco ,copia --CO-- */
      copy_n_car(var+10,"--CO--",6);

   /* Recupera la posizione corrente del puntatore al file F01 */
      offset = ftell(fp_f01);

      if ( *offs_var_CO == -1 )
         *offs_var_CO = cerca_var_co(fp_f01);

      fseek(fp_f01, *offs_var_CO, 0L);
      while ( fgets(temp,90,fp_f01) != NULL )
      {
          if ( !strncmp(temp,nome_var,8))
          {
             copy_n_car(descr, temp+17, 50);
             break;
          }
      }
      fseek(fp_f01,offset,0);
   }
   else
      copy_n_car(descr, buffer+17, 50);
   taglia(descr);
}

/*** cerca_var_co(fp)
 ***    Parametri:
 ***      FILE *fp : file pointer file F01.DAT
 ***
 ***    Descrizione:
 ***       Ricerca nel file F01.DAT l'inizio dell'elenco delle variabili di
 ***       tipo --CO-- e restituisce l'offset di riferimento per la funzioni
 ***       fseek().
 ***/
long cerca_var_co(fp)
FILE *fp;
{
   char temp[90];
   long pos;

   fseek(fp, 0L, 0);
   pos = 0;
   while (fgets(temp,90,fp) != NULL)
      if (!strncmp(temp+10,"--CO--",6))
         return(pos);
      else
         pos=ftell(fp);

   return(-1L);
}

/*** void info_aggiuntive(fp_info, nome_blocco, offs_blocco, info_blocco, flag)
 ***   Parametri:
 ***      FILE *fp_info : puntatore al file delle informazioni aggiuntive.
 ***      char *nome_blocco : nome del blocco.
 ***      long offs_blocco : posizione del record del blocco nel file delle
 ***			     delle informazioni aggiuntive.
 ***      void *punt : informazioni relative alla variabile o al dato geom.
 ***      byte flag : DATI_GEOMETRICI, VARIABILI
 ***
 ***   Descrizione:
 ***      Recupera le informazioni del blocco dal file e aggiorna la struttura
 ***      delle informazioni del blocco.
 ***/
void info_aggiuntive(fp_info, nome_blocco, offs_blocco, punt, flag)
FILE *fp_info;
char *nome_blocco;
long offs_blocco;
void *punt;
byte flag;
{
   char buffer[90], *buf2 = buffer;
   int size;
   Boolean trovato = False;
   char *nome, *sorg, *rel, *pag, *data, *note;
   BlockVar *var;
   BlockData *dato;

   if (fp_info == NULL)
      return;

   if (flag == DATI_GEOMETRICI)
   {
      dato = (BlockData *) punt;
      nome = dato->nome;
      sorg = dato->sorgente;
      rel = dato->release;
      pag = dato->pagina;
      data = dato->data;
      note = dato->note;
      strcpy(note,"");
   }
   else
   {
      var = (BlockVar *) punt;
      nome = var->nome;
      sorg = var->sorgente;
      rel = var->release;
      pag = var->pagina;
      data = var->data;
   }

/* inizializzazione */
   strcpy(sorg,"");
   strcpy(rel,"");
   strcpy(pag,"");
   strcpy(data,"");

   if (offs_blocco > -1)
   {
      fseek(fp_info, offs_blocco, SEEK_SET);

   /* Salta l'header del blocco selezionato */
      fgets(buffer,81,fp_info);
      while( fgets(buffer,81,fp_info) != NULL )
      {
         if ( !strncmp(buffer,"*LG*DATI DEL BLOCCO",19) ||
              !strncmp(buffer,"*LG*EOF",7) ||
              !strncmp(buffer,"*LG*NOTE ",9))
             break;

         if ( !strncmp(buffer,nome,strlen(nome)) )
         {
            trovato = True;
            break;
         }
      }
   }

   if (trovato)
   {
   /* Copia le informazioni aggiuntive */
      for( ;*buf2 != '|' && *buf2;buf2++ );
      copia_str(sorg,++buf2,'|',27);
      taglia(sorg);
      for( ;*buf2 != '|' && *buf2;buf2++ );
      copia_str(rel,++buf2,'|',5);
      taglia(rel);
      for( ;*buf2 != '|' && *buf2;buf2++ );
      copia_str(pag,++buf2,'|',3);
      taglia(pag);
      for( ;*buf2 != '|' && *buf2;buf2++ );
      copia_str(data,++buf2,'|',8);
      taglia(data);
      if (flag == DATI_GEOMETRICI)
      {
         for( ;*buf2 != '|' && *buf2;buf2++ );
         copia_str(note,++buf2,'\n',5);
         taglia(note);
      }
   }
}

/*** void recupera_nota_blocco(fp, offs, nome_block, nota)
 ***    Parametri:
 ***       FILE *fp : file informazioni aggiuntive
 ***       char **testo : testo della nota (uscita)
 ***       long offs : offset del record del blocco nel file delle info.
 ***       char *nome_block : nome del blocco
 ***
 ***    Descrizione:
 ***       Recupera il testo delle note generali del blocco.
 ***/
void recupera_nota_blocco(fp, testo, offs, nome_blocco)
FILE *fp;
char **testo;
long offs;
char *nome_blocco;
{
   char int_note[60], buffer[90];

/* cerca il testo della nota considerata */
   sprintf(int_note, "*LG*NOTE GENERALI DEL BLOCCO %s",nome_blocco);

   *testo = NULL;
   fseek(fp, offs, SEEK_SET);
   fgets(buffer,81,fp);
   while ( fgets(buffer,81,fp) != NULL &&
           strncmp(buffer,"*LG*DATI DEL BLOCCO ",20) &&
           strncmp(buffer,"*LG*EOF",7))
   {
       if ( !strncmp(buffer,int_note,strlen(int_note)) )
       {
           copia_testo_nota(fp, testo);
           break;
       }
   }
}

/*** copia_testo_nota(fp, testo)
 ***   Parametri:
 ***      FILE *fp : file pointer sorgente,
 ***      char **testo : testo della nota (uscita)
 ***
 ***   Descrizione:
 ***      Recupera dal file il testo della nota. Ritorna 1 se si e' arrivati
 ***      alla fine del file; 0 altrimenti.
 ***      N.B.: la funzione legge dalla posizione corrente del file pointer
 ***      ----  finche' non arriva alla fine del file oppure fino 
 ***            all'intestazione di una nota successiva oppure all'intestazione
 ***            di un blocco.
 ***/
int copia_testo_nota(fp, testo)
FILE *fp;
char **testo;
{
   char buffer[141], *out;
   int size = 1;

   *testo = NULL;

   while ((out = fgets(buffer,140,fp)) != NULL && strncmp(buffer,"*LG*",4))
   {
        size += strlen(buffer);
        *testo = XtRealloc(*testo, size*sizeof(char));
        if (size-1 == strlen(buffer))
           strcpy(*testo, buffer);
        else
           strcat(*testo, buffer);
   }

/* elimina i '\n' ed i ' ' finali */
   taglia(*testo);

/* Se non e' stato raggiunto la fine del file riporta il puntatore */
/* del file al record precedente */
   if ( out != NULL)
   {
      fseek( fp, -strlen(buffer), SEEK_CUR);
      return(0);
   }
   else
      return(1);
}

/*** long cerca_blocco_info(fp, nome_blocco)
 ***    Parametri:
 ***       FILE *fp : file pointer del file delle informazioni aggiuntive.
 ***       char *nome_blocco: nome del blocco.
 ***
 ***    Descrizione:
 ***       Cerca il blocco selezionato (nome_blocco) nel file delle
 ***       informazioni aggiuntive.
 ***       Se il blocco viene trovato allora la funzione restituisce l'offset
 ***       della posizione del record nel file, altrimenti restituisce -1.
 ***/
long cerca_blocco_info(fp, nome_blocco)
FILE *fp;
char *nome_blocco;
{
   char buffer[82],stringa[29];
   long offset = -1;

   sprintf(stringa,"*LG*DATI DEL BLOCCO %s",nome_blocco);

   if (fp == NULL)
       return (-1);

   fseek(fp, 0L, SEEK_SET);
   while ( fgets(buffer,81,fp) != NULL )
   {
       if ( !strncmp(buffer,"*LG*EOF",7) )
          break;
       if ( !strncmp(buffer,stringa,strlen(stringa)) )
          offset = ftell(fp) - strlen(buffer);
   }
   return(offset);
}

/*** int setta_nome_modello()
 ***
 ***   Descrizione:
 ***      Recupera dal file f01.dat il nome del modello e setta la variabile
 ***      globale nome_modello.
 ***/
int setta_nome_modello()
{
    FILE *fp;
    char buffer[140];
    int count = 0;

    if ((fp = fopen(FILE_F01,"r")) == NULL)
       return(-1);

    while ( fgets(buffer,140,fp) != NULL && count < 2)
      if (strncmp(buffer,"****",4) == 0)
         count++;

    if ( count == 2 )
       copy_n_car(nome_modello,buffer,8);
    return(0);
}

/*** double converti_val( tipo_var,valore )
 ***    Parametri:
 ***      char tipo_var  : tipo della variabile ( P - Pressione, ... ) 
 ***      float valore   : valore da convertire 
 ***
 ***    Descrizione:
 ***      Ritorna il valore convertito.
 ***/
double converti_val( tipo_var, valore )
char tipo_var;
double valore;
{
  int i;

  for ( i = 0; i < num_unita_misura ; i++ )
    if (unimis[i].tipo == tipo_var)
       return(valore*unimis[i].dim[unimis[i].ind_selez].moltip+
              unimis[i].dim[unimis[i].ind_selez].sommat);
  return(valore);
}

/*** char dim_unita_misura( tipo_var )
 ***    Parametri:
 ***      char tipo_var  : tipo della variabile ( P - Pressione, ... )
 ***
 ***    Descrizione:
 ***      Ritorna la dimensione dell'unita di misura (per intenderci .. Kg,
 ***                  m/s, ecc ...)
 ***/
char *dim_unita_misura( tipo_var )
char tipo_var;
{
  int i;

  for ( i = 0; i < num_unita_misura ; i++ )
    if (unimis[i].tipo == tipo_var)
       return(unimis[i].dim[unimis[i].ind_selez].codice);
  return("");
}

/*** int confronta_date(file1, file2)
 ***   Parametri:
 ***      char *file1, *file2: file da controllare.
 ***
 ***   Descrizione:
 ***      confronta le date di ultima modifica dei due file e ritorna:
 ***           +1 : se file1 e' piu' recente di file2
 ***         == 0 : se c'e' stato qualche errore (il file non esiste, ecc..)
 ***           -1 : se file2 e' piu' recente di file1.
 ***/
int confronta_date(file1, file2)
char *file1, *file2;
{
   struct stat finfo1, finfo2;

/* recupera le date di ultima modifica dei due file */
   if ( stat(file1, &finfo1) != 0 )
      return(0);

   if ( stat(file2, &finfo2) != 0)
      return(0);

   return ( (finfo2.st_mtime < finfo1.st_mtime) ? +1 : -1 );
}

/*** void *calloc_mem(ptr, size)
 ***    Parametri:
 ***       int num: numero oggetti da allocare
 ***       int size : memoria da allocare per ogni oggetto.
 ***
 ***    Descrizione:
 ***       chiama la funzione calloc e gestisce l'uscita dall'applicativo
 ***       nel caso in cui la funzione restituisce NULL
 ***/
void *calloc_mem(num, size)
int num, size;
{
    void *pout;

    if ((pout = calloc(num, size)) == NULL)
    {
       fprintf(stderr,"Can't allocate memory ... squitting!\n");
       exit(1);
    }
    return(pout);
}


/*** void *realloc_mem(ptr, size)
 ***    Parametri:
 ***       void *ptr : puntatore
 ***       int size : memoria da allocare.
 ***
 ***    Descrizione:
 ***       chiama la funzione realloc e gestisce l'uscita dall'applicativo
 ***       nel caso in cui la funzione restituisce NULL
 ***/
void *realloc_mem(ptr, size)
void *ptr;
int size;
{
    void *pout;

    if ((pout = realloc(ptr, size)) == NULL)
    {
       fprintf(stderr,"Can't allocate memory ... squitting!\n");
       exit(1);
    }
    return(pout);
}

/* funzione copia_str(str1,str2,endcar,max_car) *
 str1    : stringa destinazione                   (w)
 str2    : stringa sorgente                       (r)
 endcar  : carattere terminatore di str2          (r)
 max_car : numero massimo di caratteri da copiare (r)
 copia la stringa str2 in str1 finche' la stringa str2 non termina
 con '\0' oppure con il terminatore endcar */
void copia_str(char *str1, char *str2, char endcar, int max_car)
{
   for(; *str2 != endcar && *str2 && max_car-- ; *(str1++) = *(str2++) );
   if ( *(str1-1) )
      *str1 = '\0';
}

/* funzione taglia(str)
 str: stringa di caratteri
toglie da una stringa i blank finali o newline (\n) */
char *taglia(str)
char *str;
{
   char *start=str;
   str += strlen(str);

   while ( *str <= ' ' && str-- > start);

   *(str+1)='\0';
   return(start);
}

/*** double ascii_to_float(stringa)
 ***
 ***    char *stringa : stringa di caratteri da convertire a reale (double)
 ***
 ***    Descrizione:
 ***       converte una stringa in reale (double)
 ***/
double ascii_to_float(stringa)
char *stringa;
{
    double fval = 0.0;

    if (IsNumeric(stringa) && !Empty(stringa))
       sscanf(stringa, "%lf", &fval);
    return(fval);
}

/*** routine di conversione Ux -> Xt ***/
/*****
UxPutLabelString(swdg, stringa)
swidget swdg;
char *stringa;
{
   XmString cstring;

   cstring = CREATE_CSTRING(stringa);
   XtVaSetValues(swdg, XmNlabelString, cstring, NULL);
   XmStringFree(cstring);
}

UxDestroySwidget(swdg)
swidget swdg;
{
   XtDestroyWidget(swdg);
}

UxPutTitle(swdg, titolo)
swidget swdg;
char *titolo;
{
   XtVaSetValues(swdg, XmNtitle, titolo, NULL);
}

UxPutSensitive(swdg, str)
swidget swdg;
char *str;
{
   if (strcmp(str,"false") == 0)
      XtVaSetValues(swdg, XmNsensitive, False, NULL);
   else
      XtVaSetValues(swdg, XmNsensitive, True, NULL);
}
******/
/* fine aux_autodoc.c */

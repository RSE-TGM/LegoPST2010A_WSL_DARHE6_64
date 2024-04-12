
/*******************************************************************************
	Foraus.c
	(Generated from interface file Foraus.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/RowColumn.h>
#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/ArrowB.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo Foraus.i
   tipo 
   release 1.13
   data 5/16/95
   reserved @(#)Foraus.i	1.13
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif

#include <string.h>
#include <sys/stat.h>

#if defined LINUX
int esiste_file(path);
#include <unistd.h>
#else
#include <sys/access.h>
#endif

#include <linfo.h>
#include "legomain.h"

/********************************* in legomain.h
#define SAVE_TMP_FORAUS  90
#define SAVE_FORAUS      91
#define MIN_LEN_RIGA    100
#define PATTERN "C~FORAUS_"
#define FILE_TMP_NAME "foraus.tmp"
#define FILE_FORAUS   "foraus.for"
**************************************************/

extern char path_libut[];

extern swidget create_vis_msg();
swidget retswidget;

LTM *ltm;
int nmoduli;
#ifndef DESIGN_TIME
char *elenco[300];
char *codice[300];
#else
char *elenco[100];
char *codice[100];
#endif
int nmodaux;

/*******************************************************************************
	The following function is an event-handler for posting menus.
*******************************************************************************/

static void	_UxForausMenuPost( wgt, client_data, event, ctd )
	Widget		wgt;
	XtPointer	client_data;
	XEvent		*event;
	Boolean		*ctd;
{
	Widget	menu = (Widget) client_data;
	int 	which_button;

	XtVaGetValues( menu, XmNwhichButton, &which_button, NULL );

	if ( event->xbutton.button == which_button )
	{
		XmMenuPosition( menu, event );
		XtManageChild( menu );
	}
}

/*******************************************************************************
	The definition of the context structure:
	If you create multiple instances of your interface, the context
	structure ensures that your callbacks use the variables for the
	correct instance.

	For each swidget in the interface, each argument to the Interface
	function, and each variable in the Instance Specific section of the
	Declarations Editor, there is an entry in the context structure.
	and a #define.  The #define makes the variable name refer to the
	corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	Widget	UxForaus;
	Widget	UxpushButton3;
	Widget	UxpushButton5;
	Widget	UxpushButton6;
	Widget	Uxlabel8;
	Widget	UxarrowButton1;
	Widget	UxscrolledWindow2;
	Widget	UxscrolledList1;
	Widget	Uxmenu3;
	Widget	Uxview_fortran;
	Widget	Uxview_doc;
	Widget	Uxlabel9;
	Widget	UxscrolledWindow4;
	Widget	UxscrolledList2;
	Widget	Uxmenu4;
	Widget	Uxforaus_view_fortran;
	Widget	Uxforaus_remove_fortran;
	Widget	Uxforaus_edit_fortran;
	Widget	UxpushButton9;
	Widget	UxpushButton4;
	Widget	UxpushButton7;
	Widget	UxpushButton8;
	Boolean	Uxforaus_ok;
} _UxCForaus;

#define Foraus                  UxForausContext->UxForaus
#define pushButton3             UxForausContext->UxpushButton3
#define pushButton5             UxForausContext->UxpushButton5
#define pushButton6             UxForausContext->UxpushButton6
#define label8                  UxForausContext->Uxlabel8
#define arrowButton1            UxForausContext->UxarrowButton1
#define scrolledWindow2         UxForausContext->UxscrolledWindow2
#define scrolledList1           UxForausContext->UxscrolledList1
#define menu3                   UxForausContext->Uxmenu3
#define view_fortran            UxForausContext->Uxview_fortran
#define view_doc                UxForausContext->Uxview_doc
#define label9                  UxForausContext->Uxlabel9
#define scrolledWindow4         UxForausContext->UxscrolledWindow4
#define scrolledList2           UxForausContext->UxscrolledList2
#define menu4                   UxForausContext->Uxmenu4
#define foraus_view_fortran     UxForausContext->Uxforaus_view_fortran
#define foraus_remove_fortran   UxForausContext->Uxforaus_remove_fortran
#define foraus_edit_fortran     UxForausContext->Uxforaus_edit_fortran
#define pushButton9             UxForausContext->UxpushButton9
#define pushButton4             UxForausContext->UxpushButton4
#define pushButton7             UxForausContext->UxpushButton7
#define pushButton8             UxForausContext->UxpushButton8
#define foraus_ok               UxForausContext->Uxforaus_ok

static _UxCForaus	*UxForausContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_Foraus();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/*-------------------------------------------
 * 
 * routine di uso generale 
 *
 *--------------------------------------------*/

/*---------------------------------
 * distrugge la interfaccia Foraus
 * ricevendo in input uno widget
 * della interfaccia
 *---------------------------------*/

close_interface(swidget wid)
{
/* forse e' necessario recuperare il Context */
/* distruggo la interfacccia Foraus */
   UxDestroyInterface(wid);
}  

/*-----
 *   ritorna la lista delle posizioni degli item selezionati.
 *  L'utente ha la rsponsabilita' di liberare la memoria occupata
 *-----*/

get_selection_list(Widget lista,int **positions,int  *nitem)
{
  return( XmListGetSelectedPos(lista,positions,nitem) );
}

/*-----
 *
 *  seleziona tutti gli item della lista
 *
 *-----*/

select_all_item(Widget lista)
{
   int tot_item,i;

   UxPutSensitive(arrowButton1,"true");

   XtVaGetValues(lista,XmNitemCount,&tot_item,NULL);
   for(i=0;i<tot_item;i++)
      XmListSelectPos(lista,i,False);
}

/*--------
 *
 * deseleziona tutti gli item della lista
 *
 *--------*/

unselect_all_item(Widget lista)
{
   UxPutSensitive(arrowButton1,"false");
   XmListDeselectAllItems(lista);
}

/*---------
 * 
 * set di un item nella lista
 *
 *----------*/
set_item_list(Widget lista,char *cstr,int pos)
{
   XmString item;

   item = XmStringCreateSimple(cstr);
   XmListAddItem(lista,item,pos);
}

/*-------------
 *
 * carica un file in memoria
 *
 *-------------*/

int load_file_in_memory(FILE *fp,char **str)
{
   struct stat info_file;
   char *ptr = NULL,*ptr2 = NULL;
   

   if( *str != NULL)
      return(False);

/* recupero le dimensioni del file e alloco memoria */
   if ( !fstat(fileno(fp),&info_file))
   {
      ptr = (char *) XtMalloc ((unsigned) info_file.st_size+1);
   }
   else
      ptr = (char *) XtMalloc (sizeof(char) * 100000);

/* leggo tutto il file */
   ptr2 = ptr;
   while (fgets(ptr2,140,fp) != NULL)
      ptr2 = ptr2+strlen(ptr2);


   if( strlen(ptr) )
     *str = ptr;

   return(True);    
}

/*--------------------------------
 *
 * ricerca pattern in una stringa 
 *
 *---------------------------------*/ 

char *cerca_pattern(char *str,char *pattern)
{
   return( strstr(str,pattern) );
}

put_string_on_file(char *fname,char *str)
{
   FILE *fp;
   char appo[10]; 

   if( (fp = fopen(fname,"a")) == NULL)
   {
      fclose(fp);
      return(False);
   }

   fputs(str,fp);
/*   sprintf(appo,"\n%s\n","C"); */

   sprintf(appo,"\n");
   fputs(appo,fp);

   fclose(fp);
}

/*##################################################################*/

/*-----------------------------------------------
 *                                               
 *   gestione lista moduli                         
 *                                              
 *-----------------------------------------------*/

/*----------
 *
 * allocazione vettore strutture lista moduli 
 *
 *----------*/
 
int alloca_ltm(LTM **ltm,int nrecord)
{
    if(nrecord > 0 )
       (*ltm) = (LTM *)calloc(nrecord,sizeof(LTM));
       if(*ltm == NULL)
          return(NULL);
    return(TRUE);
}

/*----------
 * 
 * ritorna la riga letta dal file
 *
 *----------*/
 
read_riga(FILE *fp,char *riga)
{
   int retval;
   char nl;

/*
   l'utente deve dimensionare
   la riga almeno 100 char (per sicurezza)
*/

   retval = fscanf(fp,"%[^\n]",riga); /* legge fino al newline */
   fscanf(fp,"%c",&nl);               /* legge il new_line     */
   return(retval);
}

/*----------
 *
 * skip di una riga 
 *
 -----------*/

void skip_riga(FILE *fp)
{
    char riga[200];

    read_riga(fp,riga);               /* effettua la read di una riga
                                         il cui contenuto viene perduto*/
}

/*------------
 * 
 * ritorna il numero di mofuli presenti in crealtm.dat
 *
 *------------*/

int conta_moduli_ltm(FILE *fp)
{
   int nmod;
   char riga [200];

   rewind(fp);     /* riposiziono il file pointer all'inizio del file */
   skip_riga(fp);  /* skip prima riga */

   nmod=0;      /* ogni record conta un modulo */
   while( read_riga(fp,riga) != EOF)
      nmod++;

   return(nmod);
}

/*---------
 *
 * legge il file crealrm.dat
 * e riempie con i dati la struttura ltm
 *
 *----------*/
  
int leggi_ltm(LTM *sltm,FILE *fp)
{
   int ind;
   char riga[200],*appo;

   rewind(fp);     /* riposiziono il file pointer all'inizio del file */
   skip_riga(fp);  /* skip prima riga */

   ind =0;
   while( read_riga(fp,riga) != EOF)
   {
      strncpy(sltm[ind].nome_modulo,riga,4);
      appo = &riga[4];
      if( *appo == '*' )
         sltm[ind].rout_std = TRUE;
      else
         sltm[ind].rout_std = FALSE;

      appo++;
      strcpy(sltm[ind].descr_modulo,appo);
      ind++;
   }
}

/*-----------------------------
 *
 * legge il file crealtm.dat
 * e setta la lista
 *
 *------------------------------*/

LoadModulesList(Widget lista)
{
   extern char path_modello[];
   char fileltm[100],cstring[200];
   FILE *fpltm;
   int i;
      
   sprintf(fileltm,"%s/proc/%s",path_modello,FNAME_CREALTM);
   if( !esiste_file( fileltm) )
      return(False);

   if( (fpltm = fopen(fileltm,"r")) == NULL )
   {
      fclose(fpltm);
      return(False);
   }

   nmoduli = conta_moduli_ltm(fpltm);  

   if( alloca_ltm(&ltm,nmoduli) == NULL)
   {
      fclose(fpltm);
      return(False);
   }

   leggi_ltm(ltm,fpltm);

   for(i=0;i<nmoduli;i++)
   {
       if(ltm[i].rout_std)
          sprintf(cstring,"%s *  %s",ltm[i].nome_modulo, ltm[i].descr_modulo);
       else
          sprintf(cstring,"%s    %s",ltm[i].nome_modulo, ltm[i].descr_modulo);

        set_item_list(lista,cstring,i+1);
   }

   return(True);
}

get_foraux(char *modname,char *path,char **auxcode)
{
   char minname[10];
   char pathfile[200];
   char pattern_search[100];
   FILE *fp;
   char *ptrini=NULL,*ptrfin=NULL;
   char *strfile=NULL,*appo;
   int i;
   char *fcode;

   strcpy(minname,modname);
   for(i=0;i<strlen(minname);i++)
      minname[i] = tolower(minname[i]);

/* recupero il percorso del modulo in libut */
   sprintf(pathfile,"%s/%s.f",path,minname);

   if( !esiste_file(pathfile) )
      return(False);


   if( (fp = fopen(pathfile,"r")) == NULL)
   {
       fclose(fp);
       return(False);
   }


   load_file_in_memory(fp,&strfile);


   sprintf(pattern_search,"%s%s~",PATTERN,modname);

   ptrini = cerca_pattern(strfile,pattern_search);
   if( ptrini == NULL)
      return(False);

   ptrfin = cerca_pattern( (ptrini+strlen(pattern_search)),pattern_search); 
   if( ptrfin == NULL)
      return(False);   

   ptrfin += (strlen(pattern_search)+1);

   fcode = malloc( ((ptrfin - ptrini) +10) );
  
   memcpy(fcode,ptrini,(ptrfin - ptrini));

/* tappo la fine del fortran che e' chiuso da ~C */
   appo = strrchr(fcode,'~');
   appo += 2;
   *appo = 0;
      

   (*auxcode) = malloc( strlen(fcode) +2 );
   strcpy((*auxcode),fcode);
         
   return(True);
}

get_fortran_module(char *nome_mod,char **code)
{

   if( get_foraux(nome_mod,path_libut,code) == False)
      return(False);
   
   return(True);
}

/*##########################################################################*/

/*----------------------------------------------
 *
 *   gestione lista FORAUS
 *
 *----------------------------------------------*/


/*----------------------------------
 *
 * recupero il nome di un modulo
 *
 *--------------------------------*/

char *get_module_name(char *ptr)
{
   char *appo;
   char nomemod[10];
   char *ptr2=NULL;

/* alloco memoria per il nome (che poi non libero) */
   appo = malloc( sizeof(char)*6 );

/* cerco l'inizio del nome del modulo all'interno del PATTERN */
   ptr2 = strchr(ptr,'_');        
   ptr2++;


   strncpy(appo,ptr2,4);
   appo[4]=0;

   return(appo);
}


/*------------------------------------------------
 *
 * set del nome del modulo nell'elenco moduli
 *
 *------------------------------------------------*/
set_elenco_modulo(char *modname,int pos)
{
   
   elenco[pos] = malloc( strlen(modname)+2 );
   strcpy(elenco[pos] , modname);
}

/*------------------------------------------------
 *
 * set del codice del modulo 
 *
 *------------------------------------------------*/
salva_elenco_codice(char *code,int pos)
{
   codice[pos] = malloc( strlen(code)+2 );
   strcpy(codice[pos] , code);
}


libera_elenco_codice(int pos)
{
   if( codice[pos] )
      free(codice[pos]);
}

libera_elenco_moduli(int pos)
{
   if( elenco[pos] )
      free( elenco[pos] );
}
/*----------------------------------------------
 *  rimuovo un modulo dal fortran ausiliario
 *  input:   nome del modulo
 *           posinlist  posizione nella lista
 ----------------------------------------------*/

rimuovi_modulo(int posinlist)
{
   int iarray,i;

   iarray = posinlist -1;


/* libero il codice del modulo */
   libera_elenco_codice(iarray);
   libera_elenco_moduli(iarray);

/* compatto l'elenco */

   printf("compatta elenco \n");

   for(i = iarray;i<nmodaux-1;i++)
   {
      codice[i] = codice[i+1];
      elenco[i] = elenco[i+1];
   }


   nmodaux--;
}


/*----------------------------
 *
 * crea l'elenco dei moduli presenti in foraus.for
 *
 *------------------------------*/

crea_elenco(char *str)
{
   char *ptr1=NULL,*ptr2=NULL,appo[100];
   char *ptrini=NULL,*ptrfin=NULL,*ptrapp=NULL;
   char name[100],pattern_search[50];
   char *cod;


   nmodaux = 0;

   strcpy(pattern_search,PATTERN);
   ptr1 = str;
   while( True ) 
   {

/* cerco il pattern d'inizio codice modulo */
      ptrini = cerca_pattern(ptr1,pattern_search);

/* finisco il ciclo quando non ne trovo piu' */ 
      if( ptrini == NULL)
         break;

/* recupero il nome del modulo e lo aggiungo nella lista */
      strcpy(name, get_module_name(ptrini));  
      set_elenco_modulo(name,nmodaux);


/* cerco (e mi aspetto) la fine del codice del modulo */
      ptrfin = cerca_pattern(ptrini+strlen(pattern_search),PATTERN);  
      if( ptrfin == NULL)
         break;

/*recupero il codice in foraus relativo al modulo */
      cod = malloc( (ptrfin - ptrini) + strlen(pattern_search) + 10 );
      memcpy( cod, ptrini, ( (ptrfin - ptrini ) + strlen(pattern_search) + 8 ) );
      ptr2 = strrchr(cod,'~');
      ptr2 += 2;
      *ptr2=0;   
      salva_elenco_codice( cod, nmodaux );
      free(cod);


/* reinizializzo e sposto un po' piu avanti il 
   pointer altrimenti ritrova questa stringa */ 
      ptr1 = ptrfin + strlen(pattern_search);
      nmodaux++;
   }
   return(True);
}

LoadForausStdList()
{
   extern char path_modello[];
   FILE *fpfor;
   char filefor[100];
   char *stringa; 
   int i;
   
   sprintf(filefor,"%s/%s",path_modello,FILE_FORAUS);
   if( !esiste_file(filefor) )
      return(False);
 

   if( (fpfor = fopen(filefor,"r")) == NULL)
   {
      fclose(fpfor);
      return(False);
   } 


   stringa = NULL;
   if( load_file_in_memory(fpfor,&stringa) == False)
   {
      fclose(fpfor);
      return(False);
   }

   if( stringa)
   {
      crea_elenco(stringa);

      for(i=0;i<nmodaux;i++)   
      {   
         set_item_list(scrolledList2,elenco[i],i+1);      
      }

      free(stringa);
   }
 
   return(True);
}

int save_foraus(int cod_op)
{
//   extern swidget create_vis_msg();
   extern char path_modello[];
   int i;
   char filename[200];
   char msg[200];

   switch( cod_op)
   {
      case SAVE_TMP_FORAUS:
         sprintf(filename,"%s/%s",path_modello,FILE_TMP_NAME);
      break;
      case SAVE_FORAUS:
         sprintf(filename,"%s/%s",path_modello,FILE_FORAUS);
      break;
   }

/* testo la esistenza del file temporaneo */
   if( esiste_file )
      if( svuota_file(filename) != True)
      {
         sprintf(msg,"Error opening file %s",filename);
         retswidget=create_vis_msg(msg);
         foraus_ok = False;
         return(False);
      }          
      
   for(i=0;i<nmodaux;i++)
      put_string_on_file(filename,codice[i]);

   return(True);
}

int salva_su_conferma()
{
//    extern swidget create_vis_msg();

   if( foraus_ok != True)
   {
      retswidget=create_vis_msg("Auxiliary fortran problem.\nError on Compilation test or not compiled.");  
      return(False);
   } 
   else
   {
      /* richiama interfaccia di conferma sovrascrittura 
         per il file foraus.for
      */
      create_question_operation(Foraus,SAVE_FORAUS);   
    }     
}

int aggiungi_in_foraus()
{
//   extern swidget create_vis_msg();
   int i,j;
   int *pos,nitem;
   Boolean found = False,nofor = False;
   char *appo=NULL;
   char mesg[200];

   strcpy(mesg,"");
   if( get_selection_list(scrolledList1,&pos,&nitem) == 0 )
   {
      retswidget=create_vis_msg("Nothing selected!");
      return;
   }

   for(i=0;i<nitem;i++)
   {
      found = False;
      for(j=0;j<nmodaux;j++)
      {
         if( strcmp(ltm[ pos[i] -1 ].nome_modulo,elenco[j]) == NULL)
         {
             found = True;
             break;
         }
         else
         {
            found = False;
         }
       }       

       if( !found )
       {
         if( get_fortran_module( ltm[ pos[i]-1 ].nome_modulo,&appo) != False)
         {
            set_elenco_modulo(ltm[ pos[i] -1 ].nome_modulo,nmodaux);
            set_item_list(scrolledList2,elenco[nmodaux],0);
            salva_elenco_codice(appo,nmodaux);
            nmodaux++;
         }
         else
         {
            nofor = True;
            sprintf((mesg+strlen(mesg)),"%s\n",ltm[ pos[i]-1 ].nome_modulo);
         }  
       }
   }

   if( nofor )
   {
      sprintf((mesg+strlen(mesg)),"%s","no fortran for module");
      retswidget=create_vis_msg(mesg);
   }

   if( appo != NULL)
      free(appo); 

   return(True);
}

svuota_file(char *filename)
{
   FILE *fp;
  
   if( (fp = fopen(filename,"w")) == NULL)
   {
      fclose(fp);
      return(False);
   }
   else
   {
      fclose(fp);
      return(True);
   }    
}

/*------------
 *
 * testa_foraus()
 *
 * effettua una compilazione del foraus
 * che dovra' essere salvato. Se la compilazione
 * va' a buon fine setta la variabile foraus_ok
 *
 *--------------*/

testa_foraus()
{
//   extern swidget create_vis_msg();
   extern char path_modello[];
   int i;
   char filename[200];

/* salvo su file temporaneo foraus.tmp */
   save_foraus(SAVE_TMP_FORAUS);

  
/* lancia il make di compilazione del file foraus.tmp 
   l'output deve essere rediretto sulla man window di legocad
   e se la compilazione e' ok setta foraus_ok a True
*/  

   return(esegui_comando(TEST_FORAUS));
} 



rimuovi_moduli_foraus(Widget wcaller)
{
#ifndef DESIGN_TIME
   _UxCForaus              *UxSaveCtx, *UxContext;
#endif

   int i,*pos,nit;

#ifndef DESIGN_TIME
   UxSaveCtx = UxForausContext;
   UxForausContext = UxContext =
              (_UxCForaus *) UxGetContext( wcaller);
#endif



  if( get_selection_list(scrolledList2,&pos,&nit) == 0)
  {
     retswidget=create_vis_msg("Nothing selected");
     return;
  }
  else
  {
    for(i=0;i<nit;i++)
    {
       if(i)
       {
          XmListDeletePos(scrolledList2,pos[i]-i);
          rimuovi_modulo(pos[i]-i);
       }
       else
       {
          XmListDeletePos(scrolledList2,pos[i]);
          rimuovi_modulo(pos[i]);
       }
    }
  }

#ifndef DESIGN_TIME
  UxForausContext = UxSaveCtx;
#endif
}


delete_foraus(Widget wcaller)
{
#ifndef DESIGN_TIME
   _UxCForaus              *UxSaveCtx, *UxContext;
#endif

//   extern swidget create_vis_msg();
   char comando[256];
   int i;

#ifndef DESIGN_TIME
   UxSaveCtx = UxForausContext;
   UxForausContext = UxContext =
              (_UxCForaus *) UxGetContext( wcaller);
#endif

/* libero il vettore */ 
   for(i = 0;i<nmodaux;i++)
   {
      free(codice[i]);
      free(elenco[i]);
   }

   nmodaux=0;

/* e cancello il file foraus */
   if( !esiste_file(FILE_FORAUS) )
      retswidget=create_vis_msg("Auxiliary fortran file foraus.for not exists");
   else
   {
      sprintf(comando,"rm %s",FILE_FORAUS);
      system(comando);
   }
#ifndef DESIGN_TIME
  UxForausContext = UxSaveCtx;
#endif
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_pushButton3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
	salva_su_conferma();
	}
	UxForausContext = UxSaveCtx;
}

static void	activateCB_pushButton5( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
	select_all_item(scrolledList1);
	}
	UxForausContext = UxSaveCtx;
}

static void	activateCB_pushButton6( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
	unselect_all_item(scrolledList1);
	}
	UxForausContext = UxSaveCtx;
}

static void	activateCB_arrowButton1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
	aggiungi_in_foraus();
	}
	UxForausContext = UxSaveCtx;
}

static void	multipleSelectionCB_scrolledList1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
	{
	int *positions,item;
	
	if( get_selection_list( scrolledList1,&positions,&item) == False)
	   UxPutSensitive(arrowButton1,"false");
	else
	   UxPutSensitive(arrowButton1,"true");
	}
	}
	UxForausContext = UxSaveCtx;
}

static void	mapCB_menu3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
	int *posiz=NULL,nsel=0;
	
	printf("chaimata la Map callback del popup menu\nrelativo alla module list\n"); 
	
	if( get_selection_list(scrolledList1,&posiz,&nsel) == True)
	{
	  printf("%d item selected in module list \n",nsel);
	   UxPutSensitive( view_fortran,"true");
	   UxPutSensitive( view_doc,"true");
	}
	else
	{
	   UxPutSensitive( view_fortran,"false");
	   UxPutSensitive( view_doc,"false");
	}
	if(posiz != NULL)
	   free(posiz);
	}
	UxForausContext = UxSaveCtx;
}

static void	activateCB_view_fortran( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
//	  extern swidget create_vis_msg();
	  extern swidget create_editText();
	  swidget swid;
	  int *pos,nit;
	  char titolo[200];
	
	  if( get_selection_list(scrolledList1,&pos,&nit) == 0)
	  {
	     retswidget=create_vis_msg("Nothing selected");
	     return;
	  }
	  if( nit > 1)
	  {
	     retswidget=create_vis_msg("Too much items selected");
	     return;
	  }
	 
	
#ifndef DESIGN_TIME
	  if( get_fortran_module( ltm[ pos[0]-1 ].nome_modulo,&(ltm[ pos[0]-1 ]).auxftn_modulo ) == False)
	  {
	    retswidget=create_vis_msg("No auxiliary fortran for selected module.");
	    return;       
	  }
#endif
	
	  if( strlen( ltm[ pos[0]-1 ].auxftn_modulo ) == 0 )
	  {
	    retswidget=create_vis_msg("No auxiliary fortran for selected module.");
	    return;       
	  }
	
	  create_editText(foraus_edit_fortran,VIEW_FORAUS,(ltm[ pos[0]-1 ]).auxftn_modulo,&(ltm[pos[0]-1]).auxftn_modulo,NULL );
	
	}
	UxForausContext = UxSaveCtx;
}

static void	activateCB_view_doc( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
	
//	  extern swidget create_vis_msg();
	  int *pos,nit;
	 
	  retswidget=create_vis_msg("Use Librarian (Documentation View) for see module documentation");
	  return;
	
	  if( get_selection_list(scrolledList1,pos,&nit) == 0)
	  {
	     retswidget=create_vis_msg("Nothing selected");
	     return;
	  }
	  if( nit > 1)
	  {
	     retswidget=create_vis_msg("Too much items selected");
	     return;
	  }
	    
	
	}
	UxForausContext = UxSaveCtx;
}

static void	mapCB_menu4( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
	int *posiz=NULL,nsel=0;
	
	if( get_selection_list(scrolledList2,&posiz,&nsel) == True)
	{
	   UxPutSensitive( foraus_view_fortran,"true");
	   UxPutSensitive( foraus_remove_fortran,"true");
	}
	else
	{
	   UxPutSensitive( foraus_view_fortran,"false");
	   UxPutSensitive( foraus_remove_fortran,"false");
	}
	if(posiz != NULL)
	   free(posiz);
	}
	UxForausContext = UxSaveCtx;
}

static void	activateCB_foraus_view_fortran( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
	
//	  extern swidget create_vis_msg();
	  extern swidget create_editText();
	  int *pos,nit;
	
	  if( get_selection_list(scrolledList2,&pos,&nit) == 0)
	  {
	     create_vis_msg("Nothing selected");
	     return;
	  }
	  if( nit > 1)
	  {
	     retswidget=create_vis_msg("Too much items selected");
	     return;
	  }
	
	  create_editText(foraus_edit_fortran,VIEW_FORAUS,codice[ pos[0]-1 ],&(codice[pos[0]-1]),NULL );
	}
	UxForausContext = UxSaveCtx;
}

static void	activateCB_foraus_remove_fortran( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
//	   extern swidget create_vis_msg();
	   int *pos,nit;
	
	  if( get_selection_list(scrolledList2,&pos,&nit) == 0)
	  {
	     retswidget=create_vis_msg("Nothing selected");
	     return;
	  }
	
	   create_question_operation(Foraus,REMOVE_FORAUS);
	}
	UxForausContext = UxSaveCtx;
}

static void	activateCB_foraus_edit_fortran( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
	
//	  extern swidget create_vis_msg();
	  extern swidget create_editText();
	  int *pos,nit;
	
	  if( get_selection_list(scrolledList2,&pos,&nit) == 0)
	  {
	     retswidget=create_vis_msg("Nothing selected");
	     return;
	  }
	  if( nit > 1)
	  {
	     retswidget=create_vis_msg("Too much items selected");
	     return;
	  }
	
	  create_editText(foraus_edit_fortran,EDIT_FORAUS,codice[ pos[0]-1 ],&(codice[pos[0]-1]),NULL );
	}
	UxForausContext = UxSaveCtx;
}

static void	activateCB_pushButton9( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
//	extern swidget create_vis_msg();
	
	if( testa_foraus() == 0 )
	  foraus_ok = True;
	else
	{
	   retswidget=create_vis_msg("Auxiliary fortran compilation error");
	   foraus_ok = False;
	}
	}
	UxForausContext = UxSaveCtx;
}

static void	activateCB_pushButton4( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(XtParent(UxWidget));
	}
	UxForausContext = UxSaveCtx;
}

static void	activateCB_pushButton7( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
	select_all_item(scrolledList2);
	}
	UxForausContext = UxSaveCtx;
}

static void	activateCB_pushButton8( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCForaus              *UxSaveCtx, *UxContext;

	UxSaveCtx = UxForausContext;
	UxForausContext = UxContext =
			(_UxCForaus *) UxGetContext( UxWidget );
	{
	unselect_all_item(scrolledList2);
	}
	UxForausContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_Foraus()
{
	Widget	Foraus_shell;
	Widget	menu3_shell;
	Widget	menu4_shell;

	Foraus_shell = XtVaCreatePopupShell( "Foraus_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 210,
			XmNy, 169,
			XmNwidth, 740,
			XmNheight, 480,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "Foraus",
			XmNiconName, "Foraus",
			NULL );

	Foraus = XtVaCreateManagedWidget( "Foraus",
			xmFormWidgetClass, Foraus_shell,
			RES_CONVERT( XmNdialogTitle, "Edit Auxiliary Fortran" ),
			XmNheight, 480,
			XmNwidth, 740,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( Foraus, (char *) UxForausContext );

	pushButton3 = XtVaCreateManagedWidget( "pushButton3",
			xmPushButtonWidgetClass, Foraus,
			XmNrightOffset, 620,
			XmNrightAttachment, XmATTACH_NONE,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomOffset, 15,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Ok" ),
			XmNheight, 30,
			XmNwidth, 140,
			XmNy, 430,
			XmNx, 20,
			NULL );

	UxPutContext( pushButton3, (char *) UxForausContext );

	pushButton5 = XtVaCreateManagedWidget( "pushButton5",
			xmPushButtonWidgetClass, Foraus,
			XmNbottomWidget, pushButton3,
			XmNbottomOffset, 30,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Select All" ),
			XmNheight, 40,
			XmNwidth, 90,
			XmNy, 340,
			XmNx, 20,
			NULL );

	UxPutContext( pushButton5, (char *) UxForausContext );

	pushButton6 = XtVaCreateManagedWidget( "pushButton6",
			xmPushButtonWidgetClass, Foraus,
			XmNleftWidget, pushButton5,
			XmNleftOffset, 5,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNbottomWidget, pushButton3,
			XmNbottomOffset, 30,
			XmNbottomAttachment, XmATTACH_WIDGET,
			RES_CONVERT( XmNlabelString, "Unselect All" ),
			XmNheight, 40,
			XmNwidth, 90,
			XmNy, 340,
			XmNx, 110,
			NULL );

	UxPutContext( pushButton6, (char *) UxForausContext );

	label8 = XtVaCreateManagedWidget( "label8",
			xmLabelWidgetClass, Foraus,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_NONE,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "module list" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 120,
			XmNy, 10,
			XmNx, 20,
			NULL );

	UxPutContext( label8, (char *) UxForausContext );

	arrowButton1 = XtVaCreateManagedWidget( "arrowButton1",
			xmArrowButtonWidgetClass, Foraus,
			XmNleftOffset, 30,
			XmNleftAttachment, XmATTACH_NONE,
			XmNrightOffset, 300,
			XmNrightAttachment, XmATTACH_FORM,
			XmNarrowDirection, XmARROW_RIGHT,
			XmNheight, 50,
			XmNwidth, 50,
			XmNy, 160,
			XmNx, 390,
			NULL );

	UxPutContext( arrowButton1, (char *) UxForausContext );

	scrolledWindow2 = XtVaCreateManagedWidget( "scrolledWindow2",
			xmScrolledWindowWidgetClass, Foraus,
			XmNrightWidget, arrowButton1,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_WIDGET,
			XmNtopWidget, label8,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNbottomWidget, pushButton5,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 40,
			XmNx, 20,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( scrolledWindow2, (char *) UxForausContext );

	scrolledList1 = XtVaCreateManagedWidget( "scrolledList1",
			xmListWidgetClass, scrolledWindow2,
			XmNselectionPolicy, XmMULTIPLE_SELECT,
			XmNitemCount, 0,
			XmNheight, 315,
			XmNwidth, 260,
			NULL );

	UxPutContext( scrolledList1, (char *) UxForausContext );

	menu3_shell = XtVaCreatePopupShell ("menu3_shell",
			xmMenuShellWidgetClass, scrolledList1,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu3 = XtVaCreateWidget( "menu3",
			xmRowColumnWidgetClass, menu3_shell,
			XmNmenuAccelerator, "<KeyUp>F4",
			XmNrowColumnType, XmMENU_POPUP,
			NULL );

	UxPutContext( menu3, (char *) UxForausContext );

	view_fortran = XtVaCreateManagedWidget( "view_fortran",
			xmPushButtonWidgetClass, menu3,
			RES_CONVERT( XmNlabelString, "View fortran" ),
			NULL );

	UxPutContext( view_fortran, (char *) UxForausContext );

	view_doc = XtVaCreateManagedWidget( "view_doc",
			xmPushButtonWidgetClass, menu3,
			RES_CONVERT( XmNlabelString, "View module doc" ),
			NULL );

	UxPutContext( view_doc, (char *) UxForausContext );

	label9 = XtVaCreateManagedWidget( "label9",
			xmLabelWidgetClass, Foraus,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNleftWidget, arrowButton1,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			RES_CONVERT( XmNlabelString, "std routine in auxiliary fortran" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			XmNheight, 20,
			XmNwidth, 250,
			XmNy, 10,
			XmNx, 460,
			NULL );

	UxPutContext( label9, (char *) UxForausContext );

	scrolledWindow4 = XtVaCreateManagedWidget( "scrolledWindow4",
			xmScrolledWindowWidgetClass, Foraus,
			XmNleftWidget, arrowButton1,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNwidth, 250,
			XmNtopWidget, label8,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 10,
			XmNbottomWidget, pushButton5,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 10,
			XmNrightOffset, 20,
			XmNrightAttachment, XmATTACH_FORM,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 50,
			XmNx, 360,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( scrolledWindow4, (char *) UxForausContext );

	scrolledList2 = XtVaCreateManagedWidget( "scrolledList2",
			xmListWidgetClass, scrolledWindow4,
			XmNselectionPolicy, XmMULTIPLE_SELECT,
			XmNitemCount, 0,
			XmNheight, 290,
			XmNwidth, 250,
			NULL );

	UxPutContext( scrolledList2, (char *) UxForausContext );

	menu4_shell = XtVaCreatePopupShell ("menu4_shell",
			xmMenuShellWidgetClass, scrolledList2,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	menu4 = XtVaCreateWidget( "menu4",
			xmRowColumnWidgetClass, menu4_shell,
			XmNmenuAccelerator, "<KeyUp>F4",
			XmNrowColumnType, XmMENU_POPUP,
			NULL );

	UxPutContext( menu4, (char *) UxForausContext );

	foraus_view_fortran = XtVaCreateManagedWidget( "foraus_view_fortran",
			xmPushButtonWidgetClass, menu4,
			RES_CONVERT( XmNlabelString, "View Fortran" ),
			NULL );

	UxPutContext( foraus_view_fortran, (char *) UxForausContext );

	foraus_remove_fortran = XtVaCreateManagedWidget( "foraus_remove_fortran",
			xmPushButtonWidgetClass, menu4,
			RES_CONVERT( XmNlabelString, "Remove fortran" ),
			NULL );

	UxPutContext( foraus_remove_fortran, (char *) UxForausContext );

	foraus_edit_fortran = XtVaCreateManagedWidget( "foraus_edit_fortran",
			xmPushButtonWidgetClass, menu4,
			RES_CONVERT( XmNlabelString, "Edit Fortran" ),
			NULL );

	UxPutContext( foraus_edit_fortran, (char *) UxForausContext );

	pushButton9 = XtVaCreateManagedWidget( "pushButton9",
			xmPushButtonWidgetClass, Foraus,
			XmNleftWidget, pushButton3,
			XmNleftOffset, 300,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomOffset, 15,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Compilation Test" ),
			XmNheight, 30,
			XmNwidth, 140,
			XmNy, 430,
			XmNx, 280,
			NULL );

	UxPutContext( pushButton9, (char *) UxForausContext );

	pushButton4 = XtVaCreateManagedWidget( "pushButton4",
			xmPushButtonWidgetClass, Foraus,
			XmNleftWidget, pushButton9,
			XmNleftOffset, 580,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomOffset, 15,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNrightOffset, 20,
			XmNrightAttachment, XmATTACH_NONE,
			RES_CONVERT( XmNlabelString, "Cancel" ),
			XmNheight, 30,
			XmNwidth, 140,
			XmNy, 440,
			XmNx, 590,
			NULL );

	UxPutContext( pushButton4, (char *) UxForausContext );

	pushButton7 = XtVaCreateManagedWidget( "pushButton7",
			xmPushButtonWidgetClass, Foraus,
			XmNtopWidget, scrolledWindow2,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNbottomWidget, pushButton4,
			XmNbottomOffset, 30,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNleftWidget, arrowButton1,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			RES_CONVERT( XmNlabelString, "Select All" ),
			XmNheight, 40,
			XmNwidth, 90,
			XmNy, 340,
			XmNx, 460,
			NULL );

	UxPutContext( pushButton7, (char *) UxForausContext );

	pushButton8 = XtVaCreateManagedWidget( "pushButton8",
			xmPushButtonWidgetClass, Foraus,
			XmNtopWidget, scrolledWindow2,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNbottomWidget, pushButton4,
			XmNbottomOffset, 30,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNleftWidget, pushButton7,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			RES_CONVERT( XmNlabelString, "Unselect All" ),
			XmNheight, 40,
			XmNwidth, 90,
			XmNy, 340,
			XmNx, 550,
			NULL );

	UxPutContext( pushButton8, (char *) UxForausContext );

	XtAddCallback( Foraus, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxForausContext );

	XtAddCallback( pushButton3, XmNactivateCallback,
			activateCB_pushButton3,
			(XtPointer) UxForausContext );

	XtAddCallback( pushButton5, XmNactivateCallback,
			activateCB_pushButton5,
			(XtPointer) UxForausContext );

	XtAddCallback( pushButton6, XmNactivateCallback,
			activateCB_pushButton6,
			(XtPointer) UxForausContext );

	XtAddCallback( arrowButton1, XmNactivateCallback,
			activateCB_arrowButton1,
			(XtPointer) UxForausContext );

	XtAddCallback( scrolledList1, XmNmultipleSelectionCallback,
			multipleSelectionCB_scrolledList1,
			(XtPointer) UxForausContext );

	XtAddCallback( menu3, XmNmapCallback,
			mapCB_menu3,
			(XtPointer) UxForausContext );

	XtAddCallback( view_fortran, XmNactivateCallback,
			activateCB_view_fortran,
			(XtPointer) UxForausContext );

	XtAddCallback( view_doc, XmNactivateCallback,
			activateCB_view_doc,
			(XtPointer) UxForausContext );

	XtAddCallback( menu4, XmNmapCallback,
			mapCB_menu4,
			(XtPointer) UxForausContext );

	XtAddCallback( foraus_view_fortran, XmNactivateCallback,
			activateCB_foraus_view_fortran,
			(XtPointer) UxForausContext );

	XtAddCallback( foraus_remove_fortran, XmNactivateCallback,
			activateCB_foraus_remove_fortran,
			(XtPointer) UxForausContext );

	XtAddCallback( foraus_edit_fortran, XmNactivateCallback,
			activateCB_foraus_edit_fortran,
			(XtPointer) UxForausContext );

	XtAddCallback( pushButton9, XmNactivateCallback,
			activateCB_pushButton9,
			(XtPointer) UxForausContext );

	XtAddCallback( pushButton4, XmNactivateCallback,
			activateCB_pushButton4,
			(XtPointer) UxForausContext );

	XtAddCallback( pushButton7, XmNactivateCallback,
			activateCB_pushButton7,
			(XtPointer) UxForausContext );

	XtAddCallback( pushButton8, XmNactivateCallback,
			activateCB_pushButton8,
			(XtPointer) UxForausContext );


	XtAddEventHandler( scrolledList1, ButtonPressMask,
			False, _UxForausMenuPost, menu3 );
	XtAddEventHandler( scrolledList2, ButtonPressMask,
			False, _UxForausMenuPost, menu4 );

	return ( Foraus );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_Foraus()
{
	Widget                  rtrn;
	_UxCForaus              *UxContext;

	UxForausContext = UxContext =
		(_UxCForaus *) XtMalloc( sizeof(_UxCForaus) );

	{
		foraus_ok = False;
		rtrn = _Uxbuild_Foraus();

		UxPutSensitive(arrowButton1,"false");
		
		if( LoadModulesList(scrolledList1) != True)
		{
		   retswidget=create_vis_msg("Can't read model module list: crealtm.dat");
		   return(NULL);
		}
		   
		if( LoadForausStdList() != True)
		   retswidget=create_vis_msg("Can't read user auxiliary fortran: foraus.for");
		
		
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_Foraus()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_Foraus();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/















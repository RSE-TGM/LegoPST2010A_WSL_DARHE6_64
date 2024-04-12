/**********************************************************************
*
*       C Source:               iconinterf.c
*       Subsystem:              8
*       Description:
*       %created_by:    famgr %
*       %date_created:  Mon Sep 21 16:40:37 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: iconinterf.c-5 %  (%full_filespec: iconinterf.c-5:csrc:8 %)";
#endif
/*
   modulo iconinterf.c
   tipo 
   release 5.4
   data 2/5/96
   reserved @(#)iconinterf.c	5.4
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)iconinterf.c	5.4\t2/5/96";
/*
        Fine sezione per SCCS
*/
/*----------------------------------------------------------------------- 
  Scrive il file necessario alla creazione dei file f01.dat e f14.dat di
  una task contenente le informazioni sugli schemi e sulle icone connesse 
  ad altri schemi.
  Contiene le seguenti routine
  1) info_top_schemi
  2) interroga_pagina
  4) GetPag_FromName
  5) read_file_schemi 
 ----------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#if defined VMS
#include <stat.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Xresource.h>
#include <Xm/Xm.h>
#include <X11/Xlib.h>
#include <UxXt.h>
#include <X11/Core.h>
#include <Xl/XlCore.h>
#include <Xl/XlManager.h>
#include <Xl/Xl.h>
#include <Xl/XlIconReg.h>
#include <Xl/XlPort.h>
#include <Ol/OlConn.h>
#include <Ol/OlDatabaseTopologia.h>
#include <Xd/Xd.h>
#include <Xd/XdLista.h>
#include <Xm/DrawingA.h>

#include "config.h"
#include "message.h"
#include "forme.h"     /* per topologia schemi regolazione */
#include "top_icon.h"  /* per topologia schemi regolazione */



/*
   Variabili esterne
*/
extern PAGEDIT_CONTEXT *pagedit;
extern Widget UxTopLevel;
extern XtAppContext UxAppContext;
extern Display *UxDisplay;
extern Boolean StateInterfaceMode;
extern OlConnObject conn_obj; /* oggetto OlConn (gestione connessioni) */
extern *lista_macro;
extern Boolean comm_found;

/* 
  Prototyping funzioni
*/
int info_top_schemi();
int interroga_pagina(char *,  DESC_SCHEMA *,  char *);
int sel_moduletti(char *, char *, MODUL_LST *);
PAGINA *GetPag_FromName(char *);
int read_file_schemi(char *);
int CaricaListaMacroModuli(char *);
int EscludiMacro(char *);

/* 
  Prototyping funzioni esterne
*/
extern char *OlEstrRegTaskName(char *, char *);
extern Boolean PagIsOpen(char *);
extern Boolean PagGetInUses(PAGINA *);
extern Boolean GetInUseFromName(char *);
extern copia_n(char *, char *, int );
extern char *getpul (char *, int , FILE *);
extern int nome_underscore(char *, char *, int );
extern int rd_lst_schemi(LST_SCHM **, char *, char *);
extern int schema_presente(LST_SCHM *, char *, int );


/* 
  Variabili globali
*/
LST_SCHM *lista_macromoduli=NULL;
int n_mcro;

/*
      Produce un file contenete le strutture descrittive di ogni schema
      La struttura di ogni schema e' del tipo DESC_SCHEMA contenente le
      descrizioni di tipo generale e le informazioni relative alle icone
      di interfaccia.
      Richiama la routine di generazione dei files f01.dat e f14.dat relativi
      alla task.
*/
int info_top_schemi()
{
extern XrmDatabase defdb;
char task[50];
char task_4[5];
char task_sigl[3];
int ret,ret_sy;
int numero_schemi;
DESC_SCHEMA *schemi;
char nome_vms[200];
char nomefile[200];
char nomepagina[200];
PAGINA *pagina;
AN_OBJ *listaogg;
extern Widget topLevelShell;
Widget DrawingArea;
XrmValue value;
char *tipo=NULL;
Boolean retval=True;
Arg args[20];
FILE *fp;
char comando[500]={'\0'};
char messaggio[200]={'\0'};
char labour_dir[200];
char task_dir[200];
char file_err[200];
char path_pwd[FILENAME_MAX];
char file_conn[200];   /* Path name del file Connessioni.reg */
int i,j,k;
int ret1,ret2;
struct stat st;
extern OlDatabaseTopologiaObject dbtopologia;
extern int MessaggiErrore(int , int , char *);
char *appo=NULL;

/*
	
	elimino il vecchio database della topologia
 
*/
if(dbtopologia!=NULL)
	{
	if(OlDestroyDatabaseTopologia(dbtopologia))
		printf("Distrutto il database della topolgia\n");
	else
		printf("Impossibile distruggere il database della topolgia\n");
	dbtopologia = NULL;
	}


/* Directory di sviluppo della task, deve esistere */
   if( XlGetenv(ENVPAG) !=NULL )
      {
      strcpy(task_dir,XlGetenv(ENVPAG));
#if defined VMS
      strcpy(task_dir,XlConvDirVms(XlGetenv(ENVPAG)));
#endif
      }
   else
      {
      strcpy(task_dir,"");
      strcpy(messaggio,
             "Non e' stata definita la variabile di environment LEGOMMI_PAG\n");
      goto FINE;
      }

/* Directory di lavoro, se non esiste viene costruita */
   if( XlGetenv(WORK_PAG)!=NULL )
      {
      strcpy(labour_dir,XlGetenv(WORK_PAG));
#if defined VMS
      strcpy(labour_dir,XlConvDirVms(XlGetenv(WORK_PAG)));
#endif
      }
   else
      {
      strcpy(labour_dir,"");
      strcpy(messaggio,
             "Non e' stata definita la variabile di ambiente LEGOMMI_WORK: ");
      strcat(messaggio," si assegna la variabile ENVPAG,proc");
      if(comm_found!=0)
         printf("%s\n",messaggio);
      else
         SetMsg(topLevelShell,NULL,INFMSG,"ConfigInfo",messaggio,
                NULL,False,NULL,False,NULL);
      strcpy(labour_dir,XlGetenv(ENVPAG));
      strcat(labour_dir,"/proc");
#if defined VMS
      strcpy(labour_dir,XlConvDirVms(labour_dir));
#endif
     if ( !XlPutenv(WORK_PAG,labour_dir) )
        printf("Fallita la Putenv di WORK_PAG\n");
     }

/*
   Costruzione nomi:
   nomefile         file con informazioni sugli schemi
   task (task_4)    nome della task, estratta dal task_dir
   file_err         file degli errori della generazione della task
                    <nome_schema>.reg (_err viene aggiunto dalle routine
                    Xl che gestiscono tale file)
   file_conn        file contenente le informazioni sulle connessioni
                    fra gli schemi di regolazione
*/
   strcpy(nomefile,labour_dir);
#if defined UNIX
   strcat(nomefile,"/");
#endif
   strcat(nomefile,"schemi.dsc");

/* Estraggo id_task del direttorio della task */
   appo = OlEstrRegTaskName(task_dir,task);
   if( appo!=NULL )
       {
       strcpy(task_sigl,appo);
       tomaius(task_sigl);
       free(appo);
       }
   else
       {    
       printf("  iconinterf chiama OlEstrRegTaskName che ritorna NULL\n");
       strcpy(task_sigl,"");
       }
   /*printf("Ritorno=%s|  Completo=%s|\n",task_sigl,task);*/

   strncpy(task_4,task,4);
   if ( strlen(task_4)<4 )
     task_4[strlen(task_4)] = '\0';
   else
     task_4[4] = '\0';


   strcpy(file_err,task_dir);
#if defined UNIX
   strcat(file_err,"/");
#endif
   strcat(file_err,task);
   strcat(file_err,".reg");

   strcpy(file_conn,XlGetenv(ENVPAG));
   strcat(file_conn,"/");
#if defined VMS
   strcpy(file_conn,XlConvDirVms(XlGetenv(ENVPAG)));
#endif
   strcat(file_conn,"Connessioni.reg");

/* Generazione file degli errori,scrittura header e chiusura */
   XlSetFileErrComp(file_err);
   XlHeaderFileErrCompTask(file_err);
   XlSetFileErrComp(NULL);

/* Controllo l'esistenza di lista_schemi e libreria */
   getcwd(path_pwd,sizeof(path_pwd));
   chdir(labour_dir);
   ret1 = stat("lista_schemi.dat", &st );
   if( ret1==-1 )
     {
     strcpy(messaggio,"Manca il file lista_schemi.dat\n");
     goto FINE;
     }
   ret2 = stat("schemi_reg.a", &st );
   if( ret2==-1 )
     {
     strcpy(messaggio,"Manca il file schemi_reg.a\n");
     goto FINE;
     }
   chdir(path_pwd);

/*
   printf("\t NOMI FILE\n");
   printf("\t task_dir=%s (%d) \n",task_dir,strlen(task_dir)); 
   printf("\t labour_dir=%s (%d) \n",labour_dir,strlen(labour_dir)); 
   printf("\t file_conn=%s (%d) \n",file_conn,strlen(file_conn)); 
   printf("\t file_err=%s (%d) \n",file_err,strlen(file_err)); 
   printf("\t nomefile=%s (%d) \n\n",nomefile,strlen(nomefile)); 
*/
/*
   Vengono analizzati tutti gli schemi di regolazione
*/
/* Allocazione dei vettori di strutture  */
   numero_schemi = pagedit->pag_num;
   if( numero_schemi>0 )
      {
      schemi = (DESC_SCHEMA*)XtCalloc(numero_schemi,sizeof(DESC_SCHEMA));
      fp = fopen(nomefile,"w");
      if ( !fp )
         {
         strcpy(messaggio,"non si puo' aprire il file ");
         strcat(messaggio,nomefile);
         goto FINE;
         }
      }

/* Mi colloco nel direttorio di lavoro */
   chdir(labour_dir);

/* Creo l'oggetto Conn */
   if(!StateInterfaceMode)
        {
   	conn_obj=OlCreateConn(file_conn);
        }

/* Lettura lista macromoduli */
   n_mcro= CaricaListaMacroModuli(file_err);

/* Ciclo di interrogazione su tutti gli schemi */
   for(k=0;k<numero_schemi;k++)
      {
      strcpy(nomepagina,pagedit->page_list[k]);
/*    Escludo gli schemi nella lista dei macromoduli */
      if ( n_mcro!=0 )
         if ( !EscludiMacro(nomepagina) )
            continue;

      if ( GetInUseFromName(nomepagina)==True )
	{
        strcpy(schemi[k].schm.uso_schema,"S");
        interroga_pagina(nomepagina,&schemi[k],task_sigl);
	}
       else
        strcpy(schemi[k].schm.uso_schema,"N");

      } /* Fine ciclo su tutti gli schemi */
   UxDisplay->db = defdb;      
   if( lista_macromoduli!=NULL )
      free(lista_macromoduli);

/* Distruggo l'oggetto conn */
   if(!StateInterfaceMode)
   	OlDestroyConn(conn_obj);

/* Scrittura del file */
   fwrite(&numero_schemi,sizeof(int),1,fp);
   for(i=0;i<numero_schemi;i++)
      {
      fwrite(&schemi[i],sizeof(DESC_SCHEMA)-sizeof(ICON_INTERF*),1,fp);
      if( schemi[i].schm.num_icn_interf>0 )
          {
          fwrite(schemi[i].icn_interf,sizeof(ICON_INTERF),
                 schemi[i].schm.num_icn_interf,fp);
          }
      }
   fclose(fp);

/* Prova lettura del file scritto */
/***
   read_file_schemi(nomefile);
***/

/* Liberazione del vettore di strutture */
   for(i=0;i<numero_schemi;i++)
      {
      if( schemi[i].schm.num_icn_interf>0 )
         XtFree(schemi[i].icn_interf);
      }
   XtFree(schemi);


/*
    Generazione dei file f01.dat e f14.dat relativi ad una task
*/
   printf("comando -----> |%s| |%s| |%s| |%s| |%s| |%s| \n\n",
           "gen_f01task",task,task_dir,labour_dir,nomefile,file_err);

   sprintf(comando,"%s %s %s %s %s %s",
           "gen_f01task",task,task_dir,labour_dir,nomefile,file_err);

   ret_sy = system(comando);
#if defined UNIX
   ret = W_EXITSTATUS(ret_sy);
#else
   ret = ret_sy;
#endif
   if( ret!=0 )
      {
      MessaggiErrore(6,ret,messaggio);
      goto FINE;
      }

   strcpy(comando,"");
   printf("comando -----> |%s| |%s| |%s| |%s| |%s| |%s| \n\n",
           "gen_f14task",task,task_dir,labour_dir,nomefile,file_err);

   sprintf(comando,"%s %s %s %s %s %s",
           "gen_f14task",task,task_dir,labour_dir,nomefile,file_err);

   ret_sy = system(comando);
#if defined UNIX
   ret = W_EXITSTATUS(ret_sy);
#else
   ret = ret_sy;
#endif
   if( ret!=0 )
      {
      MessaggiErrore(7,ret,messaggio);
      goto FINE;
      }

/* Generazione della task */
   getcwd(path_pwd,sizeof(path_pwd));
   chdir(XlGetenv(ENVPAG));
   ret_sy = system("creamrg5sk");
   ret = W_EXITSTATUS(ret_sy);
   if( ret != 0 )
      {
      strcpy(messaggio,"creamrg5sk non e' terminata correttamente");
      goto FINE;
      }


   chdir(path_pwd);

/* Messaggio di fine corretta */
   tomaius(task_4);
   sprintf(messaggio,"Generazione corretta della task %s",task_4);
   if(comm_found!=0) {
      printf("%s\n",messaggio);
      printf("TASK %s generated \n",task_4);
   }
   else {
      SetMsg(topLevelShell,NULL,INFMSG,"Regolation Task",messaggio,
             NULL,False,NULL,False,NULL);
      sprintf(messaggio,"TASK %s generated \n",task_4);
      show_message(messaggio);
   }

/*
	riaggancio il database della topologia
*/
   chdir(XlGetenv(ENVRTF));
printf("Richiamo change_database\n");
   change_database();

   return(1);


FINE:
/*
	riaggancio il database della topologia
*/
   change_database();

/* Messaggio errore e chiusura del file */
   chdir(path_pwd);

   if(comm_found!=0)
      printf("%s\n",messaggio);
   else
      SetMsg(topLevelShell,NULL,ERRMSG,"ConfigInfo",messaggio,
             NULL,False,NULL,False,NULL);

   XlOpenFileErrComp(file_err);
   XlErrComp(NULL,"Compile Regolation Task","ERRORE\n ",messaggio);
   XlErrComp(NULL,"Compile Regolation Task - Termine-","ERRORE\n ",
              "Fine non corretta generazione task");
   XlSetFileErrComp(NULL);

   if(comm_found!=0)
      printf("TASK generation failed\n");
   else
      show_message("TASK generation failed\n");
   return(-1);
}




/*
    Routine per debugging.
    Lettura del file delle connessioni prodotto.
*/
int read_file_schemi(char *nome_del_file)
{
DESC_SCHEMA *schema;
FILE *ff;
int num_sch;
int i,k,h;

/*  Apertura del file */
    if ( !(ff=fopen(nome_del_file,"r")) )
       {
       fprintf(stderr,"non si puo' aprire il file %s\n",nome_del_file);
       return(-1);
       }

/*  Lettura */
    fread(&num_sch,sizeof(int),1,ff);
    schema = (DESC_SCHEMA*)XtCalloc(sizeof(DESC_SCHEMA),num_sch);
    for(i=0;i<num_sch;i++)
       {
       printf("\nSchema n.%d\n",i+1);
       fread(&schema[i],sizeof(DESC_SCHEMA)-sizeof(ICON_INTERF*),1,ff);
       printf("%d) nicn_interf=%d  uso=%s|  id_sch=%s| desc=%s|\n",i,
               schema[i].schm.num_icn_interf,schema[i].schm.uso_schema,
               schema[i].schm.id_schema,schema[i].schm.des_schema);
       printf("______________________________\n");
       for(k=0;k<schema[i].mdlt.num;k++)
           printf("%d) NOME=%s| DESC=%s| (totale=%d)\n",
                   k,schema[i].mdlt.nome[k],schema[i].mdlt.desc[k],
                   schema[i].mdlt.num);
       printf("______________________________\n");
       if( schema[i].schm.num_icn_interf>0 )
          {
          schema[i].icn_interf = (ICON_INTERF*)XtCalloc(sizeof(ICON_INTERF),
                                             schema[i].schm.num_icn_interf);
          fread(&schema[i].icn_interf[0],sizeof(ICON_INTERF),
                schema[i].schm.num_icn_interf,ff);

          for(h=0;h<schema[i].schm.num_icn_interf;h++)
           printf("  %d.%d) sigla=%s| int_conn=%s| int_sche=%s| VL=%s| VR=%s|\n",
                      i,k,
                      schema[i].icn_interf[h].int_icnsigl,
                      schema[i].icn_interf[h].int_conn,
                      schema[i].icn_interf[h].clg.int_sche,
                      schema[i].icn_interf[h].clg.int_varl,
                      schema[i].icn_interf[h].clg.int_varr);

          }
       }

/* Liberazione delle strutture */
   for(i=0;i<num_sch;i++)
      {
      if( schema[i].schm.num_icn_interf>0 )
         {
         /*
         printf("%d) Libero schema (<%d> icone di interf)  int_conn[0]=%s|  int_conn[1]=%s|\n",
               i,schema[i].schm.num_icn_interf,schema[i].icn_interf[0].int_conn,
               schema[i].icn_interf[1].int_conn);
         */
         XtFree(schema[i].icn_interf);
         }
      }
   XtFree(schema);
   fclose(ff);
}






/*
    Carica la struttura descrittiva dei moduletti di regolazione. 
*/
int sel_moduletti(char *nome, char *desc, MODUL_LST *mod)
{
int ret;
int lun;
int i,j;
int inserimento=1;

      if ( (nome!=NULL)&&(strlen(nome)>0) )
         {
         for(i=0;i<mod->num;i++)
            {
            /*
            printf("%d)CONFRONTO nome=%s con lista=%s\n",
                    i,nome,mod->nome[i]);
            */
            if( !strncmp(nome,mod->nome[i],4) )
               {
               inserimento = 0;
               break;
               }
            }
         if( inserimento )
            {
            copy_n_car(mod->nome[mod->num],nome,LUNSIGL-1);
            copy_n_car(mod->desc[mod->num],desc,LUNDESC-1);
            /*copia_n(mod->nome[mod->num],nome,LUNSIGL-1);*/
            /*copia_n(mod->desc[mod->num],desc,LUNDESC-1);*/
            mod->num++;
/*
printf("   %d) Ho inserito :NOME=%s|  nome=%s|  DESC=%s|(%d %d)\n",
       mod->num,mod->nome[mod->num-1],nome,mod->desc[mod->num-1],
       strlen(mod->nome[mod->num-1]),
       strlen(mod->desc[mod->num-1]));
*/
            }
         }
      return(1);
}



PAGINA *GetPag_FromName(char *nome_pagina)
{
   extern PAGINA *pagine;
   PAGINA *pappo;

   pappo = pagine;

   if(pagine != NULL)
   {
      while(pappo != NULL)
      {
         if(!strcmp(pappo->nomepag,nome_pagina))
         {
            /*pagine = pappo;*/
            return(pappo);
         }
         pappo = pappo->pagsucc;
      }
   }

   return(NULL);
}




/* 
    Carica in memoria la lista dei macromoduli
    Ritorna il numero dei macromoduli esistenti.
*/
int CaricaListaMacroModuli(char *filerr)
{
int num;

/*    Memorizza lista macromoduli e ritorno il numero */
      num= rd_lst_schemi(&lista_macromoduli,filerr,lista_macro);

      if ( num<0 )
         return(0);
      else
         return(num);
}



int EscludiMacro(char *nome)
{

   if ( -1==(schema_presente(lista_macromoduli,nome,n_mcro)) )
         {
         return(1);   /* Il macromodulo non c'e' */
         }
   else
         {
         return(0);  /* Trovato il macromodulo */
         }
}




int interroga_pagina(char *nome,DESC_SCHEMA *sch,char *sigla_task)
{
char nome_file_reg[200];
char appoggio[10];
FILE *fp;
MODUL_LST moduletti;
char descr[LUNDESC];
TOP_ICON icona;
CONNESSIONE *connessione;
int i,j,num_conn,num_ico;
                  
   moduletti.num = 0;
   sch->schm.num_icn_interf = 0;

printf("interroga pagina_new    nome = %s sigla_task [%s]\n",nome,sigla_task);

strcpy(appoggio,nome);
tominus(appoggio);
strcpy(nome_file_reg,appoggio);
strcat(nome_file_reg,".reg");

fp=fopen(nome_file_reg,"r");
if(fp==NULL)
	return(-1);

/*
	leggo il file nome_schema.reg per ricavare l'elenco dei moduli
	inseriti nello schema
*/
   fread(descr,LUNDESC,1,fp);
   /* printf("descr= [%s] sizeof(TOP_ICON)=%d\n",descr,sizeof(TOP_ICON));*/

/* Descrizioni proprie dello schema */
   strncpy(sch->schm.id_schema,nome,5);
   sch->schm.id_schema[5] = '\0';
   strncpy(sch->schm.des_schema,descr,LUNDESC);
   sch->schm.des_schema[LUNDESC] = '\0';


while(fread(&icona,sizeof(TOP_ICON),1,fp)>0)
        sel_moduletti(icona.pr_nome,icona.pr_desc,&moduletti);

memcpy(&sch->mdlt,&moduletti,sizeof(MODUL_LST));

fclose(fp);


/*
	cerco le connessioni
*/
num_conn=OlGetNumConn(conn_obj);
num_ico = 0;
for(i=0;i<num_conn;i++)
	{
	connessione = OlGetConn(conn_obj,i);
	if((strcmp(nome,connessione->u_nome_pagina)==0) ||
		(strcmp(nome,connessione->i_nome_pagina)==0))
			++num_ico;
	}
sch->schm.num_icn_interf = num_ico;
if(num_ico == 0)
	return(1);  /* non ci sono icone di interfaccia connesse */

sch->icn_interf = (ICON_INTERF*)
               XtCalloc(sch->schm.num_icn_interf,sizeof(ICON_INTERF));

j = 0;
for(i=0;i<num_conn;i++)
	{
	connessione = OlGetConn(conn_obj,i);
	if(!((strcmp(nome,connessione->u_nome_pagina)==0) ||
		(strcmp(nome,connessione->i_nome_pagina)==0)))
			continue;

	strcpy(sch->icn_interf[j].int_conn,"SI");
	strcpy(sch->icn_interf[j].int_icnsigl,connessione->i_nome_icona_int);
	if(strcmp(nome,connessione->u_nome_pagina)==0)
	   	{
		strcpy(sch->icn_interf[j].clg.int_sche,
			connessione->i_nome_pagina);
		strcat(sch->icn_interf[j].clg.int_sche,
			&(connessione->i_nome_tag[2]));
		strcat(sch->icn_interf[j].clg.int_sche,sigla_task);

		strcpy(sch->icn_interf[j].clg.int_varl,
			connessione->u_nome_var);
		strcat(sch->icn_interf[j].clg.int_varl,
			connessione->u_nome_tag);
		strcat(sch->icn_interf[j].clg.int_varl,sigla_task);

		strcpy(sch->icn_interf[j].clg.int_varr,
			connessione->i_nome_var);
		strcat(sch->icn_interf[j].clg.int_varr,
			connessione->i_nome_tag);
		strcat(sch->icn_interf[j].clg.int_varr,sigla_task);
		}
	else
		{
		strcpy(sch->icn_interf[j].clg.int_sche,
			connessione->u_nome_pagina);
		strcat(sch->icn_interf[j].clg.int_sche,
			&(connessione->u_nome_tag[2]));
		strcat(sch->icn_interf[j].clg.int_sche,sigla_task);

		strcpy(sch->icn_interf[j].clg.int_varl,
			connessione->i_nome_var);
		strcat(sch->icn_interf[j].clg.int_varl,
			connessione->i_nome_tag);
		strcat(sch->icn_interf[j].clg.int_varl,sigla_task);

		strcpy(sch->icn_interf[j].clg.int_varr,
			connessione->u_nome_var);
		strcat(sch->icn_interf[j].clg.int_varr,
			connessione->u_nome_tag);
		strcat(sch->icn_interf[j].clg.int_varr,sigla_task);
		}
	++ j;
	}

return(1);
}
/* Fine file */

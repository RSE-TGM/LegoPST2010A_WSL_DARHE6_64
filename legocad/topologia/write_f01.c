/**********************************************************************
*
*       C Source:               write_f01.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 13:59:42 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: write_f01.c,2 %  (%full_filespec: 1,csrc,write_f01.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)write_f01.c	2.26\t3/30/95";
/*
        Fine sezione per SCCS
*/

/*================================================================  
|
|   write_f01:  scrittura file f01.dat
|
|   16-6-93
|
=================================================================*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lg1.h"
#include "errore.h"

#define COL0 0
#define COL1 10 
#define COL2 17   

extern ERR_LEVEL err_level;
extern int changes_in_F01;
extern int graphics_on;


static FILE *f01;

write_f01_tappo()
{
  char *tappo = {"****"};

  fprintf(f01,"%s\n",tappo);
}


write_f01_bl()
{
  char riga[80];
  int i;

  
  for(i=0;i<num_blocchi;i++)
  {

/* costruzione stringa per elenco blocchi 
*/
     memset(riga,' ',80);
     riga[79] = 0;
     sprintf(riga,"%.4s",blocchi[i].sigla_modulo);
     riga[strlen(riga)] = ' ';
     sprintf(&(riga[COL1]),"%s","BLOCCO");
     riga[strlen(riga)] = ' ';
     riga[17]= '(';
     sprintf(&(riga[18]),"%.4s",blocchi[i].sigla_blocco);
     riga[22] = ')';
     riga[24] = '-';
     sprintf(&(riga[26]),"%s",blocchi[i].descr_blocco);
     riga[strlen(riga)]=' ';
     riga[79]=0;


/* scrittura riga su file 
*/
     fprintf(f01,"%s\n",riga);
  }
}


write_f01_modello()
{
  extern char *str_toupper();
  char nome[80];
  int i,len;


  sprintf(nome,"%s",modello.nome); 
  str_toupper(nome);


  if( (len = strlen(nome)) < 9)
     strncat(nome,"        ",(8-len));
  strncat(nome,"                                                        ", (80-len) );
  nome[79]=0;
  fprintf(f01,"%s\n",nome);
}


write_f01_var()
{
  char riga[150];
  int i,j,k,ind_var_int,ind_var_ext,ind_bl_ext;
  VAR *var;
  CONN *conn;

  for(i=0;i<num_blocchi;i++)
  {
     if(i)
     {
        memset(riga,' ',80);
        strcpy(riga,"****");
        riga[strlen(riga)]=' ';
        riga[79]=0; 
        fprintf(f01,"%s\n",riga);
     }
       
     memset(riga,' ',sizeof(riga));
     sprintf(riga,"%s",blocchi[i].label);
     riga[strlen(riga)] = ' ';
     sprintf(&(riga[COL1]),"%s","BL.-");
     sprintf(&(riga[COL1+4]),"%s",blocchi[i].sigla_blocco);
     riga[strlen(riga)] = ' ';

     if(blocchi[i].tipo == PROCESSO)
        sprintf(&(riga[COL1+8]),"%s","- **** MODULO ");
     else if(blocchi[i].tipo == REGOLAZIONE)
        sprintf(&(riga[COL1+8]),"%s","- **** REGOL. ");
     else
     {
        sprintf(&(riga[COL1+8]),"%s","- **** INDEF. ");
        err_level = WARNING;
        errore("Tipo blocco non identificato ?!? ");
     }

     sprintf(&(riga[COL1+22]),"%4s",blocchi[i].sigla_modulo);
     riga[strlen(riga)] = ' ';
     sprintf(&(riga[COL1+27]),"%s","- ");
     sprintf(&(riga[COL1+29]),"%s",blocchi[i].descr_blocco);
     riga[strlen(riga)]= ' ';
     riga[79] = 0;

     fprintf(f01,"%s\n",riga);
   
     var = blocchi[i].variabili;

     for(j=0;j<blocchi[i].num_variabili;j++)
     {

        conn = blocchi[i].variabili_connesse;

        memset(riga,' ',sizeof(riga));

        if(  var[j].tipo == INGRESSO) 
        {
           if( var[j].connessioni)
           {
              while(1) 
              {
                 if(conn->var_interna == j)
                 {
                    ind_var_ext = conn->var_esterna;
                    ind_var_int = conn->var_interna;
                    ind_bl_ext  = conn->blocco_esterno;

                    sprintf(riga,"%s",blocchi[ind_bl_ext].variabili[ind_var_ext].nome);
                    riga[strlen(riga)]=' ';
                    sprintf(&(riga[COL1]),"%s","--IN-- #");
                    riga[strlen(riga)]=' ';
                    sprintf(&(riga[COL2+1]),"%s",var[j].nome);
                    riga[strlen(riga)]=' ';
                    sprintf(&(riga[COL2+9]),"%s","#....................<===");
                    sprintf(&(riga[strlen(riga)]),blocchi[ind_bl_ext].label);
                    sprintf(&(riga[strlen(riga)]),"  BL.-");
                    sprintf(&(riga[strlen(riga)]),blocchi[ind_bl_ext].sigla_blocco);
                    sprintf(&(riga[strlen(riga)]),"-");
                    break;
                 }
                 conn = conn->succ;
              }
           }
           else
           {
              sprintf(riga,"%s",var[j].nome);
              riga[strlen(riga)]=' ';
              sprintf(&(riga[COL1]),"%s","--IN--");
              riga[strlen(riga)]=' ';
              sprintf(&(riga[COL2]),"%s",var[j].descr);
           }
        }
        else if( var[j].tipo == STATO )
        {
           sprintf(riga,"%s",var[j].nome);
           riga[strlen(riga)]=' ';
           sprintf(&(riga[COL1]),"%s","--US--");
           riga[strlen(riga)]=' ';
           sprintf(&(riga[COL2]),"%s",var[j].descr);
        }
        else if( var[j].tipo == USCITA) 
        {
           sprintf(riga,"%s",var[j].nome);
           riga[strlen(riga)]=' ';
           sprintf(&(riga[COL1]),"%s","--UA--");
           riga[strlen(riga)]=' ';
           sprintf(&(riga[COL2]),"%s",var[j].descr);
        }
        riga[strlen(riga)]=' ';
        riga[79]=0;
        fprintf(f01,"%s\n",riga);
     }
     memset(riga,' ',80);
     strcpy(riga,"****");
     riga[strlen(riga)]=' ';
     riga[79]=0; 
     fprintf(f01,"%s\n",riga);
  }
}

write_f01_ing()
{
   char riga[86];
   int i,j;
   VAR *var;

   sprintf(riga,"%s","****      >>>>>>INGRESSI DI TUTTI I MODULI<<<<<<");
   fprintf(f01,"%s\n",riga);
   for(i=0;i<num_blocchi;i++)
   {
     var = blocchi[i].variabili;
     for(j=0;j<blocchi[i].num_variabili;j++)
     {
        if(  var[j].tipo == INGRESSO) 
        {
           if( !(var[j].connessioni) )
           {
              sprintf(riga,"%s",var[j].nome);
              riga[strlen(riga)]=' ';
              sprintf(&(riga[COL1]),"%s","--IN--");
              riga[strlen(riga)]=' ';
              sprintf(&(riga[COL2]),"%s",var[j].descr);
              riga[strlen(riga)]=' ';
              riga[79]=0;
              fprintf(f01,"%s\n",riga);
           }
        }
     }
   } 
}


write_f01_conn()
{
  char riga[86];
  int i,j,k,ind_var_int,ind_var_ext,ind_bl_ext;
  VAR *var;

   for(i=0;i<num_blocchi;i++)
   {
     var = blocchi[i].variabili;

     for(j=0;j<blocchi[i].num_variabili;j++)
     {
        if(  var[j].tipo == INGRESSO)
        {
           if( var[j].connessioni)
           {
              memset(riga,' ',80);
              sprintf(riga,"%s",var[j].nome);
              riga[strlen(riga)]=' ';
              sprintf(&(riga[COL1]),"%s","--CO--");
              riga[strlen(riga)]=' ';
              sprintf(&(riga[COL2]),"%s",var[j].descr);
              riga[strlen(riga)]=' ';
              riga[79]=0;
              fprintf(f01,"%s\n",riga);
           }
         }
      }
   }
}


int write_f01()
{
  char path[1024];
  char direttorio[1024];
  char shell_command[300];
  int ret_stat;


  /* Apertura del file F01 in scrittura */
  strcpy ( path, modello.path_legocad );
  strcat ( path, modello.nome );
  strcpy(direttorio,path);
  strcat ( path, "/f01.dat" );

  strcpy(shell_command,"cp ");
  strcat(shell_command,path);
  strcat(shell_command," ");
  strcat(shell_command,direttorio);
  strcat(shell_command,"/f01.lastsave");
  ret_stat = system(shell_command);
  if( ret_stat == 127 )
     printf("I can't perform backup of f01.dat\n");
  else if( ret_stat != 0)
     printf("I can't nake backup of f01.dat\n");
  else
     printf("last version of f01.dat is in f01.lastsave\n");

  if ( !(f01=fopen (  path, "w" )) )
  {
    err_level = ERROR;
    errore ( OPEN_F01_ERR, modello.nome );
    return;
  }
  if(num_blocchi == 0)
  {
     fclose(f01);
     remove(path);
     remove(direttorio);
     return;  
  }


  printf("Fase Di Salvataggio del Modello %s\n",modello.nome);
  write_f01_tappo();
  write_f01_bl();
  write_f01_tappo();
  write_f01_modello();
  write_f01_tappo();
  write_f01_var();
  write_f01_ing();
  write_f01_tappo();
  write_f01_conn();

  changes_in_F01 = 0;
  fclose(f01);

}







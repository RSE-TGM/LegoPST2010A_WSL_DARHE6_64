/**********************************************************************
*
*       C Source:               gen_util.c
*       Subsystem:              2
*       Description:
*       %created_by:    zanna %
*       %date_created:  Mon Jul  1 15:28:03 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: gen_util.c,2 %  (%full_filespec: 2,csrc,gen_util.c,2 %)";
#endif
/*
   modulo gen_util.c
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)gen_util.c	5.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)gen_util.c	5.1\t11/13/95";
/*
        Fine sezione per SCCS
*/
/*----------------------------------------------------------------------
 *       							       *
 * Routines che sostituiscono localmente le routines Xl per
 * la gestione degli errori: in questo modo si evita l'inclusione
 * di tutte le librerie Xm,Xt,X
 *  XlSetFileErrComp						       *
 *  XlErrComp   						       *
 *  OlEstrRegTaskName
 *   								       * 
 *---------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <pagresdef.h>

FILE *fpErrCom;
int numErrCom;
int numErrComWidget;


void XlErrComp(char* w,char *procedura,char *commentoA,char *commentoB)
{
static char nameWidget[100];

/*
	incrementa il contatore degli errori
*/
++numErrCom;
numErrComWidget=1;
fprintf(fpErrCom,"\n\n");

fprintf(fpErrCom,"%4d - Elaboration error\n", numErrCom);
fprintf(fpErrCom,"         Procedure [%s]",procedura);
fprintf(fpErrCom,"         %s",commentoA);
if(commentoB!=NULL)
	fprintf(fpErrCom,"   %s\n\n",commentoB);
else
	fprintf(fpErrCom,"\n\n");
}

/*
   Apre per la prima volta il file degli errori
*/
void XlSetFileErrComp(char *nomeFile)
{
char nome[100];
#if defined VMS
char nome_vms[100];
#endif

if(nomeFile==NULL)
	fclose(fpErrCom);
else
	{
	sprintf(nome,"%s_err",nomeFile);
#if defined VMS
	strcpy(nome_vms,XlConvPathVms(nome));
	strcpy(nome,nome_vms);
#endif
	if((fpErrCom=fopen(nome,"w"))==NULL)
		fpErrCom=NULL;

	numErrCom=0;
	numErrComWidget=0;
	return;
	}
}


/*
   Apre il file degli errori
*/
void XlOpenFileErrComp(char *nomeFile)
{
char nome[100];
#if defined VMS
char nome_vms[100];
#endif

if(nomeFile==NULL)
	fclose(fpErrCom);
else
	{
	sprintf(nome,"%s_err",nomeFile);
#if defined VMS
	strcpy(nome_vms,XlConvPathVms(nome));
	strcpy(nome,nome_vms);
#endif
	if((fpErrCom=fopen(nome,"a"))==NULL)
            {
            printf("Il file %s non esiste, lo apro in write\n",nome);
	    if((fpErrCom=fopen(nome,"w"))==NULL)
    		fpErrCom=NULL;
            }

	numErrCom=0;
	numErrComWidget=0;
	return;
	}
}

void XlHeaderFileErrCompTask(char *nomeFile)
{
fprintf(fpErrCom,
	"****************************************************************************\n\n");
fprintf(fpErrCom,"Generazione dei files f01.dat, f14.dat e della task \n");
fprintf(fpErrCom,
	"\n*****************************************************************************\n");
}

void XlHeaderFileErrComp(char *nomeFile)
{
fprintf(fpErrCom,
	"****************************************************************************\n\n");
fprintf(fpErrCom,"Compilazione pagina %s\n",nomeFile);
fprintf(fpErrCom,
	"\n*****************************************************************************\n");
}


/*
     Estrae da un assegnato pathname di regolazione del tipo standard
     xxxxxx/r_tasknumero1 i primi due caratteri che seguono r_ e ritorna
     fra i suoi parametri il nome della task, in questo caso nome_out
     ma limita ad 8 caratteri.
*/
char *OlEstrRegTaskName(char *nome_path, char *nome_out)
{
#define FILTRO_REG "r_"
#define DIM_RET 2
int i;
int old_directory=0;
int poscpy;
char *ret;
char appoggio[200]={'\0'};
char appoggio1[200]={'\0'};


   /*printf("\n    NOMEIN=%s\n",nome_path);*/
   strcpy(nome_out,"");
   for(i=strlen(nome_path)-2;i>0;i--)
      {
#if defined UNIX
      if( nome_path[i]=='/' )
#endif
#if defined VMS
      if( nome_path[i]=='.' )
#endif
          {
          strcpy(appoggio,&nome_path[i+1]);

/*        Controllo che il direttorio sia del tipo regolazione */
          if( strncmp(appoggio,FILTRO_REG,2)!=0 )
             {
             fprintf(stderr,"Directory senza la chiave %s\n",FILTRO_REG);
             old_directory = 1;
             /* return(NULL);*/
             }
          if( strlen(appoggio)<= strlen(FILTRO_REG) )
             {
             fprintf(stderr,"Directory task non standard\n%s\n",appoggio);
             return(NULL);
             }

/*        Se il direttorio e' vecchio copio da 0 */
          if ( old_directory==1 )
             {
             poscpy = 0;
             }
          else
             {
             poscpy = strlen(FILTRO_REG);
             }

          strncpy(appoggio1,&appoggio[poscpy],8);

          if( strlen(appoggio1)>8 )
             appoggio1[8]='\0';

          strcpy(nome_out,appoggio1);

#if defined VMS
          nome_out[strlen(nome_out)-1]='\0';
#endif
#if defined UNIX
          nome_out[strlen(nome_out)]='\0';
#endif

/*        Determinato il nome si esce */
                                       
          break;
          }
     }

/* Test */
   if(i==0)
     {
     fprintf(stderr,"Estrazione nome task scorretta ");
     return(NULL);
     }

/* Ritorno: i primi DIM_RET (2) caratteri */
   ret = (char*)calloc(DIM_RET+1,sizeof(char));
   strncpy(ret,nome_out,DIM_RET);
   ret[DIM_RET] = '\0';

   return(ret);
}


/*  ROUTINE DI UTILIZZO GENERALE */
char *getpul (char *str, int n, FILE *fp)
{
char *ptr;
if (! fgets (str, n, fp))
   return NULL;
ptr = str + strlen(str) - 1;
for ( ; ptr >= str && (unsigned)*ptr <= 32; )
   *(ptr--) = '\0';
return (str);
}


char *copia_n (char *str1, char *str2, int n)
{
int i, j;

for (i = 0, j = 1; i < n; i++)
   if (j)
      j = (int)(str1[i] = str2[i]);
   else
      str1[i] = '\0';
str1[n] = '\0';
return (str1);
}

char *maiuscolo (char *str)
{
char *p;
for (p = str; *p; p++)
   if (*p > 96 && *p <= 122)
      *p -= 32;
return (str);
}



char *minuscolo (char *str)
{
char *p;
for (p = str; *p; p++)
   if (*p > 64 && *p <= 90)
      *p += 32;
return (str);
}
/* Fine file */

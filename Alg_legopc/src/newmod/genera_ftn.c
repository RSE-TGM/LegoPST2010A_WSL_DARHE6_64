
/*** File genera_ftn.c - generazione del FORTRAN di un modulo lego dal file
                         interfaccia.


 Contiene le funzioni per :

 1 ) recuperare le informazioni dal file interfaccia .i in memoria
     ( leggi_file_interfaccia() );

 2 ) generare il FORTRAN dalle informazioni contentute in memoria (variabili
     globali)
     ( genera_fortran() ).

***/

/****************************************************************/
/* INCLUDE FILES						*/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definizioni.h"


/****************************************************************/
/* VARIABILI GLOBALI ESTERNE					*/
/****************************************************************/

int num_var_stato = 0;
int num_var_algebriche = 0;
int num_var_ingresso = 0;
int num_dati_geometrici = 0;

char *str_dichI2 = NULL, *str_codI2 = NULL;
char *str_dichJC = NULL, *str_codJC = NULL;
char *str_dichMOD = NULL, *str_codMOD = NULL,*str_resMOD[MAX_EQUAZIONI];
char *str_signeq[MAX_EQUAZIONI], *str_uniteq[MAX_EQUAZIONI],
     *str_cosnor[MAX_EQUAZIONI];

JacToggStruct jactoggstruct[MAX_EQUAZIONI][MAX_VARIABILI_IN_OUT];

int num_yes_toggle;
byte jacobian_type;

StructVars *variabili;
StructDati *dati_geom;

char nome_modulo[5];
char titolo_esteso[51];
char descr_modulo[81];

/* char nome_modulo[], descr_modulo[];*/

/* widget testo relativo alle variabili ed ai dati geometrici 
extern WdgVariabili *wvar_stato, *wvar_algebriche, *wvar_ingresso;
extern WdgDatiGeometrici *wdati_geometrici;

extern swidget nmod_bboard;/


/*** leggi_file_interfaccia()
 ***
 ***   Descrizione:
 ***     Legge dal file interfaccia le informazioni della NEWMOD e le carica
 ***     in memoria nelle variabili globali
 ***/
leggi_file_interfaccia()
{
   FILE *fp_iface;
   char nome_file_interfaccia[256], nome[5];
   int i, j, numero_variabili;
   int flag = 0;
   
   componi_file_modulo(nome_file_interfaccia,nome_modulo,FILE_IFACE);
   
   
   printf("file INTERFACCIA: %s\n", nome_file_interfaccia);
   if ((fp_iface = fopen(nome_file_interfaccia,"r")) == NULL)
   {
      fprintf(stderr, "Cannot open interface file %s.\n",nome_file_interfaccia);
      return(-1);
   }

   ifile_nome_modulo( fp_iface, nome, titolo_esteso );
   if (ifile_header( fp_iface, &num_var_stato, &num_var_algebriche, &num_var_ingresso, &num_dati_geometrici) != 0)
   {
   	num_var_stato = 0;
	num_var_algebriche = 0;
	num_var_ingresso = 0;
	num_dati_geometrici = 0;
	
      	flag = -1;
   }

   numero_variabili = num_var_stato+num_var_algebriche+num_var_ingresso;
   
/* allocazione della memoria */
   variabili = (StructVars *) calloc(numero_variabili,sizeof(StructVars));
   dati_geom = (StructDati *) calloc(num_dati_geometrici,sizeof(StructDati));

/* Azzera lo jacobiano */
   for (i=0 ; i<num_var_stato+num_var_algebriche ;i++)
      for (j=0 ; j<num_var_stato+num_var_algebriche+num_var_ingresso ;j++)
      {
         jactoggstruct[i][j].jac_yes = False;
         jactoggstruct[i][j].stringa = NULL;
      }

   ifile_variabili( fp_iface, variabili, num_var_stato, num_var_algebriche, num_var_ingresso );
   ifile_dati_geometrici( fp_iface, dati_geom, num_dati_geometrici );
   ifile_jacobiano( fp_iface, &jacobian_type, jactoggstruct, &num_yes_toggle );
   ifile_subI2( fp_iface,&str_dichI2, &str_codI2 );
   ifile_subJC( fp_iface,&str_dichJC,&str_codJC,jactoggstruct,num_var_stato+num_var_algebriche,
		         numero_variabili );
   ifile_subMOD( fp_iface,&str_dichMOD,&str_codMOD,str_resMOD,num_var_stato+num_var_algebriche );
   ifile_subD1( fp_iface, str_signeq, str_uniteq, str_cosnor, num_var_stato+num_var_algebriche );

   fclose(fp_iface);

   return(flag);
}

/*** genera_fortran(nome_modulo,titolo_esteso)
 ***
 ***   Descrizione:
 ***     Genera il codice FORTRAN dalle informazioni inserite dall'utente
 ***     nelle window della NEWMOD
 ***/
genera_fortran(nome_modulo,titolo_esteso)
char *nome_modulo, *titolo_esteso; 
{
   FILE *fp_ftn;
   char nome_file_fortran[256];
   int numero_variabili;

   numero_variabili = num_var_stato+num_var_algebriche+num_var_ingresso;

   componi_file_modulo(nome_file_fortran,nome_modulo,FILE_FTN);

   printf("file FORTRAN: %s\n", nome_file_fortran);
   if ((fp_ftn = fopen(nome_file_fortran,"w+")) == NULL)
   {
      fprintf(stderr, "Cannot create FORTRAN output file %s.\n",
              nome_file_fortran);
      return(-1);
   }

/* generazione del FORTRAN */
   genmodI3(fp_ftn, nome_modulo, variabili, numero_variabili,
                    num_var_stato, num_var_algebriche);

   intesta_subroutine(fp_ftn);
   genmodI4(fp_ftn, nome_modulo);

   intesta_subroutine(fp_ftn);
   genmodI2(fp_ftn, nome_modulo, titolo_esteso, dati_geom, num_dati_geometrici,
                    variabili, numero_variabili, str_dichI2, str_codI2);
   intesta_subroutine(fp_ftn);
   genmodC1(fp_ftn, nome_modulo, titolo_esteso, jacobian_type, 
                    dati_geom, num_dati_geometrici,
                    variabili, numero_variabili);

   intesta_subroutine(fp_ftn);
   genmodJC(fp_ftn, nome_modulo, dati_geom, num_dati_geometrici,
                    variabili, numero_variabili, num_var_stato, 
                    num_var_algebriche, jactoggstruct, str_dichJC, str_codJC);

   intesta_subroutine(fp_ftn);
   genmodMOD(fp_ftn, nome_modulo, titolo_esteso, dati_geom, num_dati_geometrici,
                     variabili, numero_variabili, num_var_stato, 
                     num_var_algebriche, str_dichMOD, str_codMOD, str_resMOD);

   intesta_subroutine(fp_ftn);
   genmodD1(fp_ftn,  nome_modulo, titolo_esteso, variabili, numero_variabili,
                     num_var_stato, num_var_algebriche, jactoggstruct,
                     str_signeq, str_uniteq, str_cosnor);

/* chiusura dei files */
   fclose(fp_ftn);

/* ritorno alla procedura chiamante */
   return(0);
}

/*** ifile_nome_modulo( fp, nome, descr )
 ***   Parametri :
 ***     FILE *fp   : file pointer interfaccia (.i)
 ***     char *nome : nome del modulo (uscita)
 ***     char *descr: descrizione del modulo (uscita)
 ***
 ***   Descrizione:
 ***     Legge dal file interfaccia (.i) il nome del modulo e la sua
 ***     descrizione.
 ***/
ifile_nome_modulo( fp, nome, descr )
FILE *fp;
char nome[], descr[];
{
   char buffer[100];

   fseek( fp, 0L, SEEK_SET );
   if (fgets(buffer,80,fp) == NULL)
      return(-1);
   sscanf( buffer, "%s %[^\n]", nome, descr);
   return(0);
}

/*** ifile_header( fp, nstati, nuscite, ningressi, ndati )
 ***   Parametri :
 ***     FILE *fp      : file pointer interfaccia (.i)
 ***     int *nstati   : numero var. stato (uscita)
 ***     int *nuscite  : numero var. algebriche (uscita)
 ***     int *ningressi: numero var. ingresso (uscita)
 ***     int *ndati    : numero dati geometrici e fisici (uscita)
 ***
 ***   Descrizione:
 ***     Recupera dall'header del file interfaccia (.i) il il numero delle
 ***     variabili e dei dati geometrici e fisici
 ***/
ifile_header( fp, nstati, nuscite, ningressi, ndati )
FILE *fp;
int *nstati, *nuscite, *ningressi, *ndati;
{
    char buffer[100];

    if (fgets( buffer, 100, fp ) == NULL)     /* salta la riga '****' */
       return(-1);
    if (fscanf(fp,"%d\n%d\n%d\n%d\n",nstati,nuscite,ningressi,ndati) == EOF)
       return(-1);
    return(0);
}

/*** ifile_variabili(fp,&variabili,numero_stati,numero_uscite,numero_ingressi)
 ***   Parametri:
 ***     FILE *fp      : file pointer interfaccia (.i)
 ***     StructVars *variabili: struttura variabili (stati, uscite, ingressi)
 ***                            che viene letta dal file (uscita).
 ***     int numero_stati : numero variabili di stato 
 ***     int numero_uscite: numero variabili di uscita
 ***     int numero_ingressi : numero variabili di ingresso.
 ***
 ***   Descrizione:
 ***     Recupera dal file interfaccia (.i) le variabili di ingresso, stato e 
 ***     algebriche 
 ***/
ifile_variabili( fp, variabili, numero_stati, numero_uscite, numero_ingressi )
FILE *fp;
StructVars *variabili;
int numero_stati, numero_uscite, numero_ingressi;
{
    char buffer[100];
    int i;

    if (fgets( buffer, 100, fp ) == NULL)    /* salta la riga '****' */
       return(-1);
    for (i=0 ; i<numero_stati ; i++)
    {
       if (fgets( buffer, 100, fp ) == NULL)
          return(-1);
       sscanf(buffer,"%s %s %[^\n]", variabili[i].nome, variabili[i].norm,
                                     variabili[i].descr);
    }

    if (fgets( buffer, 100, fp ) == NULL)    /* salta la riga '****' */
       return(-1);
    for (i=numero_stati ; i<numero_uscite+numero_stati ; i++)
    {
       if (fgets( buffer, 100, fp ) == NULL)
          return(-1);
       sscanf(buffer,"%s %s %[^\n]", variabili[i].nome, variabili[i].norm,
                                     variabili[i].descr);
    }

    if (fgets( buffer, 100, fp ) == NULL)    /* salta la riga '****' */
       return(-1);
    for (i=numero_stati+numero_uscite ; 
         i<numero_ingressi+numero_stati+numero_uscite ; i++)
    {
       if (fgets( buffer, 100, fp ) == NULL)
          return(-1);
       sscanf(buffer,"%s %s %[^\n]", variabili[i].nome, variabili[i].norm,
                                     variabili[i].descr);
    }
    return(0);
}

/*** ifile_dati_geometrici( fp, dati_f14, numero_dati )
 ***   Parametri:
 ***     FILE *fp      : file pointer interfaccia (.i)
 ***     StructVars *dati_f14: struttura dati geometrici e fisici che viene
 ***                           letta dal file (uscita).
 ***     int numero_dati : numero dati geometrici e fisici 
 ***
 ***   Descrizione:
 ***     Legge i dati geometrici e fisici dal file interfaccia (.i)
 ***/
ifile_dati_geometrici( fp, dati_f14, numero_dati )
FILE *fp;
StructDati *dati_f14;
int numero_dati;
{
    char buffer[100];
    int i;

    if (fgets( buffer, 100, fp ) == NULL)    /* salta la riga '****' */
       return(-1);
    for (i=0 ; i<numero_dati ; i++)
    {
       if (fgets( buffer, 100, fp ) == NULL)
          return(-1);
/* 16-1-95 Micheletti 
       sscanf(buffer, "%s %s\n", dati_f14[i].sigla, dati_f14[i].nome);
*/
/* 29-1-96
       sscanf(buffer, "%s %s\n", dati_f14[i].nome, dati_f14[i].sigla);
*/

       strncpy(dati_f14[i].nome,buffer,8);

       sscanf(buffer+10,"%s",dati_f14[i].sigla);
          
    }

    return(0);
}

/*** ifile_jacobiano( fp, tipo_jacobiano, jactoggstruct, num_coef )
 ***   Parametri:
 ***     FILE *fp; : puntatore file interfaccia (.i)
 ***     char tipo_jacobiano : tipo jacobiano (numerico o analitico)
 ***                           (uscita)
 ***     JacToggStruct jactoggstruct[][] : topologia jacobiano (uscita).
 ***     int num_coef : numero coefficienti jacobiano (uscita).
 ***
 ***   Descrizione:
 ***     Legge dal file interfaccia il tipo e la topologia dello jacobiano.
 ***/
ifile_jacobiano( fp, tipo_jacobiano, jactoggstruct, num_coef )
FILE *fp;
byte *tipo_jacobiano;
JacToggStruct  jactoggstruct[MAX_EQUAZIONI][MAX_VARIABILI_IN_OUT];
int *num_coef;
{
   char buffer[100];
   int i,j, tipo;

   *num_coef = 0;

   if (fgets( buffer, 100, fp ) == NULL)    /* salta la riga '****' */
      return(-1);
   fscanf(fp,"%d\n", &tipo);

   *tipo_jacobiano = (byte) tipo;

   if (fgets( buffer, 100, fp ) == NULL)    /* salta la riga '****' */
      return(-1);
   while (fgets(buffer, 100, fp) != NULL && strncmp(buffer,"****",4))
   {
      sscanf(buffer,"%d %d", &i, &j);
      jactoggstruct[i][j].jac_yes = True;
      (*num_coef)++;
   }

   return(0);
}

/*** ifile_subI2( fp, dichI2, codiceI2 )
 *** Parametri :
 ***    FILE *fp : file interfaccia
 ***    char **dichI2 : dichiarazione variabili (uscita)
 ***    char **codiceI2 : codice utente (uscita)
 ***
 *** Descrizione:
 ***    Recupera dal file interfaccia la dichiarazione ed il codice utente
 ***    relativi alla subroutine FORTRAN I2.
 ***/
ifile_subI2( fp, dichI2, codiceI2 )
FILE *fp;
char **dichI2,**codiceI2;
{
   da_file_a_buffer(fp, dichI2);
   da_file_a_buffer(fp, codiceI2);

   return(0);
}

/*** ifile_subJC( fp, dichJC, codiceJC, jactoggstruct, num_equazioni,
 ***		      num_variabili )
 *** Parametri :
 ***    FILE *fp : file interfaccia
 ***    char **dichJC : dichiarazione variabili (uscita)
 ***    char **codiceJC : codice utente (uscita)
 ***    char jactoggstruct[][] : coefficienti jacobiano (uscita)
 ***    int  num_equazioni : numero equazioni
 ***    int  num_variabili : numero variabili (stato, algebriche, ingresso)
 ***
 *** Descrizione:
 ***    Recupera dal file interfaccia la dichiarazione, il codice utente e la
 ***    parte guidata dei coefficienti dello jacobiano relativi alla
 ***    subroutine JC.
 ***/
ifile_subJC( fp, dichJC, codiceJC, jactoggstruct, num_equazioni,
                 num_variabili )
FILE *fp;
char **dichJC, **codiceJC;
JacToggStruct jactoggstruct[MAX_EQUAZIONI][MAX_VARIABILI_IN_OUT];
int num_equazioni, num_variabili;
{
   int i,j;
   char buffer[100], esci = 0;

   da_file_a_buffer(fp, dichJC);
   da_file_a_buffer(fp, codiceJC);
   
   if (fgets(buffer,100,fp) == NULL)
      return(-1);
   for (i=0 ; i<num_equazioni && !esci ; i++)
      for (j=0 ; j<num_variabili && !esci ; j++)
         if (jactoggstruct[i][j].jac_yes)
            if (da_file_a_buffer(fp, &jactoggstruct[i][j].stringa) == 1)
               esci = 1;

   return(0);
}

/*** ifile_subMOD( fp, dichMOD, codiceMOD, residuiMOD, num_eq )
 *** Parametri :
 ***    FILE *fp : file interfaccia
 ***    char **dichMOD : dichiarazione variabili (uscita)
 ***    char **codiceMOD : codice utente (uscita)
 ***    char **residuiMOD : residui (uscita)
 ***    int  num_eq : numero equazioni del modulo 
 ***
 *** Descrizione:
 ***    Recupera dal file interfaccia la dichiarazione, il codice utente e la
 ***    parte guidata dei residui relativi alla subroutine <nome modulo>.
 ***/
ifile_subMOD( fp, dichMOD, codiceMOD, residuiMOD, num_eq )
FILE *fp;
char **dichMOD, **codiceMOD, *residuiMOD[];
int num_eq;
{
   int i;
   char buffer[100];

   da_file_a_buffer(fp, dichMOD);
   da_file_a_buffer(fp, codiceMOD);

   if (fgets(buffer,100,fp) == NULL)
      return(-1);
   for ( i=0 ; i < num_eq ; i++ )
      if (da_file_a_buffer(fp, &residuiMOD[i]) == 1)
         break;

   return(0);
}

/*** ifile_subD1( fp, signeq, uniteq, cosnor, num_eq )
 *** Parametri :
 ***    FILE *fp : file interfaccia
 ***    char **signeq : significato delle equazioni (uscita)
 ***    char **uniteq : unita di misura (uscita)
 ***    char **cosnor : costanti di normalizzazione (uscita)
 ***    int  num_eq : numero equazioni del modulo 
 ***
 *** Descrizione:
 ***    Recupera dal file interfaccia il significato, l'unita di misura e la 
 ***    costante di normalizzazione di ogni equazione (subroutine D1).
 ***/
ifile_subD1( fp, signeq, uniteq, cosnor, num_eq )
FILE *fp;
char *signeq[MAX_EQUAZIONI], *uniteq[MAX_EQUAZIONI], *cosnor[MAX_EQUAZIONI];
int num_eq;
{
   int i;
   char buffer[100];

   for ( i=0 ; i < num_eq ; i++ )
   {
       if (fgets(buffer, 100, fp) == NULL || !strncmp(buffer,"****",4))
          break;

       signeq[i] = (char *) malloc(51 * sizeof(char));
       strncpy(signeq[i], buffer, 50);
       signeq[i][50] = '\0';
       if (Empty(signeq[i]))
          strcpy(signeq[i],"");

       uniteq[i] = (char *) malloc(7 * sizeof(char));
       strncpy(uniteq[i], buffer+51, 6);
       uniteq[i][6] = '\0';
       if (Empty(uniteq[i]))
          strcpy(uniteq[i],"");

       cosnor[i] = (char *) malloc(7 * sizeof(char));
       strncpy(cosnor[i],buffer+58, 6);
       cosnor[i][6] = '\0';
       if (Empty(cosnor[i]))
          strcpy(cosnor[i],"");
   }
   return(0);
}

/*** da_file_a_buffer(fp, varbuf)
 ***   Parametri:
 ***     FILE *fp : file sorgente
 ***     char **varbuf : puntatore al buffer;
 ***
 ***   Descrizione:
 ***     La funzione recupera un testo dal file e lo inserisce in un buffer
 ***     dimensionato automaticamente ad hoc. Il loop di inserimento si
 ***     interrompe quando si incontra la fine del file, se si incontra la
 ***     stringa "****" o la stringa "++++".
 ***/
da_file_a_buffer(fp, varbuf)
FILE *fp;
char **varbuf;
{
   char buffer[100];
   int size = 1;

   while (fgets(buffer, 100, fp) != NULL && strncmp(buffer,"****",4) &&
          strncmp(buffer,"++++",4))
   {
       size += strlen(buffer);

    /* nuovo dimensionamento */
       *varbuf = (char *) realloc(*varbuf, size * sizeof(char));
       if (*varbuf == NULL)
          fprintf(stderr,"memoria esaurita ...\n");

    /* la prima volta si deve fare strcpy() */
       if (size-1 == strlen(buffer))
          strcpy(*varbuf, buffer); 
       else
          strcat(*varbuf, buffer);
   }

/* toglie l'ultimo \n */
   if (size > 1)
      *((*varbuf)+size-2) = '\0';

   if (strncmp(buffer,"++++",4) == 0)
      return(2);
   else
      return(1);  /* "****" oppure fine file */
}

/*** void genmodI2(fp, fpi, nome_modulo, titolo_esteso, dati, numero_dati,
 ***                   variabili, numero_variabili)
 ***   Parametri:
 ***     FILE *fp  : file di output
 ***     char *nome_modulo : nome del modulo (4 char.)
 ***     char *titolo_esteso : descrizione del modulo
 ***     StructDati dati[] : dati geometrici del modulo
 ***     int numero_dati : numero dati geoemtrici del modulo
 ***     StructVars variabili : variabili del modulo (stato,uscita,ingresso)
 ***     int numero_variabili : numero variabili del modulo.
 ***     char *dich_utente : dichiarazione inserita dall'utente in librarian
 ***     char *cod_utente : codice inserita dall'utente in librarian
 ***
 ***   Descrizione:
 ***     Generazione della subroutine I2 (sezione DATI).
 ***/
void genmodI2(fp, nome_modulo, titolo_esteso, dati, numero_dati,
                  variabili, numero_variabili, dich_utente, cod_utente)
FILE *fp;
char *nome_modulo, *titolo_esteso;
StructDati dati[];
int numero_dati;
StructVars variabili[];
int numero_variabili;
char *dich_utente, *cod_utente;
{
   int i;
   char buffer[100];

   fprintf(fp,
           "      SUBROUTINE %sI2 (IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,\n",
           nome_modulo);
   fprintf(fp,
           "     $                    IBL1,IBL2,IER,CNXYU,TOL)\n");
   fprintf(fp,"C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)");
   fprintf(fp,"                             !DBLE\n");
   fprintf(fp,"C\n");
   fprintf(fp,"      REAL VAR(MX1,2)\n");
   fprintf(fp,"      DIMENSION XYU(*),DATI(*),CNXYU(*),TOL(*)\n");

   dichiaraI2_common(fp);

   fprintf(fp,"      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE\n");

/*********************************************************************/
/* inserimento della dichiarazione variabili definita dall'utente in */
/* librarian 							     */
/*********************************************************************/


/* variabili automatiche */ 
   fprintf(fp,"C\n");
   dich_variabili_e_dati(fp, dati, numero_dati, variabili, numero_variabili);

/* variabili utente */ 
   fprintf(fp,"C\n");
   fprintf(fp,"C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE\n");
   fprintf(fp,"C--- (LIBRARIAN)\n");
   fprintf(fp,"C\n");

   da_buffer_a_fileFTN(fp,"",dich_utente,0);
   
   fprintf(fp,"C\n");
   fprintf(fp,"C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE\n");
   fprintf(fp,"C\n");

/*** questa chiamata e' stata spostata prima delle variabili utente  *
   16-1-95 Micheletti
   dich_variabili_e_dati(fp, dati, numero_dati, variabili, numero_variabili);
***/

   fprintf(fp,"C---%s\n",titolo_esteso);
   fprintf(fp,"C\n");
   fprintf(fp,"      GO TO(100,200), IFUN\n");
   fprintf(fp,"C\n");
   if ( numero_dati > 0 )
   {
      fprintf(fp,"  100 WRITE(14,500) '%-8s'\n",dati[0].nome);
      for ( i = 1 ; i <= numero_dati-1 ; i++ )
         if ( i % MAX_DATI_FORMAT == 0 )
            fprintf(fp,"      WRITE(14,500) '%-8s'\n", dati[i].nome);
         else
            fprintf(fp,"     $             ,'%-8s'\n", dati[i].nome);
      fprintf(fp,"      RETURN\n");
   }
   else
      fprintf(fp,"  100 RETURN\n");

   fprintf(fp,"C\n");
   fprintf(fp,"C---lettura e memorizzazione dati\n");
   fprintf(fp,"C\n");
   fprintf(fp,"  200 READ(14,501)\n");
   if ( numero_dati > 0 )
   {
      fprintf(fp,"      READ(14,501) %s\n",dati[0].sigla);
      for ( i = 1 ; i <= numero_dati-1 ; i++ )
      {
         if ( i % MAX_DATI_FORMAT == 0 )
            fprintf(fp,"      READ(14,501) %s\n",dati[i].sigla);
         else
            fprintf(fp,"     $            ,%s\n",dati[i].sigla);
      }
   }
   fprintf(fp,"C\n");
   fprintf(fp,"  500 FORMAT(3(4X,A8,' =',10X,'*'))\n");
   fprintf(fp,"  501 FORMAT(3(14X,F10.0,1X))\n");
   fprintf(fp,"C\n");

/*********************************************************************/
/* inserimento del codice definito dall'utente in librarian          */
/*********************************************************************/

/****************************
   fprintf(fp,"C\n");
   fprintf(fp,"C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE\n");
   fprintf(fp,"C--- (LIBRARIAN)\n");
   fprintf(fp,"C\n");

   da_buffer_a_fileFTN(fp,"",cod_utente,0);
   
   fprintf(fp,"C\n");
   fprintf(fp,"C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE\n");
*************************/

/* mwmorizzazione dati */

   fprintf(fp,"C\n");
   for ( i = 0 ; i <= numero_dati-1 ; i++ )
      if ( i == 0 )
         fprintf(fp,"      DATI(ID2   ) = %s\n",dati[i].sigla);
      else
         fprintf(fp,"      DATI(ID2+%2d) = %s\n",i,dati[i].sigla);
   if ( numero_dati > 0 )
      fprintf(fp,"      ID2 = ID2+%d\n",numero_dati-1);
   else
      fprintf(fp,"      ID2 = ID1\n");


/*** questa parte e' stata spostata orima della memorizzazione dei dati 
  16-1-95 Micheletti
  ma rimessa qui l'1-2-95 su richiesta di Spelta

   inserimento del codice definito dall'utente in librarian          
**************/

   fprintf(fp,"C\n");
   fprintf(fp,"C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE\n");
   fprintf(fp,"C--- (LIBRARIAN)\n");
   fprintf(fp,"C\n");

   da_buffer_a_fileFTN(fp,"",cod_utente,0);
   
   fprintf(fp,"C\n");
   fprintf(fp,"C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE\n");

   fprintf(fp,"C\n");
   fprintf(fp,"C---costanti di normalizzazione\n");
   fprintf(fp,"C\n");
   for ( i = 0 ; i <= numero_variabili-1 ; i++ )
      if ( i == 0 )
         fprintf(fp,"      CNXYU(IV1   ) = %s\n",variabili[i].norm);
      else
         fprintf(fp,"      CNXYU(IV1+%2d) = %s\n",i,variabili[i].norm);
   fprintf(fp,"C\n");
   fprintf(fp,"      RETURN\n");
   fprintf(fp,"      END\n");
}

/*** void genmodC1(fp, nome_modulo, titolo_esteso, tipo_jacobiano,
 ***                   dati, numero_dati, variabili, numero_variabili)
 ***   Parametri:
 ***     FILE *fp : file di output
 ***     char *nome_modulo : nome del modulo (4 char.)
 ***     char *titolo_esteso : descrizione del modulo
 ***     char tipo_jacobiano : tipo jacobiano (numerico o analitico)
 ***     StructDati dati[] : dati geometrici del modulo
 ***     int numero_dati : numero dati geometrici del modulo
 ***     StructVars variabili : variabili del modulo (stato,uscita,ingresso)
 ***     int numero_variabili : numero variabili del modulo.
 ***
 ***   Descrizione:
 ***     Genera il codice relativo alla subroutine C1.
 ***/
void genmodC1(fp, nome_modulo, titolo_esteso, tipo_jacobiano,
                  dati, numero_dati, variabili, numero_variabili)
FILE *fp;
char *nome_modulo, *titolo_esteso;
byte tipo_jacobiano;
StructDati dati[];
int numero_dati;
StructVars variabili[];
int numero_variabili;
{
   fprintf(fp,
   "      SUBROUTINE %sC1 (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)\n",
          nome_modulo);
   fprintf(fp, "C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE\n");
   fprintf(fp,"C\n");
   fprintf(fp,"      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)\n");

   dichiara_common(fp);

   fprintf(fp,"      EXTERNAL %s\n",nome_modulo);

   dich_variabili_e_dati(fp, dati, numero_dati, variabili, numero_variabili);

   fprintf(fp,"C---%s\n",titolo_esteso);
   fprintf(fp,"C\n");
   fprintf(fp,"      GO TO(100,200,300),IFUN\n");
   fprintf(fp,"C\n");
   fprintf(fp,"C---topologia jacobiano\n");
   fprintf(fp,"C\n");
   fprintf(fp,"  100 CONTINUE\n");
   fprintf(fp,
           "      CALL %sJC (1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)\n",
           nome_modulo);
   fprintf(fp,"C\n");
   fprintf(fp,"      RETURN\n");
   fprintf(fp,"C\n");
   fprintf(fp,"C---calcolo residui\n");
   fprintf(fp,"C\n");
   fprintf(fp,"  200 CALL %s (IFUN,IXYU,XYU,IPD,DATI,RNI)\n", nome_modulo);
   fprintf(fp,"      RETURN\n");
   fprintf(fp,"C\n");
   fprintf(fp,"C---calcolo jacobiano\n");
   fprintf(fp,"C\n");
   fprintf(fp,"C      jacobiano analitico CALL %sJC (2,...\n", nome_modulo);
   fprintf(fp,"C\n");
   fprintf(fp,"C      jacobiano numerico  CALL %sJC (3,...\n", nome_modulo);
   fprintf(fp,"C\n");
   fprintf(fp,"C$*$\n");   /* Parte modificabile dall' utente     */
   fprintf(fp,"  300 CONTINUE\n");
   if ( tipo_jacobiano == ANALYTICAL )
      fprintf(fp,
              "      CALL %sJC (2,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)\n",
              nome_modulo);
   else
      fprintf(fp,
              "      CALL %sJC (3,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)\n",
              nome_modulo);
   fprintf(fp,"C\n");
   fprintf(fp,"      RETURN\n");
   fprintf(fp,"      END\n");
}

/*** void genmodJC(fp, nome_modulo, dati, numero_dati, 
 ***                   variabili, numero_variabili,
 ***                   numero_stati, numero_uscite, jactoggstruct,
 ***                   dich_utente, cod_utente, jactoggstruct )
 ***   Parametri:
 ***     FILE *fp : file di output
 ***     char *nome_modulo : nome del modulo (4 char.)
 ***     StructDati dati[] : dati geometrici del modulo
 ***     int numero_dati : numero dati geometrici del modulo
 ***     StructVars variabili : variabili del modulo (stato,uscita,ingresso)
 ***     int numero_variabili : numero variabili del modulo.
 ***     int numero_stati : numero variabili di stato del modulo.
 ***     int numero_uscite : numero variabili di uscita del modulo.
 ***     JacToggStruct jactoggstruct[][] : topologia jacobiano
 ***     char *dich_utente : dichiarazione inserita dall'utente in librarian
 ***     char *cod_utente : codice inserito dall'utente in librarian
 ***
 ***   Descrizione:
 ***     Genera il codice relativo alla subroutine JC (sezione JACOBIANO).
 ***/
void genmodJC(fp, nome_modulo, dati, numero_dati, variabili, numero_variabili,
                  numero_stati, numero_uscite, jactoggstruct, 
                  dich_utente, cod_utente )
FILE *fp;
char *nome_modulo;
StructDati dati[];
int numero_dati;
StructVars variabili[];
int numero_variabili, numero_stati, numero_uscite;
JacToggStruct jactoggstruct[MAX_EQUAZIONI][MAX_VARIABILI_IN_OUT];
char *dich_utente, *cod_utente;
{
   int i,j;
   char *tipo_equazione, buffer[100];

   fprintf(fp,
   "      SUBROUTINE %sJC (IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)\n",
          nome_modulo);
   fprintf(fp,"C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)");
   fprintf(fp,"                             !DBLE\n");
   fprintf(fp,"C\n");
   fprintf(fp,"      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)\n");

   dichiara_common(fp);

   fprintf(fp,"      EXTERNAL %s\n",nome_modulo);

/************************************************************************/
/* inserimento della dichiarazione variabili definita dall'utente in 	*/
/* librarian            						*/
/************************************************************************/

   fprintf(fp,"C\n");
   fprintf(fp,"C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE\n");
   fprintf(fp,"C--- (LIBRARIAN)\n");
   fprintf(fp,"C\n");

   da_buffer_a_fileFTN(fp,"",dich_utente,0);
   
   fprintf(fp,"C\n");
   fprintf(fp,"C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE\n");
   fprintf(fp,"C\n");

   dich_variabili_e_dati(fp, dati, numero_dati, variabili, numero_variabili);

   fprintf(fp,"      GOTO (1,2,3), IFUN\n");

   fprintf(fp,"C\n");
   fprintf(fp,"C---topologia jacobiano\n");
   fprintf(fp,"C\n");
   fprintf(fp,"    1 CONTINUE\n");

/* La matrice topologica non viene azzerata poiche' questa operazione */
/* viene gia' eseguita dal nucleo del lego. */

   genera_topologia(fp, variabili, numero_variabili, numero_stati,
                        numero_uscite, jactoggstruct);

   fprintf(fp,"C\n");
   fprintf(fp,"      RETURN\n");
   fprintf(fp,"C\n");
   fprintf(fp,"C     calcolo jacobiano analitico\n");
   fprintf(fp,"C\n");
   fprintf(fp,"    2 CONTINUE\n");
   for (i = 0 ; i <= numero_variabili-1 ; i++)
      if ( i == 0 )
         fprintf(fp,"      %-6s = XYU(IXYU   )\n",variabili[i].nome);
      else
         fprintf(fp,"      %-6s = XYU(IXYU+%2d)\n",variabili[i].nome,i);
   fprintf(fp,"C\n");
   for (i = 0 ; i <= numero_dati-1 ; i++)
      if ( i == 0 )
         fprintf(fp,"      %-6s = DATI(IPD   )\n",dati[i].sigla);
      else
         fprintf(fp,"      %-6s = DATI(IPD+%2d)\n",dati[i].sigla,i);
   fprintf(fp,"C\n");

/************************************************************************/
/* inserimento del codice utente definita dall'utente in librarian      */
/************************************************************************/

   fprintf(fp,"C\n");
   fprintf(fp,"C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE\n");
   fprintf(fp,"C--- (LIBRARIAN)\n");
   fprintf(fp,"C\n");

   da_buffer_a_fileFTN(fp,"",cod_utente,0);
   
   fprintf(fp,"C\n");
   fprintf(fp,"C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE\n");
   fprintf(fp,"C\n");

/***************************************************/
/* parte guidata di librarian per la subroutine JC */
/***************************************************/

   fprintf(fp,"C$*$\n");  /* Inizio zona da completare da parte dell' utente */
   for ( i = 1 ; i <= numero_stati+numero_uscite ; i++ )
   {
      if ( i <= numero_stati )
         tipo_equazione = "di stato";
      else
         tipo_equazione = "algebrica";
      fprintf(fp,"C\n");
      fprintf(fp,"C--derivata del residuo n. %2d (equazione %s)   *******\n",
              i,tipo_equazione);

      for ( j = 1 ; j <= numero_variabili ; j++ )
         if ( jactoggstruct[i-1][j-1].jac_yes )
         {
            fprintf(fp,"C     --- rispetto alla variabile %s\n",
                       variabili[j-1].nome);
            if (jactoggstruct[i-1][j-1].stringa == NULL)
               fprintf(fp,"C      AJAC(%d,%d) = \n",i,j);
            else
            {
               sprintf(buffer, "      AJAC(%d,%d) = ", i, j);
               da_buffer_a_fileFTN(fp,buffer,jactoggstruct[i-1][j-1].stringa,1);
            }
         } /* <- if */
   } /* <- for */

   fprintf(fp,"C\n");
   fprintf(fp,"      RETURN\n");
   fprintf(fp,"C\n");
   fprintf(fp,"C---calcolo jacobiano numerico\n");
   fprintf(fp,"C\n");
   fprintf(fp,"    3 CONTINUE\n");
   fprintf(fp,"C\n");
   fprintf(fp,"      NSTATI = %d\n",numero_stati);
   fprintf(fp,"      NUSCIT = %d\n",numero_uscite);
   fprintf(fp,"      NINGRE = %d\n",
              numero_variabili-(numero_stati+numero_uscite));
   fprintf(fp,"      EPS    = 1.E-3\n");
   fprintf(fp,"      EPSLIM = 1.E-4\n");
   fprintf(fp,"      CALL NAJAC (AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,\n");
   fprintf(fp,"     $            NSTATI,NUSCIT,NINGRE,EPS,EPSLIM,%s)\n",
	      nome_modulo);
   fprintf(fp,"      RETURN\n");
   fprintf(fp,"      END\n");
}

/*** void genmodMOD(fp, nome_modulo, titolo_esteso, dati, numero_dati,
 ***                    variabili, numero_variabili,numero_stati,numero_uscite,
                        dich_utente, cod_utente, residui_utente)
 ***   Parametri:
 ***     FILE *fp : file di output
 ***     char *nome_modulo : nome del modulo (4 char.)
 ***     char *titolo_esteso : descrizione del modulo
 ***     StructDati dati[] : dati geometrici del modulo
 ***     int numero_dati : numero dati geoemtrici del modulo
 ***     StructVars variabili : variabili del modulo (stato,uscita,ingresso)
 ***     int numero_variabili : numero variabili del modulo.
 ***     int numero_stati : numero variabili di stato del modulo.
 ***     int numero_uscite : numero variabili di uscita del modulo.
 ***     char *dich_utente : dichiarazione inserita dall'utente in librarian
 ***     char *cod_utente : codice inserito dall'utente in librarian
 ***     char **residui_utente : residui equazioni inseriti dall'utente in
 ***                             librarian
 ***
 ***   Descrizione:
 ***     Generazione del codice FORTRAN relativa alla subroutine <nome_modulo>
 ***     (sezione RESIDUI).
 ***/
void genmodMOD(fp, nome_modulo, titolo_esteso, dati, numero_dati,
                   variabili, numero_variabili, numero_stati, numero_uscite,
                   dich_utente, cod_utente, residui_utente)
FILE *fp;
char *nome_modulo, *titolo_esteso;
StructDati dati[];
int numero_dati;
StructVars variabili[];
int numero_variabili, numero_stati, numero_uscite;
char *dich_utente, *cod_utente, *residui_utente[];
{
   int i;
   char *tipo_equazione, buffer[100];

   fprintf(fp,"      SUBROUTINE %s (IFUN,IXYU,XYU,IPD,DATI,RNI)\n",nome_modulo);
   fprintf(fp,"C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)");
   fprintf(fp,"                             !DBLE\n");

   dichiara_common(fp);

   fprintf(fp,"      DIMENSION XYU(*),DATI(*),RNI(*)\n");

/************************************************************************/
/* inserimento della dichiarazione variabili definita dall'utente in 	*/
/* librarian            						*/
/************************************************************************/

   fprintf(fp,"C\n");
   fprintf(fp,"C--- INIZIO DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE\n");
   fprintf(fp,"C--- (LIBRARIAN)\n");
   fprintf(fp,"C\n");

   da_buffer_a_fileFTN(fp,"",dich_utente,0);
   
   fprintf(fp,"C\n");
   fprintf(fp,"C--- FINE DICHIARAZIONE VARIABILI DA PARTE DELL'UTENTE\n");
   fprintf(fp,"C\n");

   dich_variabili_e_dati(fp,dati,numero_dati,variabili,numero_variabili);

   fprintf(fp,"C---%s\n",titolo_esteso);
   fprintf(fp,"C   calcolo residui\n");
   fprintf(fp,"C\n");
   fprintf(fp,"C---decodifica variabili e dati\n");
   fprintf(fp,"C\n");
   for (i = 0 ; i <= numero_variabili-1 ; i++)
      if ( i == 0 )
         fprintf(fp,"      %-6s = XYU(IXYU   )\n",variabili[i].nome);
      else
         fprintf(fp,"      %-6s = XYU(IXYU+%2d)\n",variabili[i].nome,i);
   fprintf(fp,"C\n");
   for (i = 0 ; i <= numero_dati-1 ; i++)
      if ( i == 0 )
         fprintf(fp,"      %-6s = DATI(IPD   )\n",dati[i].sigla);
      else
         fprintf(fp,"      %-6s = DATI(IPD+%2d)\n",dati[i].sigla,i);

/************************************************************************/
/* inserimento del codice utente definita dall'utente in librarian      */
/************************************************************************/

   fprintf(fp,"C\n");
   fprintf(fp,"C--- INIZIO INSERIMENTO CODICE DA PARTE DELL'UTENTE\n");
   fprintf(fp,"C--- (LIBRARIAN)\n");
   fprintf(fp,"C\n");

   da_buffer_a_fileFTN(fp,"",cod_utente,0);
   
   fprintf(fp,"C\n");
   fprintf(fp,"C--- FINE INSERIMENTO CODICE DA PARTE DELL'UTENTE\n");
   fprintf(fp,"C\n");

/*************************************************************/
/* parte guidata di librarian per l'assegnazione dei residui */
/*************************************************************/

   fprintf(fp,"C$*$\n");
   fprintf(fp,"C\n");
   fprintf(fp,"C---calcolo residui\n");

   for ( i = 1 ; i <= numero_stati+numero_uscite ; i++ )
   {
      char primo;

      if ( i <= numero_stati )
         tipo_equazione = "di stato";
      else
         tipo_equazione = "algebrica";
      fprintf(fp,"C\n");
      fprintf(fp,"C--residuo n. %2d (equazione %s)   *******\n",
              i, tipo_equazione);

      primo = 1;
      if (residui_utente[i-1] == NULL)
         fprintf(fp,"C      RNI(%d) = \n",i);
      else
      {
          sprintf(buffer,"      RNI(%d) = ",i);
          da_buffer_a_fileFTN(fp,buffer,residui_utente[i-1],1);
      }
   }

   fprintf(fp,"C\n");
   fprintf(fp,"      RETURN\n");
   fprintf(fp,"      END\n");
}

/*** void genmodI3(fp, nome_modulo, variabili, numero_variabili, 
 ***                   numero_stati, numero_uscite )  
 ***   Parametri:
 ***     FILE *fp : file di output
 ***     char *nome_modulo : nome del modulo (4 char.)
 ***     StructVars variabili : variabili del modulo (stato,uscita,ingresso)
 ***     int numero_variabili : numero variabili del modulo.
 ***     int numero_stati : numero variabili di stato del modulo.
 ***     int numero_uscite : numero variabili di uscita del modulo.
 ***
 ***   Descrizione:
 ***     Generazione del codice FORTRAN relativa alla subroutine I3.
 ***/
void genmodI3(fp, nome_modulo, variabili, numero_variabili, 
                  numero_stati, numero_uscite )  
FILE *fp;
char *nome_modulo;
StructVars *variabili;
int numero_variabili, numero_stati, numero_uscite;
{
   int i, j;
   char temp[L_STRINGA_APPOGGIO], *tipo;

   fprintf(fp,"      SUBROUTINE %sI3 (IFO,IOB,DEBL)\n",nome_modulo);
   fprintf(fp,"      PARAMETER (NV=%d)\n",numero_variabili);
   fprintf(fp,"C\n");
   fprintf(fp,"      COMMON/%s01/IBLOC\n",nome_modulo);
   fprintf(fp,"      COMMON/%s02/NCEL,NPAR\n",nome_modulo);
   fprintf(fp,"      CHARACTER*4 IOB, MOD, IBLOC*8, DEBL*80\n");
   fprintf(fp,"      CHARACTER*4 NOMI(NV), TIPI(NV)*2, DESC(NV)*50\n");
   fprintf(fp,"C\n");
   fprintf(fp,"      DATA MOD/'%s'/\n",nome_modulo);
   for (i=1,j=1;i<=numero_variabili;i++,j++)
   {
      if (j==1)
      {
         if (i+19 < numero_variabili)
            sprintf(temp,"%d",i+19);
         else
            strcpy(temp,"NV");
         fprintf(fp,"      DATA (NOMI(I), TIPI(I), DESC(I), I=%d,%s) /\n",
                 i, temp);
      }
      strnleftindent(temp,4,variabili[i-1].nome);
      fprintf(fp,"     $ '%4s',",temp);
      strnleftindent(temp,50,variabili[i-1].descr);
      if (i <= numero_stati)
         tipo="US";
      else if (i <= numero_stati+numero_uscite)
         tipo="UA";
      else
         tipo="IN";
      fprintf(fp,"'%2s','%s'",tipo,temp);
      if (j==20 || i==numero_variabili)
      {
         fprintf(fp,"/\n");
         j=0;
      }
      else
         fprintf(fp,",\n");
   }
   fprintf(fp,"C\n");
   fprintf(fp,"      CALL %sI4(IOB,MOD)\n",nome_modulo);
   fprintf(fp,"      NSTATI = %d\n",numero_stati);
   fprintf(fp,"      NUSCIT = %d\n",numero_uscite);
   fprintf(fp,"      NINGRE = %d\n",
           numero_variabili-(numero_stati+numero_uscite));
   fprintf(fp,"      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL\n");
   fprintf(fp,
           "      WRITE(IFO,3000)(NOMI(I), IOB, TIPI(I), DESC(I), I = 1,NV)\n");
   fprintf(fp,"      RETURN\n");
   fprintf(fp," 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)\n");
   fprintf(fp," 3000 FORMAT(2A4,'  --',A2,'-- ',A)\n");
   fprintf(fp,"      END\n");
}

/*** void genmodI4(fp, nome_modulo)
 ***   Parametri:
 ***     FILE *fp : file di output
 ***     char *nome_modulo : nome del modulo (4 char.)
 ***
 ***   Descrizione:
 ***     Generazione del codice FORTRAN relativa alla subroutine I4.
 ***/
void genmodI4(fp, nome_modulo)
FILE *fp;
char *nome_modulo;
{
   fprintf(fp,"      SUBROUTINE %sI4 (IOB,MOD)\n",nome_modulo);
   fprintf(fp,"      COMMON/%s01/IBLOC\n",nome_modulo);
   fprintf(fp,"      COMMON/%s02/NCEL,NPAR\n",nome_modulo);
   fprintf(fp,"      CHARACTER*4 IOB, MOD, IBLOC*8\n");
   fprintf(fp,"C\n");
   fprintf(fp,"      WRITE(IBLOC,1)MOD,IOB\n");
   fprintf(fp,"    1 FORMAT(2A4)\n");
   fprintf(fp,"      RETURN\n");
   fprintf(fp,"      END\n");
}
/*** void genmodD1(fp, titolo_esteso, variabili, numero_variabili,
 ***                   numero_stati, numero_uscite, jactoggstruct,
 ***                   signeq, uniteq, cosnor )
 ***   Parametri:
 ***     FILE *fp : file di output
 ***     char *nome_modulo : nome del modulo (4 char.)
 ***     char *titolo_esteso : descrizione del modulo
 ***     StructVars variabili : variabili del modulo (stato,uscita,ingresso)
 ***     int numero_variabili : numero variabili del modulo.
 ***     int numero_stati : numero variabili di stato del modulo.
 ***     int numero_uscite : numero variabili di uscita del modulo.
 ***
 ***   Descrizione:
 ***     Generazione del codice FORTRAN relativa alla subroutine D1 
 ***     (significato delle equazioni).
 ***/
void genmodD1(fp, nome_modulo, titolo_esteso, variabili, numero_variabili,
                  numero_stati, numero_uscite, jactoggstruct,
                  signeq, uniteq, cosnor)
FILE *fp;
char *nome_modulo, *titolo_esteso;
StructVars variabili[];
int numero_variabili, numero_stati, numero_uscite;
JacToggStruct jactoggstruct[MAX_EQUAZIONI][MAX_VARIABILI_IN_OUT];
char *signeq[], *uniteq[], *cosnor[];
{
   int i, j;
   char *tipeq;
   char commento;

   fprintf(fp,"      SUBROUTINE %sD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,",
              nome_modulo);
   fprintf(fp,"SYMVAR,XYU,\n", nome_modulo);
   fprintf(fp,"     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,");
   fprintf(fp,"ITOPVA,MXT)\n");
   fprintf(fp,"C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)");
   fprintf(fp,"                             !DBLE\n");
   fprintf(fp,"C\n");
   fprintf(fp,"C----significato delle variabili di uscita\n");
   fprintf(fp,"C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) -");
   fprintf(fp," 50 CAR.\n");
   fprintf(fp,"C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.\n");
   fprintf(fp,"C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN");
   fprintf(fp," STAZIONARIO\n");
   fprintf(fp,"C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER\n");
   fprintf(fp,"C\n");
   fprintf(fp,"C---%s\n",titolo_esteso);
   fprintf(fp,"C\n");
   fprintf(fp,"      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0\n");
   fprintf(fp,"      CHARACTER *8 BLOCCO, SYMVAR(*)\n");
   fprintf(fp,"      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)\n");
   fprintf(fp,"      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)\n");
   fprintf(fp,"C\n");
   fprintf(fp,"C$*$\n");

/* Temporaneamente si suppone che la topologia dello jacobiano in */
/* stazionario sia eguale a quella in transitorio (TOPOL_REGIME = TOPOL) */

/*******************************************************************/
/* parte guidata di librarian per il significato delle equazioni.  */
/*******************************************************************/

   for (i = 0; i < numero_stati+numero_uscite; i++)
   {
      commento = ' ';

      tipeq = (i<numero_stati) ? "DI STATO" : "ALGEBRICA";
      fprintf(fp,"C\nC DATI RELATIVI ALL'EQUAZIONE %s RESIDUO %s\nC\n",
              tipeq, variabili[i].nome);
      fprintf(fp,
              "C---descrizione equazione %s in stazionario (max. 50 car)\n",
              variabili[i].nome);
      fprintf(fp,"%c      SIGNEQ (%2d) ='%s'\nC\n", commento, i+1, 
                 (signeq[i] == NULL) ? "" : signeq[i]);
      fprintf(fp,"C---unita` di misura residuo %s (max. 10 car)\n", 
              variabili[i].nome);
      fprintf(fp,"%c      UNITEQ (%2d) = '%s'\nC\n", commento, i+1, 
                 (uniteq[i] == NULL) ? "" : uniteq[i]);
      fprintf(fp,
              "C---costante di normalizzazione residuo %s in stazionario\n",
              variabili[i].nome);
/* tolti gli apici a %s (Villa) */
      fprintf(fp,"%c      COSNOR (%2d) = %s\nC\n", commento, i+1, 
                 (cosnor[i] == NULL) ? "" : cosnor[i]);
      fprintf(fp,
              "C---topologia jacobiano in stazionario per il residuo %s\n",
              variabili[i].nome);

      for (j = 0; j < numero_variabili; j++)
         if (jactoggstruct[i][j].jac_yes)
         {
            fprintf(fp,"C------dipendenza dalla variabile %s\n", 
                    variabili[j].nome);
            fprintf(fp,"      ITOPVA (%2d,%2d) = 1\n", i+1, j+1);
         }
   }
   fprintf(fp,"      RETURN\n");
   fprintf(fp,"      END\n");
}

/*** void dichiara_common(fp)
 ***   Parametri:
 ***     FILE *fp : file di output (FORTRAN)
 ***
 ***   Descrizione:
 ***     Dichiarazione delle COMMON.
 ***/
void dichiara_common(fp)
FILE *fp;
{
   fprintf(fp,"C\n");
   fprintf(fp,"      LOGICAL KREGIM\n");
   fprintf(fp,"      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0\n");
   fprintf(fp,"      COMMON/REGIME/KREGIM\n");
   fprintf(fp,"      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT");
   fprintf(fp,"                   !SNGL\n");
   fprintf(fp,"C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS");
   fprintf(fp,"                   !DBLE\n");
   fprintf(fp,"      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,");
   fprintf(fp,"ITERT\n");
   fprintf(fp,"C\n");
}

/*** void dichiaraI2_common(fp)
 ***   Parametri:
 ***     FILE *fp : file di output (FORTRAN)
 ***
 ***   Descrizione:
 ***     Dichiarazione delle COMMON subroutine I2.
 ***/
void dichiaraI2_common(fp)
FILE *fp;
{
   fprintf(fp,"C\n");
   fprintf(fp,"      LOGICAL KREGIM\n");
   fprintf(fp,"      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0\n");
   fprintf(fp,"      COMMON/REGIME/KREGIM\n");
   fprintf(fp,"C\n");
}

/*** void dich_variabili_e_dati(fp, dati, numero_dati, 
 ***				    variabili, numero_variabili)
 ***  Parametri:
 ***     FILE *fp : file pointer di uscita (FORTRAN)
 ***     StructDati dati[] : dati geometrici del modulo
 ***     int numero_dati   : numernumero_variabili+numero_dati geoemtrici
 ***     StructVars variabili[] : variabili del modulo (ingresso,uscita e
 ***				  stato)
 ***     int numero_variabili   : numero variabili del modulo.
 ***
 ***  Descrizione:
 ***     Dichiarazione delle variabili e dei dati geometrici del modulo.
 ***/
void dich_variabili_e_dati(fp, dati, numero_dati, variabili, numero_variabili)
FILE *fp;
StructDati dati[];
int numero_dati;
StructVars variabili[];
int numero_variabili;
{
   int i, quante = 0, riga = -1;
   char *simbolo, *p1, *p2;
   char temp_s[MAX_DICHIAR][L_STRINGA_APPOGGIO];
   char temp_d[MAX_DICHIAR][L_STRINGA_APPOGGIO];

   quante = numero_variabili+numero_dati;
   if (numero_variabili+numero_dati)
   {
      fprintf(fp,"C\n");
      for ( i = 0 ; i < numero_variabili+numero_dati ; i++ )
      {
         if ( i < numero_variabili )
            simbolo = variabili[i].nome;
         else
            simbolo = dati[i-numero_variabili].sigla;

         if ( i % 5 == 0 )
         {
            riga++;
            p1 = temp_s[riga];
            p2 = temp_d[riga];
            strcpy (p1, "      REAL ");
            strcpy (p2, "C      DOUBLE PRECISION ");
         }
         strcat (p1, simbolo);
         strcat (p2, simbolo);
         if ( i % 5 == 4 || i == quante-1)
         {
            while (strlen(p1) < 72)
               strcat (p1, " ");
            strcat (p1, "!SNGL");
            while (strlen(p2) < 73)
               strcat (p2, " ");
            strcat (p2, "!DBLE");
         }
         else
         {
            strcat (p1, ", ");
            strcat (p2, ", ");
         }
      }
      for ( i = 0 ; i <= riga ; i++ )
         fprintf(fp,"%s\n", temp_s[i]);
      for ( i = 0 ; i <= riga ; i++ )
         fprintf(fp,"%s\n", temp_d[i]);
   }
   fprintf(fp,"C\n");
}

/*** void genera_topologia(fp, variabili, numero_variabili,
 ***                           numero_stati, numero_uscite, jactoggstruct)
 ***   Parametri:
 ***     FILE *fp : file di output
 ***     StructVars variabili : variabili del modulo (stato,uscita,ingresso)
 ***     int numero_variabili : numero variabili del modulo.
 ***     int numero_stati : numero variabili di stato del modulo.
 ***     int numero_uscite : numero variabili di uscita del modulo.
 ***     JacToggStruct jactoggstruct[][] : topologia dello jacobiano
 ***
 ***   Descrizione:
 ***     Genera il codice relativo alla subroutine JC per la parte riguardante
 ***     la topologia dello jacobiano (parte guidata).
 ***/
void genera_topologia(fp, variabili, numero_variabili,
                          numero_stati, numero_uscite, jactoggstruct)
FILE *fp;
StructVars variabili[];
int numero_variabili, numero_stati, numero_uscite;
JacToggStruct jactoggstruct[MAX_EQUAZIONI][MAX_VARIABILI_IN_OUT];
{
   int i,j;
   char *tipo_equazione, *temp, *num;

   for ( i = 1 ; i <= numero_stati+numero_uscite ; i++ )
   {
      if ( i <= numero_stati )
         tipo_equazione = "di stato";
      else
         tipo_equazione = "algebrica";
      fprintf(fp,"C\n");
      fprintf(fp,"C---equazione n.%d (%s):\n",i,tipo_equazione);
      for ( j = 1 ; j <= numero_variabili ; j++ )
      if ( jactoggstruct[i-1][j-1].jac_yes == 1 )
      {
         temp="dipendenza da";
         fprintf(fp,"C   ---%-12s %s\n",temp,variabili[j-1].nome);
         fprintf(fp,"      AJAC(%d,%d)=1.\n",i,j);
      }
   }
}

/*** void  strnleftindent(resultp, n, originp)
 *** Parametri:
 ***   char *resultp : stringa di caratteri (uscita)
 ***   int n : numero di caratteri.
 ***   char *originp : stringa di caratteri (ingresso)
 ***
 *** Descrizione:
 ***   Riceve il puntatore a stringa (originp) e la larghezza finale (n) della 
 ***   stringa.
 ***   Genera il puntatore a stringa (resultp) in cui appare la stringa
 ***   iniziale disposta a sinistra in un campo di ampiezza n
 ***/

void strnleftindent (resultp, n, originp)
char *resultp,*originp;
int  n;
{
   int i;

   strcpy(resultp,originp);
   if ( strlen(originp) <= n )
   {
      for ( i=strlen(originp) ; i <= n ; i++ )
         *(resultp+i)=' ';
      *(resultp+n)='\0';
   }
   else
      *(resultp+n)='\0';
}

/*** void intesta_subroutine(fp)
 *** Parametri:
 ***   FILE *fp : file pointer FORTRAN
 ***
 *** Descrizione:
 ***   Inserisce tre righe vuote commentate prima di ogni subroutine.
 ***/
void intesta_subroutine(fp)
FILE *fp;
{
   fprintf(fp,"C\n");
   fprintf(fp,"C\n");
   fprintf(fp,"C\n");
}

/*** da_buffer_a_fileFTN(fp, lstring, buffer, flag)
 ***   Parametri:
 ***     FILE *fp : file FORTRAN destinazione
 ***     char *lstring : stringa da riportare a sinistra
 ***     char *buffer  : stringa da riportare
 ***     char flag : indica se bisogna effettuare il ritorno a capo
 ***                 ($,& ecc. come si fa solitamente in FORTRAN)
 ***
 ***   Descrizione:
 ***     Riporta il contentuto del buffer nel file FORTRAN.
 ***/
da_buffer_a_fileFTN(fp, lstring, buffer, flag)
FILE *fp;
char *lstring, *buffer, flag;
{
   char baffer[100], *ptr, *rip, primo = 1;

   if (buffer == NULL)
      return;

   rip = (flag) ? "$ " : " ";
   ptr = buffer;
   while ( *ptr )
   {
      copy_n_car(baffer,ptr,100);
      if (primo)
      {
         fprintf(fp, "      %s%s\n", lstring, baffer);
         primo = 0;
      }
      else
         fprintf(fp, "     %s%s\n", rip, baffer);
      ptr += strlen(baffer);
      if (*ptr == '\n')
         ptr++;
   }
}

/* fine genera_ftn.c */


char *componi_file_modulo(nomefile, nome_mod, tipo_file)
char *nomefile, *nome_mod;
byte tipo_file;
{
   char minus_nome[10];

   strcpy(minus_nome, nome_mod);
   tominus(minus_nome);


   switch (tipo_file) {
     case FILE_FTN:
     strcat(minus_nome,".for");
     break;
     case FILE_IFACE:
     strcat(minus_nome,".i");
     break;
   }
   strcpy(nomefile, minus_nome);

}

tominus(stringa)
char *stringa;
{
   for( ; *stringa ; stringa++ )
      *stringa = tolower(*stringa);
}

/* funzione copy_n_car(str1,str2,n)
  str1 : stringa destinazione        (w)
  str2 : stringa sorgente            (r)
  n    : numero caratteri da copiare (r)
  copia n caratteri della stringa str2 in str1 terminando str1 con il
  terminatore ( '\0' ). Il newline e' considerato fine-stringa. */
copy_n_car(str1,str2,n)
char *str1,*str2;
int n;
{
   while( n-- && *str2 != '\n' && (*(str1++) = *(str2++)));
   *str1='\0';
}

/* funzione Empty(stringa)
 stringa : stringa di caratteri da controllare (r)
 controlla se una stringa e' vuota (cioe' contiene solo blank o tab)
 la stringa viene controllata fino al terminatore '\0' oppure fino al
 carattere di newline '\n' */
int Empty(stringa)
char *stringa;
{
   for(; *stringa && *stringa != '\n';stringa++)
     if( *stringa != ' ' && *stringa != '\t' )
        return(0);
   return(1);
}



main(int argv, char *argc[])
{
 strcpy(nome_modulo, argc[1]);
 if (leggi_file_interfaccia() != 0)
 {
  printf("Cannot read NEWMOD information (check permission).");
 }
 if (genera_fortran(nome_modulo,titolo_esteso) != 0) 
  {
  printf("Cannot generate file .for");
 }
} 

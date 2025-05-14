/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/************************************************************************/
/*
 *
 *  programma per la generazione dei files descrittivi del database 
 *		delle malfunzioni.
 *	Premessa:
 *		i files *.mf devono essere in uno stato congruente (non esistenti
 *		o allineati ai set presenti)
 *		La lettura delle classi viene effettuata dai files *.templ
 *		La lettura delle istanze viene effettuata dai files *.list (stessa radice
 *			dei .templ)
 *		E' quindi previsto 1 solo .list per classe
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#define BASEPATH	"legocad/libut_mmi"
#define MAX_LUN_RIGA 200
#define MAX_CLASSI   100
#define CHIAVE_RICERCA	"varOutput"
#define TOKEN         	"@#V@"
#define PERT_PRINCIPALE "PERT_MALFUNCTION"
#define PERT_SWITCH		"PERT_NOT"

#define FILE_CLASSI		"tipo_comp_malf.mf"
#define FILE_VALORI_CLASSI		"malf_set.mf"
#define FILE_ISTANZE_MALF		"component.mf"

#define MAX_VALORI	20	/* max numero di valori associabili alla var princ.*/
#define MAX_VARSEC	 4	/* max numero di variabili secondarie              */

FILE *FileOpen();
char *estraiRadice();
char *estraiKKS();

int existFile (char *);
int checkClassiEsistenti (FILE *, char *, int *,int *);
int cercaClasseLibera (int *, int );
int alreadyIncluded (char *, char *, char *);
int aggiungiIstanzaMalf (char *, char *, int , char *);



int main (int argc, char *argv[])
{
char homePath[MAX_LUN_RIGA];
int indiceParametro;
int i,k,n;
char filename[MAX_LUN_RIGA];
char fileTempl[MAX_LUN_RIGA];
char radiceFile[MAX_LUN_RIGA];
char fileClassi[MAX_LUN_RIGA];
char fileIstanze[MAX_LUN_RIGA];
char riga[MAX_LUN_RIGA+1];
FILE *fp;
FILE *fpClassi;
FILE *fpIstanze;
char classe[20];
char classeLetta[20];
char temp[20];		/* appoggio temporaneo		*/
char *point;

char valPert[MAX_VALORI][20]; 
char varPrinc[MAX_VALORI][3]; 
char pert[MAX_VALORI][20]; 
char rego[MAX_VALORI][20];

char varSec[MAX_VARSEC][3]; 
char pertSec[MAX_VARSEC][20]; 
char valVarSec[MAX_VARSEC][20]; 

char modRego[20];
char campo[10][50];
int trovata;
int classeGiaEsistente;
int n_varsec;            /* numero variabili secondarie					*/
int n_princ;             /* numero entries per variabile principale	*/
int n_entries;           /* numero di entries totali						*/
int n_classi;            /* numero di classi presenti nel file   		*/
int indxClassi[MAX_CLASSI];
int indx;

char pagina_F[50];
char siglaKKS[50];
char varModTask[50];

	for (i=0; i<argc; i++)
		fprintf (stderr,"Par. %d [%s]\n",i,argv[i]);
/*
 * i parametri in ingresso sono i nomi dei files mal*.templ
 */
	for (indiceParametro=1; indiceParametro<argc; indiceParametro++)
		{
		strcpy (fileTempl,argv[indiceParametro]); 
		strcpy (homePath,getenv("HOME"));
		sprintf (filename,"%s/%s/%s",homePath,BASEPATH,argv[indiceParametro]);
	/*	strcpy (filename,argv[indiceParametro]);  */
		fprintf (stderr,"Esame file %s\n",filename);
		if (!existFile (filename))
			{
			fprintf (stderr,"Il file %s non esiste\n",filename);
			continue;
			}
		if ((fp = fopen (filename,"r")) == NULL)
      	{
      	fprintf (stderr,"Il file %s esiste ma non si apre\n",filename);
			continue;
      	}
/*
 * determino la classe
 */
		for (i=3,k=0; i <= strlen(fileTempl) ;i++,k++)
			{
			classe[k] = fileTempl[i];
			if (( classe[k] == '.') || ( classe[k] == '\0'))
				{
				classe[k] = '\0';
				break;
				}
			}
		fprintf (stderr,"Esamino classe %s \n",classe);

		rewind (fp);
/*
 * inizializzazione var. secondarie
 */
		for (i=0; i<MAX_VARSEC; i++)
			{
			strcpy (varSec[i],"");
			strcpy (pertSec[i],"");
			strcpy (valVarSec[i],"");
			}
		
		n_varsec = 0;  /* numero di variabili secondarie					*/
		n_princ = 0; 	/* entries relative alla variabile principale	*/
		n = 0;			/* conteggio entries										*/

		while (fgets (riga,MAX_LUN_RIGA,fp) != NULL)
      	{
			point = strstr (riga,CHIAVE_RICERCA);
			if (point == NULL)		/* non trovata	*/
				continue;	
/*			fprintf (stderr,"Esamino riga [%s]\n",riga);*/	/* trovata		*/	
/*
 * acquisizione campi
 */
			sscanf (riga,"%s %s %s %s %s %s %s",
							campo[0],campo[1],campo[2],
							campo[3],campo[4],campo[5],campo[6]);

/**			for (i=0; i<7; i++)
				printf ("Campo %d [%s]\n",i,campo[i]);  ***/

			if (strcmp(campo[2],PERT_PRINCIPALE))       /* e' var. secondaria  	*/
				{
/* perturbazione associata    */
         	strcpy (pertSec[n_varsec],campo[2]);
/* variabile secondaria       */
				point = strstr (campo[1],TOKEN);
				for (i=0,k=0;point[strlen(TOKEN)+i] != '\0' ;i++,k++)
               modRego[k] = point[strlen(TOKEN)+i];
            modRego[k] = '\0';
            campo[1][strlen(campo[1])-strlen(TOKEN)-strlen(modRego)] = '\0';
            strcpy (varSec[n_varsec], campo[1]);
 /*           fprintf (stderr,"Var princ: [%s]\n",varSec[n_varsec]); */

/* valore della pert		*/
				strcpy (valVarSec[n_varsec], campo[3]);

				n_varsec ++;
				}
			else												/* var. principale		*/
				{
/*
 * nome modulo rego
 */
				point = strstr (campo[1],TOKEN);
         	if (point == NULL)
                  /* se .templ correttamente configurata non si verifica */
            	{
            	fprintf (stderr,"Riga [%s] Token non presente [%s]\n",
                        riga,TOKEN);
					continue;
            	}
         	for (i=0,k=0;point[strlen(TOKEN)+i] != '\0' ;i++,k++)
            	rego[n_princ][k] = point[strlen(TOKEN)+i];
         	rego[n_princ][k] = '\0';
  /*       	fprintf (stderr,"Rego [%s]\n",rego[n_princ]);   */

/* perturbazione associata    */
         	strcpy (pert[n_princ],campo[2]);
				
/* variabile principale			*/
				campo[1][strlen(campo[1]) -
							strlen(TOKEN)-strlen(rego[n_princ])] = '\0';
				strcpy (varPrinc[n_princ], campo[1]);
/*				fprintf (stderr,"Var princ: [%s]\n",varPrinc[n_princ]);  */
/* valore della pert		*/
				strcpy (valPert[n_princ], campo[3]);

				n_princ ++;
				}

			n++;
			}
		n_entries = n;				/* numero di entries nel file *.templ		*/

/* analisi e stampa dei parametri		*/
/*
 * FILE DELLE CLASSI
 */
      strcpy (fileClassi,FILE_CLASSI);
		fpClassi = FileOpen (fileClassi);
/* verifico se la classe in questione gia' esiste	*/
		classeGiaEsistente = checkClassiEsistenti (fpClassi,classe,
													&n_classi,&indxClassi[0]);
		fclose (fpClassi);
		if (classeGiaEsistente == 1)						/* se gia' esistente		*/
			{		
			fprintf (stderr,"Classe %s gia' in elenco nel file %s\n",
               classe,fileClassi);
			}
		if (classeGiaEsistente > 1)
			{
			fprintf (stderr,"ATTENZIONE: classe %s duplicata in file %s\n",
					classe,fileClassi);
			}
		if (!classeGiaEsistente)
			{
/* aggiungo la classe */
			fpClassi = fopen (fileClassi,"a");
/* cerco un indice libero ( verra' associato anche agli altri files )		*/
			indx = cercaClasseLibera (&indxClassi[0],n_classi);
			sprintf (riga,"%d;%s;;;%s;%s",
							indx,classe,rego[0],varPrinc[0]);
			for (i=0; i<MAX_VARSEC; i++)
				{
				sprintf (riga,"%s;%s;;%s;%s",
									riga,varSec[i],pertSec[i],valVarSec[i]);
				}
			fprintf (fpClassi,"%s\n",riga);
			fflush (fpClassi);
			fclose (fpClassi);
			}

		fprintf (stderr,"Terminato settaggio classi\n");
/*
 * FILE DEI VALORI DELLE CLASSI
 */
		if (!classeGiaEsistente)
         {
			strcpy (fileClassi,FILE_VALORI_CLASSI);
/* eventualmente crea il file */
			fpClassi = FileOpen (fileClassi);
			fclose (fpClassi);
		/* aggiungo la classe */
      	fpClassi = fopen (fileClassi,"a");
/* cerco un indice libero     */
			for (i=0; i<n_princ; i++)
				{
				sprintf (riga,"%s;%d;DESCR. %s",
							valPert[i],indx,valPert[i]);
				fprintf (fpClassi,"%s\n",riga);
				}
			fflush (fpClassi);
      	fclose (fpClassi);
			}
		
		fprintf (stderr,"Terminato settaggio valori classi\n");
/*
 * FILE DELLE ISTANZE
 */
/*
 * apro il file delle istanze 
 */
		strcpy (fileClassi,FILE_ISTANZE_MALF);
/* eventualmente crea il file */
      fpClassi = FileOpen (fileClassi);
		fclose (fpClassi);
/* 
 *  il file di configurazione delle istanze si chiamera' <radice filename>.list
 */
		strcpy (radiceFile,estraiRadice(fileTempl));
		sprintf (fileIstanze,"%s.list",radiceFile);
		fprintf (stderr,"Istanze del file [%s]\n",fileIstanze);

		if (!existFile (fileIstanze))/* non ci sono istanze per questa classe */
			{
			fprintf (stderr,"Classe %s : nessuna istanza prevista\n", classe);
			continue;
			}
		if ((fpIstanze = fopen (fileIstanze,"r")) == NULL)
         {
         fprintf (stderr,"File Istanze %s non utilizzabile\n",fileIstanze);
         perror ("--->");
         continue;
         }
/*
 * leggo il file delle istanze (la prima riga e' l' intestazione)
 */
		fgets (riga,MAX_LUN_RIGA,fpIstanze);
      while (fgets (riga,MAX_LUN_RIGA,fpIstanze) != NULL)
         {
         sscanf (riga,"%s %s %s",
                     campo[0],campo[1],campo[2]);
			sprintf (pagina_F,"%s.pag",campo[0]);
			strcpy (siglaKKS,estraiKKS(campo[1]));
			strcpy (varModTask,campo[2]);
			
			if (!alreadyIncluded (siglaKKS,varModTask,fileClassi))
				aggiungiIstanzaMalf (siglaKKS,varModTask,indx,fileClassi);
			}

		fclose(fpClassi);
		fclose(fpIstanze);

		fprintf (stderr,"Terminato con file %s\n",filename);
		fclose (fp);
		}
}
/**********************************************************/
/*
 * aggiunge una istanza al file delle malfunzioni
 *	Al momento non si sono configurate variabili secondarie 
 *		al di fuori del blocco di appartenenza della variabile primaria,
 *		quindi i codRego, blocco ,task delle var secondarie sono assunte
 *		uguali a quelle delle variabili primarie
 */
int aggiungiIstanzaMalf (char *kks, char *var, int indClasse, char *fname)
{
char riga[MAX_LUN_RIGA];
FILE *fp;

	/* si posiziona alla fine del file */
	fp = fopen (fname,"a");
	sprintf (riga,"%d;Descr;%s;%s;%s;%s;%s;%s\n",
				indClasse,kks,var,var,var,var,var);
/* printf ("aggiungo [%s]\n",riga); */
	fprintf (fp,"%s",riga);
	fclose (fp);
	return (0);
}
/**********************************************************/
/*
 * controlla se la entry e' gia' compresa nel file
 * (il check viene fatto sulla variabile (varModTask)
 */
int alreadyIncluded (char *kks, char *var, char *fname)
{
int i,k;
char riga[MAX_LUN_RIGA];
char varLetta[MAX_LUN_RIGA];
FILE *fp;
	

	fp = fopen (fname,"r");

	while (fgets (riga,MAX_LUN_RIGA,fp) != NULL)
      {
/* printf ("alreadyIncluded : letto [%s]\n",riga);   **/
		for (i=0;riga[i]!=';';i++) ;	/* skip primo campo(classe)			*/
		for (i++;riga[i]!=';';i++) ;  /* skip secondo campo(descrizione)	*/
		for (i++;riga[i]!=';';i++) ;  /* skip terzo campo(KKS)				*/
		for (i++,k=0; ;k++,i++)
			{
			varLetta[k] = riga[i];
			if ((varLetta[k] == ' ')	||
				 (varLetta[k] == '\t')	||
				 (varLetta[k] == '\n')	||
				 (varLetta[k] == '\0'))
				{
				varLetta[k] = '\0';
				break;
				}
			}
/* printf ("check [%s] [%s]\n",varLetta,var);   **/
		if (!strncmp(varLetta,var,strlen(var)))
			{
			fclose (fp);
			return (1);							/* gia' presente							*/
			}
		}
	fclose (fp);
	return (0);									/* new entry								*/
}
/**********************************************************/
/* 
 * ritorna la sigla kks dal formato ..aaaaaaaaaaa????
 *  (2 char iniziali + 11 char KKS + n char dettaglio)
 */
char *estraiKKS (char *s)
{
int i,k;
char *KKS;
	
	KKS = (char *)malloc(strlen(s)+1);
	for (i=2,k=0; k<11; i++,k++)
		KKS[k] = s[i];
	KKS[k] = '\0';
	return (KKS);
}
/**********************************************************/
/*
 * ritorna la stringa corrispondente alla radice del filename
 *	(tutto quanto sta a sinistra del punto)
 */
char *estraiRadice(char *s)
{
char *radix;
int i,k;

	radix = (char *)malloc(strlen(s)+1);
	for (i=0,k=0; ;i++,k++)
		{
		radix[k] = s[i];
		if (radix[k] == '\0')  /* non c' e' estensione		*/
         break;
		if (radix[k] == '.')
			{
			radix[k] = '\0';
			break;
			}
		}
	return (radix);
}
/**********************************************************/
int existFile (char *n)
{
struct stat buffer;

   if (stat(n, &buffer) < 0)     /* non esiste */
      return (0);
   return (1);
}
/**********************************************************/
FILE *FileOpen (char *s)
{
FILE *fp;
      if (!existFile (s))
         {
         fprintf (stderr,"Il file %s non esiste (crea nuovo)\n",s);
         if ((fp = fopen (s,"w")) == NULL)
            {
            fprintf (stderr,"File classi %s non utilizzabile\n",s);
            perror ("--->");
            exit (-1);
            }
         }
      else
         {
         if ((fp = fopen (s,"r+")) == NULL)
            {
            fprintf (stderr,"File classi %s non utilizzabile\n",s);
            perror ("--->");
            exit (-1);
            }
         }
	return (fp);
}
/**********************************************************/
int checkClassiEsistenti (FILE *fp, char *classe, int *n_c,int *indx)
{
char riga[MAX_LUN_RIGA+1];
char temp[20];    /* appoggio temporaneo     */
int found = 0;
char classeLetta[20];
int i,k;

      *n_c=0;       /* contatore delle entries    */
      while (fgets (riga,MAX_LUN_RIGA,fp) != NULL)
         {
         for (i=0; riga[i] != ';'; i++) /* primo campo: indice classe */
            temp[i] = riga[i];
         temp[i] = '\0';
         *(indx+(*n_c)) = atoi(temp);

         for (i++,k=0; riga[i] != ';'; i++,k++)
            classeLetta[k] = riga[i];
         classeLetta[k] = '\0';
         if (!strcmp(classeLetta,classe))    /* esiste gia' */
            found++;             /* continua per ricavare gli indici */
         (*n_c)++;
         }
	return (found);
}
/**********************************************************/
int cercaClasseLibera (int *indxClassi, int n_c)
{
int i,k;
int trovata;
      for (i=0; ;i++)
         {
         trovata = 0;
         for (k=0; k<n_c; k++)
            {
            if (*(indxClassi+k) == i)    /* se c'e' gia' skippa  */
               {
               trovata = 1;
               break;
               }
            }
         if (!trovata)        /* la classe di indice i non esiste */
            return (i);
         }
}

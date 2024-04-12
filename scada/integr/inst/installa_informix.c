/*
   modulo installa_informix.c
   tipo 
   release 1.6
   data 10/14/96
   reserved @(#)installa_informix.c	1.6
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>

#include<db.h>
#include<installa.h>

char *path_input;
char *path_output;
char *path_rtf;
char *path_variabili;

#if defined USE_INFORMIX
static int accoda_tab(char * tabella, char * tabella_ascii);
#endif

extern int usa_informix;
extern int start_informix;

int scarica_informix()
{
#if defined USE_INFORMIX
char *path_locale;
ID_TABLE *tabella;
int i,num_rec;
VAL_RET valore;

if(!start_informix)
	{
	if(!usa_informix)
		return(1);
	}

// recupera il path locale
path_locale = getcwd(NULL,255);
// va nel direttorio di variabili.rtf
if(chdir(path_input)!=0)
         {
         fprintf(stderr,
		"installa_informix: il path [%s] non esiste\n",path_input);
         exit(1);
         }
if(!DbConnect("online","Online"))
        {
        fprintf(stderr,"Errore connessione database\n");
        return(0);
        }

if(!SQLTableToAscii(ALARM_TABLE,ALARM_TABLE,NULL))
        {
        fprintf(stderr,"Errore accesso tabella ALARM\n");
        return(0);
        }
if(!SQLTableToAscii(LOG_TABLE,LOG_TABLE,NULL))
        {
        fprintf(stderr,"Errore accesso tabella LOG\n");
        return(0);
        }
if(!SQLTableToAscii(SCDDBA_TABLE,SCDDBA_TABLE,NULL))
        {
        fprintf(stderr,"Errore accesso tabella SCDDBA\n");
        return(0);
        }
if(!SQLTableToAscii(TAG_TABLE,TAG_TABLE,NULL))
        {
        fprintf(stderr,"Errore accesso tabella TAG\n");
        return(0);
        }
if(!SQLTableToAscii(ALARMTYPE_TABLE,ALARMTYPE_TABLE,NULL))
        {
        fprintf(stderr,"Errore accesso tabella ALARMTYPE\n");
        return(0);
        }
if(!SQLTableToAscii(MEASURE_TABLE,MEASURE_TABLE,NULL))
        {
        fprintf(stderr,"Errore accesso tabella MEASURE\n");
        return(0);
        }
if(!SQLTableToAscii(SCDLBG_TABLE,SCDLBG_TABLE,NULL))
        {
        fprintf(stderr,"Errore accesso tabella SCDLBG\n");
        return(0);
        }
if(!SQLTableToAscii(HDR_TABLE,HDR_TABLE,NULL))
        {
        fprintf(stderr,"Errore accesso tabella HDR\n");
        return(0);
        }
if(!SQLTableToAscii(SCDCONF_TABLE,SCDCONF_TABLE,NULL))
        {
        fprintf(stderr,"Errore accesso tabella SCDCONF\n");
        return(0);
        }
if(!SQLTableToAscii(SCDTAB_TABLE,SCDTAB_TABLE,NULL))
        {
        fprintf(stderr,"Errore accesso tabella SCDTAB\n");
        return(0);
        }

DbDisconnect();

// torna indietro
if(chdir(path_locale)!=0)
         {
         fprintf(stderr,
		"installa_informix: il path [%s] non esiste\n",path_locale);
         exit(1);
         }

// rinomina i file dei tabulati
tabella=OpenTablePath(path_input,LOG_TABLE);
if(!tabella)
{
        fprintf(stderr,"installa_informix: apertura tabella [%s]\n",LOG_TABLE);
        return(0);
}
num_rec=NumRecord(tabella);
for(i=0;i<num_rec;i++)
	{
	char from[255];
	char to[255];

	if(GetVal(tabella,"LOG_NAME",i,&valore)!=1)
          {
          fprintf(stderr,"installa_informix: Errore GetVal LOG_NAME\n");
          return 0;
          }
	sprintf(from,"%s/%s.%d",path_input,LOG_TABLE,i+1);
	sprintf(to,"%s/%s.tcr",path_output,valore.char_val);
	if(rename(from,to)!=0)
	  {
          fprintf(stderr,"installa_informix: Errore rename\n");
          return (0);
          }
	}

CloseTable(tabella);

return(1);
#else
return(1);
#endif
}

int carica_informix()
{
#if defined USE_INFORMIX
char *path_locale;
ID_TABLE *tabella;
int i,num_rec;
VAL_RET valore;

if(!usa_informix)
	return(1);

// recupera il path locale
path_locale = getcwd(NULL,255);
// va nel direttorio di variabili.rtf
if(chdir(path_output)!=0)
         {
         fprintf(stderr,
		"installa_informix: il path [%s] non esiste\n",path_output);
         exit(1);
         }
if(!DbConnect("online","Online"))
        {
        fprintf(stderr,"Errore connessione database\n");
        return(0);
        }

// editaa
if(!accoda_tab("editaa","editaa"))
        {
        fprintf(stderr,"Errore accodamento editaa\n");
        return(0);
        }

// editac
if(!accoda_tab("editac","editac"))
        {
        fprintf(stderr,"Errore accodamento editac\n");
        return(0);
        }

// editas
if(!accoda_tab("editas","editas"))
        {
        fprintf(stderr,"Errore accodamento editas\n");
        return(0);
        }

// editad
if(!accoda_tab("editad","editad"))
        {
        fprintf(stderr,"Errore accodamento editad\n");
        return(0);
        }

// editao
if(!accoda_tab("editao","editao"))
        {
        fprintf(stderr,"Errore accodamento editao\n");
        return(0);
        }

// editda
if(!accoda_tab("editda","editda"))
        {
        fprintf(stderr,"Errore accodamento editda\n");
        return(0);
        }

// editdc
if(!accoda_tab("editdc","editdc"))
        {
        fprintf(stderr,"Errore accodamento editdc\n");
        return(0);
        }

// editds
if(!accoda_tab("editds","editds"))
        {
        fprintf(stderr,"Errore accodamento editds\n");
        return(0);
        }

// editdd
if(!accoda_tab("editdd","editdd"))
        {
        fprintf(stderr,"Errore accodamento editdd\n");
        return(0);
        }

// editdo
if(!accoda_tab("editdo","editdo"))
        {
        fprintf(stderr,"Errore accodamento editdo\n");
        return(0);
        }

// editor
if(!accoda_tab("editor","editor"))
        {
        fprintf(stderr,"Errore accodamento editor\n");
        return(0);
        }

// editst
if(!accoda_tab("editst","editst"))
        {
        fprintf(stderr,"Errore accodamento editst\n");
        return(0);
        }

// editto
if(!accoda_tab("editst","editto"))
        {
        fprintf(stderr,"Errore accodamento editto\n");
        return(0);
        }

// AllarDB
if(!accoda_tab("AllarDB","editAllarDB"))
        {
        fprintf(stderr,"Errore accodamento AllarDB\n");
        return(0);
        }

// AllarLine
if(!accoda_tab("AllarLine","editAllarLin"))
        {
        fprintf(stderr,"Errore accodamento AllarLine\n");
        return(0);
        }

// AllarLiv
if(!accoda_tab("AllarLiv","editAllarLiv"))
        {
        fprintf(stderr,"Errore accodamento AllarLiv\n");
        return(0);
        }

// AllarServ
if(!accoda_tab("AllarServ","editAllarServ"))
        {
        fprintf(stderr,"Errore accodamento AllarServ\n");
        return(0);
        }

// AllarStrat
if(!accoda_tab("AllarStrat","editAllarStr"))
        {
        fprintf(stderr,"Errore accodamento AllarServ\n");
        return(0);
        }

// CPerif
if(!accoda_tab("CPerif","editCPerif"))
        {
        fprintf(stderr,"Errore accodamento CPerif\n");
        return(0);
        }

// ConfigurazioneDB
if(!accoda_tab("ConfigurazioneDB","editConfDB"))
        {
        fprintf(stderr,"Errore accodamento ConfigurazioneDB\n");
        return(0);
        }

// DescriSc
if(!accoda_tab("DescriScheda","editDescriSc"))
        {
        fprintf(stderr,"Errore accodamento DescriScheda\n");
        return(0);
        }

// MisTabK
if(!accoda_tab("MisTabK","editMisTabK"))
        {
        fprintf(stderr,"Errore accodamento MisTabK\n");
        return(0);
        }

// TDIZST
if(!accoda_tab("TDIZST","editTDIZST"))
        {
        fprintf(stderr,"Errore accodamento TDIZST\n");
        return(0);
        }

// TabPeri
if(!accoda_tab("TabPeri","editTabPeri"))
        {
        fprintf(stderr,"Errore accodamento TabPeri\n");
        return(0);
        }

// Tabulati
if(!accoda_tab("Tabulati","editlog"))
        {
        fprintf(stderr,"Errore accodamento TabPeri\n");
        return(0);
        }


// Errori di istallazione
if(!accoda_tab("pointinsterr","PointInstErr"))
        {
        fprintf(stderr,"Errore accodamento TabPeri\n");
        return(0);
        }

DbDisconnect();

// torna indietro
if(chdir(path_locale)!=0)
         {
         fprintf(stderr,
		"installa_informix: il path [%s] non esiste\n",path_locale);
         exit(1);
         }
return(1);
#else
return(1);
#endif
}

#if defined USE_INFORMIX
static int accoda_tab(char * tabella, char * tabella_ascii)
{
if(!SQLClearTable(tabella))
        {
        fprintf(stderr,"Errore cancellazione tabella [%s]\n",tabella);
        return(0);
        }
if(!SQLAsciiToTable(tabella_ascii,tabella))
        {
        fprintf(stderr,"Errore accodamento tabella [%s]\n",tabella);
        return(0);
        }
return(1);
}
#endif

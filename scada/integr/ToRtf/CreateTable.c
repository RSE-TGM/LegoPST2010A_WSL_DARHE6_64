/*
   modulo %M%
   tipo %Y%
   release %I%
   data %G%
   reserved %W%
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern char path_txt[FILENAME_MAX+1];
extern int usa_informix;

int CreateTable()
{
#if defined USE_INFORMIX
char *path_locale;


if(!usa_informix)
        return(1);
printf("Create table\n");

// recupera il path locale
path_locale = getcwd(NULL,FILENAME_MAX);
// va nel direttorio di variabili.rtf
if(chdir(path_txt)!=0)
         {
         fprintf(stderr,
                "installa_informix: il path [%s] non esiste\n",path_txt);
         exit(1);
         }
if(!DbConnect("online","Online"))
        {
        fprintf(stderr,"Errore connessione database\n");
        return(0);
        }

if(!SQLTableToAscii("AllarDB","AllarDB","order by indice"))
        {
        fprintf(stderr,"Errore accesso tabella AllarDB\n");
        return(0);
        }
if(!SQLTableToAscii("AllarLine","AllarLin","order by indice"))
        {
        fprintf(stderr,"Errore accesso tabella AllarLin\n");
        return(0);
        }
if(!SQLTableToAscii("AllarLiv","AllarLiv","order by indice"))
        {
        fprintf(stderr,"Errore accesso tabella AllarLiv\n");
        return(0);
        }
if(!SQLTableToAscii("AllarServ","AllarServ",NULL))
        {
        fprintf(stderr,"Errore accesso tabella AllarServ\n");
        return(0);
        }
if(!SQLTableToAscii("AllarStrat","AllarStr","order by indice"))
        {
        fprintf(stderr,"Errore accesso tabella AllarStrat\n");
        return(0);
        }
if(!SQLTableToAscii("CPerif","CPerif",NULL))
        {
        fprintf(stderr,"Errore accesso tabella CPerif\n");
        return(0);
        }
if(!SQLTableToAscii("ConfigurazioneDB","ConfDB",NULL))
        {
        fprintf(stderr,"Errore accesso tabella ConfDB\n");
        return(0);
        }
if(!SQLTableToAscii("DescriScheda","DescriSc",NULL))
        {
        fprintf(stderr,"Errore accesso tabella DescriSc\n");
        return(0);
        }
if(!SQLTableToAscii("Nomi","Nomi",NULL))
        {
        fprintf(stderr,"Errore accesso tabella Nomi\n");
        return(0);
        }
if(!SQLTableToAscii("MisTabK","MisTabK",NULL))
        {
        fprintf(stderr,"Errore accesso tabella MisTabK\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunAA","PuntAA",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntAA\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunAC","PuntAC",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntAC\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunAS","PuntAS",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntAS\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunAD","PuntAD",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntAD\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunAO","PuntAO",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntAO\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunDA","PuntDA",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntDA\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunDC","PuntDC",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntDC\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunDS","PuntDS",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntDS\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunDD","PuntDD",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntDD\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunDO","PuntDO",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntDO\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunOR","PuntOR",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntOR\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunST","PuntST",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntST\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunTO","PuntTO",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntTO\n");
        return(0);
        }
if(!SQLTableToAscii("tdpunARC","PuntARC",NULL))
        {
        fprintf(stderr,"Errore accesso tabella PuntARC\n");
        return(0);
        }
if(!SQLTableToAscii("TDIZST","TDIZST",NULL))
        {
        fprintf(stderr,"Errore accesso tabella TDIZST\n");
        return(0);
        }
if(!SQLTableToAscii("TabPeri","TabPeri",NULL))
        {
        fprintf(stderr,"Errore accesso tabella TDIZST\n");
        return(0);
        }
if(!SQLTableToAscii("Tabulati","Tabulati",NULL))
        {
        fprintf(stderr,"Errore accesso tabella TDIZST\n");
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

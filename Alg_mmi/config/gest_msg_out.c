/**********************************************************************
*
*	C Source:		gest_msg_out.c
*	Instance:		1
*	Description:	
*	%created_by:	lomgr %
*	%date_created:	Tue Jul 19 11:00:47 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: gest_msg_out.c-5 %  (%full_filespec: gest_msg_out.c-5:csrc:1 %)";
#endif

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
#include <stdarg.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>

/*
 Esecuzione di comando di shell con intercettazione dell'output
 e sua visualizzazione tramite la routine lc_errore
*/
static char riga[1001]; /* la dimensione e' notevole perche' l'output
                           puo' essere composto da comandi di link o
                           di creazione librerie notevolmente lunghi */

static char str[1001],mess[1001];

extern int comm_found;


gest_errore( char * StringaErrore, ... )
{
   va_list args;

   char *str_arg;
   int  int_arg;

   char *fmt, *format, fmt_ch, save_ch;


   /* Il primo parametro contiene la stringa di format. Il numero ed il
    * tipo dei restanti parametri e' determinato dai specificatori di formato
    * contenuti nella stringa.
    */

   format = StringaErrore;

   va_start(args, StringaErrore);

/*
   Costruzione del messaggio di errore
*/
   *mess='\0';

   for ( ; fmt = (char*)strchr ( format, '%' ); format = fmt )
   {
      fmt_ch  = *(++fmt);
      save_ch = *(++fmt);
      *fmt    = '\0';
      switch ( fmt_ch )
      {
         case 's':
                   str_arg = va_arg(args, char *);
                   sprintf ( str, format, str_arg );
                   break;
         case 'd':
                   int_arg = va_arg(args, int);
                   sprintf ( str, format, int_arg );
                   break;
         default:
                   /* sto pippo */
                   break;
      }

      strcat ( mess, str );
      *fmt = save_ch;
   }

   va_end(args);

   strcat ( mess, format );

/*
   Visualizzazione errore.
   Se la config e' attivata senza comandi (comm_found=0) i messaggi
   vengono inviati nell'area messaggi della topLevelShell, altrimenti
   (comm_found!=0) sullo standard output.
*/
   if(comm_found==0)
      show_message(mess);
   else
      printf("%s",mess);

}



esegui_comando(comando)
char *comando;
{
/*
extern ERR_LEVEL err_level;
*/
FILE *fp;
int retval,exit_stat;
signal(SIGCHLD,(SIG_DFL) );
fp=popen(comando,"r");
while(fgets(riga,1000,fp)!=NULL)
        {
/*
        err_level=NO_ERROR;
*/
        gest_errore(riga);
        }
retval=pclose(fp);
printf("\n FINE COMANDO retval=%d exit status= %d\n",retval,WEXITSTATUS(retval));
return(WEXITSTATUS(retval));
}






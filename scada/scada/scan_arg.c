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
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*    scan_arg.c

      Contiene: 
      1) la funzione che scandisce i parametri passati a scada
         dalla linea di comando
      2) la funzione che visualizza l'help

		6 aprile 1995
		Inserimento gestione parametro retry su rete TCP/IP

      11 Settembre 1995
      Inserimento gestione chiusura settimanale libro giornale

		2 Novembre 1995
		Opzione stringa allarmi in formato HH/MM/SS
*/
#include <osf1.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "switch.inc"
extern char _STR_LOCK[];
pub short sys_master;
short tcp_retry=12;

/* Function prototypes */
void help(void);

int scan_arg(parameter)
	char *parameter;
	{
	int ival,j,lun;

	if (strnicmp(parameter,"/",1)==0 || strnicmp(parameter,"-",1)==0)     // FUNZIONI
		{
      parameter++;
      switch(*parameter)
         {
         case '?': 
         case 'H': case'h':
            help();
            exit(0);
            break;
         case 'f': case'F':
		      parameter++;
            lun=strlen(parameter);
            for(j=1;j<=lun;j++,parameter++)
               {
               switch(*parameter)
                  {
                  case 'i': case 'I':
                     ISA=1; 
                     break;
                  case 't': case 'T':
                     TABUL=1; 
                     break;
                  case 'a': case 'A':
                     ARCHIVI_NV=1; 
                     break;
                  case 'D': case 'd':
                     SYS_DUALE=1;
                     sys_master=0;
                     break;
                  case 'E': case 'e':
                     NET_ABIL=0;
                     break;
                  case 'H': case 'h':
                     HCPY=1;
                     break;
                  case 'R': case 'r' :
                     GESREP=1;
                     break;
                  default:
                     help();
                     exit(0);
                  }
               }
            break;
         case 'a': case'A':
		      parameter++;
            lun=strlen(parameter);
            for(j=1;j<=lun;j++,parameter++)
               {
               switch(*parameter)
                  {
                  case 'S': case 's':
                     SEGNALA_RIC_ALLARMI=1; 
                     break;
                  case 'c': case 'C':
                     CONT_ALL_ZONE=1; 
                     break;
                  case 'R': case 'r':
                     RIC_SI=1; 
                     break;
                  case 'V': case 'v':
                     SKR_ALL=1; 
                     break;
                  case 'B': case 'b':
                     BUZZER=1;
                     break;
                  case 'W': case 'w':
                     RESET_LBGSETT=1;
                     break;
                  case 'F': case 'f':
                     SEC_FORMAT=1;
                     break;
                  default:
                     help();
                     exit(0);
                  }
               }
            break;
         case 'p': case'P':
            PAS_STOP=1;
		      parameter++;
            lun=strlen(parameter);
            for(j=1;j<=lun;j++,parameter++)
               {
               ival=atoi(parameter);
               if (ival>0 && ival<=NMAX_PAS)
                  NPC_PAS=(short)ival;
               else
                  if (*parameter=='I' || *parameter=='i')
                     PAS_INI=1;
                  else
                     {
                     help();
                     exit(0);
                     }
               }
            break;
         case 'V': case 'v':
            ival=atoi(++parameter);
		      if (ival>0 && ival<=MAXPER_GDAC) 
               PER_GDAC=(char)ival;
            else
               {
               help();
               exit(0);
               }
            break;
         case 'M': case 'm':
            ival=atoi(++parameter);
		      if (ival>0 && ival<=max_video) 
               num_video=(char)ival;
            else
               {
               help();
               exit(0);
               }
            break;
         case 'T': case 't':
            ival=atoi(++parameter);
		      if (ival>0) tcp_retry=(char)ival;
            else
               {
               help();
               exit(0);
               }
            break;
         case '@': 
		      if (strlen(parameter)==1)
               DEBUG=1;
            else
               {
               help();
               printf("per debugger /@\n");
               exit(0);
               }
            break;
         default:
            help();
            exit(0);
         }
      }
   else
      {
      help();
      exit(0);
      }
   }


void help()
	{
   printf("\n\nSCADA 32 bit - versione: %s \n\n",(_STR_LOCK+7));

	printf("uso:  SCADA [/Ffunzioni] [/Aopzioni_allarmi] [/P[I]numero_pas]\n");
   printf("            [/Tcicli]\n");
   printf("            [/Vfrequenza_video] [/Mnumero_mmi]\n\n");

	printf("funzioni:         D   abilita sistema duale\n");
   printf("                  I   abilita funzione isa\n");
	printf("                  T   abilita tabulati\n");
	printf("                  A   abilita archivi\n\n");
	printf("                  R   abilita gestione reperibili\n\n");

	printf("opzioni_allarmi:  R   abilita riconoscimento singolo pagina allarmi\n");
	printf("                  S   abilita stampa riconoscimento allarme\n");
	printf("                  V   abilita visita intera pagina allarmi\n");
	printf("                  C   uso contatori allarmi per zone e database\n");
	printf("                  W   chiusura libro giornale settimanale\n\n");
	printf("                  F   formato stringa allarmi: HH/MM/SS...\n\n");

   printf("I:                pas 1 di inizializzazione subito attivo\n");
   printf("numero_pas:       numero dei pas attivabili - da 1 a %d (default 0)\n\n",NMAX_PAS);

	printf("Time out rete TCP:  n. cicli di attesa da 3 tick (default 12)");

	printf("frequenza_video:  frequenza aggiornamento pagine video - da 1 (default) a %d\n\n",MAXPER_GDAC);

   printf("numero_mmi:       numero MMI collegabili - da 1 (default) a %d\n\n",max_video);
	}

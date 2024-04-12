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
#include <string.h>



short TABUL=0;        // per default non abilito le funzioni
short ARCHIVI_NV=0;
short SYS_DUALE=0;
short ISA=0;


main(argc,argv)
short int argc;
char *argv[];

{
int i;


/* test per help */
if (argc<0)
	{
	help();
	exit(0);
 	};


/* analisi argomenti passati in attivazione */
for (i=1; i<argc ;i++)
   scan_arg(argv[i]);

}

/* 
scan_arg - analisi opzioni 
*/

scan_arg(parameter)
	char *parameter;
	{
	int j,lun;


	if (strnicmp(parameter,"/f",2)==0)
		{
		parameter+=2;
      lun=strlen(parameter);
      for(j=1;j<=lun;j++,parameter++)
         {
         switch(*parameter)
            {
            case 'i':
            case 'I':
               ISA=1;
               break;
            case 't':
            case 'T':
               TABUL=1;
               break;
            case 'a':
            case 'A':
               ARCHIVI_NV=1;
               break;
            case 'S':
            case 's':
               SYS_DUALE=1;
               break;
            default:
                help();
                exit(0);
            }
         }
		}
   else
      {
                help();
                exit(0);
      }
	}	  

help()
	{
   printf("\n***************************************");
   printf("\nSCADA 32 bit - versione 1.00 - 07/09/93");
   printf("\n***************************************\n\n");
	printf("uso:     SCADA [/Foptions] \n\n");
	printf("options:  S   abilita sistema duale\n");
   printf("          I   abilita funzione isa\n");
	printf("          T   abilita tabulati\n");
	printf("          A   abilita archivi\n");
	printf("\n");
	}                                                    



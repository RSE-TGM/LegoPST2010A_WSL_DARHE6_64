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
/**

	dfpol.c  -  Display utility per file prodotti da POL

**/

#include <memory.h>
#include <string.h>

#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>
#include <stdio.h>

#include "fio.h"

int irecno=0;
int frecno=0x7fff;
int pause=0;

/* 
scan_arg - analisi opzioni 
*/

scan_arg(parameter)
	char *parameter;
	{
	int ival;
	int ret=1;

	if (strnicmp(parameter,"-i",2)==0)
		{
		parameter+=2;
		if ((ival=atoi(parameter))!=0) irecno=ival;
		}
	else if (strnicmp(parameter,"-f",2)==0)
		{
		parameter+=2;
		if ((ival=atoi(parameter))!=0) frecno=ival;
		}
	else if (strnicmp(parameter,"-p",2)==0)
		pause=1;
	else
		ret=0;
	
	return ret;
	}	  

help()
	{
		printf("\nDisplay Utility per file creati da P.O.L\n\n");
		printf("DFPOL [option] nome-file\n\n");
		printf("option:    -Innnnn   indice record iniziale\n");
		printf("           -Fnnnnn   indice record finale\n");
		printf("           -P        attesa prima del record successivo\n");
		printf("\n");
	}


/***
_fchks	- checksum del buffer modificata per questo programma
***/
char _fchks(b,l)
	char *b;
	int	l;
	{
	char	c=0;
	char	zero=0;
	register i;

	for (i=0; i<l; i++,b++)
		{
		c+=*b;
		zero|=*b;
		}
	if (zero)
		return(c);
	else
		return (-1);
	}

main(argc,argv)
	int argc;
	char *argv[];
	{
	int dfh;
	int ri=0;
	int td;
	int ldat;
	int	i;
	float	f;
	char *pdat;

	char buffer[300];


	/* test per help */
	if (argc<2)
		{
		help();
		exit(0);
    	};

	/* analisi argomenti passati in attivazione */
	for (i=1; i<argc && scan_arg(argv[i]); i++);
	if (i==argc)
		/* manca nome del file */
		{
		help();
		exit(0);
    	};

	if ( (dfh=open(argv[i],O_BINARY|O_RDONLY)) == -1)
		perror(argv[i]);
	else
		{
		lseek(dfh,((long) irecno << LRECFIO_EXP2),SEEK_SET);

		while (ri<frecno && read(dfh,buffer,LRECFIO))
			{
			pdat=buffer+LRECFIO-1;
			if (*pdat!=_fchks(buffer,LRECFIO-1))
				printf ("\nRecord %i (indefinito)\n",ri);
			else
				{
				int idato=0;
				int dato_valido=1;

				pdat=buffer;
				printf ("\nRecord %i\n",ri);
				do	 	// per tutti gli argomenti legali
					{
					td=*pdat;
					pdat++;
					ldat=*pdat;
					pdat++;
					idato++;
					printf("%3.i = ",idato);
					switch(td)
						{
						case FIO_ANALOG:
							f=*(float *)pdat;
							i=*(int *)(pdat+4);
							printf ("%f %4.4Xh (analogico)\n",f,i);
							break;

						case FIO_DIGIT:
							i=*(char *)pdat;
							printf ("%2.2Xh (digitale)\n",i);
							break;

						case FIO_ORGANO:
							i=*(int *)pdat;
							printf ("%4.4Xh (organo)\n",i);
							break;

						case FIO_REAL:
							f=*(float *)pdat;
							printf ("%f (reale)\n",f);
							break;

						case FIO_INT:
							i=*(int *)pdat;
							printf ("%i (intero)\n",i);
							break;

						case FIO_LOG:
							i=*(int *)pdat;
							printf ("%4.4Xh (logico)\n",i);
							break;

						case FIO_STRING:
							printf ("%s (stringa)\n",pdat);
							break;

						default:
							dato_valido=0;
							printf ("** fine-dati **\n",f);
							break;
						};
					pdat+=ldat;
					} while(dato_valido);
				}
				ri++;
				if (pause)
					{
					printf("Un carattere qualsiasi per continuare ...");
					getch();
					}
			};
		dfh=close(dfh);
		}

	exit(0);
	}

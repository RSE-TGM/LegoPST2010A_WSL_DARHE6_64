/*
   modulo ToRtf.c
   tipo 
   release 2.6
   data 6/14/96
   reserved @(#)ToRtf.c	2.6
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include <dconf.inc>

char path_txt[FILENAME_MAX+1];
char path_rtf[FILENAME_MAX+1];
extern DB_HEADER header_ToRtf;
 
extern int usa_informix;

main(argc,argv)
int argc;
char **argv;
{
int solo_tabulati =0;
int solo_svin =0;
int i;

if(argc<3)
	{
	fprintf(stderr,
	"Usage: ToRtf <path txt> <path rtf> ... [/t /sim -noinformix]\n");
	exit(1);
	}
/*
	vengono compilati solo i tabulati o i file svinana.rtf e svindig.rtf
*/
if((argc>3)&&(strcmp("/t",argv[3])==0))
	solo_tabulati =1;
if((argc>3)&&(strcmp("/sim",argv[3])==0))
	solo_svin =1;
if((argc>4)&&(strcmp("/t",argv[4])==0))
	solo_tabulati =1;
if((argc>4)&&(strcmp("/sim",argv[4])==0))
	solo_svin =1;

usa_informix=1;
for(i=1;i<argc;i++)
	if(strncmp(argv[i],"-noinformix",7)==0)
		usa_informix = 0;

strcpy(path_txt,argv[1]);
strcpy(path_rtf,argv[2]);

/*
	scarica le tabelle operative da Informix
*/
if(usa_informix)
	{
	if(!CreateTable())
	 	{
         	fprintf(stderr,"Errore: Scaricamento tabelle Informix\n");
         	exit(1);
         	}
	}
printf("Installazione files operativi %s -> %s\n",path_txt,path_rtf);
if(chdir(path_rtf)!=0)
	 {
         fprintf(stderr,"Errore: il path [%s] non esiste\n",path_rtf);
         exit(1);
         }
if(!CreateConfCfg())
	 {
         fprintf(stderr,"Errore creazione file conf.cfg");
         exit(1);
         }
if(!CreateFdbdpHea())
	 {
         fprintf(stderr,"Errore creazione file fdbdp.hea");
         exit(1);
         }
if(!(solo_tabulati||solo_svin))
{
	if(!CreateFnomi())
	 	{
         	fprintf(stderr,"Errore creazione file fnomi.rtf");
         	exit(1);
         	}
	if(!CreateFdde())
	 	{
         	fprintf(stderr,"Errore creazione file fdde.rtf");
         	exit(1);
         	}
	if(!CreateFdbdp())
	 	{
         	fprintf(stderr,"Errore creazione file fdbdp.rtf");
         	exit(1);
         	}
	if(!CreateARC())
	 	{
         	fprintf(stderr,"Errore creazione file fdarc.rtf de_arcxx.rtf");
         	exit(1);
         	}
	if(!CreateFdizst())
	 	{
         	fprintf(stderr,"Errore creazione file fdizst.rtf");
         	exit(1);
         	}
	if(!CreateFstato())
	 	{
         	fprintf(stderr,"Errore creazione file fstato.rtf");
         	exit(1);
         	}
	if(!CreateFvirtprn())
	 	{
         	fprintf(stderr,"Errore creazione file fvirtprn.rtf");
         	exit(1);
         	}
	if(!CreateFdesal())
	 	{
         	fprintf(stderr,"Errore creazione file fdesal.rtf");
         	exit(1);
         	}
	if(!CreateFgerarch())
	 	{
         	fprintf(stderr,"Errore creazione file fgerarch.rtf");
         	exit(1);
         	}
	if(!CreateFdeao())
	 	{
         	fprintf(stderr,"Errore creazione file fdeao.rtf");
         	exit(1);
         	}
	if(!CreateFdcom())
	 	{
         	fprintf(stderr,"Errore creazione file fdcom.rtf");
         	exit(1);
         	}
}
if((solo_svin)||(!(solo_tabulati||solo_svin)))
   if(!CreateSvinAnaDig())
 	{
       	fprintf(stderr,"Errore creazione file fsvinana.rtf e fsvindig.rtf");
       	exit(1);
       	}
if((solo_tabulati)||(!(solo_tabulati||solo_svin)))
   if(!CreateLOG())
	 {
         fprintf(stderr,"Errore creazione file fdiztab.rtf e ftab.rtf\n");
         exit(1);
         }
exit(0);
}

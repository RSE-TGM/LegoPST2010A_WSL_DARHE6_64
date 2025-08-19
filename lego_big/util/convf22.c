/*
   modulo convf22.c
   tipo 
   release 1.4
   data 7/25/94
   reserved @(#)convf22.c	1.4
*/
#include <stdio.h>
#include "libnet.h"

struct common_variabili {
                         char nomi_misure[1000][8];
                         char simboli[1000][80];
                         float misure[1000];
                         float tempo;
                         char titolo[80];
                         int numvar;
                         int numsimb;
                         char model[8];
                        };

typedef struct common_variabili VARIABILE;

char file_in_name[81], file_out_name[85];
VARIABILE variabili_;
FILE  *file22, *file22out;
int importo=1,flag,formato_dati,test=FALSE;

int leggi_testa_bin_vms();

void main(argc,argv)
int     argc;                   /* # of elements in argv */
char  **argv;                   /* vector of command line arguments */
{
   int j;
   char sistop[10];
   char estensione[10]="_out";

   strcpy(sistop,getenv("OS"));
   if ( argc > 5 )
   {
     printf("Usage: %s -f nomefile -t [ -i -e] [-aix -osf1 -vms -ultrix]\n",argv[0]);
     exit(1);
   }
   for (j=1; j<argc; j++)
   {
	if (!strncmp(getenv("DEBUG"),"YES",3))
	   printf("argv[%d]=%s\n",j,argv[j]);
	if (!strncmp(argv[j],"-f",2))
        {
           if ( strlen(argv[j]) > 2)
              strcpy(file_in_name,&argv[j][2]);
           else
	   {
	      j++;
              strcpy(file_in_name,argv[j]);
	   }
        }
        else if (!strncmp(argv[j],"-t",2))
        {
	   test=TRUE;
        }
        else if (!strncmp(argv[j],"-i",2))
        {
	   flag=RICEZIONE;
        }
        else if (!strncmp(argv[j],"-e",2))
        {
	   flag=TRASMISSIONE;
        }
        else if (!strncmp(argv[j],"-aix",4))
        {
	   strcpy(estensione,"_AIX");
	   if      (strcmp(sistop,"AIX") )
		formato_dati=AIX_AIX;
	   else if (strcmp(sistop,"ULTRIX") )
		formato_dati=AIX_ULTRIX;
	   else if (strcmp(sistop,"VMS") )
		formato_dati=AIX_VMS;
	   else if (strcmp(sistop,"OSF1") )
		formato_dati=AIX_ULTRIX;

        }
        else if (!strncmp(argv[j],"-ultrix",7)) 
        {
	   strcpy(estensione,"_ULTRIX");
	   if      (strcmp(sistop,"AIX") )
		formato_dati=ULTRIX_AIX;
	   else if (strcmp(sistop,"ULTRIX") )
		formato_dati=ULTRIX_ULTRIX;
	   else if (strcmp(sistop,"VMS") )
		formato_dati=ULTRIX_VMS;
	   else if (strcmp(sistop,"OSF1") )
		formato_dati=ULTRIX_ULTRIX;
        }
        else if (!strncmp(argv[j],"-osf1",5))
        {
	   strcpy(estensione,"_OSF1");
	   if      (strcmp(sistop,"AIX") )
		formato_dati=ULTRIX_ULTRIX;
	   else if (strcmp(sistop,"ULTRIX") )
		formato_dati=ULTRIX_ULTRIX;
	   else if (strcmp(sistop,"VMS") )
		formato_dati=ULTRIX_VMS;
	   else if (strcmp(sistop,"OSF1") )
		formato_dati=ULTRIX_ULTRIX;
        }
        else if (!strncmp(argv[j],"-vms",4))
        {
	   strcpy(estensione,"_VMS");
	   if      (strcmp(sistop,"AIX") )
		formato_dati=VMS_AIX;
	   else if (strcmp(sistop,"ULTRIX") )
		formato_dati=VMS_ULTRIX;
	   else if (strcmp(sistop,"VMS") )
		formato_dati=VMS_VMS;
	   else if (strcmp(sistop,"OSF1") )
		formato_dati=VMS_ULTRIX;
        }
   }
   if (strlen(file_in_name)==0)
   {
     strcpy(file_in_name,"f22");
   }
   strcpy(file_out_name,file_in_name);
   strcat(file_out_name,estensione);
   if (!strncmp(getenv("DEBUG"),"YES",3))
	printf(" file_in_name=%s file_out_name=%s S.O.=%s estensione=%s test=%d flag=%d\n",file_in_name,file_out_name,sistop,estensione,test,flag);

   if (!strcmp(estensione,"_VMS"))
      leggi_testa_bin_vms();
   else
      leggi_testa_bin();
   if (test)
   {
	   if      (!strcmp(sistop,"AIX") )
           {
	        printf("Formato %s: Numero variabili =%d \n","AIX",*converti_int_f(&variabili_.numvar,RICEZIONE,AIX_AIX));
	        printf("Formato %s: Numero variabili =%d \n","ULTRIX",*converti_int_f(&variabili_.numvar,RICEZIONE,AIX_ULTRIX));
	        printf("Formato %s: Numero variabili =%d \n","VMS",*converti_int_f(&variabili_.numvar,TRASMISSIONE,AIX_VMS));
	        printf("Formato %s: Numero variabili =%d \n","VMS",*converti_int_f(&variabili_.numvar,RICEZIONE,AIX_VMS));
	        printf("Formato %s: Numero variabili =%d \n","OSF1",*converti_int_f(&variabili_.numvar,RICEZIONE,AIX_ULTRIX));
	   }
	   else if (!strcmp(sistop,"ULTRIX") )
           {
	        printf("Formato %s: Numero variabili =%d \n","AIX",*converti_int_f(&variabili_.numvar,RICEZIONE,ULTRIX_AIX));
	        printf("Formato %s: Numero variabili =%d \n","ULTRIX",*converti_int_f(&variabili_.numvar,RICEZIONE,ULTRIX_ULTRIX));
	        printf("Formato %s: Numero variabili =%d \n","VMS",*converti_int_f(&variabili_.numvar,RICEZIONE,ULTRIX_VMS));
	        printf("Formato %s: Numero variabili =%d \n","OSF1",*converti_int_f(&variabili_.numvar,RICEZIONE,ULTRIX_ULTRIX));
	   }
	   else if (!strcmp(sistop,"VMS") )
           {
	        printf("Formato %s: Numero variabili =%d \n","AIX",*converti_int_f(&variabili_.numvar,RICEZIONE,VMS_AIX));
	        printf("Formato %s: Numero variabili =%d \n","ULTRIX",*converti_int_f(&variabili_.numvar,RICEZIONE,VMS_ULTRIX));
	        printf("Formato %s: Numero variabili =%d \n","VMS",*converti_int_f(&variabili_.numvar,RICEZIONE,VMS_VMS));
	        printf("Formato %s: Numero variabili =%d \n","OSF1",*converti_int_f(&variabili_.numvar,RICEZIONE,VMS_ULTRIX));
	   }
	   else if (!strcmp(sistop,"OSF1") )
           {
	        printf("Formato %s: Numero variabili =%d \n","AIX",*converti_int_f(&variabili_.numvar,RICEZIONE,ULTRIX_AIX));
	        printf("Formato %s: Numero variabili =%d \n","ULTRIX",*converti_int_f(&variabili_.numvar,RICEZIONE,ULTRIX_ULTRIX));
	        printf("Formato %s: Numero variabili =%d \n","VMS",*converti_int_f(&variabili_.numvar,RICEZIONE,ULTRIX_VMS));
	        printf("Formato %s: Numero variabili =%d \n","OSF1",*converti_int_f(&variabili_.numvar,RICEZIONE,ULTRIX_ULTRIX));
	   }
   }
   scrivi_testa_bin_();
   while ( leggi_corpo_bin() )
      scrivi_corpo_bin_();
}

leggi_testa_bin()
   {
   int i;
   char nomi[8][1000];
      file22 = fopen(file_in_name,"r");
      fread(variabili_.titolo,80,1,file22);
      if (!strncmp(getenv("DEBUG"),"YES",3))
	 printf("Titolo: %s\n",variabili_.titolo);
      fread(&variabili_.numvar,sizeof(variabili_.numvar),1,file22);
      if (test) return;
      fread(variabili_.nomi_misure,8,variabili_.numvar,file22);
      fread(variabili_.model,8,1,file22);
      fread(&variabili_.numsimb,sizeof(variabili_.numsimb),1,file22);
      fread(variabili_.simboli,80,variabili_.numsimb,file22);
   }

int leggi_testa_bin_vms()
   {
   char pad[2];
   int i;
   char nomi[8][1000];
      file22 = fopen(file_in_name,"r");
      fread(pad,sizeof(pad),1,file22);
      fread(variabili_.titolo,80,1,file22);
printf("Titolo: %s\n",variabili_.titolo);
      fread(pad,sizeof(pad),1,file22);
      fread(&variabili_.numvar,sizeof(variabili_.numvar),1,file22);
printf("numvar: %d-%d\n",variabili_.numvar,converti_int_f(&variabili_.numvar,RICEZIONE,AIX_VMS));
printf("Numero variabili =%d \n",*converti_int_f(&variabili_.numvar,TRASMISSIONE,AIX_VMS));
      fread(pad,sizeof(pad),1,file22);
      if (test) return;
      for (i=0;i< *converti_int_f(&variabili_.numvar,RICEZIONE,AIX_VMS) ;i++)
      {
          fread(variabili_.nomi_misure[8*i],8,1,file22);
          fread(pad,sizeof(pad),1,file22);
      }
      fread(variabili_.model,8,1,file22);
      fread(pad,sizeof(pad),1,file22);
      fread(&variabili_.numsimb,sizeof(variabili_.numsimb),1,file22);
printf("numvar: %d\n",variabili_.numsimb);
      fread(pad,sizeof(pad),1,file22);
      for (i=0;i< *converti_int_f(&variabili_.numsimb,RICEZIONE,AIX_VMS) ;i++)
      {
          fread(variabili_.simboli[80*i],80,1,file22);
          fread(pad,sizeof(pad),1,file22);
      }
   }

leggi_corpo_bin()
   {
   int i;
            if ( ! fread(&variabili_.tempo,sizeof(variabili_.tempo),1,file22))
               return(0);
            fread(variabili_.misure,sizeof(float),variabili_.numvar,file22);

   }

scrivi_testa_bin_()
   {
   int i;
   char nomi[8][1000];
      file22out = fopen(file_out_name,"w+");
      fwrite(variabili_.titolo,80,1,file22out);
      fwrite(converti_int_f(&variabili_.numvar,0,formato_dati),sizeof(variabili_.numvar),1,file22out);
      fwrite(variabili_.nomi_misure,8,variabili_.numvar,file22out);
      fwrite(variabili_.model,8,1,file22out);
      fwrite(converti_int_f(&variabili_.numsimb,0,formato_dati),sizeof(variabili_.numsimb),1,file22out);
      fwrite(variabili_.simboli,80,variabili_.numsimb,file22out);
   }


scrivi_corpo_bin_()
   {
   int i;
      fwrite(converti_float_f(&variabili_.tempo,0,formato_dati),sizeof(variabili_.tempo),1,file22out);
      for (i=0;i<variabili_.numvar;i++)
          memcpy(&variabili_.misure[i],converti_float_f(&variabili_.misure[i],0,AIX_ULTRIX),sizeof(float));
            fwrite(variabili_.misure,sizeof(float),variabili_.numvar,file22out);

   }

     

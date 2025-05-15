/*
   modulo modpagutil.c
   tipo 
   release 1.1
   data 1/8/96
   reserved @(#)modpagutil.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)modpagutil.c	1.1\t1/8/96";
/*
        Fine sezione per SCCS
*/
/*             modpagutil.c     S.Balistreri

 * sono contenute tutte le routine necessarie per modpag.c e
 * modallpag.c
 */



#include<stdio.h>
#include<string.h>

#define DIM 200

int t=0;


/* CAMBIO COLORE SOGLIE */
/*caso COLORE FUORI SCANSIONE */
char *wordkeycolor1[]={"coloreFuoriScansione1:","coloreFuoriScansione2:",
                       "coloreFuoriScansione3:","coloreFuoriScansione4:"
                       };

/*caso COLORE FUORI ATTENDIBILITA */
char *wordkeycolor2[]={"coloreFuoriAttendib1:","coloreFuoriAttendib2:",
                       "coloreFuoriAttendib3:","coloreFuoriAttendib4:"
                       };

/*caso COLORE DIGITALE ON */
char *wordkeycolor3[]={"coloreDigSet1:","coloreDigSet2:",
                       "coloreDigSet3:","coloreDigSet4:"
                       };

/*caso COLORE FUORI LIMITE BASSO SICUREZZA */
char *wordkeycolor4[]={"coloreBassissimo1:","coloreBassissimo2:",
                       "coloreBassissimo3:","coloreBassissimo4:"
                       };

/*caso COLORE FUORI LIMITE BASSO CONDUZIONE */
char *wordkeycolor5[]={"coloreBassissimoBasso1:","coloreBassissimoBasso2:",
                       "coloreBassissimoBasso3:","coloreBassissimoBasso4:"
                       };

/*caso COLORE IN CONDUZIONE */
char *wordkeycolor6[]={"coloreBassoAlto1:","coloreBassoAlto2:",
                       "coloreBassoAlto3:","coloreBassoAlto4:"
                       };

/*caso COLORE FUORI LIMITE ALTO CONDUZIONE */
char *wordkeycolor7[]={"coloreAltoAltissimo1:","coloreAltoAltissimo2:",
                       "coloreAltoAltissimo3:","coloreAltoAltissimo4:"
                       };

/*caso COLORE FUORI LIMITE ALTO SICUREZZA */
char *wordkeycolor8[]={"coloreAltissimo1:","coloreAltissimo2:",
                       "coloreAltissimo3:","coloreAltissimo4:"
                       };

#ifdef VMS
/*caso COLORE FLAG AUTOMATICO */
char *wordkeycolor9[]={"coloreAutomatico1:","coloreAutomatico2:",
                       "coloreAutomatico3:","coloreAutomatico4:"
                      };

/*caso COLORE FLAG STIMATO*/
char *wordkeycolor10[]={"coloreStimato1:","coloreStimato2:", 
                        "coloreStimato3:","coloreStimato4:"
                       };
#endif
                  

menu1()        
/*gestisce un secondo menu se l'opzione scelta nel precedente menu' e' 2 */
{
int s1=0;

printf(" 0-EXIT\n");
printf(" 1-COLORE FUORI SCANSIONE\n");
printf(" 2-COLORE FUORI ATTENDIBILITA'\n");
printf(" 3-COLORE DIGITALE ON\n");
printf(" 4-COLORE FUORI LIMITE BASSO SICUREZZA\n");
printf(" 5-COLORE FUORI LIMITE BASSO CONDUZIONE\n");
printf(" 6-COLORE IN CONDUZIONE\n");
printf(" 7-COLORE FUORI LIMITE ALTO CONDUZIONE\n");
printf(" 8-COLORE FUORI LIMITE ALTO SICUREZZA\n");
#ifdef VMS
printf(" 9-COLORE AUTOMATICO\n");
printf("10-COLORE STIMATO\n");
#endif
printf("l'opzione scelta e'-->");
scanf ("%d",&s1);
return(s1);
}


#ifdef VMS
int rinombak(char *salva,char *path)
#else
int rinombak(char *salva,char *path,char *bak2)
#endif
{
int lungpag,i,ren;


strcpy(salva,path);
lungpag = strlen(path);    /*lungpag=lunghezza della stringa*/

#ifndef VMS
/*conversione nome iniziale in.bak */
for(i=0;i<lungpag;i++) 
	{
   	if (path[i]=='.') 
		{
      		path[i+1]='\0';
      		strcpy(bak2,path);
      		strcat(path,"bak");
      		strcat(bak2,"bak2");

/*la pagina .pag viene rinominata in .bak nel direttorio specificato
 *salvapagina=.pag , pathnomepagina=.bak */
/*function rename ritorna -1 se non e' andata a buon fine*/
/*printf("\n salva = %s    path = %s",salva,path);*/
      		ren=rename(salva,path);

      		if (ren == -1) 
			{
         
			printf("permission denied,impossibile modificare .pag\n");
         
			return(-1);
      
			}
  
		}
	}
#endif
}

#ifdef VMS
tiposoglia(int ritornomenu,char *colore,char *path,char *salva,int col)
#else
tiposoglia(int ritornomenu,char *colore,char *path,char *salva,char *bak2,int col)
#endif
{
             /*verifico se l'opz e' diversa da zero o non maggiore
              *8(max opz) e chiedo l'inser del colore desiderato
              */
              
              
#ifdef VMS
              if((ritornomenu>0)&&(ritornomenu<=10)&&(col==1)) {
#else
              if((ritornomenu>0)&&(ritornomenu<=8)&&(col==1)) {
#endif

              printf("inserire colore desiderato(es formato-->ffffffffffff)o white:\n");
              scanf("%s",colore);
              }

             switch(ritornomenu) {
                   case 0:
                        /* in questo caso il .bak non e' necessario
                         * attenzione vale solo se 0 e' la 1^opzione
                         * introduco la variabile t,se 0 fai rename
                         * se 1 indica che sono gia' state fatte delle
                         * sostituzioni
                         */
                        if (t==0){
                        rename(path,salva);
#ifndef VMS
                        unlink(bak2);
#endif
                        }
                        else {
                        rename(path,salva);
#ifndef VMS
                        rename(bak2,path);
#endif
                        }
                        t=0;
                        return(-1);
                   break;

                   case 1:
                        /*caso COLORE FUORI SCANSIONE*/
                        sostituisci(path,salva,wordkeycolor1,4,0,colore);
                        t++;
                   break;

                   case 2:
                        /*caso COLORE FUORI ATTENDIBILITA'*/
                        sostituisci(path,salva,wordkeycolor2,4,0,colore);
                        t++;
                   break;

                   case 3:
                        /*caso COLORE DIGITALE ON*/
                        sostituisci(path,salva,wordkeycolor3,4,0,colore);
                        t++;
                   break;

                   case 4:
                        /*caso COLORE FUORI LIM BASSO SICUR*/
                        sostituisci(path,salva,wordkeycolor4,4,0,colore);
                        t++;
                   break;

                   case 5:
                        /*caso COLORE FUORI LIM BASSO COND*/
                        sostituisci(path,salva,wordkeycolor5,4,0,colore);
                        t++;
                   break;

                   case 6:
                        /*caso COLORE IN CONDUZONE*/
                        sostituisci(path,salva,wordkeycolor6,4,0,colore);
                        t++;
                   break;

                   case 7:
                        /*caso COLORE FUORI LIM ALTO COND*/
                        sostituisci(path,salva,wordkeycolor7,4,0,colore);
                        t++;
                   break;

                   case 8:
                        /*caso COLORE FUORI LIM ALTO SICUR*/
                        sostituisci(path,salva,wordkeycolor8,4,0,colore);
                        t++;
                   break;
#ifdef VMS
                  case 9:
                       /*caso COLORE FLAG AUTOMATICO*/
                       sostituisci(path,salva,wordkeycolor9,4,0,colore);
                        t++;
                   break;
                   
                   case 10:
                       /*caso COLORE FLAG STIMATO*/
                       sostituisci(path,salva,wordkeycolor10,4,0,colore);
                        t++;
                   break;
#endif
                   default:
                        printf("selezione errata\n");
             }
}

/*
 Sostuisci : sostituisce nel file .pag la risorsa relativa alla
 parola chiave passata come parametro
*/
void sostituisci(pagina,salva,findword,numword,tipoopz,colore)
char *pagina;    /* path name completo della pagina .bak che
                    viene aperta in sola lettura  */
char *salva;     /* path name completo della nuova pagina */
char **findword; /* array di nomi chiave da cercare  */
int  numword;    /* numero di parole-chiave */
int  tipoopz;    /* tipo di opzione*/
char *colore;    /* nuova stringa da inserire in sostituzione */

{
char linea[DIM],stringa[60],stringa2[30];
int set;  /*indica a 0=non trovata chiave 1=trovata */

/*lung=intera linea ,lungchiave=lunghezza della chiave*/
int c,c2,lung,lungchiave;

FILE *fp,*fp1;


fp=fopen(pagina,"r");    /*apro il .bak in lettura e il .pag in scrittura*/
fp1=fopen(salva,"w");
while ((fgets(linea,DIM-1,fp))!=NULL) {

/* ho letto una linea e dalla linea devo estrarre le varie stringhe*/
     sscanf(linea,"%s",stringa);
     set=0;
     
     for (c=0;c<numword;c++) {
         if ((strstr(stringa,findword[c]))!=NULL) {
         /*ho trovato una parola chiave*/
           set=1;
           lung=strlen(linea); /*determino la lunghezza della linea*/
           
/*         
 * per evitare che venga sostituito un carattere della parola chiave si fa
 * iniziare il controllo dalla stringa successiva senza tale accorgimento
 * es.varName3 diventerebbe varName4
 */
               if (numword==8){
           /* se numword=8 sono nel caso cambio tag */
              if (tipoopz==1)
              /*caso cambio tag da 3 a 4*/
              {
                 lungchiave=strlen(stringa);
                 for(c2=lungchiave;c2<lung;c2++) {
                    if (linea[c2]=='3'){
                        linea[c2]='4';
                        break;
                    }
                 }
              }
              if (tipoopz==2)
              /*caso cambio tag da 4 a 3*/
              {
                 lungchiave=strlen(stringa);
                 for(c2=lungchiave;c2<lung;c2++) {
                    if (linea[c2]=='4'){
                        linea[c2]='3';
                        break;
                    }
                 }
              }
             fputs(linea,fp1);
             }
             else
             {
             /*in questo caso numword vale 4-->cambio soglie */
             strcat(stringa,"    "); /*aggiungo 4 spazi */
             fputs(stringa,fp1); 
             fputs(colore,fp1);  /*scrivo su file colore utente */
             fputc('\n',fp1);   /*vai a capo*/
             break;
             }
           } 
     }
     if (set==0)
     fputs(linea,fp1);
}  
fclose(fp);
fclose(fp1);
}


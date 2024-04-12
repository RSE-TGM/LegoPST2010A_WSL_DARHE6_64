/*
   modulo modpag.c
   tipo 
   release 1.1
   data 1/8/96
   reserved @(#)modpag.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)modpag.c	1.1\t1/8/96";
/*
        Fine sezione per SCCS
*/
/*                 modpag.c    S.Balistreri

 *programma di utilita' che consente di duplicare pagine del gruppo 3 e generar
 *le del gruppo 4 cambiando nel file.pag le relative tag.Inoltre e' possibile
 *cambiare i colori delle varie soglie
 */
 


#include<stdio.h>
#include<string.h>

extern t;

#define DIM 200        /*dimensione max della linea da leggere da file*/

int s=0,ritm1=0,col=0;

 
/* CAMBIO TAG */
char *wordkeymodify[]={"varName1:","varName2:","varName3:","varName4:",
		       "varInputCambioColore1:","varInputCambioColore2:",
		       "varInputCambioColore3:","varInputCambioColore4:"
		       };

char pathnomepagina[80],salvapagina[80];    /*in salvapagina .bak */
char appbak2[80];                           /*tempoaneo per cambio soglie*/

char colorselez[30];    /*colore che l'utente inserisce per modifica soglie*/

FILE *fp,*fp1,*fp2;

#ifdef VMS
char *XlConvPathVms();
#endif


main (argc,argv)
int argc;
char *argv[];
{ 
int cont=0;

if (argc==1)
   {
   /* si chiede all'utente di inserire il nome della pagina */
 
   printf("inserisci path completo della pagina:");
   scanf("%s",pathnomepagina);

   /*verificare se il file esiste effettivamente altrimenti comunicarlo*/

   if((fp=fopen(pathnomepagina,"r"))==NULL) {
       printf ("pagina non esistente\n"); 
       return(-1);
       }
#ifdef VMS
       rinombak(salvapagina,pathnomepagina);
#else
       rinombak(salvapagina,pathnomepagina,appbak2);
#endif   
   /*gestione menu con possibilita' di cambio soglie o duplicazione pagina 
    *con modifica*/
       s=menu();
       switch(s) {
        case 0:
             /* in questo caso il .bak non e' necessario*/
             rename(pathnomepagina,salvapagina);
             return(-1);
        break;

        case 1:
             sostituisci(pathnomepagina,salvapagina,wordkeymodify,8,1);
             printf("terminata operazione di sostituzione\n");
        break;
  
        case 2:
             sostituisci(pathnomepagina,salvapagina,wordkeymodify,8,2);
             printf("terminata operazione di sostituzione\n");
        break;

        case 3:
#ifndef VMS             
              copiafile(pathnomepagina,appbak2); 
#endif
             do
             {
             /* ATT.NE!!!! se ho effettuato almeno una sostituzione
              * devo rifare il rename del .pag in .bak altrimenti
              * andrei a sovrascrivere il file appena  modificato
              * dentro la routine sostituisci viene aperto il .bak
              * in lettura e il .pag in scrittura,senza questo nuovo
              * rename il .bak risulterebbe quello iniziale senza quindi
              * la 1...n modifiche fatte
              */ 

             ritm1=menu1();
             if(ritm1!=0)
             col=1;

#ifdef VMS
              tiposoglia(ritm1,colorselez,pathnomepagina,salvapagina,col);
#else
              tiposoglia(ritm1,colorselez,pathnomepagina,salvapagina,appbak2,col);
#endif
             if (t != 0)
             rename(salvapagina,pathnomepagina);
            }
            while(ritm1!=0);
        break;
        default:
                 printf("selezione errata\n");
       }
  }
if (argc!=1) {

/* in argv[1] ho path della pagina 
 * in argv[2] ho nome pagina
 * in argv[3] ho tipo soglia da modificare ..intero da 1...8
 * in argv[4] ho colore
 */

ritm1=atoi(argv[3]);
/*
printf("argv[1]=%s\n",argv[1]);
printf("argv[2]=%s\n",argv[2]);
printf("argv[3]=%d\n",ritm1);
printf("argv[4]=%s\n",argv[4]);
*/

strcpy (pathnomepagina,argv[1]);   
strcat (pathnomepagina,"/");      
strcat (pathnomepagina,argv[2]); 
strcat (pathnomepagina,".pag");
#ifdef VMS
strcpy (pathnomepagina,XlConvPathVms(pathnomepagina));
#endif

strcpy (colorselez,argv[4]);
                           

#ifdef VMS
 rinombak(salvapagina,pathnomepagina);
#else
 rinombak(salvapagina,pathnomepagina,appbak2);
/* copiafile(pathnomepagina,appbak2);*/
#endif



if(ritm1!=0)
   tiposoglia(ritm1,colorselez,pathnomepagina,salvapagina,appbak2,col);

}
#ifndef VMS
rename (appbak2,pathnomepagina);
#endif
}


menu()
/*gestisce il primo menu dopo la richiesta di immissione path pagina */
{
printf("0-EXIT\n");
printf("1-MODIFICA TAG DELLE VARIABILI DA GRUPPO3 A GRUPPO4\n");
printf("2-MODIFICA TAG DELLE VARIABILI DA GRUPPO4 A GRUPPO3\n");
printf("3-CAMBIO COLORE SOGLIE\n");
printf("l'opzione scelta e'-->");
scanf ("%d",&s);
return(s);
}

copiafile(fil1,fil2)
char *fil1,*fil2;
{
char linea[DIM];

 fp=fopen(fil1,"r");
 fp2=fopen(fil2,"w");
 while ((fgets(linea,DIM-1,fp))!=NULL)
        fputs (linea,fp2);
fclose (fp);
fclose (fp2);
}








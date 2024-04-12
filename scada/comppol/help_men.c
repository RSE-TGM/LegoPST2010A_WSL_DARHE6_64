/*
   modulo help_men.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)help_men.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <osf1.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

/***********************************************************************
*								                                               *
*			Procedura help_menu 			                                   *
*								                                               *
* La procedura viene chiamata per mostrare il nenu' di help,           *
* la si richiama introducendo l' opzione di help ("?" o "/h") quando   *
* si attiva il compilatore.                                            *
*								                                               *
***********************************************************************/

#ifdef INGLESE
#define syntax    " Compiler command line:"
#define compila   "compila (filename) (address) [option]"
#define otherwise "otherwise"
#define compilh   "compila (option) ? and /h only"
#define compAdd   " Compiling address:"
#define synMan    "/0 ---> synoptic management program"
#define tabMan    "/1 ---> report management program"
#define appPrg    "/2 ---> application program"
#define option    " Options :"
#define helpMneu  "/h ---> help menu"
#define helpMenu  " ? ---> help menu"
#define intFil    "/i ---> intermediate file <codice.int>"
#define listFil   "/ls --> list file <codice.lst> with symbol-table"
#define nlistFil  "/lo --> list file <codice.lst> without symbol-table"
#define mapFil    "/st --> map file <codice.map>"
#define debFil    "/deb -> debugger file <codice.deb>"
#define inclEsp   "/ie=[drive][path] -> pathname for expansion"
#define Utente    "/u<user> -> allowed users: P (Piombino)"
#define ricCorr   "Type new command correctly"
#else
#define ricCorr   "Ricomponi ora il comando con gli argomenti corretti"
#define Utente    "/u<utente> -> utenti permessi: P (Piombino)"
#define inclEsp   "/ie=[drive][path] -> nome drive e path per espansione include"
#define debFil    "/deb -> produzione file debugger <codice.deb>"
#define mapFil    "/st --> produzione file mappa    <codice.map>"
#define nlistFil  "/lo --> produzione file listato  <codice.lst> senza symbol-table"
#define listFil   "/ls --> produzione file listato  <codice.lst> con   symbol-table"
#define intFil    "/i ---> produzione file intermedio <codice.int>"
#define helpMenu  " ? ---> visualizzazione menu di help "
#define helpMneu  "/h ---> visualizzazione menu di help "
#define option    " Opzioni consentite :"
#define appPrg    "/2 ---> programma applicativo"
#define tabMan    "/1 ---> programma gestione tabulato"
#define synMan    "/0 ---> programma gestione pagina video"
#define compAdd   " Indirizzo di compilazione :"
#define compilh   "compila (opzioni) ammesse soltanto ? e /h"
#define otherwise "oppure in alternativa"
#define compila   "compila (nomefile) (indirizzo) [opzioni]"
#define syntax    " Sintassi linea comando del compilatore :"
#endif

help_menu()

{

int i;
i=3;
erase_screen();
curxy(2,30);
reverse_video();
printf("******  HELP  ******");
attrib_off();
row(i++);
printf(syntax);
row(i++);
curxy(i++,10);
printf(compila);
curxy(i++,20);
printf(otherwise);
curxy(i++,10);
printf(compilh);

row(i++);
row(i++);
printf(compAdd);
row(i++);
printf(synMan);
row(i++);
printf(tabMan);
row(i++);
printf(appPrg);

row(i++);
row(i++);
printf(option);
row(i++);
printf(helpMneu);
row(i++);
printf(helpMenu);
row(i++);
printf(intFil);
row(i++);
printf(listFil);
row(i++);
printf(nlistFil);
row(i++);
printf(mapFil);
row(i++);
printf(debFil);
row(i++);
printf(inclEsp);
row(i++);
printf(Utente);
row(i++);
row(i++);
printf(ricCorr);
exit(0);

}



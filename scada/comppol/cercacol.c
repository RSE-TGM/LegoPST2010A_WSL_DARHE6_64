/*
   modulo cercacol.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)cercacol.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   Cercacol

   Funzione che verifica se una stringa identifica
   un colore definito nella tabella TabCol
   Se la tabella e' vuota viene letta dal file PolCol.pal

   Parametri

   char *   stCol stringa nome colore

   ritorno  posizione del colore nella tabella
*/
#include "osf1.h"
#include <stdio.h>

#define max_col   256      // n. massimo colori
#define max_name_col 20    // n. massimo caratteri definizione colore

char  TabCol[max_col][max_name_col];

int CercaCol(char *strCol)
{
FILE *fp;
short iCol;
char stringa[200];
char bCol;

if(!TabCol[0][0])    // tabella non inizializzata
{
   fp=fopen("MMI.INI","r+");
   if(fp==NULL)
   {
      return(-1);
   }
   bCol=0;
   for(iCol=0;;)
   {
      if(fgets(stringa,200,fp)==NULL) break;
      if(stringa[0]==';') continue;
      if(!strncmp(stringa,"[COLORS]",8))     // inizia sezione colori
      {
         bCol=1;
         continue;
      }
      if(!bCol) continue;
      if(stringa[0]=='[') bCol=0;         // fine sezione colori
      sscanf(stringa,"%s",TabCol[iCol]);
      iCol++;
   }
   fclose(fp);
}
for(iCol=0;iCol<max_col;iCol++)
{
   if(!strcmp(strCol,TabCol[iCol])) return(iCol);
}
stampa_err(42,1,strCol);
return(-1);
}

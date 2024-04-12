/**********************************************************************
*
*       C Source:               aux.c
*       Subsystem:              2
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Nov  7 13:56:18 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: auxiliary.c-2 %  (%full_filespec: auxiliary.c-2:csrc:2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)aux.c	1.11\t3/27/95";
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <ctype.h>
#include "linfo.h"

#if defined LINUX
#define TRUE 1
#define FALSE 0
#endif
     
void mintomaius(char *stringa)
{
   int i;
   for(i=0;i=strlen(stringa);i++)
       stringa[i] = toupper(stringa[i]);
}


void AllocaForaus(FORAUS *ptr,int nchar)
{
   ptr->foraus = (char *)XtMalloc( (nchar*sizeof(char)) );
}

/* -------------------------------------------
   cerca il monulo 'nome_modulo' in foraus.for
   e torna True se lo trova oppure False 
   ------------------------------------------- */
int  CercaModuloInForaus(FORAUS *foraus, char *nome_modulo )
{
   char pattern[50];
   int i;

   /* pulizia *
   strcpy(pattern,"");


   /* definisce il pattern di ricerca */
   sprintf(pattern,"%s%s%s",PATTERN_START,nome_modulo,PATTERN_END);   
   printf("Pattern di ricerca modulo in foraus.for -> %s\n",pattern);
   
   if( strstr(foraus->foraus,pattern) != NULL)
   {
      printf("Fotran ausiliario del modulo %s inserito in foraus\n",nome_modulo);
      return(TRUE);
   }
   else
   {
      printf("Fotran ausiliario del modulo %s NON inserito in foraus\n",nome_modulo);
      return(FALSE);
   }
}

/* ----------------------------------------------
   aggiunge il monulo 'nome_modulo' in foraus.for
   e torna True se ci riesce oppure False 
   ---------------------------------------------- */
int AggiungiModuloInForaus( char *nome_modulo )
{

}

/* --------------------------------------------
   toglie il monulo 'nome_modulo' in foraus.for
   e torna True se ci riesce oppure False 
   -------------------------------------------- */
int TogliModuloInForaus( char *nome_modulo )
{

}

/* -----------------------------------------
   ritorna l'elenco dei moduli in foraus.for
   ----------------------------------------- */
char *ElencoModuliInForaus( )
{

}

/* --------------------------------
   commenta il modulo 'nome_modulo'
   in foraus.for
   -------------------------------- */
int CommentaModuloInForaus( char *nome_modulo )
{
  
}

/* ---------------------------------
   scommenta il modulo 'nome_modulo'
   in foraus.for
   --------------------------------- */
int ScommentaModuloInForaus( char *nome_modulo )
{

}


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
/*
   allsev

   Gestisce i flag relativi ai livelli di severita'

   Parametri

   ptdbsad  short *     puntatore al data base flag
   numalls  short       n. allarmi pendenti della severita' indicata
   livsev   short       n. severita' selezionata

   Ritorno

   nessuno

   18 Novembre 1992

*/ 

#include  "g2comdb.inc"

// External function declarations
extern void bitset(short* buffer, short indice, short bit);

int allsev (ptdbsad,numalls,livsev)

short *ptdbsad;   // puntatore in dbs an. diag. per flag coontatori allarmi   
short numalls ;   // num degli allarmi pendenti per quel livello di sev.  
short livsev  ;   // livello di severita' interessato alla gestione
{
short bit,mask;

/*
   eseguo la gestione solo se numalls e' 0 (reset) oppure 1 (set)
*/
if (numalls>1) return(0);

switch (livsev) 
{           
case 0:   
   mask=g2an_s1;
break;
case 1:   
   mask=g2an_s2;
break;
case 2:   
   mask=g2an_s3;
break;
}

if (numalls==0)            // verifico se devo alzare o abbasare flag
       bit=0;
else
       bit=1;

bitset(ptdbsad,mask,bit);  // modifico il flag
return(0);
}


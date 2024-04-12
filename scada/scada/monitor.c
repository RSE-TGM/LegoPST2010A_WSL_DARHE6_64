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
/* -> monitor.C
 *       Task meno prioritario che 
 *			gestisce il menu per l'utilizzo di utilities come
 *			mandb.
 *       <END> termina l'esecuzione del task e
 *       reinstalla tutto il vettore precedentemenete
 *       salvato - Usa la RestIDT()
 */
 #include <stdio.h>
 #include <bios.h>
 #include <stdlib.h>

 #include "ansiscr.h"
 #include "pscs.cfg"
#if defined (SYS_MMI)
#else
 #include "diagnodi.inc"
 #include "g1tipdb.inc"
 #include "g2comdb.inc"
 #include "dconf.inc"
 #include "comunic.inc"
 extern  DB_HEADER h_db;
#endif
#include "pscserr.inc"

extern pscswd_tcb;

#ifdef MMI_VGA
	extern unsigned long mbox_mandb;
	extern unsigned long mbox_keyb;
#endif
   extern   char _STR_LOCK[];

monitor()
{
short car;
long    s;

#if defined (SYS_MMI)
static char *systype=" -    M M I    - ";
#else
  #if defined (SCADA)			// definizione stringa di sistema
    static char *systype=" -    S C A D A    - ";
  #endif
#endif

static  char *titolo=" - PSCS:   REAL TIME MENU - ";
short new_input=0;

#ifdef MMI_VGA
rew(mbox_mandb,0,&s);		/** attesa prima commutazione tastiera */
#endif
 
for(;;)
 	{
	clrscr() ;
#if defined (VERSIONE)
	scrxy(2,40);
	printf("%s",VERSIONE);
#endif
   
	scrxy(4,1);
	printf("Software Release ....>  %s ",(_STR_LOCK+7));
#if defined (SYS_MMI)
#else
	scrxy(1,1);
	printf("Data Base Reference: %s",h_db.nome);	  	// Utente
	scrxy(2,1);
	printf("Data Base Release ...>  %s ",h_db.release) ; 
	scrxy(3,1);
	printf("Data Base Date  .....>  %d-%d-%d  %2d:%2d:%2d ",
			h_db.data.day,h_db.data.month,h_db.data.year,
			h_db.ora.hour,h_db.ora.minute,h_db.ora.second) ;
	scrxy(4,1);
#endif

   scrxy(6,(80-strlen(titolo))/2);
   printf("%s",titolo);

   scrxy(7,(80-strlen(titolo))/2);
   printf("%s",systype);

#if defined (SYS_MMI)
#else
   scrxy(12,20);
   printf(" M )   MANDB ");
#endif

   scrxy(14,20);
   printf(" D )   DEBUGGER ");
   scrxy(16,20);
   printf(" Q )   DOS ");

#ifdef MMI_VGA
   scrxy(18,20);
   printf(" O )   VIDEO OPERATORE");
#endif

LEGGI:

   if (SYS_DUALE)
      {
	   scrxy(1,52);
#if defined (SYS_MMI)
#else
	   if(sys_master) 
         printf("system : MASTER");
   	else 
         printf("system : SLAVE");
		scrxy(1,70);
	   if(bitvalue(&dbdd[sysab],g2di_sl)) 
         printf(" - B ");
	   else 
         printf(" - A ");
#endif
      }
   car=get_key(&s);
   if(car==81 || car== 113)    // Q 
	   {
	   clrscr();
	   scrxy(0,0);
#if defined (SYS_MMI)
#else
 #if defined (AC_INETDUALE) 
      InetEnd();					// fine comunicazioni Inet
 #endif
#endif
	   scd();
      if(NET_ABIL)
         NetMarteEnd();          // chiusura comunicazione rete Etehernet
#if defined (SYS_MMI)
      closegestkey();
#endif

      RestIDT();                       // ripristino IDT DOS (era stata salvata
                                 // da beg_marte con SaveIDT)
#if defined (SYS_MMI)
		cclosevideo();				// clear video matrox
		cinitvideo();
		cclosevideo();				// clear video matrox
#else
      rwdbal(1,&h_db,&h_db);
      allocdb(1,&h_db);
#endif
#if defined (MMI_VGA)
	   close_video();
#endif
	   exit(END_ERR);// fa anche close_all
	   }    
   else 
      if(car==77 || car==109  )  	 		/* M   attivazione mandb */
	      {
#if defined (SYS_MMI)
#else
	      mandb();						  //abilito task mandb
#endif
	      }
      else 
         if(car==68 || car==100)   
            rtdebug();
#ifdef MMI_VGA
         else 
         if(car=='o' || car=='O') 
	         {
		/* commutazione a operatore */
	         tra(mbox_keyb,-1);
		/* attesa ritorno a sistemista */
	         rew(mbox_mandb,0,&s);
	         }
#endif
   }  
}

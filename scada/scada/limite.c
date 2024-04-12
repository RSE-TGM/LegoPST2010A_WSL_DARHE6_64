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
// corretta per 386 32 bit

/*  ->RTDEBUG.C
 *			effettua una funzione di debug in real time ;
 *			comandi accettati e relative funzioni svolte:
 *			>>D XXXXXXXX 		  = dump ciclico in memoria;l'indirizzo va specificato
 *										 in notazione esa.
 *										 Viene visualizzato un blocco di 128 byte e rinfrescato
 *										 ogni secondo.
 *										 Se non Š specificato l'indirizzo viene visualizzato
 *										 il blocco successivo.
 *			>>E XXXXXXXX 			= modifica dei valori in memoria a partire dall'indiriz_
 *										  zo specificato. Vengono visualizzati i valori attuali
 *										  in memoria un byte alla volta.
 *										  E'possibile : - inserire un nuovo valore.
 *															 - tornare al byte precedente digitando
 *																il segno '-'.
 *															 - uscire dalla modalit… di inserimento
 *																battendo RETURN.
 *										  Le operazioni di modifica sono possibili all'interno
 *										  di un blocco di 128 byte.	
 */
#define YIN 5					/* ordinata iniziale dalla quale viene visualizzato il
										blocco di memoria */
#include <dos.h>
#include <string.h>
#include <pharlap.h>
#include <hw386.h>

#undef TRUE

#include "pscs.cfg"


/* get_limit_ldt ritorna il limite del segmento il cui selettore Š passato
   come parametro. Legge nella LDT il descrittore del segmento e calcola il
   limite concatenando i campi 0_15 e 16_19. Se il bit di granulosit… Š a 1
   il limite viene shiftato di 12 a sinistra ed incrementato di FFF.
   La funzione ritorna 0 se il selettore non Š in LDT. 


unsigned long get_limit_ldt(unsigned short segmento)

CD_DES desc;
unsigned long segment;
#define bit_g_ltd 0x80   // bit di granulosit… nel descrittore di segmento

{
if (_dx_ldt_rd(segmento,(UCHAR *)&desc))
   {
   return 0;
   }
   else
   }
   get_limit=((unsigned long)(desc.limit16_19 & 0x80))*65536+(unsigned long)desc.limit0_15;

// se bit granulosit…=1 shl di 12 bit

   if (desc.limit16_19 & bit_g_ltd) get_limit_ldt=(get_limit_ldt+1)*4096-1;
   }
}

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

#include "ansiscr.h"
#include "ctasti.inc"

#define L_COM 10				/* lunghezza massima stringa di comando */
char visbuf[128];				/* buffer che conterr… l'area di memoria da visualizzare */

unsigned long get_limit_ldt(unsigned segmento);

extern char *exitmem;
extern char *esamem;
extern char *dummem;
extern char *dusmem;

rtdebug()	  
{
char comando[L_COM+1];
char  *ind;
short t_out;
unsigned long of,obuf;
unsigned long ofser;
extern int wtcb, wmbox, queue_des;

int *temp;

static char *titolo="  PSCS2  -  DEBUGGER  ";
short mess;
short letti,i;
of=0;
ind=visbuf;
obuf=FP_OFF(ind);
clrscr();
scrxy(0,(80-strlen(titolo))/2);
printf("%s",titolo);
for(;;)
 {
INIZIO:
 do
 	{
 	scrxy(22,1) ;
	deleol() ;
	printf(">>");
	letti=rdpb(3,22,comando,L_COM,0);
	}
 while(letti==0);
 i=1;
 if(comando[1]!=' ' && comando[1]!=0) goto INIZIO;

/* se la stringa di ingresso ha uno
	spazio dopo la prima lettera va decodificato		
   l'indirizzo				*/

 if(comando[1]==' ')   		
 	{
   switch (comando[2])
		{
      case 'T':
      case 't':
	     {
			temp= &wtcb;
		   of= FP_OFF(temp);
			break;
		  }
      case 'M':
      case 'm':
	     {
			temp= &wmbox;
		   of= FP_OFF(temp);
			break;
		  }
      case 'Q':
      case 'q':
	     {
			temp= &queue_des;
		   of= FP_OFF(temp);
			break;
		  }
 	  default:
      if (decind(&comando[2],&of)) goto INIZIO;	//indirizzo non corretto riparto
 	  }
   }
 scrxy(10,5);

// filtro indirizzi non appartenenti al segmento 

 if (get_limit_ldt(FP_SEG(wtcb))<of+128) of=get_limit_ldt(FP_SEG(wtcb))-128;
 movedata(FP_SEG(of),of,FP_SEG(obuf),obuf,128);
 switch(comando[0])
 	{
	case 'D':					/* visualizzazione blocco di memoria */
	clrscr();	
	scrxy(0,(80-strlen(titolo))/2);
	printf("%s",titolo);
	scrxy(16,YIN) ;
	deleol();

	VIS:
// filtro indirizzi non appartenenti al segmento 

   if (get_limit_ldt(FP_SEG(wtcb))<of+128) of=get_limit_ldt(FP_SEG(wtcb))-128;
   movedata(FP_SEG(of),of,FP_SEG(obuf),obuf,128);
  	visblock(of,visbuf);
/*
	attesa con time out alla mailbox di comunicazione con rtmenu:
	rtmenu attende che venga premuto un tasto 
	Se il tasto non viene premuto entro il time out	cicla nella visualiz-
	zazione del blocco.
*/
		t_out=getkey_wait(20,&mess,&i);	
		if(t_out) goto VIS;	/* se Š scattato il time out va a VIS */
		if(mess==ESC) return;
									  /* incrementa l'indirizzo 								*/
		of+=128;
		break;

	case 'E': 
		ofser=of;								/* salva offset blocco
														prima delle modifiche			*/
		clrscr();
		scrxy(0,(80-strlen(titolo))/2);
		printf("%s",titolo);
		vmbyte(&of,visbuf);			/* visualizza e modifica byte  */

   if (get_limit_ldt(FP_SEG(wtcb))<of+128) of=get_limit_ldt(FP_SEG(wtcb))-128;
      movedata(FP_SEG(obuf),obuf,FP_SEG(ofser),ofser,128);
 		                     	   /* copia le modifiche effettuate 	*/
		break;
	case 'H':
		clrscr();
		scrxy(1,20);
		printf("H E L P");
		scrxy(3,2);
		printf(exitmem);
		printf(esamem);
		printf(dummem);
		printf(dusmem);
		printf("\nD T TCB");
		printf("\nD M WMBOX");
		printf("\nD Q QUEUE");
//		printf("\n\nIndirizzi in notazione esadecimale.");
//		printf("\nGli indirizzi esterni al segmento sono filtrati.");
		break;
	case 'Q':
		return;
	}
 }
}


/* get_limit_ldt ritorna il limite del segmento il cui selettore Š passato
   come parametro. Legge nella LDT il descrittore del segmento e calcola il
   limite concatenando i campi 0_15 e 16_19. Se il bit di granulosit… Š a 1
   il limite viene shiftato di 12 a sinistra ed incrementato di FFF.
   La funzione ritorna 0 se il selettore non Š in LDT.                      */         

unsigned long get_limit_ldt(unsigned segmento)

#define bit_g_ltd 0x80   // bit di granulosit… nel descrittore di segmento

{
CD_DES desc;
unsigned int limite;

if (_dx_ldt_rd((unsigned short)segmento,(UCHAR *)&desc))
   {
   limite=0;
   return (limite);
   }
   else
   {
   limite=((unsigned long)(desc.limit16_19 & 0x80))*65536+(unsigned long)desc.limit0_15;

// se bit granulosit…=1 shl di 12 bit

   if (desc.limit16_19 & bit_g_ltd) limite=(limite+1)*4096-1;
   }
   return (limite);
}

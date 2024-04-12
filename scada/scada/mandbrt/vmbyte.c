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

#define XIN 15
#define YIN 5
#define XFIN 57		  /* posizione ultimo valore inserito su una riga 	*/
#define YFIN 21		  /* ultima riga */

#include "ansiscr.h"

vmbyte(unsigned int *of,unsigned char *buf)
{
unsigned char servbuf[10];
char indietro;				/* flag che indica se si sta procedendo all'indietro
									e quindi non Š necessario riscrivere l'indirizzo */
short val;					/* nuovo valore da inserire			*/
short i,j,letti;
char c[3];				/* caratteri in input da tastiera 	*/
short x,y,ibuf;	/* posizione sullo schermo e posizione all'interno del buffer */
x=XIN;y=YIN;
indietro=0;
ibuf=0;
for(j=0;j<16;j++)				 // pulisce la zona di schermo utilizzata per la
	{								 // visualizzazione del blocco di memoria    
	scrxy(0,YIN+j) ;
	deleol() ;
	}
for(;;)
	{
	if(x==XIN && !indietro)					/* se si Š ad inizio riga scrive l'indirizzo		*/
		{
//		sprintf(servbuf,"%.4x",*seg);
//		servbuf[4]=':';
		sprintf(&servbuf[0],"%.8x",*of);
		scrxy(y+1,2);
		printf("%s",servbuf);
									/* incrementa l'indirizzo								*/
		if((*of)>=0xfffffffff) (*of)=0;	  /* se l'offset Š FFFFFFFF lo azzero */
			(*of)+=8;
		}
									/* visualizza il byte									*/
	sprintf(&servbuf[0],"%.2x.",buf[ibuf]);
	scrxy(y+1,x);
	printf("%s",servbuf);
RIPETI:
	letti=rdpb(x+3,y+1,c,2,0);
	if(letti==0) 	 /* se return  esce dalla modalit… di modifica	*/
		return;
	if(c[0]=='-')	 /* ritorno al byte precedente  	*/
		{
		indietro=1;
		scrxy(y+1,x);
		printf("    ");	/* cancella l'ultimo valore scritto */
		if(x > XIN)
			{
			ibuf--;
			x-=6;
			}
		else 
			{
			if(y > YIN)
				{
				ibuf--;
				y--;
				x=XFIN;
				}
			}
		scrxy(y+1,x+3);
		printf("   "); 	/* cancella il campo occupato dal valore sostituito */
	 	}
	else								 /* caso di inserimento normale  */
		{
		indietro=0;
		if(sscanf(c,"%x",&val)!=1) 	 /* se 1 errore inserimento dati */
			{
			scrxy(y+1,x+3);
			printf("  ");
			goto RIPETI;
			}
		else 					/* Š stato inserito un valore valido: mi sposto 
								alla posizione successiva						*/
	  		{
			buf[ibuf]=(char)val;	 /* inserisce il valore nel buffer 	*/
	  		if(x < XFIN)
	  			{
				ibuf++;
	  			x+=6;
				}
	  		else 
	  			{
				if(y < YFIN)	/* passa alla prossima riga solo se non Š esaurito 
								il blocco 													*/
					{
					ibuf++;
					y+=1;
		   		x=XIN;
					}
				}
	  		}
	 	}
	}
}

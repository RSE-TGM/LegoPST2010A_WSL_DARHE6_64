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
/* ->RDPD.C
 *		NB: VERSIONE DOS : utilizza il driver ANSI.
 *		legge una stringa in input.
 *		chiamata:
 *				rdp(xin,yin,buff,maxlun,mod);
 *		con:
 *				xin,yin = colonna e riga di inizio input stringa
 *				buff = puntatore al buffer in cui verr… inserita la stringa o
 *						 in cui Š gi… presente una stringa da modificare
 *				maxlun = massima lunghezza ammissibile per la stringa in ingresso.
 *							se maxlun Š settato a 0 viene acquisito un singolo carattere
 *							senza conferma con return e senza visualizzazione.
 *							Il carattere Š posto in stringa[0]. 
 *				mod = specifica il modo di funzionamento.
 *		valore di ritorno : numero di caratteri letti ( 0 in funzionamento
 *								  con maxlun = 0.	
 *		modi di funzionamento:
 *					- modifica :(mod=1)	la stringa viene ripresentata sullo schermo
 *									e modificata in base agli input da tastiera.
 *					- normale :(mod=0) non vi Š una stringa di partenza.
 *		uscita con : return -> memorizzazione in buffer della stringa ; la
 *									  funzione ritorna il numero di caratteri letti
 *									  se solo return ritorna il valore 0.	
 *						 escape -> la funzione ritorna il valore 0 e nel caso
 *									  di modifica ripresenta la stringa di partenza
 *									  in quello normale cancella la stringa.
 */

#include <stdio.h>
#include <string.h>

#include "ansiscr.h"		   /* parametri per gestione video */
#include "ctasti.inc"

#define LMAX 41   	/* lunghezza massima ammissibile per la stringa in input */

int rdpb(xin,yin,buff,maxlun,mod)
short xin,yin;						  /* coordinate di partenza scrittura stringa */
char* buff;
short maxlun;
char mod;
{
char string[LMAX];				  /* stringa di servizio per visualizzazione */
char *pstring;
short i_str;	 /* indice che scorre la stringa				*/	
short ii;		 /* indice di servizio						 	*/
static char ins=0;	/* flag che indica se si Š in modalit… INS(=1) o normale (=0) */
short s;
short car;
short x,xfin;								  /* posizione corrente del cursore				*/	
xfin=xin+maxlun;
i_str=0;
string[0]=0;
pstring=string;
x=xin;
scrxy(yin,xin);
/*
      se in modifica scrive la stringa in input e la copia nella stringa di servizio
*/
/* se Š specificata una lunghezza massima di 0 viene acquisito un singolo
	carattere senza bisogno di return e senza visualizzazione												*/
if(!maxlun){buff[0]=get_key(&s);buff[0]=toupper(buff[0]); return(0);}
if(mod) 
	{
	while(buff[i_str])
		{string[i_str]=buff[i_str];putchar((int)buff[i_str++]);
		x++;
		scrxy(yin,x);}	
	ii=i_str;
	while(ii<=maxlun) string[ii++]=0;
	}
else memset(string,0,maxlun+1);
while(1)
	{
	car=get_key(&s);
	if(car!=0)	 		
		{
		switch(car)
			{
			case CR:
				if(ins)
					{string[++i_str]=0;x++;}
				else
					string[i_str]=0;
				strcpy(buff,string);
				scrxy(yin,x);
				deleol();				/* cancella fino a fine riga	*/
				return(i_str);
				break;
			case ESC:
				if(mod)			 	/* se in modifica riscrive la stringa */
					{
					scrxy(yin,xin);
					printf("%s",buff);
					x=xin+strlen(buff);
					scrxy(yin,x);
					deleol();
					return(0);
					}
				 else					/* esce annullando la stringa				*/
				 	{
					buff[0]=0;
					scrxy(yin,xin);
					deleol();
					return(-1);
					}
				break;
			case RIT:					/* ritorno indietro cancellando			*/
				if(i_str>0)
					{i_str--;x--;scrxy(yin,x);}	/* torno indietro di una posizione	 */
				ii=i_str;					/* inizializza un indice di servizio */
				do
					{string[ii]=string[ii+1];ii++;}
				while(string[ii]!=0);
				string[ii-1]=' ';string[ii]=0;
				scrxy(yin,xin);
				printf("%s",string);
				scrxy(yin,x);
				string[ii-1]=0;
				break;
			default:
				if (car>31 && car<123)
					{
					if(car>96) car-=32;		 	/* se il carattere Š minuscolo lo converto in maiuscolo */
					if(ins)	/* modalit… inserimento  */
						{
						if(i_str==maxlun)
							string[maxlun-1]=car;
						else 
							{
							ii=strlen(pstring);
							if(ii==maxlun){ii=maxlun-1;putchar('\07');}
							else string[ii+1]=0;
							while (ii>i_str) {string[ii]=string[ii-1];--ii;}
							string[i_str]=car;
							}
						scrxy(yin,xin);
						printf("%s",string);
						scrxy(yin,x);
						}
					else	  /* modalit… sovrapposizione */
						{
						if(i_str<maxlun)
							{
							string[i_str]=car;
							putchar(car);
							x++;
							scrxy(yin,x);
							i_str++;
							}
						else {string[i_str]=0; putchar('\07');}
						}
					break;
					}
			}
		}
	else
		{
		switch(s)
			{
			case DEL:
				if(string[i_str]!=0)
					{
					ii=i_str;					/* inizializza un indice di servizio */
					while(string[ii]!=0)
						{string[ii]=string[ii+1];ii++;}
					string[ii-1]=' ';string[ii]=0;		  /* per cancellare l'ultimo carattere */
					scrxy(yin,xin);
					printf("%s",string);
					scrxy(yin,x);
					string[ii-1]=0;
					}
				break;
			case RIGHT:
				if(i_str<maxlun-1 && string[i_str]!=0)
					{
					i_str++;	x++;
					scrxy(yin,x);
					}
				 break;
			case LEFT:
				if(i_str>0)
					{
					i_str--; x--;
					scrxy(yin,x);
					}
				break;
			case INS:
			   ins=!ins;
				break;
			}
		}
	}
}

/*
   modulo scrivisu.c
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)scrivisu.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <malloc.h>


extern short FINEPAGINA;
extern short fdint;

extern char c[];


/*********************************************************************
*          							                                       *
*			Procedura scrivisufile 			                              *
*          							                                       *
* 	La procedura serve per inserire sul file di listing o su          *
* quello intermedio a seconda che il primo parametro passato sia     *
* fdlst o fdint ls stringa specificata dal secondo parametro per un  *
* numero di caratteri specificati dal terzo argomento. Viene incre=  *
* mentato il numero di righe scritte nel rispettivo file e se        *
* raggingonmo la dimensione della pagina viene riscritta l' intesta= *
* zione.                                                             *
*          							                                       *
*********************************************************************/

scrivisufile(fdlocale,stringa,quantita,numeror)
short fdlocale;
char stringa[];
short quantita;
short *numeror;
{
short i;
char sp[2];
sp[0]=0x0c;
sp[1]=0x0d;

if(*numeror==FINEPAGINA && fdlocale!=fdint) {
	*numeror=2;
	write(fdlocale,sp,2);
	for(i=0;i<4;i++)
		write(fdlocale,c,2);
}
write(fdlocale,stringa,strlen (stringa));
write(fdlocale,c,2);
if(*numeror!=-1)
	(*numeror)++;
if((strcmp(stringa,c))==0 && *numeror!=-1)
	(*numeror)++;
}


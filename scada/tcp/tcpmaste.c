/*
   modulo tcpmaste.c
   tipo 
   release 1.1
   data 12/1/95
   reserved @(#)tcpmaste.c	1.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	tcpmaster

	Routine utilizzata dalla rete TCP/IP per testare se il sistema
	e' master o slave	e filtrare alcuni messaggi

	Parametri

	short	*	indice messaggio

	Ritorno

	1	se master
	0	se slave

*/

#define NO_STATOSIS	19

int system_master=1;

tcpmaster(mess)
short *mess;
{
	if(*(mess+1)==NO_STATOSIS) return(1);
	return((short) system_master);
}

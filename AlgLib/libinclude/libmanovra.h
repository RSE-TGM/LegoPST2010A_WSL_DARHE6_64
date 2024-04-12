/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
   modulo libmanovra.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)libmanovra.h	5.1
*/
/*

	Il seguente include contiene le definizioni e i tipi delle
	chiamate contenute in libmanovra.a e nel processo ag_manovra
*/

#define ID_MSG_TASKBM		55 /* indice della coda di messaggi
				      fra le task e il processo
				      agg_manovra
				    */
#define ID_MSG_AGG_MANOVRA	56 /* indice coda messaggi fra processo agg_manovra MASTER
				      e SLAVE residenti sulla stessa macchina    */

unsigned float_to_bin(float);
int impacca_bit(char* , float , int);
int print_bit(char *);
int setta_bit(char *, unsigned, int);

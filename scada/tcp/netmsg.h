/*
   modulo netmsg.h
   tipo 
   release 1.1
   data 12/1/95
   reserved @(#)netmsg.h	1.1
*/
/*
   elenco codici messaggi utilizzati da ethernet
*/


#define ONLINE  0
#define OFFLINE 1

#define STATUS    0x0001
#define MODOFF    0x0003
#define MODABIL   0x0005
#define MODDISAB  0x0007

#define STATUS_R   0x0081
#define STATOPORTA 0x0083

#define MMASTER	 0x64			// messaggio linea master

#define NODO_DIAG  -1         // nodo per richiedere la diagnostica


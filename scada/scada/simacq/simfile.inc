/**********************************************************************
*
*       C Header:               simfile.inc
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Dec 16 13:26:04 2002 %
*
**********************************************************************/
/*
     SIMFILE.INC

     contiene le strutture file di svincolo tra nomi simulatore e
     puntatori data base di SSC
     (Simulatore ENEL PC).

     22.09.92  -  Rev. 1.00  -  GM.Furlan
*/
#include <all_1.h>
#if defined OSF1 || defined LINUX
#undef long
#define long int
#endif

/* 
        struttura header file FSVINANA.RTF e FSVINDIG.RTF
*/
typedef struct svinhea {
                long tipopunti;         /* tipo punti */
                long numpunti;          /* numero punti */
                }   SVINHEA;
#define SVINHEA_L sizeof(SVINHEA)

/* numero caratteri nome punto su simulatore */
#define LUN   8 

/* 
        struttura record file FSVINANA.RTF e FSVINDIG.RTF
*/
typedef struct svinrec {
                char sigla[LUN];        /* nome punto su simulatore */
                long punt;      /* puntatore in DB del punto del SSC 
                                   corrispondente al punto del simulatore */
                }   SVINREC;
#define SVINREC_L sizeof(SVINREC)

/* 
        struttura descrittore analogici di output [record file FDEAO.RTF]
*/
typedef struct rec_fdeao_sim  { 
                        short puntdb;      // puntatore in db del comando analogico
			short flabst;      // flag abilitazione in stampa
                        short puntaa;      // puntatore in db dell'analogico comandato
                        char spare[16];    // spare allineamento struttura record generale
			      }  S_FDEAO_SIM;

#define rec_fdeao_sim (sizeof(S_FDEAO_SIM))


/* 
        struttura descrittore digitali di output (comandi) [record file FDCOM.RTF]
*/
typedef struct s_fdcom_sim    {   
                        short comando;    // indice logico comando
                        short tipo;       // tipo comando
                        short organo;     // indice organo associato (o -1)
                        short time;       // time out organo associato (o 0)
                        S_STATI  stat[st_com]; // stati attuale e atteso
                        short abili;      // flag abilitazione in stampa
                        short onoff;      // flag ON/OFF
                        short puntda;     // puntatore in db del digitale comandato
                        char spare[16];   // spare allineamento struttura record generale
                              }  S_FDCOM_SIM;

#define rec_fdcom_sim sizeof(S_FDCOM_SIM)

#if defined OSF1 || defined LINUX
#undef long
#define long long
#endif
#include <all_16.h>

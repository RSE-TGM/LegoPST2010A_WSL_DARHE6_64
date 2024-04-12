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
   modulo mod_data.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)mod_data.h	5.1
*/
/*
   Elenco delle define necessarie per la fase di modifica dei dati 
   riferita al file f14.dat
*/
#define HEADER_SEZ_DATI "*LG*DATI FISICI E GEOMETRICI DEL SISTEMA SUDDIVISI A BLOCCHI"
#define HEADER_BLOCCO_F14       "*LG*DATI DEL BLOCCO "
#define DESCRIZIONE_IN_DATI     "*   "
#define FINE_FILE               "*LG*EOF"
#define OFF_INI_DATO1 14
#define OFF_INI_DATO2 39
#define OFF_INI_DATO3 64
#define OFF_INI_DESC1 4
#define OFF_INI_DESC2 29
#define OFF_INI_DESC3 54
#define OFF_END_DATO1 24
#define OFF_END_DATO2 49
#define OFF_END_DATO3 74
#define OFF_NOME_BLOC_DATI 20
#define LUN_RIGA_F14 134
#define MDAT_I2 1000
#define NCHBL 9
#define NCHFL 20
#define LEGOCAD_PATH "legocad"
#define LIBUT "libut"
#define LUNLEGO 7
#define CARF14 7
#define ESTENS 3
#define MOM "mom"
#define NMAXDATI 500
#define BLOCCO_PROCESSO		1
#define BLOCCO_REGOLAZIONE	2


/*  
    Struttura contenente valore e spiazzamento dei dati
    ricalcolati dalla rotine I2
*/
typedef struct buf_i2
{
int idbufreg;
int nskip;
int inizoff;
#if defined UNIX
float *bufdati;
#else
float bufdati[N007];
#endif
} BUF_I2;

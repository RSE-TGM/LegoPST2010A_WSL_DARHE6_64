/**********************************************************************
*
*	Header %name:	skey_manager3.h %
*	Instance:		1
*	Description:	
*	%created_by:	lomgr %
*	%date_created:	Thu Apr 27 15:21:20 2006 %
*
**********************************************************************/
#ifndef _1_skey_manager3_h_H
#define _1_skey_manager3_h_H

#ifndef lint
static char    *_1_skey_manager3_h = "@(#) %filespec: skey_manager3.h-1 %  (%full_filespec: skey_manager3.h-1:incl:1 %)";
#endif

/* Everything else goes here */
#include "clink.h"
 
// prototiping delle funzioni

int skey_verifica_e_carica3 (int , char *, char *, char *, int * );

// Gestione parametri struttura  chiave

        struct BUFFER
        {
                char nome_prodotto[16];
                char data_scadenza[8];
                char data_ultimo_uso[8];
                char codice_societa[4];
                char spare[12];
        } buff;

#define LICBLOCKDIM sizeof(buff)
#define MAXLICINKEY (int)((DATA_LENGTH + EXTENDED_DATA_LENGTH)/LICBLOCKDIM)

// Gestione errori chiave
#define KEYOK	    0
#define KEYNOTFOUND 1
#define KEYWROPASSW 2
#define DATEBACK    3
#define EXPIREDLIC  4
#define KEYWRITEERR 5
#define KEYNOTVALID 6
#define KEYNOTCESI  7
#define LICNOTFOUND 9

// Gestione flag scrittura su chiave 
#define KEYNOWRITE  0
#define KEYWRITE    1

// Gestione username e password 
#define KEYLABEL    "CESISPA"
#define KEYPASSWD   "CESI5548"

// Gestione sigle prodotti 
#define LICRUNTIME    "ALGRUNTIME"
#define LICMMI    "ALGMMI"
#define LICCONFIG    "ALGCONFIG"
#define LICSCADA    "ALGSCADA"
#define LICLEGOCAD    "ALGLEGOCAD"

// Gestione società 
#define ENELPISA  99
#define CESI      100

#endif

/**********************************************************************
*
*       C Source:               skey_manager3.c
*       Subsystem:              6
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Wed Feb 28 16:31:55 2007 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: skey_manager3.c-4 %  (%full_filespec: skey_manager3.c-4:csrc:1 %)";
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "skey_manager3.h"



// cambiata la funzione per evitare il tes della smartkey

int skey_verifica_e_carica3 (int WriteMode, char label[], char password[], char product[],
				    int * indice_societa) // WriteMode: se R no_write, se W write  
{
	SKEY_DATA skey;               /* SMARTKEY 's parameters structure */

	char data_corr_ascii[9];
	char data_ultimo_uso_ascii[9];
	char data_fin_ascii[9];
	char immagine_chiave[DATA_LENGTH + EXTENDED_DATA_LENGTH];
	struct tm *act_time;
	time_t long_time;
	char Domanda[9];
	unsigned char Risposta[8];
	int i, n_record;
	long data_cor;
	long data_mem;
	long data_fin; 
	int found=0; 


return(KEYNOTFOUND);	// Chiave non trovata


}

int clink(SKEY_DATA *skey) {

}

int skey_verifica_e_carica3_old (int WriteMode, char label[], char password[], char product[],
				    int * indice_societa) // WriteMode: se R no_write, se W write  
{
	SKEY_DATA skey;               /* SMARTKEY 's parameters structure */

	char data_corr_ascii[9];
	char data_ultimo_uso_ascii[9];
	char data_fin_ascii[9];
	char immagine_chiave[DATA_LENGTH + EXTENDED_DATA_LENGTH];
	struct tm *act_time;
	time_t long_time;
	char Domanda[9];
	unsigned char Risposta[8];
	int i, n_record;
	long data_cor;
	long data_mem;
	long data_fin; 
	int found=0; 

	/* Inizialize */
	memset (&skey,0,sizeof(skey));
	/* Set Username & Password*/
	memset (skey.label,'\0',LABEL_LENGTH);
	strncpy(skey.label, label, strlen(label));
	memset (skey.password,'\0',PASSWORD_LENGTH);
	strncpy((char *)skey.password, password, strlen(password));

	
	/* Locating Mode */
	

        skey.command = LOCATING_MODE;
	clink(&skey);
	if ( skey.status != ST_OK )
	{
		return(KEYNOTFOUND);	// Chiave non trovata
	}
	
	/* Scrambling Mode */

	sprintf(Domanda, "12345678");

	Risposta[0] = 0xc4;
	Risposta[1] = 0x24;
	Risposta[2] = 0x07;
	Risposta[3] = 0x73;
	Risposta[4] = 0x25;
	Risposta[5] = 0x04;
	Risposta[6] = 0x8a;
	Risposta[7] = 0xe3;

	skey.command = SCRAMBLING_MODE;

	memcpy(skey.data,Domanda,strlen(Domanda));
	clink(&skey);

	if (skey.status != ST_OK) 
	{
		return(KEYNOTVALID); // Errore interrogazione chiave
	}
	else
	{
		for(i=0; i<8; i++)
		{
			if(skey.data[i] != Risposta[i])
			{
				return(KEYNOTCESI); // Esecuzione non autorizzata
			}
		}
	}		



	/* Reading Mode */

	skey.command = READING_MODE;
	clink(&skey);

	if (skey.status != ST_OK)
		return(KEYWROPASSW);   // errore in username o password
	
	/* Trasferisco i contenuti della chiave nell'apposita immagine */
	memcpy( &immagine_chiave, &skey.data, sizeof(skey.data) );
        memcpy( &immagine_chiave[sizeof(skey.data)], &skey.ext_data, sizeof(skey.ext_data) );


        /* Apro un ciclo di lettura di MAXLICINKEY record dalla chiave */
	found=0;

	for(n_record=0; n_record < MAXLICINKEY; n_record++)
	{
		memcpy( &buff, &immagine_chiave[n_record*sizeof(buff)], sizeof(buff));
		if ( strncmp(buff.nome_prodotto, product, strlen(product)) == 0 )
		{
			found=1;
			break;
		}
	}

	if (found == 0 )
	{
		return(LICNOTFOUND); //Product license not found.
	}


	time(&long_time);
        act_time = localtime(&long_time);
        sprintf(data_corr_ascii,"%04d%02d%02d",
            act_time->tm_year + 1900,
	    act_time->tm_mon + 1,
	    act_time->tm_mday);

	data_cor = atol(data_corr_ascii);
        strncpy(data_ultimo_uso_ascii, buff.data_ultimo_uso, sizeof(buff.data_ultimo_uso));
	data_ultimo_uso_ascii[8]=(char)NULL;
	data_mem = atol(data_ultimo_uso_ascii);

//printf("data_cor = |%d| -  data_mem = |%d|x\n", data_cor, data_mem);
	
	if (data_cor < data_mem)
		return(DATEBACK); // la data corrente �stata spostata indietro!!!!


	strncpy(data_fin_ascii, buff.data_scadenza, sizeof(buff.data_scadenza));
	data_fin_ascii[8]=(char)NULL;
	data_fin = atol(data_fin_ascii);
	
	
	if (data_cor > data_fin)
	{
		return(EXPIREDLIC); // la licenza �scaduta
	}
	*indice_societa = atoi(buff.codice_societa);

    if (WriteMode == 1)
	{
 	    memcpy( &immagine_chiave[24 + n_record*sizeof(buff)], &data_corr_ascii, 
                    sizeof(buff.data_ultimo_uso));
	    /* Writing Mode */
	    skey.command = WRITING_MODE;
	    memcpy(&skey.data, &immagine_chiave, sizeof(skey.data) );
	    memcpy(&skey.ext_data, &immagine_chiave[64],  sizeof(skey.ext_data) );    
	    clink(&skey);
            if (skey.status != ST_OK)
	        return(KEYWRITEERR);   // errore in scrittura della chiave
	}
     return(KEYOK);
}


int skey_stampa_errore(int error_code, char * messaggio_errore)
{
    switch ( error_code)
        {
                case KEYOK:
                        strcpy(messaggio_errore, "SmartKey OK.");
                        break;
                case KEYNOTFOUND:
                        strcpy(messaggio_errore, "SmartKey not found. Please insert your SmartKey in the parallel port.");
                        break;
                case KEYWROPASSW:
                        strcpy(messaggio_errore, "Wrong Username/Password. Check your SmartKey.");
                        break;
                case DATEBACK:
                        strcpy(messaggio_errore, "Error checking the system date. Put the right system date on your PC.");
                        break;
                case EXPIREDLIC:
                        strcpy(messaggio_errore, "The license is expired.");
                        break;
                case KEYWRITEERR:
                        strcpy(messaggio_errore, "Error accessing the SmartKey in updating mode.");
                        break;
                case KEYNOTVALID:
                        strcpy(messaggio_errore, "Error accessing the SmartKey in scrambling mode.");
                        break;
                case KEYNOTCESI:
                        strcpy(messaggio_errore, "Wrong SmartKey scrambling code.");
                        break;
                case LICNOTFOUND:
                        strcpy(messaggio_errore, "Product license not found.");
                        break;
                default:
                return  1;
    }
        return 0;
}


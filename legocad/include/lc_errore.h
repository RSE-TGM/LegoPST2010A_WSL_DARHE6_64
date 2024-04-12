/**********************************************************************
*
*       C Header:               lc_errore.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:02:22 1996 %
*
**********************************************************************/


#ifndef ERRORE_H
#define ERRORE_H
/*
 * Errori che si riferiscono tipicamente al main di legocad
 */

#define COMANDO_ERR "Error executing command:\n%s"

#define MODEL_IN_PROGRESS_ERR "Model construction in progress\n Cannot activate %s"

#define OPEN_F01_ERR "Errore tentando di aprire il file F01 del modello %s"

#define EOF_F01_ERR "Fine del file non attesa per il file F01 del modello %s"

#define READ_F01_ERR "Errore leggendo il file F01 del modello %s"

#define FORMATO_F01_ERR "Il formato del file F01 del modello %s non e' \
corretto"

#define MAX_BL_ERR "Nel modello %s e' stato superato il massimo numero di \
blocchi (%d) previsto \nda questa versione del LEGO"

#define BL_SEQ_ERR "L'ordine dei dati topologici dei blocchi e' diverso \
dall'ordine dei blocchi nell'elenco iniziale.\nIl blocco %s modulo %s e' \
fuori sequenza"

#define TIPO_VAR_ERR "La variabile %s del blocco %s%s non e' ne di stato \
ne di uscita ne d'ingresso."

#define DIFF_BL_CONT_ERR "errore diff %d %d"

#define NO_MODULO_ERR "errore no_modulo %s"

#define OPEN_LIS_MOD_ERR "errore lista moduli %s"

#define OPEN_LIS_SCH_ERR "errore lista schemi %s"

#define MAX_MOD_ERR "errore max. moduli %s"





#ifdef NO_ERROR
#undef NO_ERROR
#endif

#ifdef ERROR
#undef ERROR
#endif



typedef enum _tag_err_level { NO_ERROR, WARNING, ERROR } ERR_LEVEL;




#endif

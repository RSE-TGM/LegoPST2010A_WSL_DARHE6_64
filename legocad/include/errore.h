/**********************************************************************
*
*       C Header:               errore.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:02:40 1996 %
*
**********************************************************************/


#ifndef ERRORE_H
#define ERRORE_H

#define ENV_VAR_ERR  "Environment Variable Not Defined %s"

#define OPEN_F01_ERR "Model %s. Cannot open F01.dat"

#define EOF_F01_ERR "Model %s. F01.dat found EOF"

#define READ_F01_ERR "Model %s. Error reading F01.dat "

#define FORMATO_F01_ERR "Model %s. Invalid format for F01.dat"

#define MAX_BL_ERR "Model %s. MAX block number reached %d"

#define BL_SEQ_ERR "Out of sequences for block %s of module %s" 

#define TIPO_VAR_ERR "Unrecognized variable type %s found in  block %s%s"

#define DIFF_BL_CONT_ERR "Error diff %d %d"

#define NO_MODULO_ERR "%s Module not found"

#define OPEN_LIS_MOD_ERR "Error open %s lista_moduli.dat "

#define OPEN_LIS_SCH_ERR "Error open %s lista_schemi"

#define MAX_MOD_ERR "Max module number reached  %s"

#define PARAMETRI_ERRATI "Error in parameter %s"  




#ifdef NO_ERROR
#undef NO_ERROR
#endif

#ifdef ERROR
#undef ERROR
#endif



typedef enum _tag_err_level { NO_ERROR, WARNING, ERROR ,FATAL_ERROR} ERR_LEVEL;




#endif

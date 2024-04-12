/**********************************************************************
*
*       C Header:               tabelle_malf.h
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Fri Mar 20 15:20:34 1998 %
*
**********************************************************************/

/* 
 * tabelle_malf.h
 */
#ifndef TABELLE_MALF_INCLUDED_
#define TABELLE_MALF_INCLUDED_
/************************************************************************/
#define 	LUN_NOME_TIPO					40
#define	LUN_DESCR_TIPO_BREVE			40
#define	LUN_DESCR_TIPO_LUNGA			100
#define	LUN_DESCR_MALF_BREVE			40
#define	MAX_LUN_KKS						20
#define	MAX_LUN_MODU_CODE				40
#define  LUN_COD_REGO               7
#define  LUN_MOD_NAME               10


#define  MAX_MALF_SET_VALUE         10  /* max 10 valori per malf.      */

#define  FILE_MALF_COMP_TYPE			"tipo_comp_malf.mf"
#define  FILE_MALF_SET              "malf_set.mf"
#define	FILE_MALF_CONFIG           "component.mf"

#define  FILE_FREM_COMP_TYPE        "tipo_comp_malf.fr"
#define  FILE_FREM_SET              "malf_set.fr"
#define  FILE_FREM_CONFIG           "component.fr"

/*
 * Libreria descrittiva dei tipi di componenti soggetti a malfunzionamento
 *	Codifica i componenti per codice numerico e descrittivo, identifica il
 * modulo LEGO/REGO che gestisce il componente, la variabile principale
 * relativa al malfunzionamento e le variabili secondarie
 * NB: malfunzionamento perdita da un tubo: il codice della malf sara' 
 *     di tipo tubo, mentre il blocco sara' relativo alla valvola che
 *     realizzera' la perdita.
 */ 
struct m_comp_type_st
	{ 
	int m_c_t_code;                        /* indice classe della malf	*/
	char m_c_type[LUN_NOME_TIPO];          /* classe della malf in chiaro*/
	char m_c_t_desc[LUN_DESCR_TIPO_BREVE]; /* descrizione breve del tipo */
	char m_c_t_note[LUN_DESCR_TIPO_LUNGA]; /* descrizione lunga del tipo */	
	char module[MAX_LUN_NOME_BLOCCO];      /* sigla tipo modulo abbinato */

	char main_var[MAX_LUN_NOME_VAR];       /* variabile principale       */

	char sec_var_1[MAX_LUN_NOME_VAR];      /* variabile sec. 1           */
	char sec_des_1[MAX_LUN_DESCR_VAR];     /* descriz. var. sec 1        */
	char pertSec1[MAX_LUN_DESCR_VAR];		/* tipo di pert abbinata		*/
	char valPertSec1[MAX_LUN_DESCR_VAR];	/* valore associato alla pert */

   char sec_var_2[MAX_LUN_NOME_VAR];      /* variabile sec. 2           */
   char sec_des_2[MAX_LUN_DESCR_VAR];     /* descriz. var. sec 2        */
	char pertSec2[MAX_LUN_DESCR_VAR];		/* tipo di pert abbinata		*/
	char valPertSec2[MAX_LUN_DESCR_VAR];	/* valore associato alla pert */

   char sec_var_3[MAX_LUN_NOME_VAR];      /* variabile sec. 3           */
   char sec_des_3[MAX_LUN_DESCR_VAR];     /* descriz. var. sec 3        */
	char pertSec3[MAX_LUN_DESCR_VAR];		/* tipo di pert abbinata		*/
	char valPertSec3[MAX_LUN_DESCR_VAR];	/* valore associato alla pert */

   char sec_var_4[MAX_LUN_NOME_VAR];      /* variabile sec. 4           */
   char sec_des_4[MAX_LUN_DESCR_VAR];     /* descriz. var. sec 4        */
	char pertSec4[MAX_LUN_DESCR_VAR];		/* tipo di pert abbinata		*/
	char valPertSec4[MAX_LUN_DESCR_VAR];	/* valore associato alla pert */
	};
typedef struct m_comp_type_st M_COMP_TYPE;
/*
 * Libreria che elenca, per ogni tipo di componente, i valori possibili
 * della variabile principale associati alla descrizione
 */
struct malf_set_st
   {
   int m_s_value;                         /* valore variabile principale*/
   int m_c_t_code;                        /* codice tipo di componente  */
   char m_s_descr[LUN_DESCR_MALF_BREVE];  /* descrizione del valore     */
   };
typedef struct malf_set_st MALF_SET;

/*
 * Istanza dei singoli malfunzionamenti
 * 
 */
struct m_component_st
	{
/*	int m_c_code; valore run-time (non in conf)*//* valore variabile principale*/
	int m_c_t_code;                        /* indice della classe della malf */
	char m_c_desc[LUN_DESCR_MALF_BREVE];   /* descrizione breve malf.    */
	char comp_code[MAX_LUN_KKS];           /* codice KKS del comp.       */
	char modu_code[MAX_LUN_MODU_CODE];     /* codice REGO/LEGO del modulo*/
	char modu_code1[MAX_LUN_MODU_CODE];     /* codice della var sec 1		*/
	char modu_code2[MAX_LUN_MODU_CODE];     /* codice della var sec 2    */
	char modu_code3[MAX_LUN_MODU_CODE];     /* codice della var sec 3    */
	char modu_code4[MAX_LUN_MODU_CODE];     /* codice della var sec 4    */

	char cod_rego[LUN_COD_REGO];           /* codice rego                */
   char label_main_var[MAX_LUN_NOME_VAR]; /* label variabile principale */
   int  p_main_var;                       /* indice in variabili        */
   int  ind_main_var;                     /* indice in variabili        */
   char label_sec_var_1[MAX_LUN_NOME_VAR];/* label variabile secondaria */
   int  p_sec_var_1;                      /* indice in variabili        */
   int  ind_sec_var_1;                    /* indice in variabili        */
   char label_sec_var_2[MAX_LUN_NOME_VAR];/* label variabile secondaria */
   int  p_sec_var_2;                      /* indice in variabili        */
   int  ind_sec_var_2;                    /* indice in variabili        */
   char label_sec_var_3[MAX_LUN_NOME_VAR];/* label variabile secondaria */
   int  p_sec_var_3;                      /* indice in variabili        */
   int  ind_sec_var_3;                    /* indice in variabili        */
   char label_sec_var_4[MAX_LUN_NOME_VAR];/* label variabile secondaria */
   int  p_sec_var_4;                      /* indice in variabili        */
   int  ind_sec_var_4;                    /* indice in variabili        */
	};
typedef struct m_component_st M_COMPONENT;

/*
 *   struttura contenente il nome di una task (mod_name) e il puntatore
 *   (ind_var) alla prima variabile della task salvata nella struttura di
 *   tipo VARIABILI.
*/
struct ind_variabili 
        {
   unsigned short ind_mod;
   char           nome_mod[LUN_MOD_NAME];
   int            ind_var;
        };
typedef struct ind_variabili IND_VARIABILI; 


/************************************************************************/
#endif

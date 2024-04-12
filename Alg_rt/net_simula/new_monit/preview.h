/**********************************************************************
*
*       C Header:               preview.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:41:59 1997 %
*
**********************************************************************/

/*
 * preview.h
 */
#ifndef PREVIEW_INCLUDED
#define PREVIEW_INCLUDED
/*******************************************************************/
#define MAX_LUN_DESCR_VIEW    60

#ifndef MAX_LUN_NOME_VAR
#define MAX_LUN_NOME_VAR 9
#endif

#define NON_NOTA		-1

char c_num[MAX_VIEW_ENTRY][3];

struct preview_data_st
	{
	int nentry;									/* numero di entry in display */
	int entry_valida[MAX_VIEW_ENTRY];   /* entry occupata             */
	Boolean	tb_stat[MAX_VIEW_ENTRY];   /* stato dei bottoni          */
	char label[MAX_VIEW_ENTRY][MAX_LUN_NOME_VAR]; /* label selezionata */
	char descrizione[MAX_VIEW_ENTRY][MAX_LUN_DESCR_VIEW]; 
													/* descrizione in display   */
	int puntatore[MAX_VIEW_ENTRY];      /* indirizzo in database      */
	};
typedef struct preview_data_st PREVIEW_DATA;

struct lista_var_st
	{
	char var_view[MAX_VIEW_ENTRY][MAX_LUN_NOME_VAR];  
	};
typedef struct lista_var_st LISTA_VAR;

/*******************************************************************/
#endif
